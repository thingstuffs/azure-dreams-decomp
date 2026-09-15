#!/usr/bin/env python3
"""THE POOL TABLE: every remaining pinned row by family and stratum, served against unserved, with
the near band and the last measured lane rate - the table round 26 rebuilt by hand three times
before a pack was launched.

    python3 tools/lanes/pools.py                          # the table (+ the TOTAL check line)
    python3 tools/lanes/pools.py --rows REG alloc5 --band 1-3 --unserved   # row ids for a builder
    python3 tools/lanes/pools.py --json out.json          # the per-row records
    python3 tools/lanes/pools.py --search-tag <tag>       # the near band from ONE pin_search tag

Reads (nothing else; nothing is written into the tree): `common.rows()`/`clean_path()` and each row's
clean text through `pin_census.sites_of()` (the families and the band); `lanes/served.py
served_rows()` over work/native_lane/*/base/*/*.c (who served the row); the per-row allocator traces
under work/alloc_retrace/raw/ AND work/native_lane/alloc_astra/scratch/trace_population/, both
through `build_alloc_lanes.collect()`, plus work/alloc_retrace/summary*.json for coverage (the
register stratum); work/alloc_probe/reg_all/*.json then missed_small/*.json (the probe knob class);
work/pin_search/*/results/baseline/*.json (the near band); ledger/lanes.jsonl (the rates).

Writes work/lanes_cache/pools_sites.json (per-row site counts keyed by the file's text sha, beside a
`.ignore` of `*`, so a second run re-parses nothing) and the file named by `--json`.

Denominator: the pin count excludes `common.PARKED_CONTAINERS` (ovmovie) exactly as tools/status.py's
"Pin sites now" line does, so TOTAL is comparable with STATUS.md; the TOTAL line prints the table's
pin sum next to an independent `sites_of()` pass over the tree and asserts they are equal.

Classification (pure functions, unit-tested in tools/tests/test_pools.py):
  family    the row's dominant family: REG (`ASM_REG*`), KEEP (`ASM_KEEP*`), FENCE
            (`ASM_SCHED_BARRIER`/`ASM_MEM_BARRIER`), OTHER; ties go REG > KEEP > FENCE > OTHER.
  stratum   the FIRST matching `build_alloc_lanes.STRATA` entry over the union of the row's
            `site_reasons()` - the rule the alloc packs were cut with, so a rate measured on alloc3
            applies to the alloc3 line here.  BOTH trace directories are read: work/alloc_retrace/raw
            (the re-traces, whose always-on `attempt_reasons` resolve sites the lane left coarse)
            first, then the alloc_astra population the alloc packs were actually cut from, which
            still supplies about a third of the stratified rows; `stratum_source` names the winner.
            `no-stratum` = traced, no stratum reason; `trace-stale` = a trace file exists but
            `collect()` dropped the row in every directory (the source drifted since the trace, or
            the site index no longer lines up); `-` = no per-row trace anywhere.
  band      pin sites per row: 1 / 2-3 / 4-8 / 9-20 / 21+ (`--band` takes 1-3, 4, 21+ as well).
  knob      the alloc_probe class: one-knob > force-only > no-knob-plan > none (an `untrusted` site,
            or one already exact when erased, is no evidence and is skipped); `-` = no report.
  near      min d0 over the groups of the row's baseline result, and whether any group already has
            best < d0 - counted only while that result's `source_sha` is still the row's text sha,
            else `stale`.  DEFAULT: every tag under work/pin_search/ merged, newest FRESH result per
            row winning (`at`, else the tag's mtime order), so a stale result never hides an older
            fresh one.  That is a deliberate change from the spec's "newest tag only" default: the
            sha gate makes merging safe, while the newest tag by mtime covered 2.9% of the tree, so
            `near` read 0 for want of a search.  `--search-tag <tag>` is the single-tag view.

Columns: `u` (unserved: no lane has served the row) and `s` (served) side by side, each with `rows`,
`pins`, `srch` (rows with a fresh baseline result - without it a 0 in `near` cannot be told from
"never searched") and `near` (of those, min d0 <= 4).  A pack is cut from the `u` columns alone, so
the two halves are never added together.

`ledger/lanes.jsonl` (tools/lanes/ledger.py) is one record per model lane; this tool never builds it
and prints every rate as `-` when it is absent.  The reader is tolerant of the schema: the stratum
under `stratum`/`pool`/`lane_stratum`, the rows served under `served`/`rows`/`n_rows`/`tried`, the
wins under `landed`/`exact`/`hits`/`wins`.  The rate is `landed / served` over every lane of that
stratum; with no lane on the stratum (most KEEP, FENCE and untraced rows) it falls back to the
family's own lanes, marked `fam` - weaker, because those lanes were not cut on this stratum.  No
lane record carries a pin band, so the same rate prints on every band even though the diagnosed
register packs paid 33-42% on 1-3 pin rows and 0-8% on the rest (round 25).  On a KEEP, FENCE or
OTHER row the stratum describes that row's REG pins only.

Side effect of reusing `build_alloc_lanes.collect()` unchanged: it reads the alloc_astra lane's
`heldout_h1_census_rows.txt` / `heldout_h2_population_rows.txt`, and this tool sets that module's
`ALLOW_FENCES` / `INCLUDE_HELDOUTS` globals in its own process so the census admits every traced row.
"""
import argparse
import collections
import json
import math
import os
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path, sha_text, PARKED_CONTAINERS
from pin_census import sites_of
from served import served_rows
import build_alloc_lanes as bal

