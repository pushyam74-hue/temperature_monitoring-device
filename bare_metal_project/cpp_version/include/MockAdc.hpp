#pragma once
#include "IAdc.hpp"

namespace tempmon {

// PC-demonstration stand-in for the ADC peripheral: holds the "last
// converted" value that AdcIRQHandler would normally latch, and lets
// the demo harness inject values deterministically.
class MockAdc final : public IAdc {
public:
    uint16_t readRaw() const override { return m_lastValue; }

    void setNextValue(uint16_t value) { m_lastValue = value; }

private:
    uint16_t m_lastValue{0};
};

} // namespace tempmon
