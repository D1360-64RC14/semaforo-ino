#include <Arduino.h>
#include <SevSeg.h>

class SevenSegCounter {
    public: // vars
        enum DisplayTypes : uint8_t { COMM_CATHODE, COMM_ANODE };

    private: // vars
        SevSeg display;
        const uint8_t*& pin_array;

    public: // funcs
        SevenSegCounter(
            DisplayTypes display_type,
            const uint8_t*& pin_array
        ): pin_array(pin_array) {
            uint8_t hardware = COMMON_ANODE;

            if (display_type == DisplayTypes::COMM_CATHODE) {
                hardware = COMMON_CATHODE;
            }

            display.begin(hardware, 1, {}, pin_array, true);
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