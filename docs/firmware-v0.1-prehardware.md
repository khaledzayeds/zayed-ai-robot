# Zayed AI S3 firmware v0.1 — pre-hardware candidate

## Verified CI build
- GitHub Actions successful run: https://github.com/khaledzayeds/zayed-ai-robot/actions/runs/44885703734
- Git commit: `a14d37d8390a65ea504b562b2d53c08ee3c15307`
- Artifact name: `zayed-ai-s3-merged-firmware`
- Firmware file inside artifact: `merged-binary.bin`
- Metadata artifact: `zayed-ai-s3-build-metadata`
- Toolchain: ESP-IDF release/v6.1 Docker image
- Target: ESP32-S3
- Source: pinned Xiaozhi upstream with Zayed board overlay

## Important distinction
This is a **successfully compiled pre-hardware firmware**, not a validated ready-to-use robot firmware. The build ran in GitHub Actions, not on the purchased board.

## Known hardware blockers
1. Confirm exact ST7789 172x320 panel offset, inversion, backlight voltage and active polarity.
2. Confirm board/module GPIO markings and power rails before connecting peripherals.
3. Check I2S microphone channel select and speaker amplifier wiring.
4. Confirm flash size and PSRAM detected on the actual N16R8 board.
5. First boot and Xiaozhi server activation/configuration have not been tested.

## How to download
Open the successful workflow run above, scroll to **Artifacts**, download `zayed-ai-s3-merged-firmware`, and extract `merged-binary.bin`. GitHub artifact downloads may require sign-in and expire according to GitHub retention settings.

For Windows flashing steps, see [windows-flash.md](windows-flash.md). Do not flash while hardware identity and firmware flashing metadata remain unverified.
