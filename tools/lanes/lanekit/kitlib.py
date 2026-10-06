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

def rep(text, old, new, label="", count=1):
    """`text` with the first `old` (every `old` when count=0) replaced by `new`; on a miss, the nearest lines.

    Six lanes hit an `AssertionError: old in text` from a stale literal and paid one exec each
    working out which literal had drifted.  The message does that work."""
    if old in text:
        return text.replace(old, new, count if count else -1)
    lines = [l.strip() for l in text.splitlines() if l.strip()]
    near = difflib.get_close_matches(old.strip(), lines, n=3, cutoff=0.4)
    raise KeyError("%spattern not in text: %r\n  nearest lines in the text:\n%s"
                   % (label and label + ": ", old,
                      "\n".join("    %r" % n for n in near) or "    (nothing close)"))


def apply_subs(base, reps, label=""):
    """`variants.json` semantics, byte-compatible with `tools/xform/variant_screen.py`:
    a list of `[old, new]` pairs applied in order, each replacing the FIRST occurrence.  A third element
    `"all"` (`[old, new, "all"]`) replaces EVERY occurrence (round 80: r80_sonnet_vol4 measured two-site
    volatile rows with only the first site edited before noticing)."""
    out = base
    for i, pair in enumerate(reps):
        old, new = pair[0], pair[1]
        every = len(pair) > 2 and pair[2] == "all"
        out = rep(out, old, new, label="%s[%d]" % (label, i) if label else "sub[%d]" % i, count=0 if every else 1)
    return out


# ----------------------------------------------------------------------------- admission gate (9)

BANNED = (
    (re.compile(r"\bvolatile\b"), "volatile"),
    (re.compile(r"__asm__|\basm\s*\("), "__asm__"),
    (re.compile(r"\bODDITY_[A-Z_]+\s*\("), "ODDITY_* (orchestrator-only, ledger/oddities.jsonl)"),
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


def goto_count(text):
    """`goto` statements outside comments: plain `goto label;` AND computed `goto *table[i];` (round 80: an
    honest `switch` in place of a computed-goto dispatch is a readability win the gate must see)."""
    t = re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", text, flags=re.S))
    # each `&&label` in a label array is a jump site too: a switch that replaces the array may add a plain goto
    return len(re.findall(r"\bgoto\s+\w+\s*;", t)) + len(re.findall(r"\bgoto\s*\*", t)) + len(re.findall(r"[{,=]\s*&&\s*[A-Za-z_]\w*", t))


M2C_RX = re.compile(r"\bM2C_[A-Z_]+\b|\b(?:temp|var|phi)_[a-z][a-z0-9_]*\b|\barg[0-9]\b|\bsp[0-9A-F]{2,3}\b|\bNON_MATCHING\b")


def m2c_count(t):
    """Decompiler leftovers in a row's text, comments excluded (round 91 cleanup lanes)."""
    return len(M2C_RX.findall(re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))))


# round 93 (owner: fake dependencies are refused): arithmetic that cancels itself only to add a use/order -
# `+ v - v`, `- v + v`, `v ^ v`, `& m & m`.  Removing one is scaffolding removed; adding one is refused.
_FAKEDEP = [re.compile(r"\+\s*(\w+)\s*-\s*\1\b(?!\s*[\[(.]|\s*->)"), re.compile(r"-\s*(\w+)\s*\+\s*\1\b(?!\s*[\[(.]|\s*->)"),
            re.compile(r"\b(\w+)\s*\^\s*\1\b"), re.compile(r"&\s*(\w+)\s*&\s*\1\b"),
            # round 96 (r96_opus_fd kit gap): self-assignment `x = x;` and the split pair `d += h; d -= h;`
            re.compile(r"(?<![\w.>\]])\b(\w+)\s*=\s*\1\s*;"),
            re.compile(r"(?<![\w.>\]])\b(\w+)\s*\+=\s*(\w+)\s*;\s*\1\s*-=\s*\2\s*;")]


