"""T129: calls trimmed to the callee's DEFINED arity (m2c's invented trailing arguments dropped).

APPEARS     a call passing more arguments than the callee's definition in src/ takes (280 sites in 156 pinned rows on
            2026-09-30): m2c saw live argument registers and invented arguments, and pins were then added to hold the
            registers those fake arguments set.  Round 80 lanes solved rows with exactly this move - r80_opus_ap1
            (dungeon/func_80A1FBBC 7 -> 4: func_80047784 takes 3, not 4; `li $7,1` then gets sched1's birthing boost
            because $7 is set once), r80_opus_cl_move (81339700), r80_opus_ap2 (8009A1CC), r80_opus_r10 (8009CC44 needed
            the OTHER direction - see t8/t8b for adding arguments).
RESOLVES    every over-arity call to a single-arity callee trimmed (only when the dropped arguments have no side
            effects: no call, assignment or ++/--), a file-local prototype of that callee rewritten to the definition's
            parameter count (`()` when its parameter types are not plain scalars/pointers); tried alone, then jointly
            with ONE pin erased (each pin, last first).
ACCEPTANCE  exact; pins never grow (fake arguments are a fidelity error of their own, so an exact trim with no pin
            change is kept too).
"""
import glob, os, re, sys
from pathlib import Path
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from pin_census import sites_of
from pin_sites import erase_many

MAX_VERIFY = int(os.environ.get("T129_MAX", "12"))
NAME = r"(?:func|w)_[0-9A-Fa-f]{8}"
DEF = re.compile(r"^(?:static\s+)?[A-Za-z_][\w\s\*]*?\b(%s)\s*\(([^;{)]*)\)\s*\{" % NAME, re.M)
SCALAR = re.compile(r"^\s*(?:const\s+)?(?:unsigned\s+|signed\s+)?(?:s8|u8|s16|u16|s32|u32|int|char|short|long|void)\s*\**\s*\w*\s*$")
_DEFS = None


def defs():
    """name -> parameter list text, for callees with exactly one definition (one arity) in src/."""
    global _DEFS
    if _DEFS is None:
        seen = {}
        for f in glob.glob(str(ROOT / "src/*/*.c")):
            for m in DEF.finditer(open(f, errors="replace").read()):
                p = m.group(2).strip()
                seen.setdefault(m.group(1), set()).add("" if p == "void" else p)
        _DEFS = {k: next(iter(v)) for k, v in seen.items() if len({_n(p) for p in v}) == 1}
    return _DEFS


def _n(params):
    return 0 if not params.strip() else _split(params).__len__()


def _split(s):
    out, d, cur = [], 0, ""
    for ch in s:
        if ch in "([{": d += 1
        elif ch in ")]}": d -= 1
        if ch == "," and d == 0:
            out.append(cur); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur)
    return out


def _close(t, i):
    d = 1
    while i < len(t) and d:
        d += {"(": 1, ")": -1}.get(t[i], 0); i += 1
    return i - 1 if d == 0 else -1


def trim(text):
    """(text with every trimmable over-arity call fixed and the callees' local prototypes aligned, callee names)."""
    D = defs(); edits = []; names = set()
    for m in re.finditer(r"\b(%s)\s*\(" % NAME, text):
        name = m.group(1)
        if name not in D:
            continue
        ls = text.rfind("\n", 0, m.start()) + 1
        head = text[ls:m.start()]
        if re.search(r"\b(extern|static|typedef)\b", head):
            continue
        if head.strip() and re.match(r"^\s*[A-Za-z_][\w\s\*]*$", head) and not re.search(r"\b(return|else|do)\s*$", head):
            continue                                    # `T name(` at statement start: a declaration/definition
        e = _close(text, m.end())
        if e < 0:
            continue
        body = text[m.end():e]
        args = _split(body); want = _n(D[name])
        if len(args) <= want:
            continue
        if any(re.search(r"\(|(?<![=!<>])=(?!=)|\+\+|--", a) for a in args[want:]):
            continue
        edits.append((m.end(), e, ",".join(args[:want]).strip() if want else ""))
        names.add(name)
    t = text
    for s, e, rep in sorted(edits, reverse=True):
        t = t[:s] + rep + t[e:]
    for name in names:
        want = _n(D[name])

        def cut(mm, want=want):
            ps = _split(mm.group(2)) if mm.group(2).strip() not in ("", "void") else []
            if len(ps) <= want:
                return mm.group(0)
            return mm.group(1) + (",".join(ps[:want]).strip() if want else "void") + mm.group(3)
        t = re.sub(r"(^[ \t]*(?:extern\s+)?[A-Za-z_][\w \t\*]*?\b%s\s*\()([^;{)]*)(\)\s*;)" % name, cut, t, flags=re.M)
    return t, names


class T:
    name = "t129_defarity"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        t, names = trim(text)
        return None if names and t != text else "no over-arity call to a defined callee"

    @staticmethod
    def apply_verified(text, row, census, vf):
        base, names = trim(text)
        if not names or base == text:
            return None, {"refused": ["no over-arity call to a defined callee"]}
        n0 = len(sites_of(text)); tried = [0]

        def ok(t):
            if len(sites_of(t)) > n0 or tried[0] >= MAX_VERIFY:
                return False
            tried[0] += 1
            return bool(vf(t).get("exact"))

        for s in sorted(sites_of(base), key=lambda s: -s[3]):
            cand = erase_many(base, [s], clean_notes=True)
            if len(sites_of(cand)) < n0 and ok(cand):
                return cand, {"callees": sorted(names), "erased": s[1], "verifies": tried[0]}
        if ok(base):
            return base, {"callees": sorted(names), "erased": None, "verifies": tried[0]}
        return None, {"refused": ["no exact defined-arity text (%d verifies)" % tried[0]]}
