"""T94: one assignment written as TWO statements, so the intermediate value gets a pseudo of its own.

APPEARS     a pinned local assigned a compound right-hand side, the pin standing for a copy or an
            ordering the single statement does not produce.  Four spellings, all from the
            round-63/66 big-row lanes:

              (a) a cast ON TOP of arithmetic on the local itself (dungeon/func_8181B3E8, five sites):
                      impact_position = func_80069EF8() & 0xF;
                      ASM_KEEP(impact_position);                  <- the pin
                      impact_position = (s16)(impact_position - 8);
                  ->  impact_position -= 8;
                      impact_position = (s16)impact_position;

              (b) two operators over the local (dungeon/func_8180C3C0):
                      ASM_KEEP_NV(table_index);
                      table_index = (table_index + 0x100) >> 8;
                  ->  table_index += 0x100;
                      table_index >>= 8;

              (c) the arithmetic done in the SOURCE local, which the destination then copies
                  (dungeon/func_810332A4):
                      ASM_KEEP_NV(collision_coord);
                      coord_base = collision_coord + 0x20;
                  ->  collision_coord += 0x20;
                      coord_base = collision_coord;

              (d) a signed halving written back OUT as gcc's own expansion - the inverse of
                  t17_divpow2, which folds the expansion INTO a `/` (dungeon/func_80097C50, twice):
                      ASM_KEEP(tile_index_or_level);
                      map_index = tile_index_or_level / 2;
                  ->  map_index = tile_index_or_level + ((u32)tile_index_or_level >> 31);
                      map_index >>= 1;

RESOLVES    nine pins over four rows of the lanes, byte-exact at their recorded recipes
            (func_8181B3E8 5, func_80097C50 2, func_810332A4 2, func_8180C3C0 1).  Mechanism: gcc 2.x
            gives every tree temporary its own pseudo and `expand_expr` emits the outer operation
            into the destination's pseudo only when the inner value has died; split in two, the
            intermediate is a NAMED local that is set once and reused, which is what drives both the
            scheduler's birth priority (sched.c `birthing_insn_p`) and the allocator's preference -
            the same lever as t87/t89/t91.  Shape (d) is the other direction: `x / 2` makes gcc
            re-emit its own copy, while the written-out expansion lets cse collapse it.
            No generator splits a statement today: t35_shiftspell flips ONE scale spelling in place,
            t17_divpow2 only folds the idiom into a `/`, and t74_multiset splits a chain of the SAME
            operator (`a + b + c`), never a cast over arithmetic or a two-operator right-hand side.

CANDIDATES  every split of a statement that has a pin within three lines, ranked by how close the
            nearest pin is; each split paired with the nearest pin alone, the nearest two, and the
            pins naming either local.  A candidate is screened against the pinned text's cc1 listing
            and only listing-exact ones (plus two nearest) reach the byte verifier.
"""
import difflib, re, sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
from xform.t29_addrsym import mask_comments
from xform.t36_paramwidth import functions
from xform.t72_stmtperm import decl_names
import xform.screen as screen

MAX_SITES = 14
MAX_LISTINGS = 220
MAX_VERIFY = 6
NEAR = 3                                           # lines between a statement and a pin that pair them

NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
CAST = r"\(\s*(?:unsigned\s+|signed\s+)?[A-Za-z_]\w*\s*\)"
ASSIGN = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*=[ \t]*(?P<rhs>[^;]+);[ \t]*$")
SHIFT_UP = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*<<=[ \t]*(?P<n>16|24)[ \t]*;[ \t]*$")
SHIFT_DOWN = re.compile(r"^(?P<ind>[ \t]*)(?P<w>[A-Za-z_]\w*)[ \t]*=[ \t]*\(\s*s32\s*\)[ \t]*"
                        r"(?P<v>[A-Za-z_]\w*)[ \t]*>>[ \t]*(?P<n>16|24)[ \t]*;[ \t]*$")
OPS = ("+", "-", "&", "|", "^", "<<", ">>", "*")
NARROW = {24: "s8", 16: "s16"}


def _op_split(rhs):
    """`X <op> K` at the top level -> (X, op, K), else None."""
    depth = 0
    for i in range(len(rhs) - 1, 0, -1):
        c = rhs[i]
        if c in ")]":
            depth += 1
        elif c in "([":
            depth -= 1
        elif depth == 0:
            for op in ("<<", ">>"):
                if rhs[i - 1:i + 1] == op:
                    return rhs[:i - 1].strip(), op, rhs[i + 1:].strip()
            if c in "+-&|^*" and i and rhs[i - 1] not in "+-&|^*<>=!/(" and rhs[i + 1:].strip():
                return rhs[:i].strip(), c, rhs[i + 1:].strip()
    return None