def fakedep_count(text):
    t = re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", text, flags=re.S))
    t = "\n".join(l for l in t.split("\n") if not l.lstrip().startswith("#"))
    return sum(len(rx.findall(t)) for rx in _FAKEDEP)


def admissible(base, cand, equal_pins=False):
    """[] when `cand` may be staged against `base`, else the reasons it may not.

    The checks `publish_local.py`, `finalize.py`, `stage.py`, `prepare_outputs.py`, `finish.py`
    (seven lanes) each re-derived: strictly fewer pin sites (round 80: or equal pins and strictly fewer
    plain gotos), the remaining pins a SUBSET of the base's, no new volatile/`__asm__`, no new one-trip block.

    `equal_pins=True` (`lab.py stage-cell --equal-pins`, round 81) waives ONLY the "fewer pins" requirement: a
    cell move that is exact at its target with the pin count unchanged (a byte-neutral recipe switch, or a
    coherence move that keeps its pins) may stage.  More pins, pins the base did not have, new volatile /
    `__asm__` / `ASM_*` / one-trip blocks and added gotos are refused exactly as without it."""
    bad = []
    b, c = pin_keys(base), pin_keys(cand)
    gb, gc = goto_count(base), goto_count(cand)
    # equal pins also stage when scaffolding fell (land_lanes.sh, round 78: volatile, while (0), __asm__) or
    # plain `goto` statements fell (round 80 readability lanes) - nothing banned may grow either way (below)
    scaffold_fell = any(len(rx.findall(cand)) < len(rx.findall(base)) for rx, _ in BANNED + ONE_TRIP)
    # round 91 (luna cleanup lanes): equal pins also stage when decompiler leftovers fell (M2C_* tokens, temp_/var_/phi_
    # locals, argN parameters, spXX stack names, NON_MATCHING) - the same measure land_lanes.sh lands on
    mb, mc = m2c_count(base), m2c_count(cand)
    scaffold_fell = scaffold_fell or mc < mb
    fb, fc = fakedep_count(base), fakedep_count(cand)
    scaffold_fell = scaffold_fell or fc < fb
    if fc > fb:
        bad.append("adds %d fake dependency(ies) (x + v - v / v ^ v / & m & m)" % (fc - fb))
    if sum(c.values()) == sum(b.values()) and mc > mb:
        bad.append("adds %d decompiler leftover(s) (M2C_/temp_/var_/phi_/argN/spXX/NON_MATCHING)" % (mc - mb))
    if sum(c.values()) > sum(b.values()) or (sum(c.values()) == sum(b.values()) and gc >= gb and not scaffold_fell
                                             and not equal_pins):
        bad.append("pin sites not reduced (%d -> %d), no scaffolding removed, gotos not reduced (%d -> %d)"
                   % (sum(b.values()), sum(c.values()), gb, gc))
    if sum(c.values()) == sum(b.values()) and gc > gb:
        bad.append("adds %d goto(s) with pins unchanged" % (gc - gb))
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


