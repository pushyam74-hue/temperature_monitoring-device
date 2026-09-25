#ifndef LED_CONTROL_H
#define LED_CONTROL_H

#include "types.h"

/* Drives the 3 status LEDs (mutually exclusive) from an evaluated
 * temp_status_t, via the gpio.h HAL. */
void led_control_init(void);
void led_control_update(temp_status_t status);

#endif /* LED_CONTROL_H */
