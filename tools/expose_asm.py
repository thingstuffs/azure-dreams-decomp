#!/usr/bin/env python3
"""Hidden pins renamed to the ASM_* macro they spell (2026-09-13).

    python3 tools/expose_asm.py <outdir> [--only id,id]     # candidates <outdir>/<container>/<name>.c
    python3 tools/apply_candidates.py <outdir> --transform t47_expose_asm

pin_census.hidden_asm counts scaffolding the pin count cannot see.  Two of its kinds are pins under
another name, and this rewrites them so every pin tool sees them:
  raw-pin       an empty-template `__asm__` statement in a function body
  wrapper-call  a call of the file's own macro whose body is such a statement (or an ASM_* call);
                the call is expanded and the wrapper's definition removed once nothing uses it
A statement is rewritten only when its constraints and operands are exactly those of one macro in
include/common.h, so the matching build's preprocessed text is token-identical (`volatile` and
`__volatile__` are one keyword).  Every candidate is still scored, and apply_candidates' lint checks
that the -DNON_MATCHING port build generates the same code (a wrapper's port definition against the
macro's).  What maps to no macro stays and stays counted (STATUS "Hidden scaffolding").
"""
import argparse, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path
from pin_census import RAW_ASM_RE, WRAPPER_DEF_RE, CMT_RE, HAS_PP_RE, arm_labels


def _split(s, sep):
    """Split at top-level `sep` (outside strings and parentheses)."""
    out, depth, cur, i, q = [], 0, "", 0, None
    while i < len(s):
        ch = s[i]
        if q:
            cur += ch
            if ch == "\\" and i + 1 < len(s): cur += s[i + 1]; i += 1
            elif ch == q: q = None
        elif ch in "\"'": q = ch; cur += ch
        elif ch == "(": depth += 1; cur += ch
        elif ch == ")": depth -= 1; cur += ch
        elif ch == sep and depth == 0: out.append(cur); cur = ""
        else: cur += ch
        i += 1
    out.append(cur)
    return [x.strip() for x in out]


def _operands(part):
    if not part:
        return []
    ops = []
    for x in _split(part, ","):
        m = re.fullmatch(r'"([^"]*)"\s*\((.*)\)', x, re.S)
        if not m:
            return None
        ops.append((m.group(1), m.group(2).strip()))
    return ops


def macro_for(stmt):
    """The ASM_* invocation that spells this `__asm__` statement exactly, or None."""
    m = re.fullmatch(r"__asm__\s*(__volatile__|volatile)?\s*\((.*)\)", stmt.strip(), re.S)
    if not m:
        return None
    vol, parts = bool(m.group(1)), _split(m.group(2), ":")
    if parts[0].strip() != '""' or len(parts) > 4:
        return None
    outs = _operands(parts[1]) if len(parts) > 1 else []
    ins = _operands(parts[2]) if len(parts) > 2 else []
    clob = [c.strip() for c in _split(parts[3], ",")] if len(parts) > 3 and parts[3].strip() else []
    if outs is None or ins is None:
        return None
    sfx = "" if vol else "_NV"
    if not outs and not ins and not clob:
        return "ASM_SCHED_BARRIER()"                 # no outputs: gcc treats the asm as volatile
    if not outs and not ins and clob == ['"memory"'] and vol:
        return "ASM_MEM_BARRIER()"
    if not outs and not ins and len(clob) == 1 and re.fullmatch(r'"\$\w+"', clob[0]) and vol:
        return f"ASM_CLOBBER({clob[0]})"
    if clob:
        return None
    if len(outs) == 1 and outs[0][0] == "=r" and len(ins) == 1 and ins[0] == ("0", outs[0][1]):
        return f"ASM_KEEP{sfx}({outs[0][1]})"
    if len(outs) == 1 and outs[0][0] == "=r" and len(ins) == 1 and ins[0][0] == "0" and re.fullmatch(r"\w+", outs[0][1]):
        return f"{outs[0][1]} = {ins[0][1]}; ASM_KEEP{sfx}({outs[0][1]})"   # a copy through the asm: scored like the rest
    if not outs and len(ins) == 1 and ins[0][0] == "r":
        return f"ASM_USE{sfx}({ins[0][1]})"
    if not outs and len(ins) == 2 and ins[0][0] == ins[1][0] == "r":
        return f"ASM_USE2{sfx}({ins[0][1]}, {ins[1][1]})"
    if not outs and len(ins) == 1 and ins[0][0] == "g" and not vol:
        return f"ASM_USE_G_NV({ins[0][1]})"
    if len(outs) == 1 and outs[0][0] == "=r" and not ins and vol:
        return f"ASM_UNDEF({outs[0][1]})"
    return None


def _live(text):
    lines = text.split("\n")
    labs = arm_labels(text) if HAS_PP_RE.search(text) else ["both"] * len(lines)
    return lines, labs


