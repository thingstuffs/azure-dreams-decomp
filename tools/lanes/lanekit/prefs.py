#!/usr/bin/env python3
"""prefs.py - why global.c gave an allocno its register: the hard-register PREFERENCES, replayed exactly.

    cd work/native_lane/<lane>
    python3 <KIT>/prefs.py <row> <candidate.c|pinned|erased> [PSEUDO|NAME ...] [--retail P=REG ...]
                           [--all] [--oracle] [--json OUT] [--cfg CFG]

The model is tools/alloc_prefs.py (set_preference -> expand_preferences -> prune_preferences / regs_someone_prefers
-> find_reg, gcc 2.7.2-cdk global.c; 2.8.x identical).  One `-da` compile; the fidelity lines come first (the
dumped `;; N preferences:` sets and the greg dispositions; `--oracle` adds every intermediate set and every
find_reg result read out of the cell's cc1 under gdb, prefs_gdb.py).  Then, per pseudo asked for (default: the
allocnos a preference moved off the scan's choice, plus the --retail ones):

    101 (pixel_offset) -> $s0  [GR_REGS, refs 10 live 15 calls 0, rank 5 of 35]
      DECIDED BY PREFERENCE $s0 (the scan alone gave $v1 in pass 0)
        <- merged from 90 (facing_shift) at insn 279 `r101:pixel_offset = abs(r90:facing_shift)` (90 dies here)
          <- direct insn 140 `r145@$s0 = zero_extend(subreg(r90:facing_shift))` (r145 is local-alloc'd to $s0)
      retail $v1: then preference $s0 overrode the scan

and, with retail registers (`--retail 101=v1`; alloc_need.py passes its listing votes), the single preference
changes that give them, each re-run through the whole allocation: drop one set_preference insn, one expand merge,
every merge between one allocno pair, or every tie of one allocno to one hard register; collateral = the other
allocnos that move.  Each is a source-visible thing (a copy to/from a parameter / call argument / return value /
ASM_REG variable / local qty's register, or a statement `x = f(y)` where y dies).  An ADDED copy preference is
listed last: it is a lever only where retail's code already moves that value through the register.
"""
from __future__ import annotations

import argparse
import collections
import json
import sys
from pathlib import Path

_HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(_HERE))
if not (_HERE / "kitlib.py").is_file():                      # a lane copy: use the repository's kit
    _root = next(p for p in _HERE.parents if (p / "tools/common.py").is_file())
    sys.path.insert(1, str(_root / "tools/lanes/lanekit"))
if (_HERE.parents[1] / "alloc_prefs.py").is_file():          # a patch copy (draft/tools/...): its own tools/
    sys.path.insert(0, str(_HERE.parents[1]))
import kitlib                                                             # noqa: E402
kitlib.add_paths()
from alloc_prefs import (X, CALL_USED, FIXED, Problem, Replay, fidelity, rname, regset, show,  # noqa: E402,F401
                         single_set, walk_regs)

# ------------------------------------------------------------------------------------------ explanation

