#!/usr/bin/env python3
"""Harvest landed pin removals that also CHANGED THE BODY, as a lane's exemplar set.

    python3 tools/lanes/build_exemplars.py --family REG --since 35af0001 \\
        --out work/native_lane/alloc_astra/evidence/exemplars_landed

Walks git history (`git log --reverse <since>..HEAD`) and, for every commit and every changed
`src/<container>/<row>.c`, counts the family's pin sites (tools/pin_census.py `sites_of`) in the
parent and child texts.  A diff is kept only when the count DECREASED *and* the change is more
than erasing pins: both texts are stripped of their pin sites (tools/pin_sites.py `erase_many`,
clean_notes=True), of C comments and of whitespace, and the two stripped texts must still differ.
That is the exemplar an astra lane wants - a removal that needed a rewrite, not a deletion.

Families: REG = `ASM_REG*`, KEEP = `ASM_KEEP*`, FENCE = `ASM_SCHED_BARRIER` / `ASM_MEM_BARRIER`.

Writes `<out>/<container>_<row>.<commit>.diff` (the git diff of that file at that commit) and
`<out>/INDEX.md`, one row per kept diff: commit, row id, family count before->after, the
generators the sweep journals (ledger/sweeps/*.jsonl) record as `"outcome":"applied"` for that row
at any time, and the diff filename.  The commit subjects follow at the end of INDEX.md.
Reads git and ledger/sweeps only; never writes into src/ and never commits.
"""
import argparse
import json
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of
from pin_sites import erase_many

FAMILIES = {
    "REG": lambda m: m.startswith("ASM_REG"),
    "KEEP": lambda m: m.startswith("ASM_KEEP"),
    "FENCE": lambda m: m in ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER"),
}
CMT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
WS_RE = re.compile(r"\s+")
MAX_JOURNAL = 64 * 1024 * 1024


def git(*args, **kw):
    return subprocess.run(["git", "-C", str(ROOT)] + list(args), capture_output=True, text=True,
                          errors="replace", **kw)


def blob(rev, path):
    """File text at a revision, or None when it does not exist there."""
    r = git("show", f"{rev}:{path}")
    return r.stdout if r.returncode == 0 else None


def skeleton(text):
    """The text with every pin site, comment and run of whitespace gone."""
    return WS_RE.sub("", CMT_RE.sub("", erase_many(text, sites_of(text), clean_notes=True)))


def generators():
    """row id -> set of transform names a sweep journal records as applied."""
    out = {}
    d = ROOT / "ledger" / "sweeps"
    if not d.is_dir():
        return out
    for j in sorted(d.glob("*.jsonl")):
        try:
            if j.stat().st_size > MAX_JOURNAL:
                print(f"  skip journal (too large): {j.name}", file=sys.stderr)
                continue
            with open(j, errors="replace") as fh:
                for line in fh:
                    if '"applied"' not in line:
                        continue
                    try:
                        rec = json.loads(line)
                    except Exception:
                        continue
                    if rec.get("outcome") != "applied":
                        continue
                    rid, tr = rec.get("id"), rec.get("transform")
                    if rid and tr:
                        out.setdefault(rid, set()).add(tr)
        except OSError as e:
            print(f"  skip journal {j.name}: {e}", file=sys.stderr)
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--family", required=True, choices=sorted(FAMILIES))
    ap.add_argument("--since", required=True, help="commit BEFORE the first one to walk")
    ap.add_argument("--out", required=True)
    a = ap.parse_args()
    keep = FAMILIES[a.family]
    out = Path(a.out)
    out.mkdir(parents=True, exist_ok=True)

    gens = generators()
    commits = git("log", "--reverse", "--format=%h", f"{a.since}..HEAD").stdout.split()
    rows, subjects, skipped = [], [], []
    for c in commits:
        subjects.append((c, git("log", "-1", "--format=%s", c).stdout.strip()))
        names = git("diff", "--name-only", f"{c}^", c, "--", "src").stdout.splitlines()
        for path in names:
            p = path.strip()
            parts = p.split("/")
            if len(parts) != 3 or parts[0] != "src" or not p.endswith(".c"):
                continue
            before, after = blob(f"{c}^", p), blob(c, p)
            if before is None or after is None:
                skipped.append(f"{c} {p}: added or deleted in this commit")
                continue
            try:
                nb = sum(1 for s in sites_of(before) if keep(s[1]))
                na = sum(1 for s in sites_of(after) if keep(s[1]))
            except Exception as e:
                skipped.append(f"{c} {p}: census failed ({type(e).__name__}: {e})")
                continue
            if na >= nb:
                continue
            try:
                if skeleton(before) == skeleton(after):
                    continue
            except Exception as e:
                skipped.append(f"{c} {p}: pin erasure failed ({type(e).__name__}: {e})")
                continue
            container, row = parts[1], parts[2][:-2]
            name = f"{container}_{row}.{c}.diff"
            diff = git("diff", f"{c}^", c, "--", p).stdout
            (out / name).write_text(diff)
            rows.append((c, f"{container}/{row}", nb, na,
                         ",".join(sorted(gens.get(f"{container}/{row}", ()))) or "-", name))

    idx = out / "INDEX.md"
    with open(idx, "w") as fh:
        fam = {"REG": "`ASM_REG*`", "KEEP": "`ASM_KEEP*`",
               "FENCE": "`ASM_SCHED_BARRIER` / `ASM_MEM_BARRIER`"}[a.family]
        fh.write(f"# Landed {a.family.lower()} removals with a body change (git history {a.since}..HEAD)\n\n")
        fh.write(f"""Each diff here lowered the number of {fam} pins AND changed the text beyond erasing pins
(with pins, comments and whitespace stripped, the two texts still differ).  `generators` lists the
generators the sweep journals (ledger/sweeps/) record as applied to that row at any time, so a row
can list several and the one that made this diff is usually among them; a lane win landed under its
lane tool's name (the column is unfiltered, so bookkeeping generators appear in it too).
Diffs are named `<container>_<row>.<commit>.diff`; commit subjects are at the end.

Built by `tools/lanes/build_exemplars.py --family {a.family} --since {a.since} --out {a.out}`.

| commit | row | {a.family.lower()}s | generators | diff |
|---|---|---|---|---|
""")
        for c, rid, nb, na, g, name in rows:
            fh.write(f"| {c} | {rid} | {nb}→{na} | {g} | {name} |\n")
        fh.write(f"\n{len(rows)} exemplars from {len(commits)} commits.\n\n## Commits\n\n")
        for c, s in subjects:
            fh.write(f"- {c} {s}\n")
        if skipped:
            fh.write("\n## Not processed\n\n")
            for s in skipped:
                fh.write(f"- {s}\n")
    print(f"{len(rows)} diffs + INDEX.md -> {out}")
    for s in skipped:
        print(f"skipped: {s}")


if __name__ == "__main__":
    main()
