#!/usr/bin/env python3
"""Resolve a function name to its retail target bytes — overlay or main EXE.

Single source of truth for the func -> (container, foff, size, config) lookup
so tools stop needing hand-fed --overlay/--container parameters (the 8004099C
rebuild burnt time re-deriving them per invocation).

VRAM ALIASING GUARD: the same func_XXXXXXXX name can exist both as a main-EXE
function and inside an overlay (e.g. func_80041588: main/SLUS bytes, NOT the
OVMOVIE bytes at the same apparent address). When a name resolves in more than
one place this module refuses to guess — callers must pass overlay=... or
main_exe=True.
"""
import importlib.util
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

CONTAINERS = {
    "ovmovie": "work/s3_splat/extract/OVMOVIE.BIN",
    "town": "work/s3_splat/extract/TOWN_TOWN.BIN",
    "dungeon": "work/s3_splat/extract/DUNGEON_DUNGEON.BIN",
    "dungeon_engine": "work/s3_splat/extract/DUNGEON_DUNGEON.BIN",
    "main": "work/s3_splat/extract/MAIN_MAIN.BIN",
}

_match_mod = None


def _match():
    global _match_mod
    if _match_mod is None:
        spec = importlib.util.spec_from_file_location(
            "match", os.path.join(ROOT, "tools", "match.py"))
        _match_mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(_match_mod)
    return _match_mod


def overlay_rows(overlay):
    path = os.path.join(ROOT, "overlays", overlay, "overlay_first_pass_results.json")
    if not os.path.exists(path):
        return []
    with open(path) as f:
        return json.load(f)


def overlay_names():
    base = os.path.join(ROOT, "overlays")
    return sorted(
        d for d in os.listdir(base)
        if os.path.exists(os.path.join(base, d, "overlay_first_pass_results.json")))


def find_overlay_hits(func, overlay=None):
    hits = []
    for ov in ([overlay] if overlay else overlay_names()):
        for row in overlay_rows(ov):
            if row.get("func_vram") == func and not row.get("rerun"):
                hits.append((ov, row))
    return hits


def resolve(func, overlay=None, main_exe=False):
    """Return a target descriptor dict:
      kind: 'overlay' | 'main-exe'
      overlay, row, container (abs path), foff, size, config  (overlay kind)
      start, size                                             (main-exe kind)
    Raises SystemExit with an actionable message on miss or ambiguity.
    """
    if main_exe and overlay:
        sys.exit("az_target: pass overlay=... or main_exe=True, not both")

    ov_hits = [] if main_exe else find_overlay_hits(func, overlay)
    main_hit = None
    if not overlay:
        start, length = _match().func_extent(func)
        if start is not None:
            main_hit = (start, length)

    if main_exe:
        if main_hit is None:
            sys.exit(f"az_target: {func} not found in main-EXE asm/")
        return {"kind": "main-exe", "start": main_hit[0], "size": main_hit[1]}

    if ov_hits and main_hit and not overlay:
        places = ", ".join(f"overlay {ov}" for ov, _ in ov_hits)
        sys.exit(
            f"az_target: {func} is AMBIGUOUS — exists as main-EXE bytes AND in "
            f"{places} (vram aliasing; cf. the func_80041588 false lead). "
            f"Pass --overlay <name> or --main to disambiguate.")
    if len(ov_hits) > 1:
        places = ", ".join(ov for ov, _ in ov_hits)
        sys.exit(f"az_target: {func} found in multiple overlays ({places}); pass --overlay")

    if ov_hits:
        ov, row = ov_hits[0]
        cont_key = row.get("container") or ov
        rel = CONTAINERS.get(cont_key)
        if rel is None:
            sys.exit(f"az_target: no container mapping for '{cont_key}' (overlay {ov})")
        cont = os.path.join(ROOT, rel)
        if not os.path.exists(cont):
            sys.exit(f"az_target: container missing: {cont}")
        return {
            "kind": "overlay", "overlay": ov, "row": row, "container": cont,
            "foff": int(row["foff"]), "size": int(row["size"]),
            "config": row.get("config"),
        }
    if main_hit:
        return {"kind": "main-exe", "start": main_hit[0], "size": main_hit[1]}
    sys.exit(f"az_target: {func} not found in main-EXE asm/ or any overlay results JSON")


def retail_bytes(desc):
    """Read the retail bytes for a descriptor returned by resolve()."""
    if desc["kind"] == "overlay":
        with open(desc["container"], "rb") as f:
            f.seek(desc["foff"])
            return f.read(desc["size"])
    with open(_match().BASEROM, "rb") as f:
        f.seek(desc["start"])
        return f.read(desc["size"])


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser(description="resolve a function to its retail target")
    ap.add_argument("func")
    ap.add_argument("--overlay")
    ap.add_argument("--main", action="store_true")
    a = ap.parse_args()
    d = resolve(a.func, overlay=a.overlay, main_exe=a.main)
    print(json.dumps({k: v for k, v in d.items() if k != "row"}, indent=1))
