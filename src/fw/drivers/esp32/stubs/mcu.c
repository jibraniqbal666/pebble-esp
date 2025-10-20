#include "drivers/mcu.h"

#define ESP32_COMPATIBLE
#include <mcu.h>

// ESP32 includes for basic functionality
#include <stdint.h>

// Stub implementations for ESP32 MCU functions
static uint32_t esp32_device_id = 0x32C3; // Mock device ID for ESP32-C3

const uint32_t* mcu_get_serial(void) {
  return &esp32_device_id;
}

uint32_t mcu_cycles_to_milliseconds(uint64_t cpu_ticks) {
  // Assume 160MHz CPU clock for ESP32 (will be configurable later)
  return ((cpu_ticks * 1000) / 160000000);
}

void pwr_enable_wakeup(bool enable) {
  // ESP32 power management stub
  (void)enable;
}

void pwr_flash_power_down_stop_mode(bool power_down) {
  // ESP32 flash power management stub
  (void)power_down;
}

void pwr_access_backup_domain(bool enable_access) {
  // ESP32 backup domain stub (RTC memory equivalent)
  (void)enable_access;
}
