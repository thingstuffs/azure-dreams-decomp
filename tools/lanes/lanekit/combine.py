#!/usr/bin/env python3
"""combine.py - WHY combine merged, or did not merge, a LOG_LINK chain: every try_combine attempt, its outcome and the
check that refused it, read out of the cell's own cc1 under gdb (combine_gdb.py).

    cd work/native_lane/<lane> && source <repo>/tools/lanes/lanekit/env.sh
    python3 <repo>/tools/lanes/lanekit/combine.py <row> [pinned|erased|cand.c] [--insn UID ...] [--i3-only]
                [--all] [--list] [--cfg CFG] [--func NAME] [--json OUT] [--timeout S]

UIDs are the insn uids of the `.flow` dump (combine runs on flow's output; `dump.py <row> <text> <dir>` writes it) -
not the `.combine` dump, where the i2/i1 a merge deleted are gone.  Every attempt prints the three patterns as
they were when try_combine was entered, so the dump is rarely needed.

  --insn UID   every attempt that involves UID as i3, i2 or i1 (`--i3-only`: as i3 only), in full
  --all        every attempt of the function, in full
  --list       one line per attempt
  (default)    the refusal census: attempts per reason, with an example attempt number per reason

Per attempt: `COMBINED` (the new i3 pattern, and whether i2/i1 were deleted or i2 got a new pattern) or `REFUSED`
with the return site (combine.c line) and the reason:

  can_combine_p(i2|i1 UID)   the insn may not be substituted: for the long test chain the clause that was TRUE -
                             use_crosses_set_p (and WHAT crossed: `register N is set again by insn M`, or `the source
                             reads memory and a store / a CALL lies between: insn M` = mem_last_set), crosses-call
                             (last_call_cuid), used-between, call-arg, libcall-end, no-conflict, volatile-asm ...;
                             otherwise two-sets, dest-not-reg (a store), hard-reg, volatile-between, i3-clobber
  combinable_i3pat           i3's destination is a partial (subreg / strict_low_part) write over i2dest/i1dest,
                             or i3 kills two registers
  subst-fail                 subst gave up: (clobber (const_int 0)) / a new pseudo / a new MULT
  no-recog                   the merged pattern matches no mips.md insn: every recog_for_combine call is listed with
                             the pattern it was handed and the insn code it returned (-1 = none).  `no-recog (volatile
                             MEM)`: combine recognizes with volatile_ok = 0, so a volatile MEM operand never matches;
                             `no-recog (added sets)`: i2dest/i1dest stays live, the kept-SET PARALLEL matches nothing

2.x combine has NO cost test: what looks like "not profitable" in this compiler is `no-recog`.

Cells: 2.7.2-cdk validated (the r93 fixtures, dungeon/func_800C9858; README).  Other cells: the site tables are
paired with their own combine.c only when the counts agree (printed); the chain clause model is cdk's and is
marked UNVERIFIED wherever the call evidence disagrees.  Nothing is written outside the lane.
"""
from __future__ import annotations

import argparse
import json
import re
import sys
from collections import Counter
from pathlib import Path

_HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(_HERE))
if not (_HERE / "kitlib.py").is_file():                      # a lane copy: use the repository's kit
    _root = next(p for p in _HERE.parents if (p / "tools/common.py").is_file())
    sys.path.insert(0, str(_root / "tools/lanes/lanekit"))
import kitlib                                                             # noqa: E402
import combine_gdb as G                                                   # noqa: E402


def ccp_text(ev):
    """One can_combine_p refusal as a short reason."""
    s = ev.get("site") or {}
    if s.get("key") == "chain":
        c = ev.get("clause")
        return c or "chain (no clause true?)"
    return s.get("key") or "refused (site not traced)"


