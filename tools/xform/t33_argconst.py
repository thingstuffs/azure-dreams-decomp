"""T33: a pinned local that only ever holds constants, written back as the constants.

APPEARS     `register s32 call_zero ASM_REG("$4");` (or any pinned local) whose every assignment is an
            integer constant (`call_zero = 0;`, an initialiser), read as call arguments or operands:
            `func_80066460(call_zero, call_one, call_zero, call_zero);`.
RESOLVES    m2c names a constant it sees in a register; the pin then forces that name into the
            register. Where retail used the constant in place, writing it back lets gcc emit its own
            load at the use (first sweep, 2026-09-12: 15 functions / 17 pins byte-exact, e.g.
            `->unk_0C = 0x00808080;` for a pinned `color`). NOT a fix for the displaced-argument-move
            family: the argmove lane measured `func(0, ...)` for `call_zero` at total 2 on both rows.
POPULATION  2026-09-12: 215 constant-valued locals pinned to $a0-$a3 in 139 functions; 361
            constant-valued pinned locals rewritable in 247 functions.

Each read takes the constant of the last assignment above it (text order); the assignments, the
declaration and every pin of the variable go. A variable that is modified any other way, has
its address taken, or is read before any assignment is left alone. Candidates: each variable
alone, then all together; the byte verifier decides.
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments, decls_of, operand_lead, NOTE_RE
except ImportError:
    from t29_addrsym import mask_comments, decls_of, operand_lead, NOTE_RE
import collections

CONST = r"-?\s*(?:0x[0-9A-Fa-f]+|\d+)[UuLl]*"


def constvars(text):
    """Pinned locals whose every assignment (initialiser included) is an integer constant."""
    masked = mask_comments(text)
    pinned = set()
    for s in sites_of(text):
        pinned.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
    out = []
    for v in sorted(pinned):
        V = re.escape(v)
        decs = decls_of(text, v)
        if not decs:
            continue
        vals = re.findall(r"(?<![\w.>])%s\s*=(?!=)\s*([^;]+);" % V, masked)
        if vals and all(re.fullmatch(r"\s*\(?\s*%s\s*\)?\s*" % CONST, x) for x in vals) \
                and not any(is_address(x) for x in vals):
            out.append(v)
    return out


def is_address(c):
    """A RAM or scratchpad address: retail names those as symbols (t29_addrsym), never literals."""
    try:
        n = int(re.sub(r"[\s()UuLl]", "", c), 0) & 0xFFFFFFFF
    except ValueError:
        return False
    return 0x80000000 <= n <= 0x80FFFFFF or 0x1F800000 <= n <= 0x1F80FFFF


def rewrite_const(text, v):
    V = re.escape(v)
    masked = mask_comments(text)
    decs = decls_of(text, v)
    dspans = [sp for _, _, sp in decs]
    defs = []
    for m in re.finditer(r"^[ \t]*%s\s*=\s*\(?\s*(?P<c>%s)\s*\)?\s*;[^\n]*\n" % (V, CONST), masked, re.M):
        defs.append((m.start(), m.end(), m.group("c").replace(" ", "")))
    for a, b in dspans:
        dm = re.search(r"=\s*\(?\s*(%s)\s*\)?\s*;" % CONST, masked[a:b])
        if dm:
            defs.append((a, b, dm.group(1).replace(" ", "")))
        elif "=" in masked[a:b]:
            return None, "decl-init"
    if not defs:
        return None, "no-def"
    pins = [s for s in sites_of(text) if re.search(r"\b%s\b" % V, text[s[3]:s[4]])]
    fixed = [(a, b) for a, b, _ in defs] + dspans + [(s[3], s[4]) for s in pins]
    inside = lambda p, spans: any(a <= p < b for a, b in spans)
    edits = []
    for m in re.finditer(r"\b%s\b" % V, masked):
        if inside(m.start(), fixed):
            continue
        before = [(b, c) for a, b, c in defs if b <= m.start()]
        if not before:
            return None, "use-before-def"
        # the reaching assignment must still be in scope: a `}` closing its block between the two
        # means other paths (an else, the skipped branch) reach this read with other values
        depth = 0
        for ch in masked[before[-1][0]:m.start()]:
            depth += (ch == "{") - (ch == "}")
            if depth < 0:
                return None, "use-outside-def-block"
        before = [c for _, c in before]
        after = masked[m.end():].lstrip()
        if re.match(r"(\+\+|--|[-+*/|&^%]?=(?!=)|\[|->|\.)", after) or masked[:m.start()].rstrip().endswith(("++", "--", "&")):
            return None, "modified-or-address"
        if not operand_lead(masked, m.start()) and not masked[:m.start()].rstrip().endswith((")", "*", "/", "%")):
            return None, "not-operand"
        c = before[-1]
        edits.append((m.start(), m.end(), "(%s)" % c if c.startswith("-") else c))
    if not edits:
        return None, "no-uses"
    t = text
    for a, b, rep in sorted(set(edits) | {(a, b, "") for a, b, _ in defs} | {(a, b, "") for a, b in dspans},
                            key=lambda e: e[0], reverse=True):
        t = t[:a] + rep + t[b:]
    left = [s for s in sites_of(t) if re.search(r"\b%s\b" % V, t[s[3]:s[4]])]
    if left:
        t = erase_many(t, left, clean_notes=True)
    if re.search(r"\b%s\b" % V, mask_comments(t)):
        return None, "still-mentioned"
    orig = collections.Counter(m.group(0).strip() for m in NOTE_RE.finditer(text))
    def keep_original(m):
        k = m.group(0).strip()
        if orig[k] > 0:
            orig[k] -= 1; return m.group(0)
        return ""
    t = NOTE_RE.sub(keep_original, t)
    if unscored_text(t) != unscored_text(text):
        return None, "port-arm"
    return t, {"var": v, "uses": len(edits)}


def candidates(text):
    out, cur, used, skipped = [], text, [], {}
    for v in constvars(text):
        new, info = rewrite_const(text, v)
        if new is None:
            skipped[v] = info; continue
        out.append(("argconst:" + v, new))
        nxt, _ = rewrite_const(cur, v)
        if nxt is not None:
            cur = nxt; used.append(v)
    if len(used) > 1:
        out.insert(0, ("argconst:*" + "+".join(used), cur))
    return out, skipped


class T:
    name = "t33_argconst"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not constvars(text):
            return "no pinned constant-valued local"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands, skipped = candidates(text)
        if not cands:
            return None, {"refused": ["no rewritable variable: " + ", ".join("%s %s" % kv for kv in sorted(skipped.items()))]}
        cands.sort(key=lambda c: len(sites_of(c[1])))              # most pins removed first
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
