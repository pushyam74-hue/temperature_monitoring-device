#pragma once
#include <memory>
#include <stdexcept>
#include "ITemperatureSensor.hpp"
#include "TemperatureSensorRevA.hpp"
#include "TemperatureSensorRevB.hpp"
#include "IAdc.hpp"

namespace tempmon {

// Only one sensor type is operational at any given time (per the
// requirements) - this factory picks the concrete strategy based on
// the hardware revision read from EEPROM, so the rest of the
// application only ever depends on the ITemperatureSensor interface.
inline std::unique_ptr<ITemperatureSensor> createSensor(HwRevision revision, const IAdc &adc)
{
    switch (revision) {
        case HwRevision::RevA:
            return std::make_unique<TemperatureSensorRevA>(adc);
        case HwRevision::RevB:
            return std::make_unique<TemperatureSensorRevB>(adc);
    }
    throw std::runtime_error("Unknown hardware revision");
}

} // namespace tempmon