def reason(att):
    """(census key, one-line reason) of an attempt."""
    if att.get("ret"):
        return "COMBINED", "COMBINED"
    s = att.get("site") or {}
    key = s.get("key")
    ev = att.get("events", [])
    if key == "can_combine_p":
        bad = [e for e in ev if e["e"] == "can_combine_p" and e.get("ret") == 0]
        if bad:
            e = bad[-1]
            r = ccp_text(e)
            return "can_combine_p(%s): %s" % (e["role"], r), "can_combine_p(%s %s): %s" % (e["role"], e["insn"], r)
    if key in ("i3pat", "i3pat-i1"):
        bad = [e for e in ev if e["e"] == "combinable_i3pat" and e.get("ret") == 0]
        r = ((bad[-1].get("site") or {}).get("key") if bad else None) or "refused"
        return "combinable_i3pat: %s" % r, "combinable_i3pat (%s): %s" % (key, r)
    if key == "subst-fail":
        return "subst-fail: %s" % subst_why(att), "subst failed: %s" % subst_why(att)
    if key == "no-recog":
        tags = [k for k, _ in recog_notes(att)]
        if "volatile" in tags:
            return "no-recog (volatile MEM)", "NO RECOG: a volatile MEM operand (combine recognizes with volatile_ok = 0)"
        if "added-sets" in tags:
            return "no-recog (added sets)", "NO RECOG: the PARALLEL that keeps i2dest/i1dest live matches no insn"
    if key is None:
        return "refused (no site)", "refused (no return site traced)"
    return key, s.get("text") or key


VOL_MEM = re.compile(r"\(mem(?:/[a-z])*/v[/:]")
VOL_NOTE = ("combine runs recog with volatile_ok = 0 (combine_instructions -> init_recog_no_volatile): general_operand "
            "refuses a volatile MEM, so a merge that moves a volatile MEM into another insn is never recognized - "
            "the volatile qualifier, not mips.md, refuses it")
ADDED_NOTE = ("i2dest/i1dest is still live after i3 (added_sets): the merged insn must keep the old SET too, so a "
              "multi-SET PARALLEL was tried")


def recog_notes(att):
    """[(tag, note)] for an attempt's recog_for_combine calls: volatile MEM operands, added-sets PARALLELs."""
    rec = [e for e in att.get("events", []) if e["e"] == "recog_for_combine"]
    out = []
    if rec and VOL_MEM.search(rec[0].get("pat") or "") and (rec[0].get("ret") or 0) < 0:
        out.append(("volatile", VOL_NOTE))
    if rec and (rec[0].get("pat") or "").startswith("(parallel") and not (att["pat"].get("i3") or "").startswith(
            "(parallel"):
        out.append(("added-sets", ADDED_NOTE))
    return out


def subst_why(att):
    subs = [e for e in att.get("events", []) if e["e"] == "subst"]
    why = []
    if subs and subs[-1].get("ret_code") == "clobber":
        why.append("subst returned (clobber (const_int 0))")
    if att.get("regs0") is not None and att.get("regs1") is not None and att["regs1"] != att["regs0"]:
        why.append("a new pseudo was made (%d -> %d)" % (att["regs0"], att["regs1"]))
    if subs and "(mult" in (subs[-1].get("ret") or "") and not any("(mult" in (p or "") for p in att["pat"].values()):
        why.append("the result is a new MULT")
    return "; ".join(why) or "an auto-inc side effect duplicated"


def head(att):
    return "#%d try_combine i3 %s  i2 %s%s" % (att["n"], att["i3"], att["i2"],
                                                "  i1 %s" % att["i1"] if att.get("i1") is not None else "")


def line_of(att):
    k, r = reason(att)
    s = att.get("site") or {}
    if att.get("ret"):
        return "%-44s COMBINED%s" % (head(att), "  -> i3 " + (att.get("new") or {}).get("i3", "")[:90])
    sub = [e for e in att.get("events", []) if e.get("ret") == 0 and e.get("site")]
    where = "combine.c:%s" % (sub[-1]["site"]["line"] if sub else s.get("line"))
    return "%-44s REFUSED  %s   [%s]" % (head(att), r, where)


