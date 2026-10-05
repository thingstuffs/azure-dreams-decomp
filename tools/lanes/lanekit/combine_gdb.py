#!/usr/bin/env python3
"""combine_gdb.py - why combine.c merged, or refused to merge, a LOG_LINK chain: every try_combine attempt of one
function, read out of the cell's own cc1 under gdb.  combine.py is the front end (`combine.py <row> <text> --insn UID`);
this file is both halves of the trace:

  * imported by python (combine.py, the tests): the HOST side - `nm` symbols, the objdump site tables, the source
    site tables (the cell's own toolchain/gcc-src/<cell>/combine.c), the compile and the gdb run (`trace()`);
  * sourced by gdb (`gdb -batch -x combine_gdb.py --args cc1 ...`, built by `run_gdb`; never run it by hand): the
    TRACER, which writes one JSON line per try_combine attempt to $COMBINE_OUT.

How a refusal is located.  The cc1 binaries are static i386 executables built at -O0 with their symbol table and no
DWARF, by one modern gcc: every `return 0;` in try_combine / can_combine_p / combinable_i3pat is its own
`mov $0x0,%eax; jmp <epilogue>` and the sites come out in source order.  `return_sites()` finds them in the
disassembly, `source_returns()` enumerates the `return 0;` statements of the cell's combine.c (comments stripped,
`#ifdef HAVE_cc0` / `AUTO_INC_DEC` / `#if 0` blocks dropped - MIPS has neither), and the two lists are paired by
order ONLY when their counts agree (otherwise the site prints as `unmapped` with its address).  Each site carries its
source line and the `if` condition that guards it; REASONS maps those conditions to short reasons.

can_combine_p's long `||` chain (one return site for ~10 tests) is decided clause by clause at the site, from memory
only: the clause tests that are plain rtx tests are evaluated from the locals `src` / `dest` / `all_adjacent` (their
%ebp slots are read from the disassembly after the expand_field_assignment call), and the tests that are calls
(use_crosses_set_p, reg_used_between_p, find_reg_note, find_reg_fusage, rtx_equal_p) are read from the RESULTS of the
calls this can_combine_p invocation made (a breakpoint on each call instruction's return address).  The chain
short-circuits, so the first true clause in source order is the rejecting one.  For use_crosses_set_p the tracer also
names WHAT crossed: the register set again after i2/i1 (reg_last_set) or the store/call at mem_last_set.

No breakpoint is placed on a routine that other passes call (find_reg_note, rtx_equal_p ...): only on addresses inside
combine_instructions / try_combine / can_combine_p / combinable_i3pat.  The tracer never calls into the inferior and
never writes to it, so the traced compile's assembly is the plain compile's (`faithful`, checked every run).
"""
from __future__ import annotations

import json
import os
import re
import subprocess
import sys
from collections import Counter
from pathlib import Path

try:
    import gdb                                                            # noqa: F401  (only inside gdb)
    IN_GDB = True
except ImportError:
    IN_GDB = False

_HERE = Path(__file__).resolve().parent
ROOT = next(p for p in _HERE.parents if (p / "tools/common.py").is_file())

ROUTINES = ("combine_instructions", "try_combine", "can_combine_p", "combinable_i3pat")
DATA = ("rtx_name", "rtx_format", "rtx_length", "mode_name", "mode_size", "reg_note_name", "current_function_name",
        "stack_pointer_rtx", "last_call_cuid", "mem_last_set", "reg_last_set", "uid_cuid", "max_uid_cuid",
        "reg_rtx_no", "global_regs")
COMBINE_STATICS = ("last_call_cuid", "mem_last_set", "reg_last_set", "uid_cuid", "max_uid_cuid")

# Cells whose site tables were checked by hand against the source and the r93 fixtures (dungeon/func_800C9858).
VALIDATED = {"2.7.2-cdk"}

# condition regex (on the compacted `if` condition that guards a `return 0;`) -> (key, short reason).  First match wins.
REASONS = {
    "try_combine": [
        (r"GET_RTX_CLASS \(GET_CODE \(i3\)\) != 'i'", "not-insn",
         "i3/i2/i1 is not an insn (deleted) or i3 has a REG_LIBCALL note"),
        (r"can_combine_p", "can_combine_p", "can_combine_p refused i2 or i1 (detail below)"),
        (r"combinable_i3pat \(i3", "i3pat", "combinable_i3pat refused i3's pattern as a destination"),
        (r"combinable_i3pat \(NULL_RTX", "i3pat-i1", "combinable_i3pat refused the merged pattern for i1dest"),
        (r"max_reg_num \(\) != maxreg", "subst-fail",
         "subst failed: (clobber (const_int 0)) result, a new pseudo needed, an auto-inc duplicated, or a new MULT"),
        (r"REG_NOTE_KIND \(link\) == REG_INC", "autoinc", "i3 auto-increments a register i2/i1 uses"),
        (r"insn_code_number < 0", "no-recog",
         "NO RECOG: the merged pattern matches no insn in mips.md (and no split of it did)"),
        (r"other_code_number < 0", "other-no-recog", "the other insn changed with it (a cc user) is not recognized"),
    ],
    "can_combine_p": [
        (r"^if \(set\)$", "two-sets", "the insn has two live SETs (a PARALLEL)"),
        (r"^default", "parallel-other", "the insn is a PARALLEL holding something other than SET/CLOBBER"),
        (r"set == 0 \|\| GET_CODE \(SET_SRC \(set\)\) == ASM_OPERANDS", "no-set",
         "no single live SET in the PARALLEL, or an asm"),
        (r"^else", "not-set", "the insn's pattern is neither a SET nor a PARALLEL"),
        (r"^if \(set == 0\)$", "no-set", "no SET"),
        (r"use_crosses_set_p", "chain", "can_combine_p's test chain (clause below)"),
        (r"HARD_REGNO_MODE_OK \(REGNO \(dest\)", "hard-reg",
         "a hard-register copy (combine will not extend a hard register's life)"),
        (r"GET_CODE \(dest\) != CC0", "dest-not-reg", "the insn's destination is not a REG (a store)"),
        (r"CLOBBER", "i3-clobber", "i3 clobbers the value / a register of its source"),
        (r"volatile_refs_p \(PATTERN", "volatile-src",
         "the source has a volatile reference (volatile MEM / asm) and another volatile reference lies between it "
         "and i3 (volatile_refs_p counts a volatile MEM, unlike the volatile_insn_p site)"),
        (r"volatile_insn_p", "volatile-between", "a volatile insn (volatile asm / unspec_volatile) lies between it and i3"),
        (r"REG_NOTE_KIND \(link\) == REG_INC", "autoinc", "an auto-increment register is used between it and i3"),
        (r"sets_cc0_p", "cc0", "it follows a cc0 setter"),
    ],
    "combinable_i3pat": [
        (r"inner_dest != dest", "i3-partial-dest",
         "i3 modifies its output only partly (subreg/strict_low_part/zero_extract over i2dest/i1dest), its destination "
         "is a hard register it cannot hold, or i1dest is in the source"),
        (r"\*pi3dest_killed", "i3-kills-two", "i3 both sets and uses two registers"),
        (r"combinable_i3pat", "i3-parallel", "an element of i3's PARALLEL was refused"),
    ],
}

