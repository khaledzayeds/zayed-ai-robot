#!/usr/bin/env python3
"""Apply Zayed board overlay to pinned Xiaozhi checkout (idempotently)."""
from pathlib import Path
import shutil

ROOT = Path(__file__).resolve().parents[1]
UPSTREAM = ROOT / "upstream" / "xiaozhi-esp32"
SOURCE = ROOT / "board" / "zayed-ai-s3"
TARGET = UPSTREAM / "main" / "boards" / "zayed-ai-s3"
KCONFIG = UPSTREAM / "main" / "Kconfig.projbuild"
CMAKE = UPSTREAM / "main" / "CMakeLists.txt"

KCONFIG_ANCHOR = '    config BOARD_TYPE_BREAD_COMPACT_WIFI\n'
CMAKE_ANCHOR = 'if(CONFIG_BOARD_TYPE_BREAD_COMPACT_WIFI)\n'
KCONFIG_INSERT = (
    '    config BOARD_TYPE_ZAYED_AI_S3\n'
    '        bool "Zayed AI S3 (prototype)"\n'
    '        depends on IDF_TARGET_ESP32S3\n'
)
CMAKE_INSERT = (
    'if(CONFIG_BOARD_TYPE_ZAYED_AI_S3)\n'
    '    set(BOARD_DIR "zayed-ai-s3")\n'
    '    set(BUILTIN_TEXT_FONT font_noto_sans_basic_14_1)\n'
    '    set(BUILTIN_ICON_FONT font_material_symbols_14_1)\n'
    'elseif(CONFIG_BOARD_TYPE_BREAD_COMPACT_WIFI)\n'
)

def patch(path: Path, anchor: str, replacement: str, marker: str) -> None:
    original = path.read_text(encoding="utf-8")
    if marker in original:
        print(f"Already integrated: {path.name}")
        return
    if original.count(anchor) != 1:
        raise RuntimeError(f"Unexpected upstream layout in {path}: anchor count != 1")
    path.write_text(original.replace(anchor, replacement, 1), encoding="utf-8")

def main() -> None:
    if not (UPSTREAM / "LICENSE").exists():
        raise SystemExit("Missing submodule: git submodule update --init --recursive")
    TARGET.mkdir(parents=True, exist_ok=True)
    for src in SOURCE.iterdir():
        if src.is_file():
            shutil.copy2(src, TARGET / src.name)
    patch(KCONFIG, KCONFIG_ANCHOR, KCONFIG_INSERT + KCONFIG_ANCHOR, "BOARD_TYPE_ZAYED_AI_S3")
    patch(CMAKE, CMAKE_ANCHOR, CMAKE_INSERT, "CONFIG_BOARD_TYPE_ZAYED_AI_S3")
    print("Zayed board overlay applied. Build/hardware validation still required.")

if __name__ == "__main__":
    main()
