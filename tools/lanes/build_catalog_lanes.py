#!/usr/bin/env python3
"""Build model lanes on the rows the round-33 perturbation catalogue CANNOT explain (round 35 plan item 1).

    python3 tools/lanes/build_catalog_lanes.py [--bucket near|far|both] [--per 12] [--band 4-8] [--repack]
        [--ignore-closed] [--dry-run] [--match DIR] [--census FILE] LANE...

THE ADMISSION RULE.  A pinned row (its pin sites read from `src/` NOW, with `pin_census.sites_of`) is

  UNEXPLAINED-NEAR  it has at least one site with d0 <= 4 and NONE of those near sites is covered at L1 or
                    finer with a cause (`per_site.jsonl`: `level` in (L1, L2) and `causes` non-empty);
  FAR               it has no site with d0 <= 4 at all - every site sits in a band where round 33's negative
                    control says the L1 key means nothing (the key covers the catalogue's own other half at
                    41 / 13 / 2 / 3% in bands 5-8 / 9-16 / 17-32 / 33+);
  and a row with a near site covered at L1 is BUCKET A - the generators' work, never admitted here.

Ranked by pins descending (the plan's rule), ties by row id; `--band` restricts the pin band first and the
ranking then runs inside it.  Both guards are on by default:

  served   a row any lane has served is refused (`served.served_rows()`); `--repack` lifts it and marks the
           pack a retry (rows.md and BRIEF.md name the lanes that served each row).
  closed   a row whose (family, stratum) is a CLOSED group is refused (`ledger.py --closed 0.2`, read
           in-process through `ledger.load()`/`ledger.closed()`; this tool never builds the ledger).
           `--ignore-closed` lifts it.

  The two guards are INDEPENDENT - each flag lifts only its own refusal - so neither pool is the candidate
  count.  `--dry-run` prices each guard still standing on its own, under the admitted count.

  family   `pools.dominant_family(pools.family_counts(text))` - the row's own macros, REG > KEEP > FENCE > OTHER.
  stratum  `pools.strata_by_row()` (both trace directories, the re-traces first), then FOLDED: `no-stratum`,
           `trace-stale` and `-` all become `-`, because they are one fact - no usable allocator stratum -
           and that is how `ledger.group_key` spells a lane with no stratum and how `pools.py` falls back to
           the family rate.  Without the fold a row whose trace merely went stale would escape (REG,-) while
           an untraced twin is refused.  `--dry-run` prints the closed count under both readings.
           The lookup stays strict to the printed list otherwise: (KEEP, alloc3) is not closed even though
           alloc3's own REG rate is 0.15 - extending the list is the ledger's job, not this builder's.

Rows whose text changed since the census are DROPPED, not re-counted: an erasure residue depends on the rest
of the function, so after round 34's landings those rows' fingerprints are wrong, not merely misindexed.  A
row is stale when its current site count differs from the census's `n` or a macro at an index differs.

THE PACK: `base/<container>/<name>.c` (+ `.base_sha`), an empty `out/`, `rows.md` (per row: every site's
line, macro, d0, class, band, shape and register pairs, and for a NEAR row the site's top three causes with
their shares and generators - each labelled a compatible mechanism, NOT the move, the oracle agreed on 45%
of landed rows - the journal outcome of that generator on this text where `bucket_a_split.jsonl` has it, and
the measured negative that applies), `BRIEF.md` (from `tools/lanes/catalog_lane_brief.md`) and `PROMPT.txt`.
FAR rows carry no causes at all: the control says a key beyond d = 4 names nothing, so printing one would be
noise dressed as evidence.  Nothing is compiled here (the tree is gated; the bases are exact by construction).

Inputs (nothing is written outside the pack): `work/native_lane/r33_catalog/rows/match3/per_site.jsonl`
(`--match DIR`), `.../scratch/census_fp2.jsonl` (`--census FILE`, for each site's line, shape and register
pairs), `.../rows/match3/bucket_a_split.jsonl` (the journal outcomes).  Written in round 35, to the shape of
`build_keep_lanes.py` and `build_alloc_lanes.py`.
"""
import argparse
import collections
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path, sha_text          # noqa: E402
from pin_census import sites_of                        # noqa: E402
from served import served_rows, assert_unserved        # noqa: E402
import pools                                           # noqa: E402
import ledger                                          # noqa: E402
import build_alloc_lanes as bal                        # noqa: E402

