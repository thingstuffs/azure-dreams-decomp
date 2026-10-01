#!/usr/bin/env python3
"""Fixture oracle for the birthing-boost family.

    python3 tools/lanes/lanekit/counts.py FILE.c [--row dungeon/func_800A1020] [--cfg CFG] [--keep]

Compiles the fixture as the row (its recipe), keeps every -da dump under ./tmp/fx/<stem>/ (relative to the cwd) and prints
  * per register: sets counted in the .flow dump (after flow's dead-insn deletion = what reg_n_sets holds
    when flow ends) and in the .combine dump (what sched1 reads: combine.c 2368/2391 decrement when it
    merges a setter away, 1864 increments on a split) - SET and CLOBBER, through SUBREG / STRICT_LOW_PART,
    pseudos and hard registers alike (flow.c mark_set_1 2102/2120);
  * per sched1 block: the insns whose dynamic priority reached 0x7f000001 in a ready list (= adjust_priority's
    birthing boost, sched.c 2583) with their pattern, and the insns that were ready at the same tick but NOT
    boosted (dest multi-set / not a REG / not live).
"""
import argparse
import collections
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import kitlib  # noqa: E402

SET_RE = re.compile(r"\((set|clobber) \((?:(reg)[^ ]* (\d+)|(subreg|strict_low_part|zero_extract|sign_extract)[^ ]* \(reg[^ ]* (\d+)\))")
INSN_RE = re.compile(r"^\((insn|call_insn|jump_insn) (\d+) ", re.M)
READY_RE = re.compile(r";; ready list at T-(\d+): (.*?), now (.*)")
PRIO_RE = re.compile(r"(\d+) \(([0-9a-f]+)\)")
BB_RE = re.compile(r";;\s+-- basic block number (\d+) from (\d+) to (\d+) --")

FIRST_PSEUDO = 76  # mips 2.7.2-cdk / 2.8.x


def insn_patterns(dump):
    """uid -> (kind, pattern text) for the LAST function in a dump (sched dumps hold one)."""
    out = {}
    lines = dump.splitlines()
    i = 0
    while i < len(lines):
        m = INSN_RE.match(lines[i])
        if m:
            uid = int(m.group(2))
            buf = [lines[i]]
            i += 1
            while i < len(lines) and not lines[i].startswith("(") and lines[i].strip() != "":
                buf.append(lines[i])
                i += 1
            out[uid] = (m.group(1), "\n".join(buf))
            continue
        i += 1
    return out


def set_counts(dump):
    """regno -> [ (uid, kind, how) ] over every insn pattern of the dump (notes excluded)."""
    counts = collections.defaultdict(list)
    for uid, (kind, pat) in insn_patterns(dump).items():
        body = pat.split("(expr_list:REG_")[0] if "(expr_list:REG_" in pat else pat
        # the insn header `(insn 8 6 20 (set ...` : strip the first 4 tokens
        for m in SET_RE.finditer(body):
            regno = int(m.group(3) or m.group(5))
            how = m.group(1) + ("" if m.group(2) else "/" + m.group(4))
            counts[regno].append((uid, kind, how))
    return counts


def dest_of(pat):
    m = SET_RE.search(pat)
    if not m:
        return None, None
    return int(m.group(3) or m.group(5)), (m.group(1) + ("" if m.group(2) else "/" + m.group(4)))


def boosts(sched):
    """per block: {tick: (picked, [(uid, prio)], )} and the set of uids seen at 0x7f000001."""
    blocks = []
    cur = None
    for line in sched.splitlines():
        m = BB_RE.match(line)
        if m:
            cur = {"bb": int(m.group(1)), "head": int(m.group(2)), "tail": int(m.group(3)), "ticks": []}
            blocks.append(cur)
            continue
        m = READY_RE.match(line)
        if m and cur is not None:
            ready = [(int(u), int(p, 16)) for u, p in PRIO_RE.findall(m.group(2))]
            now = [int(x) for x in m.group(3).split()]
            cur["ticks"].append((int(m.group(1)), ready, now[0] if now else None))
    return blocks