SITES_VERSION = 1                      # bump when the family rule or pin_census's site regexes change
CACHE = ROOT / "work/lanes_cache/pools_sites.json"
# Both per-row trace directories, in precedence order: the re-traces first (finer reasons), then the
# population the alloc packs were cut from.  The .gz files beside the population are per-SITE gdb
# dumps (`<row>_<site>.trace.json.gz`), not row traces, and `collect()` rightly ignores them.
TRACE_DIRS = (("raw", ROOT / "work/alloc_retrace/raw"), ("population", bal.TRACES))
SUMMARIES = ROOT / "work/alloc_retrace"
PROBES = [ROOT / "work/alloc_probe/reg_all", ROOT / "work/alloc_probe/missed_small"]   # first hit wins per row
SEARCH = ROOT / "work/pin_search"
LANES_JSONL = ROOT / "ledger/lanes.jsonl"
FENCE_MACROS = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")
FAMILIES = ("REG", "KEEP", "FENCE", "OTHER")          # also the tie-break order
BANDS = ("1", "2-3", "4-8", "9-20", "21+")
NEAR_D0 = 4
KNOB_ORDER = ("one-knob", "force-only", "no-knob-plan", "none")


# ---------------------------------------------------------------- pure classifiers

def macro_family(macro):
    if macro.startswith("ASM_REG"):
        return "REG"
    if macro.startswith("ASM_KEEP"):
        return "KEEP"
    if macro in FENCE_MACROS:
        return "FENCE"
    return "OTHER"


def family_counts(text):
    c = collections.Counter(macro_family(s[1]) for s in sites_of(text))
    return {f: c[f] for f in FAMILIES}


def dominant_family(counts):
    """The row's family: the most sites, ties broken REG > KEEP > FENCE > OTHER."""
    return max(FAMILIES, key=lambda f: (counts.get(f, 0), -FAMILIES.index(f)))


def band(n):
    return "1" if n <= 1 else "2-3" if n <= 3 else "4-8" if n <= 8 else "9-20" if n <= 20 else "21+"


def parse_band(spec):
    """'1-3' -> (1, 3), '21+' -> (21, inf), '4' -> (4, 4); the table's own band labels parse too."""
    spec = spec.strip()
    if spec.endswith("+"):
        return int(spec[:-1]), math.inf
    if "-" in spec:
        lo, hi = spec.split("-", 1)
        return int(lo), int(hi)
    return int(spec), int(spec)


def stratum_of(reasons):
    """The first `build_alloc_lanes.STRATA` pack whose reasons this row's trace names."""
    reasons = set(reasons or ())
    for name, rs in bal.STRATA:
        if reasons & set(rs):
            return name
    return "no-stratum"