MATCH = ROOT / "work/native_lane/r33_catalog/rows/match3"
CENSUS = ROOT / "work/native_lane/r33_catalog/scratch/census_fp2.jsonl"
BRIEF = ROOT / "tools/lanes/catalog_lane_brief.md"
NEAR_D0 = 4                       # the band where round 33's control says an L1 key means something
CLOSED_THRESHOLD = 0.2            # ledger.py --closed 0.2
PACK_STRATA = {n for n, _ in bal.STRATA}
COVERED_LEVELS = ("L1", "L2")
TOP_CAUSES = 3                    # causes printed per site, and the causes a negative is looked up from

# ------------------------------------------------------------------ the measured negatives
# Keyed by a label; `negatives_for()` maps a site's causes and its residue class onto the labels.  Every
# entry names the round it was measured in, so a lane can find the source instead of re-deriving it.
NEGATIVES = {
    "t69": (
        "the parameter-copy class (t69_prologue)",
        "Round 34: on the 72 rows where t69's candidate was produced and vf refused it, the residue is decided "
        "at `greg`, before sched2 or dbr run - the candidate already emits the merged parameters' entry copies "
        "in parameter order while retail has body copies in declaration order, so the question is WHICH copies "
        "retail's C had as parameters, not how they were scheduled. Measured negative, all at 0: the T69_TWICE "
        "no-fold variant (2 rows change class, 0 at 0); t51's menu composed at the moved statement (43 of 45 "
        "moved insns sit on the function's opening line, where t51 has no statement: `stmt-not-simple` 44 of "
        "45); `alloc_trace.py` + t53's `wiring`/`order` menus on the colouring half (0 of 3 nearer); t53 / t37 "
        "/ a declaration reorder / the `register` keyword moved onto the parameter. Round 32 adds: `T69_CAST_"
        "COPY`, `T69_PIN_BEFORE_COPY`, `T69_TWICE` built and measured, 0 verified pins on 35 rows."),
    "address": (
        "the address / page-base class (t29_addrsym, t54_pagebase, t59_offsetsym)",
        "Round 34: t29's refusal table was opened with the pins behind it. `T29_SYMDEF` (the largest class, "
        "297 pins behind it) 164 candidate rows -> 1 hit / 1 pin, left off - its misses are MOVED / RECOLOURED "
        "at d 3-4, schedule and allocation AFTER the respelling, not spelling; `T29_NONRAM` 0 of 37, off; the "
        "copy-drop composition on t29's 97 missed rows (dropcopy / varset merges / t69's menu on the candidate "
        "text) 0 at 0, one row strictly nearer - a clean negative. t54's 126 `noop` rows are a search miss, "
        "not a blind spot: every row produces a menu, 4 sit at t54's own distance 0, and four times the verify "
        "budget (`T54_VERIFY=32 T54_COMPILERS=768`) over the 40 nearest rows bought 0 of 40. Respelling the "
        "address is not the lever left here."),
    "t51": (
        "the scheduling / statement-order class (t51_sched_order)",
        "Round 31: on 60 sites where t51's OWN independence test allows the move the residue names, 0 reach "
        "distance 0 (23 stop at 2, 26 at 4, 7 offer no such move), and 312 of the 402 sched-moved sites move "
        "three or more instructions: the body class is a REGION reschedule, not a statement swap. Round 33 "
        "adds that the re-matched pairs do not ground a composition either (a kind pair is the top cause on 14 "
        "of 1,965 sites on t51's rows). A single statement moved is measured and negative; what is untested is "
        "a rewrite that changes the whole region's dependence structure."),
    "recoloured": (
        "the allocation residues (RECOLOURED / BOTH, a register copy appearing or disappearing)",
        "Round 33: of the 898 uncovered near-band pins, 516 (57%) are RECOLOURED residues or a register copy "
        "appearing/disappearing - NO single text perturbation in the 16-kind catalogue produces those. Round "
        "34 re-measured the lever on t69's colouring half: 3 of 10 bindable sites name an allocator input and "
        "t53's menus aimed at that input reach 0 of 3 nearer. Treat a recolouring as an allocation decision "
        "(the allocator model in the brief), not as a spelling."),
    "invisible": (
        "the INVISIBLE class",
        "Round 30 (`erase_census.py`, the whole tree in 23 s): only 21 of 6,480 sites are cc1-invisible - the "
        "residue is assembler-side (maspsx / ASPSX), not something the C text decides. A pin here is not a "
        "compiler-input question at all; say so and move on."),
}
# cause kind -> negative label (a composed cause like `addr_literal+hoist` is split on `+`)
CAUSE_NEGATIVE = {
    "param_copy": "t69",
    "addr_literal": "address", "page_local": "address",
    "adjacent_swap": "t51", "stmt_shift": "t51",
}
CLASS_NEGATIVE = {"RECOLOURED": "recoloured", "BOTH": "recoloured", "INVISIBLE": "invisible"}


