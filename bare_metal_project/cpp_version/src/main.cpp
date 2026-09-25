// main.cpp - PC demonstration harness for the temperature monitoring
// application (C++ / OOP version).
//
// Mirrors the C version's behavior and test scenarios, but expressed
// with interfaces (IAdc/IGpio/IEeprom), a Strategy pattern for the
// two sensor hardware revisions (ITemperatureSensor), and a small
// orchestrator (TemperatureMonitor) that composes them.

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

#include "Types.hpp"
#include "MockAdc.hpp"
#include "MockGpio.hpp"
#include "MockEeprom.hpp"
#include "SensorFactory.hpp"
#include "LedController.hpp"
#include "TemperatureMonitor.hpp"
#include "Isr.hpp"

using namespace tempmon;

namespace {

const char *statusName(TempStatus s)
{
    switch (s) {
        case TempStatus::Ok:       return "OK";
        case TempStatus::Warning:  return "WARNING";
        case TempStatus::Critical: return "CRITICAL";
    }
    return "?";
}

const char *revisionName(HwRevision r)
{
    return r == HwRevision::RevB ? "Rev-B" : "Rev-A";
}

void runScenario(const std::string &title, HwRevision revision,
                  const std::string &serial, const std::vector<uint16_t> &rawSamples)
{
    std::cout << "\n=== " << title << " ===\n";

    MockAdc     adc;
    MockGpio    gpio;
    MockEeprom  eeprom(revision, serial);
    LedController ledController(gpio);
    ledController.init();

    const EepromConfig cfg = eeprom.readConfig();
    std::cout << "Config: hw_revision=" << revisionName(cfg.hwRevision)
              << ", serial=" << cfg.serialNumber << "\n";

    auto sensor = createSensor(cfg.hwRevision, adc);
    TemperatureMonitor monitor(std::move(sensor), ledController);

    for (uint16_t raw : rawSamples) {
        adc.setNextValue(raw);
        auto result = monitor.processSample();

        int32_t whole = result.tenthsCelsius / 10;
        int32_t frac  = std::abs(result.tenthsCelsius % 10);

        std::cout << "raw=" << std::setw(5) << std::left << raw
                   << " -> " << whole << "." << frac << "C -> "
                   << statusName(result.status) << "\n";
    }
}

} // namespace

int main()
{
    std::cout << "Bare-metal Temperature Monitor - PC demonstration build (C++/OOP)\n";
    std::cout << "(sampling policy: every " << kSamplePeriodUs << " us on target hardware)\n";

    // Rev-A: 1 degC / digit
    runScenario("Rev-A sensor (1 degC/digit)", HwRevision::RevA, "ABC1234",
                { 20, 60, 84, 85, 99, 105, 120, 4, 0 });

    // Rev-B: 0.1 degC / digit (same physical temps, x10 raw)
    runScenario("Rev-B sensor (0.1 degC/digit)", HwRevision::RevB, "XYZ9876",
                { 200, 600, 840, 850, 990, 1050, 1200, 40, 0 });

    std::cout << "\nDone.\n";
    return 0;
}
