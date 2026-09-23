"""T114: a `register T z ASM_REG("$0")` zero register written back as the literal it reads.

APPEARS     a local bound to the hardware zero register and read as a constant 0 - a compare operand, an
            addend, a return value, a call argument (10 pinned rows carry one; town/func_80096134,
            claude-opus-5-5 lane work/native_lane/r73_opus_s20):

                register s32 zero ASM_REG("$0");
            #ifdef NON_MATCHING
                zero = 0;
            #else
            #endif
                mode = (u32)zero < (u32)is_available;
            ->  mode = is_available != 0;

RESOLVES    opus (func_80096134): "APPEARS: `register T zero ASM_REG("$0")` used as a comparison operand.
            RESOLVES: the literal comparison (`x != 0`)."  `(u32)0 < (u32)x` is m2c's reading of retail's
            `sltu $d,$0,$x`, which cc1 emits for `x != 0` itself (the MIPS `sne` expansion), so the pin was
            holding a spelling, not a register.

WHY THE OWNERS MISS IT  no generator reads the `$0` binding: erasing the pin leaves `zero` an ordinary
            uninitialised (or `= 0`) local, which cse folds differently from the literal compare.

CANDIDATES  per `$0`-bound local z (all of them jointly, then each alone): the pin erased (the declaration
            becomes a plain local, so a NON_MATCHING arm that still names z keeps compiling and stays
            byte-for-byte unchanged), every scored `z = 0;` statement dropped and every other scored read of
            z written as `0` - LITERAL - or with the literal folded - FOLD: `(u32)0 < (u32)x` / `0 < (u32)x`
            -> `x != 0`, `x + 0` / `x | 0` / `0 | x` -> `x`.  Ranked by the cc1 listing distance to the
            pinned text; listing-exact candidates and the two nearest go to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text, arm_labels
from pin_sites import erase_many
try:
    from . import screen
except ImportError:
    import screen

MAX_LISTINGS = 12
MAX_VERIFY = 4
DECL_RE = re.compile(r"^[ \t]*register[ \t]+[^;\n()]*?\b(?P<v>[A-Za-z_]\w*)[ \t]*ASM_REG\([ \t]*\"\$0\"[ \t]*\)[ \t]*;", re.M)
OPERAND = r"(?:\([^()]*\)\s*)?[A-Za-z_][\w.>\-\[\]]*"


def zeros(text):
    """The `$0`-bound local names, in order."""
    out = []
    for m in DECL_RE.finditer(text):
        if m.group("v") not in out:
            out.append(m.group("v"))
    return out


def fold(line):
    line = re.sub(r"\(\s*u32\s*\)\s*0\s*<\s*(?:\(\s*u32\s*\)\s*)?(%s)" % OPERAND, r"\1 != 0", line)
    line = re.sub(r"(?<![\w)\]])0\s*<\s*\(\s*u32\s*\)\s*(%s)" % OPERAND, r"\1 != 0", line)
    line = re.sub(r"(%s)\s*[+|]\s*0(?![\w.xX])" % OPERAND, r"\1", line)
    line = re.sub(r"(?<![\w)\]])0\s*\|\s*", "", line)
    return line


def rewrite(text, names, folded):
    """The pins on `names` erased, scored `z = 0;` lines dropped, scored reads written as 0."""
    pins = [p for p in sites_of(text) if p[1] == "ASM_REG" and any(
        re.search(r"\b%s\b" % re.escape(v), text[text.rfind("\n", 0, p[3]) + 1:text.find("\n", p[3])]) for v in names)]
    if not pins:
        return None
    t = erase_many(text, pins, clean_notes=True)
    lines, labels = t.split("\n"), arm_labels(t)
    out = []
    for i, l in enumerate(lines):
        lab = labels[i] if i < len(labels) else None
        if lab in ("port", "dead") or l.lstrip().startswith("#"):
            out.append(l)
            continue
        code = l
        drop = False
        for v in names:
            if re.match(r"^[ \t]*%s[ \t]*=[ \t]*0[ \t]*;[ \t]*(?:/\*.*\*/)?[ \t]*$" % re.escape(v), code):
                drop = True
                break
            if re.match(r"^[ \t]*(?:[A-Za-z_]\w*[ \t]+)+\**%s[ \t]*;" % re.escape(v), code):
                continue                              # the (now plain) declaration stays
            new = re.sub(r"(?<![.>\w])\b%s\b" % re.escape(v), "0", code)
            if new != code and folded:
                new = fold(new)
            code = new
        if not drop:
            out.append(code)
    return "\n".join(out)


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    zs = zeros(text)
    sets = ([zs] if len(zs) > 1 else []) + [[z] for z in zs]
    out, seen = [], {text}
    for sel in sets:
        for tag, folded in (("fold", True), ("literal", False)):
            cand = rewrite(text, sel, folded)
            if not cand or cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                continue
            seen.add(cand)
            out.append(("%s:%s" % ("+".join(sel), tag), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t114_zeroreg"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not zeros(text):
            return "no `register ... ASM_REG(\"$0\")` local"
        if not candidates(text):
            return "no rewrite removes a pin"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        menu = candidates(text)
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
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
