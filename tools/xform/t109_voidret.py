"""T109: a `void` function returns the pointer it leaves in `$v0` - the `$2` pin and its keep go.

APPEARS     a `void` function (or `static __inline__` helper) that stores through a pointer held in a local
            pinned to `$2` and kept alive:

                void func_80028774(UnalignedBlock12 *dest) {
                    register UnalignedBlock12 *dst ASM_REG("$2") = dest;
                    ASM_KEEP(dst);
                    dst[0] = D_80029550.chunks[0];
                    dst[1] = D_80029550.chunks[1];
                }

            (dungeon/func_81813774, claude-opus-5-5 lane work/native_lane/r73_opus_s4, 2 pins),
            main/func_800206C8 (r73_opus_s2, a block-scoped `final_base = base` copy of a LOCAL, 2 pins),
            main/func_8000FD60 (r73_opus_s3, the pin sits in the `static __inline__ void set_handler(u8 *base)`
            helper, 2 pins) and the pinless-`$2` variant town/func_8067F5C4 (astra lane r74_astra_a8: a
            `tail_base = entries; ASM_KEEP(tail_base)` copy before the terminal address arithmetic, 3 pins
            with a `$3` binding on the tail pointer).

RESOLVES    opus (func_81813774): "APPEARS: a leaf `void` function whose pinned text is `register T *x
            ASM_REG("$2") = param; ASM_KEEP(x);`, with the body storing through x (listing: a leading `move
            $2,$4`). RESOLVES: make the function return the parameter (`return param;`, return type `T *`)."
            opus (func_8000FD60): "give the function a pointer return type and `return` the object that is
            held in `$sN`" - all four return spellings were exact there, the helper returning `base` too.
            astra (func_8067F5C4): "test the natural original-buffer return so result liveness preserves the
            copy and excludes `$v0` from the terminal address."  Mechanism: the retail function RETURNS the
            pointer (the SDK/utility `memcpy`-style convention), so `$v0` is the return-value pseudo set by
            a plain copy at the point the source names it; m2c typed the function `void` because no caller
            reads the result, and the pin re-created the copy by hand.

WHY THE OWNERS MISS IT (measured 2026-09-23, work/native_lane/r73_h2_t75_returnkept_check)
            t75_returnkept adds a return value only to a function ALREADY declared non-void (`return;` ->
            `return v;`); the four rows are `void`.

SAFETY      the only changes are the return type (every textual declaration of the function in the scored
            arms), `return V;` appended when the body falls off its end, bare `return;` statements turned
            into `return V;` (or left, as a C89 non-void `return;`), and - for the copy form - the copy local
            renamed to its source.  Callers that ignore the result are unaffected; `info["signature_change"]`
            names the function so the landing step can review textual callers.

CANDIDATES  per `void` definition with pins: V = every pointer parameter, the SOURCE of every pinned or
            kept pointer copy `x = SRC;` (x renamed to SRC, its declaration and the self-copy dropped), and x
            itself (its `ASM_REG` erased); x (return spellings: every `return;` -> `return V;`, or only the
            fall-off end) x (pin plans: the pins naming x/V, those plus the function's `$2`/`$3` bindings,
            every pin of the function).  Ranked by cc1 listing distance to the pinned text; the
            listing-exact candidates and the two nearest go to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text, arm_labels, HAS_PP_RE
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments, decls_of
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments, decls_of
    from t36_paramwidth import functions
    import screen

MAX_LISTINGS = 60
MAX_VERIFY = 4
RETURN_BARE = re.compile(r"\breturn[ \t]*;")


def _labels(text):
    return arm_labels(text) if HAS_PP_RE.search(text) else None


def _scored(labels, text, pos):
    if labels is None:
        return True
    ln = text.count("\n", 0, pos)
    return ln >= len(labels) or labels[ln] not in ("port", "dead")


def void_decls(text, fname):
    """[(a, b)] spans of the `void` return-type word of every declaration/definition of fname (scored arms)."""
    masked, labels, out = mask_comments(text), _labels(text), []
    for m in re.finditer(r"(?<![\w.>])%s[ \t\n]*\(" % re.escape(fname), masked):
        hs = masked.rfind("\n", 0, m.start()) + 1
        head = masked[hs:m.start()]
        vm = re.search(r"\bvoid[ \t]+$", head)
        if not vm or "=" in head or "(" in head or "return" in head:
            continue
        if not _scored(labels, text, m.start()):
            continue
        out.append((hs + vm.start(), hs + vm.start() + 4))
    return out


def void_functions(text):
    """[(fname, params, b0, b1)] of the definitions returning plain `void` that hold pins."""
    pins = sites_of(text)
    out = []
    for fname, params, b0, b1 in functions(text):
        if not any(b0 < p[3] < b1 for p in pins):
            continue
        spans = void_decls(text, fname)
        if not any(a < b0 and not re.search(r"[;{}]", mask_comments(text)[a:b0]) for a, _ in spans):
            continue
        out.append((fname, params, b0, b1))
    return out


def copies(text, b0, b1):
    """[(x, src, ptr_type)] pointer locals of the body copied from an identifier and pinned or kept."""
    masked = mask_comments(text)
    body = masked[b0:b1]
    pins = [p for p in sites_of(text) if b0 < p[3] < b1]
    named = set()
    for p in pins:
        if p[0] == "reg":
            ls = text.rfind("\n", 0, p[3]) + 1
            le = text.find("\n", p[4])
            m = re.search(r"\b([A-Za-z_]\w*)\s*ASM_REG", text[ls:le])
            if m:
                named.add(m.group(1))
        else:
            named.update(re.findall(r"\b([A-Za-z_]\w*)\b", p[2]))
    out = []
    for x in sorted(named):
        ds = [d for d in decls_of(text, x) if b0 < d[2][0] < b1]
        if len(ds) != 1 or ds[0][1] < 1:
            continue
        ty = ds[0][0] + " " + "*" * ds[0][1]
        dtext = text[ds[0][2][0]:ds[0][2][1]]
        srcs = set(re.findall(r"=\s*(?:\([^()]*\)\s*)?([A-Za-z_]\w*)\s*;", re.sub(r"ASM_REG\([^)]*\)", "", dtext)))
        srcs.update(re.findall(r"(?<![\w.>])%s\s*=(?!=)\s*(?:\([^()]*\)\s*)?([A-Za-z_]\w*)\s*;" % re.escape(x), body))
        for s in sorted(srcs):
            if s != x and not s.startswith(("D_", "func_")) and not s.isupper():
                out.append((x, s, ty.strip()))
    return out


def _rename(text, b0, b1, x, src):
    """Drop x's declaration and `x = src;` statements inside [b0, b1), rename x -> src there."""
    body = text[b0:b1]
    for d in sorted(decls_of(body, x), key=lambda d: -d[2][0]):
        a, b = d[2]
        body = body[:a] + body[b:]
    body = re.sub(r"^[ \t]*%s[ \t]*=(?!=)[ \t]*(?:\([^()]*\)[ \t]*)?%s[ \t]*;[^\n]*\n" % (re.escape(x), re.escape(src)),
                  "", body, flags=re.M)
    body = re.sub(r"(?<![\w.>])%s\b" % re.escape(x), src, body)
    return text[:b0] + body + text[b1:]