def knob_class(report):
    """The probe class of a row from its alloc_probe report: the best class over its sites.
    A site that is not `ok`, or whose pin is already inert (`erased_distance == 0`), is no
    evidence about a knob and is skipped; `no-knob-plan` is a status, not an outcome."""
    best = None
    for s in (report or {}).get("sites") or []:
        st = s.get("status")
        if st == "no-knob-plan":
            cls = "no-knob-plan"
        elif st != "ok" or s.get("erased_distance") == 0:
            continue
        elif s.get("any_knob"):
            cls = "one-knob"
        elif s.get("force_exact"):
            cls = "force-only"
        else:
            cls = "none"
        if best is None or KNOB_ORDER.index(cls) < KNOB_ORDER.index(best):
            best = cls
    return best or "none"


def near_of(result, cur_sha):
    """(state, min d0, any group improving) for one pin_search baseline result: `stale` when the
    result was measured on other text than the row's current text."""
    if not result:
        return "-", None, False
    if result.get("source_sha") != cur_sha:
        return "stale", None, False
    groups = result.get("groups") or []
    d0s = [g["d0"] for g in groups if g.get("d0") is not None]
    if not d0s:
        return "fresh", None, False
    improving = any(g.get("best") is not None and g.get("d0") is not None and g["best"] < g["d0"]
                    for g in groups)
    return "fresh", min(d0s), improving


def near_merged(cands, cur_sha):
    """(state, min d0, improving, tag) over ALL of a row's baseline results, as [(sort key, tag,
    result)] in read order (oldest tag first).  The newest FRESH result decides d0, so a stale
    newer result never hides a fresh older one; `improving` is true if any fresh result improved.
    With nothing fresh the newest stale result is reported as `stale`, which is not `-`."""
    fresh = [(k, t, near_of(r, cur_sha)) for k, t, r in cands or () if r.get("source_sha") == cur_sha]
    if fresh:
        k, tag, (state, d0, _) = max(fresh, key=lambda c: c[0])
        return state, d0, any(f[2][2] for f in fresh), tag
    if cands:
        return "stale", None, False, max(cands, key=lambda c: c[0])[1]
    return "-", None, False, None


# ---------------------------------------------------------------- inputs

def cache_io(cache=None):
    """The site-count cache: read it with no argument, write it (tmp + rename, beside its .ignore)
    with one.  A key is `<text sha>:<SITES_VERSION>`, so a changed site rule never reads stale counts."""
    if cache is None:
        try:
            return json.loads(CACHE.read_text())
        except Exception:
            return {}
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    if not (CACHE.parent / ".ignore").exists():
        (CACHE.parent / ".ignore").write_text("*\n")
    tmp = CACHE.with_suffix(".json.tmp")
    tmp.write_text(json.dumps(cache, separators=(",", ":")))
    os.replace(tmp, CACHE)


def read_json_by_id(paths):
    """{record id: record} over a directory of per-row JSON reports, with the unreadable ones
    counted rather than fatal (a live run may be mid-write)."""
    out, bad = {}, 0
    for f in paths:
        try:
            d = json.loads(f.read_text())
        except Exception:
            bad += 1
            continue
        if d.get("id"):
            out[d["id"]] = d
    return out, bad


def trace_ids(d):
    """The row ids a trace directory holds files for: dungeon_func_7FFEA9D4.json -> dungeon/func_..."""
    return {f.stem.partition("_")[0] + "/" + f.stem.partition("_")[2] for f in d.glob("*.json")}


DRIFT = ("source drifted since the trace", "site index no longer aligns", "no such row")


def merge_strata(per_dir):
    """({row id: stratum}, {row id: which directory said so}) from [(dir name, {row id: stratum},
    {row ids with a trace file})] in precedence order: the first directory that stratified a row
    wins, a row every directory has a file for but none stratified is `trace-stale`, and a row no
    directory has a file for is absent (the caller reads it as `-`)."""
    out, src, on_disk = {}, {}, set()
    for name, strata, ids in per_dir:
        on_disk |= set(ids)
        for rid, st in strata.items():
            if rid not in out:
                out[rid], src[rid] = st, name
    for rid in on_disk - set(out):
        out[rid], src[rid] = "trace-stale", "dropped by both"
    return out, src


