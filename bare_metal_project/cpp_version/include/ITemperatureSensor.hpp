#pragma once
#include <cstdint>
#include "Types.hpp"

namespace tempmon {

// Strategy interface: each hardware revision knows how to convert its
// own raw ADC digit into a normalized "tenths of a degree Celsius"
// value. Keeping this as int32_t (rather than float) avoids an FPU
// dependency, which matters for a bare-metal target.
class ITemperatureSensor {
public:
    virtual ~ITemperatureSensor() = default;
    virtual int32_t readTenthsCelsius() const = 0;
    virtual HwRevision revision() const = 0;
};

} // namespace tempmon
