#!/usr/bin/env python3
"""Rebuild upstream/ as a read-only mirror of the tracked sources at PIN.

    python3 tools/refresh.py            # (re)extract src overlays include config docs at PIN
The live tree's untracked build.ninja (SLUS per-TU compiler recipes) is copied alongside
and its hash recorded, because tools/configure.py only writes into the live tree.
"""
import shutil, subprocess, sys, json, time
from common import ROOT, UP, UP_LIVE, PIN, sha_file, LEDGER

def main():
    head = subprocess.run(["git", "-C", str(UP_LIVE), "rev-parse", "--verify", PIN + "^{commit}"],
                          capture_output=True, text=True, check=True).stdout.strip()
    if UP.exists():
        shutil.rmtree(UP)
    UP.mkdir()
    subprocess.run(f"git -C {UP_LIVE} archive {head} src overlays include config docs | tar -x -C {UP}",
                   shell=True, check=True)
    shutil.copy(UP_LIVE / "build.ninja", UP / "build.ninja.pinned")
    meta = {"pin": PIN, "commit": head, "extracted_at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
            "build_ninja_sha256": sha_file(UP / "build.ninja.pinned"),
            "live_head": subprocess.run(["git", "-C", str(UP_LIVE), "rev-parse", "HEAD"], capture_output=True, text=True).stdout.strip()}
    LEDGER.mkdir(exist_ok=True)
    (LEDGER / "pin.json").write_text(json.dumps(meta, indent=1) + "\n")
    print(json.dumps(meta, indent=1))

if __name__ == "__main__":
    main()
