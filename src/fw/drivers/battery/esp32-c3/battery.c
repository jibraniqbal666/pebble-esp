// src/fw/drivers/battery/esp32-c3/battery.c
#include "../battery.h"
#include "system/logging.h"

void battery_init(void) {
    ESP_LOGI("BATTERY_STUB", "battery_init() - stub");
}

uint16_t battery_get_voltage_mv(void) {
    return 3700; // Fake 3.7V
}

uint8_t battery_get_charge_percent(void) {
    return 85; // Fake 85% charge
}