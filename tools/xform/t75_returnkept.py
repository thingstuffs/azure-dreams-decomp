"""T75: a bare `return;` in a non-void function returns the register-pinned local that holds the result.

APPEARS     a function declared to return a value, a path ending in `return;`, and a local pinned to `$2`/`$v0`
            (`register T v ASM_REG("$2")`) that holds the value retail leaves in `$v0`:
                register s32 result ASM_REG("$2");
                ...
                result = obj;
                return;
RESOLVES    four lanes (r35_sol_far, r36_returns, lackeep4, lac3; docs/PIN_LANE_RULES_AUDIT_20260519.md gap 6):
            `return result;` (or a cast of it) makes the value the function's result, so the compiler keeps it in
            `$v0` across the tail without a pin.  t48_gotoreturn turns gotos into returns but never introduces a
            return value.
CANDIDATES  per bare return (nearest the pinned local's last assignment first): `return v;` with the `$2` pin
            erased, then also the other pins of `v`, then every pin jointly; a cast to the declared return type when
            the local's type differs; screened by the cc1 listing against the pinned text, listing-exact texts go to
            `vf`.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

MAX_VERIFY = 6
MAX_LISTINGS = 60
DEF_RE = re.compile(r"^(?P<ret>(?:static\s+)?(?:const\s+)?[A-Za-z_]\w*(?:\s*\*+)?)\s+(?P<name>[A-Za-z_]\w*)\s*\(", re.M)
PIN2 = re.compile(r"^[ \t]*register[ \t]+(?P<ty>[A-Za-z_][\w \t\*]*?)\s*\b(?P<v>[A-Za-z_]\w*)\s+ASM_REG\(\"\$(?:2|v0)\"\)", re.M)


def sites_in(text):
    """[(ret_line_index, v, vtype, rettype, fname)] for each bare return in a non-void function with a $2-pinned local."""
    masked = mask_comments(text)
    ml = masked.split("\n")
    out = []
    for fname, params, b0, b1 in functions(text):
        head = masked[:b0]
        dm = list(DEF_RE.finditer(head))
        dm = [d for d in dm if d.group("name") == fname]
        if not dm:
            continue
        ret = dm[-1].group("ret").strip()
        if ret == "void" or ret.endswith("void"):
            continue
        body = masked[b0:b1]
        pins = [(m.group("v"), m.group("ty").strip()) for m in PIN2.finditer(body)]
        if not pins:
            continue
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first, last):
            if re.match(r"^[ \t]*return;\s*$", ml[i]):
                for v, ty in pins:
                    out.append((i, v, ty, ret, fname))
    return out


class T:
    name = "t75_returnkept"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if sites_in(text) else "no bare return with a $2-pinned local in a non-void function"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        import difflib
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        for i, v, ty, ret, fname in sites_in(text):
            live = [s for s in sites_in(cur) if s[1] == v and cur.split("\n")[s[0]].strip() == "return;"]
            if not live:
                continue
            found = False
            for j, _, _, _, _ in live:
                ls = cur.split("\n")
                ind = re.match(r"[ \t]*", ls[j]).group(0)
                forms = ["return %s;" % v] + (["return (%s) %s;" % (ret, v)] if ret.replace(" ", "") != ty.replace(" ", "") else [])
                for form in forms:
                    new = "\n".join(ls[:j] + [ind + form] + ls[j + 1:])
                    pins = sites_of(new)
                    mine = [s for s in pins if s[1] == "ASM_REG" and re.search(r"\b%s\b" % re.escape(v), new.split("\n")[s[5] - 1])]
                    of_v = [s for s in pins if re.search(r"\b%s\b" % re.escape(v), (s[2] or "")) or s in mine]
                    plans = [mine] + ([of_v] if len(of_v) > len(mine) else []) + ([pins] if len(pins) > len(of_v) else [])
                    for group in plans:
                        if not group or listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                            continue
                        cand = erase_many(new, group, clean_notes=True)
                        if len(sites_of(cand)) >= len(sites_of(cur)):
                            continue
                        lst = screen.compile_s(row, cand); listings += 1
                        if lst is None:
                            continue
                        d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))
                        if d:
                            continue
                        verifies += 1
                        if vf(cand).get("exact"):
                            cur, found = cand, True
                            steps.append("return_%s@%d-erase%d" % (v, j + 1, len(group)))
                            break
                    if found:
                        break
                if found:
                    break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur))}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
