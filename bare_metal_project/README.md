# Bare-Metal Temperature Monitor

Architecture and implementation of a bare-metal embedded temperature
monitoring and visualization device, with Green/Yellow/Red LED
indicators for OK / Warning / Critical temperature ranges.

Implemented twice, per the assignment:

|Version|Language|Location|
|-|-|-|
|v1|C|[`c\_version/`](c_version)|
|v2|C++ (OOP)|[`cpp\_version/`](cpp_version)|

Both are PC demonstration builds: hardware interfaces (ADC, GPIO,
EEPROM/I2C) are mocked in software so the application logic can be
built and run on a regular machine, with no target hardware or
emulator required.

## Requirements coverage

* **ADC sampling** — `adc` driver models the sensor's raw digit
register; on target hardware a timer fires every **100 µs** and
triggers `TIMER\_IRQHandler` / `ADC\_IRQHandler`, which latch the
conversion result with minimal jitter (see [`docs/`](docs)).
* **3 LEDs, GPIO-driven** — Green `<85°C`, Yellow `>=85°C`,
Red `>=105°C` or `<5°C`, mutually exclusive.
* **Two hardware revisions**

  * Rev-A: 1 °C / digit (raw `10` → `10 °C`)
  * Rev-B: 0.1 °C / digit (raw `100` → `10 °C`)
  * Only one sensor type is active at a time — selected at runtime
from the EEPROM-configured hardware revision (C: `if/else` on
`hw\_revision\_t`; C++: a **Strategy pattern**, `ITemperatureSensor`
with `TemperatureSensorRevA` / `TemperatureSensorRevB`, chosen by
a factory).
* **EEPROM config** — hardware revision (0/1) and a serial number
placeholder (e.g. `"ABC1234"`), mocked as an in-memory
image/struct standing in for the real I2C device.
* **ISRs** — `TIMER\_IRQHandler` / `ADC\_IRQHandler` (C) and
`TimerIRQHandler` / `AdcIRQHandler` (C++) are defined and
implemented as stubs describing what real hardware would do; they
are intentionally **not** wired to an interrupt controller in the
PC demo, which instead drives sampling with a plain polling loop,
per the assignment ("no need to make ISR calls functional from PC
demonstration program").
* Internal temperature representation avoids floating point
(`int32\_t`, "tenths of a degree") — a small nod to realistic
bare-metal practice (no guaranteed FPU), though it isn't a hard
requirement.

## Architecture diagrams

See [`docs/hardware\_topology.svg`](docs/hardware_topology.svg) (the
device's physical block diagram: µC ↔ ADC/sensor, GPIOs ↔ LEDs, I2C ↔
EEPROM) and [`docs/software\_architecture.svg`](docs/software_architecture.svg)
(the layered software design — Application / Driver-HAL / Interrupt
layers — shared by both the C and C++ implementations).

## Building \& running

Each version is self-contained with its own `Makefile` (requires
`gcc`/`g++`, no other dependencies).

```bash
# C version
cd c\_version
make run

# C++ version
cd cpp\_version
make run
```

Each demo programs the mocked EEPROM for **Rev-A**, then **Rev-B**,
and for each revision sweeps a set of raw ADC values across the
OK → Warning → Critical-high and Critical-low ranges, printing the
converted temperature, evaluated status, and every LED transition.

## Repository layout

```
.
├── README.md
├── docs/
│   ├── hardware\_topology.svg
│   └── software\_architecture.svg
├── c\_version/
│   ├── inc/            # config.h, types.h, adc.h, gpio.h, eeprom.h,
│   │                    # temperature.h, led\_control.h, isr.h
│   ├── src/             # matching .c files + main.c (demo harness)
│   └── Makefile
└── cpp\_version/
    ├── include/         # Types, IAdc/IGpio/IEeprom interfaces,
    │                    # Mock\* implementations, ITemperatureSensor +
    │                    # RevA/RevB strategies, SensorFactory,
    │                    # LedController, TempEvaluator,
    │                    # TemperatureMonitor, Isr
    ├── src/              # Isr.cpp, main.cpp (demo harness)
    └── Makefile
```

## 