class Explainer:
    def __init__(self, pb, names=None):
        self.pb = pb
        self.names = names or {}
        self.base = Replay(pb)

    def label(self, p):
        n = self.names.get(p)
        return "%d (%s)" % (p, n) if n else str(p)

    def event_text(self, k):
        e = self.pb.events[k]
        ins = e["ins"]
        role = self._role(e)
        return "insn %d `%s` (%s %s%s)%s" % (
            e["uid"], show(e["set"], self.pb, self.names), "copy" if e["copy"] else "non-copy",
            "preference" if e["copy"] else "preference", "" if not role else ", " + role,
            "")

    def _role(self, e):
        h, nm = e["hard"], self.names.get(e["pseudo"])
        if e["via_local"]:
            return "r%d is local-alloc'd to %s" % (e["other"], rname(e["hard"]))
        if e.get("user_hard"):
            return "a register variable (ASM_REG pin) in %s" % rname(h)
        if e["side"] == "src" and 4 <= h <= 7:
            return "parameter %s %s" % ("arrives in" if e["ins"].prologue else "read from", rname(h))
        if e["side"] == "dest" and 4 <= h <= 7:
            return "call argument %s" % rname(h)
        if e["side"] == "src" and h == 2:
            return "call result / $v0 value"
        if e["side"] == "dest" and h == 2:
            return "return value / $v0 set"
        return ""

    def merge_text(self, k):
        m = self.base.merge_list[k]
        return "insn %d `%s` (%s dies here: %s merge)" % (m["uid"], show(single_set(m["ins"]), self.pb, self.names),
                                                       self.label(m["a2"]), "copy" if m["copy"] else "plain")

    def chain(self, rp, p, nm, h, depth=0, seen=None):
        """[(depth, text)] provenance of bit h in set nm of p."""
        seen = seen or set()
        out = []
        if (p, nm, h) in seen or depth > 6:
            return out
        seen.add((p, nm, h))
        for org in rp.why.get((p, nm, h), []):
            if org[0] == "direct":
                out.append((depth, "direct " + self.event_text(org[1])))
            elif org[0] == "merge":
                out.append((depth, "merged from %s at %s" % (self.label(org[2]), self.merge_text(org[1]))))
                out.extend(self.chain(rp, org[2], nm, h, depth + 1, seen))
            else:
                out.append((depth, "added by hand"))
        return out

    def decision(self, p, rp=None):
        rp = rp or self.base
        tr = rp.trace.get(p)
        if tr is None:
            return ["%s is not a global allocno" % self.label(p)]
        if "skipped" in tr:
            return ["%s skipped: %s" % (self.label(p), tr["skipped"])]
        st = self.pb.stats.get(p, {})
        got = rp.result[p]
        lines = ["%s -> %s  [%s, refs %d live %d calls %d, rank %d of %d]%s" % (
            self.label(p), rname(got), tr["class"], st.get("refs", 0), st.get("live", 0), st.get("calls", 0),
            rp.order.index(p) + 1, len(rp.order), "  (caller-saves)" if tr.get("via") else "")]
        if tr["how"] in ("copy-preference", "preference"):
            nm = "copy" if tr["how"] == "copy-preference" else "pref"
            if tr["scan"] != got:
                lines.append("  DECIDED BY %s %s (the scan alone gave %s in pass %s)" % (
                    tr["how"].upper(), rname(got), rname(tr["scan"]), tr["pass"]))
            else:
                lines.append("  %s %s confirmed by %s (the pass-%s scan gives the same register)" % (
                    "scan", rname(got), tr["how"], tr["pass"]))
            for d, t in self.chain(rp, p, nm, got):
                lines.append("    " + "  " * d + "<- " + t)
        else:
            lines.append("  %s: lowest free register in %s" % (tr["how"] or "no register", "pass 0 (already-used, "
                         "not preferred by a lower-priority conflict)" if tr["pass"] == 0 else "pass 1"))
            lower = [r for r in range(got if got >= 0 else 32) if r < 32 and r not in tr["used1"]]
            if tr["pass"] == 0 and lower:
                for r in lower:
                    lines.append("    skipped %s in pass 0: %s" % (rname(r), self.skip_reason(rp, p, r, tr)))
        return lines

    def skip_reason(self, rp, p, r, tr):
        why = []
        if r in tr["unused"]:
            why.append("not used yet in the function (regs_used_so_far)")
        if r in tr["someone"]:
            srcs = rp.someone_src[p].get(r, [])
            why.append("regs_someone_prefers: lower-priority conflicting %s prefer%s it" % (
                ", ".join(self.label(q) for q in srcs[:4]), "s" if len(srcs) == 1 else ""))
        return "; ".join(why) or "?"

    def blocked(self, p, r, rp=None):
        """Why p did not get register r (retail's), in this replay."""
        rp = rp or self.base
        tr = rp.trace.get(p)
        if tr is None or "skipped" in tr:
            return "not a global allocno"
        st = self.pb.stats.get(p, {})
        if r in FIXED:
            return "fixed register"
        if st.get("calls") and r in CALL_USED and not tr.get("accept"):
            return "call-used and %s crosses %d call(s)" % (self.label(p), st["calls"])
        if r in self.pb.hconf0.get(p, ()):
            return "HARD conflict in the dump (a hard register / local qty in %s is live inside its life)" % rname(r)
        taken = tr.get("taken_by", {})
        if r in taken:
            q = taken[r]
            return "taken earlier by conflicting allocno %s (rank %d)" % (self.label(q), rp.order.index(q) + 1)
        got, scan = rp.result[p], tr.get("scan", -1)
        parts = []
        if scan >= 0 and r < scan:                        # the scan passed r: it was in `used` in that pass
            if tr["pass"] == 0 and r in tr["someone"]:
                srcs = rp.someone_src[p].get(r, [])
                parts.append("pass 0 skipped it: regs_someone_prefers (lower-priority conflicting %s prefer%s it)"
                             % (", ".join(self.label(q) for q in srcs[:4]), "s" if len(srcs) == 1 else ""))
            if tr["pass"] == 0 and r in tr["unused"]:
                parts.append("pass 0 skipped it: not used yet in the function (pass 0 never opens a register)")
            if tr["pass"] == 1:
                parts.append("pass 1 skipped it (in used1)")
        elif scan >= 0 and r > scan:
            parts.append("the scan reaches %s first (lowest free register)" % rname(scan))
            parts.append(self.needs(p, r, rp))
        if tr["how"] in ("copy-preference", "preference") and got != scan:
            parts.append("then %s %s overrode the scan" % (tr["how"], rname(got)))
        elif tr["how"] in ("copy-preference", "preference"):
            parts.append("and a %s for %s confirms it" % (tr["how"], rname(got)))
        return "; ".join(parts) or "free, but not chosen"

    def needs(self, p, r, rp=None):
        """What would have to change for p's scan to reach r: the free registers below r, and the allocnos that could
        take them out of pass 0 (lower-priority conflicting allocnos, via regs_someone_prefers) or out of both passes
        (higher-priority conflicting allocnos holding them, or a hard register live inside p's life)."""
        rp = rp or self.base
        tr = rp.trace[p]
        below = [x for x in range(r) if x not in tr["used1"] and x < 32]
        if not below:
            return "nothing below %s is free" % rname(r)
        st0 = self.pb.stats.get(p, {})
        if r not in CALL_USED and not st0.get("calls") and any(x in CALL_USED for x in below):
            return ("retail's %s is CALLEE-SAVED but %s crosses no call here, so every free call-used register below it "
                    "(%s) comes first: in retail the value most likely lives across a call (the CLASS lever: "
                    "move a set/use across the call), or a copy preference ties it to a %s holder" % (
                        rname(r), self.label(p), " ".join(rname(x) for x in below if x in CALL_USED), rname(r)))
        rank = {q: i for i, q in enumerate(rp.order)}
        me = rank[p]
        st = self.pb.stats
        lower_all = sorted((q for q in self.pb.adj[p] if q != p and rank.get(q, -1) > me), key=rank.get)
        # prune_preferences strips call-used registers from a call-crossing allocno's preferences: only allocnos
        # that cross no call (or registers that are not call-used) can put a register into regs_someone_prefers
        lower = [q for q in lower_all if not st.get(q, {}).get("calls") or any(x not in CALL_USED for x in below)]
        higher = sorted((q for q in self.pb.adj[p] if q != p and 0 <= rank.get(q, -1) < me), key=rank.get)
        pre = {q: sorted(x for x in rp.full_after_prune.get(q, ()) if x in below) for q in lower}
        have = ["%s prefers %s" % (self.label(q), " ".join(rname(x) for x in v)) for q, v in pre.items() if v]
        return ("to reach %s, pass 0 must lose %s: each must be a hard conflict (a higher-priority conflicting allocno "
                "or a hard register holding it inside %s's life; higher-priority conflicts: %s) or preferred by a "
                "LOWER-priority conflicting allocno (regs_someone_prefers; candidates: %s%s)" % (
                    rname(r), " ".join(rname(x) for x in below), self.label(p),
                    ", ".join("%s=%s" % (self.label(q), rname(rp.result.get(q))) for q in higher[:6]) or "none",
                    ", ".join(self.label(q) for q in lower[:8]) or (
                        "NONE: the %d lower-priority conflicting allocno(s) all cross calls, so prune strips these "
                        "call-used registers from their preferences" % len(lower_all) if lower_all else "none"),
                    "; already: " + "; ".join(have) if have else ""))

    def counterfactuals(self, targets, limit=8, include_adds=True, keep=None):
        """targets {p: retail reg} (mis-coloured now); keep {p: reg} (right now, must stay).  Single event removals
        (one set_preference insn, one expand merge, or every merge between one allocno pair) and, per target, one
        added copy preference: which give targets their retail registers, and what else moves."""
        base = self.base.result
        keep = {p: r for p, r in (keep or {}).items() if p not in targets}
        res = []
        nE, nM = len(self.pb.events), len(self.base.merge_list)
        trials = [("event", k) for k in range(nE)] + [("merge", k) for k in range(nM)]
        pairs = collections.defaultdict(list)            # every merge between the same two allocnos, as one trial
        for k, m in enumerate(self.base.merge_list):
            pairs[frozenset((m["a1"], m["a2"]))].append(k)
        trials += [("pair", tuple(ks)) for ks in pairs.values() if len(ks) > 1]
        hard = collections.defaultdict(list)             # every set_preference event between one allocno and one hard reg
        for k, e in enumerate(self.pb.events):
            hard[(e["pseudo"], e["hard"])].append(k)
        trials += [("hard", tuple(ks)) for ks in hard.values() if len(ks) > 1]
        if include_adds:
            trials += [("add", (p, r)) for p, r in targets.items()]
        for kind, k in trials:
            if kind == "event":
                rp = Replay(self.pb, drop_events={k})
            elif kind == "merge":
                rp = Replay(self.pb, drop_merges={k})
            elif kind == "pair":
                rp = Replay(self.pb, drop_merges=set(k))
            elif kind == "hard":
                rp = Replay(self.pb, drop_events=set(k))
            else:
                rp = Replay(self.pb, add=[(k[0], k[1], True)])
            hit = [p for p, r in targets.items() if rp.result.get(p) == r]
            lost = [p for p, r in keep.items() if rp.result.get(p) != r]
            moved = [q for q in self.pb.allocnos if rp.result.get(q) != base.get(q) and q not in targets
                     and q not in keep]
            if not hit or len(hit) <= len(lost):
                continue
            res.append({"kind": kind, "k": k, "hit": hit, "lost": lost, "moved": moved,
                        "result": {q: rp.result.get(q) for q in moved + hit + lost}})
        res.sort(key=lambda d: (-len(d["hit"]) + len(d["lost"]), len(d["moved"])))
        return [d for d in res if d["kind"] != "add"][:limit] + [d for d in res if d["kind"] == "add"][:3]

    def cf_text(self, c):
        if c["kind"] == "event":
            what = "drop " + self.event_text(c["k"])
        elif c["kind"] == "merge":
            what = "drop " + self.merge_text(c["k"])
        elif c["kind"] == "hard":
            e = self.pb.events[c["k"][0]]
            what = "drop every insn tying %s to %s (%s)" % (self.label(e["pseudo"]), rname(e["hard"]),
                                                          "; ".join(self.event_text(k) for k in c["k"]))
        elif c["kind"] == "pair":
            m = self.base.merge_list[c["k"][0]]
            what = "break every merge between %s and %s (%s)" % (
                self.label(m["a1"]), self.label(m["a2"]), "; ".join(self.merge_text(k) for k in c["k"]))
        else:
            what = "give %s a copy preference for %s (a copy to/from a value that lives in %s)" % (
                self.label(c["k"][0]), rname(c["k"][1]), rname(c["k"][1]))
        side = ", ".join("%s -> %s" % (self.label(q), rname(c["result"][q])) for q in c["moved"][:6])
        return "%s: fixes %s%s; collateral %d%s" % (
            what, ", ".join(self.label(q) for q in c["hit"]),
            "; breaks " + ", ".join(self.label(q) for q in c["lost"]) if c["lost"] else "",
            len(c["moved"]), " (" + side + ("..." if len(c["moved"]) > 6 else "") + ")" if c["moved"] else "") + (
            "  [an ADDED preference is a lever only where retail's code already moves that value through %s - "
            "never a same-value re-copy]" % rname(c["k"][1]) if c["kind"] == "add" else "")



