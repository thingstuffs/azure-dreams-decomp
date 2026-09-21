"""T90c: an arithmetic right shift respelled as a logical one, where every consumer masks low bits.

APPEARS     a pinned local set from a signed right shift whose value is only ever read through a
            small mask (dungeon/func_809F4F90, the round-64 astra lane work/native_lane/r64_astra_bivhide):

                register s32 heading_byte ASM_REG("$19");   <- the pin
                s32 heading_raw;
                ...
                heading_raw = ((S_80172790_0 *)actor)->unk_2A.s;
                heading_byte = heading_raw >> 8;
                direction_offset = heading_byte & 0xE;      <- the only read of this value

RESOLVES    dungeon/func_809F4F90 byte-exact: `heading_byte = (u32)heading_raw >> 8;` and the
            `ASM_REG("$19")` binding gone.  Mechanism: gcc 2.x expands a signed `>>` as `ashiftrt`
            and an unsigned one as `lshiftrt`, which on MIPS are `sra` and `srl`.  The two cost the
            same, but they are different RTL, so combine.c folds them differently against the mask
            that follows - `(sra x 8) & 0xE` keeps two insns while `(lshiftrt x 8) & 0xE` is the
            shift-and-mask pair retail emits - and the value's live range and register class change
            with it, which is the decision the hard-register binding was standing in for.
            SAFETY: the two spellings agree exactly when every read masks bits strictly below the
            sign-extended ones.  `(x >> k) & C` reads bits k..k+log2(C) of `x`, and an arithmetic
            shift only differs from a logical one in the TOP k bits of the result, so the rewrite is
            value-identical whenever `C < 1 << (32 - k)`.  That inequality is checked per read, and a
            read that is not a plain mask refuses the whole definition.
WHY THE ANCESTORS MISS IT
            t35_shiftspell and t88_castshift flip a power-of-two scale between `*` and `<<` - they
            change the OPERATOR, never the signedness of the operand, and neither has a value-range
            argument that would let it.  t37_localwidth and t84_narrowparams retype a declaration,
            which changes the width of every use of the variable, not the one shift.
            t39_signbit rewrites a sign TEST, not a shift.
CANDIDATES  per definition `v = X >> k;` (k a positive literal) whose reaching-definition web's every
            read is `v & C` with `C < 1 << (32 - k)`: the shifted operand cast to `u32` (and, where
            it is a bare name, the `unsigned` spelling as a second candidate).  Each is screened with
            the pins erased - the definition's window, then every single pin of the row, then all of
            them - by the cc1 listing against the pinned text, and only listing-exact texts reach
            `vf`.
            Refused: an operand that is already unsigned in its declaration, a shift by a name rather
            than a literal, a definition on an `unknown` or preprocessor CFG node, a web with a read
            that is not a plain mask, a `v` that is address-taken, volatile, const, static, an array
            or a multi-declarator, and any rewrite that changes the text of a surviving pin.
"""
import difflib
import os
import re
import sys
from collections import Counter
from pathlib import Path

ROOT = next(p for p in Path(__file__).resolve().parents if (p / "tools/common.py").is_file())
if str(ROOT / "tools") not in sys.path:
    sys.path.insert(0, str(ROOT / "tools"))

from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
from xform import varset as V
from xform import screen

MAX_CANDS = 16
MAX_LISTINGS = 160
MAX_VERIFY = 6
ID = r"[A-Za-z_]\w*"
UNSIGNED = ("u8", "u16", "u32", "unsigned", "az_uptr", "size_t")
SHIFT_RE = re.compile(r"^[ \t]*(?P<v>%s)\s*=\s*(?P<x>[^;]*?)\s*>>\s*(?P<k>0[xX][0-9A-Fa-f]+|\d+)\s*;[ \t]*$" % ID)


def _mask_read(masked, v):
    """The constant of a `v & C` read on this line, or None when the line is not a plain mask read."""
    m = re.search(r"(?<![\w.])(?<!->)%s\s*&\s*(0[xX][0-9A-Fa-f]+|\d+)" % re.escape(v), masked)
    if not m:
        return None
    if len(re.findall(r"(?<![\w.])(?<!->)%s\b" % re.escape(v), masked)) != 1:
        return None
    return int(m.group(1), 0)


def _operand_ok(fn, x):
    """The shifted operand is a value this module may cast: a name, a field read or a parenthesised
    expression, and not already unsigned where the function declares it."""
    x = x.strip()
    if not x or x.endswith(("+", "-", "*", "/", "%", "&", "|", "^", "<", ">", "!", "~", "=")):
        return False
    if re.fullmatch(ID, x):
        d = fn.decls.get(x)
        if d and (d[0]["base"] in UNSIGNED or "unsigned" in d[0]["prefix"]):
            return False
        return True
    return bool(re.fullmatch(r"[\w\s().\[\]*>\-]+", x))


