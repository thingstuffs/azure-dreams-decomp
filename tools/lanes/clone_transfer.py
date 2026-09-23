#!/usr/bin/env python3
"""Clone transfer: replay one solved row's base->out edit on its still-pinned clones.

APPEARS.  The tree is full of CLONE FAMILIES - near-identical functions in different overlays that
differ only in their addresses (`D_8016AB64` vs `D_80170B64`), their struct tags (`S_8016A86C_3` vs
`S_8017086C_3`) and the odd constant: ten `$20 *outer` spawners, five `ASM_KEEP(elem)` rows, the
item-target rows, the sprite-spawn rows.  A model lane solves ONE member (work/native_lane/<lane>/
base/<row>.c is the pinned text it started from, out/<row>.c the byte-exact rewrite); the siblings
stay pinned until someone ports the same move with the sibling's own identifiers.

RESOLVES.  Nothing by itself - it carries an already-proven C shape across a family.  The pins fall
in the sibling for the reason they fell in the exemplar (dungeon/func_80EB506C, r64_astra_bivhide:
both loop updates moved after the call and the constants folded into it, four constraints at once).

CANDIDATES.  For each (base, out) pair whose out has fewer pin sites:
  * SIBLINGS - pinned rows whose identifier-normalised line signatures match the exemplar's BASE
    (line count prefilter, then a token-shingle Jaccard, then difflib ratio >= --threshold).
  * MAP - the two BASE texts are aligned line by line on those signatures; the identifiers, numbers
    and strings of every aligned equal-signature line pair give exemplar -> sibling substitutions.
  * REPLAY - the exemplar's base->out grouped hunks (difflib, 3 lines of context) are each located
    in the sibling through that alignment and spliced in with the substitutions applied.  A hunk
    whose span does not align contiguously, or which needs an address-bearing identifier the map
    does not know, is REFUSED; the remaining hunks are still tried (a partial transfer that drops
    pins is a win).  Candidates: all hunks together, then each hunk alone.
  * JUDGE - screen.compile_s against the sibling's PINNED listing first (free), then the byte
    scorer on listing-exact candidates, at most --max-verify runs per sibling, with gen_drive's
    unscored_text guard.  Exact results are staged as a lane (out/<container>/<name>.c + .base_sha),
    never landed.

ROUND 76 (aligner v2, --aligner v1|v2|both, default both).  v1 needed the 3 raw lines around a hunk
to align contiguously; 22 of 38 siblings of r73_h3_clones were refused on that.  v2 works in CODE-LINE
space (blank and comment-only lines invisible), cuts the edit twice (3-line groups and bare changed
runs, so two pins a few lines apart can go alone), locates each hunk through the code-line alignment
or else as an exact occurrence of its window (2, 1, then 0 code lines of context; nearest the
predicted position), and never refuses on a number the file maps two ways (the hunk's own lines
decide, else it stays literal).  An unmapped address-bearing identifier still refuses.  Siblings are
COMPOSED: after an exact, the remaining exemplars re-run on the new text (--no-compose to stop).
--transplant LEDGER adds every family member's CURRENT text as an exemplar for its siblings (from
tools/lanes/clone_families.py): a less-pinned member is the best exemplar a family has.  The JUDGE
is unchanged.

    python3 tools/lanes/clone_transfer.py --families                 # who is a clone of whom
    python3 tools/lanes/clone_transfer.py --lane r76_clones --lanes-glob 'r5*,r6*,r7*' \
        --transplant ledger/clone_families.jsonl --max-exemplars-per-sibling 12 --workers 12
    python3 tools/lanes/clone_transfer.py --only dungeon/func_80EBB06C --workers 2
    python3 tools/lanes/clone_transfer.py --lane r65_clone_transfer --workers 4
"""
from __future__ import annotations

import argparse
import collections
import difflib
import json
import re
import sys
import tempfile
import threading
import time
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools/xform"))

from common import rows, clean_path, sha_text  # noqa: E402
from pin_census import sites_of, unscored_text  # noqa: E402

# The model lanes harvested for exemplars (a lane needs both base/ and out/).
LANES = (
    [f"r59_sol_large{s}" for s in ("", "2", "3", "4", "5", "6", "7", "8", "9")]
    + [f"r59_sol_mid{s}" for s in ("", "2", "3", "4", "5", "6")]
    + ["r59_sol_far", "r59_sol_far2", "r59_sol_residues"]
    + ["r60_sol_largep4_1", "r60_sol_midp4_1", "r60_sol_midp4_2"]
    + [f"r60_sol_farp4_{i}" for i in range(1, 7)]
    + [f"r61_sol_gemmoved_{i}" for i in range(1, 5)]
    + [f"r61_sol_far13_{i}" for i in range(1, 4)]
    + ["r62_astra_families", "r62_astra_big", "r62_astra_alloc"]
    + ["r63_astra_movemove", "r63_astra_moveli", "r63_astra_loadmove",
       "r63_astra_prologue", "r63_astra_recolour"]
    + ["r64_astra_loop", "r64_astra_bivhide", "r61_alloc_study"]   # alloc_study's base/ is the
    # pre-landing text recovered from git (`git show 428ef17f^:src/<c>/<f>.c`): the lane kept only out/
    + [f"r58_order{s}" for s in [""] + [str(i) for i in range(2, 17)]]
)

# ---------------------------------------------------------------------------------------------
# normalisation

KEYWORDS = {
    "auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else",
    "enum", "extern", "float", "for", "goto", "if", "inline", "int", "long", "register",
    "return", "short", "signed", "sizeof", "static", "struct", "switch", "typedef", "union",
    "unsigned", "void", "volatile", "while",
}
TYPES = {"u8", "s8", "u16", "s16", "u32", "s32", "u64", "s64", "f32", "f64", "vu8", "vs8",
         "vu16", "vs16", "vu32", "vs32", "size_t", "uintptr_t", "intptr_t", "bool"}
DIRECTIVES = {"include", "define", "undef", "ifdef", "ifndef", "endif", "elif", "pragma",
              "defined", "NON_MATCHING", "NULL"}
