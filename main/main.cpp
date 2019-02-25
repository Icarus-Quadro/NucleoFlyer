#include "Propeller.hpp"

#include <mbed.h>

#include <chrono>
#include <vector>

constexpr auto kGreenLedId   = LED1;
constexpr auto kBlueLedId    = LED2;
constexpr auto kRedLedId     = LED3;
constexpr auto kUserButtonId = BUTTON1;

constexpr auto kBrownLeftMotorId = PC_6;
constexpr auto kBrownRightMotorId = PB_8;
constexpr auto kWhiteRightMotorId = PB_9;
constexpr auto kWhiteLeftMotorId = PB_15;

extern "C" int main();

auto now() {
    return std::chrono::high_resolution_clock::now().time_since_epoch().count();
}

int main() {
    auto propellers = std::vector<Propeller>{
        kBrownLeftMotorId,
        kBrownRightMotorId,
        kWhiteLeftMotorId,
        kWhiteRightMotorId
    };
    Thread::wait(4000);
    // propeller.write(0.125);
    for(auto& propeller : propellers) {
        propeller.thrust(0.08);
    }
    DigitalOut blueLed(kBlueLedId);
    blueLed = 1;
    Thread::wait(4000);
    for(auto& propeller : propellers) {
        propeller.thrust(0);
    }
    while(true);
    return 0;
}