def _spell(x):
    """The operand written as the argument of a cast - parenthesised unless it is already a term."""
    x = x.strip()
    if re.fullmatch(ID, x) or re.fullmatch(r"\(.*\)", x):
        return x
    return "(%s)" % x


def candidates(text):
    """[(label, cand, window, must)] for every definition whose reads all mask low bits."""
    out, seen = [], set()
    sites = sites_of(text)
    for fn in V.functions(text, Counter()):
        if not [s for s in sites if fn.lo <= s[5] - 1 <= fn.hi]:
            continue
        locs = V.usable_locals(fn, Counter(), allow_register_pin=True)
        for v, d in sorted(locs.items()):
            kinds = fn.kinds(v)
            if not kinds or V._multi_occurrence(fn, v, kinds):
                continue
            for ds, us, back in V.webs(fn, v, kinds):
                if len(ds) != 1 or not us:
                    continue
                n = ds[0]
                node = fn.nodes[n]
                if node.kind != "stmt" or fn.pp[node.line]:
                    continue
                sm = SHIFT_RE.match(node.masked)
                if not sm or sm.group("v") != v:
                    continue
                k = int(sm.group("k"), 0)
                if not 0 < k < 32 or not _operand_ok(fn, sm.group("x")):
                    continue
                limit = 1 << (32 - k)
                ok = True
                for u in us:
                    if fn.pp[fn.nodes[u].line]:
                        ok = False
                        break
                    c = _mask_read(fn.nodes[u].masked, v)
                    if c is None or c >= limit:
                        ok = False
                        break
                if not ok:
                    continue
                real = fn.lines[node.line].rstrip("\n")
                x = real[sm.start("x"):sm.end("x")]
                for ty in ("u32", "unsigned"):
                    if ty == "unsigned" and not re.fullmatch(ID, x.strip()):
                        continue
                    new = real[:sm.start("x")] + "(%s)%s" % (ty, _spell(x)) + real[sm.end("x"):]
                    cand = "".join(fn.lines[:node.line]) + new + "\n" + "".join(fn.lines[node.line + 1:])
                    if cand == text or cand in seen:
                        continue
                    seen.add(cand)
                    out.append(("ushift:%s>>%d>%s@%d" % (v, k, ty, node.line + 1), cand,
                                (node.line, max(fn.nodes[u].line for u in us)), ()))
    return out[:MAX_CANDS]


def _plans(sites, rs, win):
    lo, hi = win[0] + 1, win[1] + 1
    req = [i for i, s in enumerate(rs) if lo <= s[5] <= hi]
    out = []
    if req:
        out.append(req)
    for i in range(len(rs)):
        g = sorted(set(req) | {i})
        if g not in out:
            out.append(g)
    allp = list(range(len(rs)))
    if allp and allp not in out:
        out.append(allp)
    return out


def _kept_ok(sites, cand):
    want = Counter((s[1], s[2]) for s in sites)
    got = Counter((s[1], s[2]) for s in sites_of(cand))
    return not (got - want)


class T:
    name = "t90_unsignedshift"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if candidates(text) else "no mask-only signed shift in a pinned function"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        sites = sites_of(text)
        pins_in = len(sites)
        target = screen.compile_s(row, text)
        if target is None:
            return None, {"refused": "pinned text does not build to a listing", "pins_in": pins_in,
                          "pins_out": pins_in}
        listings = verifies = 0
        best, near, rest, tried = None, None, [], 0
        for label, flipped, win, _must in candidates(text):
            if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                break
            tried += 1
            rs = sites_of(flipped)
            for g in _plans(sites, rs, win):
                if listings >= MAX_LISTINGS or verifies >= MAX_VERIFY:
                    break
                cand = erase_many(flipped, [rs[i] for i in g], clean_notes=True)
                if len(sites_of(cand)) >= pins_in or not _kept_ok(sites, cand):
                    continue
                lst = screen.compile_s(row, cand)
                listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                near = d if near is None else min(near, d)
                tag = "%s-erase%d" % (label, len(g))
                if d == 0:
                    verifies += 1
                    if vf(cand).get("exact"):
                        best = (cand, tag)
                        break
                else:
                    rest.append((d, len(rest), cand, tag))
            if best:
                break
        if best is None:
            rest.sort(key=lambda x: (x[0], x[1]))
            for d, _, cand, tag in [x for x in rest if x[0] <= 2][:int(os.environ.get("NEAR_VERIFY", "3"))]:
                if verifies >= MAX_VERIFY:
                    break
                verifies += 1
                if vf(cand).get("exact"):
                    best = (cand, tag)
                    break
        if best is None:
            return None, {"pins_in": pins_in, "pins_out": pins_in, "listings": listings,
                          "verifies": verifies, "nearest": near, "tried": tried}
        cand, tag = best
        return cand, {"pins_in": pins_in, "pins_out": len(sites_of(cand)), "move": tag,
                      "listings": listings, "verifies": verifies, "nearest": 0}
