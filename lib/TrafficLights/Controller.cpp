#include <Arduino.h>
#include "TrafficLights.hpp"

class TrafficLights::Controller {
    private: // vars
        const Pins& light_pins;
        const uint64_t yellow_light_threshold = 20;
        States actual_state = RED;

        // -- Modules --
        SevSegCounter::Controller* module_sevseg_counter = nullptr;

    public: // funcs
        Controller(Pins& light_pins): light_pins(light_pins) {
            change_to_state(RED);
        }

        Controller(Pins& light_pins, uint64_t yellow_light_threshold):
            light_pins(light_pins),
            yellow_light_threshold(yellow_light_threshold)
        {
            change_to_state(RED);
        }

        void startTimer(uint64_t red_delay_ms, uint64_t green_delay_ms) {
            uint64_t yellow_wait = yellow_light_threshold * red_delay_ms / 100ul;
            uint64_t red_wait = red_delay_ms - yellow_wait;

            change_to_state(RED);
            if (module_sevseg_counter != nullptr) {
                module_sevseg_counter->delay(red_wait / 1000, 0);
            } else {
                delay(red_wait);
            }

            change_to_state(YELLOW);
            delay(yellow_wait);

            change_to_state(GREEN);
            delay(green_delay_ms);
        }

        void restart() {
            change_to_state(RED);
        }

        States get_actual_state() {
            return actual_state;
        }

        void assign_module(SevSegCounter::Controller& sevseg_counter) {
            module_sevseg_counter = &sevseg_counter;
        }

    private: // funcs
        void change_to_state(States state) {
            // 1. Define novo estado;
            actual_state = state;

            // 2. Apaga as luzes;
            clear_lights();

            /**
             * 3. Liga apenas as luzes pertencentes ao estado.
             * 
             * |   Luzes   | Luzes de |
             * | Primárias | Pedestre |
             * |-----------|----------|
             * |  Vermelha | Verde    |
             * |   Amarela | Vermelha |
             * |     Verde | Vermelha |
             */
            switch (state) {
                case States::RED:
                    digitalWrite(light_pins.light_red, HIGH);
                    if (light_pins.has_ped_lights) {
                        digitalWrite(light_pins.pe_light_green, HIGH);
                    }
                    break;
                
                case States::YELLOW:
                    digitalWrite(light_pins.light_yellow, HIGH);
                    if (light_pins.has_ped_lights) {
                        digitalWrite(light_pins.pe_light_red, HIGH);
                    }
                    break;
                
                case States::GREEN:
                    digitalWrite(light_pins.light_green, HIGH);
                    if (light_pins.has_ped_lights) {
                        digitalWrite(light_pins.pe_light_red, HIGH);
                    }
                    break;
                
                default:
                    break;
            }
        }

        void clear_lights() {
            uint8_t scan_range = 3;

            if (light_pins.has_ped_lights) {
                // Se as luzes de pedestre estiverem inclusas, adiciona
                // 'pe_light_red' e 'pe_light_green' ao range do for.
                scan_range += 2;
            }

            // Percorre toda a lista definindo cada pino como LOW. Incluindo os
            // pinos das luzes de pedestre caso a condicional anterior seja
            // verdadeira.
            for (uint8_t i = 0; i < scan_range; i++) {
                digitalWrite(light_pins.pin_array[i], LOW);
            }
        }
};
