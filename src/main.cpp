#define DEBUG true

#include <Arduino.h>
#include <HCSR04.h>

#include "../lib/TrafficLights.cpp"
#include "../lib/LightPins.cpp"


#define LED_RED    2
#define LED_YELLOW 3
#define LED_GREEN  4

#define LED_PE_RED   5
#define LED_PE_GREEN 6

#define SENSOR_TRIGGER 7
#define SENSOR_ECHO    8

UltraSonicDistanceSensor ultrassonic(
    SENSOR_TRIGGER,
    SENSOR_ECHO
);

LightPins light_pins(
    LED_RED,
    LED_YELLOW,
    LED_GREEN,
    LED_PE_RED,
    LED_PE_GREEN
);

TrafficLights traffic_lights(&light_pins);

void setup() {
    Serial.begin(9600);
}

void loop() {
    traffic_lights.change_to(TrafficLights::RED);
    delay(500);

    traffic_lights.change_to(TrafficLights::YELLOW);
    delay(500);

    traffic_lights.change_to(TrafficLights::GREEN);
    delay(500);
}
