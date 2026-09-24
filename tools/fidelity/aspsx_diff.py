#!/usr/bin/env python3
"""Genuine-ASPSX differential over the tree (toolchain fidelity plan, STEP 1; measurement only).

For every row: the row's CURRENT source (src/), compiled by its registered recipe (cell + flags), is
assembled twice from ONE gcc -S stream:

  maspsx leg   exactly the project pipeline (slus: tools/verify.compile_slus = gcc -> ccproc -> maspsx
               --aspsx-version=2.79 --dont-force-G0 -G8 <row_asflags> -> GNU as; overlays: the per-row
               scorer's own match.build_text inside build_ovl/, with the overlay evidence env, the
               row's as-flags dial and the rowbase link base), re-run through
               tools/fidelity/maspsx_trace.py so the maspsx post-passes that FIRED are named;
  genuine leg  the same gcc -S stream maspsx reads, assembled by the genuine SN ASPSX.EXE
               2.56 / 2.67 / 2.77 / 2.79 / 2.81 / 2.86 under wibo (`-q`, CRLF, `.include`/`#APP`/
               `.size`/`.type` stripped, ccproc's `.section .text.NAME` back to `.text`, every
               `.set NAME, X` / `NAME = VALUE` equate dropped so the symbol stays external as in
               the original TU), with `-0` (unchecked div) and without, and `-G0` when the row's
               cc1 runs at -G0.

Comparison (the word comparator, `compare_units`): both objects are normalised per FUNCTION into
tokens (instruction word with its relocation field masked, canonical relocation), where a canonical
relocation is (type, target, addend) with every TU-local target rewritten to a function-relative
or symbol-relative location (tools/fidelity/objread.py decodes the LNK expressions). Two functions
whose token streams are equal link to the same bytes. Every landed row's maspsx object is
retail-exact (the gate), so "genuine ASPSX == maspsx" is "genuine ASPSX reproduces retail" for it;
slus rows are ALSO resolved against the retail SLUS directly (build_slus/build/slus_006.14.elf
symbol addresses + baserom), which is what the d92c control needs.

Attribution (non-exact versions): the maspsx leg is re-run with each fired post-pass disabled, all
fired passes disabled, `.extern` sizes withheld (genuine ASPSX's small-extern model, decision 3),
each row as-flag dropped, and maspsx configured as the genuine version; a variant that makes
maspsx == genuine names the maspsx behaviour that made the difference.

Journal: work/fidelity/aspsx_diff.jsonl, one record per row, keyed by a hash of the row's text,
recipe and every tool input (tool_fingerprint); a row whose key is unchanged is never recomputed.

    python3 tools/fidelity/aspsx_diff.py [--workers 12] [--only ID,ID|@file] [--container slus] [--limit N]
    python3 tools/fidelity/aspsx_diff.py --one slus/w_8003D92C [--cfile X.c] [--cfg "2.7.2-cdk"] [--asflags ""]
    python3 tools/fidelity/aspsx_diff.py --controls        # the validation controls (exit 1 on a failure)
"""
from __future__ import annotations

import argparse
import difflib
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(HERE))
from objread import read_elf, read_lnk  # noqa: E402

BROOT = ROOT / "build_ovl"
JOURNAL = ROOT / "work/fidelity/aspsx_diff.jsonl"
TMP = ROOT / "work/fidelity/tmp/rows"            # per-row scratch, removed when a run ends
# genuine PsyQ toolchain (ASPSX.EXE per version + wibo): a local, git-ignored link toolchain/genuine -> the sibling
# decomp repo's toolchain/ directory (override with GENUINE_TOOLCHAIN)
GENUINE = Path(os.environ.get("GENUINE_TOOLCHAIN", str(ROOT / "toolchain/genuine")))
WIBO = GENUINE / "bin/wibo"
VERSIONS = ["2.56", "2.67", "2.77", "2.79", "2.81", "2.86"]
ASPSX = {"2.56": "psyq4.0", "2.67": "psyq4.1", "2.77": "psyq4.3", "2.79": "psyq4.4", "2.81": "psyq4.5", "2.86": "psyq4.6"}
NICE = ["nice", "-n10", "ionice", "-c2", "-n7"]
VENV_PY = ROOT / ".venv/bin/python"
TRACE = HERE / "maspsx_trace.py"
SLUS_ELF = ROOT / "build_slus/build/slus_006.14.elf"
SLUS_BIN = ROOT / "baserom/slus_006.14"
TOOL_VERSION = "1"
# maspsx behaviour thresholds (tools/maspsx/maspsx.py config_for_aspsx_version): the distinct configs
MASPSX_VCONF = {"2.67": "2.67", "2.77": "2.77", "2.79": "2.79", "2.81": "2.79", "2.86": "2.79"}


def _sha(b: bytes) -> str:
    return hashlib.sha256(b).hexdigest()


# ------------------------------------------------------------------------------------ fingerprint
def tool_fingerprint() -> str:
    """Everything outside a row's own text + recipe that can change a record."""
    h = hashlib.sha256(TOOL_VERSION.encode())
    files = [HERE / "aspsx_diff.py", HERE / "objread.py", HERE / "maspsx_trace.py",
             ROOT / "tools/maspsx/maspsx.py", ROOT / "tools/maspsx/maspsx/__init__.py",
             ROOT / "tools/verify.py", ROOT / "tools/build/ccproc.py", ROOT / "config/names.tsv",
             ROOT / "tools/slus_module_context.py", ROOT / "tools/build/slus_modules.py",
             HERE / "slus_iso.py", ROOT / "tools/build/slus_partitions.py",
             ROOT / "tools/row_db.py", ROOT / "tools/build/mk_slus_root.sh",
             ROOT / "tools/slus_module_evidence.py", HERE / "certify_slus_module.py", HERE / "prove_slus_ownership.py",
             ROOT / "tools/build/configure.py", ROOT / "config/slus_modules.json",
             BROOT / "tools/match.py", BROOT / "work/g3/overlay_func_compare.py",
             BROOT / "tools/overlay_as_flags.py", BROOT / "tools/overlay_evidence.py",
             BROOT / "tools/rowbase.py", BROOT / "config/names.tsv", SLUS_ELF, ROOT / "ledger/cache/slus_obj.json"]
    files += sorted((ROOT / "config").glob("noreturn_syms*.txt")) + sorted((ROOT / "config").glob("sibcall_syms*.txt"))
    files += sorted((ROOT / "config/overlays").glob("*.as_flags.jsonl"))
    files += [GENUINE / "psyq" / ASPSX[v] / "ASPSX.EXE" for v in VERSIONS]
    for f in files:
        h.update(str(f).encode())
        h.update(_sha(f.read_bytes()).encode() if f.exists() else b"-")
    for inc in (ROOT / "include", ROOT / "raw/include"):
        for p in sorted(inc.rglob("*")):
            if p.is_file():
                st = p.stat(); h.update(f"{p}:{st.st_size}:{st.st_mtime_ns}".encode())
    return h.hexdigest()[:20]


def row_key(row, text: str, fp: str, cfg: str, asflags: str) -> str:
    from slus_module_context import fingerprint
    return _sha(json.dumps([row["id"], _sha(text.encode()), cfg, asflags, fp, fingerprint(row)]).encode())[:24]


# ------------------------------------------------------------------------------- normalisation
FIELD = {"26": 0x03FFFFFF, "HI16": 0xFFFF, "LO16": 0xFFFF, "GPREL16": 0xFFFF, "32": 0xFFFFFFFF}


def _is_text(sec):
    return bool(sec) and (sec == ".text" or sec.startswith(".text."))


