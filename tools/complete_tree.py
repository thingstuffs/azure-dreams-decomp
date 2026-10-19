#!/usr/bin/env python3
"""Check that every registered row resolves to a current source file."""
import sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, rows
from source_layout import row_path as layout_row_path
def main():
    missing = []
    for r in rows():
        cp = layout_row_path(r, ROOT)
        if not cp.exists():
            missing.append(r["id"])
    if missing:
        raise SystemExit(f"{len(missing)} registered rows lack current source: {missing[:10]}")
    print("all registered rows resolve to current source")
if __name__ == "__main__": main()
