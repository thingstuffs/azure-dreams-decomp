#!/usr/bin/env python3
"""Family-mode measurement: a move applied at EVERY eligible site of the function at once, screened
beside the singles on the near band (LANE_KIT round 31: a move that only works jointly is invisible
to every one-site generator ranked by screen distance).

    python3 tools/lanes/family_measure.py CENSUS.jsonl OUT.jsonl [--procs 8] [--band 4]
                                          [--moves dropcopy,inline_def,retype_ptr] [--only ROWS.txt]
    python3 tools/lanes/family_measure.py summary OUT.jsonl [--new NEW.txt]

CENSUS is `erase_census.py` output; the near band is every site with 1 <= d0 <= BAND and the rows
holding one.  One record per (row, move, base):

  dropcopy    base = the pinned text.  Singles: `natural.dropcopy_candidates` (the `x->y` form, which
              drops the pins on x; the `+pins` form removes nothing and is not counted).  Joint: the
              copies folded one after another, each step re-read on the current text.
  inline_def  varset moves.  Two bases, both erased with `erase_many(clean_notes=True)`: `one` = one
  retype_ptr  near-band ASM_REG/KEEP/KEEP_NV site erased (t64's own structure), `all` = every such site
              of the row erased (t69's shape: the keeps on every moved local went together).  Singles:
              the move's own menu on the base; joint: the fold of that menu.

Every distance is `xform.screen.sdiff` against the PINNED listing, so 0 means identical cc1 output
with fewer pins.  `k` is the number of moves the joint applied (k >= 2 is where a joint can differ
from a single; t64's depth-2 beam already composes two moves, so k >= 3 is the reach no search has).
A joint is counted only if t64's `allowed` admits it (no scaffolding, arms and qualifiers unchanged).
Keep OUT in the scratchpad (a record carries candidate labels, not texts, but there are thousands).
"""
import collections
import json
import sys
import time
from multiprocessing import Pool
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
from common import rows as all_rows                      # noqa: E402
from pin_census import sites_of, unscored_text           # noqa: E402
from pin_sites import erase_many                         # noqa: E402
from screen import compile_s, sdiff                      # noqa: E402
import natural as N                                      # noqa: E402
import varset as V                                       # noqa: E402
from t64_varset import allowed, PIN_MACROS, site_var     # noqa: E402

SINGLES_CAP = 48
FOLD_CAP = 32
ROWS = None
CFG = {"band": 4, "moves": ("dropcopy", "inline_def", "retype_ptr")}


def _rows():
    global ROWS
    if ROWS is None:
        ROWS = {r["id"]: r for r in all_rows()}
    return ROWS


def _compile(row, text):
    try:
        return compile_s(row, text)
    except Exception:            # a cc1 timeout propagates by design; here it is one failed screen
        return None


# ---------------------------------------------------------------- the move kinds

def _dropcopy(text):
    return [(l, c) for l, c in N.dropcopy_candidates(text) if not l.endswith("+pins")]


def _inline(text):
    return V.inline_def_candidates(text)


def _retype(text):
    return V.retype_ptr_candidates(text)


def _key(label):
    """The variable a candidate moves: the fold applies each variable once."""
    head, _, rest = label.partition(":")
    if head == "dropcopy":
        return rest.split("->")[0]
    if head == "inline_def":
        rest = rest.removeprefix("all:")
        return rest.split("@")[0]
    if head == "retype_ptr":
        return rest.split(">")[0]
    return None


MOVES = {"dropcopy": _dropcopy, "inline_def": _inline, "retype_ptr": _retype}


def fold(base, gen, cap=FOLD_CAP):
    """The move applied to every eligible site, one step at a time, each re-read on the new text."""
    cur, applied, labels = base, set(), []
    for _ in range(cap):
        try:
            cands = gen(cur)
        except Exception:
            break
        cands = sorted(cands, key=lambda lc: 0 if ":all:" in lc[0] else 1)   # a whole web set first
        step = next(((k, l, c) for l, c in cands for k in [_key(l)] if k and k not in applied), None)
        if step is None:
            break
        applied.add(step[0])
        labels.append(step[1])
        cur = step[2]
    return cur, labels


