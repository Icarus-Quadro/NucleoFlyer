#include "SRF05.hpp"

#include <chrono>

namespace {

using std::chrono::milliseconds;
using std::chrono::microseconds;

using FloatSeconds = std::chrono::duration<float>;

constexpr auto kDigitalOutOn = 1;
constexpr auto kDigitalOutOff = 0;
constexpr auto kAttachTimeInterval = std::chrono::duration_cast<FloatSeconds>(milliseconds(100));
constexpr auto kRangeTimeGap = microseconds(20);

}

SRF05::SRF05(PinName trigger, PinName echo):
trigger_(trigger), echo_(echo){
    echo_.rise([this]() {
        timer_.reset();
        timer_.start();
    });

    echo_.fall([this]() {
        timer_.stop();
        timeGap_ = timer_.read_us();
    });

    ticker_.attach([this]() {
        trigger_ = kDigitalOutOn;
        wait_us(kRangeTimeGap.count());
        trigger_ = kDigitalOutOff;
    }, kAttachTimeInterval.count());
}

std::int64_t SRF05::read() {
    return timeGap_;
}

SRF05::operator std::int64_t() {
    return read();
}