# an identifier carrying an address (D_80170B64, func_8017086C, S_8017086C_3): porting one of
# these into a sibling unmapped would be silently wrong, so an unmapped one refuses its hunk.
ADDR_RE = re.compile(r"[0-9A-Fa-f]{8}")

TOK_RE = re.compile(
    r"""(?P<str>"(?:[^"\\\n]|\\.)*"|'(?:[^'\\\n]|\\.)*')
       |(?P<num>(?:0[xX][0-9a-fA-F]+|\d+(?:\.\d*)?(?:[eE][-+]?\d+)?)[uUlLfF]*)
       |(?P<id>[A-Za-z_]\w*)
       |(?P<op><<=|>>=|\.\.\.|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||[-+*/%&|^!<>=]=)
       |(?P<punct>[^\s])""",
    re.X,
)
_BLOCK = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)


def mask_comments(text: str) -> str:
    """`text` with every comment replaced by spaces: offsets and line structure are preserved,
    so a token span found in the mask is the same span in the original."""
    return _BLOCK.sub(lambda m: re.sub(r"[^\n]", " ", m.group(0)), text)


def tokens_of(line: str):
    """[(kind, text, start, end)] of one comment-masked line."""
    out = []
    for m in TOK_RE.finditer(line):
        kind = m.lastgroup
        out.append((kind, m.group(0), m.start(), m.end()))
    return out


def norm_token(kind: str, text: str) -> str:
    """One token of the identifier-normalised stream: keywords, types, directive words and the
    ASM_* pin macros keep their spelling; every other name is `I`, numbers `N`, strings `S`."""
    if kind == "id":
        if text in KEYWORDS or text in TYPES or text in DIRECTIVES or text.startswith("ASM_"):
            return text
        return "I"
    if kind == "num":
        return "N"
    if kind == "str":
        return "S"
    return text


def line_sig(line: str):
    return tuple(norm_token(k, t) for k, t, _, _ in tokens_of(line))


class Doc:
    """A C file as the transfer sees it: raw lines, comment-masked lines, per-line tokens and
    per-line normalised signatures, plus a token-shingle sketch for the prefilter."""

    __slots__ = ("name", "text", "lines", "masked", "toks", "sigs", "shingles", "nlines")

    def __init__(self, name: str, text: str):
        self.name = name
        self.text = text
        self.lines = text.splitlines()
        self.masked = mask_comments(text).splitlines()
        # a trailing newline difference must not shift the line lists
        while len(self.masked) < len(self.lines):
            self.masked.append("")
        self.toks = [tokens_of(l) for l in self.masked]
        self.sigs = [tuple(norm_token(k, t) for k, t, _, _ in ts) for ts in self.toks]
        self.nlines = len([s for s in self.sigs if s])
        self.shingles = shingle_set(self.sigs)


def shingle_set(sigs, k: int = 4):
    """Hashes of the k-grams of the flattened normalised token stream (blank lines dropped)."""
    flat = [t for s in sigs for t in s]
    if len(flat) < k:
        return frozenset({hash(tuple(flat))}) if flat else frozenset()
    return frozenset(hash(tuple(flat[i:i + k])) for i in range(len(flat) - k + 1))


def jaccard(a: frozenset, b: frozenset) -> float:
    if not a or not b:
        return 0.0
    inter = len(a & b)
    return inter / (len(a) + len(b) - inter)


def similarity(a: Doc, b: Doc) -> float:
    """difflib ratio over the two line-signature sequences (blank lines dropped)."""
    sa = [s for s in a.sigs if s]
    sb = [s for s in b.sigs if s]
    return difflib.SequenceMatcher(None, sa, sb, autojunk=False).ratio()


# ---------------------------------------------------------------------------------------------
# alignment and identifier map

def alignment(a: Doc, b: Doc):
    """{line index in a: line index in b} for the lines difflib calls equal on their signatures."""
    sm = difflib.SequenceMatcher(None, a.sigs, b.sigs, autojunk=False)
    out = {}
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            for d in range(i2 - i1):
                out[i1 + d] = j1 + d
    return out


def identifier_map(a: Doc, b: Doc, align):
    """(map, ambiguous): exemplar spelling -> sibling spelling, read off the aligned equal lines.
    A name that maps two ways is dropped into `ambiguous` (using it refuses the hunk)."""
    seen = {}
    ambiguous = set()
    for i, j in align.items():
        ta, tb = a.toks[i], b.toks[j]
        if len(ta) != len(tb):
            continue
        for (ka, xa, _, _), (kb, xb, _, _) in zip(ta, tb):
            if ka != kb or ka not in ("id", "num", "str"):
                continue
            if norm_token(ka, xa) != "I" and ka == "id":
                continue                      # keywords/types/ASM_ macros map to themselves
            if xa in seen and seen[xa] != xb:
                ambiguous.add(xa)
            seen[xa] = xb
    for x in ambiguous:
        seen.pop(x, None)
    return seen, ambiguous


class Refused(Exception):
    pass


def port_line(line: str, mapping, ambiguous, indent_delta: int = 0) -> str:
    """One exemplar out line rewritten with the sibling's names, constants and strings."""
    masked = mask_comments(line)
    out = []
    pos = 0
    for kind, text, s, e in tokens_of(masked):
        out.append(line[pos:s])
        if kind in ("id", "num", "str") and norm_token(kind, text) in ("I", "N", "S"):
            if text in ambiguous:
                raise Refused(f"ambiguous mapping for {text}")
            if text in mapping:
                out.append(mapping[text])
            else:
                if kind == "id" and ADDR_RE.search(text):
                    raise Refused(f"unmapped address symbol {text}")
                out.append(text)
        else:
            out.append(line[s:e])
        pos = e
    out.append(line[pos:])
    new = "".join(out)
    # comments carry the exemplar's names too (`/* obj in func_8017086C */`); only an
    # address-bearing name is ported - the rest of a comment is English, not code
    def word(m):
        t = m.group(0)
        return mapping.get(t, t) if ADDR_RE.search(t) else t
    parts = []
    last = 0
    for m in _BLOCK.finditer(new):
        parts.append(new[last:m.start()])
        parts.append(re.sub(r"[A-Za-z_]\w*", word, m.group(0)))
        last = m.end()
    parts.append(new[last:])
    new = "".join(parts)
    if indent_delta and new.strip():
        if indent_delta > 0:
            new = " " * indent_delta + new
        else:
            strip = min(-indent_delta, len(new) - len(new.lstrip(" ")))
            new = new[strip:]
    return new


