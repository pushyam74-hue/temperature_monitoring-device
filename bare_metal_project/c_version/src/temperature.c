#include "temperature.h"
#include "config.h"
#include <stdlib.h>

int32_t temperature_raw_to_tenths_c(uint16_t raw_value, hw_revision_t hw_revision)
{
    int32_t tenths;

    if (hw_revision == HW_REV_B) {
        /* 0.1 degC per digit -> raw value already IS tenths of a degree */
        tenths = (int32_t)raw_value;
    } else {
        /* HW_REV_A: 1 degC per digit */
        tenths = (int32_t)raw_value * 10;
    }
    return tenths;
}

temp_status_t temperature_evaluate_status(int32_t tenths_c)
{
    const int32_t warning_tenths      = TEMP_WARNING_C * 10;
    const int32_t critical_hi_tenths  = TEMP_CRITICAL_HIGH_C * 10;
    const int32_t critical_lo_tenths  = TEMP_CRITICAL_LOW_C * 10;

    if ((tenths_c >= critical_hi_tenths) || (tenths_c < critical_lo_tenths)) {
        return TEMP_STATUS_CRITICAL;
    }
    if (tenths_c >= warning_tenths) {
        return TEMP_STATUS_WARNING;
    }
    return TEMP_STATUS_OK;
}

void temperature_split_tenths(int32_t tenths_c, int32_t *whole_out, int32_t *frac_out)
{
    if (whole_out == NULL || frac_out == NULL) {
        return;
    }
    *whole_out = tenths_c / 10;
    *frac_out  = abs(tenths_c % 10);
}
