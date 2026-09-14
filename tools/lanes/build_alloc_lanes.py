#!/usr/bin/env python3
"""Build luna allocation lanes (round 25's recipe): each row's register pins carry the allocator decision the
alloc_astra lane observed inside the stock compiler, translated into the C lever it names.

    python3 tools/lanes/build_alloc_lanes.py [--per 12] [--no-verify] [--traces DIR] alloc1 alloc2 alloc3 alloc4

Source of the diagnoses: `work/native_lane/alloc_astra/` (REPORT.md "Mechanism per allocator input",
"Population coverage and input taxonomy", "Deciding-pass evidence"). The per-row traces live in
`scratch/trace_population/<container>_<func>.json`: per pin site, the quantity or allocno the pinned value
becomes (refs, live interval, calls crossed, preferences, conflicts/occupied registers, priority) and the
reason the allocator gave that site a different register without the pin. `--traces DIR` reads that same
per-row format from another directory instead (e.g. rows re-traced with tools/alloc_trace.py, whose
always-on find_reg reading resolves sites the lane left coarse); the held-out lists stay in the lane's
directory either way.

SITE INDEX (measured, not assumed): a trace record's `site` indexes the FULL `pin_census.sites_of(text)` list
of the snapshot text, not the ASM_REG subset - the full-list reading agrees with the record's own `hard`
register on 2,352 of 2,358 sites, the reg-only reading on 1,787. The builder re-checks `hard` against the
pinned register spelling at that index and drops any row where a site disagrees, so a silently reindexed row
cannot reach a lane.

Pool: rows whose current `src/` sha still equals the trace snapshot sha (14 rows drifted, the t61 sweep among
them), not in either held-out list, with no live fence site, at most 3 pin sites in total, and with EVERY
ASM_REG site carrying at least one specific reason (anything but `global-competition-or-scan-unresolved`).
Rows are then cut into strata by the allocator reason, one or two per pack, and the first matching pack wins.
`hard-register-scan-order` and `global-scan-order-or-class` are deliberately NOT strata: the allocator simply
took the first free register there and no C lever is named.

The four confirmed unsuggested equal-priority local ties (REPORT "Five-cell fixtures") are appended to the
last pack regardless of pin count and flagged, and are held out of the earlier packs so they land there only.

Each lane gets base/, out/, rows.md, BRIEF.md (tools/lanes/alloc_lane_brief.md) and PROMPT.txt; launch with
tools/lanes/launch_lane.sh. Built in round 25, after tools/lanes/build_keep_lanes.py.
"""
import argparse
import collections
import hashlib
import json
import re
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, sha_text
from pin_census import sites_of
from verify import verify

ALLOC = ROOT / "work/native_lane/alloc_astra"
TRACES = ALLOC / "scratch/trace_population"
HELDOUT = ("heldout_h1_census_rows.txt", "heldout_h2_population_rows.txt")
UNRESOLVED = "global-competition-or-scan-unresolved"
FENCES = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")

# One or two reasons per pack, in order; a row goes to the FIRST pack whose stratum it matches.
STRATA = [
    ("alloc1", ["global-hard-conflict"]),
    ("alloc2", ["suggestion-selection", "other-global-preference",
                "global-preference-selection", "global-copy-preference-selection"]),
    ("alloc3", ["call-clobber-exclusion", "earlier-quantity-conflict",
                "preexisting-hard-conflict", "preexisting-hard-or-local-conflict", "earlier-global-conflict"]),
    ("alloc4", ["pseudo-eliminated-before-allocation", "target-register-already-selected"]),
]
TIE_PACK = "alloc4"
# The only confirmed unsuggested equal-priority local-conflict events in the population (REPORT.md).
TIES = [("town/func_8047E1C0", 0), ("dungeon/func_8199A800", 5),
        ("dungeon/func_819835AC", 8), ("dungeon/func_800C29F0", 0)]