def strata_by_row(notes):
    """({row id: stratum}, {row id: which directory said so}) over BOTH trace directories, through
    `build_alloc_lanes.collect()`: every trace is admitted (fences, held-out rows, any pin count,
    served or not) because this is a census, not a pack.  The re-traces win where both have the row;
    a row every directory dropped is `trace-stale`, a row no directory has is `-`."""
    bal.ALLOW_FENCES, bal.INCLUDE_HELDOUTS = True, True
    per_dir, parts = [], []
    for name, d in TRACE_DIRS:
        if not d.is_dir():
            parts.append("%s (%s): directory missing" % (name, d.relative_to(ROOT)))
            continue
        stats = collections.Counter()
        pool = bal.collect(stats, max_pins=10 ** 9, exclude=(), traces=d, min_pins=0, served=())
        ids = trace_ids(d)
        per_dir.append((name, {p["id"]: stratum_of(p["reasons"]) for p in pool}, ids))
        parts.append("%s (%s): %d trace files, %d rows stratified, %d dropped by collect() (%s)"
                     % (name, d.relative_to(ROOT), len(ids), len(pool), len(ids) - len(pool),
                        ", ".join("%s %d" % (k, stats[k]) for k in DRIFT if stats[k])
                        or "none of the drift reasons"))
    out, src = merge_strata(per_dir)
    first = collections.Counter(src.values())
    parts = [p + (", %d rows first stratified here" % first[p.split(" ")[0]]
                  if p.split(" ")[0] in first else "") for p in parts]
    notes["traces"] = "traces: %d rows stratified, %d trace-stale, over %d trace files" % (
        sum(1 for v in out.values() if v != "trace-stale"),
        sum(1 for v in out.values() if v == "trace-stale"),
        len(set().union(*[ids for _, _, ids in per_dir]) if per_dir else ()))
    notes["trace_dirs"] = parts
    cov = []                     # the summaries are aggregates: coverage only, no per-row record
    for f in sorted(Path(SUMMARIES).glob("summary*.json")):
        d = json.loads(f.read_text())
        n = next((d[k] for k in ("rows_traced", "retraced_ok", "new_rows") if k in d), None)
        cov.append("%s: %s rows" % (f.name, n if n is not None else "aggregate only"))
    notes["retrace_summaries"] = "; ".join(cov) or "no summary*.json"
    return out, src


def knobs_by_row(notes):
    """The probe class per row over every probe directory, the first directory in PROBES winning for a
    row that has a report in several (reg_all is the round-27 triage of the whole register family)."""
    reps, parts = {}, []
    for d in PROBES:
        got, bad = read_json_by_id(sorted(Path(d).glob("*.json")))
        for rid, rep in got.items():
            reps.setdefault(rid, rep)
        parts.append("%d under %s%s" % (len(got), Path(d).relative_to(ROOT), (", %d unreadable" % bad) if bad else ""))
    notes["probes"] = "%d probe reports (%s)" % (len(reps), "; ".join(parts))
    return {rid: knob_class(rep) for rid, rep in reps.items()}


def search_tags():
    """Every pin_search tag with a results/baseline/, oldest first by that directory's mtime."""
    if not SEARCH.is_dir():
        return []
    cand = [d for d in SEARCH.iterdir() if d.is_dir() and (d / "results/baseline").is_dir()]
    return [d.name for d in sorted(cand, key=lambda d: (d / "results/baseline").stat().st_mtime)]


