# Hardware inventory and integration constraints

| Part | Interface | Notes |
|---|---|---|
| ESP32-S3 N16R8 | MCU | Verify board revision, pinout, PSRAM and flash settings |
| GC9A01 round TFT 1.28-inch 240x240 (MicroSD variant) | SPI | Replaces unavailable ST7789 1.47-inch 172x320; check actual connector labels, reset, backlight polarity, orientation and mounting clearance |
| INMP441 | I2S RX | 3.3V only; inspect L/R select and clock pins |
| MAX98357A | I2S TX | Confirm power rail and gain configuration |
| 3W 8-ohm speaker | Amplifier output | Neither speaker terminal should be tied to ground |

## Display notes
- Firmware targets the GC9A01 panel controller via Espressif's `esp_lcd_gc9a01` component already included in pinned Xiaozhi upstream.
- Active circular display diameter is approximately 32.4 mm; PCB/microSD assembly is larger. Measure the robot's laser aperture and internal clearance before installation.
- The original laser projector must not shine into the display. Relocation/control of the laser is a separate, unimplemented project requiring identification and safety review.
- Backlight GPIO is intentionally **not driven** pending confirmation of the exact module's BL voltage and active polarity. A successful firmware boot may therefore still show a dark screen.
- SPI GPIO assignments are provisional, not an approved wiring diagram. MicroSD is not connected or supported in v0.1.

## GPIO allocation
The values in `board/zayed-ai-s3/config.h` are **provisional**. Verify exact module pinouts and ESP32-S3 board revision before connecting. Avoid flash/PSRAM, USB, and strapping conflicts.

## Bring-up order
1. ESP-IDF hello-world and serial logs.
2. GC9A01 SPI display solid colors, backlight and orientation test.
3. I2S microphone level/recording test.
4. I2S amplifier voice playback at low volume.
5. Combined audio + display + Wi-Fi stability test.
6. Integrate upstream Xiaozhi voice stack and add round-screen expressive eyes.

## Power
USB-C 5V supply for first tests. Confirm current requirements and module voltage tolerances. Use common ground, decoupling and short signal leads. Do not feed 5V into INMP441.
