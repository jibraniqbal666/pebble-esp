/*
 * ESP32 portmacro.h compatibility stub
 * 
 * Pebble firmware includes "portmacro.h" directly, but ESP-IDF 
 * has it at "freertos/portmacro.h". This stub provides compatibility.
 */

#ifndef PORTMACRO_H_ESP32_STUB
#define PORTMACRO_H_ESP32_STUB

#ifdef MICRO_FAMILY_ESP32_C3

// Include ESP-IDF's FreeRTOS portmacro.h
#include "portmacro.h"

// Additional compatibility definitions that might be needed
#ifndef portTICK_PERIOD_MS
#define portTICK_PERIOD_MS portTICK_RATE_MS
#endif

#endif // MICRO_FAMILY_ESP32_C3

#endif // PORTMACRO_H_ESP32_STUB
