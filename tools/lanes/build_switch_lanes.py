#!/usr/bin/env python3
"""Build codex packs of computed-goto switch rows: the 317 src files that spell a `switch` as
`goto *D_XXXXXXXX[value];` through an extern table plus a label-array scaffold.

    python3 tools/lanes/build_switch_lanes.py [--pool ROWS.txt] [--per 10] [--model sol|astra|luna]
                                              [--no-verify] [--repack] LANE...
    python3 tools/lanes/build_switch_lanes.py                 # no lane: print the pool and its stats

The workaround exists only because our assembler front end (maspsx) rewrote a COMPILER-LOCAL
(`$L...`) jump-table indexed load into a 5-word base-materialised sequence where retail (and genuine
ASPSX 2.56/2.67/2.79) has GNU as's 4-word `$at` macro -- `work/maspsx_jtbl/REPORT.md`. A global
table (`goto *D_...[v]`) dodges the pass, at the cost of an extern table, a `&&label` array
(`state_labels`/`action_labels`/`case_labels`/`jt_keep`/`dispatch_labels`/`kind_labels`/
`phase_labels`/`keepalive`/`switch_keepalive`/`switch_keep`/`reachable_arms`) and, on 62 rows,
`ASM_REG("$5")`/`("$6")` pins on the dispatch value. With the pass fixed to a no-op, an honest
`switch (value) { case 0: ... }` reproduces retail: at 2.6.3/2.7.2/2.7.2-cdk gcc emits the macro
form directly, and at 2.8.0/2.8.1 it needs `-mno-split-addresses` in the row's cfg (a cell change
under tools/pin_cells_land.py rules 1-2). Four landed rows are already real switches with zero
pins: town/func_8080F4A4, town/func_808109A4, town/func_80811C54, town/func_80813E14.

Pool (default: every src file whose CODE contains `goto *`, matched to a row), sorted:
rows carrying an `ASM_REG("$5")`/`("$6")` dispatch pin first, then by live pin count descending,
then 2.6.3/2.7.x cells before 2.8.x (then 2.91.66), then by id. Each lane gets base/ (current src
text + .base_sha), out/, rows.md (per row: cell, the table symbol(s), the label array and its
entries in table order, the case count, the pin sites per macro, the dispatch pins, the bounds
guard, and for 2.8.x the exact cfg to write into out_cell/<name>.c.cfg), BRIEF.md
(tools/lanes/switch_lane_brief.md) and PROMPT.txt; launch with tools/lanes/launch_lane.sh <lane>.
"""
import argparse
import collections
import hashlib
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path
from pin_census import sites_of
from served import served_rows, assert_unserved

R = {r["id"]: r for r in rows()}

# `goto *EXPR;` in code (comments blanked first).  19 rows dispatch twice.
GOTO_RE = re.compile(r"goto\s*\*[^;]*;")
# the label-array scaffold; `static void *const N[]`, `static void *volatile N[13]`, with or
# without __attribute__((used)), possibly inside `#ifndef NON_MATCHING` / `#ifdef __mips__`
ARR_RE = re.compile(r"static\s+(?:const\s+|volatile\s+)*void\s*\*\s*(?:const\s+|volatile\s+)*"
                    r"([A-Za-z_]\w*)\s*\[[^\]\n]*\]\s*(?:__attribute__\s*\(\(.*?\)\)\s*)?=\s*\{(.*?)\}\s*;", re.S)
ENTRY_RE = re.compile(r"&&(\w+)")
GLOBAL_TABLE_RE = re.compile(r"\b(D_[0-9A-Fa-f]{8}|jtbl_\w+)\b")
INDEXED_RE = re.compile(r"\b([A-Za-z_]\w*)\s*\[")
KEYWORDS = {"void", "goto", "const", "volatile", "unsigned", "signed", "int", "long", "short", "char",
            "u8", "s8", "u16", "s16", "u32", "s32", "f32"}
# a bounds guard immediately before the dispatch: the switch emits its own sltiu
GUARD_RE = re.compile(r"if\s*\([^;{}]*\)\s*\{?\s*goto\s+\w+\s*;\s*\}?")
CMT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
DISPATCH_REGS = {"5", "6", "a1", "a2"}
CELL_RANK = {"2.6.3": 0, "2.7.2": 0, "2.7.2-cdk": 0, "2.8.0": 1, "2.8.1": 1}
SPLIT_CELLS = ("2.8.0", "2.8.1")
MNOSPLIT = "-mno-split-addresses"


