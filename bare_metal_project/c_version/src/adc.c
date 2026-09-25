#include "adc.h"
#include <stddef.h>

/* Mocked "latched conversion result" register, as would be written by
 * the ADC-complete ISR on real hardware. */
static volatile uint16_t s_last_raw_value = 0U;

void adc_init(void)
{
    /* Real HW: configure ADC channel, resolution, trigger source and
     * the sampling timer (period = SAMPLE_PERIOD_US), enable the
     * conversion-complete interrupt. Nothing to do for the mock. */
    s_last_raw_value = 0U;
}

uint16_t adc_read_raw(void)
{
    return s_last_raw_value;
}

void adc_mock_set_next_value(uint16_t raw_value)
{
    s_last_raw_value = raw_value;
}
