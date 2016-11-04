# yubench

A benchmark created for "Yu" (You) to adapt to your very need or general interest.  
With initial focus on deep learning and popular "DL" platforms.


## usage
1. Install nvidia-docker
2. Run following commands to build docker image and run benchmark
```
docker build -t yubench https://raw.githubusercontent.com/yucore/yubench/master/docker/Dockerfile
nvidia-docker run -ti yubench
```
