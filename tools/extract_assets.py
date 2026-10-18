#!/usr/bin/env python3
"""Extract link-list asset slices from a user's disc into ignored work/assets; verify every SHA-256."""
from __future__ import annotations
import argparse
import hashlib
import json
from pathlib import Path
import sys
import tempfile

sys.path.insert(0, str(Path(__file__).resolve().parent / "gate"))
import linklist
from disc_slice import Disc

DISC_FILES = {"main": "MAIN/MAIN.BIN", "town": "TOWN/TOWN.BIN", "dungeon": "DUNGEON/DUNGEON.BIN",
              "ovmovie": "OVMOVIE.BIN", "slus": "SLUS_006.14"}


def extract(root, disc, keys=None, output=None, catalogue=None):
    root = Path(root).resolve()
    if catalogue is None:
        images = linklist.load(root)[0]
    else:
        from byte_map import load_maps
        images = load_maps(root, catalogue)[0]
    keys = keys or [k for k, v in images.items() if v["schema"] == linklist.MAP_SCHEMA]
    if any(k not in images or images[k]["schema"] != linklist.MAP_SCHEMA for k in keys):
        raise ValueError("selected image is missing or is still v0")
    base = (root/"work/assets").resolve()
    # Resolve symlinks before checking containment; extracted bytes must remain under this private root.
    base.relative_to(root)
    out = Path(output).resolve() if output is not None else base
    out.relative_to(base)
    base.mkdir(parents=True, exist_ok=True)
    for name in (".gitignore", ".ignore"):
        p = base/name
        wanted = "*\n!.gitignore\n!.ignore\n" if name == ".gitignore" else "*\n"
        if p.exists() and p.read_text() != wanted:
            raise ValueError("unexpected asset ignore rules: " + str(p))
        p.write_text(wanted)
    assets, visited = {}, set()
    def collect(key):
        if key in visited:
            return
        visited.add(key)
        for e in images[key]["entries"]:
            if e.get("kind") == "image":
                collect(e["ref"])
            elif e.get("kind") == "asset":
                identity = (images[key]["container"], e["foff"], e["size"])
                if identity in assets and assets[identity]["sha256"] != e["sha256"]:
                    raise ValueError("conflicting asset hashes for one physical extent")
                assets[identity] = e
    for key in keys:
        collect(key)
    receipts = []
    with Disc(disc) as source:
        for (cont, off, size), e in sorted(assets.items()):
            directory = out/cont
            directory.mkdir(parents=True, exist_ok=True)
            directory.resolve().relative_to(base)
            target = directory/("%08x_%x_%s.blob" % (off, size, e["sha256"][:16]))
            target.resolve().relative_to(base)
            h = hashlib.sha256()
            # A bad disc/hash leaves no published asset (only verified bytes replace an existing result).
            with tempfile.NamedTemporaryFile(dir=directory, prefix=".extract-", delete=False) as f:
                tmp = Path(f.name)
                try:
                    for start in range(0, size, 1 << 20):
                        blob = source.slice(DISC_FILES[cont], off+start, min(1 << 20, size-start))
                        h.update(blob)
                        f.write(blob)
                    if h.hexdigest() != e["sha256"]:
                        raise ValueError("asset SHA-256 differs: %s 0x%X" % (cont, off))
                except BaseException:
                    tmp.unlink(missing_ok=True)
                    raise
            tmp.replace(target)
            receipts.append({"container": cont, "foff": off, "size": size, "sha256": h.hexdigest(),
                             "path": target.relative_to(root).as_posix(), "verified": True})
    return {"assets": receipts, "count": len(receipts), "bytes": sum(x["size"] for x in receipts)}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, default=Path(__file__).resolve().parents[1])
    ap.add_argument("--disc", type=Path, required=True)
    ap.add_argument("--image", action="append")
    ap.add_argument("--out", type=Path)
    ap.add_argument("--catalogue", type=Path, help="byte-map catalogue, e.g. link")
    a = ap.parse_args()
    try:
        print(json.dumps(extract(a.root, a.disc, a.image, a.out, a.catalogue), sort_keys=True, indent=2))
    except (OSError, ValueError, KeyError, TypeError) as exc:
        ap.exit(1, "extract assets: " + str(exc) + "\n")


if __name__ == "__main__":
    main()
