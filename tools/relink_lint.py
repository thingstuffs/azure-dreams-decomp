#!/usr/bin/env python3
"""Ratchet lint for name-keyed relocation text (docs/LINK_LISTS.md, decision 59/60).

Copies of a TU are link-list placements (config/link/): the object is rebound BY ADDRESS after compile. Two text
mechanisms of the old relink copies are therefore refused in new code:
  * `#define <ident> func_XXXXXXXX` / `D_XXXXXXXX` relocation lines (name-keyed substitution: B7 class 1);
  * new `/* Relink of matched <row>` copy files.
The files that still carry either are frozen in config/lint/relink_text.allow (one src/include path per line, plus
the kind). The allowlist only shrinks: a listed file that no longer carries the text is an error too, so a
conversion must drop it in the same change.

    python3 tools/relink_lint.py [--root R] check      # exit 1 on any problem
    python3 tools/relink_lint.py [--root R] shrink     # rewrite the allowlist without stale entries (never adds)
"""
import argparse, re, sys
from pathlib import Path

DEFINE = re.compile(r"^#define\s+\w+\s+(?:func|D)_[0-9A-Fa-f]{8}\b", re.M)
RELINK = re.compile(r"^/\* Relink of matched", re.M)
ALLOW = "config/lint/relink_text.allow"


def scan(root):
    """{relative path: set(kinds)} for every src/include .c/.h file carrying relink text."""
    out = {}
    for top in ("src", "include"):
        base = root / top
        if not base.is_dir():
            continue
        for p in sorted(base.rglob("*")):
            if p.suffix not in (".c", ".h") or not p.is_file():
                continue
            t = p.read_text(errors="replace")
            kinds = set()
            if RELINK.search(t):
                kinds.add("relink")
            if DEFINE.search(t):
                kinds.add("define")
            if kinds:
                out[str(p.relative_to(root))] = kinds
    return out


def read_allow(root):
    p = root / ALLOW
    out = {}
    if p.exists():
        for line in p.read_text().splitlines():
            line = line.strip()
            if line and not line.startswith("#"):
                path, kinds = line.split("\t")
                out[path] = set(kinds.split(","))
    return out


def problems(root):
    have, allow = scan(root), read_allow(root)
    bad = []
    for path, kinds in sorted(have.items()):
        extra = kinds - allow.get(path, set())
        if extra:
            bad.append("%s: new relocation text (%s); place the copy in config/link instead" % (path, ",".join(sorted(extra))))
    for path, kinds in sorted(allow.items()):
        gone = kinds - have.get(path, set())
        if gone:
            bad.append("%s: allowlist entry %s is stale; run tools/relink_lint.py shrink" % (path, ",".join(sorted(gone))))
    return bad


def shrink(root):
    have, allow = scan(root), read_allow(root)
    keep = {p: k & have.get(p, set()) for p, k in allow.items()}
    keep = {p: k for p, k in keep.items() if k}
    head = "# relink_lint ratchet (tools/relink_lint.py): files still carrying relink text. Only ever shrinks.\n"
    (root / ALLOW).write_text(head + "".join("%s\t%s\n" % (p, ",".join(sorted(k))) for p, k in sorted(keep.items())))
    return len(allow) - len(keep)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--root", default=str(Path(__file__).resolve().parent.parent))
    ap.add_argument("cmd", choices=["check", "shrink"])
    a = ap.parse_args()
    root = Path(a.root).resolve()
    if a.cmd == "shrink":
        print("dropped", shrink(root), "stale entries")
        return 0
    bad = problems(root)
    for b in bad:
        print(b)
    print("relink lint: %d problem(s), %d allowed file(s)" % (len(bad), len(read_allow(root))))
    return 1 if bad else 0


if __name__ == "__main__":
    sys.exit(main())
