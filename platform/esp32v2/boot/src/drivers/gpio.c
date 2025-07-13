// Minimal GPIO driver for ESP32-C3
// filepath: gpio_minimal.c

#include <stdint.h>
#include <gpio.h>

#define GPIO_BASE               0x60004000
#define GPIO_OUT_W1TS_REG       (GPIO_BASE + 0x08) // Write 1 to set output
#define GPIO_OUT_W1TC_REG       (GPIO_BASE + 0x0C) // Write 1 to clear output
#define GPIO_ENABLE_W1TS_REG    (GPIO_BASE + 0x24) // Write 1 to enable output
#define GPIO_ENABLE_W1TC_REG    (GPIO_BASE + 0x28) // Write 1 to disable output
#define GPIO_IN_REG             (GPIO_BASE + 0x3C) // Read input


void gpio_set_output(uint8_t gpio_num) {
    *((volatile uint32_t*)GPIO_ENABLE_W1TS_REG) = (1 << gpio_num);
}

void gpio_set_input(uint8_t gpio_num) {
    *((volatile uint32_t*)GPIO_ENABLE_W1TC_REG) = (1 << gpio_num);
}

void gpio_write(uint8_t gpio_num, uint8_t level) {
    if (level)
        *((volatile uint32_t*)GPIO_OUT_W1TS_REG) = (1 << gpio_num);
    else
        *((volatile uint32_t*)GPIO_OUT_W1TC_REG) = (1 << gpio_num);
}

uint8_t gpio_read(uint8_t gpio_num) {
    return ((*((volatile uint32_t*)GPIO_IN_REG)) >> gpio_num) & 1;
}

// Example usage:
// gpio_set_output(2);      // Set GPIO2 as output
// gpio_write(2, 1);        // Set GPIO2 high
// gpio_write(2, 0);        // Set GPIO2 low
// gpio_set_input(2);       // Set GPIO2 as input
// uint8_t val = gpio_read(2); // Read GPIO2 level