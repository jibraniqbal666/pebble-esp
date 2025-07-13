#include "drivers/gpio.h"
#include "board/board.h"

void app_main(void) {
    volatile int x = 0;
    while (1) {
        x++;
    }
}