#include "eeprom.h"
#include "config.h"
#include <string.h>

/* Mocked flat EEPROM memory image. Layout:
 *   [0]      hw revision (0 = Rev-A, 1 = Rev-B)
 *   [1..8]   serial number, NUL-terminated ASCII, up to 8 chars
 */
static uint8_t s_eeprom_image[64];
static bool    s_initialized = false;

void eeprom_init(void)
{
    /* Real HW: init I2C peripheral used to talk to the EEPROM. */
    memset(s_eeprom_image, 0xFF, sizeof(s_eeprom_image));
    s_eeprom_image[EEPROM_ADDR_HW_REVISION] = (uint8_t)HW_REV_A;
    memset(&s_eeprom_image[EEPROM_ADDR_SERIAL_NO], 0, EEPROM_SERIAL_NO_LEN);
    s_initialized = true;
}

bool eeprom_read_config(eeprom_config_t *out_config)
{
    if (!s_initialized || out_config == NULL) {
        return false;
    }

    /* Real HW: I2C_Read(EEPROM_I2C_ADDR, reg, buf, len) per field. */
    uint8_t raw_rev = s_eeprom_image[EEPROM_ADDR_HW_REVISION];
    out_config->hw_revision = (raw_rev == (uint8_t)HW_REV_B) ? HW_REV_B : HW_REV_A;

    memcpy(out_config->serial_number,
           &s_eeprom_image[EEPROM_ADDR_SERIAL_NO],
           EEPROM_SERIAL_NO_LEN);
    out_config->serial_number[8] = '\0';

    return true;
}

void eeprom_mock_program(hw_revision_t hw_revision, const char *serial_number)
{
    if (!s_initialized) {
        eeprom_init();
    }
    s_eeprom_image[EEPROM_ADDR_HW_REVISION] = (uint8_t)hw_revision;

    memset(&s_eeprom_image[EEPROM_ADDR_SERIAL_NO], 0, EEPROM_SERIAL_NO_LEN);
    if (serial_number != NULL) {
        strncpy((char *)&s_eeprom_image[EEPROM_ADDR_SERIAL_NO],
                serial_number, EEPROM_SERIAL_NO_LEN - 1);
    }
}