def dumps(row, text, want=None, timeout=None, asm_names=False):
    """{'asm': ..., '<pass>': dump text} for `text` compiled as `row` with `-da`.

    `asm_names=True` compiles with `-dap` instead: gcc annotates the first assembler line of every
    insn with `# <uid> <pattern name>` (`final.c` flag_print_asm_name) - the uid -> assembly map
    `why.py --trace --retail` and `checks.py` read.  The dumps themselves are unchanged.

    One compile gives every pass, so `why.py` never needs a second one for a second pass.  The
    compile runs inside a TemporaryDirectory, which `bootstrap()` has already placed inside the
    lane; the directory and its dumps are removed on the way out.  Returns None if it does not
    build (with the compiler's message under 'error')."""
    add_paths()
    from common import parse_cfg, NICE                                   # noqa: E402
    to = float(timeout or os.environ.get("PIN_CC_TIMEOUT", "60"))
    with tempfile.TemporaryDirectory(prefix="lanekit_") as td:
        d = Path(td)
        candidate = d / "f.c"
        candidate.write_text(text)
        sources = [(candidate, row["cfg"])]
        context_fp = module_fingerprint(row)
        if context_fp is not None:
            # a module row compiles its module (siblings included); a PARTITIONED row compiles each physical unit
            # that holds its functions at that unit's recipe - the plural context verify.py builds (r81_opus_kitgap)
            from variant_screen import screen_sources                    # noqa: E402
            sources = screen_sources(row, candidate, d)
        def stale_context():
            return context_fp is not None and module_fingerprint(row) != context_fp
        env = dict(os.environ, TMPDIR=str(d), PYTHONDONTWRITEBYTECODE="1")
        out = {"error": None}
        for i, (source, cfg) in enumerate(sources):
            cell, flags = parse_cfg(cfg)
            D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
            w = d if len(sources) == 1 else d / ("unit%d" % i)
            w.mkdir(exist_ok=True)
            try:
                r = subprocess.run(NICE + [str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags,
                                           "-I" + str(ROOT / "include"), "-w", source.name, "-o", str(w / "f.i")],
                                   cwd=source.parent, capture_output=True, text=True, env=env, timeout=to)
                if stale_context():
                    return {"error": "module context changed during diagnostic compile; re-run"}
                if r.returncode:
                    return {"error": (r.stderr or r.stdout)[-800:]}
                r = subprocess.run(NICE + [str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-dap" if asm_names else "-da",
                                           "-o", "f.s"], cwd=w, capture_output=True, text=True,
                                   env=env, timeout=to)
                if stale_context():
                    return {"error": "module context changed during diagnostic compile; re-run"}
                if r.returncode:
                    return {"error": (r.stderr or r.stdout)[-800:]}
            except subprocess.TimeoutExpired:
                return {"error": "compiler-timeout"}
            # several units (a partition parent's remainder + its parts): each pass's dumps concatenated in unit
            # order, like one file with more functions in it
            out["asm"] = out.get("asm", "") + (w / "f.s").read_text(errors="replace")
            for p in sorted(w.iterdir()):
                suf = p.suffix[1:]
                if suf in PASS_SUFFIX and (want is None or suf in want):
                    out[suf] = out.get(suf, "") + p.read_text(errors="replace")
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
        from variant_screen import partitioned                           # noqa: E402
        if partitioned(row):
            raise SystemExit("lanekit: %s is a partitioned slus row - per-row recipe trials (--cfg) are not supported; "
                             "score it at its registered cfg" % row["id"])
        require_individual_recipe(row)
    from common import parse_cfg                                         # noqa: E402
    cell, flags = parse_cfg(cfg)
    return dict(row, cfg=cfg, cell=cell, flags=" ".join(flags))


def score_at(row, text, cfg=None, verify=None, diff=False, no_jtbl=False):
    """Byte-score `text` as `row` at `cfg` (default the registered cfg) - `tools/verify.verify`
    on a temporary copy named like the row's file, include root `<repo>/include`.

    `diff=True` returns the score fields AND the scorer's listing: `exact`/`total`/`subs`/`indels`/`status`
    (and the rest of the summary record) from the summary score, `text` from the scorer's `--diff`
    (`diff_status` keeps the diff call's own status).  `tools/verify.py --diff` alone carries no score fields
    (they were all None - round 81, r81_fable_late), and the `TOTAL` its text prints is the GLOBAL-LCS
    distance, not the regional total the summary (and every roster) reports, so the two runs are merged
    rather than the text parsed.  They run concurrently: the wall time is the slower of the two.

    JUMP TABLES (round 82).  A text whose switch table differs from retail is rejected by the scorer with a
    `jtbl:` error and no listing; that used to surface as `failed` / `build-fail/no-hex`.  It is now the status
    `jtbl-mismatch` with `jtbl` = [{addr, word, got, retail}] (`nojtbl.jtbl_status`); the raw `err` is kept.

    `no_jtbl=True` scores with the table-content check OFF (`nojtbl.verify_nojtbl`): INFORMATIONAL - `exact` is
    forced False, `text_exact` says whether the code matched, `jtbl_checked` is False.  Overlay rows only."""
    verify_is_real = verify is None
    if verify is None:
        add_paths()
        from verify import verify                                        # noqa: E402
    import nojtbl                                                        # noqa: E402
    call = verify
    if no_jtbl:
        def call(r, f, **kw):
            return nojtbl.verify_nojtbl(r, f, include_root=kw.get("include_root"), diff=kw.get("diff", False),
                                        verify_fn=None if verify_is_real else verify)
    r = row_at_cfg(row, cfg)
    with tempfile.TemporaryDirectory(prefix="lanekit_score_") as td:
        f = Path(td) / Path(r["c_path"]).name
        f.write_text(text)
        inc = (ROOT / "include").resolve()
        if not diff:
            return nojtbl.jtbl_status(call(r, f, include_root=inc))
        from concurrent.futures import ThreadPoolExecutor
        with ThreadPoolExecutor(max_workers=2) as ex:
            fs = ex.submit(call, r, f, include_root=inc)
            fd = ex.submit(call, r, f, include_root=inc, diff=True)
            summ, dtext = fs.result() or {}, fd.result() or {}
        out = dict(summ)
        out["text"] = dtext.get("text")
        out["diff_status"] = dtext.get("status")
        return nojtbl.jtbl_status(out)


