#ifndef ISR_H
#define ISR_H

/*
 * Interrupt Service Routines.
 *
 * On real hardware:
 *  - TIMER_IRQHandler fires every SAMPLE_PERIOD_US (100 us) from a
 *    hardware timer configured in adc_init(), and kicks off an ADC
 *    conversion (or, if the ADC is itself hardware-triggered by the
 *    timer, simply exists to guarantee the deterministic period).
 *  - ADC_IRQHandler fires on ADC conversion-complete, latches the
 *    raw sample for adc_read_raw(), and optionally sets a flag/
 *    semaphore for the main loop to re-evaluate temperature status.
 *
 * Per the requirements, these are defined and implemented here so
 * the architecture is complete, but they are NOT wired to a real or
 * emulated interrupt controller in the PC demonstration build -
 * main.c drives sampling directly via a polling loop instead.
 */

void TIMER_IRQHandler(void);
void ADC_IRQHandler(void);

#endif /* ISR_H */
