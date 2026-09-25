#pragma once
#include <cstdint>
#include "Types.hpp"

namespace tempmon {

// Configurable thresholds, expressed in tenths of a degree Celsius,
// with defaults matching the project requirements.
struct TempThresholds {
    int32_t warningTenths     = 850;   //  85.0 degC
    int32_t criticalHiTenths  = 1050;  // 105.0 degC
    int32_t criticalLoTenths  = 50;    //   5.0 degC
};

class TempEvaluator {
public:
    TempEvaluator(TempThresholds thresholds = {}) : m_thresholds(thresholds) {}

    TempStatus evaluate(int32_t tenthsC) const
    {
        if (tenthsC >= m_thresholds.criticalHiTenths || tenthsC < m_thresholds.criticalLoTenths) {
            return TempStatus::Critical;
        }
        if (tenthsC >= m_thresholds.warningTenths) {
            return TempStatus::Warning;
        }
        return TempStatus::Ok;
    }

private:
    TempThresholds m_thresholds;
};

} // namespace tempmon
