#!/usr/bin/env python3
"""Fidelity step 4 measurement: which step-4 candidate rows have a natural pin-free text at the recipe their
retail bytes prove?  (docs/TOOLCHAIN_FIDELITY_PLAN.md step 4; brief work/fidelity/STEP4_BRIEF.md part B.)

    python3 tools/fidelity/step4_measure.py [--rows ID,ID] [--workers 6] [--out work/fidelity/step4]
                                            [--stage work/native_lane/r77_step4]

Input: docs/evidence/fidelity_step4_candidates.tsv (70 strict + 2 weak rows registered at a non-splitting cell
whose retail shows the split-address fingerprint; step 2).  Per row:

1. EVIDENCED RECIPES.  Overlay rows in a module whose census `best_recipe` splits: that recipe (primary) and
   2.7.2-cdk with the row's own flags (the census label carries only cell+G, so a row-specific flag such as
   -fno-schedule-insns would otherwise be dropped silently).  Rows without a census recipe (slus, 5 dungeon):
   2.7.2-cdk and 2.8.1, both with the row's flags (charter ruling 2026-09-24 (later) item 1: the cell at which
   the natural C is exact; both -> the TU neighbours' cell).  `-mmips-as` / `-mno-split-addresses` are dropped:
   they are what turns a splitting cell off.
2. CANDIDATES.  The current text; the current text with every pin erased; tools/xform/t86_symaddr's menu (the
   page base respelled as the symbol it encodes, at its place, in its type) with t86's erasure ladder (window
   pins jointly, singly, all pins) - over EVERY address base in the scored arm, not only pin-reachable ones (a
   page literal with no pin is the `page_literal` class); the hand candidates of the r77 sceptic lane
   (work/native_lane/r77_fable_splitaddr/cands) for its five rows.
3. SCORE at each evidenced recipe.  Overlay rows: tools/verify.py (the per-row scorer, cfg override in memory,
   nothing written).  Slus rows: tools/fidelity/slus_iso.py - an isolated copy of build_slus/ built and linked
   with the TU swapped and its recipe changed, compared with retail (verify.py's slus reference is the pinned
   object with literal page immediates and cannot score a symbol respelling).  Slus rows are also scored under
   the genuine-ASPSX small-data model (`.extern` lines withheld from maspsx except the symbols retail addresses
   through $gp) - a measurement of the pending step-3 decision 3, never a staging path.
4. The CURRENT pinned text is scored at every recipe too (rule 2: exact there = a plain byte-neutral switch).
5. Exact candidates that pass tools/pin_census.landing_refusal are STAGED in the lane kit's convention:
   <stage>/out/<container>/<file>.c + .c.base_sha (sha of the current src text) and <stage>/cells.jsonl
   {"id","to","coherence"} - nothing lands; the orchestrator runs tools/fidelity/land_recipe_move.py.

Output: <out>/results.jsonl (one record per row), <out>/cands/<container>/<file>.<label>.c (best candidate per
row), <out>/progress.log.  Read-only on src/, ledger/, config/ and every recipe.
"""
from __future__ import annotations
import argparse, collections, csv, json, os, re, sys, time, traceback
from concurrent.futures import ProcessPoolExecutor, as_completed
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE.parent)); sys.path.insert(0, str(HERE.parent / "xform")); sys.path.insert(0, str(HERE))
from common import ROOT, LEDGER, rows, current_text, clean_path, parse_cfg, sha_text, read_jsonl  # noqa: E402

TSV = ROOT / "docs/evidence/fidelity_step4_candidates.tsv"
HAND = ROOT / "work/native_lane/r77_fable_splitaddr/cands"
HAND_CANDS = {"slus/w_8003D92C": ["d92c_cdk.c"], "slus/w_8003E39C": ["e39c_sym.c"], "slus/w_80046E38": ["6e38_sym.c"],
              "dungeon/func_80AEF73C": ["ef73c_sym.c"], "dungeon/func_818CEB58": ["ceb58_sym.c"]}
SPLIT_CELLS = {"2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2"}
OFF_SWITCHES = {"-mmips-as", "-mno-split-addresses"}
MAX_TEXTS = int(os.environ.get("STEP4_MAX_TEXTS", "160"))


# ------------------------------------------------------------------ recipes

