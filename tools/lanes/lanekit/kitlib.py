#!/usr/bin/env python3
"""Shared plumbing for the lane kit (`tools/lanes/lanekit/`).

Nothing here touches the filesystem at import time and nothing here asserts "you are in a lane":
`unittest discover` imports this module from the repository root, and a module-level lane check
would fail discovery.  Call `bootstrap()` from a tool's `main()` instead.

What a lane gets from this module:

* `bootstrap()`  - resolve the lane directory, put `tools/`, `tools/xform/` and `tools/lanes/` on
  `sys.path`, point `TMPDIR` *and* `tempfile.tempdir` at `<lane>/tmp`, and install the compiler-cwd
  shim.  Every shared tool (`xform.screen`, `alloc_sim`, `loop_census`, `sched_trace`) compiles
  inside its own `TemporaryDirectory`, so once `tempfile.tempdir` is inside the lane every `-da`
  dump lands inside the lane BY CONSTRUCTION - the shim is only the backstop for a compiler that
  would otherwise run at the repository root.
* `row_of`, `base_text`, `erased_text`, `sites` - the row and its two reference texts.
* `rep` / `apply_subs` - the assert-and-replace helper every lane hand-rolls, with the near-miss
  message (16 lanes hit a stale literal and paid one exec each for a bare `AssertionError`).
* `admissible` - the admission gate seven lanes independently re-derived as asserts.
* `dumps` - one `-da` compile -> every pass dump as text, for `why.py`.
* `log_append` / `log_read` - the per-lane measurement ledger `lab_log.jsonl`.
"""
from __future__ import annotations

import difflib
import json
import os
import re
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
KIT = Path(__file__).resolve().parent

LOG_NAME = "lab_log.jsonl"
VARIANT_CAP = 60                 # per row, per lane: the 209-probe explosion of r66_sol_big6

_BOOTSTRAPPED = None


# --------------------------------------------------------------------------------- lane + imports

def lane_dir(create=True):
    """The lane directory: `$LANEKIT_LANE` if set, else the current directory.

    Never the repository root and never outside it: a lane writes only inside itself."""
    d = Path(os.environ.get("LANEKIT_LANE") or Path.cwd()).resolve()
    if d == ROOT:
        raise SystemExit(
            "lanekit: refusing to run at the repository root.\n"
            "  cd work/native_lane/<lane> && python3 %s/<tool>.py ...   (or set LANEKIT_LANE)" % KIT)
    try:
        d.relative_to(ROOT)
    except ValueError:
        raise SystemExit("lanekit: lane directory %s is outside the repository %s" % (d, ROOT))
    if not d.is_dir():
        raise SystemExit("lanekit: lane directory %s does not exist" % d)
    if create:
        (d / "tmp").mkdir(exist_ok=True)
    return d


def add_paths():
    """`tools/`, `tools/xform/`, `tools/lanes/` on sys.path, in that order, once.

    These are the three directories every lane guesses wrong (>=15 recorded misses in 7 astra lanes
    and 4 sol lanes): `pin_census`/`pin_sites`/`verify`/`common` live in `tools/`, `screen`/
    `variant_screen`/`sched_trace`/`reg_state` in `tools/xform/`, `joint_scan`/`loop_census`/
    `duck_brief` in `tools/lanes/`."""
    for sub in ("tools", "tools/xform", "tools/lanes"):
        p = str(ROOT / sub)
        if p not in sys.path:
            sys.path.insert(0, p)


