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
#
# CORRECTED after the round-33 text oracle (report_oracle.txt §2, "THE TWO ROWS WITH THE WRONG
# CAUSE", and §4's method list).  Three entries named a generator that does not make the move:
#   * `merge` / `split` are t51_sched_order's moves as much as t64's.  t51's own docstring records
#     `single-set lifetime split 27` of the 61 rows of its first sweep, with the split lifetimes
#     named `<var>_2`; the oracle found two t51 landings (dungeon/func_8133985C,
#     main/func_80012F0C) that ONLY `merge` reproduces, with labels `merge:merge_local:frame>
#     frame_2`.  Until this line said t51 the catalogue named the wrong generator on that class.
#   * `local_alias` is t20_fencefree's and t61_naturalkeep's landing as well as natural.dropcopy's
#     - 24 t20 rows and 6 t61 rows in the oracle's population, against 0 for dropcopy alone.
#   * `tail_merge` (implementer D's kind) is t15_shapes.dup_after_if's move, which arrives on rows
#     the journals attribute to t61_naturalkeep - the oracle's §3 shape 4, 12 rows.
KIND_GENERATOR = {
    "param_copy": "t69_prologue",
    "hoist": "varset.inline_def / t64",
    "cond_temp": "varset.inline_def / t64",
    "decl_reorder": "t53 decl-swap",
    "retype_void": "varset.retype_ptr / t64",
    "split": "varset.split_def / t64 + t51 split lever",
    "merge": "varset.merge_local + merge_param / t64 + t51 split lever",
    "width_change": "t36 / t37",
    "adjacent_swap": "t51",
    "stmt_shift": "t51",
    "local_alias": "natural.dropcopy / t20 / t61",
    "page_local": "t54 / t59",
    "addr_literal": "t29_addrsym / t54",
    "goto_to_loop": "t41 / t41b",
    "tail_merge": "t15_shapes.dup_after_if / t61_naturalkeep",
    "dup_tail": "t15_shapes.dup_after_if",
}

# The same table in the sweep journals' own vocabulary: the `transform` values whose records are
# evidence that this kind's generator has run on a row.  KIND_GENERATOR's strings are prose and
# never match a journal record; this is what `match --bucket-a-split` looks up.
KIND_TRANSFORMS = {
    "param_copy": ["t69_prologue"],
    "hoist": ["t64_varset"],
    "cond_temp": ["t64_varset"],
    "decl_reorder": ["t53_reg_state", "t53k_keep"],
    "retype_void": ["t64_varset"],
    "split": ["t64_varset", "t51_sched_order"],
    "merge": ["t64_varset", "t51_sched_order"],
    "width_change": ["t36_paramwidth", "t37_localwidth", "t37b_localwidth_keep"],
    "adjacent_swap": ["t51_sched_order"],
    "stmt_shift": ["t51_sched_order"],
    "local_alias": ["t20_fencefree", "t61_naturalkeep"],
    "page_local": ["t54_pagebase", "t59_offsetsym"],
    "addr_literal": ["t29_addrsym", "t54_pagebase"],
    "goto_to_loop": ["t41_gotoloop", "t41b_gotoloop_while", "t41c_gotoloop_greedy",
                     "t44_doloop_greedy"],
    "tail_merge": ["t15_shapes", "t61_naturalkeep"],
    "dup_tail": ["t15_shapes"],
}


def transforms_of(cause):
    """The journal transforms behind a cause (`a+b` for a two-move composition)."""
    out = []
    for part in cause.split("+"):
        for t in KIND_TRANSFORMS.get(part, []):
            if t not in out:
                out.append(t)
    return out


