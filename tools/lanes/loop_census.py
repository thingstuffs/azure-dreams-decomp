#!/usr/bin/env python3
"""Census of gcc `loop.c` DECISIONS that a row's pins hold in place (round 64).

    python3 tools/lanes/loop_census.py                       # whole tree -> ledger/loop_census.jsonl
    python3 tools/lanes/loop_census.py --only dungeon/func_809A38E4
    python3 tools/lanes/loop_census.py --limit 50 --workers 4

WHY.  `work/native_lane/r64_astra_loop/REPORT.md` took dungeon/func_809A38E4 from 37 pins to 2 by
showing that its 34 `ASM_USE_NV(angle)` sites were ONE fact: loop.c counts every RTL insn in the
loop into `insn_count` (`count_loop_regs_set`, 2.7.2 loop.c:2989) and hoists an invariant only when
`threshold * savings * lifetime >= insn_count` (:1631).  The pins padded the count over the
boundary, so the `0xFB` byte constant stayed inside the loop, as retail has it.  Erase the pins and
the constant moves out - that is the whole 10-line residue.  `work/native_lane/r64_loop_study/NOTE.md`
measured the boundary and warns that a count change WITHOUT a pass-decision change is not evidence.

WHAT THIS DOES.  For every pinned row whose text mentions a loop keyword, compile the pinned text
and the all-pins-erased text with `-dL` and compare the two `.loop` dumps' DECISIONS, not their
insn counts: each movable's `moved to` / `not desirable` / `not safe`, the strength-reduction
(`giv ... not worth while`) and biv/unrolling diagnostics.  A row is FLAGGED when a decision
differs.  It then finds which pins flip that decision (all statement pins, all register pins, each
`MACRO(arg)` group largest first, then one single site of the biggest flipping group) and reports
both the biggest flipping group - the pins this one decision holds - and the cheapest one.  Finally
it diffs the cc1 listing of `pinned` against `pinned minus the cheapest flipping erasure`, so the
flag can be checked against the residue the pin actually holds: a small distance means the decision
IS the pin, a large one means the pin holds allocation or scheduling as well.

Output: `ledger/loop_census.jsonl`, one small JSON line per FLAGGED row (overwritten each run), plus
a printed table.  Every compile runs in its own temporary directory with TMPDIR inside it, and the
directory (and its RTL dump) is removed immediately: nothing is left behind and nothing large is
written into `work/`.

NOT a generator and not a landing tool: it reads `src/`, writes one small ledger file, and never
scores bytes.
"""
from __future__ import annotations

import argparse, collections, glob, json, os, re, subprocess, sys, tempfile, threading, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))

from common import LEDGER, NICE, rows, clean_path, parse_cfg, write_jsonl   # noqa: E402
from pin_census import sites_of                                             # noqa: E402
from pin_sites import erase_many                                            # noqa: E402
import screen                                                               # noqa: E402
from t29_addrsym import mask_comments                                       # noqa: E402

OUT = LEDGER / "loop_census.jsonl"
CONTAINERS = ("town", "dungeon", "main", "slus")
LOOP_KW = re.compile(r"\b(?:for|while|do)\b")
MAX_REFINE = 12                 # extra compiles per flagged row


# --------------------------------------------------------------------------- dump parsing (pure)

FUNC_RE = re.compile(r"^;; Function (\S+)", re.M)
HDR_REAL = re.compile(r"^Loop from (\d+) to (\d+): (\d+) real insns\.")
HDR_PHONY = re.compile(r"^Loop from (\d+) to (\d+) is phony\.")
HDR_IGNORED = re.compile(r"^Loop at (\d+) ignored due to (.*)\.")
# loop.c:1557 onward.  Flags print in this order; `savings` and `halved ...` only for a safe movable.
MOVABLE_RE = re.compile(
    r"^Insn (?P<uid>\d+): regno (?P<regno>\d+) \(life (?P<life>\d+)\), "
    r"(?:consec (?P<consec>\d+), )?(?P<cond>cond )?(?P<force>force )?(?P<global>global )?"
    r"(?P<done>done )?(?P<move_insn>move-insn )?(?:matches (?P<matches>\d+) )?"
    r"(?:forces (?P<forces>\d+) )?(?:savings (?P<savings>\d+) )?(?P<halved>halved since already moved )?"
    r"\s*(?P<status>moved to \d+|not desirable|not safe|not induction variable)\s*$")
