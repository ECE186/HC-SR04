#include <stdio.h>
#include <stdint.h>
#include "pico/stdlib.h"
#include "hardware/gpio.h"
#define TRIG_PIN 13
#define ECHO_PIN 10
#define TIMEOUT_US 30000
float measure_distance_cm(void) {
    // Generate 10 us trigger pulse
    gpio_put(TRIG_PIN, 0);
    sleep_us(2);
    gpio_put(TRIG_PIN, 1);
    sleep_us(10);
    gpio_put(TRIG_PIN, 0);
    // Wait for ECHO to rise
    uint64_t start = time_us_64();
    while (!gpio_get(ECHO_PIN)) {
        if (time_us_64() - start >= TIMEOUT_US)
            return -1.0f;
    }
    // Measure HIGH pulse duration
    uint64_t echo_start = time_us_64();
    while (gpio_get(ECHO_PIN)) {
        if (time_us_64() - echo_start >= TIMEOUT_US)
            return -1.0f;
    }
    uint64_t duration = time_us_64() - echo_start;
    // HC-SR04 approximate conversion
    return (float)duration / 58.0f;
}
int main(void) {
    stdio_init_all();
    gpio_init(TRIG_PIN);
    gpio_set_dir(TRIG_PIN, GPIO_OUT);
    gpio_put(TRIG_PIN, 0);
    gpio_init(ECHO_PIN);
    gpio_set_dir(ECHO_PIN, GPIO_IN);
    // Wait for USB serial connection
    sleep_ms(2000);
    while (true) {
        float distance = measure_distance_cm();
        if (distance < 0.0f) {
            printf("\rTOO FAR/CLOSE       ");
        } else {
            printf("\rDistance: %7.2f cm       ", distance);
        }
        fflush(stdout);
        sleep_ms(50);
    }
    // Using carriage returns and fflush() required the `screen` program on my
    // MacBook, VSCode's native serial monitor shits itself. Erase the while
    // loop above and replace it with this one if that happens with your
    // editor
    /*while (true) {
        float distance = measure_distance_cm();
        if (distance < 0.0f) {
            printf("TOO FAR/CLOSE\n");
        } else {
            printf("Distance: %.2f cm\n", distance);
        }
        sleep_ms(50);
    }*/
}
