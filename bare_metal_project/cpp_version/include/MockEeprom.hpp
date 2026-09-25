#pragma once
#include "IEeprom.hpp"

namespace tempmon {

// PC-demonstration stand-in for the I2C EEPROM device. Real hardware
// would issue I2C reads against fixed register addresses instead of
// returning an in-memory struct.
class MockEeprom final : public IEeprom {
public:
    MockEeprom() = default;
    MockEeprom(HwRevision rev, std::string serial)
        : m_config{ rev, std::move(serial) } {}

    EepromConfig readConfig() const override { return m_config; }

    // Test/mock-only helper to (re)program the device contents.
    void program(HwRevision rev, std::string serial)
    {
        m_config = EepromConfig{ rev, std::move(serial) };
    }

private:
    EepromConfig m_config{ HwRevision::RevA, "ABC1234" };
};

} // namespace tempmon