def blank_comments(text):
    """Comments replaced by same-length blanks: offsets and line numbers stay put."""
    return CMT_RE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def line_of(text, pos):
    return text.count("\n", 0, pos) + 1


def one_line(s):
    return re.sub(r"\s+", " ", s).strip()


def arrays(code):
    """[(name, [entry labels in table order], line)] for every label array."""
    out = []
    for m in ARR_RE.finditer(code):
        entries = ENTRY_RE.findall(m.group(2))
        if entries:
            out.append((m.group(1), entries, line_of(code, m.start())))
    return out


def parse_goto(stmt):
    """`goto *D_80170838[kind];` -> (['D_80170838'], 'kind'); a dispatch through a variable names
    the variable (its `extern void *X[]` declaration is in the file)."""
    body = stmt[stmt.index("*") + 1:].rstrip(";").strip()
    m = re.search(r"\[(.*)\]", body)
    index = m.group(1).strip() if m else None
    tabs = list(dict.fromkeys(GLOBAL_TABLE_RE.findall(body)))
    m2 = INDEXED_RE.search(body)
    if m2 and m2.group(1) not in tabs and m2.group(1) not in KEYWORDS:
        tabs.append(m2.group(1))
    if not tabs:
        tabs = [w for w in dict.fromkeys(re.findall(r"\b[A-Za-z_]\w*\b", body)) if w not in KEYWORDS]
    return tabs, index


def dispatches(code, text):
    """[(line, statement, [table symbols], index expr, guard or None)] for every `goto *` in code."""
    out = []
    for m in GOTO_RE.finditer(code):
        stmt = one_line(m.group(0))
        tabs, index = parse_goto(stmt)
        head = code[max(0, m.start() - 400):m.start()]
        g = None
        for gm in GUARD_RE.finditer(head):
            if not one_line(head[gm.end():]):        # the guard is the statement right before
                g = one_line(gm.group(0))
        out.append((line_of(code, m.start()), stmt, tabs, index, g))
    return out


def reg_sites(text, sites):
    """[(line, register, declaration)] for the ASM_REG pins."""
    out = []
    for kind, macro, arg, start, end, line, _ in sites:
        if kind == "reg":
            out.append((line, arg, one_line(text[start:end])))
    return out


def info_of(rid, text, a):
    """Per-row facts, or (None, reason)."""
    code = blank_comments(text)
    if "goto *" not in code:
        return None, "`goto *` only in a comment"
    arrs = arrays(code)
    disp = dispatches(code, text)
    if not disp:
        return None, "no `goto *` statement"
    if not arrs and not any("[" in d[1] for d in disp):
        return None, "not a table dispatch (%s)" % disp[0][1]
    ncases = sum(len(e) for _, e, _ in arrs)
    if ncases > a.max_cases:
        return None, "%d cases > --max-cases %d" % (ncases, a.max_cases)
    if len(text) > a.max_text:
        return None, "%d B of C > --max-text %d" % (len(text), a.max_text)
    sites = sites_of(text)
    regs = reg_sites(text, sites)
    macros = collections.Counter(s[1] for s in sites)
    d56 = [x for x in regs if x[1] in DISPATCH_REGS]
    r = R[rid]
    cell = r["cell"]
    newcfg = None
    if cell in SPLIT_CELLS and MNOSPLIT not in r["cfg"]:
        newcfg = r["cfg"] + " " + MNOSPLIT
    # the owner's cap: at most two optimization flags per row (a glued -G0 is not one of them,
    # tools/pin_cells_scan.py stacked())
    nflags = len([t for t in r["cfg"].replace("+", " ").split()[1:] if t.startswith(("-f", "-O", "-m"))])
    return dict(rid=rid, row=r, arrays=arrs, disp=disp, ncases=ncases, sites=sites, regs=regs, nflags=nflags,
                macros=macros, d56=d56, newcfg=newcfg, mips_ifdef="__mips__" in code,
                nonmatching="NON_MATCHING" in code, ncode=len(text)), None


