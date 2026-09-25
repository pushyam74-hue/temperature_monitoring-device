#include "Isr.hpp"

namespace tempmon {

void TimerIRQHandler()
{
    // Real HW: clear timer interrupt flag; trigger an ADC conversion
    // if not already hardware-triggered by this timer.
}

void AdcIRQHandler()
{
    // Real HW: clear ADC interrupt flag, latch HAL_ADC_GetValue(...)
    // into the concrete IAdc implementation, signal the application
    // task that a fresh sample is ready.
}

} // namespace tempmon