# ------------------------------------------------------------------ pure classifiers (unit-tested)

def fold_stratum(stratum):
    """Every stratum that is not a `build_alloc_lanes.STRATA` pack name is one fact - no usable stratum -
    and `ledger.group_key` spells that `-`."""
    return stratum if stratum in PACK_STRATA else "-"


def census_aligned(recs, macros):
    """Does the census still describe this text? `recs` are the row's per-site records, `macros` the macro
    of every site `sites_of` finds today. False when a pin was landed away since the census."""
    if len(recs) != len(macros):
        return False
    return all(0 <= r["i"] < len(macros) and macros[r["i"]] == r["macro"] for r in recs)


def near_sites(recs):
    return [r for r in recs if r.get("d0") is not None and r["d0"] <= NEAR_D0]


def covered(rec):
    """Covered at L1 or finer WITH a cause - the catalogue explains this site."""
    return rec.get("level") in COVERED_LEVELS and bool(rec.get("causes"))


def bucket_of(recs):
    """'near' (unexplained in the near band), 'far' (no near site), or 'a' (a near site is covered)."""
    near = near_sites(recs)
    if not near:
        return "far"
    return "a" if any(covered(r) for r in near) else "near"


def classify(recs, macros, served_lanes, closed_groups, family, stratum,
             repack=False, ignore_closed=False):
    """(bucket or None, refusal or None, detail).  Pure: no repo access, so the tests feed it dicts.

    `recs` per-site census/match records, `macros` today's macro per site, `served_lanes` the lanes that
    served this row ([] if none), `closed_groups` the set of CLOSED (family, stratum) pairs."""
    if not macros:
        return None, "no pin left", ""
    if not census_aligned(recs, macros):
        return None, "census stale", "census %d sites -> %d today" % (len(recs), len(macros))
    b = bucket_of(recs)
    if b == "a":
        return None, "bucket a", "a near site is covered at L1 with a cause (the generators' work)"
    if served_lanes and not repack:
        return b, "served", ",".join(served_lanes)
    key = (family, fold_stratum(stratum))
    if key in closed_groups and not ignore_closed:
        return b, "closed", "%s %s" % key
    return b, None, ""


def rank_key(rec):
    """The plan's rule: pins descending, ties by row id."""
    return (-rec["pins"], rec["id"])


def negatives_for(causes, cls):
    """The measured-negative labels that apply to a site, in order: its causes' kinds, then its residue
    class.  `causes` is the per-site `causes` list (possibly empty, as on every FAR site)."""
    out = []
    for c in causes or ():
        for kind in str(c.get("cause", "")).split("+"):
            label = CAUSE_NEGATIVE.get(kind.strip())
            if label and label not in out:
                out.append(label)
    label = CLASS_NEGATIVE.get(cls)
    if label and label not in out:
        out.append(label)
    return out


# ------------------------------------------------------------------ inputs

