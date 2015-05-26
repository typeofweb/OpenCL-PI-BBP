# OpenCL-PI-BBP
Bailey–Borwein–Plouffe formula for PI implemented in OpenCL and C++

# Compile
```bash
cmake CMakeLists.txt
make
```

# Run
```bash
./PI2 {FROM} {DECIMAL_PLACES}
```
* `{FROM}` is the first decimal place you want to calculate. The lowest possible value is 1. If you select 1 then output will start with "3." otherwise you'll get only decimal places.
* `{DECIMAL_PLACES}` is how many decimal places you want to calculate

Example input:
```bash
./PI2 1 100
```
output:
```bash
Select platform from given list: 
0. NVIDIA CUDA
1. Intel(R) OpenCL
0
Select device from given list: 
0. GeForce GTX 480
1. GeForce GTS 450
0
Using platform: NVIDIA CUDA
Using device: GeForce GTX 480
1 work groups of size 1024
3.243F6A8885A308D313198A2E03707344A4093822299F31D0082EFA98EC4E6C89452821E638D01377BE5466CF34E90C6CC0AC
Time: 0.004s
```
