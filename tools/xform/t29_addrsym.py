"""T29: a pinned local holding an address literal, where retail references a SYMBOL.

APPEARS     `V = 0x800E0000;` (any cast, U suffix, do{}while(0) wrapper, the one-line split idiom
            `(V) = PAGE; ASM_KEEP(V); (V) -= OFF;`, or PAGE / keeps / `V += OFF;` across lines, or a
            symbol-spelled page `V = (u8 *)&D_X + K;`), pins on V, and uses `V +/- K`,
            `(T *)(V +/- K)`, `(u8 *)V + K`, `(T *)V` or a bare `V` in operand position.
RESOLVES    retail's `lui` into a scratch register then `addiu` into the destination (or a lone `lui`
            in a delay slot) is gcc splitting a SYMBOL address into HIGH/LO_SUM. The CDK build
            (2.7.2-cdk) splits; FSF 2.7.2 and 2.6.3 emit the one-insn `la` macro. Upstream matched these
            rows at a non-splitting cell and emulated the split with an integer page plus pins.
            Written as the symbol, the row is exact at the recorded cell or at a CDK cell where its
            pinned text is exact too (tools/pin_cells_land.py rules 1-2: the shipped bytes never
            depend on the switch).
POPULATION  2026-09-12 atlas: 975 pins / 336 functions on address-literal variables; this generator
            reaches 431 of them in 199 rows. First harvest: 52 rows / 113 pins, 32 of them via a CDK
            cell. An attribution control put 27 of those 32 on the pair (symbol AND cell): erasing
            the pins at the CDK cell without the rewrite was exact for only two.

Each use becomes the symbol at its effective address, spelled from the file's own declaration
(an array decays, a scalar takes `&`, a missing symbol gets `extern u8 D_X[];`); V's definitions,
its pins and every declaration of V go. Candidates: every variable alone, then all together.
Where the only use is a macro base or a struct view, the symbol named is the page itself
(`S32(D_80080000, 0x346C)`), the spelling the earlier litsym landings used.

ROUND-34 OPENINGS (each an env switch; T29_SYMDEF and T29_NONRAM default OFF as measured negatives,
T29_DEREF_USE defaults ON because it paid - `DEFAULTS` below is the authority; the refusal table with the pins behind each
refusal is `work/native_lane/r34_wave/rows/t29_refusals.txt`, built by `scratch/t29_refusals.py`
over the whole pinned tree from the `Detail` counter below).  The table's largest honest classes:

  T29_SYMDEF   `symbol-page-def-only` 237 records / 208 rows / 297 pins, plus
               `symbol-decl-init-only` 21 / 20 / 23 - the LARGEST class in the table by a factor of
               five, and a SCAN STOPPER, not a parser gap: `rewrite_var` has carried a `symdef`
               branch (`v = (T *)&D_X + K;`, read by `sym_value`) since the atlas round, but
               `addrvars` admits a variable only when some definition matches `LIT` (an integer
               page), so a variable whose ONLY definition already names the symbol is never offered
               and the branch is unreachable on its own.  The switch admits those variables
               (`symbol_defined`), and accepts the same value in a declaration initialiser, which
               `rewrite_var` otherwise refuses `decl-init`.  The move is unchanged - every use
               becomes the symbol at its effective address and the local, its definitions and its
               pins go - only the variable's DEFINITION is spelled differently on the way in.
  T29_NONRAM   `non-ram-page-literal` 43 / 37 / 58: `LIT` hard-codes `0x8XXXXXXX`, so a scratchpad
               or uncached page (`(u8 *)0x1F800000`, `0xA0700000`) is not an address literal to
               this generator.  The tree does name symbols there (`extern u8 D_1F800000[];` in two
               landed rows), so the refusal is a regex bound, not a link-convention wall.
  T29_DEREF_USE `operand-context` 25 / 19 / 45 and `not-operand` 9 / 9 / 15, one shape between them:
               a use under a `*`.  `*(s32 *)(page + 0xAFC) = x;` fails the `tail` test (the text
               after the use is `=`, not one of `) ; , ]`) and `if (x == *page)` fails
               `operand_lead` (the character before the use is `*`, which is not in its list).
               Both are addresses in operand position; the switch adds `*` to the lead characters
               and lets an assignment follow a use that is itself under a `*`.

ROUND-34 REVIEW (the adversarial pass on the openings above; every fix is measured in
`work/native_lane/r34_wave/report_B.txt`, section "Review fixes"):
  D1  the "a candidate that removes no pin is not a result" filter in `apply_verified` changed the
      sequence put to vf on rows no opening applies to.  It now exempts every candidate of
      `_baseline_candidates`, so those rows behave byte-identically to HEAD.
  D2  `sym_value` read a bare `D_X` as an address without asking whether D_X is an ARRAY, so a LOAD
      of a scalar or pointer global counted as a symbol-address definition (and T29_SYMDEF offered a
      rewrite built on it).  It now requires the array declaration, or a `&`.
  D3  admitting one more variable rewrote the joint `addrsym:*a+b` candidate, taking HEAD's joint
      TEXT off the menu.  `candidates` now appends every pre-round-34 candidate it lacks: an opening
      only ever adds.
  D4  `star_lead` read a multiplication (`n * page`) as a dereference and emitted `n * D_80110000`,
      an int times an array, which cannot build.  A factor before the star now refuses.
"""
import contextlib, os, re, sys, threading, collections
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from pin_census import sites_of
from pin_sites import erase_many