def render(info):
    r, rid = info["row"], info["rid"]
    L = ["## %s" % rid,
         "- cell `%s`, %s B retail, `src/%s.c`, %d live pin sites, %d B of C"
         % (r["cfg"], r.get("size"), rid, len(info["sites"]), info["ncode"])]
    for line, stmt, tabs, index, guard in info["disp"]:
        via = "" if any(GLOBAL_TABLE_RE.fullmatch(t) for t in tabs) else \
            " (no `D_`/`jtbl_` symbol here: the table is reached through a variable -- find its `extern void *X[]` declaration)"
        L.append("- dispatch at line %d: `%s` -- table symbol(s) %s, index expression `%s`%s"
                 % (line, stmt, ", ".join("`%s`" % s for s in tabs) or "unknown", index or "?", via))
        if guard:
            L.append("  - bounds guard right before it: `%s` (delete it: the switch emits its own `sltiu`; its target becomes `default:`)" % guard)
    for name, entries, line in info["arrays"]:
        cases = ", ".join("%d=%s" % (i, e) for i, e in enumerate(entries))
        L.append("- label array `%s` at line %d, %d entries (case order): %s" % (name, line, len(entries), cases))
        dup = [e for e, n in collections.Counter(entries).items() if n > 1]
        if dup:
            L.append("  - repeated target(s) %s: every index that names the block gets its own `case N:` on it"
                     % ", ".join("`%s`" % d for d in dup))
    if not info["arrays"]:
        L.append("- no label array in this row: read the table's entries from the retail `.rdata` / `--diff` listing")
    L.append("- pin sites: %d (%s)" % (len(info["sites"]), ", ".join("%s %d" % kv for kv in sorted(info["macros"].items())) or "none"))
    if info["regs"]:
        L.append("- register pins: " + ", ".join("$%s@%d" % (x[1], x[0]) for x in info["regs"]))
    for line, reg, decl in info["d56"]:
        L.append("  - `$%s` pin at line %d: `%s` -- the family's `$5`/`$6` pins are the dispatch-argument pins the "
                 "switch spelling retires; check what this one holds and try erasing it once the switch is exact"
                 % (reg, line, decl))
    if info["mips_ifdef"]:
        L.append("- carries `#ifdef __mips__`: if the `#else` arm already holds a real `switch`, the rewrite is "
                 "to drop the `#ifdef` and keep that arm (check it reads the same dispatch value)")
    if info["nonmatching"]:
        L.append("- carries a `NON_MATCHING` arm: never edit it; a label array wrapped in `#ifndef NON_MATCHING` "
                 "goes away with the `#ifndef`/`#endif` pair")
    if info["newcfg"]:
        L.append("- **2.8.x cell**: gcc splits the table address itself here. Add `%s`; the cfg to write into "
                 "`out_cell/%s.c.cfg` is exactly `%s` (rules 1-2 in BRIEF.md)" % (MNOSPLIT, rid.split("/")[1], info["newcfg"]))
        if info["nflags"] >= 2:
            L.append("  - but this row already carries %d optimization flags: adding one more breaks the owner's "
                     "two-flag cap. Measure it and report it; write no `.cfg`" % info["nflags"])
    elif r["cell"] not in CELL_RANK:
        L.append("- cell `%s` is outside the family's measured cells: split-addresses behaviour unknown, "
                 "measure before assuming (report what you find)" % r["cell"])
    return "\n".join(L) + "\n"