def splits(cfg):
    cell, flags = parse_cfg(cfg)
    return cell in SPLIT_CELLS and not (OFF_SWITCHES & set(flags))


def with_cell(cfg, cell, dialect):
    """`cfg` moved to `cell`, the row's flags kept minus the split off-switches, in the container's dialect
    (overlays glue -G0 to the cell: '2.7.2-cdk-G0 -fno-x'; slus writes '2.7.2-cdk -G0 -fno-x')."""
    _, flags = parse_cfg(cfg)
    flags = [f for f in flags if f not in OFF_SWITCHES]
    if dialect == "overlay":
        head = cell + ("-G0" if "-G0" in flags else "")
        rest = [f for f in flags if f != "-G0"]
        return head + ((" " + " ".join(rest)) if rest else "")
    return " ".join([cell] + flags)


def evidenced_recipes(row, census):
    """[(label, cfg)] in priority order."""
    dialect = "slus" if row["kind"] == "slus" else "overlay"
    out = []
    if census and splits(census):
        out.append(("census", census))
        c2 = with_cell(row["cfg"], parse_cfg(census)[0], dialect)
        if c2 != census:
            out.append(("census_cell+row_flags", c2))
        cdk = with_cell(row["cfg"], "2.7.2-cdk", dialect)
        if cdk not in (census, c2):
            out.append(("cdk+row_flags", cdk))
    else:
        out.append(("cdk+row_flags", with_cell(row["cfg"], "2.7.2-cdk", dialect)))
        out.append(("2.8.1+row_flags", with_cell(row["cfg"], "2.8.1", dialect)))
    seen, uniq = set(), []
    for lab, c in out:
        if c not in seen and c != row["cfg"]:
            seen.add(c); uniq.append((lab, c))
    return uniq


def neighbour_cells(row, by, modules):
    """Cells of the row's TU neighbours: the other rows of its module (ledger/modules.jsonl), else the six
    nearest rows of its container by file offset / TU name."""
    mod = modules.get(row["id"])
    peers = [r for rid, m in modules.items() if m == mod and rid != row["id"] and rid.split("/")[0] == row["container"]
             for r in [by.get(rid)] if r] if mod else []
    if not peers:
        same = [r for r in by.values() if r["container"] == row["container"] and r["id"] != row["id"]]
        if row.get("foff") is not None:
            same = [r for r in same if r.get("foff") is not None]
            same.sort(key=lambda r: abs(r["foff"] - row["foff"]))
        else:
            same.sort(key=lambda r: r["id"])
            ids = [r["id"] for r in same]
            import bisect
            i = bisect.bisect(ids, row["id"])
            same = same[max(0, i - 3):i + 3]
        peers = same[:6]
    return dict(collections.Counter(r["cell"] for r in peers))


# ------------------------------------------------------------------ candidates

def _bases_all(text):
    """t86's bases() without the pin-reachability filter: a page literal with no pin is the
    `page_literal` class this measurement also covers."""
    import t86_symaddr as T
    from t54_pagebase import definitions, masked
    import t29_addrsym as A
    t = masked(text)
    out, seen = [], set()
    for d in definitions(text):
        if (d["var"], d["pos"]) in seen:
            continue
        seen.add((d["var"], d["pos"]))
        out.append(dict(d, kind="literal", pinned=d["var"] in T.pinned_names(text)))
    for m in re.finditer(A.SYMDEF_ANY_RE, t, re.M):
        val = A.sym_value(text, m.group(2))
        if val is None or (m.group(1), m.start()) in seen:
            continue
        seen.add((m.group(1), m.start()))
        out.append(dict(var=m.group(1), value=val, start=m.start(2), end=m.end(2), pos=m.start(), kind="symbol",
                        pinned=m.group(1) in T.pinned_names(text)))
    out.sort(key=lambda b: (not b["pinned"], b["pos"]))
    return out[:T.MAX_BASES]


_PADDED = re.compile(r"^extern\s+struct\s*\{\s*(?P<ty>[A-Za-z_][\w ]*?\s*\**)\s*(?P<f>[A-Za-z_]\w*)\s*;"
                     r"(?P<pads>(?:\s*[A-Za-z_][\w ]*?\s+\w+\s*(?:\[\s*\w+\s*\])?\s*;)+)\s*\}\s*(?P<n>D_[0-9A-F]{8})\s*;[^\n]*$", re.M)