# ---------------------------------------------------------------------------------------------
# hunks

def hunks_of(base_lines, out_lines):
    """The exemplar's base->out edit as grouped hunks (3 lines of context), whitespace-only
    groups dropped.  Raw opcodes would cut one move into half a dozen fragments that mean
    nothing alone; a group is the unit a sibling can take."""
    sm = difflib.SequenceMatcher(None, base_lines, out_lines, autojunk=False)
    out = []
    for group in sm.get_grouped_opcodes(3):
        b1, b2 = group[0][1], group[-1][2]
        j1, j2 = group[0][3], group[-1][4]
        a_code = [l.strip() for l in base_lines[b1:b2] if l.strip()]
        b_code = [l.strip() for l in out_lines[j1:j2] if l.strip()]
        if a_code == b_code:
            continue                                   # blank lines only: cannot move a pin
        changed = [op for op in group if op[0] != "equal"]
        out.append({"b1": b1, "b2": b2, "j1": j1, "j2": j2,
                    "i1": changed[0][1], "i2": changed[-1][2],      # the changed base lines
                    "k1": changed[0][3], "k2": changed[-1][4]})     # and their replacement
    return out


def hunk_span(h, ctx):
    """The (base, out) line ranges of a hunk with `ctx` lines of context on each side: the whole
    group at ctx=3, the changed lines alone at ctx=0.  The leading and trailing context is equal
    text, so the two ranges shrink together."""
    lead = min(ctx, h["i1"] - h["b1"], h["k1"] - h["j1"])
    tail = min(ctx, h["b2"] - h["i2"], h["j2"] - h["k2"])
    return h["i1"] - lead, h["i2"] + tail, h["k1"] - lead, h["k2"] + tail


def local_map(a: Doc, b: Doc, span, offset):
    """The substitutions read off one hunk's own aligned lines (b line = a line + offset).  A
    name the whole-file map cannot decide - `func_800AFDD0` called in one place and another
    callee in the next - is decided here, where the replay actually needs it."""
    out, bad = {}, set()
    for i in span:
        j = i + offset
        if not (0 <= j < len(b.toks)) or a.sigs[i] != b.sigs[j]:
            continue
        for (ka, xa, _, _), (kb, xb, _, _) in zip(a.toks[i], b.toks[j]):
            if ka != kb or ka not in ("id", "num", "str") or norm_token(ka, xa) not in ("I", "N", "S"):
                continue
            if xa in out and out[xa] != xb:
                bad.add(xa)
            out[xa] = xb
    for x in bad:
        out.pop(x, None)
    return out


def transfer(exemplar: Doc, out_doc: Doc, sib: Doc, hunks, align, mapping, ambiguous, pick=None,
             ctx=3, align_out=None):
    """Replay the selected hunks on the sibling's lines.  Returns (text|None, applied, refusals).

    `ctx` is how much of a hunk's context must align before it may be spliced: 3 lines is the
    grouped diff's own window, 1 or 0 is the retry for a sibling that diverges from the exemplar
    beside the move (a landed fix of its own, a comment the exemplar carries).  `align_out` is the
    alignment of the exemplar's OUT text to the sibling: it tells a hunk already present in the
    sibling from one whose context is simply gone."""
    lines = list(sib.lines)
    applied, refusals = [], []
    chosen = list(range(len(hunks))) if pick is None else list(pick)
    for idx, h in sorted(((i, hunks[i]) for i in chosen), key=lambda t: -t[1]["b1"]):
        b1, b2, j1, j2 = hunk_span(h, ctx)
        span = range(b1, b2)
        aligned = all(i in align for i in span)
        if aligned:
            start = align[b1]
            aligned = all(align[i] == start + (i - b1) for i in span)
            if not aligned:
                refusals.append([idx, "aligned context is not contiguous"])
                continue
        if not aligned:
            if align_out is not None and all(i in align_out for i in range(j1, j2)):
                refusals.append([idx, "already applied in the sibling"])
            else:
                refusals.append([idx, "context does not align"])
            continue
        # only the CHANGED lines are replaced: the sibling keeps its own context (and its own
        # comments), and an insert lands where its context says it does
        core_s, core_e = start + (h["i1"] - b1), start + (h["i2"] - b1)
        # the sibling's own indentation at the first context line
        delta = 0
        first = exemplar.lines[b1]
        sfirst = sib.lines[start] if start < len(sib.lines) else ""
        if first.strip() and sfirst.strip():
            delta = (len(sfirst) - len(sfirst.lstrip(" "))) - (len(first) - len(first.lstrip(" ")))
        # a name that maps two ways across the file is read off THIS hunk's own aligned lines
        local = local_map(exemplar, sib, range(b1, b2), start - b1)
        m = dict(mapping, **local)
        try:
            repl = [port_line(l, m, ambiguous - set(local), delta) for l in out_doc.lines[h["k1"]:h["k2"]]]
        except Refused as e:
            refusals.append([idx, str(e)])
            continue
        lines[core_s:core_e] = repl
        applied.append(idx)
    if not applied:
        return None, applied, refusals
    text = "\n".join(lines)
    if sib.text.endswith("\n"):
        text += "\n"
    return text, sorted(applied), refusals


