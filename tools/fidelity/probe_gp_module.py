#!/usr/bin/env python3
"""Private full-SLUS link proof for one owned small datum and three merged TUs."""

import argparse
import hashlib
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
SOURCE = ROOT / "docs/evidence/gp_data_module_pilot"
ap = argparse.ArgumentParser(description=__doc__)
ap.add_argument("--out", type=Path, default=ROOT / "work/fidelity/gp_data_module")
ap.add_argument("--maspsx", type=Path, default=ROOT / "work/fidelity/gp_probe279/candidate/maspsx.py")
args = ap.parse_args()
HERE = args.out.resolve()
HERE.mkdir(parents=True, exist_ok=True)
(HERE / "tmp").mkdir(exist_ok=True)
ASSEMBLER = args.maspsx.resolve()
if not ASSEMBLER.is_file():
    ap.error("run probe_small_data.py --out work/fidelity/gp_probe279 first, or supply --maspsx")
VIEW = HERE / "full_link_view"
STEMS = ("konami_runtime_w_8003C634", "konami_runtime_w_8003C758",
         "konami_runtime_w_8003C920")
SYMS = ("func_8003C634", "func_8003C758", "func_8003C920")
sys.path.insert(0, str(ROOT / "tools/fidelity"))
from slus_iso import SlusView  # noqa: E402


def run(cmd, *, env=None):
    result = subprocess.run(cmd, cwd=VIEW, env=env, text=True, capture_output=True)
    if result.returncode:
        raise RuntimeError(f"{' '.join(map(str, cmd))}\n{(result.stdout + result.stderr)[-1500:]}")
    return result.stdout


def make_real(path, content):
    """Never follow a copied view symlink back to a production source/config."""
    if path.is_symlink() or path.exists():
        path.unlink()
    if isinstance(content, bytes):
        path.write_bytes(content)
    else:
        path.write_text(content)


def named_symbols(elf):
    out = {}
    raw = subprocess.check_output(("mipsel-linux-gnu-nm", "-S", "--defined-only", str(elf)), text=True)
    for line in raw.splitlines():
        fields = line.split()
        if len(fields) == 4 and fields[-1] in SYMS:
            out[fields[-1]] = {"address": "0x" + fields[0].upper(), "size": int(fields[1], 16)}
    return out


def display_path(path):
    path = Path(path)
    return str(path.relative_to(ROOT)) if path.is_relative_to(ROOT) else "<external>/" + path.name


if VIEW.exists():
    shutil.rmtree(VIEW)  # this script owns this exact private view directory
view = SlusView(VIEW)
calibration = view.calibrate()
assert calibration["result"] == "MATCH", calibration
pristine = named_symbols(VIEW / "build/slus_006.14.elf")

# Replace only symlinks inside the private view. All production files stay read-only.
make_real(VIEW / "src/gp_data_module.h", (SOURCE / "gp_data_module.h").read_text())
make_real(VIEW / "src" / (STEMS[0] + ".c"), (SOURCE / "gp_data_module.c").read_text())
for stem in STEMS[1:]:
    make_real(VIEW / "src" / (stem + ".c"), "/* merged into konami_runtime_w_8003C634.c */\n")

# 54240.bin begins at retail file offset 0x54240; remove only [0x2c,0x30).
asset = (VIEW / "assets/54240.bin").read_bytes()
assert asset[0x2C:0x30] == bytes.fromhex("04 00 00 00")
prefix, suffix = asset[:0x2C], asset[0x30:]
assert prefix + asset[0x2C:0x30] + suffix == asset
for tag, data in (("prefix", prefix), ("suffix", suffix)):
    bname = f"54240_{tag}"
    (VIEW / "assets" / (bname + ".bin")).write_bytes(data)
    run(("mipsel-linux-gnu-ld", "--relocatable", "--format=binary", "-o",
         f"build/assets/{bname}.o", f"assets/{bname}.bin"))

old_slot = "build/assets/54240.o(.data);"
new_slot = ("build/assets/54240_prefix.o(.data);\n"
            "        build/src/konami_runtime_w_8003C634.o(.sdata);\n"
            "        build/assets/54240_suffix.o(.data);")
