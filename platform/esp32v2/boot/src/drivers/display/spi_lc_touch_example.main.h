#include <stdint.h>


void display_init(void);
void bootloader_show_logo(void);
void render_on_display(int width, int height, uint16_t* buffer);