#pragma once
#include "ITemperatureSensor.hpp"
#include "IAdc.hpp"

namespace tempmon {

// Rev-A hardware: sensor resolution is 1 degC per raw digit.
class TemperatureSensorRevA final : public ITemperatureSensor {
public:
    explicit TemperatureSensorRevA(const IAdc &adc) : m_adc(adc) {}

    int32_t readTenthsCelsius() const override
    {
        return static_cast<int32_t>(m_adc.readRaw()) * 10;
    }

    HwRevision revision() const override { return HwRevision::RevA; }

private:
    const IAdc &m_adc;
};

} // namespace tempmon
