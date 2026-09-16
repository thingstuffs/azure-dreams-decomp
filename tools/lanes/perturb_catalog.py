#!/usr/bin/env python3
"""The round-33 FORWARD perturbation catalogue: what each m2c-style C move costs, measured on the
5,467 byte-exact rows that carry no pin - and the match that gives every pinned site its ranked causes.

    python3 tools/lanes/perturb_catalog.py sample --n 1000 --seed 20260916 \\
            --out work/native_lane/r33_catalog/rows/sample_rows.txt
    python3 tools/lanes/perturb_catalog.py run ROWS.txt OUT.jsonl [--procs 6] [--per-kind 3] \\
            [--per-row 12] [--kinds k1,k2] [--two-move] [--phase]
    python3 tools/lanes/perturb_catalog.py summary OUT.jsonl
    python3 tools/lanes/perturb_catalog.py match --census CENSUS.jsonl --catalog CAT.jsonl \\
            [--catalog2 CAT2.jsonl] --out DIR [--min 5]

The direction, on both sides, is the census's: `ref` is RETAIL's listing and `cand` the m2c-like
text's, so the `-` lines of every diff are retail's.  On the census side (`erase_census.py --fp`)
`ref` is the PINNED text and `cand` the text with one site erased; here `ref` is a PIN-FREE row's
text - byte-exact as it stands, so its listing IS retail's - and `cand` the same text with ONE
perturbation applied.  Each perturbation is a generator's move reversed: the catalogue therefore
speaks the generators' language, and a pinned site's fingerprint can be looked up among the
catalogue's to name the C move that produces that residue (`tools/lanes/residue.py`).

The kinds come from two modules that never import each other, both to the same contract
(`PERTURBATIONS = [(kind, fn)]`, `fn(text, detail=None) -> [(params, new_text)]`):
`perturb_basic` (the text-level moves) and `perturb_struct` (the structural ones), the second
imported optionally - the run logs which modules loaded and goes on without it.

`run` writes ONE record per compiled instance (`id`, `kind`, `params`, `fp`, and `nobuild` when cc1
refuses the perturbed text), one `done` marker per finished row - a row that yields no instance is
finished too, and without the marker it would be recompiled on every resume - and the kinds' refusal
counters into `OUT.refusals.json` (merged on resume).  `fp.cls == INVISIBLE` records are KEPT: a move
cc1 cannot see is a finding, never a cause.  `--two-move` adds the ordered pairs of a row's own
chosen instances (the second kind re-enumerated on the first's text), so compositions have
fingerprints too.  `--phase` adds the first differing RTL pass on the near records only (`d` 1..4);
it costs about 40 compiles' worth of time each and is never a gate input.

Keep OUT under `work/perturb_catalog/` or a lane's `scratch/` (both behind a `.ignore`): a 1,000-row
catalogue is tens of MB of JSONL.
"""
import argparse
import collections
import json
import os
import random
import re
import sys
import time
import zlib
from multiprocessing import Pool
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
for _p in (str(ROOT / "tools"), str(ROOT / "tools/xform"), str(ROOT / "tools/lanes")):
    if _p not in sys.path:
        sys.path.insert(0, _p)
from common import rows as all_rows, clean_path                     # noqa: E402
from pin_census import sites_of                                     # noqa: E402
from screen import compile_s                                        # noqa: E402
import residue                                                      # noqa: E402
import perturb_basic                                                # noqa: E402

PP_IN_BODY = re.compile(r"^[ \t]*#[ \t]*(?:if|ifdef|ifndef|else|elif|endif)\b", re.M)
TWO_MOVE_CAP = 100
DEFAULT_SEED = 20260916

# Which generator already spells a kind's inverse (the (a)/(b) split of the round-33 plan).
KIND_GENERATOR = {
    "param_copy": "t69_prologue",
    "hoist": "varset.inline_def / t64",
    "decl_reorder": "t53 decl-swap",
    "retype_void": "varset.retype_ptr / t64",
    "split": "varset.split_def / t64",
    "merge": "varset.merge_local + merge_param / t64",
    "width_change": "t36 / t37",
    "adjacent_swap": "t51",
    "local_alias": "natural.dropcopy",
    "page_local": "t54 / t59",
    "goto_to_loop": "t41 / t41b",
}


