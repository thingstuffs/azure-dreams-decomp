#!/usr/bin/env python3
"""Portability lint for the byte-matching decomp -> PC-port pipeline (ROADMAP §3 D/E).

Matched C has to compile for the eventual native port. Several constructs byte-match
on MIPS but do NOT cross-compile when left UNGUARDED. See
docs/asm_pinning_portability_analysis.md for the full census this lint enforces.

ABSOLUTE-HARD classes (always refuse a NEW candidate, baseline-independent):

  1. MIPS hardware-register pins used as an inline-asm OPERAND -- x86 gcc
     HARD-ERRORS ("invalid register name for 'v'"). A standalone pin compiles (the
     name is silently dropped) but still carries a dead MIPS-ism.
  2. Instruction-emitting inline asm -- `__asm__("lhu ...")`. Never allowed: it
     transcribes the target rather than decompiling it (tools/match.py already
     downgrades such a byte-match to NO MATCH).

BASELINE-TRACKED classes (grandfathered via config/portability_baseline.json;
a NEW landing is refused only when its per-file count EXCEEDS the committed
baseline -- i.e. it ADDS scaffolding an existing function did not have):

  RAW_PIN           any raw `register T v asm("$N")` / `__asm`/`__asm__` register
                    declaration NOT routed through the guarded ASM_REG/LOCAL_ASM_REG
                    macros. BLOCKING on exceed.
  UNSANCTIONED_ASM  any empty/inline-asm construct written literally in the source
                    -- direct `__asm__ __volatile__("" ...)` barriers, empty-asm
                    macro definitions, and local wrapper macros (PIN_KEEP, TF14_HOLD,
                    KEEP_REG, COMPILER_MEMORY_BARRIER, TAILSLOT_KEEP, LEGACY_* ...).
                    The SANCTIONED include/common.h macros (ASM_REG, the ASM_KEEP
                    family, ASM_PAGEBASE_PIN, ASM_TAILSLOT_PIN[_TIED],
                    ASM_SCHED_BARRIER + their NON_MATCHING forms)
                    are used by NAME and never appear as a literal here, so they are
                    not flagged. BLOCKING on exceed.

PORT-CONTRACT class (checked at LAND time, self-grandfathering):

  PORT_COMPILE      the candidate does not survive the port build's own front end
                    (`gcc -m32 -DNON_MATCHING -Iinclude -fsyntax-only`). The text
                    classes above catch MIPS-isms the port cannot express; this one
                    catches C that simply is not there once -DNON_MATCHING compiles
                    the guarded macros away -- a carrier whose DECLARATION lives in
                    the matching-only arm of an `#ifndef NON_MATCHING` while a USE
                    survives, a type that only the matching arm defines, and so on.
                    BLOCKING, except when the row already committed at the
                    destination path fails the same probe (then the shape predates
                    the candidate and the ratchet must not block it).

DEBT class (counted for burn-down, NEVER blocks a landing):

  ADDR_ALIAS        `.set NAME, 0xADDR` fixed-address binds and `.globl NAME`
                    aliases. The `__asm__(".set D_XXXX, 0xXXXX")` absolute-bind
                    idiom is an allowed landing construct; reported for the
                    eventual PC symbol/memory model, not refused.

FIX for RAW_PIN/UNSANCTIONED_ASM: guard MIPS pins with ASM_REG()/ASM_KEEP()
(include/common.h) so the -DNON_MATCHING port build compiles portable plain C, or
restructure to a pure-C shape needing no pin.

Usage:
  tools/portability_lint.py                 # scan src/*.c, print report
  tools/portability_lint.py src/w_X.c ...   # scan specific files
  tools/portability_lint.py --all           # scan every landed source root
  tools/portability_lint.py --strict        # also FAIL on SOFT standalone pins
  tools/portability_lint.py --port-compile  # also run + FAIL on the PORT_COMPILE probe
  tools/portability_lint.py --write-baseline # regenerate config/portability_baseline.json
Exit: 0 clean, 1 HARD/baseline-exceed findings (or SOFT under --strict), 2 usage error.
"""
from __future__ import annotations
import argparse
import glob
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))

# The active landed-source roots the census/baseline covers.
SCAN_ROOTS = (
    "src",
    "overlays/main/first_pass_matched",
    "overlays/town/first_pass_matched",
    "overlays/dungeon/first_pass_matched",
    "overlays/dungeon_engine/first_pass_matched",
    "overlays/ovmovie/first_pass_matched",
)

