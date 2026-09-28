"""Tiny dataflow over a gcc MIPS listing: every memory access / address use of symbols matching PAT.
   Returns records (func, sym, off, op, how) where how is:
     direct  - op %lo(SYM+k)($r) or op SYM+k       (own lui / macro)
     base    - op N($r) where $r = &SYM+k (lui/addiu or la), off = k+N
     based_i - op N($r) where $r = (&SYM+k) + index,  off = k+N (indexed element)
     addr    - the address escapes (stored, passed, compared) - off = k"""
import re
MEM = re.compile(r"^(lb|lbu|lh|lhu|lw|sb|sh|sw|lwl|lwr|swl|swr|ulw|ulh|ulhu|usw|ush)\s+(\$\w+),(.*)$")
def parse_sym(expr, rx):
    m = re.match(r"^(%lo\(|%gp_rel\()?(D_[0-9A-F]{8})([+-]\d+)?\)?(\((\$\w+)\))?$", expr.strip())
    if not m or not rx.fullmatch(m.group(2)): return None
    return m.group(2), int(m.group(3) or 0), m.group(5)
def scan(asm, rx):
    out = []; func = None; base = {}; hi = {}
    for raw in asm.splitlines():
        l = raw.split("#")[0].strip()
        if not l: continue
        if l.startswith(".ent"): func = l.split()[1]; base = {}; hi = {}; continue
        if l.startswith(".") or l.endswith(":"): continue
        parts = l.split(None, 1); op = parts[0]; args = parts[1] if len(parts) > 1 else ""
        a = [x.strip() for x in re.split(r",(?![^(]*\))", args)] if args else []
        m = MEM.match(l)
        if m:
            reg, expr = m.group(2), m.group(3)
            s = parse_sym(expr, rx)
            if s: out.append((func, s[0], s[1], op, "gp" if "%gp_rel" in expr else "direct"))
            else:
                mm = re.match(r"^(-?\d+)\((\$\w+)\)$", expr)
                if mm and mm.group(2) in base:
                    sym, k, how = base[mm.group(2)]
                    out.append((func, sym, k + int(mm.group(1)), op, how))
            if op[0] == "s":
                if reg in base: out.append((func,) + base[reg][:2] + (op, "addr-stored"))
                continue
            dest = reg
        else:
            dest = a[0] if a else None
        if op == "lui":
            m2 = re.match(r"%hi\((D_[0-9A-F]{8})([+-]\d+)?\)", a[1]) if len(a) > 1 else None
            base.pop(dest, None); hi.pop(dest, None)
            if m2 and rx.fullmatch(m2.group(1)): hi[dest] = (m2.group(1), int(m2.group(2) or 0))
            continue
        if op == "addiu" and len(a) == 3 and a[2].startswith("%lo("):
            s = parse_sym(a[2], rx)
            if s: base[dest] = (s[0], s[1], "base")
            else: base.pop(dest, None)
            continue
        if op == "la" and len(a) == 2:
            s = parse_sym(a[1], rx)
            if s: base[dest] = (s[0], s[1], "base")
            else: base.pop(dest, None)
            continue
        if op == "move" and len(a) == 2:
            if a[1] in base: base[dest] = base[a[1]]
            else: base.pop(dest, None)
            continue
        if op in ("addu", "subu") and len(a) == 3 and (a[1] in base or a[2] in base) and not a[2].lstrip("-").isdigit():
            src = base.get(a[1]) or base.get(a[2])
            base[dest] = (src[0], src[1], "based_i"); out.append((func, src[0], src[1], op, "indexed"))
            continue
        if op in ("addu", "addiu") and len(a) == 3 and a[1] in base and a[2].lstrip("-").isdigit():
            src = base[a[1]]; base[dest] = (src[0], src[1] + int(a[2]), src[2]); continue
        # any other use of a base register
        for x in a[1:]:
            if x in base and op not in ("j", "jal"): out.append((func,) + base[x][:2] + (op, "addr-use"))
        if a and op in ("jal", "jalr"):
            for r in ("$2", "$3", "$4", "$5", "$6", "$7", "$8", "$9", "$10", "$11", "$12", "$13", "$14", "$15", "$24", "$25", "$1", "$31"):
                base.pop(r, None)
        elif dest in base: base.pop(dest, None)
    return out
