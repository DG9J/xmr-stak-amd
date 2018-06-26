# This is a test repo for Cryptonight anti-ASIC/FPGA modifications

It's based on the old xmr-stak-amd repo. Only benchmarking is supported. Can run on NVIDIA GPU as well.

### Description and perfrormance tests

Can be found here: https://github.com/SChernykh/xmr-stak-cpu/blob/master/README.md

### Building on Linux
```
sudo apt-get install ocl-icd-opencl-dev libmicrohttpd-dev libssl-dev cmake build-essential
cmake .
make
```

### Building on Windows

You'll need Visual Studio 2017 and NVIDIA CUDA toolkit version 9.2. Why NVIDIA toolkit? It's easier to find and download and the resulting executable will still work on AMD cards without any issues - OpenCL is an open standard after all. After installing it, open xmr-stak-amd.sln and build it in Visual Studio.
