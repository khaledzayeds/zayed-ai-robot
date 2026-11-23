# Zayed AI Robot firmware roadmap

## Milestone 0 — baseline (current)
- [x] Repository initialized
- [x] Development branch created
- [x] Hardware inventory and integration checklist documented
- [ ] Verify actual GPIO pinout and display module wiring
- [ ] Inspect current upstream Xiaozhi license, supported boards, and ESP-IDF toolchain

## Milestone 1 — board support
- [ ] Import or fork upstream source preserving license and attribution
- [ ] Create custom board definition for ESP32-S3 N16R8
- [ ] Add ST7789 SPI display driver/configuration
- [ ] Add INMP441 I2S input and MAX98357A I2S output
- [ ] Confirm clean build in CI with pinned toolchain

## Milestone 2 — interactive robot
- [ ] Wi-Fi provisioning and secure configuration
- [ ] Voice assistant end-to-end test
- [ ] Animated eyes: idle/listening/thinking/speaking/error
- [ ] OTA firmware update and rollback plan

## Acceptance criteria
A reproducible CI build is not equivalent to hardware validation. v0.1 requires successful on-device tests of Wi-Fi, screen, microphone, speaker and voice interaction.
