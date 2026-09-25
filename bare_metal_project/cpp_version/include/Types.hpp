#pragma once
#include <cstdint>
#include <string>

namespace tempmon {

enum class HwRevision : uint8_t {
    RevA = 0,   // 1 degC / digit
    RevB = 1    // 0.1 degC / digit
};

enum class LedId : uint8_t {
    Green = 0,
    Yellow,
    Red
};

enum class LedState : uint8_t {
    Off = 0,
    On  = 1
};

enum class TempStatus : uint8_t {
    Ok = 0,        // Green:  < 85 degC
    Warning,       // Yellow: >= 85 degC
    Critical       // Red:    >= 105 degC OR < 5 degC
};

struct EepromConfig {
    HwRevision  hwRevision{HwRevision::RevA};
    std::string serialNumber{};
};

} // namespace tempmon
