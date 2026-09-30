#!/usr/bin/env python3
"""Tree-wide lone-erasure census: every live pin site erased alone, screened against the pinned listing.

    python3 tools/lanes/erase_census.py OUT.jsonl [--procs 8] [--only ROWS.txt] [--diff 4 | --full-diff] [--fp]
    python3 tools/lanes/erase_census.py summary OUT.jsonl

One record per pin site: `d0` is `xform.screen.sdiff` between cc1's listing of the pinned text and of
the text with that one site erased (`pin_sites.erase_many`).  `d0 == 0` is the class the cc1 screen
cannot see at all (the pin's effect is assembler-side, or the site is dead and T2's) - round 30
measured it at 21 of 6,480 sites, which closed the maspsx-level-screen question.  With `--diff N`
the records of sites with `d0 <= N` also carry the changed listing lines (`-`/`+` prefixed, from
difflib), so the residues can be grouped by opcode: what one erasure changes is the mechanism the
pin holds, and the census of those is what a generator brief starts from.

`--full-diff` (round 81, r81_fable_eqv: "class sizing over long-diff sites needs the full diffs") gives EVERY
site that builds its changed listing lines, all of them - no `d0 <= N` gate and no 16-line cap - still one
JSONL record per site, so the residue classes of the far band (68% of all sites) can be sized.  It replaces
`--diff N`.  The output is much larger (the far band's diffs run to hundreds of lines per site): write it where
the caller says, OUTSIDE the work/ subtrees agents search (a directory with a `.ignore`, or the scratchpad);
the tool warns when OUT is under work/ without a `.ignore` above it, and when OUT passes 50 MB.

With `--fp` EVERY record (not only the near ones) also carries `fp`, the residue fingerprint of
`tools/lanes/residue.py` - the same function the round-33 perturbation catalogue
(`tools/lanes/perturb_catalog.py`) applies to its own diffs, so a census fingerprint can be looked up
directly among the catalogue's and each pinned site gets its ranked CAUSES.  The flag is additive:
without it the output is byte-identical to the flagless output of every earlier run.

The whole tree takes about half a minute at 8 processes (gcc 2.x cc1 compiles a row in ~25 ms).
Keep OUT outside work/ subtrees that agents search (a full census with diffs is ~3 MB); the
scratchpad is the right place.  Resumable: rows already in OUT are skipped.
"""
import collections
import difflib
import glob
import json
import sys
import time
from multiprocessing import Pool
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))
from common import rows as all_rows                      # noqa: E402
from pin_census import sites_of                          # noqa: E402
from pin_sites import erase_many                         # noqa: E402
from screen import compile_s, sdiff                      # noqa: E402
sys.path.insert(0, str(ROOT / "tools/lanes"))
import residue                                           # noqa: E402

ROWS = None
DIFF_MAX = -1
FP = False
FULL = False
DIFF_CAP = 16                    # lines kept per record under --diff N (unchanged since round 30)
WARN_BYTES = 50 * 1024 * 1024    # --full-diff output size warning


def _rows():
    global ROWS
    if ROWS is None:
        ROWS = {r["id"]: r for r in all_rows()}
    return ROWS


def one(rid):
    row = _rows().get(rid)
    if row is None or not row.get("cfg"):
        return [dict(id=rid, err="no-row-or-cfg")]
    text = (ROOT / "src" / (rid + ".c")).read_text()
    sites = sites_of(text)
    if not sites:
        return []
    ref = compile_s(row, text)
    if ref is None:
        return [dict(id=rid, err="ref-build")]
    out = []
    for i, s in enumerate(sites):
        cand = erase_many(text, [s])
        c = compile_s(row, cand)
        d0 = None if c is None else sdiff(ref, c)
        rec = dict(id=rid, i=i, kind=s[0], macro=s[1], arg=str(s[2])[:40], line=s[5], d0=d0, n=len(sites))
        if FP:
            rec["fp"] = residue.fingerprint(ref, c)
        keep = diff_keep(d0, DIFF_MAX, FULL) if c is not None else None
        if keep is not None:
            rec["diff"] = changed_lines(ref, c, keep)
        out.append(rec)
    return out


def diff_keep(d0, diff_max, full):
    """How many changed lines a record keeps: None = no `diff` field, 0 = every line (`--full-diff`)."""
    if d0 is None:
        return None
    if full:
        return 0
    if 0 <= diff_max and d0 <= diff_max:
        return DIFF_CAP
    return None


def changed_lines(ref, cand, cap=DIFF_CAP):
    """The `-`/`+` lines of the n=0 unified diff of two listings, the first `cap` of them (0 = all)."""
    lines = [ln for ln in difflib.unified_diff(ref, cand, n=0, lineterm="")
             if ln[:1] in "+-" and not ln.startswith(("---", "+++"))]
    return lines if not cap else lines[:cap]