# ---------------------------------------------------------------- one row

def measure(row, text, ref, base, base_kind, base_label, move, n_in, usig):
    gen = MOVES[move]
    rec = dict(id=row["id"], move=move, base=base_kind, base_label=base_label, n_in=n_in)
    try:
        singles = gen(base)
    except Exception as e:
        rec["err"] = "menu:%s" % type(e).__name__
        return rec
    keys = {k for l, _ in singles for k in [_key(l)] if k}
    rec["eligible"] = len(keys)
    rec["singles_n"] = len(singles)
    if not singles:
        return rec
    sd = []
    for label, cand in singles[:SINGLES_CAP]:
        got = _compile(row, cand)
        sd.append((sdiff(ref, got), label, allowed(text, cand, usig, n_in)))
    rec["single_fail"] = sum(1 for d, _, _ in sd if d is None)
    ok = [(d, l) for d, l, a in sd if d is not None and a]
    rec["single_min"] = min((d for d, _ in ok), default=None)
    rec["singles"] = sorted(ok)[:8]
    if len(keys) < 2:
        rec["k"] = 1
        return rec
    joint, labels = fold(base, gen)
    rec["k"] = len(labels)
    rec["joint_labels"] = labels
    if len(labels) < 2:
        return rec
    got = _compile(row, joint)
    rec["joint_d"] = sdiff(ref, got)
    rec["joint_allowed"] = allowed(text, joint, usig, n_in)
    rec["joint_pins_removed"] = n_in - len(sites_of(joint))
    return rec


def one(job):
    rid, near_sites = job
    row = _rows().get(rid)
    if row is None or not row.get("cfg"):
        return [dict(id=rid, err="no-row-or-cfg")]
    p = ROOT / "src" / (rid + ".c")
    if not p.is_file():
        return [dict(id=rid, err="no-src")]
    text = p.read_text(errors="replace")
    ref = _compile(row, text)
    if ref is None:
        return [dict(id=rid, err="ref-build")]
    sites = sites_of(text)
    n_in = len(sites)
    usig = unscored_text(text)
    out = []
    if "dropcopy" in CFG["moves"]:
        out.append(measure(row, text, ref, text, "pinned", "", "dropcopy", n_in, usig))
    vmoves = [m for m in CFG["moves"] if m != "dropcopy"]
    if vmoves:
        bases = []
        pinned = [(i, s) for i, s in enumerate(sites) if s[1] in PIN_MACROS]
        for i, s in pinned:
            if i in near_sites:
                bases.append(("one", "pin%d:%s:%s" % (i, s[1], site_var(s) or ""), erase_many(text, [s], clean_notes=True)))
        if len(pinned) > 1:
            bases.append(("all", "pins:%d" % len(pinned), erase_many(text, [s for _, s in pinned], clean_notes=True)))
        for kind, label, base in bases:
            if unscored_text(base) != usig:
                out.append(dict(id=rid, base=kind, base_label=label, err="erasure-in-unscored-arm"))
                continue
            for m in vmoves:
                out.append(measure(row, text, ref, base, kind, label, m, n_in, usig))
    return out


def _init(cfg):
    CFG.update(cfg)


# ---------------------------------------------------------------- summary

