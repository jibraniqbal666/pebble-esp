/*
 * libos portmacro.h compatibility header
 * 
 * This header provides FreeRTOS portmacro.h for libos across different architectures
 */

#ifndef LIBOS_PORTMACRO_H_COMPATIBILITY
#define LIBOS_PORTMACRO_H_COMPATIBILITY

#if defined(MICRO_FAMILY_ESP32_C3)
    // Define xPORT_TASK_INFO FIRST before any ESP-IDF FreeRTOS headers
    #ifndef xPORT_TASK_INFO
    typedef struct PORT_TASK_INFO
    {
        const char *pcName;
        void *taskHandle;
        unsigned long registers[32]; // RISC-V has 32 general purpose registers
    } xPORT_TASK_INFO;
    #endif
    
    // ESP32: Use ESP-IDF's FreeRTOS with proper config first
    #include "freertos/FreeRTOSConfig.h"
    #include "freertos/portmacro.h"
    
#elif defined(MICRO_FAMILY_STM32F2) || defined(MICRO_FAMILY_STM32F4) || defined(MICRO_FAMILY_STM32F7) || defined(MICRO_FAMILY_NRF52840)
    // ARM platforms: Include from third_party FreeRTOS
    #include "../../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#else
    // Default: Try to include from third_party
    #include "../../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/portable.h"
    
#endif

#endif // LIBOS_PORTMACRO_H_COMPATIBILITY
