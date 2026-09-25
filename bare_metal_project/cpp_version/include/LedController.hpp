#pragma once
#include "IGpio.hpp"
#include "Types.hpp"

namespace tempmon {

// Translates an evaluated TempStatus into the (mutually exclusive)
// Green/Yellow/Red LED pattern, via the injected IGpio HAL.
class LedController {
public:
    explicit LedController(IGpio &gpio) : m_gpio(gpio) {}

    void init()
    {
        m_gpio.setLed(LedId::Green, LedState::On);
        m_gpio.setLed(LedId::Yellow, LedState::Off);
        m_gpio.setLed(LedId::Red, LedState::Off);
    }

    void update(TempStatus status)
    {
        m_gpio.setLed(LedId::Green,  status == TempStatus::Ok       ? LedState::On : LedState::Off);
        m_gpio.setLed(LedId::Yellow, status == TempStatus::Warning  ? LedState::On : LedState::Off);
        m_gpio.setLed(LedId::Red,    status == TempStatus::Critical ? LedState::On : LedState::Off);
    }

private:
    IGpio &m_gpio;
};

} // namespace tempmon
