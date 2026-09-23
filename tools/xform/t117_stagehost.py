"""T117: a value STAGED through an existing, dead local - a store's source or a parenthesised operand written to a
local that is dead at that point, then used from it - in place of a fence or a keep.

APPEARS     (astra, the largest move of the late round-73 lanes: ~23 rows / ~42 pins as "host a value on an
            existing variable"; the owners t112_deadhost 0/10 and t87_lifetimemerge 0/5 on them):
            * a scheduling fence beside a store: town/func_8081FCE0 (r74_astra_a7)
                  ((S *)obj)->unk_10 = D_80023DE0;  ASM_SCHED_BARRIER();  value = 0x1000; ...
              ->  value = (s32)D_80023DE0;  ((S *)obj)->unk_10 = (void *)value;           (value dead there)
            * a keep on a local whose last use is long past: dungeon/func_80087054 (r74_astra_a7)
                  initial_state = 0x1C;  ASM_KEEP_NV(initial_state);  ...
                  direction_entry = direction_table + (((s32)(...) >> 9) & 7);
              ->  initial_state = ((s32)(...) >> 9) & 7;  direction_entry = direction_table + initial_state;

RESOLVES    astra (func_8081FCE0): "APPEARS: a fence separates a pointer-sized store producer from a later scalar
            producer, and a compatible local already carries the later value. RESOLVES: host the earlier real
            store value on that local too, so its overwrite has the required output/anti edges".  astra
            (func_80087054): "APPEARS: a keep on a constant store producer whose lone erasure reverses a
            neighboring independent address load. RESOLVES: reuse that scalar for a later real expression of
            compatible type, and retain only variants whose scheduler ready list loses the birthing boost".
            A second set on the host's pseudo takes it out of sched.c's `birthing_insn_p` boost (reg_n_sets
            > 1) and adds the output/anti dependences the fence or keep stood in for.

WHY THE OWNERS MISS IT  t112 hosts on a DEAD PARAMETER / dead local only a value that already had its own local;
            t87/t90 merge two existing locals; neither stages a store's source or an operand.

CANDIDATES  per pin: a fence - the one-line store just above and just below it; a keep / register pin on a
            local V - the one-line statements after V's last read, V as the only host.  Staged: the whole
            right-hand side, and each parenthesised operand of a top-level `+`/`-`.  Hosts: locals of the
            function (declared, not parameters) not named by the statement and DEAD there (their next mention
            is a plain assignment that does not read them, or there is none).  The pin erased.  At most
            MAX_LISTINGS candidates, nearest the pin first; ranked by cc1 listing distance to the pinned text;
            listing-exact and the two nearest go to `vf`.
"""
import difflib
import re
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, asm_blocker, unscored_text, arm_labels
from pin_sites import erase_many
try:
    from .t36_paramwidth import functions
    from .t115_carrierfold import stmt, pure, mentions, PIN_LINE, KEYWORD
    from . import screen
except ImportError:
    from t36_paramwidth import functions
    from t115_carrierfold import stmt, pure, mentions, PIN_LINE, KEYWORD
    import screen

MAX_HOSTS = 40
MAX_STMTS = 80
MAX_LISTINGS = 40
MAX_VERIFY = 4
FENCES = ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER")
LOCAL_DECL = re.compile(r"^[ \t]+(?:register[ \t]+)?(?:(?:unsigned|signed|const|volatile)[ \t]+)*"
                        r"(?P<ty>(?:s8|u8|s16|u16|s32|u32|int|short|char|long|void|[A-Z]\w*)[ \t\*]*?)[ \t]*(?P<ptr>\**)[ \t]*"
                        r"(?P<v>[A-Za-z_]\w*)[ \t]*(?:ASM_REG\([^()]*\))?[ \t]*(?:=[^;]*)?;")


def hosts_of(lines, lo, hi, labels):
    """{name: type} of the locals declared in [lo, hi)."""
    out = {}
    for i in range(lo, hi):
        if labels[i] in ("port", "dead"):
            continue
        m = LOCAL_DECL.match(lines[i])
        if m and m.group("v") not in out:
            out[m.group("v")] = (m.group("ty").strip() + " " + m.group("ptr")).strip()
    return out


def dead_at(lines, i, hi, v, labels):
    """v is not read after line i before a plain assignment to it (textual, pins and port arms skipped)."""
    for k in range(i + 1, hi):
        l = lines[k]
        if labels[k] in ("port", "dead") or PIN_LINE.match(l) or not mentions(l, v):
            continue
        st = stmt(l)
        return bool(st and st[1] == v and not st[2] and not mentions(st[3], v))
    return True


def operands(rhs):
    """The whole rhs, and each parenthesised operand of a top-level `+`/`-`."""
    out = [rhs]
    depth, parts, cur = 0, [], ""
    for ch in rhs:
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
        if depth == 0 and ch in "+-" and cur.strip() and not cur.rstrip().endswith(("(", "*", "/", "&", "|", "<", ">")):
            parts.append(cur); cur = ""
            continue
        cur += ch
    parts.append(cur)
    if len(parts) > 1:
        for p in parts:
            p = p.strip()
            if p.startswith("(") and p.endswith(")") and len(p) > 2:
                out.append(p)
    return out


