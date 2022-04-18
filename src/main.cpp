#include <Arduino.h>
#include <HCSR04.h>

#include <TrafficLights.hpp>

// Pinos do Semáforo
#define LED_RED    2
#define LED_YELLOW 3
#define LED_GREEN  4

#define LED_PE_RED   5
#define LED_PE_GREEN 6

// Pinos do Sensor Ultrassonico
#define SENSOR_TRIGGER 8
#define SENSOR_ECHO    9

// Configurações de Funcionamento
#define TRAFFIC_DISTANCE         60.0 // cm
#define TRAFFIC_RED_DELAY        10   // seconds
#define TRAFFIC_GREEN_DELAY      10   // seconds
#define TRAFFIC_YELLOW_THRESHOLD 30   // %

UltraSonicDistanceSensor ultrassonic(
    SENSOR_TRIGGER,
    SENSOR_ECHO
);

TrafficLights::Pins light_pins(
    LED_RED,
    LED_YELLOW,
    LED_GREEN,
    LED_PE_RED,
    LED_PE_GREEN
);

TrafficLights::Controller traffic_lights(light_pins, TRAFFIC_YELLOW_THRESHOLD);

void setup() {
    pinMode(13, OUTPUT);

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
        // Processo das luzes iniciado ao veículo entrar no range do sensor.
        Serial.println("Objeto identificado. Iniciando contagem do semáforo.");
        digitalWrite(13, HIGH);

        traffic_lights.startTimer(
            TRAFFIC_RED_DELAY * 1000,
            TRAFFIC_GREEN_DELAY * 1000
        );

        Serial.println("Ciclo de semáforo completo.");
        digitalWrite(13, LOW);
    }
}