"""T104: EVERY page local of a function respelled as symbols at once - the unpinned ones too - with a
page's struct-field access folded into the field's own symbol, and the pins in the run erased jointly.

APPEARS     two or more locals assigned an address literal in one statement run, only SOME of them
            pinned (town/func_80092AB0, claude-opus-5-5 lane work/native_lane/r73_opus_s1, 2 pins):

                handler_page = (u8 *)0x80090000;
                ASM_KEEP(handler_page);
                callback_page = (u8 *)0x800D0000;                      <- no pin names it
                callback = ((S_80090210_2 *)callback_page)->unk_438.s;
                ASM_SCHED_BARRIER();
                ((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_14 = (M2C_UNK *)(handler_page + 0x7D54);
                ...
                ((S_80090210_2 *)callback_page)->unk_438.u = 0;
            ->  callback = (M2C_UNK (*)())D_800D0438;
                ((S_80090210_0 *)((u8 *)handler_state - 0x10))->unk_14 = (M2C_UNK *)&D_80097D54;
                ...
                D_800D0438 = 0;

RESOLVES    the lane's rule (r73_opus_s1/REPORT.md, func_80092AB0): "APPEARS: `p = (T *)0x80XX0000;
            ASM_KEEP(p); ... p + off` or `((S *)page)->field` where page+off is a declared `D_` symbol.
            RESOLVES: replace every page+offset in the same statement run with the symbol (the t86
            rule applied to all pages in the run, not just the kept one)."  Measured by the lane:
            symbolising ONE page leaves listing distance 4.  The unpinned page is a second integer
            constant cse can share a `lui` with; while it stays an integer the pinned page's
            HIGH/LO_SUM pair is still merged with it, so the barrier and the keep both stay needed.

WHY THE OWNERS MISS IT (measured 2026-09-23, work/native_lane/r73_h_probe_t86_symaddr_o and _t59_)
            t29_addrsym's `addrvars` admits only a PINNED page (`literal-def-not-pinned` for
            callback_page), so its joint `addrsym:*a+b` candidate never forms; its rewrite of a
            struct view names the PAGE symbol (`((S *)D_800D0000)->unk_438`), not the field's.
            t86_symaddr's best (`handler_page:defsym/one88`) is listing distance 1 for the same
            reason, and t59 refuses `no-keep-of-the-page-within-8-lines`.

CANDIDATES  per function: t29's `rewrite_var` applied to the pinned page locals AND every unpinned
            literal-page local, jointly (all of them, then the pinned ones plus each unpinned one);
            each text in up to four field spellings of `((S *)D_PAGE)->unk_K R` (as t29 writes it, a
            `__typeof__` dereference of the field symbol, the field symbol through a byte pointer, and
            - when the file declares the field symbol as a scalar - the bare symbol with a cast on a
            read); each with no further erasure, with the pins between the first and last edited
            lines erased, and with every pin erased.  Screened by the cc1 listing against the pinned
            text's; the listing-exact candidates and the two nearest go to `vf`.
"""
import difflib
import itertools
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from . import t29_addrsym as A
    from . import screen
except ImportError:
    import t29_addrsym as A
    import screen

MAX_TEXTS = 60
MAX_LISTINGS = 60
MAX_VERIFY = 4
FIELD = re.compile(r"\(\s*\(\s*(?P<s>[A-Za-z_]\w*)\s*\*\s*\)\s*\(?\s*(?P<p>D_(?P<a>[0-9A-Fa-f]{8}))\s*\)?\s*\)"
                   r"\s*->\s*unk_(?P<k>[0-9A-Fa-f]+)(?P<r>(?:\s*\.\s*[A-Za-z_]\w*)*)")
SCALAR_TY = re.compile(r"^(?:u8|s8|u16|s16|u32|s32|int|long|M2C_UNK)$")


def page_vars(text):
    """(pinned, unpinned) locals assigned an address literal."""
    masked = A.mask_comments(text)
    names = sorted({m.group(1) for m in re.finditer(r"\(?\b([A-Za-z_]\w*)\)?\s*=\s*%s\s*;" % A._lit(), masked)})
    pinned = set(A.addrvars(text))
    return [n for n in names if n in pinned], [n for n in names if n not in pinned]