def candidates_for(exemplar: Doc, out_doc: Doc, sib: Doc, max_candidates: int = 8):
    """[(text, applied hunks, refusals)] - all hunks together, then each hunk alone, at 3 lines of
    required context and then at 1 (a sibling that diverges from the exemplar next to the move)."""
    hunks = hunks_of(exemplar.lines, out_doc.lines)
    if not hunks:
        return [], hunks, {}, set()
    align = alignment(exemplar, sib)
    align_out = alignment(out_doc, sib)
    mapping, ambiguous = identifier_map(exemplar, sib, align)
    cands, seen, shown = [], set(), None
    picks = [None] + ([[i] for i in range(len(hunks))] if len(hunks) > 1 else [])
    for ctx in (3, 1):
        for pick in picks:
            text, applied, refusals = transfer(exemplar, out_doc, sib, hunks, align, mapping,
                                               ambiguous, pick, ctx=ctx, align_out=align_out)
            if text is None or text == sib.text or text in seen:
                if text is None and pick is None and shown is None:
                    shown = (None, {"hunks": [], "ctx": ctx}, refusals)   # carries the refusals
                continue
            seen.add(text)
            cands.append((text, {"hunks": applied, "ctx": ctx}, refusals))
            if len(cands) >= max_candidates:
                return cands, hunks, mapping, ambiguous
    if not cands and shown is not None:
        cands.append(shown)
    return cands, hunks, mapping, ambiguous


# ---------------------------------------------------------------------------------------------
# aligner v2 (round 76): code-line space, anchored windows, per-pin hunks

def code_index(doc: Doc):
    """[raw line index] of the lines that carry code (a non-empty signature): blank lines and
    comment-only lines are invisible to the v2 aligner, so a sibling-only comment or blank line
    can no longer break a hunk's context (v1's 'aligned context is not contiguous')."""
    return [i for i, s in enumerate(doc.sigs) if s]


def _code_range(idx, r1, r2):
    """The code-line range [c1, c2) of the raw line range [r1, r2); an empty range sits at the
    number of code lines before r1."""
    import bisect
    return bisect.bisect_left(idx, r1), bisect.bisect_left(idx, r2)


def hunks_v2(base: Doc, out: Doc):
    """The exemplar's edit as hunks, twice: difflib's 3-line groups (a move whose parts belong
    together) and the bare changed runs (0 lines of context: two pins four lines apart are two
    hunks, which v1's 'each hunk alone' could not separate).  Deduplicated; whitespace- and
    comment-only changes dropped.  Each hunk: raw ranges b1:b2 (base) -> k1:k2 (out)."""
    sm = difflib.SequenceMatcher(None, base.lines, out.lines, autojunk=False)
    seen, outl = set(), []
    for ctx in (3, 0):
        for group in sm.get_grouped_opcodes(ctx):
            changed = [op for op in group if op[0] != "equal"]
            if not changed:
                continue
            b1, b2, k1, k2 = changed[0][1], changed[-1][2], changed[0][3], changed[-1][4]
            if [s for s in base.sigs[b1:b2] if s] == [s for s in out.sigs[k1:k2] if s] and \
                    [t[1] for l in base.toks[b1:b2] for t in l] == [t[1] for l in out.toks[k1:k2] for t in l]:
                continue                              # blank lines / comments only: cannot move a pin
            if (b1, b2, k1, k2) in seen:
                continue
            seen.add((b1, b2, k1, k2))
            outl.append({"b1": b1, "b2": b2, "k1": k1, "k2": k2, "ctx": ctx})
    return outl


def _find_all(hay, needle):
    n = len(needle)
    if n == 0:
        return []
    first = needle[0]
    return [p for p in range(len(hay) - n + 1) if hay[p] == first and hay[p:p + n] == needle]


def locate_v2(base: Doc, sib: Doc, bidx, sidx, c1, c2, calign, ctx):
    """Where the base code lines [c1, c2) sit in the sibling's code lines, or (None, reason).

    The window is the changed code lines plus `ctx` code lines of context each side (clipped at
    the file ends).  Found (1) through the global code-line alignment when the whole window is
    aligned contiguously, else (2) as an exact occurrence of the window's signature sequence in
    the sibling - the occurrence nearest the position the alignment predicts when there are
    several.  Returns the sibling code index of c1."""
    bs = [base.sigs[i] for i in bidx]
    ss = [sib.sigs[i] for i in sidx]
    w1, w2 = max(0, c1 - ctx), min(len(bs), c2 + ctx)
    if w2 <= w1:
        return None, "empty window"
    if all(i in calign for i in range(w1, w2)):
        st = calign[w1]
        if all(calign[i] == st + (i - w1) for i in range(w1, w2)):
            return st + (c1 - w1), None
    hits = _find_all(ss, bs[w1:w2])
    if not hits:
        return None, "context does not align"
    # predicted position: the nearest aligned code line before the window
    pred = None
    for i in range(w1, -1, -1):
        if i in calign:
            pred = calign[i] + (w1 - i)
            break
    if pred is None:
        pred = w1
    if len(hits) > 1 and ctx == 0 and len(set(abs(h - pred) for h in hits)) < len(hits):
        return None, "ambiguous anchor"
    best = min(hits, key=lambda h: abs(h - pred))
    return best + (c1 - w1), None


def code_alignment(a: Doc, b: Doc, aidx, bidx):
    """{a code index: b code index} for the code lines difflib calls equal on their signatures."""
    sm = difflib.SequenceMatcher(None, [a.sigs[i] for i in aidx], [b.sigs[i] for i in bidx],
                                 autojunk=False)
    out = {}
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            for d in range(i2 - i1):
                out[i1 + d] = j1 + d
    return out


def identifier_map_v2(a: Doc, b: Doc, aidx, bidx, calign):
    """(map, ambiguous names): v1's map read off the code-line alignment.  A NUMBER that maps two
    ways is not an ambiguity to refuse on: it is left to the hunk's local map, else kept literal
    (the judge is the exactness gate)."""
    seen, amb = {}, set()
    for i, j in calign.items():
        ta, tb = a.toks[aidx[i]], b.toks[bidx[j]]
        if len(ta) != len(tb):
            continue
        for (ka, xa, _, _), (kb, xb, _, _) in zip(ta, tb):
            if ka != kb or ka not in ("id", "num", "str") or norm_token(ka, xa) not in ("I", "N", "S"):
                continue
            if xa in seen and seen[xa] != xb:
                amb.add(xa)
            seen[xa] = xb
    for x in amb:
        seen.pop(x, None)
    return seen, {x for x in amb if not re.match(r"[0-9]", x)}