def _is_name(s):
    return bool(re.fullmatch(r"[A-Za-z_]\w*", s))


def _const(s):
    return bool(re.fullmatch(NUM, s))


def splits(lines, i, locals_):
    """[(label, [new lines])] for the statement on line `i`, or []."""
    m = ASSIGN.match(lines[i])
    out = []
    if not m:
        return out
    ind, v, rhs = m.group("ind"), m.group("v"), m.group("rhs").strip()
    if v not in locals_:
        return out
    # (a) a cast over arithmetic on V itself: `v = (s16)(v - 8);`
    cm = re.fullmatch(r"(?P<c>%s)[ \t]*\((?P<inner>.+)\)" % CAST, rhs)
    if cm:
        sp = _op_split(cm.group("inner").strip())
        if sp and sp[0] == v and _const(sp[2]) and sp[1] in OPS:
            out.append(("cast", [f"{ind}{v} {sp[1]}= {sp[2]};", f"{ind}{v} = {cm.group('c')}{v};"]))
    sp = _op_split(rhs)
    if sp:
        a, op, k = sp
        # (b) two operators over V: `v = (v + 0x100) >> 8;`
        inner = re.fullmatch(r"\((?P<x>.+)\)", a)
        if inner and _const(k) and op in OPS:
            sp2 = _op_split(inner.group("x").strip())
            if sp2 and sp2[0] == v and _const(sp2[2]) and sp2[1] in OPS:
                out.append(("two-op", [f"{ind}{v} {sp2[1]}= {sp2[2]};", f"{ind}{v} {op}= {k};"]))
        # (c) the arithmetic moved into the source local: `dst = src + 0x20;`
        if _is_name(a) and a != v and a in locals_ and _const(k) and op in OPS:
            out.append(("insource", [f"{ind}{a} {op}= {k};", f"{ind}{v} = {a};"]))
        # (a') arithmetic on V with a cast on the OPERAND: `v = (s16)v - 8;` stays one statement
    # (d) a signed halving written out as gcc's expansion
    dm = re.fullmatch(r"(?P<x>[A-Za-z_]\w*)[ \t]*/[ \t]*2", rhs)
    if dm and dm.group("x") in locals_:
        x = dm.group("x")
        out.append(("half", [f"{ind}{v} = {x} + ((u32){x} >> 31);", f"{ind}{v} >>= 1;"]))
    return out


def merges(lines, i, locals_):
    """[(label, span, [new lines])] for `v <<= 24; ... w = (s32)v >> 24;` collapsed to one cast."""
    up = SHIFT_UP.match(lines[i])
    if not up or up.group("v") not in locals_:
        return []
    v, n = up.group("v"), int(up.group("n"))
    out = []
    for j in range(i + 1, min(len(lines), i + 4)):
        dn = SHIFT_DOWN.match(lines[j])
        if dn and dn.group("v") == v and int(dn.group("n")) == n:
            w = dn.group("w")
            if any(re.search(r"\b%s\b" % re.escape(v), lines[q]) for q in range(i + 1, j)):
                break                              # V is touched in between: not one idiom
            body = [l for q, l in enumerate(lines[i:j + 1], i) if q not in (i, j)]
            out.append(("signext", (i, j), body + ["%s%s = (%s)(%s + 0);"
                                                   % (dn.group("ind"), w, NARROW[n], v)]))
            break
        if re.search(r"\b%s\b" % re.escape(v), lines[j]):
            break
    return out


def sites(text):
    """[(line, label, span, new lines)] - every split/merge with a pin within NEAR lines."""
    masked = mask_comments(text)
    lines, out = masked.split("\n"), []
    pin_lines = {s[5] - 1 for s in sites_of(text)}
    if not pin_lines:
        return out
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        locals_ = decl_names(body) | {p for p, _, _, _ in params}
        first, last = masked.count("\n", 0, b0), masked.count("\n", 0, b1)
        for i in range(first, min(last + 1, len(lines))):
            if not any(abs(i - p) <= NEAR for p in pin_lines):
                continue
            for label, new in splits(lines, i, locals_):
                out.append((i, label, (i, i), new))
            for label, span, new in merges(lines, i, locals_):
                out.append((i, label, span, new))
    out.sort(key=lambda s: min(abs(s[0] - p) for p in pin_lines))
    return out[:MAX_SITES]