def search_results(tag, notes):
    """{row id: [(sort key, tag, result)]} - one tag's baseline results with `tag`, every tag merged
    without (the caller's `near_merged` picks the newest fresh one per row)."""
    tags = [tag] if tag else search_tags()
    out, per, bad, nbytes, seq = collections.defaultdict(list), [], 0, 0, 0
    for t in tags:
        d = SEARCH / t / "results/baseline"
        if not d.is_dir():                       # only reachable through --search-tag: name the tags
            raise SystemExit("pin_search tag %r has no results/baseline/; tags with one, newest "
                             "first: %s" % (t, ", ".join(reversed(search_tags())) or "none"))
        n = 0
        for f in sorted(d.glob("*.json")):
            try:
                txt = f.read_text()
                rec = json.loads(txt)
            except Exception:
                bad += 1
                continue
            nbytes += len(txt)
            if not rec.get("id"):
                continue
            seq += 1
            out[rec["id"]].append(((rec.get("at") or "", seq), t, rec))
            n += 1
        per.append("%s %d" % (t, n))
    if not tags:
        notes["search"] = "no pin_search tag with results/baseline/ - the near band is '-' everywhere"
        notes["search_tags"] = []
        return {}, None
    notes["search"] = "%s, %d rows with a result, %.1f MB read%s" % (
        ("tag %s" % tag) if tag else "%d tags merged (newest fresh result per row)" % len(tags),
        len(out), nbytes / 1e6, (", %d unreadable (a run in flight)" % bad) if bad else "")
    notes["search_tags"] = list(reversed(per))            # newest tag first, as the listing reads
    return dict(out), (tag or "ALL")


def lane_rates(notes):
    """({stratum: rate string}, {family: rate string}) from ledger/lanes.jsonl - landed / served
    summed over every lane of that stratum (and, as the fallback the table marks `fam`, of that
    family).  None when the file does not exist."""
    if not LANES_JSONL.exists():
        notes["lanes"] = "ledger/lanes.jsonl does not exist: every rate prints '-' " \
                         "(this tool does not build it)"
        return None
    by_st, by_fam, bad, lanes = collections.defaultdict(lambda: [0, 0, 0]), \
        collections.defaultdict(lambda: [0, 0, 0]), 0, 0
    for ln in LANES_JSONL.read_text().splitlines():
        try:
            rec = json.loads(ln) if ln.strip() else {}
        except Exception:
            bad += 1
            continue
        if not rec:
            continue
        lanes += 1
        served = next((rec[k] for k in ("served", "rows", "n_rows", "tried") if isinstance(rec.get(k), int)), 0)
        landed = next((rec[k] for k in ("landed", "exact", "hits", "wins") if isinstance(rec.get(k), int)), 0)
        if not served:
            continue
        for tgt, key in ((by_st, next((rec[k] for k in ("stratum", "pool", "lane_stratum")
                                       if rec.get(k)), None)),
                         (by_fam, rec.get("family"))):
            if key:
                a = tgt[key]
                a[0] += served; a[1] += landed; a[2] += 1
    fmt = lambda a: "%d%% (%d/%d, %d lanes)" % (round(100.0 * a[1] / a[0]), a[1], a[0], a[2])
    notes["lanes"] = "ledger/lanes.jsonl: %d lane records, %d strata and %d families with a rate%s" \
                     % (lanes, len(by_st), len(by_fam), (", %d unparsable lines" % bad) if bad else "")
    return {k: fmt(v) for k, v in by_st.items()}, {k: fmt(v) for k, v in by_fam.items()}


# ---------------------------------------------------------------- the records

def build_records(search_tag=None):
    notes, t0 = {}, time.time()
    cache, cache_hits = cache_io(), 0
    served = served_rows()
    strata, strata_src = strata_by_row(notes)
    knobs = knobs_by_row(notes)
    results, tag = search_results(search_tag, notes)
    rates = lane_rates(notes)

    recs, live_pins = [], 0
    for r in rows():
        if r["container"] in PARKED_CONTAINERS:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        sha = sha_text(text)
        key = "%s:%d" % (sha, SITES_VERSION)
        hit = key in cache
        counts = dict(zip(FAMILIES, cache[key])) if hit else family_counts(text)
        cache[key] = [counts[f] for f in FAMILIES]
        npins = sum(counts.values())
        if not npins:
            continue
        cache_hits += hit
        live_pins += npins
        state, d0, improving, near_tag = near_merged(results.get(r["id"]), sha)
        fam = dominant_family(counts)
        recs.append({"id": r["id"], "container": r["container"], "size": r["size"], "cfg": r["cfg"],
                     "family": fam, "counts": counts, "pins": npins, "band": band(npins),
                     "served": served.get(r["id"], []), "stratum": strata.get(r["id"], "-"),
                     "stratum_source": strata_src.get(r["id"], "-"),
                     "knob": knobs.get(r["id"], "-"), "near": state, "d0": d0,
                     "improving": improving, "near_tag": near_tag})
    cache_io(cache)
    notes["cache"] = "%d of %d rows from work/lanes_cache/pools_sites.json" % (cache_hits, len(recs))
    notes["seconds"] = round(time.time() - t0, 1)
    return recs, notes, rates, tag, live_pins