def _is_write(text, end):
    rest = text[end:end + 4].lstrip()
    return rest.startswith("=") and not rest.startswith("==")


def fold_fields(text, form):
    """`((S *)D_PAGE)->unk_K R` respelled at the field's own address, in one of the forms."""
    out, pos, n = [], 0, 0
    ext = set()
    for m in FIELD.finditer(text):
        addr = int(m.group("a"), 16) + int(m.group("k"), 16)
        sym = "D_%08X" % addr
        decl = A.sym_decl(text, sym)
        field = "((%s *)0)->unk_%s%s" % (m.group("s"), m.group("k"), re.sub(r"\s+", "", m.group("r")))
        if form == "typeof":
            if decl is None:
                ext.add("extern u8 %s[];\n" % sym)
            rep = "(*(__typeof__(%s) *)&%s)" % (field, sym)
        elif form == "bytes":
            if decl is None:
                ext.add("extern u8 %s[];\n" % sym)
            rep = "((%s *)((u8 *)&%s - 0x%s))->unk_%s%s" % (m.group("s"), sym, m.group("k"), m.group("k"), m.group("r"))
        elif form == "bare":
            if decl is None or decl[1] or not SCALAR_TY.match(decl[0]):
                return None
            rep = sym if _is_write(text, m.end()) else "((__typeof__(%s))%s)" % (field, sym)
        else:
            return None
        out.append(text[pos:m.start()]); out.append(rep); pos = m.end(); n += 1
    if not n:
        return None
    new = "".join(out) + text[pos:]
    # a page symbol t29 declared for the view and nothing else names any more goes with it
    for d in re.findall(r"^extern u8 (D_[0-9A-Fa-f]{8})\[\];\n", new, re.M):
        if len(re.findall(r"\b%s\b" % d, new)) == 1:
            new = new.replace("extern u8 %s[];\n" % d, "", 1)
    if ext:
        at = new.find("\n", max(new.rfind("\nextern "), 0) + 1) + 1 if "\nextern " in new else 0
        new = new[:at] + "".join(sorted(ext)) + new[at:]
    return new


def joint_texts(text):
    """[(label, text, edited line span)] - the page locals rewritten together."""
    pinned, free = page_vars(text)
    if not pinned or not free:
        return []
    sets = [pinned + free] + [pinned + [f] for f in free if len(free) > 1]
    out, seen = [], set()
    for vs in sets:
        cur, used = text, []
        for v in vs:
            new, info = A.rewrite_var(cur, v)
            if new is not None:
                cur, used = new, used + [v]
        if not any(v in free for v in used) or cur in seen:
            continue
        seen.add(cur)
        out.append(("+".join(used), cur))
    return out


def _edited_lines(a, b):
    """0-based line numbers of `b` that differ from `a`."""
    out = set()
    sm = difflib.SequenceMatcher(None, a.split("\n"), b.split("\n"), autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag != "equal":
            out.update(range(j1, max(j2, j1 + 1)))
    return out


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    for label, jt in joint_texts(text):
        forms = [("page", jt)] + [(f, fold_fields(jt, f)) for f in ("typeof", "bare", "bytes")]
        for ftag, ft in forms:
            if ft is None:
                continue
            fl = ft.split("\n")
            lines = sorted(k for k in _edited_lines(text, ft)
                           if k < len(fl) and not fl[k].lstrip().startswith("extern "))
            pins = sites_of(ft)
            win = [s for s in pins if lines and lines[0] - 1 <= s[5] - 1 <= lines[-1] + 1]
            for ptag, group in (("none", []), ("win", win), ("all", pins)):
                if ptag != "none" and not group:
                    continue
                cand = erase_many(ft, group, clean_notes=True) if group else ft
                if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                    continue
                seen.add(cand)
                out.append(("%s:%s:%s" % (label, ftag, ptag), cand))
                if len(out) >= MAX_TEXTS:
                    return out
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t104_pagejoint"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        pinned, free = page_vars(text)
        if not pinned:
            return "no pinned page local"
        if not free:
            return "no unpinned page local beside the pinned one"
        if not joint_texts(text):
            return "no joint rewrite"
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
