#pragma once

#include <mbed.h>

#include <cstdint>

/**
 * Represents SRF05 - sonic distance measurer.
 */

struct SRF05 {
    SRF05() = delete;
    SRF05(const SRF05&) = delete;
    SRF05& operator=(const SRF05) = delete;

    SRF05(PinName trigger, PinName echo);

    /**
     * @return time in microseconds passed from sonic burst emission.
     */
    std::int64_t read();

    /**
     * @return time in microseconds passed from sonic burst emission.
     */
    operator std::int64_t();

private:
    DigitalOut trigger_;
    InterruptIn echo_;
    Timer timer_;
    Ticker ticker_;
    std::int64_t timeGap_;
};