# ------------------------------------------------------------------------------------------ driver

def problem_for(row, text, dumps=None):
    """(Problem, names, dumps) for a text compiled as row (one -da compile via kitlib.dumps)."""
    import kitlib
    import alloc_sim as sim
    from common import parse_cfg
    cell, cflags = parse_cfg(row["cfg"])
    fp = sim.FIRST.get(cell)
    if fp != 76:
        raise SystemExit("prefs.py: models the FIRST_PSEUDO_REGISTER=76 cells (2.7.2-cdk, 2.8.x); %s is %s"
                         % (cell, fp))
    d = dumps or kitlib.dumps(row, text, want={"greg", "lreg", "flow"})
    if d is None or d.get("error"):
        raise SystemExit("prefs.py: does not build: %s" % ((d or {}).get("error") or "")[-300:])
    dp = sim.decl_pseudos(text, fp) or {}
    names = {v: k for k, v in (dp.get("map") or {}).items()}
    pb = Problem(d["lreg"], d["greg"], d.get("flow", ""), dp.get("fname"),
                 caller_saves="-fno-caller-saves" not in cflags)
    return pb, names, d


def parse_targets(items, names):
    from alloc_need import REGNUM
    inv = {v: k for k, v in names.items()}
    out = {}
    for it in items:
        k, _, v = it.partition("=")
        v = v.strip().lstrip("$")
        r = int(v) if v.isdigit() else REGNUM.get(v)
        p = int(k) if k.strip().isdigit() else inv.get(k.strip())
        if p is None or r is None:
            raise SystemExit("prefs.py: --retail %r: need PSEUDO|NAME=REG" % it)
        out[p] = r
    return out