_PADDED_T = re.compile(r"^typedef\s+struct\s*\w*\s*\{\s*(?P<ty>[A-Za-z_][\w ]*?\s*\**)\s*(?P<f>[A-Za-z_]\w*)\s*;"
                       r"(?P<pads>(?:\s*[A-Za-z_][\w ]*?\s+pad\w*\s*(?:\[\s*\w+\s*\])?\s*;)+)\s*\}\s*(?P<t>\w+)\s*;[^\n]*\n", re.M)
_SIZED = re.compile(r"^extern\s+(?P<ty>(?:const\s+|volatile\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*)\s+(?P<n>D_[0-9A-F]{8})"
                    r"\s*\[\s*(?:0x)?[0-9A-Fa-f]+\s*\]\s*;[^\n]*$", re.M)


def inline_asm(text):
    """Inline asm statements other than symbol definitions (`.set`, `.include`): hidden scaffolding."""
    return len(re.findall(r'__asm__\s*(?:volatile\s*|__volatile__\s*)?\(\s*"(?!\s*\.(?:set|include|globl)\b)', _nocomment(text)))


def _nocomment(s):
    return re.sub(r"/\*.*?\*/|//[^\n]*", " ", s, flags=re.S)


def smallext(text):
    """The small-data spelling of externs a text inflated past -G8 so that maspsx would not address them
    through $gp: `extern struct { T v; T pad[2]; } D_X;` read only as `D_X.v`, and `extern T D_X[16];` read
    only as `D_X[0]`, become `extern T D_X;` (lane r77_fable_splitaddr: retail addresses such externs as
    unsplit absolute macros - cc1 saw them small, genuine ASPSX kept them absolute).  Returns the new text
    or None when nothing applies.  Meaningful under the genuine-ASPSX small-data model only."""
    new = text
    for m in list(_PADDED_T.finditer(text)):               # typedef struct { T f; T pad4; ... } S_X; extern S_X D_X;
        tn = m["t"]
        for e in list(re.finditer(r"^extern\s+%s\s+(D_[0-9A-F]{8})\s*;[^\n]*$" % re.escape(tn), new, re.M)):
            n, f = e.group(1), m["f"]
            rest = _nocomment(new.replace(e.group(0), ""))
            uses = re.findall(r"\b%s\b(\s*\.\s*\w+)?" % n, rest)
            if uses and all(u and u.replace(" ", "") == "." + f for u in uses):
                new = new.replace(e.group(0), "extern %s %s;" % (m["ty"].strip(), n))
                new = re.sub(r"\b%s\s*\.\s*%s\b" % (n, f), n, new)
        if not re.search(r"\b%s\b" % re.escape(tn), _nocomment(new.replace(m.group(0), ""))):
            new = new.replace(m.group(0), "")
    for m in list(_PADDED.finditer(new)):
        n, f = m["n"], m["f"]
        rest = _nocomment(new.replace(m.group(0), ""))
        uses = re.findall(r"\b%s\b(\s*\.\s*\w+)?" % n, rest)
        if uses and all(u and u.replace(" ", "") == "." + f for u in uses):
            new = new.replace(m.group(0), "extern %s %s;" % (m["ty"].strip(), n))
            new = re.sub(r"\b%s\s*\.\s*%s\b" % (n, f), n, new)
    for m in list(_SIZED.finditer(new)):
        n = m["n"]
        rest = _nocomment(new.replace(m.group(0), ""))
        uses = re.findall(r"\b%s\b(\s*\[\s*[^\]]*\])?" % n, rest)
        if uses and all(u and re.fullmatch(r"\[\s*0\s*\]", u.strip()) for u in uses):
            new = new.replace(m.group(0), "extern %s %s;" % (m["ty"].strip(), n))
            new = re.sub(r"\b%s\s*\[\s*0\s*\]" % n, n, new)
    return new if new != text else None


