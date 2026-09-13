"""Temporary-only compiler observations and conservative GCC 2.x trace attribution.

No score is computed here. Assembly distance ranks experiments; the caller's vf
is the only acceptance authority. Pattern alignment never equates UIDs across
different compilations, and ambiguous repeated patterns are not called ties.
"""
import collections
import difflib
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))
from common import parse_cfg
from xform.screen import _addr


_WS = re.compile(r"\s+")
_LABEL = re.compile(r"\$L\d+")
_LREF = re.compile(r"\(label_ref(?::\w+)? \d+\)")
_REG = re.compile(r"\(reg(?:/\w+)?:([A-Z0-9]+) (\d+)(?: [^)]+)?\)")
_PAREN = re.compile(r'[()"\\]')


def normalize(src):
    out, labels, inside = [], {}, False
    for line in src.splitlines():
        s = line.split("#")[0].strip()
        if s.startswith(".ent"):
            inside = True
            out.append(".ent")
            continue
        if s.startswith(".end"):
            inside = False
        if not inside or not s or s.startswith((".ent", ".loc", ".file", ".frame", ".mask", ".fmask", ".set")):
            continue
        s = _WS.sub(" ", s)
        s = _LABEL.sub(lambda m: labels.setdefault(m[0], "L%d" % len(labels)), s)
        out.append(_addr(s))
    return out


def distance(a, b):
    if a is None or b is None:
        return 1000000
    return sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in
               difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes() if tag != "equal")


def compile_text(row, text, dumps=False, debug=False):
    cell, flags = parse_cfg(row["cfg"])
    cc = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="t51_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        cmd = [str(cc / "gcc"), "-B" + str(cc) + "/", "-S", "-O2", *flags,
               "-I" + str(ROOT / "include"), "-w"]
        if dumps:
            cmd.append("-da")
        if debug:
            cmd.append("-g")
        cmd += [f.name, "-o", "f.s"]
        try:                               # runs inside its temporary directory: -da dumps land there
            r = subprocess.run(cmd, cwd=d, capture_output=True,
                               text=True, timeout=float(os.getenv("T51_TIMEOUT", "35")))
        except subprocess.TimeoutExpired:
            return {"assembly": None, "error": "compiler-timeout", "dumps": {}}
        if r.returncode or not (d / "f.s").exists():
            return {"assembly": None, "error": (r.stderr or r.stdout)[-800:], "dumps": {}}
        raw = (d / "f.s").read_text(errors="replace")
        ds = {}
        if dumps:
            for p in d.iterdir():
                if p.suffix[1:] in ("rtl", "cse", "combine", "flow", "sched", "lreg", "greg", "sched2", "dbr"):
                    ds[p.suffix[1:]] = p.read_text(errors="replace")
        return {"assembly": normalize(raw), "raw_assembly": raw, "error": None, "dumps": ds}


def close_paren(s, i):
    # Jumps between ( ) " and backslash (the only characters that change state); same result as a
    # character-by-character walk: inside a string a backslash escapes the next character.
    depth, quoted, skip = 0, False, -1
    for m in _PAREN.finditer(s, i):
        k = m.start()
        if k == skip:
            continue
        c = s[k]
        if quoted:
            if c == "\\":
                skip = k + 1
            elif c == '"':
                quoted = False
        elif c == '"':
            quoted = True
        elif c == "(":
            depth += 1
        elif c == ")":
            depth -= 1
            if depth == 0:
                return k + 1
    return None


def instructions(src, abstract=False):
    """Ordered pattern records, ignoring linkage UIDs/notes but retaining operands.

    Abstract signatures rename registers by first appearance over the whole
    stream. This is a useful negative control, not graph-isomorphism proof.
    """
    out, regs = [], {}
    for m in re.finditer(r"^\((insn|jump_insn|call_insn)(?:/\w+)?\s+(\d+)\s+[-\d]+\s+[-\d]+\s+", src, re.M):
        a = m.end()
        if src[a:a + 1] != "(":
            continue
        b = close_paren(src, a)
        end = close_paren(src, m.start())
        if b is None or end is None:
            continue
        pat = _WS.sub(" ", src[a:b])
        pat = _LREF.sub("(label_ref LABEL)", pat)
        if abstract:
            def reg(mm):
                key = mm[2]
                return "(reg:" + mm[1] + " " + regs.setdefault(key, "R%d" % len(regs)) + ")"
            pat = _REG.sub(reg, pat)
        out.append({"uid": int(m[2]), "kind": m[1], "pattern": pat,
                    "links": [(int(k), t or "true") for t, k in
                              re.findall(r"\(insn_list(?::(\w+))?\s+(\d+)", src[b:end])],
                    "dump_line": src.count("\n", 0, m.start()) + 1})
    return out


