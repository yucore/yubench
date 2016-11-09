echo "nvidia gemm"
cd nvidia && make clean && make gemm && ./gemm < gemm.in && cd ..

echo "intel gemm"
cd intel && make clean && make gemm && ./gemm < gemm.in && cd ..

echo "common memory"
cd common/memory && make clean && make memory && ./memory < memory.in && cd ../..

echo "ffbench"
cd common/ffbench && make clean && make && time ./ffbench && cd ../..