MOVED_TO_RE = re.compile(r"moved to (\d+)")
INSN_RE_T = r"^\(insn(?:/[a-z]+)* %d "
REG_RE = re.compile(r"\(reg(?:/[a-z]+)*:(\w+) (\d+)\)")      # pseudo: no hard-register name token
CONST_PROTECT = re.compile(r"const = (-?\d+)")


# A `.loop` dump line is either a PASS DECISION (strength reduction taken or refused, a biv
# eliminated or not, the unrolling verdict) or an ANALYSIS NOTE about a candidate.  Only a decision
# change is evidence that a pin holds a loop.c decision: `possible biv, reg N, const = K` moves
# whenever a constant moves.  Order matters - first match wins.
DIAG_BUCKETS = [
    ("unroll", re.compile(r"^(?:Loop unrolling:|Preconditioning:|Can reverse loop|Reversed loop)")),
    ("giv_dec", re.compile(r"giv of insn .*(?:not worth while|would need a multiply)"
                           r"|giv at \d+ (?:reduced to|combined with)")),
    ("biv_dec", re.compile(r"Cannot eliminate biv|biv \d+ .*eliminated|: biv eliminated")),
    ("giv_info", re.compile(r"giv")),
    ("biv_info", re.compile(r"biv")),
]
DIAG_TAGS = [t for t, _ in DIAG_BUCKETS]
DIAG_KIND = {"unroll": "unroll_changed", "giv_dec": "giv_decision_changed",
             "biv_dec": "biv_elim_changed", "giv_info": "giv_info_changed",
             "biv_info": "biv_info_changed"}
DECISION_DIAGS = ("unroll", "giv_dec", "biv_dec")


def split_functions(dump: str):
    """[(function name, diagnostics text, RTL text)] for one `-dL` dump.

    The loop pass prints its diagnostics for a function before that function's RTL; the RTL starts
    at the first line beginning with `(`."""
    out = []
    marks = list(FUNC_RE.finditer(dump))
    if not marks:
        marks = [None]
    for i, m in enumerate(marks):
        name = m.group(1) if m else "?"
        start = m.end() if m else 0
        end = marks[i + 1].start() if (i + 1 < len(marks) and marks[i + 1]) else len(dump)
        body = dump[start:end]
        lines = body.splitlines()
        cut = len(lines)
        for j, ln in enumerate(lines):
            if ln.startswith("("):
                cut = j
                break
        out.append((name, "\n".join(lines[:cut]), "\n".join(lines[cut:])))
    return out


def _norm_diag(line: str) -> str:
    """A diagnostic line with its unstable numbers (UIDs, regnos) removed but `const = N` kept."""
    line = CONST_PROTECT.sub(lambda m: "const = C%s" % m.group(1).replace("-", "m"), line)
    line = re.sub(r"\b\d+\b", "#", line)
    return re.sub(r"\bC(m?)(\d+)\b", lambda m: ("-" if m.group(1) else "") + m.group(2), line).strip()


def _movable(line: str):
    m = MOVABLE_RE.match(line.rstrip())
    if not m:
        return None
    g = m.groupdict()
    status = g["status"]
    mv = MOVED_TO_RE.match(status)
    flags = [k for k in ("cond", "force", "global", "done", "move_insn", "halved") if g[k]]
    return {
        "uid": int(g["uid"]), "regno": int(g["regno"]), "life": int(g["life"]),
        "consec": int(g["consec"]) if g["consec"] else 0,
        "savings": int(g["savings"]) if g["savings"] else None,
        "matches": int(g["matches"]) if g["matches"] else None,
        "forces": int(g["forces"]) if g["forces"] else None,
        "flags": flags,
        "status": "moved" if mv else status,
        "moved_to": int(mv.group(1)) if mv else None,
        "line": line.strip(),
    }