def stats(pool):
    cells = collections.Counter(p["row"]["cell"] for p in pool)
    macros = collections.Counter()
    for p in pool:
        macros.update(p["macros"])
    return ("pool %d rows | by cell: %s | with a $5/$6 dispatch pin: %d | pin-free rows: %d | "
            "pin sites %d (%s) | cases %d"
            % (len(pool), ", ".join("%s %d" % kv for kv in sorted(cells.items())),
               sum(1 for p in pool if p["d56"]), sum(1 for p in pool if not p["sites"]),
               sum(macros.values()), ", ".join("%s %d" % kv for kv in sorted(macros.items())),
               sum(p["ncases"] for p in pool)))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="*")
    ap.add_argument("--pool", help="file of row ids (first field per line); default: every src file with a `goto *`")
    ap.add_argument("--per", type=int, default=10)
    ap.add_argument("--model", default="sol")
    ap.add_argument("--no-verify", action="store_true", help="skip the base-is-exact check (a landing gate is running)")
    ap.add_argument("--repack", action="store_true", help="admit rows already served by a lane (retry packs)")
    ap.add_argument("--dry-run", action="store_true", help="print the pack composition and the stats; write nothing")
    ap.add_argument("--max-cases", type=int, default=40, help="size guard: skip rows with more label-array entries")
    ap.add_argument("--max-text", type=int, default=40000, help="size guard: skip rows whose C is larger")
    a = ap.parse_args()

    if a.pool:
        ids = [l.split()[0] for l in open(a.pool) if l.strip() and not l.startswith("#")]
    else:
        ids = []
        for f in sorted((ROOT / "src").glob("*/*.c")):
            t = f.read_text(errors="replace")
            if "goto *" in t:
                ids.append("%s/%s" % (f.parent.name, f.stem))
    packed = set()
    for f in (ROOT / "work/native_lane").glob("sw*/base/*/*.c"):
        packed.add(f.parent.name + "/" + f.stem)
    served = served_rows()
    nserved = 0

    pool, skipped = [], []
    for rid in ids:
        if rid not in R or not clean_path(R[rid]).exists():
            skipped.append((rid, "unknown row or missing file")); continue
        if rid in packed and not a.repack:
            skipped.append((rid, "already packed")); continue
        if rid in served:
            nserved += 1
            if not a.repack:
                skipped.append((rid, "served by an earlier lane")); continue
        text = clean_path(R[rid]).read_text(errors="replace")
        info, why = info_of(rid, text, a)
        if info is None:
            skipped.append((rid, why)); continue
        info["text"] = text
        pool.append(info)

    if not a.no_verify:
        from verify import verify
        with ThreadPoolExecutor(max_workers=3) as ex:
            ok = list(ex.map(lambda p: bool(verify(p["row"], clean_path(p["row"])).get("exact")), pool))
        bad = [p["rid"] for p, o in zip(pool, ok) if not o]
        pool = [p for p, o in zip(pool, ok) if o]
        if bad:
            print("base not exact, dropped:", bad)

    pool.sort(key=lambda p: (0 if p["d56"] else 1, -len(p["sites"]),
                             CELL_RANK.get(p["row"]["cell"], 2), p["rid"]))
    if not a.dry_run:
        (ROOT / "work/native_lane").mkdir(parents=True, exist_ok=True)
        # tab separated (a cfg holds spaces); --pool reads the first field of each line.  This is the
        # pool THIS run would pack: rows already in a sw* pack are absent unless --repack.
        (ROOT / "work/native_lane/sw_pool.txt").write_text(
            "# id\tcfg\tlive pins\tcases\tdispatch pin\n" + "".join("%s\t%s\t%d pins\t%d cases\t%s\n" % (p["rid"], p["row"]["cfg"], len(p["sites"]), p["ncases"],
                                                         "$5/$6" if p["d56"] else "-") for p in pool))
    print(stats(pool) + " | served by an earlier lane: %d" % nserved)

    brief = (ROOT / "tools/lanes/switch_lane_brief.md").read_text()
    i = 0
    for name in a.lanes:
        chunk = pool[i:i + a.per]; i += a.per
        if not chunk:
            print(name, "no rows left"); continue
        assert_unserved([p["rid"] for p in chunk], a.repack)    # never re-serve a row by accident
        if a.dry_run:
            print(name, len(chunk), "rows (dry run, nothing written):",
                  ", ".join(p["rid"] for p in chunk))
            continue
        L = ROOT / "work/native_lane" / name
        assert not (L / "last_message.txt").exists(), name
        (L / "out").mkdir(parents=True, exist_ok=True)
        md = ["# Rows (computed-goto dispatches to rewrite as real switches)\n"]
        for info in chunk:
            md.append(render(info))
            cont, nm = info["rid"].split("/")
            (L / "base" / cont).mkdir(parents=True, exist_ok=True)
            (L / "base" / cont / (nm + ".c")).write_text(info["text"])
            (L / "base" / cont / (nm + ".c.base_sha")).write_text(hashlib.sha256(info["text"].encode()).hexdigest() + "\n")
        (L / "rows.md").write_text("\n".join(md))
        b = (brief.replace("@ROOT@", str(ROOT)).replace("@LANE@", name).replace("@NROWS@", str(len(chunk)))
             .replace("@HOME@", str(Path.home())).replace("@MODEL@", a.model))
        (L / "BRIEF.md").write_text(b)
        (L / "PROMPT.txt").write_text(
            f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; gcc -da writes its "
            f"dumps into the current directory, and lanes have left dozens of dump files at the repo root.\n"
            f"Read work/native_lane/{name}/BRIEF.md and follow it exactly. Work only inside work/native_lane/{name}/ "
            f"and never write files at the repo root. Never add ASM_* macros, __asm__, volatile, fake dependencies, "
            f"one-trip blocks or maspsx flags. When done, end with one line per row: row, result, the table symbol(s) "
            f"and case count, the cell change if any, pins before -> after, and what did not work.\n")
        print(name, len(chunk), "rows:", ", ".join(p["rid"] for p in chunk))
    for s in skipped:
        print("skipped", s)


if __name__ == "__main__":
    main()
