# Windows flashing preparation (not yet hardware validated)

Use only a firmware artifact from a **successful** GitHub Actions run.

## Download
1. Open Actions > Build Zayed AI S3 firmware.
2. Select a successful run and download the `zayed-ai-s3-merged-firmware` artifact.
3. Extract `merged-binary.bin` from the ZIP.
4. Confirm the board is ESP32-S3 N16R8 and the selected USB port is correct.

## Flash
Install Python and the Espressif esptool package on your PC:

```powershell
py -m pip install --upgrade esptool
py -m esptool --chip esp32s3 -p COMx chip-id
py -m esptool --chip esp32s3 -p COMx write-flash 0x0 merged-binary.bin
```

Replace COMx with your actual serial port. **Do not run the write-flash command before a successful firmware build and review of flash settings.** A merged image is intended for offset 0x0; if the build produces separate images instead, follow its generated flashing metadata.

## What remains
- A passing ESP-IDF compile and generated firmware artifact.
- GPIO map confirmed against actual modules.
- Display backlight, panel offsets and I2S electrical tests.
- First boot logs and actual voice conversation test.

The current build has not yet been confirmed as successful.
