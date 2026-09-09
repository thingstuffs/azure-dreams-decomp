#!/usr/bin/env python3
"""Post-process gcc -S output: put each function (delimited by `.ent NAME`) into
its own `.text.NAME` section. gcc 2.7.2 emits all top-level asm() (our INCLUDE_ASM
blocks) before any C function, which would clump decompiled functions at the end of
the object. Sectioning every function lets the linker sort them back into address
order via SORT_BY_NAME(.text.func_*). Reads stdin, writes stdout.

Semantic renaming (config/names.tsv): a decompiled function may be given a readable
C symbol (e.g. initMonsterFromStats) while its machine code must still land at the
original address. The linker orders code purely by SORTING section names, and only
sections literally named `.text.func_<addr>` participate (see tools/configure.py's
SORT_BY_NAME(.text.func_*) glob). So for a renamed function this script:
  1. emits the section as `.text.func_<addr>` (NOT `.text.<readable>`) so it keeps
     its address slot in the sort, and
  2. appends a `func_<addr> = <readable>` symbol alias so any still-in-asm (or not
     yet renamed C) caller that `jal`s the old `func_<addr>` symbol still resolves.
Both are byte-neutral: section names and the symbol table are stripped by objcopy,
so the final binary is unaffected. When names.tsv is absent or a function is not
listed, behaviour is byte-identical to the original per-`.ent` sectioning."""
import sys, re, os

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
NAMES_TSV = os.path.join(ROOT, "config", "names.tsv")

# new_name -> original section base (func_<addr>). Only renamed funcs appear here;
# everything else falls through to the unchanged `.text.<name>` default.
_rename = {}
if os.path.exists(NAMES_TSV):
    with open(NAMES_TSV) as fh:
        for raw in fh:
            raw = raw.split("#", 1)[0].rstrip("\n")
            if not raw.strip():
                continue
            cols = raw.split("\t")
            if len(cols) < 3:
                continue
            old, new = cols[1].strip(), cols[2].strip()
            if old and new and new != old:
                _rename[new] = old

# Names are a C-level alias layer.  The assembly is spelled back to the original func_<addr>
# symbols before anything else sees it - the definition, every call, every address reference -
# so the assembler front end's name-keyed tables (config/noreturn_syms*, sibcall_syms*), the
# linker scripts, the per-row scorer and the SLUS link all work on exactly the pre-rename
# symbols and the bytes cannot move.  String data (.ascii/.asciz) is left alone.
_lines = sys.stdin.readlines()
if _rename:
    _text = "".join(_lines)
    _present = [n for n in _rename if n in _text]
    if _present:
        _pat = re.compile(r"\b(" + "|".join(re.escape(n) for n in sorted(_present, key=len, reverse=True)) + r")\b")
        _lines = [l if re.match(r"\s*\.(ascii|asciz|string)\b", l) else _pat.sub(lambda m: _rename[m.group(1)], l) for l in _lines]

aliases = []  # (original func_<addr>, readable) to emit at EOF
cur_section = None  # func_<addr> section name while between .ent and .end
for line in _lines:
    m = re.match(r'\s*\.ent\s+(\S+)', line)
    if m:
        name = m.group(1)
        section = _rename.get(name, name)
        cur_section = section
        sys.stdout.write(f'\t.section .text.{section},"ax",@progbits\n')
        if section != name:
            aliases.append((section, name))
        sys.stdout.write(line)
        continue
    # A function may switch to .rdata/.rodata mid-body for a compiler-generated
    # switch jump table (or a constant pool) and resume its code with a bare
    # `.text`. That returns the assembler to the generic .text section, but the
    # function's label lives in `.text.<func>` (renamed above), so the
    # `.size <func>, .-<func>` that MIPS gas synthesizes at `.end` subtracts two
    # symbols in different sections and errors with "does not evaluate to a
    # constant". Redirect the resume back into the function's own section: the
    # code stays contiguous, the jump table stays in .rodata, and .size becomes a
    # within-section (constant) difference. This only fires between .ent and .end
    # (cur_section set), so the leading `.text` directives gcc emits before each
    # function and any code that already assembles clean (no in-body split ->
    # this branch never runs) are byte-for-byte untouched.
    if cur_section is not None and re.match(r'\s*\.text\s*$', line):
        sys.stdout.write(f'\t.section .text.{cur_section},"ax",@progbits\n')
        continue
    if re.match(r'\s*\.end\b', line):
        cur_section = None
    sys.stdout.write(line)

# Keep the original func_<addr> symbol resolvable for un-renamed callers (asm or C).
for original, readable in aliases:
    sys.stdout.write(f'\t.globl {original}\n\t.set {original}, {readable}\n')
