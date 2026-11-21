# Zayed AI S3 — official Xiaozhi first boot

## Firmware default (verified against pinned upstream)
The build explicitly sets `CONFIG_OTA_URL="https://api.tenclass.net/xiaozhi/ota/"`. This is the upstream Xiaozhi official default bootstrap endpoint. It is **not** an API key or a private server.

On startup, Xiaozhi requests OTA/activation information from this endpoint. The server can provide MQTT or WebSocket connection parameters and an activation code. Do not hardcode credentials, tokens, Wi-Fi passwords, or device IDs.

## User actions after hardware arrives
1. Check board model, GPIO wiring and power; first boot with USB and serial logs.
2. Flash a **successful new CI build** with the official endpoint setting.
3. Enter Wi-Fi provisioning mode and connect to 2.4 GHz Wi-Fi; the device needs internet access.
4. Create/sign in to a personal account at https://xiaozhi.me.
5. Follow the device's activation instructions (code/voice/display or serial log). Activation flow may change.
6. Select/configure the available AI agent/model and test a spoken question.

No self-hosted server or paid LLM API key is required for the official personal-user path described by upstream, subject to the official service's current limits and policies.

## Not yet tested
- Live access to the official service from the purchased ESP32-S3.
- Actual microphone, amplifier, screen/backlight, audio playback and activation.
- Wi-Fi provisioning UI, activation voice output, and Arabic conversational quality.
- The screen backlight remains disabled pending verification of polarity.

## Sources
- Pinned upstream README: https://github.com/78/xiaozhi-esp32/blob/831ffd14188553cc887408b75396ae38618538e0/README.md
- Pinned upstream OTA implementation: https://github.com/78/xiaozhi-esp32/blob/831ffd14188553cc887408b75396ae38618538e0/main/ota.cc
- Official service: https://xiaozhi.me
