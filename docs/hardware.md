# Hardware inventory and integration constraints

| Part | Interface | Notes |
|---|---|---|
| ESP32-S3 N16R8 | MCU | Verify board revision, pinout, PSRAM and flash settings |
| ST7789 1.47-inch 172x320 | SPI | Check actual connector labels, reset, backlight polarity, rotation |
| INMP441 | I2S RX | 3.3V only; inspect L/R select and clock pins |
| MAX98357A | I2S TX | Confirm power rail and gain configuration |
| 3W 8-ohm speaker | Amplifier output | Neither speaker terminal should be tied to ground |

## GPIO allocation
**Not assigned yet.** Exact module pinouts and ESP32-S3 board pinout must be verified from physical hardware or reliable datasheets before producing a wiring diagram or firmware pin map. Avoid strapping pins and pins reserved by flash/PSRAM/USB as appropriate to the actual board.

## Bring-up order
1. ESP-IDF hello-world and serial logs.
2. SPI display solid colors and orientation test.
3. I2S microphone level/recording test.
4. I2S amplifier sine/voice playback at low volume.
5. Combined audio + display + Wi-Fi stability test.
6. Integrate upstream Xiaozhi voice stack and add expressive UI.

## Power
USB-C 5V supply for first tests. Confirm current requirements and module voltage tolerances. Use common ground, decoupling and short signal leads. Do not feed 5V into INMP441.
