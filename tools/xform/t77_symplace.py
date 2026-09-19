"""T77: an address literal respelled as the symbol at that exact address, in place, the variable kept.

APPEARS     `v = (T *)0x800XXXXX;` (a local, a parameter reassigned, or a `register ... ASM_REG` local) whose
            pin's erase diff is `-addiu +ori` or `-addiu,lui +lui,ori`: with the pin retail materialises the
            address as `lui/addiu %lo` (a symbol, sign-adjusted), without it cse's `fold_rtx` folds the CONST_INT
            page + offset and the compiler emits `lui/ori`.
RESOLVES    Opus lane r58_opus3 (2026-09-19), `dungeon/func_800C96AC`: `state = (u16 *)D_80083460;` at the SAME
            statement position (the HIGH register of gcc's HIGH/LO_SUM pair is fixed by the statement's LUID), the
            variable kept, the pin erased.  t29_addrsym deletes the variable and substitutes every use (allocation
            changes) and refuses parameters and port-arm variables; t54_pagebase respells a PAGE symbol only.
            Two-register pairs (`lui $a / addiu $b,$a`) need a splitting cell (2.7.2-cdk, 2.8.x); one-register
            pairs are an atomic `la` at FSF cells and win only when adjacent and outside a delay slot.
CANDIDATES  per literal definition (pinned variables first): the exact-address symbol expression (an existing
            `extern` or a new `extern u8 D_XXXXXXXX[];`), the variable's pins erased singly and jointly, then the
            function's pins jointly; a listing that contains `la` is rejected before scoring; listing-exact texts go
            to `vf`.  Only the scored arm is edited: a definition inside the port arm is skipped.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, arm_labels, unscored_text
from pin_sites import erase_many
try:
    from . import t29_addrsym as A
    from .t54_pagebase import definitions, add_externs
    from . import screen
except ImportError:
    import t29_addrsym as A
    from t54_pagebase import definitions, add_externs
    import screen

MAX_DEFS = 8
MAX_LISTINGS = 60
MAX_VERIFY = 6


def defs_in(text):
    """Literal definitions in the scored arm, pinned variables first: [(var, addr, start, end, want_type)]."""
    labels = arm_labels(text)
    out = []
    pins = sites_of(text)
    for d in definitions(text):
        line = text.count("\n", 0, d["pos"])
        if labels[line] in ("port", "dead"):
            continue
        pinned = any(re.search(r"\b%s\b" % re.escape(d["var"]), text[s[3]:s[4]]) for s in pins)
        decl = A.decls_of(text, d["var"])
        want = None
        if decl:
            ty, ptr, _ = decl[0]
            want = (ty + " " + "*" * ptr) if ptr else None
        elif re.search(r"\(\s*[A-Za-z_][\w ]*\*+\s*\)", text[d["start"]:d["end"]]):
            cm = re.search(r"\(\s*([A-Za-z_][\w ]*\*+)\s*\)", text[d["start"]:d["end"]]); want = cm.group(1).strip()
        out.append((pinned, d["var"], d["value"], d["start"], d["end"], want))
    out.sort(key=lambda x: (not x[0], x[3]))
    return [x[1:] for x in out[:MAX_DEFS]]


def respell(text, var, addr, start, end, want):
    ext = set()
    expr = A.sym_expr(text, addr, want, ext)
    new = text[:start] + expr + text[end:]
    return add_externs(new, ext) if ext else new


DERIVED = r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)\s*=\s*(?P<cast>\(\s*[A-Za-z_][\w ]*\*+\s*\)\s*)?\(?\s*(?:\(\s*[A-Za-z_][\w ]*\*+\s*\)\s*)?%s\s*\+\s*(?P<k>0x[0-9A-Fa-f]+|\d+)\s*\)?\s*;[ \t]*$"


def derived_candidates(text, var, addr, start, end):
    """Texts where a derived `V = (T)(page + K)` becomes `V = (T)D_<page+K>` AT THE PAGE DEFINITION'S PLACE,
    the page's scored definition and the derived statement removed (the Opus r58_opus3 shape)."""
    ls = text.split("\n")
    dline = text.count("\n", 0, start)
    rx = re.compile(DERIVED % re.escape(var), re.M)
    out = []
    for j, ln in enumerate(ls):
        m = rx.match(ln)
        if not m or j <= dline:
            continue
        k = int(m.group("k"), 0)
        ext = set()
        cast = (m.group("cast") or "").strip()
        want = cast[1:-1].strip() if cast else None
        expr = A.sym_expr(text, addr + k, want, ext)
        stmt = m.group("ind") + "%s = %s;" % (m.group("v"), expr)
        new_ls = ls[:dline] + [stmt] + ls[dline + 1:j] + ls[j + 1:]
        new = "\n".join(new_ls)
        out.append((m.group("v"), addr + k, add_externs(new, ext) if ext else new))
    return out


class T:
    name = "t77_symplace"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if defs_in(text) else "no address-literal definition in the scored arm"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        import difflib
        pins_in, listings, verifies, steps, cur = len(sites_of(text)), 0, 0, [], text
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": ["pinned text does not build to a listing"], "pins_in": pins_in, "pins_out": pins_in}
        usig = unscored_text(text)
        for var, addr, _, _, want in defs_in(text):
            live = [d for d in defs_in(cur) if d[0] == var and d[1] == addr]
            if not live:
                continue
            var, addr, start, end, want = live[0]
            forms = [("inplace", var, addr, respell(cur, var, addr, start, end, want))]
            forms += [("derived:" + v2, var, a2, txt) for v2, a2, txt in derived_candidates(cur, var, addr, start, end)]
            found = False
            for form, _, a2, new in forms:
              if new == cur or unscored_text(new) != usig:
                continue
              pins = sites_of(new)
              mine = [s for s in pins if re.search(r"\b%s\b" % re.escape(var), new[s[3]:s[4]])]
              plans = [[p] for p in mine] + ([mine] if len(mine) > 1 else []) + ([pins] if len(pins) > len(mine) else [])
              for group in plans:
                if not group or listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    continue
                cand = erase_many(new, group, clean_notes=True)
                if len(sites_of(cand)) >= len(sites_of(cur)):
                    continue
                lst = screen.compile_s(row, cand); listings += 1
                if lst is None or any(l.startswith("la ") for l in lst) and not any(l.startswith("la ") for l in target):
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0) if y[:1] in "+-" and not y.startswith(("---", "+++")))
                if d:
                    continue
                verifies += 1
                if vf(cand).get("exact"):
                    cur, found = cand, True
                    steps.append("%s:%s=D_%08X-erase%d" % (form, var, a2, len(group)))
                    break
              if found:
                break
        info = {"listings": listings, "tried": verifies, "pins_in": pins_in, "pins_out": len(sites_of(cur))}
        if not steps:
            return None, info
        return cur, dict(info, step="+".join(steps))