def l1f_of(fp):
    """`L1f` from a fingerprint record, derived when the record predates the key.

    scratch/census_fp.jsonl was written before residue.py carried L1f, so the census side has to be
    derived; the catalogue side (written after) carries it.  Deriving it is exact - L1f is a pure
    function of `cls`, `band` and `regfam`, all three of which every record already holds."""
    if fp.get("L1f"):
        return fp["L1f"]
    return "%s|%s" % (fp["L0"], residue.famset(fp.get("regfam") or []))


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
            cat[("L1f", l1f_of(r["fp"]))][c] += 1
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
                   L0=fp["L0"], L1=fp["L1"], L2=fp["L2"], L1f=l1f_of(fp), level=level,
                   mass=mass, causes=[dict(cause=k, n=v, share=round(sh, 3),
                                           generator=generator_of(k)) for k, v, sh in causes[:6]])
        per_site.append(rec)
        rowinfo[s["id"]].append(rec)
        for lvl in ("L0", "L1", "L2", "L1f"):
            c = cat.get((lvl, rec[lvl]))
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
    for lvl in ("L0", "L1", "L2", "L1f", "any"):
        L.append("%-10s %8d %6.1f%%" % (lvl, cov[lvl], 100.0 * cov[lvl] / max(1, n)))
    L += ["", "L1f is the SIDEWAYS key of residue.py: cls|band|the set of register families in the",
          "recolour pairs.  It is not a level between L1 and L2 - a MOVED residue has no pairs, so",
          "its L1f is cls|band| and can only be as coarse as L0.  It is here for the FAR band, where",
          "L1's `far:` opcode shape is close to a per-function signature; scratch/control.py's",
          "negative control is what decides whether it means anything, not this table."]
    for name, keyf in (("d band", lambda r: r["band"]), ("residue class", lambda r: r["cls"]),
                       ("row pin band", lambda r: pin_band(r["n"] or 1)),
                       ("macro family", lambda r: family(r["macro"] or ""))):
        L += ["", "coverage by %s" % name,
              "%-12s %7s %9s %9s %9s %9s" % (name, "sites", "cov L0", "cov L1", "cov L2", "cov L1f")]
        groups = collections.defaultdict(list)
        for r in per_site:
            groups[keyf(r)].append(r)
        for g in sorted(groups):
            rs = groups[g]
            c = {lvl: sum(1 for r in rs if _covered_at(cat, r, lvl, args.min))
                 for lvl in ("L0", "L1", "L2", "L1f")}
            L.append("%-12s %7d %8.1f%% %8.1f%% %8.1f%% %8.1f%%"
                     % (g, len(rs), 100.0 * c["L0"] / len(rs), 100.0 * c["L1"] / len(rs),
                        100.0 * c["L2"] / len(rs), 100.0 * c["L1f"] / len(rs)))
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

    # 6. bucket a, split by the sweep journal
    if not args.no_bucket_a_split:
        tab("bucket a split", bucket_a_split(brows["a"], rowinfo, args))

    # 7. the zero-instance rate the oracle asked for beside every coverage number
    if not args.no_zero_instance:
        tab("zero instance", zero_instance(sorted(rowinfo), args))

    with (out / "summary.txt").open("w") as f:
        print("round-33 catalogue match: census %s, catalogue %s%s"
              % (args.census, args.catalog, (" + " + args.catalog2) if args.catalog2 else ""), file=f)
        for title, lines in tables:
            print("\n\n%s\n%s" % (title.upper(), "=" * len(title)), file=f)
            print("\n".join(lines), file=f)
    print("wrote %d tables + per_site.jsonl + summary.txt in %s" % (len(tables), out))


# --------------------------------------------------------------- bucket a, split by the journal

def journal_index(ids=None):
    """`ledger/sweeps/*.jsonl` indexed once: (row id, in_sha) -> [(transform, outcome)].

    Every sweep record carries the sha256 of the text the transform was HANDED (`in_sha`), so a
    record whose in_sha is the sha of the row's text AS IT STANDS TODAY is a run of that transform
    on this very text - and its outcome says what happened.  Any other record was a run on an older
    text and proves nothing about the row now.  215 files, ~318,000 records, about 5 s.
    """
    idx = collections.defaultdict(list)
    n = 0
    for p in sorted((ROOT / "ledger/sweeps").glob("*.jsonl")):
        with p.open() as f:
            for line in f:
                if not line.strip():
                    continue
                try:
                    r = json.loads(line)
                except Exception:
                    continue
                n += 1
                rid, sha = r.get("id"), r.get("in_sha")
                if not rid or not sha or (ids is not None and rid not in ids):
                    continue
                idx[(rid, sha)].append((r.get("transform"), r.get("outcome")))
    return idx, n


