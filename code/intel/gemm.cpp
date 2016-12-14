#include <chrono>
#include <iomanip>
#include <memory>
#include <stdexcept>
#include <cstdio>
#include <cstdlib>

#include <mkl.h>


template<typename T>
class Matrix {
public:
    Matrix(int row, int col):n_row(row), n_col(col), size(row*col) {
        T *tmp = (T*)mkl_malloc(size*sizeof(T), sizeof(T));
        if (tmp == NULL) {
            printf("row:%d, col:%d, size:%d\n", row, col, size);
            throw std::bad_alloc();
        }
        data_ptr.reset(tmp, [](T *p){ mkl_free(p); });
    }

    void fillRand() {
        for (int i=0; i<size; i++) {
            data()[i] = rand() / (double)(RAND_MAX);
        }
    }

    void fill(T val) {
        for (int i=0; i<size; i++) {
            data()[i] = val;
        }
    }

    int row() { return n_row; }
    int col() { return n_col; }
    T* data() { return data_ptr.get(); }

private:
    int n_row, n_col, size;
    std::shared_ptr<T> data_ptr;
};





double gemm(Matrix<float> A, Matrix<float> B, Matrix<float> C, bool at, bool bt) {

    const float alpha = 1.0f / A.col(); 
    const float beta = 0; 

    int m = C.row();
    int n = C.col();
    int k = at ? A.row() : A.col();
    int repeats = std::max(1e11/(m*k*n), 10.0);

    // warm up
    cblas_sgemm(CblasRowMajor,
                at ? CblasTrans : CblasNoTrans,
                bt ? CblasTrans : CblasNoTrans,
                m, n, k,
                alpha,
                A.data(), A.col(),
                B.data(), B.col(),
                beta,
                C.data(), C.col());

    // go
    auto t0 = std::chrono::steady_clock::now();
    for (int i=0; i<repeats; i++) {
        cblas_sgemm(CblasRowMajor,
                at ? CblasTrans : CblasNoTrans,
                bt ? CblasTrans : CblasNoTrans,
                m, n, k,
                alpha,
                A.data(), A.col(),
                B.data(), B.col(),
                beta,
                C.data(), C.col());
    }
    auto t1 = std::chrono::steady_clock::now();

    return std::chrono::duration<double, std::micro>(t1-t0).count() / repeats;
}




int main()
{
    // initialize
    srand(time(NULL));
    
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

        a.fillRand();
        b.fillRand();
        c.fill(0);

        double t = gemm(a, b, c, at, bt);

        printf("%7d%7d%7d%7c%7c", m, n, k, at ? 't':'n', bt ? 't':'n');
        printf("%13.3lf\n", t);

        fprintf(fout, "%7d,%7d,%7d,%7c,%7c,", m, n, k, at ? 't':'n', bt ? 't':'n');
        fprintf(fout, "%13.3lf\n", t);
    }

    return 0;
}