def candidates(row, text, hand_dir=None):
    """[(label, text)] deduplicated, fewest pins first.  `hand_dir`/<container>/<stem>.<label>.c files are
    hand-written natural spellings (the scaffold-removal cases the generators do not reach)."""
    import t86_symaddr as T
    from pin_census import sites_of
    from pin_sites import erase_many
    out, seen = [], set()

    def add(label, t):
        if t is None:
            return
        h = sha_text(t)
        if h in seen:
            return
        seen.add(h); out.append((label, t))

    add("current", text)
    pins = sites_of(text)
    if pins:
        add("erase_all", erase_many(text, pins, clean_notes=True))
    for f in HAND_CANDS.get(row["id"], []):
        p = HAND / f
        if p.exists():
            add("hand:" + f, p.read_text(errors="replace"))
    if hand_dir:
        stem = Path(row["c_path"]).stem
        for p in sorted((Path(hand_dir) / row["container"]).glob(stem + ".*.c")):
            add("hand:" + p.name[len(stem) + 1:-2], p.read_text(errors="replace"))
    orig = T.bases
    T.bases = _bases_all
    try:
        for label, newtext, names, lines in T.menu(text):
            add("t86:" + label, newtext)
            for tag, group in T.pin_plans(newtext, names, lines):
                add("t86:%s/%s" % (label, tag), erase_many(newtext, group, clean_notes=True))
            if len(out) >= MAX_TEXTS:
                break
    except Exception:
        pass
    finally:
        T.bases = orig
    out = out[:MAX_TEXTS]
    if row["kind"] == "slus":
        # the small-data extern spelling of every text (scored under both assembler models)
        for label, t in list(out):
            add("smallext+" + label, smallext(t))
    order = {lab: i for i, (lab, _t) in enumerate(out)}
    out.sort(key=lambda q: (len(sites_of(q[1])), order[q[0]]))
    return out


# ------------------------------------------------------------------ scoring

_VIEW = None


def slus_view(scratch):
    global _VIEW
    if _VIEW is None:
        from slus_iso import SlusView
        _VIEW = SlusView(Path(scratch) / ("view_%d" % os.getpid()))
        _VIEW.pristine_symbols()
    return _VIEW


def score(row, text, cfg, scratch, gp_model=False):
    """-> {"exact", "total", "class", "status"} at `cfg` (text None = the current src text)."""
    if row["kind"] == "slus":
        from slus_iso import cfg_to_ninja, gp_symbols
        stem = Path(row["c_path"]).stem
        cell, flags = cfg_to_ninja(cfg)
        r = slus_view(scratch).gate({stem: (text, cell, flags)}, strip_externs=gp_model,
                                    keep_externs=gp_symbols(stem) if gp_model else ())
        return {"exact": r["result"] == "MATCH", "total": r.get("residue"), "status": r["result"],
                "class": "size-drift" if r.get("fn_size_drift") else ("link" if r["result"] == "MATCH" else "words"),
                "err": (r.get("detail") or "")[:200] if r["result"] == "ERROR" else None}
    sys.path.insert(0, str(ROOT / "tools/lanes/lanekit"))
    import kitlib
    t = text if text is not None else current_text(row)
    v = kitlib.score_at(row, t, cfg)
    return {"exact": bool(v.get("exact")), "total": v.get("total"), "class": v.get("class"), "status": v.get("status"),
            "err": (v.get("err") or None) and str(v.get("err"))[:200]}


# ------------------------------------------------------------------ one row