CDK = ("2.7.2-cdk", "2.7.2-cdk-G0")
CAST = r"(?:\(\s*(?:const\s+|volatile\s+|unsigned\s+|signed\s+)*[A-Za-z_]\w*(?:\s+long)?\s*\**\s*\)\s*)"
LIT = r"\(?\s*" + CAST + r"*0x(?P<a>8[0-9A-Fa-f]{7})[Uu]?[Ll]?\s*\)?"
# T29_NONRAM widens the page range INSIDE t29 only (`_lit()`); the module constant `LIT` never moves,
# because tools/xform/t54_pagebase.py reads `A.LIT` by name and its menu must not change.
LIT_NONRAM = (r"\(?\s*" + CAST +
              r"*0x(?P<a>8[0-9A-Fa-f]{7}|1F8[0-9A-Fa-f]{5}|[9ABab][0-9A-Fa-f]{7})[Uu]?[Ll]?\s*\)?")
NUM = r"(?:0x[0-9A-Fa-f]+|\d+)"
BYTEPTR = {"u8", "s8", "char", "void", "unsigned char", "signed char"}
INTTY = {"u32", "s32", "int", "unsigned int", "unsigned long", "long", "unsigned", "signed"}
ELEMSIZE = dict({t: 1 for t in BYTEPTR}, u16=2, s16=2, u32=4, s32=4, int=4, **{"unsigned int": 4})
NOTE_RE = re.compile(r"^[ \t]*/\*[^\n]*(?:\(pin\)|\bPin:|Byte-exact pin|MATCH:)[^\n]*\*/[ \t]*\n", re.M)
LOCAL_SYM_RE = re.compile(r"^[ \t]+(?:register[ \t]+)?(?!(?:return|else|case|goto|do|sizeof)\b)"
                          r"[A-Za-z_][\w \t]*[\s*]\**\s*D_[0-9A-F]{8}\s*[;=,\[]", re.M)
NOT_TYPES = {"return", "else", "goto", "case", "do", "if", "while", "for", "switch", "sizeof"}
# The eligibility scan's own refusals (round 34).  `addrvars` admits a name only when it is PINNED and
# carries a definition `V = <cast>* 0x8XXXXXXX;`; every other pinned assigned name leaves the scan with
# no record at all, and the sweep journals the whole row as `no pinned address-literal variable`.  These
# two regexes name the two shapes that scan drops on purpose, so the refusal table can count them.
# A definition whose RHS NAMES a symbol.  Only the ones `sym_value` can read are addresses: the same
# regex also matches `result = D_80083160.angle;` and `id = D_80010000[0x33E7];`, which LOAD from a
# symbol and are not address definitions at all (153 of the class's first 412 records) - every caller
# filters the match through `sym_value` before counting it.
SYMDEF_ANY_RE = r"^[ \t]*\(?([A-Za-z_]\w*)\)?[ \t]*=[ \t]*([^;=\n]*\bD_[0-9A-Fa-f]{8}\b[^;=\n]*);"
# An address literal outside RAM: the scratchpad (0x1F80xxxx) and the uncached/IO segments
# (0x9XXXXXXX / 0xAXXXXXXX / 0xBXXXXXXX).  NOT every 8-digit constant: `mask = 0xFFFC0000;` is a
# number, not a page, and counting it would inflate the refusal class it lands in.
NONRAM_RE = r"\(?\b([A-Za-z_]\w*)\)?\s*=\s*" + CAST + r"*0x(1F8[0-9A-Fa-f]{5}|[9ABab][0-9A-Fa-f]{7})[Uu]?[Ll]?\s*;"


# An opening's default.  T29_DEREF_USE is the one that paid (round 34: 20 candidate rows, 2 hits,
# 17 pins - `town/func_800BA42C` 14 -> 0 and `town/func_800BA82C` 8 -> 5, both diffs read); the other
# two are measured negatives and stay off.  Identity, exactly as it holds after the review
# (`work/native_lane/r34_wave/scratch/menu_identity2.py`, all 1,299 pinned rows, `candidates` AND
# `apply_verified`'s sequence under a stub vf):
#   * every switch off - the module offers what it offered before round 34 EXCEPT on the rows the
#     D2 bug fix moves (a bare `D_X` that LOADS a scalar is no longer an address definition); that
#     class is counted separately in the report, and it is a bug fix, not an opening;
#   * at the shipped default - a row no opening applies to is byte-identical to HEAD, and on a row
#     one does apply to the HEAD sequence is a SUBSET of the new one (nothing is taken away).
DEFAULTS = {"T29_SYMDEF": "0", "T29_NONRAM": "0", "T29_DEREF_USE": "1"}


