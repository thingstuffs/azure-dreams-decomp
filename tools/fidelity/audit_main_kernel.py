#!/usr/bin/env python3
"""Extract and disassemble the three MAIN kernel-installer row extents."""

from __future__ import annotations

import argparse
import hashlib
import subprocess
from pathlib import Path


ROWS = (
    ("func_800217C8", 0x2717C8, 104, 0x800217C8),
    ("func_800218A0", 0x2718A0, 136, 0x800218A0),
    ("func_80021958", 0x271958, 108, 0x80021958),
)


def main() -> None:
    repo = Path(__file__).resolve().parents[2]
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--image",
        type=Path,
        default=repo / "build_ovl/work/s3_splat/extract/MAIN_MAIN.BIN",
    )
    parser.add_argument("--out-dir", type=Path, default=repo / "work/fidelity/main_kernel_audit")
    parser.add_argument("--objdump", default="mipsel-linux-gnu-objdump")
    args = parser.parse_args()

    image = args.image.resolve()
    args.out_dir.mkdir(parents=True, exist_ok=True)
    hashes: list[tuple[str, str]] = []
    with image.open("rb") as source:
        image_size = image.stat().st_size
        for name, offset, size, vram in ROWS:
            end = offset + size
            if end > image_size:
                raise SystemExit(
                    f"{name}: requested extent 0x{offset:X}..0x{end:X} "
                    f"exceeds image size 0x{image_size:X}"
                )
            source.seek(offset)
            data = source.read(size)
            if len(data) != size:
                raise SystemExit(f"{name}: short read ({len(data)} of {size} bytes)")

            binary_path = args.out_dir / f"{name}.bin"
            binary_path.write_bytes(data)
            digest = hashlib.sha256(data).hexdigest()
            hashes.append((name, digest))
            (args.out_dir / f"{name}.sha256").write_text(
                f"{digest}  {name}.bin\n", encoding="ascii"
            )

            disassembly_path = args.out_dir / f"{name}.disasm.txt"
            with disassembly_path.open("w", encoding="utf-8") as out:
                subprocess.run(
                    [
                        args.objdump,
                        "-D",
                        "-b",
                        "binary",
                        "-m",
                        "mips:3000",
                        "-EL",
                        f"--adjust-vma=0x{vram:08X}",
                        str(binary_path),
                    ],
                    check=True,
                    stdout=out,
                    text=True,
                )

    (args.out_dir / "SHA256SUMS").write_text(
        "".join(f"{digest}  {name}.bin\n" for name, digest in hashes),
        encoding="ascii",
    )
    for name, digest in hashes:
        print(f"{name} {digest}")


if __name__ == "__main__":
    main()
