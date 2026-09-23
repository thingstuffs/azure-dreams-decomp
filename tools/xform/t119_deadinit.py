"""T119: a dead zero initializer at a local's declaration, added or removed - the set-exactly-once family, pure C.

APPEARS     a keep whose only job is to make a variable set twice:

                void *effect;                              void *effect = 0;
                ...                                   ->   ...
                effect = allocated_effect;                 <next statement>
                ASM_KEEP(allocated_effect);                effect = allocated_effect;
                <next statement>

            dungeon/func_809CAE20 (claude-opus-5-5, work/native_lane/r76_opus_b12_2): "`x = call(); y = x;
            ASM_KEEP(x); mem = x; if (y ...)` with a one-word residue `sw $s,..` vs `sw $v0,..`. RESOLVES: store
            before the copy and give `y` a life beyond the cse block" - byte-exact with a never-read `= 0` at y's
            declaration, admitted by the owner's 2026-09-23 ruling (docs/PIN_CAMPAIGN_CHARTER.md, "Ruling
            2026-09-23 - dead zero initializer"; each landing is a `dead_init` record in ledger/recipe_trades.jsonl,
            appended by tools/apply_candidates.py through tools/dead_init.py).
MECHANISM   an ASM_KEEP is an asm "+r" output: a SECOND set.  gcc 2.x gives a pseudo with REG_N_SETS == 1 two
            boosts - sched.c `birthing_insn_p` (the producer scheduled as a birth) and local-alloc.c
            `update_equiv_regs` (REG_EQUIV, live length doubled, global.c priority halved).  An initializer at
            the declaration is a set too (it emits a `li $r,0` that flow deletes as dead, or folds away), so
            `T v = 0;` switches both boosts off exactly as the keep did - and REMOVING an existing never-needed
            `= 0` switches them on, the other direction of the same lever (the round-76 opus rows: "the keeps
            only (a) make each parameter set twice (no doubling) and (b) add 2 refs").
WHY THE OWNERS MISS IT  no generator edits an initializer; t69/t85/t118 change sets in statements.
CANDIDATES  add    per pin naming a local v (a keep argument, a register-pinned declaration): v and the locals a
                   copy `w = v;` / `v = w;` within three lines of the pin links to it, each without an
                   initializer, get `= 0` at the declaration, the pin erased; each also with the adjacent copy
                   statement sunk past the next simple statement (the exemplar's move);
            remove per `T v = 0;` declaration in the function: the initializer dropped with the pins naming v
                   erased.
            Ranked by cc1 listing distance to the pinned text; listing-exact candidates (and the two nearest) go
            to `vf`.  Candidates that add pins or change the unscored text are dropped.
"""
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
import dead_init
try:
    from .t36_paramwidth import functions
    from . import screen
except ImportError:
    from t36_paramwidth import functions
    import screen

ID = r"[A-Za-z_]\w*"
MAX_MENU = 48
MAX_LISTINGS = 48
MAX_VERIFY = 4
COPY_WIN = 3
COPY = re.compile(r"^[ \t]*(?P<a>%s)[ \t]*=(?!=)[ \t]*(?:\([^()]*\)[ \t]*)?(?P<b>%s)[ \t]*;[ \t]*(?:/\*.*\*/)?[ \t]*$" % (ID, ID))
SIMPLE = re.compile(r"^[ \t]*[^;{}\n]*;[ \t]*(?:/\*.*\*/)?[ \t]*$")
PIN_LINE = re.compile(r"^[ \t]*ASM_\w+[ \t]*\(")
KEYW = re.compile(r"^[ \t]*(?:if|else|for|while|do|switch|case|default|return|goto|break|continue)\b|^[ \t]*%s[ \t]*:" % ID)


def _named_sites(text, v):
    return [s for s in sites_of(text) if s[0] != "expand" and re.search(r"\b%s\b" % re.escape(v), text[s[3]:s[4]])]


def _local_decls(text, fn):
    """{name: match} of the function's local declarations (dead_init.DECL), first declaration per name."""
    out = {}
    for m in dead_init.DECL.finditer(text, fn[2], fn[3]):
        if m.group("ty").split()[-1] in dead_init.NOT_TYPES:
            continue
        out.setdefault(m.group("v"), m)
    return out


def _with_init(text, m, on):
    """The declaration `m` with (on) or without (not on) a `= 0` initializer."""
    ln = m.group(0)
    if on:
        new = re.sub(r"[ \t]*;$", " = 0;", ln, count=1)
    else:
        new = re.sub(r"[ \t]*=[ \t]*%s[ \t]*;$" % dead_init.ZERO, ";", ln, count=1)
    return text[:m.start()] + new + text[m.end():]


