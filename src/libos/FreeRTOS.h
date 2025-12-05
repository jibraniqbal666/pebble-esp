/*
 * libos FreeRTOS.h compatibility header
 * 
 * This header provides FreeRTOS.h for libos across different architectures
 */

#ifndef LIBOS_FREERTOS_H_COMPATIBILITY
#define LIBOS_FREERTOS_H_COMPATIBILITY

#if defined(MICRO_FAMILY_ESP32_C3)
    // ESP32: Use ESP-IDF's FreeRTOS with proper include order
    #include "freertos/FreeRTOSConfig.h"
    #include "freertos/portmacro.h"
    #include "freertos/FreeRTOS.h"
    
#elif defined(MICRO_FAMILY_STM32F2) || defined(MICRO_FAMILY_STM32F4) || defined(MICRO_FAMILY_STM32F7) || defined(MICRO_FAMILY_NRF52840)
    // ARM platforms: Include from third_party FreeRTOS
    #include "../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/FreeRTOS.h"
    #include "task.h"
    
#else
    // Default: Try to include from third_party
    #include "../third_party/freertos/FreeRTOS-Kernel/FreeRTOS/Source/include/FreeRTOS.h"
    #include "task.h"
    
#endif

#endif // LIBOS_FREERTOS_H_COMPATIBILITY