def _canon_sec(sec):
    return ".rodata" if sec in (".rdata", ".rodata") else sec


def functions(obj, ref=None):
    """{name: (section, start, end)} for the functions an object defines.

    ELF carries sizes. LNK has only symbol offsets, so a function ends at the next symbol - except
    at a symbol the maspsx object (`ref`) shows NESTED inside another function (a composite row's
    `func_X_body` entry inside `func_X`), which is not a boundary."""
    out = {}
    if obj.fmt == "elf":
        for nm, (sec, off, kind, size) in obj.symbols.items():
            if kind == "func" and _is_text(sec):
                out[nm] = (sec, off, off + (size or 0))
        return out
    nested = set()
    if ref is not None:
        rf = ref.funcs
        for n, (sec, s, e) in rf.items():
            if any(m != n and ms == sec and s0 <= s and e <= e0 and (s0, e0) != (s, e)
                   for m, (ms, s0, e0) in rf.items()):
                nested.add(n)
    by_sec = {}
    for nm, (sec, off, kind, _) in obj.symbols.items():
        if _is_text(sec) and not nm.startswith("$") and not nm.startswith(".") and nm not in nested:
            by_sec.setdefault(sec, []).append((off, nm))
    for sec, lst in by_sec.items():
        lst.sort()
        end_sec = len(obj.sections.get(sec, b""))
        for i, (off, nm) in enumerate(lst):
            nxt = next((o for o, _ in lst[i + 1:] if o > off), end_sec)
            out[nm] = (sec, off, nxt)
    for nm, (sec, s, e) in obj.func_extents.items():       # FUNCTION/FUNCTION_END records win
        if e is not None and nm in out:
            out[nm] = (sec, s, e)
    return out


class View:
    """An object normalised for comparison: per-function token lists."""

    def __init__(self, obj, ref=None, alias=None):
        self.obj = obj
        self.alias = alias or {}
        self.composite = set()     # overlay row symbols scored with the composite extent rule
        self.follow = {}           # row symbol -> functions that follow it inside the row's retail extent
        self.funcs = functions(obj, ref)
        # absolute equates (ELF SHN_ABS), ours and the reference object's: a relocation against one
        # is a constant the linker writes
        self.absmap = {n: v[1] for o in ([ref.obj] if ref is not None else []) + [obj]
                       for n, v in o.symbols.items() if v[2] == "abs"}
        self.text_index = {}
        for nm, (sec, s, e) in self.funcs.items():
            self.text_index.setdefault(sec, []).append((s, e, nm))
        for v in self.text_index.values():
            v.sort()
        self.data_index = {}
        for nm, (sec, off, kind, _) in obj.symbols.items():
            if sec and not _is_text(sec) and not nm.startswith("$") and nm not in ("gcc2_compiled.", "__gnu_compiled_c"):
                self.data_index.setdefault(_canon_sec(sec), []).append((off, nm))
        for v in self.data_index.values():
            v.sort()
        self._index_relocs()

    def _index_relocs(self):
        self.rel = {}
        for sec, off, rtype, target, addend in self.obj.relocs:
            self.rel[(sec, off)] = (rtype, self.canon(target, addend))

    def add_unit(self, name, ref=None):
        """Make `name` a comparison unit when the extent rules did not: a data-shaped row symbol
        (a bank label in a text section) or, in an LNK object, a label ASPSX kept no symbol for (placed
        where the maspsx object has it). The unit runs to the next boundary symbol or section end."""
        if name in self.funcs:
            return
        s = self.obj.symbols.get(name)
        if s and _is_text(s[0]):
            sec, start = s[0], s[1]
        elif ref is not None and name in ref.funcs and ref.funcs[name][0] in self.obj.sections:
            sec, start = ref.funcs[name][0], ref.funcs[name][1]
        else:
            return
        nested = set()
        if ref is not None and name in ref.funcs:
            _, rs, re_ = ref.funcs[name]
            nested = {n for n, (ss, a, b) in ref.funcs.items() if n != name and rs <= a and b <= re_}
        ends = [st for st, e, n in self.text_index.get(sec, []) if st > start and n not in nested]
        ends += [v[1] for n, v in self.obj.symbols.items() if v[0] == sec and v[1] > start and n not in nested
                 and not n.startswith("$")]
        end = min(ends) if ends else len(self.obj.sections.get(sec, b""))
        self.funcs[name] = (sec, start, end)
        self.text_index.setdefault(sec, []).append((start, end, name))
        self.text_index[sec].sort()
        self._index_relocs()                   # targets inside the new unit are function-relative now

    def loc(self, sec, off):
        if _is_text(sec):
            for s, e, nm in self.text_index.get(sec, []):
                if s <= off < e or (off == e and s == e):
                    return ("fn", nm, off - s)
            return ("text", None, off)
        cs = _canon_sec(sec)
        if cs not in (".bss", ".sbss"):
            # initialised data and tables: the section offset (both assemblers lay these out in source
            # order; a data label is a local symbol in one object and absent from the other)
            return ("sec", cs, off)
        # .bss/.sbss: maspsx materialises a .comm/.lcomm as a labelled `.space`, ASPSX keeps a common -
        # the covering symbol is the only shared name
        best = None
        for o, nm in self.data_index.get(cs, []):
            if o <= off:
                best = (o, nm)
            else:
                break
        if best:
            m = NAME_ADDR.match(best[1])
            if m:                              # same rule as an external: the name is the address
                return ("addr", None, (int(m.group(1), 16) + off - best[0]) & 0xFFFFFFFF)
            return ("sym", best[1], off - best[0])
        return ("sec", cs, off)

    def canon(self, target, addend):
        kind, name = target
        if kind == "sym":
            name = self.alias.get(name, name)
        if kind == "sym" and name in self.absmap:
            return ("abs", None, (self.absmap[name] + addend) & 0xFFFFFFFF)
        if kind == "sym":
            s = self.obj.symbols.get(name)
            if s and s[0] is not None:
                return self.loc(s[0], (s[1] + addend) & 0xFFFFFFFF)
            m = NAME_ADDR.match(name)
            if m:
                # an external whose name IS its address (D_/func_XXXXXXXX; the link scripts define it
                # there): `D_80288EE0+376` and `D_80289058` are one location
                return ("addr", None, (int(m.group(1), 16) + addend) & 0xFFFFFFFF)
            return ("sym", name, addend)
        if kind == "sec":
            return self.loc(name, addend)
        return (kind, name, addend)

    def tokens(self, fname):
        out = self._unit_tokens(fname)
        for g in self.follow.get(fname, []):
            if g in self.funcs:
                out = out + self._unit_tokens(g)
        return out

    def _unit_tokens(self, fname):
        """The function's words as tokens.  A COMPOSITE row (a pinned `.text.<name>` section - a
        pointer bank - ahead of a body in `.text`) is the prefix section followed by the body: the
        order the gate's link script gives `*(.text.*) *(.text)` and the extent the scorer slices."""
        sec, s, e = self.funcs[fname]
        out = []
        pre = ".text." + fname
        if sec == ".text" and self.obj.sections.get(pre):
            out = self._tokens(pre, 0, len(self.obj.sections[pre]))
        if fname in self.composite and sec == pre and s == 0 and self.obj.sections.get(".text"):
            # the row symbol opens its own pinned section and the body follows in .text
            # (ELF: up to the last function in .text - GNU as pads the section, the link does not)
            tend = max((e for (sc, _, e) in self.funcs.values() if sc == ".text"), default=len(self.obj.sections[".text"]))
            return self._tokens(sec, 0, len(self.obj.sections[sec])) + self._tokens(".text", 0, tend)
        return out + self._tokens(sec, s, e)

    def unit_layout(self, fname):
        """{function: byte offset from the start of `fname`'s unit} for every function the unit holds
        (used to resolve jumps between the pieces of a composite/bank unit against retail)."""
        sec, s, e = self.funcs[fname]
        pre = ".text." + fname
        lay = {}
        if fname in self.composite and sec == pre and s == 0 and self.obj.sections.get(".text"):
            lay[fname] = 0
            for n, (sc, st, _) in self.funcs.items():
                if sc == ".text":
                    lay.setdefault(n, len(self.obj.sections[sec]) + st)
            pos = None
        else:
            lay[fname] = len(self.obj.sections.get(pre, b"")) if sec == ".text" else 0
        pos = len(self._unit_tokens(fname)) * 4
        for g in self.follow.get(fname, []):
            if g in self.funcs:
                lay[g] = pos; pos += len(self._unit_tokens(g)) * 4
        return lay

    def gp_extern_names(self, scope):
        """Names this object addresses $gp-relative inside `scope` without defining them."""
        spans = [self.funcs[f] for f in scope if f in self.funcs]
        out = set()
        for sec, off, rtype, target, _ in self.obj.relocs:
            if rtype == "GPREL16" and target[0] == "sym" and target[1] not in self.obj.symbols and \
                    any(sec == s and a <= off < b for s, a, b in spans):
                out.add(target[1])
        return sorted(out)

    def prefix_bytes(self, fname):
        sec = self.funcs[fname][0]
        pre = ".text." + fname
        return len(self.obj.sections.get(pre, b"")) if sec == ".text" else 0

    def _tokens(self, sec, s, e):
        body = self.obj.sections.get(sec, b"")
        out = []
        for off in range(s, min(e, len(body)) - 3, 4):
            w = struct.unpack_from("<I", body, off)[0]
            r = self.rel.get((sec, off))
            if r and r[1][0] == "abs" and r[0] in ("HI16", "LO16", "26", "32"):
                # a constant-only LNK patch (`la $3,0x8008B2F0`, an .equ'd address): the linker writes
                # the constant, GNU as already did - compare the word it becomes
                v = r[1][2] & 0xFFFFFFFF
                fv = {"HI16": ((v + 0x8000) >> 16) & 0xFFFF, "LO16": v & 0xFFFF,
                      "26": (v >> 2) & 0x03FFFFFF, "32": v}[r[0]]
                out.append(((w & ~FIELD[r[0]] & 0xFFFFFFFF) | fv, None, None))
                continue
            if r:
                rtype, key = r
                w &= ~FIELD.get(rtype, 0) & 0xFFFFFFFF
                if rtype in ("LO16", "GPREL16") and isinstance(key[2], int):
                    key = (key[0], key[1], key[2] & 0xFFFF)
                out.append((w, rtype, key))
            else:
                out.append((w, None, None))
        return out