def detail(att):
    out = [line_of(att)]
    pat = att["pat"]
    for role in ("i3", "i2", "i1"):
        if att.get(role) is not None:
            out.append("      %-2s %-5s %s" % (role, att[role], pat.get(role)))
    for e in att.get("events", []):
        k = e["e"]
        if k == "can_combine_p":
            if e.get("ret"):
                out.append("      can_combine_p(%s %s%s) ok" % (e["role"], e["insn"],
                                                              ", succ %s" % e["succ"] if e.get("succ") else ""))
                continue
            s = e.get("site") or {}
            out.append("      can_combine_p(%s %s%s) REFUSED at combine.c:%s - %s" % (
                e["role"], e["insn"], ", succ %s" % e["succ"] if e.get("succ") else "", s.get("line"),
                s.get("text") if s.get("key") != "chain" else "chain clause %s" % e.get("clause")))
            if s.get("key") == "chain":
                cl = dict(G.CHAIN).get(e.get("clause"), "")
                out.append("          %s" % cl)
                out.append("          src %s  dest %s  all_adjacent %s  (clause check: %s)" % (
                    e.get("src"), e.get("dest"), e.get("all_adjacent"), e.get("clause_check")))
                for d in e.get("clause_detail") or []:
                    out.append("          " + d)
            elif s.get("cond"):
                out.append("          if %s" % s["cond"][:200].removeprefix("if "))
        elif k == "combinable_i3pat":
            if e.get("ret") == 0:
                s = e.get("site") or {}
                out.append("      combinable_i3pat(%s) REFUSED at combine.c:%s - %s" % (e.get("on"), s.get("line"),
                                                                                      s.get("text")))
        elif k == "subst":
            out.append("      subst %s := %s  ->  %s" % (e.get("from"), e.get("to"), e.get("ret")))
        elif k == "recog_for_combine":
            c = e.get("ret")
            out.append("      recog_for_combine (insn %s) %s  ->  %s" % (
                e.get("insn"), e.get("pat"), "%d (no insn)" % c if c is not None and c < 0 else "code %s" % c))
            if e.get("after") and e.get("after") != e.get("pat") and c is not None and c >= 0:
                out.append("          recognized as %s" % e["after"])
        elif k == "use_crosses_set_p":
            out.append("      use_crosses_set_p -> %s (the split path)" % e.get("ret"))
    for _, note in recog_notes(att):
        out.append("      note: " + note)
    s = att.get("site") or {}
    if not att.get("ret") and s:
        out.append("      try_combine returns 0 at combine.c:%s (%s)" % (s.get("line"), s.get("key")))
        if s.get("key") == "subst-fail":
            out.append("          " + subst_why(att))
    if att.get("ret"):
        n = att.get("new") or {}
        out.append("      => i3 %s now %s" % (att["i3"], n.get("i3")))
        if n.get("i2_kind") not in ("insn", "jump_insn", "call_insn"):
            out.append("         i2 %s deleted (%s)" % (att["i2"], n.get("i2_kind")))
        elif n.get("i2") and n.get("i2") != pat.get("i2"):
            out.append("         i2 %s now %s" % (att["i2"], n.get("i2")))
        if att.get("i1") is not None:
            out.append("         i1 %s %s" % (att["i1"], "deleted" if n.get("i1_kind") not in ("insn", "jump_insn",
                                                                                              "call_insn") else "kept"))
        out.append("         resume scanning at insn %s" % att["ret"])
    return out


def dump_stats(dump, func):
    """(attempts, successes) of `func` from the `.combine` dump's `;; Combiner statistics:` lines (None if absent)."""
    parts = re.split(r"^;; Function (\S+)", dump, flags=re.M)
    for i in range(1, len(parts) - 1, 2):
        if parts[i] == func:
            m = re.search(r";; Combiner statistics: (\d+) attempts.*?\n;; (\d+) successes", parts[i + 1], re.S)
            if m:
                return int(m.group(1)), int(m.group(2))
    return None


