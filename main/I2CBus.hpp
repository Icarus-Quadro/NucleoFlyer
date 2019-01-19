#pragma once

#include <mbed.h>
#include <I2C.h>

struct I2CBus
{
    explicit I2CBus(PinName sda, PinName scl) :
        mDriver(sda, scl)
    {}
    
    void transfer(uint8_t deviceAddress, std::byte const * writeBuffer, size_t writeSize, std::byte * readBuffer, size_t readSize)
    {
        mDriver.write(deviceAddress << 1, reinterpret_cast<char const *>(writeBuffer), writeSize, true); 
        mDriver.read(deviceAddress << 1, reinterpret_cast<char *>(readBuffer), readSize);
    }
private:
    I2C mDriver;
}; 
