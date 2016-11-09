#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/time.h>
#include <string.h>
#include <assert.h>


#define NUM_THREADS 4
#define NUM_BLOCKS 10485760

#define KILO  (1024)
#define MEGA  (1024*1024)
#define GIGA  (1024*1024*1024)

double SeqAccess(int size, int blocksize, int times) {
    assert(size % blocksize == 0);

    char *src = (char *)malloc(size);
    char *dst = (char *)malloc(size);
    memset(src, '?', size);
    int n = size / blocksize;

    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    for (int i=0; i<times; i++) {
        int j = i % n;
        memcpy(dst+j*blocksize, src+j*blocksize, blocksize);
    }
    gettimeofday(&t1, NULL);

    double t = t1.tv_sec-t0.tv_sec + 1e-6*(t1.tv_usec-t0.tv_usec);

    free(src);
    free(dst);

    return t;
}

double RandAccess(int size, int blocksize, int times) {
    assert(size % blocksize == 0);

    char *src = (char *)malloc(size);
    char *dst = (char *)malloc(size);
    memset(src, '?', size);

    srand(time(NULL));
    struct timeval t0, t1;
    gettimeofday(&t0, NULL);
    for (int i=0; i<times; i++) {
        int offset = rand() % (size - blocksize);
        memcpy(dst+offset, src+offset, blocksize);
    }
    gettimeofday(&t1, NULL);

    double t = t1.tv_sec-t0.tv_sec + 1e-6*(t1.tv_usec-t0.tv_usec);

    free(src);
    free(dst);
    return t;
}


int main() {
    char op[256];
    int size, blocksize, times;
    FILE *fout = fopen("memory.out", "w");
    if (!fout) {
        printf("can not open memory.out!\n");
        exit(1);
    }

    printf("%14s%14s%14s%14s%16s\n", "access", "size", "blocksize", "repeat", "time cost (s)");
    fprintf(fout, "%14s%14s%14s%14s%16s\n", "access", "size", "blocksize", "repeat", "time cost (s)");
    while (scanf("%s%d%d%d", op, &size, &blocksize, &times) != EOF) {
        double t = op[0]=='s' ? SeqAccess(size, blocksize, times) :
                                RandAccess(size, blocksize, times);
        printf("%14s%14d%14d%14d%16.10lf\n", op[0]=='s' ? "seq":"rand", size, blocksize, times, t);
        fprintf(fout, "%14s%14d%14d%14d%16.10lf\n", op[0]=='s' ? "seq":"rand", size, blocksize, times, t);
    }

    return 0;
}