REASON_TEXT = {
    "global-hard-conflict":
        "retail's register is held by another value that is live at the same time as this one (the conflict "
        "list names it); the overlap has to end: split or shorten the other value's lifetime, or move this "
        "value's definition or last use",
    "suggestion-selection":
        "the allocator chose by a preference from a copy to or from a hard register (a call argument, a return "
        "value, an arithmetic tie) that the pinned build lacks or has elsewhere: change which value is staged "
        "into the argument or return register, or fuse/split the copy",
    "other-global-preference":
        "the allocator chose by a preference from a copy to or from a hard register (a call argument, a return "
        "value, an arithmetic tie) that the pinned build lacks or has elsewhere: change which value is staged "
        "into the argument or return register, or fuse/split the copy",
    "global-preference-selection":
        "the allocator chose by a preference from a copy to or from a hard register (a call argument, a return "
        "value, an arithmetic tie) that the pinned build lacks or has elsewhere: change which value is staged "
        "into the argument or return register, or fuse/split the copy",
    "global-copy-preference-selection":
        "the allocator chose by a preference from a copy to or from a hard register (a call argument, a return "
        "value, an arithmetic tie) that the pinned build lacks or has elsewhere: change which value is staged "
        "into the argument or return register, or fuse/split the copy",
    "call-clobber-exclusion":
        "the value's lifetime crosses a call, so caller-saved registers are excluded and it competes for saved "
        "ones: end the lifetime before the call or start it after (a real use moved, a copy sunk)",
    "earlier-quantity-conflict":
        "an earlier local quantity already holds the register when this one is born: lifetimes overlap; split "
        "or reorder the earlier value's definition and death",
    "preexisting-hard-conflict":
        "an earlier local quantity already holds the register when this one is born: lifetimes overlap; split "
        "or reorder the earlier value's definition and death",
    "preexisting-hard-or-local-conflict":
        "an earlier local quantity already holds the register when this one is born: lifetimes overlap; split "
        "or reorder the earlier value's definition and death",
    "earlier-global-conflict":
        "an earlier local quantity already holds the register when this one is born: lifetimes overlap; split "
        "or reorder the earlier value's definition and death",
    "pseudo-eliminated-before-allocation":
        "without the pin the value is coalesced or substituted away before allocation, so nothing competes for "
        "the register: keep a real separate value alive (a lifetime split, a copy kept by a later real use) as "
        "t51's split does",
    "target-register-already-selected":
        "an earlier allocation already took retail's register: change which earlier value gets it (its "
        "priority, refs or lifetime)",
    "already-used-register-selection":
        "global allocation preferred a register already in use in this function over retail's free one: change "
        "which registers the earlier real values occupy",
    "fixed-register-exclusion":
        "retail's register is fixed (reserved by the ABI or the compiler) at this point, so the allocator could "
        "never hand it out here: the value has to be born or die somewhere else",
    "global-fixed-or-frame-exclusion":
        "retail's register is excluded as fixed or as the frame pointer for this allocno: the lifetime or the "
        "frame usage has to change, not the priority",
    "lower-priority-preference-reservation":
        "the register is held back for a lower-priority value's preference: change that other value's copy or "
        "staging so it no longer prefers this register",
    "no-successful-global-attempt":
        "the value got no successful global attempt at all (it was spilled or never reached allocation): give "
        "it a shorter, simpler lifetime before asking which register it wins",
    "hard-register-scan-order":
        "the allocator simply took the first free register in scan order - no lever is named by this reason "
        "alone; look at the other sites and at what makes retail's register unavailable",
    "global-scan-order-or-class":
        "the choice follows scan order within the register class - no lever is named by this reason alone",
    UNRESOLVED:
        "the global competition was not resolved to a single cause by the tracer: the inputs above are still "
        "exact, but the deciding step is unknown",
}

REG_NAMES = {0: "zero", 1: "at", 2: "v0", 3: "v1", 4: "a0", 5: "a1", 6: "a2", 7: "a3",
             8: "t0", 9: "t1", 10: "t2", 11: "t3", 12: "t4", 13: "t5", 14: "t6", 15: "t7",
             16: "s0", 17: "s1", 18: "s2", 19: "s3", 20: "s4", 21: "s5", 22: "s6", 23: "s7",
             24: "t8", 25: "t9", 26: "k0", 27: "k1", 28: "gp", 29: "sp", 30: "fp", 31: "ra"}
NAME_NUM = {v: k for k, v in REG_NAMES.items()}
NAME_NUM["s8"] = 30


def reg_name(n):
    """A hard register number as a name; above 31 it is not a GPR (an FP or frame pseudo)."""
    return "$%d (%s)" % (n, REG_NAMES[n]) if n in REG_NAMES else "non-GPR %d" % n


def reg_num(spelling):
    """The register number an ASM_REG argument names ('4', '$4', 'a0')."""
    s = spelling.lstrip("$")
    return int(s) if s.isdigit() else NAME_NUM.get(s)


def reg_list(ns):
    return ", ".join(reg_name(n) for n in ns) if ns else "none"


def heldout():
    out = set()
    for fn in HELDOUT:
        for line in open(ALLOC / fn):
            if line.strip():
                out.add(line.strip().split()[0])
    return out