def parse_loops(diag: str):
    """Ordered loop records for one function's diagnostics text.

    kind is 'real' (with `insns`), 'phony' or 'ignored'.  Movable and other-diagnostic lines belong
    to the loop header above them."""
    loops, cur = [], None
    for line in diag.splitlines():
        s = line.rstrip()
        m = HDR_REAL.match(s)
        if m:
            cur = {"kind": "real", "start": int(m.group(1)), "end": int(m.group(2)),
                   "insns": int(m.group(3)), "movables": [], **{k: [] for k in DIAG_TAGS}}
            loops.append(cur)
            continue
        m = HDR_PHONY.match(s)
        if m:
            cur = {"kind": "phony", "start": int(m.group(1)), "end": int(m.group(2)), "insns": None,
                   "movables": [], **{k: [] for k in DIAG_TAGS}}
            loops.append(cur)
            continue
        m = HDR_IGNORED.match(s)
        if m:
            cur = {"kind": "ignored", "start": int(m.group(1)), "end": None, "insns": None,
                   "why": m.group(2), "movables": [], **{k: [] for k in DIAG_TAGS}}
            loops.append(cur)
            continue
        if cur is None or not s.strip():
            continue
        mv = _movable(s)
        if mv:
            cur["movables"].append(mv)
            continue
        low = s.strip()
        for tag, rx in DIAG_BUCKETS:
            if rx.search(low):
                cur[tag].append(_norm_diag(low))
                break
    return loops


def rtl_expr(rtl: str, uid: int):
    """(normalised SET_SRC, dest mode) of the insn with this UID, or (None, None).

    Pseudo registers are anonymised (their numbers move when pins are erased); a hard register keeps
    its name token, which the dump prints."""
    m = re.search(INSN_RE_T % uid, rtl, re.M)
    if not m:
        return None, None
    # read balanced parens from the start of the pattern (after `(insn UID PREV NEXT `)
    rest = rtl[m.end():]
    m2 = re.match(r"\d+ \d+ ", rest)
    if not m2:
        return None, None
    rest = rest[m2.end():]
    if not rest.startswith("("):
        return None, None
    depth, i = 0, 0
    for i, ch in enumerate(rest):
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                break
    pat = rest[:i + 1]
    m3 = re.match(r"\(set \(reg(?:/[a-z]+)*:(\w+) \d+\)\s*(.*)\)\s*$", pat, re.S)
    if not m3:
        return _squash(pat), None
    return _squash(m3.group(2)), m3.group(1)


def _squash(expr: str) -> str:
    expr = REG_RE.sub(lambda m: "(reg:%s ?)" % m.group(1), expr)
    return re.sub(r"\s+", " ", expr).strip()


# ------------------------------------------------------------------------------- dump comparison

PRIMARY = ("hoist_gained", "hoist_lost", "decision_changed", "forced_follow")
SECONDARY = ("giv_decision_changed", "biv_elim_changed", "unroll_changed")
# `movable_set_changed` and the *_info_changed kinds are structure/analysis, not decisions: erasing a
# pin routinely adds or removes an invariant CANDIDATE or moves a constant.  Recorded, never flagging.
FLAGGING = PRIMARY + SECONDARY


def _align(a, b):
    """(pairs, unmatched, realigned).

    Positional while the two lists are the same length AND no positional pair holds two different
    defining expressions - erasure can drop one movable and add another, and a blind positional
    pair would then read as a decision change.  Otherwise pair by expression signature."""
    if len(a) == len(b):
        pairs = list(zip(a, b))
        if not any(x.get("expr") and y.get("expr") and x["expr"] != y["expr"] for x, y in pairs):
            return pairs, 0, False
    ia = collections.defaultdict(list)
    for x in b:
        ia[x.get("expr")].append(x)
    pairs, un = [], 0
    for x in a:
        cand = ia.get(x.get("expr"))
        if x.get("expr") is not None and cand:
            pairs.append((x, cand.pop(0)))
        else:
            un += 1
    un += sum(len(v) for v in ia.values())
    return pairs, un, len(a) == len(b)


