#include <Arduino.h>

class TrafficLights {
    public: // vars
        enum STATES : int { RED, YELLOW, GREEN };
        STATES actual_state = STATES::RED;

    private: // vars
        LightPins* light_pins;
        unsigned long yellow_light_threshold;

    public: // funcs
        TrafficLights(
            LightPins* light_pins,
            unsigned long yellow_light_threshold = 20
        ):
            light_pins(light_pins),
            yellow_light_threshold(yellow_light_threshold)
        {
            change_to(STATES::RED);
        }

        void startTimer(unsigned long red_delay_ms, unsigned long green_delay_ms) {
            unsigned long yellow_wait = yellow_light_threshold * red_delay_ms / 100ul;
            unsigned long red_wait = red_delay_ms - yellow_wait;

            change_to(STATES::RED);
            delay(red_wait);

            change_to(STATES::YELLOW);
            delay(yellow_wait);

            change_to(STATES::GREEN);
            delay(green_delay_ms);
        }

        void restart() {
            change_to(STATES::RED);
        }

    private: // funcs
        void change_to(STATES state) {
            actual_state = state;

            clear_lights();

            switch (state) {
                case STATES::RED:
                    digitalWrite(light_pins->light_red, HIGH);
                    if (light_pins->has_ped_lights) digitalWrite(light_pins->pe_light_green, HIGH);
                    break;

                case STATES::YELLOW:
                    digitalWrite(light_pins->light_yellow, HIGH);
                    if (light_pins->has_ped_lights) digitalWrite(light_pins->pe_light_red, HIGH);
                    break;
                
                case STATES::GREEN:
                    digitalWrite(light_pins->light_green, HIGH);
                    if (light_pins->has_ped_lights) digitalWrite(light_pins->pe_light_red, HIGH);
                    break;
                
                default:
                    break;
            }
        }

    private: // funcs
        void clear_lights() {
            digitalWrite(light_pins->light_red, LOW);
            digitalWrite(light_pins->light_yellow, LOW);
            digitalWrite(light_pins->light_green, LOW);

            if (light_pins->has_ped_lights) {
                digitalWrite(light_pins->pe_light_red, LOW);
                digitalWrite(light_pins->pe_light_green, LOW);
            }

        }
};