def apply_sites(text, chosen):
    """The chosen sites rewritten, last one first so the earlier spans keep their line numbers."""
    lines = text.split("\n")
    for i, label, (a, b), new in sorted(chosen, key=lambda s: s[2][0], reverse=True):
        lines = lines[:a] + new + lines[b + 1:]
    return "\n".join(lines)


def candidates(text):
    """[(label, new_text)] - each split with the pin groups around it, then the JOINT form.

    A duplicated block splits the same statement two or three times over (dungeon/func_80097C50
    writes `map_index = tile_index_or_level / 2;` in two copies of one loop body, and the row is
    byte-exact only when BOTH are split): one site at a time never reaches it, so every set of
    sites with an identical statement is also offered together.
    """
    out, seen, sig = [], {text}, unscored_text(text)
    found = sites(text)
    lines = text.split("\n")
    same = {}
    for s in found:
        same.setdefault((s[1], lines[s[0]].strip()), []).append(s)
    for chosen in [[s] for s in found] + [v for v in same.values() if len(v) > 1]:
        moved = apply_sites(text, chosen)
        if len(sites_of(moved)) != len(sites_of(text)):
            continue                               # the rewrite swallowed a pin line: not this move
        label = chosen[0][1] + ("@%d" % (chosen[0][0] + 1) if len(chosen) == 1
                                else "x%d@%d" % (len(chosen), chosen[0][0] + 1))
        pins = sites_of(moved)
        names = set(re.findall(r"[A-Za-z_]\w*", "\n".join(x for s in chosen for x in s[3])))

        def nearest(k):                            # each site's k nearest pins, in one group
            g = []
            for s in chosen:
                for p in sorted(pins, key=lambda p: abs(p[5] - 1 - s[0]))[:k]:
                    if p not in g:
                        g.append(p)
            return g
        def side(below):                           # the nearest pin BELOW (or above) each site
            g = []
            for s in chosen:
                cs = [p for p in pins if (p[5] - 1 > s[0]) == below]
                for p in sorted(cs, key=lambda p: abs(p[5] - 1 - s[0]))[:1]:
                    if p not in g:
                        g.append(p)
            return g
        named = [p for p in pins if p[2] in names
                 and any(abs(p[5] - 1 - s[0]) <= NEAR + 2 for s in chosen)]
        # `map_index = tile / 2;` sits BETWEEN two keeps on `tile` and only the one below it falls
        # (dungeon/func_80097C50), so each side is a plan of its own and not just "the nearest".
        plans = [("n1", nearest(1)), ("below", side(True)), ("above", side(False)),
                 ("n2", nearest(2)), ("var", named)]
        for tag, group in plans:
            if not group:
                continue
            cand = erase_many(moved, group, clean_notes=True)
            if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= len(sites_of(text)):
                continue
            seen.add(cand)
            out.append(("%s:%s" % (label, tag), cand))
    return out


class T:
    name = "t94_castsplit"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pins"
        return None if sites(text) else "no splittable assignment next to a pin"

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "sites": len(sites(text))}
        menu = candidates(text)
        if not menu:
            return None, dict(info, refused=["no candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        cur, steps, listings, verifies, spent, nearest = text, [], 0, 0, set(), []
        while listings < MAX_LISTINGS and verifies < MAX_VERIFY:
            ranked = []
            for label, cand in candidates(cur):
                if cand in spent or listings >= MAX_LISTINGS:
                    continue
                lst = screen.compile_s(row, cand); listings += 1
                if lst is None:
                    continue
                d = sum(1 for y in difflib.unified_diff(target, lst, lineterm="", n=0)
                        if y[:1] in "+-" and not y.startswith(("---", "+++")))
                ranked.append((d, len(sites_of(cand)), label, cand))
            ranked.sort(key=lambda x: (x[0], x[1]))
            if not steps:
                nearest = [{"distance": d, "label": l} for d, _, l, _ in ranked[:6]]
            moved = False
            for d, _, label, cand in ranked:
                if verifies >= MAX_VERIFY or (d and (steps or verifies >= 2)):
                    break
                spent.add(cand); verifies += 1
                if vf(cand).get("exact"):
                    cur, moved = cand, True
                    steps.append("%s|d%d" % (label, d))
                    break
            if not moved:
                break
        info.update(listings=listings, tried=verifies)
        if not steps:
            return None, dict(info, nearest=nearest)
        return cur, dict(info, step="+".join(steps), pins_out=len(sites_of(cur)))
