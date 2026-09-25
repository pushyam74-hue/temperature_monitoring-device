#ifndef GPIO_H
#define GPIO_H

#include "types.h"

/*
 * GPIO driver interface (HAL layer). Drives the 3 status LEDs.
 * On real hardware this would map led_id_t to a physical
 * port/pin and write the ODR/BSRR register. The PC build mocks
 * the pin state in memory and prints transitions to stdout.
 */

void gpio_init(void);

void gpio_set_led(led_id_t led, led_state_t state);

led_state_t gpio_get_led(led_id_t led);

#endif /* GPIO_H */
