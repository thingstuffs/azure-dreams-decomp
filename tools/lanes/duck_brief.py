#!/usr/bin/env python3
"""Rubber-duck brief: a row's pins stated plainly, so a model (or a person) starts from the state.

    python3 tools/lanes/duck_brief.py dungeon/func_80A9D4E8 [more rows ...] [--notes FILE.md]
    from duck_brief import duck; md = duck("dungeon/func_80A9D4E8")

The owner's round-62 rule: every pack row carries a brief that says, without prose or salesmanship,
which pins are there and what each one's note claims, what is known about the mechanism behind each,
what has been tried and how close it got, whether the pins must fall together, and what one would
still have to measure.  Three sections per row:

STATE   every live pin site (`pin_census.sites_of`) with its trailing `/* ... */` note, the residue
        class of erasing IT ALONE (`lanes/residue.fingerprint` over the cc1 listings - the same
        function `lanes/erase_census.py --fp` records) and the changed listing lines; then the JOINT
        picture: all pins erased together, and - for 2..6 pins - the pairs, so the brief can say
        which pins fall together (a pair whose joint residue is no larger than either pin alone) and
        which are independent.  Bounded at about fifteen listings a row.
KNOWN   one sentence of mechanism hypothesis per pin, from its kind and residue class, naming the
        generator that covers that mechanism and quoting its newest verdict on this row from
        `ledger/sweeps/*.jsonl` (marked "(on earlier text)" when the verdict was recorded against a
        different sha), the best listing distance any `work/native_lane/r6*_*/journal.jsonl` reached,
        the `tools/alloc_sim.py` order-site verdict for callee-saved ASM_REG pins (t85's APPEARS
        test, imported), and the model lanes that already served the row with the distances their
        REPORT.md quotes.
NEEDED  what must change in the C, in plain words; whether the pins must fall together; and what is
        UNKNOWN.  A pin whose kind and class match no documented mechanism is written "unknown" -
        never a mechanism the evidence does not support.

Everything is measured fresh: the cached census (`erase_r61.jsonl`) carries no input sha and no diff
above `--diff 4`, so it cannot be trusted for a brief that claims to state the current state.
"""
import argparse
import difflib
import glob
import json
import re
import sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
sys.path.insert(0, str(ROOT / "tools/lanes"))
from common import rows as all_rows, clean_path, sha_text, parse_cfg   # noqa: E402
from pin_census import sites_of                                        # noqa: E402
from pin_sites import erase_many                                       # noqa: E402
import residue                                                         # noqa: E402
from screen import sdiff                                               # noqa: E402
import screen                                                        # noqa: E402

MAX_PAIRS = 15               # pair listings per row
PAIR_CAP_LARGE = 8           # when C(n,2) would exceed MAX_PAIRS
DIFF_LINES = 6               # changed listing lines shown per single erasure
JOINT_DIFF_LINES = 10
REPORT_QUOTES = 3            # distance sentences quoted per serving lane
CENSUS_PINS = 10             # more pins than this: the STATE section becomes a grouped census
CENSUS_GROUPS = 10           # groups printed in census mode