_TL = threading.local()


def _on(name):
    """An opening's env switch, read at call time (`DEFAULTS` above gives its default).

    `_openings_off` forces every opening off for ONE THREAD by setting `_TL.off`, never by writing
    `os.environ`: `tools/lane_eval.py`, `tools/sweep.py` and the lane's screens all run this module
    on a ThreadPoolExecutor, and an environment flipped for the duration of one row's baseline menu
    would silently switch the openings off under every other row in flight.  (Measured while this
    was still env-based: one screen run reported 1 candidate on `town/func_800BA82C` where the same
    row screened alone gives 3.)
    """
    if name in OPENINGS and getattr(_TL, "off", False):
        return False
    return os.environ.get(name, DEFAULTS.get(name, "0")) not in ("", "0")


def _lit():
    """The address-literal pattern this run reads (see T29_NONRAM)."""
    return LIT_NONRAM if _on("T29_NONRAM") else LIT


OPENINGS = ("T29_SYMDEF", "T29_NONRAM", "T29_DEREF_USE")


def _any_opening():
    return any(_on(k) for k in OPENINGS)


@contextlib.contextmanager
def _openings_off():
    """Every round-34 switch off inside the block, for THIS THREAD only (see `_on`)."""
    prev = getattr(_TL, "off", False)
    _TL.off = True
    try:
        yield
    finally:
        _TL.off = prev


def _baseline_candidates(text):
    """The menu with every opening OFF - exactly what the module offered before round 34.

    An opening may only ADD.  Two things follow, and both were round-34 review defects:
      D3  admitting one more variable rewrites the joint `addrsym:*a+b` candidate - the one tried
          first, because it removes the most pins - so HEAD's joint TEXT vanished from the menu on
          10 rows.  `candidates` appends every pre-round-34 candidate the opening's menu does not
          already carry.
      D1  the pin-count filter in `apply_verified` dropped candidates HEAD would have put to vf on
          rows the opening does not apply to at all.  It now exempts every candidate of this menu.
    Recursion is impossible: inside the block no opening is on, so `candidates` does not come back.
    """
    with _openings_off():
        return candidates(text)[0]


def symbol_defined(text, masked, pinned, names):
    """Pinned variables whose ADDRESS definition already names a symbol, by spelling.

    Returns (statement-form, declaration-initialiser-form); both exclude `names` (the variables
    `addrvars` already admits) and both read every candidate RHS through `sym_value`, so a LOAD from
    a symbol (`v = D_X[3];`, `v = D_X.f;`) is in neither set.  T29_SYMDEF's opening is exactly these
    two sets - see the module docstring's round-34 note.
    """
    stmt = {m.group(1) for m in re.finditer(SYMDEF_ANY_RE, masked, re.M)
            if sym_value(text, m.group(2)) is not None} & pinned
    stmt -= names
    di = set()
    for n in sorted(pinned - names - stmt):
        for ty, ptr, sp in decls_of(text, n):
            m = re.search(r"=\s*([^;=\n]*\bD_[0-9A-Fa-f]{8}\b[^;=\n]*);", masked[sp[0]:sp[1]])
            if m and sym_value(text, m.group(1)) is not None:
                di.add(n)
                break
    return stmt, di


class Detail(collections.Counter):
    """A refusal counter that also records (refusal, variable), for a refusal table with the pins
    behind each refusal (the pins behind a record are the sites naming that variable).

    Passing one changes nothing a caller sees: `addrvars` and `candidates` return exactly what they
    return without it (proved by tools/tests/test_t29_addrsym.py's menu-identity tests).
    """

    def __init__(self, *a, **k):
        super().__init__(*a, **k)
        self.detail = []

    def note(self, key, var=None):
        self[key] += 1
        self.detail.append((key, var))


def mask_comments(t):
    return re.sub(r"/\*.*?\*/", lambda m: re.sub(r"[^\n]", " ", m.group(0)), t, flags=re.S)


def decls_of(t, v):
    """Every local declaration of V: [(type, pointer depth, span)]; block-scoped redeclarations too."""
    rx = re.compile(r"^[ \t]*(?:register[ \t]+)?(?P<ty>(?:unsigned[ \t]+|signed[ \t]+|const[ \t]+)*[A-Za-z_]\w*(?:[ \t]+long)?)"
                    r"[ \t]*(?P<p>\**)[ \t]*\b%s\b[ \t]*(?:ASM_REG\([^)]*\))?[ \t]*(?:=[^;]*)?;[^\n]*\n" % re.escape(v), re.M)
    return [(m.group("ty").strip(), len(m.group("p")), (m.start(), m.end()))
            for m in rx.finditer(t) if m.group("ty").strip() not in NOT_TYPES]


def sym_decl(t, s):
    m = re.search(r"^extern\s+(?P<ty>[\w ]+?)\s*(?P<p>\**)\s*\b%s\b\s*(?P<arr>\[[^\]]*\])?\s*;" % s, t, re.M)
    if not m:
        return None
    return m.group("ty").strip() + "*" * len(m.group("p")), bool(m.group("arr"))