def bootstrap(lane=None):
    """Lane directory + sys.path + lane-local TMPDIR + the compiler-cwd shim.  Idempotent."""
    global _BOOTSTRAPPED
    if _BOOTSTRAPPED is not None:
        return _BOOTSTRAPPED
    d = Path(lane).resolve() if lane else lane_dir()
    (d / "tmp").mkdir(exist_ok=True)
    os.environ["LANEKIT_LANE"] = str(d)
    os.environ["TMPDIR"] = str(d / "tmp")
    os.environ.setdefault("PYTHONDONTWRITEBYTECODE", "1")
    sys.dont_write_bytecode = True
    tempfile.tempdir = str(d / "tmp")        # gettempdir() caches: the env var alone is not enough
    add_paths()
    sys.path.insert(0, str(KIT))             # so a child python inherits the shim via PYTHONPATH
    os.environ["PYTHONPATH"] = os.pathsep.join(
        [str(KIT)] + [x for x in os.environ.get("PYTHONPATH", "").split(os.pathsep) if x])
    import lane_shim                          # noqa: E402  (installs the Popen wrapper)
    lane_shim.install(d)
    _BOOTSTRAPPED = d
    return d


# ------------------------------------------------------------------------------- rows and texts

def row_of(row_id):
    add_paths()
    from common import rows                                              # noqa: E402
    for r in rows():
        if r["id"] == row_id or r["id"].split("/")[-1] == row_id or r["func"] == row_id:
            # slus rows (all 556) carry func=None in common.rows(); lab.py/erase.py name files by it (r77_opus_m1)
            return r if r["func"] else dict(r, func=r["id"].split("/")[-1])
    raise SystemExit("lanekit: no row %r (use the full id, e.g. dungeon/func_8009612C)" % row_id)


def base_path(row, lane):
    """The lane's own copy of the row's text (`base/<container>/<name>.c`) or the tree's.

    A lane pack copies each row under `base/`; that copy is the text the lane must work from, and it
    is also what `served.py` reads.  When a lane has no copy (a scratch lane), the tree is used."""
    local = Path(lane) / "base" / row["container"] / Path(row["c_path"]).name
    if local.is_file():
        return local
    add_paths()
    from common import clean_path                                        # noqa: E402
    return clean_path(row)


def base_text(row, lane):
    return base_path(row, lane).read_text(errors="replace")


def sites(text):
    add_paths()
    from pin_census import sites_of                                      # noqa: E402
    return sites_of(text)


def erase(text, chosen):
    add_paths()
    from pin_sites import erase_many                                     # noqa: E402
    return erase_many(text, chosen, clean_notes=True)


def erased_text(text):
    """The row's text with every LIVE pin erased (the base every generator starts from)."""
    return erase(text, sites(text))


def screen_for(row, pinned):
    """`variant_screen.Screen` against the PINNED listing (retail's order on a byte-exact row)."""
    add_paths()
    from variant_screen import Screen                                    # noqa: E402
    return Screen(row, pinned)


def module_fingerprint(row):
    """Current module inputs, or None for an ordinary row."""
    if row.get("kind") != "slus":
        return None
    add_paths()
    from slus_module_context import fingerprint                         # noqa: E402
    return fingerprint(row)


# ------------------------------------------------------------------- substitution helper (item 6)

def rep(text, old, new, label=""):
    """`text` with the first `old` replaced by `new`; on a miss, the nearest lines in the text.

    Six lanes hit an `AssertionError: old in text` from a stale literal and paid one exec each
    working out which literal had drifted.  The message does that work."""
    if old in text:
        return text.replace(old, new, 1)
    lines = [l.strip() for l in text.splitlines() if l.strip()]
    near = difflib.get_close_matches(old.strip(), lines, n=3, cutoff=0.4)
    raise KeyError("%spattern not in text: %r\n  nearest lines in the text:\n%s"
                   % (label and label + ": ", old,
                      "\n".join("    %r" % n for n in near) or "    (nothing close)"))


def apply_subs(base, reps, label=""):
    """`variants.json` semantics, byte-compatible with `tools/xform/variant_screen.py`:
    a list of `[old, new]` pairs applied in order, each replacing the FIRST occurrence."""
    out = base
    for i, pair in enumerate(reps):
        old, new = pair[0], pair[1]
        out = rep(out, old, new, label="%s[%d]" % (label, i) if label else "sub[%d]" % i)
    return out


# ----------------------------------------------------------------------------- admission gate (9)

