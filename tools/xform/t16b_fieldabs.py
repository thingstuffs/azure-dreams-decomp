"""T16b: a field's absolute value staged through a temporary, written back as `field = abs(field);`.

APPEARS     m2c's staging of gcc's `abssi2` on a struct field or array element: the field is loaded
            into a local, the local is negated in place under `if (v < 0)`, and the local is stored
            back to the same field, often for two fields at once with a fence around the run:
                ASM_SCHED_BARRIER();
                x = actor->unk_72.as_s8;  y = actor->unk_73.as_s8;
                if (x < 0) { x = -x; }    if (y < 0) { y = -y; }
                actor->unk_72.as_s8 = x;  actor->unk_73.as_s8 = y;
RESOLVES    t16's reason (abs goes through expand_abs -> abssi2, which cse cannot see into), plus the
            staging: the temporaries let the scheduler move the second load ahead of the first store,
            which the fence was holding. `actor->unk_72.as_s8 = abs(actor->unk_72.as_s8);` computes
            and stores each field in turn. The fences18 lane found it (`dungeon/func_80E0F7C0`,
            round 19); t16 was eligible there but offers only `v = abs(v);`, keeping the staging.
POPULATION  2026-09-13: 12 load-negate-storeback sites in 6 pinned rows, every one with a fence.
RESULT      2026-09-13: reproduces the fences18 lane's `func_80E0F7C0` (identical assembly); swept over
            the other 5 census rows, 5 applied, one fence each. Its detector's 3 further rows
            (func_80A734C0, func_80A9D4E8, func_810860B4): noop.
Rewrite: every such idiom at once (the load and the `if` go, the store becomes `L = abs(L);`, a
temporary nothing else uses loses its declaration), with the pins inside the run erased (fences and
pins naming a temporary), then without erasing the fences; from an exact result, every pin still
standing is tried once on its own. Only `vf` accepts.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker
from pin_sites import erase_many
try:
    from .t12_stmtorder import mask
    from .t16_absidiom import idioms, with_abs_decl, names_var, BUDGET
except ImportError:
    from t12_stmtorder import mask
    from t16_absidiom import idioms, with_abs_decl, names_var, BUDGET

CAST = re.compile(r"^\(\s*(?:(?:un)?signed\s+)?(?:[su](?:8|16|32)|int|short|char|long)\s*\)\s*")
LVAL = re.compile(r"->|\.|\[|^\*|\(\s*\*")
FENCES = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")


def norm(e):
    return re.sub(r"\s+", "", CAST.sub("", e.strip()))


def stmt_span(masked, start, end):
    """Widen [start, end) to whole lines when the statement is alone on its line."""
    ls = masked.rfind("\n", 0, start) + 1
    le = masked.find("\n", end)
    le = len(masked) if le < 0 else le + 1
    if masked[ls:start].strip() == "" and masked[end:le].strip() == "":
        return ls, le
    return start, end


def find(text):
    """[{d, load: (s, e), neg: (s, e), store: (s, e), lv}] for each load-negate-storeback idiom."""
    masked = mask(text)
    out = []
    for it in idioms(text):
        d = it["d"]
        if it["t"] != d:
            continue
        loads = list(re.finditer(r"(?<![.>\w])\b%s\s*=\s*(?!=)([^;]+);" % re.escape(d), masked[:it["start"]]))
        if not loads:
            continue
        ld = loads[-1]
        rhs = ld.group(1)
        if not LVAL.search(CAST.sub("", rhs.strip())) or re.search(r"\w\s*\(", CAST.sub("", rhs.strip())):
            continue                               # a field, element or dereference, not a call
        st = re.compile(r"([^;{}]+?)\s*=\s*%s\s*;" % re.escape(d)).search(masked, it["end"])
        if not st or norm(st.group(1)) != norm(rhs):
            continue
        # between the load and the store, d appears only in its own negate
        mid = masked[ld.end():it["start"]] + masked[it["end"]:st.start()]
        if re.search(r"\b%s\b" % re.escape(d), mid):
            continue
        # the load and the store sit in the same block: brace depth never drops below it between them
        depth, low = 0, 0
        for ch in masked[ld.end():st.start()]:
            depth += (ch == "{") - (ch == "}")
            low = min(low, depth)
        if depth or low:
            continue
        # nothing between them writes the field
        if re.search(re.escape(st.group(1).strip()) + r"\s*=(?!=)", masked[ld.end():st.start()]):
            continue
        g = st.group(1)
        s0 = st.start(1) + len(g) - len(g.lstrip())    # the lvalue itself, not the whitespace before it
        out.append({"d": d, "load": (ld.start(), ld.end()), "neg": (it["start"], it["end"]),
                    "store": (s0, st.end()), "lv": text[s0:st.end(1)].strip()})
    return out


def rewrite(text, its, erase_fences):
    """All idioms rewritten; pins in the run erased (fences only if asked). Returns the new text."""
    pins = sites_of(text)
    lo, hi = min(i["load"][0] for i in its), max(i["store"][1] for i in its)
    names = {i["d"] for i in its}
    # the pin before the run (a fence right above the first load, its note comment masked) belongs to it
    masked0 = mask(text)
    prev = [s for s in pins if s[4] <= lo and masked0[s[4]:lo].strip(" \t\n;") == ""]
    run = [k for k, s in enumerate(pins) if (lo <= s[3] < hi or s in prev) and
           ((erase_fences and s[1] in FENCES) or names_var(s, names))]
    run += [k for k, s in enumerate(pins) if k not in run and s[1] not in FENCES and names_var(s, names)]
    masked = mask(text)
    edits = []
    for i in its:
        edits.append((*stmt_span(masked, *i["load"]), ""))
        edits.append((*stmt_span(masked, *i["neg"]), ""))
        s, e = i["store"]
        edits.append((s, e, "%s = abs(%s);" % (i["lv"], i["lv"])))
    # pins erase first, on the original offsets, by the same sites list order (rewrites add no pins)
    new = text
    for s, e, rep in sorted(edits, reverse=True):
        new = new[:s] + rep + new[e:]
    after = sites_of(new)
    if len(after) != len(pins):
        return None
    new = erase_many(new, [after[k] for k in sorted(set(run))], clean_notes=True)
    m2 = mask(new)
    for d in names:                                # a temporary nothing uses any more loses its declaration
        uses = [m.start() for m in re.finditer(r"(?<![.>\w])\b%s\b" % re.escape(d), m2)]
        decl = re.search(r"^[ \t]*(?:register\s+)?(?:(?:un)?signed\s+)?[A-Za-z_]\w*(?:\s+[A-Za-z_]\w*)?\s+%s\s*;[^\n]*\n" % re.escape(d), m2, re.M)
        if decl and len(uses) == 1 and decl.start() <= uses[0] < decl.end():
            new = new[:decl.start()] + new[decl.end():]
            m2 = mask(new)
    return with_abs_decl(new)


class T:
    name = "t16b_fieldabs"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no live pin site"
        why = asm_blocker(text)
        if why:
            return why
        return None if find(text) else "no load-negate-storeback idiom"

    @staticmethod
    def apply_verified(text, row, census, vf):
        pins_in, its, tried = len(sites_of(text)), find(text), 0
        cur, step = None, None
        for erase_fences in (True, False):
            if tried >= BUDGET:
                break
            cand = rewrite(text, its, erase_fences)
            if cand is None or len(sites_of(cand)) >= pins_in:
                continue
            tried += 1
            if vf(cand).get("exact"):
                cur, step = cand, "fieldabs:%s%s" % ("+".join(i["d"] for i in its), "+fences" if erase_fences else "")
                break
        if cur is None:
            return None, {"tried": tried, "pins_in": pins_in, "pins_out": pins_in, "idioms": len(its)}
        steps, i = [step], 0
        while tried < BUDGET:
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
                     "pins_out": len(sites_of(cur)), "idioms": len(its)}
