#pragma once

#include <stdint.h>

// Set the given GPIO as output
void gpio_set_output(uint8_t gpio_num);

// Set the given GPIO as input
void gpio_set_input(uint8_t gpio_num);

// Write level (0 or 1) to the given GPIO
void gpio_write(uint8_t gpio_num, uint8_t level);

// Read the current level (0 or 1) from the given GPIO
uint8_t gpio_read(uint8_t gpio_num);