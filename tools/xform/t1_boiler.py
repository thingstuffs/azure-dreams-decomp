"""T1: hoist the m2c 'valid syntax' macro block into include/m2c_compat.h.

Subtracts the canonical block's lines one by one (exact text), so hand-added lines that sit
inside the block region survive.  Adds `#include "m2c_compat.h"` after `#include "common.h"`
when any of the hoisted names is still used.

Self-contained prelude (2026-09-22): some rows were split out of a larger m2c dump with NO
`#include "common.h"` at all -- the whole boilerplate (the u8/s8/../s32 primitive typedefs, the
f32/f64/s64/u64/M2C_UNK* compat block, the NULL guard) is spelled out inline instead, ahead of
whatever struct/extern/prototype declarations that split actually needs.  Recognised ONLY when the
file carries no `#include` of any kind (so a genuinely hand-written local header is never
touched): the same canonical lines (plus the primitive typedefs, common.h's own) are subtracted
and `#include "common.h"` (+ `m2c_compat.h` if a hoisted name is still used) is inserted at the
top.

A second, per-row-dead block of the SAME m2c dump also has to go before that include can land:
28 of these splits carry a byte-for-byte (mod whitespace) copy of the "global dispatch/callback
state" declarations `include/game.h` and `include/globals.h` reconstruct from evidence -- struct
`S_80083178[Vector|State]`, the `MonsterInitialStats`/`Trap`/`StatGrowth` record typedefs, and the
`D_800814C8`.. `D_80083CE8` externs (first measured on func_802F13A0: `#include "common.h"` then
errors `redefinition of struct S_80083178` / `conflicting types for MonsterInitialStats` against
`build_ovl/include/game.h`, which is the checked-in `include/game.h` -- an earlier grep for this
that came back empty had searched the wrong address, S_80083160 instead of S_80083178).  A handful
of splits instead carry a mismatching flat guess of the same `struct S_80083178` tag (fields
`f_A0`/`f_A4`/.. instead of game.h's nested `state_94`); either way the tag collides with game.h's
the moment `common.h` is included, so it has to go too.  Checked (`ledger/sweeps/t1_boiler.jsonl`
build errors, then a targeted scan of every row's post-prelude text): none of these 28 rows'
function bodies, or any other kept declaration, reference ANY of these names -- the whole block is
dead in every row it appears in, an artifact of splitting one large m2c dump into one file per
function without dropping the union of forward declarations the dump as a whole needed.  So it is
dropped like the compat block, but conservatively: `_strip_dead_game_globals` only removes a
struct/typedef/extern chunk naming one of these symbols when that symbol does not appear anywhere
outside the union of such chunks (computed once, so removing one candidate never "explains away" a
genuine reference sitting in another candidate that will also be removed) -- a row that DOES still
need one keeps it, and then either builds fine (game.h's declaration is compatible) or comes back
`build-failed`/`mismatch` exactly as an unrecognised row would, never a silent wrong landing.

Every OTHER declaration in a self-contained prelude -- structs, externs, prototypes not in that
fixed name set -- is left byte-for-byte untouched, whether or not this particular split's function
still uses it: pruning general "unused" declarations needs real liveness analysis this transform
does not attempt (checked against `include/game.h`/`globals.h`/`records/` too: none of those other
names are declared there, so keeping them verbatim never collides).

The M2C_UNK family is additionally recognised canonical under a signed/unsigned spelling swap at
the same width (`typedef u32 M2C_UNK;` next to the compat header's `typedef s32 M2C_UNK;`, seen on
func_8059E540): every landed use of these names is through a pointer (`M2C_UNK *`, `M2C_UNK **`),
never a loaded scalar, so sign never reaches codegen -- and this applies to both branches (a row
that already carries `#include "common.h"` can have the same mismatch, which is what broke
func_8059E540's build: the stray local typedef collided with m2c_compat.h's canonical one once
NAME_RE decided the file still needed it).  `verify()` still catches any row where that is not
true; a wrong guess just leaves the row as unapplied/refused, same as before this rule existed.
"""
import re
from pathlib import Path
COMPAT = Path(__file__).resolve().parents[2] / "include/m2c_compat.h"

def _canon_lines():
    t = COMPAT.read_text().split("#define M2C_COMPAT_H\n", 1)[1].rsplit("#endif", 1)[0]
    return [l for l in t.split("\n")]