def measure(rid, tsvrow, scratch, out_dir):
    from pin_census import sites_of, landing_refusal
    t0 = time.time()
    by = {r["id"]: r for r in rows()}
    row = by[rid]
    mods = {r["id"]: r.get("module") for r in read_jsonl(LEDGER / "modules.jsonl")}
    census = tsvrow.get("census_recipe") or None
    text = current_text(row)
    recipes = evidenced_recipes(row, census)
    rec = {"id": rid, "registered": row["cfg"], "module": tsvrow.get("module"), "census_recipe": census,
           "mechanism": tsvrow.get("mechanism"), "fp_kinds": tsvrow.get("kinds"), "tier": tsvrow.get("fp"),
           "recipes": [c for _l, c in recipes], "recipe_labels": {c: l for l, c in recipes},
           "neighbour_cells": neighbour_cells(row, by, mods), "pins_before": len(sites_of(text)),
           "src_sha": sha_text(text)}
    # rule 2: the current pinned text at every evidenced recipe
    rec["pinned_at"] = {}
    for _lab, cfg in recipes:
        s = score(row, None if row["kind"] == "slus" else text, cfg, scratch)
        rec["pinned_at"][cfg] = {"exact": s["exact"], "total": s["total"], "class": s["class"]}
    cands = candidates(row, text, Path(out_dir) / "hand")
    rec["n_candidates"] = len(cands)
    scored, gp_scored = [], []                     # (exact, pins, total, label, cfg, text, s)
    best_exact_pins = {}
    models = ("stock", "gp") if row["kind"] == "slus" else ("stock",)
    for label, ctext in cands:
        pins = len(sites_of(ctext))
        key = (pins, inline_asm(ctext))
        for _lab, cfg in recipes:
            for model in models:
                if (cfg, model) in best_exact_pins and key >= best_exact_pins[(cfg, model)]:
                    continue
                if model == "stock" and label.startswith("smallext+"):
                    continue                           # an inflated-extern repair is meaningful under the gp model only
                s = score(row, ctext if not (row["kind"] == "slus" and label == "current") else None, cfg, scratch,
                          gp_model=(model == "gp"))
                q = (s["exact"], pins, s["total"] if s["total"] is not None else 1 << 20, label, cfg, ctext, s)
                (scored if model == "stock" else gp_scored).append(q)
                if s["exact"]:
                    best_exact_pins[(cfg, model)] = min(best_exact_pins.get((cfg, model), (1 << 20, 0)), key)
    prio = {c: i for i, (_l, c) in enumerate(recipes)}
    # among equally pinned exact texts the one with less inline asm (hidden scaffolding the pin census does not
    # count: `__asm__("lui ...%hi...")`) is the more natural one
    exact = sorted([q for q in scored if q[0]], key=lambda q: (q[1], inline_asm(q[5]), prio[q[4]]))
    near = sorted([q for q in scored if not q[0] and q[1] < rec["pins_before"]], key=lambda q: (q[2], q[1]))
    near_any = sorted([q for q in scored if not q[0]], key=lambda q: (q[2], q[1]))
    rec["exact_at"] = sorted({q[4] for q in exact})
    # the natural (fewest-pin) exact text per recipe
    rec["best_exact_per_recipe"] = {cfg: min((q[1] for q in exact if q[4] == cfg), default=None) for _l, cfg in recipes}
    best = exact[0] if exact else (near[0] if near else (near_any[0] if near_any else None))
    if best:
        ex, pins, total, label, cfg, ctext, s = best
        c, n = rid.split("/")
        stem = Path(row["c_path"]).stem
        p = Path(out_dir) / "cands" / c / ("%s.%s.c" % (stem, re.sub(r"[^A-Za-z0-9_.+-]", "_", label)[:60]))
        p.parent.mkdir(parents=True, exist_ok=True); p.write_text(ctext)
        rec["best"] = {"label": label, "path": str(p.relative_to(ROOT)) if p.is_relative_to(ROOT) else str(p), "pins_after": pins, "exact": ex, "recipe": cfg,
                       "residue": None if ex else {"total": s["total"], "class": s["class"], "status": s["status"]},
                       "err": s.get("err")}
        # exact at several evidenced recipes with the same pins: the tie rule (neighbours' cell)
        if exact:
            tied = sorted({q[4] for q in exact if q[1] == pins})
            rec["best"]["exact_recipes_same_pins"] = tied
            if len(tied) > 1 and not census:
                nb = rec["neighbour_cells"]
                pick = max(tied, key=lambda cf: (nb.get(parse_cfg(cf)[0], 0), parse_cfg(cf)[0] == "2.7.2-cdk"))
                if pick != cfg:
                    rec["best"]["recipe"] = pick; rec["best"]["tie_rule"] = "neighbours' cell %s" % parse_cfg(pick)[0]
            if ex:
                bad = landing_refusal(ctext, text, "src/%s/%s" % (c, Path(row["c_path"]).name), row=row)
                rec["best"]["landing_refusal"] = (bad or None) and bad.replace(str(ROOT), "<repo>")[:300]
    # slus: the genuine-ASPSX small-data model (measurement of step-3 decision 3; never staged)
    if gp_scored:
        gx = sorted([q for q in gp_scored if q[0]], key=lambda q: (q[1], prio[q[4]]))
        gn = sorted([q for q in gp_scored if not q[0]], key=lambda q: (q[2], q[1]))
        g = gx[0] if gx else (gn[0] if gn else None)
        if g:
            stem = Path(row["c_path"]).stem
            p = Path(out_dir) / "cands" / "slus" / ("%s.gp.%s.c" % (stem, re.sub(r"[^A-Za-z0-9_.+-]", "_", g[3])[:60]))
            p.parent.mkdir(parents=True, exist_ok=True); p.write_text(g[5])
            rec["gp_model"] = {"label": g[3], "recipe": g[4], "pins_after": g[1], "exact": g[0],
                               "total": None if g[0] else g[6]["total"],
                               "path": str(p.relative_to(ROOT)) if p.is_relative_to(ROOT) else str(p)}
        rec["gp_model_exact"] = sorted({"%s@%s(pins %d)" % (q[3], q[4], q[1]) for q in gx})[:12]
        rec["gp_pinned_at"] = {q[4]: {"exact": q[0], "total": q[6]["total"]} for q in gp_scored if q[3] == "current"}
    rec["secs"] = round(time.time() - t0, 1)
    rec["scored"] = len(scored) + len(gp_scored)
    return rec


