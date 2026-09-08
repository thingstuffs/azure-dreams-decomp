"""Shared paths and helpers for azure-clean tools.

RAW is the frozen pinned source snapshot (raw/<container>/<file>.c, raw/include): the text every
row started from.  The clean file of a row is src/<container>/<file>.c (clean_path), its pinned
text raw/<container>/<file>.c (raw_path).  The row database is ledger/splits/ + ledger/rows.jsonl
(tools/row_db.py, tools/registry.py); the toolchain, venv, disc and containers live in this tree
(tools/setup.sh).  UP / UP_LIVE only matter to tools/refresh.py and tools/pin_bump.py, the
historical sync path: a transient mirror of another checkout at a commit, gone after the
swap-over (docs/SWAPOVER.md).
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
UP = ROOT / "upstream"          # transient mirror (pin bumps only)
RAW = ROOT / "raw"
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

def raw_path(row) -> Path:
    """The row's pinned text (frozen)."""
    return RAW / row["container"] / Path(row["c_path"]).name

def clean_path(row) -> Path:
    """The row's clean file (every registered row has one: tools/complete_tree.py)."""
    return ROOT / "src" / row["container"] / Path(row["c_path"]).name

def current_text(row) -> str:
    p = clean_path(row)
    return (p if p.exists() else raw_path(row)).read_text(errors="replace")

_WM = None
def window_map():
    """{container: [(name, file_start, file_end, vram_start), ...]} from config/overlays/*.overlay.yaml
    (the engine window is a dungeon-container window)."""
    global _WM
    if _WM is None:
        _WM = {}
        for y in sorted((ROOT / "config/overlays").glob("*.overlay.yaml")):
            t = y.read_text(errors="replace")
            tp = re.search(r"target_path:\s*(\S+)", t); fs = re.search(r"file_start:\s*(0x[0-9A-Fa-f]+)", t)
            fe = re.search(r"file_end:\s*(0x[0-9A-Fa-f]+)", t); vs = re.search(r"vram_start:\s*(0x[0-9A-Fa-f]+)", t)
            if not (tp and fs and fe): continue
            cont = Path(tp.group(1)).name.split("_")[0].lower().replace(".bin", "")
            _WM.setdefault(cont, []).append((y.name, int(fs.group(1), 16), int(fe.group(1), 16), int(vs.group(1), 16) if vs else None))
    return _WM

def covering_windows(container, foff, size, wm=None):
    """Windows whose file range holds [foff, foff+size): the gate compiles every MATCH row inside
    a window's range, whether or not the row's record names that window."""
    wm = wm or window_map()
    return [w for w in wm.get(container, []) if w[1] <= foff and foff + size <= w[2]]

def rows(only=None):
    rs = read_jsonl(LEDGER / "rows.jsonl")
    if only:
        keep = set(only)
        rs = [r for r in rs if r["id"] in keep]
    return rs

KEYED_ASFLAG_RE = re.compile(r"(^|\s)--retail-")          # a per-function maspsx dial (upstream: ASM_KEYED_FLAG_RE)
ORDINARY_FLAG_RE = re.compile(r"-(G\d+|O[0-3]|f(?!retail-|sn-|driver-)[a-z0-9-]+|m[a-z0-9-]+)")

def parse_cfg(cfg: str):
    """'2.7.2-cdk-G0 -fno-schedule-insns' -> ('2.7.2-cdk', ['-G0','-fno-schedule-insns']).
    Mirrors upstream tools/match.py parse_config_label: both label dialects parse identically —
    space dialect '2.8.1 -G0 -f..' and plus dialect '2.8.1+-G0 -f..' (a '+' glues the first
    flag to the version); a -G0 glued to the version is a flag."""
    parts = cfg.split()
    head, flags = parts[0], parts[1:]
    if "+" in head:
        head, plus = head.split("+", 1)
        if plus:
            flags.insert(0, plus)
    if head.endswith("-G0"):
        head = head[:-3]; flags.insert(0, "-G0")
    return head, flags

def is_stock_cfg(cfg) -> bool:
    """A stock cc1 with ordinary gcc flags only (no -fretail-/-fsn-/-fdriver- bridge flags),
    the same rule upstream's live_truth applies to its census."""
    if not cfg:
        return False
    head, flags = parse_cfg(cfg)
    return head in STOCK_CELLS and all(ORDINARY_FLAG_RE.fullmatch(f) for f in flags)

def is_keyed_asflags(asflags) -> bool:
    """True when a row's maspsx options include a per-function --retail-* dial (non-stock);
    general-purpose options (--expand-div, --aspsx-version=, --preserve-*, ...) are stock."""
    return bool(asflags) and bool(KEYED_ASFLAG_RE.search(asflags))

def run(cmd, cwd=None, env=None, timeout=900):
    t0 = time.time()
    r = subprocess.run(cmd, capture_output=True, text=True, cwd=cwd, env=env, timeout=timeout)
    return r, round(time.time() - t0, 2)

def set_row_cfg(row_id: str, cfg: str, note: str = ""):
    """Correct a row's compiler config (must be a stock cell): ledger/splits/<container>.jsonl `config`,
    ledger/rows.jsonl cfg/cell/flags, and the exported row tables of the build roots (so the window gate
    compiles the row with the new cell).  The caller has verified the row's text exact at `cfg`."""
    import subprocess, sys as _sys
    if not is_stock_cfg(cfg):
        raise ValueError(f"{cfg!r} is not a stock config")
    container, func = row_id.split("/", 1)
    p = LEDGER / "splits" / f"{container}.jsonl"
    recs = read_jsonl(p); hit = 0
    for r in recs:
        if r.get("func_vram") == func:
            r["config_was"] = r.get("config"); r["config"] = cfg
            if note: r["config_note"] = note
            hit += 1
    if hit != 1:
        raise ValueError(f"{row_id}: {hit} split records")
    write_jsonl(p, recs)
    rs = read_jsonl(LEDGER / "rows.jsonl"); cell, flags = parse_cfg(cfg)
    for r in rs:
        if r["id"] == row_id:
            r["cfg"] = cfg; r["cell"] = cell; r["flags"] = " ".join(flags); r["stock"] = True; r["cfg_corrected"] = True
    write_jsonl(LEDGER / "rows.jsonl", rs)
    for root in (ROOT / "build_ovl", ROOT / "build_ovl_raw"):
        if (root / "overlays").exists():
            subprocess.run([_sys.executable, str(ROOT / "tools/row_db.py"), "export", str(root)], check=True, stdout=subprocess.DEVNULL)