ordered = (ROOT / "build_slus/build/slus_006.14_ordered.ld").read_text()
assert ordered.count(old_slot) == 1
make_real(VIEW / "build/slus_006.14_ordered.ld", ordered.replace(old_slot, new_slot))

undefined = VIEW / "config/generated/slus_006.14.undefined_syms.txt"
sym_text = undefined.read_text()
assignment = "D_80080A6C = 0x80080A6C;\n"
assert sym_text.count(assignment) == 1
make_real(undefined, sym_text.replace(assignment, ""))

env = dict(os.environ, AZURE_MASPSX_COMPANION=str(ASSEMBLER),
           TMPDIR=str(HERE / "tmp"))
run(("ninja", "-j", "2", *(f"build/src/{stem}.o" for stem in STEMS)), env=env)

# The stock ninja link command and all its inputs, with only the old raw data
# object replaced by the two private pieces. Link flags are exactly stock.
ninja = (VIEW / "build.ninja").read_text()
edges = [s for s in ninja.splitlines() if s.startswith("build build/slus_006.14.elf: link ")]
assert len(edges) == 1
inputs = edges[0].split(": link ", 1)[1].split(" | ", 1)[0].split()
assert inputs.count("build/assets/54240.o") == 1
at = inputs.index("build/assets/54240.o")
inputs[at:at + 1] = ["build/assets/54240_prefix.o", "build/assets/54240_suffix.o"]
run(("mipsel-linux-gnu-ld", "-EL", "-T", "build/slus_006.14_ordered.ld", "-T",
     "config/generated/slus_006.14.undefined_funcs.txt", "-T",
     "config/generated/slus_006.14.undefined_syms.txt", "--no-check-sections",
     "-o", "build/slus_006.14.elf", *inputs))
run(("mipsel-linux-gnu-objcopy", "-O", "binary", "build/slus_006.14.elf", "build/slus_006.14"))

image = (VIEW / "build/slus_006.14").read_bytes()
retail = (ROOT / "baserom/slus_006.14").read_bytes()
linked = named_symbols(VIEW / "build/slus_006.14.elf")
readelf = run(("mipsel-linux-gnu-readelf", "-Ws", "build/slus_006.14.elf"))
symbol_lines = [line for line in readelf.splitlines() if line.split()[-1:] == ["D_80080A6C"]]
assert len(symbol_lines) == 1, symbol_lines
parts = symbol_lines[0].split()
symbol = {"address": "0x" + parts[1].upper(), "type": parts[3], "binding": parts[4],
          "section_index": parts[6], "raw": symbol_lines[0].strip()}
offset = 0x800 + (0x80080A6C - 0x8002D000)
receipt = {"calibration": calibration, "recipe": "2.7.2-cdk; empty ccflags/asflags",
           "assembler": display_path(ASSEMBLER),
           "asset_carve": {"source": "assets/54240.bin", "prefix_bytes": len(prefix),
                           "removed_bytes": asset[0x2C:0x30].hex(), "suffix_bytes": len(suffix)},
           "image": {"match_retail": image == retail, "size": len(image),
                     "sha1": hashlib.sha1(image).hexdigest(), "retail_sha1": hashlib.sha1(retail).hexdigest(),
                     "first_differing_offsets": [i for i, (a, b) in enumerate(zip(image, retail)) if a != b][:16]},
           "data_symbol": symbol, "data_bytes_at_vma": image[offset:offset + 4].hex(),
           "functions": {name: {"pristine": pristine.get(name), "linked": linked.get(name)} for name in SYMS},
           "link_flags": ["-EL", "--no-check-sections"],
           "private_view": display_path(VIEW)}
(HERE / "full_link_receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
print(json.dumps(receipt, indent=2))
assert image == retail
assert symbol["address"] == "0x80080A6C" and symbol["section_index"] != "ABS"
assert image[offset:offset + 4] == bytes.fromhex("04 00 00 00")
assert all(x["pristine"] == x["linked"] for x in receipt["functions"].values())