def transfer_v2(base: Doc, out: Doc, sib: Doc, hunks, pick, ctx, prep):
    """Replay the picked hunks on the sibling.  Returns (text|None, applied, refusals)."""
    bidx, sidx, oidx, calign, oalign, mapping, amb = prep
    lines = list(sib.lines)
    applied, refusals, spans = [], [], []
    todo = []
    for n in pick:
        h = hunks[n]
        c1, c2 = _code_range(bidx, h["b1"], h["b2"])
        pos, why = locate_v2(base, sib, bidx, sidx, c1, c2, calign, ctx)
        if pos is None:
            # the exemplar's OUT text already present in the sibling: not a refusal to chase
            o1, o2 = _code_range(oidx, h["k1"], h["k2"])
            if o2 > o1 and locate_v2(out, sib, oidx, sidx, o1, o2, oalign, max(ctx, 1))[0] is not None:
                why = "already applied in the sibling"
            refusals.append([n, why])
            continue
        # sibling raw range: its code lines pos..pos+(c2-c1), plus any comment/blank lines between them
        if c2 > c1:
            r1, r2 = sidx[pos], sidx[pos + (c2 - c1) - 1] + 1
        else:                                            # a pure insertion: after the previous code line
            r1 = r2 = (sidx[pos - 1] + 1) if pos > 0 else 0
        if any(not (r2 <= s1 or s2 <= r1) or (r1 == r2 == s1 == s2) for s1, s2 in spans):
            refusals.append([n, "overlaps another hunk"])
            continue
        # local substitutions: the window's own aligned lines
        local, bad = {}, set()
        for d in range(-max(ctx, 3), (c2 - c1) + max(ctx, 3)):
            i, j = c1 + d, pos + d
            if not (0 <= i < len(bidx) and 0 <= j < len(sidx)):
                continue
            ta, tb = base.toks[bidx[i]], sib.toks[sidx[j]]
            if base.sigs[bidx[i]] != sib.sigs[sidx[j]]:
                continue
            for (ka, xa, _, _), (kb, xb, _, _) in zip(ta, tb):
                if ka != kb or ka not in ("id", "num", "str") or norm_token(ka, xa) not in ("I", "N", "S"):
                    continue
                if xa in local and local[xa] != xb:
                    bad.add(xa)
                local[xa] = xb
        for x in bad:
            local.pop(x, None)
        m = dict(mapping, **local)
        delta = 0
        if c2 > c1:
            fb, fs = base.lines[bidx[c1]], sib.lines[sidx[pos]]
            delta = (len(fs) - len(fs.lstrip(" "))) - (len(fb) - len(fb.lstrip(" ")))
        try:
            refuse = (amb | {x for x in bad if not re.match(r"[0-9]", x)}) - set(local)
            repl = [port_line(l, m, refuse, delta) for l in out.lines[h["k1"]:h["k2"]]]
        except Refused as e:
            refusals.append([n, str(e)])
            continue
        spans.append((r1, r2))
        todo.append((r1, r2, repl, n))
    for r1, r2, repl, n in sorted(todo, key=lambda t: (-t[0], -t[1])):
        lines[r1:r2] = repl
        applied.append(n)
    if not applied:
        return None, applied, refusals
    text = "\n".join(lines)
    if sib.text.endswith("\n"):
        text += "\n"
    return text, sorted(applied), refusals


def candidates_v2(base: Doc, out: Doc, sib: Doc, max_candidates: int = 12):
    """[(text, info, refusals)] - every 3-line group together, every bare run together, then each
    hunk alone; at 2 code lines of anchored context, then 1, then 0 (the changed lines alone,
    unique in the sibling).  Same return shape as v1's candidates_for."""
    hunks = hunks_v2(base, out)
    if not hunks:
        return [], hunks, {}, set()
    bidx, sidx, oidx = code_index(base), code_index(sib), code_index(out)
    calign = code_alignment(base, sib, bidx, sidx)
    oalign = code_alignment(out, sib, oidx, sidx)
    mapping, amb = identifier_map_v2(base, sib, bidx, sidx, calign)
    prep = (bidx, sidx, oidx, calign, oalign, mapping, amb)
    g3 = [i for i, h in enumerate(hunks) if h["ctx"] == 3]
    g0 = [i for i, h in enumerate(hunks) if h["ctx"] == 0]
    picks = [g3, g0] + [[i] for i in g0] + [[i] for i in g3 if len(g3) > 1]
    cands, seen, shown = [], set(), None
    for ctx in (2, 1, 0):
        for pick in picks:
            if not pick:
                continue
            text, applied, refusals = transfer_v2(base, out, sib, hunks, pick, ctx, prep)
            if text is None or text == sib.text or text in seen:
                if text is None and shown is None:
                    shown = (None, {"hunks": [], "ctx": ctx, "aligner": "v2"}, refusals)
                continue
            seen.add(text)
            cands.append((text, {"hunks": applied, "ctx": ctx, "aligner": "v2"}, refusals))
            if len(cands) >= max_candidates:
                return cands, hunks, mapping, amb
    if not cands and shown is not None:
        cands.append(shown)
    return cands, hunks, mapping, amb


# ---------------------------------------------------------------------------------------------
# exemplars and siblings

