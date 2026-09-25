#pragma once
#include <cstdint>

namespace tempmon {

// ADC HAL abstraction. On real hardware, a concrete implementation
// would configure the ADC peripheral + sampling timer (period =
// kSamplePeriodUs, see Isr.hpp) and latch conversion results from
// AdcIRQHandler(). readRaw() then returns the last latched sample
// with no wait/jitter, satisfying the "very low jitter" requirement.
class IAdc {
public:
    virtual ~IAdc() = default;
    virtual uint16_t readRaw() const = 0;
};

} // namespace tempmon
