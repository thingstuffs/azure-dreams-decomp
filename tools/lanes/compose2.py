#!/usr/bin/env python3
"""Depth-2 composition of generators: generator B applied to generator A's nearest NON-exact candidates (round 76).

    python3 tools/lanes/compose2.py <lane> (--rows id[@A,A..][,id..] | --near D) [--A t110_paramfold,..] [--B cascade|a,b]
                                    [--k 3] [--workers 6] [--base-from auto|<lane>] [--journals 'glob,glob']

Why.  The round-73 harvests record rows whose exemplar needs a SECOND move: t110 misses 80E0D090 d18 / 80B9D094 d16 /
818F33BC d6 "each needs its second move", t115's 800C30E4 d14 "needs t108", t113's 80BEE4EC d13 "needs the symbol
store".  A generator's apply_verified() scores only its own candidates, and every generator ranks by the listing
distance of a candidate to the INPUT text's listing, so B run on A's inexact output would steer towards A's output,
not towards the retail listing.  This driver fixes both, generically, without touching any generator:

  1. A's menu is CAPTURED: every text A hands to `screen.compile_s` while it runs with a verifier that says "not
     exact" (so A only enumerates; nothing is scored).  The captured texts are ranked by the listing distance to the
     ORIGINAL pinned text's listing (screen.sdiff) and the k nearest that keep the scored/unscored split
     (pin_census.unscored_text) and do not add pins are kept.
  2. B runs on each kept candidate cA with the real verifier, and with `screen.compile_s(row, cA)` answered by the
     ORIGINAL text's listing, so B's own ranking measures distance to the retail listing (the pinned text is
     byte-exact, so its listing IS the target).  B's `nearest` distances are then retail distances: the distance table
     of a bounded negative.
  3. A B result that the verifier calls exact AND has fewer pin sites than the original row is a win; the best win per
     row (fewest pins) is staged as out/<container>/<name>.c + .base_sha - an ordinary generator lane that
     land_finished2.sh / land_gap.sh land.  Rows read from --base-from texts (exemplar checks on rows a model lane has
     already landed) stage a base_sha that is not the current src/ text, so they can never land: measurement only.

Row selection.  --rows names rows, each optionally with its A generators after `@` (`dungeon/func_80E0D090@t110_paramfold`);
--near D takes every miss record with nearest distance <= D from the --journals lane journals whose in_sha is still the
row's current src/ text, A = that lane's generator.  --base-from auto looks up the in_sha a *_check lane journal
recorded for the row and finds the model lane base/<id>.c with that sha (the pre-landing exemplar text).

B defaults to the whole landing cascade (tools/lanes/cascade_list.full(), minus t2_pins and the Python-bound t53s) plus
the t66..t117 generators not in it.  Journal: one record per (row, A, cA): the cA label/distance/pins and, per eligible
B, the B outcome and nearest distance.

--pinfree (round 76, "pin-free intermediates").  Stage 1 keeps A's k nearest PIN-FREE candidates (within --max-dA)
instead of the pinned ones, and B's anchor is the RESIDUE: tools/lanes/residue_anchor.py localises the C statements
whose instructions differ from retail (a -g listing diff, `.loc` line notes) and registers them as synthetic
`RESIDUE` site tuples for exactly that text, so a pin-anchored detector sees "pinned" statements there (a RESIDUE
tuple is never erased).  B defaults to the generators whose rewrite means something without a pin (PF_B: widths,
symbols/pages, multiset/order, set-once/dead-init).  The win rule is unchanged: B exact AND fewer real pin sites than
the row's text; the landers keep the scaffolding-growth check.
"""
import argparse, glob, hashlib, json, os, re, sys, tempfile, threading, time, importlib
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools")); sys.path.insert(0, str(ROOT / "tools/xform")); sys.path.insert(0, str(ROOT / "tools/lanes"))
from common import rows, clean_path, sha_text, read_jsonl, parse_cfg          # noqa: E402
from pin_census import sites_of, unscored_text                                # noqa: E402
from verify import verify                                                     # noqa: E402
import cascade_list                                                           # noqa: E402
import xform.screen as XS                                                     # noqa: E402

NL = ROOT / "work/native_lane"
_ORIG = XS.compile_s
_CACHE, _CLOCK = {}, threading.Lock()
SUBST = {}          # sha(text) -> text whose listing answers for it (B's target = the original's listing)
CAPTURE = {}        # row id -> {sha: text} while A enumerates that row
STATS = {}          # (row id, A module) -> menu statistics
PF_B = ["t36_paramwidth", "t37_localwidth", "t94_castsplit", "t77_symplace", "t86_symaddr", "t97_pagesym",
        "t104_pagejoint", "t72_stmtperm", "t74_multiset", "t118_setonce", "t119_deadinit"]