def load_exemplars(lanes=LANES, verbose=False):
    """[(lane, row_id, base Doc, out Doc, pins_in, pins_out)] for every pair whose out text has
    fewer pin sites than its base."""
    out, seen = [], set()
    for lane in lanes:
        d = ROOT / "work/native_lane" / lane
        ob, bb = d / "out", d / "base"
        if not (ob.is_dir() and bb.is_dir()):
            continue
        for f in sorted(ob.rglob("*.c")):
            rel = f.relative_to(ob)
            b = bb / rel
            if not b.exists():
                continue
            bt = b.read_text(errors="replace")
            ot = f.read_text(errors="replace")
            pin, pout = len(sites_of(bt)), len(sites_of(ot))
            if pout >= pin or len(rel.parts) != 2:
                continue
            rid = str(rel)[:-2]                       # <container>/<name>
            key = (rid, sha_text(bt), sha_text(ot))
            if key in seen:
                continue                              # the same move from another lane
            seen.add(key)
            out.append({"lane": lane, "id": rid, "base": Doc(rid, bt), "out": Doc(rid, ot),
                        "pins_in": pin, "pins_out": pout, "proof": exemplar_proof(rid, ot, pout)})
    return out


_SRC = {}


def exemplar_proof(rid, out_text, pins_out):
    """How far an exemplar's out text is known to be byte-exact: 'landed' (src/ holds exactly this
    text), 'superseded' (src/ has since reached as few pins or fewer), else 'unproven' (a model
    lane's out/ is its best attempt, not proof).  Proven exemplars are tried first."""
    if not _SRC:
        for r in rows():
            _SRC[r["id"]] = r
    r = _SRC.get(rid)
    if r is None or not clean_path(r).exists():
        return "unproven"
    t = clean_path(r).read_text(errors="replace")
    if t == out_text:
        return "landed"
    return "superseded" if len(sites_of(t)) <= pins_out else "unproven"


PROOF_RANK = {"landed": 0, "superseded": 1, "unproven": 2}


def lanes_matching(globs):
    """Lane names under work/native_lane matching comma-separated globs that have base/ and out/."""
    out = []
    for g in globs.split(","):
        for d in sorted((ROOT / "work/native_lane").glob(g.strip())):
            if (d / "base").is_dir() and (d / "out").is_dir() and d.name not in out:
                out.append(d.name)
    return out


def pinned_index(containers=("town", "dungeon", "main", "slus")):
    """[(row, Doc)] for every currently pinned row of those containers."""
    out = []
    for r in rows():
        if r["container"] not in containers:
            continue
        p = clean_path(r)
        if not p.exists():
            continue
        t = p.read_text(errors="replace")
        if not sites_of(t):
            continue
        out.append((r, Doc(r["id"], t)))
    return out


_FAM = {}


def _family_of(k):
    """One exemplar against the pinned index (a fork worker: reads _FAM)."""
    ex = _FAM["exemplars"][k]
    threshold, floor, jac_floor, span = _FAM["args"]
    ed = ex["base"]
    hits, pairs = [], []
    for r, d in _FAM["index"]:
        if r["id"] == ex["id"]:
            continue
        if not (1 - span) * ed.nlines <= d.nlines <= (1 + span) * ed.nlines:
            continue
        lo, hi = sorted((ed.nlines, d.nlines))
        if hi and 2 * lo / (lo + hi) < floor:          # difflib ratio <= 2*min/(a+b)
            continue
        if jaccard(ed.shingles, d.shingles) < jac_floor:
            continue
        s = similarity(ed, d)
        if s >= floor:
            pairs.append((round(s, 4), ex["id"], r["id"], s >= threshold))
        if s >= threshold:
            hits.append((round(s, 4), r["id"]))
    hits.sort(reverse=True)
    return ex["id"] + "@" + ex["lane"], hits, pairs


def families(exemplars, index, threshold=0.85, floor=0.5, jac_floor=0.12, span=0.6, workers=1):
    """{exemplar id@lane: [(similarity, row id)]} plus every pair above `floor` (for the distribution).
    Prefilter: line count within +-span (and the ratio bound), then the token-shingle Jaccard, then
    the difflib ratio.  `workers` > 1 forks a process pool (the pairs are pure CPU)."""
    global _FAM
    _FAM = {"exemplars": exemplars, "index": index, "args": (threshold, floor, jac_floor, span)}
    fams, allpairs = {}, []
    if workers > 1:
        from concurrent.futures import ProcessPoolExecutor
        with ProcessPoolExecutor(workers) as ex:
            res = list(ex.map(_family_of, range(len(exemplars)), chunksize=4))
    else:
        res = [_family_of(k) for k in range(len(exemplars))]
    for key, hits, pairs in res:
        fams[key] = hits
        allpairs.extend(pairs)
    return fams, allpairs


# ---------------------------------------------------------------------------------------------
# family transplant (round 76): a less-pinned family member is itself the exemplar

def transplant_exemplar(donor: Doc, sib: Doc):
    """(base Doc, out Doc) for replaying a DONOR member's current text on a sibling: base is the
    sibling itself, out is the donor's text with the donor's names, numbers and strings rewritten
    to the sibling's (read off their aligned code lines, as the clone map is).  A donor line that
    names an address the map does not know stays in the donor's spelling, so a hunk that needs it
    refuses at replay (the unmapped-address rule), never guesses."""
    didx, sidx = code_index(donor), code_index(sib)
    calign = code_alignment(donor, sib, didx, sidx)
    mapping, amb = identifier_map_v2(donor, sib, didx, sidx, calign)
    out = []
    for l in donor.lines:
        try:
            out.append(port_line(l, mapping, amb))
        except Refused:
            out.append(l)
    text = "\n".join(out) + ("\n" if donor.text.endswith("\n") else "")
    return Doc(sib.name, sib.text), Doc(sib.name, text)


# ---------------------------------------------------------------------------------------------
# judge

_MISSING = object()


