#include "I2CBus.hpp"
#include "MbedWait.hpp"

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

DigitalOut led1(LED2);
DigitalOut led2(LED3);

extern "C" int main();

int main()
{
    led2 = 1;
    I2CBus i2c(PB_9, PB_8);
    auto mpu9255Device = icarus::I2CRegisterBank(&i2c, 104);
    auto mpu9255 = icarus::MPU9255(&mpu9255Device);
    auto ak8963Device = icarus::I2CRegisterBank(&i2c, 12);
    auto ak8963 = icarus::AK8963<MbedWait, decltype(ak8963Device)>(&ak8963Device);
    wait_ms(1000);
    while (true) {
        try {
            mpu9255.initialize();
            mpu9255.i2cBypass(true);
            break;
            // ak8963.initialize();
        } catch (std::runtime_error const & error){
            printf("\n\r%s", error.what());
        }
    }
    
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
        try {
            mpu9255.read();
            // ak8963.read();
        } catch (std::runtime_error const & error) {
            printf("\n\r%s", error.what());
        }
        
        filter.integrateReadings(readings.data(), readings.size(), 1.0 / frequency);
        readings.clear();

        quadro.fly();

        Eigen::Matrix<float, 3, 1> mag = ak8963.mScale * 1000000;
        printf("$");

        // printf("%fuT %fuT %fuT\n\r", mag[0], mag[1], mag[2]);

        led1 = !led1;
        led2 = !led2;
        
        timeToSleep += 1000 / frequency;
        ThisThread::sleep_until(timeToSleep);
    }
}
