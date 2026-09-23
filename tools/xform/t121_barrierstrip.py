"""T121: scheduling barriers stripped - one-trip `do { } while (0)` blocks and `ASM_SCHED_BARRIER()` pins, all at
once and one at a time.  Mainly the A side of a composition probe (tools/lanes/compose2.py --A t121_barrierstrip):
the generator set run on the STRIPPED text.

APPEARS     dungeon/func_800A6A78 (claude-opus-5-5, work/native_lane/r76_opus_b37_1): "erasing [pin 3] AND deleting the
            two existing `do { } while (0);` wrappers around `right_u -= 1` / the `unk_0D` store gives the retail
            colours (distance 4) ... in the pinned text that dependence comes from the do-while loop notes (sched.c:
            a LOOP_BEG/END note flushes the pending memory lists)".  dungeon/func_809815A8 (r76o_opus_b37): the
            pre-existing `do { return; } while (0)` is load-bearing - so every strip is scored, never assumed.
MECHANISM   a one-trip do-while emits NOTE_INSN_LOOP_BEG/END; gcc 2.x sched.c treats a loop note like an asm
            (reg_pending_sets_all), a full dependency cut.  A barrier can hide the register shape a generator
            needs (the right colours appear only with the barrier gone), so a generator run on the pinned text
            refuses what it would find on the stripped one.
CANDIDATES  every `do {` ... `} while (0);` block rewritten as a plain `{ ... }` block (scope kept, no loop notes) and
            every ASM_SCHED_BARRIER pin erased: all barriers of the function at once, then each alone.  Ranked by
            listing distance; listing-exact candidates that remove a pin site go to `vf` (standalone use).
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import screen

MAX_SINGLE = 12
MAX_VERIFY = 3
DO_OPEN = re.compile(r"\bdo[ \t]*\{")
WHILE0 = re.compile(r"\}[ \t]*while[ \t]*\([ \t]*0[ \t]*\)[ \t]*;")


def one_trip_blocks(text):
    """[(do_start, do_end, close_start, close_end)] of `do { .. } while (0);` blocks inside function bodies."""
    masked = mask_comments(text)
    out = []
    for _f, _p, b0, b1 in functions(text):
        for m in DO_OPEN.finditer(masked, b0, b1):
            depth, i = 1, m.end()
            while i < b1 and depth:
                c = masked[i]
                depth += (c == "{") - (c == "}")
                i += 1
            if depth:
                continue
            w = WHILE0.match(masked, i - 1)
            if w:
                out.append((m.start(), m.end(), w.start(), w.end()))
    return out


def barriers(text):
    """[('dowhile', span4) | ('pin', site)] in source order."""
    out = [("dowhile", b) for b in one_trip_blocks(text)]
    out += [("pin", s) for s in sites_of(text) if s[0] != "expand" and "SCHED_BARRIER" in text[s[3]:s[4]]]
    return sorted(out, key=lambda x: x[1][0] if x[0] == "dowhile" else x[1][3])


def strip(text, chosen):
    """The chosen barriers removed: do-while blocks become plain blocks (from the bottom up), then the pins."""
    t = text
    edits = []
    for kind, b in chosen:
        if kind == "dowhile":
            edits += [(b[0], b[1], "{"), (b[2], b[3], "}")]
    for a, z, rep in sorted(edits, key=lambda e: -e[0]):       # every edit bottom-up: nested blocks stay valid
        t = t[:a] + rep + t[z:]
    pins = [c[1] for c in chosen if c[0] == "pin"]
    if pins:
        keys = {(p[1], p[2], p[5]) for p in pins}
        # the do-while rewrite keeps every line, so a pin's (kind, name, line) still names it
        t = erase_many(t, [p for p in sites_of(t) if (p[1], p[2], p[5]) in keys], clean_notes=True)
    return t


def candidates(text):
    sig = unscored_text(text)
    bs = barriers(text)
    out, seen = [], {text}
    plans = [("all", bs)] if bs else []
    if len(bs) > 1:
        plans += [("one@%d" % i, [b]) for i, b in enumerate(bs[:MAX_SINGLE])]
    for label, ch in plans:
        t = strip(text, ch)
        if t in seen or unscored_text(t) != sig:
            continue
        seen.add(t)
        out.append((label, t))
    return out


class T:
    name = "t121_barrierstrip"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not barriers(text):
            return "no one-trip do-while block or ASM_SCHED_BARRIER"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        ranked = []
        for label, cand in candidates(text):
            lst = screen.compile_s(row, cand)
            if lst is None:
                continue
            ranked.append((screen.sdiff(target, lst), len(sites_of(cand)), label, cand))
        ranked.sort(key=lambda x: (x[0], x[1]))
        info["nearest"] = [{"distance": d, "pins": p, "label": l} for d, p, l, _c in ranked[:6]]
        tried = 0
        for d, pins, label, cand in ranked:
            if d or pins >= pins_in or tried >= MAX_VERIFY:
                continue
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d0" % label, pins_out=pins, tried=tried)
        return None, dict(info, tried=tried)