def read_jsonl(path):
    for line in Path(path).read_text(errors="replace").splitlines():
        if line.strip():
            yield json.loads(line)


def load_match(match_dir):
    """({row id: [per-site records, by site index]}, {row id: bucket-a split record})."""
    per = collections.defaultdict(list)
    for d in read_jsonl(Path(match_dir) / "per_site.jsonl"):
        per[d["id"]].append(d)
    for v in per.values():
        v.sort(key=lambda d: d["i"])
    split = {}
    p = Path(match_dir) / "bucket_a_split.jsonl"
    if p.exists():
        for d in read_jsonl(p):
            split[d["id"]] = d
    return dict(per), split


def load_census(path):
    """{(row id, site index): census record} - the line, the shape and the register pairs."""
    return {(d["id"], d["i"]): d for d in read_jsonl(path)}


def closed_groups(threshold=CLOSED_THRESHOLD):
    """The CLOSED (family, stratum) groups, read in-process (never `ledger.py build`, which writes)."""
    recs = ledger.load(quiet=True)
    return {(fam, st) for fam, st, _, _ in ledger.closed(recs, threshold)}, recs


# ------------------------------------------------------------------ the pool

def build_pool(match_dir, band=None, repack=False, ignore_closed=False, notes=None):
    """[row record] for every census row, each with its bucket and its refusal (None = admitted)."""
    notes = notes if notes is not None else {}
    per, split = load_match(match_dir)
    served = served_rows()
    closed, ledger_recs = closed_groups()
    strata, _src = pools.strata_by_row(notes)
    notes["ledger"] = "%d lane records, %d CLOSED group(s) at %.2f: %s" % (
        len(ledger_recs), len(closed), CLOSED_THRESHOLD,
        ", ".join("%s/%s" % g for g in sorted(closed)) or "none")
    R = {r["id"]: r for r in rows()}
    lo, hi = pools.parse_band(band) if band else (0, float("inf"))
    fold_counts = collections.Counter()
    out = []
    for rid, recs in per.items():
        r = R.get(rid)
        if not r or not clean_path(r).exists():
            out.append({"id": rid, "bucket": None, "refusal": "no such row", "detail": "",
                        "pins": 0, "recs": recs})
            continue
        text = clean_path(r).read_text(errors="replace")
        sites = sites_of(text)
        family = pools.dominant_family(pools.family_counts(text))
        stratum = strata.get(rid, "-")
        fold_counts[stratum] += 1
        bucket, refusal, detail = classify(recs, [s[1] for s in sites], served.get(rid, []), closed,
                                           family, stratum, repack, ignore_closed)
        rec = {"id": rid, "row": r, "text": text, "sites": sites, "recs": recs, "pins": len(sites),
               "family": family, "stratum": stratum, "folded": fold_stratum(stratum),
               # the group's closedness independently of WHICH refusal fired first, so the table can price
               # each guard on its own: `classify` refuses served before closed, so a served row's group
               # would otherwise be unknown and `--repack` unpriceable.
               "closed_group": (family, fold_stratum(stratum)) in closed,
               "served": served.get(rid, []), "split": split.get(rid),
               "bucket": bucket, "refusal": refusal, "detail": detail,
               "in_band": lo <= len(sites) <= hi}
        if bucket and not refusal and not rec["in_band"]:
            rec["refusal"], rec["detail"] = "out of band", "%d pins" % len(sites)
        out.append(rec)
    notes["fold"] = ", ".join("%s %d" % kv for kv in sorted(fold_counts.items()))
    # the closed count under the literal (unfolded) reading, so the fold's effect is visible
    strict = sum(1 for rec in out if rec.get("bucket") and not rec.get("served")
                 and (rec.get("family"), rec.get("stratum")) in closed)
    notes["closed_strict"] = strict
    return out, closed


