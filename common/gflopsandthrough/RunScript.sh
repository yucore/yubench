
gcc CPUBenchmark.c -o CPUBenchmark -l pthread
./CPUBenchmark

gcc DiskBenchmark.c -o DiskBenchmark -l pthread
./DiskBenchmark

gcc MemoryBenchmark.c -o MemoryBenchmark -l pthread
./MemoryBenchmark