def summary(path, new_out=None):
    by = collections.defaultdict(collections.Counter)
    new_rows = collections.defaultdict(list)
    pins_new = collections.Counter()
    errs = collections.Counter()
    for l in open(path):
        r = json.loads(l)
        if "err" in r:
            errs[r["err"]] += 1
            continue
        key = (r["move"], r["base"])
        c = by[key]
        c["records"] += 1
        if r.get("singles_n"):
            c["with-a-candidate"] += 1
        if r.get("k", 0) < 2:
            continue
        c["k>=2"] += 1
        dj, ds = r.get("joint_d"), r.get("single_min")
        if dj is None:
            c["joint-fail"] += 1
            continue
        if not r.get("joint_allowed"):
            c["joint-not-allowed"] += 1
            continue
        if dj == 0 and (ds is None or ds > 0):
            c["JOINT-0-no-single"] += 1
            if r["k"] >= 3:
                c["  of which k>=3"] += 1
            pins_new[key] += r.get("joint_pins_removed", 0)
            new_rows[key].append(r)
        elif dj == 0:
            c["joint-0-and-a-single-0"] += 1
        elif ds is None or dj < ds:
            c["joint-closer"] += 1
        elif dj == ds:
            c["joint-equal"] += 1
        else:
            c["joint-worse"] += 1
    print("errors:", dict(errs) or "none")
    cols = ["records", "with-a-candidate", "k>=2", "JOINT-0-no-single", "  of which k>=3", "joint-0-and-a-single-0",
            "joint-closer", "joint-equal", "joint-worse", "joint-fail", "joint-not-allowed"]
    print("%-22s" % "move/base" + "".join("%8s" % c.strip()[:8] for c in cols) + "  pins-new")
    for key in sorted(by):
        c = by[key]
        print("%-22s" % "/".join(key) + "".join("%8d" % c[x] for x in cols) + "  %d" % pins_new[key])
    print("columns: " + " | ".join(cols))
    if new_out:
        with open(new_out, "w") as f:
            for key in sorted(new_rows):
                for r in sorted(new_rows[key], key=lambda r: -r.get("joint_pins_removed", 0)):
                    f.write("%s\t%s\t%s\t%s\tk=%d\tpins=%d\tsingle_min=%s\t%s\n" % (
                        r["id"], r["move"], r["base"], r.get("base_label", ""), r["k"],
                        r.get("joint_pins_removed", 0), r.get("single_min"), "+".join(r["joint_labels"])))
        print("new-reach rows ->", new_out)


def main():
    a = sys.argv[1:]
    if a and a[0] == "summary":
        new_out = a[a.index("--new") + 1] if "--new" in a else None
        return summary(a[1], new_out)
    census, out = Path(a.pop(0)), Path(a.pop(0))
    procs, only, cfg = 8, None, dict(CFG)
    while a:
        k = a.pop(0)
        if k == "--procs":
            procs = int(a.pop(0))
        elif k == "--band":
            cfg["band"] = int(a.pop(0))
        elif k == "--moves":
            cfg["moves"] = tuple(a.pop(0).split(","))
        elif k == "--only":
            only = set(x.split()[0] for x in Path(a.pop(0)).read_text().splitlines() if x.strip())
    near = collections.defaultdict(set)
    for l in census.open():
        d = json.loads(l)
        if "err" in d or d.get("d0") is None:
            continue
        if 1 <= d["d0"] <= cfg["band"]:
            near[d["id"]].add(d["i"])
    done = set()
    if out.exists():
        for l in out.open():
            try:
                done.add(json.loads(l)["id"])
            except Exception:
                pass
    jobs = sorted((rid, s) for rid, s in near.items() if rid not in done and (only is None or rid in only))
    print("near-band rows %d, to do %d, moves %s" % (len(near), len(jobs), ",".join(cfg["moves"])), flush=True)
    t0 = time.time()
    n = 0
    with Pool(procs, initializer=_init, initargs=(cfg,)) as p, out.open("a") as f:
        for recs in p.imap_unordered(one, jobs, chunksize=2):
            for r in recs:
                f.write(json.dumps(r) + "\n")
            f.flush()
            n += 1
            if n % 50 == 0:
                print(n, "rows", round(time.time() - t0), "s", flush=True)
    print("done", n, "rows", round(time.time() - t0), "s")


if __name__ == "__main__":
    main()