def would_admit(sel, ok, guard):
    """What lifting ONE guard would admit, as (rows, pins): the rows it alone refuses, added to `ok`.

    The two guards are independent - `--repack` lifts only the served refusal, `--ignore-closed` only the
    closed one - so neither is priced by the CANDIDATE count (round 35 review: the candidate count was read
    as the `--ignore-closed` pool and overstated it 5x in rows, 6x in pins).  A served row whose group is
    also closed stays refused under `--ignore-closed`, and a row out of the `--band` stays refused under
    either, so both are excluded here."""
    if guard == "closed":
        extra = [p for p in sel if p["refusal"] == "closed" and p["in_band"]]
    else:
        extra = [p for p in sel if p["refusal"] == "served" and p["in_band"]
                 and not p.get("closed_group")]
    return len(ok) + len(extra), sum(p["pins"] for p in ok + extra)


def dry_run_table(pool, bucket, band, repack=False, ignore_closed=False):
    """The per-bucket table: candidates, refused as served, refused as closed (with the group), admitted,
    and the pin-band histogram of the admitted rows.  Each guard still standing is priced on its own."""
    sel = [p for p in pool if p.get("bucket") == bucket]
    served = [p for p in sel if p["refusal"] == "served"]
    closed = [p for p in sel if p["refusal"] == "closed"]
    oob = [p for p in sel if p["refusal"] == "out of band"]
    ok = sorted([p for p in sel if not p["refusal"]], key=rank_key)
    lines = ["bucket %s: %d candidate row(s), %d pins" % (bucket, len(sel), sum(p["pins"] for p in sel)),
             "  refused as served   %3d rows / %4d pins" % (len(served), sum(p["pins"] for p in served)),
             "  refused as closed   %3d rows / %4d pins" % (len(closed), sum(p["pins"] for p in closed))]
    groups = collections.Counter((p["family"], p["folded"]) for p in closed)
    for (fam, st), n in sorted(groups.items(), key=lambda kv: -kv[1]):
        lines.append("      %s %s: %d row(s)" % (fam, st, n))
    if band:
        lines.append("  refused out of band %3d rows (--band %s)" % (len(oob), band))
    lines.append("  ADMITTED            %3d rows / %4d pins" % (len(ok), sum(p["pins"] for p in ok)))
    # each guard lifts ONLY its own refusal: price them separately, never by the candidate count
    for flag, guard, on in (("--repack", "served", repack), ("--ignore-closed", "closed", ignore_closed)):
        if on:
            continue
        n, pins = would_admit(sel, ok, guard)
        lines.append("      lifting %-16s would admit %3d rows / %4d pins (the other guard still stands)"
                     % (flag, n, pins))
    hist = collections.Counter(pools.band(p["pins"]) for p in ok)
    lines.append("  pin band of the admitted rows: "
                 + (", ".join("%s %d" % (b, hist[b]) for b in pools.BANDS if hist[b]) or "none"))
    head = ", ".join("%s(%d)" % (p["id"], p["pins"]) for p in ok[:25])
    lines.append("  order (pins desc): " + (head or "none")
                 + (" ... +%d more" % (len(ok) - 25) if len(ok) > 25 else ""))
    return "\n".join(lines), ok


# ------------------------------------------------------------------ rows.md

def reg_pairs(fp):
    pairs = (fp or {}).get("regs") or []
    return ", ".join("%s>%s" % (a, b) for a, b in pairs) if pairs else "none"


def journal_line(split, generator):
    """The journal outcome of that generator on this text, where `bucket_a_split.jsonl` has it; '' when
    the row has no split record at all (the row head says so once)."""
    if not split:
        return ""
    seen = [(g, o) for g, o in (split.get("journal") or [])
            if generator and g.split("_")[0] in generator.replace("/", " ")]
    if not seen:
        return "no record for this generator on this text"
    return "; ".join("`%s` %s" % (g, o) for g, o in seen)


