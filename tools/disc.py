#!/usr/bin/env python3
"""The disc: extract it, rebuild it, prove the rebuild byte-identical.

    python3 tools/disc.py extract            # bin/<image> -> work/disc/extract/ (+ azure.xml), containers, baserom
    python3 tools/disc.py rebuild [--sources DIR ...]   # work/disc/azure.xml -> work/disc/rebuilt.bin (+ .cue)
    python3 tools/disc.py check              # SHA-1 of the rebuilt image against the original (and the lock)

The image is supplied by the user (never committed): `bin/Azure Dreams.bin` + `.cue`, or
$AZURE_CLEAN_DISC.  tools/toolchain.lock.json records the SHA-1 the tree was built from and the
SHA-1 of every container the gates read.  `extract` lays the disc out with dumpsxiso (the mkpsxiso
project XML is what `rebuild` feeds back), links the four overlay containers under the flat names
the window gates use (work/disc/containers/MAIN_MAIN.BIN ...) and drops the SLUS executable in
baserom/.  `rebuild --sources DIR` overlays files from DIR (same layout as the extract: SLUS_006.14,
MAIN/MAIN.BIN, ...) on the extract before building, which is how a disc is rebuilt from gate
outputs instead of the retail extract.
"""
from __future__ import annotations
import argparse, hashlib, json, os, shutil, subprocess, sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
LOCK = ROOT / "tools/toolchain.lock.json"
WORK = ROOT / "work/disc"
EXTRACT = WORK / "extract"
XML = WORK / "azure.xml"
CONTAINERS = WORK / "containers"
BIN = ROOT / "toolchain/bin"
# flat name the window gates read -> path inside the extract
FLAT = {"MAIN_MAIN.BIN": "MAIN/MAIN.BIN", "TOWN_TOWN.BIN": "TOWN/TOWN.BIN",
        "DUNGEON_DUNGEON.BIN": "DUNGEON/DUNGEON.BIN", "OVMOVIE.BIN": "OVMOVIE.BIN"}


def sha1(p: Path) -> str:
    h = hashlib.sha1()
    with open(p, "rb") as f:
        for chunk in iter(lambda: f.read(1 << 20), b""):
            h.update(chunk)
    return h.hexdigest()


def lock() -> dict:
    return json.loads(LOCK.read_text()) if LOCK.exists() else {}


def disc_path(arg: str | None) -> Path:
    if arg:
        return Path(arg)
    env = os.environ.get("AZURE_CLEAN_DISC")
    if env:
        return Path(env)
    name = lock().get("disc", {}).get("name", "Azure Dreams.bin")
    return ROOT / "bin" / name


def link_or_copy(src: Path, dst: Path):
    dst.parent.mkdir(parents=True, exist_ok=True)
    if dst.exists() or dst.is_symlink():
        dst.unlink()
    try:
        os.link(src, dst)
    except OSError:
        shutil.copyfile(src, dst)


def cmd_extract(a):
    disc = disc_path(a.disc)
    if not disc.exists():
        sys.exit(f"disc image not found: {disc} (copy the image into bin/ or set AZURE_CLEAN_DISC)")
    want = lock().get("disc", {}).get("sha1")
    got = sha1(disc)
    print(f"disc {disc.name}: sha1 {got}" + ("" if not want else (" OK" if got == want else f" MISMATCH (lock {want})")))
    if want and got != want and not a.force:
        sys.exit("refusing to extract an image that is not the one the tree was built from (--force to override)")
    if EXTRACT.exists():
        shutil.rmtree(EXTRACT)
    WORK.mkdir(parents=True, exist_ok=True)
    # dumpsxiso writes the project XML with source paths relative to its cwd: run it in work/disc
    subprocess.run([str(BIN / "dumpsxiso"), "-x", "extract", "-s", "azure.xml", str(disc.resolve())],
                   cwd=WORK, check=True, stdout=subprocess.DEVNULL)
    missing = [rel for rel in FLAT.values() if not (EXTRACT / rel).exists()]
    if missing or not (EXTRACT / "SLUS_006.14").exists():
        sys.exit(f"extract incomplete: missing {missing}")
    for flat, rel in FLAT.items():
        link_or_copy(EXTRACT / rel, CONTAINERS / flat)
    (ROOT / "baserom").mkdir(exist_ok=True)
    shutil.copyfile(EXTRACT / "SLUS_006.14", ROOT / "baserom/slus_006.14")
    cmd_check_containers()


def cmd_check_containers() -> bool:
    ok = True
    want = lock().get("containers", {})
    for flat in list(FLAT) + ["SLUS_006.14"]:
        p = CONTAINERS / flat if flat in FLAT else EXTRACT / flat
        if not p.exists():
            print(f"  {flat:22} missing"); ok = False; continue
        got = sha1(p); w = want.get(flat)
        state = "" if not w else (" OK" if got == w else f" MISMATCH (lock {w})")
        ok &= (not w) or got == w
        print(f"  {flat:22} {p.stat().st_size:>10} {got}{state}")
    return ok


def cmd_rebuild(a):
    if not XML.exists():
        sys.exit("no work/disc/azure.xml: run `tools/disc.py extract` first")
    src_root = EXTRACT
    if a.sources:
        # stage: the extract tree with the given directories overlaid (hardlinks; nothing copied twice)
        src_root = WORK / "stage"
        if src_root.exists():
            shutil.rmtree(src_root)
        for base in [EXTRACT] + [Path(s) for s in a.sources]:
            for p in base.rglob("*"):
                if p.is_file():
                    link_or_copy(p, src_root / p.relative_to(base))
        xml = WORK / "stage.xml"
        xml.write_text(XML.read_text().replace('source="extract/', 'source="stage/'))
    else:
        xml = XML
    out = WORK / (a.output or "rebuilt.bin")
    cue = out.with_suffix(".cue")
    subprocess.run([str(BIN / "mkpsxiso"), "-y", "-q", "-o", out.name, "-c", cue.name, xml.name],
                   cwd=WORK, check=True)
    print(f"rebuilt {out.relative_to(ROOT)} ({out.stat().st_size} bytes) from {src_root.relative_to(ROOT)}")
    return out


def cmd_check(a):
    disc = disc_path(a.disc)
    out = WORK / (a.output or "rebuilt.bin")
    if not out.exists():
        sys.exit(f"no {out.relative_to(ROOT)}: run `tools/disc.py rebuild` first")
    got, want = sha1(out), (sha1(disc) if disc.exists() else lock().get("disc", {}).get("sha1"))
    same = got == want
    print(f"rebuilt sha1 {got}\noriginal sha1 {want}\n{'BYTE-IDENTICAL' if same else 'DIFFERENT'} ({out.stat().st_size} bytes)")
    print("containers:")
    cok = cmd_check_containers()
    sys.exit(0 if same and cok else 1)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("extract"); p.add_argument("--disc"); p.add_argument("--force", action="store_true")
    p = sub.add_parser("rebuild"); p.add_argument("--sources", nargs="*"); p.add_argument("--output")
    p = sub.add_parser("check"); p.add_argument("--disc"); p.add_argument("--output")
    a = ap.parse_args()
    {"extract": cmd_extract, "rebuild": cmd_rebuild, "check": cmd_check}[a.cmd](a)


if __name__ == "__main__":
    main()
