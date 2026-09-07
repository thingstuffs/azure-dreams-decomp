"""Shared paths and helpers for azure-clean tools.

UP_LIVE is the upstream byte-matching tree: read-only here (toolchain, scorer, row DB).
Its location comes from $AZURE_CLEAN_UPSTREAM or the gitignored file `.upstream` at the repo
root (one line: the path); default `../upstream-decomp`.
UP is the mirror of that tree's tracked sources at the pinned commit (tools/refresh.py).
"""
from __future__ import annotations
import hashlib, json, os, re, subprocess, time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
def _upstream():
    env = os.environ.get("AZURE_CLEAN_UPSTREAM")
    if env: return Path(env)
    f = ROOT / ".upstream"
    if f.exists(): return Path(f.read_text().strip())
    return ROOT.parent / "upstream-decomp"
UP_LIVE = _upstream()
UP = ROOT / "upstream"
LEDGER = ROOT / "ledger"
CACHE = LEDGER / "cache"
PIN = (ROOT / "PIN").read_text().strip()
NICE = ["nice", "-n10", "ionice", "-c2", "-n7"]
OVERLAYS = ("main", "town", "dungeon", "ovmovie")   # dungeon_engine is a mirror of dungeon
PARKED_CONTAINERS = {"ovmovie"}   # owner 2026-09-07: movie playback exists elsewhere (ffmpeg); a curiosity at most
STOCK_CELLS = {"2.6.3", "2.7.2", "2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2"}

def sha_file(p) -> str:
    return hashlib.sha256(Path(p).read_bytes()).hexdigest()

def sha_text(s: str) -> str:
    return hashlib.sha256(s.encode()).hexdigest()

def read_jsonl(p):
    p = Path(p)
    if not p.exists():
        return []
    return [json.loads(l) for l in p.read_text().splitlines() if l.strip()]

def append_jsonl(p, rec):
    with open(p, "a") as fh:
        fh.write(json.dumps(rec, separators=(",", ":")) + "\n")

def write_jsonl(p, recs):
    with open(p, "w") as fh:
        for r in recs:
            fh.write(json.dumps(r, separators=(",", ":")) + "\n")

def rows(only=None):
    rs = read_jsonl(LEDGER / "rows.jsonl")
    if only:
        keep = set(only)
        rs = [r for r in rs if r["id"] in keep]
    return rs

def parse_cfg(cfg: str):
    """'2.7.2-cdk-G0 -fno-schedule-insns' -> ('2.7.2-cdk', ['-G0','-fno-schedule-insns']).
    Mirrors upstream tools/match.py parse_config_label: a -G0 glued to the version is a flag."""
    parts = cfg.split()
    head, flags = parts[0], parts[1:]
    if head.endswith("+"):
        head = head[:-1]
    if head.endswith("-G0"):
        head = head[:-3]; flags.insert(0, "-G0")
    return head, flags

def is_stock_cfg(cfg) -> bool:
    if not cfg:
        return False
    head, flags = parse_cfg(cfg)
    return head in STOCK_CELLS and all(re.fullmatch(r"-(G0|O[0-3]|f[a-z0-9-]+)", f) for f in flags)

def run(cmd, cwd=None, env=None, timeout=900):
    t0 = time.time()
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=cwd, env=env, timeout=timeout)
    return r, round(time.time() - t0, 2)
