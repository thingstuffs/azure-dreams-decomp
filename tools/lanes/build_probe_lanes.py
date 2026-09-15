#!/usr/bin/env python3
"""Build sol packs of register rows whose pin sites carry a MEASURED sufficient allocator knob (round 26).

    python3 tools/lanes/build_probe_lanes.py --probes DIR [--pool ROWS.txt] [--per 12] [--min-sites 1] LANE...

`DIR` holds one `tools/alloc_probe.py <row> --json --out DIR/<container>_<name>.json` report per row (the
driver `tools/lanes/probe_rows.sh ROWS.txt DIR` writes them).  A row is admitted when its report's `sha`
equals the current src text, and at least `--min-sites` of its ASM_REG sites are `status == "ok"`, not
`erased_exact` (erasing the pin alone already reproduces retail: nothing to learn) and `any_knob` (one
allocator input, changed alone under gdb, reproduces the pinned assembly).  Rows with every ASM_REG site
knob-sufficient come first, then fewer pins.  These packs are deliberate RETRY packs on rows earlier packs
missed, so the served-row guard runs with repack=True and the earlier lanes are named in rows.md (their
REPORT.md says what was already tried).  Each lane gets base/, out/, rows.md, BRIEF.md
(tools/lanes/probe_lane_brief.md) and PROMPT.txt; launch with tools/lanes/launch_lane.sh <lane> sol.
"""
import argparse
import collections
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path, sha_text
from pin_census import sites_of
from served import served_rows, assert_unserved

REG_NAMES = {0: "zero", 1: "at", 2: "v0", 3: "v1", 4: "a0", 5: "a1", 6: "a2", 7: "a3",
             8: "t0", 9: "t1", 10: "t2", 11: "t3", 12: "t4", 13: "t5", 14: "t6", 15: "t7",
             16: "s0", 17: "s1", 18: "s2", 19: "s3", 20: "s4", 21: "s5", 22: "s6", 23: "s7",
             24: "t8", 25: "t9", 28: "gp", 29: "sp", 30: "fp", 31: "ra"}
KNOB_TEXT = {
    "pref": "the value needs a global PREFERENCE for retail's register: a real copy between the value and that "
            "hard register (staged as a call argument in that register, read as a call's return, returned by the "
            "function, tied by an operation) with no temp or re-computation in between",
    "copypref": "same as pref, recorded from a plain register copy: make the value itself the argument / return "
                "value / read of the return",
    "sugg": "the value needs a local SUGGESTION: a copy to or from retail's hard register inside its own block "
            "(argument staging, a return, a tied operand)",
    "unconflict": "retail's register is held by another value while this one is live: end the overlap by "
                  "shortening or splitting the OTHER value's lifetime, or by moving this value's definition later "
                  "or its last use earlier",
    "order-swap": "this value must be allocated BEFORE the value that took the register: more real references, a "
                  "shorter live interval, a wider mode (the landed fixes here were mostly a type width change on "
                  "the value), or for a genuine global tie the declaration order",
    "refs+1": "one more REAL reference to the value raises its rank",
    "refs-1": "one fewer reference to the value lowers its rank (it should be allocated later)",
    "shorten-death": "the value's lifetime must end one instruction earlier (its last use moved up)",
    "shorten-birth": "the value's lifetime must start one instruction later (its definition moved down)",
    "competitor-refs-1": "the COMPETITOR (named if the probe could bind it) must lose one reference",
    "competitor-unsugg": "the competitor must lose its suggestion for the register (its copy to/from that hard "
                         "register goes through another value or disappears)",
    "competitor-unpref": "the competitor must lose its preference for the register",
    "used-so-far-set": "retail's register must already be in use by an EARLIER real value in the function",
    "used-so-far-clear": "the register the allocator chose must NOT be in use earlier in the function",
}


def reg_name(spelling):
    s = str(spelling).lstrip("$").strip('"')
    n = int(s) if s.isdigit() else None
    return "$%s (%s)" % (s, REG_NAMES.get(n, "?")) if n is not None else "$" + s


def load_reports(d):
    out = {}
    for f in sorted(Path(d).glob("*.json")):
        try:
            rep = json.loads(f.read_text())
        except Exception:
            continue
        if isinstance(rep, dict) and rep.get("id"):
            out[rep["id"]] = rep
    return out


def admissible_sites(rep):
    return [s for s in rep.get("sites") or []
            if s.get("status") == "ok" and not s.get("erased_exact") and s.get("any_knob")]


