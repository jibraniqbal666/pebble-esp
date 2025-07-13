void app_main(void) __attribute__((used));

void call_start_cpu0(void) __attribute__((noreturn, used, section(".entry.text")));
void call_start_cpu0(void) {
    app_main();
    while (1) {}
}