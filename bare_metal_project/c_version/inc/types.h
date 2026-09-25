#ifndef TYPES_H
#define TYPES_H

#include <stdint.h>
#include <stdbool.h>

/* Hardware revision, as read from EEPROM */
typedef enum {
    HW_REV_A = 0,   /* 1 degC / digit sensor   */
    HW_REV_B = 1    /* 0.1 degC / digit sensor */
} hw_revision_t;

/* Logical GPIO-driven LED identifiers */
typedef enum {
    LED_GREEN = 0,
    LED_YELLOW,
    LED_RED,
    LED_COUNT
} led_id_t;

typedef enum {
    LED_OFF = 0,
    LED_ON  = 1
} led_state_t;

/* Evaluated temperature condition, drives the LED indicators */
typedef enum {
    TEMP_STATUS_OK = 0,        /* Green:  < 85 degC                     */
    TEMP_STATUS_WARNING,       /* Yellow: >= 85 degC                    */
    TEMP_STATUS_CRITICAL       /* Red:    >= 105 degC  OR  < 5 degC     */
} temp_status_t;

/* Configuration block stored in EEPROM */
typedef struct {
    hw_revision_t hw_revision;
    char          serial_number[9]; /* 8 chars + NUL terminator */
} eeprom_config_t;

#endif /* TYPES_H */