def load_modules(log=True):
    """`perturb_basic` plus `perturb_struct` when the other implementer's module is present."""
    mods = [("perturb_basic", perturb_basic)]
    try:
        import perturb_struct                                       # noqa: F401
        mods.append(("perturb_struct", perturb_struct))
    except Exception as e:                                          # a half-written sibling raises anything
        if log:
            print("perturb_struct not loaded (%s: %s)" % (type(e).__name__, e), flush=True)
    if log:
        print("modules:", ", ".join("%s(%d kinds)" % (n, len(m.PERTURBATIONS)) for n, m in mods), flush=True)
    return mods


def kinds_of(mods, only=None):
    out = []
    for _, m in mods:
        for kind, fn in m.PERTURBATIONS:
            if only is None or kind in only:
                out.append((kind, fn))
    return out


# --------------------------------------------------------------------------- population / sample

def population():
    """The catalogue's rows: registered, clean text present, NO pin site, no `#if` in a body."""
    keep, excl = [], collections.Counter()
    for r in all_rows():
        p = clean_path(r)
        if not p.exists():
            excl["no-clean-file"] += 1
            continue
        if not r.get("cfg"):
            excl["no-compiler-recipe"] += 1
            continue
        text = p.read_text(errors="replace")
        if sites_of(text):
            excl["has-pin-sites"] += 1
            continue
        if _pp_in_body(text):
            excl["preprocessor-conditional-in-a-function-body"] += 1
            continue
        keep.append((r, len(text.splitlines())))
    return keep, excl


def _pp_in_body(text):
    ctx = perturb_basic.Ctx(text)
    return any(fn["pp"] for fn in ctx.fns)