def nearband(rid, tsvrow, scratch, out_dir, prev, max_resid=6, top=5):
    """Second pass for a row whose best natural candidate missed by <= max_resid: the top candidates at the
    evidenced CELL with every subset of the row's own flags (a flag the row carries is a per-row loan the
    census label drops; charter rule 4 allows pin-for-flag trades).  -> {"exact": [...], "best": ...}."""
    import itertools
    from pin_census import sites_of, landing_refusal
    by = {r["id"]: r for r in rows()}
    row = by[rid]
    text = current_text(row)
    b = prev.get("best") or {}
    ev = b.get("recipe") or prev["recipes"][0]
    cell, evflags = parse_cfg(ev)
    g0 = "-G0" in evflags
    rowflags = [f for f in parse_cfg(row["cfg"])[1] if f not in OFF_SWITCHES and f != "-G0"]
    dialect = "slus" if row["kind"] == "slus" else "overlay"
    variants = []
    for k in range(len(rowflags) + 1):
        for sub in itertools.combinations(rowflags, k):
            fl = (["-G0"] if g0 else []) + list(sub)
            cfg = (cell + ("-G0" if g0 else "") + ((" " + " ".join(sub)) if sub else "")) if dialect == "overlay" else " ".join([cell] + fl)
            if cfg not in prev["recipes"] and cfg != row["cfg"]:
                variants.append(cfg)
    variants = variants[:16]
    cands = candidates(row, text, Path(out_dir) / "hand")
    first = []
    for label, ctext in cands:
        s = score(row, ctext if not (row["kind"] == "slus" and label == "current") else None, ev, scratch)
        first.append((s["total"] if s["total"] is not None else 1 << 20, len(sites_of(ctext)), label, ctext))
    first.sort(key=lambda q: (q[0], q[1]))
    pool = [q for q in first if q[1] < max(1, len(sites_of(text))) or q[2] == "current"][:top]
    found, best = [], None
    for total0, pins, label, ctext in pool:
        for cfg in variants:
            s = score(row, ctext if not (row["kind"] == "slus" and label == "current") else None, cfg, scratch)
            q = {"label": label, "recipe": cfg, "pins_after": pins, "exact": s["exact"], "total": s["total"]}
            if s["exact"]:
                c = rid.split("/")[0]
                bad = landing_refusal(ctext, text, "src/%s/%s" % (c, Path(row["c_path"]).name), row=row) if ctext != text else None
                q["landing_refusal"] = (bad or None) and bad.replace(str(ROOT), "<repo>")[:300]
                pth = Path(out_dir) / "cands" / c / ("%s.nb.%s.c" % (Path(row["c_path"]).stem, re.sub(r"[^A-Za-z0-9_.+-]", "_", label)[:60]))
                pth.parent.mkdir(parents=True, exist_ok=True); pth.write_text(ctext)
                q["path"] = str(pth.relative_to(ROOT)) if pth.is_relative_to(ROOT) else str(pth)
                found.append(q)
            if best is None or (q["total"] or 1 << 20) < (best["total"] or 1 << 20):
                best = q
    return {"variants": variants, "pool": [q[2] for q in pool], "exact": sorted(found, key=lambda q: q["pins_after"]), "best": best}


def _job(args):
    rid, tsvrow, scratch, out_dir = args[:4]
    try:
        if len(args) > 4:
            prev = args[4]
            return dict(prev, nearband=nearband(rid, tsvrow, scratch, out_dir, prev))
        return measure(rid, tsvrow, scratch, out_dir)
    except Exception as e:
        return {"id": rid, "error": repr(e)[:300], "trace": traceback.format_exc()[-1500:].replace(str(ROOT), "<repo>")}