def render_site(rec, site, cens, split):
    """One site's section of rows.md.  Causes are printed only for a site within `NEAR_D0` lines: beyond
    that band round 33's control says the key names nothing, so a cause there would be noise."""
    fp = (cens or {}).get("fp") or {}
    macro, arg = site[1], site[2]
    line = (cens or {}).get("line", "?")
    d0 = rec.get("d0")
    near = d0 is not None and d0 <= NEAR_D0
    out = ["### site %d (line %s): `%s(%s)`  d0 %s, class %s, band %s%s"
           % (rec["i"], line, macro, arg, d0, rec.get("cls"), rec.get("band"),
              "" if near else "  (beyond the near band)"),
           "- shape `%s`; register pairs %s" % (fp.get("shape", "?"), reg_pairs(fp))]
    causes = (rec.get("causes") or [])[:TOP_CAUSES] if near else []
    if not near:
        out.append("- no cause: at d0 %s the catalogue's key covers its own other half at 41 / 13 / 2 / 3%% "
                   "(bands 5-8 / 9-16 / 17-32 / 33+), so nothing it says here would be evidence. The class "
                   "and shape above are the whole of what is known about this site." % d0)
    else:
        level = rec.get("level")
        out.append("- causes, level %s (%s):"
                   % (level or "none",
                      "L0 = class and band only, the opcode shape is NOT matched" if level == "L0"
                      else "matched on the opcode shape" if level in COVERED_LEVELS
                      else "no level: the catalogue has nothing with this fingerprint"))
        if not causes:
            out.append("  - none at any level: the catalogue produces nothing with this fingerprint.")
        for c in causes:
            j = journal_line(split, c.get("generator") or "")
            out.append("  - `%s` %.0f%% of the key's catalogue mass -> %s - **a compatible mechanism, not "
                       "the move**%s"
                       % (c.get("cause"), 100.0 * (c.get("share") or 0),
                          c.get("generator") or "no generator", ("  [journal: %s]" % j) if j else ""))
    labels = negatives_for(causes, rec.get("cls"))
    if labels:
        out.append("- MEASURED NEGATIVE (full text at the top of this file): "
                   + "; ".join("**%s** - %s" % (label, NEGATIVES[label][0]) for label in labels))
    else:
        out.append("- no measured negative is recorded for this class; nothing here has been ruled out.")
    return out


def render_row(rec, census):
    r, far = rec["row"], rec["bucket"] == "far"
    head = ["## %s  [%s]" % (rec["id"], "FAR" if far else "UNEXPLAINED-NEAR"),
            "- cell `%s`, %d B retail, `src/%s/%s`, %d pin site(s); family %s, stratum %s (folded %s)"
            % (r["cfg"], r["size"], r["container"], Path(r["c_path"]).name, rec["pins"],
               rec["family"], rec["stratum"], rec["folded"]),
            "- bucket: " + ("**far** - no site of this row is within %d listing lines of retail when erased "
                            "alone, so the catalogue's key says nothing about any of them." % NEAR_D0
                            if far else
                            "**unexplained-near** - this row HAS a site within %d listing lines of retail, "
                            "and not one of those near sites is covered at L1 by the catalogue with a cause. "
                            "The instrument that explains 56.5%% of the near band does not explain this row."
                            % NEAR_D0)]
    names_a_generator = any(r.get("d0") is not None and r["d0"] <= NEAR_D0 and (r.get("causes") or [])[:TOP_CAUSES]
                            for r in rec["recs"])
    if names_a_generator and not rec["split"]:
        head.append("- journal: this row is not in the catalogue's bucket-a split, so no sweep outcome is "
                    "recorded for the generators named below on this text.")
    if rec["served"]:
        head.append("- RETRY: this row was already served by %s (`--repack`); read that lane's REPORT.md "
                    "before you start and do not repeat what it measured." % ", ".join(rec["served"]))
    body = []
    for site_rec in rec["recs"]:
        body += render_site(site_rec, rec["sites"][site_rec["i"]],
                            census.get((rec["id"], site_rec["i"])), rec["split"])
    return "\n".join(head + body) + "\n"