# The clauses of can_combine_p's chain, in source order (2.7.2-cdk combine.c 892-944).
CHAIN = [
    ("stack-pointer", "the destination is the stack pointer"),
    ("field-dest", "the destination is a ZERO_EXTRACT / STRICT_LOW_PART (a field assignment)"),
    ("self-copy", "the insn copies a register to itself and has a REG_EQUAL note"),
    ("call-src", "the source is a CALL"),
    ("call-arg", "i3 is a call and the destination is one of its argument registers (CALL_INSN_FUNCTION_USAGE)"),
    ("libcall-end", "the insn ends a libcall (REG_RETVAL)"),
    ("used-between", "the destination is used between succ (i2) and i3 (reg_used_between_p)"),
    ("use_crosses_set_p", "use_crosses_set_p: a register or the memory the source reads is set again between the "
                          "insn and i3"),
    ("volatile-asm", "the source is a volatile asm / unspec_volatile and the insns are not adjacent"),
    ("no-conflict", "a REG_NO_CONFLICT note for the destination in i3 or succ"),
    ("crosses-call", "a CALL lies between the insn and i3 (INSN_CUID < last_call_cuid) and the source is not "
                     "constant"),
]


# =========================================================================================== host side

def nm_table(cc1):
    out = subprocess.run(["nm", "-S", "-n", str(cc1)], capture_output=True, text=True, check=True).stdout
    rows = []
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4:
            rows.append((int(p[0], 16), int(p[1], 16), p[2], p[3]))
        elif len(p) == 3:
            rows.append((int(p[0], 16), 0, p[1], p[2]))
    return rows


def symbols(cc1):
    """{'addr': {name: address}, 'size': {...}, 'range': {routine: [start, end]}} for one cc1.  Statics that exist twice
    (uid_cuid is also sched.c's) are taken nearest to a combine.c anchor; reg_names-style globals beat statics."""
    rows = nm_table(cc1)
    text = sorted({a for a, s, t, n in rows if t in "tT"})
    by = {}
    for a, s, t, n in rows:
        by.setdefault(n, []).append((a, s, t))
    addr, size, rng = {}, {}, {}
    for r in ROUTINES:
        c = [x for x in by.get(r, []) if x[2] in "tT"]
        if not c:
            raise SystemExit("combine_gdb: %s has no symbol %s - cannot trace this cc1" % (cc1, r))
        start = c[0][0]
        nxt = next((a for a in text if a > start), start + 0x10000)
        addr[r] = start
        rng[r] = [start, nxt]
    anchor = None
    for n in ("max_uid_cuid", "mem_last_set", "last_call_cuid"):
        if len(by.get(n, [])) == 1:
            anchor = by[n][0][0]
            break
    for n in DATA:
        c = [x for x in by.get(n, []) if x[2] in "bBdD"]
        if not c:
            continue
        if n in COMBINE_STATICS and len(c) > 1 and anchor is not None:
            pick = min(c, key=lambda x: abs(x[0] - anchor))
        else:
            glob = [x for x in c if x[2] in "BD"]
            pick = (glob or c)[0]
        addr[n], size[n] = pick[0], pick[1]
    for n in ("reg_names",):
        c = [x for x in by.get(n, []) if x[2] in "bBdD"]
        if c:
            glob = [x for x in c if x[2] in "BD"]
            addr[n], size[n] = (glob or c)[0][0], (glob or c)[0][1]
    return {"addr": addr, "size": size, "range": rng}


INSN_RE = re.compile(r"^\s*([0-9a-f]+):\s+(\S+)\s*(.*?)\s*$")


def disasm(cc1, start, end):
    """[(address, mnemonic, operands)] of [start, end) (objdump, AT&T syntax)."""
    out = subprocess.run(["objdump", "-d", "--no-show-raw-insn", "--start-address=0x%x" % start,
                          "--stop-address=0x%x" % end, str(cc1)], capture_output=True, text=True, check=True).stdout
    res = []
    for line in out.splitlines():
        m = INSN_RE.match(line)
        if m and not line.rstrip().endswith(">:"):
            res.append((int(m.group(1), 16), m.group(2), m.group(3)))
    return res