def _init(diff_max, fp=False, full=False):
    global DIFF_MAX, FP, FULL
    DIFF_MAX = diff_max
    FP = fp
    FULL = full


def searched_work_path(out, work=None):
    """True when `out` sits under <repo>/work/ (or `work`) with no `.ignore` in any directory between it and
    work/ (agents' recursive searches read such a file in full - the IO rule in the owner's CLAUDE.md)."""
    out = Path(out).resolve()
    work = Path(work or ROOT / "work").resolve()
    try:
        out.relative_to(work)
    except ValueError:
        return False
    d = out.parent
    while True:
        if (d / ".ignore").is_file() and d != work:
            return False
        if d == work:
            return not (work / ".ignore").is_file() or not ignored_by(work / ".ignore", out.relative_to(work))
        d = d.parent


def ignored_by(ignore_file, rel):
    """Rough `.ignore` check: a pattern line matching the first path component (or the whole path) of `rel`."""
    import fnmatch
    parts = Path(rel).parts
    for pat in ignore_file.read_text(errors="replace").splitlines():
        pat = pat.strip().rstrip("/").lstrip("/")
        if not pat or pat.startswith("#") or pat.startswith("!"):
            continue
        if any(fnmatch.fnmatch("/".join(parts[:k]), pat) or fnmatch.fnmatch(parts[k - 1], pat)
               for k in range(1, len(parts) + 1)):
            return True
    return False


def size_warning(out, limit=WARN_BYTES):
    """A warning line when `out` is over `limit` bytes, else None."""
    try:
        n = Path(out).stat().st_size
    except OSError:
        return None
    if n <= limit:
        return None
    return ("WARNING: %s is %.0f MB (> %d MB): keep it out of searched work/ subtrees, gzip it when done"
            % (out, n / 1048576.0, limit // 1048576))


def summary(path):
    c = collections.Counter(); z = collections.Counter(); rows = set(); errs = collections.Counter()
    for l in open(path):
        d = json.loads(l)
        if "err" in d:
            errs[d["err"]] += 1
            continue
        rows.add(d["id"])
        d0 = d["d0"]
        c["none" if d0 is None else min(d0, 30)] += 1
        if d0 == 0:
            z[d["macro"]] += 1
    n = sum(c.values())
    print("rows %d  sites %d  errors %s" % (len(rows), n, dict(errs) or "none"))
    print("d0 distribution (30 = 30 or more):")
    for k in sorted(c, key=lambda x: (isinstance(x, str), x)):
        print("  %4s %5d  %4.1f%%" % (k, c[k], 100.0 * c[k] / max(1, n)))
    print("d0 == 0 by macro:", z.most_common())


def main():
    a = sys.argv[1:]
    if a and a[0] == "summary":
        return summary(a[1])
    out = Path(a.pop(0)); procs = 8; only = None; diff_max = -1; fp = False; full = False
    while a:
        k = a.pop(0)
        if k == "--procs":
            procs = int(a.pop(0))
        elif k == "--only":
            only = set(x.split()[0] for x in Path(a.pop(0)).read_text().splitlines() if x.strip())
        elif k == "--diff":
            diff_max = int(a.pop(0))
        elif k == "--fp":
            fp = True
        elif k == "--full-diff":
            full = True
        else:
            raise SystemExit("erase_census: unknown argument %r" % k)
    if full and diff_max >= 0:
        raise SystemExit("erase_census: --full-diff keeps every line of every site; drop --diff N")
    if full and searched_work_path(out):
        print("WARNING: %s is under work/ with no .ignore above it; a --full-diff census is large and agents' "
              "recursive searches would read it in full - prefer the scratchpad or a directory with a .ignore"
              % out, flush=True)
    ids = sorted(f[len(str(ROOT)) + 5:-2] for f in glob.glob(str(ROOT / "src/*/*.c")))
    ids = [i for i in ids if i in _rows() and (only is None or i in only)]
    done = set()
    if out.exists():
        for l in out.open():
            try:
                done.add(json.loads(l)["id"])
            except Exception:
                pass
    ids = [i for i in ids if i not in done]
    t0 = time.time(); n = 0
    warned = False
    with Pool(procs, initializer=_init, initargs=(diff_max, fp, full)) as p, out.open("a") as f:
        for recs in p.imap_unordered(one, ids, chunksize=4):
            for r in recs:
                f.write(json.dumps(r) + "\n")
            f.flush(); n += 1
            if n % 200 == 0:
                print(n, "rows", round(time.time() - t0), "s", flush=True)
                w = size_warning(out)
                if w and not warned:
                    print(w, flush=True)
                    warned = True
    print("done", n, "rows", round(time.time() - t0), "s")
    w = size_warning(out)
    if w:
        print(w, flush=True)


if __name__ == "__main__":
    main()
