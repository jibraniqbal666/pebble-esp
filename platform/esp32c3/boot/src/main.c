#include "esp_log.h"
#include "esp_system.h"

// Simple logging macros for ESP32
#define LOG_INFO(format, ...) ESP_LOGI("PEBBLE", format, ##__VA_ARGS__)
#define LOG_DEBUG(format, ...) ESP_LOGD("PEBBLE", format, ##__VA_ARGS__)

// Forward declarations and stub implementations for ESP32
void display_init(void) {
    LOG_INFO("Display init - ESP32 stub");
}

void bootloader_show_logo(void) {
    LOG_INFO("Show Pebble logo - ESP32 stub");
}
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#ifdef COMBINED_BOOT_FW
// Forward declaration for pebble_os_start
void pebble_os_start(void);
#endif

void boot_main(void) {
    LOG_INFO("ESP32-C3 Pebble Bootloader Starting\n");
    
    display_init();
    
    LOG_INFO("Displaying Pebble logo\n");
    bootloader_show_logo();
    vTaskDelay(3000 / portTICK_PERIOD_MS);
    
    #ifdef COMBINED_BOOT_FW  
        LOG_INFO("Transitioning to Pebble OS (Phase 1)\n");
        
        pebble_os_start();
        
        LOG_INFO("Bootloader handed off to OS kernel\n");
        
    #else
        LOG_INFO("Loading main firmware...\n");
        while(1) {
            vTaskDelay(1000 / portTICK_PERIOD_MS);
        }
    #endif
}