BASELINE_PATH = os.path.join(ROOT, "config", "portability_baseline.json")
CLASS_NAMES = ("RAW_PIN", "UNSANCTIONED_ASM", "ADDR_ALIAS")
# RAW_PIN / UNSANCTIONED_ASM refuse a landing on baseline-exceed; ADDR_ALIAS never does.
BLOCKING_CLASSES = ("RAW_PIN", "UNSANCTIONED_ASM")

# A RAW (unguarded) MIPS register pin. Guarded pins use ASM_REG(...)/LOCAL_ASM_REG(...)
# -> the UPPERCASE macro name never matches the lowercase asm keyword alternation, so
# guarded pins are excluded by design. The `__asm__`/`__asm` spellings are included so
# the raw pin `register u8 *p __asm__("$6")` is not missed (census regex gap).
PIN_RE = re.compile(
    r'register\b[^;{}]*?\b(\w+)\s+(?:__asm__|__asm|asm)\s*\(\s*"(\$[^"]+)"\s*\)')
# Any inline-asm keyword that opens a paren (statement OR the pin decl above).
ASM_KW_RE = re.compile(r'\b(?:__asm__|__asm|asm)\b\s*(?:volatile|__volatile__)?\s*\(')
# A literal empty-asm construct: `asm|__asm|__asm__ [volatile] ("" ...)`. Matches the
# direct barriers and the matching-side bodies of local keep/barrier wrapper macros;
# does NOT match the sanctioned macros, which are used by name (no literal here), nor a
# pin (`asm("$2")`), nor a `.set`/instruction template (both start with a non-`"` char).
EMPTY_ASM_RE = re.compile(
    r'\b(?:__asm__|__asm|asm)\b\s*(?:__volatile__|volatile)?\s*\(\s*""')
# Fixed-address assembler aliases: `.set NAME, 0xADDR` binds and `.globl NAME` aliases.
# Assembler mode directives (`.set noat`, `.set noreorder`, ...) carry no address and
# are excluded.
ADDR_ALIAS_RE = re.compile(
    r'\.set\s+[A-Za-z_]\w*\s*,\s*0x[0-9A-Fa-f]+|\.globl\s+[A-Za-z_]\w*')


def _strip_c_comments(src: str) -> str:
    src = re.sub(r'/\*.*?\*/', ' ', src, flags=re.DOTALL)
    src = re.sub(r'//[^\n]*', ' ', src)
    return src


def _balanced(src: str, open_idx: int) -> str | None:
    depth = 0
    for i in range(open_idx, len(src)):
        if src[i] == '(':
            depth += 1
        elif src[i] == ')':
            depth -= 1
            if depth == 0:
                return src[open_idx + 1:i]
    return None


def instruction_fragments(src: str) -> list[str]:
    """Inline-asm templates that emit real instructions (transcription). Excludes
    "" barriers, .set binds, bare labels, and single register tokens."""
    frags = []
    for m in ASM_KW_RE.finditer(src):
        body = _balanced(src, m.end() - 1)
        if body is None:
            continue
        parts = re.findall(r'"((?:[^"\\]|\\.)*)"', body.split(':')[0])
        tmpl = " ".join(parts).replace("\\n", " ").replace("\\t", " ").strip()
        if not tmpl or tmpl.startswith(".") or re.fullmatch(r'\$?\w+', tmpl) \
                or re.fullmatch(r'[A-Za-z_]\w*:', tmpl):
            continue
        frags.append(tmpl)
    return frags


def classify_src(src: str) -> dict:
    """Return {raw_pins, coupled, frags} for a C source STRING."""
    src = _strip_c_comments(src)
    raw_pins = PIN_RE.findall(src)                      # [(name, reg), ...]
    pin_names = {n for n, _ in raw_pins}
    pin_spans = [(m.start(), m.end()) for m in PIN_RE.finditer(src)]
    in_pin = lambda pos: any(s <= pos < e for s, e in pin_spans)
    coupled = set()
    for m in ASM_KW_RE.finditer(src):
        if in_pin(m.start()):                           # this asm(...) IS a pin decl
            continue
        body = _balanced(src, m.end() - 1)
        if not body or ':' not in body:                 # basic asm / no operands
            continue
        operands = body[body.index(':'):]               # extended-asm operand region
        for n in pin_names:
            if re.search(r'\b' + re.escape(n) + r'\b', operands):
                coupled.add(n)
    return {"raw_pins": raw_pins, "coupled": sorted(coupled),
            "frags": instruction_fragments(src)}


