#include "Propeller.hpp"

#include <mbed.h>

constexpr auto kGreenLedId   = LED1;
constexpr auto kBlueLedId    = LED2;
constexpr auto kRedLedId     = LED3;
constexpr auto kUserButtonId = BUTTON1;

constexpr auto kBrownLeftMotorId = PC_6;
constexpr auto kBrownRightMotorId = PB_8;
constexpr auto kWhiteRightMotorId = PB_9;
constexpr auto kWhiteLeftMotorId = PB_15;

extern "C" int main();

int main() {
    auto propeller = Propeller(kWhiteLeftMotorId);
    auto propeller2 = propeller;
    Thread::wait(4000);
    auto blueLed = DigitalOut(kBlueLedId);
    blueLed = 1;
    while(true);
    return 0;
}
