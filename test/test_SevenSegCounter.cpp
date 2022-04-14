#include <Arduino.h>
#include <unity.h>
#include <SevSegCounter.hpp>

#define ERROR_THRESHOLD 0.1 // %

SevSegCounter::Pins counter_pins(
    5, 6, 9, 8,
    7, 4, 3
);

SevSegCounter::Controller counter(
    SevSegCounter::COMM_ANODE,
    counter_pins
);

void check_end_symbol() {
    TEST_ASSERT_EQUAL(LOW,  digitalRead(counter_pins.pin_A));
    TEST_ASSERT_EQUAL(LOW,  digitalRead(counter_pins.pin_B));
    TEST_ASSERT_EQUAL(LOW,  digitalRead(counter_pins.pin_C));
    TEST_ASSERT_EQUAL(LOW,  digitalRead(counter_pins.pin_D));
    TEST_ASSERT_EQUAL(LOW,  digitalRead(counter_pins.pin_E));
    TEST_ASSERT_EQUAL(LOW,  digitalRead(counter_pins.pin_F));
    TEST_ASSERT_EQUAL(HIGH, digitalRead(counter_pins.pin_G));
}

void test_elapsed_time_ascendent() {
    float true_elapsed_time = 6000; // 100
    float error_line = true_elapsed_time * ERROR_THRESHOLD / 100;

    uint64_t start_time = millis();
    counter.delay(2, 8); // 6 seconds
    uint64_t end_time = millis();

    float elapsed_time = end_time / 1000 - start_time / 1000;

    TEST_ASSERT_LESS_THAN(error_line, abs(elapsed_time - true_elapsed_time));

    check_end_symbol();
}

void test_elapsed_time_descendent() {
    float true_elapsed_time = 6000; // 100
    float error_line = true_elapsed_time * ERROR_THRESHOLD / 100;

    uint64_t start_time = millis();
    counter.delay(8, 2); // 6 seconds
    uint64_t end_time = millis();

    float elapsed_time = end_time / 1000 - start_time / 1000;

    TEST_ASSERT_LESS_THAN(error_line, abs(elapsed_time - true_elapsed_time));

    check_end_symbol();
}

void setup() {
    delay(2000);

    UNITY_BEGIN();
}

void loop() {
    RUN_TEST(test_elapsed_time_ascendent);
    RUN_TEST(test_elapsed_time_descendent);

    UNITY_END();
}
