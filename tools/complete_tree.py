#!/usr/bin/env python3
"""Keep src/ complete: every registered row has a file (the raw pinned copy when no transform
has touched it).  Run after any re-derivation or pin bump."""
import json, shutil, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, rows
def main():
    n = 0
    for r in rows():
        name = Path(r["c_path"]).name
        cp = ROOT / "src" / r["container"] / name; raw = ROOT / "raw" / r["container"] / name
        if not cp.exists() and raw.exists():
            cp.parent.mkdir(parents=True, exist_ok=True); shutil.copyfile(raw, cp); n += 1
    print(f"restored {n} missing files from raw/")
if __name__ == "__main__": main()
