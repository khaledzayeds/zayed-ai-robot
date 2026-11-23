# Zayed AI Robot

Open-source ESP32-S3 N16R8 voice-assistant prototype, based on [Xiaozhi ESP32](https://github.com/78/xiaozhi-esp32), with a **1.28-inch round GC9A01 SPI TFT (240×240)**, INMP441 I2S microphone, MAX98357A I2S amplifier, and 3 W / 8 Ω speaker.

> **Status:** Hardware ordered; not yet assembled or physically tested. The custom firmware **has compiled successfully in GitHub Actions**, but this does **not** prove the screen, audio, Wi-Fi provisioning, or device activation work on real hardware.

## Hardware

| Component | Specification | Status |
|---|---|---|
| Main board | ESP32-S3 N16R8, 16 MB flash / 8 MB PSRAM, dual USB-C | Ordered; verify actual board markings |
| Display | **GC9A01 1.28-inch round TFT, 240×240, SPI, MicroSD variant** | Selected to replace unavailable ST7789 1.47-inch |
| Microphone | INMP441 I2S | Planned; **3.3 V only** |
| Amplifier | MAX98357A I2S 3 W | Ordered |
| Speaker | 3 W / 8 Ω passive speaker | Ordered |
| USB and prototyping | USB-C data cable, breadboard, Dupont wires | Available |

The earlier **ST7789 1.47-inch 172×320** display is **no longer the target**.

## Firmware status

- **Development branch:** [`dev/firmware-foundation`](https://github.com/khaledzayeds/zayed-ai-robot/tree/dev/firmware-foundation)
- **Build workflow:** [Build Zayed AI S3 firmware](https://github.com/khaledzayeds/zayed-ai-robot/actions/workflows/build-firmware.yml)
- **Confirmed successful GC9A01 build:** [GitHub Actions run 45186921595](https://github.com/khaledzayeds/zayed-ai-robot/actions/runs/45186921595)
- **Download artifact:** `zayed-ai-s3-merged-firmware`, containing `merged-binary.bin` (from the successful run's Artifacts section)
- **Source:** pinned Xiaozhi upstream submodule with the `board/zayed-ai-s3` overlay
- **Server:** official Xiaozhi OTA/bootstrap endpoint; Wi-Fi provisioning and device activation are still required and untested
- **Hardware validation:** **not done**; no first flash yet

> The successful build above predates the latest documentation-only commit. The firmware source for that successful run already contains the GC9A01 display driver and 240×240 configuration.

## What is implemented

- Custom ESP32-S3 board integration and reproducible ESP-IDF CI builds
- GC9A01 SPI panel initialization (using the existing Espressif component)
- Provisional GPIO assignments for display, INMP441 and MAX98357A
- Xiaozhi audio/network application integration
- Basic LCD UI through upstream Xiaozhi

## Still to do

1. Confirm the actual module pin labels, 3.3 V requirements, display backlight voltage/polarity and ESP32-S3 board revision.
2. Measure the robot's existing laser opening and internal clearance: electrical compatibility **does not guarantee physical fit**.
3. **Backlight is intentionally not driven** in current firmware; the screen may remain dark until verified and configured.
4. Test flash/PSRAM, display, microphone, amplifier and Wi-Fi/activation on real hardware.
5. Design and implement custom animated **two-eye expressions** for the round screen. These animations are **not implemented yet**.
6. Investigate the original laser projector separately; **laser control is not implemented**. Never aim its beam at the screen or people.

## Safety

- **Do not wire the hardware from a rendered image.** Verify the exact labels and board pinout first.
- Never power the INMP441 from 5 V.
- Never connect either MAX98357A speaker output to ground.
- Keep the original laser disconnected during initial bring-up; identify its rating and control electronics before any integration.
- Do not commit Wi-Fi passwords or account credentials.

## Documentation

- [Hardware and GPIO cautions](docs/hardware.md)
- [Build and checkout](docs/build.md)
- [First flash](docs/first-flash.md)
- [Windows flash](docs/windows-flash.md)
- [Official Xiaozhi first boot](docs/official-xiaozhi-first-boot.md)
- [Firmware candidate and limitations](docs/firmware-v0.1-prehardware.md)
- [Roadmap](docs/roadmap.md)

Upstream Xiaozhi licensing and notices are retained.
