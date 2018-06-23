# This is a test repo for Cryptonight anti-ASIC/FPGA modifications

It's based on the old xmr-stak-amd repo. Only benchmarking is supported. Can run on NVIDIA GPU as well.

### Steps to build the executable
```
sudo apt-get install ocl-icd-opencl-dev libmicrohttpd-dev libssl-dev cmake build-essential
cmake .
make
```
