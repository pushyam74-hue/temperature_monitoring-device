#pragma once
#include "Types.hpp"

namespace tempmon {

// EEPROM HAL abstraction (I2C-backed on real hardware).
class IEeprom {
public:
    virtual ~IEeprom() = default;
    virtual EepromConfig readConfig() const = 0;
};

} // namespace tempmon
