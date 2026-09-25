#ifndef CONFIG_H
#define CONFIG_H

/* ---------------------------------------------------------------------
 * System configuration constants
 * ------------------------------------------------------------------- */

/* Sampling period for the temperature ADC channel, in microseconds.
 * On real hardware this drives a hardware timer that fires TIMER_ISR
 * (see isr.h) every SAMPLE_PERIOD_US with minimal jitter. */
#define SAMPLE_PERIOD_US        (100U)

/* Temperature thresholds, expressed in degrees Celsius (integer,
 * matches Rev-A resolution). Rev-B values are scaled x10 internally
 * by the temperature module before comparison - see temperature.c */
#define TEMP_WARNING_C           (85)
#define TEMP_CRITICAL_HIGH_C     (105)
#define TEMP_CRITICAL_LOW_C      (5)

/* EEPROM logical addresses (mocked as a flat byte array) */
#define EEPROM_ADDR_HW_REVISION  (0x00U)
#define EEPROM_ADDR_SERIAL_NO    (0x01U)
#define EEPROM_SERIAL_NO_LEN     (8U)   /* e.g. "ABC1234" + null */

#endif /* CONFIG_H */