def sample(args):
    pop, excl = population()
    print("pin-free rows with a clean file: %d" % (len(pop) + excl["preprocessor-conditional-in-a-function-body"]))
    for k, v in excl.most_common():
        print("  excluded %-46s %5d" % (k, v))
    print("catalogue population: %d rows" % len(pop))
    sizes = sorted(n for _, n in pop)
    t1, t2 = sizes[len(sizes) // 3], sizes[2 * len(sizes) // 3]

    def tercile(n):
        return "small" if n <= t1 else ("medium" if n <= t2 else "large")

    strata = collections.defaultdict(list)
    for r, n in pop:
        strata[(r["container"], tercile(n))].append(r["id"])
    for k in strata:
        strata[k].sort()
    total = sum(len(v) for v in strata.values())
    want = min(args.n, total)
    # proportional allocation, largest remainder, then a deterministic top-up
    raw = {k: want * len(v) / total for k, v in strata.items()}
    draw = {k: min(len(strata[k]), int(v)) for k, v in raw.items()}
    for k in sorted(strata, key=lambda k: (-(raw[k] - int(raw[k])), k)):
        if sum(draw.values()) >= want:
            break
        if draw[k] < len(strata[k]):
            draw[k] += 1
    rnd = random.Random(args.seed)
    picked = []
    for k in sorted(strata):
        picked += sorted(rnd.sample(strata[k], draw[k]))
    picked.sort()
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("\n".join(picked) + "\n")
    man = out.parent / "sample_manifest.txt"
    lines = ["round-33 perturbation catalogue - sample manifest",
             "seed %d   requested %d   drawn %d   population %d rows (terciles by line count: "
             "small <= %d, medium <= %d, large > %d)" % (args.seed, args.n, len(picked), total, t1, t2, t2),
             "",
             "%-12s %-8s %10s %8s" % ("container", "tercile", "population", "draw")]
    for k in sorted(strata):
        lines.append("%-12s %-8s %10d %8d" % (k[0], k[1], len(strata[k]), draw[k]))
    lines += ["", "excluded from the population:"]
    for k, v in excl.most_common():
        lines.append("  %-50s %5d" % (k, v))
    man.write_text("\n".join(lines) + "\n")
    print("wrote %s (%d rows) and %s" % (out, len(picked), man))


# --------------------------------------------------------------------------- run

ROWS = None
MODS = None
CFG = {}


def _rows():
    global ROWS
    if ROWS is None:
        ROWS = {r["id"]: r for r in all_rows()}
    return ROWS


def _init(cfg):
    global MODS, CFG
    CFG = cfg
    MODS = load_modules(log=False)
    _rows()


def _pick(rid, kind, instances, n):
    """`n` instances of a kind, chosen deterministically (a seed derived from the row and the kind,
    so adding a kind never reshuffles another) and returned in site order."""
    if len(instances) <= n:
        return list(range(len(instances)))
    idx = list(range(len(instances)))
    random.Random(zlib.crc32(("%s|%s" % (rid, kind)).encode())).shuffle(idx)
    return sorted(idx[:n])


def _phase_pass(row, text, cand):
    """The first RTL pass whose operation sequence differs (phase_census's dumps), or None."""
    import phase_census as PC
    a = PC.compile_dumps(row, text)
    b = PC.compile_dumps(row, cand)
    if a is None or b is None:
        return None
    for p in PC.PHASES:
        if p in a["dumps"] and p in b["dumps"]:
            if PC.features(a["dumps"][p])[1] != PC.features(b["dumps"][p])[1]:
                return p
    return "none"


def one(rid):
    row = _rows().get(rid)
    out, refus = [], collections.defaultdict(collections.Counter)
    if row is None or not row.get("cfg"):
        return [dict(id=rid, done=True, n=0, err="no-row-or-cfg")], refus
    text = clean_path(row).read_text(errors="replace")
    if sites_of(text):
        return [dict(id=rid, done=True, n=0, err="has-pin-sites")], refus
    ref = compile_s(row, text)
    if ref is None:
        return [dict(id=rid, done=True, n=0, err="ref-build")], refus
    chosen = []                                  # (kind, params, new_text)
    per_kind = {}
    for kind, fn in kinds_of(MODS, CFG.get("kinds")):
        d = collections.Counter()
        try:
            ins = fn(text, d)
        except Exception as e:
            refus[kind]["EXCEPTION:" + type(e).__name__] += 1
            continue
        refus[kind].update(d)
        take = [ins[i] for i in _pick(rid, kind, ins, CFG["per_kind"])]
        per_kind[kind] = (fn, take)
    # round-robin over the kinds so one prolific kind cannot eat the row's budget
    pools = {k: list(v[1]) for k, v in per_kind.items()}
    while len(chosen) < CFG["per_row"] and any(pools.values()):
        for kind in sorted(pools):
            if not pools[kind] or len(chosen) >= CFG["per_row"]:
                continue
            params, new = pools[kind].pop(0)
            chosen.append((kind, params, new))
    for kind, params, new in chosen:
        c = compile_s(row, new)
        fp = residue.fingerprint(ref, c)
        rec = dict(id=rid, kind=kind, params=params, fp=fp)
        if c is None:
            rec["nobuild"] = True
        if CFG.get("phase") and fp["d"] is not None and 1 <= fp["d"] <= 4:
            rec["phase"] = _phase_pass(row, text, new)
        out.append(rec)
    if CFG.get("two_move") and len(chosen) > 1:
        pairs = 0
        for k1, p1, t1 in chosen:
            for k2, p2, _t2 in chosen:
                if pairs >= TWO_MOVE_CAP:
                    break
                if p1 is p2:
                    continue
                fn2 = dict(kinds_of(MODS, CFG.get("kinds")))[k2]
                try:
                    ins2 = fn2(t1, collections.Counter())
                except Exception as e:
                    refus[k2]["EXCEPTION-2:" + type(e).__name__] += 1
                    continue
                if not ins2:
                    refus[k2]["two-move-no-instance-after-" + k1] += 1
                    continue
                q, t2 = min(ins2, key=lambda z: (abs(z[0]["site"] - p2["site"]), z[0]["site"]))
                c = compile_s(row, t2)
                fp = residue.fingerprint(ref, c)
                rec = dict(id=rid, kinds=[k1, k2], params=[p1, q], fp=fp)
                if c is None:
                    rec["nobuild"] = True
                out.append(rec)
                pairs += 1
    out.append(dict(id=rid, done=True, n=len(out)))
    return out, refus


def run(args):
    mods = load_modules()
    ids = [x.split()[0] for x in Path(args.rows).read_text().splitlines() if x.strip()
           and not x.startswith("#")]
    out = Path(args.out)
    out.parent.mkdir(parents=True, exist_ok=True)
    done = set()
    if out.exists():
        for l in out.open():
            try:
                r = json.loads(l)
                if r.get("done"):
                    done.add(r["id"])
            except Exception:
                pass
    todo = [i for i in ids if i not in done]
    print("%d rows, %d already done, %d to do" % (len(ids), len(done), len(todo)), flush=True)
    cfg = dict(per_kind=args.per_kind, per_row=args.per_row, two_move=args.two_move,
               phase=args.phase, kinds=set(args.kinds.split(",")) if args.kinds else None)
    rpath = Path(str(out) + ".refusals.json")
    refus = collections.defaultdict(collections.Counter)
    if rpath.exists():
        for k, v in json.loads(rpath.read_text()).items():
            refus[k].update(v)
    t0, n, inst = time.time(), 0, 0
    with Pool(args.procs, initializer=_init, initargs=(cfg,)) as p, out.open("a") as f:
        for recs, rf in p.imap_unordered(one, todo, chunksize=2):
            for r in recs:
                f.write(json.dumps(r) + "\n")
                inst += 0 if r.get("done") else 1
            f.flush()
            for k, v in rf.items():
                refus[k].update(v)
            n += 1
            if n % 50 == 0:
                print("%d/%d rows  %d instances  %ds" % (n, len(todo), inst, time.time() - t0), flush=True)
                rpath.write_text(json.dumps({k: dict(v) for k, v in refus.items()}, indent=1, sort_keys=True))
    rpath.write_text(json.dumps({k: dict(v) for k, v in refus.items()}, indent=1, sort_keys=True))
    print("done %d rows, %d instances, %ds; refusals in %s" % (n, inst, time.time() - t0, rpath))


# --------------------------------------------------------------------------- summary

def _load(path, want_pairs=None):
    for l in Path(path).open():
        if not l.strip():
            continue
        r = json.loads(l)
        if r.get("done"):
            continue
        if want_pairs is None or (("kinds" in r) == want_pairs):
            yield r


def _dist(c, n):
    return "  ".join("%s %d (%.0f%%)" % (k, v, 100.0 * v / max(1, n)) for k, v in c.most_common())


def summary(path, fh=sys.stdout):
    singles = collections.defaultdict(list)
    pairs = collections.defaultdict(list)
    rows_seen = set()
    for r in _load(path):
        rows_seen.add(r["id"])
        (pairs["+".join(r["kinds"])] if "kinds" in r else singles[r["kind"]]).append(r)
    n_all = sum(len(v) for v in singles.values()) + sum(len(v) for v in pairs.values())
    print("catalogue %s: %d rows, %d instances (%d single, %d two-move)"
          % (path, len(rows_seen), n_all, sum(len(v) for v in singles.values()),
             sum(len(v) for v in pairs.values())), file=fh)
    for title, group in (("single moves", singles), ("two-move compositions", pairs)):
        if not group:
            continue
        print("\n%s" % title.upper(), file=fh)
        for kind in sorted(group, key=lambda k: -len(group[k])):
            rs = group[kind]
            nb = sum(1 for r in rs if r.get("nobuild"))
            cls = collections.Counter(r["fp"]["cls"] for r in rs)
            band = collections.Counter(r["fp"]["band"] for r in rs)
            print("\n  %-28s instances %5d   nobuild %4d (%.0f%%)   INVISIBLE %.0f%%"
                  % (kind, len(rs), nb, 100.0 * nb / len(rs), 100.0 * cls["INVISIBLE"] / len(rs)), file=fh)
            print("      class  %s" % _dist(cls, len(rs)), file=fh)
            print("      d band %s" % _dist(band, len(rs)), file=fh)
            keys = collections.Counter(r["fp"]["L1"] for r in rs)
            print("      top L1 keys:", file=fh)
            for k, v in keys.most_common(10):
                print("        %5d  %s" % (v, k[:110]), file=fh)


# --------------------------------------------------------------------------- match

def family(macro):
    if macro.startswith("ASM_REG"):
        return "REG"
    if macro.startswith("ASM_KEEP"):
        return "KEEP"
    return "FENCE" if macro in ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER") else "other"


def pin_band(n):
    return "1" if n <= 1 else "2-6" if n <= 6 else "7-20" if n <= 20 else "21+"


def _cause(rec):
    return "+".join(rec["kinds"]) if "kinds" in rec else rec["kind"]


def generator_of(cause):
    parts = cause.split("+")
    gens = [KIND_GENERATOR.get(p) for p in parts]
    return " + ".join(g for g in gens if g) if all(gens) else None


def match(args):
    out = Path(args.out)
    out.mkdir(parents=True, exist_ok=True)
    cat = collections.defaultdict(collections.Counter)      # level key -> Counter(cause)
    n_cat = 0
    skipped = collections.Counter()
    for path in [args.catalog] + ([args.catalog2] if args.catalog2 else []):
        for r in _load(path):
            # an INVISIBLE move is kept in the catalogue (it is a finding) but is never a CAUSE: it
            # would otherwise "explain" the 21 census sites at d0 == 0, the assembler-side class
            # round 30 closed.  A NOBUILD record explains nothing either.
            if r["fp"]["cls"] in ("INVISIBLE", "NOBUILD"):
                skipped[r["fp"]["cls"]] += 1
                continue
            c = _cause(r)
            for lvl in ("L0", "L1", "L2"):
                cat[(lvl, r["fp"][lvl])][c] += 1
            n_cat += 1
    sites = [r for r in (json.loads(l) for l in Path(args.census).open() if l.strip())
             if "fp" in r and "err" not in r]
    print("catalogue instances usable as causes %d (%s not a cause); distinct keys L0/L1/L2 %d/%d/%d;"
          " census sites with fp %d"
          % (n_cat, ", ".join("%s %d" % (k, v) for k, v in sorted(skipped.items())) or "none",
             *[sum(1 for k in cat if k[0] == lvl) for lvl in ("L0", "L1", "L2")], len(sites)))

    per_site, rowinfo = [], collections.defaultdict(list)
    cov = collections.Counter()
    for s in sites:
        fp = s["fp"]
        level, causes, mass = None, [], 0
        for lvl in ("L2", "L1", "L0"):
            c = cat.get((lvl, fp[lvl]))
            if c and sum(c.values()) >= args.min:
                level, mass = lvl, sum(c.values())
                causes = [(k, v, v / mass) for k, v in c.most_common()]
                break
        rec = dict(id=s["id"], i=s.get("i"), macro=s.get("macro"), d0=s.get("d0"),
                   n=s.get("n"), cls=fp["cls"], band=fp["band"],
                   L0=fp["L0"], L1=fp["L1"], L2=fp["L2"], level=level,
                   mass=mass, causes=[dict(cause=k, n=v, share=round(sh, 3),
                                           generator=generator_of(k)) for k, v, sh in causes[:6]])
        per_site.append(rec)
        rowinfo[s["id"]].append(rec)
        for lvl in ("L0", "L1", "L2"):
            c = cat.get((lvl, fp[lvl]))
            if c and sum(c.values()) >= args.min:
                cov[lvl] += 1
        if level:
            cov["any"] += 1
    with (out / "per_site.jsonl").open("w") as f:
        for r in per_site:
            f.write(json.dumps(r) + "\n")

    tables = []
    n = len(per_site)

    def tab(title, lines):
        tables.append((title, lines))
        (out / (re.sub(r"\W+", "_", title.lower()).strip("_") + ".txt")).write_text(
            title + "\n" + "=" * len(title) + "\n" + "\n".join(lines) + "\n")

    # 1. coverage
    L = ["sites %d   catalogue instances usable as causes %d (INVISIBLE %d and NOBUILD %d kept in the"
         " catalogue but never a cause)   --min %d"
         % (n, n_cat, skipped["INVISIBLE"], skipped["NOBUILD"], args.min), ""]
    L.append("%-10s %8s %7s" % ("level", "covered", "share"))
    for lvl in ("L0", "L1", "L2", "any"):
        L.append("%-10s %8d %6.1f%%" % (lvl, cov[lvl], 100.0 * cov[lvl] / max(1, n)))
    for name, keyf in (("d band", lambda r: r["band"]), ("residue class", lambda r: r["cls"]),
                       ("row pin band", lambda r: pin_band(r["n"] or 1)),
                       ("macro family", lambda r: family(r["macro"] or ""))):
        L += ["", "coverage by %s" % name,
              "%-12s %7s %9s %9s %9s" % (name, "sites", "cov L0", "cov L1", "cov L2")]
        groups = collections.defaultdict(list)
        for r in per_site:
            groups[keyf(r)].append(r)
        for g in sorted(groups):
            rs = groups[g]
            c = {lvl: sum(1 for r in rs if _covered_at(cat, r, lvl, args.min)) for lvl in ("L0", "L1", "L2")}
            L.append("%-12s %7d %8.1f%% %8.1f%% %8.1f%%"
                     % (g, len(rs), 100.0 * c["L0"] / len(rs), 100.0 * c["L1"] / len(rs),
                        100.0 * c["L2"] / len(rs)))
    tab("coverage", L)

    # 2. concentration
    L = ["the top-10 keys' share of the catalogue's mass and of the census's, per level", ""]
    for lvl in ("L0", "L1", "L2"):
        ckeys = collections.Counter({k[1]: sum(v.values()) for k, v in cat.items() if k[0] == lvl})
        skeys = collections.Counter(r[lvl] for r in per_site)
        ctop = sum(v for _, v in ckeys.most_common(10))
        stop = sum(v for _, v in skeys.most_common(10))
        L.append("%s: catalogue keys %d, top-10 = %.1f%% of catalogue mass; census keys %d, "
                 "top-10 = %.1f%% of census mass"
                 % (lvl, len(ckeys), 100.0 * ctop / max(1, sum(ckeys.values())), len(skeys),
                    100.0 * stop / max(1, sum(skeys.values()))))
        for k, v in skeys.most_common(10):
            L.append("    census %5d  catalogue %5d  %s" % (v, ckeys.get(k, 0), k[:100]))
    tab("concentration", L)

    # 3. cause purity
    L = ["for every covered site, the share of its key's catalogue mass held by the TOP cause", ""]
    pur = collections.Counter()
    for r in per_site:
        if r["level"]:
            pur[min(10, int(r["causes"][0]["share"] * 10))] += 1
    tot = sum(pur.values())
    L.append("%-12s %7s %7s" % ("top share", "sites", "share"))
    for b in sorted(pur):
        L.append("%-12s %7d %6.1f%%" % ("%d-%d%%" % (b * 10, min(100, b * 10 + 10)), pur[b],
                                        100.0 * pur[b] / max(1, tot)))
    L += ["", "the top cause by site count (covered sites only):"]
    top = collections.Counter(r["causes"][0]["cause"] for r in per_site if r["level"])
    for k, v in top.most_common(20):
        L.append("  %-40s %6d  generator %s" % (k, v, generator_of(k) or "-"))
    tab("cause purity", L)

    # 4. the uncovered keys
    L = ["L1 keys of the census that the catalogue does not reach %d times - the residues no single"
         " move (or pair) in the catalogue produces" % args.min, ""]
    unc = collections.Counter()
    for r in per_site:
        if not _covered_at(cat, r, "L1", args.min):
            unc[r["L1"]] += 1
    L.append("uncovered L1 keys %d, pins behind them %d (%.1f%% of sites)"
             % (len(unc), sum(unc.values()), 100.0 * sum(unc.values()) / max(1, n)))
    L.append("")
    for k, v in unc.most_common(40):
        L.append("  %6d  catalogue %4d  %s" % (v, sum((cat.get(("L1", k)) or {}).values()), k[:110]))
    tab("uncovered keys", L)

    # 5. the per-row buckets
    buckets, bpins = collections.Counter(), collections.Counter()
    brows = collections.defaultdict(list)
    for rid, rs in rowinfo.items():
        b = "c"
        if any(r["level"] in ("L1", "L2") and r["causes"] and r["causes"][0]["generator"] for r in rs):
            b = "a"
        elif any(r["level"] in ("L1", "L2") for r in rs):
            b = "b"
        elif any(r["level"] == "L0" for r in rs):
            b = "weak"
        buckets[b] += 1
        bpins[b] += len(rs)
        brows[b].append(rid)
    L = ["a     some site covered at L1 or finer whose top cause has a generator (open its refusals)",
         "b     covered at L1 or finer, but the top cause's kind has no generator (build one)",
         "weak  covered at L0 only (the class is known, the shape is not)",
         "c     no site covered (the rows only a model rewrites)", "",
         "%-6s %7s %7s" % ("bucket", "rows", "pins")]
    for b in ("a", "b", "weak", "c"):
        L.append("%-6s %7d %7d" % (b, buckets[b], bpins[b]))
    L.append("%-6s %7d %7d" % ("total", sum(buckets.values()), sum(bpins.values())))
    for b in ("a", "b", "weak", "c"):
        (out / ("bucket_%s_rows.txt" % b)).write_text("\n".join(sorted(brows[b])) + "\n")
    L += ["", "row lists in bucket_<a|b|weak|c>_rows.txt, per-site causes in per_site.jsonl"]
    tab("row buckets", L)

    with (out / "summary.txt").open("w") as f:
        print("round-33 catalogue match: census %s, catalogue %s%s"
              % (args.census, args.catalog, (" + " + args.catalog2) if args.catalog2 else ""), file=f)
        for title, lines in tables:
            print("\n\n%s\n%s" % (title.upper(), "=" * len(title)), file=f)
            print("\n".join(lines), file=f)
    print("wrote %d tables + per_site.jsonl + summary.txt in %s" % (len(tables), out))


def _covered_at(cat, rec, lvl, minimum):
    c = cat.get((lvl, rec[lvl]))
    return bool(c) and sum(c.values()) >= minimum


# --------------------------------------------------------------------------- cli

def main():
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    a = sub.add_parser("sample")
    a.add_argument("--n", type=int, default=1000)
    a.add_argument("--seed", type=int, default=DEFAULT_SEED)
    a.add_argument("--out", default=str(ROOT / "work/native_lane/r33_catalog/rows/sample_rows.txt"))
    b = sub.add_parser("run")
    b.add_argument("rows")
    b.add_argument("out")
    b.add_argument("--procs", type=int, default=6)
    b.add_argument("--per-kind", type=int, default=3)
    b.add_argument("--per-row", type=int, default=12)
    b.add_argument("--kinds")
    b.add_argument("--two-move", action="store_true")
    b.add_argument("--phase", action="store_true")
    c = sub.add_parser("summary")
    c.add_argument("jsonl")
    d = sub.add_parser("match")
    d.add_argument("--census", required=True)
    d.add_argument("--catalog", required=True)
    d.add_argument("--catalog2")
    d.add_argument("--out", required=True)
    d.add_argument("--min", type=int, default=5)
    args = ap.parse_args()
    if args.cmd == "sample":
        sample(args)
    elif args.cmd == "run":
        run(args)
    elif args.cmd == "summary":
        summary(args.jsonl)
    else:
        match(args)


if __name__ == "__main__":
    main()
