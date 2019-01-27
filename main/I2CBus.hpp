#pragma once

#include <drivers/I2C.h>
#include <stdexcept>
#include "MbedWait.hpp"

struct I2CBus
{
    explicit I2CBus(PinName sda, PinName scl) :
        mDriver(sda, scl)
    {
        mDriver.frequency(400000);
    }
    
    void transfer(uint8_t const deviceAddress, std::byte const * writeBuffer, size_t const writeSize, std::byte * readBuffer, size_t const readSize)
    {
        MbedWait::microseconds(1000);
        if (mDriver.write(deviceAddress << 1, reinterpret_cast<char const *>(writeBuffer), writeSize) != 0) {
            throw std::runtime_error("I2C write failed.");
        }
        if (readSize == 0) return;
        MbedWait::microseconds(1000);
        if (mDriver.read(deviceAddress << 1, reinterpret_cast<char *>(readBuffer), readSize) != 0) {
            throw std::runtime_error("I2C read failed.");
        }
    }
private:
    mbed::I2C mDriver;
}; 
