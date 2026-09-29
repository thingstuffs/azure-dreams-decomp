"""T126: preprocessor splits that no longer split anything, collapsed (readability; pins untouched).

APPEARS     (1) `#ifdef X / A / #else / A / #endif` - two arms with the same tokens, left behind when a pin or a
                spelling difference between the builds went away (29 `__mips__` + 18 `NON_MATCHING` blocks on
                2026-09-29), and `#ifdef __mips__ / #endif` with nothing inside (24);
            (2) `#ifdef __mips__ / MIPS / #else / PORTABLE / #endif`: the mips arm holds the spelling that was
                needed for the bytes at the time (inline `.set noreorder` asm, a goto), the other arm the plain
                C.  r80_sonnet_gd20 found town/func_80097648's plain arm byte-exact on its own (2 gotos and a
                noreorder asm pair gone); 142 such blocks on 2026-09-29.
RESOLVES    (1) the one arm, no directives - the compiled tokens are identical by construction.
            (2) the portable arm alone, where the row stays byte-exact: all `__mips__` blocks at once first
                (their arms often open and close braces across blocks), then block by block, last first.
            Only `#ifdef/#ifndef X` and `#if 0`-free `#if` heads with a single `#else` are touched; `#elif`
            chains never.  Pins are never touched (their count may only fall with a dropped arm).
ACCEPTANCE  pins never grow; the number of conditional blocks strictly falls; step (2) must verify exact.
"""
import os, re, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of

MAX_VERIFY = int(os.environ.get("T126_MAX", "24"))
HEAD = re.compile(r"^[ \t]*#[ \t]*(ifdef|ifndef|if)\b[ \t]*(.*?)[ \t]*$")
ELSE = re.compile(r"^[ \t]*#[ \t]*else\b")
ELIF = re.compile(r"^[ \t]*#[ \t]*elif\b")
ENDIF = re.compile(r"^[ \t]*#[ \t]*endif\b")
MIPS_TRUE = {("ifdef", "__mips__"), ("if", "defined(__mips__)"), ("if", "defined(__mips__) || defined(mips)")}
MIPS_FALSE = {("ifndef", "__mips__"), ("if", "!defined(__mips__)")}


def blocks(lines):
    """[(head, else_or_None, endif, kind, cond, depth)] for every conditional block without #elif."""
    st, out = [], []
    for i, l in enumerate(lines):
        m = HEAD.match(l)
        if m:
            st.append([i, None, m.group(1), m.group(2), False]); continue
        if not st:
            continue
        if ELIF.match(l):
            st[-1][4] = True
        elif ELSE.match(l):
            if st[-1][1] is None: st[-1][1] = i
            else: st[-1][4] = True
        elif ENDIF.match(l):
            h, e, k, c, bad = st.pop()
            if not bad:
                out.append((h, e, i, k, c, len(st)))
    return out


def _norm(ls):
    return " ".join(re.sub(r"/\*.*?\*/|//[^\n]*", " ", "\n".join(ls), flags=re.S).split())


def collapsible(lines):
    """Blocks whose arms are the same tokens, or with an empty body and no #else: (head, endif, keep_lines)."""
    out = []
    for h, e, z, k, c, d in blocks(lines):
        if c.strip() == "0" and k == "if":
            continue
        if e is None:
            if not _norm(lines[h + 1:z]):
                out.append((h, z, []))
        elif _norm(lines[h + 1:e]) == _norm(lines[e + 1:z]):
            out.append((h, z, lines[h + 1:e]))
    return out


def collapse_all(text):
    lines = text.split("\n")
    while True:
        cs = collapsible(lines)
        if not cs:
            return "\n".join(lines)
        h, z, keep = max(cs, key=lambda x: x[0])      # innermost/last first, then re-scan
        lines = lines[:h] + keep + lines[z + 1:]


def mips_blocks(lines):
    """Top-level `__mips__` splits with two different arms: (head, else, endif, portable_first)."""
    out = []
    for h, e, z, k, c, d in blocks(lines):
        key = (k, " ".join(c.split()))
        if e is None or d != 0:
            continue
        if key in MIPS_TRUE:
            out.append((h, e, z, False))
        elif key in MIPS_FALSE:
            out.append((h, e, z, True))
    return out


def take_portable(text, chosen):
    lines = text.split("\n")
    mb = mips_blocks(lines)
    for i in sorted(chosen, key=lambda i: -mb[i][0]):
        h, e, z, pfirst = mb[i]
        keep = lines[h + 1:e] if pfirst else lines[e + 1:z]
        lines = lines[:h] + keep + lines[z + 1:]
    return "\n".join(lines)


def nblocks(text):
    return len(blocks(text.split("\n")))


class T:
    name = "t126_ppcollapse"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        lines = text.split("\n")
        return None if collapsible(lines) or mips_blocks(lines) else "no collapsible #if split"

    @staticmethod
    def apply_verified(text, row, census, vf):
        n0, b0 = len(sites_of(text)), nblocks(text)
        cur = collapse_all(text)                        # (1): compiled tokens identical, the sweep verifies it
        budget = [MAX_VERIFY]; tried = []

        def ok(t):
            if t == cur or len(sites_of(t)) > n0 or nblocks(t) >= nblocks(cur) or budget[0] <= 0:
                return False
            budget[0] -= 1; tried.append(1)
            return bool(vf(t).get("exact"))

        mb = mips_blocks(cur.split("\n"))
        took = 0
        if mb:
            allt = take_portable(cur, range(len(mb)))
            if ok(allt):
                cur, took = allt, len(mb)
            else:
                keep = []
                for i in sorted(range(len(mb)), key=lambda i: -mb[i][0]):
                    if ok(take_portable(cur, keep + [i])):
                        keep.append(i)
                if keep:
                    cur, took = take_portable(cur, keep), len(keep)
        if cur == text or len(sites_of(cur)) > n0 or nblocks(cur) >= b0:
            return None, {"refused": ["nothing collapsed (%d verifies)" % len(tried)]}
        return cur, {"blocks": b0 - nblocks(cur), "portable": took, "verifies": len(tried)}
