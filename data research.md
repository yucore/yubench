# data research

## Convolution

We analyze the parameters of the convolution layers in the vggnet16, vggnet19, googlent and alexnet with the parameters in the benchmark. Parameters mainly include the length and width of the convolution kernel, the number of channels、pad size and stride size, the number of input image size and other parameters determined by the data set, therefore, in the process of comparison, we mainly compare the parameters of the convolution kernel. The results show that the parameters in the benchmark are not randomly generated, mainly from the vggnet and googlenet.

|      | (w, h,  c, n, k, r, s, pad_w, pad_h, wstride, hstride) | Type                                     |
| ---- | ---------------------------------------- | ---------------------------------------- |
| 1    | (700,  161, 1, 4, 32, 5, 20, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 2    | (700,  161, 1, 8, 32, 5, 20, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 3    | (700,  161, 1, 16, 32, 5, 20, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 4    | (700,  161, 1, 32, 32, 5, 20, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 5    | (341,  79, 32, 4, 32, 5, 10, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 6    | (341,  79, 32, 8, 32, 5, 10, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 7    | (341,  79, 32, 16, 32, 5, 10, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 8    | (341,  79, 32, 32, 32, 5, 10, 0, 0, 2, 2) | Does  not belong to any classical neural network |
| 9    | (480,  48, 1, 16, 16, 3, 3, 1, 1, 1, 1)  | Does  not belong to any classical neural network |
| 10   | (240,  24, 16, 16, 32, 3, 3, 1, 1, 1, 1) | Does  not belong to any classical neural network |
| 11   | (120,  12, 32, 16, 64, 3, 3, 1, 1, 1, 1) | vgg16, vgg19                             |
| 12   | (60,  6, 64, 16, 128, 3, 3, 1, 1, 1, 1)  | vgg16, vgg19, googleNet                  |
| 13   | (108,  108, 3, 8, 64, 3, 3, 1, 1, 2, 2)  | vgg16, vgg19                             |
| 14   | (54,  54, 64, 8, 64, 3, 3, 1, 1, 1, 1)   | vgg16, vgg19                             |
| 15   | (27,  27, 128, 8, 128, 3, 3, 1, 1, 1, 1) | vgg16, vgg19, googleNet                  |
| 16   | (14,  14, 128, 8, 256, 3, 3, 1, 1, 1, 1) | vgg16, vgg19, googleNet, alexnet         |
| 17   | (7, 7,  256, 8, 512, 3, 3, 1, 1, 1, 1)   | vgg16, vgg19                             |
| 18   | (224,  224, 3, 8, 64, 3, 3, 1, 1, 1, 1)  | vgg16, vgg19                             |
| 19   | (112,  112, 64, 8, 128, 3, 3, 1, 1, 1, 1) | vgg16, vgg19, googleNet                  |
| 20   | (56,  56, 128, 8, 256, 3, 3, 1, 1, 1, 1) | vgg16, vgg19, googleNet, alexnet         |
| 21   | (28,  28, 256, 8, 512, 3, 3, 1, 1, 1, 1) | vgg16, vgg19                             |
| 22   | (14,  14, 512, 8, 512, 3, 3, 1, 1, 1, 1) | vgg16, vgg19                             |
| 23   | (7, 7,  512, 8, 512, 3, 3, 1, 1, 1, 1)   | vgg16, vgg19                             |
| 24   | (224,  224, 3, 16, 64, 3, 3, 1, 1, 1, 1) | vgg16, vgg19                             |
| 25   | (112,  112, 64, 16, 128, 3, 3, 1, 1, 1, 1) | vgg16, vgg19, googleNet                  |
| 26   | (56,  56, 128, 16, 256, 3, 3, 1, 1, 1, 1) | vgg16, vgg19, googleNet, alexnet         |
| 27   | (28,  28, 256, 16, 512, 3, 3, 1, 1, 1, 1) | vgg16, vgg19                             |
| 28   | (14,  14, 512, 16, 512, 3, 3, 1, 1, 1, 1) | vgg16, vgg19                             |
| 29   | (7, 7,  512, 16, 512, 3, 3, 1, 1, 1, 1)  | vgg16, vgg19                             |
| 30   | (224,  224, 3, 16, 64, 7, 7, 3, 3, 2, 2) | GoogleNet                                |
| 31   | (28,  28, 192, 16, 32, 5, 5, 2, 2, 1, 1) | GoogleNet                                |
| 32   | (28,  28, 192, 16, 64, 1, 1, 0, 0, 1, 1) | GoogleNet                                |
| 33   | (14,  14, 512, 16, 48, 5, 5, 2, 2, 1, 1) | GoogleNet                                |
| 34   | (14,  14, 512, 16, 192, 1, 1, 0, 0, 1, 1) | GoogleNet                                |
| 35   | (7, 7,  832, 16, 256, 1, 1, 0, 0, 1, 1)  | GoogleNet                                |
| 36   | (7, 7,  832, 16, 128, 5, 5, 2, 2, 1, 1)  | GoogleNet                                |

## GEMM

## yubench research results

In the convolution layers of neural network, we often convert convolution to GEMM. This is done in two steps:

* do an im2col to convert the image to a matrix
* call GEMM to do the actual computation


In the full connected layers of neural network, the size of the image is expanded to 1*1, and the number of neurons is large.

Therefore, we tested the parameters of the convolutional matrix multiplication of caffenet, vggnet and googlenet on caffe 1.0.0-rc3. The results are listed as followed:

***caffenet:***

```
row: 96 col: 3025 vec: 363
row: 96 col: 3025 vec: 1
row: 128 col: 729 vec: 1200
row: 128 col: 729 vec: 1200
row: 256 col: 729 vec: 1
row: 384 col: 169 vec: 2304
row: 384 col: 169 vec: 1
row: 192 col: 169 vec: 1728
row: 192 col: 169 vec: 1728
row: 384 col: 169 vec: 1
row: 128 col: 169 vec: 1728
row: 128 col: 169 vec: 1728
row: 256 col: 169 vec: 1
row: 1 col: 4096 vec: 9216
row: 1 col: 4096 vec: 1
row: 1 col: 4096 vec: 4096
row: 1 col: 4096 vec: 1
row: 1 col: 1000 vec: 4096
row: 1 col: 1000 vec: 1
row: 1000 col: 1 vec: 1
```

***Vggnet:***

```
row: 64 col: 50176 vec: 27
row: 64 col: 50176 vec: 1
row: 64 col: 50176 vec: 576
row: 64 col: 50176 vec: 1
row: 128 col: 12544 vec: 576
row: 128 col: 12544 vec: 1
row: 128 col: 12544 vec: 1152
row: 128 col: 12544 vec: 1
row: 256 col: 3136 vec: 1152
row: 256 col: 3136 vec: 1
row: 256 col: 3136 vec: 2304
row: 256 col: 3136 vec: 1
row: 256 col: 3136 vec: 2304
row: 256 col: 3136 vec: 1
row: 512 col: 784 vec: 2304
row: 512 col: 784 vec: 1
row: 512 col: 784 vec: 4608
row: 512 col: 784 vec: 1
row: 512 col: 784 vec: 4608
row: 512 col: 784 vec: 1
row: 512 col: 196 vec: 4608
row: 512 col: 196 vec: 1
row: 512 col: 196 vec: 4608
row: 512 col: 196 vec: 1
row: 512 col: 196 vec: 4608
row: 512 col: 196 vec: 1
row: 1 col: 4096 vec: 25088
row: 1 col: 4096 vec: 1
row: 1 col: 4096 vec: 4096
row: 1 col: 4096 vec: 1
row: 1 col: 1000 vec: 4096
row: 1 col: 1000 vec: 1
row: 1000 col: 1 vec: 1
```

***Googlenet:***

```
row: 64 col: 12544 vec: 147
row: 64 col: 12544 vec: 1
row: 64 col: 3136 vec: 64
row: 64 col: 3136 vec: 1
row: 192 col: 3136 vec: 576
row: 192 col: 3136 vec: 1
row: 64 col: 784 vec: 192
row: 64 col: 784 vec: 1
row: 96 col: 784 vec: 192
row: 96 col: 784 vec: 1
row: 128 col: 784 vec: 864
row: 128 col: 784 vec: 1
row: 16 col: 784 vec: 192
row: 16 col: 784 vec: 1
row: 32 col: 784 vec: 400
row: 32 col: 784 vec: 1
row: 32 col: 784 vec: 192
row: 32 col: 784 vec: 1
row: 128 col: 784 vec: 256
row: 128 col: 784 vec: 1
row: 128 col: 784 vec: 256
row: 128 col: 784 vec: 1
row: 192 col: 784 vec: 1152
row: 192 col: 784 vec: 1
row: 32 col: 784 vec: 256
row: 32 col: 784 vec: 1
row: 96 col: 784 vec: 800
row: 96 col: 784 vec: 1
row: 64 col: 784 vec: 256
row: 64 col: 784 vec: 1
row: 192 col: 196 vec: 480
row: 192 col: 196 vec: 1
row: 96 col: 196 vec: 480
row: 96 col: 196 vec: 1
row: 208 col: 196 vec: 864
row: 208 col: 196 vec: 1
row: 16 col: 196 vec: 480
row: 16 col: 196 vec: 1
row: 48 col: 196 vec: 400
row: 48 col: 196 vec: 1
row: 64 col: 196 vec: 480
row: 64 col: 196 vec: 1
row: 160 col: 196 vec: 512
row: 160 col: 196 vec: 1
row: 112 col: 196 vec: 512
row: 112 col: 196 vec: 1
row: 224 col: 196 vec: 1008
row: 224 col: 196 vec: 1
row: 24 col: 196 vec: 512
row: 24 col: 196 vec: 1
row: 64 col: 196 vec: 600
row: 64 col: 196 vec: 1
row: 64 col: 196 vec: 512
row: 64 col: 196 vec: 1
row: 128 col: 196 vec: 512
row: 128 col: 196 vec: 1
row: 128 col: 196 vec: 512
row: 128 col: 196 vec: 1
row: 256 col: 196 vec: 1152
row: 256 col: 196 vec: 1
row: 24 col: 196 vec: 512
row: 24 col: 196 vec: 1
row: 64 col: 196 vec: 600
row: 64 col: 196 vec: 1
row: 64 col: 196 vec: 512
row: 64 col: 196 vec: 1
row: 112 col: 196 vec: 512
row: 112 col: 196 vec: 1
row: 144 col: 196 vec: 512
row: 144 col: 196 vec: 1
row: 288 col: 196 vec: 1296
row: 288 col: 196 vec: 1
row: 32 col: 196 vec: 512
row: 32 col: 196 vec: 1
row: 64 col: 196 vec: 800
row: 64 col: 196 vec: 1
row: 64 col: 196 vec: 512
row: 64 col: 196 vec: 1
row: 256 col: 196 vec: 528
row: 256 col: 196 vec: 1
row: 160 col: 196 vec: 528
row: 160 col: 196 vec: 1
row: 320 col: 196 vec: 1440
row: 320 col: 196 vec: 1
row: 32 col: 196 vec: 528
row: 32 col: 196 vec: 1
row: 128 col: 196 vec: 800
row: 128 col: 196 vec: 1
row: 128 col: 196 vec: 528
row: 128 col: 196 vec: 1
row: 256 col: 49 vec: 832
row: 256 col: 49 vec: 1
row: 160 col: 49 vec: 832
row: 160 col: 49 vec: 1
row: 320 col: 49 vec: 1440
row: 320 col: 49 vec: 1
row: 32 col: 49 vec: 832
row: 32 col: 49 vec: 1
row: 128 col: 49 vec: 800
row: 128 col: 49 vec: 1
row: 128 col: 49 vec: 832
row: 128 col: 49 vec: 1
row: 384 col: 49 vec: 832
row: 384 col: 49 vec: 1
row: 192 col: 49 vec: 832
row: 192 col: 49 vec: 1
row: 384 col: 49 vec: 1728
row: 384 col: 49 vec: 1
row: 48 col: 49 vec: 832
row: 48 col: 49 vec: 1
row: 128 col: 49 vec: 1200
row: 128 col: 49 vec: 1
row: 128 col: 49 vec: 832
row: 128 col: 49 vec: 1
row: 1 col: 1000 vec: 1024
row: 1 col: 1000 vec: 1
row: 1000 col: 1 vec: 1
```

## deepbench data

    (1760, 32, 1760, false, false),
    (1760, 64, 1760, false, false),
    (1760, 128, 1760, false, false),
    (1760, 7000, 1760, false, false),
    (2048, 16, 2048, false, false),
    (2048, 32, 2048, false, false),
    (2048, 64, 2048, false, false),
    (2048, 128, 2048, false, false),
    (2048, 7000, 2048, false, false),
    (2560, 16, 2560, false, false),
    (2560, 32, 2560, false, false),
    (2560, 64, 2560, false, false),
    (2560, 128, 2560, false, false),
    (2560, 7000, 2560, false, false),
    (4096, 16, 4096, false, false),
    (4096, 32, 4096, false, false),
    (4096, 64, 4096, false, false),
    (4096, 128, 4096, false, false),
    (4096, 7000, 4096, false, false),
    (1760, 16, 1760, true, false),
    (1760, 32, 1760, true, false),
    (1760, 64, 1760, true, false),
    (1760, 128, 1760, true, false),
    (1760, 7000, 1760, true, false),
    (2048, 16, 2048, true, false),
    (2048, 32, 2048, true, false),
    (2048, 64, 2048, true, false),
    (2048, 128, 2048, true, false),
    (2048, 7000, 2048, true, false),
    (2560, 16, 2560, true, false),
    (2560, 32, 2560, true, false),
    (2560, 64, 2560, true, false),
    (2560, 128, 2560, true, false),
    (2560, 7000, 2560, true, false),
    (4096, 16, 4096, true, false),
    (4096, 32, 4096, true, false),
    (4096, 64, 4096, true, false),
    (4096, 128, 4096, true, false),
    (4096, 7000, 4096, true, false),
    (1760, 7133, 1760, false, true),
    (2048, 7133, 2048, false, true),
    (2560, 7133, 2560, false, true),
    (4096, 7133, 4096, false, true),
    (5124, 9124, 1760, false, false),
    (35, 8457, 1760, false, false),
    (5124, 9124, 2048, false, false),
    (35, 8457, 2048, false, false),
    (5124, 9124, 2560, false, false),
    (35, 8457, 2560, false, false),
    (5124, 9124, 4096, false, false),
    (35, 8457, 4096, false, false),
    (5124, 9124, 1760, true, false),
    (35, 8457, 1760, true, false),
    (5124, 9124, 2048, true, false),
    (35, 8457, 2048, true, false),
    (5124, 9124, 2560, true, false),
    (35, 8457, 2560, true, false),
    (5124, 9124, 4096, true, false),
    (35, 8457, 4096, true, false),
    (7680, 16, 2560, false, false),
    (7680, 32, 2560, false, false),
    (7680, 64, 2560, false, false),
    (7680, 128, 2560, false, false),
    (7680, 16, 2560, true, false),
    (7680, 32, 2560, true, false),
    (7680, 64, 2560, true, false),
    (7680, 128, 2560, true, false),
    (3072, 16, 1024, false, false),
    (3072, 32, 1024, false, false),
    (3072, 64, 1024, false, false),
    (3072, 128, 1024, false, false),
    (3072, 16, 1024, true, false),
    (3072, 32, 1024, true, false),
    (3072, 64, 1024, true, false),
    (3072, 128, 1024, true, false),
    (3072, 7435, 1024, false, true),
    (7680, 5481, 2560, false, true)
## RNN

Since rnn does not have a classical network model, we refer to the cnn model to analyze rnn.

|      | (hidden_state,  batch_size, time_steps, lstm) | Type                                     |
| ---- | ---------------------------------------- | ---------------------------------------- |
| 1    | (1760,  16, 50, false)                   | Does  not belong to any classical neural network |
| 2    | (1760,  32, 50, false)                   | Does  not belong to any classical neural network |
| 3    | (1760,  64, 50, false)                   | Does  not belong to any classical neural network |
| 4    | (1760,  128, 50, false)                  | Does  not belong to any classical neural network |
| 5    | (2048,  16, 50, false)                   | Does  not belong to any classical neural network |
| 6    | (2048,  32, 50, false)                   | Does  not belong to any classical neural network |
| 7    | (2048,  64, 50, false)                   | Does  not belong to any classical neural network |
| 8    | (2048,  128, 50, false)                  | Does  not belong to any classical neural network |
| 9    | (2560,  16, 50, false)                   | Does  not belong to any classical neural network |
| 10   | (2560,  32, 50, false)                   | Does  not belong to any classical neural network |
| 11   | (2560,  64, 50, false)                   | Does  not belong to any classical neural network |
| 12   | (2560,  128, 50, false)                  | Does  not belong to any classical neural network |
| 13   | (512,  16, 25, true)                     | vgg16, vgg19                             |
| 14   | (512,  32, 25, true)                     | vgg16, vgg19                             |
| 15   | (512,  64, 25, true)                     | vgg16, vgg19                             |
| 16   | (512,  128, 25, true)                    | vgg16, vgg19                             |
| 17   | (1024,  16, 25, true)                    | GoogleNet                                |
| 18   | (1024,  32, 25, true)                    | GoogleNet                                |
| 19   | (1024,  64, 25, true)                    | GoogleNet                                |
| 20   | (1024,  128, 25, true)                   | GoogleNet                                |
| 21   | (2048,  16, 25, true)                    | Does  not belong to any classical neural network |
| 22   | (2048,  32, 25, true)                    | Does  not belong to any classical neural network |
| 23   | (2048,  64, 25, true)                    | Does  not belong to any classical neural network |
| 24   | (2048,  128, 25, true)                   | Does  not belong to any classical neural network |
| 25   | (4096,  16, 25, true)                    | Does  not belong to any classical neural network |
| 26   | (4096,  32, 25, true)                    | Does  not belong to any classical neural network |
| 27   | (4096,  64, 25, true)                    | vgg16, vgg19                             |
| 28   | (4096,  128, 25, true)                   | vgg16, vgg19                             |