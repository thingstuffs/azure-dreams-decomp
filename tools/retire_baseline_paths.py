#!/usr/bin/env python3
"""Remove live raw paths from baseline events while retaining measured facts."""
from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
RAW_LOCATION = re.compile(r"(?:(?:[A-Za-z0-9_.-]+/)+)?raw/(?:main|town|dungeon|ovmovie|slus|include)/[A-Za-z0-9_./-]+")


def clean(record: dict) -> dict:
    result = dict(record)
    for key in ("source", "source_path", "m2c_first_pass"):
        if isinstance(result.get(key), str) and result[key].startswith("raw/"):
            del result[key]
    err = result.get("err")
    if isinstance(err, str) and RAW_LOCATION.search(err):
        result["err_sha256"] = hashlib.sha256(err.encode()).hexdigest()
        result["err"] = RAW_LOCATION.sub("[archived first-pass source]", err)
    return result


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--path", type=Path, default=ROOT / "ledger/baseline.jsonl")
    ap.add_argument("--check", action="store_true")
    args = ap.parse_args()
    original = args.path.read_text()
    output = "".join(json.dumps(clean(json.loads(line)), separators=(",", ":")) + "\n"
                     for line in original.splitlines() if line.strip())
    if args.check:
        if output != original:
            print("baseline contains live raw paths or is not in canonical form")
            return 1
    elif output != original:
        tmp = args.path.with_suffix(args.path.suffix + ".tmp")
        tmp.write_text(output)
        os.replace(tmp, args.path)
    print(f"baseline records: {len(output.splitlines())}; changed={output != original}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