def _sink_copy(text, line):
    """The single-line copy at 0-based `line` swapped with the next simple statement (pins/blank lines skipped)."""
    ls = text.split("\n")
    k = line + 1
    while k < len(ls) and (not ls[k].strip() or PIN_LINE.match(ls[k])):
        k += 1
    if k >= len(ls) or not SIMPLE.match(ls[k]) or KEYW.match(ls[k]) or PIN_LINE.match(ls[k]):
        return None
    cm = COPY.match(ls[line])
    a, b = cm.group("a"), cm.group("b")
    # the statement may read the copy's SOURCE, never its destination, and may write neither
    if re.search(r"(?<![\w.>])%s\b" % re.escape(a), ls[k]) or \
            re.search(r"(?<![\w.>])%s\s*(?:=(?!=)|\+\+|--|[-+*/%%&|^]=|<<=|>>=)|(?:\+\+|--)\s*%s\b" % (re.escape(b), re.escape(b)), ls[k]):
        return None
    ls[line], ls[k] = ls[k], ls[line]
    return "\n".join(ls)


def menu(text):
    """[(label, candidate text)]."""
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}

    def put(label, t):
        if t and t not in seen and unscored_text(t) == sig and len(sites_of(t)) < n0:
            seen.add(t)
            out.append((label, t))

    for fn in functions(text):
        decls = _local_decls(text, fn)
        lines = text.split("\n")
        l0, l1 = text.count("\n", 0, fn[2]), text.count("\n", 0, fn[3])
        # add: the pinned variable, or a copy linked to it near the pin
        for s in sites_of(text):
            if s[0] == "expand" or not (fn[2] <= s[3] < fn[3]):
                continue
            seg = text[s[3]:s[4]]
            names = [n for n in re.findall(ID, seg) if n in decls]
            sl = text.count("\n", 0, s[3])
            links = []
            for v in names:
                links.append((v, None))
                for q in range(max(l0, sl - COPY_WIN), min(l1, sl + COPY_WIN) + 1):
                    cm = COPY.match(lines[q])
                    if cm and v in (cm.group("a"), cm.group("b")):
                        w = cm.group("a") if cm.group("b") == v else cm.group("b")
                        if w in decls and w != v:
                            links.append((w, q))
            for w, q in links:
                m = decls[w]
                if m.group("init"):
                    continue
                t1 = erase_many(text, [s], clean_notes=True)
                # the erasure removed a line at most: find the declaration again by its text
                m2 = next((x for x in dead_init.DECL.finditer(t1) if x.group("v") == w and x.group(0) == m.group(0)), None)
                if m2 is None:
                    continue
                t2 = _with_init(t1, m2, True)
                put("add:%s@%d" % (w, sl + 1), t2)
                if q is not None:
                    # the copy line in t2: same text, nearest to its old place
                    ls2 = t2.split("\n")
                    cands = [i for i, x in enumerate(ls2) if x == lines[q]]
                    if cands:
                        qq = min(cands, key=lambda i: abs(i - q))
                        put("add:%s@%d:sink" % (w, sl + 1), _sink_copy(t2, qq))
                if len(out) >= MAX_MENU:
                    return out
        # remove: an existing zero initializer
        for v, m in decls.items():
            if not m.group("init"):
                continue
            t1 = _with_init(text, m, False)
            named = _named_sites(t1, v)
            if named:
                put("remove:%s:named" % v, erase_many(t1, named, clean_notes=True))
            if len(out) >= MAX_MENU:
                return out
    return out


class T:
    name = "t119_deadinit"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not menu(text):
            return "no local to give or take a dead zero initializer"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        mn = menu(text)
        if not mn:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        # the pin-removing texts first (a `remove` without erasure only matters as a listing probe)
        mn.sort(key=lambda c: len(sites_of(c[1])))
        ranked, listings = [], 0
        for label, cand in mn:
            if listings >= MAX_LISTINGS:
                break
            lst = screen.compile_s(row, cand); listings += 1
            if lst is None:
                continue
            ranked.append((screen.sdiff(target, lst), len(sites_of(cand)), label, cand))
        info.update(listings=listings, menu=len(mn))
        ranked = [r for r in ranked if r[1] < pins_in]
        ranked.sort(key=lambda x: (x[0], x[1]))
        tried = 0
        for d, pins, label, cand in ranked:
            if tried >= MAX_VERIFY or (d and tried >= 2):
                break
            tried += 1
            if vf(cand).get("exact"):
                info["dead_init"] = [t["init"] for t in dead_init.trades(text, cand)]
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "pins": p, "label": l} for d, p, l, _c in ranked[:6]])