def classify_file(path: str) -> dict:
    """Return {raw_pins, coupled, frags} for one C file."""
    return classify_src(open(path, encoding="utf-8", errors="replace").read())


def class_counts(src: str) -> dict:
    """Per-file occurrence counts for the baseline-tracked classes."""
    s = _strip_c_comments(src)
    return {
        "RAW_PIN": len(PIN_RE.findall(s)),
        "UNSANCTIONED_ASM": len(EMPTY_ASM_RE.findall(s)),
        "ADDR_ALIAS": len(ADDR_ALIAS_RE.findall(s)),
    }


def hard_findings(src: str) -> list[str]:
    """ABSOLUTE-HARD (won't cross-compile) issues in a C source string: instruction
    fragments and unguarded pins used as asm operands. Empty list = no hard block.
    Baseline-independent; used by integrate.py/land routes to refuse a candidate."""
    c = classify_src(src)
    out = [f'inline-asm instruction fragment: "{f}"' for f in c["frags"]]
    out += [f'unguarded pin `register {n} asm(...)` used as an asm operand (x86 hard-error)'
            for n in c["coupled"]]
    return out


# ---------------------------------------------------------------------------
# PORT_COMPILE -- the port build's own front end, run over ONE candidate.
#
# WHY THIS EXISTS.  The classes above are text classifiers: they know which
# MIPS-isms the port cannot express.  They cannot know whether the C that is
# LEFT once -DNON_MATCHING compiles the guarded macros away is still valid C.
# port/tools/gen_sources.py -> the port build is the only thing that ever found
# that out, i.e. a day or more after the landing, in a build log 2,000 lines
# long.  This probe is the same question asked at land time, for 16 ms.
#
# The flags mirror port/Makefile's GAME_CFLAGS (the phase-2 recipe) minus the
# codegen ones: -m32 because the port links i686, -DNON_MATCHING because that
# is the port's build mode, -Iinclude for common.h, -w because a landed row is
# gcc-2.x C and warns freely on a modern front end.  -fsyntax-only is
# deliberate here (unlike tools/port_gate.py, which needs real allocation to
# surface `invalid register name`): the classes THIS probe owns are all
# front-end, and 16 ms is what makes it affordable on the landing path.
# ---------------------------------------------------------------------------
PORT_COMPILE_FLAGS = ["-DNON_MATCHING", "-Iinclude", "-w", "-fsyntax-only",
                      "-fno-diagnostics-color"]
_M32_OK: bool | None = None


def _m32_ok() -> bool:
    """Is the i686 multilib present?  Cached; the port links -m32, but a host
    without the 32-bit headers must degrade to a 64-bit probe, never to a
    false refusal."""
    global _M32_OK
    if _M32_OK is None:
        try:
            with tempfile.NamedTemporaryFile("w", suffix=".c", delete=False) as fh:
                fh.write("int main(void){return 0;}\n")
                probe_path = fh.name
            _M32_OK = subprocess.run(
                ["gcc", "-m32", "-fsyntax-only", probe_path],
                capture_output=True).returncode == 0
            os.unlink(probe_path)
        except (OSError, subprocess.SubprocessError):
            _M32_OK = False
    return _M32_OK


def port_compile_errors(src: str, root: str | None = None) -> list[str]:
    """`error:` lines from the port front end on a C source STRING. Empty list =
    the port build's front end accepts it. Fail-OPEN (empty) when no gcc is
    usable: a missing toolchain must not manufacture a refusal."""
    root = root or ROOT
    if shutil.which("gcc") is None:
        return []
    flags = (["-m32"] if _m32_ok() else []) + PORT_COMPILE_FLAGS
    tmp = None
    try:
        # The temp file lives OUTSIDE the repo (nothing is written into a tree
        # agents search); `cwd=root` is what makes -Iinclude resolve, and a
        # landed TU only ever quotes common.h, which -Iinclude serves.
        with tempfile.NamedTemporaryFile(
                "w", suffix=".c", delete=False, encoding="utf-8") as fh:
            fh.write(src)
            tmp = fh.name
        r = subprocess.run(["gcc"] + flags + [tmp],
                           cwd=root, capture_output=True, text=True)
        if r.returncode == 0:
            return []
        return [ln.strip().replace(tmp, "<candidate>")
                for ln in r.stderr.splitlines() if "error:" in ln]
    except (OSError, subprocess.SubprocessError):
        return []                       # fail-open, as above
    finally:
        if tmp:
            try:
                os.unlink(tmp)
            except OSError:
                pass