def landable(r):
    """The candidate to stage for a row: the main pass's best when exact and not refused, else the near-band
    pass's fewest-pin exact one; None when neither."""
    if "error" in r or splits(r["registered"]):
        return None                                  # already at a splitting recipe (slus/w_8005A1D0, ca253080)
    b = r.get("best") or {}
    if b.get("exact") and not b.get("landing_refusal"):
        return b
    for q in (r.get("nearband") or {}).get("exact") or []:
        if not q.get("landing_refusal") and q["pins_after"] <= r.get("pins_before", 0):
            return dict(q, via="nearband (row flag subset at the evidenced cell)")
    return None


def stage(results, stage_dir):
    """Stage exact, refusal-free candidates for tools/fidelity/land_recipe_move.py."""
    stage_dir = Path(stage_dir)
    lines = []
    for r in results:
        b = landable(r)
        if not b:
            continue
        c, n = r["id"].split("/")
        row = next(x for x in rows() if x["id"] == r["id"])
        cur = current_text(row)
        if sha_text(cur) != r["src_sha"]:
            continue                                   # the row changed while we measured
        dst = stage_dir / "out" / c / Path(row["c_path"]).name
        dst.parent.mkdir(parents=True, exist_ok=True)
        dst.write_text((ROOT / b["path"]).read_text())      # an absolute path joins as itself
        dst.with_name(dst.name + ".base_sha").write_text(r["src_sha"] + "\n")
        rule2 = bool(r["pinned_at"].get(b["recipe"], {}).get("exact")) if b["recipe"] in r["pinned_at"] else None
        ev = "retail split-address fingerprint (%s; tier %s)" % (r.get("fp_kinds"), r.get("tier"))
        ev += ("; module census best_recipe %s" % r["census_recipe"]) if r.get("census_recipe") else \
              "; no module census: retail-proven splitting cell, %s" % (b.get("tie_rule") or "the cell where the natural C is exact")
        lines.append({"id": r["id"], "to": b["recipe"],
                      "coherence": "%s; candidate %s pins %d -> %d exact at %s%s; %s" % (
                          ev, b["label"], r["pins_before"], b["pins_after"], b["recipe"],
                          " (%s)" % b["via"] if b.get("via") else "",
                          "pinned text not scored at this recipe (the lander scores rule 2)" if rule2 is None else
                          "pinned text exact at the target (rule 2 holds: byte-neutral)" if rule2 else
                          "pinned text not exact at the target (rule 2 does not hold: coherence trade)"),
                      "rule2": rule2, "pins_before": r["pins_before"], "pins_after": b["pins_after"],
                      "evidence": {"fp_kinds": r.get("fp_kinds"), "census_recipe": r.get("census_recipe") or "retail-proven",
                                   "neighbour_cells": r.get("neighbour_cells")}})
    (stage_dir).mkdir(parents=True, exist_ok=True)
    with open(stage_dir / "cells.jsonl", "w") as f:
        for l in lines:
            f.write(json.dumps(l) + "\n")
    return lines