def short(pat, width=110):
    s = " ".join(pat.split())
    s = re.sub(r"^\((?:insn|call_insn|jump_insn) \d+ \d+ \d+ ", "", s)
    s = s.split(" (expr_list:REG_")[0]
    s = re.sub(r"\s*-1 \(nil\)\s*$", "", s)
    s = re.sub(r"\s*\d+ \{[^}]*\}.*$", "", s)
    return s if len(s) <= width else s[:width - 1] + "…"


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("fixture")
    ap.add_argument("--row", default="dungeon/func_800A1020")
    ap.add_argument("--cfg")
    ap.add_argument("--all-regs", action="store_true", help="print hard registers too")
    ap.add_argument("--quiet", action="store_true")
    a = ap.parse_args()
    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row)
    if a.cfg:
        row = kitlib.row_at_cfg(row, a.cfg)
    text = Path(a.fixture).read_text()
    d = kitlib.dumps(row, text, want=None)
    stem = Path(a.fixture).stem
    outdir = Path(lane) / "tmp" / "fx" / stem
    outdir.mkdir(parents=True, exist_ok=True)
    if d is None or d.get("error"):
        print("BUILD FAIL", (d or {}).get("error"))
        return 1
    for k, v in d.items():
        if k != "error" and v is not None:
            (outdir / ("%s.%s" % (stem, "s" if k == "asm" else k))).write_text(v)
    flow = set_counts(d.get("flow", ""))
    comb = set_counts(d.get("combine", ""))
    sched = d.get("sched", "")
    pats = insn_patterns(sched)
    print("# %s  at %s  (dumps in %s)" % (a.fixture, row["cfg"], outdir))
    print("## reg_n_sets: flow -> combine (what sched1 reads)")
    regs = sorted(set(flow) | set(comb))
    for r in regs:
        if r < FIRST_PSEUDO and not a.all_regs:
            continue
        f, c = flow.get(r, []), comb.get(r, [])
        tag = ""
        if r >= FIRST_PSEUDO:
            tag = "  <- single-set" if len(c) == 1 else "  <- multi-set" if len(c) > 1 else ""
        print("  reg %-4d flow %d  combine %d  %s%s" % (r, len(f), len(c),
              " ".join("%s@%d%s" % (how, uid, "" if kind == "insn" else "/" + kind) for uid, kind, how in c), tag))
    print("## sched1 boosts (dynamic priority 0x7f000001 in a ready list)")
    for b in boosts(sched):
        boosted = {}
        losers = {}
        for tick, ready, picked in b["ticks"]:
            for uid, p in ready:
                if p == 0x7f000001:
                    boosted.setdefault(uid, tick)
                elif any(q == 0x7f000001 for _, q in ready):
                    losers.setdefault(uid, (tick, p))
        if not boosted and a.quiet:
            continue
        print("  block %d (%d..%d): %d insns, boosted %s" % (b["bb"], b["head"], b["tail"], len(b["ticks"]),
              sorted(boosted) or "-"))
        for uid in sorted(boosted):
            pat = pats.get(uid, ("?", "?"))[1]
            dr, how = dest_of(pat)
            print("    BOOST  uid %-4d T-%-3d dest %s (%s, combine sets %d)  %s" % (
                uid, boosted[uid], dr, how, len(comb.get(dr, [])), short(pat)))
        for uid in sorted(losers):
            pat = pats.get(uid, ("?", "?"))[1]
            dr, how = dest_of(pat)
            print("    ready  uid %-4d T-%-3d prio %-3d dest %s (%s, combine sets %s)  %s" % (
                uid, losers[uid][0], losers[uid][1], dr, how, len(comb.get(dr, [])) if dr is not None else "-", short(pat)))
    return 0


if __name__ == "__main__":
    sys.exit(main())
