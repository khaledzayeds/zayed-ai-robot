# First flash checklist

Do not connect peripherals before verifying physical pin labels and the provisional GPIO map.

## Before arrival
- Confirm the ESP-IDF 6.1 firmware build succeeds in GitHub Actions.
- Download the `zayed-ai-s3-merged-firmware` artifact (merged-binary.bin).
- Confirm ESP32-S3 N16R8 board marking and flash/PSRAM sizes.
- Verify ST7789 panel offsets, SPI pins, and backlight voltage/polarity.

## On arrival
1. First connect the ESP32-S3 by USB with all external modules disconnected.
2. Identify the COM port and check serial connectivity.
3. Inspect the firmware artifact and build metadata; flash only a successful build.
4. Example Windows command (replace COMx):
```bash
python -m esptool --chip esp32s3 -p COMx write-flash 0x0 merged-binary.bin
```
5. Record boot logs. Firmware that initializes the display immediately may fail with the display disconnected; a successful USB connection is not proof of a successful boot.
6. Disconnect USB before wiring; test verified display, microphone and speaker connections in stages.

## Safety
- INMP441 requires 3.3V; never connect it to 5V.
- Speaker attaches across MAX98357A speaker output terminals; neither terminal goes to GND.
- Never follow provisional GPIO numbers as final wiring instructions.
- Keep credentials out of the GitHub repository.

A successful CI build is not a hardware validation or proof of AI voice functionality.