def sym_expr(t, addr, want, externs):
    """The symbol at `addr` as an expression of pointer type `want` ('u16 *' / None = natural)."""
    s = "D_%08X" % addr
    d = sym_decl(t, s)
    if d is None:
        externs.add("extern u8 %s[];\n" % s)
        elem, arr = "u8", True
    else:
        elem, arr = d
    base = s if arr else "&" + s
    if want is None:
        return base
    w = re.sub(r"\s+", " ", want.replace("*", "").strip())
    if w == elem and want.count("*") == 1:
        return base
    return "(%s)%s" % (want.strip(), base)


def sym_value(t, e):
    """Address of a symbol-spelled page: `(u8 *)&D_X + K`, `(u8 *)D_X - K`, `&D_X`, `D_X` (byte offsets only).

    A BARE `D_X` (no `&`) is the symbol's ADDRESS only where the file declares D_X an ARRAY, which
    decays.  `extern s32 D_X;` or `extern void *D_X;` make the same text a LOAD of the global's
    value, and a cast in front of it (`(void *)D_X`) casts that VALUE - it does not take an address.
    Round-34 review D2: without this test 30 definitions in 29 rows (35 pins) were counted as
    address definitions and T29_SYMDEF offered a rewrite built on the misreading
    (`ot_addr = D_80083160;` + `ot_addr += 0xB0;` -> `D_80083210`, a symbol invented at an address
    derived from another symbol's value).  Where the file declares D_X nowhere the shape is
    undecidable, and undecidable is refused: measured at 4 records in 2 rows over the whole pinned
    tree (`work/native_lane/r34_wave/rows/rev_d2_census.txt`).
    """
    m = re.fullmatch(r"\s*(?:\(\s*(?P<c>[A-Za-z_][\w ]*)\s*\*\s*\)\s*)?(?P<amp>&)?\s*D_(?P<x>[0-9A-Fa-f]{8})\s*"
                     r"(?:(?P<op>[-+])\s*(?P<k>%s))?\s*" % NUM, e)
    if not m:
        return None
    x = int(m.group("x"), 16)
    d = sym_decl(t, "D_" + m.group("x").upper())
    if not m.group("amp") and not (d and d[1]):
        return None                              # a LOAD of a scalar or a pointer, or undecidable
    if not m.group("k"):
        return x
    if not m.group("c") or re.sub(r"\s+", " ", m.group("c").strip()) not in BYTEPTR:
        if not d or d[0] not in BYTEPTR:
            return None                          # a scaled offset: leave it alone
    k = int(m.group("k"), 0)
    return x + k if m.group("op") == "+" else x - k


def operand_lead(masked, pos):
    """True when the token before `pos` puts it in operand position (not a declarator)."""
    before = masked[:pos].rstrip()
    if before.endswith("return"):
        return True
    ch = before[-1:]
    if ch in ("(", "=", "+", "-", "?", ":", "[", "|", "&", "^", "<", ">", "!", "~"):
        return not before.endswith(("++", "--"))
    if ch == ",":
        stmt = re.split(r"[;{}]", before)[-1]
        return stmt.count("(") > stmt.count(")")         # inside an argument list
    return False


def star_lead(masked, pos):
    """True when the `*` before `pos` DEREFERENCES it - never a declarator, never a multiplication.

    `operand_lead` leaves `*` out of its list because `T *v` puts the name in a declarator, where a
    rewrite would be nonsense.  What stands before the star run decides: a type name is a
    declaration (`u8 *page`), and an identifier, a `)`, a `]` or a digit is a MULTIPLICATION
    (`n * page`, `f(a) * page`).  A multiplication must refuse as firmly as a declarator, because
    the local is an integer page and the symbol is an ARRAY: round-34 review D4 had
    `x = n * page;` rewritten to `x = n * D_80110000;`, an int times a pointer, which cannot build.
    Only `return` / `case` / `else` / `sizeof` may stand there and still leave a dereference.
    Conservative by design - `if (c) *p = 1;` written on one line and `(s32)*p` end in `)` and are
    refused too; a refusal is never wrong C.  T29_DEREF_USE is the only caller.
    """
    before = masked[:pos].rstrip()
    if not before.endswith("*"):
        return False
    head = re.split(r"[;{}]", before.rstrip("* \t"))[-1]
    if re.search(r"\b(?:if|while|for|switch)\s*\([^()]*\)\s*$", head):
        return True                                    # a control head, then the statement
    if re.search(r"[)\]\d]$", head):
        return False                                   # `f(a) * v`, `t[i] * v`, `4 * v`
    w = re.search(r"[A-Za-z_]\w*$", head)
    return not w or w.group(0) in ("return", "case", "else", "sizeof")


