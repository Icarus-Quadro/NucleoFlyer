#include "Propeller.hpp"

#include <cmath>

namespace {

constexpr auto kMinPulseWidth = 1.f;
constexpr auto kMaxPulseWidth = 2.f;
constexpr auto kFrequency = 450.f;
constexpr auto kMillisInSecond = 1000.f;

float normalize(const float value) {
    return std::max(0.f, std::min(value, 1.f));
}

float thrustToDutyCycle(float thrust) {
    thrust = normalize(thrust);
    const auto pulseWidth = thrust
                            * (kMaxPulseWidth - kMinPulseWidth)
                            + kMinPulseWidth;
    return pulseWidth * kFrequency / kMillisInSecond;
}

float dutyCycleToThrust(const float dutyCycle) {
    const auto pulseWidth = dutyCycle * kMillisInSecond / kFrequency;
    return (pulseWidth - kMinPulseWidth) / (kMaxPulseWidth - kMinPulseWidth);
}

}

Propeller::Propeller(PinName motorId):
pin_(motorId) {
    pin_.period(1 / kFrequency);
    thrust(0);
}

void Propeller::thrust(const float thrust) {
    pin_.write(thrustToDutyCycle(thrust));
}

float Propeller::thrust() {
    return dutyCycleToThrust(pin_.read());
}
