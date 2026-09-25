#ifndef TEMPERATURE_H
#define TEMPERATURE_H

#include "types.h"
#include <stdint.h>

/*
 * Temperature module: converts a raw ADC sample into a normalized
 * value and evaluates it against the OK/Warning/Critical thresholds.
 *
 * To keep this bare-metal friendly (no FPU dependency), temperature
 * is represented internally in "tenths of a degree Celsius"
 * (int32_t), e.g. 105.0 degC == 1050.
 *
 *   Rev-A: 1 digit   = 1 degC   -> tenths = raw * 10
 *   Rev-B: 1 digit   = 0.1 degC -> tenths = raw * 1
 */

int32_t temperature_raw_to_tenths_c(uint16_t raw_value, hw_revision_t hw_revision);

temp_status_t temperature_evaluate_status(int32_t tenths_c);

/* Utility for logging: tenths -> whole degrees + fractional digit */
void temperature_split_tenths(int32_t tenths_c, int32_t *whole_out, int32_t *frac_out);

#endif /* TEMPERATURE_H */
