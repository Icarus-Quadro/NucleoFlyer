#include <mbed.h>
#include <DigitalOut.h>

#include "I2CBus.hpp"

#include <icarus/I2CRegisterBank.hpp>
#include <icarus/MPU9255.hpp>

DigitalOut led1(LED1);

extern "C" int main();

int main()
{
    I2CBus i2c(PB_9, PB_8);
    auto mpu9255Device = icarus::I2CRegisterBank(&i2c, 104);
    auto mpu9255 = icarus::MPU9255(&mpu9255Device);
    mpu9255.initialize();

    while (true) {
        mpu9255.read();

        printf("Hello\n\r");
        led1 = !led1;
        wait(1.0);
    }
}