def tree_pins():
    """An independent live-pin pass (never the cache): the number TOTAL is asserted against."""
    n = 0
    for r in rows():
        if r["container"] in PARKED_CONTAINERS:
            continue
        p = clean_path(r)
        if p.exists():
            n += len(sites_of(p.read_text(errors="replace")))
    return n


# ---------------------------------------------------------------- rendering

HEAD = ("family", "stratum", "band", "u rows", "u pins", "u srch", "u near",
        "s rows", "s pins", "s srch", "s near", "rate on stratum (all lanes)")
WIDTH = (6, 12, 5, 6, 6, 6, 6, 6, 6, 6, 6, 26)
LEGEND = ("  u = unserved (no lane has served the row), s = served; srch = rows with a fresh "
          "baseline result, near = of those, min d0 <= %d." % NEAR_D0,
          "  A pack is cut from the u columns alone: the two halves are never added together, and a "
          "near of 0 beside a srch of 0 means unsearched, not far.")


def wrap(head, items, width=110):
    """`head` then the comma-separated items, folded onto continuation lines of `head`'s indent."""
    out, cur = [], head
    for i, it in enumerate(items):
        piece = it + (", " if i < len(items) - 1 else "")
        if len(cur) + len(piece) > width and cur.strip() != head.strip():
            out.append(cur.rstrip())
            cur = " " * (len(head) - len(head.lstrip())) + "  "
        cur += piece
    return out + [cur.rstrip()]


def line(cells):
    return "  ".join(str(c).ljust(w) if i < 3 else str(c).rjust(w) for i, (c, w) in enumerate(zip(cells, WIDTH)))


TAIL_STRATA = ("no-stratum", "trace-stale", "-")


def stratum_key(s):
    """Pack order first (alloc1..alloc5), then any other label, then the three non-pack labels."""
    order = {n: i for i, (n, _) in enumerate(bal.STRATA)}
    if s in order:
        return (0, order[s])
    if s in TAIL_STRATA:
        return (2, TAIL_STRATA.index(s))
    return (1, s)


def agg(group):
    """(rows, pins, searched, near) for the unserved half, then the same four for the served half."""
    half = lambda g: (len(g), sum(r["pins"] for r in g),
                      sum(1 for r in g if r["near"] == "fresh"),
                      sum(1 for r in g if r["near"] == "fresh" and r["d0"] is not None
                          and r["d0"] <= NEAR_D0))
    return half([r for r in group if not r["served"]]) + half([r for r in group if r["served"]])