def render_site(s, knob_site):
    lines = ["### site %d (line %s): `register ... %s ASM_REG(\"%s\")` -> %s%s"
             % (s["site"], s.get("line"), s.get("var"), s.get("register"), reg_name(s.get("register")),
                "  **<- a measured knob**" if knob_site else "")]
    if s.get("status") != "ok":
        lines.append("- probe status `%s`: no measurement for this site; treat the pin as undiagnosed." % s.get("status"))
        return lines
    lines.append("- **%s** value, pseudo %s; observer reasons: %s%s; erasing the pin alone: %s assembly lines from retail"
                 % (s.get("owner"), s.get("pseudo"), ", ".join(s.get("labels") or []) or "none",
                    ("; find_reg reading: " + ", ".join(s.get("attempt_labels"))) if s.get("attempt_labels") else "",
                    s.get("erased_distance")))
    if s.get("erased_exact"):
        lines.append("- **PIN INERT**: erasing this pin alone already reproduces retail; no knob needed.")
        return lines
    suff = [k for k in s.get("sufficient") or [] if k not in ("force", "force-return")]
    by = {r["name"]: r for r in s.get("knobs") or []}
    if suff:
        for k in suff:
            r = by.get(k, {})
            comp = (s.get("competitor_names") or {}).get(k)
            lines.append("- SUFFICIENT knob `%s`%s: %s%s"
                         % (k, " (the allocator's decision changed)" if r.get("changed_result") else
                            " (assembly exact although the recorded decision did not change)",
                            KNOB_TEXT.get(k, "no translation recorded"),
                            ("; the competitor is `%s`" % comp) if comp else ""))
        lines.append("- minimal knob: **`%s`**; force (this one assignment alone): %s"
                     % (s.get("minimal_knob"), "exact" if s.get("force_exact") else "not exact"))
    else:
        lines.append("- no single input knob is sufficient (force alone: %s): an ordinary diagnosed site, lower priority"
                     % ("exact" if s.get("force_exact") else "not exact"))
    near = sorted((r for r in s.get("knobs") or [] if r.get("distance") is not None and not r.get("equal")
                   and r["name"] not in ("force", "force-return")), key=lambda r: r["distance"])[:3]
    if near and not suff:
        lines.append("- nearest knobs: " + ", ".join("`%s` %d lines" % (r["name"], r["distance"]) for r in near))
    return lines


def render_row(rid, r, rep, text, served):
    sites = sites_of(text)
    prior = served.get(rid, [])
    head = ["## %s" % rid,
            "- cell `%s`, %d B retail, `src/%s.c`, %d pin site(s) (%d `ASM_REG`)"
            % (r["cfg"], r["size"], rid, len(sites), rep.get("reg_sites", 0)),
            "- earlier packs on this row: %s" % (", ".join("`work/native_lane/%s/REPORT.md`" % l for l in prior) or "none")]
    good = {s["site"] for s in admissible_sites(rep)}
    body = []
    for s in rep.get("sites") or []:
        body += render_site(s, s.get("site") in good)
    return "\n".join(head + body) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="+")
    ap.add_argument("--probes", required=True, help="directory of alloc_probe --json --out reports")
    ap.add_argument("--pool", help="file of row ids (first field per line) to restrict to")
    ap.add_argument("--per", type=int, default=12)
    ap.add_argument("--min-sites", type=int, default=1)
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    R = {r["id"]: r for r in rows()}
    pool = None
    if a.pool:
        pool = {l.split()[0] for l in open(a.pool) if l.strip() and not l.startswith("#")}
    reps = load_reports(a.probes)
    stats = collections.Counter()
    cand = []
    for rid, rep in reps.items():
        if pool is not None and rid not in pool:
            continue
        r = R.get(rid)
        if not r or not clean_path(r).exists():
            stats["no such row"] += 1
            continue
        text = clean_path(r).read_text(errors="replace")
        if sha_text(text) != rep.get("sha"):
            stats["source drifted since the probe"] += 1
            continue
        good = admissible_sites(rep)
        reg = [s for s in rep.get("sites") or [] if s.get("status") not in (None, "not-an-ASM_REG-site")]
        if len(good) < a.min_sites:
            stats["no knob-sufficient site"] += 1
            continue
        stats["POOL"] += 1
        cand.append((0 if len(good) == len(reg) else 1, len(sites_of(text)), rid, r, rep, text))
    cand.sort(key=lambda x: (x[0], x[1], x[2]))
    served = served_rows()
    brief = (ROOT / "tools/lanes/probe_lane_brief.md").read_text()
    it = iter(cand)
    for name in a.lanes:
        chunk = [next(it, None) for _ in range(a.per)]
        chunk = [c for c in chunk if c]
        if not chunk:
            print(name, "no rows left")
            break
        overlap = assert_unserved([c[2] for c in chunk], repack=True)
        if a.dry_run:
            print(name, len(chunk), "rows (dry run, nothing written; %d previously served):" % len(overlap),
                  ", ".join(c[2] for c in chunk))
            continue
        L = ROOT / "work/native_lane" / name
        assert not (L / "last_message.txt").exists(), name
        (L / "out").mkdir(parents=True, exist_ok=True)
        out = ["# Rows (each ASM_REG site with the allocator knob the probe measured as sufficient; rows whose every "
               "site has one first, then fewest pins)\n",
               "Site numbers index every `ASM_*` site of the file in source order, as `tools/pin_census.py` lists "
               "them.\n"]
        for _, _, rid, r, rep, text in chunk:
            out.append(render_row(rid, r, rep, text, served))
            cont, nm = rid.split("/")
            (L / "base" / cont).mkdir(parents=True, exist_ok=True)
            (L / "base" / cont / (nm + ".c")).write_text(text)
            (L / "base" / cont / (nm + ".c.base_sha")).write_text(sha_text(text))
        (L / "rows.md").write_text("\n".join(out))
        (L / "BRIEF.md").write_text(brief.replace("@LANE@", name).replace("@NROWS@", str(len(chunk)))
                                    .replace("@ROOT@", str(ROOT)).replace("@HOME@", str(Path.home())))
        (L / "PROMPT.txt").write_text(
            f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; gcc -da writes its dumps "
            f"into the current directory, and lanes have left dozens of dump files at the repo root.\nRead "
            f"work/native_lane/{name}/BRIEF.md and follow it exactly. Work only inside work/native_lane/{name}/ and "
            f"never write files at the repo root. When done, end with one line per row: row, result, the change in "
            f"one sentence, the knob and whether your change supplied it, the generator rule in one sentence, and "
            f"what did not work.\n")
        print(name, len(chunk), "rows (%d previously served)" % len(overlap))
    for k, v in stats.most_common():
        print("  %-40s %d" % (k, v))


if __name__ == "__main__":
    main()