def rewrite_var(text, v):
    """Return (new_text, info) with every use of V turned into symbols, or (None, reason)."""
    V = re.escape(v)
    decs = decls_of(text, v)
    if not decs:
        return None, "no-decl"
    if len({(ty, p) for ty, p, _ in decs}) != 1:
        return None, "mixed-decl"
    ty, ptr, _ = decs[0]
    # `V + K` on a pointer steps K elements: scale to bytes (void * steps bytes, a GNU extension)
    if ptr == 0 and ty in INTTY:
        scale = 1
    elif ptr == 1 and ty in ELEMSIZE:
        scale = ELEMSIZE[ty]
    elif ptr == 2:
        scale = 4
    else:
        return None, "type:%s%s" % (ty, "*" * ptr)
    t = text
    split = re.compile(r"^[ \t]*\(?%s\)?\s*=\s*%s\s*;\s*ASM_\w+\(\s*%s\s*\)\s*;\s*\(?%s\)?\s*(?P<op>[-+])=\s*(?P<k>%s)\s*;[^\n]*\n"
                       r"(?:[ \t]*/\*[^\n]*\*/[ \t]*\n)?" % (V, _lit(), V, V, NUM), re.M)
    dow = re.compile(r"^[ \t]*do\s*\{\s*%s\s*=\s*%s\s*;\s*\}\s*while\s*\(\s*0\s*\)\s*;[^\n]*\n" % (V, _lit()), re.M)
    plain = re.compile(r"^[ \t]*\(?%s\)?\s*=\s*%s\s*;[^\n]*\n" % (V, _lit()), re.M)
    symdef = re.compile(r"^[ \t]*\(?%s\)?\s*=\s*(?P<e>[^;=\n]*\bD_[0-9A-Fa-f]{8}\b[^;=\n]*)\s*;[^\n]*\n" % V, re.M)
    rawkeep = re.compile(r"^[ \t]*__asm__\s+__volatile__\s*\(\s*\"\"\s*:\s*\"=r\"\s*\(\s*%s\s*\)\s*:\s*\"0\"\s*\(\s*%s\s*\)\s*\)\s*;[^\n]*\n"
                         % (V, V), re.M)
    keepline = re.compile(r"^[ \t]*(?:ASM_\w+\([^;\n]*\b%s\b[^;\n]*\)\s*;|__asm__\s+__volatile__\s*\([^;\n]*\b%s\b[^;\n]*\)\s*;)[^\n]*\n"
                          r"|^[ \t]*/\*[^\n]*\*/[ \t]*\n" % (V, V), re.M)
    bump = re.compile(r"[ \t]*\(?%s\)?\s*(?P<op>[-+])=\s*(?P<k>-?\s*%s)\s*;[^\n]*\n" % (V, NUM))
    marks = []
    for rx, kind in ((split, "split"), (dow, "dowhile"), (plain, "plain"), (symdef, "symdef")):
        for m in rx.finditer(t):
            if any(a < m.end() and m.start() < b for a, b, _ in marks):
                continue
            end = m.end()
            if kind == "symdef":
                val = sym_value(t, m.group("e"))
                if val is None:
                    continue
            else:
                val = int(m.group("a"), 16)
            if kind == "split":
                k = int(m.group("k"), 0)
                val = val - k if m.group("op") == "-" else val + k
            elif kind in ("plain", "symdef"):
                # PAGE; keeps of V (pins or raw empty asm); `V +/-= OFF;` - one definition across lines
                p = end
                while True:
                    k2 = keepline.match(t, p)
                    if not k2:
                        break
                    p = k2.end()
                b2 = bump.match(t, p)
                if b2:
                    k = int(b2.group("k").replace(" ", ""), 0)
                    val = val - k if b2.group("op") == "-" else val + k
                    end = b2.end()
            marks.append((m.start(), end, val))
    for m in rawkeep.finditer(t):                 # stray empty-asm keeps of V: scaffolding like the pins
        if not any(a <= m.start() < b for a, b, _ in marks):
            marks.append((m.start(), m.end(), None))
    dspans = [sp for _, _, sp in decs]
    for a, b in dspans:
        dm = re.search(r"=\s*%s\s*;" % _lit(), text[a:b])
        if dm:
            marks.append((a, b, int(dm.group("a"), 16)))
            continue
        # T29_SYMDEF: the same definition spelled as the symbol (`T *v = (T *)&D_X;`).  `sym_value`
        # reads only an address expression, so a declaration that LOADS from a symbol still refuses.
        sm = (re.search(r"=\s*([^;=\n]*\bD_[0-9A-Fa-f]{8}\b[^;=\n]*);", mask_comments(text[a:b]))
              if _on("T29_SYMDEF") else None)
        sv = sym_value(text, sm.group(1)) if sm else None
        if sv is not None:
            marks.append((a, b, sv))
        elif "=" in mask_comments(text[a:b]):
            return None, "decl-init"
    if not marks:
        return None, "no-literal-def"
    marks.sort()
    masked = mask_comments(t)
    pins = [s for s in sites_of(t) if re.search(r"\b%s\b" % V, t[s[3]:s[4]])]
    pin_spans = [(s[3], s[4]) for s in pins]
    def inside(pos, spans):
        return any(a <= pos < b for a, b in spans)
    fixed = [(a, b) for a, b, _ in marks] + pin_spans + dspans
    # statements that change V: `V +/-= K` and `V++` fold while the literal is known; anything else
    # (`V = load`, `V += x`) ends the literal's range and stays - V keeps its other role (CONFINED)
    chg_rx = re.compile(r"^[ \t]*\(?%s\)?\s*(?P<op>[-+*/|&^]?=(?!=)|\+\+|--)\s*(?P<rhs>[^;]*);[^\n]*\n" % V, re.M)
    changes = [m for m in chg_rx.finditer(masked) if not inside(m.start(), fixed)]
    lhs = [(m.start(), m.start("op")) for m in changes]
    use_rx = re.compile(
        r"(?P<c1>\(\s*(?P<t1>[A-Za-z_][\w ]*\*)\s*\)\s*\(\s*%s\s*(?P<o1>[-+])\s*(?P<k1>%s)\s*\))"   # (T *)(V + K)
        r"|(?P<c2>\(\s*(?P<t2>[A-Za-z_][\w ]*\*)\s*\)\s*%s\s*(?P<o2>[-+])\s*(?P<k2>%s))"            # (T *)V + K
        r"|(?P<c3>\b%s\s*(?P<o3>[-+])\s*(?P<k3>%s))"                                               # V + K
        r"|(?P<c4>\(\s*(?P<t4>[A-Za-z_][\w ]*\*)\s*\)\s*%s\b)"                                     # (T *)V
        r"|(?P<c6>\(\s*(?P<t6>(?:unsigned\s+|signed\s+)?(?:u32|s32|int|long))\s*\)\s*%s\b)"          # (u32)V
        r"|(?P<c5>\b%s\b)" % (V, NUM, V, NUM, V, NUM, V, V, V))
    uses = [m for m in use_rx.finditer(masked) if not inside(m.start(), fixed + lhs)]
    events = sorted([(a, 0, "def", val) for a, b, val in marks if val is not None]
                    + [(m.end(), 1, "chg", m) for m in changes]      # a change takes effect after its RHS
                    + [(m.start(), 2, "use", m) for m in uses], key=lambda e: (e[0], e[1]))
    externs, edits, drops, known = set(), [], [], []
    cur = start = None; confined = False
    for pos, _, kind, x in events:
        if kind == "def":
            if cur is not None:
                known.append((start, pos))
            cur, start = x, pos
            continue
        if kind == "chg":
            op, rhs = x.group("op"), x.group("rhs").strip()
            step = scale if op in ("++", "--") and not rhs else \
                int(rhs.replace(" ", ""), 0) * scale if op in ("+=", "-=") and re.fullmatch(r"-?\s*%s" % NUM, rhs) else None
            if cur is not None and step is not None:
                cur = cur + step if op in ("+=", "++") else cur - step
                drops.append((x.start(), x.end()))
                continue
            if cur is not None and op != "=":
                return None, "modified"                 # reads the literal in a way that does not fold
            if cur is not None:
                known.append((start, x.end()))
            cur = start = None; confined = True
            continue
        m = x
        if cur is None:
            confined = True                             # V's other role (or a read before any literal): left alone
            continue
        val = cur
        after = masked[m.end():].lstrip()
        tail = after[:1]
        deref = after.startswith(("->", "["))
        # T29_DEREF_USE: a use UNDER a `*` is in operand position, and the assignment that may follow
        # it (`*(s32 *)(page + 0xAFC) = x;`) is a store through that address, not a declarator.
        star = _on("T29_DEREF_USE") and star_lead(masked, m.start())
        store = star and tail == "=" and not after.startswith("==")
        if m.group("c1"):
            k = int(m.group("k1"), 0) * scale; a = val + k if m.group("o1") == "+" else val - k
            # `(T *)(V op K)` is a complete, self-delimiting cast expression: under a `*` it drops
            # in wherever it stands, an `=` store and an `==` comparison alike.  `(T *)V + K` and the
            # bare `V + K` below are NOT self-delimiting (`V + K * 2` would rebind), so those two keep
            # the tail test and gain only the store.
            if tail not in (")", ";", ",", "]") and not deref and not star:
                return None, "operand-context"
            rep = sym_expr(t, a, m.group("t1"), externs)
            if deref:
                rep = "(" + rep + ")"
        elif m.group("c2"):
            if re.sub(r"\s+", " ", m.group("t2").replace("*", "").strip()) not in BYTEPTR:
                return None, "scaled-cast"
            k = int(m.group("k2"), 0); a = val + k if m.group("o2") == "+" else val - k
            if tail not in (")", ";", ",") and not store:
                return None, "operand-context"
            rep = sym_expr(t, a, m.group("t2"), externs)
        elif m.group("c3"):
            k = int(m.group("k3"), 0) * scale; a = val + k if m.group("o3") == "+" else val - k
            if (tail not in (")", ";", ",") and not store) or not (operand_lead(masked, m.start()) or star):
                return None, "operand-context"
            rep = sym_expr(t, a, (ty + " *") if ptr else None, externs)
        elif m.group("c4"):
            rep = sym_expr(t, val, m.group("t4"), externs)
            if deref and not re.fullmatch(r"D_[0-9A-F]{8}", rep):
                rep = "(" + rep + ")"                  # a bare array symbol indexes as it stands
        elif m.group("c6"):
            rep = "(%s)%s" % (m.group("t6"), sym_expr(t, val, None, externs))
        else:
            if re.match(r"(\+\+|--|[-+*/|&^]?=(?!=))", after) or masked[:m.start()].rstrip().endswith(("++", "--")):
                return None, "modified"
            if after.startswith("."):
                return None, "deref"
            if after.startswith(("->", "[")):
                if not ptr:
                    return None, "deref"
                # a view of the symbol with V's own pointer type: `((T *)D_X)->f`, `D_X[i]`
                rep = sym_expr(t, val, ty + " " + "*" * ptr, externs)
                if not re.fullmatch(r"D_[0-9A-F]{8}", rep):
                    rep = "(" + rep + ")"
                edits.append((m.start(), m.end(), rep))
                continue
            if not operand_lead(masked, m.start()) and not star:
                return None, "not-operand"
            rep = sym_expr(t, val, (ty + " *") if ptr else None, externs)
        edits.append((m.start(), m.end(), rep))
    if cur is not None:
        known.append((start, len(t)))
    if not edits:
        return None, "no-uses"
    if confined and any("=" in mask_comments(text[a:b]) for a, b in dspans):
        return None, "decl-init-confined"
    # one pass, last first: use edits; definitions and folded steps cut; the declarations too
    # unless V keeps another role
    cuts = set(edits) | {(a, b, "") for a, b, _ in marks} | {(a, b, "") for a, b in drops}
    if not confined:
        cuts |= {(a, b, "") for a, b in dspans}
    gone = [(a, b) for a, b, _ in marks] + drops + ([] if confined else dspans)
    kept_pins = [s for s in pins if not inside(s[3], gone)]
    # full elimination: every pin of V goes; confined: statement pins inside a literal's range go,
    # the declaration's register pin and pins on V's other role stay
    kill_pin = [not confined or (s[0] == "stmt" and inside(s[3], known)) for s in kept_pins]
    for a, b, rep in sorted(cuts, key=lambda c: c[0], reverse=True):
        t = t[:a] + rep + t[b:]
    left = [s for s in sites_of(t) if re.search(r"\b%s\b" % V, t[s[3]:s[4]])]
    if len(left) != len(kept_pins):
        return None, "pin-drift"
    chosen = [s for s, k in zip(left, kill_pin) if k]
    if chosen:
        t = erase_many(t, chosen, clean_notes=True)
    if not confined and re.search(r"\b%s\b" % V, mask_comments(t)):
        return None, "still-mentioned"
    # pin notes the edit left standing alone on their own line go too (the original's stay)
    orig_notes = collections.Counter(m.group(0).strip() for m in NOTE_RE.finditer(text))
    def drop_new_orphans(m):
        k = m.group(0).strip()
        if orig_notes[k] > 0:
            orig_notes[k] -= 1; return m.group(0)
        return ""
    t = NOTE_RE.sub(drop_new_orphans, t)
    # `(T *)((u8 *)D_X)` is `(T *)D_X`: the byte view was only there for the offset that is gone
    t = re.sub(r"\((\s*[A-Za-z_][\w ]*\*+\s*)\)\s*\(\s*\((?:u8|s8|char|unsigned char|signed char) \*\)(&?D_[0-9A-F]{8})\s*\)",
               r"(\1)\2", t)
    # and a cast of a parenthesised lone symbol drops the parentheses: `(void **)(D_X)` -> `(void **)D_X`
    t = re.sub(r"\((\s*[A-Za-z_][\w ]*\*+\s*)\)\s*\(\s*(&?D_[0-9A-F]{8})\s*\)", r"(\1)\2", t)
    for e in sorted(externs):
        if e.strip() in t:
            continue
        # after the top-level includes, never after the last extern: that one can sit inside an
        # #ifdef arm, where the -DNON_MATCHING port build would not see the new declaration
        L = t.splitlines(True)
        at = max((i for i, l in enumerate(L) if l.startswith("#include")), default=-1)
        L.insert(at + 1, e); t = "".join(L)
    if LOCAL_SYM_RE.search(mask_comments(t)) and not LOCAL_SYM_RE.search(mask_comments(text)):
        return None, "local-named-like-a-symbol"
    from pin_census import unscored_text
    if unscored_text(t) != unscored_text(text):
        return None, "port-arm"                 # V lives in a NON_MATCHING / #if 0 arm too: leave it
    return t, {"var": v, "uses": len(uses), "defs": len(marks), "pins": len(pins)}