class Judge:
    """screen.compile_s against the sibling's pinned listing, then the byte scorer."""

    def __init__(self, max_verify=4, do_verify=True):
        import screen
        from verify import verify
        self.screen = screen
        self.verify = verify
        self.max_verify = max_verify
        self.do_verify = do_verify
        self._pinned = {}
        self._lock = threading.Lock()

    def pinned_listing(self, row, text):
        with self._lock:
            hit = self._pinned.get(row["id"], _MISSING)
        if hit is _MISSING:          # None is a legitimate cached value (the pinned text failed)
            hit = self.screen.compile_s(row, text)
            with self._lock:
                self._pinned[row["id"]] = hit
        return hit

    def vf(self, row, text, sig):
        if unscored_text(text) != sig:
            return {"exact": False, "status": "unscored-text-changed"}
        with tempfile.TemporaryDirectory() as td:
            p = Path(td) / Path(row["c_path"]).name
            p.write_text(text)
            return self.verify(row, p, include_root=ROOT / "include")

    def run(self, row, sib_text, cands, budget=None):
        """(exact text|None, record dict).  `budget` is the scorer runs already spent on the row."""
        sig = unscored_text(sib_text)
        pins_in = len(sites_of(sib_text))
        base_listing = self.pinned_listing(row, sib_text)
        scored = []
        notes = collections.Counter()
        for text, applied, refusals in cands:
            if text is None:
                continue
            if unscored_text(text) != sig:
                notes["edits an unscored arm"] += 1
                continue
            pins_out = len(sites_of(text))
            if pins_out >= pins_in:
                notes["no pin removed"] += 1
                continue
            s = self.screen.compile_s(row, text)
            if s is None:
                notes["candidate does not compile"] += 1
                continue
            d = self.screen.sdiff(base_listing, s) if base_listing is not None else None
            if d is None:
                notes["pinned text does not compile"] += 1
                continue
            scored.append((d, -len(applied["hunks"]), text, applied, refusals, pins_out))
        if not scored:
            return None, {"outcome": "miss", "listing": None, "notes": dict(notes)}
        scored.sort(key=lambda t: (t[0], t[1]))
        best = scored[0][0]
        if not self.do_verify:
            return None, {"outcome": "screened", "listing": best, "notes": dict(notes),
                          "hunks": scored[0][3], "pins_out": scored[0][5]}
        spent = budget or 0
        for d, _, text, applied, refusals, pins_out in scored:
            if d > 0 and (d > 2 or spent):
                break                          # listing-exact first; one near miss if nothing else
            if spent >= self.max_verify:
                notes["verify budget"] += 1
                break
            spent += 1
            res = self.vf(row, text, sig)
            if res.get("exact"):
                return text, {"outcome": "exact", "listing": d, "hunks": applied,
                              "pins_out": pins_out, "verifies": spent, "notes": dict(notes)}
            notes[f"scorer {res.get('status')} total={res.get('total')}"] += 1
        return None, {"outcome": "miss", "listing": best, "hunks": scored[0][3],
                      "pins_out": scored[0][5], "verifies": spent, "notes": dict(notes)}


# ---------------------------------------------------------------------------------------------
# driver