def render(recs, notes, rates, tag, live_pins):
    out = ["THE POOL TABLE  (%s, %d pinned rows, %d pin sites; ovmovie parked and excluded, as in "
           "STATUS.md)" % (time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()), len(recs), live_pins),
           "  " + notes["traces"]] \
        + ["    " + p for p in notes["trace_dirs"]] \
        + ["  retrace summaries: " + notes["retrace_summaries"],
           "  " + notes["probes"],
           "  near band: " + notes["search"]] \
        + wrap("    per tag (newest first): ", notes["search_tags"] or ["none"]) \
        + [
           "  lane rates: " + notes["lanes"],
           "  " + notes["cache"] + "; built in %ss" % notes["seconds"], ""] \
        + list(LEGEND) + ["", line(HEAD), line(tuple("-" * w for w in WIDTH))]
    by = collections.defaultdict(list)
    for r in recs:
        by[(r["family"], r["stratum"], r["band"])].append(r)
    for fam in FAMILIES:
        keys = sorted([k for k in by if k[0] == fam],
                      key=lambda k: (stratum_key(k[1]), BANDS.index(k[2])))
        if not keys:
            continue
        for k in keys:
            # the stratum's own measured rate, else the family's, marked `fam` (it is a weaker number)
            rate = "-" if rates is None else rates[0].get(
                k[1], "fam " + rates[1][fam] if fam in rates[1] else "-")
            out.append(line(k + agg(by[k]) + (rate,)))
        fr = [r for r in recs if r["family"] == fam]
        out.append(line((fam, "* all", "*") + agg(fr) +
                        ("fam " + rates[1][fam] if rates and fam in rates[1] else "",)))
        out.append("")
    ur, up, usr, un, sr, sp, ssr, sn = agg(recs)
    out.append(line(("TOTAL", "*", "*", ur, up, usr, un, sr, sp, ssr, sn, "")))
    tp = tree_pins()
    out.append("TOTAL CHECK  table pins %d (unserved %d + served %d) vs tree live pin count %d: %s"
               % (up + sp, up, sp, tp, "EQUAL" if up + sp == tp else "MISMATCH"))
    out.append("KNOB CLASS (rows, alloc_probe): " +
               ", ".join("%s %d" % (k, v) for k, v in collections.Counter(r["knob"] for r in recs).most_common()))
    out.append("STRATUM SOURCE (rows): " +
               ", ".join("%s %d" % (k, v) for k, v in
                         collections.Counter(r["stratum_source"] for r in recs).most_common()))
    return "\n".join(out), up + sp == tp       # the caller prints the table BEFORE it asserts


def render_rows(recs, family, stratum, band_spec, want):
    lo, hi = parse_band(band_spec) if band_spec else (0, math.inf)
    out = []
    for r in sorted(recs, key=lambda r: (r["pins"], r["size"], r["id"])):
        if (family and r["family"] != family.upper()) or (stratum and r["stratum"] != stratum) \
                or not lo <= r["pins"] <= hi \
                or (want == "unserved" and r["served"]) or (want == "served" and not r["served"]):
            continue
        out.append("%-34s pins=%-3d d0=%-5s %s%s" % (
            r["id"], r["pins"], r["d0"] if r["d0"] is not None else r["near"],
            "knob=%s" % r["knob"] if r["knob"] != "-" else "",
            "  served=%s" % ",".join(r["served"]) if r["served"] else ""))
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0],
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rows", nargs="+", metavar="FAMILY [STRATUM]",
                    help="print row ids instead of the table, e.g. --rows REG alloc5")
    ap.add_argument("--band", help="pin-count band: 1-3, 4, 21+ (the table's labels parse too)")
    ap.add_argument("--unserved", action="store_true", help="only rows no lane has served")
    ap.add_argument("--served", action="store_true", help="only rows a lane has served")
    ap.add_argument("--search-tag", help="read the near band from this pin_search tag alone "
                                         "(default: every tag, newest fresh result per row)")
    ap.add_argument("--json", help="write the per-row records to this file")
    a = ap.parse_args()
    recs, notes, rates, tag, live_pins = build_records(a.search_tag)
    if a.json:
        Path(a.json).write_text(json.dumps({"generated": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
                                            "search_tag": tag, "notes": notes,
                                            "lane_rates": rates, "rows": recs}, indent=1))
        print("%d row records -> %s" % (len(recs), a.json))
        return
    if a.rows:
        want = "unserved" if a.unserved else "served" if a.served else "all"
        listing = render_rows(recs, a.rows[0], a.rows[1] if len(a.rows) > 1 else None, a.band, want)
        if listing:                                   # an empty pool prints nothing, not a blank line
            print(listing)
        return
    table, ok = render(recs, notes, rates, tag, live_pins)
    print(table)
    assert ok, "the table's pin sum is not the tree's live pin count (see the TOTAL CHECK line)"


if __name__ == "__main__":
    main()