def decisions(src):
    """Dynamic ready ranks; the final 'now' list follows sorting and hazard selection."""
    result, block, func = [], None, None
    for line in src.splitlines():
        m = re.match(r";; Function (\S+)", line)
        if m:
            func = m[1]
        m = re.search(r"basic block number (\d+)", line)
        if m:
            block = int(m[1])
        m = re.search(r"ready list at T-(\d+): (.*?)(?:, now(.*))?$", line)
        if m:
            ranks = {int(u): int(v, 16) for u, v in re.findall(r"(\d+) \(([0-9a-f]+)\)", m[2])}
            order = [int(u) for u in (m[3] or "").split() if u.isdigit()]
            result.append({"function": func, "block": block, "tick": int(m[1]),
                           "ranks": ranks, "ready_order": order})
    return result


def pair_reason(trace, a, b):
    for d in decisions(trace):
        if a in d["ranks"] and b in d["ranks"]:
            ra, rb = d["ranks"][a], d["ranks"][b]
            return {"cause": "dynamic-priority" if ra != rb else "equal-rank-candidate",
                    "a_rank": hex(ra), "b_rank": hex(rb), "block": d["block"],
                    "tick": d["tick"], "ready_order": d["ready_order"]}
    return {"cause": "not-co-ready-observed"}


def diagnose(before, after):
    """Identify surviving unique insn pairs, never claim absence is impossibility."""
    report = {"asm_distance": distance(before["assembly"], after["assembly"]), "phases": {}}
    for phase in ("combine", "sched", "greg", "sched2", "dbr"):
        a, b = before["dumps"].get(phase), after["dumps"].get(phase)
        if a is None or b is None:
            report["phases"][phase] = {"available": False}
            continue
        aa, bb = instructions(a), instructions(b)
        ap, bp = [x["pattern"] for x in aa], [x["pattern"] for x in bb]
        ca, cb = collections.Counter(ap), collections.Counter(bp)
        rec = {"available": True, "patterns_before": len(ap), "patterns_after": len(bp),
               "ordered_equal": ap == bp, "multiset_equal": ca == cb,
               "abstract_order_equal": [x["pattern"] for x in instructions(a, True)] ==
                                       [x["pattern"] for x in instructions(b, True)]}
        ua = {x["pattern"]: (i, x) for i, x in enumerate(aa) if ca[x["pattern"]] == 1 and cb[x["pattern"]] == 1}
        ub = {x["pattern"]: (i, x) for i, x in enumerate(bb) if x["pattern"] in ua}
        pairs = []
        keys = sorted(ua, key=lambda x: ua[x][0])
        # Adjacent surviving unique records suffice to exhibit order inversions.
        for x, y in zip(keys, keys[1:]):
            if ub[x][0] > ub[y][0]:
                xa, ya, xb, yb = ua[x][1], ua[y][1], ub[x][1], ub[y][1]
                pairs.append({"a": x, "b": y, "before_uids": [xa["uid"], ya["uid"]],
                              "after_uids": [xb["uid"], yb["uid"]],
                              "before_lines": [xa["dump_line"], ya["dump_line"]],
                              "after_lines": [xb["dump_line"], yb["dump_line"]],
                              "before_decision": pair_reason(a, xa["uid"], ya["uid"]),
                              "after_decision": pair_reason(b, xb["uid"], yb["uid"])})
                if len(pairs) == 6:
                    break
        rec["inversions"] = pairs
        report["phases"][phase] = rec
    return report