def _target(ops):
    m = re.match(r"([0-9a-f]+)(?:\s+<([^>]+)>)?", ops)
    return (int(m.group(1), 16), m.group(2)) if m else (None, None)


def return_sites(insns):
    """{'ret0': [addr of each `mov $0x0,%eax` that returns], 'ret': [addr of `ret`], 'calls': [[call addr, return
    addr, callee]], 'epilogue': addr} for one routine's disassembly."""
    jt = Counter()
    for i in range(1, len(insns)):
        a, mn, ops = insns[i]
        if mn == "jmp" and insns[i - 1][1] == "mov" and insns[i - 1][2].endswith(",%eax"):
            jt[_target(ops)[0]] += 1
    epi = jt.most_common(1)[0][0] if jt else None
    ret0, ret, calls = [], [], []
    for i, (a, mn, ops) in enumerate(insns):
        if mn == "ret":
            ret.append(a)
        if mn == "call" and i + 1 < len(insns):
            t, name = _target(ops)
            calls.append([a, insns[i + 1][0], (name or "").split("+")[0]])
        if mn == "mov" and ops == "$0x0,%eax" and i + 1 < len(insns):
            na, nmn, nops = insns[i + 1]
            if (nmn == "jmp" and _target(nops)[0] == epi) or na == epi:
                ret0.append(a)
    return {"ret0": ret0, "ret": ret, "calls": calls, "epilogue": epi}


def ccp_locals(insns):
    """%ebp offsets of can_combine_p's src / dest / set (stored right after expand_field_assignment) and all_adjacent
    (the first `movzbl %al,%eax; mov %eax,OFF(%ebp)`)."""
    off = {}
    for i, (a, mn, ops) in enumerate(insns):
        if mn == "call" and "expand_field_assignment" in ops:
            seq = insns[i + 1:i + 12]
            for j in range(len(seq) - 1):
                if seq[j][1] == "mov" and seq[j][2] in ("0x8(%eax),%eax", "0x4(%eax),%eax"):
                    m = re.match(r"%eax,(-?0x[0-9a-f]+)\(%ebp\)$", seq[j + 1][2])
                    if m and seq[j + 1][1] == "mov":
                        off["src" if seq[j][2].startswith("0x8") else "dest"] = int(m.group(1), 16)
            m = re.match(r"%eax,(-?0x[0-9a-f]+)\(%ebp\)$", seq[0][2]) if seq else None
            if m:
                off["set"] = int(m.group(1), 16)
            break
    for i in range(1, len(insns)):
        if insns[i - 1][1] == "movzbl" and insns[i - 1][2] == "%al,%eax" and insns[i][1] == "mov":
            m = re.match(r"%eax,(-?0x[0-9a-f]+)\(%ebp\)$", insns[i][2])
            if m:
                off["all_adjacent"] = int(m.group(1), 16)
                break
    return off


# ------------------------------------------------------------------------------------------ the source

UNDEFINED = {"HAVE_cc0", "AUTO_INC_DEC"}             # MIPS defines neither


def _preprocess(src):
    """combine.c with the lines of inactive conditional blocks blanked (line numbers kept) and comments blanked."""
    src = re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), src, flags=re.S)
    out, stack = [], []
    for line in src.split("\n"):
        s = line.strip()
        m = re.match(r"#\s*(ifdef|ifndef|if|else|elif|endif)\b\s*(.*)", s)
        if m:
            kind, arg = m.group(1), m.group(2).strip()
            if kind == "ifdef":
                stack.append([arg not in UNDEFINED, False])
            elif kind == "ifndef":
                stack.append([arg in UNDEFINED, False])
            elif kind == "if":
                v = not re.match(r"0\b", arg) and not re.match(r"defined\s*\(?\s*(%s)\b" % "|".join(UNDEFINED), arg)
                stack.append([bool(v), False])
            elif kind in ("else", "elif") and stack:
                stack[-1][0] = not stack[-1][0] and not stack[-1][1]
                stack[-1][1] = True
            elif kind == "endif" and stack:
                stack.pop()
            out.append("")
            continue
        out.append(line if all(x[0] for x in stack) else "")
    return "\n".join(out)


def _balanced_back(t, close):
    depth = 0
    for i in range(close, -1, -1):
        if t[i] == ")":
            depth += 1
        elif t[i] == "(":
            depth -= 1
            if depth == 0:
                return i
    return None


def source_returns(cell, routine):
    """[(line, condition)] of every `return 0;` of `routine` in the cell's combine.c, in source order."""
    p = ROOT / "toolchain/gcc-src" / cell / "combine.c"
    if not p.is_file():
        return None
    t = _preprocess(p.read_text(errors="replace"))
    m = re.search(r"^%s \(" % routine, t, re.M)
    if not m:
        return None
    b = t.index("\n{", m.end())
    depth, i = 0, b + 1
    while i < len(t):
        if t[i] == "{":
            depth += 1
        elif t[i] == "}":
            depth -= 1
            if depth == 0:
                break
        i += 1
    body_start, body_end = b + 1, i
    res = []
    for r in re.finditer(r"\breturn\s+0\s*;", t[body_start:body_end]):
        pos = body_start + r.start()
        line = t.count("\n", 0, pos) + 1
        j = pos
        while True:                                       # skip back over `{`, blanks and `undo_all ();`
            k = j - 1
            while k >= 0 and t[k] in " \t\n{":
                k -= 1
            if t[max(0, k - 11):k + 1] == "undo_all ();":
                j = k - 11
                continue
            break
        cond = "?"
        if t[k] == ")":
            o = _balanced_back(t, k)
            kw = re.search(r"(\w+)\s*$", t[:o])
            cond = "%s %s" % (kw.group(1) if kw else "", t[o:k + 1])
        elif t[k] == ":":
            kw = re.search(r"(\w+)\s*:$", t[:k + 1])
            cond = kw.group(1) if kw else ":"
        elif t[k - 3:k + 1] == "else":
            cond = "else"
        res.append((line, re.sub(r"\s+", " ", cond).strip()))
    return res