def compare(pin_funcs, era_funcs):
    """(transitions, refusal).  Loops are aligned by function name then by real-loop ordinal."""
    pf = {n: (d, r) for n, d, r in pin_funcs}
    ef = {n: (d, r) for n, d, r in era_funcs}
    if set(pf) != set(ef):
        return [], "function_set_changed"
    trans = []
    for name in pf:
        pl = [l for l in parse_loops(pf[name][0]) if l["kind"] == "real"]
        el = [l for l in parse_loops(ef[name][0]) if l["kind"] == "real"]
        if len(pl) != len(el):
            return [], "loop_count_differs:%s:%d_vs_%d" % (name, len(pl), len(el))
        for li, (p, e) in enumerate(zip(pl, el)):
            for mv, rtl in ((p, pf[name][1]), (e, ef[name][1])):
                for x in mv["movables"]:
                    uid = x["moved_to"] if x["status"] == "moved" else x["uid"]
                    x["expr"], x["mode"] = rtl_expr(rtl, uid)
            pairs, unmatched, realigned = _align(p["movables"], e["movables"])
            if realigned:
                trans.append({"fn": name, "loop": li, "kind": "positional_realigned",
                              "pinned": "", "erased": "", "insns": [p["insns"], e["insns"]],
                              "expr": None, "mode": None, "life": None, "savings": None,
                              "key": (name, li, -9)})
            moved_to_uids = {x["uid"] for x in p["movables"]}
            by_uid_new = {a["uid"]: b for a, b in pairs}
            for a, b in pairs:
                if a["status"] == b["status"]:
                    continue
                kind = ("hoist_gained" if b["status"] == "moved" and a["status"] != "moved" else
                        "hoist_lost" if a["status"] == "moved" and b["status"] != "moved" else
                        "decision_changed")
                # a movable that only follows the partner it `forces` is not an independent decision
                partner = by_uid_new.get(a["forces"]) if a["forces"] else None
                pa = next((x for x in p["movables"] if x["uid"] == a["forces"]), None) if a["forces"] else None
                if kind == "hoist_gained" and partner is not None and pa is not None \
                        and pa["status"] != "moved" and partner["status"] == "moved":
                    kind = "forced_follow"
                trans.append({
                    "fn": name, "loop": li, "kind": kind,
                    "pinned": a["status"], "erased": b["status"],
                    "life": a["life"], "savings": a["savings"],
                    "expr": a.get("expr") or b.get("expr"), "mode": a.get("mode") or b.get("mode"),
                    "insns": [p["insns"], e["insns"]],
                    "key": (name, li, p["movables"].index(a)),
                })
            if unmatched:
                trans.append({"fn": name, "loop": li, "kind": "movable_set_changed",
                              "pinned": "%d movables" % len(p["movables"]),
                              "erased": "%d movables" % len(e["movables"]),
                              "insns": [p["insns"], e["insns"]], "expr": None, "mode": None,
                              "life": None, "savings": None, "key": (name, li, -1)})
            for tag in DIAG_TAGS:
                if collections.Counter(p[tag]) != collections.Counter(e[tag]):
                    kind = DIAG_KIND[tag]
                    diff = sorted(set(p[tag]) ^ set(e[tag]))[:3]
                    trans.append({"fn": name, "loop": li, "kind": kind,
                                  "pinned": " | ".join(x for x in diff if x in p[tag])[:200],
                                  "erased": " | ".join(x for x in diff if x in e[tag])[:200],
                                  "insns": [p["insns"], e["insns"]], "expr": None, "mode": None,
                                  "life": None, "savings": None, "key": (name, li, -2 - DIAG_TAGS.index(tag))})
            _ = moved_to_uids
    return trans, None


def loop_counts(funcs):
    return [l["insns"] for _, d, _ in funcs for l in parse_loops(d) if l["kind"] == "real"]


# --------------------------------------------------------------------------------------- compile

TIMEOUT = float(os.environ.get("PIN_CC_TIMEOUT", "30"))


