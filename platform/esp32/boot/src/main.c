#include "drivers/gpio.h"
#include "board/board.h"

void app_main(void) {
    gpio_set_output(LED_GPIO);
    while (1) {
        gpio_write(LED_GPIO, 1);
        for (volatile int i = 0; i < 100000; ++i);
        gpio_write(LED_GPIO, 0);
        for (volatile int i = 0; i < 100000; ++i);
    }
}

int main(void) {
    app_main();
    return 0;
}