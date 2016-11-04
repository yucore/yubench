echo "nvidia gemm"
cd nvidia && make clean && make gemm && ./gemm < gemm.in && cd ..

echo "intel gemm"
cd intel && make clean && make gemm && ./gemm < gemm.in && cd ..

