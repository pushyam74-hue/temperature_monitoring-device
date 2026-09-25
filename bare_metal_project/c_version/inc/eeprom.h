#ifndef EEPROM_H
#define EEPROM_H

#include "types.h"
#include <stdbool.h>

/*
 * EEPROM driver interface (HAL layer). On real hardware this talks
 * to the EEPROM over I2C. The PC build mocks the device as a small
 * in-memory image that main.c can pre-load for demo purposes.
 */

void eeprom_init(void);

/* Reads the full configuration block (hw revision + serial number).
 * Returns true on success. */
bool eeprom_read_config(eeprom_config_t *out_config);

/* Test/mock-only helper: program the mocked EEPROM contents. */
void eeprom_mock_program(hw_revision_t hw_revision, const char *serial_number);

#endif /* EEPROM_H */
