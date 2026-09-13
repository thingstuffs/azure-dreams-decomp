"""T58: a pinned matching arm replaced by the NON_MATCHING arm that already names the symbol.

APPEARS     a preprocessor split whose NON_MATCHING arm assigns a symbol and whose matching arm builds the
            same pointer by hand under a pin:
                #ifdef NON_MATCHING
                    tail_sprite = D_80174C64;
                #else
                    ASM_KEEP(tail_state);
                    tail_sprite = (u8 *)tail_state + 0x4C64;
                #endif
RESOLVES    the fences25 lane (round 21, `dungeon/func_8132B8AC`): with the fence above gone, the symbol
            the NON_MATCHING arm names is exact in the matching build; the page local and its keep go.
            A NON_MATCHING arm was written as the natural C and set aside when it missed; other changes
            since (a fence removed, a cell switched, a neighbour rewritten) can make it exact.
POPULATION  2026-09-13: 21 NON_MATCHING arms naming a symbol over a pinned matching arm, in 15 rows.
RESULT      2026-09-13: 0 of 14 eligible rows. The first version deleted the NON_MATCHING arm and every
            candidate died on the sweep's unscored-arm check; the arm is now kept and copied into the
            matching arm, and still none is exact alone. The fences25 win also needed the fence above
            removed and a temporary inlined: a NON_MATCHING arm is evidence, not a lever by itself.
Each block collapsed to its NON_MATCHING arm alone, then all jointly; then the pins naming a local the
collapse left unused (a page and its keep), then every pin still standing once on its own. Only `vf`
accepts; the unscored-arm check is the sweep's own.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many

BLOCK = re.compile(r"^[ \t]*#[ \t]*ifdef[ \t]+NON_MATCHING[^\n]*\n(?P<nm>(?:(?![ \t]*#[ \t]*(?:else|endif|if)).*\n){1,8})"
                   r"[ \t]*#[ \t]*else[^\n]*\n(?P<m>(?:(?![ \t]*#[ \t]*(?:endif|if|else)).*\n){1,10})[ \t]*#[ \t]*endif[^\n]*\n", re.M)
SYM = re.compile(r"\b\w+\s*=\s*(?:\([^)]*\)\s*)?&?\s*D_[0-9A-Fa-f]{8}\b")


def find(text):
    """[(m_start, m_end, nm_text)] for each NON_MATCHING/else block whose NON_MATCHING arm assigns a symbol
    and whose matching arm holds a pin: the span is the MATCHING arm's body."""
    return [(m.start("m"), m.end("m"), m.group("nm")) for m in BLOCK.finditer(text)
            if SYM.search(m.group("nm")) and "ASM_" in m.group("m")]


def collapse(text, blocks):
    """The matching arm's body becomes a copy of the NON_MATCHING arm's; the NON_MATCHING arm itself is left
    as it is (the sweep refuses any change to an unscored arm), as the fences25 lane wrote it."""
    for s, e, nm in sorted(blocks, reverse=True):
        text = text[:s] + nm + text[e:]
    return text


def unused_pins(text):
    """Pins on locals that nothing but pins and their own assignments mention any more."""
    out = []
    code = re.sub(r"/\*.*?\*/", "", text, flags=re.S)
    for s in sites_of(text):
        if not s[1].startswith("ASM_KEEP"):
            continue
        v = re.match(r"\s*(\w+)", s[2])
        if not v:
            continue
        uses = [l for l in code.splitlines() if re.search(r"\b%s\b" % re.escape(v.group(1)), l)
                and not re.match(r"\s*(?:ASM_\w+\(|(?:[\w\s\*]+\s)?%s\s*=[^=])" % re.escape(v.group(1)), l)
                and not re.match(r"\s*(?:register\s+)?[\w\s\*]+\b%s\s*;" % re.escape(v.group(1)), l)]
        if not uses:
            out.append(s)
    return out


class T:
    name = "t58_nmsymbol"
    level = 1
    needs_verify = True
    BUDGET = 24

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        return None if find(text) else "no NON_MATCHING arm naming a symbol over a pinned arm"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in, blocks, tried = len(sites_of(text)), find(text), 0
        trials = ([blocks] if len(blocks) > 1 else []) + [[b] for b in reversed(blocks)]
        cur, steps = text, []
        for chosen in trials:
            live = [b for b in find(cur) if any(b[2] == c[2] for c in chosen)]
            if not live or tried >= cls.BUDGET:
                continue
            base = collapse(cur, live)
            for cand, tag in ((erase_many(base, unused_pins(base), clean_notes=True), "+unpin"), (base, "")):
                if len(sites_of(cand)) >= len(sites_of(cur)) or tried >= cls.BUDGET:
                    continue
                tried += 1
                if vf(cand).get("exact"):
                    cur = cand
                    steps.append("nm%d%s" % (len(live), tag))
                    break
            if steps and len(live) == len(blocks):
                break
        if not steps:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in, "blocks": len(blocks)}
        i = 0
        while tried < cls.BUDGET:
            live = sites_of(cur)
            if i >= len(live):
                break
            cand = erase_many(cur, [live[i]], clean_notes=True)
            tried += 1
            if vf(cand).get("exact"):
                cur = cand
                steps.append("dead:" + live[i][1])
            else:
                i += 1
        return cur, {"step": "+".join(steps), "tried": tried, "pins_in": pins_in,
                     "pins_out": len(sites_of(cur)), "blocks": len(blocks)}
