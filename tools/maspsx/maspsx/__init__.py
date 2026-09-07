import hashlib
import os
import struct
import re

from functools import lru_cache
from pathlib import Path
from typing import List


# LEAD 27 page-base tail-slot pin marker. Emitted ONLY by the C-side
# ``ASM_PAGEBASE_PIN`` macro (include/common.h) as an inline-asm comment
# ``#maspsx_pagebase_pin $R`` that names the pinned register. gcc never emits
# this token in any natural output (its own comments are #APP/#NO_APP, `#nop`,
# `.file` names and `# 0x..` value annotations -- never an arbitrary
# identifier), so its presence is an unforgeable side-channel proving a bare
# upper-half load is a DELIBERATE dead page-base pin rather than a natural
# ``0xNNNN0000`` mask constant. ``process_line`` normally drops every ``#``
# comment; it preserves lines carrying THIS token so the sink pass can key on
# them, then the pass consumes them (and a leftover marker comment is a no-op
# to GNU as, so it is byte-neutral even if never consumed).
PAGEBASE_PIN_MARKER = "maspsx_pagebase_pin"

# LEAD 28 tail-slot dead-value pin marker (same unforgeable-marker family as
# ``PAGEBASE_PIN_MARKER``; emitted ONLY by the ``ASM_TAILSLOT_PIN`` C macro).
# Generalises the page-base pin from a bare ``lui``/``li`` to ANY dead value
# ASPSX rematerialises into a converted tail-``j`` delay slot (e.g. a dead
# dispatch ``addu``). ``process_line`` preserves lines carrying THIS token (like
# the page-base marker) so ``_rotate_dead_value_into_tail_j_delay`` can key on it.
TAILSLOT_PIN_MARKER = "maspsx_tailslot_pin"

# LEAD 22 live-return pin.  This is deliberately distinct from the generic
# dead-value tail-slot marker: it authorizes preserving a post-call field
# restore while a proven sibcall is converted to a retail tail jump.
LIVE_SIBCALL_PIN_MARKER = "maspsx_live_sibcall_pin"

# LEAD 29 SHAPE-D explicit per-site marker.  Unlike the evidence-file-only
# LEAD-22 shapes, this authorizes an otherwise live fall-through after a
# proven sibcall.  The marker carries caller function, retail site address,
# and direct callee; the pass authenticates all three before changing only
# the jal opcode.  It is emitted only by ASM_SHAPE_D_SIBCALL_PIN in common.h.
SHAPE_D_PIN_MARKER = "maspsx_shape_d_pin"


# LEAD 30 jal-delay store pin marker (same unforgeable-marker family as the two
# above; emitted ONLY by the ``ASM_JALDELAY_PIN`` C macro). The two older markers
# both govern a CONVERTED tail ``j`` -- a slot maspsx itself created. This one
# governs a REAL ``jal`` call's delay slot, which gcc has already filled: ASPSX's
# own schedule keeps a store of a just-loaded value pending until that delay slot
# and pulls the displaced filler up in front of the call, a length-preserving
# 2-way rotation gcc's dbr pass never performs (measured: genuine ASPSX
# 2.67/2.77/2.79/2.86 all reproduce gcc's order byte-for-byte, so this is an
# opt-in lever, NOT an assembler-emulation fix). ``process_line`` preserves lines
# carrying THIS token so ``_rotate_marked_store_into_jal_delay`` can key on it.
JALDELAY_PIN_MARKER = "maspsx_jaldelay_pin"

# LEAD 31 forward-edge label split.  This reserved token is emitted only by
# ``ASM_BRANCH_LABEL_SPLIT``; natural gcc comments cannot opt into the pass.
BRANCH_LABEL_SPLIT_MARKER = "maspsx_branch_label_split"

branch_mnemonics = {
    "beq",
    "bgez",
    "bgtz",
    "blez",
    "bltz",
    "bne",
}
jump_mnemonics = {
    "j",
    "jal",
}
load_mnemonics = {
    "lb",
    "lbu",
    "lh",
    "lhu",
    "lw",
    "lwl",
    "lwr",
}
store_mnemonics = {
    "sb",
    "sh",
    "sw",
    "swl",
    "swr",
    "swc2",
}
# LEAD 2/4 guard #6 (DESTINATION CLASSIFICATION, 2026-08-14): mnemonics whose FIRST
# operand is a SOURCE, not a destination. Both %lo-fold passes used to read operand 1
# of ANY instruction as a write, so `bgez $3,$L1` silently UNTAGGED a still-live %hi
# base: the addiu was deleted while every later access through $3 kept its numeric
# offset (work/town_100_20260812/maspsx_lo_fold_audit/repro/b.s -- a miscompile on
# ALL paths, no control-flow join required). Anything NOT listed here (and not a
# store) keeps the old "operand 1 is written" reading; an unlisted mnemonic that
# merely MENTIONS a tagged register still falls through to the value-use bail, which
# is the conservative direction. Strictly SUBTRACTIVE: it can only decline folds.
first_operand_is_source = {
    # conditional branches (hardware + `as` pseudo forms)
    "b", "bal", "beq", "beql", "bne", "bnel", "beqz", "beqzl", "bnez", "bnezl",
    "blez", "blezl", "bgtz", "bgtzl", "bltz", "bltzl", "bgez", "bgezl",
    "bltzal", "bltzall", "bgezal", "bgezall",
    "bgt", "bgtu", "blt", "bltu", "bge", "bgeu", "ble", "bleu",
    "bc0f", "bc0t", "bc1f", "bc1t", "bc2f", "bc2t",
    "bc0fl", "bc0tl", "bc1fl", "bc1tl", "bc2fl", "bc2tl",
    # jumps: `jr $R` / `jalr $R` READ the register
    "j", "jr", "jal", "jalr",
    # hi/lo + coprocessor writes: operand 1 is the GPR being read
    "mtlo", "mthi", "mtc0", "mtc1", "mtc2", "ctc0", "ctc1", "ctc2",
    # multiply/divide: the GPR operands are all sources (dest is HI/LO, or the
    # `$0` placeholder gcc emits in the three-operand form)
    "mult", "multu", "div", "divu", "dmult", "dmultu", "ddiv", "ddivu",
    # traps
    "teq", "tne", "tlt", "tltu", "tge", "tgeu",
}
# LEAD 29 (func_80E65598 / true name func_80174D98, dungeon 2.8.1-G0): gcc emits the
# UNALIGNED access macros for a packed/misaligned scalar. Both maspsx and GNU `as`
# expand them to an lwl/lwr (swl/swr) pair, but the pair still ends in a real LOAD, so
# its destination register carries a load-delay slot exactly like a plain `lw`. maspsx
# passed these through its dispatch's final `else` (they are in neither table), so no
# delay nop was ever considered and a dependent next instruction followed immediately.
# Genuine ASPSX 2.67 / 2.77 / 2.79 / 2.86 all emit `lwl; lwr; nop; swl; swr` for
# `ulw $2,72($18); usw $2,76($16)` and retail agrees (retail word 31 is that nop) — see
# work/debt_20260803/maspsx_leads/func_80E65598/. Kept as their OWN tables, not merged
# into load_mnemonics/store_mnemonics, because those two drive ~20 other passes
# (fold-lo, delay-slot fills, frame elision) that have never seen a 2-word macro.
unaligned_load_mnemonics = {
    "ulw",
    "ulh",
    "ulhu",
}
unaligned_store_mnemonics = {
    "usw",
    "ush",
}


# LEAD 34 -- RETURN-DELAY BACKFILL, FILL/KEEP DISCRIMINATOR (ladder step 3,
# FUNCTION-BLIND since 2026-09-06; the per-function waiver set that used to sit
# here is DELETED).  `_backfill_return_delay_store` (LEAD 19/23) sinks the
# reg-base store that sits immediately before a frameless `jr $ra` into the
# return delay slot.  Its guard (a) declines whenever the store's VALUE
# register is written by the instruction immediately before the store; two
# matched rows contradicted that shape (retail FILLS on both) and were carried
# by an opt-in-by-name waiver until the real separator was found one
# instruction further back: whether the PRODUCER of the stored value is itself
# stalled in the load-delay shadow of the load feeding it.  That test is
# `_producer_in_load_shadow`; it is local, name-free and strictly additive --
# but the shape alone does not predict retail (the same shape KEEPS in another
# container), so it fires only under the DEFAULT-OFF, function-blind build
# switch `--fill-shadowed-return-delay`, which is set per CONTAINER.
# Corpus receipts (every backfill candidate site in the matched overlay corpus,
# with the live FILL/KEEP decision and the rule's verdict on each):
# work/bridge_wave_20260906/maspsx_general_return_delay/REPORT.md.

# LEAD 13 EXTERN DISPATCH TABLES.  `_expand_casesi_jumptable_load` rewrites a
# compiler-generated switch dispatch from GNU as's `$at` indexed-load macro to the
# base-materialised form retail uses.  It admits COMPILER-LOCAL tables (`$L...`)
# unconditionally, because nothing but a casesi can produce one; an ORDINARY
# GLOBAL is admitted only by name, here.
#
# WHY A GLOBAL EVER APPEARS.  The repo's LANDING idiom for a row whose retail jump
# table lives in the data blob is a computed goto through an
# `extern void *jtbl_XXXX[]` absolute (src/w_800595C0.c, w_8005F134.c,
# w_8004CECC.c, w_80057D20.c, w_80042BDC.c, and the symbols in
# config/generated/*.undefined_syms.txt) -- so the dispatch symbol is a global and
# the TU emits no `.rodata` jump table of its own, which is what makes it LINK.
#
# WHY THOSE FIVE ROWS DO NOT NEED AN ENTRY.  They compile at the default `-mgas`,
# where `mips_split_addresses` is ON (config/mips/mips.c:3679 --
# `TARGET_GAS && optimize && !flag_pic && Pmode == SImode`) and gcc emits the split
# `lui`/`addiu`/`addu`/`lw 0()` itself; the `$at` macro this pass keys on never
# appears.  MEASURED on src/w_8004CECC.c: its listing has no `$at` block at the
# dispatch at all.  Under `-mmips-as` the SAME switch turns splitting OFF and macro
# emission ON, so the identical source arrives as the `$at` indexed-load macro --
# and retail's bytes are the base-materialised form either way.
#
# WHY BY NAME AND NOT STRUCTURALLY.  The shape guards alone cannot tell this site
# from `lw $2,D_80070000($2)` / `j $2`, a DATA-symbol indexed load feeding an
# indirect jump, which the pass deliberately leaves as an `$at` macro
# (`tests/test_casesi_jumptable.py::test_data_symbol_indexed_load_stays_at_macro`).
# So a global is opt-in: naming the symbol is the claim that it is a table of CODE
# addresses.  A symbol that is not listed is a no-op; the structural guards still
# decide every listed one, and a LOCAL `$L...` table never needs an entry.
#
# DEPRECATED AND INTENTIONALLY EMPTY since 2026-09-07.  Its one member
# (`jtbl_8002D5C0`) existed only because its owning main-EXE TU was built
# `-mmips-as`, where `mips_split_addresses` is OFF and the dispatch arrives as the
# `$at` indexed-load macro.  That TU now compiles at stock `-G32` under the default
# `-mgas`, so gcc emits the split `lui`/`addiu`/`addu`/`lw 0()` itself and this
# admission never fires.  MEASURED: with the table emptied the TU is still
# byte-exact (match.py MATCH words_off=0 698/698) and the full main-EXE rebuild is
# `build/slus_006.14: OK`.  Do not add members; the mechanism is kept (with its
# tests) only so a future row can be evidenced into it.
casesi_extern_dispatch_tables: set[str] = set()


# NO FUNCTION-NAME KEYS REMAIN IN maspsx (2026-09-07, bridge burn-down Phase 2c).
#
# The last one, `QUALIFIED_NORETURN_TAILS = {("func_818CE83C",
# "func_80024094")}`, was deleted here once its single dependent row was
# re-landed at stock: 0x80024094 is that row's OWN loop head (bank law true base
# 0x8002403C; the "both-ways conflict" on the symbol was a bank-alias collision
# between two overlay pages mapped at 0x80020000), so an ordinary `for (;;)`
# loop reproduces the retail bytes with no fake noreturn extern, no census
# member and no table -- landed as true-space `func_8002403C`
# (work/bridge_wave_20260906/close_func_818CE83C/REPORT.md).
# `_rewrite_tail_call_jal_to_j` now has ONLY its general side-channel path.
#
# Do not add a name table back.  A site the family-wide census cannot answer
# ("does this callee return in THIS TU") needs a source-declared per-site
# side-channel -- an `ASM_*` pin macro of the `#maspsx_shape_d_pin` kind -- or,
# as here, a C shape that does not pose the question.


@lru_cache(maxsize=None)
def _read_noreturn_file(path_str: str, _mtime: float) -> frozenset:
    syms: set[str] = set()
    try:
        with open(path_str, errors="replace") as f:
            for raw in f:
                line = raw.split("#", 1)[0].strip()
                if line:
                    syms.add(line)
    except OSError:
        return frozenset()
    return frozenset(syms)


def load_noreturn_syms() -> frozenset:
    """LEAD 18-GENERAL: load the source-derived zero-arg noreturn callee set.

    Path selection: ``$MASPSX_NORETURN_FILE`` when set, else the package-relative
    default ``<repo>/config/noreturn_syms.txt`` (the maspsx package lives at
    ``<repo>/toolchain/maspsx/maspsx``, so the repo root is three parents up from
    the package directory). A missing/unreadable file is an EMPTY set, never an
    error. Results are cached per (path, mtime) so a full build reads the file
    once per unique state.
    """
    path = os.environ.get("MASPSX_NORETURN_FILE")
    if not path:
        try:
            repo_root = Path(__file__).resolve().parent.parents[2]
            path = str(repo_root / "config" / "noreturn_syms.txt")
        except Exception:
            return frozenset()
    try:
        mtime = os.path.getmtime(path)
    except OSError:
        return frozenset()
    return _read_noreturn_file(str(path), mtime)


@lru_cache(maxsize=None)
def _read_sibcall_file(path_str: str, _mtime: float) -> frozenset:
    syms: set[str] = set()
    try:
        with open(path_str, errors="replace") as f:
            for raw in f:
                line = raw.split("#", 1)[0].strip()
                if line:
                    syms.add(line)
    except OSError:
        return frozenset()
    return frozenset(syms)


def load_sibcall_syms() -> frozenset:
    """LEAD 22: load the binary-derived ARG-CARRYING ``j``-only sibcall set.

    These callees are reached ONLY by ``j`` (never ``jal``) across MAIN.BIN, so
    they are genuine noreturn dispatchers -- retail always emits ``j CALLEE`` for a
    tail call into them. maspsx's arg-sibcall pass gates its ``jal``->``j`` shape
    test on membership here, which is what keeps an ordinary RETURNING tail call
    (``return foo(x)`` where foo returns) as ``jal``. Distinct from the zero-arg
    void-noreturn set in config/noreturn_syms.txt (LEAD 18).

    Path selection mirrors ``load_noreturn_syms``: ``$MASPSX_SIBCALL_FILE`` when
    set, else the package-relative default ``<repo>/config/sibcall_syms.txt``. A
    missing/unreadable file is an EMPTY set (never an error), so the pass is a
    no-op wherever the evidence file is absent. Cached per (path, mtime).
    """
    path = os.environ.get("MASPSX_SIBCALL_FILE")
    if not path:
        try:
            repo_root = Path(__file__).resolve().parent.parents[2]
            path = str(repo_root / "config" / "sibcall_syms.txt")
        except Exception:
            return frozenset()
    try:
        mtime = os.path.getmtime(path)
    except OSError:
        return frozenset()
    return _read_sibcall_file(str(path), mtime)


@lru_cache(maxsize=None)
def _read_shape_d_manifest(path_str: str, _mtime: float) -> tuple[tuple[str, int, str], ...]:
    """Read an explicit, work-only SHAPE-D caller/site/callee sidecar.

    The sidecar is intentionally separate from cc1 output: it is a review
    artifact supplied to maspsx by the isolated harness, never a general
    membership rule.  Malformed rows are ignored as a whole (fail closed).
    """
    rows: list[tuple[str, int, str]] = []
    try:
        with open(path_str, errors="replace") as f:
            for raw in f:
                line = raw.split("#", 1)[0].strip()
                if not line:
                    continue
                parts = line.split()
                if len(parts) != 3 or not re.fullmatch(r"[A-Za-z_]\w*", parts[0]):
                    return ()
                if not re.fullmatch(r"0x[0-9A-Fa-f]+", parts[1]):
                    return ()
                site = int(parts[1], 16)
                if (site & 3) or not (0x80000000 <= site <= 0x8FFFFFFF):
                    return ()
                if not re.fullmatch(r"[A-Za-z_.][\w.]*", parts[2]):
                    return ()
                rows.append((parts[0], site, parts[2]))
    except OSError:
        return ()
    if len({(caller, site) for caller, site, _ in rows}) != len(rows):
        return ()
    return tuple(rows)


def load_shape_d_manifest(path_str: str | None = None) -> tuple[tuple[str, int, str], ...]:
    """Load an explicit SHAPE-D manifest, or the legacy environment path."""
    path = path_str or os.environ.get("MASPSX_SHAPE_D_MANIFEST")
    if not path:
        return ()
    try:
        mtime = os.path.getmtime(path)
    except OSError:
        return ()
    return _read_shape_d_manifest(str(path), mtime)


register_aliases = {
    "$0": "$zero",
    "$1": "$at",
    "$2": "$v0",
    "$3": "$v1",
    "$4": "$a0",
    "$5": "$a1",
    "$6": "$a2",
    "$7": "$a3",
    "$8": "$t0",
    "$9": "$t1",
    "$10": "$t2",
    "$11": "$t3",
    "$12": "$t4",
    "$13": "$t5",
    "$14": "$t6",
    "$15": "$t7",
    "$16": "$s0",
    "$17": "$s1",
    "$18": "$s2",
    "$19": "$s3",
    "$20": "$s4",
    "$21": "$s5",
    "$22": "$s6",
    "$23": "$s7",
    "$24": "$t8",
    "$25": "$t9",
    "$28": "$gp",
    "$29": "$sp",
    "$30": "$fp",
    "$31": "$ra",
}

single_reg_loads = {
    "mult",
    "multu",
    "div",
    "divu",
    "rem",
    "remu",
    "move",
    "negu",
    "nor",
}
double_reg_loads = {
    "and",
    "andi",
    "or",
    "ori",
    "xor",
    "xori",
    "addu",
    "subu",
    "sll",
    "slr",
    "srl",
    "sra",
    "slt",
    "slti",
    "sltu",
}


def strip_comments(line: str) -> str:
    if line.count("#") > 0:
        line = line.split("#")[0]
    return line.strip()


def canonical_reg(reg: str) -> str:
    return register_aliases.get(reg, reg)


def line_loads_from_reg(line: str, r_source: str) -> bool:
    """
    NOTE: Returns True even if line might use $at expansion
    """
    line = strip_comments(line)

    # escape dollar
    r_source = r_source.replace("$", r"\$")

    if match := re.match(r"^([A-z][A-z0-9]*)\s+(.*)$", line):
        op, rest = match.group(1, 2)
    else:
        return False

    if op in load_mnemonics:
        # lwl	$9,7($2)
        if re.match(rf"^.*\(\s*{r_source}\s*\)$", rest):
            return True

    elif op in store_mnemonics:
        if re.match(rf"^.*\(\s*{r_source}\s*\)$", rest):
            return True
        # "line_loads_from_reg" is a bit of a lie
        if re.match(rf"^{r_source},.*$", rest):
            return True

    elif op in unaligned_load_mnemonics:
        # LEAD 29: `ulw $2,72($18)` reads its BASE register only.
        if re.match(rf"^.*\(\s*{r_source}\s*\)$", rest):
            return True

    elif op in unaligned_store_mnemonics:
        # LEAD 29: `usw $2,76($16)` reads BOTH the stored value and the base.
        if re.match(rf"^.*\(\s*{r_source}\s*\)$", rest):
            return True
        if re.match(rf"^{r_source},.*$", rest):
            return True

    elif op == "lwc2":
        # lwc2 $5, 4( $4
        if re.match(rf"^.*\(\s*{r_source}\s*\)$", rest):
            return True

    elif op == "jal":
        if re.match(rf"^.*,\s*{r_source}$", rest):
            return True

    elif op == "j":
        if re.match(rf"^{r_source}$", rest):
            return True

    elif op in ("ctc2", "mtc0", "mtc2"):
        if re.match(rf"^{r_source},.*$", rest):
            return True

    elif op in ("mtlo", "mthi"):
        if re.match(rf"^{r_source}$", rest):
            return True

    elif op in branch_mnemonics:
        if re.match(rf"^{r_source},.*$", rest):
            return True
        if re.match(rf"^.*,\s*{r_source},.*$", rest):
            return True

    elif op in single_reg_loads:
        if re.match(rf"^.*,\s*{r_source}$", rest):
            return True
        if op.startswith("mult"):
            if re.match(rf"^{r_source},.*$", rest):
                return True
        if op.startswith("div") or op.startswith("rem"):
            # e.g. div	$3,$3,$7
            if re.match(rf"^.*,{r_source}.*$", rest):
                return True

    elif op in double_reg_loads:
        if re.match(rf"^.*,\s*{r_source},.*$", rest):
            return True
        if re.match(rf"^.*,.*,\s*{r_source}$", rest):
            return True

    return False


def is_number(value: str) -> bool:
    if re.match(r"^-?\d+$", value) or re.match(r"^-?0x[A-Fa-f0-9]+$", value):
        return True
    return False


def uses_at(line: str) -> bool:
    line = strip_comments(line)

    # sw	$2,%lo(s_attr)($3)
    if match := re.match(r"^s[wbh]\s+(\$[a-z0-9]+),\s*%lo\(([^(]+)\)\(([^)]+)\)", line):
        return False

    # sw	$2,D_801813A4
    # sw	$3,g_CurrentRoom+40
    # sw	$2,D_us_8017863C.4
    if match := re.match(r"^s[wbh]\s+(\$[a-z0-9]+),\s*(-?[A-z0-9_.+]+)$", line):
        operand = match.group(2)
        if not is_number(operand):
            return True

    # sb	$2,g_InputSaveName($3)
    # sw	$2,-26($16)
    elif match := re.match(r"^s[wbh]\s+(\$[a-z0-9]+),\s*([^(]+)\(([^)]+)\)", line):
        operand = match.group(2)

    # lw	$2,-1000($16)
    elif match := re.match(r"l[a-z]+\s+(\$[a-z0-9]+),\s*([^(]+)\(([^)]+)\)", line):
        operand = match.group(2)

    else:
        return False

    if is_number(operand):
        num = int(operand, 0)
        if -32769 < num < 32768:
            return False

    return True


def parse_load_or_store(rest: str):
    if match := re.match(r"(\$[a-z0-9]+),\s*%lo\(([^(]+)\)\(([^(]+)\)", rest):
        r_dest, operand, r_source = match.group(1, 2, 3)
        needs_expanding = False
    elif match := re.match(r"(\$[a-z0-9]+),\s*([^(]+)\(([^)]+)\)", rest):
        r_dest, operand, r_source = match.group(1, 2, 3)
        needs_expanding = True
    elif match := re.match(r"(\$[a-z0-9]+),\s*([^(]+)", rest):
        r_dest, operand = match.group(1, 2)
        r_source = None
        needs_expanding = True
    else:
        raise Exception(f"Unable to parse load/store instruction: {rest}")

    if re.match(r"^-?\d+$", operand) or re.match(r"^-?0x[A-Fa-f0-9]+$", operand):
        is_addend = False
    else:
        is_addend = True

    return (r_source, r_dest, operand, is_addend, needs_expanding)


def div_needs_expanding(line: str) -> bool:
    inst, *rest = line.split()
    if not (inst.startswith("div") or inst.startswith("rem")):
        return False

    r_dest, *_ = rest[0].split(",")
    return r_dest not in ("$zero", "$0")


def expand_load_immediate(line: str) -> List[str]:
    res = []

    match = re.match(r"li\s+(\$[0-9A-z]+),\s?(-?[x0-9a-fA-F]+)", line)
    assert match is not None, "li regex failed"

    r_dest = match.group(1)
    operand = int(match.group(2), 0)

    if 0 < operand < 0x10000:
        res.append(f"ori\t{r_dest},$zero,{operand}")
    elif operand >= 0x10000:
        res.append(f"lui\t{r_dest},({operand} >> 16) & 0xFFFF")
        if operand & 0xFFFF:
            res.append(f"ori\t{r_dest},{r_dest},{operand} & 0xFFFF")
    elif 0 > operand > -0x8000:
        res.append(f"addiu\t{r_dest},$zero,{operand}")
    elif operand == -0x8000:
        res.append(f"addiu\t{r_dest},$zero,{operand} & 0xFFFF")
    elif operand < -0x8000:
        res.append(f"lui\t{r_dest},({operand} >> 16) & 0xFFFF")
        if operand & 0xFFFF:
            res.append(f"ori\t{r_dest},{r_dest},{operand} & 0xFFFF")
    else:
        # TODO: raise an exception here instead?
        # ori is actually addiu on ASPSX 2.56+
        res.append(f"ori\t{r_dest},0")

    return res


def expand_move(line: str):
    line = strip_comments(line)
    op, *rest = line.split()
    if op == "move":
        args = " ".join(rest)
        r_dest, r_source = args.split(",")
        return f"addu\t{r_dest},{r_source},$zero"
    return line


def is_label(line: str):
    return re.match(r"\$L(b|e)?\d+:$", line)


def is_instruction(line: str, ignore_nop=False, ignore_set=False, ignore_label=False):
    if len(line) == 0:
        return False

    if ignore_nop and line == "#nop":
        return False
    if ignore_set and line in (
        ".set\treorder",
        ".set\tnoreorder",
        ".set\tvolatile",
        ".set\tnovolatile",
    ):
        return False
    if ignore_label and is_label(line):
        return False

    if line.startswith(".stab"):
        return False
    if line.startswith(".def") or line.startswith(".bend") or line.startswith(".begin"):
        return False
    if line.startswith(".loc"):
        return False

    if line.startswith("L") and line[1] not in "0123456789" and line.endswith(":"):
        return False
    if line in (".set\tmacro", ".set\tnomacro"):
        return False
    if line in ("#.set\tvolatile", "#.set\tnovolatile"):
        return False
    if line in ("#APP", "#NO_APP"):
        return False
    # LEAD 30: the jal-delay pin is a pure ANNOTATION -- it must be transparent to
    # ``get_next_instruction``, which every load-delay decision consults. Without
    # this, `lw $3,..` / marker / `<user of $3>` would ask
    # ``line_loads_from_reg`` about the MARKER (a bare `#` comment, so always
    # False) and silently drop a required hazard nop. Deliberately NOT extended to
    # PAGEBASE/TAILSLOT_PIN_MARKER: those two are already carried by landed
    # candidates, so widening them here would change bytes outside this
    # instrument's zero-affected cohort (see the receipt's review_flags).
    if JALDELAY_PIN_MARKER in line:
        return False

    return True


def get_next_register(reg: str):
    lut = {
        # li $fx
        "$f0": "$f1",
        "$f2": "$f3",
        "$f4": "$f5",
        "$f6": "$f7",
        "$f12": "$f13",
        "$f14": "$f15",
        # names
        "$v0": "$v1",
        "$a0": "$a1",
        "$a2": "$a3",
        "$t0": "$t1",
        "$t2": "$t3",
        "$s0": "$s1",
        "$s2": "$s3",
        # nums
        "$2": "$3",  # $v0
        "$4": "$5",  # $a0
        "$6": "$7",  # $a2
        "$8": "$9",  # $t0
        "$10": "$11",  # t2
        "$18": "$19",  # s2
    }
    next_reg = lut.get(reg)
    assert next_reg is not None, f"Unknown mapping for {reg}"
    return next_reg


def expand_macro(line: str):
    res = []
    for l in strip_comments(line).split(";"):
        l = l.strip()
        if len(l) == 0:
            continue
        op, *rest = l.split()
        res.append(
            (op, " ".join(rest)),
        )
    return res


def load_immediate_single(line: str):
    res = []
    r1, value = line[5:].split(",")
    (num,) = struct.unpack(">i", struct.pack(">f", float(value)))
    upper = (num & 0xFFFF_0000) >> 16
    lower = (num & 0x0000_FFFF) >> 0

    res.append(f"lui\t{r1},0x{upper:X}")
    # we don't always need the lower part
    if lower:
        res.append(f"ori\t{r1},0x{lower:X}")
    return res


def load_immediate_double(line: str):
    res = []
    r1, value = line[5:].split(",")
    r2 = get_next_register(r1)
    (num,) = struct.unpack(">q", struct.pack(">d", float(value)))

    r1_upper = (num & 0x0000_0000_FFFF_0000) >> 16
    r1_lower = (num & 0x0000_0000_0000_FFFF) >> 0
    r2_upper = (num & 0xFFFF_0000_0000_0000) >> 48
    r2_lower = (num & 0x0000_FFFF_0000_0000) >> 32

    if r1_upper or r1_lower:
        res.append(f"lui\t{r1},0x{r1_upper:X}")
        if r1_lower:
            res.append(f"ori\t{r1},0x{r1_lower:X}")
    else:
        res.append(f"li\t{r1},0x0")

    res.append(f"lui\t{r2},0x{r2_upper:X}")
    if r2_lower:
        res.append(f"ori\t{r2},0x{r2_lower:X}")

    return res