def _is_jump(w):
    op = w >> 26
    return op in (1, 2, 3, 4, 5, 6, 7, 20, 21, 22, 23) or (op == 0 and (w & 0x3F) in (8, 9))


def unfill(tokens):
    """Delay-slot normal form, for CLASSIFICATION only: every `jump; X` with X a real instruction is
    written `X; jump; nop`.  Two streams equal in this form differ only in which instruction sits
    in a delay slot (fill vs un-fill)."""
    out, i = [], 0
    while i < len(tokens):
        t = tokens[i]
        if _is_jump(t[0]) and i + 1 < len(tokens) and tokens[i + 1][0] != 0:
            out += [tokens[i + 1], t, (0, None, None)]; i += 2
        else:
            out.append(t); i += 1
    return out


def compare_units(ma, ge, scope=None):
    """Compare two Views function by function (the word comparator).

    Returns {"diff": differing words (aligned: max(len) of every non-equal opcode), "exact": bool,
    "len_m": words, "len_g": words, "missing": [functions absent from the genuine object],
    "regions": [(func, op, m_tokens, g_tokens)] (first few, for classification)}."""
    scope = scope or sorted(ma.funcs)
    diff = 0; lm = lg = 0; missing = []; regions = []; delay_only = []
    for f in scope:
        a = ma.tokens(f)
        lm += len(a)
        if f not in ge.funcs:
            missing.append(f); diff += len(a); continue
        b = ge.tokens(f)
        lg += len(b)
        if a == b:
            continue
        if unfill(a) == unfill(b):
            delay_only.append(f)
        sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
        for op, a1, a2, b1, b2 in sm.get_opcodes():
            if op == "equal":
                continue
            diff += max(a2 - a1, b2 - b1)
            regions.append((f, op, a[a1:a2], b[b1:b2], a1))
    return {"diff": diff, "exact": diff == 0 and lm == lg and not missing, "len_m": lm, "len_g": lg,
            "missing": missing, "regions": regions, "delay_only": delay_only}


def _op(w):
    return w >> 26


def classify(regions, ma=None, delay_only=()):
    """Name the shape of each differing region (maspsx side a, genuine side b)."""
    cls = {}
    def add(k):
        cls[k] = cls.get(k, 0) + 1
    for f, op, a, b, _ in regions:
        if f in delay_only:
            add("delay-slot"); continue
        ident = lambda k: (k[0], k[1], k[2] & 0xFFFF if isinstance(k[2], int) else k[2])   # noqa: E731
        ra = {ident(t[2]) for t in a if t[1] == "GPREL16" and t[2]}
        rb = {ident(t[2]) for t in b if t[1] in ("HI16", "LO16") and t[2]}
        gb = {ident(t[2]) for t in b if t[1] == "GPREL16" and t[2]}
        ga = {ident(t[2]) for t in a if t[1] in ("HI16", "LO16") and t[2]}
        if ra & rb:
            ext = any(k[0] == "addr" or (k[0] == "sym" and ma is not None and k[1] not in ma.obj.symbols) for k in ra & rb)
            add("gp-extern" if ext else "gp-local"); continue
        if gb & ga:
            add("gp-genuine-only"); continue
        words_a = [t[0] for t in a]; words_b = [t[0] for t in b]
        brk = lambda ws: any((w & 0xFC00003F) in (0x0000000D, 0x00000034) for w in ws)   # break / teq
        if brk(words_b) != brk(words_a):
            add("div-check"); continue
        if len(a) == len(b) and all(x[1:] == y[1:] and {_op(x[0]), _op(y[0])} == {2, 3} for x, y in zip(a, b) if x != y):
            add("jal-j"); continue
        if (not a and all(t[0] == 0 for t in b)) or (not b and all(t[0] == 0 for t in a)):
            add("nop"); continue
        if len(a) == len(b) and sorted(a, key=repr) == sorted(b, key=repr):
            add("reorder"); continue
        if len(a) == len(b) and all(x[0] == y[0] for x, y in zip(a, b)):
            add("reloc"); continue
        if len(a) == len(b) and all(_op(x[0]) == 0 and _op(y[0]) == 0 for x, y in zip(a, b)):
            add("rtype"); continue
        if sorted((t for t in a if t[0]), key=repr) == sorted((t for t in b if t[0]), key=repr):
            add("nop-placement"); continue
        add("other")
    return cls


# ---------------------------------------------------------------------------- retail resolution
_SLUS = None


