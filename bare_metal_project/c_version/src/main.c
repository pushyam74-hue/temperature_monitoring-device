/*
 * main.c - PC demonstration harness for the temperature monitoring
 * application (C, bare-metal style with mocked HAL).
 *
 * This exercises the same application logic that would run on the
 * target: read config from EEPROM, sample the ADC every
 * SAMPLE_PERIOD_US, convert according to the configured hardware
 * revision, evaluate OK/Warning/Critical and drive the LEDs.
 *
 * Sampling here is driven by a simple polling loop instead of the
 * TIMER_IRQHandler/ADC_IRQHandler pair (see isr.c), since no
 * interrupt controller is available/emulated on the PC.
 */

#include <stdio.h>
#include "config.h"
#include "types.h"
#include "adc.h"
#include "gpio.h"
#include "eeprom.h"
#include "temperature.h"
#include "led_control.h"

static const char *status_name(temp_status_t s)
{
    switch (s) {
        case TEMP_STATUS_OK:       return "OK";
        case TEMP_STATUS_WARNING:  return "WARNING";
        case TEMP_STATUS_CRITICAL: return "CRITICAL";
        default:                   return "?";
    }
}

/* One "sample tick": read ADC, convert per hw revision, evaluate,
 * drive LEDs. This is the routine that on real HW would be invoked
 * every SAMPLE_PERIOD_US (from the main loop, after ADC_IRQHandler
 * signals a fresh sample). */
static void process_sample(hw_revision_t hw_revision)
{
    uint16_t raw = adc_read_raw();
    int32_t  tenths_c = temperature_raw_to_tenths_c(raw, hw_revision);
    temp_status_t status = temperature_evaluate_status(tenths_c);

    int32_t whole, frac;
    temperature_split_tenths(tenths_c, &whole, &frac);

    printf("raw=%-5u -> %ld.%ldC -> %s\n", raw, (long)whole, (long)frac,
           status_name(status));

    led_control_update(status);
}

static void run_scenario(const char *title, hw_revision_t hw_revision,
                          const char *serial, const uint16_t *raw_samples,
                          int sample_count)
{
    printf("\n=== %s ===\n", title);

    eeprom_mock_program(hw_revision, serial);

    eeprom_config_t cfg;
    if (!eeprom_read_config(&cfg)) {
        printf("EEPROM read failed!\n");
        return;
    }
    printf("Config: hw_revision=%s, serial=%s\n",
           (cfg.hw_revision == HW_REV_B) ? "Rev-B" : "Rev-A",
           cfg.serial_number);

    for (int i = 0; i < sample_count; i++) {
        adc_mock_set_next_value(raw_samples[i]);
        process_sample(cfg.hw_revision);
    }
}

int main(void)
{
    printf("Bare-metal Temperature Monitor - PC demonstration build\n");
    printf("(sampling policy: every %u us on target hardware)\n", SAMPLE_PERIOD_US);

    adc_init();
    gpio_init();
    eeprom_init();
    led_control_init();

    /* Rev-A: 1 degC / digit. Sweep OK -> Warning -> Critical-high,
     * plus a Critical-low case. */
    const uint16_t rev_a_samples[] = { 20, 60, 84, 85, 99, 105, 120, 4, 0 };
    run_scenario("Rev-A sensor (1 degC/digit)", HW_REV_A, "ABC1234",
                 rev_a_samples, (int)(sizeof(rev_a_samples) / sizeof(rev_a_samples[0])));

    /* Rev-B: 0.1 degC / digit. Same physical temperatures, x10 raw. */
    const uint16_t rev_b_samples[] = { 200, 600, 840, 850, 990, 1050, 1200, 40, 0 };
    run_scenario("Rev-B sensor (0.1 degC/digit)", HW_REV_B, "XYZ9876",
                 rev_b_samples, (int)(sizeof(rev_b_samples) / sizeof(rev_b_samples[0])));

    printf("\nDone.\n");
    return 0;
}