class MaspsxProcessor:
    is_reorder = True
    skip_instructions = 0
    file_num = 1
    line_index = 0

    def __init__(
        self,
        lines: List[str],
        sdata_limit=0,
        expand_div=False,
        expand_li=False,
        nop_at_expansion=False,
        nop_mflo_mfhi=True,
        sltu_at=False,
        addiu_at=False,
        div_uses_tge=False,
        gp_allow_offset=False,
        gp_allow_la=False,
        use_comm_section=False,
        use_comm_for_lcomm=False,
        preserve_casesi_at=False,
        preserve_return_delay=False,
        fill_shadowed_return_delay=False,
        retain_tail_frame=0,
        noreturn_epilogue_syms=(),
        live_sibcall_tail=False,
        prefer_target_arg_setup=False,
        preserve_immediate_funcaddr_la=False,
    ):
        self.lines = [x.strip() for x in lines]

        self.sdata_limit = sdata_limit

        self.expand_div = expand_div
        self.expand_li = expand_li

        self.nop_at_expansion = nop_at_expansion
        self.nop_mflo_mfhi = nop_mflo_mfhi

        self.sltu_at = sltu_at
        self.addiu_at = addiu_at
        self.div_uses_tge = div_uses_tge

        self.gp_allow_offset = gp_allow_offset
        self.gp_allow_la = gp_allow_la

        self.use_comm_section = use_comm_section
        self.use_comm_for_lcomm = use_comm_for_lcomm

        # Per-TU dialect controls. These default to the established ASPSX
        # emulation and change output only when an explicit assembler flag is
        # selected for the current translation unit.
        self.preserve_casesi_at = preserve_casesi_at
        self.preserve_return_delay = preserve_return_delay
        self.fill_shadowed_return_delay = fill_shadowed_return_delay
        self.retain_tail_frame = retain_tail_frame
        self.noreturn_epilogue_syms = set(noreturn_epilogue_syms)
        self.live_sibcall_tail = live_sibcall_tail
        self.prefer_target_arg_setup = prefer_target_arg_setup
        self.preserve_immediate_funcaddr_la = preserve_immediate_funcaddr_la

        self.bss_entries: dict[str, int] = {}
        self.sbss_entries: dict[str, int] = {}
        self.sdata_entries: dict[str, int] = {}

        self.comm_symbols: set[str] = set()

        # gcc emits `.extern SYM, size`; `as -G` uses the size to pick $gp
        # (size <= -G) vs %hi/%lo (size > -G) access. We track it to gate the
        # store-into-delay-slot %hi/%lo expansion to non-small-data symbols only.
        self.extern_sizes: dict[str, int] = {}

        # LEAD 18-GENERAL: source-derived set of ZERO-ARG noreturn callee
        # symbols. A `jal` into one of these whose $ra link is dead is rewritten
        # to `j` (retail/ASPSX does the same; corpus-proven, 66/66).
        self.noreturn_syms = load_noreturn_syms()

        # LEAD 22: binary-derived ARG-CARRYING `j`-only sibcall dispatcher set
        # (config/sibcall_syms.txt). The arg-sibcall pass gates its jal->j shape
        # test on membership here so it fires ONLY on proven dispatchers, never
        # on a returning tail call. Distinct from the void-noreturn set above.
        self.sibcall_syms = load_sibcall_syms()

        # SHAPE-D sidecar manifest: supplied only by the environment test hook
        # (MASPSX_SHAPE_D_MANIFEST).  The default-off per-function release flag
        # that used to point this at a tracked fixture was deleted with the rest
        # of the per-function retail dial family (2026-09-07 Phase 2).  The last
        # such dial went the same day (Phase 2d): maspsx has NO per-function
        # option and NO function-name key left.  Do not add one back.
        self.shape_d_manifest = load_shape_d_manifest()

    def preprocess_lines(self) -> None:
        in_sdata = False
        uses_size = False

        for line in self.lines:
            if line == "":
                continue

            if line.startswith(".align"):
                # TODO: worry about alignment later
                continue

            if line.startswith(".globl"):
                continue

            if line.startswith(".text"):
                in_sdata = False
                continue
            if line.startswith(".data"):
                in_sdata = False
                continue
            if line.startswith(".rdata"):
                in_sdata = False
                continue

            if line.startswith(".section") and line.endswith(".text"):
                in_sdata = False
                continue

            if line.startswith("#"):
                continue

            if line.startswith(".sdata"):
                in_sdata = True
                continue

            if line.startswith(".file"):
                in_sdata = False
                continue

            if line.startswith(".extern"):
                in_sdata = False
                # e.g. .extern	D_800814C8, 4
                if match := re.match(r"\.extern\s+([^,]+),\s*([0-9]+)", line):
                    self.extern_sizes[match.group(1).strip()] = int(match.group(2))
                continue

            if line.startswith(".comm") or line.startswith(".lcomm"):
                # e.g.	.comm	MENU_RadarScale_800AB480,4
                in_sdata = False
                _, var = line.split()
                symbol, size_str, *_ = var.split(",")
                size = int(size_str)
                if size <= self.sdata_limit:
                    self.sbss_entries[symbol] = size
                else:
                    self.bss_entries[symbol] = size

                if line.startswith(".comm"):
                    self.comm_symbols.add(symbol)
                continue

            if in_sdata:
                # NOTE: newer compilers emit .size for sdata, old ones do not...
                if match := re.match(r"\.size\s+([^,]+),([0-9]+)", line):
                    current_symbol = match.group(1)
                    size = int(match.group(2))
                    self.sdata_entries[current_symbol] = size
                    uses_size = True
                    continue

                if not uses_size:
                    if line.endswith(":"):
                        current_symbol = line.replace(":", "")
                        self.sdata_entries[current_symbol] = 0
                    else:
                        if line.startswith(".type"):
                            continue

                        if line.startswith(".space"):
                            _, size_str = line.split()
                            size = int(size_str)
                        elif line.startswith(".word"):
                            size = 4
                        elif line.startswith(".half") or line.startswith(".short"):
                            size = 2
                        elif line.startswith(".byte"):
                            size = 1
                        elif line.startswith(".ascii"):
                            # e.g. .ascii	"Map poly groups\000"
                            # NOTE: len('.ascii\t""') == 9
                            size = len(line) - 9
                        else:
                            raise Exception(
                                f"Unable to parse .sdata instruction: {line}"
                            )
                        self.sdata_entries[current_symbol] += size

    def _split_marked_branch_label(self, res):
        """Retarget one marked forward edge across a direct ``la`` pair.

        Old GCC can make several branches share the label immediately before a
        direct ``la`` macro while retail has one edge target the point between
        its ``lui`` and ``addiu`` halves.  A source marker before the exact
        ``slt``/zero-test branch opts that one edge into the split.  Unmarked
        streams and malformed markers are returned unchanged.
        """
        def clean(i):
            return strip_comments(res[i]).strip()

        def ignorable(i):
            body = clean(i)
            return not body or res[i].lstrip().startswith("#")

        def next_code(i, stop=None):
            if stop is None:
                stop = len(res)
            while i < stop and ignorable(i):
                i += 1
            return i

        # Keep label resolution inside the marker's .ent/.end function.  GCC's
        # local $L names are not an interface we should assume globally unique,
        # and a malformed marker must never reach into a following function.
        function_ranges = []
        function_start = None
        for i in range(len(res)):
            body = clean(i)
            if body.startswith(".ent"):
                function_start = i
            elif body.startswith(".end") and function_start is not None:
                function_ranges.append((function_start, i + 1))
                function_start = None
        if function_start is not None:
            function_ranges.append((function_start, len(res)))

        used = set()
        for i in range(len(res)):
            body = clean(i)
            if body.endswith(":"):
                used.add(body[:-1])
        serial = 0
        branch_re = re.compile(r"^(beq|bne)\s+(.+)$")
        lui_re = re.compile(r"^lui\s+(\$\w+),\s*%hi\(([^)]+)\)$")
        addiu_re = re.compile(
            r"^addiu\s+(\$\w+),(\$\w+),\s*%lo\(([^)]+)\)$"
        )
        la_re = re.compile(r"^la\s+(\$\w+),([A-Za-z_.][\w.]*)$")

        for marker_i, line in enumerate(res):
            if BRANCH_LABEL_SPLIT_MARKER not in line:
                continue
            marker_match = re.search(
                BRANCH_LABEL_SPLIT_MARKER + r"\s+(\$\w+)", line
            )
            if not marker_match:
                continue
            marker_reg = canonical_reg(marker_match.group(1))

            scope = next((bounds for bounds in function_ranges
                          if bounds[0] <= marker_i < bounds[1]), None)
            if scope is None:
                # Unit-sized snippets and old callers may omit .ent/.end.  In
                # that case the whole input remains one explicit scope.
                scope = (0, len(res))
            scope_start, scope_end = scope
            label_sites = {}
            for i in range(scope_start, scope_end):
                body = clean(i)
                if body.endswith(":"):
                    label_sites.setdefault(body[:-1], []).append(i)

            slt_i = next_code(marker_i + 1, scope_end)
            if slt_i >= scope_end:
                continue
            slt_match = re.match(r"^slt\s+(\$\w+),(\$\w+),(.+)$", clean(slt_i))
            if not slt_match or canonical_reg(slt_match.group(2)) != marker_reg:
                continue
            cond_reg = canonical_reg(slt_match.group(1))

            branch_i = next_code(slt_i + 1, scope_end)
            if branch_i >= scope_end:
                continue
            branch_match = branch_re.match(clean(branch_i))
            if not branch_match:
                continue
            operands = [item.strip() for item in branch_match.group(2).split(",")]
            if len(operands) != 3:
                continue
            if {canonical_reg(item) for item in operands[:2]} != {cond_reg, "$zero"}:
                continue
            target = operands[2]
            target_sites = label_sites.get(target, [])
            if len(target_sites) != 1:
                continue
            label_i = target_sites[0]
            if label_i <= branch_i:
                continue

            first_i = next_code(label_i + 1, scope_end)
            if first_i >= scope_end:
                continue
            first = clean(first_i)
            la_match = la_re.match(first)
            if la_match:
                reg, symbol = la_match.groups()
                pair = [
                    f"lui\t{reg},%hi({symbol})",
                    f"addiu\t{reg},{reg},%lo({symbol})",
                ]
                second_i = first_i
                explicit = False
            else:
                lui_match = lui_re.match(first)
                if not lui_match:
                    continue
                second_i = next_code(first_i + 1, scope_end)
                if second_i >= scope_end:
                    continue
                addiu_match = addiu_re.match(clean(second_i))
                if not addiu_match:
                    continue
                reg, symbol = lui_match.groups()
                if (addiu_match.group(1) != reg or addiu_match.group(2) != reg
                        or addiu_match.group(3) != symbol):
                    continue
                pair = [clean(first_i), clean(second_i)]
                explicit = True

            fresh = f"{target}__maspsx_branch_split_{serial}"
            while fresh in used:
                serial += 1
                fresh = f"{target}__maspsx_branch_split_{serial}"

            raw_branch = res[branch_i]
            comment = ""
            if "#" in raw_branch:
                raw_branch, comment = raw_branch.split("#", 1)
                comment = "#" + comment
            raw_branch = raw_branch.rstrip()
            if not raw_branch.endswith(target):
                continue
            res[branch_i] = (raw_branch[:-len(target)] + fresh
                             + ((" " + comment) if comment else ""))

            if explicit:
                res[first_i] = pair[0]
                res.insert(second_i, fresh + ":")
            else:
                res[first_i:first_i + 1] = [pair[0], fresh + ":", pair[1]]
            break

        return res

    def process_lines(self):
        self.is_reorder = True
        self.skip_instructions = 0
        self.file_num = 1
        self.callee_restores = 0  # LEAD 1: callee-saved regs restored in the current function
        # funcaddr-split (see _split_funcaddr_la): a pending `la $R,FUNC` that should
        # claim the next jal's delay slot, so a data store immediately before that jal
        # must NOT steal the slot via _expand_store_to_symbol_in_delay.
        self._pending_funcaddr = None

        self.bss_entries = {}
        self.sbss_entries = {}
        self.sdata_entries = {}
        self.extern_sizes = {}

        self.preprocess_lines()

        res = []
        in_include_asm_hack = False
        for i, line in enumerate(self.lines):
            self.line_index = i

            # LEAD 1 bookkeeping: count callee-saved regs restored from the stack in the
            # current function (reset at each .ent). Used to decide whether the sp-restore
            # may occupy the return-jump delay slot (see _maybe_unfill_return_delay).
            if line.startswith(".ent\t"):
                self.callee_restores = 0
            elif re.match(r"lw\t\$(1[6-9]|2[0-3]|30|31|s[0-7]|fp|ra),[^,]*\(\$sp\)",
                          strip_comments(line)):
                self.callee_restores += 1

            # funcaddr-split bookkeeping: remember a `la $R,FUNC` (function address
            # loaded as a call argument) so the store-into-delay expansion yields the
            # next jal's delay slot to it. Cleared at any control-flow boundary so the
            # window is a single straight-line run ending at the consuming jal.
            _sl = strip_comments(line).strip()
            if line.startswith(".ent\t"):
                self._pending_funcaddr = None
            elif m_la := re.match(r"^la\t(\$\w+),([A-Za-z_.][\w.]*)$", _sl):
                self._pending_funcaddr = (
                    (m_la.group(1), m_la.group(2))
                    if self._is_func_symbol(m_la.group(2))
                    else None
                )
            elif re.match(r"^(jal|j|jr|b\w*)\b", _sl) or _sl.endswith(":"):
                self._pending_funcaddr = None

            if ".ent\t__maspsx_include_asm_hack" in line:
                in_include_asm_hack = True

            if in_include_asm_hack:
                if "# maspsx-keep" in line:
                    res += [line]
                else:
                    res += [f"# {line} # DEBUG: skipped due to include asm hack"]
                if ".end\t__maspsx_include_asm_hack" in line:
                    in_include_asm_hack = False
                continue

            if is_instruction(line) and self.skip_instructions > 0:
                self.skip_instructions -= 1
                res += [f"# {line}  # DEBUG: skipped"]
            else:
                res += self.process_line(line)

        if not self.preserve_casesi_at:
            res = self._expand_casesi_jumptable_load(res)
        res = self._fold_lo_into_accesses(res)
        res = self._fold_selfinc_la(res)
        res = self._sink_call_separated_la(res)
        res = self._split_funcaddr_la(res)
        res = self._prefer_lui_over_sll_branch_delay(res)
        res = self._prefer_marked_target_arg_setup(res)
        res = self._hoist_delay_luis(res)
        res = self._unfill_via_load_delay(res)
        res = self._unfill_jal_sp_delay(res)
        res = self._hoist_zero_arg_before_global_clears(res)
        res = self._expand_smalldata_la(res)
        res = self._rewrite_tail_call_jal_to_j(res)
        # _rewrite_arg_sibcall_jal_to_j (LEAD 22) must run BEFORE the frame
        # elision: for a SIBCALL-member tail it owns the jal->j conversion AND
        # the SHAPE-C deletion of the dead `j $Lepilogue` return path (whose
        # pattern needs the still-`jal` form). If elision converted the jal->j
        # first, that cleanup would no longer match and the dead epilogue jump
        # would survive around the elided frame (LEAD 23).
        res = self._rewrite_arg_sibcall_jal_to_j(res)
        res = self._rewrite_sidecar_shape_d_sibcall(res)
        res = self._rewrite_marked_shape_d_sibcall(res)
        res = self._rewrite_marked_live_sibcall_tail(res)
        res = self._elide_ra_only_frame_for_noreturn_tail(res)
        res = self._rotate_sibcall_v0_into_branch_delay(res)
        res = self._sink_dead_pagebase_into_tail_j_delay(res)
        res = self._rotate_dead_value_into_tail_j_delay(res)
        # LEAD 30 runs LAST of the slot passes: it needs a `jal` that survived the
        # jal->j conversions above (a converted tail is the other passes' turf) and
        # a delay slot in its final, post-fill form.
        res = self._rotate_marked_store_into_jal_delay(res)
        res = self._split_marked_branch_label(res)

        for section, entries in [
            ("sbss", self.sbss_entries),
            ("bss", self.bss_entries),
        ]:
            for i, (symbol, size) in enumerate(entries.items()):
                if i == 0:
                    res.append(f".section .{section}")

                if self.use_comm_section and (
                    symbol in self.comm_symbols or self.use_comm_for_lcomm
                ):
                    # implicit alignment for COMMON
                    res.append(f"\t.comm {symbol},{size}")
                    continue

                if section == "sbss":
                    if size >= 8:
                        res.append("\t.align 3")
                    elif size >= 4:
                        res.append("\t.align 2")
                    elif size >= 2:
                        res.append("\t.align 1")

                # only mark bss symbols as global
                if section == "bss":
                    res.append(
                        f"\t.globl {symbol}",
                    )
                res.extend(
                    [
                        f"{symbol}:",
                        f"\t.space {size}",
                    ]
                )

        return res


    def get_next_instruction(
        self, skip=0, ignore_nop=False, ignore_set=False, ignore_label=False
    ):
        i = self.line_index + 1
        while i < len(self.lines):
            line = self.lines[i]
            if is_instruction(
                line,
                ignore_nop=ignore_nop,
                ignore_set=ignore_set,
                ignore_label=ignore_label,
            ):
                if skip == 0:
                    return line
                skip -= 1
            i += 1

        return ""  # warn user?

    def _symbol_is_non_small_data(self, operand: str) -> bool:
        symbol = operand.split("+")[0]

        if symbol in self.extern_sizes:
            return self.extern_sizes[symbol] > self.sdata_limit
        if symbol in self.bss_entries:
            return self.bss_entries[symbol] > self.sdata_limit
        if symbol in self.sbss_entries or symbol in self.sdata_entries:
            return False
        return False

    @staticmethod
    def _operand_base_symbol(operand: str) -> str:
        return operand.split("+")[0]

    @staticmethod
    def _line_reg_list(line: str) -> list[str]:
        return [canonical_reg(reg) for reg in re.findall(r"\$[A-Za-z0-9]+", line)]

    @staticmethod
    def _instruction_operands(line: str):
        line = strip_comments(line).strip()
        if (
            not line
            or line.startswith(".")
            or line.endswith(":")
            or line.startswith("$L")
            or line.startswith("glabel")
        ):
            return None, []

        parts = line.split(None, 1)
        op = parts[0]
        if len(parts) == 1:
            return op, []
        return op, [part.strip() for part in parts[1].split(",")]

    @classmethod
    def _line_writes_reg(cls, line: str, reg: str) -> bool:
        op, operands = cls._instruction_operands(line)
        if op is None or not operands:
            return False

        reg = canonical_reg(reg)

        if op in store_mnemonics or op in branch_mnemonics:
            return False
        if op in ("j", "jr", "break"):
            return False
        if op in ("jal", "jalr"):
            return reg == "$ra"
        if op in ("mtc0", "mtc2", "ctc2", "mthi", "mtlo"):
            return False
        if op in ("mult", "multu"):
            return False
        if op in ("div", "divu", "rem", "remu"):
            first = cls._line_reg_list(operands[0])
            return len(first) > 0 and first[0] == reg and reg != "$zero"

        first = cls._line_reg_list(operands[0])
        return len(first) > 0 and first[0] == reg and reg != "$zero"

    @classmethod
    def _line_reads_reg(cls, line: str, reg: str) -> bool:
        op, operands = cls._instruction_operands(line)
        if op is None:
            return False

        reg = canonical_reg(reg)

        if op == "lui" or op == "li" or op == "la":
            return False
        if op in load_mnemonics:
            return reg in cls._line_reg_list(",".join(operands[1:]))
        if op in store_mnemonics:
            return reg in cls._line_reg_list(",".join(operands))
        if op in branch_mnemonics:
            return reg in cls._line_reg_list(",".join(operands[:-1]))
        if op == "j":
            return len(operands) == 1 and canonical_reg(operands[0]) == reg
        if op == "jr":
            return reg in cls._line_reg_list(",".join(operands))
        if op == "jal":
            return False
        if op == "jalr":
            return reg in cls._line_reg_list(",".join(operands))
        if op in ("mtc0", "mtc2", "ctc2", "mthi", "mtlo"):
            return reg in cls._line_reg_list(operands[0])
        if op in ("mflo", "mfhi", "break"):
            return False
        if op in ("mult", "multu"):
            return reg in cls._line_reg_list(",".join(operands))
        if op in ("div", "divu", "rem", "remu"):
            regs = cls._line_reg_list(",".join(operands))
            if len(regs) >= 3 and regs[0] not in ("$zero", "$0"):
                regs = regs[1:]
            return reg in regs

        return reg in cls._line_reg_list(",".join(operands[1:]))

    def _reg_dead_after(self, res, start: int, reg: str) -> bool:
        reg = canonical_reg(reg)
        for j in range(start, len(res)):
            line = strip_comments(res[j]).strip()
            if not line:
                continue
            if line.startswith(".end\t") or line.startswith(".ent\t"):
                return True
            if self._line_reads_reg(line, reg):
                return False
            if self._line_writes_reg(line, reg):
                return True
        return True


    def _rewrite_tail_call_jal_to_j(self, res):
        """LEAD 18 / 18-GENERAL: rewrite a non-returning tail-call `jal`->`j`.

        Retail/ASPSX emits a bare `j TARGET` (no $ra write) for a final void
        tail-call into a `noreturn` callee, where gcc + GNU as always emit
        `jal TARGET`. The delay slot is identical either way; the only byte diff
        is the jal(0x0c)->j(0x08) opcode.

        Two paths pick the sites:

        DERIVED (LEAD 18-GENERAL, primary): a DIRECT `jal SYM` fires when SYM is
        in the source-derived ZERO-ARG noreturn set (`self.noreturn_syms`, from
        config/noreturn_syms.txt) AND its $ra link is DEAD -- scanning forward
        from past its delay slot, $ra is written (by a later jal / `lw $ra`
        restore) before it is ever read, so no return depends on this call's
        link. Every qualifying site is rewritten (a noreturn callee's link is
        dead by definition, so there is no exactly-one restriction here). The
        `noreturn` property is invisible in the assembly; the side-channel file
        supplies it. Only the `jal` line changes; the delay slot is untouched.

        Belt-and-braces (corpus-proven, build/tmp_infra/tailcall_discriminator_report.md,
        66/66): a zero-arg noreturn callee never sets up an argument in its call's
        delay slot, so the derived path additionally SKIPS any site whose delay
        slot writes an argument register ($a0-$a3). This guards the theoretical
        case of a stale/wrong side-channel file (or an independent arg-reg write
        reordered into a void call's slot).

        This pass is now FUNCTION-NAME-BLIND: it keys only on the callee's
        membership in the source-derived side-channel set and on the local
        assembly shape.  The historical by-name paths (`tail_call_j_functions` /
        `tail_call_j_index`, `QUALIFIED_RETURNING_TAILS`,
        `QUALIFIED_LEAD18_ARG_TAILS`, the caller-alias registry, and finally
        `QUALIFIED_NORETURN_TAILS`) were all DELETED on 2026-09-07 (bridge
        burn-down Phase 2/2c), each measured byte-neutral over the landed corpus.
        """
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def is_return_epilogue(i):
            c = C(i)
            return bool(
                re.match(r"^lw\t\$(31|ra),[^,]*\(\$sp\)$", c)
                or re.match(r"^(j|jr)\t\$(31|ra)$", c)
            )

        def ra_link_dead(reals, from_pos):
            # True when, scanning forward from reals[from_pos], $ra is written
            # (overwritten) before it is read -> this jal's return link is unused.
            for p in range(from_pos, len(reals)):
                line = out[reals[p]]
                if self._line_reads_reg(line, "$ra"):
                    return False
                if self._line_writes_reg(line, "$ra"):
                    return True
            return True

        def falls_through_to_call(pos):
            """LEAD 18 PER-TU FIX: True when control provably FALLS THROUGH from
            the `jal` at reals[pos] into ANOTHER call in the SAME basic block.

            WHY (work/queues/maspsx_lead_18_per_tu.md): `noreturn` is a PER-TU
            property, but config/noreturn_syms.<fam>.txt is a per-FAMILY,
            union-only census. A symbol entered from ONE TU's
            `__attribute__((noreturn))` decl then licenses the conversion in
            EVERY TU of the family -- including TUs where retail keeps the `jal`.
            Measured damage: func_80171574 (in the dungeon census since
            2026-07-22 from func_809C9B9C.c alone) and func_80025598 each
            converted an ordinary RETURNING call in a foreign TU, leaving the
            banked func_80BEB814, func_818124A8 and func_818127A8 exactly one
            word off, with no C in those TUs able to avoid it.

            The defect is precisely in what `ra_link_dead` accepts as evidence: a
            LATER `jal` in the same straight-line run overwrites $ra, so the link
            "is dead" -- but that proves only that the compiler had no use for
            this link, NOT that the callee never returns. Falling through to a
            second call means control provably continues past the first one, so
            in THIS TU the callee RETURNS and retail keeps the `jal`.

            Deliberately narrow: only a call reached by fall-through inside the
            SAME basic block (scan stops at the first label) declines. Ordinary
            dead-value/epilogue fall-through still converts -- e.g. the banked
            dungeon func_800A6E68, whose retail bytes DO carry a `move $2,$0`
            after the converted `j func_800AC7CC`. Strictly SUBTRACTIVE: it can
            only decline sites, never create new ones.

            Corpus-checked over every banked TU that calls a census member (280
            TUs across main/town/dungeon): exactly the three victims change, and
            the 5 banked main TUs that deliberately rely on the census WITHOUT a
            local noreturn decl (func_80012DC8, func_80014AFC, func_8001EAE8,
            func_8001EB98, func_8001F7BC) are untouched.
            """
            for p in range(pos + 2, len(reals)):
                # A label between the previous real instruction and this one
                # ends the basic block -> stop looking.
                prev = reals[p - 1]
                if any(
                    C(t).endswith(":") or C(t).startswith("$L")
                    or C(t).startswith("glabel")
                    for t in range(prev + 1, reals[p])
                ):
                    return False
                c = C(reals[p])
                if re.match(r"^jalr?\b", c):
                    return True
            return False

        def writes_arg_reg(k):
            # True when instruction k writes any argument register ($a0-$a3).
            # A zero-arg noreturn callee never sets up an argument in its call's
            # delay slot, so a delay slot that writes $a0-$a3 means the site is
            # not the void-noreturn tail-call we expect -> skip (belt-and-braces).
            line = out[k]
            return any(
                self._line_writes_reg(line, r)
                for r in ("$a0", "$a1", "$a2", "$a3")
            )

        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j  # index of `.end` (or n)

            reals = [k for k in range(i + 1, end) if is_real(k)]

            def direct_jal_target(k):
                m = re.match(r"^jal\t([A-Za-z_.][\w.]*)$", C(k))
                return m.group(1) if m else None

            picks: set[int] = set()

            # DERIVED (LEAD 18-GENERAL) side-channel path: a direct `jal SYM`
            # into a source-declared ZERO-ARG noreturn callee whose $ra link is
            # dead. Fires on ALL qualifying sites.
            if self.noreturn_syms:
                for pos, k in enumerate(reals):
                    target = direct_jal_target(k)
                    if target is None or target not in self.noreturn_syms:
                        continue
                    # Belt-and-braces (corpus 66/66): a zero-arg noreturn call
                    # never parks an argument in its delay slot. If the delay
                    # slot ($ra-restore aside) writes $a0-$a3, the side-channel
                    # file is stale/wrong for this site -> keep the jal.
                    # NOT RELAXED for census members (measured 2026-09-06): 21
                    # arg-slot sites in the matched dungeon corpus are census
                    # noreturn callees, and converting them costs 11 landed rows
                    # 1-2 words. "Does this callee return HERE" is per-TU and the
                    # family census cannot answer it at an arg-carrying site;
                    # receipts in
                    # work/bridge_wave_20260906/maspsx_general_return_delay/.
                    if pos + 1 < len(reals) and writes_arg_reg(reals[pos + 1]):
                        continue
                    # CENSUS-TRUSTED (2026-09-06): the guard below is a
                    # per-callsite SHAPE proxy for the single question "does
                    # this callee return here". When the callee is carried by
                    # the symbol-level noreturn census
                    # (config/noreturn_syms.<fam>.txt, generated from source
                    # `__attribute__((noreturn))` decls and corrected by
                    # config/noreturn_false_members.jsonl), that question is
                    # already answered by evidence stronger than the proxy.
                    census_noreturn = target in self.noreturn_syms
                    # A jal whose post-delay instruction is the return epilogue
                    # (`lw $ra,N($sp)` restore then `j/jr $ra`) is the ordinary
                    # last-call-before-return: its link is read by the return, so
                    # keep the jal -- UNLESS the callee is a census noreturn, in
                    # which case that epilogue is unreachable code and retail
                    # emits `j` (measured on a matched dungeon row; same
                    # receipts directory). Note that
                    # `ra_link_dead` carries NO information at this position
                    # (the `lw $ra,N($sp)` restore trivially "kills" the link),
                    # which is the whole reason this shape guard existed; the
                    # census answers it directly. The residual per-TU risk --
                    # a family census member that genuinely returns in THIS TU
                    # -- is what `falls_through_to_call` below and
                    # config/noreturn_false_members.jsonl exist for.
                    if (pos + 2 < len(reals)
                            and is_return_epilogue(reals[pos + 2])
                            and target not in self.noreturn_epilogue_syms
                            and not census_noreturn):
                        continue
                    if not ra_link_dead(reals, pos + 2):
                        continue  # a real return depends on this link -> keep jal
                    # PER-TU guard: the census is a family-wide union, so a
                    # symbol another TU declared noreturn must not convert a
                    # call THIS TU's gcc treated as returning. Falling through
                    # into a second call in the same basic block proves exactly
                    # that (and is the only thing that made `ra_link_dead` true).
                    if falls_through_to_call(pos):
                        continue
                    picks.add(k)

            for k in picks:
                out[k] = re.sub(
                    r"^(\s*)jal\b", r"\1j", out[k], count=1
                ) + "\t# maspsx: tail-call jal->j (LEAD 18)"

            i = end + 1 if end < n else n
        return out

    def _rewrite_arg_sibcall_jal_to_j(self, res):
        """LEAD 22: rewrite an ARG-carrying sibling-call ``jal CALLEE``->``j CALLEE``.

        Retail/ASPSX emits a bare ``j CALLEE`` (no $ra write) for a tail-position
        call into a *sibcall dispatcher* -- a callee reached only by ``j`` and never
        by ``jal`` across MAIN.BIN, which therefore never returns to its caller --
        where gcc + GNU as always emit ``jal CALLEE`` and (in the branchy case) a
        dead ``j $Lepilogue`` jump. The sibcall reuses the caller's $ra, so control
        returns straight past the caller. This EXTENDS LEAD 18 (zero-arg void
        noreturn callees) to the ARG-carrying dispatchers documented in
        build/tmp_infra/lead22_investigation.md.

        MEMBERSHIP GATE (the decisive fix over the shape-only attempt): a caller's
        LOCAL ``.s`` cannot tell a true sibcall from an ordinary RETURNING tail call
        (``return foo(x)``) -- both compile to byte-identical shapes; the ONLY
        discriminator is the callee's identity. So this pass fires ONLY when the
        callee is in ``self.sibcall_syms`` (config/sibcall_syms.txt, the binary-
        derived ``j``-only set from tools/gen_sibcall_syms.py). A returning callee
        (PopMatrix, func_80040A88, ExitCriticalSection, ...) carries ``jal`` sites in
        the container, is absent from the set, and keeps its ``jal``. Because a set
        member is never ``jal``'d in retail, converting its ``jal``->``j`` can never
        regress a matched function.

        SHAPE TEST (decidable from the ccproc'd stream this pass receives; the whole
        stream is already in explicit-delay-slot form, so every ``jal`` has an
        explicit delay slot at reals[pos+1]). Fire on a DIRECT ``jal SYM`` with
        ``SYM in self.sibcall_syms`` iff:

          SHAPE B: the jal is immediately followed (after its own delay slot) by an
            explicit ``j $Llabel`` whose OWN delay slot is a ``nop`` and whose label
            resolves to the function epilogue (first real instruction at the label is
            ``lw $ra,N($sp)`` / ``j|jr $ra``). The dead ``j $Llabel`` and its nop
            delay slot are DELETED; the jal's own delay slot (arg setup / a reordered
            store) is KEPT as the converted ``j``'s slot.
          SHAPE A: the jal's delay slot is a ``nop`` AND the next real instruction is
            the epilogue. Opcode flip only; nothing is deleted.
          SHAPE C (value-returning / dead-store sibcall): like SHAPE B but the
            trailing ``j $Llabel``'s delay slot is NOT a ``nop`` -- it holds a
            single ALU/store instruction X (a ``return CONST`` value setup, e.g.
            ``li $v0,-1``, or a dead field store) that gcc scheduled into the dead
            epilogue jump. Fires only when the jal's OWN delay slot is a ``nop``
            (nothing to displace). Retail relocates X into the sibcall ``j``'s own
            delay slot; this pass moves X up into that slot, deletes the dead
            ``j $Llabel`` and X's old copy. Corpus-proven: 1192/1618 DUNGEON
            sibcall ``j`` sites carry such a non-nop ALU/store delay fill (only 426
            are nop), so this is the dominant, not the exceptional, retail shape.
            X is restricted to single-machine-instruction ALU ops/stores/small-li
            (never a load, branch, or wide-``li`` macro) so the single delay slot
            is never corrupted. Unlocks func_800931C0 (DUNGEON, ``li $v0,-1``).

        The func_8007BEF0 shape (arg parked in the jal's OWN delay slot, inline
        epilogue, no ``j $Llabel``) never fires two ways: it is not in the set, and
        SHAPE A requires a nop delay while SHAPE B requires a following ``j $Llabel``.
        A mid-function call with a live fall-through and an indirect ``jal $reg`` /
        ``jalr`` never match. Runs AFTER LEAD 18/19; any site those already converted
        is a ``j`` and the ``jal`` match below skips it, so their logic is untouched.
        """
        if not self.sibcall_syms:
            return res
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def is_nop(i):
            return C(i) == "nop"

        def is_epilogue(i):
            c = C(i)
            return bool(
                re.match(r"^lw\t\$(31|ra),[^,]*\(\$sp\)$", c)
                or re.match(r"^(j|jr)\t\$(31|ra)$", c)
            )

        def direct_jal_target(i):
            m = re.match(r"^jal\t([A-Za-z_.][\w.]*)$", C(i))
            return m.group(1) if m else None

        def jump_label_target(i):
            m = re.match(r"^j\t(\$L\w+)$", C(i))
            return m.group(1) if m else None

        # SHAPE C delay-slot fill guard: the ONLY instructions we relocate out of
        # a dead `j $Lepilogue` delay slot into the sibcall `j`'s own delay slot.
        # Restricted to single-machine-instruction ALU ops and stores -- exactly
        # the shapes the retail DUNGEON discriminator scan found in genuine
        # sibcall `j` delay slots (addiu/sh/move(=addu $zero)/sb/sw/ori/lui/addu/
        # sll/subu/sra/or/sltiu/andi/sltu/srl/slt/negu/mult/slti/xori/and) plus a
        # small-immediate `li`. NEVER a load (would need a use-delay), a branch/
        # jump, or a macro that expands to >1 instruction (a wide `li`), any of
        # which would corrupt the single delay slot.
        _single_alu = re.compile(
            r"^(addu|addiu|subu|and|andi|or|ori|xor|xori|nor|sll|srl|sra"
            r"|sllv|srlv|srav|slt|slti|sltu|sltiu|neg|negu|lui|sh|sb|sw"
            r"|swl|swr|mult|multu|mflo|mfhi)\t"
        )

        def is_delay_fill(i):
            if not is_real(i) or is_nop(i):
                return False
            c = C(i)
            if _single_alu.match(c):
                return True
            # small-immediate li only (li reg,BIG expands to lui+ori => 2 insns)
            m = re.match(r"^li\t\$\w+,\s*(-?\d+|0x[0-9a-fA-F]+)$", c)
            if m:
                v = int(m.group(1), 0)
                return -32768 <= v <= 65535
            return False

        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j  # index of `.end` (or n)

            reals = [k for k in range(i + 1, end) if is_real(k)]

            # $Llabel -> index of the first real instruction at/after its definition
            label_first_real: dict[str, int] = {}
            for k in range(i + 1, end):
                lm = re.match(r"^(\$L\w+):", C(k))
                if lm:
                    for kk in range(k + 1, end):
                        if is_real(kk):
                            label_first_real[lm.group(1)] = kk
                            break

            to_flip: set[int] = set()
            to_delete: set[int] = set()
            to_fill: dict[int, str] = {}  # SHAPE C: nop-slot index -> relocated text

            for pos, k in enumerate(reals):
                target = direct_jal_target(k)
                if target is None:
                    continue  # direct symbol targets only (never jal $reg / jalr)
                # MEMBERSHIP GATE: only proven `j`-only sibcall dispatchers.
                if target not in self.sibcall_syms:
                    continue

                # SHAPE B: jal SYM ; <delayA> ; j $Llabel ; nop ; ... $Llabel: <epilogue>
                if pos + 3 < len(reals):
                    lbl = jump_label_target(reals[pos + 2])
                    if lbl is not None and is_nop(reals[pos + 3]):
                        tgt = label_first_real.get(lbl)
                        if tgt is not None and is_epilogue(tgt):
                            to_flip.add(k)
                            to_delete.add(reals[pos + 2])  # the dead j $Llabel
                            to_delete.add(reals[pos + 3])  # its nop delay slot
                            continue

                # SHAPE C: jal SYM ; nop ; j $Llabel ; <X> ; ... $Llabel: <epilogue>
                #   the VALUE-RETURNING / dead-store sibcall. gcc scheduled the
                #   return-value setup (or a dead store) X into the dead
                #   `j $Lepilogue` delay slot; retail instead relocates X into the
                #   sibcall `j`'s OWN delay slot (corpus-proven: 1192/1618 DUNGEON
                #   sibcall `j` sites carry such an ALU/store fill, not a nop).
                #   Only fires when the jal's own delay slot is a nop (nothing to
                #   displace) and X is a single-instruction ALU/store fill.
                if pos + 3 < len(reals):
                    lbl = jump_label_target(reals[pos + 2])
                    if (lbl is not None and is_nop(reals[pos + 1])
                            and is_delay_fill(reals[pos + 3])):
                        tgt = label_first_real.get(lbl)
                        if tgt is not None and is_epilogue(tgt):
                            to_flip.add(k)
                            to_fill[reals[pos + 1]] = C(reals[pos + 3])
                            to_delete.add(reals[pos + 2])  # the dead j $Llabel
                            to_delete.add(reals[pos + 3])  # X, relocated up
                            continue

                # SHAPE A: jal SYM ; nop ; <epilogue>
                if pos + 2 < len(reals):
                    if is_nop(reals[pos + 1]) and is_epilogue(reals[pos + 2]):
                        to_flip.add(k)

            for k in to_flip:
                out[k] = re.sub(
                    r"^(\s*)jal\b", r"\1j", out[k], count=1
                ) + "\t# maspsx: arg sibcall jal->j (LEAD 22)"
            for dest, text in to_fill.items():
                out[dest] = (
                    "\t" + text
                    + "\t# maspsx: LEAD 22 SHAPE C return-value into sibcall delay"
                )
            for k in to_delete:
                out[k] = (
                    "# " + out[k]
                    + "\t# maspsx: LEAD 22 dead j-to-epilogue removed"
                )

            i = end + 1 if end < n else n
        return out

    def _rewrite_marked_shape_d_sibcall(self, res):
        """LEAD 29 SHAPE-D: authenticated live-continuation sibcall pin.

        A C-side marker is required because a live fall-through after a
        sibcall member is intentionally a LEAD-22 negative in the general
        case.  The marker syntax is::

            #maspsx_shape_d_pin CALLER,0xRETAIL_SITE,CALLEE

        The marker must sit in the non-instruction gap immediately before a
        direct ``jal CALLEE`` inside ``.ent CALLER``.  All three fields are
        checked, CALLEE must still be in the binary-derived sibcall set, and
        the call's link must be dead forward.  The only mutation is ``jal`` to
        ``j``; the original delay word and all continuation instructions stay
        byte-for-byte unchanged.  No unmarked/member-only shape is accepted.
        """
        if not self.sibcall_syms:
            return res
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def parse_marker(i):
            raw = out[i].strip()
            m = re.fullmatch(
                r"#\s*" + re.escape(SHAPE_D_PIN_MARKER)
                + r"\s+([A-Za-z_]\w*),\s*"
                + r"(0x[0-9A-Fa-f]+),\s*([A-Za-z_.][\w.]*)",
                raw,
            )
            if not m:
                return None
            site = int(m.group(2), 16)
            if (site & 3) or not (0x80000000 <= site <= 0x8FFFFFFF):
                return None
            return m.group(1), site, m.group(3)

        def marker_before(k, block_start):
            x = k - 1
            while x >= block_start:
                marker = parse_marker(x)
                if marker is not None:
                    return marker
                c = C(x)
                if is_real(x) or c.endswith(":") or c.startswith("$L"):
                    return None
                x -= 1
            return None

        def direct_jal_target(i):
            m = re.match(r"^jal\t([A-Za-z_.][\w.]*)$", C(i))
            return m.group(1) if m else None

        def is_return_epilogue(i):
            c = C(i)
            return bool(
                re.match(r"^lw\t\$(31|ra),[^,]*\(\$sp\)$", c)
                or re.match(r"^(j|jr)\t\$(31|ra)$", c)
            )

        def ra_link_dead(reals, from_pos):
            for p in range(from_pos, len(reals)):
                line = out[reals[p]]
                if self._line_reads_reg(line, "$ra"):
                    return False
                if self._line_writes_reg(line, "$ra"):
                    return True
            return True

        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            caller = m_ent.group(1)
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j
            reals = [k for k in range(i + 1, end) if is_real(k)]
            seen_sites = set()
            picks = set()

            for pos, k in enumerate(reals):
                target = direct_jal_target(k)
                if target is None or target not in self.sibcall_syms:
                    continue
                marker = marker_before(k, i + 1)
                if marker is None:
                    continue
                marked_caller, site, marked_target = marker
                if marked_caller != caller or marked_target != target:
                    continue
                # Synthetic/true caller aliases describe one identity; a
                # repeated retail site is ambiguous regardless of spelling.
                key = (site,)
                if key in seen_sites:
                    # Duplicate site authorization is ambiguous: fail closed
                    # for the whole function rather than picking one call.
                    picks.clear()
                    break
                seen_sites.add(key)
                if pos + 2 >= len(reals):
                    continue
                if is_return_epilogue(reals[pos + 2]):
                    continue
                if not ra_link_dead(reals, pos + 2):
                    continue
                picks.add(k)

            for k in picks:
                out[k] = re.sub(
                    r"^(\s*)jal\b", r"\1j", out[k], count=1
                ) + "\t# maspsx: marked SHAPE-D jal->j"

            i = end + 1 if end < n else n
        return out

    def _rewrite_sidecar_shape_d_sibcall(self, res):
        """Apply explicit SHAPE-D pins from the isolated sidecar manifest.

        This is the compiler-neutral delivery experiment: cc1 emits no marker
        at all.  A caller's manifest rows are ordered by retail site and must
        match the same callee occurrences in that caller's assembly.  The
        pass then applies the exact same dead-$ra/return-epilogue guards as the
        marker path and changes only ``jal`` to ``j``.
        """
        if not self.shape_d_manifest or not self.sibcall_syms:
            return res
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def direct_jal_target(i):
            m = re.match(r"^jal\t([A-Za-z_.][\w.]*)$", C(i))
            return m.group(1) if m else None

        def is_return_epilogue(i):
            c = C(i)
            return bool(
                re.match(r"^lw\t\$(31|ra),[^,]*\(\$sp\)$", c)
                or re.match(r"^(j|jr)\t\$(31|ra)$", c)
            )

        def ra_link_dead(reals, from_pos):
            for p in range(from_pos, len(reals)):
                line = out[reals[p]]
                if self._line_reads_reg(line, "$ra"):
                    return False
                if self._line_writes_reg(line, "$ra"):
                    return True
            return True

        by_caller: dict[str, list[tuple[int, str]]] = {}
        for caller, site, callee in self.shape_d_manifest:
            by_caller.setdefault(caller, []).append((site, callee))

        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            caller = m_ent.group(1)
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j
            caller_rows = [
                by_caller[name]
                for name in (caller,)
                if by_caller.get(name)
            ]
            # Supplying both the true and synthetic spellings is ambiguous;
            # never silently prefer one alias over the other.
            pins = sorted(caller_rows[0]) if len(caller_rows) == 1 else []
            if pins:
                pin_targets = [callee for _, callee in pins]
                candidates = [
                    (pos, k, direct_jal_target(k))
                    for pos, k in enumerate(
                        [k for k in range(i + 1, end) if is_real(k)])
                    if direct_jal_target(k) in pin_targets
                ]
                if (len(candidates) == len(pins)
                        and [target for _, _, target in candidates] == pin_targets
                        and all(target in self.sibcall_syms for target in pin_targets)):
                    reals = [k for k in range(i + 1, end) if is_real(k)]
                    picks: list[tuple[int, int]] = []
                    for pos, (retail_site, _) in enumerate(pins):
                        real_pos, k, _ = candidates[pos]
                        # retail_site is deliberately carried into the output
                        # comment: it is the authenticated manifest identity.
                        if real_pos + 2 >= len(reals):
                            picks = []
                            break
                        if is_return_epilogue(reals[real_pos + 2]):
                            picks = []
                            break
                        if not ra_link_dead(reals, real_pos + 2):
                            picks = []
                            break
                        picks.append((k, retail_site))
                    for k, retail_site in picks:
                        out[k] = re.sub(
                            r"^(\s*)jal\b", r"\1j", out[k], count=1
                        ) + (f"\t# maspsx: sidecar SHAPE-D 0x{retail_site:08X}")
            i = end + 1 if end < n else n
        return out

    def _rewrite_marked_live_sibcall_tail(self, res):
        """Preserve a marker-authorized live continuation after a sibcall tail.

        Retail converts the proven dispatcher call to ``j`` but retains gcc's
        unreachable field-restore continuation.  The dedicated C marker names
        the one-word value to move from the entering branch delay into the new
        tail-j delay.  Membership, block shape, store, epilogue, and predecessor
        value must all agree; otherwise the stream is left unchanged.
        """
        if not self.live_sibcall_tail or not self.sibcall_syms:
            return res
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(c and not c.startswith("#") and not c.startswith(".")
                        and not c.endswith(":") and not c.startswith("glabel"))

        def is_epilogue(i):
            return bool(re.match(r"^lw\t\$(31|ra),[^,]*\(\$sp\)$", C(i)))

        def is_control(i):
            return bool(re.match(r"^(b\w+|j|jr|jal|jalr)\t", C(i)))

        def marked_pin(k, block_start):
            for x in range(k - 1, block_start - 1, -1):
                if is_real(x):
                    break
                if LIVE_SIBCALL_PIN_MARKER in out[x]:
                    m = re.search(
                        LIVE_SIBCALL_PIN_MARKER
                        + r"\s+(\$\w+)\s*,\s*(-?(?:0x[0-9a-fA-F]+|\d+))",
                        out[x],
                    )
                    if m:
                        return m.group(1), int(m.group(2), 0)
            return None

        def one_word_imm(value):
            if value < -0x80000000 or value > 0xFFFFFFFF:
                return False
            bits = value & 0xFFFFFFFF
            signed = bits - 0x100000000 if bits & 0x80000000 else bits
            return (-0x8000 <= signed < 0x8000 or bits <= 0xFFFF
                    or (bits & 0xFFFF) == 0)

        def label_between(lo, hi):
            return any(
                re.match(r"^(?:\$L\w+|[A-Za-z_.][\w.]*)\:$", out[x].strip())
                for x in range(lo + 1, hi + 1)
            )

        def owning_label(k, func_start):
            for x in range(k - 1, func_start, -1):
                c = C(x)
                if re.match(r"^\$L[\w.]+:$", c):
                    return c[:-1]
                if is_control(x):
                    break
            return None

        def predecessor_value(label, reg, imm, func_start, call_i):
            if label is None:
                return None
            expected = f"li\t{reg},{imm}"
            for x in range(func_start + 1, call_i):
                m = re.match(
                    r"^(?:beq|bne|beqz|bnez)\t.*,(\$L[\w.]+)$", C(x)
                )
                if not m or m.group(1) != label:
                    continue
                delay = next(
                    (y for y in range(x + 1, call_i) if is_real(y)), None
                )
                if delay is not None and C(delay) == expected:
                    return delay
            return None

        i = 0
        while i < len(out):
            if not re.match(r"^\.ent\s+\w+$", C(i)):
                i += 1
                continue
            end = i + 1
            while end < len(out) and not re.match(r"^\.end\b", C(end)):
                end += 1
            reals = [k for k in range(i + 1, end) if is_real(k)]
            for pos, k in enumerate(reals):
                call = re.match(r"^jal\t([A-Za-z_.][\w.]*)$", C(k))
                if not call or call.group(1) not in self.sibcall_syms:
                    continue
                if pos + 2 >= len(reals) or C(reals[pos + 1]) != "nop":
                    continue
                pin = marked_pin(k, i + 1)
                if pin is None or not one_word_imm(pin[1]):
                    continue
                first = reals[pos + 2]
                if is_epilogue(first):
                    continue
                saw_store = False
                has_epilogue = False
                for q in range(pos + 2, len(reals)):
                    cur = reals[q]
                    if is_epilogue(cur):
                        has_epilogue = saw_store
                        break
                    if is_control(cur) or label_between(reals[q - 1], cur):
                        break
                    saw_store |= bool(re.match(r"^(sb|sh|sw|swl|swr)\t", C(cur)))
                if not has_epilogue:
                    continue
                moved = predecessor_value(
                    owning_label(k, i), pin[0], pin[1], i, k
                )
                if moved is None:
                    continue
                out[k] = re.sub(r"^(\s*)jal\b", r"\1j", out[k], count=1)
                out[k] += "\t# maspsx: marked live sibcall jal->j"
                out[reals[pos + 1]] = (
                    f"\tli\t{pin[0]},{pin[1]}"
                    "\t# maspsx: marked live sibcall delay value"
                )
                out[moved] = (
                    "\tnop\t# maspsx: live sibcall value moved from entry delay"
                )
            i = end + 1
        return out

    def _rotate_sibcall_v0_into_branch_delay(self, res):
        """LEAD 26: rotate a converted sibcall/noreturn ``j``'s ``$v0``-setup delay
        slot up into the immediately-preceding BACKWARD conditional branch's empty
        (``nop``) delay slot, leaving a ``nop`` in the ``j`` slot.

        Retail/ASPSX carries ``bcond ...,BACK ; move/li $v0,K ; j SYM ; nop`` where
        gcc + current maspsx (LEAD 18/22 SHAPE C) emit
        ``bcond ...,BACK ; nop ; j SYM ; move/li $v0,K`` -- the SHAPE-C relocation
        parks the return-value setup in the converted ``j``'s OWN delay slot; ASPSX
        instead hoists it into the empty branch delay slot (it then also executes on
        the taken back-edge, safe only because ``$v0`` is dead there).

        This pass runs LAST, on the OUTPUT of ``_rewrite_tail_call_jal_to_j`` (LEAD
        18) and ``_rewrite_arg_sibcall_jal_to_j`` (LEAD 22 SHAPE C). Fires only when
        ALL FIVE hold (confirmation: work/maspsx_investigations/branch_jump_slot/
        notes.md + confirm_func_8009B70C/800C7F80_opus_20260708.md; the retail scan
        found 0 counterexamples under the evidence-target + BACKWARD restriction):

          1. the ``j SYM`` was produced by THIS run's own sibcall/noreturn
             conversion -- tracked DIRECTLY by the ``jal->j`` marker the LEAD 18/22
             passes stamp onto the line they rewrote (gcc's input stream never
             contains it); a direct ``j SYM`` only, never ``j $Llabel`` / ``jr``.
          2. its delay slot is a SINGLE ``$v0``-writing move / small-li -- ``move
             $v0,X``, a canonical ``addu``/``or $v0,$zero,X`` (gcc's ``move``
             lowering), or a 16-bit ``li $v0,imm``. NEVER a load, a wide-``li``
             macro, or anything touching memory.
          3. the immediately preceding real instruction is a conditional branch
             whose OWN delay slot is a ``nop`` (i.e. reals: ``bcond ; nop ; j``).
          4. the branch target is BACKWARD (label already emitted in this function).
          5. conservative local liveness: ``$v0`` is DEAD on the taken edge --
             scanning forward from the branch-target label, ``$v0`` is WRITTEN (an
             explicit ``$v0`` def, or clobbered by a ``jal``/``jalr`` return) before
             any read. Anything unclear -- a ``$v0`` read, a non-call control
             transfer (``j``/``jr``/branch), or end-of-function before a write --
             means DO NOT fire.

        Must-not-fire (encoded as unit tests): forward branch (cond 4; main
        func_8001A444 ``li $s0,K`` sites, also cond 2 -- dest is $s0); a filled
        branch delay slot (cond 3; func_8009B70C sites 1/2, func_800C7F80 idx 43); a
        ``jal``-preceded ``j`` (cond 3; func_800C7F80 idx 37); a non-``$v0`` /
        non-move-li ``j`` slot (cond 2); a ``$v0`` READ at the branch target (cond
        5); a ``j`` this run did not convert (cond 1). POSITIVE: func_8009B70C
        site 3 shape (the ``lhu $v0,0($fp)`` back-edge reload proves deadness).
        """
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        # Direct record of "THIS run converted this j": the LEAD 18/22 jal->j
        # passes stamp a `jal->j` comment onto the line they rewrote (never in
        # gcc's input). A direct `j SYM` only -- not `j $Llabel` / `jr`.
        def converted_sibcall_j(i):
            if "jal->j" not in out[i]:
                return False
            return bool(re.match(r"^j\t[A-Za-z_.][\w.]*\b", C(i)))

        def is_cond_branch(i):
            op, operands = self._instruction_operands(out[i])
            return op in branch_mnemonics and bool(operands)

        def branch_label(i):
            _op, operands = self._instruction_operands(out[i])
            return operands[-1] if operands else None

        def is_v0_setup(i):
            # single-instruction $v0 def: move / canonical-move / small-li ONLY
            # (never a load, store, or wide-li macro).
            if not self._line_writes_reg(out[i], "$v0"):
                return False
            op, operands = self._instruction_operands(out[i])
            if op == "move":
                return True
            if op in ("addu", "or") and len(operands) == 3:
                srcs = [
                    canonical_reg(self._line_reg_list(o)[0])
                    for o in operands[1:]
                    if self._line_reg_list(o)
                ]
                return "$zero" in srcs
            if op == "li":
                m = re.match(r"^li\t\$\w+,\s*(-?\d+|0x[0-9a-fA-F]+)$", C(i))
                if m:
                    return -32768 <= int(m.group(1), 0) <= 65535
            return False

        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j

            reals = [k for k in range(i + 1, end) if is_real(k)]
            real_pos = {k: p for p, k in enumerate(reals)}

            # label -> source line index (backward test) and -> position in `reals`
            # of the first real at/after its definition (liveness scan start).
            label_line: dict[str, int] = {}
            label_first_real: dict[str, int] = {}
            for k in range(i + 1, end):
                lm = re.match(r"^(\$L\w+):", C(k))
                if lm:
                    label_line[lm.group(1)] = k
                    for kk in range(k + 1, end):
                        if is_real(kk):
                            label_first_real[lm.group(1)] = real_pos[kk]
                            break

            def v0_dead_at(start_pos):
                # Conservative: from reals[start_pos], $v0 must be WRITTEN before
                # any read for the rotation to be safe on the taken edge.
                q = start_pos
                while 0 <= q < len(reals):
                    line = out[reals[q]]
                    if self._line_reads_reg(line, "$v0"):
                        return False  # live use -> bail
                    op, _ = self._instruction_operands(line)
                    if op in ("jal", "jalr"):
                        # a call clobbers $v0 (return reg); but its delay slot
                        # executes with the OLD $v0, so a $v0 read there is live.
                        if (q + 1 < len(reals)
                                and self._line_reads_reg(out[reals[q + 1]], "$v0")):
                            return False
                        return True  # $v0 redefined by the call -> dead
                    if op in ("j", "jr", "b") or op in branch_mnemonics:
                        return False  # control leaves before a write -> unclear
                    if self._line_writes_reg(line, "$v0"):
                        return True
                    q += 1
                return False  # end-of-function before a write -> bail

            for pos, k in enumerate(reals):
                if not converted_sibcall_j(k):
                    continue
                # cond 2: the j delay slot is a single $v0 move / small-li
                if pos + 1 >= len(reals) or not is_v0_setup(reals[pos + 1]):
                    continue
                # cond 3: reals[pos-2] is a cond branch, reals[pos-1] its nop slot
                if pos < 2:
                    continue
                br = reals[pos - 2]
                slot = reals[pos - 1]
                if not is_cond_branch(br) or C(slot) != "nop":
                    continue
                # If a label sits between the branch delay slot and the `j`,
                # that `j` may be a distinct entry path; rotating would skip the
                # $v0 setup on that path.
                if any(C(x).endswith(":") or C(x).startswith("glabel")
                       for x in range(slot + 1, k)):
                    continue
                # cond 4: branch target BACKWARD (label emitted before the branch)
                lbl = branch_label(br)
                if lbl is None or lbl not in label_line or label_line[lbl] >= br:
                    continue
                # cond 5: $v0 dead on the taken edge
                tgt = label_first_real.get(lbl)
                if tgt is None or not v0_dead_at(tgt):
                    continue

                # ROTATE: $v0 setup up into the branch slot; nop the j slot.
                out[slot] = (
                    "\t" + C(reals[pos + 1])
                    + "\t# maspsx: LEAD 26 rotate $v0 setup into branch delay"
                )
                out[reals[pos + 1]] = (
                    "\tnop\t# maspsx: LEAD 26 nop into sibcall j delay"
                )

            i = end + 1 if end < n else n
        return out

    def _sink_dead_pagebase_into_tail_j_delay(self, res):
        """LEAD 27 (marker-gated): sink a DELIBERATELY-PINNED, consumer-free bare
        PAGE immediate (``lui $R,X`` or a ``li $R,K`` with ``K & 0xffff == 0`` --
        a single-``lui`` upper-half load) that sits IMMEDIATELY before a converted
        noreturn/sibcall tail ``j SYM`` (empty ``nop`` delay slot) DOWN into that
        delay slot (normalised to an explicit ``lui``), leaving retail's shape
        ``j SYM ; lui $R,X`` (net -1 word).

        Retail/ASPSX rematerialises a DEAD page base into the delay slot of a tail
        ``j`` to a void/noreturn callee; the value is dead (the callee returns
        nothing / never returns), a pure cc1 scheduling artifact. gcc-2.8.x shares
        ONE page base across the branch and DCEs the rest, so it never emits that
        dead rematerialisation -- the CLASS-C "gcc DCEs the instruction" wall for a
        page-base fill. The fill is MATERIALISED C-side by the ``ASM_PAGEBASE_PIN``
        page-base pin, which gcc places as a consumer-free immediate BEFORE the
        ``j``; this pass moves it into the ``j``'s otherwise-``nop`` delay slot.

        THE DISCRIMINATOR (why the round-1 revision was vetoed and this is not):
        the bare-page-immediate SHAPE is NOT unique to a pin. gcc materialises a
        natural ``0xNNNN0000`` mask constant (``FIELD(x,0x1C) |= 0x10000000`` ->
        ``lui $v1,0x1000``, low16==0) as the SAME shape, and retail sometimes
        leaves such a natural load STANDALONE with a ``nop`` tail slot -- the exact
        opposite of a sink (landed ``func_81880F28`` is the counter-example). The
        ``jal->j`` marker proves only "this ``j`` is a converted tail", never "this
        ``lui`` is a pin". So this pass fires ONLY when an explicit
        ``#maspsx_pagebase_pin $R`` marker -- emitted by the C macro, unforgeable by
        gcc (see ``PAGEBASE_PIN_MARKER``) -- sits between the immediate and the
        ``j`` and names the immediate's register. A natural mask constant carries
        no such marker and is left untouched.

        Fires only when ALL hold, per ``.ent``/``.end`` function:
          1. the ``j SYM`` carries THIS run's ``jal->j`` marker (LEAD 18/22 stamp;
             gcc's input never has it) -- a direct ``j SYM`` only.
          2. its delay slot (reals[pos+1]) is a ``nop``.
          3. reals[pos-1] is a bare PAGE immediate -- ``lui $R,IMM`` or ``li $R,K``
             with ``(K & 0xffff) == 0`` and ``K != 0`` (single upper load; never a
             wide ``li`` that expands to lui+ori in the slot).
          4. no label sits between reals[pos-1] and the ``j`` (single entry).
          5. THE PIN MARKER: a ``#maspsx_pagebase_pin $R`` comment naming the SAME
             register ``$R`` as the immediate sits (raw) between the immediate and
             the ``j``. This is the guard the round-1 revision lacked.
          6. belt-and-braces liveness (mirrors LEAD 26's cond-5): ``$R`` is a dead
             rematerialisation -- neither the ``j`` nor its delay slot reads it, and
             cond 3/4 already guarantee nothing sits between the immediate and the
             ``j``. Redundant given the marker; enforced in code, not just asserted.

        Fire sites are collected READ-ONLY first, then applied, so a just-sunk
        ``lui`` can never be re-read as another site's preceding immediate (the
        double-sink hazard of the round-1 revision, which mutated ``out`` while
        re-reading it).
        """
        out = list(res)
        firelog = os.environ.get("MASPSX_LEAD27_FIRELOG")

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def converted_tail_j(i):
            if "jal->j" not in out[i]:
                return False
            return bool(re.match(r"^j\t[A-Za-z_.][\w.]*\b", C(i)))

        def bare_page_lui(i):
            """(canonical_reg, normalised `lui $R,UPPER` text) if reals[i] is a
            bare page immediate (a consumer-free single upper-half load), else
            None."""
            c = C(i)
            m = re.match(r"^lui\t(\$\w+),\s*(0x[0-9a-fA-F]+|\d+)$", c)
            if m:
                return canonical_reg(m.group(1)), f"lui\t{m.group(1)},{m.group(2)}"
            m = re.match(r"^li\t(\$\w+),\s*(-?\d+|0x[0-9a-fA-F]+)$", c)
            if m:
                v = int(m.group(2), 0) & 0xFFFFFFFF
                if v != 0 and (v & 0xFFFF) == 0:
                    return (
                        canonical_reg(m.group(1)),
                        f"lui\t{m.group(1)},0x{(v >> 16) & 0xFFFF:x}",
                    )
            return None

        def pin_marker_reg(lo, hi):
            """Canonical register named by a ``#maspsx_pagebase_pin $R`` marker in
            the raw lines out[lo:hi], or None. Only ``ASM_PAGEBASE_PIN`` emits it;
            gcc never does -> this is what separates a genuine pin from a natural
            ``0xNNNN0000`` mask constant."""
            for x in range(lo, hi):
                if PAGEBASE_PIN_MARKER in out[x]:
                    mm = re.search(PAGEBASE_PIN_MARKER + r"\s+(\$\w+)", out[x])
                    if mm:
                        return canonical_reg(mm.group(1))
            return None

        # PHASE 1: collect fire sites read-only (no mutation while scanning ->
        # a just-sunk lui can never be re-consumed as a following site's
        # preceding immediate).
        fires = []  # (lui_idx, slot_idx, lui_text, func_name, j_target)
        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            func_name = m_ent.group(1)
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j

            reals = [k for k in range(i + 1, end) if is_real(k)]
            for pos, k in enumerate(reals):
                if not converted_tail_j(k):
                    continue
                # cond 2: the tail j delay slot is a nop
                if pos + 1 >= len(reals) or C(reals[pos + 1]) != "nop":
                    continue
                # cond 3: the immediately-preceding real is a bare page immediate
                if pos < 1:
                    continue
                parsed = bare_page_lui(reals[pos - 1])
                if parsed is None:
                    continue
                lui_reg, lui_text = parsed
                # cond 4: no label between the immediate and the j (single entry)
                if any(C(x).endswith(":") or C(x).startswith("glabel")
                       for x in range(reals[pos - 1] + 1, k)):
                    continue
                # cond 5 (THE discriminator): a pin marker naming this exact
                # register sits between the immediate and the j. Absent for every
                # natural 0xNNNN0000 mask constant -> that shape is left alone.
                marker_reg = pin_marker_reg(reals[pos - 1] + 1, k)
                if marker_reg is None or marker_reg != lui_reg:
                    continue
                # cond 6 (belt-and-braces liveness): the pinned register is a dead
                # rematerialisation -- neither the tail j nor its delay slot reads
                # it (cond 3/4 already bar any real insn between the imm and the j).
                if any(self._line_reads_reg(out[reals[p]], lui_reg)
                       for p in range(pos, min(pos + 2, len(reals)))):
                    continue
                m_j = re.match(r"^j\t([A-Za-z_.][\w.]*)", C(k))
                j_target = m_j.group(1) if m_j else "?"
                fires.append((reals[pos - 1], reals[pos + 1],
                              lui_text, func_name, j_target))

            i = end + 1 if end < n else n

        # PHASE 2: apply. Each lui is deleted at most once and each slot filled at
        # most once; the disjoint index sets make double-sinking impossible.
        for lui_idx, slot_idx, lui_text, func_name, j_target in fires:
            out[slot_idx] = (
                "\t" + lui_text
                + "\t# maspsx: LEAD 27 dead page-base into tail j delay"
            )
            out[lui_idx] = (
                "# " + out[lui_idx]
                + "\t# maspsx: LEAD 27 page-base relocated into tail j delay"
            )
            if firelog:
                reg_imm = lui_text.split("\t", 1)[1]
                try:
                    with open(firelog, "a") as fh:
                        fh.write(
                            f"{func_name}\tj\t{j_target}\tlui\t{reg_imm}\n"
                        )
                except OSError:
                    pass
        return out

    def _rotate_dead_value_into_tail_j_delay(self, res):
        """LEAD 28 (marker-gated): sink a DELIBERATELY-PINNED dead value into a
        converted noreturn/sibcall tail ``j SYM`` delay slot, reproducing ASPSX's
        schedule (net -1 word -> retail's shape). Two arms share the same marker
        family and discipline:

          ARM A (rotation): the branch delay is already the call's last arg-move.
          ASPSX parks the dead value in the delay and pulls the arg-move UP into an
          earlier load-delay ``nop``; this arm performs that 3-way rotation.

          ARM B (empty-slot sink, "LEAD 28b"): the branch delay is a bare ``nop``
          and gcc parks the pinned dead value STANDALONE before the ``j`` (or, for a
          rematerialised page-base, schedules it to the TOP of the block). There is
          no arg-move to rotate -- this arm simply SINKS the pinned producer down
          into the ``nop`` slot and drops the standalone copy. (LEAD 27 is the
          page-``lui``-specific ancestor of this arm; ARM B generalises it to ANY
          single-dest ALU dead value keyed on the ``#maspsx_tailslot_pin`` marker
          and, unlike LEAD 27, tolerates a non-adjacent producer.)

        Retail/ASPSX parks a DEAD dispatch value (e.g. ``addu $v0,$v0,$a1`` =
        base+index, dead because the sibcall callee ignores ``$v0``) in the delay
        slot of the tail ``j`` and pulls the call's last arg-move UP into an
        earlier load-delay ``nop``. gcc-2.8.x does the opposite: it parks the dead
        value STANDALONE before the ``jal`` and schedules the arg-move into the
        branch delay, wasting the load-delay as a ``nop`` -- one word longer than
        retail. The dead value is materialised C-side by ``ASM_TAILSLOT_PIN``
        (kept live + marked); this pass performs ASPSX's rotation:
          - sink the pinned dead value D into the tail-``j`` delay slot (evicting
            the arg-move M),
          - relocate M up into the nearest preceding load-delay ``nop`` S, when
            that move is byte-legal there,
          - delete the now-redundant standalone D.

        THE DISCRIMINATOR (same discipline as LEAD 27, whose round-1 revision was
        VETOED for shape-only firing): fires ONLY when an explicit
        ``#maspsx_tailslot_pin $R`` marker -- emitted by the ``ASM_TAILSLOT_PIN``
        macro, unforgeable by gcc (see ``TAILSLOT_PIN_MARKER``) -- sits between D
        and the ``j`` and names D's register. A natural arithmetic op before a
        converted tail ``j`` carries no such marker and is left untouched. Every
        condition that fails simply SKIPS the site: the worst case is the
        un-rotated near-miss, NEVER a regression.

        ARM A (rotation) fires only when ALL hold, per ``.ent``/``.end`` function:
          1. reals[k] is a ``j SYM`` carrying THIS run's ``jal->j`` marker (LEAD
             18/22 stamp; gcc input never has it) -- a direct ``j SYM`` only.
          2. its delay slot reals[k+1] is a SIMPLE MOVER M: ``move $Rd,$Rs`` or
             ``addu|or $Rd,$Rs,$zero`` writing an ARGUMENT register ($a0-$a3) and
             reading exactly one non-``$zero`` source. NOT a ``nop`` (the nop-slot
             case is ARM B / LEAD 27).
          3. reals[k-1] is the pinned dead value D: a single-dest ALU op (never a
             load/store/branch/jump/hi-lo/``jal``) writing exactly register $R.
          4. no label between reals[k-1] and the ``j`` (single entry).
          5. THE PIN MARKER: ``#maspsx_tailslot_pin $R`` naming D's register sits
             (raw) between D and the ``j``.
          6. liveness: neither the ``j`` nor M reads $R -> D is a dead
             rematerialisation the callee ignores.
          7. a valid load-delay slot S for M: the NEAREST real ``nop`` before D
             whose preceding real is a LOAD, in the same block (no label between S
             and the ``j``), where relocating M to S is byte-legal --
               a. M's source and dest are not the load's dest (M independent of
                  the load -> a legal load-delay fill),
               b. M's source reg is not written in (S, M) (inputs stable),
               c. M's dest reg is not read in (S, M) (output unobserved until the
                  callee).

        ARM B (empty-slot sink) fires only when ALL hold, per function:
          1. reals[k] is a converted tail ``j SYM`` (as ARM A cond 1).
          2. its delay slot reals[k+1] is a bare ``nop``.
          3. THE PIN MARKER: the NEAREST ``#maspsx_tailslot_pin $R`` above the
             ``j`` within the block (raw scan, stopping at any label/.ent/.end)
             names register $R.
          4. the LAST real writing $R before the ``j`` (the value live in $R at the
             ``j``) is a single-dest ALU dead value D we can legally sink (same
             shape as ARM A cond 3). Its position need NOT be adjacent to the ``j``:
             gcc may schedule a pinned page-base up to the top of the block.
          5. no label between D and the ``j`` (single entry).
          6. liveness: no real from just after D through the delay slot reads $R (D
             is the last writer by cond 4, so the sunk value is exactly the pinned
             one and the callee's dead arg).
        ARM B is exactly LEAD 27's sink generalised off the page-``lui`` shape onto
        the tailslot-pin marker; a bare nop delay with NO marker (a natural dead ALU
        op before a converted tail j) is left untouched.

        Fire sites are collected READ-ONLY first (ARM A: comment D, overwrite S/M;
        ARM B: comment D, overwrite the nop delay), so mutation never perturbs a
        later scan. The ``S`` slot of an ARM-B fire tuple is ``None``.
        """
        out = list(res)
        firelog = os.environ.get("MASPSX_LEAD28_FIRELOG")
        ARG_REGS = {"$a0", "$a1", "$a2", "$a3"}
        ZERO = {"$zero", "$0"}

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def converted_tail_j(i):
            if "jal->j" not in out[i]:
                return False
            return bool(re.match(r"^j\t[A-Za-z_.][\w.]*\b", C(i)))

        def simple_mover(i):
            """(canonical_dest, canonical_src, verbatim_text) if reals[i] is a
            reg->reg copy into an argument register reading one non-$zero source,
            else None. Text is preserved VERBATIM so the relocated move assembles
            to the exact retail bytes."""
            c = C(i)
            m = re.match(r"^(move|addu|or)\t(\$\w+),\s*(\$\w+)(?:,\s*(\$\w+))?$", c)
            if not m:
                return None
            dst = canonical_reg(m.group(2))
            srcs = [canonical_reg(g) for g in (m.group(3), m.group(4)) if g]
            nonzero = [r for r in srcs if r not in ZERO]
            if m.group(1) == "move":
                if len(srcs) != 1 or len(nonzero) != 1:
                    return None
            else:  # addu/or: exactly one non-$zero source -> a copy
                if len(srcs) != 2 or len(nonzero) != 1:
                    return None
            src = nonzero[0]
            if dst not in ARG_REGS or dst == src:
                return None
            return dst, src, "\t" + c

        def dead_value(i):
            """(canonical_reg, verbatim_text) if reals[i] is a single-dest ALU op
            (no memory/branch/jump/hi-lo) writing exactly one non-$zero GPR."""
            c = C(i)
            op, operands = self._instruction_operands(c)
            if op is None or not operands:
                return None
            if (op in load_mnemonics or op in store_mnemonics
                    or op in branch_mnemonics
                    or op in ("j", "jr", "jal", "jalr", "nop", "break",
                              "mult", "multu", "div", "divu", "rem", "remu",
                              "mflo", "mfhi", "mthi", "mtlo",
                              "mtc0", "mtc2", "ctc2")):
                return None
            first = self._line_reg_list(operands[0])
            if len(first) != 1 or first[0] in ZERO:
                return None
            return first[0], "\t" + c

        def pin_marker_reg(lo, hi):
            """Canonical register named by a ``#maspsx_tailslot_pin $R`` marker in
            the raw lines out[lo:hi], or None. Only ``ASM_TAILSLOT_PIN`` emits it;
            gcc never does."""
            for x in range(lo, hi):
                if TAILSLOT_PIN_MARKER in out[x]:
                    mm = re.search(TAILSLOT_PIN_MARKER + r"\s+(\$\w+)", out[x])
                    if mm:
                        return canonical_reg(mm.group(1))
            return None

        def load_dest(i):
            op, operands = self._instruction_operands(C(i))
            if op not in load_mnemonics or not operands:
                return None
            regs = self._line_reg_list(operands[0])
            return regs[0] if regs else None

        def empty_slot_sink(reals, pos, k, block_start, func_name):
            """ARM B (LEAD 28b, empty-slot). Return a fire tuple
            ``(producer_idx, nop_delay_idx, None, producer_text, "", func, target)``
            when a marker-pinned dead value produced before the converted tail
            ``j`` (reals[k]) -- whose delay slot reals[pos+1] is a bare ``nop`` --
            can be legally sunk into that slot, else ``None`` (the ``None`` in the
            ``S`` slot marks the empty-slot variant for PHASE 2).

            Unlike ARM A the producer need NOT be immediately before the ``j``
            (gcc may schedule a rematerialised page-base to the TOP of the block):
            this keys on the unforgeable ``#maspsx_tailslot_pin $R`` marker, takes
            the LAST writer of $R before the ``j`` (which must itself be a clean
            single-dest ALU dead value), and verifies $R is dead from that writer
            through the delay slot. A missing marker / non-ALU last writer / a live
            $R all simply decline -- never a regression."""
            # cond 3 (THE discriminator): the nearest tailslot pin marker above the
            # j, within this block (stop at any label / .ent / .end).
            mreg = None
            xr = k - 1
            while xr > block_start:
                cc = C(xr)
                if (cc.endswith(":") or cc.startswith("glabel")
                        or re.match(r"^\.(ent|end)\b", cc)):
                    break
                if TAILSLOT_PIN_MARKER in out[xr]:
                    mm = re.search(TAILSLOT_PIN_MARKER + r"\s+(\$\w+)", out[xr])
                    mreg = canonical_reg(mm.group(1)) if mm else None
                    break
                xr -= 1
            if mreg is None:
                return None
            # cond 4: the LAST real writing $R before the j -- the value live in $R
            # at the j -- must be a single-dest ALU dead value we can legally sink.
            p = None
            for q in range(pos - 1, -1, -1):
                if self._line_writes_reg(out[reals[q]], mreg):
                    p = q
                    break
            if p is None:
                return None
            dv = dead_value(reals[p])
            if dv is None or dv[0] != mreg:
                return None
            _d_reg, d_text = dv
            # A delay slot holds exactly ONE machine word. Real single-dest ALU ops
            # are one word, but the ``li``/``la`` MACROS can expand to ``lui``+``ori``
            # (two words) -- never sink one of those (guards a future pin of a
            # split constant, exactly as LEAD 27's ``bare_page_lui`` does).
            p_op, p_ops = self._instruction_operands(C(reals[p]))
            if p_op == "la":
                return None
            if p_op == "li":
                try:
                    v = int(p_ops[1], 0) & 0xFFFFFFFF
                except (ValueError, IndexError):
                    return None
                sv = v - 0x100000000 if v >= 0x80000000 else v
                single_word = (-0x8000 <= sv < 0x8000     # addiu $R,$zero,imm
                               or 0 <= v <= 0xFFFF          # ori   $R,$zero,imm
                               or (v & 0xFFFF) == 0)        # lui   $R,upper
                if not single_word:
                    return None
            # cond 5: no label between the producer and the j (single entry).
            if any(C(x).endswith(":") or C(x).startswith("glabel")
                   for x in range(reals[p] + 1, k)):
                return None
            # cond 6 (liveness): $R is dead -- no real from just after the producer
            # through the delay slot reads it (the producer is the last writer by
            # cond 4, so the sunk value is exactly the pinned one).
            if any(self._line_reads_reg(out[reals[r]], mreg)
                   for r in range(p + 1, pos + 2)):
                return None
            m_j = re.match(r"^j\t([A-Za-z_.][\w.]*)", C(k))
            j_target = m_j.group(1) if m_j else "?"
            # STALE LOAD-DELAY NOP CLEANUP (LEAD 28c, 2026-07-24; blocking
            # instance func_800C1D6C town, family func_800971DC): when D is a
            # load-user, gcc parks a hazard ``nop`` between the load and D.
            # After the sink, D executes in the ``j`` delay slot -- the ``j``
            # itself now provides the one intervening cycle (retail's own
            # ``load; j; D-slot`` shape) and the standalone nop is dead weight
            # retail never emits. Delete it ONLY under the narrowest conditions,
            # all inside this already-marker-gated ARM B fire (never shape-only):
            #   a. D is the real immediately before the ``j`` (p == pos-1), so
            #      after commenting D the load lands directly against the ``j``
            #      and NOTHING else shifts into the load's shadow;
            #   b. the real immediately before D is a bare ``nop``;
            #   c. the real before THAT is a GPR load whose dest D reads (the
            #      nop is provably D's hazard gap, not some other fence);
            #   d. no label between the load and D (straight line).
            # Post-deletion hazard proof: load @t, j @t+1, D @t+2 -- one
            # intervening instruction, exactly the legal MIPS-I load shadow.
            stale_idx = None
            if p == pos - 1 and p >= 2:
                nop_i, load_i = reals[p - 1], reals[p - 2]
                l_op, l_ops = self._instruction_operands(C(load_i))
                if (C(nop_i) == "nop" and l_op in load_mnemonics and l_ops):
                    l_dest = canonical_reg(l_ops[0])
                    if (self._line_reads_reg(out[reals[p]], l_dest)
                            and not any(C(x).endswith(":") or C(x).startswith("glabel")
                                        for x in range(load_i + 1, reals[p]))):
                        stale_idx = nop_i
            return (reals[p], reals[pos + 1], None, d_text, "", func_name,
                    j_target, stale_idx)

        # PHASE 1: collect fire sites read-only.
        fires = []  # (D_idx, M_idx, S_idx, D_text, M_text, func, target)
        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            func_name = m_ent.group(1)
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j

            reals = [k for k in range(i + 1, end) if is_real(k)]
            for pos, k in enumerate(reals):
                if not converted_tail_j(k):
                    continue
                if pos < 1 or pos + 1 >= len(reals):
                    continue
                # ARM B (empty-slot sink): a bare `nop` branch delay -> there is no
                # arg-move to rotate; sink the marker-pinned producer into the nop.
                if C(reals[pos + 1]) == "nop":
                    site = empty_slot_sink(reals, pos, k, i, func_name)
                    if site is not None:
                        fires.append(site)
                    continue
                # ARM A (rotation) cond 2: the branch delay is a simple arg-move.
                mv = simple_mover(reals[pos + 1])
                if mv is None:
                    continue
                m_dst, m_src, m_text = mv
                # cond 3: the immediately-preceding real is the dead value
                dv = dead_value(reals[pos - 1])
                if dv is None:
                    continue
                d_reg, d_text = dv
                # cond 4: no label between D and the j
                if any(C(x).endswith(":") or C(x).startswith("glabel")
                       for x in range(reals[pos - 1] + 1, k)):
                    continue
                # cond 5 (THE discriminator): a pin marker names D's register.
                marker_reg = pin_marker_reg(reals[pos - 1] + 1, k)
                if marker_reg is None or marker_reg != d_reg:
                    continue
                # cond 6: D's register is dead -- neither the j nor M reads it.
                if (self._line_reads_reg(out[k], d_reg)
                        or self._line_reads_reg(out[reals[pos + 1]], d_reg)):
                    continue
                # cond 7: nearest preceding load-delay nop S where M relocates
                # legally (M independent of the load; M's inputs stable; M's dest
                # unobserved until the callee).
                S = None
                for q in range(pos - 2, 0, -1):
                    if C(reals[q]) != "nop":
                        continue
                    ldst = load_dest(reals[q - 1])
                    if ldst is None:
                        continue
                    # 7a: M independent of the load (source and dest != load dest)
                    if m_src == ldst or m_dst == ldst:
                        continue
                    # single-entry: no label between S and the j
                    if any(C(x).endswith(":") or C(x).startswith("glabel")
                           for x in range(reals[q] + 1, k)):
                        break
                    gap = range(reals[q] + 1, reals[pos + 1])
                    # 7b: M's source unchanged between S and M's original slot
                    if any(self._line_writes_reg(out[x], m_src) for x in gap):
                        continue
                    # 7c: M's dest unread between S and M's original slot
                    if any(self._line_reads_reg(out[x], m_dst) for x in gap):
                        continue
                    S = reals[q]
                    break
                if S is None:
                    continue
                m_j = re.match(r"^j\t([A-Za-z_.][\w.]*)", C(k))
                j_target = m_j.group(1) if m_j else "?"
                fires.append((reals[pos - 1], reals[pos + 1], S,
                              d_text, m_text, func_name, j_target, None))

            i = end + 1 if end < n else n

        # PHASE 2: apply.
        #   ARM A: S (load-delay nop) <- M; M's slot (branch delay) <- D.
        #   ARM B (s_idx is None): the nop branch delay <- D directly.
        # Either way the standalone D is commented out (net -1 word -> retail).
        for d_idx, m_idx, s_idx, d_text, m_text, func_name, j_target, stale_idx in fires:
            if s_idx is None:
                out[m_idx] = (d_text
                              + "\t# maspsx: LEAD 28 dead value into empty tail j delay")
                out[d_idx] = ("# " + out[d_idx]
                              + "\t# maspsx: LEAD 28 dead value sunk into empty tail j delay")
                if stale_idx is not None:
                    out[stale_idx] = ("# " + out[stale_idx]
                                      + "\t# maspsx: LEAD 28c stale load-delay nop"
                                        " (j covers the shadow after sink)")
            else:
                out[s_idx] = m_text + "\t# maspsx: LEAD 28 arg-move into load-delay"
                out[m_idx] = d_text + "\t# maspsx: LEAD 28 dead value into tail j delay"
                out[d_idx] = ("# " + out[d_idx]
                              + "\t# maspsx: LEAD 28 dead value relocated into tail j delay")
            if firelog:
                try:
                    with open(firelog, "a") as fh:
                        fh.write(f"{func_name}\tj\t{j_target}\t{d_text.strip()}\n")
                except OSError:
                    pass
        return out

    def _rotate_marked_store_into_jal_delay(self, res):
        """LEAD 30: rotate a marker-pinned STORE down into a REAL ``jal``'s delay
        slot, lifting the instruction gcc parked there up in front of the call.

        Blocking instance: func_800463EC (MAIN, 2.7.2-cdk -O2, 294 words, aligned
        {indels 2, subs 1}).  Retail holds ``sh $v1,0x8c($s2)`` -- the store of a
        value loaded well before the call -- pending until the ``RotAverage4``
        delay slot, AFTER all six outgoing stack arguments have been written, and
        keeps the last stack-argument store ``sw $v0,0x24($sp)`` in front of the
        ``jal``.  gcc's dbr pass does the opposite at EVERY pinned compiler
        (2.7.2/2.7.2-cdk/2.8.0/2.8.1 and genuine PsyQ 4.4 cc1): it emits the store
        as soon as its input is ready and fills the delay slot with the last
        argument store.  Same instruction multiset, same registers, same length --
        one 2-way rotation apart.

        THIS IS NOT AN ASPSX EMULATION FIX AND MUST NOT BE SHAPE-GATED.  The
        assembler differential was MEASURED on this exact gcc ``.s``: genuine
        ASPSX 2.67 / 2.77 / 2.79 / 2.86 all assemble it to bytes identical to our
        maspsx (ASPSX 2.56 cannot parse the %hi/%lo this cc1 emits, so it is N/A),
        i.e. no shipped ASPSX performs this rotation.  It is a schedule ASPSX's
        own scheduler produced from DIFFERENT cc1 input, so the only sound form is
        an explicit, C-authored opt-in.  Accordingly the pass fires ONLY on an
        unforgeable ``#maspsx_jaldelay_pin $R`` comment -- emitted solely by the
        ``ASM_JALDELAY_PIN`` macro in include/common.h, a token gcc never produces
        (see ``JALDELAY_PIN_MARKER``).  Unmarked code is never touched, so the set
        of census candidates this pass can move is EMPTY.

        Relation to LEAD 27/28: those sink a DEAD value into a delay slot maspsx
        itself created by converting a tail ``jal`` to ``j`` (net -1 word).  This
        one leaves a real call intact, moves a LIVE store (its memory effect is
        observed by the callee -- it writes the GTE/scratchpad operand the call
        consumes), and is LENGTH-PRESERVING: nothing is deleted, two lines swap.

        Fires only when ALL hold, per ``.ent``/``.end`` function:
          1. reals[k] is a real direct call ``jal SYM`` (never ``jalr``, never a
             LEAD 18/22 ``jal->j`` conversion -- those are the other passes' turf).
          2. its delay slot reals[k+1] is M: a single-word non-branch real that is
             NOT a ``nop`` (a bare nop delay would make this a length-CHANGING
             sink, which is LEAD 28 ARM B's shape, not this one), whose memory
             form -- if it touches memory -- is a numeric ``off($base)`` in signed
             16-bit range (so it cannot be an ``$at``-expanding 2-word access), and
             which neither reads nor writes ``$ra`` (M crosses the ``jal``, the one
             instruction that redefines ``$ra``).
          3. THE DISCRIMINATOR: the NEAREST ``#maspsx_jaldelay_pin $R`` marker
             above the ``jal`` inside the block (raw scan, stopping at any label /
             ``.ent`` / ``.end``) names register $R.
          4. D = the LAST store of $R before the ``jal``: a store whose SOURCE is
             exactly $R through a numeric ``off($base)`` in signed 16-bit range.
             Position is not fixed relative to the marker -- gcc schedules the
             pinned value's liveness tail wherever it likes, and on the blocking
             instance the marker lands ABOVE D -- so D is found by last-writer
             search, exactly as LEAD 28 ARM B finds its producer.
          5. no label between D and the ``jal`` (single entry, straight line).
          6. no ``jal``/``jalr``/``j``/branch strictly between D and the ``jal``
             (the marker must govern exactly one call; a second call in the window
             would make "the next jal" ambiguous and could move D across a call
             that observes it), and none between the marker and the ``jal``.
          7. D moves DOWN past everything in (D, jal):
             a. nothing there writes D's source $R or D's base $base (D's inputs
                are unchanged at the new position),
             b. nothing there LOADS from memory (never reorder a store past a
                load -- the one direction that can change a program's meaning),
             c. every STORE there uses a base register different from $base (no
                same-base aliasing with D),
             d. $R and $base are not ``$ra`` (the ``jal`` D now follows redefines
                it).
          8. M moves UP past the ``jal`` and therefore also past D (their relative
             order inverts):
             a. M does not write $R or $base (D's inputs still stable),
             b. if M touches memory, its base register differs from $base.

        Every condition that fails simply SKIPS the site; the worst case is the
        un-rotated near-miss, never a regression.  Fire sites are collected
        READ-ONLY first so mutation cannot perturb a later scan.
        """
        out = list(res)
        firelog = os.environ.get("MASPSX_LEAD30_FIRELOG")
        RA = {"$ra", "$31"}

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def is_call_jal(i):
            """A real direct ``jal SYM``.  A LEAD 18/22 conversion is already a
            ``j`` by the time this pass runs, so matching ``jal`` alone excludes
            it; ``jalr`` (indirect) is excluded by the symbol form."""
            return bool(re.match(r"^jal\t[A-Za-z_.][\w.]*$", C(i)))

        def mem_base(operand):
            """(base_reg, offset) for a numeric ``off($base)`` operand whose
            displacement fits the 16-bit field GNU as encodes without an ``$at``
            expansion, else None (symbol/`%lo` forms decline: no retail witness,
            and they can assemble to two words)."""
            m = re.match(r"^(-?(?:0[xX])?[0-9a-fA-F]+)\((\$\w+)\)$", operand)
            if not m:
                return None
            try:
                off = int(m.group(1), 0)
            except ValueError:
                return None
            if not -0x8000 <= off < 0x8000:
                return None
            return canonical_reg(m.group(2)), off

        def pinned_store(i, reg):
            """(base_reg, verbatim_text) if reals[i] is a one-word store whose
            SOURCE register is exactly ``reg``.  Text is preserved VERBATIM so the
            relocated store assembles to the exact retail bytes."""
            c = C(i)
            op, operands = self._instruction_operands(c)
            if op not in store_mnemonics or len(operands) != 2:
                return None
            src = self._line_reg_list(operands[0])
            if len(src) != 1 or src[0] != reg:
                return None
            bo = mem_base(operands[1])
            if bo is None:
                return None
            return bo[0], "\t" + c

        def delay_filler(i):
            """(verbatim_text, mem_base_reg_or_None, is_load) if reals[i] is a
            single-word non-branch real usable as the rotation's M, else None."""
            c = C(i)
            op, operands = self._instruction_operands(c)
            if op is None or c == "nop":
                return None
            if (op in branch_mnemonics or op in jump_mnemonics
                    or op in unaligned_load_mnemonics
                    or op in unaligned_store_mnemonics
                    or op in ("jr", "jalr", "b", "break", "la", "li", "nop",
                              "div", "divu", "rem", "remu")):
                # ``la``/``li`` are macros (up to two words); div/rem expand with
                # a zero-divisor break; branches/jumps cannot sit in a delay slot.
                return None
            base = None
            if op in load_mnemonics or op in store_mnemonics:
                if len(operands) != 2:
                    return None
                bo = mem_base(operands[1])
                if bo is None:
                    return None
                base = bo[0]
            for r in RA:
                if self._line_reads_reg(c, r) or self._line_writes_reg(c, r):
                    return None
            return "\t" + c, base, op in load_mnemonics

        def marker_reg_above(k, block_start):
            """Canonical register named by the NEAREST ``#maspsx_jaldelay_pin $R``
            above out[k] within the block, or None.  Only ``ASM_JALDELAY_PIN``
            emits this token; gcc never does."""
            x = k - 1
            while x > block_start:
                c = C(x)
                if (c.endswith(":") or c.startswith("glabel")
                        or re.match(r"^\.(ent|end)\b", c)):
                    return None, x
                if JALDELAY_PIN_MARKER in out[x]:
                    mm = re.search(JALDELAY_PIN_MARKER + r"\s+(\$\w+)", out[x])
                    return (canonical_reg(mm.group(1)) if mm else None), x
                x -= 1
            return None, block_start

        def is_control_flow(i):
            op, _ = self._instruction_operands(C(i))
            return op in branch_mnemonics or op in jump_mnemonics or op in (
                "jr", "jalr", "b", "bal")

        # PHASE 1: collect fire sites read-only.
        fires = []  # (d_idx, m_idx, d_text, m_text, func_name, target)
        i = 0
        n = len(out)
        while i < n:
            m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
            if not m_ent:
                i += 1
                continue
            func_name = m_ent.group(1)
            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            end = j

            reals = [k for k in range(i + 1, end) if is_real(k)]
            for pos, k in enumerate(reals):
                if not is_call_jal(k):
                    continue
                if pos < 1 or pos + 1 >= len(reals):
                    continue
                # cond 3 (THE discriminator).
                mreg, marker_idx = marker_reg_above(k, i)
                if mreg is None:
                    continue
                # cond 2: the delay slot holds a rotatable single-word filler.
                fill = delay_filler(reals[pos + 1])
                if fill is None:
                    continue
                m_text, m_base, _m_is_load = fill
                # cond 4: D is the LAST store of $R before the jal.
                p = None
                for q in range(pos - 1, -1, -1):
                    st = pinned_store(reals[q], mreg)
                    if st is not None:
                        p = q
                        d_base, d_text = st
                        break
                    # a plain redefinition of $R before any store of it means the
                    # pinned value never reached memory in this window: decline.
                    if self._line_writes_reg(out[reals[q]], mreg):
                        break
                if p is None:
                    continue
                # cond 7d / 2: neither end of the rotation may involve $ra.
                if mreg in RA or d_base in RA:
                    continue
                # cond 5: no label between D and the jal (single entry).
                if any(C(x).endswith(":") or C(x).startswith("glabel")
                       for x in range(reals[p] + 1, k)):
                    continue
                # cond 6: exactly one call governed -- no control flow between D
                # (or the marker, whichever is earlier) and the jal.
                lo = min(reals[p], marker_idx)
                if any(is_control_flow(x) for x in range(lo, k) if is_real(x)):
                    continue
                # cond 7: D crosses everything in (D, jal) downwards.
                span = [reals[r] for r in range(p + 1, pos)]
                bad = False
                for x in span:
                    cx = C(x)
                    if (self._line_writes_reg(out[x], mreg)
                            or self._line_writes_reg(out[x], d_base)):
                        bad = True
                        break
                    op_x, ops_x = self._instruction_operands(cx)
                    if op_x in load_mnemonics or op_x in unaligned_load_mnemonics:
                        bad = True                      # 7b: never past a load
                        break
                    if op_x in store_mnemonics or op_x in unaligned_store_mnemonics:
                        bo = mem_base(ops_x[1]) if len(ops_x) == 2 else None
                        if bo is None or bo[0] == d_base:
                            bad = True                  # 7c: same-base aliasing
                            break
                if bad:
                    continue
                # cond 8: M crosses the jal (and hence D) upwards.
                if (self._line_writes_reg(out[reals[pos + 1]], mreg)
                        or self._line_writes_reg(out[reals[pos + 1]], d_base)):
                    continue
                if m_base is not None and m_base == d_base:
                    continue
                # cond 9: the window (D, jal) carries no real ``nop``.  Every insn
                # in it shifts up by one; a nop there is a hazard filler whose
                # shadow would move with it, and re-proving its coverage is not
                # worth it when no retail witness needs it.
                if any(C(reals[r]) == "nop" for r in range(p + 1, pos)):
                    continue
                # The rotation window: D's slot through the last real before the
                # ``jal``.  Texts are snapshotted here (PHASE 1 is read-only) so a
                # later site's scan can never see a half-applied rotation.
                window = [reals[r] for r in range(p, pos)]
                shifted = [("\t" + C(x)) for x in window[1:]] + [m_text]
                # cond 10: the real ABOVE D keeps its load shadow.  D leaving pulls
                # ``shifted[0]`` into D's slot; if D was filling a load-delay for
                # the preceding load, the replacement must not read that load's
                # destination.  (Loads INSIDE the window are already excluded by
                # 7b, so the load immediately above D is the only one at risk.)
                if p >= 1:
                    prev_op, prev_ops = self._instruction_operands(C(reals[p - 1]))
                    if prev_op in load_mnemonics and prev_ops:
                        l_regs = self._line_reg_list(prev_ops[0])
                        if l_regs and self._line_reads_reg(shifted[0], l_regs[0]):
                            continue
                m_j = re.match(r"^jal\t([A-Za-z_.][\w.]*)", C(k))
                fires.append((window, shifted, reals[pos + 1], d_text,
                              func_name, m_j.group(1) if m_j else "?"))

            i = end + 1 if end < n else n

        # PHASE 2: apply.  A ROTATION, length-preserving by construction: D leaves
        # the window, every real between D and the ``jal`` shifts up one slot, the
        # displaced delay filler M lands in the freed slot immediately before the
        # ``jal``, and the delay slot becomes D.  (An in-place D<->M swap would be
        # wrong twice over: it puts M at D's index, where M's inputs are not yet
        # the ones it must store, and it does not reproduce retail's word order.)
        for window, shifted, delay_idx, d_text, func_name, target in fires:
            for slot, text in zip(window, shifted):
                out[slot] = text
            out[window[-1]] += "\t# maspsx: LEAD 30 jal-delay filler lifted before the call"
            out[delay_idx] = d_text + "\t# maspsx: LEAD 30 pinned store into jal delay"
            if firelog:
                try:
                    with open(firelog, "a") as fh:
                        fh.write(f"{func_name}\tjal\t{target}\t{d_text.strip()}\n")
                except OSError:
                    pass
        return out

    def _elide_ra_only_frame_for_noreturn_tail(self, res):
        """LEAD 19 (CLASS-A): elide the whole stack frame of a single-call
        noreturn-tail function whose frame exists ONLY to save $ra for that call.

        Retail/ASPSX emits NO prologue and NO epilogue for a function whose sole
        reason to build a frame is to preserve $ra across a single non-returning
        tail call: once that call never returns, the saved $ra is dead and the
        frame is pure overhead. gcc always builds the frame; retail elides it and
        ends the function at a bare `jr $ra`/nop. This pass reproduces that.

        Runs immediately AFTER _rewrite_tail_call_jal_to_j, so the noreturn tail
        call has usually already been rewritten to `j SYM` (LEAD 18). The elision
        DECISION is made independently of that opcode rewrite: the single call is
        recognised whether it survives as the rewritten `j SYM` or the original
        `jal SYM` (either way SYM must be in the noreturn side-channel). Class A
        is LEAD 18 EXTENDED, so a still-`jal` tail (a shape the jal->j pass left
        alone because it sat directly before the epilogue) is completed to `j`
        here once the frame goes.

        FIRING CONDITION (all decidable from the gcc-emitted `.s` directives plus
        the noreturn side-channel; census-verified zero-counterexample across all
        521 MAIN.BIN functions -- build/tmp_infra/lead19_investigation.md):

          1. `.mask 0x80000000,*` (the ONLY saved GPR is $ra) AND
             `.fmask 0x00000000,0` (no callee-saved FPRs).
          2. `.frame ...` with `vars= 0` (no local stack slots).
          3. AT LEAST ONE call, and EVERY call is a DIRECT `jal`/`j` to a symbol
             in `self.noreturn_syms` OR `self.sibcall_syms`. No indirect call, no
             direct call to a non-member (that would be a live return link).
          4. The only $sp-relative memory accesses are the `sw $ra,K($sp)` save
             and the `lw $ra,K($sp)` restore (same K); the only $sp arithmetic is
             the frame alloc (`subu|addiu $sp,$sp,-N`) and the matching dealloc
             (`addu|addiu $sp,$sp,N`) -- PLUS, per LEAD 23, incoming caller-arg
             LOADS at offsets N+16, N+20, ... . Any other $sp use => not class A.

        LEAD 23 EXTENSION: an $ra-only frame around an ARG-carrying tail sibcall
        (confirmed on town func_800CF814, which tail-dispatches the same sibcall
        member twice). The elision (a) accepts sibcall-set members as tail targets
        and multiple such tail calls, and (b) tolerates incoming caller-argument
        stack loads at N+16, N+20, ... , rebasing each by -N (`lw a1,40($sp)` ->
        `lw a1,16($sp)`) as the removed frame no longer sits under them. Anything
        that points into the removed frame [0,N) or cannot be classified as a
        recognised caller-arg load aborts the whole elision (unclear => don't fire).

        TRANSFORM: comment out the prologue (alloc + ra-save) and the epilogue
        frame-teardown (ra-restore + dealloc); rewrite the tail `jal`->`j` if the
        jal->j pass had not already; leave the terminal `jr $ra`/nop.

        PER-TU CONTROL: ``retain_tail_frame=N`` replaces the removed alloc and
        dealloc with an N-byte envelope while still deleting the dead ra save and
        restore. This is evidence-only for retail's partial-frame dialect; zero
        retains the established whole-frame-elision behavior.

        Belt-and-braces: after building the elided function, ABORT the elision
        (leave the whole function untouched) if any remaining instruction still
        references $sp, or references $ra other than a final `jr $ra`/`j $ra`
        return path, or if a second call of any kind (`jal`/`jalr`) survives --
        i.e. the rule fired where it should not.
        """
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def is_real_line(line):
            c = strip_comments(line).strip()
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        SAVE = re.compile(r"^sw\t\$(?:31|ra),(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)$")
        RESTORE = re.compile(r"^lw\t\$(?:31|ra),(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)$")
        RETURN = re.compile(r"^(?:j|jr)\t\$(?:31|ra)$")
        JAL_SYM = re.compile(r"^jal\t([A-Za-z_.][\w.]*)$")
        J_SYM = re.compile(r"^j\t([A-Za-z_.][\w.]*)$")
        IND_CALL = re.compile(r"^(?:jalr\b|jal\t\$)")
        SP_ADJUST = re.compile(
            r"^(subu|addu|addiu)\t\$sp,\$sp,(-?(?:0x[0-9A-Fa-f]+|\d+))$"
        )

        def sp_adjust(c):
            m = SP_ADJUST.match(c)
            if not m:
                return None
            imm = int(m.group(2), 0)
            return -imm if m.group(1) == "subu" else imm

        # LEAD 23: an $sp-based memory op `<mnem>\t$reg,OFF($sp)`. Used to
        # classify the residual $sp uses (after the frame plumbing) as incoming
        # caller-argument LOADS at N+16, N+20, ... -- the only extra $sp use an
        # $ra-only-frame elision tolerates.
        MEM_SP = re.compile(
            r"^(\w+)\t\$\w+,(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)$"
        )
        LOAD_MNEMONICS = {
            "lw", "lh", "lhu", "lb", "lbu", "lwl", "lwr",
            "lwc1", "lwc2", "ldc1", "ldc2",
        }

        result = []
        i = 0
        n = len(out)
        while i < n:
            if not re.match(r"^\.ent\s+\w+$", C(i)):
                result.append(out[i])
                i += 1
                continue

            j = i + 1
            while j < n and not re.match(r"^\.end\b", C(j)):
                j += 1
            hi = min(j + 1, n)  # exclusive; includes the `.end` line
            region = list(range(i, hi))
            reals = [k for k in range(i, hi) if is_real(k)]

            def keep():
                result.extend(out[k] for k in region)

            # (1) frame directives: ra-only mask, empty fmask, zero locals.
            mask = fmask = frame_vars = None
            for k in range(i, hi):
                c = C(k)
                if m := re.match(r"^\.mask\s+(0x[0-9A-Fa-f]+)", c):
                    mask = int(m.group(1), 16)
                elif m := re.match(r"^\.fmask\s+(0x[0-9A-Fa-f]+)", c):
                    fmask = int(m.group(1), 16)
                elif re.match(r"^\.frame\b", c):
                    if mv := re.search(r"\bvars=\s*(\d+)", out[k]):
                        frame_vars = int(mv.group(1))
            if not (mask == 0x80000000 and fmask == 0x00000000
                    and frame_vars in (0, None)):
                keep()
                i = hi
                continue

            # (2) at least one call, and EVERY call is a DIRECT jal/j into the
            # noreturn OR sibcall evidence set. LEAD 19 required exactly one; the
            # LEAD 23 extension allows several (the confirmed town func_800CF814
            # tail-dispatches the same sibcall member twice). Safety is unchanged:
            # a `j MEMBER` is always a tail exit and never uses $ra as a link, and
            # a `jal MEMBER` is jal->j'd by LEAD 18/22 upstream (members are
            # zero-jal in retail), so $ra stays dead across all of them. Any
            # INDIRECT call, or any direct call to a NON-member, means a live
            # return link (a real returning call) -> the frame is genuine, keep.
            calls = []
            for k in reals:
                c = C(k)
                if IND_CALL.match(c):
                    calls.append((k, "indirect", None))
                elif m := JAL_SYM.match(c):
                    calls.append((k, "jal", m.group(1)))
                elif m := J_SYM.match(c):
                    calls.append((k, "j", m.group(1)))
            targets = self.noreturn_syms | self.sibcall_syms
            if not calls or any(
                kind == "indirect" or sym not in targets
                for (_ck, kind, sym) in calls
            ):
                keep()
                i = hi
                continue

            # (3) arg-reg delay-slot guard (inherited from LEAD 18): decline if
            # ANY tail call parks an argument register in its delay slot (unclear
            # shape -> don't fire). Conservative for sibcalls, which do pass args.
            g3_bad = False
            for (ck, _kind, _sym) in calls:
                cpos = reals.index(ck)
                if cpos + 1 < len(reals):
                    delay = out[reals[cpos + 1]]
                    if any(self._line_writes_reg(delay, r)
                           for r in ("$a0", "$a1", "$a2", "$a3")):
                        g3_bad = True
                        break
            if g3_bad:
                keep()
                i = hi
                continue

            # (4) the frame is exactly {alloc, ra-save, ra-restore, dealloc}. The
            # ONLY other $sp uses tolerated (LEAD 23) are incoming caller-argument
            # LOADS at offsets N+16, N+20, ... -- collected as `pending` here and
            # classified below once the frame size N is known. Any other $sp use
            # (a store, an address-of-stack, a load into the removed frame) aborts.
            alloc_idx = save_idx = restore_idx = dealloc_idx = None
            save_off = restore_off = None
            alloc_amt = dealloc_amt = None
            pending = []
            ok = True
            for k in reals:
                c = C(k)
                if not re.search(r"\$sp\b", c):
                    continue
                if ms := SAVE.match(c):
                    if save_idx is not None:
                        ok = False
                        break
                    save_idx, save_off = k, int(ms.group(1), 0)
                elif mr := RESTORE.match(c):
                    if restore_idx is not None:
                        ok = False
                        break
                    restore_idx, restore_off = k, int(mr.group(1), 0)
                elif (adj := sp_adjust(c)) is not None and adj < 0:
                    if alloc_idx is not None:
                        ok = False
                        break
                    alloc_idx, alloc_amt = k, -adj
                elif adj is not None and adj > 0:
                    if dealloc_idx is not None:
                        ok = False
                        break
                    dealloc_idx, dealloc_amt = k, adj
                else:
                    pending.append(k)  # classify as caller-arg slot below
            if not (ok and None not in (alloc_idx, save_idx, restore_idx, dealloc_idx)
                    and save_off == restore_off and alloc_amt == dealloc_amt):
                keep()
                i = hi
                continue

            # (4b) LEAD 23: classify every residual $sp use as an incoming
            # caller-argument load at N+16, N+20, ... (N == the removed frame
            # size). Reject (don't fire) if any points INTO the removed frame
            # [0,N), is misaligned, or is not a recognised load. `argslot` maps
            # each such line to its rebased offset (original - N) for the rewrite.
            N = alloc_amt
            retained = self.retain_tail_frame
            if retained >= N:
                keep()
                i = hi
                continue
            argslot = {}
            for k in pending:
                mm = MEM_SP.match(C(k))
                if not mm:
                    ok = False
                    break
                mnem = mm.group(1)
                off = int(mm.group(2), 0)
                if mnem not in LOAD_MNEMONICS:
                    ok = False
                    break
                if off < N or (off - N) < 16 or (off - N) % 4 != 0:
                    ok = False
                    break
                argslot[k] = off - (N - retained)
            if not ok:
                keep()
                i = hi
                continue

            # Build the elided function: drop the four frame instructions
            # (comment them out; a dealloc sitting in the return's delay slot is
            # replaced by nop so the slot is not silently re-filled), and finish
            # the jal->j rewrite if the tail is still a jal.
            transform = {
                alloc_idx: (
                    f"addiu\t$sp,$sp,-{retained}"
                    "\t# maspsx: LEAD 19 retained partial tail frame"
                    if retained else
                    "# " + out[alloc_idx]
                    + "\t# maspsx: LEAD 19 elided prologue alloc"
                ),
                save_idx: "# " + out[save_idx]
                + "\t# maspsx: LEAD 19 elided ra-save",
                restore_idx: "# " + out[restore_idx]
                + "\t# maspsx: LEAD 19 elided ra-restore",
            }
            dealloc_pos = reals.index(dealloc_idx)
            prev_is_ctrl = dealloc_pos > 0 and re.match(
                r"^(?:j|jr|jal|jalr|b(?:eq|ne|gez|gtz|lez|ltz))\b",
                C(reals[dealloc_pos - 1]),
            )
            if retained:
                transform[dealloc_idx] = (
                    f"addiu\t$sp,$sp,{retained}"
                    "\t# maspsx: LEAD 19 retained partial tail frame"
                )
            elif prev_is_ctrl:
                transform[dealloc_idx] = (
                    "nop\t# maspsx: LEAD 19 elided sp-teardown (was delay slot)"
                )
            else:
                transform[dealloc_idx] = (
                    "# " + out[dealloc_idx]
                    + "\t# maspsx: LEAD 19 elided sp-teardown"
                )
            # Complete any surviving jal->j on an evidence-member tail call (a
            # jal the earlier passes left directly before the epilogue).
            for (ck, kind, sym) in calls:
                if kind == "jal":
                    transform[ck] = (
                        "j\t" + sym
                        + "\t# maspsx: tail-call jal->j (LEAD 19 frame elision)"
                    )

            # LEAD 23: rebase each incoming caller-argument load by the removed
            # frame size N (e.g. `lw a1,40($sp)` -> `lw a1,16($sp)`).
            for k, new_off in argslot.items():
                transform[k] = (
                    re.sub(
                        r"(-?(?:0x[0-9A-Fa-f]+|\d+))\(\$sp\)",
                        f"{new_off}($sp)",
                        out[k],
                        count=1,
                    )
                    + f"\t# maspsx: LEAD 23 caller-arg slot rebased -{N}"
                )

            new_region = [transform.get(k, out[k]) for k in region]

            # Belt-and-braces: no residual $sp use, no non-return $ra use, no
            # surviving second call. If anything trips, abort -- keep untouched.
            bad = False
            for pos, line in enumerate(new_region):
                if not is_real_line(line):
                    continue
                # A rebased caller-arg load legitimately still references $sp.
                if region[pos] in argslot:
                    continue
                c = strip_comments(line).strip()
                if (re.search(r"\$sp\b", c)
                        and region[pos] not in argslot
                        and region[pos] not in (alloc_idx, dealloc_idx)):
                    bad = True
                    break
                if re.search(r"\$(?:31|ra)\b", c) and not RETURN.match(c):
                    bad = True
                    break
                if re.match(r"^jal\b", c) or re.match(r"^jalr\b", c):
                    bad = True
                    break
            if bad:
                keep()
                i = hi
                continue

            # LEAD 19/23 return-delay backfill: the elision above vacated the
            # `jr $ra` return delay slot (the sp-teardown became a nop). When a
            # reg-base displacement store sits immediately before that return,
            # retail SINKS it into the delay slot (`jr $ra; s[bhw] Rt,off(Rb)`)
            # rather than leaving `store; jr $ra; nop`. Applied only to a clean,
            # already-validated elided region and gated by the fill/keep
            # discriminator (see _backfill_return_delay_store).
            if not self.preserve_return_delay:
                m_ent = re.match(r"^\.ent\s+(\w+)$", C(i))
                new_region = self._backfill_return_delay_store(
                    new_region, func_name=m_ent.group(1) if m_ent else None
                )

            result.extend(new_region)
            i = hi
        return result

    @classmethod
    def _producer_in_load_shadow(cls, out, reals, q):
        """LEAD 34 ladder step 3: the FUNCTION-BLIND exception to the
        value-freshness KEEP guard of ``_backfill_return_delay_store``.

        True when the instruction at ``reals[q]`` -- the producer of the value
        the store writes -- is a register ALU op sitting in the LOAD-DELAY
        SHADOW of the load that feeds it:

            <load> Rx,off(Rb)     <- reals[q-2]
            nop                   <- reals[q-1]  (the load's hazard slot, idle)
            <alu>  val,Rx,...     <- reals[q]    (reads Rx, writes the store value)
            <store> val,off2(Rb2) <- the store the caller wants to sink

        WHY THIS IS THE DISCRIMINATOR (corpus, all matched rows at the time of
        landing; every one of them byte-exact under this rule):
          * FILL, shadowed producer: two dungeon rows whose tail is
            `lhu $2,20($8); nop; andi $2,$2,0xbfff; sh $2,20($8)`.  Retail is
            one word shorter than a KEEP: `jr $ra` carries the store.
          * KEEP, producer NOT shadowed: a town row whose tail is
            `lhu $2,104($4); sh $0,106($4); addu $2,$2,1; sh $2,104($4)` --
            the same read-modify-write of the SAME address, the same "value
            written by the previous instruction", but the load's hazard slot is
            FILLED with independent work, so the tail is not a single stalled
            chain and retail keeps the nop.
          * KEEP, no producer at all: dungeon rows shaped
            `lw/lhu $2,..; nop; s.. $2,..` -- the value comes straight out of
            the load, so ``reals[q]`` is the LOAD itself and this returns False
            (loads are excluded).  Guard (a) still declines them.
        The unconditional-FILL rows the pass was derived from (a `$zero` store
        and two whose value was set far earlier) never reach guard (a) at all
        and are unaffected.  Per-row receipts, including every candidate site in
        the matched corpus: the REPORT.md named above.

        SHAPE IS NECESSARY BUT NOT SUFFICIENT -- WHY THIS IS A BUILD SWITCH.
        The matched overlay corpus (5,882 rows, 2026-09-06) contains exactly SIX
        sites with this shape.  The two that FILL are both DUNGEON rows; the
        four that KEEP are all TOWN rows, and two of those are textually
        identical to the FILL pair modulo load/store width
        (`lw $2,20($4); nop; ori $2,$2,1; sw $2,20($4)`).  No local feature
        separates them: the split follows the CONTAINER, i.e. the build that
        produced the retail object, not anything visible in the instruction
        stream.  So this method is only ever consulted when the caller was
        switched on with `--fill-shadowed-return-delay`, which is meant to be
        set once for a whole container and is OFF by default.  Passing it per
        function would be a name-keyed dial wearing a different hat; passing it
        per container is a build fact.  Receipts (all six sites, with the
        rescore that refutes the unconditional rule): the REPORT.md named above.

        Reading: an idle hazard slot immediately before the producer means the
        function's whole tail is ONE dependent chain with nothing to interleave;
        a filled hazard slot means there was independent work in the tail.  The
        test is local, name-free, and strictly ADDITIVE (it can only turn a
        guard-(a) KEEP into a FILL; every correctness guard -- reg-base
        displacement store, no $sp/$ra operand, and the fall-through-only live
        label test (b) -- is applied by the caller either way).
        """
        if q < 2:
            return False
        op, _operands = cls._instruction_operands(out[reals[q]])
        if op is None:
            return False
        if (op in load_mnemonics or op in unaligned_load_mnemonics
                or op in store_mnemonics or op in unaligned_store_mnemonics
                or op in branch_mnemonics or op in jump_mnemonics
                or op in ("jr", "jalr", "nop", "break")):
            return False
        if strip_comments(out[reals[q - 1]]).strip() != "nop":
            return False
        lop, loperands = cls._instruction_operands(out[reals[q - 2]])
        if lop is None or not loperands:
            return False
        if lop not in load_mnemonics and lop not in unaligned_load_mnemonics:
            return False
        dest = cls._line_reg_list(loperands[0])
        if not dest:
            return False
        # The nop must really be THIS load's hazard slot: the producer reads the
        # register the load just wrote.
        return cls._line_reads_reg(out[reals[q]], dest[0])

    def _backfill_return_delay_store(self, region_lines, func_name=None):
        """LEAD 19/23 gap `maspsx-return-delay-backfill`: sink a REG-BASE store
        into a vacated ``jr $ra`` return delay slot after frame elision.

        After ``_elide_ra_only_frame_for_noreturn_tail`` removes the frame, a
        frameless return whose delay slot held the dealloc becomes
        ``... ; s[bhw] Rt,off(Rbase) ; jr $ra ; nop`` (the nop is the vacated
        sp-teardown slot). Retail/ASPSX for the SAME frameless function instead
        carries ``... ; jr $ra ; s[bhw] Rt,off(Rbase)`` -- the store filled the
        return delay slot. gcc's own dbr could not reproduce it because gcc built
        the (now-elided) frame and spent the slot on the dealloc; ``is_delay_fill``
        only relocates a single ALU/``li`` and ``_expand_store_to_symbol_in_delay``
        only a DIRECT-symbol store, so neither covers a register-base displacement
        store -> +1 word. This rotates the store down into the slot.

        FILL/KEEP DISCRIMINATOR (the decisive gate over the 2026-07-10 LEAD-23b
        naive fill, which was RESTORED as a `mixed, no discriminator` wall).
        Retail FILLS only when BOTH hold; otherwise it KEEPS the nop:
          (a) VALUE FRESHNESS: the store's VALUE register is NOT produced by the
              instruction immediately before the store (skipping MIPS load-delay
              nops). When the value is defined right before the store, retail
              keeps the nop.
          (b) FALL-THROUGH ONLY: the store is not a branch target and the return
              is not a branch target (no live label between the store's
              predecessor and the return delay slot).
        Corpus (all matched overlay funcs at the time of landing):
          * FILL:  func_8008C1D4 (`sw $0,0x8C(a0)`, value $zero, straight-line),
                   func_800403EC (`sh v1,42(t0)`, v1 set far earlier),
                   func_800B79CC (`sb v1,10(..)`, v1 set far earlier).
          * KEEP (a): func_800CF814 (`addiu v0,v0,1; sh v0,104(a0)`),
                   func_800A1600 / func_8195A2C4 (`lw/lhu v0; nop; s.. v0` -- the
                   value is freshly loaded, one real insn + a load-delay nop
                   before the store).
          * KEEP (b): func_800B4C60 (`beqz ...,L; ... L: sw $0,4(a0); jr ra; nop`
                   -- the store is the beqz target).
        A store of $zero passes (a) (nothing defines $zero) but still must pass
        (b).

        LEAD 34 (2026-09-06, ladder step 3 -- FUNCTION-BLIND): (a) is not
        MIXED after all.  It is stated over the wrong window: the separator is
        not "was the value written by the previous instruction" but "was the
        PRODUCER of that value itself stalled in a load-delay shadow".  Retail
        FILLS whenever the store's value comes out of an ALU op that sits in
        the hazard slot shadow of the load feeding it (`<load> Rx,off(Rb);
        nop; <alu> val,Rx,..; <store>`), and KEEPS otherwise.  That exception
        is `_producer_in_load_shadow`, and it replaces the per-function waiver
        list entirely; see that method for the corpus that fixes it.

        SAFETY:
          * Fires only on the region of a function the elision already accepted
            (single ra-only frame, all calls noreturn/sibcall members, belt-and-
            braces clean), so it can never touch a non-elided function. Within
            such a function it fires on the frameless return's nop delay slot --
            whether that nop is the vacated sp-teardown slot (dealloc was in the
            delay slot) or a genuine gcc nop (gcc put the dealloc before the
            return, e.g. under -fno-schedule-insns). The fill/keep discriminator
            below is what keeps a genuine-nop KEEP case (func_800CF814) untouched,
            NOT the origin of the nop.
          * The store/return/nop must be a contiguous straight-line run with NO
            label defined on the store, the return, or the nop -- so no branch can
            reach the return while skipping the store (which would wrongly execute
            the store in the delay slot on that edge). A label BEFORE the store is
            fine: that path still flows store->return.
          * Never a $sp/$ra-based or $ra-valued store (the elision belt-and-braces
            already removed all $sp/$ra uses; re-checked here).
        """
        out = list(region_lines)

        def C(i):
            return strip_comments(out[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def label_name(i):
            c = C(i)
            if c.startswith("glabel"):
                parts = c.split()
                return parts[1] if len(parts) > 1 else None
            if c.endswith(":"):
                return c[:-1]
            return None

        RET = re.compile(r"^(?:j|jr)\t\$(?:31|ra)$")
        STORE = re.compile(
            r"^(s[bhw])\t(\$\w+),(-?(?:0x[0-9A-Fa-f]+|\d+))\((\$\w+)\)$"
        )

        # Labels REFERENCED anywhere (branch/jump/`la`/jump-table `.word $L`) but
        # not their definitions. A dead label left behind by an earlier pass
        # (e.g. the `$Lepilogue` LEAD 22 deleted its `j $Llabel` for) emits zero
        # bytes and is harmless to sit between the store and the return; a LIVE
        # one means control could reach the return while skipping the store,
        # which must abort the rotation. A commented-out reference strips to ""
        # (so a removed `j $L` does not count as live); a label DEFINITION line is
        # excluded so a label is not made live by its own `$Ln:`.
        live_labels: set[str] = set()
        for k in range(len(out)):
            if label_name(k) is None:
                live_labels.update(re.findall(r"\$L\w+", C(k)))

        reals = [k for k in range(len(out)) if is_real(k)]
        for p in range(len(reals)):
            nop_k = reals[p]
            # (1) the frameless return's delay slot is a nop (vacated sp-teardown
            #     OR a genuine gcc nop -- either way retail may have filled it).
            if C(nop_k) != "nop":
                continue
            if p < 2:
                continue
            ret_k = reals[p - 1]
            store_k = reals[p - 2]
            # (2) the return, and a reg-base store immediately before it.
            if not RET.match(C(ret_k)):
                continue
            m = STORE.match(C(store_k))
            if not m:
                continue
            _mnem, val_reg, _off, base_reg = m.group(1, 2, 3, 4)
            val = canonical_reg(val_reg)
            base = canonical_reg(base_reg)
            if base in ("$sp", "$ra") or val in ("$sp", "$ra"):
                continue
            # The store must have a predecessor to reason about.
            if p < 3:
                continue
            pred_k = reals[p - 3]  # real instruction textually before the store
            # (3) the store must be reached ONLY by fall-through from its
            # predecessor: NO LIVE label may be defined between the predecessor
            # and the return delay slot. This aborts two retail-KEEP shapes at
            # once:
            #   * a branch-target STORE -- `beqz ...,L; ... ; L: s.. $x,off(Rb);
            #     jr ra; nop` where retail leaves the nop (func_800B4C60); the
            #     live label sits between pred and the store.
            #   * a branch-target RETURN -- a live label between the store and
            #     the nop; a branch could reach `jr ra` skipping the store.
            # A live label ON or BEFORE the predecessor is fine (func_8008C1D4's
            # bnez target sits on the predecessor). A DEAD label (unreferenced,
            # emits no bytes -- e.g. the epilogue label LEAD 22 orphaned) is also
            # fine, since `lbl in live_labels` is False.
            if any((lbl := label_name(k)) is not None and lbl in live_labels
                   for k in range(pred_k + 1, nop_k + 1)):
                continue
            # (4) FILL/KEEP value-freshness discriminator: retail KEEPS the nop
            # when the store's VALUE register is produced by the instruction
            # immediately before the store -- looking PAST MIPS load-delay nops.
            #   KEEP: func_800CF814 (`addiu v0,v0,1; sh v0,104(a0)`),
            #         func_800A1600 / func_8195A2C4 (`lw/lhu v0; nop; s.. v0`).
            #   FILL: func_8008C1D4 / func_800403EC / func_800B79CC, whose nearest
            #         real predecessor is a store/move that does not write the
            #         value (a $zero constant is never "written", so it fills).
            # LEAD 34 (2026-09-06): guard (a) is a retail-BEHAVIOUR predictor,
            # not a correctness guard (the delay slot issues after the preceding
            # instruction has written its result). Its one exception is
            # structural, not per-function -- a producer stalled in the
            # load-delay shadow of the load feeding it -- but that SHAPE alone
            # does not predict retail: the same shape FILLS in one container and
            # KEEPS in another (see `_producer_in_load_shadow`). The exception is
            # therefore a DEFAULT-OFF, FUNCTION-BLIND build switch
            # (`--fill-shadowed-return-delay`), to be set per CONTAINER, never
            # per function. No function name is consulted anywhere in this pass.
            if val != "$zero":
                q = p - 3
                while q >= 0 and C(reals[q]) == "nop":
                    q -= 1
                if (q >= 0
                        and self._line_writes_reg(out[reals[q]], val)
                        and not (self.fill_shadowed_return_delay
                                 and self._producer_in_load_shadow(out, reals, q))):
                    continue
            # ROTATE: comment the store's old slot; emit it in the delay slot.
            moved = C(store_k)
            out[store_k] = (
                "# " + out[store_k]
                + "\t# maspsx: LEAD 19/23 return-delay backfill (store sunk"
                " into jr delay)"
            )
            out[nop_k] = (
                "\t" + moved
                + "\t# maspsx: LEAD 19/23 return-delay backfill"
            )
        return out


    def _uses_gp(self, line: str) -> bool:
        if self.sdata_limit == 0:
            return False

        line = strip_comments(line)
        if uses_at(line):
            op, *rest = line.split("\t")
            if op in load_mnemonics or op in store_mnemonics:
                (
                    _,
                    _,
                    operand,
                    _,
                    _,
                ) = parse_load_or_store(" ".join(rest))

                if operand.count("+") == 1:
                    symbol, _ = operand.split("+")
                    gp_allowed = self.gp_allow_offset or symbol not in self.comm_symbols
                else:
                    symbol = operand
                    gp_allowed = True

                if gp_allowed and (
                    symbol in self.sbss_entries
                    or symbol in self.sdata_entries
                    or (
                        symbol in self.extern_sizes
                        and 0 < self.extern_sizes[symbol] <= self.sdata_limit
                    )
                ):
                    return True

        return False

    def _handle_nop_before_next_instruction(
        self, next_instruction: str, r_dest: str
    ) -> List[str]:
        res: List[str] = []

        if line_loads_from_reg(next_instruction, r_dest):
            nop_required = False

            if not uses_at(next_instruction):
                reason = f"'{next_instruction}' does not use $at"
                nop_required = True
            if self._uses_gp(next_instruction):
                reason = f"'{next_instruction}' uses $gp"
                nop_required = True
            if uses_at(next_instruction) and self.nop_at_expansion:
                reason = (
                    f"'{next_instruction}' inject nop beween {r_dest} and $at expansion"
                )
                nop_required = True

            if nop_required:
                label = self.get_next_instruction(
                    skip=0, ignore_nop=True, ignore_set=True
                )
                if is_label(label):
                    res.append(label)
                    self.skip_instructions = 1
                res.append(f"nop # DEBUG: Reuse of '{r_dest}'. {reason}")
        else:
            res.append(
                f"#nop # DEBUG: '{next_instruction}' does not load from {r_dest}"
            )

        return res

    def _handle_mflo_mfhi(self, r_source=None) -> List[str]:
        # we cannot use a div/mult within 2 instructions of mflo/mfhi
        res: List[str] = []

        if not self.nop_mflo_mfhi:
            return res

        next_instruction = self.get_next_instruction(
            skip=0, ignore_nop=True, ignore_set=True, ignore_label=True
        )
        next_next_instruction = self.get_next_instruction(
            skip=1, ignore_nop=True, ignore_set=True, ignore_label=True
        )

        if any(
            next_instruction.startswith(x)
            for x in ["mult\t", "multu\t", "div\t", "divu\t", "rem\t", "remu\t"]
        ):
            # #nop
            # #nop
            # mult...
            skip = 0
            while True:
                inst = self.get_next_instruction(skip=skip)
                skip += 1
                if inst == next_instruction:
                    res.append("nop")
                    res.append("nop")
                    if div_needs_expanding(inst):
                        res.append("# DEBUG: div needs expanding")
                        skip -= 1
                    else:
                        res.append(expand_move(inst))
                    break
                if not inst.startswith("#"):
                    res.append(expand_move(inst))
            self.skip_instructions = skip

        elif any(
            next_next_instruction.startswith(x)
            for x in ["mult\t", "multu\t", "div\t", "divu\t", "rem\t", "remu\t"]
        ):

            # #nop
            # #nop
            # bne or addu or lh ...
            # mult ...
            skip = 0
            no_reorder = False
            while True:
                inst = self.get_next_instruction(skip=skip)

                if inst.startswith(".set") and inst.endswith("noreorder"):
                    no_reorder = True
                    skip += 1
                    continue

                skip += 1
                if inst == next_instruction:
                    op, *_ = inst.strip().split()
                    if op in load_mnemonics:
                        # allow for $at handling later in the script
                        skip = 0
                        break

                    if op in ("mflo", "mfhi"):
                        # allow for mflo/mfhi handling later on
                        skip = 0
                        break

                    if op == "li":
                        expanded = expand_load_immediate(inst)

                        if self.expand_li:
                            res += expanded
                        else:
                            res.append(inst)

                        if len(expanded) == 2:
                            res.append(
                                "#nop  # DEBUG: mflo/mfhi with mult/div/rem and li expands to 2 ops"
                            )
                        else:
                            res.append(
                                "nop  # DEBUG: mflo/mfhi with mult/div/rem and li expands to 1 op"
                            )

                    else:

                        if no_reorder:
                            res.append(
                                "nop  # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction (noreorder)"
                            )
                            res.append(".set\tnoreorder")
                            res.append(expand_move(inst))
                        else:
                            if r_source and line_loads_from_reg(inst, r_source):
                                # NOTE: only relevant when div has been expanded (i.e. -0 flag)
                                res.extend(
                                    [
                                        f"nop  # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction which loads from {r_source}",
                                        expand_move(inst),
                                    ]
                                )
                            else:
                                if op in branch_mnemonics:
                                    res.extend(
                                        [
                                            inst,
                                            "nop # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction (branch)",
                                        ]
                                    )
                                else:
                                    maybe_label = self.get_next_instruction(skip=skip)
                                    if is_label(maybe_label):
                                        res.extend(
                                            [
                                                expand_move(inst),
                                                maybe_label,
                                                "nop  # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction (label)",
                                            ]
                                        )
                                        skip += 1
                                    else:
                                        res.extend(
                                            [
                                                expand_move(inst),
                                                "nop  # DEBUG: mflo/mfhi with mult/div/rem and 1 instruction",
                                            ]
                                        )

                elif inst == next_next_instruction:
                    # reached mult/div/rem
                    if div_needs_expanding(inst):
                        res.append("# DEBUG: div needs expanding")
                        skip -= 1
                    else:
                        res.append(inst)
                    break
                elif not inst.startswith("#"):
                    res.append(expand_move(inst))
            self.skip_instructions = skip

        else:
            # do nothing
            pass

        return res

    def _access_is_volatile_marked(self) -> bool:
        """True when the line currently being expanded sits inside a gcc
        `.set volatile` region.

        gcc's MIPS back end brackets every VOLATILE memory reference with
        `.set volatile` / `.set novolatile` (config/mips/mips.c operand codes
        `%{` / `%}`, mirroring its own `set_volatile` nesting counter). The
        directive is printed BARE for `TARGET_MIPS_AS` (the SN assembler) and
        `#`-commented for GNU `as`::

            #.set	volatile
            sh	$0,D_XXXXXXXX
            #.set	novolatile

        Retail's translation units went through the SN assembler, which sees
        the live directive and stops rescheduling the marked access: the macro
        stays where the compiler put it and the following jump keeps its `nop`.
        Our pipeline gets the identical compiler output in its `#`-commented
        spelling, and `is_instruction` deliberately classifies BOTH spellings
        as non-instructions -- which is exactly why `get_next_instruction`
        looks straight through the closing marker and a delay-slot rotation
        would otherwise steal a volatile access.

        Flat scan, not a counter: gcc emits one `%{`/`%}` pair per access, so
        the nearest preceding marker decides, and a `.ent` resets the state (a
        region can never span a function boundary).
        """
        i = self.line_index
        while i >= 0:
            line = self.lines[i].strip()
            if line in (".set\tvolatile", "#.set\tvolatile"):
                return True
            if line in (".set\tnovolatile", "#.set\tnovolatile"):
                return False
            if line.startswith(".ent\t"):
                return False
            i -= 1
        return False

    def _expand_store_to_symbol_in_delay(self, op: str, r_data: str, operand: str):
        """Replicate ASPSX scheduling a store-to-global macro into the delay slot
        of a following unconditional jump.

        For code like `D_X = c;` at the end of a function, gcc emits a bare store
        macro immediately before the return jump, e.g.::

            sw	$0,D_80084130
            j	$31

        GNU `as` would expand the macro with `$at` (`lui $at,%hi; sw $0,%lo($at)`)
        and, being unable to reorder a macro into the delay slot, leave a `nop`
        there. ASPSX instead materialises `%hi()` in a caller-saved temp register
        and schedules the `%lo()` store into the jump's delay slot::

            lui	$2,%hi(D_80084130)
            j	$31
            sw	$0,%lo(D_80084130)($2)

        (see func_8004EB30, func_8005ACD0, func_800557BC, func_8005A39C).

        Only fires in reorder mode when the very next instruction is an
        unconditional `j $31` / `jr $ra`; anything else (a `.set noreorder`
        boundary, a conditional branch, a gcc-prefilled delay slot) blocks it and
        we fall back to leaving the macro for `as`. A `.set volatile` region is
        a further blocker -- see `_access_is_volatile_marked`. Returns the
        replacement lines, or None when not applicable.
        """
        if not self.is_reorder:
            return None

        # Only for non-small-data globals: a symbol whose `.extern` size exceeds
        # the -G threshold is addressed via %hi/%lo (not $gp). Small-data symbols
        # (size <= -G, or those `as -G` treats as $gp) must be left untouched so
        # `as` emits the single %gp_rel store instead. A symbol with no seen
        # `.extern` size is treated as small-data (the historic default).
        symbol = operand.split("+")[0]
        if self.extern_sizes.get(symbol, 0) <= self.sdata_limit:
            return None

        # A `.set volatile` region is a SCHEDULING BARRIER, not a comment: the
        # access inside it may not be moved. See `_access_is_volatile_marked`
        # for why the marker survives as a `#` comment in our input and why
        # this pass is the one that has to read it.
        if self._access_is_volatile_marked():
            return None

        next_instruction = self.get_next_instruction(ignore_nop=True)
        # unconditional return-style jump (j $31 / jr $ra / jr $31) OR a call (jal target):
        # ASPSX schedules the %lo tail into the delay slot of a following `jal` too, e.g.
        # `func(&D_X)` compiled as `lui a0,%hi; jal func; addiu a0,a0,%lo(delay)` rather than
        # gcc/as's `lui; addiu; jal; nop`. (see func_80050FA8)
        if not re.match(r"^(j|jr)\t\$(31|ra)$|^jal\t\S+$", strip_comments(next_instruction)):
            return None

        # If a function-address `la` is pending for this same jal (see
        # _split_funcaddr_la), don't let a data store steal the delay slot — the
        # funcaddr %lo tail claims it and this store stays an in-place ($at) macro.
        if (
            op != "la"
            and self._pending_funcaddr is not None
            and re.match(r"^jal\t\S+$", strip_comments(next_instruction))
        ):
            return None

        # consume the jump: we emit it ourselves and put the %lo tail in its delay slot
        self.skip_instructions = 1

        if op == "la":
            # load-address (`return &D_X;`): ASPSX puts `lui` before the jump and
            # the `addiu` %lo tail into the delay slot (rather than GNU as's
            # lui+addiu pair before the jump + a nop delay).
            return [
                f"lui\t{r_data},%hi({operand})",
                next_instruction,
                f"addiu\t{r_data},{r_data},%lo({operand})",
            ]

        # store: ASPSX uses a caller-saved temp ($v0), stepping to $v1 when $v0 is
        # the value being stored (and would otherwise be clobbered / is the return).
        reg = "$2" if r_data not in ("$2", "$v0") else "$3"
        return [
            f"lui\t{reg},%hi({operand})",
            next_instruction,
            f"{op}\t{r_data},%lo({operand})({reg})",
        ]

    def _unfill_via_load_delay(self, res):
        """cs=1 companion to _maybe_unfill_return_delay. When `lw $ra` is immediately
        followed by a load-delay `nop` (because the return `j/jr $ra` reuses the just-
        loaded $ra) and gcc>=2.8 fills the jump delay slot with the sp teardown, retail
        instead fills the lw-$ra load-delay slot with the teardown and nops the jump
        delay::

            lw $31,K($sp); nop; j $31; addu $sp,$sp,N
              ->  lw $31,K($sp); addu $sp,$sp,N; j $31; nop

        Only fires on this exact 4-instruction shape. See func_8004A8D8, func_8004B404.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        idx = [
            i for i in range(len(res))
            if C(i) and not C(i).startswith("#") and not C(i).startswith(".")
            and not C(i).endswith(":") and not C(i).startswith("$L")
            and not C(i).startswith("glabel")
        ]
        for p in range(len(idx) - 3):
            a, b, c, d = idx[p], idx[p + 1], idx[p + 2], idx[p + 3]
            if (
                re.match(r"^lw\t\$(31|ra),[^,]*\(\$sp\)$", C(a))
                and C(b) == "nop"
                and re.match(r"^(j|jr)\t\$(31|ra)$", C(c))
                and re.match(r"^add[i]?u\t\$sp,\$sp,(\d+|0x[0-9A-Fa-f]+)$", C(d))
            ):
                res[b], res[d] = res[d], res[b]  # teardown -> load-delay; nop -> jump delay
        return res

    def _unfill_jal_sp_delay(self, res):
        """Retail/ASPSX leaves a direct-call (`jal SYM`) delay slot UNFILLED (nop)
        when the instruction that would fill it is a stack-pointer swap
        (`move $sp,$reg`, i.e. `addu $sp,$reg,$zero`) -- the coroutine/stack-switch
        idiom where $sp is repointed just before the call. gcc's delayed-branch
        pass instead fills the slot with that move::

            jal   func_XXXX              addu  $sp,$t0,$zero
            addu  $sp,$t0,$zero    ->    jal   func_XXXX
                                         nop

        Hoisting the move above the jal is semantics-preserving: the delay slot
        always executes, and the move neither reads nor is affected by the jal's
        only output ($ra/$31). Fires ONLY on this exact shape -- a direct `jal` to
        a named symbol (never `jalr`/register targets) whose very next instruction
        is `addu $sp,$R,$zero` with $R neither $ra nor $31. See func_8004CAA0.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        idx = [i for i in range(len(res)) if is_real(i)]
        fix_jal_to_delay = {}
        for p in range(len(idx) - 1):
            a, b = idx[p], idx[p + 1]
            m = re.match(r"^addu\t\$sp,(\$\w+),\$zero$", C(b))
            if (
                re.match(r"^jal\t(?!\$)[A-Za-z_.][\w.]*$", C(a))
                and m
                and m.group(1) not in ("$ra", "$31", "$sp")
            ):
                fix_jal_to_delay[a] = b

        if not fix_jal_to_delay:
            return res

        fix_delay_positions = set(fix_jal_to_delay.values())
        out = []
        for i, line in enumerate(res):
            if i in fix_jal_to_delay:
                out.append(res[fix_jal_to_delay[i]])  # sp-swap hoisted before the jal
                out.append(line)  # jal
                out.append("nop\t# maspsx: un-filled jal delay (sp-swap)")
            elif i in fix_delay_positions:
                continue  # already emitted ahead of its jal
            else:
                out.append(line)
        return out

    def _hoist_zero_arg_before_global_clears(self, res):
        """Hoist a zero call-argument move out of a direct-call delay slot.

        gcc 2.7.2 can sink `move $a0,$zero` into a later call's delay slot even
        when retail/ASPSX leaves that delay empty and performs the argument move
        before adjacent direct global clears. Keep this to the observed safe
        shape: exactly two adjacent direct `s[bhw] $zero,SYM` stores, then a
        direct `jal SYM`, then a zero move to an argument register in the delay.
        No labels/directives may sit in the window.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def is_real(i):
            c = C(i)
            return bool(
                c and not c.startswith("#") and not c.startswith(".")
                and not c.endswith(":") and not c.startswith("$L")
                and not c.startswith("glabel")
            )

        def only_blank_or_comment_between(a, b):
            for j in range(a + 1, b):
                c = C(j)
                if c and not c.startswith("#"):
                    return False
            return True

        def is_zero_global_store(i):
            return re.match(
                r"^s[bhw]\t\$(0|zero),[A-Za-z_.][\w.]*([+-]\d+)?$",
                C(i),
            )

        def is_zero_arg_move(i):
            return re.match(
                r"^(addu|or)\t\$(4|5|6|7|a0|a1|a2|a3),\$(0|zero),\$(0|zero)$",
                C(i),
            )

        idx = [i for i in range(len(res)) if is_real(i)]
        fixes = []
        for p in range(2, len(idx) - 1):
            s0, s1, jal, delay = idx[p - 2], idx[p - 1], idx[p], idx[p + 1]
            if not (
                is_zero_global_store(s0)
                and is_zero_global_store(s1)
                and re.match(r"^jal\t(?!\$)[A-Za-z_.][\w.]*$", C(jal))
                and is_zero_arg_move(delay)
                and (p == 2 or not is_zero_global_store(idx[p - 3]))
                and only_blank_or_comment_between(s0, s1)
                and only_blank_or_comment_between(s1, jal)
                and only_blank_or_comment_between(jal, delay)
            ):
                continue
            fixes.append((s0, delay))

        if not fixes:
            return res

        move_from = {delay: s0 for s0, delay in fixes}
        delay_positions = set(move_from)
        insert_before = {s0: delay for s0, delay in fixes}

        out = []
        for i, line in enumerate(res):
            if i in insert_before:
                out.append(res[insert_before[i]])
                out.append(line)
            elif i in delay_positions:
                out.append("nop\t# maspsx: un-filled jal delay (zero arg)")
            else:
                out.append(line)
        return out

    def _expand_casesi_jumptable_load(self, res):
        """LEAD 13: ASPSX materialises compiler-generated switch jump-table bases
        in a normal register instead of using GNU as's `$at` indexed-load macro.

        gcc emits the casesi dispatch as a local-label indexed load:

            sll   $2,$3,2
            lw    $2,$Ltable($2)
            nop
            j     $2

        The line pass expands that `lw` through `$at`. Retail instead uses the
        load destination as the table-base scratch, then reuses the switch index
        register for the scaled index:

            lui   $2,%hi($Ltable)
            addiu $2,$2,%lo($Ltable)
            sll   $3,$3,2
            addu  $3,$3,$2
            lw    $2,0($3)
            nop
            j     $2

        Firing condition is intentionally narrow: only a `$at` expansion of
        `lw $d,%lo($L... )($at)` from a local `$L` table, immediately preceded
        by `sll $tmp,$idx,2`, immediately followed by the load-delay `nop` and
        an indirect `j`/`jr` through `$d`. Data-symbol indexed loads, non-word
        loads, non-dispatch table probes, and ambiguous `$idx == $d` cases are
        left untouched.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def is_comment_or_blank(i):
            body = res[i].strip()
            return not C(i) or body.startswith("#")

        def next_code(i):
            while i < len(res) and is_comment_or_blank(i):
                i += 1
            return i

        def dispatch_table(sym):
            """A compiler-generated LOCAL table (`$L...`) or an EXTERNAL one.

            A `$L` label can only ever be a casesi table.  An ordinary global
            is admitted only when it is named in `casesi_extern_dispatch_tables`
            -- see that table for the `-mgas`/`-mmips-as` asymmetry that makes the
            landing idiom's `extern void *jtbl_XXXX[]` reach this pass at all, and
            for why the shape guards alone cannot decide it.
            """
            if re.match(r"^\$L[\w.]+$", sym):
                return True
            return sym in casesi_extern_dispatch_tables

        def indirect_jump_through(i, reg):
            body = C(i)
            return re.match(r"^(?:j|jr)\t" + re.escape(reg) + r"$", body) is not None

        out = []
        i = 0
        while i < len(res):
            m_sll = re.match(r"^sll\t(\$\w+),(\$\w+),2$", C(i))
            if not m_sll:
                out.append(res[i])
                i += 1
                continue

            tmp, idx_src = m_sll.groups()
            noat_i = next_code(i + 1)
            lui_i = next_code(noat_i + 1)
            addu_i = next_code(lui_i + 1)
            lw_i = next_code(addu_i + 1)
            at_i = next_code(lw_i + 1)
            if any(pos >= len(res) for pos in (noat_i, lui_i, addu_i, lw_i, at_i)):
                out.append(res[i])
                i += 1
                continue

            m_lui = re.match(r"^lui\t\$at,%hi\(([^)]+)\)$", C(lui_i))
            m_addu = re.match(r"^addu\t\$at,\$at," + re.escape(tmp) + r"$", C(addu_i))
            m_lw = re.match(r"^lw\t(\$\w+),%lo\(([^)]+)\)\(\$at\)$", C(lw_i))
            if (
                C(noat_i) != ".set\tnoat"
                or C(at_i) != ".set\tat"
                or not m_lui
                or not m_addu
                or not m_lw
                or m_lui.group(1) != m_lw.group(2)
                or not dispatch_table(m_lui.group(1))
            ):
                out.append(res[i])
                i += 1
                continue

            dst, sym = m_lw.group(1), m_lw.group(2)
            if tmp == dst:
                if idx_src == dst:
                    out.append(res[i])
                    i += 1
                    continue
                index_reg = idx_src
            else:
                index_reg = tmp

            after_at = at_i + 1
            while after_at < len(res) and is_comment_or_blank(after_at):
                after_at += 1
            jump_i = next_code(after_at + 1)
            if (
                after_at >= len(res)
                or C(after_at) != "nop"
                or jump_i >= len(res)
                or not indirect_jump_through(jump_i, dst)
            ):
                out.append(res[i])
                i += 1
                continue

            out.extend([
                f"lui\t{dst},%hi({sym})",
                f"addiu\t{dst},{dst},%lo({sym})",
                f"sll\t{index_reg},{idx_src},2",
                f"addu\t{index_reg},{index_reg},{dst}",
                f"lw\t{dst},0({index_reg})",
            ])
            i = at_i + 1
            while i < len(res) and is_comment_or_blank(i):
                i += 1
        return out

    def _fold_lo_into_accesses(self, res):
        """ASPSX (and gcc<2.8) do not pre-combine %hi+%lo into a full base register;
        they keep the base as %hi(SYM) [+ a runtime index via addu] and fold
        %lo(SYM+off) into each memory access. gcc>=2.8 instead materialises the full
        base with an extra `addiu $R,$R,%lo(SYM)` and uses numeric offsets::

            lui   $3,%hi(SYM)
            addiu $3,$3,%lo(SYM)     # <- extra
            sll   $2,$4,2
            addu  $2,$2,$3           # derived base = index + full base
            sh    $0,0($2)
            sh    $0,2($2)

        Retail keeps `lui $3,%hi(SYM); ...; addu $2,$2,$3; sh $0,%lo(SYM)($2);
        sh $0,%lo(SYM+2)($2)`. When the addiu's result is used ONLY as a memory base
        (directly, or via one `addu` with a runtime index), drop the addiu and fold
        %lo(SYM+off) back into each access — arithmetically identical, byte-matches
        retail. Conservative: bails if any tagged base is used as a value (moved,
        stored, arithmetic other than the index add), so the full address is provably
        never needed. See func_8004A8D8, func_8003E188.

        LEAD 2 guard #4 (control-flow join): that "provably never needed" argument
        is only sound inside ONE basic block. ``joins_from_outside`` below declines
        the fold when an access is reachable from an edge that never passed the
        seed `lui` (func_800C738C). See its docstring for the discriminator.
        """
        def code(l):
            return strip_comments(l).strip()
        def mentions(text, reg):
            return re.search(r"(?<![\w$])" + re.escape(reg) + r"(?![\w])", text) is not None
        def epilogue_return_copy(pos, reg):
            if reg not in ("$2", "$v0"):
                return False
            cp = code(res[pos])
            if not (
                re.match(r"^move\t" + re.escape(reg) + r",\$\w+$", cp) or
                re.match(r"^addu\t" + re.escape(reg) + r",\$\w+,\$(?:0|zero)$", cp) or
                re.match(r"^or\t" + re.escape(reg) + r",\$\w+,\$(?:0|zero)$", cp)
            ):
                return False
            saw_return = False
            for p in range(pos + 1, len(res)):
                cp = code(res[p])
                if cp.startswith(".end") or cp.startswith(".ent") or cp.startswith(".section") \
                        or cp.startswith("glabel") or re.match(r"^func_[0-9A-Fa-f]+:", cp):
                    return saw_return
                if not cp or cp.startswith("#") or cp.startswith(".") \
                        or cp.endswith(":") or cp.startswith("$L"):
                    continue
                if cp == "nop":
                    continue
                if re.match(r"^lw\t\$(?:16|17|18|19|20|21|22|23|30|31|s[0-7]|fp|ra),-?(?:0x)?[0-9a-fA-F]+\(\$sp\)$", cp):
                    continue
                if re.match(r"^(?:addiu|addu)\t\$sp,\$sp,-?(?:0x)?[0-9a-fA-F]+$", cp):
                    continue
                if re.match(r"^j(?:r)?\t\$(?:31|ra)$", cp):
                    saw_return = True
                    continue
                return False
            return saw_return

        def func_region(pos):
            """[start, end) line range of the function containing ``res[pos]``.

            Local `$L` labels are per-function and gcc REUSES the same names in
            every function of a TU, so the outside-edge search below must never
            look past the enclosing `.ent`/`.end`.
            """
            start = 0
            for p in range(pos, -1, -1):
                cp = code(res[p])
                if cp.startswith(".ent") or cp.startswith("glabel") \
                        or re.match(r"^func_[0-9A-Fa-f]+:", cp):
                    start = p
                    break
            end = len(res)
            for p in range(pos, len(res)):
                cp = code(res[p])
                if cp.startswith(".end") or (
                    p > pos and (cp.startswith(".ent") or cp.startswith("glabel"))
                ):
                    end = p
                    break
            return start, end

        def base_is_dead_after(seed_i, last_access, carriers):
            """LEAD 2 guard #6 (POST-WINDOW LIVENESS, label- and branch-aware).

            Deleting the `addiu` leaves every CARRIER of the base (the seed `$R`
            plus every register the scan tagged as an indexed derivation of it)
            holding a %hi-ONLY value.  A later READ of a carrier through a
            numeric offset therefore reads `SYM_hi + idx + off` instead of
            `SYM + idx + off`.  The fold is declined exactly when such a read can
            still happen.

            Only a READ declines.  A plain REDEFINITION never declines -- it can
            only shorten the range being watched, and it does so only when the
            reasoning is valid.  That distinction is the whole guard:

            * `repro/c.s`: `lw $3,0($10)` redefines the base, but `bgez $5,$L1`
              jumps AROUND it to a label where the old base is still read. So a
              redefinition may retire a carrier only when neither a LABEL nor a
              BRANCH/JUMP has been crossed since the last rewritten access;
              otherwise the carrier stays watched and the later read declines.
            * `func_8004A700` / `func_8004A7D8` (landed, byte-exact): the epilogue
              `$L2: move $2,$16` redefines the seed AFTER a label and NOTHING ever
              reads a carrier again. v1 declined at the redefinition because it
              was fenced and broke both rows (+4 bytes each). A fenced
              redefinition must simply keep watching, not decline.

            Strictly SUBTRACTIVE: it can only decline folds, never create one.
            """
            live = set(carriers)
            if not live:
                return True
            _, end = func_region(seed_i)
            fenced = False   # a label or branch/jump has been crossed
            for p in range(last_access + 1, end):
                cp = code(res[p])
                if not cp or cp.startswith("#") or cp.startswith("."):
                    continue
                if cp.endswith(":") or cp.startswith("$L"):
                    fenced = True
                    continue
                mnem = cp.split("\t", 1)[0]
                hit = [t for t in live if mentions(cp, t)]
                if hit:
                    # A plain redefinition of exactly one carrier: `reg` is the
                    # written first operand and is not read anywhere else on the
                    # line. Anything else that mentions a carrier is a READ.
                    reg = hit[0] if len(hit) == 1 else None
                    wr = re.match(r"^[a-z][a-z0-9.]*\t(\$\w+)(?:,|$)", cp)
                    rest = cp.split(",", 1)[1] if "," in cp else ""
                    redef = (
                        reg is not None
                        and wr is not None and wr.group(1) == reg
                        and mnem not in first_operand_is_source
                        and mnem not in store_mnemonics
                        and not mentions(rest, reg)
                    )
                    if not redef:
                        return False        # a READ of a %hi-only carrier
                    if not fenced:
                        live.discard(reg)   # range provably over
                        if not live:
                            return True
                if re.match(r"^(j|jr|jal|jalr|b)", mnem):
                    fenced = True
            return True

        def joins_from_outside(seed_i, last_access, labels):
            """LEAD 2 guard #4 (CONTROL-FLOW JOIN): True when a label crossed by
            the forward access scan is reachable from an edge that does NOT pass
            through the seed `lui`.

            The rest of this pass is linear-scan dataflow: it refuses to PAIR
            `lui`/`addiu` across a label but happily FOLDS accesses across one, so
            it has no notion of a second predecessor. func_800C738C (town overlay)
            is the counterexample: two arms of a symbol select each materialise a
            full base (`D_800D2650` in the fall-through arm, `D_800D2FC0` in the
            taken arm) and merge at `$L9`, where four shared `lhu` read the base.
            Folding `%lo(D_800D2FC0+k)` into those loads and deleting the taken
            arm's `addiu` is not merely infidelic, it MISCOMPILES the other edge:
            arriving with `$2 = D_800D2650` (already full) the folded load computes
            `D_800D2650 + idx*32 + 0x2FC0`.

            Discriminator (exact against LEAD 2's own cross-branch win): a branch
            INSIDE the window `[seed lui .. last folded access]` cannot bring in a
            different definition of the base — everything reaching the label passed
            the seed first. func_8003E188 (`lbu %lo(SYM)($v1)`, `beqz`, then
            `sb %lo(SYM)($v1)` in the jr delay) is exactly that shape and still
            folds. func_800C738C's `j $L9` sits BEFORE the seed `lui` — an outside
            edge — so it bails.

            Strictly SUBTRACTIVE: it can only decline folds, never create one.
            """
            if not labels:
                return False
            start, end = func_region(seed_i)
            for name, at in labels:
                if at > last_access:
                    # Guard #6 note: the audit called this a hole ("labels after
                    # the last folded access are skipped while the base is still
                    # live"). With base_is_dead_after in force it is NOT
                    # independently exploitable, and widening it here actively
                    # BREAKS landed rows. Every folded access sits at or before
                    # `last_access`, so entering at a later label skips them all;
                    # the only residual hazard is a read of a %hi-only carrier
                    # after that label, which base_is_dead_after already declines
                    # directly. A back-edge from below into the window is caught
                    # by the p > last_access sweep below, since the target label
                    # is itself in-window. Widening the bound to the carriers'
                    # dataflow live range declined func_8004A700/func_8004A7D8,
                    # whose `$L2` epilogue label is targeted by a `beq` that sits
                    # BEFORE the seed lui -- an "outside edge" that provably
                    # cannot reach any folded access.
                    continue  # crossed after the last folded access -> no effect
                ref = re.compile(r"(?<![\w$.])" + re.escape(name) + r"(?![\w$.])")
                for p in range(start, end):
                    if seed_i <= p <= last_access:
                        continue  # inside the window: not an outside edge
                    cp = code(res[p])
                    if not cp or cp.startswith("#"):
                        continue
                    if re.match(r"^[\w.$]+:$", cp):
                        continue  # a label DEFINITION is not an edge
                    if ref.search(cp):
                        return True
            return False

        i = 0
        while i < len(res):
            m = re.match(r"^lui\t(\$\w+),%hi\(([^)]+)\)$", code(res[i]))
            if not m:
                i += 1
                continue
            R, sym = m.group(1), m.group(2)
            sym_re = re.escape(sym)
            # (1) the very next instruction that mentions $R must be addiu $R,$R,%lo(SYM)
            j = i + 1
            addiu_i = None
            while j < len(res):
                cj = code(res[j])
                if cj.startswith(".end") or cj.startswith(".ent") or cj.startswith(".section"):
                    break
                if not cj or cj.startswith("#") or cj.startswith("."):
                    j += 1
                    continue
                if cj.endswith(":") or cj.startswith("$L") or cj.startswith("glabel"):
                    break
                if mentions(cj, R):
                    if re.match(r"^addiu\t" + re.escape(R) + r"," + re.escape(R)
                                + r",%lo\(" + sym_re + r"\)$", cj):
                        addiu_i = j
                    break
                j += 1
            if addiu_i is None:
                i += 1
                continue
            if "maspsx: preserve-full-base" in res[addiu_i]:
                i = addiu_i + 1
                continue
            # (2) forward-scan. tags: reg -> `indexed` (was the %hi base combined with a
            # runtime index via addu?). Only fold accesses through an INDEXED base — a
            # direct (non-indexed) multi-offset access to a fixed %hi+%lo base is kept
            # with numeric offsets by retail, so bail there.
            tags = {R: False}
            # LEAD 2 guard #5 (DERIVATION IDENTITY, func_80953300): which *addu*
            # produced the indexed base currently living in a register. The
            # shared-register guard below compares base REGISTER NAMES, which
            # cannot see two independent derivations that gcc happens to route
            # through the same scratch register. See the guard for the witness.
            derivs = {}
            deriv_seq = 0
            accesses = []
            safe = True
            # base-reuse guard (see func_8005AF74, func_8005AFF4): if gcc REDEFINES the
            # %hi/%lo base register $R with a new value (e.g. `li $R,imm` to reuse it as a
            # store value) after consuming it in the indexing addu, then gcc/retail treated
            # $R as a fully-MATERIALISED pointer (spent, then freed) — the addiu is real and
            # must be kept, offsets stay numeric. This is the opposite of the fold cases
            # (func_8004A8D8), where the store value is an independent reg ($0) and $R is
            # dead after the addu (never redefined). Only counts a redefinition of $R while
            # it is still the raw %hi base (tags[R] is False); an in-place `addu $R,$idx,$R`
            # that RE-tags $R as the indexed base is handled by the addu branch, not here.
            r_reused = False
            call_crossed = set()
            # LEAD 2 guard #4: every label the forward scan walks past, so a fold
            # that crosses a control-flow JOIN can be declined below.
            labels_crossed = []
            # LEAD 2 guard #6: registers still carrying the %hi-only value at the
            # moment the last rewritten access retires (see base_liveness_after).
            carriers_at_last = set()
            k = addiu_i + 1
            while k < len(res):
                ck = code(res[k])
                # STOP at a function boundary — a tagged base never lives across functions;
                # scanning into the next function (and seeing its reuse of $v0/$v1) would
                # wrongly bail. (.ent/.end from gcc, .section from ccproc, or a func label.)
                if ck.startswith(".end") or ck.startswith(".ent") or ck.startswith(".section") \
                        or ck.startswith("glabel") or re.match(r"^func_[0-9A-Fa-f]+:", ck):
                    break
                if not ck or ck.startswith("#") or ck.startswith(".") \
                        or ck.endswith(":") or ck.startswith("$L"):
                    lbl = re.match(r"^([\w.$]+):$", ck)
                    if lbl:
                        labels_crossed.append((lbl.group(1), k))
                    k += 1
                    continue
                mm = re.match(r"^([a-z][a-z0-9]*)\t(\$\w+),(-?(?:0x)?[0-9a-fA-F]+)\((\$\w+)\)$", ck)
                folded_base = None
                if mm and mm.group(4) in tags and (
                    mm.group(1) in load_mnemonics or mm.group(1) in store_mnemonics
                ):
                    op, val, off, base = mm.groups()
                    if base in call_crossed:
                        safe = False
                        break
                    if not tags[base]:
                        safe = False  # direct access to the raw %hi+%lo base -> keep addiu
                        break
                    # LEAD 2 guard #6 (VALUE OPERAND OF A FOLDED ACCESS). The old
                    # rewrite branch ended in `continue`, so the access's OTHER
                    # register operand was never examined at all. Both spellings
                    # are wrong, and both are straight-line -- no join required:
                    #
                    #   store: the value operand is a READ. `sw $3,0($3)` and
                    #     `sw $3,0($2)` folded to `sw $3,%lo(SYM)($3)`, writing a
                    #     %hi-ONLY pointer into memory (probes/f4b.s).
                    #   load: the destination may BE the base. `lw $3,0($3)` left
                    #     $3 tagged although it now holds a loaded VALUE, and the
                    #     next access was folded onto that value (probes/f4a.s).
                    #
                    # Both are answered by one BAIL rather than by untagging.
                    # Untagging is tempting (it is more precise) but it is not
                    # SUBTRACTIVE: retiring the tag also retires the accidental
                    # value-use bail that made the scan collect a second
                    # derivation, so folds the pristine pass declined would newly
                    # fire. That regressed func_8004A658 (landed, byte-exact):
                    # `lw $3,12($3)` untagged $3, the later `addu $2,$2,$3` no
                    # longer created derivation #2, one_base became true and a
                    # REAL addiu was deleted (-4 bytes vs retail). A bail can
                    # never do that.
                    if val in tags:
                        safe = False
                        break
                    offv = int(off, 0)
                    lo = f"%lo({sym})" if offv == 0 else f"%lo({sym}+{offv})"
                    accesses.append((k, f"{op}\t{val},{lo}({base})", base,
                                     derivs.get(base)))
                    folded_base = base
                    # LEAD 2 guard #6 (NO REWRITE-BRANCH BYPASS): fall THROUGH to the
                    # untag / value-use logic below instead of `continue`-ing past it,
                    # so an access can no longer hide a use of a tagged register from
                    # every downstream guard. The base register itself is excluded from
                    # the value-use test below (`folded_base`) -- it is the one mention
                    # this pass just authorised.
                ma = re.match(r"^addu\t(\$\w+),(\$\w+),(\$\w+)$", ck)
                if ma:
                    X, A, B = ma.groups()
                    if (A in tags) ^ (B in tags):
                        if A in call_crossed or B in call_crossed:
                            safe = False
                            break
                        tags[X] = True  # base + runtime index -> foldable indexed base
                        derivs[X] = deriv_seq   # guard #5: a NEW derivation instance
                        deriv_seq += 1
                        k += 1
                        continue
                    if (A in tags) and (B in tags):
                        safe = False
                        break
                # untag a tagged reg overwritten as a destination. Loads count when
                # they are not themselves an access through a tagged base, e.g. a
                # callee-saved restore after the folded stores.
                #
                # LEAD 2 guard #6: operand 1 is only a DESTINATION for mnemonics that
                # write it. `bgez $3,$L1` reads $3; treating it as a write untagged a
                # live base and produced repro/b.s. Unlisted mnemonics keep the old
                # reading, and anything that merely reads a tagged reg now reaches the
                # value-use bail below instead of silently dropping the tag.
                # The `mm.group(4) not in tags` clause stays: an access THROUGH a
                # tagged base can no longer reach here with a tagged value operand
                # (that bails above), so there is never a tag to retire, and
                # retiring one would not be subtractive (see func_8004A658).
                mnem0 = ck.split("\t", 1)[0]
                wd = re.match(r"^[a-z][a-z0-9.]*\t(\$\w+)", ck)
                dest = None
                if wd and mm is None and mnem0 not in first_operand_is_source \
                        and mnem0 not in store_mnemonics:
                    dest = wd.group(1)
                elif mm and mm.group(1) in load_mnemonics and mm.group(4) not in tags:
                    dest = mm.group(2)
                if dest in tags and not (mm and mm.group(1) in store_mnemonics):
                    if dest == R and tags.get(R) is False:
                        # A raw %hi base restored/reused later means gcc spent a materialised
                        # pointer. The only verified F3 exception is the return-value copy in
                        # the epilogue (`move $v0,$s0`) after all folded accesses are done.
                        r_reused = not epilogue_return_copy(k, R)
                    tags.pop(dest, None)
                    derivs.pop(dest, None)
                    call_crossed.discard(dest)
                if re.match(r"^jalr?(?:\t|\s)", ck):
                    call_crossed.update(tags)
                # any remaining mention of a tagged reg is a value-use -> unsafe.
                # On a folded-access line the BASE register is precisely the mention
                # this pass just authorised, so it is excluded; the store-VALUE read
                # was vetted above and a load destination was untagged just now.
                if any(mentions(ck, t) for t in tags if t != folded_base):
                    safe = False
                    break
                if folded_base is not None:
                    # Guard #6: the registers still carrying the %hi-only value at
                    # the moment this access retires. A folded access can no longer
                    # overwrite a carrier (that bails above), so this is simply the
                    # live tag set.
                    carriers_at_last = set(tags)
                k += 1
            # Shared-register provenance guard (see func_8004AE68): only fold when the
            # 2+ accesses all derive from the SAME base register — i.e. one indexed base
            # reused for multiple field offsets (func_8004A8D8/func_8003E188). Two
            # INDEPENDENT single-use derivations off one shared %hi base (each addu into a
            # distinct reg, each accessed once) are NOT folded by retail: it materialises
            # the full base ONCE (keeps the addiu) and uses 0-offset loads. Dropping the
            # addiu is only correct if EVERY access through the %hi base gets the %lo folded
            # in, which the single-shared-base pattern guarantees.
            #
            # LEAD 2 guard #5 (DERIVATION IDENTITY, func_80953300 — town, 2.7.2-cdk-G0):
            # the register-NAME test above is not the property the paragraph describes.
            # gcc routinely re-uses ONE scratch register for two independent derivations
            # off the same %hi base::
            #
            #     lui   $5,%hi(SYM) ; addiu $5,$5,%lo(SYM)
            #     sll   $3,$16,1 ; addu $3,$3,$5 ; sh $4,0($3)   <- derivation A
            #     sll   $3,$6,1  ; addu $3,$3,$5 ; sh $4,0($3)   <- derivation B
            #
            # `base_regs` is {$3} for BOTH, so the name test passed and the addiu was
            # dropped — but this is the func_8004AE68 shape, only spelled with one
            # register instead of two, and retail keeps the addiu with 0-offset stores
            # (retail word 34 `addiu a1,a1,%lo(D_80024308)`; genuine ASPSX 2.67/2.77/
            # 2.79/2.86 all keep it too — work/debt_20260803/maspsx_leads/func_80953300).
            # So key the guard on WHICH `addu` produced the base, not on its name.
            # Strictly SUBTRACTIVE: it can only decline folds, never create one.
            base_regs = {b for (_, _, b, _) in accesses}
            deriv_ids = {d for (_, _, _, d) in accesses}
            one_base = len(base_regs) == 1 and len(deriv_ids) == 1
            if safe and not r_reused and len(accesses) >= 2 and one_base:
                # LEAD 2 guards #4/#6: only checked once the fold would otherwise
                # happen, so the scan cost is paid only on real fold sites.
                last_k = max(a[0] for a in accesses)
                if not base_is_dead_after(i, last_k, carriers_at_last):
                    safe = False
                elif joins_from_outside(i, last_k, labels_crossed):
                    safe = False
            if safe and not r_reused and len(accesses) >= 2 and one_base:
                for idx, newline, _, _ in accesses:
                    res[idx] = newline
                res[addiu_i] = "# " + code(res[addiu_i]) + "  # maspsx: %lo folded into accesses"
            i += 1
        return res

    def _fold_selfinc_la(self, res):
        """LEAD 4: fold `%lo(SYM+off)` into the accesses of a loop-invariant `%hi`
        base that is self-incremented by a constant stride each iteration.

        A struct-array scan keeps `%hi(SYM)` as a loop-invariant base, folds
        `%lo(SYM+off)` into each field access, and self-increments that SAME base by
        `sizeof(entry)` each lap::

            lui   $3,%hi(SYM)          # base, %hi only
          .L:
            lh    $2,%lo(SYM)($3)      # field a
            lh    $2,%lo(SYM+2)($3)    # field b
            ...
            addiu $3,$3,4              # self-increment (one entry)

        gcc emits a `la $R,SYM` (a macro `as` later expands to a full lui+addiu
        pointer) with 0-offset numeric accesses and a raw `addu $R,$R,STRIDE`
        self-increment; no pinned gcc reproduces retail's folded shape (see
        func_8004A6C0). `_fold_lo_into_accesses` cannot help: (a) maspsx leaves the
        seed as a `la` (it never expands to the `lui`/`addiu` pair that pass looks
        for), and (b) that pass only folds through a register-register `addu`
        index-combine, never through a loop-carried self-increment.

        Fires only when, across $R's whole live range, EVERY use of $R is either a
        memory-access with $R as the base OR a constant self-increment
        `(addu|addiu) $R,$R,IMM` (and at least one access and one self-increment are
        present). It then rewrites the `la` to a bare `lui $R,%hi(SYM)` and folds
        `%lo(SYM+off)` into every access. Arithmetically identical: the base carries
        only `%hi`, `%lo` moves into the displacement, and the constant stride
        applies equally to a `%hi`-only base.

        Conservative / live-range-bound:
          * skips function symbols (handled by `_split_funcaddr_la`) and
            KNOWN small-data symbols (`0 < .extern size <= -G`; those go via `$gp`,
            no %lo to fold). Unknown-size symbols are `%hi/%lo` per `as` and fold.
          * a plain redefinition of $R (a write in which $R is not read) ends the
            live range safely and the collected accesses are used.
          * ANY other mention of $R (value-use, indexed advance `addu $R,$R,$reg`,
            storing $R as data, `move`, arithmetic, a branch/jump operand) aborts
            the fold for that seed.
          * if a call is crossed before a later use of $R, abort. This pass rewrites
            a full pointer into a %hi-only base; retail keeps the materialized
            pointer for call-separated loop seeds such as func_8004AB7C.
        See func_8004A6C0.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def is_known_small_data(sym):
            base = sym.split("+")[0]
            size = self.extern_sizes.get(base, 0)
            return 0 < size <= self.sdata_limit

        i = 0
        while i < len(res):
            m_la = re.match(r"^la\t(\$\w+),([A-Za-z_.][\w.]*)$", C(i))
            if not m_la:
                i += 1
                continue
            R, sym = m_la.group(1), m_la.group(2)
            if self._is_func_symbol(sym) or is_known_small_data(sym):
                i += 1
                continue

            reg_pat = re.compile(r"(?<![\w$])" + re.escape(R) + r"(?![\w])")
            selfinc_re = re.compile(
                r"^(addu|addiu)\t" + re.escape(R) + r"," + re.escape(R)
                + r",(-?(?:0x)?[0-9a-fA-F]+)$"
            )
            accesses = []
            has_selfinc = False
            safe = True
            call_crossed = False
            # LEAD 4 guard #6: has ANY label or branch/jump been crossed since the
            # seed `la`? Case (c) below ends the live range on a plain redefinition,
            # which is only sound when nothing can jump AROUND that redefinition.
            fenced = False
            k = i + 1
            while k < len(res):
                ck = C(k)
                # stop at a function boundary — a base never lives across functions
                if ck.startswith(".end") or ck.startswith(".ent") \
                        or ck.startswith(".section") or ck.startswith("glabel") \
                        or re.match(r"^func_[0-9A-Fa-f]+:", ck):
                    break
                if ck == "" or ck.startswith("#") or ck.startswith(".") \
                        or ck.endswith(":") or ck.startswith("$L"):
                    if ck.endswith(":") or ck.startswith("$L"):
                        fenced = True
                    k += 1
                    continue
                is_call = re.match(r"^jalr?(?:\t|\s)", ck) is not None
                if not reg_pat.search(ck):
                    if is_call:
                        call_crossed = True
                    if re.match(r"^(j|jr|jal|b)", ck.split("\t", 1)[0]):
                        fenced = True
                    k += 1
                    continue
                if is_call:
                    safe = False
                    break
                # (a) memory access with R as the BASE register -> foldable
                mm = re.match(
                    r"^([a-z][a-z0-9]*)\t(\$\w+),(-?(?:0x)?[0-9a-fA-F]+)\((\$\w+)\)$",
                    ck,
                )
                if mm and mm.group(4) == R and (
                    mm.group(1) in load_mnemonics or mm.group(1) in store_mnemonics
                ):
                    if call_crossed:
                        safe = False
                        break
                    op, val, off, base = mm.groups()
                    if val == R:  # R is also the value operand (e.g. sw $R,0($R))
                        safe = False
                        break
                    offv = int(off, 0)
                    lo = f"%lo({sym})" if offv == 0 else f"%lo({sym}+{offv})"
                    accesses.append((k, f"{op}\t{val},{lo}({base})"))
                    k += 1
                    continue
                # (b) constant self-increment of R -> keep, continues the live range
                if selfinc_re.match(ck):
                    if call_crossed:
                        safe = False
                        break
                    has_selfinc = True
                    k += 1
                    continue
                # (c) plain redefinition (R written, not read) -> live range ends
                parts = ck.split("\t", 1)
                op0 = parts[0]
                opnds = [o.strip() for o in parts[1].split(",")] if len(parts) > 1 else []
                positions = [idx for idx, o in enumerate(opnds) if reg_pat.search(o)]
                if positions == [0] and op0 not in store_mnemonics \
                        and op0 not in first_operand_is_source \
                        and not re.match(r"^(j|jr|jal|b)", op0):
                    # LEAD 4 guard #6 (LABEL/BRANCH-AWARE LIVE RANGE): "a plain
                    # redefinition ends the live range" is LINEAR reasoning. If any
                    # label or branch/jump has been crossed since the seed `la`, a
                    # path can skip this redefinition and reach a later numeric-offset
                    # read of $R, which by then holds the %hi-ONLY base this pass
                    # installed -- repro/e.s (`lw $3,0($10)` is jumped around by
                    # `bgez $5,$L1`, and `lh $8,2($3)` at $L1 is left numeric while
                    # the `la` has already been rewritten to a bare `lui`). Only a
                    # straight-line redefinition proves the range is over.
                    if not fenced:
                        break
                    safe = False
                    break
                # (d) anything else mentioning R -> value use, abort
                safe = False
                break

            if safe and has_selfinc and len(accesses) >= 1:
                for idx, newline in accesses:
                    res[idx] = newline
                res[i] = f"lui\t{R},%hi({sym})"
            i += 1
        return res

    def _sink_call_separated_la(self, res):
        """LEAD 15 correction: gcc can emit a loop seed `la $sN,SYM` before a call,
        with the first real use of `$sN` in the loop immediately after that call.

        GNU `as` expands the leftover `la` in place (`lui/addiu` before the call).
        Retail ASPSX output for func_8004AB7C instead leaves the call-adjacent work
        first, then materializes the loop seed after the call delay slot using the
        first load's `$v0` destination as the macro scratch:

            la    $17,SYM
            lw    $4,ARG
            jal   callee
            nop
          $L:
            lbu   $2,1($17)

        becomes:

            lw    $4,ARG
            jal   callee
            nop
          $L:
            lui   $2,%hi(SYM)
            addiu $17,$2,%lo(SYM)
            lbu   $2,1($17)

        This is deliberately narrower than a scheduler: only callee-saved `$sN`
        seeds, exactly one crossed call, an unfilled call delay slot, labels only
        between the call and first use, and first use must be a load into `$2`.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def boundary(body):
            return body.startswith(".end") or body.startswith(".ent") \
                or body.startswith(".section") or body.startswith("glabel") \
                or re.match(r"^func_[0-9A-Fa-f]+:", body)

        def ignorable(body):
            return not body or body.startswith("#") or body.startswith(".")

        def label(body):
            return body.endswith(":") or body.startswith("$L")

        def mentions(body, reg):
            return re.search(r"(?<![\w$])" + re.escape(reg) + r"(?![\w])", body) is not None

        def is_callee_saved(reg):
            return reg in {f"${n}" for n in range(16, 24)} | {f"$s{n}" for n in range(8)}

        def is_known_small_data(sym):
            base = sym.split("+")[0]
            size = self.extern_sizes.get(base, 0)
            return 0 < size <= self.sdata_limit

        i = 0
        while i < len(res):
            m = re.match(r"^la\t(\$\w+),([A-Za-z_.][\w.]*)$", C(i))
            if not m:
                i += 1
                continue
            R, sym = m.group(1), m.group(2)
            if self._is_func_symbol(sym) or is_known_small_data(sym) or not is_callee_saved(R):
                i += 1
                continue

            call_i = None
            delay_i = None
            j = i + 1
            while j < len(res):
                cj = C(j)
                if boundary(cj):
                    break
                if ignorable(cj) or label(cj):
                    j += 1
                    continue
                is_call = re.match(r"^jalr?(?:\t|\s)", cj) is not None
                if mentions(cj, R):
                    break
                if is_call:
                    if call_i is not None:
                        break
                    call_i = j
                    q = j + 1
                    while q < len(res) and ignorable(C(q)):
                        q += 1
                    if q >= len(res) or C(q) != "nop":
                        call_i = None
                        break
                    delay_i = q
                j += 1

            if call_i is None or delay_i is None or j >= len(res):
                i += 1
                continue
            use = C(j)
            mm = re.match(
                r"^([a-z][a-z0-9]*)\t(\$2|\$v0),(-?(?:0x)?[0-9a-fA-F]+)\("
                + re.escape(R)
                + r"\)$",
                use,
            )
            if not mm or mm.group(1) not in load_mnemonics:
                i += 1
                continue
            if any(
                (not ignorable(C(k)) and not label(C(k)))
                for k in range(delay_i + 1, j)
            ):
                i += 1
                continue

            insert_at = j
            for k in range(delay_i + 1, j):
                if label(C(k)):
                    insert_at = k
                    break

            scratch = mm.group(2)
            res.pop(i)
            if i < insert_at:
                insert_at -= 1
            res[insert_at:insert_at] = [
                f"lui\t{scratch},%hi({sym})",
                f"addiu\t{R},{scratch},%lo({sym})",
            ]
            i = insert_at + 2
        return res

    def _expand_smalldata_la(self, res):
        """When `la` is NOT gp-relativizable in ASPSX (`gp_allow_la` False, i.e.
        aspsx<2.80 — the pinned PSYQ 4.0 / aspsx-2.56), a bare `la $R,SYM` macro
        for a small-data symbol must be materialised as an explicit `%hi/%lo` pair
        BEFORE it reaches `as`.

        Genuine ASPSX 2.56 never `$gp`-relativizes a `la` macro, so it always emits
        `lui $R,%hi(SYM); addiu $R,$R,%lo(SYM)` for an address-load — even of a
        small (<=8B) global. maspsx models `gp_allow_la=False` by leaving the `la`
        line UNTOUCHED (see `_process`, the `if op == "la" and not self.gp_allow_la`
        branch falls through to a bare `res.append(line)`), assuming the downstream
        assembler will not gp-optimize it either. But our `mipsel-linux-gnu-as -G8`
        independently re-applies ITS OWN small-data optimization to that passed-
        through bare `la` (using the same `.extern SYM,SIZE` hint), silently turning
        a 2-word %hi/%lo address-load into a 1-word `$gp` form that real ASPSX never
        produced.

        This bites any function that BOTH stores to a small global AND takes its
        address: the store must gp-relativize (`sw $v0,%gp_rel(SYM)($gp)`, correct
        for size<=8) while the `return &SYM` / address-load must stay `lui;addiu`
        (retail keeps the two split for the SAME symbol). No single declared symbol
        size can produce that mix — `as` treats a symbol's `sw` and `la` uniformly.
        See func_80047D44 (`D_8008152C`): store gp_rel, `&D_8008152C` %hi/%lo.

        Fires only when `gp_allow_la` is False and SYM is a KNOWN small-data symbol
        (`0 < .extern size <= -G`), and NEVER for function symbols (handled by
        `_split_funcaddr_la`) or non-small-data symbols (`as` already emits %hi/%lo
        for those; no change). Runs LAST, after every other `la`-consuming post-pass
        (`_fold_selfinc_la`, `_split_funcaddr_la`), so only genuine leftover bare
        small-data `la`s remain. A `la` sitting in a jump/branch delay slot is
        left untouched (a 1->2 insn rewrite there would corrupt the slot).

        No-op on all currently-matched functions: real ASPSX never gp-relativizes a
        `la`, so any matched function with such a `la` already carries the %hi/%lo
        pair in retail; a bare (as-gp-relativized, 1-word) `la` could not have
        matched retail, hence none exist to be affected.
        """
        if self.gp_allow_la:
            return res

        def C(i):
            return strip_comments(res[i]).strip()

        def is_known_small_data(sym):
            base = sym.split("+")[0]
            size = self.extern_sizes.get(base, 0)
            return 0 < size <= self.sdata_limit

        JUMPS = {"j", "jr", "jal", "jalr"}

        def in_delay_slot(i):
            # A `la` in a jump/branch delay slot must stay a single instruction:
            # expanding it to lui+addiu would push a second insn into the slot and
            # shift every following byte. `break` is not a branch despite the prefix.
            for k in range(i - 1, -1, -1):
                body = C(k)
                if not body or body.endswith(":") or body.startswith("."):
                    continue
                op = body.split(None, 1)[0]
                return op in JUMPS or (op.startswith("b") and op != "break")
            return False

        out = []
        for i in range(len(res)):
            m = re.match(r"^la\t(\$\w+),([A-Za-z_.][\w.]*(?:\+\d+)?)$", C(i))
            if (
                m
                and not self._is_func_symbol(m.group(2))
                and is_known_small_data(m.group(2))
                and not in_delay_slot(i)
            ):
                R, sym = m.group(1), m.group(2)
                out.append(f"lui\t{R},%hi({sym})")
                out.append(f"addiu\t{R},{R},%lo({sym})")
            else:
                out.append(res[i])
        return out

    @staticmethod
    def _instr_mentions_reg(line: str, reg: str) -> bool:
        """True if `reg` (e.g. "$4") appears as an operand token of the instruction.
        Conservative: any read OR write of the register counts, so it acts as a
        movement barrier. Directives/labels/comments never mention a register."""
        body = strip_comments(line).strip()
        m = re.match(r"^([A-Za-z][\w.]*)\s+(.*)$", body)
        if not m:
            return False
        operands = m.group(2)
        return re.search(r"(?<![\w$])" + re.escape(reg) + r"(?![\w])", operands) is not None

    def _is_func_symbol(self, symbol: str) -> bool:
        """A text-segment (function) symbol. Function addresses are never in the
        $gp small-data window, so `la $R,FUNC` must be materialised via %hi/%lo —
        but gcc emits no `.extern FUNC,SIZE` for functions, so the data size-gate
        never classifies them. Recognise them by the project naming convention
        (`func_########`) or by being a `jal` target seen in this unit."""
        symbol = symbol.split("+")[0]
        if re.match(r"^func_[0-9A-Fa-f]{8}$", symbol):
            return True
        return symbol in getattr(self, "_jal_targets", ())

    def _split_funcaddr_la(self, res):
        """ASPSX splits a `la $R,FUNC` that supplies a function-address argument to a
        following `jal`: the `lui $R,%hi(FUNC)` is hoisted up to right after the
        frame prologue and the `addiu $R,$R,%lo(FUNC)` tail is scheduled into the
        jal's (otherwise-empty) delay slot::

            addiu sp,sp,-N
            lw    $2,D_BIG            # unrelated setup gcc scheduled before the call
            la    $4,func_XXXX        # gcc: plain la (lui+addiu), nop in jal delay
            sw    $31,K(sp)
            sw    $2,D_BIG2
            jal   func_YYYY
            nop                       # empty delay slot

        becomes::

            addiu sp,sp,-N
            lui   $4,%hi(func_XXXX)   # hoisted to just after the prologue
            lw    $2,D_BIG
            sw    $31,K(sp)
            sw    $2,D_BIG2
            jal   func_YYYY
            addiu $4,$4,%lo(func_XXXX)  # %lo tail in the delay slot

        No gcc version/flags reproduce this: extern function symbols carry no
        `.extern SIZE`, so the size-gate that drives the data-address delay-fill
        (`_expand_store_to_symbol_in_delay`) never fires for a func address.

        Tightly guarded — only fires when, in one straight-line basic block:
          * `la $R,FUNC` with FUNC a function symbol (naming convention / jal target),
          * a following `jal` reaches without $R being read/written in between and
            without any intervening label / branch / other jump,
          * that jal's delay slot is an unfilled `nop`,
          * a frame prologue (`addiu/subu $sp,$sp,-N`) precedes the la.
        The lui is hoisted only across instructions that don't touch $R (stopping at
        the prologue), so it is arithmetically identical. See func_80041AB0,
        func_80043CD0.

        LEAD 36: the hoist stops one instruction SHORT of a preceding branch/jump,
        because the first instruction after a branch is that branch's delay slot and
        the hoisted `lui` must not displace whatever the scheduler already put there.
        See `_branch_delay_safe_hoist_dest` and func_818D4E68.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def immediate_consuming_jal(la_i):
            """Return true when jal is the next real instruction after la."""
            next_i = la_i + 1
            while next_i < len(res):
                candidate = C(next_i)
                if candidate == "" or candidate.startswith("#"):
                    next_i += 1
                    continue
                if candidate.endswith(":") or candidate.startswith("glabel"):
                    return False
                if candidate.startswith("."):
                    next_i += 1
                    continue
                return re.match(r"^jal\t\S+$", candidate) is not None
            return False

        self._jal_targets = {
            m.group(1)
            for ln in res
            if (m := re.match(r"^jal\t(\S+)$", strip_comments(ln).strip()))
        }

        i = 0
        while i < len(res):
            m_la = re.match(r"^la\t(\$\w+),([A-Za-z_.][\w.]*)$", C(i))
            if not (m_la and self._is_func_symbol(m_la.group(2))):
                i += 1
                continue
            reg, sym = m_la.group(1), m_la.group(2)

            # Genuine ASPSX preserves an adjacent bare function-address load.
            # Existing split witnesses have intervening setup and keep the
            # established behavior.  This exception is default-off and only
            # subtracts an existing rewrite.
            if (self.preserve_immediate_funcaddr_la
                    and immediate_consuming_jal(i)):
                i += 1
                continue

            # scan forward (same basic block) for the jal that consumes the arg
            found = None
            j = i + 1
            while j < len(res):
                cj = C(j)
                if cj == "" or cj.startswith("#"):
                    j += 1
                    continue
                if cj.startswith(".") or cj.endswith(":") or cj.startswith("glabel"):
                    break
                if re.match(r"^jal\t\S+$", cj):
                    found = j
                    break
                if re.match(r"^(j|jr|b\w*)\b", cj):
                    break
                if self._instr_mentions_reg(cj, reg):
                    break
                j += 1
            if found is None:
                i += 1
                continue

            # jal delay slot must be an (unfilled) nop we can repurpose
            d = found + 1
            while d < len(res) and (C(d) == "" or C(d).startswith("#")):
                d += 1
            if d >= len(res) or C(d) != "nop":
                i += 1
                continue

            # hoist target: as far up as safe, stopping right after the frame
            # prologue (addiu/subu $sp,$sp,-N) or at a boundary / an insn touching $R.
            dest = i
            stopped_at_branch = False
            p = i - 1
            while p >= 0:
                cp = C(p)
                if cp == "" or cp.startswith("#"):
                    p -= 1
                    continue
                if cp.startswith(".") or cp.endswith(":") or cp.startswith("glabel"):
                    break
                if re.match(r"^(addiu|subu|addu)\t\$sp,\$sp,", cp):
                    break
                if re.match(r"^(j|jr|jal|b\w*)\b", cp):
                    # `break` matches the walk's `b\w*` barrier but owns no delay
                    # slot, so it must NOT arm the LEAD 36 guard (same distinction
                    # `_expand_smalldata_la`'s in_delay_slot() draws).
                    stopped_at_branch = self._owns_a_delay_slot(cp)
                    break
                if self._instr_mentions_reg(cp, reg):
                    break
                dest = p
                p -= 1

            # LEAD 36 delay-slot guard (see _branch_delay_safe_hoist_dest).
            dest, split_in_place = self._branch_delay_safe_hoist_dest(
                res, i, dest, stopped_at_branch
            )

            if dest == i and not split_in_place:
                # nothing to hoist across (no prologue seen) -> leave untouched
                i += 1
                continue

            # rewrite: %lo tail into the delay slot, drop the la, hoist %hi to `dest`
            res[d] = f"addiu\t{reg},{reg},%lo({sym})"
            res.pop(i)  # dest <= i, so dest and everything above it is unaffected
            res.insert(dest, f"lui\t{reg},%hi({sym})")
            i = dest + 1
        return res

    @staticmethod
    def _owns_a_delay_slot(body: str) -> bool:
        """True when `body` is a control transfer whose NEXT instruction is its
        delay slot.  Mirrors `_expand_smalldata_la`'s in_delay_slot() test: every
        `j*`/`b*` except `break`, which only shares the prefix."""
        body = strip_comments(body).strip()
        if not body or body.endswith(":") or body.startswith("."):
            return False
        op = body.split(None, 1)[0]
        return op in ("j", "jr", "jal", "jalr") or (
            op.startswith("b") and op != "break"
        )

    def _branch_delay_safe_hoist_dest(self, res, la_i, dest, stopped_at_branch):
        """LEAD 36: keep `_split_funcaddr_la`'s hoisted `%hi` out of a delay slot.

        `_split_funcaddr_la` walks BACKWARDS from a `la $R,FUNC` looking for the
        highest safe home for the generated `lui $R,%hi(FUNC)`.  The walk stops on a
        preceding branch/jump -- and, because a stop only ever happens AFTER the
        walk has already accepted every real instruction below it, the surviving
        `dest` is the first real instruction after that branch, i.e. **the branch's
        own delay slot**.  Inserting the `lui` there does not merely place it: it
        DISPLACES the instruction the scheduler had already put in the slot.

        Retail does not do that.  Witness `func_818D4E68` (dungeon, foff 0x18F4E68,
        2.7.2-G0)::

            bne   $2,$0,$L13
            addu  $4,$20,-32          # delay slot, kept by retail
            lui   $5,%hi(func_80045340)
            jal   func_8004491C
            addiu $5,$5,%lo(func_80045340)

        while the un-guarded hoist emitted `bne / lui / addu / jal / addiu`.

        The retired F2 `la`-expansion hoist (removed 2026-09-07 with the main-EXE
        name tables) carried exactly this rule -- "The first hoisted-over load must
        not be a branch delay slot: the lui would take the slot instead" -- but it
        could simply CANCEL, because its hoist was an optional refinement of an
        otherwise-correct whole `la`.  Here the split is
        not optional: cancelling would leave the `la` intact AND the consuming jal's
        delay slot a bare `nop`, which is one word MORE than retail.  So instead of
        cancelling, step the destination one real instruction PAST the delay slot.
        When that step lands back on the `la` itself the pair simply splits in place
        (`lui` where the `la` was, `%lo` still in the jal delay slot) -- the same two
        words the pass already emits, only positioned one instruction lower.

        Correctness is trivially preserved: the new destination is strictly LATER
        than the old one, so the `lui` crosses a subset of the instructions the walk
        had already proved do not mention $R.

        Returns `(dest, split_in_place)`; `split_in_place` is True only when the
        guard collapsed the destination onto the `la`, which is how the caller tells
        that case apart from "no hoist room at all" (which still declines).
        """
        if not stopped_at_branch or dest >= la_i:
            return dest, False
        q = dest + 1
        while q < la_i:
            c = strip_comments(res[q]).strip()
            if c and not c.startswith("#"):
                break
            q += 1
        return q, q >= la_i

    def _prefer_lui_over_sll_branch_delay(self, res):
        """LEAD 11: when a conditional branch can fill its delay slot either with a
        path-local index shift or with the `%hi` half of the taken path's `la`,
        ASPSX prefers the register-independent `lui`.

        gcc emits this found-entry shape:

            bne   $idx,$cmp,$Lfound
            sll   $idx,$idx,3        # delay slot
            j     $Ldone
            move  $v0,$zero
        $Lfound:
            la    $base,SYM
            addu  $idx,$idx,$base

        Retail instead puts `lui $base,%hi(SYM)` in the branch delay slot and
        starts `$Lfound` with the `%lo` tail, then performs the shift. This pass
        only fires on that exact local-control-flow shape; the fallthrough must
        immediately jump away, so the shifted value is used only on the taken path.
        See func_80048224.
        """
        def C(i):
            return strip_comments(res[i]).strip()

        def next_code(i):
            while i < len(res):
                c = C(i)
                if c and not c.startswith("#") and not c.startswith(".") \
                        and not c.endswith(":") and not c.startswith("glabel"):
                    return i
                i += 1
            return len(res)

        def code_until_label(start, label_i):
            out = []
            i = start
            while i < label_i:
                c = C(i)
                if c and not c.startswith("#") and not c.startswith(".") \
                        and not c.endswith(":") and not c.startswith("glabel"):
                    out.append(i)
                i += 1
            return out

        labels = {}
        for i in range(len(res)):
            c = C(i)
            if c.endswith(":"):
                labels[c[:-1]] = i

        i = 0
        while i < len(res):
            m_branch = re.match(r"^(beq|bne)\t(\$\w+),(\$\w+),(\$L[\w.]+)$", C(i))
            if not m_branch:
                i += 1
                continue

            delay_i = next_code(i + 1)
            if delay_i >= len(res):
                i += 1
                continue
            m_sll = re.match(r"^sll\t(\$\w+),(\$\w+),([0-9]+)$", C(delay_i))
            if not (m_sll and m_sll.group(1) == m_sll.group(2)):
                i += 1
                continue
            idx_reg, shift = m_sll.group(1), m_sll.group(3)
            if idx_reg not in (m_branch.group(2), m_branch.group(3)):
                i += 1
                continue

            label = m_branch.group(4)
            label_i = labels.get(label)
            if label_i is None or label_i <= delay_i:
                i += 1
                continue

            found_i = next_code(label_i + 1)
            add_i = next_code(found_i + 1)
            if add_i >= len(res):
                i += 1
                continue
            m_la = re.match(r"^la\t(\$\w+),([A-Za-z_.][\w.]*(?:\+\d+)?)$", C(found_i))
            if not (m_la and not self._is_func_symbol(m_la.group(2))):
                i += 1
                continue
            base_reg, sym = m_la.group(1), m_la.group(2)
            if not (
                re.match(
                    r"^addu\t" + re.escape(idx_reg) + r"," + re.escape(idx_reg)
                    + r"," + re.escape(base_reg) + r"$",
                    C(add_i),
                )
                or re.match(
                    r"^addu\t" + re.escape(idx_reg) + r"," + re.escape(base_reg)
                    + r"," + re.escape(idx_reg) + r"$",
                    C(add_i),
                )
            ):
                i += 1
                continue

            between = code_until_label(delay_i + 1, label_i)
            if len(between) != 2 or not re.match(
                r"^j\t(?!\$(?:[0-9]+|[a-z][a-z0-9]*)$)\S+$",
                C(between[0]),
            ):
                i += 1
                continue
            if line_loads_from_reg(C(between[1]), base_reg):
                i += 1
                continue

            res[delay_i] = f"lui\t{base_reg},%hi({sym})"
            res[found_i] = f"addiu\t{base_reg},{base_reg},%lo({sym})"
            res.insert(add_i, f"sll\t{idx_reg},{idx_reg},{shift}")
            i = add_i + 1
        return res

    def _prefer_marked_target_arg_setup(self, res):
        """Evidence-scoped LEAD 11 target-entry reorder.

        At the opted-in TOWN site gcc has already placed a page ``li`` in the
        conditional branch delay.  The target begins with the matching low-half
        add followed by an independent stack-argument setup; retail emits those
        two target instructions in the opposite order.  The generic corpus is
        mixed, so this pass is disabled unless the current TU explicitly opts in.
        """
        if not self.prefer_target_arg_setup:
            return res
        out = list(res)

        def C(i):
            return strip_comments(out[i]).strip()

        def next_real(i, end):
            while i < end:
                c = C(i)
                if (c and not c.startswith("#") and not c.startswith(".")
                        and not c.endswith(":")):
                    return i
                i += 1
            return end

        labels = {
            C(i)[:-1]: i for i in range(len(out))
            if re.match(r"^\$L[\w.]+:$", C(i))
        }
        for i in range(len(out)):
            branch = re.match(
                r"^(?:beq|bne)\t\$\w+,\$\w+,(\$L[\w.]+)$", C(i)
            )
            if not branch:
                continue
            delay_i = next_real(i + 1, len(out))
            delay = re.match(r"^li\t(\$\w+),(-?(?:0x[0-9a-fA-F]+|\d+))$", C(delay_i))
            if not delay or (int(delay.group(2), 0) & 0xFFFF):
                continue
            label_i = labels.get(branch.group(1))
            if label_i is None or label_i <= delay_i:
                continue
            first = next_real(label_i + 1, len(out))
            second = next_real(first + 1, len(out))
            third = next_real(second + 1, len(out))
            base = re.escape(delay.group(1))
            if not re.match(
                rf"^(?:addu|addiu)\t{base},{base},-?(?:0x[0-9a-fA-F]+|\d+)$",
                C(first),
            ):
                continue
            if not re.match(r"^(?:addu|addiu)\t\$4,\$sp,(?:0x[0-9a-fA-F]+|\d+)$", C(second)):
                continue
            if not re.match(rf"^addu\t\$5,{base},\$zero$", C(third)):
                continue
            out[first], out[second] = out[second], out[first]
        return out

    def _hoist_delay_luis(self, res):
        """ASPSX hoists the `lui $R,%hi(SYM)` generated for a store scheduled into a
        following (j/jal) delay slot ABOVE an immediately-preceding stack save.

        gcc 2.7.2 emits the bare store macro after the `sw $ra,K($sp)` save, so the
        store-into-delay expansion lands the generated lui right after the save::

            sw	$31,16($sp)
            lui	$2,%hi(D_X)      # generated
            jal	func
            sh	$4,%lo(D_X)($2)  # delay slot

        Retail places the lui before the save (`addiu sp; lui; sw $ra; jal; sh`).
        Swap the two lines when the lui feeds a %lo(SYM) access in the following
        jump's delay slot (leaf return-store cases have no preceding save, so are
        untouched). See func_80053DCC.
        """
        i = 0
        while i + 3 < len(res):
            a = strip_comments(res[i]).strip()
            b = strip_comments(res[i + 1]).strip()
            c = strip_comments(res[i + 2]).strip()
            d = strip_comments(res[i + 3]).strip()
            m_sw = re.match(r"^s[whb]\t(\$\w+),[^,]*\(\$sp\)$", a)
            m_lui = re.match(r"^lui\t(\$\w+),%hi\(([^)]+)\)", b)
            if (
                m_sw
                and m_lui
                and re.match(r"^(j|jr|jal)\b", c)
                and m_sw.group(1) != m_lui.group(1)   # save doesn't source the lui reg
                and f"({m_lui.group(1)})" in d         # delay slot uses the lui reg
                and "%lo(" in d
            ):
                res[i], res[i + 1] = res[i + 1], res[i]  # hoist lui above the stack save
                i += 2
                continue
            i += 1
        return res


    def _maybe_unfill_return_delay(self, line: str):
        """Replicate ASPSX/retail leaving the stack-pointer restore BEFORE a return
        jump (with a nop in the delay slot) rather than in the delay slot itself.

        gcc >= 2.8's delayed-branch pass fills the `j $31` / `jr $ra` delay slot with
        the `addu $sp,$sp,+N` frame teardown::

            j	$31
            addu	$sp,$sp,24   # delay slot (gcc-filled, under .set noreorder)

        But the retail binary only does this for leaf-ish functions restoring a single
        callee-saved reg ($ra). When 2+ callee-saved regs are restored it leaves the
        teardown before the jump with an unfilled (nop) delay slot::

            addu	$sp,$sp,24
            j	$31
            nop

        Empirically consistent across the whole game: 2+ callee-saved restored ->
        0 filled / 382 unfilled; every filled-with-sp-restore case restores exactly 1.
        Only fires in gcc-scheduled (noreorder) regions; a no-op on 2.7.2 (which already
        leaves it unfilled at >=2 restores) and on non-sp delay fills. Returns the
        replacement lines, or None when not applicable.
        """
        if self.is_reorder:
            return None  # only when gcc explicitly scheduled the delay slot
        if self.callee_restores < 2:
            return None
        if not re.match(r"^(j|jr)\t\$(31|ra)$", strip_comments(line)):
            return None
        nxt = strip_comments(self.get_next_instruction(ignore_nop=True, ignore_set=True))
        if not re.match(r"^add[i]?u\t\$sp,\$sp,(\d+|0x[0-9A-Fa-f]+)$", nxt):
            return None
        # hoist the sp-restore ahead of the jump; leave a nop in the delay slot
        self.skip_instructions = 1
        return [nxt, line, "nop\t# maspsx: un-filled return delay (2+ callee-saved)"]

    def process_line(self, line: str):
        res = []

        if len(line) == 0:
            return [line]

        if line.startswith("#"):
            # LEAD 27/28/30: keep the slot pin markers (page-base, dead-value and
            # jal-delay-store families) so the sink/rotate post-passes can key on
            # them; every other comment is dropped as before. A marker is a bare
            # `#`-comment, harmless (no-op) to GNU as if it is ever left behind, so
            # preserving it is byte-neutral.
            if (PAGEBASE_PIN_MARKER in line or TAILSLOT_PIN_MARKER in line
                    or LIVE_SIBCALL_PIN_MARKER in line
                    or SHAPE_D_PIN_MARKER in line
                    or JALDELAY_PIN_MARKER in line
                    or BRANCH_LABEL_SPLIT_MARKER in line):
                return [line]
            return []

        if line.startswith("."):
            if (
                line.startswith(".def\t")
                or line.startswith(".begin\t")
                or line.startswith(".bend\t")
            ):
                # skip these coff directives - gnu as does not like them
                pass

            elif line.startswith(".set\t"):
                if line.endswith("\tnoreorder"):
                    self.is_reorder = False
                elif line.endswith("\treorder"):
                    self.is_reorder = True

            elif line.startswith(".file\t"):
                # fix same-numbered files
                _, file_num, filename = line.split(maxsplit=2)
                res.append(f".file\t{self.file_num} {filename}")
                self.file_num += 1

            elif line.startswith(".ent\t"):
                # enforce noreorder for each function
                res.append(line)
                res.append(".set\tnoreorder")

            elif line.startswith(".comm") or line.startswith(".lcomm"):
                # already handled via preprocess_lines
                pass

            elif line.startswith(".data"):
                res.append(".section .data")
            elif line.startswith(".sdata"):
                res.append(".section .sdata")
            elif line.startswith(".rdata"):
                res.append(".section .rodata")

            else:
                res.append(line)

            return res

        if line.startswith("$L"):
            return [line]

        actual_r_dest = None
        is_macro = ";" in line
        if is_macro:
            expanded = expand_macro(line)
            if len(expanded) > 0:
                actual_op, *actual_rest = expanded[-1]
                if actual_op in load_mnemonics:
                    _, actual_r_dest, _, _, _ = parse_load_or_store(
                        " ".join(actual_rest)
                    )

        op, *rest = line.split()

        # LEAD 1: un-fill the sp-restore from a return-jump delay slot (matches retail/ASPSX).
        unfilled = self._maybe_unfill_return_delay(line)
        if unfilled is not None:
            return unfilled

        if op in load_mnemonics:
            r_source, r_dest, operand, is_addend, needs_expanding = parse_load_or_store(
                " ".join(rest)
            )

            next_instruction = self.get_next_instruction(
                skip=0, ignore_nop=True, ignore_set=True, ignore_label=True
            )
            # Naively handle scenario where *next* line is a macro
            if ";" in next_instruction:
                next_instruction = next_instruction.split(";")[0]

            if not needs_expanding:
                # newer GCCs can emit %hi() and %lo() separately...
                res.append(f"{line} # DEBUG: leaving for assembler to expand")
                extra_nops = self._handle_nop_before_next_instruction(
                    next_instruction, r_dest
                )
                res.extend(extra_nops)

            elif is_addend and r_source is None:
                # e.g. lb	$s0,D_800E52E0
                if operand.count("+") == 1:
                    symbol, offset = operand.split("+")
                    gp_rel = f"%gp_rel({symbol}+{offset})($gp)"
                    gp_allowed = self.gp_allow_offset or symbol not in self.comm_symbols
                else:
                    symbol = operand
                    gp_rel = f"%gp_rel({symbol})($gp)"
                    gp_allowed = True

                if gp_allowed and (
                    symbol in self.sdata_entries or symbol in self.sbss_entries
                ):
                    res.append(f"{op}\t{r_dest},{gp_rel}")
                else:
                    res.append(line)

                extra_nops = self._handle_nop_before_next_instruction(
                    next_instruction, r_dest
                )
                res.extend(extra_nops)

            elif is_addend and r_source:
                # e.g. lw	$2,test_sym($4)
                if self.addiu_at:
                    res.extend(
                        [
                            "# EXPAND_AT START",
                            ".set\tnoat",
                            f"lui\t$at,%hi({operand})",
                            f"addiu\t$at,$at,%lo({operand})",
                            f"addu\t$at,$at,{r_source}",
                            f"{op}\t{r_dest},0x0($at)",
                            ".set\tat",
                            "# EXPAND_AT END",
                        ]
                    )
                else:
                    res.extend(
                        [
                            "# EXPAND_AT START",
                            ".set\tnoat",
                            f"lui\t$at,%hi({operand})",
                            f"addu\t$at,$at,{r_source}",
                            f"{op}\t{r_dest},%lo({operand})($at)",
                            ".set\tat",
                            "# EXPAND_AT END",
                        ]
                    )

                extra_nops = self._handle_nop_before_next_instruction(
                    next_instruction, r_dest
                )
                res.extend(extra_nops)

            else:
                if r_source and (int(operand, 0) > 32767 or int(operand, 0) < -32768):
                    # e.g. lhu	$2,49344($2)
                    res.extend(
                        [
                            "# EXPAND_AT START",
                            ".set\tnoat",
                            f"lui\t$at,%hi({operand})",
                            f"addu\t$at,{r_source},$at",
                            f"{op}\t{r_dest},%lo({operand})($at)",
                            ".set\tat",
                            "# EXPAND_AT END",
                        ]
                    )
                else:
                    # e.g. lhu	$2,528482304
                    res.append(line)

                # Naively handle scenario where *current* line is a macro
                if actual_r_dest is not None:
                    r_dest = actual_r_dest

                extra_nops = self._handle_nop_before_next_instruction(
                    next_instruction, r_dest
                )
                res.extend(extra_nops)

        elif op in unaligned_load_mnemonics and len(rest) == 1 and re.match(
            r"^\$\w+,-?(?:0x)?[0-9a-fA-F]+\(\$\w+\)$", rest[0]
        ):
            # LEAD 29 (func_80E65598): an unaligned-load macro in the plain
            # `reg,off(reg)` form. Emit it unchanged (GNU `as` expands it to the same
            # lwl/lwr pair genuine ASPSX emits) but give its DESTINATION the load-delay
            # slot every other load gets. Deliberately narrow: only the numeric-offset
            # register-base form — a symbol/addend operand would need the $at/%gp_rel
            # expansion machinery above and has no retail witness, so it keeps falling
            # through to the pass-through `else` below, exactly as before.
            r_dest = rest[0].split(",", 1)[0]
            next_instruction = self.get_next_instruction(
                skip=0, ignore_nop=True, ignore_set=True, ignore_label=True
            )
            if ";" in next_instruction:
                next_instruction = next_instruction.split(";")[0]
            res.append(line)
            res.extend(
                self._handle_nop_before_next_instruction(next_instruction, r_dest)
            )

        elif op in store_mnemonics or (op == "la" and self.sdata_limit > 0):
            r_source, r_dest, operand, is_addend, _ = parse_load_or_store(
                " ".join(rest)
            )

            if is_addend and r_source is None:
                # e.g. sw	$v0,D_800E52E0
                if operand.count("+") == 1:
                    symbol, offset = operand.split("+")
                    gp_rel = f"%gp_rel({symbol}+{offset})($gp)"
                    gp_allowed = self.gp_allow_offset or symbol not in self.comm_symbols
                else:
                    symbol = operand
                    gp_rel = f"%gp_rel({symbol})($gp)"
                    gp_allowed = True

                if op == "la" and not self.gp_allow_la:
                    gp_allowed = False

                if gp_allowed and (
                    symbol in self.sdata_entries or symbol in self.sbss_entries
                ):
                    res.append(f"{op}\t{r_dest},{gp_rel}")
                elif delayed := self._expand_store_to_symbol_in_delay(
                    op, r_dest, operand
                ):
                    res.extend(delayed)
                else:
                    res.append(line)
            elif is_addend and r_source:
                # e.g. sw	$a0,ctlbuf($v0)
                if self.addiu_at and op != "la":
                    res.extend(
                        [
                            "# EXPAND_AT START",
                            ".set\tnoat",
                            f"lui\t$at,%hi({operand})",
                            f"addiu\t$at,$at,%lo({operand})",
                            f"addu\t$at,$at,{r_source}",
                            f"{op}\t{r_dest},0x0($at)",
                            ".set\tat",
                            "# EXPAND_AT END",
                        ]
                    )
                else:
                    res.append(line)
            elif r_source and (int(operand, 0) > 32767 or int(operand, 0) < -32768):
                # e.g. sw	$2,56200($4)
                res.extend(
                    [
                        "# EXPAND_AT START",
                        ".set\tnoat",
                        f"lui\t$at,%hi({operand})",
                        f"addu\t$at,{r_source},$at",
                        f"{op}\t{r_dest},%lo({operand})($at)",
                        ".set\tat",
                        "# EXPAND_AT END",
                    ]
                )
            else:
                res.append(line)

        elif op in branch_mnemonics or op in jump_mnemonics:
            res.append(line)
            if self.is_reorder:
                res.append("nop  # DEBUG: branch/jump")

        elif op == "move":
            # expand move $2,$16 to addu $2,$16,$zero
            res.append(expand_move(line))

        elif op in ("addu", "subu", "sra", "srl", "srr", "sll", "or"):
            # no extra processing required
            res.append(line)
            # TODO: check if this line is a macro and insert a nop if required...

        elif op == "li":
            # TODO: handle non-soft floats?
            if self.expand_li:
                res += expand_load_immediate(line)
            else:
                res.append(line)

        elif op == "li.s":
            res += load_immediate_single(line)

        elif op == "li.d":
            res += load_immediate_double(line)

        elif op in ("mflo", "mfhi"):
            res.append(line)
            res += self._handle_mflo_mfhi()

        elif op == "break":
            # turn 'break 7' into 'break 0x0,0x7'
            num = int(rest[0], 0)
            line = f"break\t0x{num >> 10:X},0x{num & 0x3FF:X}"
            res.append(line)

        elif op in ("div", "rem"):
            r_dest, r_source, r_operand = rest[0].split(",")
            if r_dest in ("$zero", "$0"):
                # e.g. div $zero, $v0, $a0
                return [line]

            move_from = "mfhi" if op == "rem" else "mflo"
            if self.expand_div:
                res.extend(
                    [
                        "# EXPAND_DIV START",
                        ".set\tnoat",
                        f"div\t$zero,{r_source},{r_operand}",
                        f"bnez\t{r_operand},.L_NOT_DIV_BY_ZERO_{self.line_index}",
                        "nop",
                        "break\t0x7",
                        f".L_NOT_DIV_BY_ZERO_{self.line_index}:",
                        "addiu\t$at,$zero,-1",
                        f"bne\t{r_operand},$at,.L_DIV_BY_POSITIVE_SIGN_{self.line_index}",
                        "lui\t$at,0x8000",
                        f"bne\t{r_source},$at,.L_DIV_BY_POSITIVE_SIGN_{self.line_index}",
                        "nop",
                        "tge\t$zero,$zero,93" if self.div_uses_tge else "break\t0x6",
                        f".L_DIV_BY_POSITIVE_SIGN_{self.line_index}:",
                        f"{move_from}\t{r_dest}",
                        ".set\tat",
                        "# EXPAND_DIV END",
                    ]
                )
            else:
                res.extend(
                    [
                        "# EXPAND_ZERO_DIV START",
                        f"div\t$zero,{r_source},{r_operand}",
                        f"{move_from}\t{r_dest}",
                        "# EXPAND_ZERO_DIV END",
                    ]
                )

            extra_nops = self._handle_mflo_mfhi(r_source=r_dest)
            if len(extra_nops) > 0:
                res += extra_nops
            else:
                next_instruction = self.get_next_instruction(
                    skip=0, ignore_set=True, ignore_label=True
                )
                extra_nops = self._handle_nop_before_next_instruction(
                    next_instruction, r_dest
                )
                res.extend(extra_nops)

        elif op in ("divu", "remu"):
            r_dest, r_source, r_operand = rest[0].split(",")
            if r_dest in ("$zero", "$0"):
                # e.g. divu $zero, $v1, $a2
                return [line]

            move_from = "mfhi" if op == "remu" else "mflo"
            if self.expand_div:
                res.extend(
                    [
                        "# EXPAND_DIVU START",
                        ".set\tnoat",
                        f"divu\t$zero,{r_source},{r_operand}",
                        f"bnez\t{r_operand},.L_NOT_DIV_BY_ZERO_{self.line_index}",
                        "nop",
                        "break\t0x7",
                        f".L_NOT_DIV_BY_ZERO_{self.line_index}:",
                        f"{move_from}\t{r_dest}",
                        ".set\tat",
                        "# EXPAND_DIVU END",
                    ]
                )
            else:
                res.extend(
                    [
                        "# EXPAND_ZERO_DIVU START",
                        f"divu\t$zero,{r_source},{r_operand}",
                        f"{move_from}\t{r_dest}",
                        "# EXPAND_ZERO_DIVU END",
                    ]
                )

            extra_nops = self._handle_mflo_mfhi(r_source=r_dest)
            if len(extra_nops) > 0:
                res += extra_nops
            else:
                next_instruction = self.get_next_instruction(
                    skip=0, ignore_set=True, ignore_label=True
                )
                extra_nops = self._handle_nop_before_next_instruction(
                    next_instruction, r_dest
                )
                res.extend(extra_nops)

        elif op == "sltu":
            r_dest, r_source, r_operand = rest[0].split(",")
            if re.match(r"^-?\d+$", r_operand) or re.match(
                r"^-?0x[A-Fa-f0-9]+$", r_operand
            ):
                value = int(r_operand)
                if self.sltu_at and value < 0:
                    res.append(f"li\t$at,{r_operand}")
                    res.append(f"{op}\t{r_dest},{r_source},$at")
                else:
                    # TODO: do we want to expand sltu into sltiu?
                    res.append(line)
            else:
                res.append(line)

        else:
            res.append(line)

        return res