def dump_loop(row, text):
    """The `-dL` dump text for `text` compiled as `row` (None if it does not build).

    Own temporary directory, TMPDIR inside it, removed with its RTL on the way out."""
    cell, flags = parse_cfg(row["cfg"])
    D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="loopcensus_") as td:
        d = Path(td)
        (d / "f.c").write_text(text)
        env = dict(os.environ, TMPDIR=str(d), PYTHONDONTWRITEBYTECODE="1")
        try:
            r = subprocess.run(NICE + [str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags,
                                       "-I" + str(ROOT / "include"), "-w", "f.c", "-o", "f.i"],
                               cwd=d, capture_output=True, text=True, env=env, timeout=TIMEOUT)
            if r.returncode:
                return None
            r = subprocess.run(NICE + [str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-dL",
                                       "-o", "f.s"],
                               cwd=d, capture_output=True, text=True, env=env, timeout=TIMEOUT)
            if r.returncode:
                return None
        except subprocess.TimeoutExpired:
            return None
        g = sorted(glob.glob(str(d / "*.loop")))       # dump naming differs across cells
        if not g:
            return None
        return Path(g[0]).read_text(errors="replace")


# ------------------------------------------------------------------------------------- pin groups

USE_RE = re.compile(r"^ASM_USE")


def pin_groups(sites):
    """[(label, [site, ...])] - one entry per distinct MACRO(arg), largest first.

    A statement pin's arg is the variable it names, so `ASM_USE_NV(angle)` IS the run of sites on
    one variable.  A register pin's arg is the hard register, and two unrelated locals can share
    one, so it is keyed by its declaration as well: erasing every `$17` binding in a merged TU is
    not a same-variable run."""
    g = collections.OrderedDict()
    for s in sites:
        key = ("%s(%s)" % (s[1], s[2])) if s[0] != "reg" else \
              ("%s($%s %s)" % (s[1], s[2], (s[6] or "").split()[-1] if s[6] else "?"))
        g.setdefault(key, []).append(s)
    return sorted(g.items(), key=lambda kv: -len(kv[1]))


def use_runs(sites):
    """Maximal runs of consecutive ASM_USE* sites naming one argument: [(macro, arg, n)]."""
    out, run = [], []
    for s in sites:
        if run and USE_RE.match(s[1]) and USE_RE.match(run[-1][1]) and s[2] == run[-1][2]:
            run.append(s)
            continue
        if len(run) >= 2:
            out.append(run)
        run = [s] if USE_RE.match(s[1]) else []
    if len(run) >= 2:
        out.append(run)
    return [(r[0][1], r[0][2], len(r)) for r in out]


# ------------------------------------------------------------------------------------ one row

def keys_of(trans, kinds=PRIMARY):
    """The identity of each transition of these kinds: what a candidate erasure must reproduce."""
    return {(t["kind"], tuple(t["key"])) for t in trans if t["kind"] in kinds}


def census_row(row, text, sites, refine=True):
    rec = {"id": row["id"], "cfg": row["cfg"], "pins": len(sites)}
    runs = [r for r in use_runs(sites) if r[2] >= 4]
    if runs:
        rec["use_runs"] = [{"macro": m, "arg": a, "n": n} for m, a, n in runs]
    pinned_dump = dump_loop(row, text)
    if pinned_dump is None:
        return dict(rec, status="refused", why="pinned_nobuild")
    erased = erase_many(text, sites, clean_notes=True)
    erased_dump = dump_loop(row, erased)
    if erased_dump is None:
        return dict(rec, status="refused", why="erased_nobuild")
    pf, ef = split_functions(pinned_dump), split_functions(erased_dump)
    rec["loop_insns"] = {"pinned": loop_counts(pf), "erased": loop_counts(ef)}
    trans, refusal = compare(pf, ef)
    if refusal:
        return dict(rec, status="refused", why=refusal)
    if not rec["loop_insns"]["pinned"]:
        return dict(rec, status="noloop")
    rec["kinds"] = sorted({t["kind"] for t in trans if t["kind"] in FLAGGING})
    rec["also"] = sorted({t["kind"] for t in trans if t["kind"] not in FLAGGING})
    if not rec["kinds"]:
        # a structural or analysis-only difference: the pins changed WHICH invariants exist, or a
        # constant moved, but no loop.c decision came out differently (r64 NOTE section 3)
        return dict(rec, status="unflagged")
    rec["status"] = "flagged"
    show = [t for t in trans if t["kind"] in FLAGGING] + [t for t in trans if t["kind"] not in FLAGGING]
    rec["transitions"] = [{k: v for k, v in t.items() if k != "key"} for t in show[:6]]
    prim = [t for t in trans if t["kind"] in PRIMARY]
    rec["flag_class"] = "movable" if prim else "secondary"
    if prim:
        p, e = prim[0]["insns"]
        if p is not None and e is not None:
            rec["count_gap"] = p - e
            if prim[0]["savings"] and prim[0]["life"]:
                rec["savings_x_life"] = prim[0]["savings"] * prim[0]["life"]
    kinds = PRIMARY if prim else SECONDARY
    want = keys_of(trans, kinds)
    if refine and sites:
        exprs = [t["expr"] for t in trans if t["kind"] in PRIMARY and t.get("expr")]
        rec["deciding"] = refine_row(row, text, sites, want, kinds, exprs)
    return rec