def report_table(results):
    """The per-row markdown table of docs/evidence/fidelity_step4_measure.md, from results.jsonl."""
    out = ["| row | registered | evidenced recipe | pinned text there | best natural candidate | pins | exact | residue | genuine-$gp model (slus) |",
           "|---|---|---|---|---|---|---|---|---|"]
    for r in results:
        if "error" in r:
            out.append("| %s | | | | ERROR %s | | | | |" % (r["id"], r["error"][:60])); continue
        b = r.get("best") or {}
        ev = b.get("recipe") or (r["recipes"][0] if r["recipes"] else "-")
        pin = r["pinned_at"].get(ev) or {}
        pinned = "exact" if pin.get("exact") else ("%s" % pin.get("total") if pin else "-")
        res = "" if b.get("exact") else "%s %s" % ((b.get("residue") or {}).get("total"), (b.get("residue") or {}).get("class") or "")
        g = r.get("gp_model") if isinstance(r.get("gp_model"), dict) else {}
        gp = "" if r["id"].split("/")[0] != "slus" else ("exact (%s, pins %s)" % (g.get("label", "")[:30], g.get("pins_after")) if g.get("exact")
                                                          else "%s" % g.get("total"))
        lab = (b.get("label") or "")[:48].replace("|", "/")
        refusal = " (refused: %s)" % b["landing_refusal"][:40] if b.get("landing_refusal") else ""
        out.append("| %s | `%s` | `%s` (%s) | %s | `%s`%s | %s -> %s | %s | %s | %s |" % (
            r["id"], r["registered"], ev, r["recipe_labels"].get(ev, "?"), pinned, lab, refusal, r["pins_before"],
            b.get("pins_after"), "**yes**" if b.get("exact") else "no", res.strip(), gp))
    return "\n".join(out)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--rows"); ap.add_argument("--workers", type=int, default=6)
    ap.add_argument("--out", default="work/fidelity/step4"); ap.add_argument("--stage", default="work/native_lane/r77_step4")
    ap.add_argument("--scratch", help="where the isolated SLUS views live (default: a temp dir, removed at the end)")
    ap.add_argument("--no-stage", action="store_true")
    ap.add_argument("--redo", action="store_true", help="re-measure the --rows even when results.jsonl has them")
    ap.add_argument("--nearband", type=int, metavar="N", help="second pass: rows whose best candidate missed by <= N words, "
                    "top candidates at the evidenced cell with every subset of the row's flags")
    ap.add_argument("--table", action="store_true", help="print the per-row markdown table from results.jsonl and exit")
    a = ap.parse_args()
    out = (ROOT / a.out).resolve(); out.mkdir(parents=True, exist_ok=True)
    import shutil, tempfile
    scratch = Path(a.scratch).resolve() if a.scratch else Path(tempfile.mkdtemp(prefix="step4_views_"))   # ~30 MB a worker
    tsv = {r["id"]: r for r in csv.DictReader(open(TSV), delimiter="\t")}
    if a.table:
        res = {r["id"]: r for r in read_jsonl(out / "results.jsonl")}
        print(report_table([res[k] for k in tsv if k in res]))
        return
    ids = a.rows.split(",") if a.rows else list(tsv)
    order_all = list(tsv)
    head = os.popen("git -C %s rev-parse --short HEAD" % ROOT).read().strip()
    res_p = out / "results.jsonl"
    done = {r["id"]: r for r in read_jsonl(res_p)} if res_p.exists() else {}
    todo = [i for i in ids if a.redo or i not in done or "error" in done[i]]
    if a.nearband is not None:
        def near(r):
            b = r.get("best") or {}
            tot = (b.get("residue") or {}).get("total")
            return "error" not in r and not b.get("exact") and tot is not None and tot <= a.nearband and not r.get("nearband")
        todo = [i for i in ids if i in done and near(done[i])]
    # slus rows are the slow, view-bound ones: start them first
    todo.sort(key=lambda i: (not i.startswith("slus/"), -int(tsv[i]["pins"] or 0)))
    log = open(out / "progress.log", "a")
    print("step4: %d rows to measure (%d done), HEAD %s" % (len(todo), len(done), head), file=log, flush=True)
    t0 = time.time()
    with ProcessPoolExecutor(max_workers=a.workers) as ex:
        futs = {ex.submit(_job, (i, tsv[i], str(scratch), str(out)) + ((done[i],) if a.nearband is not None else ())): i for i in todo}
        for f in as_completed(futs):
            r = f.result(); r["head"] = head
            done[r["id"]] = r
            with open(res_p, "w") as fh:
                for k in order_all:
                    if k in done:
                        fh.write(json.dumps(done[k]) + "\n")
            b = r.get("best") or {}
            print("%-34s %s pins %s -> %s exact=%s at %s %s  (%.0fs)" % (
                r["id"], "ERROR " + r["error"][:80] if "error" in r else "", r.get("pins_before"), b.get("pins_after"),
                b.get("exact"), b.get("recipe"), (b.get("residue") or {}).get("total") if b else "", time.time() - t0), file=log, flush=True)
    results = [done[k] for k in order_all if k in done]
    if not a.no_stage:
        lines = stage(results, ROOT / a.stage)
        print("staged %d" % len(lines), file=log, flush=True)
    if not a.scratch:
        shutil.rmtree(scratch, ignore_errors=True)
    print("done in %.0fs" % (time.time() - t0), file=log, flush=True)


if __name__ == "__main__":
    main()
