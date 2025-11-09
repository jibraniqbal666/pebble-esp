/*
 * FreeRTOS portmacro.h compatibility header
 * 
 * This header provides compatibility for different architectures:
 * - ARM platforms: Include from their respective third_party locations
 * - ESP32: Include ESP-IDF's FreeRTOS portmacro.h  
 */

#ifndef PORTMACRO_H_COMPATIBILITY
#define PORTMACRO_H_COMPATIBILITY

#if defined(MICRO_FAMILY_ESP32_C3)
    // ESP32: Use ESP-IDF's FreeRTOS portmacro.h
    #include "portmacro.h"
    
    // Additional compatibility definitions that might be needed
    #ifndef portTICK_PERIOD_MS
    #define portTICK_PERIOD_MS portTICK_RATE_MS
    #endif
    
#elif defined(MICRO_FAMILY_STM32F2) || defined(MICRO_FAMILY_STM32F4) || defined(MICRO_FAMILY_STM32F7)
    // STM32: Include from third_party FreeRTOS  
    #include "../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#elif defined(MICRO_FAMILY_NRF52840)
    // NRF5: Include from third_party FreeRTOS
    #include "../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#else
    // Default: Try to include from third_party
    #include "../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#endif

#endif // PORTMACRO_H_COMPATIBILITY