def rewrite(text):
    """(new text, number of statements rewritten)."""
    n = 0
    # 1. the file's own wrappers: expand every call, then drop the definitions nothing uses
    code = CMT_RE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)
    wrappers = {}
    for m in WRAPPER_DEF_RE.finditer(code):
        name, params, body = m.group(1), [p.strip() for p in m.group(2).split(",") if p.strip()], m.group(3)
        body = re.sub(r"\\\n", " ", body).strip()
        if name.startswith("ASM_") or not re.search(r"__asm__|\bASM_[A-Z0-9_]+\s*\(", body):
            continue
        lab = _live(text)[1][text.count("\n", 0, m.start())]
        if lab in ("port", "dead"):
            continue                                     # the port definition of a two-armed wrapper
        wrappers.setdefault(name, []).append((params, body))
    for name, defs in wrappers.items():
        if len(defs) != 1:
            continue                                     # defined twice in matching code: leave it
        params, body = defs[0]
        def expand(call_args):
            if len(call_args) != len(params):
                return None
            e = body
            for p, a in zip(params, call_args):
                e = re.sub(r"\b%s\b" % re.escape(p), lambda _: a, e)
            e = e.strip().rstrip(";").strip()
            if re.fullmatch(r"ASM_[A-Z0-9_]+\s*\((?:[^()]|\([^()]*\))*\)", e):
                return e
            if re.search(r"\bASM_[A-Z0-9_]+\s*\(", e) and "__asm__" not in e and re.fullmatch(r"(?:do\s*\{.*\}\s*while\s*\(\s*0\s*\)|\(\{.*\}\))", e, re.S):
                return e                             # do { ... } while (0) / ({ ... }): the preprocessor's own expansion
            return macro_for(e) if e.startswith("__asm__") else None
        calls = list(re.finditer(r"\b%s\s*\(((?:[^()]|\([^()]*\))*)\)" % re.escape(name), text))
        lines, labs = _live(text)
        dead = not [c for c in calls if not re.match(r"[ \t]*#", lines[text.count("\n", 0, c.start())])]
        repl = []
        for c in calls:
            i = text.count("\n", 0, c.start())
            if re.match(r"[ \t]*#", lines[i]):
                continue                                 # the definition itself
            if labs[i] in ("port", "dead"):
                repl = None; break
            e = expand(_split(c.group(1), ",") if c.group(1).strip() else [])
            if e is None:
                repl = None; break
            repl.append((c.start(), c.end(), e))
        if repl is None or (not repl and not dead):
            continue
        for s, e_, new in reversed(repl):
            text = text[:s] + new + text[e_:]
            n += 1
        # the definitions: a two-armed #if block holding only NAME's defines, or the bare define
        blk = re.compile(r"^[ \t]*#[ \t]*if(?:n?def)?[^\n]*\n(?:[ \t]*#[ \t]*define[ \t]+%s\b(?:[^\n]*\\\n)*[^\n]*\n|[ \t]*#[ \t]*else[^\n]*\n|[ \t]*\n)+[ \t]*#[ \t]*endif[^\n]*\n" % re.escape(name), re.M)
        text, k = blk.subn("", text)
        if not k:
            text = re.sub(r"^[ \t]*#[ \t]*define[ \t]+%s\b(?:[^\n]*\\\n)*[^\n]*\n" % re.escape(name), "", text, flags=re.M)
            # the #if/#else/#endif shell those deletions emptied (only blank lines and comments left)
            text = re.sub(r"^[ \t]*#[ \t]*if(?:n?def)?[ \t]+NON_MATCHING[^\n]*\n(?:[ \t]*(?:/\*[^\n]*\*/)?[ \t]*\n)*"
                          r"(?:[ \t]*#[ \t]*else[^\n]*\n(?:[ \t]*(?:/\*[^\n]*\*/)?[ \t]*\n)*)?[ \t]*#[ \t]*endif[^\n]*\n",
                          "", text, flags=re.M)
    # 2. raw empty-template statements in function bodies
    lines, labs = _live(text)
    code = CMT_RE.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)
    flat = re.sub(r'"(?:[^"\\\n]|\\.)*"|\'(?:[^\'\\\n]|\\.)*\'', lambda m: " " * len(m.group(0)), code)
    edits = []
    for m in RAW_ASM_RE.finditer(code):
        i = code.count("\n", 0, m.start())
        if labs[i] in ("port", "dead") or re.match(r"[ \t]*#", lines[i]):
            continue
        if flat[:m.start()].count("{") - flat[:m.start()].count("}") <= 0:
            continue
        if not re.match(r"\s*;", code[m.end():]):
            continue                                     # not a whole statement
        mac = macro_for(m.group(0))
        if mac:
            edits.append((m.start(), m.end(), mac))
    for s, e, mac in reversed(edits):
        text = text[:s] + mac + text[e:]
        n += 1
    return text, n


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("outdir"); ap.add_argument("--only")
    a = ap.parse_args()
    keep = set(a.only.split(",")) if a.only else None
    total = files = 0
    for r in rows():
        if keep and r["id"] not in keep:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        t = p.read_text(errors="replace")
        if "__asm__" not in t and not re.search(r"#[ \t]*define[ \t]+\w+\([^)]*\)[^\n]*\bASM_", t):
            continue
        new, n = rewrite(t)
        if new != t:
            d = Path(a.outdir) / r["container"]; d.mkdir(parents=True, exist_ok=True)
            (d / p.name).write_text(new)
            total += n; files += 1
    print(f"{files} files, {total} statements rewritten")


if __name__ == "__main__":
    main()
