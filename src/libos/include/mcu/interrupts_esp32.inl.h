/*
 * Copyright 2024 Google LLC
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <stdint.h>
#include <stdbool.h>

// Forward declare FreeRTOS function 
extern int xPortInIsrContext(void);

static inline bool mcu_state_is_isr(void) {
  return (bool)xPortInIsrContext();
}

static inline uint32_t mcu_state_get_isr_priority(void) {
  // On ESP32, if we're in an interrupt context, return a default priority
  // ESP32 interrupt priorities are managed by ESP-IDF
  if (mcu_state_is_isr()) {
    return 5; // Default mid-range priority 
  }
  return ~0U; // Not in ISR
}
