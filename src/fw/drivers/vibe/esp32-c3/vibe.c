// src/fw/drivers/vibe/esp32-c3/vibe.c
#include "vibe.h"
#include "system/logging.h"

void vibe_init(void) {
    ESP_LOGI("VIBE_STUB", "vibe_init() - stub");
}

void vibe_pulse(uint32_t duration_ms) {
    ESP_LOGI("VIBE_STUB", "vibe_pulse(%lu ms) - stub", duration_ms);
}