def label_for(routine, cond):
    for rx, key, text in REASONS.get(routine, []):
        if re.search(rx, cond):
            return key, text
    return "other", cond[:100]


def site_table(cc1, cell, syms=None):
    """Per routine: the return-0 sites paired with the source (when the counts agree), calls, ret addresses."""
    syms = syms or symbols(cc1)
    out = {"mapped": {}, "routines": {}}
    for r in ROUTINES:
        lo, hi = syms["range"][r]
        ins = disasm(cc1, lo, hi)
        st = return_sites(ins)
        src = source_returns(cell, r) if r != "combine_instructions" else []
        mapped = src is not None and len(src) == len(st["ret0"])
        sites = []
        for k, a in enumerate(st["ret0"]):
            if mapped:
                line, cond = src[k]
                key, text = label_for(r, cond)
                sites.append({"addr": a, "k": k, "line": line, "cond": cond, "key": key, "text": text})
            else:
                sites.append({"addr": a, "k": k, "line": None, "cond": None, "key": "unmapped",
                              "text": "return-0 site %d at 0x%x (unmapped: %s source returns vs %d sites)" % (
                                  k, a, "no" if src is None else len(src), len(st["ret0"]))})
        st["sites"] = sites
        if r == "can_combine_p":
            st["locals"] = ccp_locals(ins)
        out["routines"][r] = st
        out["mapped"][r] = mapped
    return out


# ------------------------------------------------------------------------------------------ the run

def run_gdb(cc1, cell, workdir, flags, func, timeout=600):
    """cc1 under gdb in `workdir` (holding f.i): (attempt records, traced f.s text, error)."""
    sys.path.insert(0, str(ROOT / "tools"))
    from common import NICE                                              # noqa: E402
    syms = symbols(cc1)
    cfg = {"addr": syms["addr"], "size": syms["size"], "sites": site_table(cc1, cell, syms), "func": func or ""}
    (workdir / "combine_cfg.json").write_text(json.dumps(cfg))
    out = workdir / "combine_trace.jsonl"
    cmd = NICE + ["gdb", "-batch", "-nx", "-iex", "set debuginfod enabled off", "-iex", "set pagination off",
                  "-iex", "set confirm off", "-iex", "set startup-with-shell off", "-iex", "set width 0",
                  "-x", str(Path(__file__).resolve()), "--args", str(cc1), "f.i", "-quiet", "-O2", *flags, "-w",
                  "-o", "f.s"]
    env = dict(os.environ, COMBINE_CFG=str(workdir / "combine_cfg.json"), COMBINE_OUT=str(out), TMPDIR=str(workdir))
    try:
        r = subprocess.run(cmd, cwd=workdir, capture_output=True, text=True, env=env, timeout=timeout,
                           stdin=subprocess.DEVNULL)
    except subprocess.TimeoutExpired:
        return None, None, "gdb trace timed out after %d s (raise --timeout)" % timeout
    recs = []
    if out.is_file():
        for line in out.read_text(errors="replace").splitlines():
            try:
                recs.append(json.loads(line))
            except ValueError:
                pass
    fatal = [x["msg"] for x in recs if x.get("t") == "fatal"]
    if fatal:
        return recs, None, "gdb script failed: %s" % fatal[0]
    if not any(x.get("t") == "end" for x in recs):
        return recs, None, "gdb trace incomplete (exit %s): %s" % (r.returncode, (r.stderr or r.stdout)[-800:])
    s = workdir / "f.s"
    return recs, s.read_text(errors="replace") if s.is_file() else None, None


