"""T105: the first statement of an `if` arm hoisted above the `if` - the head-side twin of t82's sink.

APPEARS     two shapes, one per model, in the round-73 lanes:

              (dup)  the same assignment written as the first statement of a then-arm that leaves by
                     `goto`/`return`/`break`/`continue` AND as the first statement after the `if`
                     (dungeon/func_819C04E8, claude-opus-5-5 lane work/native_lane/r73_opus_a1, 2 pins):
                         if ((s16)object_index != 0) {
                             data_entry = (u8 *)current_object + 0x20;
                             ASM_KEEP(data_entry);
                             ...
                             goto shared_tail;
                         }
                         data_entry = (u8 *)current_object + 0x20;
                     ->  data_entry = (u8 *)current_object + 0x20;
                         if ((s16)object_index != 0) { ...; goto shared_tail; }
                     with the keep and `data_entry`'s `ASM_REG("$3")` erased.

              (spec) a pure copy or arithmetic value computed first in a then-arm, into a local no code
                     outside the arm reads (dungeon/func_80DE9000, astra lane r73_astra_h2 - one of its
                     two pins): `if (root != NULL) { held_flags = spawn_flags; ASM_USE_NV(held_flags);`
                     -> `held_flags = spawn_flags;` before the `if`, the use-pin erased.

RESOLVES    opus (func_819C04E8): "APPEARS: the same assignment written in both arms of an if (or in one
            arm plus the fall-through) next to a pinned/kept copy of it. RESOLVES: hoist the common
            assignment above the branch."  Mechanism, from the lane: retail's `addiu $3,$2,32` sits in
            the `beq` delay slot - computed before the branch on both paths; one assignment before the
            branch gives that insn directly, where two identical arm computations need cse/jump to merge
            them.  astra (func_80DE9000): "an input-only keep forces a narrow value's copy into a branch
            delay slot ... RESOLVES: place the useful narrow copy just before the branch".

WHY THE OWNERS MISS IT (measured 2026-09-23, work/native_lane/r73_h_probe_t67_tailform_o)
            t67_tailform is eligible on both rows but its `hoist_tail` moves a common TAIL of two arms
            (`hoist_tail:no-common-tail` 20, `empties-an-arm` 21 on func_819C04E8); t82_armsink refuses
            "no join local or duplicated arm statement in a braced if/else" - it sinks, it never hoists.

SAFETY      the hoisted statement is one line `NAME = EXPR;` whose EXPR has no call, no dereference
            (`->`, `[`, unary `*`), no `++`/`--`/assignment and names only the function's locals and
            parameters; the `if` condition must not mention NAME and holds no call or assignment, so
            evaluating the statement first cannot change the condition or fault.  (dup) needs the arm to
            leave by a jump, so the fall-through copy is the only other execution; (spec) needs every
            mention of NAME outside the arm to be its declaration or a pin.

CANDIDATES  per site: the hoist with no pin erased, with the pins naming NAME erased, with the pins in
            the site's window (the line above the `if` to the arm's third line) erased too, and with
            every pin of the function erased; ranked by cc1 listing distance to the pinned text, the
            listing-exact candidates and the two nearest sent to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
    from .t36_paramwidth import functions
    from . import t72_stmtperm as S
    from . import screen
except ImportError:
    from t29_addrsym import mask_comments
    from t36_paramwidth import functions
    import t72_stmtperm as S
    import screen

MAX_SITES = 8
MAX_LISTINGS = 80
MAX_VERIFY = 4
IF_RE = re.compile(r"^(?P<ind>[ \t]*)if[ \t]*\(", re.M)
ASSIGN_RE = re.compile(r"^(?P<ind>[ \t]*)(?P<v>[A-Za-z_]\w*)[ \t]*=(?!=)[ \t]*(?P<e>[^;{}]*);[ \t]*$")
PIN_RE = re.compile(r"^[ \t]*ASM_[A-Z0-9_]+\s*\(")
JUMP_RE = re.compile(r"^[ \t]*(?:goto\b[^;]*|return\b[^;]*|break|continue)[ \t]*;[ \t]*$")
CALL_RE = re.compile(r"\b[A-Za-z_]\w*\s*\(")
IDENT = re.compile(r"\b[A-Za-z_]\w*\b")


def _match(masked, i, o, c):
    """Index of the bracket closing masked[i] (== o)."""
    d = 0
    for j in range(i, len(masked)):
        if masked[j] == o:
            d += 1
        elif masked[j] == c:
            d -= 1
            if d == 0:
                return j
    return -1


def _pure(e, names):
    ne = S.CAST.sub(" ", e)
    if CALL_RE.search(ne) or re.search(r"->|\[|\+\+|--|(?<![=!<>])=(?!=)", ne):
        return False
    if re.search(r"(?:^|[^\w)\]\s])\s*\*", ne):         # unary `*`: a load
        return False
    ids = {i for i in IDENT.findall(ne) if i not in S.KEYWORDS and i not in S.TYPEWORDS}
    return ids <= names


def sites(text):
    """[{kind, if_line, arm, stmt_line, dup_line, name}] - 0-based line numbers."""
    masked = mask_comments(text)
    ml = masked.split("\n")
    starts, at = [], 0
    for l in ml:
        starts.append(at); at += len(l) + 1
    line_of = lambda pos: masked.count("\n", 0, pos)
    out = []
    for fname, params, b0, b1 in functions(text):
        body = masked[b0:b1]
        names = S.decl_names(body) | {p for p, _, _, _ in params}
        for m in IF_RE.finditer(masked, b0, b1):
            if re.search(r"\belse[ \t]*$", masked[starts[line_of(m.start())]:m.start()]):
                continue
            po = m.end() - 1
            pc = _match(masked, po, "(", ")")
            if pc < 0:
                continue
            cond = masked[po + 1:pc]
            rest = masked[pc + 1:pc + 40].lstrip(" \t")
            if not rest.startswith("{") or CALL_RE.search(S.CAST.sub(" ", cond)) \
                    or re.search(r"(?<![=!<>])=(?!=)|\+\+|--", cond):
                continue
            bo = masked.index("{", pc)
            bc = _match(masked, bo, "{", "}")
            if bc < 0 or line_of(bo) != line_of(m.start()):
                continue
            il, ol, cl = line_of(m.start()), line_of(bo), line_of(bc)
            k = ol + 1
            while k < cl and (not ml[k].strip() or PIN_RE.match(ml[k])):
                k += 1
            if k >= cl:
                continue
            a = ASSIGN_RE.match(ml[k])
            if not a or a.group("v") not in names or not _pure(a.group("e"), names) \
                    or re.search(r"\b%s\b" % re.escape(a.group("v")), cond) \
                    or re.search(r"\b%s\b" % re.escape(a.group("v")), a.group("e")):
                continue
            v, stmt = a.group("v"), re.sub(r"\s+", " ", ml[k].strip())
            # the statement after the `if` (no `else`)
            j = cl + 1
            while j < len(ml) and not ml[j].strip():
                j += 1
            after = ml[cl][ml[cl].index("}") + 1:].strip() if "}" in ml[cl] else ""
            last = cl - 1
            while last > k and (not ml[last].strip() or PIN_RE.match(ml[last])):
                last -= 1
            if not after and j < len(ml) and not ml[j].lstrip().startswith("else") \
                    and re.sub(r"\s+", " ", ml[j].strip()) == stmt and JUMP_RE.match(ml[last]):
                out.append({"kind": "dup", "if_line": il, "open": ol, "close": cl, "stmt_line": k,
                            "dup_line": j, "name": v})
                continue
            fb0, fb1 = line_of(b0), line_of(b1)
            outside = [q for q in range(fb0, fb1 + 1) if not (ol < q < cl)
                       and re.search(r"\b%s\b" % re.escape(v), ml[q])]
            if all(PIN_RE.match(ml[q]) or re.match(r"^[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t\*]*\b%s\b[^=]*;"
                                                    % re.escape(v), ml[q]) for q in outside):
                out.append({"kind": "spec", "if_line": il, "open": ol, "close": cl, "stmt_line": k,
                            "dup_line": None, "name": v})
            if len(out) >= MAX_SITES:
                return out
    return out


def hoist(text, st):
    lines = text.split("\n")
    ind = re.match(r"^[ \t]*", lines[st["if_line"]]).group(0)
    stmt = ind + lines[st["stmt_line"]].strip()
    drop = {st["stmt_line"]} | ({st["dup_line"]} if st["dup_line"] is not None else set())
    out = []
    for q, l in enumerate(lines):
        if q == st["if_line"]:
            out.append(stmt)
        if q not in drop:
            out.append(l)
    return "\n".join(out)


def candidates(text):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    for st in sites(text):
        h = hoist(text, st)
        pins = sites_of(h)
        rx = re.compile(r"\b%s\b" % re.escape(st["name"]))
        named = [p for p in pins if rx.search(h[p[3]:p[4]]) or (p[0] != "stmt" and rx.search(
            h[h.rfind("\n", 0, p[3]) + 1:h.find("\n", p[4]) if h.find("\n", p[4]) >= 0 else len(h)]))]
        lo, hi = st["if_line"] - 1, st["stmt_line"] + 3        # +1 for the inserted line
        win = [p for p in pins if lo <= p[5] - 1 <= hi] + named
        for tag, group in (("none", []), ("named", named), ("win", win), ("all", pins)):
            group = list({(g[3], g[4]): g for g in group}.values())
            cand = erase_many(h, group, clean_notes=True) if group else h
            if cand in seen or unscored_text(cand) != sig:
                continue
            seen.add(cand)
            out.append(("%s:%s@%d:%s" % (st["kind"], st["name"], st["if_line"] + 1, tag), cand))
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t105_headhoist"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not sites(text):
            return "no hoistable first statement of an if arm"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in, "sites": len(sites(text))}
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
            if pins >= pins_in:
                continue
            tried += 1
            if vf(cand).get("exact"):
                return cand, dict(info, step="%s|d%d" % (label, d), pins_out=pins, tried=tried)
        return None, dict(info, tried=tried,
                          nearest=[{"distance": d, "label": l} for d, _p, l, _c in ranked[:6]])
