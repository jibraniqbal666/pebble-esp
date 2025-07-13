#pragma once

#include <stdint.h>

typedef struct {
  uint32_t length;
  uint32_t checksum;
} firmware_desc_t;

// Add more fields and functions as needed