def trace(row, text, func=None, timeout=600):
    """Compile `text` as `row` (module rows: the unit that holds the function) and trace combine in the function.

    Returns {'func', 'cell', 'flags', 'records', 'faithful', 'flow', 'combine', 'error', 'gdb_error'}."""
    import shutil
    import tempfile
    sys.path.insert(0, str(_HERE))
    import kitlib
    kitlib.add_paths()
    from common import parse_cfg, NICE                                   # noqa: E402
    to = float(os.environ.get("PIN_CC_TIMEOUT", "60"))
    funcs = [func] if func else [f for f in (row.get("true_name"), row.get("func")) if f]
    with tempfile.TemporaryDirectory(prefix="combine_") as td:
        d = Path(td)
        cand = d / "f.c"
        cand.write_text(text)
        sources = [(cand, row["cfg"])]
        if kitlib.module_fingerprint(row) is not None:
            from variant_screen import screen_sources                    # noqa: E402
            sources = screen_sources(row, cand, d)
        env = dict(os.environ, TMPDIR=str(d), PYTHONDONTWRITEBYTECODE="1")
        hold, defined = None, []
        for i, (source, cfg) in enumerate(sources):
            cell, flags = parse_cfg(cfg)
            D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
            w = d / ("unit%d" % i)
            w.mkdir()
            try:
                r = subprocess.run(NICE + [str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags,
                                           "-I" + str(ROOT / "include"), "-w", source.name, "-o", str(w / "f.i")],
                                   cwd=source.parent, capture_output=True, text=True, env=env, timeout=to)
                if r.returncode:
                    return {"error": (r.stderr or r.stdout)[-800:]}
                r = subprocess.run(NICE + [str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-da", "-o", "f.s"],
                                   cwd=w, capture_output=True, text=True, env=env, timeout=to)
                if r.returncode:
                    return {"error": (r.stderr or r.stdout)[-800:]}
            except subprocess.TimeoutExpired:
                return {"error": "compiler-timeout"}
            asm = (w / "f.s").read_text(errors="replace")
            hit = [f for f in funcs if re.search(r"^%s:" % re.escape(f), asm, re.M)]
            ents = re.findall(r"^\s*\.ent\s+(\S+)", asm, re.M)
            if not hit and not func and len(ents) == 1 and len(sources) == 1:
                hit = ents                                # the file defines one function under another name
            defined += ents
            if hit and hold is None:
                hold = (w, D, cell, flags, asm, hit[0])
        if hold is None:
            return {"error": "no compiled unit defines %s (defined: %s) - pass --func NAME" % (
                "/".join(funcs), ", ".join(defined[:12]) or "?")}
        w, D, cell, flags, asm, fn = hold
        out = {"func": fn, "cell": cell, "flags": flags, "error": None, "gdb_error": None, "records": None,
               "faithful": None}
        for suf in ("flow", "combine"):
            p = next(iter(w.glob("*.%s" % suf)), None)
            out[suf] = p.read_text(errors="replace") if p else ""
        if not shutil.which("gdb"):
            out["gdb_error"] = "gdb is not installed"
            return out
        g = w / "gdb"
        g.mkdir()
        shutil.copy(w / "f.i", g / "f.i")
        recs, gasm, err = run_gdb(D / "cc1", cell, g, flags, fn, timeout)
        out["records"], out["gdb_error"] = recs, err
        if gasm is not None:
            out["faithful"] = gasm == asm
        return out


# =========================================================================================== gdb side

def _gdb_main():                                                          # noqa: C901 - one tracer, kept together
    C = json.load(open(os.environ["COMBINE_CFG"]))
    OUT = open(os.environ["COMBINE_OUT"], "w")
    A = C["addr"]
    SZ = C["size"]
    S = C["sites"]["routines"]
    FUNC = C["func"] or None
    INF = gdb.selected_inferior()

    def emit(rec):
        OUT.write(json.dumps(rec, separators=(",", ":")) + "\n")

    def mem(a, n):
        return bytes(INF.read_memory(a, n))

    def u32(a):
        return int.from_bytes(mem(a, 4), "little")

    def s32(a):
        v = u32(a)
        return v - (1 << 32) if v & 0x80000000 else v

    def reg(name):
        return int(gdb.parse_and_eval("$" + name)) & 0xffffffff

    def arg_at_call(i):                   # at a `call` instruction: the arguments are already pushed
        return u32(reg("esp") + 4 * i)

    def arg_at_entry(i):                  # at a routine's first instruction: 0(%esp) is the return address
        return u32(reg("esp") + 4 * (i + 1))

    def cstr(a, n=64):
        if not a:
            return ""
        return mem(a, n).split(b"\0", 1)[0].decode("latin-1")

    def strtab(name, n):
        return [cstr(u32(A[name] + 4 * i)) for i in range(n)]

    N_RTX = SZ["rtx_name"] // 4
    RTX = strtab("rtx_name", N_RTX)
    FMT = strtab("rtx_format", N_RTX)
    CODE = {n: i for i, n in enumerate(RTX)}
    MODES = strtab("mode_name", SZ["mode_name"] // 4) if SZ.get("mode_name") else []
    MSIZE = list(mem(A["mode_size"], SZ["mode_size"])) if SZ.get("mode_size") else []
    if SZ.get("mode_size") and SZ["mode_size"] >= 4 * len(MODES) and len(MODES):
        MSIZE = [u32(A["mode_size"] + 4 * i) for i in range(len(MODES))]
    NOTES = strtab("reg_note_name", SZ["reg_note_name"] // 4)
    NOTE = {n: i for i, n in enumerate(NOTES)}

    def code(x):
        return int.from_bytes(mem(x, 2), "little")

    def cname(x):
        if not x:
            return None
        c = code(x)
        return RTX[c] if c < len(RTX) else "code%d" % c

    def mode(x):
        m = mem(x + 2, 1)[0]
        return MODES[m] if m < len(MODES) else "m%d" % m

    def field(x, i):
        return u32(x + 4 + 4 * i)

    def uid(x):
        return s32(x + 4) if x else None

    def pattern(x):
        return field(x, 3)

    def nxt(x):
        return field(x, 2)

    def rtx_str(x, budget=None):
        budget = budget if budget is not None else [160]
        if not x:
            return "nil"
        budget[0] -= 1
        if budget[0] < 0:
            return "..."
        k = cname(x)
        if k in ("insn", "jump_insn", "call_insn", "code_label", "note", "barrier"):
            return "(%s %d)" % (k, uid(x))
        fl = mem(x + 3, 1)[0]
        s = "(" + k
        for bit, ch in ((4, "s"), (3, "v"), (2, "u"), (6, "i")):
            if fl >> bit & 1:
                s += "/" + ch
        m = mode(x)
        if m != "VOID":
            s += ":" + m
        fmt = FMT[code(x)]
        if k == "const_int":
            return s + " %d)" % s32(x + 4)
        for i, f in enumerate(fmt):
            v = field(x, i)
            if f == "e":
                s += " " + rtx_str(v, budget)
            elif f == "E":
                if not v:
                    s += " []"
                    continue
                n = s32(v)
                s += " [" + " ".join(rtx_str(u32(v + 4 + 4 * j), budget) for j in range(max(0, min(n, 12)))) + "]"
            elif f in ("i", "n", "w"):
                s += " %d" % s32(x + 4 + 4 * i)
            elif f == "s":
                s += ' "%s"' % cstr(v, 40)
            elif f == "u":
                s += " %s" % (uid(v) if v else "0")
        return s + ")"

    def walk(x, seen=None, depth=0):
        """Every sub-rtx of an expression (not into insns)."""
        if not x or depth > 40:
            return
        yield x
        k = cname(x)
        if k in ("insn", "jump_insn", "call_insn", "code_label", "note", "barrier"):
            return
        for i, f in enumerate(FMT[code(x)]):
            v = field(x, i)
            if f == "e":
                yield from walk(v, seen, depth + 1)
            elif f == "E" and v:
                for j in range(max(0, min(s32(v), 64))):
                    yield from walk(u32(v + 4 + 4 * j), seen, depth + 1)

    def regno(x):
        return s32(x + 4)

    def notes_of(insn):
        """[(kind name, datum rtx pointer)] of an insn's REG_NOTES."""
        out, link, n = [], field(insn, 6), 0
        while link and n < 40:
            kind = mem(link + 2, 1)[0]
            out.append((NOTES[kind] if kind < len(NOTES) else str(kind), field(link, 0)))
            link = field(link, 1)
            n += 1
        return out

    # ---------------------------------------------------------------------------------- cuids
    def cuid_table():
        mx = s32(A["max_uid_cuid"])
        p = u32(A["uid_cuid"])
        if not p or mx <= 0:
            return mx, []
        b = mem(p, 4 * (mx + 1))
        return mx, [int.from_bytes(b[4 * i:4 * i + 4], "little", signed=True) for i in range(mx + 1)]

    def insn_cuid(insn, tab):
        mx, cu = tab
        n = 0
        while insn and uid(insn) > mx and cname(insn) == "insn" and cname(pattern(insn)) == "use" and n < 1000:
            insn = nxt(insn)
            n += 1
        if not insn:
            return None
        u = uid(insn)
        return cu[u] if 0 <= u < len(cu) else None

    def uid_at_cuid(c, tab):
        mx, cu = tab
        for u, v in enumerate(cu):
            if v == c:
                return u
        return None

    def find_insn(u, start):
        """The insn with uid u, searched forward then backward from `start` (bounded)."""
        for step in (2, 1):
            x, n = start, 0
            while x and n < 20000:
                if uid(x) == u:
                    return x
                x = field(x, step)
                n += 1
        return None

    def short_insn(x):
        if not x:
            return "?"
        k = cname(x)
        if k not in ("insn", "jump_insn", "call_insn"):
            return "(%s %d)" % (k, uid(x))
        return "%s %d %s" % (k, uid(x), rtx_str(pattern(x), [40]))

    # ---------------------------------------------------------------------------------- the chain
    def crossing(src, insn, tab):
        """What use_crosses_set_p (src, INSN_CUID (insn)) finds: [text]."""
        frm = insn_cuid(insn, tab)
        out = []
        rls = u32(A["reg_last_set"])
        mls = s32(A["mem_last_set"])
        seen = set()
        for y in walk(src):
            k = cname(y)
            if k == "reg":
                r = regno(y)
                end = r + 1
                if r < 76 and MSIZE:                      # hard register: HARD_REGNO_NREGS ~ words of the mode
                    m = mem(y + 2, 1)[0]
                    end = r + max(1, (MSIZE[m] + 3) // 4 if m < len(MSIZE) else 1)
                for q in range(r, end):
                    if q in seen:
                        continue
                    seen.add(q)
                    ls = u32(rls + 4 * q) if rls else 0
                    if ls:
                        c = insn_cuid(ls, tab)
                        if c is not None and c > frm:
                            out.append("register %d is set again by %s (cuid %d > the insn's %d)" % (
                                q, short_insn(ls), c, frm))
            elif k == "mem" and mls > frm and "mem" not in seen:
                seen.add("mem")
                u = uid_at_cuid(mls, tab)
                x = find_insn(u, insn) if u is not None else None
                what = "a CALL" if x and cname(x) == "call_insn" else "a store"
                out.append("the source reads memory and %s lies between: %s (mem_last_set cuid %d > the insn's %d)"
                           % (what, short_insn(x) if x else "uid %s" % u, mls, frm))
        return out

    def chain_clause(ev, ebp):
        """The first true clause of can_combine_p's chain, from the locals and this invocation's call results."""
        loc = S["can_combine_p"].get("locals", {})
        insn, i3, succ = ev["p_insn"], ev["p_i3"], ev["p_succ"]
        src = u32(ebp + loc["src"]) if "src" in loc else 0
        dest = u32(ebp + loc["dest"]) if "dest" in loc else 0
        adj = s32(ebp + loc["all_adjacent"]) if "all_adjacent" in loc else None
        calls = ev["calls"]

        def ret_of(f, pred=lambda c: True):
            v = [c for c in calls if c["f"] == f and pred(c)]
            return v[-1]["r"] if v else None

        def note_ret(kind, who=None):
            return ret_of("find_reg_note", lambda c: c["a"][1] == NOTE.get(kind, -1) and (who is None or c["a"][0] == who))

        tab = cuid_table()
        ev["src"] = rtx_str(src, [60]) if src else None
        ev["dest"] = rtx_str(dest, [20]) if dest else None
        ev["all_adjacent"] = adj
        sc, dc = cname(src), cname(dest)
        sp = u32(A["stack_pointer_rtx"]) if "stack_pointer_rtx" in A else None
        tests = []
        tests.append(("stack-pointer", sp is not None and dest == sp, None))
        tests.append(("field-dest", dc in ("zero_extract", "strict_low_part"), None))
        tests.append(("self-copy", bool(ret_of("rtx_equal_p")) and bool(note_ret("REG_EQUAL", insn)), None))
        tests.append(("call-src", sc == "call", None))
        gr = False
        if cname(i3) == "call_insn" and dc == "reg" and regno(dest) < 76 and "global_regs" in A:
            gr = bool(mem(A["global_regs"] + regno(dest), 1)[0])
        tests.append(("call-arg", cname(i3) == "call_insn" and (bool(ret_of("find_reg_fusage")) or gr), None))
        tests.append(("libcall-end", bool(note_ret("REG_RETVAL", insn)), None))
        tests.append(("used-between", bool(succ) and not adj and bool(ret_of("reg_used_between_p")), None))
        ucs = ret_of("use_crosses_set_p")
        tests.append(("use_crosses_set_p", not adj and bool(ucs), None))
        vol = sc == "unspec_volatile" or (sc == "asm_operands" and bool(mem(src + 3, 1)[0] >> 3 & 1))
        tests.append(("volatile-asm", not adj and vol, None))
        tests.append(("no-conflict", bool(note_ret("REG_NO_CONFLICT", i3)) or (bool(succ) and bool(note_ret("REG_NO_CONFLICT", succ))), None))
        lcc = s32(A["last_call_cuid"])
        ic = insn_cuid(insn, tab)
        const = sc in ("label_ref", "symbol_ref", "const_int", "const_double", "const", "high")
        tests.append(("crosses-call", ic is not None and ic < lcc and not const, None))
        hit = next((k for k, v, _ in tests if v), None)
        ev["clause"] = hit
        detail = []
        if hit == "use_crosses_set_p":
            detail = crossing(src, insn, tab)
        elif hit == "crosses-call":
            u = uid_at_cuid(lcc, tab)
            x = find_insn(u, insn) if u is not None else None
            detail = ["the last CALL before i3 is %s (last_call_cuid %d > the insn's cuid %d)" % (
                short_insn(x) if x else "uid %s" % u, lcc, ic)]
        elif hit == "used-between":
            detail = ["the destination %s is read between succ %d and i3 %d" % (ev["dest"], uid(succ), uid(i3))]
        ev["clause_detail"] = detail
        last = calls[-1]["f"] if calls else None
        call_clause = {"use_crosses_set_p": "use_crosses_set_p", "used-between": "reg_used_between_p",
                       "call-arg": "find_reg_fusage", "libcall-end": "find_reg_note", "no-conflict": "find_reg_note",
                       "self-copy": "find_reg_note"}
        if hit is None:
            ev["clause_check"] = "NO clause evaluates true - the chain model disagrees with cc1 (calls: %s)" % (
                ", ".join("%s=%s" % (c["f"], c["r"]) for c in calls[-6:]))
        elif hit in call_clause and call_clause[hit] != last and not (hit == "call-arg" and gr):
            ev["clause_check"] = "UNVERIFIED: the last call before the return was %s, not %s" % (last, call_clause[hit])
        else:
            ev["clause_check"] = "ok"
        if ucs is not None:
            ev["use_crosses_set_p"] = ucs

    # ---------------------------------------------------------------------------------- state
    ST = {"active": False, "fname": None, "att": None, "n": 0, "stack": []}

    def fname():
        p = u32(A["current_function_name"])
        return cstr(p, 200)

    class BP(gdb.Breakpoint):
        def __init__(self, addr, fn):
            super().__init__("*0x%x" % addr, internal=True)
            self.fn = fn

        def stop(self):
            try:
                self.fn()
            except Exception as e:                        # noqa: BLE001 - recorded, never stops the compile
                emit({"t": "err", "msg": "%s: %s" % (type(e).__name__, e)})
            return False

    # combine_instructions: the function gate
    def ci_entry():
        f = fname()
        ST["fname"] = f
        ST["active"] = FUNC is None or f == FUNC
        emit({"t": "func", "name": f, "traced": ST["active"]})

    def ci_exit():
        ST["active"] = False

    BP(C["addr"]["combine_instructions"], ci_entry)
    for a in S["combine_instructions"]["ret"]:
        BP(a, ci_exit)

    # try_combine
    def tc_entry():
        if not ST["active"]:
            return
        i3, i2, i1 = arg_at_entry(0), arg_at_entry(1), arg_at_entry(2)
        ST["n"] += 1
        ST["stack"] = []
        ST["att"] = {"t": "attempt", "n": ST["n"], "func": ST["fname"], "i3": uid(i3), "i2": uid(i2),
                     "i1": uid(i1) if i1 else None, "p_i3": i3, "p_i2": i2, "p_i1": i1,
                     "pat": {"i3": rtx_str(pattern(i3)), "i2": rtx_str(pattern(i2)),
                             "i1": rtx_str(pattern(i1)) if i1 else None},
                     "regs0": s32(A["reg_rtx_no"]) if "reg_rtx_no" in A else None,
                     "events": [], "site": None}

    def tc_ret():
        at = ST["att"]
        if not ST["active"] or at is None:
            return
        r = reg("eax")
        at["ret"] = uid(r) if r else 0
        if r:
            i3, i2, i1 = at["p_i3"], at["p_i2"], at["p_i1"]
            at["new"] = {"i3": rtx_str(pattern(i3)) if cname(i3) in ("insn", "jump_insn", "call_insn") else None,
                         "i3_kind": cname(i3), "i2_kind": cname(i2), "i1_kind": cname(i1) if i1 else None,
                         "i2": rtx_str(pattern(i2)) if cname(i2) in ("insn", "jump_insn", "call_insn") else None}
        for k in ("p_i3", "p_i2", "p_i1"):
            at.pop(k, None)
        for e in at["events"]:
            for k in [k for k in e if k.startswith("p_")]:
                e.pop(k)
        emit(at)
        ST["att"] = None

    BP(C["addr"]["try_combine"], tc_entry)
    for a in S["try_combine"]["ret"]:
        BP(a, tc_ret)

    def site_hit(routine, site):
        def f():
            at = ST["att"]
            if not ST["active"] or at is None:
                return
            if routine == "try_combine":
                at["site"] = {"k": site["k"], "line": site["line"], "key": site["key"], "text": site["text"],
                              "cond": site["cond"]}
                at["regs1"] = s32(A["reg_rtx_no"]) if "reg_rtx_no" in A else None
                return
            ev = ST["stack"][-1] if ST["stack"] and ST["stack"][-1]["e"] == routine else None
            if ev is None or ev.get("site"):
                return                                    # recursion: the innermost refusal is kept
            ev["site"] = {"k": site["k"], "line": site["line"], "key": site["key"], "text": site["text"],
                          "cond": site["cond"]}
            if routine == "can_combine_p" and site["key"] == "chain":
                chain_clause(ev, reg("ebp"))
        return f

    for r in ("try_combine", "can_combine_p", "combinable_i3pat"):
        for s in S[r]["sites"]:
            BP(s["addr"], site_hit(r, s))

    # calls made by try_combine: can_combine_p / combinable_i3pat / subst / recog_for_combine / use_crosses_set_p
    def tc_call(callee):
        def f():
            at = ST["att"]
            if not ST["active"] or at is None:
                return
            if callee == "can_combine_p":
                insn, i3, pred, succ = (arg_at_call(i) for i in range(4))
                ev = {"e": callee, "role": "i1" if succ else "i2", "insn": uid(insn), "succ": uid(succ) if succ else None,
                      "p_insn": insn, "p_i3": i3, "p_succ": succ, "calls": []}
            elif callee == "combinable_i3pat":
                ev = {"e": callee, "on": "i3" if arg_at_call(0) else "newpat"}
            elif callee == "recog_for_combine":
                pp = arg_at_call(0)
                ev = {"e": callee, "pat": rtx_str(u32(pp)), "insn": uid(arg_at_call(1)), "p_pp": pp}
            elif callee == "subst":
                ev = {"e": callee, "from": rtx_str(arg_at_call(1), [12]), "to": rtx_str(arg_at_call(2), [30])}
            else:
                ev = {"e": callee}
            at["events"].append(ev)
            ST["stack"].append(ev)
        return f

    def tc_back(callee):
        def f():
            at = ST["att"]
            if not ST["active"] or at is None or not ST["stack"]:
                return
            ev = ST["stack"].pop()
            r = reg("eax")
            if callee in ("subst",):
                ev["ret"] = rtx_str(r)
                ev["ret_code"] = cname(r)
            elif callee == "recog_for_combine":
                ev["ret"] = r - (1 << 32) if r & 0x80000000 else r
                ev["after"] = rtx_str(u32(ev["p_pp"]))
            else:
                ev["ret"] = r - (1 << 32) if r & 0x80000000 else r
            if callee == "can_combine_p" and ev.get("ret") and "calls" in ev:
                ev.pop("calls")                           # an accepted insn: the call log is noise
        return f

    WANT = {"can_combine_p", "combinable_i3pat", "subst", "recog_for_combine", "use_crosses_set_p"}
    for a, back, callee in S["try_combine"]["calls"]:
        if callee in WANT:
            BP(a, tc_call(callee))
            BP(back, tc_back(callee))

    # calls made by can_combine_p: their arguments and results (the chain's call clauses)
    def ccp_call(callee):
        def f():
            if not ST["active"] or not ST["stack"] or ST["stack"][-1]["e"] != "can_combine_p":
                return
            ST["stack"][-1]["calls"].append({"f": callee, "a": [arg_at_call(i) for i in range(3)], "r": None})
        return f

    def ccp_back(callee):
        def f():
            if not ST["active"] or not ST["stack"] or ST["stack"][-1]["e"] != "can_combine_p":
                return
            cl = ST["stack"][-1]["calls"]
            if cl and cl[-1]["f"] == callee and cl[-1]["r"] is None:
                cl[-1]["r"] = reg("eax")
        return f

    for a, back, callee in S["can_combine_p"]["calls"]:
        if callee and not callee.startswith("__x86"):
            BP(a, ccp_call(callee))
            BP(back, ccp_back(callee))

    gdb.execute("run", to_string=True)
    emit({"t": "end"})
    OUT.close()


if IN_GDB:
    try:
        _gdb_main()
    except Exception as _e:                                               # noqa: BLE001 - reported by run_gdb
        with open(os.environ.get("COMBINE_OUT", "combine_trace.jsonl"), "a") as _f:
            _f.write(json.dumps({"t": "fatal", "msg": "%s: %s" % (type(_e).__name__, _e)}) + "\n")
