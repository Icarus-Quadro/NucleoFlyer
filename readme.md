# NucleoFlyer

Nucleo based quadcopter flight controller.

## Installation

Install mbed-cli and gcc-arm-none-eabi. gcc needs to be in PATH.
```
git submodule update --init
mbed new .
mbed export -i cmake_gcc_arm
mkdir build
cd build
cmake .. -DBOOST_ROOT=path_to/boost_version
make
```

## Running 

Copy the freshly built binary onto your Nucleo board. It will flash automatically.
In order to see debug output you need to connect to the serial device. You can use the screen program. Nucleo most commonly shows up as /dev/ttyACM0. Sometimes it can show up as /dev/ttyUSB0 (or some other number). You need to part of dialout group to access the device. You need to pass correct baud rate, otherwise you will just see random garbage.
```
cp build/NucleoFlyer.bin <PLACE_WHERE_NUCLEO_IS_MOUNTED>/NODE_F767ZI/
screen /dev/ttyACM0 921600 
```
