#!/usr/bin/env python3
"""Restore the unscored arms a lane candidate flattened away, so the landing rule can accept it.

    python3 tools/lanes/arm_restore.py <lane>            # work/native_lane/<lane>/out/*/*.c -> work/native_lane/<lane>_arms/out/
    python3 tools/lanes/arm_restore.py --check <lane>    # report only

Model lanes routinely rewrite a row's `#ifdef NON_MATCHING` scaffolding (the block that gives the port build a
plain variable and the scored build a register-pinned one) into a plain local declaration.  The scored arm is
theirs to change, but the port and dead arms are text no byte gate compiles, so `pin_census.landing_refusal`
refuses the candidate ("edits a NON_MATCHING/#if 0 arm").  Five of eight re-audited lane wins fell to this on
2026-09-19.  This tool takes each preprocessor block of the CURRENT text that carries port or dead lines and, when
the candidate no longer contains that block verbatim, re-inserts it with its scored-arm lines removed (the
candidate re-expressed them), at the block's original neighbourhood.  The result must reproduce the current text's
unscored arms exactly (checked with `unscored_text`); the byte scorer then decides as usual.
"""
import re, sys
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, sha_text                         # noqa: E402
from pin_census import arm_labels, unscored_text, PP_RE, sites_of     # noqa: E402


def blocks(text):
    """[(first, last)] line spans of top-level preprocessor blocks that contain port or dead lines."""
    lines, labels = text.split("\n"), arm_labels(text)
    out, depth, start = [], 0, None
    for i, ln in enumerate(lines):
        m = PP_RE.match(ln)
        if not m:
            continue
        d = m.group(1)
        if d in ("if", "ifdef", "ifndef"):
            if depth == 0:
                start = i
            depth += 1
        elif d == "endif":
            depth -= 1
            if depth == 0 and start is not None:
                if any(labels[k] in ("port", "dead") for k in range(start, i + 1)):
                    out.append((start, i))
                start = None
    return out


def restore(cur, cand):
    """The candidate with every port/dead-bearing block of `cur` restored (scored-arm lines dropped)."""
    cl, cand_lines = cur.split("\n"), cand.split("\n")
    labels = arm_labels(cur)
    out = cand_lines
    for a, b in blocks(cur):
        block = cl[a:b + 1]
        if any(cand_lines[i:i + len(block)] == block for i in range(len(cand_lines))):
            continue                                              # still there verbatim
        kept = [ln for k, ln in zip(range(a, b + 1), block) if labels[k] != "match"]
        # drop `#ifndef NON_MATCHING` framings left empty, keep every directive that frames a port/dead line
        anchor = None
        for k in range(a - 1, -1, -1):                            # nearest preceding context line present in the candidate
            if cl[k].strip() and not PP_RE.match(cl[k]):
                try:
                    anchor = out.index(cl[k]); break
                except ValueError:
                    continue
        pos = anchor + 1 if anchor is not None else next((i + 1 for i, ln in enumerate(out) if ln.startswith("#include")), 0)
        out = out[:pos] + kept + out[pos:]
    return "\n".join(out)


def main():
    check = "--check" in sys.argv
    lane = [a for a in sys.argv[1:] if not a.startswith("--")][0]
    by = {r["id"]: r for r in rows()}
    src = ROOT / "work/native_lane" / lane / "out"
    dst = ROOT / "work/native_lane" / (lane + "_arms") / "out"
    n = 0
    for f in sorted(src.glob("*/*.c")):
        rid = f.parent.name + "/" + f.stem
        if rid not in by:
            continue
        cur = clean_path(by[rid]).read_text(errors="replace"); cand = f.read_text(errors="replace")
        if unscored_text(cand) == unscored_text(cur):
            continue                                              # nothing to restore
        fixed = restore(cur, cand)
        ok = unscored_text(fixed) == unscored_text(cur)
        print(f"{rid}: arms {'restored' if ok else 'NOT restored'}; pins {len(sites_of(cur))} -> {len(sites_of(fixed))}")
        if ok and not check:
            (dst / f.parent.name).mkdir(parents=True, exist_ok=True)
            (dst / f.parent.name / f.name).write_text(fixed)
            (dst / f.parent.name / (f.name + ".base_sha")).write_text(sha_text(cur) + "\n")
            (dst.parent / ".ignore").write_text("*\n")
            n += 1
    print(f"written {n} to {dst}")


if __name__ == "__main__":
    main()
