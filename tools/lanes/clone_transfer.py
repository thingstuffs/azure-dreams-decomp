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

    python3 tools/lanes/clone_transfer.py --families                 # who is a clone of whom
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
# exemplars and siblings

def load_exemplars(lanes=LANES, verbose=False):
    """[(lane, row_id, base Doc, out Doc, pins_in, pins_out)] for every pair whose out text has
    fewer pin sites than its base."""
    out = []
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
            if pout >= pin:
                continue
            rid = str(rel)[:-2]                       # <container>/<name>
            out.append({"lane": lane, "id": rid, "base": Doc(rid, bt), "out": Doc(rid, ot),
                        "pins_in": pin, "pins_out": pout})
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


def families(exemplars, index, threshold=0.85, floor=0.5, jac_floor=0.12, span=0.6):
    """{exemplar id: [(similarity, row id)]} plus every pair above `floor` (for the distribution).
    Prefilter: line count within +-span, then the token-shingle Jaccard, then the difflib ratio."""
    fams, allpairs = {}, []
    for ex in exemplars:
        ed = ex["base"]
        hits = []
        for r, d in index:
            if r["id"] == ex["id"]:
                continue
            if not (1 - span) * ed.nlines <= d.nlines <= (1 + span) * ed.nlines:
                continue
            if jaccard(ed.shingles, d.shingles) < jac_floor:
                continue
            s = similarity(ed, d)
            if s >= floor:
                allpairs.append((round(s, 4), ex["id"], r["id"], s >= threshold))
            if s >= threshold:
                hits.append((round(s, 4), r["id"]))
        hits.sort(reverse=True)
        fams[ex["id"] + "@" + ex["lane"]] = hits
    return fams, allpairs


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
    ap.add_argument("--families", action="store_true", help="report the clone families and stop")
    ap.add_argument("--no-verify", action="store_true", help="listing screen only (no scorer runs)")
    ap.add_argument("--limit", type=int, default=0)
    a = ap.parse_args()

    t0 = time.time()
    lanes = a.lanes.split(",") if a.lanes else LANES
    exemplars = load_exemplars(lanes)
    if a.exemplar:
        want = set(a.exemplar.split(","))
        exemplars = [e for e in exemplars if e["id"] in want]
    index = pinned_index()
    print(f"{len(exemplars)} exemplars, {len(index)} pinned rows ({time.time() - t0:.0f}s)", flush=True)

    fams, allpairs = families(exemplars, index, a.threshold, a.floor, a.jaccard, a.span)
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
        row, sib = by_row[rid]
        recs = []
        spent = 0
        for s, ex in sorted(exs, key=lambda t: -t[0])[:a.max_exemplars_per_sibling]:
            cands, hunks, mapping, ambiguous = candidates_for(ex["base"], ex["out"], sib)
            rec = {"sibling": rid, "exemplar": ex["id"], "lane": ex["lane"], "similarity": round(s, 4),
                   "pins_in": len(sites_of(sib.text)), "hunks_total": len(hunks),
                   "map": len(mapping), "ambiguous": len(ambiguous),
                   "cands": len([c for c in cands if c[0] is not None])}
            if not [c for c in cands if c[0] is not None]:
                reasons = [r[1] for c in cands for r in c[2]] or ["no hunk applied"]
                rec.update(outcome="refused", refusals=sorted(set(reasons))[:4])
                recs.append(rec)
                continue
            rec["refusals"] = sorted({r[1] for c in cands for r in c[2]})[:4]
            text, info = judge.run(row, sib.text, cands, budget=spent)
            spent = info.get("verifies", spent)
            rec.update(info)
            recs.append(rec)
            if text is not None:
                stage(a.lane, row, text, sib.text)
                return recs, True
            if spent >= a.max_verify:
                break
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


if __name__ == "__main__":
    main()
