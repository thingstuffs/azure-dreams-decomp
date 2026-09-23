"""T106: a pinned matching arm replaced by its NON_MATCHING arm, the arm's raw asm spelled as the pin macros
it stands for, and the file-scope `register ... ASM_REG` block only the old arm used dropped with it.

APPEARS     a function whose body is split `#ifndef NON_MATCHING <pinned C> #else <natural C> #endif` (or the
            `#ifdef NON_MATCHING` polarity), often beside a FILE-SCOPE global register variable that
            only the matching arm uses (main/func_80012848, claude-opus-5-5 lane
            work/native_lane/r73_opus_s2):

                #ifndef NON_MATCHING
                register u8 *data_ptr ASM_REG("$2");        <- file scope, a pin
                #endif
                void func_80025848(void *state) {
                #ifndef NON_MATCHING
                    data_ptr = (u8 *)0x80080000; ... data_ptr += 0x3E98; ... (a page run through $2)
                #else
                    ... if (D_80083E98[table_index][0] != 0) { ... __asm__ __volatile__("" ::: "memory"); ...
                #endif
            ->  the matching arm becomes the NON_MATCHING arm's text with the raw barrier written
                `ASM_MEM_BARRIER();`, the file-scope block goes; the NON_MATCHING arm is unchanged.

RESOLVES    one pin on the exemplar (the global `ASM_REG("$2")`; the barrier stays as a pin).  The file-
            scope global register variable is the tree's third spelling of the round-73 "carrier in $2"
            shape: town/func_8032CE94 (astra, r73_astra_a2) and town/func_8032BD34 (gpt-6-luna,
            r73_luna6_s3) remove the same kind of block by rewriting the arm by hand.  A NON_MATCHING arm
            is the natural C an earlier pass set aside when it missed; later changes elsewhere (a recipe,
            a neighbour, a header) can make it exact.

WHY THE OWNER MISSES IT (measured 2026-09-23)
            t58_nmsymbol answers "no NON_MATCHING arm naming a symbol over a pinned arm" on both rows:
            it reads only the `#ifdef NON_MATCHING` polarity, arms of at most 8/10 lines, and a
            NON_MATCHING arm that assigns a `D_` symbol; it never spells the arm's raw asm as the pin
            macros, so a promoted arm holding `__asm__ __volatile__(...)` would carry an uncounted pin;
            and it cannot drop a file-scope register block.

CANDIDATES  per function-body NON_MATCHING split (T106_ANYARM: pinned or not), and all of them jointly:
            the promotion (raw asm -> ASM_MEM_BARRIER / ASM_SCHED_BARRIER / ASM_KEEP / ASM_KEEP_NV /
            ASM_CLOBBER, `asm("$n")` in a declaration -> ASM_REG("$n"); any other raw asm refuses the
            block), each orphaned file-scope `#ifndef NON_MATCHING` register block dropped; then with the
            pins on locals nothing else reads erased, then with every pin of the promoted arms erased.
            Ranked by the cc1 listing distance to the pinned text; listing-exact candidates (and the two
            nearest) go to `vf`.  The NON_MATCHING arms are never edited.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t58_nmsymbol import unused_pins
    from . import screen
except ImportError:
    from t58_nmsymbol import unused_pins
    import screen

MAX_LISTINGS = 40
MAX_BLOCKS = 12
# T106_ANYARM (harvest 3, 2026-09-23; default on): a split whose matching arm holds NO pin is promoted too - the
# pin can be the FILE-SCOPE `#ifndef NON_MATCHING register ... ASM_REG` block the arm alone reads
# (dungeon/func_819AE2AC, claude-opus-5-5 lane r73_opus_s22: "APPEARS: a row with `#ifndef NON_MATCHING` pin arms
# whose `#else` arm is plain C. RESOLVES: compile the `#else` arm as the scored arm first").  The first version
# refused it "no pin in a matching arm".  Off: T106_ANYARM=0.
import os as _os
ANYARM = _os.environ.get("T106_ANYARM", "1") != "0"
MAX_VERIFY = 4
PP = re.compile(r"^[ \t]*#[ \t]*(?P<d>if|ifdef|ifndef|elif|else|endif)\b(?P<rest>[^\n]*)$")
NM_OPEN = re.compile(r"^[ \t]*#[ \t]*(?:(?P<pos>ifdef[ \t]+NON_MATCHING|if[ \t]+defined[ \t]*\(?[ \t]*NON_MATCHING[ \t]*\)?)"
                     r"|(?P<neg>ifndef[ \t]+NON_MATCHING|if[ \t]*![ \t]*defined[ \t]*\(?[ \t]*NON_MATCHING[ \t]*\)?))[ \t]*(?:/\*.*\*/|//.*)?$")
RAW = [
    (re.compile(r"__asm__[ \t]+__volatile__[ \t]*\([ \t]*\"\"[ \t]*:[ \t]*:?[ \t]*:[ \t]*\"memory\"[ \t]*\)"), "ASM_MEM_BARRIER()"),
    (re.compile(r"__asm__[ \t]+__volatile__[ \t]*\([ \t]*\"\"[ \t]*\)"), "ASM_SCHED_BARRIER()"),
    (re.compile(r"__asm__[ \t]+__volatile__[ \t]*\([ \t]*\"\"[ \t]*:[ \t]*\"=r\"[ \t]*\([ \t]*(?P<v>\w+)[ \t]*\)[ \t]*:[ \t]*\"0\"[ \t]*\([ \t]*(?P=v)[ \t]*\)[ \t]*\)"), "ASM_KEEP(\\g<v>)"),
    (re.compile(r"__asm__[ \t]*\([ \t]*\"\"[ \t]*:[ \t]*\"=r\"[ \t]*\([ \t]*(?P<v>\w+)[ \t]*\)[ \t]*:[ \t]*\"0\"[ \t]*\([ \t]*(?P=v)[ \t]*\)[ \t]*\)"), "ASM_KEEP_NV(\\g<v>)"),
    (re.compile(r"__asm__[ \t]+__volatile__[ \t]*\([ \t]*\"\"[ \t]*:[ \t]*:[ \t]*:[ \t]*(?P<r>\"\$\w+\")[ \t]*\)"), "ASM_CLOBBER(\\g<r>)"),
    (re.compile(r"\b(?:__asm__|asm)[ \t]*\([ \t]*(?P<r>\"\$\w+\")[ \t]*\)"), "ASM_REG(\\g<r>)"),
]
ANY_ASM = re.compile(r"\b(?:__asm__|asm)\b")


def blocks(text):
    """[(kind, m0, m1, nm_text)] per NON_MATCHING split: `kind` 'body' (inside braces) or 'file';
    m0..m1 the character span of the MATCHING arm (for 'file' blocks without #else: the whole block)."""
    lines = text.split("\n")
    starts, at = [], 0
    for l in lines:
        starts.append(at); at += len(l) + 1
    depth_at, depth = [], 0
    for l in lines:
        depth_at.append(depth)
        code = re.sub(r"/\*.*?\*/|//.*$|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'", "", l)
        depth += code.count("{") - code.count("}")
    out, i = [], 0
    while i < len(lines):
        m = NM_OPEN.match(lines[i])
        if not m:
            i += 1
            continue
        nest, j, els = 0, i + 1, None
        while j < len(lines):
            p = PP.match(lines[j])
            if p:
                if p.group("d") in ("if", "ifdef", "ifndef"):
                    nest += 1
                elif p.group("d") == "endif":
                    if nest == 0:
                        break
                    nest -= 1
                elif p.group("d") == "else" and nest == 0:
                    els = j
                elif p.group("d") == "elif" and nest == 0:
                    els = -1
            j += 1
        if j >= len(lines) or els == -1:
            i += 1
            continue
        kind = "body" if depth_at[i] > 0 else "file"
        neg = bool(m.group("neg"))
        if els is None:
            if kind == "file" and neg:
                out.append(("file", starts[i], starts[j + 1] if j + 1 < len(lines) else len(text), None))
            i = j + 1
            continue
        if neg:
            ma, mb, na, nb = i + 1, els, els + 1, j
        else:
            na, nb, ma, mb = i + 1, els, els + 1, j
        nm = "\n".join(lines[na:nb]) + ("\n" if nb > na else "")
        if kind == "body":
            out.append(("body", starts[ma], starts[mb], nm))
        i = j + 1
    return out


def spell(nm):
    """The NON_MATCHING arm's text with its raw asm spelled as the pin macros, or None (unknown asm)."""
    for rx, rep in RAW:
        nm = rx.sub(rep, nm)
    code = re.sub(r"/\*.*?\*/|//[^\n]*", "", nm, flags=re.S)
    return None if ANY_ASM.search(code) else nm


def promote(text, chosen):
    """The chosen matching arms replaced (last first); then orphaned file-scope register blocks dropped."""
    for kind, a, b, nm in sorted(chosen, key=lambda x: -x[1]):
        text = text[:a] + spell(nm) + text[b:]
    for kind, a, b, _ in sorted((x for x in blocks(text) if x[0] == "file"), key=lambda x: -x[1]):
        body = text[a:b]
        decls = re.findall(r"^[ \t]*register[^;\n]*?\b([A-Za-z_]\w*)[ \t]*ASM_REG\([^)]*\)[ \t]*;", body, re.M)
        rest = re.sub(r"^[ \t]*#[^\n]*\n|/\*.*?\*/|^[ \t]*register[^;\n]*ASM_REG\([^)]*\)[ \t]*;[^\n]*\n|^[ \t]*\n", "",
                      body, flags=re.M | re.S)
        if not decls or rest.strip():
            continue
        others = text[:a] + text[b:]
        if any(re.search(r"\b%s\b" % re.escape(v), others) for v in decls):
            continue
        text = text[:a] + text[b:]
    return text


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    bs = [b for b in blocks(text) if b[0] == "body" and spell(b[3]) is not None
          and (ANYARM or any(b[1] <= s[3] < b[2] for s in sites_of(text)))]
    if len(bs) > MAX_BLOCKS:
        bs = bs[:MAX_BLOCKS]
    sets = ([bs] if len(bs) > 1 else []) + [[b] for b in bs]
    out, seen = [], {text}
    for sel in sets:
        base = promote(text, sel)
        if base in seen:
            continue
        forms = [("nm", base), ("nm+unused", erase_many(base, unused_pins(base), clean_notes=True))]
        forms.append(("nm+all", erase_many(base, sites_of(base), clean_notes=True)))
        for tag, cand in forms:
            if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
                continue
            seen.add(cand)
            out.append(("%s:%d" % (tag, len(sel)), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t106_nmpromote"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        bs = [b for b in blocks(text) if b[0] == "body"]
        if not bs:
            return "no NON_MATCHING split inside a function"
        if not ANYARM and not any(b[1] <= s[3] < b[2] for b in bs for s in sites_of(text)):
            return "no pin in a matching arm"
        if not candidates(text):
            return "no promotion removes a pin"
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