# A bare comment-continuation line ("/*", "*", "*/", ...) sits inside m2c_compat.h's OWN copy of
# the MARK block (@73-79 below), so it is technically "in CANON" -- but it carries no distinguishing
# content, and the explicit MARK-block skip in `apply` already removes that whole block as a unit
# without ever consulting CANON_SET.  Matching such a fragment standalone, anywhere else a file
# happens to have one, is never correct: found on dungeon/func_80097AB8 (2026-09-22), whose own
# unrelated trailing `/* MECHANISM ... */` note ends in a lone " */" that is byte-identical (mod
# whitespace) to the MARK block's closing line -- the per-line loop silently ate that line, leaving
# an opened-but-never-closed comment and a gcc "unterminated comment" build failure (matches the
# historical journal entries for that row).  Excluded here so CANON_SET/CANON_NORM can never match
# one on their own; the MARK block itself is untouched (it never went through this path).
_COMMENT_FRAGMENT_RE = re.compile(r"^/?\*+/?$")
CANON = _canon_lines()
CANON_SET = {l for l in CANON if l.strip() and not _COMMENT_FRAGMENT_RE.match(l.strip())}
CANON_NORM = {re.sub(r"\s+", " ", l).strip() for l in CANON if l.strip() and not _COMMENT_FRAGMENT_RE.match(l.strip())}

# a same-width signed/unsigned swap on one of the M2C_UNK-family typedefs: still canon-equivalent
# for hoisting purposes (see module docstring).
_WIDTH_ALT = {"M2C_UNK": ("s32", "u32"), "M2C_UNK8": ("s8", "u8"), "M2C_UNK16": ("s16", "u16"),
              "M2C_UNK32": ("s32", "u32"), "M2C_UNK64": ("s64", "u64")}
_ALT_RE = re.compile(r"^typedef\s+(\w+)\s+(" + "|".join(sorted(_WIDTH_ALT, key=len, reverse=True)) + r")\s*;$")
def _is_alt_compat(l):
    m = _ALT_RE.match(re.sub(r"\s+", " ", l).strip())
    return bool(m and m.group(1) in _WIDTH_ALT[m.group(2)])

def _canon(l):
    return l in CANON_SET or re.sub(r"\s+", " ", l).strip() in CANON_NORM or _is_alt_compat(l)

# common.h's own primitive-width typedefs; a self-contained split spells these out too, ahead of
# (or interleaved with) the compat block -- never hoisted for a file that already has common.h
# (that file's own stray copy, if any, is left alone: out of scope for this rule).
PRIM_TYPEDEFS = ["typedef unsigned char u8;", "typedef signed char s8;", "typedef unsigned short u16;",
                 "typedef short s16;", "typedef unsigned int u32;", "typedef int s32;"]
PRIM_NORM = {re.sub(r"\s+", " ", l).strip() for l in PRIM_TYPEDEFS}
def _is_prim(l):
    return re.sub(r"\s+", " ", l).strip() in PRIM_NORM

