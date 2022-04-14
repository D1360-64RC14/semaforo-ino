#include <Arduino.h>
#include "SevSegCounter.hpp"

class SevSegCounter::Controller {
    public: // vars
        const DisplayTypes display_type;

    private: // vars
        SevSeg display;
        const Pins& sevseg_pins;

    public: // funcs
        Controller(
            DisplayTypes display_type,
            Pins& segseg_pins
        ): sevseg_pins(sevseg_pins), display_type(display_type) {
            uint8_t hardware = COMMON_ANODE;

            if (display_type == DisplayTypes::COMM_CATHODE) {
                hardware = COMMON_CATHODE;
            }

            display.begin(hardware, 1, {}, sevseg_pins.pin_array, true);

            end();
        }

        void delay(uint8_t sec_start, uint8_t sec_end) {
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


    private: // funcs
        void end() {
            display.setChars({"-"});
            display.refreshDisplay();
        }
};