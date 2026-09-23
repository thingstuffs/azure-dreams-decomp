#!/usr/bin/env python3
"""The cascade generator lists, parsed ONCE (round 76).

    python3 tools/lanes/cascade_list.py [cascade_extra.txt]   -> the EXTRA_T list, space-separated, on stdout

tools/lanes/cascade_extra.txt holds one generator per line (`#` starts a comment).  Until round 76, land_gap.sh read
it with `grep -v '^#' | tr '\\n' ' '`, and three commits (72cbc693, 1ff6caea, 49669ba5) extended it with
`sed 's/$/ tNN .../'`, which appended six generators to EVERY line, comments included: each of t96-t102 then swept
~17 times per cascade pass.  This parser makes that class of edit harmless and loud:
  * comments are stripped (`#` to end of line, anywhere), tokens split on whitespace;
  * duplicates are dropped (first occurrence kept) with a warning on stderr;
  * a token that is not a module tools/xform/<token>.py of THIS repository is dropped with a warning (a stray word
    would otherwise cost one failing sweep.py run per cascade pass);
  * a token already in land_lanes.sh's built-in cascade (`builtin()`) is dropped with a note: it would sweep twice.
coherence_sweep.py takes `full()` = the built-in list + these extras, so its default can no longer lag behind.
"""
import re
import sys
from pathlib import Path

HERE = Path(__file__).resolve().parent            # tools/lanes of the repository this file lives in
XFORM = HERE.parent / "xform"
EXTRA = HERE / "cascade_extra.txt"
LAND = HERE / "land_lanes.sh"
_FOR = re.compile(r"for T in (.*?);\s*do", re.S)


def builtin(path=LAND):
    """land_lanes.sh's built-in cascade (the `for T in ... ${EXTRA_T:-} t2_pins; do` loop), in order, without
    the EXTRA_T expansion and without the trailing t2_pins."""
    m = _FOR.search(Path(path).read_text())
    if not m:
        return []
    toks = m.group(1).replace("\\\n", " ").split()
    return [t for t in toks if not t.startswith("$") and t != "t2_pins"]


def extras(path=EXTRA, warn=None, known=None, land=LAND):
    """The EXTRA_T generators of `path`: comment-stripped, deduplicated, restricted to existing tools/xform modules
    and to generators land_lanes.sh does not already sweep.  `warn(msg)` receives every dropped token."""
    warn = warn or (lambda m: print("cascade_list: " + m, file=sys.stderr))
    known = known if known is not None else {p.stem for p in XFORM.glob("t*.py")}
    base = set(builtin(land)) if land and Path(land).exists() else set()
    out, seen, dups = [], set(), {}
    for n, line in enumerate(Path(path).read_text().splitlines(), 1):
        for tok in line.split("#", 1)[0].split():
            if tok in seen:
                dups[tok] = dups.get(tok, 0) + 1; continue
            seen.add(tok)
            if tok not in known:
                warn("line %d: %s is not a tools/xform module, dropped" % (n, tok)); continue
            if tok in base:
                warn("line %d: %s is already in land_lanes.sh's built-in cascade, dropped" % (n, tok)); continue
            out.append(tok)
    for tok, k in dups.items():
        warn("%s listed %d more time(s), duplicates dropped - one generator per line" % (tok, k))
    return out


def full():
    """Built-in cascade + extras + t2_pins: the whole cascade land_lanes.sh runs."""
    return builtin() + extras(warn=lambda m: None) + ["t2_pins"]


if __name__ == "__main__":
    print(" ".join(extras(sys.argv[1] if len(sys.argv) > 1 else EXTRA)))
