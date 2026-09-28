"""slots.py - D_80083120 onto shared/transition_slots.h (TransitionSlot[8]); members renamed only on D_80083120[..]
   and on locals declared TransitionSlot *."""
import re
HDR = '#include "shared/transition_slots.h"'
MEM = {"field0": "type", "field_0": "type", "field2": "unk_2", "field_2": "unk_2", "field4": "param", "field_4": "param", "field6": "unk_6", "field_6": "unk_6"}
def rewrite(t):
    o = t
    if re.search(r"^extern (S_80083120|u8) D_80083120\[\d*\];", t, re.M):
        t = re.sub(r"typedef struct S_80083120\s*\{[^}]*\}\s*S_80083120;\s*\n", "", t)
        t = re.sub(r"^extern (S_80083120|u8) D_80083120\[\d*\];\s*\n", "", t, flags=re.M)
        t = re.sub(r"\bS_80083120\b", "TransitionSlot", t)
        t = t.replace("u8 *entry_table = D_80083120;", "u8 *entry_table = (u8 *)D_80083120;")
        m = re.search(r'^#include "common.h"[^\n]*\n', t, re.M)
        if not m: return None, "no common.h include"
        t = t[:m.end()] + HDR + "\n" + t[m.end():]
    elif '#include "slus/slot_transition.h"' not in t:
        return None, "no local declaration"
    t = re.sub(r"(D_80083120\[[^\]]*\]\.)(field_?[0246])\b", lambda m: m.group(1) + MEM[m.group(2)], t)
    for v in re.findall(r"TransitionSlot\s*\*\s*(\w+)\s*[;=,)]", t):
        t = re.sub(r"\b(%s->)(field_?[0246])\b" % v, lambda m: m.group(1) + MEM[m.group(2)], t)
    return t, "slots"