MODE = {"pinfree": False, "max_dA": 20, "anchors": 6}


def compile_s(row, text):
    """screen.compile_s with capture, target substitution and a cache (patched into every loaded module)."""
    h = sha_text(text)
    cap = CAPTURE.get(row["id"])
    if cap is not None:
        cap.setdefault(h, text)
    if h in SUBST:
        text = SUBST[h]; h = sha_text(text)
    key = (row["id"], row["cfg"], h)
    with _CLOCK:
        if key in _CACHE:
            return _CACHE[key]
    out = _ORIG(row, text)
    with _CLOCK:
        _CACHE[key] = out
    return out


def patch_modules():
    """Point every loaded module's compile_s (the `screen` module objects and `from screen import compile_s`
    bindings alike) at the wrapper."""
    origs = {id(_ORIG)}
    for m in list(sys.modules.values()):
        f = getattr(m, "compile_s", None)
        if f is not None and getattr(f, "__name__", "") == "compile_s" and getattr(f, "__module__", "") in ("screen", "xform.screen"):
            origs.add(id(f))
    for m in list(sys.modules.values()):
        f = getattr(m, "compile_s", None)
        if f is not None and id(f) in origs and m is not sys.modules[__name__]:
            try:
                setattr(m, "compile_s", compile_s)
            except Exception:                                                     # noqa: BLE001
                pass


def load(name):
    try:
        return importlib.import_module("xform." + name)
    except ImportError:
        return importlib.import_module(name)


def default_B():
    full = [t for t in cascade_list.full() if t not in ("t2_pins", "t53_reg_state", "t53k_keep")]
    more = sorted({p.stem for p in (ROOT / "tools/xform").glob("t*.py")
                   if re.match(r"t(6[6-9]|[7-9]\d|1[01]\d)_", p.stem)} - set(full),
                  key=lambda s: int(re.match(r"t(\d+)", s).group(1)))
    return full + more


def base_text(row, base_from):
    """(text, source) for a row: the current src/ text, or a model lane's pre-landing base text."""
    if base_from and base_from != "auto":
        p = NL / base_from / "base" / (row["id"] + ".c")
        if p.exists():
            return p.read_text(errors="replace"), base_from
    if base_from == "auto":
        shas = set()
        for j in glob.glob(str(NL / "r7[3-6]_*_check*" / "journal.jsonl")):
            for r in read_jsonl(Path(j)):
                if r.get("id") == row["id"] and r.get("in_sha"):
                    shas.add(r["in_sha"])
        for p in sorted(glob.glob(str(NL / "r7[0-9]_*" / "base" / (row["id"] + ".c")))):
            t = Path(p).read_text(errors="replace")
            if sha_text(t) in shas and sites_of(t):
                return t, Path(p).parents[2].name
    return clean_path(row).read_text(errors="replace"), "src"


def nearest_of(info):
    """The listing distances a generator reports in info["nearest"] (an int, a list of dicts or of tuples)."""
    n = info.get("nearest") if isinstance(info, dict) else None
    if isinstance(n, (int, float)) and not isinstance(n, bool):
        return [n]
    out = []
    for x in n if isinstance(n, (list, tuple)) else []:
        v = x.get("distance", x.get("d")) if isinstance(x, dict) else (x[0] if isinstance(x, (list, tuple)) and x else x)
        if isinstance(v, (int, float)) and not isinstance(v, bool):
            out.append(v)
    return out


def make_vf(row, t0):
    usig = unscored_text(t0)

    def vf(cand, cfg=None):
        if unscored_text(cand) != usig:
            return {"exact": False}
        rr = row
        if cfg and cfg != row["cfg"]:
            cell, flags = parse_cfg(cfg); rr = dict(row, cfg=cfg, cell=cell, flags=" ".join(flags))
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / Path(row["c_path"]).name; p.write_text(cand)
            return verify(rr, p, include_root=ROOT / "include")
    return vf


def menu_of(A, row, t0, cen, k):
    """A's k nearest non-identical candidates, ranked by listing distance to t0's listing."""
    CAPTURE[row["id"]] = {}
    try:
        if A.T.eligible(t0, row, cen):
            return None
        try:
            A.T.apply_verified(t0, row, cen, lambda c, cfg=None: {"exact": False})
        except Exception as e:                                                    # noqa: BLE001
            print("A error", row["id"], A.__name__, repr(e)[:120], flush=True)
    finally:
        cap = CAPTURE.pop(row["id"], {})
    target = compile_s(row, t0)
    if target is None:
        return []
    usig, p0, h0 = unscored_text(t0), len(sites_of(t0)), sha_text(t0)
    ranked = []
    for h, c in cap.items():
        if h == h0 or unscored_text(c) != usig:
            continue
        pc = len(sites_of(c))
        if pc > p0:
            continue
        lst = compile_s(row, c)
        if lst is None:
            continue
        ranked.append((XS.sdiff(target, lst), pc, h, c))
    ranked.sort(key=lambda x: (x[0], x[1]))
    # a candidate with NO pin left cannot be composed: every generator's eligible() wants a pin site.  Its
    # distance is still the evidence of a bounded negative (the move A alone gets closest to).
    STATS[row["id"], A.__name__] = {"menu": len(cap), "built": len(ranked),
                                    "pinfree_best": min([d for d, pc, _h, _c in ranked if pc == 0] or [None],
                                                        key=lambda x: (x is None, x))}
    if MODE["pinfree"]:
        return [x for x in ranked if x[1] == 0 and x[0] <= MODE["max_dA"]][:k]
    return [x for x in ranked if x[1] > 0][:k]


