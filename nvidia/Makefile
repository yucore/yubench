gemm:
	nvcc gemm.cu -std=c++11 -lcublas -lcurand -o gemm

.PHONY : clean
clean:
	-rm gemm