BANNED = (
    (re.compile(r"\bvolatile\b"), "volatile"),
    (re.compile(r"__asm__|\basm\s*\("), "__asm__"),
)
ONE_TRIP = (
    (re.compile(r"\bdo\b[\s\S]{0,400}?\bwhile\s*\(\s*0\s*\)"), "do { } while (0)"),
    (re.compile(r"\bwhile\s*\(\s*0\s*\)"), "while (0)"),
    (re.compile(r"\bfor\s*\([^;]*;\s*0\s*;"), "for (;0;)"),
)


def pin_keys(text):
    """The `(kind, macro, arg)` multiset of a text's live pins - what a candidate must SHRINK."""
    import collections
    return collections.Counter((s[0], s[1], s[2]) for s in sites(text))


def admissible(base, cand):
    """[] when `cand` may be staged against `base`, else the reasons it may not.

    The checks `publish_local.py`, `finalize.py`, `stage.py`, `prepare_outputs.py`, `finish.py`
    (seven lanes) each re-derived: strictly fewer pin sites, the remaining pins a SUBSET of the
    base's, no new volatile/`__asm__`, no new one-trip block."""
    bad = []
    b, c = pin_keys(base), pin_keys(cand)
    if sum(c.values()) >= sum(b.values()):
        bad.append("pin sites not reduced (%d -> %d)" % (sum(b.values()), sum(c.values())))
    extra = c - b
    if extra:
        bad.append("pins the base did not have: %s" % ", ".join("%s %s(%s)" % k for k in extra))
    for rx, name in BANNED:
        if len(rx.findall(cand)) > len(rx.findall(base)):
            bad.append("adds %s" % name)
    for rx, name in ONE_TRIP:
        if len(rx.findall(cand)) > len(rx.findall(base)):
            bad.append("adds a one-trip block: %s" % name)
    if "ASM_" in cand:
        na = len(re.findall(r"\bASM_[A-Z_]+", cand)) - len(re.findall(r"\bASM_[A-Z_]+", base))
        if na > 0:
            bad.append("adds %d ASM_* token(s)" % na)
    return bad


# ------------------------------------------------------------------------------------- dump compile

PASS_SUFFIX = {
    "rtl": "rtl", "jump": "jump", "cse": "cse", "loop": "loop", "cse2": "cse2", "flow": "flow",
    "combine": "combine", "sched": "sched", "lreg": "lreg", "greg": "greg", "sched2": "sched2",
    "jump2": "jump2", "dbr": "dbr", "addressof": "addressof", "bp": "bp",
}


def dumps(row, text, want=None, timeout=None):
    """{'asm': ..., '<pass>': dump text} for `text` compiled as `row` with `-da`.

    One compile gives every pass, so `why.py` never needs a second one for a second pass.  The
    compile runs inside a TemporaryDirectory, which `bootstrap()` has already placed inside the
    lane; the directory and its dumps are removed on the way out.  Returns None if it does not
    build (with the compiler's message under 'error')."""
    add_paths()
    from common import parse_cfg, NICE                                   # noqa: E402
    cell, flags = parse_cfg(row["cfg"])
    D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    to = float(timeout or os.environ.get("PIN_CC_TIMEOUT", "60"))
    with tempfile.TemporaryDirectory(prefix="lanekit_") as td:
        d = Path(td)
        candidate = d / "f.c"
        candidate.write_text(text)
        source = candidate
        context_fp = module_fingerprint(row)
        if context_fp is not None:
            from slus_module_context import compilation_source          # noqa: E402
            source = compilation_source(row, candidate, d)
        def stale_context():
            return context_fp is not None and module_fingerprint(row) != context_fp
        env = dict(os.environ, TMPDIR=str(d), PYTHONDONTWRITEBYTECODE="1")
        try:
            r = subprocess.run(NICE + [str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags,
                                       "-I" + str(ROOT / "include"), "-w", source.name, "-o", "f.i"],
                               cwd=d, capture_output=True, text=True, env=env, timeout=to)
            if stale_context():
                return {"error": "module context changed during diagnostic compile; re-run"}
            if r.returncode:
                return {"error": (r.stderr or r.stdout)[-800:]}
            r = subprocess.run(NICE + [str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-da",
                                       "-o", "f.s"], cwd=d, capture_output=True, text=True,
                               env=env, timeout=to)
            if stale_context():
                return {"error": "module context changed during diagnostic compile; re-run"}
            if r.returncode:
                return {"error": (r.stderr or r.stdout)[-800:]}
        except subprocess.TimeoutExpired:
            return {"error": "compiler-timeout"}
        out = {"error": None, "asm": (d / "f.s").read_text(errors="replace")}
        for p in sorted(d.iterdir()):
            suf = p.suffix[1:]
            if suf in PASS_SUFFIX and (want is None or suf in want):
                out[suf] = p.read_text(errors="replace")
        return out