HEADER = """# Rows

Site numbers index every `ASM_*` site of the file in source order, as `tools/pin_census.py` lists them.
`d0` is the scorer distance of erasing THAT site alone (listing lines); the class, band, shape and register
pairs are the residue fingerprint `tools/lanes/residue.py` computes (`-` is retail, `+` is the candidate).

A CAUSE is a catalogue statistic, not a diagnosis: round 33 perturbed 5,434 pin-free byte-exact rows with one
m2c-style move at a time and fingerprinted each residue, so a cause names a move whose residue has the same
fingerprint as this pin's. On the rows a generator actually landed, some catalogue kind reproduced the
pre-landing text on 45% of them - so a cause is a COMPATIBLE MECHANISM, never proof of the move. Test it, do
not assume it; and where a measured negative is named under a site, that lever is already spent.

Causes are printed only for a site at d0 <= 4. Beyond that band round 33's negative control measured that the
key covers the catalogue's own other half at 41 / 13 / 2 / 3% (bands 5-8 / 9-16 / 17-32 / 33+), so a cause
there would be noise dressed as evidence; those sites carry their class and shape and nothing else.
"""


def negatives_block(chunk):
    """The measured negatives used anywhere in this pack, in full, once."""
    used = []
    for p in chunk:
        for rec in p["recs"]:
            near = rec.get("d0") is not None and rec["d0"] <= NEAR_D0
            for label in negatives_for((rec.get("causes") or [])[:TOP_CAUSES] if near else (),
                                       rec.get("cls")):
                if label not in used:
                    used.append(label)
    if not used:
        return ""
    out = ["## Measured negatives referenced below\n",
           "Each is a measurement over a whole population, from `docs/PIN_MECHANISMS_20260912.md`. Where a "
           "site names one, that lever is spent: do not re-derive it.\n"]
    for label in used:
        title, text = NEGATIVES[label]
        out.append("**%s** - %s: %s\n" % (label, title, text))
    return "\n".join(out)


# ------------------------------------------------------------------ main

