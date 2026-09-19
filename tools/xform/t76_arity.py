"""T76: fake arguments dropped - the callee is K&R and retail calls it with fewer arguments.

APPEARS     locals that are never assigned, only `ASM_SET`/`ASM_USE`-pinned, passed to a call:
                s32 fallback_arg_0;  ...  ASM_SET(fallback_arg_0); ... func_800A6508(fallback_arg_0, fallback_arg_1, ...);
            retail's `jal` has no argument setup at all: the decompiler saw the argument registers alive (holding
            whatever the previous code left) and invented arguments; the pins keep the registers untouched.
RESOLVES    Opus lane r58_opus1 (2026-09-19), `dungeon/func_800C78A4`: `func_800A6508();` with a K&R prototype
            `extern void func_800A6508();` - four pins at once.  docs/PIN_LANE_RULES_AUDIT_20260919.md gap 3 (five
            lanes); t8/t8b only ADD arguments.  29 pinned rows carry the shape (83 pins).
CANDIDATES  per call: the trailing run of such arguments dropped (all of them when every argument is one), their
            pins and declarations erased, the file-local prototype of the callee rewritten to `()` when it named
            parameters; screened by the cc1 listing against the pinned text; listing-exact texts go to `vf`.  A
            prototype declared outside this row (a header) is not edited: the call alone is tried.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from .t72_stmtperm import decl_names
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    from t72_stmtperm import decl_names
    import screen

MAX_VERIFY = 6
MAX_LISTINGS = 40
SETPIN = re.compile(r"^[ \t]*ASM_(?:SET|USE|USE_NV|USE2_NV)\(\s*([^()]*)\)\s*;", re.M)
CALL = re.compile(r"^(?P<ind>[ \t]*)(?:(?P<lhs>[A-Za-z_][\w\.\->\[\]]*)\s*=\s*)?(?P<f>[A-Za-z_]\w*)\s*\((?P<args>[^;]*)\)\s*;[ \t]*$", re.M)


def split_args(s):
    out, depth, cur = [], 0, ""
    for ch in s:
        if ch in "([":
            depth += 1
        elif ch in ")]":
            depth -= 1
        if ch == "," and depth == 0:
            out.append(cur.strip()); cur = ""
        else:
            cur += ch
    if cur.strip():
        out.append(cur.strip())
    return out


def sites_in(text):
    """[(call_line, fname, [args], [fake arg names], proto_line_or_None)] per call carrying fake arguments."""
    masked = mask_comments(text)
    ml = masked.split("\n")
    out = []
    for fn, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body)
        pinned = set()
        for m in SETPIN.finditer(body):
            pinned.update(re.findall(r"[A-Za-z_]\w*", m.group(1)))
        fake = set()
        for v in pinned & locals_:
            uses = len(re.findall(r"\b%s\b" % re.escape(v), body))
            assigns = re.findall(r"(?<![\w.>])%s\s*(?:[-+*/%%&|^]|<<|>>)?=(?!=)|(?:\+\+|--)\s*%s\b|\b%s\s*(?:\+\+|--)|&\s*%s\b" % ((re.escape(v),) * 4), body)
            npins = sum(1 for m in SETPIN.finditer(body) if re.search(r"\b%s\b" % re.escape(v), m.group(1)))
            if not assigns and uses == 1 + npins + 1:               # declaration + pins + exactly one use (the call)
                fake.add(v)
        if not fake:
            continue
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first + 1, last):
            cm = CALL.match(ml[i])
            if not cm or cm.group("f") in ("if", "while", "for", "switch", "return", "sizeof") or cm.group("f").startswith("ASM_"):
                continue
            args = split_args(cm.group("args"))
            fk = [a for a in args if a in fake]
            if not fk:
                continue
            # trailing run only (positional registers)
            k = len(args)
            while k > 0 and args[k - 1] in fake:
                k -= 1
            trailing = args[k:]
            if not trailing:
                continue
            proto = None
            for j, ln in enumerate(ml[:first]):
                if re.match(r"^\s*(?:extern\s+)?[A-Za-z_][\w \t\*]*\b%s\s*\(" % re.escape(cm.group("f")), ln):
                    proto = j
            out.append((i, cm.group("f"), args, trailing, proto))
    return out


def rewrite(text, site):
    i, f, args, trailing, proto = site
    ls = text.split("\n")
    keep = args[:len(args) - len(trailing)]
    cm = CALL.match(mask_comments(text).split("\n")[i])
    ls[i] = cm.group("ind") + ((cm.group("lhs") + " = ") if cm.group("lhs") else "") + f + "(" + ", ".join(keep) + ");"
    if proto is not None and not keep:
        ls[proto] = re.sub(r"\((?!\s*\))[^;]*\)", "()", ls[proto], count=1)
    new = "\n".join(ls)
    # the fake arguments' pins go, then their declarations
    pins = [s for s in sites_of(new) if s[1] in ("ASM_SET", "ASM_USE", "ASM_USE_NV", "ASM_USE2_NV") and any(re.search(r"\b%s\b" % re.escape(v), s[2] or "") for v in trailing)]
    new = erase_many(new, pins, clean_notes=True) if pins else new
    for v in trailing:
        new = re.sub(r"\n[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t\*]*?\b%s[ \t]*;[^\n]*(?=\n)" % re.escape(v), "", new, count=1)
    return new


class T:
    name = "t76_arity"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if sites_in(text) else "no call with pinned fake arguments"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        import difflib
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        for _ in range(8):
            sites = sites_in(cur)
            if not sites or listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            progressed = False
            for site in sites:
                new = rewrite(cur, site)
                if len(sites_of(new)) >= len(sites_of(cur)):
                    continue
                lst = screen.compile_s(row, new); listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))
                if d:
                    continue
                verifies += 1
                if vf(new).get("exact"):
                    cur = new; progressed = True
                    steps.append("%s-%d@%d" % (site[1], len(site[3]), site[0] + 1))
                    break
            if not progressed:
                break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur))}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
