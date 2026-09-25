#include "isr.h"
#include "adc.h"

/* Set by ADC_IRQHandler(), polled by the application task on real HW
 * to know a fresh sample is ready. Unused by the PC demo. */
static volatile int s_new_sample_ready = 0;

void TIMER_IRQHandler(void)
{
    /* Real HW: clear timer interrupt flag; if the ADC is not itself
     * hardware-triggered by this timer, kick off a conversion here:
     *   HAL_ADC_Start_IT(&hadc1);
     * Left as a stub for the PC build. */
}

void ADC_IRQHandler(void)
{
    /* Real HW: clear ADC interrupt flag, read the conversion result
     * register and hand it to the driver layer, e.g.:
     *   uint16_t raw = HAL_ADC_GetValue(&hadc1);
     *   adc_mock_set_next_value(raw); // (production: adc_latch_value)
     */
    s_new_sample_ready = 1;
}