def addrvars(text, detail=None):
    """Variables assigned an address literal that carry at least one pin.

    `detail` (a `Detail`) records why a pinned assigned name was NOT admitted, so the refusal table
    can put pins behind the eligibility refusal too:
      `literal-def-not-pinned`     the page variable exists but no pin names it
      `symbol-page-def-only`       pinned, its definition already NAMES a symbol's ADDRESS
                                   (`v = (T *)D_X;` - read through `sym_value`, so a LOAD from a
                                   symbol is not counted): `rewrite_var`'s own `symdef` branch can
                                   read the shape, but this scan never offers the variable, so the
                                   branch is unreachable on its own
      `symbol-decl-init-only`      the same, spelled as a declaration initialiser (`T *v = &D_X;`),
                                   which `rewrite_var` refuses `decl-init` even when offered
      `non-ram-page-literal`       pinned, its definition is an address literal outside RAM (the
                                   scratchpad `0x1F800000`, an uncached/IO page): no symbol names it
    """
    masked = mask_comments(text)
    names = {m.group(1) for m in re.finditer(r"\(?\b([A-Za-z_]\w*)\)?\s*=\s*%s\s*;" % _lit(), masked)}
    pinned = set()
    for s in sites_of(text):
        pinned.update(re.findall(r"\b([A-Za-z_]\w*)\b", text[s[3]:s[4]]))
    out = sorted(n for n in names if n in pinned)
    symdef = di = set()
    if detail is not None or _on("T29_SYMDEF"):
        symdef, di = symbol_defined(text, masked, pinned, names)
    if _on("T29_SYMDEF"):
        out = sorted(set(out) | symdef | di)
    if detail is not None:
        for n in sorted(names - pinned):
            detail.note("literal-def-not-pinned", n)
        for n in sorted(symdef):
            detail.note("symbol-page-def-only", n)
        for n in sorted(di):
            detail.note("symbol-decl-init-only", n)
        anylit = {m.group(1) for m in re.finditer(NONRAM_RE, masked)}
        for n in sorted((anylit & pinned) - names - symdef - di):
            detail.note("non-ram-page-literal", n)
    return out


