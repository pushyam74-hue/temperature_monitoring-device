#ifndef ADC_H
#define ADC_H

#include <stdint.h>

/*
 * ADC driver interface (HAL layer).
 *
 * On real hardware, adc_init() would configure the ADC peripheral and
 * a hardware timer to trigger a conversion every SAMPLE_PERIOD_US and
 * fire ADC_IRQHandler() (see isr.h) on conversion-complete, with the
 * result latched for adc_read_raw() to pick up with no additional
 * jitter/wait.
 *
 * For the PC demonstration build, this is backed by a simple mock
 * that returns caller-injected values so the rest of the stack can be
 * exercised deterministically (see adc.c).
 */

void adc_init(void);

/* Returns the last converted raw ADC sample (sensor-resolution units,
 * meaning depends on the currently configured hardware revision). */
uint16_t adc_read_raw(void);

/* Test/mock-only helper: inject the next raw ADC value that
 * adc_read_raw() will return. Not present on real hardware. */
void adc_mock_set_next_value(uint16_t raw_value);

#endif /* ADC_H */
