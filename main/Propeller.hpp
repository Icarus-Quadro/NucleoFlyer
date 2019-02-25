#pragma once

#include <mbed.h>
#include <rtos.h>

/**
 * Represents propeller connected to a specified pwm pin.
 */

struct Propeller {

    /**
     * Creates instance of a propeller with given pin.
     * After creation it requires some time, around 2-3 seconds,
     * in order to work correctly.
     */
    Propeller(PinName motorId);

    /**
     * Sets amount of thrust for a given propeller.
     * @param thrust - amount of thrust in range 0 to 1
              where 0 means no thrust and 1 maximum power.
              Any value out of this scope is normalized into range.
     */
    void thrust(float thrust);

    /**
     * @return current propeller thrust in range 0 to 1
     *         where 0 means no thrust and 1 maximum power.
     */
    float thrust();

private:
    PwmOut pin_;
};
