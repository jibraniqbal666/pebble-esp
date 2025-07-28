#include "display.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "platform/esp32v2/boot/src/drivers/display/spi_lc_touch_example.main.h"  // If you need this
#include "../display.h"

void display_init(void) { display_init(); }

void display_show_splash_screen(void) { bootloader_show_logo(); }

void display_update(NextRowCallback nrcb, UpdateCompleteCallback uccb) {
    PBL_ASSERTN(nrcb != NULL);
    PBL_ASSERTN(uccb != NULL);

    DisplayRow row;
    u_int16_t* buffer;
    u_int8_t width;  // Example width
    while (nrcb(&row)) {
        // Process the row data
        printf("Row address: %d, Data: %p\n", row.address, row.data);
        buffer = malloc(row.address * sizeof(uint16_t));
        if (buffer == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            return;
        }
        width = row.address;  // Assuming address is the width for this example
        memcpy(buffer, row.data, row.address * sizeof(uint16_t));
        // Here you would typically send the row data to the display
    }    
    esp_lcd_panel_draw_bitmap(width, 1, buffer);
}