def one(job):
    row, t0, src, As, Bs, k, cen = job
    p0 = len(sites_of(t0)); vf = make_vf(row, t0); recs = []; best = None
    for an in As:
        A = load(an)
        menu = menu_of(A, row, t0, cen, k)
        if menu is None:
            recs.append({"id": row["id"], "A": an, "outcome": "A-refused"}); continue
        st = STATS.pop((row["id"], A.__name__), {})
        if not menu:
            recs.append({"id": row["id"], "A": an, "outcome": "A-empty", **st}); continue
        for d, pc, h, cA in menu:
            rec = {"id": row["id"], "src": src, "A": an, "dA": d, "pinsA": pc, "pins0": p0, **st, "B": {}}
            anchor = None
            if MODE["pinfree"]:
                import residue_anchor as RA
                res = RA.residue_lines(row, t0, cA)
                sites = RA.anchor_sites(cA, res, MODE["anchors"])
                if not sites and res is not None:          # listing-exact (d0): anchor on A's own move
                    sites = RA.anchor_sites(cA, RA.changed_lines(t0, cA), MODE["anchors"])
                    rec["anchor_from"] = "A-move"
                rec["residue"] = [[ln, w] for ln, w in (res or [])[:12]]
                rec["anchors"] = [s[5] for s in sites]
                if not sites:
                    rec["outcome"] = "no-residue-anchor"; recs.append(rec); continue
                anchor = RA.anchored(cA, sites); anchor.__enter__()
            SUBST[h] = t0
            try:
                for bn in Bs:
                    B = load(bn)
                    tb = time.time()
                    try:
                        if B.T.eligible(cA, row, cen):
                            continue
                        new, info = B.T.apply_verified(cA, row, cen, vf)
                    except Exception as e:                                        # noqa: BLE001
                        rec["B"][bn] = {"error": repr(e)[:100]}; continue
                    near = nearest_of(info)
                    if new and len(sites_of(new)) < p0:
                        pn = len(sites_of(new))
                        rec["B"][bn] = {"exact": True, "pins": pn, "step": str(info.get("step", ""))[:120],
                                        "s": round(time.time() - tb, 1)}
                        if best is None or pn < best[0]:
                            best = (pn, new, "%s(d%d)->%s" % (an, d, bn))
                    else:
                        rec["B"][bn] = {"exact": bool(new), "near": min(near) if near else None, "s": round(time.time() - tb, 1)}
            finally:
                SUBST.pop(h, None)
                if anchor is not None:
                    anchor.__exit__(None, None, None)
            recs.append(rec)
    return row, t0, src, recs, best


def bestB(rec):
    """(B, retail distance) of the nearest B candidate on one cA, or None."""
    bs = [(v["near"], b) for b, v in rec.get("B", {}).items() if v.get("near") is not None]
    return min(bs) if bs else None


