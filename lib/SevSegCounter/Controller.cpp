#include <Arduino.h>
#include "SevSegCounter.hpp"

using namespace SevSegCounter;

Controller::Controller(DisplayTypes display_type, Pins& sevseg_pins):
    display_type(display_type), sevseg_pins(sevseg_pins)
{
    uint8_t hardware = COMMON_ANODE;

    if (display_type == DisplayTypes::COMM_CATHODE) {
        hardware = COMMON_CATHODE;
    }

    display.begin(hardware, 1, {}, sevseg_pins.pin_array, true);

    end();
}

void Controller::delay(uint8_t sec_start, uint8_t sec_end) {
    bool countdown = false;
    uint8_t time_to_pass = sec_end - sec_start;

    if (time_to_pass < 0) {
        time_to_pass = -time_to_pass;
        countdown = true;
    }

    for (uint8_t i = 0; i < time_to_pass; i++) {
        uint8_t actual_sec = countdown ? time_to_pass - i : i;

        display.setNumber(actual_sec);
        display.refreshDisplay();

        // :: é usado para acessar a alternativa global da função.
        ::delay(1000);
    }

    end();
}

void Controller::end() {
    display.setChars("-");
    display.refreshDisplay();
}
