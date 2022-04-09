#include <Arduino.h>
#include <HCSR04.h>

#include <TrafficLights.cpp>


#define LED_RED    2
#define LED_YELLOW 3
#define LED_GREEN  4

#define LED_PE_RED   5
#define LED_PE_GREEN 6

#define SENSOR_TRIGGER 8
#define SENSOR_ECHO    9

#define TRAFFIC_DISTANCE         20.0 // cm
#define TRAFFIC_RED_DELAY        10   // seconds
#define TRAFFIC_GREEN_DELAY      2    // seconds
#define TRAFFIC_YELLOW_THRESHOLD 50   // %

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

TrafficLights traffic_lights(light_pins, TRAFFIC_YELLOW_THRESHOLD);

void setup() {
    Serial.begin(9600);
}

long ultrassonic_distance = 0.0;

void ultrassonic_update() {
    float new_measure = ultrassonic.measureDistanceCm();

    if (new_measure >= 0.0) {
        ultrassonic_distance = new_measure;
    }

    delay(100);
}

void loop() {
    ultrassonic_update();

    if (ultrassonic_distance < TRAFFIC_DISTANCE) {
        traffic_lights.startTimer(TRAFFIC_RED_DELAY * 1000, TRAFFIC_GREEN_DELAY * 1000);

        while (ultrassonic_distance < TRAFFIC_DISTANCE) {
            delay(500);
            ultrassonic_update();
        }

        traffic_lights.restart();
    }
}