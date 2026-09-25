#pragma once

namespace tempmon {

// Sampling period the timer/ADC ISR pair is configured for on real
// hardware. Kept here so the ISR layer and the application layer
// agree on the same constant.
constexpr unsigned kSamplePeriodUs = 100U;

// Free functions matching real-hardware IRQ vector names (C linkage
// naming convention kept for clarity). Defined in Isr.cpp per the
// requirements; not wired to a real/emulated interrupt controller in
// the PC demonstration build - TemperatureMonitor drives sampling via
// a polling loop instead.
void TimerIRQHandler();
void AdcIRQHandler();

} // namespace tempmon