def refine_row(row, text, sites, want, kinds, want_exprs=()):
    """Which pin group flips the decision: <=MAX_REFINE extra compiles from the PINNED text."""
    pinned_dump = dump_loop(row, text)
    pf = split_functions(pinned_dump)
    budget = [MAX_REFINE]
    tried = []

    def flips(chosen):
        if budget[0] <= 0:
            return None
        budget[0] -= 1
        cand = erase_many(text, chosen, clean_notes=True)
        d = dump_loop(row, cand)
        if d is None:
            return None
        t, refusal = compare(pf, split_functions(d))
        if refusal:
            return None
        return bool(keys_of(t, kinds) & want)

    stmt = [s for s in sites if s[0] == "stmt"]
    reg = [s for s in sites if s[0] == "reg"]
    out = {"tried": tried}
    if stmt and reg:
        for label, chosen in (("all stmt pins", stmt), ("all reg pins", reg)):
            tried.append({"what": label, "n": len(chosen), "flips": flips(chosen)})
    groups = pin_groups(sites)                      # largest MACRO(arg) group first
    out["groups_tested"] = min(len(groups), max(budget[0], 0))
    hits = []
    for label, chosen in groups:
        if budget[0] <= 0:
            break
        r = flips(chosen)
        tried.append({"what": label, "n": len(chosen), "flips": r})
        if r:
            hits.append((label, chosen))
    if not hits:
        out["group"] = None
        out["note"] = ("no MACRO(arg) group flips the decision on its own"
                       if out["groups_tested"] >= len(groups) else "compile budget spent")
        return out
    big = max(hits, key=lambda kv: len(kv[1]))       # the pins this one decision holds
    small = min(hits, key=lambda kv: len(kv[1]))     # the cheapest group that flips it
    single = True if len(big[1]) == 1 else bool(flips(big[1][:1]))
    out["group"] = {"label": big[0], "n": len(big[1]), "single_flips": single}
    out["min_group"] = {"label": small[0], "n": len(small[1])}
    # does the flag explain the row's residue?  pinned vs pinned minus the CHEAPEST flipping
    # erasure: erasing a whole group overshoots the boundary and mixes in every other pin's residue.
    chosen = big[1][:1] if single else (small[1] if len(small[1]) < len(big[1]) else big[1])
    out["residue_on"] = {"label": big[0] if single else small[0], "n": len(chosen)}
    s0 = screen.compile_s(row, text)
    s1 = screen.compile_s(row, erase_many(text, chosen, clean_notes=True))
    out["sdiff"] = screen.sdiff(s0, s1)
    if s0 is not None and s1 is not None:
        import difflib
        lines = [x for x in difflib.unified_diff(s0, s1, lineterm="", n=0)
                 if x[:1] in "+-" and not x.startswith(("+++", "---"))]
        out["residue"] = lines[:6]
        consts = [int(m.group(1)) for t in want_exprs
                  for m in [re.fullmatch(r"\(const_int (-?\d+)\)", t or "")] if m]
        if consts:
            out["residue_has_const"] = any(
                re.search(r"\b(?:li|lui|addiu|ori)\b[^,]*,\s*-?(?:%d|0x%x)\b" % (c, c & 0xFFFFFFFF), ln)
                for ln in lines for c in consts)
    return out