# ------------------------------------------------------------------ another cfg, no ledger write

def row_at_cfg(row, cfg):
    """`row` as if it were registered at `cfg` - an in-memory copy only; the ledger is never touched.

    The same override `tools/lanes/land_coherence.sh` and `land_recipe_switch.sh` score with:
    `cfg`, `cell` AND `flags` (the slus scorer reads `cell`/`flags`, not `cfg`)."""
    if not cfg:
        return row
    add_paths()
    if cfg != row["cfg"] and module_fingerprint(row) is not None:
        from slus_module_context import require_individual_recipe       # noqa: E402
        require_individual_recipe(row)
    from common import parse_cfg                                         # noqa: E402
    cell, flags = parse_cfg(cfg)
    return dict(row, cfg=cfg, cell=cell, flags=" ".join(flags))


def score_at(row, text, cfg=None, verify=None, diff=False):
    """Byte-score `text` as `row` at `cfg` (default the registered cfg) - `tools/verify.verify`
    on a temporary copy named like the row's file, include root `<repo>/include`."""
    if verify is None:
        add_paths()
        from verify import verify                                        # noqa: E402
    r = row_at_cfg(row, cfg)
    with tempfile.TemporaryDirectory(prefix="lanekit_score_") as td:
        f = Path(td) / Path(r["c_path"]).name
        f.write_text(text)
        kw = {"diff": True} if diff else {}
        return verify(r, f, include_root=(ROOT / "include").resolve(), **kw)


def score_fields(v):
    return {k: (v or {}).get(k) for k in ("exact", "total", "subs", "indels", "status")}


# ---------------------------------------------------------------------------------- lane ledger

def log_append(lane, rec):
    p = Path(lane) / LOG_NAME
    with p.open("a") as f:
        f.write(json.dumps(rec, sort_keys=True) + "\n")
    return p


def log_read(lane):
    p = Path(lane) / LOG_NAME
    if not p.is_file():
        return []
    out = []
    for line in p.read_text(errors="replace").splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            out.append(json.loads(line))
        except json.JSONDecodeError:
            continue
    return out


def variant_count(records, row_id):
    """Distinct variant names measured for one row - what the per-row cap counts."""
    return len({r.get("variant") for r in records
                if r.get("row") == row_id and r.get("variant") and r.get("kind") != "baseline"})


def lane_rows(lane):
    """Row ids the lane was served, from its own `base/<container>/<name>.c` copies."""
    d = Path(lane) / "base"
    if not d.is_dir():
        return []
    return sorted(f.parent.name + "/" + f.stem for f in d.glob("*/*.c"))


def fmt_table(head, body, sep="  "):
    """A plain aligned table (no dependency, no colour) - REPORT.md pastes it as is."""
    cols = [head] + [[("" if x is None else str(x)) for x in r] for r in body]
    w = [max(len(r[i]) for r in cols) for i in range(len(head))]
    out = [sep.join(h.ljust(w[i]) for i, h in enumerate(head)).rstrip(),
           sep.join("-" * w[i] for i in range(len(head)))]
    for r in cols[1:]:
        out.append(sep.join(r[i].ljust(w[i]) for i in range(len(head))).rstrip())
    return "\n".join(out)
