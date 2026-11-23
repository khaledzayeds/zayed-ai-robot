# Xiaozhi upstream integration assessment

Upstream: https://github.com/78/xiaozhi-esp32

## Verified from upstream main (2026-11-21)
- License: MIT, copyright 2025 Shenzhen Xinzhi Future Technology Co., Ltd. and contributors. Preserve original notices when importing source.
- Upstream README states ESP-IDF **v6.0.1 or later**, recommends **release/v6.1**, and says ESP-IDF 5.x is no longer supported.
- Board implementations live under `main/boards/`; custom board integration must follow the current board registration and Kconfig/CMake conventions, not an older tutorial.
- Supports Wi-Fi and voice transports (WebSocket and MQTT/UDP), with Opus audio streaming.

## Implementation strategy
1. Obtain a pinned upstream commit and record it here before importing code.
2. Import upstream source as a tracked base (or maintain a reproducible fork); keep LICENSE and attribution.
3. Study a compatible ESP32-S3 I2S board and SPI ST7789 board implementation, then create `zayed-ai-s3` following upstream conventions.
4. Confirm ESP32-S3 N16R8 flash/PSRAM configuration and the physical GPIO layout.
5. Add isolated screen and I2S tests before enabling online voice interaction.
6. Add GitHub Actions build after source is present and build configuration is validated.

**Current state:** This repository does not yet contain upstream source or a working firmware build. No build success or device test is claimed.