def decl_of(site):
    """('T', 'v') from a reg site: sites_of keeps the `register T v` text as the replacement."""
    txt = site[6]
    m = re.search(r"(\w+)\s*$", txt)
    return (txt[:m.start()].strip() or "?", m.group(1)) if m else ("?", "?")


def normalise(entry):
    """One trace reason entry, global (flat) or local (quantity/attempt), in one shape."""
    d = {"owner": entry.get("owner"), "pseudo": entry.get("pseudo"),
         "reasons": list(entry.get("reasons") or []), "function": entry.get("function"),
         "competitors": entry.get("competitors") or []}
    if entry.get("owner") == "global":
        d.update(number="allocno %s (allocation order %s)" % (entry.get("allocno"), entry.get("order")),
                 refs=entry.get("refs"), live="%s instructions" % entry.get("live"),
                 calls=entry.get("calls"), prefs=list(entry.get("preferences") or []),
                 conflicts=list(entry.get("hard_conflicts") or []),
                 conflict_label="hard conflicts", priority=None)
        return d
    q, at = entry.get("quantity") or {}, entry.get("attempt") or {}
    if not q:
        d.update(number="no quantity (eliminated before allocation)", refs=None, live=None, calls=None,
                 prefs=[], conflicts=[], conflict_label="occupied at the attempt", priority=None)
        return d
    d.update(number="local quantity %s in block %s" % (q.get("qty"), entry.get("block")),
             refs=q.get("n_refs"),
             live="birth/death %s/%s (local half-insn numbering, not the flow live length)"
                  % (q.get("birth"), q.get("death")),
             calls=q.get("n_calls_crossed"),
             prefs=list(q.get("phys_sugg") or []) + list(q.get("phys_copy_sugg") or []),
             conflicts=list(at.get("occupied") or []), conflict_label="occupied at the attempt",
             priority=q.get("priority"), result=at.get("result"))
    return d


def row_sites(rid, text, trace):
    """Per ASM_REG site of the current text: (index, site, trace record or None), or None if the trace's
    site index no longer lines up with the text (a reindexed row: its diagnosis would be misattributed)."""
    sites = sites_of(text)
    by_idx = {s["site"]: s for s in trace.get("sites") or []}
    out = []
    for i, s in enumerate(sites):
        if s[0] != "reg":
            continue
        st = by_idx.get(i)
        if st is not None and st.get("hard") is not None and st["hard"] != reg_num(s[2]):
            return None, sites
        out.append((i, s, st))
    return out, sites


def site_reasons(st):
    out = set()
    for e in (st or {}).get("reasons") or []:
        out |= set(e.get("reasons") or [])
    return out


def collect(per_stats, max_pins=3, exclude=(), traces=TRACES):
    """The pool: one record per admissible row, with its per-site traces (read from `traces`)."""
    held, pool = heldout() | set(exclude), []
    R = {r["id"]: r for r in rows()}
    for f in sorted(Path(traces).glob("*.json")):
        trace = json.loads(f.read_text())
        rid = trace.get("id")
        r = R.get(rid)
        per_stats["trace files"] += 1
        if not r or not clean_path(r).exists():
            per_stats["no such row"] += 1
            continue
        text = clean_path(r).read_text(errors="replace")
        if hashlib.sha256(text.encode()).hexdigest() != trace.get("sha"):
            per_stats["source drifted since the trace"] += 1
            continue
        if rid in held:
            per_stats["held out (H1/H2)"] += 1
            continue
        regs, sites = row_sites(rid, text, trace)
        if regs is None:
            per_stats["site index no longer aligns"] += 1
            continue
        rec = {"id": rid, "row": r, "text": text, "sites": sites, "regs": regs,
               "npins": len(sites), "size": r["size"],
               "reasons": set().union(*[site_reasons(st) for _, _, st in regs]) if regs else set()}
        pool.append(rec)
        if any(s[1] in FENCES for s in sites):
            per_stats["live fence site"] += 1
            rec["skip"] = "fence"
            continue
        if len(sites) > max_pins:
            per_stats["more than %d pin sites" % max_pins] += 1
            rec["skip"] = "pins"
            continue
        if not regs:
            per_stats["no ASM_REG site"] += 1
            rec["skip"] = "noreg"
            continue
        bad = [i for i, _, st in regs if not st or not st.get("valid") or not (site_reasons(st) - {UNRESOLVED})]
        if bad:
            per_stats["an ASM_REG site with no specific reason"] += 1
            rec["skip"] = "unspecific"
            continue
        per_stats["POOL"] += 1
    return pool


