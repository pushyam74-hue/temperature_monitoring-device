#pragma once
#include "ITemperatureSensor.hpp"
#include "IAdc.hpp"

namespace tempmon {

// Rev-B hardware: sensor resolution is 0.1 degC per raw digit, i.e.
// the raw value already IS tenths of a degree Celsius.
class TemperatureSensorRevB final : public ITemperatureSensor {
public:
    explicit TemperatureSensorRevB(const IAdc &adc) : m_adc(adc) {}

    int32_t readTenthsCelsius() const override
    {
        return static_cast<int32_t>(m_adc.readRaw());
    }

    HwRevision revision() const override { return HwRevision::RevB; }

private:
    const IAdc &m_adc;
};

} // namespace tempmon
