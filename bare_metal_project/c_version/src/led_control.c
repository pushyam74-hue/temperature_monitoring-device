#include "led_control.h"
#include "gpio.h"

void led_control_init(void)
{
    gpio_init();
    gpio_set_led(LED_GREEN, LED_ON);
    gpio_set_led(LED_YELLOW, LED_OFF);
    gpio_set_led(LED_RED, LED_OFF);
}

void led_control_update(temp_status_t status)
{
    /* LEDs are mutually exclusive: exactly one is lit at a time. */
    gpio_set_led(LED_GREEN,  (status == TEMP_STATUS_OK)       ? LED_ON : LED_OFF);
    gpio_set_led(LED_YELLOW, (status == TEMP_STATUS_WARNING)  ? LED_ON : LED_OFF);
    gpio_set_led(LED_RED,    (status == TEMP_STATUS_CRITICAL) ? LED_ON : LED_OFF);
}