def port_compile_refusals(src: str, dest_relpath: str,
                          root: str | None = None) -> list[str]:
    """Blocking PORT_COMPILE findings for ONE candidate landing at dest_relpath.

    SELF-GRANDFATHERING, the same one-way-ratchet rule the baseline classes use:
    if the row ALREADY committed at dest_relpath fails the identical probe, the
    shape predates this candidate and must not block it. Today that covers the
    12 landed type-conflict TUs port/tools/gen_sources.py carries a TARGETED
    rewrite for -- they are un-compilable as tracked ON PURPOSE and the port
    builds a rewritten copy instead."""
    root = root or ROOT
    errs = port_compile_errors(src, root)
    if not errs:
        return []
    current = os.path.join(root, dest_relpath)
    if os.path.isfile(current):
        with open(current, encoding="utf-8", errors="replace") as f:
            if port_compile_errors(f.read(), root):
                return []               # grandfathered: the landed row fails too
    return [f"PORT_COMPILE: the -DNON_MATCHING port build rejects this candidate "
            f"({dest_relpath}): {errs[0]}"]


# ---------------------------------------------------------------------------
# Baseline (config/portability_baseline.json): {relpath: {CLASS: count}}.
# The lint refuses a landing only when a file's blocking-class count EXCEEDS its
# committed baseline. Regeneration is explicit (--write-baseline), never automatic.
# ---------------------------------------------------------------------------
def load_baseline(path: str | None = None) -> dict:
    try:
        with open(path or BASELINE_PATH, encoding="utf-8") as f:
            return json.load(f)
    except FileNotFoundError:
        return {}


def all_source_files() -> list[str]:
    files: list[str] = []
    for root in SCAN_ROOTS:
        files += sorted(glob.glob(os.path.join(ROOT, root, "*.c")))
    return files


def build_baseline(files: list[str]) -> dict:
    base: dict[str, dict] = {}
    for f in files:
        counts = {k: v for k, v in class_counts(
            open(f, encoding="utf-8", errors="replace").read()).items() if v}
        if counts:
            base[os.path.relpath(f, ROOT)] = counts
    return dict(sorted(base.items()))


def baseline_exceed(src: str, dest_relpath: str, baseline: dict) -> list[str]:
    """Blocking baseline-exceed findings for ONE candidate landing at dest_relpath.
    A dest absent from the baseline has an implicit count of 0, so ANY blocking-class
    occurrence in a genuinely new function is refused (RAW_PIN/UNSANCTIONED_ASM
    refused like HARD for new landings)."""
    base = baseline.get(dest_relpath, {})
    counts = class_counts(src)
    out = []
    for cls in BLOCKING_CLASSES:
        allowed = base.get(cls, 0)
        if counts[cls] > allowed:
            out.append(
                f"{cls} count {counts[cls]} exceeds grandfathered baseline "
                f"{allowed} for {dest_relpath}")
    return out


def landing_refusals(src: str, dest_relpath: str,
                     baseline: dict | None = None) -> list[str]:
    """All reasons to REFUSE landing ONE candidate: absolute-HARD (instruction
    fragments / coupled pins), blocking baseline-exceed, and the PORT_COMPILE
    probe. Empty list = landable.
    This is the single gate the landing routes call, matching integrate.py's refusal
    behavior."""
    if baseline is None:
        baseline = load_baseline()
    return (hard_findings(src) + baseline_exceed(src, dest_relpath, baseline)
            + port_compile_refusals(src, dest_relpath))