def near_rows(D, journals):
    """(id -> [A generators]) from miss records with nearest distance <= D whose text is still the row's src/."""
    cur = {}
    for r in rows():
        p = clean_path(r)
        if p.exists():
            cur[r["id"]] = sha_text(p.read_text(errors="replace"))
    known = {p.stem for p in (ROOT / "tools/xform").glob("t*.py")}
    out, best = {}, {}
    for pat in journals:
        for j in glob.glob(str(NL / pat / "journal.jsonl")):
            lane = Path(j).parent.name
            gens = [g for g in known if g in lane]
            if not gens or "_check" in lane or "probe" in lane:
                continue
            gen = max(gens, key=len)
            for r in read_jsonl(Path(j)):
                n = nearest_of(r)
                if r.get("outcome") != "miss" or cur.get(r.get("id")) != r.get("in_sha") or not n:
                    continue
                if min(n) <= D:
                    out.setdefault(r["id"], [])
                    best[r["id"]] = min(best.get(r["id"], D), min(n))
                    if gen not in out[r["id"]]:
                        out[r["id"]].append(gen)
    return {k: out[k] for k in sorted(out, key=lambda k: (best[k], k))}     # nearest misses first


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lane"); ap.add_argument("--rows"); ap.add_argument("--near", type=int)
    ap.add_argument("--A"); ap.add_argument("--B", default="cascade"); ap.add_argument("--k", type=int, default=3)
    ap.add_argument("--workers", type=int, default=6); ap.add_argument("--base-from")
    ap.add_argument("--min-pins", type=int, default=1, help="skip rows with fewer pin sites (a depth-2 win needs a pin per move)")
    ap.add_argument("--max-rows", type=int, default=0)
    ap.add_argument("--skip-A", default="", help="generators never used as A (e.g. t101_crossmerge: its menu costs ~200 listings a row)")
    ap.add_argument("--journals", default="r73_h_t*,r73_h2_t*,r73_h3_t*,r76_cascade_t*")
    ap.add_argument("--pinfree", action="store_true", help="compose on A's PIN-FREE candidates, B anchored on the residue")
    ap.add_argument("--max-dA", type=int, default=20, help="--pinfree: farthest pin-free stage-1 candidate kept")
    ap.add_argument("--anchors", type=int, default=6, help="--pinfree: residue statements registered as anchors")
    a = ap.parse_args()
    MODE.update(pinfree=a.pinfree, max_dA=a.max_dA, anchors=a.anchors)
    want = {}
    if a.rows:
        for tok in a.rows.split(","):
            rid, _, gs = tok.partition("@")
            want.setdefault(rid, []).extend([g for g in gs.split("+") if g])
    if a.near is not None:
        for rid, gs in near_rows(a.near, a.journals.split(",")).items():
            want.setdefault(rid, []).extend(g for g in gs if g not in want.get(rid, []))
    defaultA = a.A.split(",") if a.A else []
    Bs = (PF_B if a.pinfree else default_B()) if a.B == "cascade" else a.B.split(",")
    for n in set(Bs) | set(defaultA) | {g for gs in want.values() for g in gs}:
        load(n)
    patch_modules()
    if a.pinfree:
        import residue_anchor
        print("residue_anchor: patched", residue_anchor.install(), "bindings", flush=True)
    cen = {c["id"]: c for c in read_jsonl(ROOT / "ledger/census.jsonl")}
    by = {r["id"]: r for r in rows()}
    OUT = NL / a.lane; (OUT / "out").mkdir(parents=True, exist_ok=True); (OUT / ".ignore").write_text("*\n")
    J = OUT / "journal.jsonl"
    done = {(r["id"], r["in_sha"]) for r in read_jsonl(J) if "in_sha" in r} if J.exists() else set()   # resumable
    skipA = set(a.skip_A.split(",")) - {""}
    jobs = []
    for rid, gs in want.items():
        r = by.get(rid)
        if not r:
            print("unknown row", rid); continue
        t0, src = base_text(r, a.base_from)
        if len(sites_of(t0)) < max(1, a.min_pins):
            print("skip", rid, "pins <", max(1, a.min_pins), "in", src); continue
        if (rid, sha_text(t0)) in done:
            continue
        As = [g for g in (gs or defaultA) if g not in skipA]
        if not As:
            print("skip", rid, "no A generator"); continue
        jobs.append((r, t0, src, As, Bs, a.k, cen.get(rid, {})))
        if a.max_rows and len(jobs) >= a.max_rows:
            break
    print(len(jobs), "rows,", len(Bs), "B generators", flush=True)
    lock, t_0, wins = threading.Lock(), time.time(), 0
    with ThreadPoolExecutor(a.workers) as ex:
        for row, t0, src, recs, best in ex.map(one, jobs):
            with lock, J.open("a") as f:
                for rec in recs:
                    f.write(json.dumps(rec) + "\n")
                summary = {"id": row["id"], "src": src, "in_sha": sha_text(t0), "pins0": len(sites_of(t0)),
                           "outcome": "exact" if best else "miss"}
                if best:
                    summary.update(pins_out=best[0], step=best[2])
                f.write(json.dumps(summary) + "\n")
            if best:
                wins += 1
                d = OUT / "out" / row["container"]; d.mkdir(exist_ok=True); n = Path(row["c_path"]).name
                (d / n).write_text(best[1]); (d / (n + ".base_sha")).write_text(sha_text(t0) + "\n")
                print("WIN", row["id"], src, len(sites_of(t0)), "->", best[0], best[2], flush=True)
            else:
                dist = sorted(((rec["dA"], rec["A"], bestB(rec)) for rec in recs if "dA" in rec), key=lambda x: x[0])[:3]
                print("miss", row["id"], src, "A/dA/bestB:", dist, flush=True)
    print(f"done {len(jobs)} rows, {wins} wins, {time.time() - t_0:.0f}s")


if __name__ == "__main__":
    main()
