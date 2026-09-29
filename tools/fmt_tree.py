#!/usr/bin/env python3
"""Apply tools/fmt_c.py to every row's src file whose C tokens, comments and preprocessor lines stay identical.

    python3 tools/fmt_tree.py [--only ids] [--dry-run]

Writes the reformatted files in place and prints the list of changed files (one per line, prefixed "CHANGED ").
A file whose token sequence would change is refused (a formatter bug) and left untouched. The caller gates the tree
(tools/build/gate_all.py + build_slus.sh) and commits; see the round-80 landing script in docs/HANDOVER.md.
"""
import argparse, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path
import fmt_c


# comments are ONE token each, with their text (whitespace-normalised): a line joined onto a `//` comment turns the
# joined code into comment text and must change the token sequence (round 80: 12 windows failed on exactly that)
CTOK = re.compile(r"/\*.*?\*/|//[^\n]*|" + fmt_c.TOK.pattern, re.S)


def toks(t):
    body = "\n".join(l for l in t.split("\n") if not l.lstrip().startswith("#") and not l.rstrip().endswith("\\"))
    return [" ".join(x.split()) if x.startswith(("/*", "//")) else x for x in CTOK.findall(body)]


def pp(t):
    return [l.strip() for l in t.split("\n") if l.lstrip().startswith("#")]


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--only")
    ap.add_argument("--dry-run", action="store_true")
    a = ap.parse_args()
    only = set(a.only.split(",")) if a.only else None
    n = refused = 0
    for r in rows():
        if only and r["id"] not in only:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        t = p.read_text(errors="replace")
        try:
            new = fmt_c.format_text(t)
        except Exception as e:                      # noqa: BLE001 - a formatter crash just skips the file
            print("REFUSED", r["id"], "crash", type(e).__name__); refused += 1; continue
        if new == t:
            continue
        if toks(new) != toks(t) or pp(new) != pp(t):
            print("REFUSED", r["id"], "token change"); refused += 1; continue
        if not a.dry_run:
            p.write_text(new)
        print("CHANGED", r["id"]); n += 1
    print("done: %d changed, %d refused" % (n, refused), file=sys.stderr)


if __name__ == "__main__":
    main()