def _stage(lines, i, v, e):
    ind, lhs, op, rhs = stmt(lines[i])
    inner = e[1:-1] if e.startswith("(") and e.endswith(")") and e != rhs else e
    new_rhs = rhs.replace(e, v, 1)
    return lines[:i] + ["%s%s = %s;" % (ind, v, inner), "%s%s %s= %s;" % (ind, lhs, op, new_rhs)] + lines[i + 1:]


def plans(text, first=False):
    """[(label, pin, line_index, host, expr)]; `first`: stop at the first plan (the eligibility test)."""
    lines = text.split("\n")
    labels = arm_labels(text)
    labels += [None] * (len(lines) - len(labels))
    out = []
    pins = sites_of(text)
    for fname, params, b0, b1 in functions(text):
        lo, hi = text.count("\n", 0, b0) + 1, text.count("\n", 0, b1)
        hosts = hosts_of(lines, lo, hi, labels)
        pnames = {p for p, _, _, _ in params}
        for p in pins:
            if not (b0 <= p[3] < b1):
                continue
            pl = text.count("\n", 0, p[3])
            if p[1] in FENCES:
                cands = []
                for k in (pl - 1, pl + 1):
                    while lo <= k < hi and (not lines[k].strip() or PIN_LINE.match(lines[k])):
                        k += -1 if k < pl else 1
                    if lo <= k < hi:
                        cands.append(k)
                hv = [h for h in hosts if h not in pnames]
            else:
                seg = lines[pl]
                vs = re.findall(r"[A-Za-z_]\w*", p[2] or "") if p[0] == "stmt" else \
                    [m.group("v") for m in [LOCAL_DECL.match(seg)] if m]
                hv = [v for v in vs if v in hosts and v not in pnames]
                if not hv:
                    continue
                # after the host's last read (textual; a later plain re-assignment ends the window's use)
                last = max([k for k in range(lo, hi) if not PIN_LINE.match(lines[k])
                            and any(mentions(lines[k], v) for v in hv)] + [pl])
                cands = list(range(last + 1, hi))[:MAX_STMTS]
            for k in cands:
                if labels[k] in ("port", "dead") or KEYWORD.match(lines[k]):
                    continue
                st = stmt(lines[k])
                if not st or st[2] or not pure(st[3]):
                    continue
                # hosts whose next plain assignment comes soonest first ("a compatible local already carries
                # the later value")
                def nxt(v, k=k):
                    for j in range(k + 1, hi):
                        if mentions(lines[j], v) and not PIN_LINE.match(lines[j]):
                            return j
                    return hi
                order = sorted(hv[:MAX_HOSTS], key=nxt)
                for e in operands(st[3]):
                    if not re.search(r"[A-Za-z_(]", e):
                        continue
                    if p[1] not in FENCES and not re.search(r"[-+*/%&|^<>]", e):
                        continue                          # a keep site stages only a computed value
                    for v in order:
                        if mentions(lines[k], v) or not dead_at(lines, k, hi, v, labels):
                            continue
                        if st[1] == v:
                            continue
                        out.append(("%s@%d:%s<-%s" % (p[1], pl + 1, v, "rhs" if e == st[3] else "op"), p, k, v, e))
                        if first:
                            return out
    # nearest the pin first
    out.sort(key=lambda x: abs(x[2] - text.count("\n", 0, x[1][3])))
    return out


def candidates(text, limit=None):
    sig, n0 = unscored_text(text), len(sites_of(text))
    out, seen = [], {text}
    for label, pin, k, v, e in plans(text):
        lines = _stage(text.split("\n"), k, v, e)
        t2 = "\n".join(lines)
        # the same pin in the new text: same kind and argument, nearest the old offset
        same = [q for q in sites_of(t2) if q[1] == pin[1] and q[2] == pin[2]]
        if not same:
            continue
        q = min(same, key=lambda q: abs(q[3] - pin[3]))
        cand = erase_many(t2, [q], clean_notes=True)
        if cand in seen or unscored_text(cand) != sig or len(sites_of(cand)) >= n0:
            continue
        seen.add(cand)
        out.append((label, cand))
        if limit and len(out) >= limit:
            break
    return out


def _dist(a, b):
    return sum(1 for y in difflib.unified_diff(a, b, lineterm="", n=0)
               if y[:1] in "+-" and not y.startswith(("---", "+++")))


class T:
    name = "t117_stagehost"
    level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        why = asm_blocker(text)
        if why:
            return why
        if not sites_of(text):
            return "no pin sites"
        if not plans(text, first=True):
            return "no fence/keep with a dead local to stage a neighbouring value on"
        return None

    @classmethod
    def apply_verified(cls, text, row, census, vf):
        pins_in = len(sites_of(text))
        info = {"pins_in": pins_in, "pins_out": pins_in}
        menu = candidates(text, MAX_LISTINGS)
        if not menu:
            return None, dict(info, refused=["no buildable candidate"])
        target = screen.compile_s(row, text)
        if target is None:
            return None, dict(info, refused=["pinned text does not build to a listing"])
        ranked, listings = [], 0
        for label, cand in menu:
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
