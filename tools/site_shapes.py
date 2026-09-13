#!/usr/bin/env python3
"""Site-shape census: every live pin site keyed by (macro, normalised neighbourhood), ranked by sites.

    python3 tools/site_shapes.py [--context 1] [--top 40] [--family KEEP] [--examples 4] [--json OUT]

Round 24 (2026-09-13). Every generator that paid in rounds 19-23 (t16b, t57, t57b, t59) came from a site
shape that recurred, found by an ad-hoc census; this ranks the recurring shapes over the whole tree at once.
A site's shape is its line and CONTEXT non-blank lines either side, comments and casts dropped, the pinned
variable spelled V, other identifiers I (keywords, base types and pin macros kept), numbers N. A register
pin's line is its variable's first assignment after the declaration (the declaration itself says nothing).
Facts measured by the t53 (REG) and t53k (KEEP) sweeps (class at combine, first wiring difference, the
lone erasure's assembly residue) are joined where the row is unchanged since the journal measured it.
CPU only, no compiles: a map of where the next generator is, never evidence that a shape is removable.
"""
import argparse
import collections
import hashlib
import json
import re
import statistics
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows
from pin_census import sites_of

KEEPWORDS = set("""if else for while do return goto switch case default break continue sizeof struct union enum
    const volatile unsigned signed register static extern void char short int long float double
    s8 u8 s16 u16 s32 u32 s64 u64 f32 f64 V I N abs""".split())
TYPES = r"(?:s8|u8|s16|u16|s32|u32|s64|u64|f32|f64|int|char|short|long|void|unsigned(?:\s+(?:char|short|int|long))?|signed(?:\s+(?:char|short|int|long))?)"
CAST = re.compile(r"\(\s*(?:(?:const|volatile)\s+)*(?:(?:struct|union)\s+)?(?:%s\s*\**|[A-Za-z_]\w*\s*\*+)\s*\)" % TYPES)
COMMENT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
IDENT = re.compile(r"\b[A-Za-z_]\w*\b")
NUM = re.compile(r"\b(?:0[xX][0-9A-Fa-f]+|\d+)[uUlL]*\b")


def family(macro):
    if macro.startswith("ASM_REG"):
        return "REG"
    if macro.startswith("ASM_KEEP"):
        return "KEEP"
    if macro in ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER"):
        return "FENCE"
    if macro.startswith("ASM_USE"):
        return "USE"
    if macro.startswith("ASM_TAILSLOT"):
        return "TAILSLOT"
    return "OTHER"


def mask(text):
    return COMMENT.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def norm(line, var):
    s = CAST.sub("", line)
    if var:
        s = re.sub(r"\b%s\b" % re.escape(var), "V", s)
    s = IDENT.sub(lambda m: m.group(0) if m.group(0) in KEEPWORDS or m.group(0).startswith("ASM_") else "I", s)
    s = NUM.sub("N", s)
    return re.sub(r"\s+", " ", s).strip()


def pinned_var(site):
    if site[1].startswith("ASM_REG"):
        ids = IDENT.findall(site[6] or "")
        return ids[-1] if ids else None
    m = IDENT.search(site[2] or "")
    return m.group(0) if m and not m.group(0).startswith('"') else None


def journal(name):
    out = {}
    p = ROOT / "ledger/sweeps" / name
    if p.exists():
        for line in open(p):
            d = json.loads(line)
            if d.get("sites"):
                out[d["id"]] = d
    return out


def shapes(ctx):
    j = {**journal("t53_reg_state.jsonl"), **{}}
    jk = journal("t53k_keep.jsonl")
    res = []
    for r in rows():
        p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        ss = sites_of(text)
        if not ss:
            continue
        sha = hashlib.sha256(text.encode()).hexdigest()
        lines = mask(text).split("\n")
        body = [i for i, l in enumerate(lines) if l.strip()]
        pos = {i: n for n, i in enumerate(body)}
        facts = {}
        for jj in (j, jk):
            d = jj.get(r["id"])
            if d and d.get("in_sha") == sha:
                for s in d["sites"]:
                    facts.setdefault(s["site"], s)
        for si, s in enumerate(ss):
            var = pinned_var(s)
            li = s[5] - 1
            if s[1].startswith("ASM_REG") and var:
                for k in range(li + 1, len(lines)):   # first plain assignment of the variable after the declaration
                    if re.search(r"(?<![.>\w])\b%s\s*=(?!=)" % re.escape(var), lines[k]):
                        li = k
                        break
            if li not in pos:
                continue
            n = pos[li]
            ctxl = [lines[i] for i in body[max(0, n - ctx):n + ctx + 1]]
            f = facts.get(si) or {}
            res.append({"id": r["id"], "site": si, "line": li + 1, "macro": s[1], "family": family(s[1]),
                        "shape": " | ".join(norm(l, var) for l in ctxl), "npins": len(ss),
                        "cls": f.get("cls"), "first": (f.get("first") or {}).get("abs"), "asm": f.get("asm")})
    return res


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--context", type=int, default=1)
    ap.add_argument("--top", type=int, default=40)
    ap.add_argument("--family")
    ap.add_argument("--examples", type=int, default=4)
    ap.add_argument("--json")
    a = ap.parse_args()
    res = shapes(a.context)
    if a.json:
        with open(a.json, "w") as fo:
            for x in res:
                fo.write(json.dumps(x) + "\n")
    fams = collections.Counter(x["family"] for x in res)
    print(len(res), "sites;", dict(fams.most_common()))
    groups = collections.defaultdict(list)
    for x in res:
        if not a.family or x["family"] == a.family:
            groups[(x["macro"], x["shape"])].append(x)
    ranked = sorted(groups.items(), key=lambda kv: -len(kv[1]))
    tot = sum(len(v) for v in groups.values())
    for k in (10, 30, 100):
        print("top %d shapes cover %d of %d sites (%.0f%%)" % (k, sum(len(v) for _, v in ranked[:k]), tot,
                                                               100.0 * sum(len(v) for _, v in ranked[:k]) / max(tot, 1)))
    print("distinct shapes", len(ranked), "; singletons", sum(1 for _, v in ranked if len(v) == 1))
    for (macro, shape), v in ranked[:a.top]:
        cls = collections.Counter(x["cls"] for x in v if x["cls"])
        res_ = [x["asm"] for x in v if x["asm"] is not None]
        print("\n%4d sites %4d rows  %s  cls %s  residue median %s" % (
            len(v), len({x["id"] for x in v}), macro, dict(cls.most_common(3)),
            statistics.median(res_) if res_ else "-"))
        print("     " + shape[:300])
        print("     e.g. " + ", ".join("%s:%d" % (x["id"], x["line"]) for x in sorted(v, key=lambda x: x["npins"])[:a.examples]))


if __name__ == "__main__":
    main()