def _write_baseline() -> int:
    files = all_source_files()
    base = build_baseline(files)
    os.makedirs(os.path.dirname(BASELINE_PATH), exist_ok=True)
    with open(BASELINE_PATH, "w", encoding="utf-8") as f:
        json.dump(base, f, indent=1, sort_keys=True)
        f.write("\n")
    totals = {cls: 0 for cls in CLASS_NAMES}
    file_hits = {cls: 0 for cls in CLASS_NAMES}
    for counts in base.values():
        for cls in CLASS_NAMES:
            n = counts.get(cls, 0)
            totals[cls] += n
            file_hits[cls] += 1 if n else 0
    print(f"wrote {os.path.relpath(BASELINE_PATH, ROOT)}: {len(base)} tracked files "
          f"across {len(files)} scanned.")
    for cls in CLASS_NAMES:
        print(f"  {cls}: {totals[cls]} sites / {file_hits[cls]} files")
    return 0


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("files", nargs="*", help="C files (default: src/*.c)")
    ap.add_argument("--all", action="store_true",
                    help="scan every landed source root, not just src/*.c")
    ap.add_argument("--strict", action="store_true",
                    help="also FAIL on SOFT standalone unguarded pins")
    ap.add_argument("--port-compile", action="store_true",
                    help="also run the PORT_COMPILE probe (gcc -DNON_MATCHING "
                         "-fsyntax-only) and FAIL on its errors. Off by default so "
                         "the report stays a pure text scan; landing_refusals() "
                         "always runs it.")
    ap.add_argument("--write-baseline", action="store_true",
                    help="regenerate config/portability_baseline.json and exit")
    ap.add_argument("--baseline", default=None, help="baseline JSON path override")
    a = ap.parse_args()

    if a.write_baseline:
        return _write_baseline()

    if a.files:
        files = a.files
    elif a.all:
        files = all_source_files()
    else:
        files = sorted(glob.glob(os.path.join(ROOT, "src", "*.c")))
    baseline = load_baseline(a.baseline)

    hard_frag, hard_pin, soft = [], [], []
    exceed = []          # (rel, cls, count, allowed)  -- blocking
    port_fail = []       # (rel, first error line)     -- blocking under --port-compile
    addr_total = 0
    addr_files = 0
    for f in files:
        rel = os.path.relpath(f, ROOT)
        src = open(f, encoding="utf-8", errors="replace").read()
        c = classify_src(src)
        for fr in c["frags"]:
            hard_frag.append((rel, fr))
        for name, reg in c["raw_pins"]:
            (hard_pin if name in c["coupled"] else soft).append((rel, name, reg))
        counts = class_counts(src)
        base = baseline.get(rel, {})
        for cls in BLOCKING_CLASSES:
            if counts[cls] > base.get(cls, 0):
                exceed.append((rel, cls, counts[cls], base.get(cls, 0)))
        if counts["ADDR_ALIAS"]:
            addr_total += counts["ADDR_ALIAS"]
            addr_files += 1
        if a.port_compile:
            errs = port_compile_errors(src)
            if errs:
                port_fail.append((rel, errs[0]))

    def block(title, rows, fmt):
        if rows:
            print(f"\n{title} ({len(rows)}):")
            for r in rows:
                print("  " + fmt(r))

    block("HARD: instruction-emitting inline asm (transcription; match.py NO MATCH)",
          hard_frag, lambda r: f'{r[0]}: __asm__("{r[1]}")')
    block("HARD: unguarded pin used as asm operand (x86 gcc hard-errors)",
          hard_pin, lambda r: f'{r[0]}: register {r[1]} asm("{r[2]}")  -> guard with ASM_REG/ASM_KEEP')
    block("BLOCKING: baseline-exceed (new/added portability scaffolding)",
          exceed, lambda r: f'{r[0]}: {r[1]} {r[2]} > baseline {r[3]}')
    block("BLOCKING: PORT_COMPILE (the -DNON_MATCHING port front end rejects the TU)",
          port_fail, lambda r: f'{r[0]}: {r[1]}')
    block("SOFT: standalone unguarded pin (compiles on x86, MIPS name dropped)",
          soft, lambda r: f'{r[0]}: register {r[1]} asm("{r[2]}")')

    n_hard = len(hard_frag) + len(hard_pin)
    print(f"\nportability_lint: {n_hard} HARD, {len(exceed)} baseline-exceed, "
          f"{len(port_fail)} PORT_COMPILE, "
          f"{len(soft)} SOFT, {addr_total} ADDR_ALIAS debt sites "
          f"(across {addr_files} files) over {len(files)} files.")
    if n_hard:
        print("  -> HARD findings will not cross-compile unguarded. Fix before Phase-E port.")
    if exceed:
        print("  -> baseline-exceed: guard MIPS pins with ASM_REG/ASM_KEEP (include/common.h) "
              "or restructure to pure C; --write-baseline only after an intended change.")
    if port_fail:
        print("  -> PORT_COMPILE: run `make -C port` for the full diagnostic; a TU that "
              "port/tools/gen_sources.py carries a TARGETED rewrite for is expected here.")
    fail = n_hard or exceed or port_fail or (a.strict and soft)
    return 1 if fail else 0


if __name__ == "__main__":
    raise SystemExit(main())