def report(row, text, tname, func=None, insns=(), i3_only=False, show_all=False, show_list=False, timeout=600,
           json_out=None, lane=None):
    lane_root = Path(lane or kitlib.lane_dir()).resolve()
    if json_out:
        jo = Path(json_out) if Path(json_out).is_absolute() else lane_root / json_out
        try:
            jo.resolve().relative_to(lane_root)
        except ValueError:
            raise SystemExit("combine: --json %s is outside the lane %s" % (json_out, lane_root))
    d = G.trace(row, text, func=func, timeout=timeout)
    if d.get("error"):
        raise SystemExit("combine: %s: %s" % (tname, d["error"]))
    cell = d["cell"]
    print("# combine %s  %s  (function %s, recipe %s, cell %s: %s)" % (
        row["id"], tname, d["func"], row["cfg"], cell,
        "validated" if cell in G.VALIDATED else "UNVALIDATED - the chain clause model is 2.7.2-cdk's"))
    if d.get("gdb_error"):
        raise SystemExit("combine: gdb: %s" % d["gdb_error"])
    print("# trace faithful: %s" % ("yes - the traced compile's assembly is identical to a plain compile"
                                     if d.get("faithful") else "NO - the traced assembly differs; distrust the trace"))
    recs = d["records"] or []
    errs = [r for r in recs if r.get("t") == "err"]
    if errs:
        print("# tracer errors: %d (first: %s)" % (len(errs), errs[0].get("msg")))
    atts = [r for r in recs if r.get("t") == "attempt"]
    ok = sum(1 for a in atts if a.get("ret"))
    print("# %d try_combine attempts: %d combined, %d refused  (uids = the .flow dump's)" % (len(atts), ok,
                                                                                           len(atts) - ok))
    st = dump_stats(d.get("combine") or "", d["func"])
    if st:
        tried = sum(1 for a in atts if (a.get("site") or {}).get("key") != "not-insn")
        print("# trace vs .combine statistics: attempts %d/%d, successes %d/%d%s" % (
            tried, st[0], ok, st[1], "" if (tried, ok) == st else "   MISMATCH - distrust the trace"))
    if json_out:
        jo.write_text(json.dumps({"func": d["func"], "cell": cell, "faithful": d.get("faithful"), "attempts": atts},
                                 indent=1))
        print("# wrote %s" % jo)
    if insns:
        want = set(insns)
        sel = [a for a in atts if a["i3"] in want or (not i3_only and (a["i2"] in want or a.get("i1") in want))]
        print("# attempts involving %s%s: %d" % (", ".join(map(str, insns)), " as i3" if i3_only else " (as i3, i2 or i1)",
                                                 len(sel)))
        if not sel:
            print("  none - is %s a .flow uid of %s?  (an insn without LOG_LINKS into or out of it is never tried)"
                  % (", ".join(map(str, insns)), d["func"]))
        for a in sel:
            print()
            print("\n".join(detail(a)))
        return atts
    if show_all:
        for a in atts:
            print()
            print("\n".join(detail(a)))
        return atts
    if show_list:
        for a in atts:
            print(line_of(a))
        return atts
    cen = Counter()
    ex = {}
    for a in atts:
        k, _ = reason(a)
        cen[k] += 1
        ex.setdefault(k, a["n"])
    print("# reasons (attempts, first attempt number) - `--insn UID` / `--list` / `--all` for the attempts:")
    for k, n in cen.most_common():
        print("  %5d  %-60s  #%d" % (n, k, ex[k]))
    return atts


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("text", nargs="?", default="erased", help="pinned, erased (default) or a candidate file")
    ap.add_argument("--insn", type=int, action="append", default=[], help="attempts involving this .flow uid")
    ap.add_argument("--i3-only", action="store_true", help="with --insn: only attempts where it is i3")
    ap.add_argument("--all", action="store_true", help="every attempt in full")
    ap.add_argument("--list", action="store_true", help="one line per attempt")
    ap.add_argument("--cfg", help="compile as if the row were registered at this cfg (no ledger write)")
    ap.add_argument("--func", help="the C function to trace (default: the row's true_name / func)")
    ap.add_argument("--timeout", type=int, default=600, help="seconds for the gdb run (default 600)")
    ap.add_argument("--json", help="write every attempt record to this file (inside the lane)")
    a = ap.parse_args(argv)
    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    if a.cfg:
        row = kitlib.row_at_cfg(row, a.cfg)
    base = kitlib.base_text(row, lane)
    if a.text in ("pinned", "base"):
        text, tname = base, "pinned"
    elif a.text == "erased":
        text, tname = kitlib.erased_text(base), "erased"
    else:
        p = Path(a.text)
        if not p.is_file():
            raise SystemExit("combine: %r is neither 'pinned', 'erased' nor a file" % a.text)
        text, tname = p.read_text(errors="replace"), p.stem
    report(row, text, tname, func=a.func, insns=a.insn, i3_only=a.i3_only, show_all=a.all, show_list=a.list,
           timeout=a.timeout, json_out=a.json, lane=lane)


if __name__ == "__main__":
    main()