def slus_image():
    """(symbol address map, _gp, retail bytes, load address) of the linked, SHA-gated SLUS."""
    global _SLUS
    if _SLUS is None:
        e = read_elf(SLUS_ELF.read_bytes())
        addrs = {nm: v[1] for nm, v in e.symbols.items()}
        # absolute / section-less symbols (the undefined_syms scripts) are not in e.symbols
        r = subprocess.run(["mipsel-linux-gnu-nm", str(SLUS_ELF)], capture_output=True, text=True)
        for l in r.stdout.splitlines():
            p = l.split()
            if len(p) == 3:
                addrs.setdefault(p[2], int(p[0], 16))
        p = ROOT / "config/names.tsv"                                   # readable alias -> func_<addr>
        if p.exists():
            for raw in p.read_text(errors="replace").splitlines():
                cols = raw.split("#", 1)[0].rstrip("\n").split("\t")
                if len(cols) >= 3 and cols[1].strip() and cols[2].strip() and cols[2].strip() not in addrs:
                    m = NAME_ADDR.match(cols[1].strip())
                    if cols[1].strip() in addrs:
                        addrs[cols[2].strip()] = addrs[cols[1].strip()]
                    elif m:
                        addrs[cols[2].strip()] = int(m.group(1), 16)
        data = SLUS_BIN.read_bytes()
        load = struct.unpack_from("<I", data, 0x18)[0]
        _SLUS = (addrs, addrs.get("_gp", 0x80080994), data, load)
    return _SLUS


NAME_ADDR = re.compile(r"^(?:func|D|jtbl|jumptable|w)_([0-9A-Fa-f]{8})$")


def resolve_tokens(view, fname, base, addr_of, gp, slice_base=None, layout=None):
    """Resolve a function's tokens into linked words; (words, masked_indices).  `base` is the
    function symbol's address; `layout` ({function: unit offset}, with `slice_base` the unit's
    address) places the other pieces of a composite/bank unit."""
    out, masked = [], []
    layout = layout or {}
    section_bases = {}
    for symbol, (section, offset, *_rest) in view.obj.symbols.items():
        if section is not None and not _is_text(section):
            linked = addr_of(symbol)
            if linked is not None:
                section_bases.setdefault(_canon_sec(section), set()).add(linked - offset)
    for i, (w, rtype, key) in enumerate(view.tokens(fname)):
        if rtype is None:
            out.append(w); continue
        kind, name, a = key
        val = None
        if kind == "addr":
            val = a
        elif kind == "fn":
            fa = base if name == fname else (slice_base + layout[name] if name in layout and slice_base is not None
                                             else addr_of(name))
            val = None if fa is None else fa + a
        elif kind == "sym":
            sa = addr_of(name)
            val = None if sa is None else sa + a
        elif kind == "sec":
            # Initialized TU-owned data is canonicalized by section offset.
            # Recover its base only from agreeing named symbols in the gated
            # link; absent or conflicting anchors remain explicitly masked.
            bases = section_bases.get(name, set())
            if len(bases) == 1:
                val = next(iter(bases)) + a
        if val is None:
            out.append(w); masked.append(i); continue
        val &= 0xFFFFFFFF
        if rtype == "26":
            w = (w & 0xFC000000) | ((val >> 2) & 0x03FFFFFF)
        elif rtype == "HI16":
            w = (w & 0xFFFF0000) | (((val + 0x8000) >> 16) & 0xFFFF)
        elif rtype == "LO16":
            w = (w & 0xFFFF0000) | (val & 0xFFFF)
        elif rtype == "GPREL16":
            w = (w & 0xFFFF0000) | ((val - gp) & 0xFFFF)
        elif rtype == "32":
            w = val
        out.append(w)
    return out, masked