def score_fields(v):
    """The five summary fields, plus `jtbl` (status `jtbl-mismatch`: the parsed words) and, for a `no_jtbl` score,
    `text_exact` / `jtbl_checked` (informational: `exact` is False there by construction)."""
    out = {k: (v or {}).get(k) for k in ("exact", "total", "subs", "indels", "status")}
    for k in ("jtbl", "text_exact", "jtbl_checked"):
        if (v or {}).get(k) is not None:
            out[k] = v[k]
    return out


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


# journal kinds the per-row cap does not count: the calibration, and diff.py's one-file measurements (the cap
# guards against lab.py variant explosions - r66_sol_big6 - not against a lane looking at a file it already has)
UNCAPPED_KINDS = ("baseline", "diff-listing", "diff-scorer", "diff-score")


def variant_count(records, row_id):
    """Distinct variant names measured for one row - what the per-row cap counts."""
    return len({r.get("variant") for r in records
                if r.get("row") == row_id and r.get("variant") and r.get("kind") not in UNCAPPED_KINDS})


def record_score(lane, row, variant, v, source, cfg=None, distance=None, pins=None, note="", kind="score", text=None):
    """Journal ONE byte score (a `score_at` result `v`) to the lane's `lab_log.jsonl` so `lab.py report` shows it.

    `lab.py report` builds the REPORT table from the journal only; before round 81 a row measured through
    `diff.py --scorer` or a lane script calling `score_at` directly printed as ZERO MEASUREMENTS (r81_fable_late).
    `source` names the tool (`"diff.py --scorer"`, `"my_probe.py"`), `cfg` a trial cfg (None = registered: the
    report marks a foreign-cfg exact as a trade, not a solve), `pins` the text's pin count (or pass `text`).
    Returns the record written."""
    sc = score_fields(v)
    if pins is None and text is not None:
        pins = len(sites(text))
    # a scorer failure (does not build, TIMEOUT, HARNESS-ERROR) keeps its own status, not "scored / total None"
    status = "exact" if sc.get("exact") else sc["status"] if sc.get("status") not in (None, "ok") \
        else "scored" if sc.get("exact") is not None or sc.get("total") is not None else "no-score"
    if sc.get("jtbl_checked") is False:           # a --no-jtbl score: informational, never an exact/solve
        status = "text-exact-nojtbl" if sc.get("text_exact") else status if status not in ("exact",) else "scored"
        note = (note + " " if note else "") + "[jump-table content check OFF]"
    rec = {"row": row["id"] if isinstance(row, dict) else row, "variant": variant, "kind": kind, "source": source,
           "distance": distance, "score": sc, "status": status, "note": note}
    if pins is not None:
        rec["pins"] = pins
    if cfg:
        rec["cfg"] = cfg
    log_append(lane, rec)
    return rec


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