def bucket_a_split(rows_a, rowinfo, args):
    """a_missed / a_unseen / a_applied, per generator.

    A bucket-a row has a site whose top cause names a generator.  The question the round-33 plan
    could not answer is whether that generator has ALREADY been offered this row: the catalogue
    says "a move of this shape produces this residue", not "nobody has tried".  So for each row,
    and for the journal transforms behind its top cause (`KIND_TRANSFORMS`), the journals are asked
    for records whose `in_sha` is the sha256 of the row's CURRENT src text:

      a_missed   the generator RAN on this very text and did not apply (the outcome is reported -
                 `refused` with its reason, `noop`, `mismatch`, `build-failed`).  Opening its
                 refusal is the cheap move: the row is already in front of it.
      a_unseen   no record on the current text at all - the generator has never run here, or ran
                 on an older text.  A sweep is what this row wants, not a widening.
      a_applied  an applied record on the current text: the generator changed the row and pins
                 remain.  Its next pin needs a different move.
    """
    from common import sha_text                                     # noqa: E402
    rows = {r["id"]: r for r in all_rows()}
    want = {}
    for rid in rows_a:
        sites = rowinfo[rid]
        best = None
        for s in sites:
            if s["level"] in ("L1", "L2") and s["causes"] and s["causes"][0]["generator"]:
                if best is None or s["causes"][0]["n"] > best["causes"][0]["n"]:
                    best = s
        if best is None:
            continue
        want[rid] = best
    idx, n_recs = journal_index(set(want))
    per = collections.defaultdict(lambda: collections.Counter())
    pins = collections.defaultdict(lambda: collections.Counter())
    outcomes = collections.defaultdict(collections.Counter)
    detail = {}
    no_text = 0
    for rid, site in sorted(want.items()):
        row = rows.get(rid)
        if row is None or not clean_path(row).exists():
            no_text += 1
            continue
        sha = sha_text(clean_path(row).read_text(errors="replace"))
        cause = site["causes"][0]["cause"]
        trs = transforms_of(cause)
        recs = [x for x in idx.get((rid, sha), []) if x[0] in trs]
        if not trs:
            sub = "a_unseen"
        elif any(o == "applied" for _t, o in recs):
            sub = "a_applied"
        elif recs:
            sub = "a_missed"
        else:
            sub = "a_unseen"
        gen = site["causes"][0]["generator"]
        per[gen][sub] += 1
        pins[gen][sub] += len(rowinfo[rid])
        for _t, o in recs:
            outcomes[sub][o] += 1
        detail[rid] = (sub, cause, gen, sorted(set(recs)))
    L = ["bucket a (%d rows) split by the sweep journals: has the generator the catalogue names"
         " already been offered THIS text?" % len(rows_a),
         "%d journal records scanned; %d bucket-a rows carry a top cause with a generator;"
         " %d rows have no clean file" % (n_recs, len(want), no_text),
         "",
         "%-46s %8s %8s %8s %8s" % ("generator (of the row's top cause)", "a_missed", "a_unseen",
                                    "a_applied", "rows")]
    tot = collections.Counter()
    tpins = collections.Counter()
    for gen in sorted(per, key=lambda g: -sum(per[g].values())):
        c = per[gen]
        L.append("%-46s %8d %8d %8d %8d" % (gen[:46], c["a_missed"], c["a_unseen"], c["a_applied"],
                                            sum(c.values())))
        tot.update(c)
        tpins.update(pins[gen])
    L.append("%-46s %8d %8d %8d %8d" % ("TOTAL rows", tot["a_missed"], tot["a_unseen"],
                                        tot["a_applied"], sum(tot.values())))
    L.append("%-46s %8d %8d %8d %8d" % ("TOTAL pins", tpins["a_missed"], tpins["a_unseen"],
                                        tpins["a_applied"], sum(tpins.values())))
    L += ["", "the outcome of the records behind a_missed and a_applied:"]
    for sub in ("a_missed", "a_applied"):
        L.append("  %-10s %s" % (sub, ", ".join("%s %d" % kv for kv in outcomes[sub].most_common())))
    key = "MOVED|3-4|-move,sw +move,sw"
    rows_key = [rid for rid, s in want.items() if s["L1"] == key]
    if rows_key:
        c = collections.Counter(detail[r][0] for r in rows_key if r in detail)
        g = collections.Counter(detail[r][2] for r in rows_key if r in detail)
        L += ["", "THE CONFIRMATION the round-33 brief asked for, on `%s`:" % key,
              "  %d bucket-a rows carry that key as their top-cause site; %s"
              % (len(rows_key), ", ".join("%s %d" % kv for kv in c.most_common())),
              "  generators: %s" % ", ".join("%s %d" % kv for kv in g.most_common())]
    L += ["", "per row: bucket_a_split.jsonl"]
    (Path(args.out) / "bucket_a_split.jsonl").write_text(
        "".join(json.dumps(dict(id=r, sub=v[0], cause=v[1], generator=v[2],
                                journal=[list(x) for x in v[3]])) + "\n"
                for r, v in sorted(detail.items())))
    return L