def candidates(text, detail=None):
    out, cur, used, skipped = [], text, [], {}
    for v in addrvars(text, detail):
        new, info = rewrite_var(text, v)
        if new is None:
            skipped[v] = info
            if detail is not None:
                detail.note(info.split(":")[0] if info.startswith("type:") else info, v)
            continue
        out.append(("addrsym:" + v, new))
        nxt, _ = rewrite_var(cur, v)
        if nxt is not None:
            cur = nxt; used.append(v)
    if len(used) > 1:
        out.insert(0, ("addrsym:*" + "+".join(used), cur))
    if _any_opening():
        # an opening only ever ADDS (review D3): every pre-round-34 candidate this menu does not
        # already carry is appended, so the joint text HEAD would have tried is still on offer.
        have = {t for _, t in out}
        for lab, t in _baseline_candidates(text):
            if t not in have:
                have.add(t)
                out.append((lab, t))
    return out, skipped


class T:
    name = "t29_addrsym"; level = 1
    needs_verify = True

    @staticmethod
    def eligible(text, row, census):
        if not sites_of(text):
            return "no pin sites"
        if not addrvars(text):
            return "no pinned address-literal variable"
        return None

    @staticmethod
    def apply_verified(text, row, census, vf):
        cands, skipped = candidates(text)
        if not cands:
            return None, {"refused": ["no rewritable variable: " + ", ".join("%s %s" % kv for kv in sorted(skipped.items()))]}
        cands.sort(key=lambda c: len(sites_of(c[1])))              # most pins removed first
        # With an opening on, a variable may now be rewritten whose pins are all on OTHER text: the
        # rewrite is exact and frees NOTHING, and `lane_eval`'s fewer-pin guard rejects it as an
        # error (three rows did exactly that under T29_SYMDEF).  A candidate an OPENING introduced
        # and that removes no pin is not a result; skip it.  A PRE-ROUND-34 candidate is never
        # skipped, however pin-free (review D1: dropping those changed what sweep.py saw on 10 rows
        # the opening does not apply to).  So on a row no opening touches, this filter removes
        # nothing and the sequence put to vf is byte-identical to HEAD.
        if _any_opening():
            n0 = len(sites_of(text))
            base = {t for _, t in _baseline_candidates(text)}
            cands = [c for c in cands if c[1] in base or len(sites_of(c[1])) < n0]
            if not cands:
                return None, {"refused": ["no candidate removes a pin"]}
        for label, t in cands:
            if vf(t).get("exact"):
                return t, {"label": label}
        # rule 1 holds from here: no candidate is exact at the recorded cell
        g0 = "-G0" in row["cfg"]
        for cell in sorted(CDK, key=lambda c: ("-G0" in c) != g0):
            if cell == row["cfg"] or not vf(text, cell).get("exact"):
                continue                                             # rule 2: the pinned text must be exact there too
            for label, t in cands:
                if vf(t, cell).get("exact"):
                    return t, {"label": label, "cfg": cell}
        return None, {"refused": ["no candidate exact at the recorded cell or at a CDK cell that admits the pinned text"]}
