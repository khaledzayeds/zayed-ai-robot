#!/usr/bin/env python3
"""Validate provisional pin assignments and board manifest without ESP-IDF."""
import json
import re
from pathlib import Path

root = Path(__file__).resolve().parents[1]
board = root / "board" / "zayed-ai-s3"
manifest = json.loads((board / "config.json").read_text())
assert manifest["target"] == "esp32s3"
assert manifest["type"] == "zayed-ai-s3"
assert all(b["name"] == "zayed-ai-s3" for b in manifest["builds"])
header = (board / "config.h").read_text()
pins = dict(re.findall(r"^#define\s+(\w+_PIN|AUDIO_I2S_\w+|BOOT_BUTTON_GPIO)\s+GPIO_NUM_(\d+)\s*$", header, re.M))
# Exclude BOOT from conflict check (it is the on-board hardware button).
used = {name: int(pin) for name, pin in pins.items() if name != "BOOT_BUTTON_GPIO"}
assert len(set(used.values())) == len(used), f"GPIO collision: {used}"
reserved = {0, 3, 19, 20, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 45, 46}
assert not (set(used.values()) & reserved), "Provisional pin map uses reserved/high-risk pins"
assert int(pins["BOOT_BUTTON_GPIO"]) == 0
print("Static provisional pin checks passed. NOT a physical wiring certification.")
