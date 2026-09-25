#pragma once
#include "Types.hpp"

namespace tempmon {

// GPIO HAL abstraction for the 3 status LEDs.
class IGpio {
public:
    virtual ~IGpio() = default;
    virtual void setLed(LedId led, LedState state) = 0;
    virtual LedState getLed(LedId led) const = 0;
};

} // namespace tempmon
