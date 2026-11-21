# Zayed AI Robot

ESP32-S3 N16R8 voice assistant with a 1.47-inch ST7789 SPI screen, INMP441 I2S microphone, MAX98357A I2S amplifier, and 3W 8-ohm speaker.

## Status
Planning / hardware ordered. **No firmware has been built, flashed, or validated yet.**

## Direction
Start from the upstream [xiaozhi-esp32](https://github.com/78/xiaozhi-esp32) project after checking its current license, build instructions, and board integration APIs. Keep upstream notices and license. This repository initially contains planning and hardware configuration scaffolding, not a working Xiaozhi fork.

## Hardware
- ESP32-S3 N16R8 (16 MB flash, 8 MB PSRAM; verify actual board marking)
- 1.47-inch ST7789 SPI display (172x320; verify pin labels and rotation)
- INMP441 digital I2S microphone (3.3 V only)
- MAX98357A digital I2S mono amplifier (power per module specs)
- 3 W / 8 ohm passive speaker
- USB-C data cable and breadboard available

## Safety and bring-up
1. Photograph both sides of each received module and verify pin labels.
2. Confirm exact GPIO assignment and power rails before wiring; **do not use a generated illustration as a wiring schematic**.
3. Test display, microphone, and speaker separately before combined operation.
4. Use a USB power source appropriate for peak amplifier current; share grounds; never ground either speaker output terminal.
5. Keep API credentials out of source control.

See `docs/hardware.md` and `docs/roadmap.md` for the proposed integration work.
