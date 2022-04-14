#include <Arduino.h>
#include "SevSegCounter.hpp"

using namespace SevSegCounter;

Pins::Pins(
    uint8_t pin_A, uint8_t pin_B,
    uint8_t pin_C, uint8_t pin_D,
    uint8_t pin_E, uint8_t pin_F,
    uint8_t pin_G
):
    pin_array {
        pin_A, pin_B, pin_C,
        pin_D, pin_E, pin_F,
        pin_G
    },
    pin_A(pin_array[0]),
    pin_B(pin_array[1]),
    pin_C(pin_array[2]),
    pin_D(pin_array[3]),
    pin_E(pin_array[4]),
    pin_F(pin_array[5]),
    pin_G(pin_array[6])
{}
