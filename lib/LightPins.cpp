#include <Arduino.h>

class LightPins {
    public: // vars
        const int light_red;
        const int light_yellow;
        const int light_green;

        const int pe_light_red;
        const int pe_light_green;

        const bool has_ped_lights;

    public: // funcs
        LightPins(
            int light_red,
            int light_yellow,
            int light_green,
            int pe_light_red = -1,
            int pe_light_green = -1
        ):
            light_red(light_red),
            light_yellow(light_yellow),
            light_green(light_green),
            pe_light_red(pe_light_red),
            pe_light_green(pe_light_green),
            has_ped_lights(pe_light_red == -1 || pe_light_green == -1 ? false : true)
        {
            pinMode(light_red, OUTPUT);
            pinMode(light_yellow, OUTPUT);
            pinMode(light_green, OUTPUT);

            if (has_ped_lights) {
                pinMode(pe_light_red, OUTPUT);
                pinMode(pe_light_green, OUTPUT);
            }
        }
};
