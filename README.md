# HC-SR04 Distance Sensor Test

A minimal C/Pico SDK program for testing an HC-SR04 ultrasonic distance sensor on a Raspberry Pi Pico 2. It triggers a measurement on GP13 (physical pin 17, see [the pinout in the datasheet](https://pip-assets.raspberrypi.com/categories/1005-raspberry-pi-pico-2/documents/RP-008299-DS-3-pico-2-datasheet.pdf#page=5)), measures the pulse on GP10 (physical pin 14), and prints the calculated distance in cm over USB serial.

Readings repeat every 50 ms and a timeout displays `TOO FAR/CLOSE`. Output updates on a single terminal line.

## Wiring

| HC-SR04 | Pico 2 |
|---|---|
| VCC | VBUS (5 V, physical pin 40) |
| GND | Any GND pin |
| TRIG | GP13 (physical pin 17) |
| ECHO | GP10 (physical pin 14), **through a voltage divider** |

> [!WARNING]
> The HC-SR04's ECHO output is **5 V**; Pico 2 GPIO is **3.3 V** and must not receive ECHO directly. Place 1 kΩ between ECHO and GP10 and 2 kΩ between GP10 and GND to reduce the signal to approximately 3.33 V at a 5 V input.

Build `Sensors.c` in a Pico SDK project with USB standard I/O enabled, then flash that .uf2 to the Pico 2. Porting to another board is possible, but requires adapting GPIO assignments, SDK calls/build setup, and voltage-level handling as needed.

**[Video demonstration](https://www.youtube.com/watch?v=CsdIkqaJuzs)**