# --------------------------------------------------------------- the zero-instance rate

def _zi_one(rid):
    row = ZI_ROWS.get(rid)
    if row is None or not clean_path(row).exists():
        return rid, None
    text = clean_path(row).read_text(errors="replace")
    from pin_sites import erase_many                                # noqa: E402
    clean = erase_many(text, sites_of(text), clean_notes=True)
    out = {}
    for kind, fn in kinds_of(ZI_MODS):
        try:
            out[kind] = len(fn(clean, collections.Counter()))
        except Exception:
            out[kind] = -1
    return rid, out


ZI_ROWS = {}
ZI_MODS = None


def _zi_init():
    global ZI_ROWS, ZI_MODS
    ZI_ROWS = {r["id"]: r for r in all_rows()}
    ZI_MODS = load_modules(log=False)


def zero_instance(ids, args):
    """Per kind and per generator: the share of PINNED rows on which the kind enumerates nothing.

    The oracle's third method change - "report the reversing kind's zero-instance rate beside any
    coverage number" - read on the census's own rows instead of on the 152 landed ones.

    THE ONE CHOICE THIS MAKES, and it has to be stated: every kind refuses a text that carries pin
    sites outright (`_guard`, "the catalogue perturbs pin-free rows only"), so the rate is measured
    on the row's text WITH ITS PINS ERASED - `erase_many(text, sites_of(text), clean_notes=True)`,
    the same m2c-like text the oracle calls the target.  That is the text a generator would be
    handed if its pins came out, so it is the right one to ask; it is NOT the pinned text, and a
    kind could in principle behave differently on the two.
    """
    t0 = time.time()
    res = {}
    with Pool(args.procs, initializer=_zi_init) as p:
        for rid, out in p.imap_unordered(_zi_one, ids, chunksize=8):
            if out is not None:
                res[rid] = out
    kinds = sorted({k for v in res.values() for k in v})
    L = ["the share of the census's %d PINNED rows on which each kind enumerates AT LEAST ONE"
         " instance, measured on the row's text with its pins erased (%.0f s)"
         % (len(res), time.time() - t0),
         "",
         "%-16s %-46s %8s %8s %8s" % ("kind", "generator", "rows", "some", "zero")]
    for kind in sorted(kinds, key=lambda k: -sum(1 for v in res.values() if v.get(k, 0) > 0)):
        some = sum(1 for v in res.values() if v.get(kind, 0) > 0)
        L.append("%-16s %-46s %8d %7d%% %7d%%"
                 % (kind, (KIND_GENERATOR.get(kind) or "-")[:46], len(res),
                    round(100.0 * some / max(1, len(res))),
                    round(100.0 * (len(res) - some) / max(1, len(res)))))
    L += ["", "per generator (a kind's rate is the generator's reach on the rows still pinned):"]
    bygen = collections.defaultdict(list)
    for kind in kinds:
        bygen[KIND_GENERATOR.get(kind) or "-"].append(kind)
    L.append("%-46s %-40s %8s" % ("generator", "kinds", "some-instance rows"))
    for gen in sorted(bygen):
        ks = bygen[gen]
        some = sum(1 for v in res.values() if any(v.get(k, 0) > 0 for k in ks))
        L.append("%-46s %-40s %7d%%" % (gen[:46], ",".join(ks)[:40],
                                        round(100.0 * some / max(1, len(res)))))
    return L


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
    d.add_argument("--procs", type=int, default=6)
    d.add_argument("--no-bucket-a-split", action="store_true")
    d.add_argument("--no-zero-instance", action="store_true")
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
