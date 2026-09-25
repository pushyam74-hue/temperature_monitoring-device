#include "gpio.h"
#include <stdio.h>

static led_state_t s_led_state[LED_COUNT] = { LED_OFF, LED_OFF, LED_OFF };

static const char *led_name(led_id_t led)
{
    switch (led) {
        case LED_GREEN:  return "GREEN";
        case LED_YELLOW: return "YELLOW";
        case LED_RED:    return "RED";
        default:         return "UNKNOWN";
    }
}

void gpio_init(void)
{
    for (int i = 0; i < LED_COUNT; i++) {
        s_led_state[i] = LED_OFF;
    }
}

void gpio_set_led(led_id_t led, led_state_t state)
{
    if (led >= LED_COUNT) {
        return;
    }
    if (s_led_state[led] != state) {
        s_led_state[led] = state;
        /* Real HW: HAL_GPIO_WritePin(...). Mock: log the transition. */
        printf("  [GPIO] LED %-6s -> %s\n", led_name(led),
               (state == LED_ON) ? "ON" : "off");
    }
}

led_state_t gpio_get_led(led_id_t led)
{
    if (led >= LED_COUNT) {
        return LED_OFF;
    }
    return s_led_state[led];
}