def _retype(text, fname, rtype):
    t = text
    for a, b in sorted(void_decls(text, fname), reverse=True):
        t = t[:a] + _typed(rtype) + t[b:].lstrip(" \t")
    return t


def _typed(rtype):
    r = re.sub(r"\s+", " ", rtype.strip())
    r = re.sub(r"\s*\*", " *", r).replace("* *", "**")
    return r if r.endswith("*") else r + " "


def _returns(text, fname, v, mode):
    """Rewrite the returns of fname's body: mode 'all' (every bare return), 'end' (fall-off only)."""
    for f, params, b0, b1 in functions(text):
        if f != fname:
            continue
        body = text[b0:b1]                              # from `{` up to (not including) the closing `}`
        if mode == "all":
            body = RETURN_BARE.sub("return %s;" % v, body)
        m = re.search(r"(?:^|[;{}])\s*([^;{}]*;)\s*$", mask_comments(body))
        if not (m and re.match(r"return\b[^;]*\S[^;]*;|return\s+\S", m.group(1).strip())):
            body = body.rstrip() + "\n    return %s;\n" % v
        return text[:b0] + body + text[b1:]
    return None


def _named_pins(text, names, b0, b1):
    out = []
    for p in sites_of(text):
        if not b0 < p[3] < b1:
            continue
        ls = text.rfind("\n", 0, p[3]) + 1
        le = text.find("\n", p[4])
        le = len(text) if le < 0 else le
        seg = text[p[3]:p[4]] if p[0] == "stmt" else text[ls:le]
        if any(re.search(r"\b%s\b" % re.escape(n), seg) for n in names):
            out.append(p)
    return out


