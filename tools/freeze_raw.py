#!/usr/bin/env python3
"""Freeze derived facts from the retired first-pass C archive.

Run before removing raw/, or extract the release archive and pass --raw-root.
The output contains hashes and facts, never source text.
"""
from __future__ import annotations

import argparse
import hashlib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools/gate"))
sys.path.insert(0, str(ROOT / "tools/build"))
from gen_noreturn_syms import scan_text  # noqa: E402
from slus_partitions import read_aliases, spans  # noqa: E402

DEF_RE = re.compile(r"^[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8})\s*\(", re.M)


def render(raw_root: Path, root: Path = ROOT) -> str:
    members = json.loads((root / "config/slus_modules.json").read_text())["modules"]
    canonical = {"raw/slus/" + Path(m["source"]).name
                 for module in members for m in module["members"]}
    plan = json.loads((root / "config/slus_partitions.json").read_text())
    canonical.update("raw/slus/" + Path(p["source"]).name for p in plan["parents"])
    aliases = read_aliases(root / "config/names.tsv")
    result = []
    for path in sorted(raw_root.rglob("*.c")):
        rel = "raw/" + str(path.relative_to(raw_root))
        data = path.read_bytes()
        source = data.decode(errors="replace")
        rec = {"path": rel, "sha256": hashlib.sha256(data).hexdigest(),
               "size": len(data)}
        names = sorted(scan_text(source))
        if names:
            rec["noreturn"] = names
        if rel.startswith("raw/slus/"):
            rec["defs"] = sorted(set(DEF_RE.findall(source)))
            if rel in canonical:
                rec["canonical"] = sorted(spans(source, aliases))
        result.append(json.dumps(rec, separators=(",", ":"), sort_keys=True) + "\n")
    return "".join(result)


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--raw-root", type=Path, default=ROOT / "raw")
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    if not args.raw_root.is_dir() or not next(args.raw_root.rglob("*.c"), None):
        ap.error("--raw-root must name an extracted release archive raw/ with C files")
    body = render(args.raw_root)
    dest = ROOT / "config/frozen_raw.jsonl"
    if args.check:
        if dest.read_text() != body:
            print("frozen raw facts differ from the archive", file=sys.stderr)
            return 1
    else:
        dest.write_text(body)
    print(f"{len(body.splitlines())} C files, {len(body)} table bytes")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