def write_pack(name, chunk, census, brief_text, repack):
    L = ROOT / "work/native_lane" / name
    assert not (L / "last_message.txt").exists(), name
    (L / "out").mkdir(parents=True, exist_ok=True)
    head = [HEADER]
    if repack and any(p["served"] for p in chunk):
        head.append("**RETRY PACK** (`--repack`): %s.\n"
                    % "; ".join("%s served by %s" % (p["id"], ",".join(p["served"]))
                                for p in chunk if p["served"]))
    block = negatives_block(chunk)
    if block:
        head.append(block)
    (L / "rows.md").write_text("\n".join(head + [render_row(p, census) for p in chunk]))
    for p in chunk:
        cont, nm = p["id"].split("/")
        (L / "base" / cont).mkdir(parents=True, exist_ok=True)
        (L / "base" / cont / (nm + ".c")).write_text(p["text"])
        (L / "base" / cont / (nm + ".c.base_sha")).write_text(sha_text(p["text"]))
    buckets = collections.Counter(p["bucket"] for p in chunk)
    kind = ("rows the catalogue cannot explain in the near band" if not buckets["far"] else
            "rows the catalogue cannot see at all (the far band)" if not buckets["near"] else
            "rows the catalogue cannot explain (near band) and rows it cannot see (far band)")
    retry = ("\n**This is a RETRY pack**: every row below was served by an earlier lane, named in `rows.md`. "
             "Read that lane's REPORT.md first and do not repeat what it measured.\n" if repack else "")
    (L / "BRIEF.md").write_text(brief_text.replace("@LANE@", name).replace("@NROWS@", str(len(chunk)))
                                .replace("@ROOT@", str(ROOT)).replace("@HOME@", str(Path.home()))
                                .replace("@BUCKET@", kind).replace("@RETRY@", retry)
                                .replace("@NEAR@", str(buckets["near"])).replace("@FAR@", str(buckets["far"])))
    (L / "PROMPT.txt").write_text(
        f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; "
        f"gcc -da writes its dumps into the current directory, and lanes have left dozens "
        f"of dump files at the repo root.\nRead work/native_lane/{name}/BRIEF.md and follow it "
        f"exactly. Work only inside work/native_lane/{name}/ and never write files at the repo "
        f"root. When done, end with one line per row: row, result, the change in one sentence, "
        f"the mechanism in one sentence, the generator rule in one sentence, and what did not work.\n")
    return L


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="+", help="pack names; successive packs take successive slices of the pool")
    ap.add_argument("--bucket", choices=("near", "far", "both"), default="near",
                    help="which admission bucket to serve (default near); `both` merges the two pools and "
                         "ranks them together by pins, each row labelled with its bucket")
    ap.add_argument("--per", type=int, default=12)
    ap.add_argument("--band", help="pin-count band (1-3, 4-8, 21+ ...): filter FIRST, then rank by pins inside it")
    ap.add_argument("--repack", action="store_true",
                    help="admit rows already served by a lane (a deliberate retry pack; rows.md and BRIEF.md "
                         "name the lanes that served each row)")
    ap.add_argument("--ignore-closed", action="store_true",
                    help="admit rows in a CLOSED (family, stratum) group (ledger.py --closed 0.2)")
    ap.add_argument("--dry-run", action="store_true", help="print the tables and the composition; write nothing")
    ap.add_argument("--match", default=str(MATCH), help="the match directory (per_site.jsonl, bucket_a_split.jsonl)")
    ap.add_argument("--census", default=str(CENSUS), help="the fingerprinted census (census_fp2.jsonl)")
    a = ap.parse_args(argv)

    notes = {}
    pool, _closed = build_pool(a.match, a.band, a.repack, a.ignore_closed, notes)
    census = load_census(a.census)
    stale = [p for p in pool if p["refusal"] in ("census stale", "no pin left", "no such row")]
    print("census %s: %d rows, %d sites" % (Path(a.match).name, len(pool), sum(len(p["recs"]) for p in pool)))
    print("  %s" % notes.get("traces", "no traces"))
    print("  strata folded to `-`: %s" % notes.get("fold", "-"))
    print("  %s (ledger/lanes.jsonl mtime %s)"
          % (notes.get("ledger", "?"),
             __import__("time").strftime("%Y-%m-%dT%H:%M:%SZ",
                                         __import__("time").gmtime((ROOT / ledger.LEDGER).stat().st_mtime))))
    print("  closed rows under the LITERAL (unfolded) reading: %d; under the folded reading: %d"
          % (notes.get("closed_strict", 0), sum(1 for p in pool if p["refusal"] == "closed")))
    print("  dropped as census-stale / no pin left: %d row(s): %s"
          % (len(stale), ", ".join("%s (%s)" % (p["id"], p["detail"] or p["refusal"]) for p in stale) or "none"))
    print("  bucket a (a near site covered at L1 with a cause): %d row(s)"
          % sum(1 for p in pool if p["refusal"] == "bucket a"))
    print()

    picked = []
    for bucket in (("near", "far") if a.bucket == "both" else (a.bucket,)):
        table, ok = dry_run_table(pool, bucket, a.band, a.repack, a.ignore_closed)
        print(table)
        print()
        picked += ok
    picked.sort(key=rank_key)

    # the join must be total for any row we are about to write
    missing = [(p["id"], r["i"]) for p in picked[:a.per * len(a.lanes)] for r in p["recs"]
               if (p["id"], r["i"]) not in census]
    if missing:
        raise SystemExit("census_fp2 has no record for %d site(s), e.g. %s" % (len(missing), missing[:3]))

    brief_text = BRIEF.read_text()
    it = iter(picked)
    for name in a.lanes:
        chunk = [p for _, p in zip(range(a.per), it)]
        if not chunk:
            print(name, "no rows left")
            continue
        assert_unserved([p["id"] for p in chunk], a.repack)      # never re-serve a row by accident
        if a.dry_run:
            print("%s %d rows (dry run, nothing written): %s"
                  % (name, len(chunk), ", ".join("%s %s %dp" % (p["id"], p["bucket"], p["pins"])
                                                 for p in chunk)))
            continue
        L = write_pack(name, chunk, census, brief_text, a.repack)
        print("%s %d rows -> %s" % (name, len(chunk), L.relative_to(ROOT)))
        for p in chunk:
            print("    %-34s %s  pins=%-3d family=%-5s stratum=%s" % (p["id"], p["bucket"], p["pins"],
                                                                      p["family"], p["folded"]))


if __name__ == "__main__":
    main()