CALLEE = {"16", "17", "18", "19", "20", "21", "22", "23", "30",
          "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "fp"}
ARGREG = {"4", "5", "6", "7", "a0", "a1", "a2", "a3"}
VREG = {"2", "3", "v0", "v1"}

NOTE_RE = re.compile(r"/\*(.*?)\*/\s*\\?\s*$")
DIST_RE = re.compile(r"distance|total=|->|listing|scorer|subs=|stayed|worsened|reached|reduced")


# ------------------------------------------------------------------ text-only helpers (unit-tested)

def note_of(text, line_no):
    """The trailing `/* ... */` note on a pin's line, or None.  Lines inside a #define end in `\\`."""
    lines = text.splitlines()
    if not (1 <= line_no <= len(lines)):
        return None
    m = NOTE_RE.search(lines[line_no - 1])
    if not m:
        return None
    return " ".join(m.group(1).split()) or None


def var_of(site):
    """The variable a site pins: a stmt pin its argument, a reg pin the name in its declaration."""
    if site[0] == "reg" and len(site) > 6 and site[6]:
        ids = re.findall(r"[A-Za-z_]\w*", site[6])
        if ids:
            return ids[-1]
    return (site[2] or "").strip()


def pair_plan(sites):
    """[(i, j)] pairs to measure: every pair while that is at most MAX_PAIRS listings, else the
    same-macro and same-variable pairs first, capped at PAIR_CAP_LARGE.  (pairs, n_possible)."""
    n = len(sites)
    allp = [(i, j) for i in range(n) for j in range(i + 1, n)]
    if len(allp) <= MAX_PAIRS:
        return allp, len(allp)
    def rank(p):
        i, j = p
        return (0 if sites[i][1] == sites[j][1] or var_of(sites[i]) == var_of(sites[j]) else 1, i, j)
    return sorted(allp, key=rank)[:PAIR_CAP_LARGE], len(allp)


def fall_together(d_pair, d_a, d_b):
    """A pair falls together when erasing both leaves a residue no larger than either alone."""
    if d_pair is None or d_a is None or d_b is None:
        return None
    return d_pair <= min(d_a, d_b)


def report_section(md_text, rid):
    """The row's own block of a lane REPORT.md: a `### \\`row\\`` heading section or a `- \\`row\\` - ...`
    bullet.  Returns '' when the row is not mentioned."""
    name = rid.split("/")[-1]
    # hand notes name a clone family as `func_80A9D4E8, 80DBBFC8, 810318E4`, so the bare address counts
    needles = [name] + ([name[5:]] if name.startswith("func_") else [])
    lines = md_text.splitlines()
    for i, ln in enumerate(lines):
        if not any(nd in ln for nd in needles):
            continue
        if ln.startswith("#"):
            out = [ln]
            for nxt in lines[i + 1:]:
                if nxt.startswith("#"):
                    break
                out.append(nxt)
            return "\n".join(out).strip()
        if ln.lstrip().startswith(("- ", "* ")):
            out = [ln]
            for nxt in lines[i + 1:]:
                if nxt.startswith("#") or nxt.lstrip().startswith(("- ", "* ")):
                    break
                out.append(nxt)
            return "\n".join(out).strip()
    return ""


def distance_sentences(section, limit=REPORT_QUOTES):
    """The sentences of a REPORT section that carry a measurement (distance / total= / ->), prose
    dropped.  The owner's rule: quote the distances, not the prose."""
    flat = " ".join(section.split())
    flat = re.sub(r"^[-*#\s]*", "", flat)
    out = []
    for s in re.split(r"(?<=[.;])\s+", flat):
        s = s.strip()
        if not s or not DIST_RE.search(s):
            continue
        if re.match(r"^\*\*(Mechanism|Generator rule)", s) or s.startswith(("Mechanism:", "Generator rule:")):
            continue
        out.append(s)
        if len(out) >= limit:
            break
    return out


def newest(records):
    """The newest record of a list by its `at` timestamp (stable for missing keys)."""
    return max(records, key=lambda r: r.get("at") or "") if records else None


# ------------------------------------------------------------------ evidence gathering (filesystem)

_SWEEPS = {}
_LANES = None


def prime_sweeps(ids):
    """One filtered pass over ledger/sweeps/*.jsonl (139 MB) for exactly these rows.
    {row id: {transform: newest record}}; a raw substring test keeps json.loads off most lines."""
    want = {rid: rid.split("/")[-1] for rid in ids if rid not in _SWEEPS}
    if not want:
        return
    for rid in want:
        _SWEEPS[rid] = {}
    needles = set(want.values())
    for f in sorted(glob.glob(str(ROOT / "ledger/sweeps/*.jsonl"))):
        try:
            fh = open(f)
        except OSError:
            continue
        with fh:
            for line in fh:
                if not any(nd in line for nd in needles):
                    continue
                try:
                    rec = json.loads(line)
                except ValueError:
                    continue
                rid = rec.get("id")
                if rid not in _SWEEPS:
                    continue
                t = rec.get("transform") or Path(f).stem
                prev = _SWEEPS[rid].get(t)
                if prev is None or (rec.get("at") or "") >= (prev.get("at") or ""):
                    _SWEEPS[rid][t] = rec


def sweep_verdicts(rid):
    prime_sweeps([rid])
    return _SWEEPS.get(rid, {})


def journal_bests(rid):
    """[(lane, best distance, outcome, refusal, in_sha)] from work/native_lane/r6*_*/journal.jsonl.
    The round-60/61 generators were swept with gen_drive, which journals into the lane, not into
    ledger/sweeps - so a generator's verdict is here or nowhere."""
    out = []
    for f in sorted(glob.glob(str(ROOT / "work/native_lane/r6*_*/journal.jsonl"))):
        lane = Path(f).parent.name
        best, rec = None, None
        try:
            fh = open(f)
        except OSError:
            continue
        with fh:
            for line in fh:
                if rid.split("/")[-1] not in line:
                    continue
                try:
                    r = json.loads(line)
                except ValueError:
                    continue
                if r.get("id") != rid:
                    continue
                rec = r
                for k in ("best_d", "near", "best"):
                    if isinstance(r.get(k), (int, float)):
                        best = r[k] if best is None else min(best, r[k])
        if rec is not None:
            out.append((lane, best, rec.get("outcome"), rec.get("refused"), rec.get("in_sha")))
    return out


def lane_membership():
    """{row id: [lane names]} from the `## row` headings of work/native_lane/r[56]*_*/rows.md - the
    pack-membership record the pack builder itself uses."""
    global _LANES
    if _LANES is None:
        m = {}
        for f in sorted(glob.glob(str(ROOT / "work/native_lane/r[56]*_*/rows.md"))):
            lane = Path(f).parent.name
            try:
                fh = open(f)
            except OSError:
                continue
            with fh:
                for line in fh:
                    if line.startswith("## "):
                        m.setdefault(line[3:].strip(), []).append(lane)
        _LANES = {k: sorted(set(v)) for k, v in m.items()}
    return _LANES


def lane_reports(rid, notes=None):
    """[(source, [distance sentences])] from each serving lane's REPORT.md, plus any --notes file."""
    out = []
    for lane in lane_membership().get(rid, []):
        p = ROOT / "work/native_lane" / lane / "REPORT.md"
        if not p.exists():
            continue
        sec = report_section(p.read_text(errors="replace"), rid)
        if sec:
            out.append((lane + "/REPORT.md", distance_sentences(sec), False))
    for np_ in (notes or []):
        p = Path(np_)
        if not p.exists():
            continue
        sec = report_section(p.read_text(errors="replace"), rid)
        if sec:
            # hand notes are already terse measurement lines: quote them as written, not sentence-filtered
            lines = [" ".join(x.split()) for x in sec.splitlines() if x.strip()][:7]
            out.append((p.name, lines, True))
    return out


# ------------------------------------------------------------------ mechanism table

def hypothesis(site, fp):
    """(one-sentence mechanism hypothesis, [covering generators]) for one pin site.
    'unknown' whenever the kind and residue class match no mechanism the campaign has documented."""
    kind, macro, arg = site[0], site[1], site[2]
    cls = (fp or {}).get("cls", "NOBUILD")
    if cls == "INVISIBLE":
        return ("the cc1 screen cannot see this pin at all: erasing it alone leaves an identical "
                "listing, so its effect is assembler-side (maspsx) or the site is dead - byte-score "
                "the erasure, do not search for a C shape (round 30: 21 of 6,480 sites)", [])
    if cls == "NOBUILD":
        return ("unknown - the text with this pin erased does not compile, so nothing about its "
                "mechanism was measured; make the erased text build before anything else", [])
    # a register pin whose erasure also CHANGES the opcodes is not a pure colouring question: a
    # width, a fold or a rematerialisation sits on top of it, and that is what has to go first.
    widened = (" - and because erasing it CHANGES the opcodes too (%s), a width, a fold or a "
               "rematerialisation sits on top of the colour" % cls) if cls == "CHANGED" else ""
    if kind == "reg" and arg in CALLEE:
        return ("a callee-saved register role: erasing the pin adds an allocno, and gcc 2.x global.c "
                "hands out $s0,$s1,... in rank order (refs/live length), so the register IS the rank - "
                "a missing-allocno ORDER error unless the dumps say otherwise" + widened,
                ["t85_allocorder", "t84_narrowparams"])
    if kind == "reg" and arg in ARGREG:
        return ("an argument-register colour: expand_call builds each argument in place, so the pin "
                "holds a preference (a value's lifetime/refs), not a scheduling order" + widened,
                ["t80_derivecall", "t76_arity", "t74_multiset"])
    if kind == "reg" and arg in VREG:
        return ("a $v0/$v1 colour on a call result or expression value - local-alloc's quantity order, "
                "which moves only when the value's set count or lifetime changes" + widened,
                ["t74_multiset", "t81_reuselocal", "t84_narrowparams"])
    if macro == "ASM_MEM_BARRIER":
        return ("a CSE barrier: gcc 2.x cse caches the field loads across the run and a real store to "
                "the object invalidates the table, so retail's reloads come back",
                ["t83_storeafterproducer"])
    if macro == "ASM_SCHED_BARRIER":
        return ("a scheduling fence: sched.c fills the block in reverse and breaks priority ties by "
                "original stream order, so the C statement order around the call decides",
                ["t71_updateaftercall", "t72_stmtperm", "t82_armsink"])
    if macro == "ASM_CLOBBER":
        return ("a register reserved across a block; one documented form is disjoint-local reuse (an "
                "arm-local value hosted on a dead same-typed local), the rest is unknown",
                ["t81_reuselocal"])
    if macro.startswith("ASM_KEEP") or macro in ("ASM_USE", "ASM_SET"):
        if macro in ("ASM_SET", "ASM_USE") and cls == "CHANGED":
            return ("a value the decompiler invented (an argument register left alive by earlier code): "
                    "the call may have fewer real arguments than the C passes",
                    ["t76_arity", "t8b_passthru_params"])
        if cls == "MOVED":
            return ("pure placement - the same instructions in another order: the sched.c tie rule, so "
                    "some statement is written in the wrong place in the recovered C",
                    ["t71_updateaftercall", "t72_stmtperm", "t80_derivecall", "t82_armsink"])
        if cls == "RECOLOURED":
            return ("pure colouring - the same opcodes in different registers: an allocation question "
                    "(set count, refs, live length), not an order one",
                    ["t74_multiset", "t85_allocorder", "t81_reuselocal"])
        if cls == "BOTH":
            return ("order and colour together: a value's lifetime is wrong, which moves both where the "
                    "instructions land and which registers they get",
                    ["t80_derivecall", "t82_armsink", "t74_multiset"])
        if cls == "CHANGED":
            return ("the instruction stream itself changes - opcodes appear or vanish, so a fold, a "
                    "narrowing, a rematerialisation or an aggregate copy is at stake, not a placement",
                    ["t78_aggcopy", "t84_narrowparams", "t74_multiset"])
    return ("unknown - this kind and residue class match no mechanism the campaign has documented", [])


# ------------------------------------------------------------------ alloc_sim verdict

def alloc_verdict(row, text):
    """t85's APPEARS test, imported: 'order site' / why it is not / why it could not be measured."""
    sites = sites_of(text)
    if not any(s[0] == "reg" and s[2] in CALLEE for s in sites):
        return None
    try:
        import alloc_sim
        import t85_allocorder as t85
    except Exception as e:                                             # noqa: BLE001
        return "alloc_sim unavailable (%r)" % (e,)
    if parse_cfg(row["cfg"])[0] not in alloc_sim.FIRST:
        return "cell %s has no FIRST_PSEUDO_REGISTER in the model" % parse_cfg(row["cfg"])[0]
    try:
        if t85.the_function(text) is None:
            return "not a single function definition - the dumps cannot be mapped to C names"
        rd_p = alloc_sim.read(row, text)
        if rd_p is None:
            return "the pinned text does not build with -dl -dg"
        if rd_p["listing"] != screen.compile_s(row, text):
            return "untrusted dump reading (the dumped listing differs from a plain compile)"
        pins = t85.pinned_vars(text)
        why = "the pin-erased text does not build"
        for label, plan in t85.erase_plans(text):
            rd_e = alloc_sim.read(row, erase_many(text, plan, clean_notes=True))
            if rd_e is None:
                continue
            ok, why = t85.is_order_site(rd_p, rd_e, pins)
            if ok:
                return "ORDER SITE (erasing the %s pins): %s" % (label, "a missing allocno, dispositions a permutation, every contested allocno crosses a call")
        return "not an order site: %s" % why
    except Exception as e:                                             # noqa: BLE001
        return "alloc_sim refused to measure (%r)" % (e,)


# ------------------------------------------------------------------ the duck

def _diff(a, b, limit):
    if a is None or b is None:
        return ["(no listing)"], 0
    lines = [x for x in difflib.unified_diff(a, b, lineterm="", n=0)
             if x[:1] in "+-" and not x.startswith(("---", "+++"))]
    return (lines[:limit] or ["(identical listing)"]), max(0, len(lines) - limit)


def measure(row, text):
    """Compile the pinned text, each single erasure, the joint erasure and the pairs.
    Returns a dict the duck renders; the only expensive part of the tool."""
    sites = sites_of(text)
    ref = screen.compile_s(row, text)
    out = {"sites": sites, "ref": ref, "singles": [], "joint": None, "pairs": [],
           "pairs_shown": 0, "pairs_possible": 0, "listings": 1}
    if ref is None or not sites:
        return out
    for s in sites:
        c = screen.compile_s(row, erase_many(text, [s]))
        out["listings"] += 1
        out["singles"].append({"site": s, "fp": residue.fingerprint(ref, c), "listing": c})
    out["joint"] = screen.compile_s(row, erase_many(text, sites, clean_notes=True))
    out["listings"] += 1
    if 2 <= len(sites) <= 6:
        plan, possible = pair_plan(sites)
        out["pairs_possible"] = possible
        for i, j in plan:
            c = screen.compile_s(row, erase_many(text, [sites[i], sites[j]], clean_notes=True))
            out["listings"] += 1
            out["pairs"].append((i, j, sdiff(ref, c) if c is not None else None))
        out["pairs_shown"] = len(plan)
    return out


def duck(row_id, notes=None, row=None, text=None, skip_lane=None):
    """The row's rubber-duck brief as markdown (STATE / KNOWN / NEEDED)."""
    by = {r["id"]: r for r in all_rows()}
    row = row or by.get(row_id)
    if row is None:
        return "### DUCK %s\n\n- unknown row: it is not in ledger/rows.jsonl.\n" % row_id
    p = clean_path(row)
    if text is None:
        if not p.exists():
            return "### DUCK %s\n\n- no clean file at %s.\n" % (row_id, p)
        text = p.read_text(errors="replace")
    sha = sha_text(text)
    L = ["### DUCK %s (recipe `%s`, %d lines, text sha %s)" % (row_id, row["cfg"],
                                                               len(text.splitlines()), sha[:12])]
    m = measure(row, text)
    sites = m["sites"]
    if not sites:
        L.append("\n- no live pins in this text: nothing to remove.\n")
        return "\n".join(L) + "\n"
    if m["ref"] is None:
        L.append("\n- the pinned text does not compile to a listing here, so nothing below could be "
                 "measured; report that before working the row.\n")
        return "\n".join(L) + "\n"

    # ---------------- STATE
    L.append("\n**STATE.** %d pin(s); every measurement below is this text, %d cc1 listings."
             % (len(sites), m["listings"]))
    wide = len(sites) >= 5            # many pins: the residues go inline so the duck stays readable
    census = len(sites) > CENSUS_PINS  # very many: one line per group of alike pins, not per pin
    if census:
        pin_notes = {k + 1: note_of(text, o["site"][5]) for k, o in enumerate(m["singles"])}
        got = [k for k, v in pin_notes.items() if v]
        L.append("- notes: %s" % ("none of these pins carries a `/* ... */` note" if not got else
                                  "%d of %d pins carry a note; the distinct texts are: %s"
                                  % (len(got), len(sites),
                                     "; ".join(sorted({v for v in pin_notes.values() if v})[:3]))))
        L.append("- pins grouped by macro, pinned variable and residue class (the group's smallest "
                 "residue is the one to start from):")
        grp = {}
        for k, one in enumerate(m["singles"]):
            s, fp = one["site"], one["fp"]
            label = "`%s(%s)`" % (s[1], s[2]) + (" on `%s`" % var_of(s) if s[0] == "reg" else "")
            grp.setdefault((label, fp["cls"], fp["band"]), []).append((k, fp["d"]))
        shown = sorted(grp.items(), key=lambda kv: min(d for _, d in kv[1] if d is not None) if
                       any(d is not None for _, d in kv[1]) else 10 ** 6)
        for (label, cls_, band), members in shown[:CENSUS_GROUPS]:
            ks = ", ".join(str(k + 1) for k, _ in members)
            lns = ", ".join(str(m["singles"][k]["site"][5]) for k, _ in members)
            ds = [d for _, d in members if d is not None]
            best = min(members, key=lambda x: x[1] if x[1] is not None else 10 ** 6)
            lines, more = _diff(m["ref"], m["singles"][best[0]]["listing"], 4)
            L.append("  - %s x%d (pin %s, line %s) - %s|%s, %s changed lines"
                     % (label, len(members), ks, lns, cls_, band,
                        ("%d" % ds[0]) if len(set(ds)) == 1 else "%d..%d" % (min(ds), max(ds))))
            L.append("    smallest (pin %d, %s lines): `%s`%s"
                     % (best[0] + 1, best[1], "` `".join(lines), " ... %d more" % more if more else ""))
        if len(shown) > CENSUS_GROUPS:
            L.append("  - ... %d further groups: read them with "
                     "`python3 tools/lanes/erase_census.py OUT.jsonl --only <(echo %s) --fp --diff 4`"
                     % (len(shown) - CENSUS_GROUPS, row_id))
    else:
        for k, one in enumerate(m["singles"]):
            s, fp = one["site"], one["fp"]
            note = note_of(text, s[5]) or "(no note)"
            L.append(("" if wide else "\n") + "%d. `%s(%s)` (%s) at line %d, on `%s`"
                     % (k + 1, s[1], s[2], s[0], s[5], var_of(s)))
            L.append("   - note: %s" % note)
            head = "   - erased ALONE: %s|%s, %s changed listing lines" % (
                fp["cls"], fp["band"], fp["d"] if fp["d"] is not None else "no")
            lines, more = _diff(m["ref"], one["listing"], 4 if wide else DIFF_LINES)
            if wide:
                L.append(head + ": `" + "` `".join(lines) + "`" +
                         (" ... %d more" % more if more else ""))
            else:
                L.append(head)
                L.append("     ```\n     " + "\n     ".join(lines) + (
                    "\n     ... %d more changed lines" % more if more else "") + "\n     ```")
    jd = residue.fingerprint(m["ref"], m["joint"])
    L.append("\n- ALL %d pins erased together: %s|%s, %s changed listing lines."
             % (len(sites), jd["cls"], jd["band"], jd["d"] if jd["d"] is not None else "no"))
    lines, more = _diff(m["ref"], m["joint"], 6 if census else JOINT_DIFF_LINES)
    L.append("  ```\n  " + "\n  ".join(lines) + (
        "\n  ... %d more changed lines" % more if more else "") + "\n  ```")
    if m["pairs"]:
        d0 = {k: m["singles"][k]["fp"]["d"] for k in range(len(sites))}
        tog, indep = [], []
        for i, j, dp in m["pairs"]:
            ft = fall_together(dp, d0.get(i), d0.get(j))
            (tog if ft else indep).append("%d+%d=%s" % (i + 1, j + 1, dp))
        L.append("- pairs (%d of %d measured): fall together %s; independent %s."
                 % (m["pairs_shown"], m["pairs_possible"],
                    ", ".join(tog) or "none", ", ".join(indep) or "none"))
        exact = [f for f in m["pairs"] if f[2] == 0 and (d0.get(f[0]) or 0) > 0 and (d0.get(f[1]) or 0) > 0]
        if exact:
            L.append("  - NOTE: pair(s) %s erase to a listing IDENTICAL to the pinned one: that is a "
                     "joint erasure to put through the byte scorer, not a search."
                     % ", ".join("%d+%d" % (i + 1, j + 1) for i, j, _ in exact))
    elif len(sites) > 6:
        L.append("- pairs not measured: %d pins is past the %d-listing bound (use "
                 "tools/lanes/joint_scan.py --only %s)." % (len(sites), MAX_PAIRS, row_id))

    # ---------------- KNOWN
    L.append("\n**KNOWN.**")
    sw = sweep_verdicts(row_id)
    jr = journal_bests(row_id)
    seen_gen, cited_lanes = set(), set()
    groups = []                       # pins with the same hypothesis are one entry, not n copies
    for k, one in enumerate(m["singles"]):
        hyp, gens = hypothesis(one["site"], one["fp"])
        for g2 in groups:
            if g2[0] == hyp:
                g2[1].append(k + 1)
                break
        else:
            groups.append([hyp, [k + 1], gens])
    for hyp, ks, gens in groups:
        L.append(("" if wide else "\n") + "%s. %s" % (", ".join(map(str, ks)), hyp))
        for g in gens:
            rec = sw.get(g)
            if rec is not None:
                seen_gen.add(g)
                stale = "" if rec.get("in_sha") == sha else " (on earlier text)"
                why = rec.get("reason") or rec.get("refused") or ""
                L.append("   - `%s`: %s%s%s" % (g, rec.get("outcome", "?"), stale,
                                                (" - " + why) if why else ""))
                continue
            tag = g.split("_")[0]
            hits = [x for x in jr if ("_%s_" % tag) in x[0] or x[0].endswith("_" + tag)]
            if hits:
                same = {}
                for lane, best, outcome, refused, jsha in hits:
                    cited_lanes.add(lane)
                    stale = "" if jsha == sha else " (on earlier text)"
                    same.setdefault((outcome, best, refused, stale), []).append(lane)
                for (outcome, best, refused, stale), lanes_ in same.items():
                    L.append("   - `%s` (journal %s): %s%s%s%s" % (
                        g, ", ".join(lanes_), outcome, stale,
                        ", best listing distance %s" % best if best is not None else "",
                        " - %s" % refused if refused else ""))
            else:
                L.append("   - `%s`: no record in ledger/sweeps or any r6* journal (the sweep never "
                         "reached this row, or refused it before journalling)." % g)
    applied = [t for t, r in sw.items() if r.get("outcome") == "applied" and t not in seen_gen]
    if applied:
        L.append("\n- other transforms that changed this row: %s." % ", ".join(sorted(applied)))
    av = alloc_verdict(row, text)
    if av:
        L.append("- alloc_sim (t85's APPEARS test): %s" % av)
    for lane, best, outcome, refused, jsha in jr:
        if lane in cited_lanes:
            continue
        stale = "" if jsha == sha else " (on earlier text)"
        L.append("- journal `%s`: %s%s%s%s" % (lane, outcome, stale,
                                               ", best listing distance %s" % best if best is not None else "",
                                               ", %s" % refused if refused else ""))
    reps = [r for r in lane_reports(row_id, notes) if not r[0].startswith((skip_lane or "\0") + "/")]
    lanes = [x for x in lane_membership().get(row_id, []) if x != skip_lane]
    L.append("- previously served by: %s." % (", ".join(lanes) if lanes else "no model lane"))
    for src, quotes, verbatim in reps:
        if not quotes:
            continue
        if verbatim:
            L.append("  - %s (verbatim):" % src)
            L.extend("    %s" % q for q in quotes)
        else:
            L.append("  - %s: %s" % (src, " ".join(quotes)))
    if not reps and lanes:
        L.append("  - those lanes' REPORT.md say nothing about this row.")

    # ---------------- NEEDED
    L.append("\n**NEEDED.**")
    hyps = [hypothesis(o["site"], o["fp"]) for o in m["singles"]]
    unknown = [k + 1 for k, (h, _) in enumerate(hyps) if h.startswith("unknown")]
    for line in needed_lines(sites, m, hyps, jd):
        L.append("- " + line)
    for src, quotes, verbatim in reps:                # an "Open:" line in the evidence IS the need
        for q in quotes:
            if "Open:" in q:
                L.append("- the open question recorded by hand (%s): %s"
                         % (src, q.split("Open:", 1)[1].strip()))
    if unknown:
        L.append("- UNKNOWN: pin(s) %s have no mechanism the campaign has documented; measure what one "
                 "erasure changes (the listing lines above) before trying a shape."
                 % ", ".join(map(str, unknown)))
    L.append("- UNKNOWN in any case: which single C statement or declaration the listing residue above "
             "comes from. Erase the pins, compile, and read the diff against the pinned listing first.")
    return "\n".join(L) + "\n"


def needed_lines(sites, m, hyps, jd):
    """The plain-words 'what must change' lines, derived only from what was measured."""
    out = []
    d0 = [o["fp"]["d"] for o in m["singles"]]
    groups = {}
    for k, (h, _) in enumerate(hyps):
        groups.setdefault(h, []).append(k + 1)
    for h, ks in groups.items():
        who = "pin " + str(ks[0]) if len(ks) == 1 else "pins " + ", ".join(map(str, ks))
        if h.startswith("a callee-saved"):
            out.append("%s: a value must gain or lose a reference, or a lifetime must start or end "
                       "somewhere else, so the allocno order changes - spelling the same statements in "
                       "another order moves nothing." % who)
        elif h.startswith("a CSE barrier"):
            out.append("%s: a real store of the just-computed value placed next to its producer, so the "
                       "field loads after it are reloads." % who)
        elif h.startswith("a scheduling fence"):
            out.append("%s: the statements around the call written in the order the original source had "
                       "them - a move across a branch, a loop edge or into an argument expression." % who)
        elif h.startswith("an argument-register"):
            out.append("%s: the argument value must be produced where retail produces it (before the "
                       "call, or inside the argument expression), not staged in a local." % who)
        elif h.startswith("a $v0/$v1"):
            out.append("%s: the value's set count or lifetime must change - a chained assignment split, "
                       "or the value hosted on a local that already lives there." % who)
        elif h.startswith("the instruction stream"):
            out.append("%s: a different C construct, not a different order - a type of the field's real "
                       "width, one aggregate assignment, or a folded expression." % who)
        elif h.startswith("pure placement"):
            out.append("%s: one statement written in another place." % who)
        elif h.startswith("pure colouring"):
            out.append("%s: a lifetime or set-count change; order alone will not move it." % who)
        elif h.startswith("order and colour"):
            out.append("%s: a lifetime change that also moves the instruction - typically a value "
                       "computed on the other side of the call." % who)
        elif h.startswith("a value the decompiler invented"):
            out.append("%s: drop the invented arguments and give the callee a K&R prototype." % who)
        elif h.startswith("a register reserved"):
            out.append("%s: the block's value must live on a local the function already uses outside "
                       "the block." % who)
        else:
            out.append("%s: unknown - state what the erasure changes before proposing a shape." % who)
        if "CHANGES the opcodes too" in h:
            out[-1] += (" The opcode difference has to go first: a mask or a reload in the residue "
                        "means the C names a wider type than the field really is.")
    if len(sites) == 1:
        out.append("One pin: nothing has to fall with it.")
    else:
        tog = [(i, j) for i, j, dp in m["pairs"] if fall_together(dp, d0[i], d0[j])]
        jd_d = jd.get("d")
        if jd_d is not None and all(x is not None for x in d0) and jd_d <= min(d0):
            out.append("All %d pins must fall together: erasing them all leaves %d changed lines, no more "
                       "than any one alone (%s)." % (len(sites), jd_d, "/".join(str(x) for x in d0)))
        elif tog:
            out.append("These pins fall together: %s; the rest are independent and can be attacked one "
                       "at a time." % ", ".join("%d+%d" % (i + 1, j + 1) for i, j in tog))
        elif m["pairs"]:
            out.append("No measured pair falls together: each pin is its own question.")
        else:
            out.append("Whether the pins fall together was not measured here (too many pins); run "
                       "tools/lanes/joint_scan.py on the row.")
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("rows", nargs="+", help="row ids, e.g. dungeon/func_80A9D4E8")
    ap.add_argument("--notes", action="append", default=[],
                    help="extra markdown whose per-row section is quoted (hand probe notes)")
    a = ap.parse_args()
    prime_sweeps(a.rows)
    for rid in a.rows:
        print(duck(rid, notes=a.notes))


if __name__ == "__main__":
    main()
