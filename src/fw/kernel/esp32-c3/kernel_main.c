// src/fw/kernel/esp32-c3/kernel_main.c
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "system/logging.h"

#define TAG "PEBBLE_KERNEL"

// Phase 1: Just prove kernel boots
void kernel_main(void) {
    ESP_LOGI(TAG, "=== Pebble ESP32-C3 Kernel Started ===");
    ESP_LOGI(TAG, "Phase 1: Foundation Layer Active");
    
    while(1) {
        ESP_LOGI(TAG, "Kernel heartbeat");
        vTaskDelay(5000 / portTICK_PERIOD_MS);
    }
}

// Entry point from your existing boot_main()
void pebble_os_start(void) {
    ESP_LOGI(TAG, "Starting Pebble OS...");
    
    // Create kernel task
    xTaskCreate(kernel_main, "pebble_kernel", 8192, NULL, 5, NULL);
    
    ESP_LOGI(TAG, "Pebble kernel task created");
}