def render_row(rec, stratum, tie_site):
    r, regs = rec["row"], rec["regs"]
    head = ["## %s%s" % (rec["id"], "  (tie)" if tie_site is not None else ""),
            "- cell `%s`, %d B retail, `src/%s/%s`, %d pin site(s) (%d `ASM_REG`)%s"
            % (r["cfg"], r["size"], r["container"], Path(r["c_path"]).name, rec["npins"], len(regs),
               "; NOTE: this row has a live fence site" if any(s[1] in FENCES for s in rec["sites"]) else ""),
            "- stratum **%s**" % stratum]
    if tie_site is not None:
        head.append("- **confirmed equal-priority local tie at site %d**: two local quantities ask with the "
                    "same priority and no suggestion, and numbering decides. Local quantity numbers follow "
                    "births, not declarations, so a declaration swap alone will not move it." % tie_site)
    body = []
    for i, s, st in regs:
        typ, var = decl_of(s)
        mark = " **<- the stratum site**" if (site_reasons(st) & set(dict(STRATA)[stratum])) else ""
        mark = " **<- the tie site**" if i == tie_site else mark
        body.append("### site %d (line %d): `register %s %s ASM_REG(\"$%s\")` -> %s%s"
                    % (i, s[5], typ, var, s[2], reg_name(reg_num(s[2])) if reg_num(s[2]) is not None
                       else "$" + s[2], mark))
        if not st:
            body.append("- no trace record for this site (the lane traced only part of this row); treat the "
                        "pin as undiagnosed.")
            continue
        if not st.get("valid"):
            body.append("- the trace for this site is not valid (%s); treat the pin as undiagnosed."
                        % (st.get("error") or "no reason given"))
            continue
        body.append("- register class **%s**; %d binding(s) of this variable in the text"
                    % (st.get("register_class"), st.get("bound_count") or 0))
        for e in st.get("reasons") or []:
            d = normalise(e)
            where = "" if not d["function"] or d["function"] == r["func"] else \
                    " (the pin sits in `%s`, not the row's own function)" % d["function"]
            body.append("- **%s** value, pseudo %s, %s%s" % (d["owner"], d["pseudo"], d["number"], where))
            body.append("  - refs %s, live %s, calls crossed %s%s"
                        % (d["refs"], d["live"], d["calls"],
                           ", priority %s" % d["priority"] if d["priority"] is not None else ""))
            body.append("  - preferences: %s" % reg_list(d["prefs"]))
            want = reg_num(s[2])
            holds = (" - retail's %s IS in that set" % reg_name(want)) if want in d["conflicts"] else \
                    (" - retail's %s is NOT in that set" % reg_name(want)) if want is not None else ""
            body.append("  - %s: %s%s" % (d["conflict_label"], reg_list(d["conflicts"]), holds))
            if d.get("result") is not None:
                body.append("  - without the pin the attempt handed out %s" % reg_name(d["result"]))
            for c in d["competitors"]:
                body.append("  - competitor: local quantity %s, priority %s%s%s"
                            % (c.get("qty"), c.get("priority"),
                               ", SAME priority" if c.get("same_priority") else "",
                               ", suggested" if c.get("suggested") else ", unsuggested"))
            for name in d["reasons"]:
                body.append("  - reason `%s`: %s" % (name, REASON_TEXT.get(name, "no translation recorded "
                                                                                 "for this reason")))
    return "\n".join(head + body) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="+", help="pack names, in stratum order: %s"
                                             % ", ".join(n for n, _ in STRATA))
    ap.add_argument("--per", type=int, default=12)
    ap.add_argument("--no-verify", action="store_true", help="do not check each base is exact")
    ap.add_argument("--max-pins", type=int, default=3, help="admit rows with at most this many pin sites (default 3)")
    ap.add_argument("--traces", default=str(TRACES),
                    help="directory of per-row trace files to read (default: the alloc_astra lane's "
                         "scratch/trace_population)")
    ap.add_argument("--exclude", help="file of row ids to leave out (rows already given to a pack); rows under "
                                      "work/native_lane/alloc*/base are always left out")
    ap.add_argument("--as", dest="alias", default="",
                    help="NEW=STRATUM[,NEW=STRATUM...]: build a pack named NEW from STRATUM's rows (alloc1-4 are "
                         "the strata); packs sharing a stratum take successive slices")
    a = ap.parse_args()
    alias = dict(x.split("=") for x in a.alias.split(",") if x)
    for name in a.lanes:
        if alias.get(name, name) not in dict(STRATA):
            ap.error("unknown pack %s (strata are %s)" % (name, ", ".join(n for n, _ in STRATA)))
    exclude = set()
    if a.exclude:
        exclude |= {l.strip() for l in open(a.exclude) if l.strip()}
    for f in (ROOT / "work/native_lane").glob("alloc*/base/*/*.c"):
        exclude.add(f.parent.name + "/" + f.stem)

    stats = collections.Counter()
    pool = collect(stats, a.max_pins, exclude, Path(a.traces))
    live = [p for p in pool if not p.get("skip")]
    tie_ids = {rid for rid, _ in TIES}
    by_id = {p["id"]: p for p in pool}

    # strata, first match wins; the tie rows are reserved for their own pack
    assigned, unstratified = {n: [] for n, _ in STRATA}, []
    for p in sorted(live, key=lambda p: (p["npins"], p["size"], p["id"])):
        if p["id"] in tie_ids:
            continue
        for name, reasons in STRATA:
            if p["reasons"] & set(reasons):
                assigned[name].append(p)
                break
        else:
            unstratified.append(p)
    for name, reasons in STRATA:
        stats["stratum " + name] = len(assigned[name])
    stats["no stratum (scan-order only)"] = len(unstratified)

    verified, failed = {}, []
    if not a.no_verify:
        want, cur = [], collections.Counter()
        for name in a.lanes:
            st = alias.get(name, name)
            want += assigned[st][cur[st]:cur[st] + a.per]; cur[st] += a.per
        want += [by_id[rid] for rid, _ in TIES if rid in by_id and TIE_PACK in a.lanes]
        want = {p["id"]: p for p in want}
        with ThreadPoolExecutor(max_workers=3) as ex:          # the scorer is the shared-disk hog: keep it low
            for rid, v in zip(want, ex.map(lambda p: verify(p["row"], clean_path(p["row"])), want.values())):
                verified[rid] = bool(v.get("exact"))
                if not verified[rid]:
                    failed.append(rid)

    brief = (ROOT / "tools/lanes/alloc_lane_brief.md").read_text()
    built, cur = [], collections.Counter()
    for name in a.lanes:
        st = alias.get(name, name)
        picked = [p for p in assigned[st][cur[st]:cur[st] + a.per] if verified.get(p["id"], True)]; cur[st] += a.per
        ties = []
        if name == TIE_PACK:
            for rid, site in TIES:
                p = by_id.get(rid)
                if p and verified.get(rid, True):
                    ties.append((p, site))
        L = ROOT / "work/native_lane" / name
        assert not (L / "last_message.txt").exists(), name
        (L / "out").mkdir(parents=True, exist_ok=True)
        out = ["# Rows (the allocator decision observed at each register pin; fewest pins first, then "
               "smallest retail size)\n",
               "Site numbers index every `ASM_*` site of the file in source order, as `tools/pin_census.py` "
               "lists them.\n"]
        for p, site in [(p, None) for p in picked] + ties:
            out.append(render_row(p, st, site))
        n = len(picked) + len(ties)
        if not n:
            print(name, "no rows left")
            continue
        (L / "rows.md").write_text("\n".join(out))
        for p, _ in [(p, None) for p in picked] + ties:
            cont, nm = p["id"].split("/")
            (L / "base" / cont).mkdir(parents=True, exist_ok=True)
            (L / "base" / cont / (nm + ".c")).write_text(p["text"])
            (L / "base" / cont / (nm + ".c.base_sha")).write_text(sha_text(p["text"]))
        (L / "BRIEF.md").write_text(brief.replace("@LANE@", name).replace("@NROWS@", str(n))
                                    .replace("@ROOT@", str(ROOT)).replace("@HOME@", str(Path.home())))
        (L / "PROMPT.txt").write_text(f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; "
                                      f"gcc -da writes its dumps into the current directory, and lanes have left dozens "
                                      f"of dump files at the repo root.\nRead work/native_lane/{name}/BRIEF.md and follow it "
                                      f"exactly. Work only inside work/native_lane/{name}/ and never write files at the repo "
                                      f"root. When done, end with one line per row: row, result, the change in one sentence, "
                                      f"the mechanism in one sentence, the generator rule in one sentence, and what did not work.\n")
        built.append((name, n))
        print(name, n, "rows", "(%d tie)" % len(ties) if ties else "")
    for k, v in stats.most_common():
        print("  %-40s %d" % (k, v))
    if failed:
        print("  base NOT exact (dropped):", ", ".join(failed))
    elif a.no_verify:
        print("  bases NOT verified (--no-verify)")


if __name__ == "__main__":
    main()