# ------------------------------------------------------------------------------------------ main

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--only", help="comma-separated row ids")
    ap.add_argument("--containers", default=",".join(CONTAINERS))
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--out", default=str(OUT))
    ap.add_argument("--no-refine", action="store_true")
    ap.add_argument("--all-rows", action="store_true",
                    help="do not skip rows whose text has no for/while/do (catches goto loops)")
    a = ap.parse_args()

    only = set(a.only.split(",")) if a.only else None
    conts = set(a.containers.split(","))
    todo, skipped, all_runs, no_kw = [], collections.Counter(), [], set()
    for r in rows():
        if only and r["id"] not in only:
            continue
        if r["container"] not in conts:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        sites = sites_of(text)
        if not sites:
            continue
        skipped["pinned_rows"] += 1
        runs = [x for x in use_runs(sites) if x[2] >= 4]
        if runs:
            all_runs.append((r["id"], len(sites), runs))
        if not a.all_rows and not LOOP_KW.search(mask_comments(text)):
            skipped["no_loop_keyword"] += 1
            no_kw.add(r["id"])
            continue
        todo.append((r, text, sites))
        if a.limit and len(todo) >= a.limit:
            break

    print("%d pinned rows, %d with a loop keyword (%d skipped)"
          % (skipped["pinned_rows"], len(todo), skipped["no_loop_keyword"]), flush=True)

    recs, lock, t0, done = [], threading.Lock(), time.time(), [0]

    def one(job):
        r, text, sites = job
        try:
            rec = census_row(r, text, sites, refine=not a.no_refine)
        except Exception as exc:                       # a broken dump must not stop the census
            rec = {"id": r["id"], "cfg": r["cfg"], "pins": len(sites), "status": "refused",
                   "why": "exception:%s" % type(exc).__name__, "detail": str(exc)[:200]}
        with lock:
            recs.append(rec)
            done[0] += 1
            if done[0] % 50 == 0:
                print("  %d/%d  %.0fs" % (done[0], len(todo), time.time() - t0), flush=True)
        return rec

    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        list(ex.map(one, todo))

    by = collections.Counter(x.get("status") for x in recs)
    flagged = [x for x in recs if x.get("status") == "flagged"]
    flagged.sort(key=lambda x: -((x.get("deciding") or {}).get("group") or {}).get("n", 0))
    write_jsonl(a.out, flagged)

    print("\nstatus: " + ", ".join("%s %d" % kv for kv in sorted(by.items())))
    why = collections.Counter(x.get("why", "").split(":")[0] for x in recs if x.get("status") == "refused")
    if why:
        print("refusals: " + ", ".join("%s %d" % kv for kv in why.most_common()))
    print("flag class: " + ", ".join("%s %d" % kv for kv in
                                     collections.Counter(x.get("flag_class") for x in flagged).most_common()))
    kinds = collections.Counter(k for x in flagged for k in x["kinds"])
    print("transition kinds: " + ", ".join("%s %d" % kv for kv in kinds.most_common()))
    other = collections.Counter(k for x in recs for k in x.get("also", []))
    if other:
        print("non-flagging differences (structure/analysis only): "
              + ", ".join("%s %d" % kv for kv in other.most_common()))
    print("\n%-34s %5s %5s %-28s %-13s %s" % ("row", "pins", "grp", "kinds", "insns p->e", "deciding group"))
    for x in flagged[:40]:
        d = x.get("deciding") or {}
        g = d.get("group") or {}
        ins = x.get("loop_insns", {})
        pi, ei = ins.get("pinned") or [], ins.get("erased") or []
        print("%-34s %5d %5s %-28s %-13s %s" % (
            x["id"], x["pins"], g.get("n", "-"), ",".join(x["kinds"])[:28],
            "%s->%s" % (max(pi) if pi else "?", max(ei) if ei else "?"),
            (g.get("label", "-") or "-") + (" single" if g.get("single_flips") else "")))
    print("\nwrote %d flagged rows to %s  (%.0fs)" % (len(flagged), a.out, time.time() - t0))

    print("\nruns of 4+ ASM_USE*/one variable (all pinned rows):")
    st = {x["id"]: x.get("status") for x in recs}
    for rid, npins, runs in all_runs:
        s = st.get(rid) or ("skipped: no loop keyword" if rid in no_kw else "not run")
        print("  %-34s pins %3d  %s   census: %s"
              % (rid, npins, ", ".join("%s(%s) x%d" % r for r in runs), s))
    if not all_runs:
        print("  (none)")


if __name__ == "__main__":
    main()
