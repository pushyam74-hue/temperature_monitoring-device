#pragma once
#include <memory>
#include "ITemperatureSensor.hpp"
#include "LedController.hpp"
#include "TempEvaluator.hpp"
#include "Types.hpp"

namespace tempmon {

// Application-layer orchestrator: owns a sensor strategy (selected
// per hardware revision), evaluates each sample against thresholds,
// and drives the LED controller. This is the class that, on real
// hardware, the periodic sampling task would call once per tick.
class TemperatureMonitor {
public:
    TemperatureMonitor(std::unique_ptr<ITemperatureSensor> sensor,
                        LedController &ledController,
                        TempEvaluator evaluator = {})
        : m_sensor(std::move(sensor))
        , m_ledController(ledController)
        , m_evaluator(evaluator)
    {
    }

    // Executes one sampling tick: read sensor, evaluate, update LEDs.
    // Returns the evaluated status and normalized reading for logging.
    struct SampleResult {
        int32_t    tenthsCelsius;
        TempStatus status;
    };

    SampleResult processSample()
    {
        const int32_t tenths = m_sensor->readTenthsCelsius();
        const TempStatus status = m_evaluator.evaluate(tenths);
        m_ledController.update(status);
        return SampleResult{ tenths, status };
    }

    HwRevision activeRevision() const { return m_sensor->revision(); }

private:
    std::unique_ptr<ITemperatureSensor> m_sensor;
    LedController                      &m_ledController;
    TempEvaluator                       m_evaluator;
};

} // namespace tempmon