def retail_compare(view, scope, kind, overlay_ctx=None):
    """Resolve `scope` functions against RETAIL words directly. -> {"diff", "masked", "checked"}."""
    diff = masked = checked = 0
    if kind == "slus":
        addrs, gp, data, load = slus_image()
        def addr_of(n):
            return addrs.get(n)
        for f in scope:
            base = addrs.get(f)
            if base is None or f not in view.funcs:
                continue
            words, mk = resolve_tokens(view, f, base, addr_of, gp)
            off = base - load + 0x800
            ret = [struct.unpack_from("<I", data, off + 4 * i)[0] for i in range(len(words))]
            d = sum(1 for i, (x, y) in enumerate(zip(words, ret)) if x != y and i not in mk)
            diff += d; masked += len(mk); checked += 1
        return {"diff": diff, "masked": masked, "checked": checked}
    # overlays: name-encoded addresses and the row's link base
    tgt, base, fname, gp = overlay_ctx["retail"], overlay_ctx["link_vram"], overlay_ctx["symbol"], overlay_ctx["gp"]
    def addr_of(n):
        m = NAME_ADDR.match(n or "")
        return int(m.group(1), 16) if m else None
    if fname not in view.funcs:
        return {"diff": None, "masked": 0, "checked": 0}
    # the slice starts at the link base; a composite row's body symbol sits after its prefix bank
    lay = view.unit_layout(fname)
    words, mk = resolve_tokens(view, fname, base + lay.get(fname, 0), addr_of, gp, slice_base=base, layout=lay)
    ret = [struct.unpack_from("<I", tgt, 4 * i)[0] for i in range(len(tgt) // 4)]
    n = max(len(words), len(ret))
    d = sum(1 for i in range(n) if i not in mk and (words[i] if i < len(words) else None) != (ret[i] if i < len(ret) else None))
    return {"diff": d, "masked": len(mk), "checked": 1, "len": len(words), "retail_len": len(ret)}


# ------------------------------------------------------------------------------------ pipelines
def _clean_env():
    env = dict(os.environ)
    for k in list(env):
        if k in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION") or k.startswith("MASPSX_LEAD"):
            env.pop(k)
    return env


def run_maspsx(s_text, as_args, out_o, env, disable=(), strip_externs=False, trace=None):
    cmd = NICE + [str(VENV_PY), str(TRACE)]
    if trace:
        cmd += ["--trace", str(trace)]
    if disable:
        cmd += ["--disable", ",".join(disable)]
    if strip_externs:
        cmd += ["--strip-externs"]
    cmd += ["--"] + as_args + ["--run-assembler", "--gnu-as-path=mipsel-linux-gnu-as", "-o", str(out_o)]
    if Path(out_o).exists():
        Path(out_o).unlink()
    r = subprocess.run(cmd, input=s_text, capture_output=True, text=True, env=env, cwd=str(ROOT))
    if r.returncode != 0 or not Path(out_o).exists():
        return None, (r.stderr or r.stdout)[-300:]
    return Path(out_o).read_bytes(), None


SETABS = re.compile(r"^\s*(\.set\s+[A-Za-z_.$][\w.$]*\s*,|\.size\b|\.type\b)")
SETNUM = re.compile(r"^\s*(?:\.set\s+([A-Za-z_.$][\w.$]*)\s*,|([A-Za-z_.$][\w.$]*)\s*=)\s*(-?(?:0x[0-9A-Fa-f]+|\d+))\s*$")
SETALIAS = re.compile(r"^\s*\.set\s+([A-Za-z_.$][\w.$]*)\s*,\s*([A-Za-z_.$][\w.$]*)\s*$")


def aliases(s_text):
    """`.set A, B` symbol aliases in the gcc -S (e.g. a noreturn census twin `func_X_returning`):
    GNU as resolves them, ASPSX never sees them (the line is dropped) - the comparator maps A -> B."""
    return {m.group(1): m.group(2) for m in map(SETALIAS.match, s_text.splitlines()) if m}


def aspsx_input(s_text, equ=False):
    """The genuine leg's input: the gcc -S the pipeline assembles, with GAS-only lines dropped.

    A C-side numeric address equate (`.set D_X, 0x8008...` / `D_X = 0x...`) has two faithful readings
    and they assemble differently: as an EXTERNAL symbol (dropped here; the linker writes it) ASPSX
    expands `lw $2,D_X($3)` as `lui $at / addu $at,$at,$3`, and `la $3,D_X` as `lui/addiu` even when
    the low half is 0; as an absolute CONSTANT (`equ=True`: respelled `.equ`, ASPSX's syntax) it
    swaps the `addu` operands and drops a zero `addiu`, like GNU as. Retail has rows of both kinds
    (an original extern vs an original integer constant), so both are run."""
    kept = []
    for l in s_text.splitlines():
        m = SETNUM.match(l)
        if m:
            if equ:
                kept.append(f"\t.equ\t{m.group(1) or m.group(2)},{m.group(3)}")
            continue
        if ".include" in l or l.strip() in ("#APP", "#NO_APP") or SETABS.match(l):
            continue
        if re.match(r"^\s*\.set\s+no?bopt\s*$", l):  # GAS branch-optimisation switch (-mmips-as cells); ASPSX has none
            continue
        kept.append(l)
    return ("\r\n".join(kept) + "\r\n").encode()


def run_aspsx(src_bytes, ver, flags, td):
    # a SHORT directory directly under the scratch root: ASPSX cannot open an input whose DOS path
    # (wibo's Z:\...) is longer than ~100 characters ("Could not open file")
    d = Path(tempfile.mkdtemp(prefix="a", dir=TMP))
    try:
        (d / "IN.S").write_bytes(src_bytes)
        env = dict(os.environ, TMPDIR=str(d), TMP=str(d), TEMP=str(d))
        r = subprocess.run(NICE + [str(WIBO), str(GENUINE / "psyq" / ASPSX[ver] / "ASPSX.EXE"), *flags,
                                   "-o", "OUT.OBJ", "IN.S"], cwd=str(d), env=env, capture_output=True, timeout=120)
        obj = d / "OUT.OBJ"
        if not obj.exists():
            out = (r.stdout + r.stderr).decode(errors="replace")
            lines = [l.strip() for l in out.splitlines() if l.strip() and "Copyright" not in l and "version" not in l]
            errs = [l for l in lines if "rror" in l]
            msg = "; ".join((errs or lines)[:3])
            msg = re.sub(r"[A-Z]:\\\S*?IN\.S", "IN.S", msg, flags=re.I)        # wibo's Z:\...\IN.S path prefix
            return None, msg[:240] or "no object"
        return obj.read_bytes(), None
    finally:
        shutil.rmtree(d, ignore_errors=True)


def prepare_slus(row, cfile, cfg, asflags, td):
    import verify
    from common import parse_cfg
    cell, flags = parse_cfg(cfg)
    r = dict(row, cell=cell, flags=" ".join(flags), row_asflags=asflags)
    # src/ texts compile against include/ (tools/reverify.py and promote.py pass include_root=INCLUDE)
    obj, err = verify.compile_slus(r, cfile, td, include_root=ROOT / "include")
    if obj is None:
        return None, err
    s_raw = (Path(td) / "a.s").read_text(errors="replace")
    m_in = (Path(td) / "a.proc.s").read_text()
    try:
        g_src = verify.postprocess_slus(s_raw, names_only=True)
    except ValueError as exc:
        return None, str(exc)
    as_args = ["--aspsx-version=2.79", "--dont-force-G0", f"-I{ROOT / 'raw'}", f"-I{ROOT / 'include'}",
               "-EL", "-march=r3000", "-G8"] + asflags.split()
    # maspsx_exact exactly as verify_slus decides it (pinned TU object; name-masked text fallback)
    ref = (verify.read_baseline_slus() or {}).get(row["id"])
    h = _sha(obj.read_bytes())
    proof = None
    if ref and h == ref["obj_sha"]:
        exact, proof = True, "pinned-object"
    else:
        dis = ROOT / "ledger/cache/slus_dis" / (row["id"].split("/")[1] + ".txt")
        exact = False
        if dis.exists():
            got = verify.disasm(obj); tgt = dis.read_text().splitlines()
            mask = lambda ls: [re.sub(r"(R_MIPS_\w+)\s+\S+", r"\1 <>", re.sub(r"<[^>]*>", "<>", re.sub(r"^\s*[0-9a-f]+:\s*", "", l))) for l in ls]
            if len(got) == len(tgt) and mask(got) == mask(tgt):
                exact, proof = True, "text-identical"
    from slus_module_context import membership
    module = membership(row)
    if module:
        gate = verify.verify_slus_module(r, cfile)
        exact, proof = bool(gate.get("exact")), gate.get("proof")
        if not exact:
            return None, "module full-image gate: " + str(gate)
    # Both legs use production's canonical names. Genuine ASPSX reads the same
    # compiler stream without the GAS-only function-section directives.
    return {"kind": "slus", "m_in": m_in, "g_src": g_src, "as_args": as_args, "env": _clean_env(),
            "pipeline_obj": obj.read_bytes(), "maspsx_exact": exact, "proof": proof, "cell": cell, "flags": flags}, None


_OFC = None


def _ofc():
    global _OFC
    if _OFC is None:
        import importlib.util
        sys.path.insert(0, str(BROOT / "tools"))
        spec = importlib.util.spec_from_file_location("ofc_fidelity", BROOT / "work/g3/overlay_func_compare.py")
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        ev_spec = importlib.util.spec_from_file_location("overlay_evidence_fid", BROOT / "tools/overlay_evidence.py")
        ev = importlib.util.module_from_spec(ev_spec)
        ev_spec.loader.exec_module(ev)
        _OFC = (mod, ev)
    return _OFC


def prepare_overlay(row, cfile, cfg, asflags_override, td):
    """The per-row scorer's pipeline (overlay_func_compare.main --summary-json), step by step, so the
    maspsx leg sees exactly what the scorer's maspsx saw and the verdict is the scorer's."""
    import verify
    ofc, ev = _ofc()
    M = ofc.M
    cfile = Path(verify.normalise_definition(row, verify.canonical_spelling(cfile)))
    c_text = cfile.read_text(errors="replace")
    overlay, func = row["container"], row["func"]
    for k in ("AZURE_MASPSX", "AZURE_MASPSX_COMPANION"):
        os.environ.pop(k, None)
    scratch = tempfile.mkdtemp(prefix="ev_", dir=td)
    os.environ.update(ev.evidence_env_with_candidate(overlay, c_text, scratch))
    ofc._assert_evidence_not_clobbered(ev, c_text)
    orow = ofc.find_row(func, overlay)
    gcc_ver, gcc_flags = ofc.split_config(cfg)
    import az_target
    cont = BROOT / az_target.CONTAINERS[overlay]
    with open(cont, "rb") as f:
        f.seek(int(orow["foff"])); target = f.read(int(orow["size"]))
    ofc.inject_name_encoded_symbols(cfile, gcc_ver, gcc_flags, func)
    link_vram, rowbase = ofc.rowbase_link_vram(overlay, int(orow["foff"]), int(orow["vram"]))
    target_symbol = func
    if rowbase is not None:
        target_symbol = ofc._ROWBASE.target_symbol(overlay, int(orow["foff"]), func, c_text)
    as_flags = ofc.default_as_flags(func, overlay, target_symbol if target_symbol != func else None) \
        if asflags_override is None else asflags_override
    asm_out = Path(td) / "gcc.latest.s"
    got, err = M.build_text(str(cfile), ofc.compiler_for(gcc_ver), "O2", "2.79", gcc_flags, as_flags, link_vram,
                            target=target_symbol, retail_text=target, asm_output=str(asm_out))
    if not asm_out.exists():
        return None, err or "no assembly"
    exact = got is not None and ofc.linked_words_equal(got, target)
    s = asm_out.read_text(errors="replace")
    as_args = ["--aspsx-version=2.79", "--dont-force-G0", f"-I{BROOT}", f"-I{BROOT / 'include'}",
               "-EL", "-march=r3000", "-G8"] + as_flags.split()
    return {"kind": "overlay", "m_in": s, "g_src": s, "as_args": as_args, "env": dict(os.environ),
            "maspsx_exact": exact, "proof": "scorer-linked" if exact else (err or "scorer: not exact"),
            "linked": got, "retail": target, "link_vram": link_vram, "symbol": target_symbol,
            "gp": M.GP_VALUE, "as_flags": as_flags, "cell": gcc_ver, "flags": gcc_flags.split()}, None


# ------------------------------------------------------------------------------------- one row
def genuine_modes(s_text, flags):
    """[(aspsx flags, equ)]: `-G0` when cc1 ran at -G0 (plus the default -G8 when the TU defines
    small data), `-0` (no div checks) as well as the default when the TU divides, and the numeric
    equates as `.equ` constants as well as externals when the TU has any."""
    has_div = bool(re.search(r"^\s*(div|divu|rem|remu)\s", s_text, re.M))
    g0 = "-G0" in flags
    fl = [["-q"] + (["-G0"] if g0 else [])]
    if has_div:
        fl.append(fl[0] + ["-0"])
    if g0 and re.search(r"^\s*\.(lcomm|comm|sdata|sbss)\b", s_text, re.M):
        fl += [["-q"]] + ([["-q", "-0"]] if has_div else [])
    eq = [False, True] if any(SETNUM.match(l) for l in s_text.splitlines()) else [False]
    return [(f, e) for e in eq for f in fl], has_div


def shape_unit(mv, sym, size):
    """An overlay row's unit in the maspsx (ELF) object is its retail extent (`size` bytes): a bank
    label runs to the next function (not to its .size), and the functions that follow it - later in
    its section, or in the .text.* sections created after it (the link's input order) - belong to the
    unit too (`View.follow`, which the genuine object's View shares)."""
    if sym not in mv.funcs:
        return
    sec0, s0, e0 = mv.funcs[sym]
    nxt = [st for st, e, n in mv.text_index.get(sec0, []) if st > s0]
    if nxt and min(nxt) != e0:
        mv.funcs[sym] = (sec0, s0, min(nxt)); e0 = min(nxt)
        mv.text_index[sec0] = sorted((st, e0 if n == sym else e, n) for st, e, n in mv.text_index[sec0])
        mv._index_relocs()
    have = len(mv.tokens(sym)) * 4
    if have < size:
        secs = [k for k in mv.obj.sections if _is_text(k) and k != ".text"]
        order = [n for st, e, n in sorted(mv.text_index.get(sec0, [])) if st >= e0 and n != sym]
        for k in secs[secs.index(sec0) + 1:] if sec0 in secs else []:
            order += [n for st, e, n in sorted(mv.text_index.get(k, []))]
        fl = []
        for n in order:
            if have >= size:
                break
            fl.append(n); have += len(mv._unit_tokens(n)) * 4
        mv.follow = {sym: fl}


def process_row(row, cfile=None, cfg=None, asflags=None, keep=False):
    from common import clean_path
    t0 = time.time()
    TMP.mkdir(parents=True, exist_ok=True)
    os.environ["TMPDIR"] = str(TMP); tempfile.tempdir = str(TMP)     # every helper's temp files stay under work/fidelity/tmp
    td = tempfile.mkdtemp(prefix=row["id"].replace("/", "__") + "_", dir=TMP)
    rec = {"row": row["id"], "container": row["container"], "kind": row["kind"]}
    try:
        from slus_module_context import fingerprint
        module_before = fingerprint(row)
        cfile = Path(cfile) if cfile else clean_path(row)
        text = cfile.read_text(errors="replace")
        cfg = cfg or row["cfg"]
        rec["cfg"] = cfg
        try:
            from pin_census import sites_of
            rec["pins"] = len(sites_of(text))
        except Exception:
            rec["pins"] = None
        if row["kind"] == "slus":
            ctx, err = prepare_slus(row, cfile, cfg, row.get("row_asflags") or "" if asflags is None else asflags, td)
        else:
            ctx, err = prepare_overlay(row, cfile, cfg, asflags, td)
        if ctx is None:
            rec.update(status="error", err=("compile: " + str(err))[:300]); return rec
        rec["asflags"] = " ".join(a for a in ctx["as_args"][7:])
        rec["cell"] = ctx["cell"]
        rec["maspsx_exact"] = ctx["maspsx_exact"]; rec["proof"] = ctx["proof"]
        env = ctx["env"]
        # ---- maspsx leg, traced
        mo, err = run_maspsx(ctx["m_in"], ctx["as_args"], Path(td) / "m.o", env, trace=Path(td) / "tr.json")
        if mo is None:
            rec.update(status="error", err=("maspsx: " + err)[:300]); return rec
        tr = json.loads((Path(td) / "tr.json").read_text())
        rec["fired"] = tr["fired"]
        mv = View(read_elf(mo))
        if ctx["kind"] == "slus":
            from slus_module_context import membership, fingerprint
            module = membership(row)
            scope = (sorted(next(m["functions"] for m in module["members"] if m["id"] == row["id"]))
                     if module else sorted(mv.funcs))
            if module:
                rec["module"] = module["name"]
                rec["module_fingerprint"] = module_before
                rec["trace_scope"] = "whole-module"
                missing = set(scope) - set(mv.funcs)
                if missing:
                    rec.update(status="error", err="module member symbols missing: " + str(sorted(missing)))
                    return rec
            rec["selfcheck"] = _sha(mo) == _sha(ctx["pipeline_obj"])
        else:
            sym = ctx["symbol"]
            mv.add_unit(sym)
            mv.composite = {sym}
            shape_unit(mv, sym, len(ctx["retail"]))
            if sym not in mv.funcs:
                rec.update(status="error", err=f"target symbol {sym} is not a function in the maspsx object "
                                               f"({sorted(mv.funcs)[:4]})"); return rec
            scope = [sym]
            # the traced object reproduces the scorer's: its instruction stream, relocation fields
            # masked, equals the scorer's linked words (same length, same non-relocation bits)
            got = ctx["linked"]
            toks = mv.tokens(sym)
            if got is None:
                rec["selfcheck"] = None
            else:
                gw = [struct.unpack_from("<I", got, 4 * i)[0] for i in range(len(got) // 4)]
                rec["selfcheck"] = len(gw) == len(toks) and all(
                    (g & ~FIELD.get(t[1], 0) & 0xFFFFFFFF) == t[0] if t[1] else g == t[0] for g, t in zip(gw, toks))
        rec["funcs"] = len(scope)
        rec["words"] = sum(len(mv.tokens(f)) for f in scope)
        rec["maspsx_retail"] = retail_compare(mv, scope, ctx["kind"], ctx if ctx["kind"] == "overlay" else None)
        mr = rec["maspsx_retail"]
        if ctx["kind"] == "slus" and not rec["maspsx_exact"] and mr["diff"] == 0 and mr["masked"] == 0 and mr["checked"] == len(scope):
            # the pinned-object reference disagrees, but every word resolves to the retail SLUS
            rec["maspsx_exact"] = True; rec["proof"] = "retail-resolved"
        # ---- genuine legs
        g_srcs = {False: aspsx_input(ctx["g_src"]), True: aspsx_input(ctx["g_src"], equ=True)}
        alias = aliases(ctx["g_src"])
        modes, has_div = genuine_modes(ctx["g_src"], ctx["flags"])
        rec["has_div"] = has_div
        gen = {}; views = {}; allviews = {}
        for v in VERSIONS:
            best = None
            for fl, equ in modes:
                label = " ".join(fl[1:] + (["equ"] if equ else []))
                lnk, err = run_aspsx(g_srcs[equ], v, fl, td)
                if lnk is None:
                    kind = ("hilo" if "Syntax error in expression" in err and "%hi(" in ctx["g_src"] else
                            "open" if "Could not open" in err else "other")
                    cand = {"err": err, "err_kind": kind, "mode": label}
                    best = best or cand
                    continue
                try:
                    gv = View(read_lnk(lnk), mv, alias)
                    gv.composite = mv.composite
                    gv.follow = mv.follow
                    for f in scope:
                        gv.add_unit(f, mv)
                except Exception as exc:
                    best = best or {"err": f"LNK: {exc}"[:200], "mode": label}
                    continue
                c = compare_units(mv, gv, scope)
                allviews.setdefault(v, []).append(gv)
                cand = {"exact": c["exact"], "diff": c["diff"], "len": c["len_g"], "mode": label}
                if c["missing"]:
                    cand["missing"] = c["missing"][:3]
                if gv.obj.unknown:
                    cand["lnk_unknown"] = gv.obj.unknown[:2]
                rc = retail_compare(gv, scope, ctx["kind"], ctx if ctx["kind"] == "overlay" else None)
                cand["retail"] = [rc["diff"], rc["masked"]]                 # direct, positional: [differing, masked]
                if best is None or "err" in best or (c["exact"], -c["diff"]) > (best.get("exact"), -best.get("diff", 1 << 30)):
                    best = cand; views[v] = (gv, c)
            gen[v] = best
        rec["genuine"] = gen
        rec["exact_versions"] = [v for v in VERSIONS if gen[v].get("exact")]
        ok = [v for v in VERSIONS if v in views]
        if ok:
            bv = min(ok, key=lambda v: (not gen[v]["exact"], gen[v]["diff"], VERSIONS.index(v)))
            rec["best"] = bv
            gv, c = views[bv]
            if not c["exact"]:
                rec["classes"] = classify(c["regions"], mv, c["delay_only"])
                rec["first_diff"] = [[f, op, off] for f, op, _, _, off in c["regions"][:4]]
                # extern symbols maspsx/GNU as addressed $gp-relative (decision 3's list)
            # $gp-relative references to symbols the TU does NOT define (not even as .comm): the
            # small-extern model genuine ASPSX does not have (it $gp's only TU-defined small data)
            gpx = mv.gp_extern_names(scope)
            if gpx:
                rec["gp_externs"] = gpx[:40]; rec["n_gp_externs"] = len(gpx)
        # ---- attribution
        need = [v for v in ok if not gen[v]["exact"]]
        if need:
            rec["attrib"] = attribute(ctx, env, tr["fired"], mv, views, allviews, need, scope, td)
        if fingerprint(row) != module_before:
            rec.update(status="error", maspsx_exact=False, err="module inputs changed during measurement")
            return rec
        rec["status"] = "ok"
        return rec
    except Exception as exc:  # a harness failure is a record, never a crash of the run
        import traceback
        rec.update(status="error", err=("harness: " + "".join(traceback.format_exception_only(type(exc), exc)).strip())[:300])
        return rec
    finally:
        rec["secs"] = round(time.time() - t0, 1)
        if not keep:
            shutil.rmtree(td, ignore_errors=True)


def attribute(ctx, env, fired, mv, views, allviews, need, scope, td):
    """Re-run the maspsx leg with one behaviour removed at a time; report which removal makes it
    equal to the genuine object of each non-exact version (any of that version's modes)."""
    variants = {}
    for p in fired:
        variants["no:" + p] = dict(disable=[p])
    if len(fired) > 1:
        variants["no:all-fired"] = dict(disable=list(fired))
    variants["extern-abs"] = dict(strip_externs=True)
    if fired:
        variants["extern-abs+no:all-fired"] = dict(strip_externs=True, disable=list(fired))
    base_args = ctx["as_args"]
    for fl in base_args[7:]:
        variants["drop:" + fl] = dict(args=[a for a in base_args if a != fl])
    for vc in sorted(set(MASPSX_VCONF[v] for v in need if v in MASPSX_VCONF)):
        a = [f"--aspsx-version={vc}" if x == "--aspsx-version=2.79" else x for x in base_args]
        variants["asv:" + vc] = dict(args=a)
        variants[f"asv:{vc}+extern-abs" + ("+no:all-fired" if fired else "")] = dict(args=a, strip_externs=True, disable=list(fired))
    res = {}
    vviews = {}
    base_sha = _sha((Path(td) / "m.o").read_bytes())
    for name, spec in variants.items():
        o, err = run_maspsx(ctx["m_in"], spec.get("args", base_args), Path(td) / "v.o", env,
                            disable=spec.get("disable", ()), strip_externs=spec.get("strip_externs", False))
        if o is None:
            vviews[name] = None; continue
        if _sha(o) == base_sha:
            vviews[name] = "same"; continue
        vw = View(read_elf(o))
        vw.composite = mv.composite
        for f in scope:
            vw.add_unit(f)
        if ctx["kind"] == "overlay":
            shape_unit(vw, scope[0], len(ctx["retail"]))
        vw.follow = mv.follow
        vviews[name] = vw
    for v in need:
        gv, c0 = views[v]
        fixes, better = [], {}
        for name, vw in vviews.items():
            if vw is None or vw == "same":
                continue
            if name.startswith("asv:") and not name.startswith("asv:" + MASPSX_VCONF.get(v, "?")):
                continue
            c = min((compare_units(vw, g, scope) for g in allviews.get(v, [gv])), key=lambda c: (not c["exact"], c["diff"]))
            if c["exact"]:
                fixes.append(name)
            elif c["diff"] < c0["diff"]:
                better[name] = c["diff"]
        single = [f for f in fixes if "+" not in f]
        res[v] = {"base": c0["diff"], "fix": single or fixes}
        if not fixes and better:
            res[v]["better"] = dict(sorted(better.items(), key=lambda kv: kv[1])[:4])
    res["_nochange"] = sorted(k for k, vw in vviews.items() if vw == "same")
    return res


# ------------------------------------------------------------------------------------ controls
def run_controls(by):
    """The validation of docs/evidence/fidelity_step1_aspsx_diff.md, runnable as a regression check.
    Prints one line per control; returns the number of failures."""
    from common import clean_path
    fails = 0
    def report(name, ok, detail):
        nonlocal fails
        fails += (not ok)
        print(f"{'PASS' if ok else 'FAIL'}  {name:58s} {detail}", flush=True)

    # 1. casesi (positive, historical): work/maspsx_jtbl kept the objects the PRE-cddcc615 maspsx made
    #    from the real-switch text; the comparator must see the 5-word rewrite as a difference and the
    #    --preserve-casesi-at object as identical to genuine ASPSX
    jt = ROOT / "work/maspsx_jtbl"
    if (jt / "sw_base.o").exists():
        TMP.mkdir(parents=True, exist_ok=True)
        src = aspsx_input((jt / "sw.proc.s").read_text(errors="replace"))
        for tag, obj in (("default (5-word rewrite)", "sw_base.o"), ("--preserve-casesi-at", "sw_preserve.o")):
            mv = View(read_elf((jt / obj).read_bytes()))
            res = {}
            for v in ("2.56", "2.67", "2.79"):
                best = None
                for fl in (["-q", "-G0"], ["-q", "-G0", "-0"]):
                    lnk, err = run_aspsx(src, v, fl, TMP)
                    if lnk is None:
                        continue
                    c = compare_units(mv, View(read_lnk(lnk), mv))
                    best = c if best is None or c["diff"] < best["diff"] else best
                res[v] = best
            if tag.startswith("default"):
                ok = all(r and not r["exact"] and r["len_m"] == r["len_g"] + 1 for r in res.values())
                report(f"casesi 2026-09-14 maspsx {tag} != genuine", ok,
                       {v: (r["diff"], r["len_m"], r["len_g"], classify(r["regions"], mv, r["delay_only"])) for v, r in res.items()})
            else:
                ok = all(r and r["exact"] for r in res.values())
                report(f"casesi maspsx {tag} == genuine", ok, {v: r["diff"] for v, r in res.items()})
    # the live maspsx (after cddcc615) on the same real-switch text: now identical to genuine
    if (jt / "sw.c").exists():
        r = process_row(by["town/func_8080E994"], jt / "sw.c")
        report("casesi live maspsx on sw.c == genuine (patch landed)", bool(r.get("exact_versions")),
               f"exact {r.get('exact_versions')} maspsx_exact {r.get('maspsx_exact')}")
    # 2. d92c_genuine at 2.7.2-cdk: genuine 2.67/2.77 -0 reproduce RETAIL directly (no maspsx involved)
    cand = ROOT / "work/native_lane/r77_fable_splitaddr/cands/d92c_genuine.c"
    if cand.exists():
        r = process_row(by["slus/w_8003D92C"], cand, cfg="2.7.2-cdk")
        g = r.get("genuine", {})
        ok = all(g.get(v, {}).get("retail") == [0, 0] and g[v].get("mode") == "-0" for v in ("2.67", "2.77"))
        report("d92c_genuine @2.7.2-cdk: genuine 2.67/2.77 -0 == retail", ok,
               {v: (g.get(v, {}).get("retail"), g.get(v, {}).get("mode"), g.get(v, {}).get("err_kind")) for v in VERSIONS})
    # 3. in-tree positive controls (the sceptic's rows): the pass fires and its ablation == genuine
    for rid, p in (("slus/w_8004AB7C", "_sink_call_separated_la"), ("slus/w_80041AB0", "_split_funcaddr_la"),
                   ("slus/w_80043CD0", "_split_funcaddr_la")):
        r = process_row(by[rid])
        fx = (r.get("attrib") or {}).get(r.get("best"), {}).get("fix", [])
        report(f"{rid}: {p} fires, ablation == genuine", p in (r.get("fired") or []) and ("no:" + p) in fx,
               f"fired {r.get('fired')} exact {r.get('exact_versions')} fix {fx}")
    # 4. plain pin-free rows at every cell: exact under some version, or explained by one ablation
    from pin_census import sites_of
    per = {}
    for row in sorted(by.values(), key=lambda r: r["id"]):
        if (row["row_asflags"] or "") or row["kind"] != "overlay" and row["container"] != "slus":
            continue
        k = (row["container"], row["cell"])
        if len(per.setdefault(k, [])) >= 2:
            continue
        cp = clean_path(row)
        if cp.exists() and not sites_of(cp.read_text(errors="replace")):
            per[k].append(row["id"])
    for k, ids in sorted(per.items()):
        for rid in ids:
            r = process_row(by[rid])
            fx = (r.get("attrib") or {}).get(r.get("best"), {}).get("fix", [])
            ok = r.get("status") == "ok" and r.get("maspsx_exact") and r.get("selfcheck") and bool(r.get("exact_versions") or fx)
            report(f"plain {rid} [{r.get('cfg')}]", ok,
                   f"exact {r.get('exact_versions')} fix {fx} err {r.get('err')}")
    return fails


# ------------------------------------------------------------------------------------- journal
def load_journal():
    recs = {}
    if JOURNAL.exists():
        for l in JOURNAL.read_text().splitlines():
            if l.strip():
                try:
                    r = json.loads(l)
                except json.JSONDecodeError:
                    continue
                recs[r["row"]] = r
    return recs


def main():
    global JOURNAL
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--only", help="comma list of row ids, or @file with one id per line")
    ap.add_argument("--container")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--force", action="store_true", help="recompute even when the journal key matches")
    ap.add_argument("--one", help="run one row and print its record (no journal)")
    ap.add_argument("--cfile"); ap.add_argument("--cfg"); ap.add_argument("--asflags")
    ap.add_argument("--keep", action="store_true", help="--one: keep the temp dir")
    ap.add_argument("--controls", action="store_true", help="run the validation controls and exit")
    ap.add_argument("--journal", default=str(JOURNAL), help="journal path (default work/fidelity/aspsx_diff.jsonl)")
    ap.add_argument("--worker", help=argparse.SUPPRESS)
    a = ap.parse_args()
    JOURNAL = Path(a.journal)
    from common import rows, clean_path
    by = {r["id"]: r for r in rows()}
    if a.controls:
        sys.exit(1 if run_controls(by) else 0)
    if a.worker or a.one:
        rid = a.worker or a.one
        rec = process_row(by[rid], a.cfile, a.cfg, a.asflags, keep=a.keep)
        print(json.dumps(rec, separators=(",", ":")) if a.worker else json.dumps(rec, indent=1))
        return
    rs = list(by.values())
    if a.only:
        ids = [x.strip() for x in (Path(a.only[1:]).read_text().split() if a.only.startswith("@") else a.only.split(","))]
        rs = [by[i] for i in ids if i in by]
    if a.container:
        rs = [r for r in rs if r["container"] == a.container]
    if a.limit:
        rs = rs[:a.limit]
    fp = tool_fingerprint()
    journal = load_journal()
    todo = []
    for r in rs:
        cp = clean_path(r)
        text = cp.read_text(errors="replace") if cp.exists() else ""
        key = row_key(r, text, fp, r["cfg"], r.get("row_asflags") or "")
        old = journal.get(r["id"])
        if not a.force and old and old.get("key") == key and old.get("status") == "ok":
            continue
        todo.append((r, key))
    print(f"aspsx_diff: {len(rs)} rows selected, {len(todo)} to compute ({len(rs) - len(todo)} unchanged in the journal), "
          f"tool fingerprint {fp}", flush=True)
    JOURNAL.parent.mkdir(parents=True, exist_ok=True)

    def one(item):
        r, key = item
        p = subprocess.run(NICE + [sys.executable, str(Path(__file__)), "--worker", r["id"]],
                           capture_output=True, text=True, timeout=3600, cwd=str(ROOT))
        try:
            rec = json.loads(p.stdout.strip().splitlines()[-1])
        except Exception:
            rec = {"row": r["id"], "container": r["container"], "kind": r["kind"], "status": "error",
                   "err": ("worker: " + (p.stderr or p.stdout)[-300:])}
        rec["key"] = key; rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
        return rec

    t0 = time.time(); n = 0
    with ThreadPoolExecutor(max_workers=min(a.workers, 16)) as ex, open(JOURNAL, "a") as fh:
        for rec in ex.map(one, todo):
            fh.write(json.dumps(rec, separators=(",", ":")) + "\n"); fh.flush()
            journal[rec["row"]] = rec; n += 1
            if n % 200 == 0:
                el = time.time() - t0
                print(f"  {n}/{len(todo)} {el:.0f}s eta {el / n * (len(todo) - n):.0f}s", flush=True)
    # compact: the latest record per current row
    keep = {r["id"] for r in by.values()}
    with open(JOURNAL, "w") as fh:
        for rid in sorted(journal):
            if rid in keep:
                fh.write(json.dumps(journal[rid], separators=(",", ":")) + "\n")
    shutil.rmtree(TMP, ignore_errors=True)
    print(f"aspsx_diff: done {n} rows in {time.time() - t0:.0f}s -> {JOURNAL}", flush=True)


if __name__ == "__main__":
    main()