def _body(text, fname):
    for f, params, b0, b1 in functions(text):
        if f == fname:
            return params, b0, b1
    return None


def candidates(text):
    sig = unscored_text(text)
    out, seen = [], {text}

    def add(label, cand):
        if cand and cand not in seen and unscored_text(cand) == sig:
            seen.add(cand); out.append((label, cand))

    for fname, params, b0, b1 in void_functions(text):
        options = []                                    # (label, value, type, rename (x, src) or None, names)
        for x, src, ty in copies(text, b0, b1):
            pty = {p: t for p, t, _, _ in params}.get(src)
            sd = [d for d in decls_of(text[b0:b1], src)]
            sty = pty if pty else (sd[0][0] + " " + "*" * sd[0][1] if sd and sd[0][1] else None)
            if sty and "*" in sty:
                options.append(("copy:%s<-%s" % (x, src), src, sty, (x, src), {x, src}))
            options.append(("local:%s" % x, x, ty, None, {x}))
        for p, ty, _, _ in params:
            if "*" in ty and not any(o[1] == p for o in options):
                options.append(("param:%s" % p, p, ty, None, {p}))
        for label, v, ty, ren, names in options:
            for plan in ("named", "reg", "all"):
                cur = text
                _, cb0, cb1 = _body(cur, fname)
                pins = _named_pins(cur, names, cb0, cb1)
                if plan == "reg":
                    pins += [p for p in sites_of(cur) if cb0 < p[3] < cb1 and p[0] == "reg"
                             and re.search(r'"\$(2|3)"', cur[p[3]:p[4]] + cur[p[4]:cur.find("\n", p[4])])]
                elif plan == "all":
                    pins = [p for p in sites_of(cur) if cb0 < p[3] < cb1]
                pins = list({(p[3], p[4]): p for p in pins}.values())
                if pins:
                    cur = erase_many(cur, pins, clean_notes=True)
                if ren:
                    _, cb0, cb1 = _body(cur, fname)
                    cur = _rename(cur, cb0, cb1, *ren)
                cur = _retype(cur, fname, ty)
                if cur is None:
                    continue
                for mode in ("all", "end"):
                    cand = _returns(cur, fname, v, mode)
                    add("%s:%s:%s:%s" % (fname, label, plan, mode), cand)
                # an inlined helper: the CALLER returns the object instead (main/func_8000FD60 - the
                # helper's pinned copy is the caller's return value once inlined)
                if ren or plan != "named":
                    continue
                for cname, cparams, c0, c1 in functions(cur):
                    if cname == fname or not void_decls(cur, cname):
                        continue
                    m = re.search(r"^[ \t]*%s[ \t]*\((?P<arg>[A-Za-z_]\w*)\)[ \t]*;\s*$" % re.escape(fname),
                                  cur[c0 + 1:c1], re.M)
                    if not m:
                        continue
                    arg = m.group("arg")
                    aty = {p: t for p, t, _, _ in cparams}.get(arg)
                    ad = decls_of(cur[c0:c1], arg)
                    aty = aty or (ad[0][0] + " " + "*" * ad[0][1] if ad and ad[0][1] else None)
                    if not aty or "*" not in aty:
                        continue
                    base = text if not pins else erase_many(text, pins, clean_notes=True)
                    _, hb0, hb1 = _body(base, fname)
                    for x, src, _t in copies(text, b0, b1):
                        if x in names:
                            base = _rename(base, hb0, hb1, x, src)
                            break
                    base = _retype(base, cname, aty)
                    add("%s:caller-%s:%s" % (cname, fname, arg), _returns(base, cname, arg, "all"))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t109_voidret"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        vf = void_functions(text)
        if not vf:
            return "no void function with pins"
        if not any(copies(text, b0, b1) or any("*" in t for _, t, _, _ in params) for _, params, b0, b1 in vf):
            return "no pointer parameter or pinned pointer copy in a void function"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        menu = [(l, c) for l, c in candidates(text) if len(sites_of(c)) < pins_in]
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        ranked, listings = [], 0
        for label, cand in menu:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((_dist(target, lst), len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info.update(listings=listings, menu=len(menu))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried,
                                  signature_change=label.split(":")[0])
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
