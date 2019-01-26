#include "I2CBus.hpp"

#include <icarus/I2CRegisterBank.hpp>
#include <icarus/MPU9255.hpp>
#include <icarus/AK8963.hpp>
#include <icarus/Aircraft.hpp>
#include <icarus/PIDController.hpp>
#include <icarus/HoverNavigator.hpp>
#include <icarus/KalmanFilter.hpp>
#include <icarus/ElectricMotor.hpp>

#include <mbed.h>
#include <DigitalOut.h>
#include <Thread.h>


DigitalOut led1(LED1);

extern "C" int main();

int main()
{
    I2CBus i2c(PB_9, PB_8);
    
    auto mpu9255Device = icarus::I2CRegisterBank(&i2c, 104);
    auto mpu9255 = icarus::MPU9255(&mpu9255Device);
    mpu9255.initialize();
    mpu9255.i2cBypass(true);

    auto ak8963Device = icarus::I2CRegisterBank(&i2c, 12);
    auto ak8963 = icarus::AK8963(&ak8963Device);
    ak8963.initialize();
    

    icarus::ElectricMotor motors[4];

    auto pid = icarus::PIDController(motors, 4);

    auto filter = icarus::KalmanFilter();

    auto quadro = icarus::Aircraft(&pid, &filter);

    auto navigator = icarus::HoverNavigator();

    quadro.navigator(&navigator);

    std::vector<icarus::SensorReading> readings;

    auto timeToSleep = rtos::Kernel::get_ms_count();
    constexpr auto frequency = 100;

    while (true) {
        mpu9255.read();
        ak8963.read();
        readings.push_back(mpu9255.acceleration());
        readings.push_back(mpu9255.angularVelocity());
        readings.push_back(ak8963.magneticField());

        filter.integrateReadings(readings.data(), readings.size(), 1.0 / frequency);
        readings.clear();

        quadro.fly();

        auto mag = ak8963.magneticField().magneticField * 1000000;
        printf("%fuT %fuT %fuT\n\r", mag[0], mag[1], mag[2]);

        led1 = !led1;
        
        timeToSleep += 1000 / frequency;
        ThisThread::sleep_until(timeToSleep);
    }
}
