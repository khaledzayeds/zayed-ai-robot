# Reproducible source checkout and build preparation

## Current automated check
`.github/workflows/verify-upstream.yml` verifies that the pinned upstream Xiaozhi submodule checks out, includes its CMake project and board directory, and has its original license. **This is NOT a firmware compilation test.**

## Local source checkout
```bash
git clone --recurse-submodules https://github.com/khaledzayeds/zayed-ai-robot.git
cd zayed-ai-robot
git checkout dev/firmware-foundation
git submodule update --init --recursive
```

## Firmware prerequisites (not yet integrated)
- ESP-IDF v6.0.1+; upstream recommends release/v6.1.
- Read upstream `docs/custom-board.md` and use its current Kconfig/CMake registration.
- Confirm hardware GPIO mapping and supported screen/audio driver before configuring `zayed-ai-s3`.
- Once the custom board is implemented, build from `upstream/xiaozhi-esp32` with a supported board selection and `idf.py build`; the custom board is **not available yet**.

Upstream pin: `831ffd14188553cc887408b75396ae38618538e0` (do not update without reviewing compatibility).
