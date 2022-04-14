#include <Arduino.h>
#include "TrafficLights.hpp"

using namespace TrafficLights;

Pins::Pins(
    uint8_t light_red,
    uint8_t light_yellow,
    uint8_t light_green
):
    pin_array {
        light_red,
        light_yellow,
        light_green,
        0,
        0
    },
    has_ped_lights(false),

    light_red     (pin_array[0]),
    light_yellow  (pin_array[1]),
    light_green   (pin_array[2]),
    pe_light_red  (pin_array[3]),
    pe_light_green(pin_array[4])
{
    /**
     * 0: red
     * 1: yellow
     * 2: green
    */
    for (uint8_t i = 0; i < 3; i++) {
        pinMode(pin_array[i], OUTPUT);
    }
}

Pins::Pins(
    uint8_t light_red,
    uint8_t light_yellow,
    uint8_t light_green,
    uint8_t pe_light_red,
    uint8_t pe_light_green
):
    pin_array {
        light_red,
        light_yellow,
        light_green,
        pe_light_red,
        pe_light_green
    },
    has_ped_lights(true),

    light_red     (pin_array[0]),
    light_yellow  (pin_array[1]),
    light_green   (pin_array[2]),
    pe_light_red  (pin_array[3]),
    pe_light_green(pin_array[4])
{
    /**
     * 0: red
     * 1: yellow
     * 2: green
     * 3: pe_red
     * 4: pe_green
    */
    for (uint8_t i = 0; i < 5; i++) {
        pinMode(pin_array[i], OUTPUT);
    }
}