NAMES = sorted({m for m in re.findall(r"^(?:#define|typedef .*?)\s+([A-Za-z_][A-Za-z0-9_]*)", "\n".join(CANON), re.M)} |
               {"f32", "f64", "s64", "u64", "NULL", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32", "M2C_UNK64"})
NAME_RE = re.compile(r"\b(" + "|".join(re.escape(n) for n in NAMES) + r")\b")
MARK = "This header contains macros emitted by m2c"

# names declared by include/game.h + include/globals.h (see module docstring): a self-contained
# split's own redeclaration of one of these -- exact copy or a mismatching flat guess of the same
# struct tag -- collides once `#include "common.h"` pulls the real one in, so `apply` drops it
# whenever nothing else in the row still needs it.
_GAME_STRUCT_TAGS = ("S_80083178Vector", "S_80083178State", "S_80083178")
_GAME_TYPEDEF_ALIASES = ("MonsterInitialStats", "Trap", "StatGrowth")
_GAME_EXTERN_NAMES = {"D_800814C8", "D_80081550", "D_80081558", "D_80081554", "D_80071298", "D_80071250",
                       "D_800712B4", "D_80084130", "D_80084808", "D_80083178", "D_80083CE8"}

def _brace_close(text, open_pos):
    """`open_pos` indexes a '{'; the index just past its matching '}', or None if unbalanced."""
    depth = 0
    for i in range(open_pos, len(text)):
        if text[i] == "{":
            depth += 1
        elif text[i] == "}":
            depth -= 1
            if depth == 0:
                return i + 1
    return None

def _game_global_chunks(text):
    """[(start, end, name)] for every struct/typedef/extern declaration of one of the fixed
    game.h/globals.h names, wherever it sits in `text` (spans include the trailing ';' and, for the
    struct/typedef forms, everything back to the 'struct'/'typedef' keyword)."""
    chunks = []
    for m in re.finditer(r"struct\s+(" + "|".join(_GAME_STRUCT_TAGS) + r")\b\s*\{", text):
        close = _brace_close(text, text.index("{", m.start()))
        if close is None:
            continue
        j = close
        while j < len(text) and text[j] in " \t":
            j += 1
        if j < len(text) and text[j] == ";":
            chunks.append((m.start(), j + 1, m.group(1)))
    for m in re.finditer(r"typedef\s+struct\s*\n?\s*\{", text):
        close = _brace_close(text, text.rindex("{", m.start(), m.end()))
        if close is None:
            continue
        mm = re.match(r"\s*(\w+)\s*;", text[close:])
        if mm and mm.group(1) in _GAME_TYPEDEF_ALIASES:
            chunks.append((m.start(), close + mm.end(), mm.group(1)))
    for m in re.finditer(r"^extern\b[^{}\n;]*;[ \t]*$", text, re.M):
        mm = re.search(r"([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*;\s*$", m.group(0))
        if mm and mm.group(1) in _GAME_EXTERN_NAMES:
            chunks.append((m.start(), m.end(), mm.group(1)))
    chunks.sort()
    return chunks

def _strip_dead_game_globals(text):
    """Drop each chunk from `_game_global_chunks` whose name is not referenced anywhere outside the
    union of ALL such chunks (so removing one candidate can never be excused by a reference that
    lives only inside another candidate that is also being removed).  A chunk whose name IS still
    referenced elsewhere is left in place -- `verify()` is the backstop if that reference and
    game.h's declaration turn out to be incompatible."""
    chunks = _game_global_chunks(text)
    if not chunks:
        return text
    core = text
    for s, e, _ in sorted(chunks, key=lambda c: -c[0]):
        core = core[:s] + core[e:]
    doomed = [(s, e) for s, e, name in chunks if not re.search(r"\b" + re.escape(name) + r"\b", core)]
    out = text
    for s, e in sorted(doomed, key=lambda c: -c[0]):
        if e < len(out) and out[e] == "\n":
            e += 1          # eat one trailing newline so no blank line is left behind
        out = out[:s] + out[e:]
    return out

class T:
    name = "t1_boiler"; level = 1
    @staticmethod
    def eligible(text, row, census):
        if '#include "common.h"' not in text:
            if '#include' in text:
                return "no common.h include (self-contained prelude)"
            # a self-contained m2c prelude: eligible only when there is something recognisable to hoist
            if MARK in text or any(_canon(l) or _is_prim(l) for l in text.split("\n")):
                return None
            return "no common.h include (self-contained prelude)"
        if MARK in text or "typedef float f32;" in text:
            return None
        # a file already carrying the compat header but with stray duplicates of its lines
        if '#include "m2c_compat.h"' in text and any(_canon(l) for l in text.split("\n")):
            return None
        return "no boilerplate"
    @staticmethod
    def apply(text, row, census):
        self_contained = '#include "common.h"' not in text
        if self_contained:
            text = _strip_dead_game_globals(text)
        lines = text.split("\n")
        out = []; removed = 0; in_comment = False
        i = 0
        while i < len(lines):
            l = lines[i]
            # the 7-line explanatory comment that starts with '/*' and contains MARK on the next line
            if l.strip() == "/*" and i + 1 < len(lines) and MARK in lines[i + 1]:
                j = i
                while j < len(lines) and not lines[j].rstrip().endswith("*/"): j += 1
                removed += j - i + 1; i = j + 1; continue
            if l.strip() == "#ifndef NULL" and i + 2 < len(lines) and lines[i + 1].strip() == "#define NULL 0" and lines[i + 2].strip() == "#endif":
                removed += 3; i += 3; continue
            if _canon(l) and not l.startswith("#endif"):
                removed += 1; i += 1; continue
            if l.startswith("/* ") and l.rstrip().endswith("*/") and any(l == c for c in CANON):
                removed += 1; i += 1; continue
            if self_contained and _is_prim(l):
                removed += 1; i += 1; continue
            out.append(l); i += 1
        body = "\n".join(out)
        # collapse runs of blank lines left behind
        body = re.sub(r"\n{3,}", "\n\n", body)
        if self_contained:
            if not removed:
                return None
            body = body.lstrip("\n")
            needs_compat = bool(NAME_RE.search(body))
            prefix = '#include "common.h"\n' + ('#include "m2c_compat.h"\n' if needs_compat else '')
            return prefix + body
        if NAME_RE.search(body.split("\n", 1)[1] if "\n" in body else body) and '#include "m2c_compat.h"' not in body:
            body = body.replace('#include "common.h"\n', '#include "common.h"\n#include "m2c_compat.h"\n', 1)
        return body if removed else None
