"""Verify a candidate that uses readable data names.
   1. listing identity: cc1 listing of the candidate (lane include dir first), spelled through ccproc
      --names-only with the LANE names table, must equal the pinned text's listing spelled through the
      real table (the assembler input; identical input = identical object).  `.extern NAME,size` lines
      are compared separately (size only drives gp decisions in gas macro expansion).
   2. byte score: the candidate with the shared header inlined and the readable names respelled D_
      (exactly ccproc's substitution, one level earlier) through tools/verify.py (kitlib.score_at)."""
import json, re, subprocess, sys, tempfile
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from cc import *
LANE_ = Path(__file__).resolve().parent.parent
import os
INC = Path(os.environ.get("TYPES_INC", str(LANE_ / "inc")))
def ccproc(asm, table):
    r = subprocess.run([sys.executable, str(REPO / "tools/build/ccproc.py"), "--names-tsv", str(table), "--names-only"], input=asm, capture_output=True, text=True)
    assert r.returncode == 0, r.stderr; return r.stdout
def listing2(row, text):
    # the candidate needs the lane include dir ahead of the repo one
    import cc as C
    cell, flags = parse_cfg(row["cfg"])
    D = REPO / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="cc_") as td:
        d = Path(td); (d / "f.c").write_text(text)
        r = subprocess.run([str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(INC), "-I" + str(REPO / "include"), "-w", "f.c", "-o", "f.i"], cwd=d, capture_output=True, text=True)
        if r.returncode: return None, r.stderr[-400:]
        r = subprocess.run([str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-o", "f.s"], cwd=d, capture_output=True, text=True)
        if r.returncode: return None, r.stderr[-400:]
        return (d / "f.s").read_text(errors="replace"), None
def split_ext(s):
    ext = sorted(l.strip() for l in s.splitlines() if l.strip().startswith(".extern"))
    body = [l for l in s.splitlines() if l.strip() and not l.strip().startswith(".extern")]
    return body, ext
def names_map():
    m = {}
    for l in [x for f in ("names_add.tsv", "names_add2.tsv", "names_add3.tsv", "names_add4.tsv") if (LANE_ / f).exists() for x in open(LANE_ / f)]:
        c = l.rstrip("\n").split("\t")
        if len(c) >= 3: m[c[2]] = c[1]
    return m
def inline_and_respell(text):
    def inc(m):
        p = INC / m.group(1)
        return p.read_text() if p.is_file() else m.group(0)
    t = re.sub(r'^#include "(shared/[^"]+)"[^\n]*$', inc, text, flags=re.M)
    for new, old in names_map().items(): t = re.sub(r"\b%s\b" % new, old, t)
    return t
def check(row, cand_text, score=True):
    pinned = clean_path(row).read_text(errors="replace")
    if row.get("kind") == "slus":
        a0 = listing(row, pinned); a1 = listing(row, inline_and_respell(cand_text)); err = None if a1 else "build"
    else:
        a0 = listing(row, pinned); a1, err = listing2(row, cand_text)
    rec = {"id": row["id"], "cfg": row["cfg"]}
    if a1 is None: rec.update(listing="build-error", err=err); return rec
    b0, e0 = split_ext(ccproc(a0, REPO / "config/names.tsv"))
    b1, e1 = split_ext(ccproc(a1, LANE_ / "names_lane.tsv"))
    rec["listing"] = "identical" if b0 == b1 else "differs"
    rec["extern_sizes"] = "same" if e0 == e1 else "differ: %s -> %s" % (sorted(set(e0) - set(e1)), sorted(set(e1) - set(e0)))
    if rec["listing"] == "differs":
        import difflib
        rec["diff"] = [l for l in difflib.unified_diff(b0, b1, lineterm="", n=0) if not l.startswith(("---", "+++", "@@"))][:12]
    if score and row.get("kind") == "slus":
        # SLUS rows are compared by object identity: a relocation that names another symbol for the SAME address
        # (D_80083160+24 for D_80083178) differs there but links identically.  Record whether the listings agree
        # once every symbol+offset is an absolute address; apply4.sh re-derives such a row's reference after the
        # SLUS image gate (verify.py --rebaseline-slus).
        def absn(lines):
            f = lambda m: "0x%08X" % (int(m.group(2), 16) + int(m.group(3) or 0))
            return [re.sub(r"\b(D|func)_([0-9A-F]{8})([+-]\d+)?", f, l) for l in lines]
        rec["abs_listing"] = "identical" if absn(b0) == absn(b1) else "differs"
    if score:
        import kitlib
        v = kitlib.score_at(row, inline_and_respell(cand_text))
        rec["score"] = {k: v.get(k) for k in ("exact", "total", "status")}
    return rec
