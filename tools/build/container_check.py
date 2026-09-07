#!/usr/bin/env python3
"""Whole-container statement from the window gates, and the disc rebuilt from it.

    python3 tools/build/container_check.py [--rebuild-disc]

For each container (MAIN, TOWN, DUNGEON, OVMOVIE) every gated window's rebuilt bytes
(build_ovl/work/s3_splat/<window>/build/<window>.window.bin, left by tools/overlay_local_gate.py)
are compared again with the retail slice and spliced into an image of the container; the image's
SHA-1 must equal the retail container's (tools/toolchain.lock.json).  SLUS is the ninja gate's
output (build_slus/build/slus_006.14).  The record says honestly where the bytes come from:

  matched_bytes   bytes of registered rows compiled from src/ inside gated windows
  window_bytes    bytes inside gated windows (matched rows + the incbin fill the gate stages for
                  data and unmatched rows from the retail container)
  fill_bytes      bytes outside every window: retail, not rebuilt

One line per container in ledger/containers.jsonl.  --rebuild-disc writes the spliced containers
and the built SLUS into work/disc/rebuilt_containers/ (disc layout) and runs
`tools/disc.py rebuild --sources work/disc/rebuilt_containers` + `check`: the disc image from the
clean tree, byte-identical or not.
"""
from __future__ import annotations
import argparse, hashlib, json, subprocess, sys, time
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import LEDGER, rows, read_jsonl, append_jsonl, window_map

B = ROOT / "build_ovl"
CONT = {"main": "MAIN_MAIN.BIN", "town": "TOWN_TOWN.BIN", "dungeon": "DUNGEON_DUNGEON.BIN", "ovmovie": "OVMOVIE.BIN"}
LAYOUT = {"main": "MAIN/MAIN.BIN", "town": "TOWN/TOWN.BIN", "dungeon": "DUNGEON/DUNGEON.BIN", "ovmovie": "OVMOVIE.BIN"}


def sha1(b: bytes) -> str:
    return hashlib.sha1(b).hexdigest()


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rebuild-disc", action="store_true")
    a = ap.parse_args()
    lock = json.load(open(ROOT / "tools/toolchain.lock.json"))
    last = {}
    for j in read_jsonl(LEDGER / "gate.jsonl"):
        last[j["window"]] = j
    wm = window_map()
    regs = rows()
    out_dir = ROOT / "work/disc/rebuilt_containers"
    all_ok = True
    for cont, flat in CONT.items():
        retail = (ROOT / "work/disc/containers" / flat).read_bytes()
        image = bytearray(retail)          # retail fill; every gated window is written over it
        covered = bytearray(len(retail))   # 1 where a gated MATCH window supplied the bytes
        wins_ok = wins_bad = wins_missing = 0; bad = []
        for name, fs, fe, _ in wm.get(cont, []):
            w = name.replace(".overlay.yaml", "")
            verdict = last.get(w)
            if verdict is None:
                continue                    # superseded seed windows are not in the journal
            rebuilt = B / "work/s3_splat" / w / "build" / f"{w}.window.bin"
            if verdict["result"] != "MATCH":
                wins_bad += 1; bad.append(f"{w}: {verdict['result']}"); continue
            if not rebuilt.exists():
                wins_missing += 1; bad.append(f"{w}: MATCH in journal but no rebuilt window on disk (re-run gate_all --retry)"); continue
            got = rebuilt.read_bytes()
            if got != retail[fs:fe]:
                wins_bad += 1; bad.append(f"{w}: rebuilt bytes differ from retail slice"); continue
            image[fs:fe] = got; covered[fs:fe] = b"\x01" * (fe - fs); wins_ok += 1
        window_bytes = sum(covered)
        matched = sum(r["size"] for r in regs if r["container"] == cont and covered[r["foff"]] and r["stock"])
        got_sha = sha1(bytes(image)); want = lock["containers"][flat]
        ok = got_sha == want and not wins_bad and not wins_missing
        all_ok &= ok
        rec = {"at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), "container": cont, "file": flat, "bytes": len(retail),
               "sha1": got_sha, "retail_sha1": want, "identical": got_sha == want, "windows_ok": wins_ok, "windows_bad": wins_bad,
               "windows_missing": wins_missing, "window_bytes": window_bytes, "matched_bytes": matched, "fill_bytes": len(retail) - window_bytes}
        append_jsonl(LEDGER / "containers.jsonl", rec)
        print(f"{cont:8} {len(retail):>9} B  windows {wins_ok} ok / {wins_bad} bad / {wins_missing} missing  "
              f"window bytes {window_bytes} ({100*window_bytes/len(retail):.1f} %)  matched C {matched} ({100*matched/len(retail):.1f} %)  "
              f"retail fill {len(retail)-window_bytes}  sha1 {'OK' if got_sha == want else 'MISMATCH'}")
        for b in bad[:10]: print("   ", b)
        if a.rebuild_disc:
            p = out_dir / LAYOUT[cont]; p.parent.mkdir(parents=True, exist_ok=True); p.write_bytes(bytes(image))
    slus = ROOT / "build_slus/build/slus_006.14"
    if slus.exists():
        s = sha1(slus.read_bytes()); ok = s == lock["containers"]["SLUS_006.14"]; all_ok &= ok
        print(f"{'slus':8} {slus.stat().st_size:>9} B  ninja gate output sha1 {'OK' if ok else 'MISMATCH'} (tools/build/build_slus.sh)")
        if a.rebuild_disc:
            (out_dir / "SLUS_006.14").write_bytes(slus.read_bytes())
    else:
        print("slus: no build_slus/build/slus_006.14 (run tools/build/build_slus.sh)"); all_ok = False
    if a.rebuild_disc:
        r = subprocess.run([sys.executable, str(ROOT / "tools/disc.py"), "rebuild", "--sources", str(out_dir), "--output", "rebuilt_from_tree.bin"], cwd=ROOT)
        r2 = subprocess.run([sys.executable, str(ROOT / "tools/disc.py"), "check", "--output", "rebuilt_from_tree.bin"], cwd=ROOT)
        all_ok &= r.returncode == 0 and r2.returncode == 0
    sys.exit(0 if all_ok else 1)


if __name__ == "__main__":
    main()