def main(argv=None):
    import kitlib
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row")
    ap.add_argument("text")
    ap.add_argument("pseudos", nargs="*", help="pseudo numbers or variable names to explain (default: all "
                    "preference-decided allocnos + the --retail ones)")
    ap.add_argument("--retail", action="append", default=[], metavar="P=REG")
    ap.add_argument("--cfg")
    ap.add_argument("--all", action="store_true", help="explain every allocno")
    ap.add_argument("--oracle", action="store_true", help="also run prefs_gdb.py (cc1 under gdb) and compare")
    ap.add_argument("--json")
    a = ap.parse_args(argv)
    lane = kitlib.bootstrap()
    row = kitlib.row_at_cfg(kitlib.row_of(a.row), a.cfg)
    base = kitlib.base_text(row, lane)
    text = base if a.text in ("pinned", "base") else kitlib.erased_text(base) if a.text == "erased" else \
        Path(a.text).read_text(errors="replace")
    pb, names, _d = problem_for(row, text)
    ex = Explainer(pb, names)
    oracle = None
    if a.oracle:
        import prefs_gdb
        oracle = prefs_gdb.trace(row, text)
    fid = fidelity(pb, ex.base, oracle)
    print("# prefs %s (%s): %d allocnos, %d set_preference events, %d expand merges" % (
        a.row, pb.fname, len(pb.allocnos), len(pb.events), len(ex.base.merge_list)))
    for k, (g, n, notes) in fid.items():
        print("#   fidelity %-30s %d/%d%s" % (k, g, n, ("   " + "; ".join(notes[:4])) if notes else ""))
    inv = {v: k for k, v in names.items()}
    want = [int(x) if x.isdigit() else inv.get(x) for x in a.pseudos]
    targets = parse_targets(a.retail, names)
    if a.all:
        want = list(ex.base.order)
    if not want:
        want = [p for p in ex.base.order if ex.base.trace[p].get("how") in ("copy-preference", "preference")]
    want += [p for p in targets if p not in want]
    for p in want:
        if p is None:
            continue
        print()
        for ln in ex.decision(p):
            print(ln)
        if p in targets:
            r = targets[p]
            print("  retail %s: %s" % (rname(r), "already" if ex.base.result.get(p) == r else ex.blocked(p, r)))
    if targets:
        print()
        cfs = ex.counterfactuals(targets)
        print("# single preference changes that give retail's register (%d of %d targets now right):" % (
            sum(1 for p, r in targets.items() if ex.base.result.get(p) == r), len(targets)))
        for c in cfs:
            print("  " + ex.cf_text(c))
        if not cfs:
            print("  none: no single set_preference event / expand merge removal or added copy preference does it")
    if a.json:
        Path(a.json).write_text(json.dumps({"fidelity": fid, "result": ex.base.result}, default=list, indent=1))


if __name__ == "__main__":
    main()
