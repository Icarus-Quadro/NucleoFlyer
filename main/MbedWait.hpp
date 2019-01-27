#pragma once

#include <platform/mbed_wait_api.h>

struct MbedWait
{
    static void microseconds(int count)
    {
        wait_us(count);
    }
};