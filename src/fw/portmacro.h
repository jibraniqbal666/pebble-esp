/*
 * FreeRTOS portmacro.h compatibility header
 * 
 * This header provides compatibility for different architectures:
 * - ARM platforms: Include from their respective third_party locations
 * - ESP32: Include ESP-IDF's FreeRTOS portmacro.h  
 */

#ifndef PORTMACRO_H_COMPATIBILITY
#define PORTMACRO_H_COMPATIBILITY

#if defined(MICRO_FAMILY_ESP32_C3) || defined(ESP32_PLATFORM) || defined(ESP32_C3)
    // Define xPORT_TASK_INFO FIRST before any ESP-IDF FreeRTOS headers
    #ifndef xPORT_TASK_INFO
    typedef struct PORT_TASK_INFO
    {
        const char *pcName;
        void *taskHandle;
        unsigned long registers[32]; // RISC-V has 32 general purpose registers
    } xPORT_TASK_INFO;
    #endif
    
    // ESP32: Use ESP-IDF's FreeRTOS portmacro.h
    #include "freertos/FreeRTOSConfig.h"
    #include "freertos/portmacro.h"
    
    // Additional compatibility definitions that might be needed
    #ifndef portTICK_PERIOD_MS
    #define portTICK_PERIOD_MS portTICK_RATE_MS
    #endif
    
    // Ensure BaseType_t is defined for ESP32 builds
    #ifndef BaseType_t
    typedef int BaseType_t;
    typedef unsigned int UBaseType_t;
    #endif
    
#elif defined(MICRO_FAMILY_STM32F2) || defined(MICRO_FAMILY_STM32F4) || defined(MICRO_FAMILY_STM32F7)
    // STM32: Include from third_party FreeRTOS  
    #include "../../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#elif defined(MICRO_FAMILY_NRF52840)
    // NRF5: Include from third_party FreeRTOS
    #include "../../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#else
    // Default: Try to include from third_party
    #include "../../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#endif

#endif // PORTMACRO_H_COMPATIBILITY
