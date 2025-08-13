#include "drivers/gpio.h"
#include "board/board.h"
#include "drivers/display/spi_lc_touch_example.main.h"
#include "system/logging.h"
#include <stdio.h>
#include <inttypes.h>
#include "sdkconfig.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_chip_info.h"
#include "esp_flash.h"
#include "esp_system.h"

#ifdef COMBINED_BOOT_FW
#include "fw/kernel/esp32-c3/kernel_main.h"
#endif

void boot_main(void) {
    LOG_INFO("ESP32-C3 Pebble Bootloader Starting\n");
    
    esp_lcd_panel_handle_t panel_handle = display_init();
    
    LOG_INFO("Displaying Pebble logo\n");
    bootloader_show_logo(panel_handle);
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