def stage(lane, row, text, sib_text):
    """Stage an exact candidate exactly as gen_drive.py does (out/ + .base_sha); never landed."""
    d = ROOT / "work/native_lane" / lane / "out" / row["container"]
    d.mkdir(parents=True, exist_ok=True)
    n = Path(row["c_path"]).name
    (d / n).write_text(text)
    (d / (n + ".base_sha")).write_text(sha_text(sib_text) + "\n")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--lane", default="r65_clone_transfer")
    ap.add_argument("--threshold", type=float, default=0.85)
    ap.add_argument("--floor", type=float, default=0.5, help="record pairs this similar for the distribution")
    ap.add_argument("--jaccard", type=float, default=0.12, help="prefilter: token-shingle Jaccard")
    ap.add_argument("--span", type=float, default=0.6, help="prefilter: allowed line-count spread")
    ap.add_argument("--workers", type=int, default=4)
    ap.add_argument("--max-verify", type=int, default=4, help="scorer runs per sibling")
    ap.add_argument("--max-exemplars-per-sibling", type=int, default=3)
    ap.add_argument("--max-siblings", type=int, default=40, help="per exemplar, best first")
    ap.add_argument("--only", help="comma separated sibling row ids")
    ap.add_argument("--exemplar", help="comma separated exemplar row ids")
    ap.add_argument("--lanes", help="comma separated model lanes (default: the harvest list)")
    ap.add_argument("--lanes-glob", help="comma separated globs under work/native_lane (e.g. 'r6*,r7*'): "
                    "every matching lane with base/ and out/")
    ap.add_argument("--aligner", choices=("v1", "v2", "both"), default="both",
                    help="v1 = 3-line hunk context (rounds 65-75); v2 = code-line anchored windows (round 76)")
    ap.add_argument("--no-compose", action="store_true",
                    help="stop at a sibling's first exact (default: re-run the remaining exemplars on it)")
    ap.add_argument("--no-stage", action="store_true", help="journal only (an A/B control run)")
    ap.add_argument("--transplant", metavar="LEDGER",
                    help="also try each family member's current text on its siblings (families from "
                         "ledger/clone_families.jsonl, tools/lanes/clone_families.py)")
    ap.add_argument("--families", action="store_true", help="report the clone families and stop")
    ap.add_argument("--no-verify", action="store_true", help="listing screen only (no scorer runs)")
    ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args()

    t0 = time.time()
    lanes = a.lanes.split(",") if a.lanes else (lanes_matching(a.lanes_glob) if a.lanes_glob else LANES)
    exemplars = load_exemplars(lanes)
    if a.exemplar:
        want = set(a.exemplar.split(","))
        exemplars = [e for e in exemplars if e["id"] in want]
    index = pinned_index()
    print(f"{len(exemplars)} exemplars, {len(index)} pinned rows ({time.time() - t0:.0f}s)", flush=True)

    fams, allpairs = families(exemplars, index, a.threshold, a.floor, a.jaccard, a.span, a.workers)
    print(f"families built ({time.time() - t0:.0f}s)", flush=True)
    sizes = sorted(((len(v), k) for k, v in fams.items()), reverse=True)
    if a.families:
        for n, k in sizes[:30]:
            if n:
                print(f"{n:3d}  {k}  {[i for _, i in fams[k]][:6]}")
        hit = [p[0] for p in allpairs if p[3]]
        miss = [p[0] for p in allpairs if not p[3]]
        print(f"pairs >= {a.floor}: {len(allpairs)}  hits {len(hit)}  below threshold {len(miss)}")
        return

    OUT = ROOT / "work/native_lane" / a.lane
    (OUT / "out").mkdir(parents=True, exist_ok=True)
    (OUT / ".ignore").write_text("*\n")
    (OUT / "families.json").write_text(json.dumps(
        {"threshold": a.threshold, "pairs": allpairs,
         "families": {k: v for k, v in fams.items() if v}}, indent=1))

    by_row = {r["id"]: (r, d) for r, d in index}
    # one task per sibling: its exemplars best first, stopping at the first exact
    tasks = collections.defaultdict(list)
    for ex in exemplars:
        for s, rid in fams[ex["id"] + "@" + ex["lane"]][:a.max_siblings]:
            tasks[rid].append((s, ex))
    if a.transplant:
        # every family member with a different pin set donates its current text to its siblings
        nt = 0
        for fam in (json.loads(l)["members"] for l in Path(a.transplant).open()):
            ids = [m["id"] for m in fam if m["id"] in by_row]
            for sid in ids:
                for did in ids:
                    if did == sid:
                        continue
                    sd, dd = by_row[sid][1], by_row[did][1]
                    b, o = transplant_exemplar(dd, sd)
                    if len(sites_of(o.text)) >= len(sites_of(sd.text)) and \
                            sorted(x[1] for x in sites_of(o.text)) == sorted(x[1] for x in sites_of(sd.text)):
                        continue                                   # nothing to give
                    tasks[sid].append((1.0, {"lane": "transplant", "id": did, "base": b, "out": o,
                                             "pins_in": len(sites_of(b.text)),
                                             "pins_out": len(sites_of(o.text)), "proof": "landed"}))
                    nt += 1
        print(f"{nt} family transplant exemplars", flush=True)
    if a.only:
        want = set(a.only.split(","))
        tasks = {k: v for k, v in tasks.items() if k in want}
    todo = sorted(tasks.items(), key=lambda kv: -max(s for s, _ in kv[1]))
    if a.limit:
        todo = todo[:a.limit]
    print(f"{len(todo)} sibling rows to try", flush=True)

    judge = Judge(max_verify=a.max_verify, do_verify=not a.no_verify)
    J = OUT / "journal.jsonl"
    lock = threading.Lock()
    stats = collections.Counter()

    def one(item):
        rid, exs = item
        row, sib0 = by_row[rid]
        sib = sib0
        recs, done_ex = [], set()
        spent = composed = 0
        order = sorted(exs, key=lambda t: (PROOF_RANK[t[1]["proof"]], -t[0]))
        order = order[:a.max_exemplars_per_sibling]
        while True:
            progress = False
            for s_, ex in order:
                key = ex["id"] + "@" + ex["lane"]
                if key in done_ex:
                    continue
                cands, nh, nmap, namb = candidates_with(ex["base"], ex["out"], sib, a.aligner)
                rec = {"sibling": rid, "exemplar": ex["id"], "lane": ex["lane"], "proof": ex["proof"],
                       "similarity": round(s_, 4), "aligner": a.aligner, "step": composed,
                       "pins_in": len(sites_of(sib.text)), "hunks_total": nh,
                       "map": nmap, "ambiguous": namb,
                       "cands": len([c for c in cands if c[0] is not None])}
                live = [c for c in cands if c[0] is not None]
                if not live:
                    reasons = [r[1] for c in cands for r in c[2]] or ["no hunk applied"]
                    rec.update(outcome="refused", refusals=sorted(set(reasons))[:4])
                    recs.append(rec)
                    done_ex.add(key)
                    continue
                rec["refusals"] = sorted({r[1] for c in cands for r in c[2]})[:4]
                text, info = judge.run(row, sib.text, cands, budget=spent)
                spent = info.get("verifies", spent)
                rec.update(info)
                recs.append(rec)
                done_ex.add(key)
                if text is not None:
                    sib = Doc(rid, text)
                    composed += 1
                    progress = True
                    if a.no_compose or not sites_of(text):
                        break
                    spent = 0                   # a fresh verify budget for the composed text
                    break
                if spent >= a.max_verify:
                    break
            if not progress or a.no_compose or not sites_of(sib.text) or spent >= a.max_verify:
                break
        if composed:
            if not a.no_stage:
                stage(a.lane, row, sib.text, sib0.text)
            recs.append({"sibling": rid, "outcome": "staged" if not a.no_stage else "final",
                         "pins_from": len(sites_of(sib0.text)), "pins_to": len(sites_of(sib.text)),
                         "steps": composed, "aligner": a.aligner})
            return recs, True
        return recs, False

    n = hits = 0
    with ThreadPoolExecutor(a.workers) as ex:
        for recs, ok in ex.map(one, todo):
            with lock, J.open("a") as f:
                for r in recs:
                    f.write(json.dumps(r) + "\n")
            n += 1
            hits += ok
            for r in recs:
                stats[r["outcome"]] += 1
            if n % 25 == 0:
                print(f"{n}/{len(todo)} exact {hits} {time.time() - t0:.0f}s {dict(stats)}", flush=True)
    print(f"done {n} siblings, exact {hits}, {time.time() - t0:.0f}s, {dict(stats)}")


def candidates_with(base, out, sib, aligner):
    """(candidates, hunk count, map size, ambiguous count) from v1, v2 or both (v2 first,
    duplicates dropped)."""
    cands, nh, nmap, namb = [], 0, 0, 0
    seen = set()
    for which in (("v2", "v1") if aligner == "both" else (aligner,)):
        fn = candidates_v2 if which == "v2" else candidates_for
        cs, hunks, mapping, amb = fn(base, out, sib)
        nh, nmap, namb = max(nh, len(hunks)), max(nmap, len(mapping)), max(namb, len(amb))
        for text, info, refusals in cs:
            if text is not None:
                if text in seen:
                    continue
                seen.add(text)
            info = dict(info, aligner=which)
            cands.append((text, info, refusals))
    return cands, nh, nmap, namb


if __name__ == "__main__":
    main()
