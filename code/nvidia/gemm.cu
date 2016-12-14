#include <chrono>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <vector>
#include <tuple>
#include <cstdio>

#include <cuda.h>
#include <cublas_v2.h>
#include <curand.h>

#include <thrust/device_ptr.h>
#include <thrust/fill.h>


template<typename T>
class Matrix {
public:
    Matrix(int row, int col):n_row(row), n_col(col), size(row*col) {
        T *tmp;
        if (cudaMalloc(&tmp, size * sizeof(T)) != cudaSuccess) {
            printf("row:%d, col:%d, size:%d\n", row, col, size);
            throw std::bad_alloc();
        }
        data_ptr.reset(tmp, [](T *p){ cudaFree(p); });
    }

    void fillRand(curandGenerator_t curand_gen) {
        curandGenerateUniform(curand_gen, data(), size);    
    }

    void fill(T val) {
        thrust::fill(thrust::device_ptr<T>(data()),
                     thrust::device_ptr<T>(data() + size),
                     val);
    }

    int row() { return n_row; }
    int col() { return n_col; }
    T* data() { return data_ptr.get(); }

private:
    int n_row, n_col, size;
    std::shared_ptr<T> data_ptr;
};





double gemm(Matrix<float> A, Matrix<float> B, Matrix<float> C, bool at, bool bt, cublasHandle_t cublas_handle) {

    const float alpha = 1.0f / A.col(); 
    const float beta = 0; 

    int m = C.row();
    int n = C.col();
    int k = at ? A.row() : A.col();
    int repeats = std::max(1e11/(m*k*n), 10.0);

    // warm up
    if (CUBLAS_STATUS_SUCCESS != cublasSgemm(cublas_handle,
                at ? CUBLAS_OP_T : CUBLAS_OP_N,
                bt ? CUBLAS_OP_T : CUBLAS_OP_N,
                m, n, k,
                &alpha,
                A.data(), A.row(),
                B.data(), B.row(),
                &beta,
                C.data(), C.row())) {
        throw std::runtime_error("sgemm failed in warming up!");
    }
    if (cudaSuccess != cudaDeviceSynchronize()) {
        throw std::runtime_error("device sync error after warming up!");
    }

    // go
    auto t0 = std::chrono::steady_clock::now();
    for (int i=0; i<repeats; i++) {
        cublasStatus_t stat = cublasSgemm(cublas_handle,
                    at ? CUBLAS_OP_T : CUBLAS_OP_N,
                    bt ? CUBLAS_OP_T : CUBLAS_OP_N,
                    m, n, k,
                    &alpha,
                    A.data(), A.row(),
                    B.data(), B.row(),
                    &beta,
                    C.data(), C.row());

        if (stat != CUBLAS_STATUS_SUCCESS) {
            printf("stat: %d\n", stat);
            throw std::runtime_error("sgemm failed!");
        }
    }
    if (cudaSuccess != cudaDeviceSynchronize()) {
        throw std::runtime_error("device sync error!");
    }
    auto t1 = std::chrono::steady_clock::now();

    return std::chrono::duration<double, std::micro>(t1-t0).count() / repeats;
}




int main()
{
    // initialize
    cudaFree(0);
    cublasHandle_t cublas_handle;
    cublasStatus_t status = cublasCreate(&cublas_handle);
    if (status != CUBLAS_STATUS_SUCCESS) {
        printf("CUBLAS init failed!\n");
        exit(1);
    }

    curandGenerator_t curand_gen;
    curandCreateGenerator(&curand_gen, CURAND_RNG_PSEUDO_DEFAULT);
    curandSetPseudoRandomGeneratorSeed(curand_gen, 123ULL);


    FILE *fout = fopen("gemm.csv", "w");
    if (!fout) {
        printf("can't open output file\n");
        exit(1);
    }

    printf("%7s%7s%7s%7s%7s%13s\n", "m", "n", "k", "at", "bt", "time(us)");
    fprintf(fout, "%7s,%7s,%7s,%7s,%7s,%13s\n", "m", "n", "k", "at", "bt", "time(us)");
    int m, n, k;
    while (scanf("%d%d%d", &m, &n, &k) != EOF) {
        bool at, bt;
        char buf[256];
        scanf("%s", buf);
        at = buf[0] == 't';
        scanf("%s", buf);
        bt = buf[0] == 't';


        Matrix<float> a(m, k), 
                      b(at ? m:(bt ? n:k), bt ? k:n), 
                      c(at ? k:m, n); 

        a.fillRand(curand_gen);
        b.fillRand(curand_gen);
        c.fill(0);

        double t = gemm(a, b, c, at, bt, cublas_handle);

        printf("%7d%7d%7d%7c%7c", m, n, k, at ? 't':'n', bt ? 't':'n');
        printf("%13.3lf\n", t);

        fprintf(fout, "%7d,%7d,%7d,%7c,%7c,", m, n, k, at ? 't':'n', bt ? 't':'n');
        fprintf(fout, "%13.3lf\n", t);
    }

    fclose(fout);

    return 0;
}


