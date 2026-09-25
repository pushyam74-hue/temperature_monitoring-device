#pragma once
#include <array>
#include <iostream>
#include <iomanip>
#include "IGpio.hpp"

namespace tempmon {

class MockGpio final : public IGpio {
public:
    void setLed(LedId led, LedState state) override
    {
        auto &current = m_state[static_cast<size_t>(led)];
        if (current != state) {
            current = state;
            std::cout << "  [GPIO] LED " << std::left << std::setw(6) << name(led)
                      << " -> " << (state == LedState::On ? "ON" : "off") << "\n";
        }
    }

    LedState getLed(LedId led) const override
    {
        return m_state[static_cast<size_t>(led)];
    }

private:
    static const char *name(LedId led)
    {
        switch (led) {
            case LedId::Green:  return "GREEN";
            case LedId::Yellow: return "YELLOW";
            case LedId::Red:    return "RED";
        }
        return "?";
    }

    std::array<LedState, 3> m_state{ LedState::Off, LedState::Off, LedState::Off };
};

} // namespace tempmon
