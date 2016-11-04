gemm:
	g++ --std=c++11 gemm.cpp -lmkl_intel_lp64 -lmkl_intel_thread -liomp5 -lmkl_core -lpthread -o gemm

.PHONY : clean
clean:
	-rm gemm
