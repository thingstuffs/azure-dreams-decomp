"""T38: a value staged through a pinned hard-register local, stored directly.

APPEARS     `X = E;` immediately followed by `LHS = (cast)X;`, where X is an `ASM_REG`-pinned local and the
            staged value has no other reader before X is next assigned. 2026-09-12: 379 sites in 195 rows.
RESOLVES    the staged producer is a hard-register insn, and an ordinary pseudo gets another ready-list
            rank in the first scheduler, which moves the neighbouring instructions. Astra lane,
            dungeon/func_8188E3A0: `effect->unk_10 = D_800255E8;` in place of staging it through the
            `v0`-pinned `addr_or_coord` made the `$4` pin of the next call's argument unnecessary. The
            pin a rewrite frees is usually ANOTHER one, so each inlining is paired with each single pin
            erasure, nearest first. X and its own pins stay (X is used elsewhere).
"""
import re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of, unscored_text
from pin_sites import erase_many
try:
    from .t29_addrsym import mask_comments
except ImportError:
    from t29_addrsym import mask_comments

STAGE = (r"^[ \t]*%s\s*=(?!=)\s*(?P<e>[^;]+);[ \t]*\n(?P<ind>[ \t]*)(?P<lhs>[^;=\n]+?)\s*=\s*"
         r"(?P<cast>\([^()]*\)\s*)?%s\s*;")
MAX_CANDS = 40
PINS_PER_SITE = 8


def stagings(text):
    """(X, start, end, E, LHS, cast, indent) for each staging whose value has no other reader."""
    m = mask_comments(text)
    out = []
    for X in set(re.findall(r"register\s+[\w\s\*]+?\b(\w+)\s+ASM_REG\(", m)):
        for mm in re.finditer(STAGE % (re.escape(X), re.escape(X)), m, re.M):
            lhs = mm.group("lhs").strip()
            if re.search(r"[-+*/%&|^<>!]$", lhs) or re.search(r"\b%s\b" % re.escape(X), lhs):
                continue                                          # compound assignment, or X on the left
            rest = m[mm.end():]
            nxt = re.search(r"\b%s\b" % re.escape(X), rest)
            if nxt and not re.match(r"\s*=(?!=)", rest[nxt.end():]):
                continue                                          # the staged value is read again
            out.append((X, mm.start(), mm.end(), mm.group("e").strip(), lhs,
                        (mm.group("cast") or "").strip(), mm.group("ind")))
    return sorted(out, key=lambda s: s[1])


def inlined(text, st):
    X, a, b, e, lhs, cast, ind = st
    rhs = []
    cm = re.fullmatch(r"\(\s*[A-Za-z_][\w\s\*]*\)\s*([A-Za-z_]\w*)", e)
    if cm:
        rhs.append(cm.group(1))                                   # a cast symbol stored as itself, first
    unary = re.fullmatch(r"(?:\(\s*[A-Za-z_][\w\s\*]*\)\s*)*(?:[A-Za-z_][\w.\[\]>-]*|-?(?:0x[0-9A-Fa-f]+|\d+)[UuLl]*)", e)
    rhs.append(cast + e if (not cast or unary) else cast + "(" + e + ")")
    return [text[:a] + ind + lhs + " = " + r + ";" + text[b:] for r in dict.fromkeys(rhs)]


def drop_unused(text, X):
    """X's declaration goes when the inlining and its pin erasure leave nothing else naming X."""
    m = mask_comments(text)
    if len(re.findall(r"\b%s\b" % re.escape(X), m)) != 1:
        return text
    d = re.search(r"\n[ \t]*(?:register[ \t]+)?[A-Za-z_][\w \t\*]*?\b%s[ \t]*;[^\n]*(?=\n)" % re.escape(X), m)
    return text[:d.start()] + text[d.end():] if d else text


def candidates(text):
    out, seen = [], set()
    for st in stagings(text):
        for t1 in inlined(text, st):
            if unscored_text(t1) != unscored_text(text):
                continue
            pins = sorted(sites_of(t1), key=lambda s: abs(s[3] - st[1]))[:PINS_PER_SITE]
            for p in pins:
                t = drop_unused(erase_many(t1, [p], clean_notes=True), st[0])
                if t not in seen and unscored_text(t) == unscored_text(text):
                    seen.add(t); out.append(("unstage:%s@%d-%s" % (st[0], st[1], p[1]), t))
            if len(out) >= MAX_CANDS:
                return out[:MAX_CANDS]
    return out


class T:
    name = "t38_unstage"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not stagings(text):
            return "no staged store through a pinned local"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands = candidates(text)
        if not cands:
            return None, {"refused": ["no buildable candidate"]}
        for label, t in cands:                                    # nearest pin first
            if vf(t).get("exact"):
                return t, {"label": label}
        return None, {"refused": ["no candidate exact at the recorded cell"]}
