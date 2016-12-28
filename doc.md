# Documentation of Yubench

## Install & Usage
Install ``nvidia-docker`` first.

Build the ``yubench`` docker image by run command 
```
docker build -t yubench https://raw.githubusercontent.com/yucore/yubench/master/docker/Dockerfile
```

Run 
```
nvidia-docker run -ti yubench
``` 
to start benchmarking.

The result for each mincro-bench will be stored by a csv file in the micro-bench folder, as the following list.
```
yubench/code/common/ffbench/ffbench.csv
yubench/code/common/memory/memory.csv
yubench/code/common/gflopsandthrough/CPUBenchmark.csv
yubench/code/common/gflopsandthrough/DiskBenchmark.csv
yubench/code/common/gflopsandthrough/MemoryBenchmark.csv
```




## Micro-Benchmark Introduction

### Common

- ffbench: Two-dimensional FFT benchmark.[1](https://www.fourmilab.ch/fbench/ffbench.html)
Input format: [number of passes], [size of square matrix].
Output format: [number of passes], [size of square matrix], [time cost(s)].

- memory: Sequential/Random memory & cache read/write benchmark.
Input format: [access type (seq/rand)], [size], [block size], [repeat].
Output format: [access type (seq/rand)], [size], [block size], [repeat], [time cost(s)].

- CPUBenchmark: GFLOPS and IOPS benchmark.[2](https://github.com/snehalhs/Benchmarking)
Input format: [number of threads].
Output format: [number of threads], [flops time], [gflops], [iops time], [giops].

- DiskBenchmark: Sequential/Random disk read/write benchmark.[2](https://github.com/snehalhs/Benchmarking)
Input format: [Blocksize], [number of threands].
Output format: [Blocksize], [number of threands], [SEQ READ/WRITE time(s)], [RAND READ/WRITE Thoughtput(MB/s)], [RAND READ/WRITE time(s)].


- MemoryBenchmark: Multi-thread sequential/random memory read/write benchmark.[2](https://github.com/snehalhs/Benchmarking)
Input format: [Blocksize], [number of threands].
Output format: [Blocksize], [number of threands], [SEQ READ/WRITE time(s)], [RAND READ/WRITE Thoughtput(MB/s)], [RAND READ/WRITE time(s)].

### Nvidia
- gemm: Matrix multiple Benchmark on Nvidia GPU.[3](https://github.com/baidu-research/DeepBench)
Input format: [m], [n], [k], [transform A], [transform B].
Output format: [m], [n], [k], [transform A], [transform B], [time cost(us)].


### Intel
- gemm: Matrix multiple Benchmark on Intel CPU.[3](https://github.com/baidu-research/DeepBench)
Input format: [m], [n], [k], [transform A], [transform B].
Output format: [m], [n], [k], [transform A], [transform B], [time cost(us)].




## Reference
1.https://www.fourmilab.ch/fbench/ffbench.html

2.https://github.com/snehalhs/Benchmarking

3.https://github.com/baidu-research/DeepBench