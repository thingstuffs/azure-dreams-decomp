#!/usr/bin/env python3
"""Compile a C function through the Azure Dreams matching pipeline and compare
its .text against the retail bytes.

  gcc -S  ->  maspsx (--aspsx-version)  ->  mipsel-linux-gnu-as  ->  objcopy .text

Target bytes are pulled from baserom/slus_006.14 using the function's extent as
recorded in the split asm (asm/**/*.s). Fingerprint targets should be
relocation-free (no %hi/%lo global refs, no calls) so the unlinked .text matches.

Usage:
  tools/match.py <func_name> <cfile> [--gcc 2.7.2] [--opt O2] [--aspsx 2.56]
  tools/match.py <func_name> <cfile> --sweep [--opt all] [--aspsx all]
"""
import argparse, ast, subprocess, re, sys, os, glob, tempfile, json, time, hashlib, importlib.util, shutil
from difflib import SequenceMatcher
import live_truth  # cycle-safe: live_truth's project imports are lazy

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
BASEROM = os.path.join(ROOT, "baserom/slus_006.14")
VENV_PY = os.path.join(ROOT, ".venv/bin/python")
# $AZURE_MASPSX overrides the assembler-macro driver for a *measurement* run
# (e.g. the name-blind maspsx copy used by the bridge-remediation audit,
# work/bridge_remediation_20260905/C_maspsx_nameblind/).  Unset -> the live
# toolchain copy, i.e. default behaviour is byte-identical.  Every consumer of
# the scored pipeline reaches maspsx through this one constant, and $AZURE_MASPSX
# is inherited by the subprocesses (overlay_func_compare, aligned_score) that
# import this module, so a single export covers the whole chain.
MASPSX  = os.environ.get("AZURE_MASPSX") or os.path.join(ROOT, "toolchain/maspsx/maspsx.py")
COMPILERS = sorted(glob.glob(os.path.join(ROOT, "toolchain/compilers/gcc-*")))


def parse_config_label(label):
    """Canonical parser for a compiler-config label -> (gcc_ver, gcc_flags).

    Two dialects circulate and both must parse identically everywhere
    (overlay_local_gate, overlay_func_compare, worker-reported configs):
      space dialect:  "2.7.2-cdk -G0 -fno-schedule-insns"   (gate/results rows)
      plus dialect:   "2.8.1+-G0 -fno-schedule-insns"       (compare/sweep labels)
    A "-G0" glued to the version token ("2.8.1-G0") is a flag, not a version.
    """
    label = (label or "").strip()
    if not label:
        return "2.7.2", ""
    head, *rest = label.split(None, 1)
    flags = [rest[0].strip()] if rest else []
    if "+" in head:
        head, plus = head.split("+", 1)
        if plus:
            flags.insert(0, plus)
    if head.endswith("-G0"):
        head = head[:-3]
        flags.insert(0, "-G0")
    return head, " ".join(f for f in flags if f)


AS = "mipsel-linux-gnu-as"
LD = "mipsel-linux-gnu-ld"
OBJCOPY = "mipsel-linux-gnu-objcopy"
OBJDUMP = "mipsel-linux-gnu-objdump"

def _default_func_as_flags():
    """Derive per-function maspsx defaults from configure.py's AS_FLAGS table."""
    path = os.path.join(ROOT, "tools", "configure.py")
    with open(path) as f:
        tree = ast.parse(f.read(), filename=path)
    for node in tree.body:
        if not isinstance(node, ast.Assign):
            continue
        if not any(isinstance(t, ast.Name) and t.id == "AS_FLAGS" for t in node.targets):
            continue
        table = ast.literal_eval(node.value)
        out = {}
        for cfile, flags in table.items():
            stem = os.path.splitext(os.path.basename(cfile))[0]
            if stem.startswith("w_") and re.fullmatch(r"w_[0-9A-Fa-f]{8}", stem):
                out[f"func_{stem[2:].upper()}"] = flags
            elif re.fullmatch(r"func_[0-9A-Fa-f]{8}", stem):
                out[f"func_{stem[5:].upper()}"] = flags
        return out
    return {}

DEFAULT_FUNC_AS_FLAGS = _default_func_as_flags()
UNDEF_SYMS = os.path.join(ROOT, "config", "generated", "slus_006.14.undefined_syms.txt")
UNDEF_FUNCS = os.path.join(ROOT, "config", "generated", "slus_006.14.undefined_funcs.txt")
NAMED_SYMS = os.path.join(ROOT, "config", "slus_006.14.symbols.txt")
GP_VALUE = 0x80080994  # runtime $gp; needed to resolve %gp_rel(D_x)($gp) references

# code segment: file offset 0x800 maps to vram 0x8002D000
VRAM_BASE = 0x8002D000
FILE_BASE = 0x800

def vram_of(file_off):
    return VRAM_BASE + (file_off - FILE_BASE)

def func_extent(name):
    for f in glob.glob(os.path.join(ROOT, "asm/**/*.s"), recursive=True):
        with open(f, encoding="utf-8", errors="replace") as source:
            lines = source.read().splitlines()
        for i, l in enumerate(lines):
            if re.match(rf"glabel {name}\b", l):
                words = []
                for l2 in lines[i + 1:]:
                    if l2.startswith("endlabel") or re.match(r"glabel ", l2):
                        break
                    m = re.match(r"\s*/\*\s*([0-9A-Fa-f]+)\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]{8})", l2)
                    if m:
                        words.append((int(m.group(1), 16), m.group(2)))
                if words:
                    return words[0][0], len(words) * 4
    return None, None

def target_bytes(name):
    start, length = func_extent(name)
    if start is None:
        sys.exit(f"function {name} not found in asm/")
    with open(BASEROM, "rb") as d:
        d.seek(start)
        return d.read(length), start, length

FUNC_SIZES_JSON = os.path.join(ROOT, "config", "func_sizes.json")

def _func_names():
    if os.path.exists(FUNC_SIZES_JSON):
        try:
            with open(FUNC_SIZES_JSON, encoding="utf-8") as source:
                values = json.load(source)
            return [k for k in values if re.fullmatch(r"func_[0-9A-Fa-f]+", k)]
        except Exception:
            pass
    return []

FUNC_NAMES = _func_names()

def _named_syms():
    """Parse config/slus_006.14.symbols.txt -> [(name, addr_hex)] of already-NAMED
    library funcs/data (DrawSync, InitPAD, gCdMode, ...) that are NOT in the
    auto-generated undefined_syms/undefined_funcs lists. Feeding these to `ld` lets
    a function that CALLS a named library routine (or references a named data symbol)
    link cleanly instead of failing R_MIPS_26 ('relocation truncated to fit') and
    silently falling back to the unlinked object -> spurious NO MATCH on unrelated
    %hi/%lo globals. The `// type:...` comments are stripped (GNU ld chokes on `//`)."""
    out = []
    if os.path.exists(NAMED_SYMS):
        try:
            with open(NAMED_SYMS, encoding="utf-8") as source:
                for line in source:
                    line = line.split("//")[0]
                    m = re.match(r"\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;", line)
                    if m:
                        out.append((m.group(1), m.group(2)))
        except Exception:
            pass
    return out

NAMED_SYMS_LIST = _named_syms()

def _prior_assembly_path(destination):
    """Where the previous published listing moves when a fresh compile is starting.

    `<f>.latest.s` -> `<f>.last.s` and `<f>.latest.maspsx.s` -> `<f>.last.maspsx.s`,
    mirroring the `results/<func>.last.c` snapshot the wave lanes already keep.
    """
    head, base = os.path.split(destination)
    if ".latest." in base:
        return os.path.join(head, base.replace(".latest.", ".last.", 1))
    return destination + ".last"


def maspsx_assembly_path(asm_output):
    """Derived sibling of --asm-output holding the text GNU as actually consumed.

    DERIVED, never a second CLI flag: every caller that already passes --asm-output
    (both verifier branches, both prompt templates) gets this listing with zero extra
    wiring, so it cannot be present on one branch and missing on the other -- which is
    exactly how the original --asm-output shipped overlay-blind for 62 waves (646e500).

    NOTE THE TOKEN ORDER. `<f>.maspsx.latest.s` would CONTAIN the substring
    `.latest.s`, so every existing `*.latest.s` glob and transcript read-counter would
    silently count maspsx reads as gcc-listing reads and corrupt the 299-read
    adoption baseline. `<f>.latest.maspsx.s` does not.
    """
    if asm_output.endswith(".latest.s"):
        return asm_output[: -len(".latest.s")] + ".latest.maspsx.s"
    root, ext = os.path.splitext(asm_output)
    return root + ".maspsx" + (ext or ".s")


def _publish_maspsx_listing(common, source_s, asm_output):
    """Re-render the gcc -S through maspsx WITHOUT assembling, and publish the text.

    This is the assembly GNU as actually consumes. It matters because gcc -S is NOT
    indexable by emitted word -- maspsx inserts the real nops (gcc -S carries none,
    only `#nop` hints) and rewrites delay slots -- so a worker citing "generated word
    N" from latest.s is counting in a file where counting is invalid.

    BEST-EFFORT BY CONTRACT: it must never change `got`, `err`, stdout or the exit
    code, so the whole body is swallowed (same discipline as _beacon()). A separate
    transform-only run is used rather than --print-output on the scored call, because
    --print-output writes to the SAME stderr that live_truth.gcc_diagnostic parses for
    the `as:` message; keeping the scored subprocess byte-identical is worth 0.1 s.
    """
    try:
        # maspsx honours MASPSX_LEAD* env switches; strip them so the published
        # listing always shows the same codegen the scored call assembled.
        env = {k: v for k, v in os.environ.items() if not k.startswith("MASPSX_LEAD")}
        with open(source_s) as fin:
            r = subprocess.run(common, stdin=fin, capture_output=True, env=env)
        if r.returncode != 0 or not r.stdout:
            return
        dest = maspsx_assembly_path(asm_output)
        parent = os.path.dirname(os.path.abspath(dest))
        os.makedirs(parent, exist_ok=True)
        tmp = os.path.join(parent, f".{os.path.basename(dest)}.{os.getpid()}.tmp")
        try:
            with open(tmp, "wb") as out:
                out.write(r.stdout)
            os.replace(tmp, dest)          # atomic, mirrors _publish_compiler_assembly
        finally:
            try:
                os.unlink(tmp)
            except FileNotFoundError:
                pass
    except Exception:
        pass


def _publish_compiler_assembly(source, destination):
    """Atomically preserve gcc's raw ``-S`` output outside the temp build dir."""
    destination = os.path.abspath(destination)
    parent = os.path.dirname(destination)
    os.makedirs(parent, exist_ok=True)
    tmp = os.path.join(parent, f".{os.path.basename(destination)}.{os.getpid()}.tmp")
    try:
        shutil.copyfile(source, tmp)
        os.replace(tmp, destination)
    finally:
        try:
            os.unlink(tmp)
        except FileNotFoundError:
            pass


def _sext16(v):
    return v - 0x10000 if v & 0x8000 else v


_LOCAL_DATA_SECTIONS = (".rodata", ".rdata")


def _local_section_placements(obj, target, vram, retail_text):
    """Retail-derived link placement for compiler-local data sections (switch
    jump tables) referenced from .text — the jtbl Option-D fix (2026-07-20).

    The isolated link maps only .text at the function's vram, so a local
    .rodata/.rdata switch table lands as an orphan after .text and its %hi/%lo
    base words can never equal retail's when retail placed the table elsewhere
    (tools/learnings/tooling.md:86). Derive retail's placement from evidence:
    for every HI16/LO16 reloc pair against the section symbol, the words at
    the same function-relative offsets in RETAIL bytes must carry the SAME
    instruction shell (upper 16 bits equal); retail's combined immediate minus
    the object's encoded addend gives the section base. Every pair must agree
    (one placement resolves every reference), the base must be word-aligned,
    and no placed section may overlap the .text mapping. Any anomaly -> {}
    (today's orphan behavior, honest mismatch). The placement grants exactly
    the degree of freedom the real linker had; every non-immediate bit is
    still compared strictly, so a wrong dispatch shape cannot ride in on it.
    """
    # The target's text section is ".text" in the isolated pipeline and
    # ".text.<func>" under the gate's function-sections compile; scan relocs
    # from, and read compiled words out of, whichever one holds the symbol.
    sym = symbol_info(obj, target) if target else None
    if not sym or not str(sym.get("section", "")).startswith(".text"):
        return {}
    text_sect = sym["section"]
    r = subprocess.run([OBJDUMP, "-r", obj], capture_output=True)
    if r.returncode != 0:
        return {}
    recs, in_text = [], False
    for line in r.stdout.decode(errors="replace").splitlines():
        if line.startswith("RELOCATION RECORDS FOR"):
            in_text = line.startswith(f"RELOCATION RECORDS FOR [{text_sect}]")
            continue
        m = re.match(r"([0-9A-Fa-f]{8})\s+(R_MIPS_\w+)\s+(\S+)", line)
        if in_text and m:
            recs.append((int(m.group(1), 16), m.group(2), m.group(3)))
    referenced = {sym_name for _, _, sym_name in recs
                  if sym_name in _LOCAL_DATA_SECTIONS}
    if not referenced:
        return {}
    sym_off = sym["value"] - (section_vma(obj, text_sect) or 0)
    with tempfile.NamedTemporaryFile(suffix=".pretext") as tf:
        subprocess.run([OBJCOPY, "-O", "binary", f"--only-section={text_sect}",
                        obj, tf.name], capture_output=True)
        comp_text = open(tf.name, "rb").read()

    def word(buf, off):
        return (int.from_bytes(buf[off:off + 4], "little")
                if 0 <= off and off + 4 <= len(buf) else None)

    bases = {}
    for i, (off, typ, s) in enumerate(recs):
        if typ != "R_MIPS_HI16" or s not in referenced:
            continue
        if i + 1 >= len(recs) or recs[i + 1][1] != "R_MIPS_LO16" or recs[i + 1][2] != s:
            return {}   # unpaired HI16 against a local section: refuse to guess
        lo_off = recs[i + 1][0]
        chi, clo = word(comp_text, off), word(comp_text, lo_off)
        rhi = word(retail_text, off - sym_off)
        rlo = word(retail_text, lo_off - sym_off)
        if None in (chi, clo, rhi, rlo):
            return {}
        if (chi ^ rhi) & 0xFFFF0000 or (clo ^ rlo) & 0xFFFF0000:
            return {}   # instruction shells differ: not a pure placement delta
        base = (((rhi & 0xFFFF) << 16) + _sext16(rlo & 0xFFFF)) \
             - (((chi & 0xFFFF) << 16) + _sext16(clo & 0xFFFF))
        if base % 4 or not (0x80000000 <= base < 0x90000000):
            return {}
        if bases.setdefault(s, base) != base:
            return {}   # sites disagree on the placement
    if set(bases) != referenced:
        return {}       # a referenced section has no derivable pair
    # no placed section may overlap the .text mapping or another placement
    hdr = subprocess.run([OBJDUMP, "-h", obj], capture_output=True)
    sizes = {}
    for line in hdr.stdout.decode(errors="replace").splitlines():
        m = re.match(r"\s*\d+\s+(\S+)\s+([0-9A-Fa-f]+)\s+", line)
        if m:
            sizes[m.group(1)] = int(m.group(2), 16)
    ranges = [(vram, vram + sizes.get(text_sect, len(comp_text)))]
    for s, base in bases.items():
        ranges.append((base, base + max(sizes.get(s, 4), 4)))
    ranges.sort()
    for (a0, a1), (b0, _) in zip(ranges, ranges[1:]):
        if b0 < a1:
            return {}
    return bases


def build_text(cfile, gccdir, opt, aspsx, gcc_flags="", as_flags="", vram=None,
               target=None, psyq=None, as_path=None, psyq_cpp=None,
               asm_output=None, require_linked=False, retail_text=None):
    if asm_output:
        if psyq:
            # The psyq path compiles straight to .o through cc_psyq.sh -- there is no
            # -S listing to publish. The CLI already rejects this pair; fail loudly for
            # programmatic callers too, rather than silently publishing nothing.
            return None, "assembly-output: unavailable with --psyq (no -S stage)"
        # PRESERVE the previous listing instead of destroying it. This used to unlink,
        # so a gcc-STAGE failure left the worker with NO assembly at all: 6/76 rows in
        # w62-w64 lost it on some eval and func_8009A590 lost it permanently on its
        # final eval, which is exactly when it is wanted for the post-mortem. Keeping
        # `latest.s` absent on failure is still correct (it must never show a stale
        # candidate's code), so the old copy moves aside under the same `.last.`
        # convention the candidate snapshots already use (results/<func>.last.c).
        try:
            if os.path.exists(asm_output):
                os.replace(asm_output, _prior_assembly_path(asm_output))
        except OSError as exc:
            return None, f"assembly-output: {exc}"
        # Rotate BOTH listings together, unconditionally, before gcc runs: after this
        # point neither `.latest.*` exists, so there is no reachable state where the
        # two files describe different candidates. The maspsx rotation is best-effort
        # and must never be able to fail the build.
        try:
            _mo = maspsx_assembly_path(asm_output)
            if os.path.exists(_mo):
                os.replace(_mo, _prior_assembly_path(_mo))
        except OSError:
            pass
    with tempfile.TemporaryDirectory() as td:
        s, o, e, t = (os.path.join(td, x) for x in ("a.s", "a.o", "a.elf", "a.text"))
        if psyq:
            # Compile via the GENUINE SN cc1 (psyq 4.0=gcc2.7.2, 4.4=gcc2.8.1) under wibo,
            # then the same ccproc->maspsx->as pipeline (all inside tools/cc_psyq.sh -> .o).
            env = os.environ.copy()
            if psyq_cpp:
                env["PSYQ_CPP"] = psyq_cpp
            r = subprocess.run([os.path.join(ROOT, "tools", "cc_psyq.sh"), cfile, o, psyq, gcc_flags],
                               capture_output=True, env=env)
            if r.returncode != 0 or not os.path.exists(o):
                return None, "psyq: " + live_truth.gcc_diagnostic(r.stderr + r.stdout)
        else:
            # -I include mirrors tools/cc.sh so `#include "common.h"` in src/*.c or scratch
            # files resolves (a missing include is a phantom "gcc: No such file" NO MATCH).
            r = subprocess.run([os.path.join(gccdir, "gcc"), f"-B{gccdir}/", "-S", f"-{opt}",
                                "-w", f"-I{os.path.join(ROOT, 'include')}",
                                *gcc_flags.split(), cfile, "-o", s], capture_output=True)
            if r.returncode != 0 or not os.path.exists(s):
                detail = live_truth.gcc_diagnostic(r.stderr + r.stdout)
                if r.returncode == 0 and not os.path.exists(s):
                    detail = (detail + " " if detail else "") + "gcc produced no assembly output"
                return None, "gcc: " + detail
            if asm_output:
                try:
                    _publish_compiler_assembly(s, asm_output)
                except OSError as exc:
                    return None, f"assembly-output: {exc}"
            common = [VENV_PY, MASPSX]
            if aspsx:
                common.append(f"--aspsx-version={aspsx}")
            common.append("--dont-force-G0")  # pinned build is -G8 (game uses $gp small-data)
            # -I ROOT / -I ROOT/include mirror tools/cc.sh so `.include`s pulled in via
            # common.h (labels.inc -> gte_macros.inc) resolve at the as step too.
            common += [f"-I{ROOT}", f"-I{os.path.join(ROOT, 'include')}",
                       "-EL", "-march=r3000", "-G8", *as_flags.split()]
            # The scored argv and the inspection argv are built from ONE `common` list
            # and differ by exactly `--run-assembler --gnu-as-path <as> -o <obj>`.
            # Never re-type these flags: maspsx takes its sdata limit from the LAST -G
            # in the as args, so a dropped or reordered flag would publish a listing
            # with different $gp decisions than the one that was actually scored.
            cmd = [*common, "--run-assembler", "--gnu-as-path", (as_path or AS), "-o", o]
            # Publish BEFORE the scored call, so an as-stage CFAIL -- precisely the
            # delay-slot/backfill class this listing exists for -- still leaves behind
            # the assembly that caused it.
            if asm_output:
                _publish_maspsx_listing(common, s, asm_output)
            with open(s) as fin:
                r = subprocess.run(cmd, stdin=fin, capture_output=True)
            if r.returncode != 0:
                return None, "as: " + live_truth.gcc_diagnostic(r.stderr + r.stdout)
        # Link at the function's real vram so internal `j`/absolute relocs resolve
        # (external refs left unresolved -> 0). Fall back to the raw object otherwise.
        obj = o
        if vram is not None:
            placements = {}
            if retail_text is not None and target:
                try:
                    placements = _local_section_placements(o, target, vram, retail_text)
                except Exception as exc:
                    print(f"match.py WARNING: jtbl placement derivation error ({exc}); "
                          f"linking with orphan data sections", file=sys.stderr)
            lds = os.path.join(td, "link.ld")
            with open(lds, "w") as f:
                if placements:
                    entries = [(vram, ".text ALIGN(4) : SUBALIGN(4) { *(.text.*) *(.text) }")]
                    # .text.<name> subsections map INTO .text AHEAD of the bare
                    # body (section-seam fix, 4th Option-D instance 2026-07-22):
                    # pure-table "functions" (pointer banks pinned via
                    # section(".text.<name>")) land at the function base, and
                    # the func_81892800 bank+body composite reproduces retail's
                    # table-before-body layout. Plain functions unaffected.
                    for sect, base in placements.items():
                        entries.append(
                            (base, f"{sect} ALIGN(4) : SUBALIGN(4) {{ *({sect}) }}"))
                    entries.sort()
                    body = " ".join(f". = 0x{a:08X}; {stmt}" for a, stmt in entries)
                    f.write(f"_gp = 0x{GP_VALUE:08X};\nSECTIONS {{ {body} }}")
                else:
                    f.write(f"_gp = 0x{GP_VALUE:08X};\n"
                            f"SECTIONS {{ . = 0x{vram:08X}; .text ALIGN(4) : SUBALIGN(4) {{ *(.text.*) *(.text) }} }}")
            cmd = [LD, "-EL", "--unresolved-symbols=ignore-all", "-T", lds]
            # The two generated catalogs are absolute assignments, so a catalog line
            # for the TARGET shadows the object's own .text definition and
            # slice_symbol_text() then refuses it as "*ABS* ... likely still
            # INCLUDE_ASM". This bites the moment a TU defines a symbol the main
            # executable also calls — exactly the rowbase true-space naming
            # inversion (func_80094ABC -> func_8009A21C, 2026-07-28). Same target
            # exclusion the FUNC_NAMES / NAMED_SYMS_LIST scripts below already do.
            def _catalog_script(src, tag):
                if not target:
                    return src
                lines = [ln for ln in open(src, errors="replace").read().splitlines()
                         if not re.match(rf"\s*{re.escape(target)}\s*=", ln)]
                dst = os.path.join(td, f"{tag}.ld")
                with open(dst, "w") as fh:
                    fh.write("\n".join(lines) + "\n")
                return dst
            if os.path.exists(UNDEF_SYMS):
                cmd += ["-T", _catalog_script(UNDEF_SYMS, "undef_syms")]  # resolve D_x data symbols for %gp_rel / %hi/%lo
            if os.path.exists(UNDEF_FUNCS):
                cmd += ["-T", _catalog_script(UNDEF_FUNCS, "undef_funcs")]  # resolve library-only routines (e.g. func_8003AEF8,
                #   InitPAD) that appear ONLY in undefined_funcs.txt; without this the jal reloc
                #   is left undefined, the R_MIPS_26 displacement overflows, ld fails, and match.py
                #   silently falls back to the unlinked .o -> spurious NO MATCH on unrelated hi/lo.
            if FUNC_NAMES:
                # define sibling function symbols (address-of-function refs, e.g. callback
                # registration) as func_XXXXXXXX = 0xXXXXXXXX, except the target itself
                # (defined in the object) to avoid a multiple-definition error.
                fld = os.path.join(td, "funcs.ld")
                with open(fld, "w") as f:
                    for fn in FUNC_NAMES:
                        if fn != target:
                            f.write(f"{fn} = 0x{fn[5:]};\n")
                cmd += ["-T", fld]
            if NAMED_SYMS_LIST:
                # define already-NAMED library funcs/data (DrawSync, InitPAD, gCdMode, …)
                # so a function that calls/references one links cleanly instead of failing
                # R_MIPS_26 and silently falling back to the unlinked object. Absolute
                # assignments; ld tolerates duplicates vs undefined_syms/funcs (same addr).
                # Exclude the target itself (defined in the object -> would collide).
                sld = os.path.join(td, "namedsyms.ld")
                with open(sld, "w") as f:
                    for sn, saddr in NAMED_SYMS_LIST:
                        if sn != target:
                            f.write(f"{sn} = {saddr};\n")
                cmd += ["-T", sld]
            cmd += ["-o", e, o]
            r = subprocess.run(cmd, capture_output=True)
            if r.returncode == 0:
                obj = e
            else:
                # LOUD warning: the silent fallback to the unlinked object makes ALL relocs
                # read 0 (strings/jals/jtbl wrong) -> phantom diffs on unrelated globals.
                # Common cause: a %hi/%lo-accessed global declared <=8B emits a %gp_rel
                # (GPREL16) ref that overflows ("small-data section too large") and ld fails.
                # Fix: declare value-loaded pointer/scalar globals as `extern T G[];` ([0]).
                err_tail = r.stderr.decode(errors="replace").strip().splitlines()
                err_tail = err_tail[-1] if err_tail else "unknown error"
                if require_linked:
                    return None, "ld: " + err_tail
                print(f"match.py WARNING: ld FAILED ({err_tail}) -> comparing the UNLINKED "
                      f"object; ALL relocs read 0 (expect phantom diffs on %hi/%lo globals, "
                      f"jals, strings). Check for small-data overflow: declare hi/lo globals "
                      f"as `extern T G[];`.", file=sys.stderr)
        subprocess.run([OBJCOPY, "-O", "binary", "--only-section=.text", obj, t], capture_output=True)
        with open(t, "rb") as stream:
            text = stream.read()
        if target:
            # `o` (the pre-link object) is the ONLY place the pinned
            # `.text.<target>` composite section is still visible by name --
            # the isolated link folds it into the bare `.text` output section.
            # slice_symbol_text needs it to tell a sanctioned bank/table
            # prefix (part of the row's retail extent) apart from unrelated
            # code that merely precedes the symbol.
            sliced, slice_err = slice_symbol_text(obj, text, target, source_obj=o)
            if slice_err:
                return None, slice_err
            else:
                text = sliced
        return text, None

def section_vma(obj, section):
    r = subprocess.run([OBJDUMP, "-h", obj], capture_output=True)
    if r.returncode != 0:
        return None
    for line in r.stdout.decode(errors="replace").splitlines():
        m = re.match(r"\s*\d+\s+(\S+)\s+[0-9A-Fa-f]+\s+([0-9A-Fa-f]+)\s+", line)
        if m and m.group(1) == section:
            return int(m.group(2), 16)
    return None

def symbol_info(obj, name):
    r = subprocess.run([OBJDUMP, "-t", obj], capture_output=True)
    if r.returncode != 0:
        return None
    for line in r.stdout.decode(errors="replace").splitlines():
        parts = line.split()
        if len(parts) < 5 or parts[-1] != name:
            continue
        if not re.fullmatch(r"[0-9A-Fa-f]+", parts[0]) or not re.fullmatch(r"[0-9A-Fa-f]+", parts[-2]):
            continue
        return {
            "value": int(parts[0], 16),
            "section": parts[-3],
            "size": int(parts[-2], 16),
        }
    return None

def section_names(obj):
    """Every section name in `obj`, in objdump -h order (may contain dups)."""
    r = subprocess.run([OBJDUMP, "-h", obj], capture_output=True)
    if r.returncode != 0:
        return []
    out = []
    for line in r.stdout.decode(errors="replace").splitlines():
        m = re.match(r"\s*\d+\s+(\S+)\s+[0-9A-Fa-f]+\s+", line)
        if m:
            out.append(m.group(1))
    return out


def section_bytes(obj, section):
    """Raw contents of one section of `obj` (b"" when absent/empty)."""
    with tempfile.NamedTemporaryFile(suffix=".sect") as tf:
        subprocess.run([OBJCOPY, "-O", "binary", f"--only-section={section}",
                        obj, tf.name], capture_output=True)
        try:
            with open(tf.name, "rb") as fh:
                return fh.read()
        except OSError:
            return b""


def has_pinned_text_section(obj, name):
    """True when `obj` pins a `.text.<name>` composite section.

    That section is the SANCTIONED shape for a row whose retail bytes begin
    with a function-pointer bank / literal table before the compiled body
    (`overlays/dungeon/first_pass_matched/func_81892800.c`; the landing gate's
    KEEP rule is object-scoped `*(.text.*)` for exactly this reason). The
    isolated link script orders `*(.text.*)` AHEAD of `*(.text)` at the row's
    vram, so those bytes occupy the head of the row extent -- see
    `slice_symbol_text`.
    """
    if not obj or not name:
        return False
    return f".text.{name}" in section_names(obj)


def slice_symbol_text(obj, text, name, source_obj=None):
    info = symbol_info(obj, name)
    if info is None:
        return None, f"symbol {name} not found in compiled object"
    # A symbol living in its OWN named section `.text.<name>` is the SANCTIONED
    # shape for pure-table "functions" (function-pointer banks expressed as
    # typed const arrays pinned via __asm__ rename + section attribute — the
    # land gate's KEEP rule requires exactly this; see func_81892800.c). Only
    # refuse foreign sections, which really do indicate INCLUDE_ASM leftovers
    # (2026-07-22, wave-43 bank-table cluster: func_81251000 n=7).
    own_section = f".text.{name}"
    if info["section"] not in (".text", own_section):
        return None, (
            f"symbol {name} is in {info['section']} (likely still INCLUDE_ASM), "
            "not compiled C .text"
        )
    text_section = info["section"]
    vma = section_vma(obj, text_section)
    if vma is None:
        return None, f"could not find {text_section} section VMA"
    if text_section != ".text":
        # The caller's blob is .text-only; pull the named section's bytes.
        text = section_bytes(obj, text_section)
        if not text:
            return None, f"could not extract {text_section} bytes"
    offset = info["value"] - vma
    size = info["size"]
    if offset < 0 or offset > len(text):
        return None, f"symbol {name} offset 0x{offset:X} is outside .text"
    if size <= 0:
        return None, f"symbol {name} has no recorded size"
    # EXTENT (2026-08-31): the comparison slice used to start at the function
    # SYMBOL, which silently dropped a pinned `.text.<name>` bank/table prefix
    # even though the retail row being compared against starts with it. The
    # scored candidate was then short by the prefix and every prefix word
    # counted as an indel: func_81892800 -- LANDED byte-exact -- reported
    # aligned 10 (its 10-word table), func_818FE800 reported 38 of which 31
    # were the prefix. Start the slice at the row's link base whenever the TU
    # pins that composite section, so the extent covers prefix + body exactly
    # as the landing gate links it.
    #
    # `offset > 0` alone is NOT the trigger: unrelated code can precede the
    # symbol in a multi-function TU, and pulling that in would change scores
    # for ordinary rows. The pinned-section evidence is what makes the leading
    # bytes part of THIS row.
    start = offset
    if offset > 0 and has_pinned_text_section(source_obj or obj, name):
        start = 0
        print(
            f"match.py: extent -- {name} scored as a composite row "
            f"(.text.{name} prefix of {offset} byte(s) + {size}-byte body); "
            "the slice starts at the row link base, not the body symbol.",
            file=sys.stderr,
        )
    return text[start:offset + size], None

def words_equal(got, tgt, length):
    """Compare .text word-by-word, ignoring j/jal target immediates (opcodes 2/3),
    which are relocations that only resolve at final link time."""
    if len(got) < length:
        return False
    if not all(b == 0 for b in got[length:]):
        return False
    for i in range(0, length, 4):
        g, t = got[i:i + 4], tgt[i:i + 4]
        if g == t:
            continue
        gw, tw = int.from_bytes(g, "little"), int.from_bytes(t, "little")
        if (gw >> 26) == (tw >> 26) and (gw >> 26) in (2, 3):  # j / jal -> reloc target
            continue
        return False
    return True

def word_mismatch_count(got_hex, tgt, mask_relocations=True):
    """Count real-mismatch words (a 'X' in word_diff) between got and tgt, ignoring
    j/jal reloc-target words (opcodes 2/3). Used only to RANK sweep configs by
    closeness when none match exactly. Returns None if got_hex isn't valid hex."""
    try:
        got = bytes.fromhex(got_hex)
    except Exception:
        return None
    n = 0
    for i in range(0, len(tgt), 4):
        g, t = got[i:i + 4], tgt[i:i + 4]
        if g == t:
            continue
        if mask_relocations and len(g) == 4 and (int.from_bytes(g, "little") >> 26) == (int.from_bytes(t, "little") >> 26) \
                and (int.from_bytes(t, "little") >> 26) in (2, 3):
            continue
        n += 1
    return n


def _normalized_words(blob, mask_relocations=True):
    """Return words normalized exactly like :func:`words_equal`.

    j/jal targets are link-time relocations, so only their opcode participates in
    positional and aligned oracle scoring.  Kept here (rather than in the CLI
    wrappers) so main-EXE and overlay callers cannot silently drift apart.
    """
    out = []
    for i in range(0, len(blob), 4):
        word = int.from_bytes(blob[i:i + 4], "little")
        opcode = word >> 26
        out.append(opcode << 26 if mask_relocations and opcode in (2, 3) else word)
    return out


def aligned_word_stats(got, tgt, mask_relocations=True):
    """LCS-aligned relocation-normalized distance as ``(subs, indels)``."""
    sm = SequenceMatcher(
        a=_normalized_words(got, mask_relocations),
        b=_normalized_words(tgt, mask_relocations), autojunk=False)
    substitutions = indels = 0
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        if tag == "replace":
            substitutions += min(i2 - i1, j2 - j1)
            indels += abs((i2 - i1) - (j2 - j1))
        else:
            indels += max(i2 - i1, j2 - j1)
    return substitutions, indels


def regional_alignment_signature(got, target, target_spans=None,
                                 mask_relocations=True):
    """Return a deterministic regional decomposition of aligned word diffs.

    ``got`` and ``target`` are the exact byte streams supplied to the existing
    aligned scorer.  ``target_spans`` is an optional contiguous sequence of
    ``(start, end)`` target-word spans.  Region boundaries belong to the
    target, never to the candidate, so a candidate insertion cannot shift the
    attribution of later words.  When omitted, four balanced target quartiles
    are used.

    The alignment and relocation behavior deliberately share the existing
    private primitives instead of defining a second scorer.  The returned
    ``vector`` is ``[region0.substitutions, region0.indels, ...]``.  A
    ``ValueError`` is raised for malformed streams/spans or if the regional
    counters cannot reproduce :func:`aligned_word_stats` exactly.
    """
    try:
        got = bytes(got)
        target = bytes(target)
    except (TypeError, ValueError) as exc:
        raise TypeError("got and target must be bytes-like word streams") from exc
    if len(got) % 4 or len(target) % 4:
        raise ValueError("got and target byte streams must be word aligned")
    if not isinstance(mask_relocations, bool):
        raise TypeError("mask_relocations must be bool")

    target_word_count = len(target) // 4
    candidate_word_count = len(got) // 4
    if target_spans is None:
        spans = [(target_word_count * i // 4,
                  target_word_count * (i + 1) // 4) for i in range(4)]
    else:
        try:
            spans = [tuple(span) for span in target_spans]
        except (TypeError, ValueError) as exc:
            raise ValueError("target_spans must contain (start, end) pairs") from exc
        if not spans:
            raise ValueError("target_spans must contain at least one span")

    previous_end = 0
    for span in spans:
        if len(span) != 2 or any(isinstance(value, bool)
                                 or not isinstance(value, int)
                                 for value in span):
            raise ValueError("target_spans must contain integer (start, end) pairs")
        start, end = span
        if start < 0 or end < start or end > target_word_count:
            raise ValueError("target_spans must lie within the target stream")
        if start != previous_end:
            raise ValueError("target_spans must be contiguous and start at zero")
        previous_end = end
    if previous_end != target_word_count:
        raise ValueError("target_spans must cover the target stream")

    region_map = {
        "scheme": "target-word-spans-v1",
        "regions": [{"id": f"R{index}",
                     "target_span": [start, end]}
                    for index, (start, end) in enumerate(spans)],
    }
    region_map_sha256 = hashlib.sha256(
        json.dumps(region_map, sort_keys=True, separators=(",", ":"))
        .encode("utf-8")).hexdigest()

    normalized_got = _normalized_words(got, mask_relocations)
    normalized_target = _normalized_words(target, mask_relocations)
    sm = SequenceMatcher(a=normalized_got, b=normalized_target, autojunk=False)

    # The candidate span is descriptive only.  It records the smallest
    # enclosing candidate interval which contributed to a target region; it is
    # never used to choose or compare regions.
    region_state = [{
        "id": f"R{index}",
        "target_span": [start, end],
        "candidate_min": None,
        "candidate_max": None,
        "substitutions": 0,
        "indels": 0,
    } for index, (start, end) in enumerate(spans)]

    def region_for_target(index):
        # The target index is only called for an existing target word.  Empty
        # spans therefore need no special treatment here.
        for region_index, (start, end) in enumerate(spans):
            if start <= index < end:
                return region_index
        raise ValueError("target index is outside the frozen region map")

    def region_for_cursor(cursor):
        # A cursor at a region boundary is right-biased.  A suffix cursor uses
        # the final region, including when the target has zero words.
        cursor = max(0, min(cursor, target_word_count))
        for region_index, (start, end) in enumerate(spans):
            if cursor < end:
                return region_index
        return len(spans) - 1

    def mark_candidate(region_index, candidate_index):
        state = region_state[region_index]
        if state["candidate_min"] is None:
            state["candidate_min"] = candidate_index
            state["candidate_max"] = candidate_index + 1
        else:
            state["candidate_min"] = min(state["candidate_min"], candidate_index)
            state["candidate_max"] = max(state["candidate_max"], candidate_index + 1)

    def add_equal(candidate_start, target_start, length):
        # Equal blocks can cross a frozen target boundary; attribute each word
        # independently so the boundary remains target-stable.
        for offset in range(length):
            region_index = region_for_target(target_start + offset)
            mark_candidate(region_index, candidate_start + offset)

    for tag, candidate_start, candidate_end, target_start, target_end in sm.get_opcodes():
        candidate_length = candidate_end - candidate_start
        target_length = target_end - target_start
        if tag == "equal":
            add_equal(candidate_start, target_start, candidate_length)
            continue
        if tag == "replace":
            substitutions = min(candidate_length, target_length)
            for offset in range(substitutions):
                region_index = region_for_target(target_start + offset)
                region_state[region_index]["substitutions"] += 1
                mark_candidate(region_index, candidate_start + offset)
            # A replace with unequal lengths is the scorer's substitution
            # prefix plus an indel suffix.  Keep that exact convention.
            for index in range(target_start + substitutions, target_end):
                region_state[region_for_target(index)]["indels"] += 1
            for index in range(candidate_start + substitutions, candidate_end):
                region_index = region_for_cursor(target_start)
                region_state[region_index]["indels"] += 1
                mark_candidate(region_index, index)
            continue
        if tag == "delete":
            # SequenceMatcher's delete means words present only in `got`.
            region_index = region_for_cursor(target_start)
            for index in range(candidate_start, candidate_end):
                region_state[region_index]["indels"] += 1
                mark_candidate(region_index, index)
            continue
        if tag == "insert":
            # SequenceMatcher's insert means words present only in `target`.
            for index in range(target_start, target_end):
                region_state[region_for_target(index)]["indels"] += 1
            continue
        raise ValueError(f"unexpected SequenceMatcher opcode: {tag!r}")

    substitutions, indels = aligned_word_stats(
        got, target, mask_relocations=mask_relocations)
    regional_substitutions = sum(state["substitutions"] for state in region_state)
    regional_indels = sum(state["indels"] for state in region_state)
    if (regional_substitutions, regional_indels) != (substitutions, indels):
        raise ValueError("regional alignment does not reproduce aligned_word_stats")

    regions = []
    vector = []
    for state in region_state:
        candidate_span = None
        if state["candidate_min"] is not None:
            candidate_span = [state["candidate_min"], state["candidate_max"]]
        regions.append({
            "id": state["id"],
            "target_span": state["target_span"],
            "candidate_span": candidate_span,
            "substitutions": state["substitutions"],
            "indels": state["indels"],
        })
        vector.extend((state["substitutions"], state["indels"]))

    return {
        "schema": "azure-clean.regional-alignment.v1",
        "region_map_sha256": region_map_sha256,
        "mask_relocations": mask_relocations,
        "target_words": target_word_count,
        "candidate_words": candidate_word_count,
        "aligned": {
            "substitutions": substitutions,
            "indels": indels,
            "total": substitutions + indels,
        },
        "regions": regions,
        "vector": vector,
    }


_SHA256_CACHE = {}
_ORACLE_RESIDUE_CLASS = None


def _sha256_file(path):
    """Best-effort content identity; an absent/unreadable artifact is ``None``."""
    if not path:
        return None
    try:
        key = (os.path.abspath(path), os.path.getmtime(path), os.path.getsize(path))
        if key not in _SHA256_CACHE:
            h = hashlib.sha256()
            with open(path, "rb") as f:
                for chunk in iter(lambda: f.read(1024 * 1024), b""):
                    h.update(chunk)
            _SHA256_CACHE[key] = h.hexdigest()
        return _SHA256_CACHE[key]
    except OSError:
        return None


def _display_path(path):
    if not path:
        return None
    path = os.path.abspath(path)
    try:
        rel = os.path.relpath(path, ROOT)
        if rel != ".." and not rel.startswith(".." + os.sep):
            return rel
    except ValueError:
        pass
    return path


def _residue_summary(got, tgt, substitutions, indels):
    """Reuse I5's classifier without making it a startup dependency.

    residue_class imports the overlay harness, which in turn imports this module;
    loading it lazily keeps all legacy match.py invocations free of that dependency
    and avoids an import cycle during normal startup.
    """
    if substitutions == 0 and indels == 0:
        return {"class": "match", "confidence": "high", "signals": []}
    try:
        global _ORACLE_RESIDUE_CLASS
        if _ORACLE_RESIDUE_CLASS is None:
            path = os.path.join(ROOT, "tools", "residue_class.py")
            spec = importlib.util.spec_from_file_location("_oracle_residue_class", path)
            mod = importlib.util.module_from_spec(spec)
            assert spec.loader is not None
            spec.loader.exec_module(mod)
            _ORACLE_RESIDUE_CLASS = mod
        classified = _ORACLE_RESIDUE_CLASS.classify(got, tgt)
        residue = {
            "class": classified.get("class", "broad"),
            "confidence": classified.get("confidence", "low"),
            "signals": list(classified.get("signals", [])),
        }
        if classified.get("secondary"):
            residue["secondary"] = classified["secondary"]
    except Exception as exc:
        residue = {
            "class": "broad",
            "confidence": "low",
            "signals": [f"classifier-error:{type(exc).__name__}"],
        }

    # I5 historically classifies only the target-sized prefix.  Preserve its
    # richer result, but make real generated-length drift explicit in the compact
    # contract (and own the primary class when I5 found no more specific signal).
    if len(got) != len(tgt):
        length_signal = f"length-words={((len(got) + 3) // 4)}/{((len(tgt) + 3) // 4)}"
        if length_signal not in residue["signals"]:
            residue["signals"].append(length_signal)
        if residue["class"] in ("match", "broad") and indels:
            residue["class"] = "length-drift"
            residue["confidence"] = "high"
    return residue


def compiler_oracle_summary(func, config, source_path, tool_path, target,
                            got=None, build_error=None, accepted_exact=None,
                            compiler_path=None, warnings=None,
                            mask_relocations=True):
    """Build the stable compact compiler-oracle record shared by all CLIs.

    ``words_off`` intentionally retains the legacy positional target-span count.
    The canonical closeness metric is ``aligned.total``.  Full generated length is
    retained so an extra tail cannot disappear as it did in older overlay output.
    """
    source_sha = _sha256_file(source_path)
    record = {
        "schema": "azure-clean.compiler-oracle.v1",
        "status": "CFAIL" if got is None else "NOMATCH",
        "build_status": "failed" if got is None else "ok",
        "exact": None if got is None else False,
        "function": func,
        "config": config,
        "source": _display_path(source_path),
        "source_sha": source_sha,
        "target_sha": hashlib.sha256(target).hexdigest(),
        "tool": _display_path(tool_path),
        "tool_sha": _sha256_file(tool_path),
        "compiler": _display_path(compiler_path),
        "compiler_sha": _sha256_file(compiler_path),
        "comparison_mode": ("relocation-masked" if mask_relocations
                            else "linked-strict"),
        "length_bytes": {"generated": None if got is None else len(got), "target": len(target)},
        "length_words": {
            "generated": None if got is None else (len(got) + 3) // 4,
            "target": (len(target) + 3) // 4,
        },
        "words_off": None,
        "positional_words_off": None,
        "aligned": {"substitutions": None, "indels": None, "total": None},
        "residue": {"class": "build-fail" if got is None else None, "signals": []},
    }
    if warnings:
        record["warnings"] = list(warnings)
    if got is None:
        if build_error:
            record["error"] = str(build_error)[:500]
        return record

    byte_exact = (words_equal(got, target, len(target)) if mask_relocations else
                  len(got) >= len(target) and got[:len(target)] == target and
                  all(b == 0 for b in got[len(target):]))
    accepted = byte_exact if accepted_exact is None else bool(accepted_exact)
    # words_equal deliberately accepts alignment-only zero padding after retail;
    # do not turn accepted padding into a phantom aligned indel.
    score_got = got
    if len(got) > len(target) and all(b == 0 for b in got[len(target):]):
        score_got = got[:len(target)]
    substitutions, indels = aligned_word_stats(
        score_got, target, mask_relocations=mask_relocations)
    residue = _residue_summary(score_got, target, substitutions, indels)
    if (not mask_relocations and substitutions + indels and
            residue.get("class") == "match"):
        residue = dict(residue)
        residue["class"] = "linked-target"
        residue["confidence"] = "high"
        signals = list(residue.get("signals") or [])
        signals.append("resolved-jump/call-target-diff")
        residue["signals"] = signals
    record.update({
        "status": "MATCH" if accepted else "NOMATCH",
        "exact": accepted,
        "byte_exact": byte_exact,
        "words_off": (0 if byte_exact else word_mismatch_count(
            got[:len(target)].hex(), target,
            mask_relocations=mask_relocations)),
        "aligned": {
            "substitutions": substitutions,
            "indels": indels,
            "total": substitutions + indels,
        },
        "residue": residue,
    })
    record["positional_words_off"] = record["words_off"]
    return record


def print_oracle_summary(record):
    """Emit exactly one compact JSON line (no hex/disassembly side channels)."""
    print(json.dumps(record, sort_keys=True, separators=(",", ":")))

def length_note(got_hex, tgt):
    """Return a loud NOTE string when got/tgt differ in trailing-zero-trimmed code
    length, else ''. A single early extra/missing instruction (e.g. a delay-slot
    fold eating a real nop) desyncs every later word into phantom-looking diffs far
    from the actual cause — surface that FIRST so the analyst checks the first X
    word for a missing/extra insn instead of chasing the tail."""
    try:
        got = bytes.fromhex(got_hex)
    except Exception:
        return ""

    def words(b):
        i = len(b)
        while i > 0 and b[i - 1] == 0:
            i -= 1
        return (i + 3) // 4

    gw, tw = words(got), words(tgt)
    if gw == tw:
        return ""
    return (f"  NOTE: code length differs (got ~{gw} words vs tgt ~{tw}, trailing zeros trimmed) — "
            f"a single early extra/missing instruction desyncs every later word (phantom diffs); "
            f"find the FIRST X word and look for one extra/missing insn there.")

def word_diff(got_hex, tgt):
    """Word-aligned got-vs-target dump for a NO MATCH. Marks each 4-byte word:
    '  ' identical, '~ ' a j/jal reloc target (ignored by the matcher), 'X ' a
    real mismatch. Makes reorder/fold/missing-insn diffs obvious vs raw hex."""
    try:
        got = bytes.fromhex(got_hex)
    except Exception:
        return f"  unable to diff non-hex build output: {got_hex}"
    out = []
    for i in range(0, len(tgt), 4):
        g, t = got[i:i + 4], tgt[i:i + 4]
        if g == t:
            mark = "  "
        elif len(g) == 4 and (int.from_bytes(g, "little") >> 26) == (int.from_bytes(t, "little") >> 26) \
                and (int.from_bytes(t, "little") >> 26) in (2, 3):
            mark = "~ "
        else:
            mark = "X "
        out.append(f"  {mark}[{i // 4:2d}] got {(g.hex() or '--------'):<8}  tgt {t.hex():<8}")
    return "\n".join(out)

def _disasm_words(blob):
    """Disassemble a little-endian MIPS r3000 blob -> {byte_offset: 'mnemonic ops'}.
    Best-effort: any failure (missing objdump, odd output) returns {} so callers
    degrade gracefully to the plain hex word_diff."""
    out = {}
    try:
        with tempfile.NamedTemporaryFile(suffix=".bin", delete=False) as f:
            f.write(blob); path = f.name
        try:
            r = subprocess.run([OBJDUMP, "-D", "-b", "binary", "-m", "mips:3000", "-EL", path],
                               capture_output=True)
            for line in r.stdout.decode(errors="replace").splitlines():
                m = re.match(r"\s*([0-9a-fA-F]+):\s+[0-9a-fA-F]{8}\s+(.*)", line)
                if m:
                    txt = re.sub(r"\s+", " ", m.group(2).split("#")[0].strip())
                    out[int(m.group(1), 16)] = txt
        finally:
            os.unlink(path)
    except Exception:
        return {}
    return out

def disasm_diff(got_hex, tgt):
    """Side-by-side MIPS disassembly of got vs tgt for a NO MATCH. Same word marks
    as word_diff ('  ' identical, '~ ' j/jal reloc target, 'X ' real mismatch).
    Returns '' if disassembly is unavailable so the caller can skip it silently."""
    got = bytes.fromhex(got_hex)
    gd, td = _disasm_words(got), _disasm_words(tgt)
    if not td:
        return ""
    out = ["  disasm (got | tgt):"]
    for i in range(0, len(tgt), 4):
        g, t = got[i:i + 4], tgt[i:i + 4]
        if g == t:
            mark = "  "
        elif len(g) == 4 and (int.from_bytes(g, "little") >> 26) == (int.from_bytes(t, "little") >> 26) \
                and (int.from_bytes(t, "little") >> 26) in (2, 3):
            mark = "~ "
        else:
            mark = "X "
        out.append(f"  {mark}[{i // 4:2d}] {gd.get(i, '--'):<28} | {td.get(i, '--')}")
    return "\n".join(out)

def closest_line(prefix, best):
    """Format a closest-config summary line.

    Keep the global caller's `closest:` prefix stable; additive summaries should
    pass a distinct prefix so existing parsers do not see them as the global best.
    """
    return f"  {prefix}: {best[1]}  ({best[0]} word{'' if best[0] == 1 else 's'} off)"

def print_closest_block(prefix, best, tgt):
    print(closest_line(prefix, best))
    ln = length_note(best[2], tgt)
    if ln:
        print(ln)
    dd = disasm_diff(best[2], tgt)
    print(dd if dd else word_diff(best[2], tgt))

def check_bytes(cfile, name, tgt, length, gccdir, opt, aspsx, gcc_flags, as_flags,
                vram=None, psyq=None, as_path=None, psyq_cpp=None,
                asm_output=None):
    got, err = build_text(cfile, gccdir, opt, aspsx, gcc_flags, as_flags,
                          vram, target=name, psyq=psyq, as_path=as_path,
                          psyq_cpp=psyq_cpp, asm_output=asm_output,
                          retail_text=tgt)
    if got is None:
        return None, None, err
    return words_equal(got, tgt, length), got, None


def check(cfile, name, tgt, length, gccdir, opt, aspsx, gcc_flags, as_flags,
          vram=None, psyq=None, as_path=None, psyq_cpp=None, asm_output=None):
    """Legacy check contract: ``(ok, target-sized-hex-or-error)``."""
    ok, got, err = check_bytes(cfile, name, tgt, length, gccdir, opt, aspsx,
                               gcc_flags, as_flags, vram, psyq, as_path, psyq_cpp,
                               asm_output)
    if got is None:
        return None, err
    return ok, got[:length].hex()

def _beacon(func, config, result, c_path):
    """Best-effort activity log for the dashboard's live-wave panel. Appends ONE
    json line to build/match_activity.jsonl per determined verdict. The ENTIRE body
    is wrapped in try/except: pass so it is provably unable to change match.py's
    stdout, stderr, exit code, or matching behavior — a missing / read-only / full
    build/ dir (or any other failure) is a silent no-op. build/ is NOT created if
    absent (that would be a behavior change); the beacon simply does nothing."""
    try:
        d = os.path.join(ROOT, "build")
        if not os.path.isdir(d):
            return
        path = os.path.join(d, "match_activity.jsonl")
        try:
            if os.path.getsize(path) > 5 * 1024 * 1024:
                os.rename(path, os.path.join(d, f"match_activity.{int(time.time())}.jsonl"))
        except OSError:
            pass
        line = json.dumps({
            "ts": int(time.time()),
            "func": func,
            "config": config,
            "result": result,
            "c_path": c_path,
            "pid": os.getpid(),
        })
        with open(path, "a") as f:
            f.write(line + "\n")
    except Exception:
        pass


# Inline asm that EMITS instructions (`__asm__ volatile("lhu ...")`) TRANSCRIBES
# the target rather than decompiling it: it byte-matches trivially by writing the
# answer, so it must not count as a clean match. What stays ALLOWED: register-var
# pins (`register T v asm("$2")` — real C, only hints allocation), empty
# barriers/hints (`asm("")`), absolute-bind directives (`asm(".set D_X, 0xX")`),
# and bare labels — none of these emit a real instruction.
_ASM_STMT_RE = re.compile(
    r'\b(?:__asm__|__asm|asm)\b\s*(?:__volatile__|volatile)?\s*'
    r'\(\s*("(?:[^"\\]|\\.)*"(?:\s*"(?:[^"\\]|\\.)*")*)',
    re.DOTALL)


def _strip_c_comments(src):
    src = re.sub(r'/\*.*?\*/', ' ', src, flags=re.DOTALL)
    src = re.sub(r'//[^\n]*', ' ', src)
    return src


def asm_instruction_fragments(cfile):
    """Return the list of inline-asm TEMPLATE strings in `cfile` that emit real
    instructions (the ones that make a byte-match a transcription, not a decomp).
    Register pins, "" barriers, .set binds and bare labels are excluded."""
    try:
        with open(cfile, encoding="utf-8", errors="replace") as f:
            src = _strip_c_comments(f.read())
    except OSError:
        return []
    frags = []
    for m in _ASM_STMT_RE.finditer(src):
        parts = re.findall(r'"((?:[^"\\]|\\.)*)"', m.group(1))
        tmpl = " ".join(parts).replace("\\n", " ").replace("\\t", " ").strip()
        if not tmpl:
            continue                          # asm("") barrier / reg hint
        if tmpl.startswith("."):
            continue                          # .set / other assembler directive
        if re.fullmatch(r"\$?\w+", tmpl):
            continue                          # register-pin token ($2 / $16 / $sp)
        if re.fullmatch(r"[A-Za-z_]\w*:", tmpl):
            continue                          # bare label
        frags.append(tmpl)
    return frags


def _print_asm_alert(frags, byte_matched):
    bar = "  " + "=" * 70
    print(bar)
    if byte_matched:
        print("  ASM ALERT: bytes match, but the candidate emits raw MIPS via inline asm")
        print("  -- this TRANSCRIBES the target, it does not decompile it, so it is NOT")
        print("  counted as a clean match. (register-var pins / \"\" barriers / .set binds")
        print("  stay fine; these are instruction fragments.)  Override: --allow-asm")
    else:
        print("  ASM ALERT: candidate emits raw MIPS via inline asm -- would not count as a")
        print("  clean match even if the bytes lined up.  Override: --allow-asm")
    for fr in frags:
        print(f'    - __asm__("{fr}")')
    print(bar)


def _preprocess_argv(argv):
    # argparse can't parse `--gcc-flags -G0` (a value starting with '-' is treated as a bare flag);
    # pre-join such pairs into the `--gcc-flags=-G0` form so both spellings work.
    out, i = [], 0
    while i < len(argv):
        tok = argv[i]
        if tok in ("--gcc-flags", "--as-flags") and i + 1 < len(argv) and argv[i + 1].startswith("-"):
            out.append(tok + "=" + argv[i + 1])
            i += 2
        else:
            out.append(tok)
            i += 1
    return out


def _single_config_label(a, gccdir):
    if a.psyq:
        suffix = "+CPPPSX-production" if a.psyq_cpp == "production" else ""
        return f"psyq{a.psyq}{suffix}"
    ver = os.path.basename(gccdir).removeprefix("gcc-")
    label = f"{ver} -{a.opt} aspsx={a.aspsx}"
    if a.gcc_flags:
        label += f" {a.gcc_flags}"
    return label


def _oracle_record(a, tgt, config, compiler, got, err, asm_frags, warnings=None):
    accepted = None if got is None else (words_equal(got, tgt, len(tgt)) and not asm_frags)
    rec = compiler_oracle_summary(
        a.name, config, a.cfile, __file__, tgt, got=got, build_error=err,
        accepted_exact=accepted, compiler_path=compiler, warnings=warnings)
    if got is not None and words_equal(got, tgt, len(tgt)) and asm_frags:
        rec["residue"] = {
            "class": "inline-asm",
            "confidence": "high",
            "signals": ["emits-instructions"],
        }
        rec.setdefault("warnings", []).append(
            "byte-identical candidate rejected because inline asm emits instructions")
    return rec


def _assembly_record(path):
    """Describe a published raw compiler assembly without embedding its contents."""
    try:
        with open(path, "rb") as stream:
            payload = stream.read()
    except OSError:
        return None
    absolute = os.path.abspath(path)
    try:
        display = os.path.relpath(absolute, ROOT)
    except ValueError:
        display = absolute
    return {
        "path": display,
        "sha256": hashlib.sha256(payload).hexdigest(),
        "bytes": len(payload),
    }


def _summary_main(a, tgt, length, vram, asm_frags):
    """Compact, machine-readable path.  Legacy text mode remains below unchanged."""
    if not a.sweep:
        g = next((x for x in COMPILERS if a.gcc in x), COMPILERS[0]) if a.gcc else COMPILERS[0]
        ok, got, err = check_bytes(
            a.cfile, a.name, tgt, length, g, a.opt, a.aspsx, a.gcc_flags,
            a.as_flags, vram, psyq=a.psyq, as_path=a.as_path,
            psyq_cpp=None if a.psyq_cpp == "decompals" else a.psyq_cpp,
            asm_output=a.asm_output)
        del ok  # compiler_oracle_summary is the canonical verdict implementation
        label = _single_config_label(a, g)
        compiler = os.path.join(g, "gcc") if not a.psyq else os.path.join(ROOT, "tools", "cc_psyq.sh")
        rec = _oracle_record(a, tgt, label, compiler, got, err, asm_frags)
        if a.asm_output:
            assembly = _assembly_record(a.asm_output)
            if assembly:
                rec["compiler_assembly"] = assembly
            maspsx = _assembly_record(maspsx_assembly_path(a.asm_output))
            if maspsx:
                rec["maspsx_assembly"] = maspsx
        _beacon(a.name, label, "MATCH" if rec["exact"] else "NOMATCH", a.cfile)
        print_oracle_summary(rec)
        return 1 if rec["status"] == "CFAIL" else 0

    opts = ["O2", "O1", "O0"] if a.opt == "all" else [a.opt]
    asps = ["2.34", "2.56", "2.79", "2.86"] if a.aspsx == "all" else [a.aspsx]
    flag_sets = ["", "-fno-delayed-branch", "-fno-expensive-optimizations",
                 "-G0", "-G0 -fno-schedule-insns",
                 "-fno-schedule-insns -fno-schedule-insns2", "-fno-schedule-insns2"]
    flagsets = flag_sets if a.gcc_flags == "all" else [a.gcc_flags]
    records = []
    for g in COMPILERS:
        ver = os.path.basename(g).removeprefix("gcc-")
        for opt in opts:
            for asp in asps:
                for flags in flagsets:
                    _ok, got, err = check_bytes(
                        a.cfile, a.name, tgt, length, g, opt, asp, flags,
                        a.as_flags, vram, as_path=a.as_path)
                    label = f"{ver} -{opt} aspsx={asp}" + (f" {flags}" if flags else "")
                    records.append(_oracle_record(
                        a, tgt, label, os.path.join(g, "gcc"), got, err, asm_frags))

    built = [r for r in records if r["build_status"] == "ok"]
    if built:
        best = min(built, key=lambda r: (
            not bool(r["exact"]), r["aligned"]["total"],
            r["words_off"] if r["words_off"] is not None else 10**9,
            r["config"]))
    elif records:
        best = records[-1]
    else:
        best = compiler_oracle_summary(
            a.name, "sweep", a.cfile, __file__, tgt,
            build_error="no compiler configurations available")
    best["sweep"] = {
        "evaluated": len(records),
        "built": len(built),
        "build_failures": len(records) - len(built),
        "matching_configs": [r["config"] for r in records if r.get("exact")],
    }
    _beacon(a.name, "sweep", "MATCH" if best.get("exact") else "NOMATCH", a.cfile)
    print_oracle_summary(best)
    return 0

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("name"); ap.add_argument("cfile")
    ap.add_argument("--gcc", default="2.7.2"); ap.add_argument("--opt", default="O2"); ap.add_argument("--aspsx", default="2.56")
    ap.add_argument("--gcc-flags", default=""); ap.add_argument("--as-flags", default=None)
    ap.add_argument("--psyq", default=None, help="use genuine SN cc1: 4.0 (gcc2.7.2) / 4.4 (gcc2.8.1) / 4.6 (gcc2.95.2)")
    ap.add_argument("--psyq-cpp", default=None, choices=("decompals", "production"),
                    help="with --psyq, choose preprocessor: default decompals gcc -E -P; "
                         "'production' uses genuine CPPPSX and CCPSX's production macros")
    ap.add_argument("--as-path", dest="as_path", default=None,
                    help="OPTIONAL: alternate GNU as binary passed to maspsx --gnu-as-path "
                         "(default: mipsel-linux-gnu-as). Used by the binutils-pin experiment (ROADMAP T3).")
    ap.add_argument("--sweep", action="store_true")
    ap.add_argument("--allow-asm", dest="allow_asm", action="store_true",
                    help="permit inline-asm instruction fragments in the candidate. Default: "
                         "a byte-match that relies on them is downgraded to NO MATCH (it "
                         "transcribes the target rather than decompiling it).")
    ap.add_argument("--no-disasm", dest="disasm", action="store_false",
                    help="suppress the auto side-by-side disassembly on a single-run NO MATCH")
    ap.add_argument("--summary-json", action="store_true",
                    help="emit one compact compiler-oracle JSON record; suppress target hex/diffs")
    ap.add_argument("--asm-output", default=None,
                    help="with a single --summary-json GCC run, atomically publish raw -S output")
    a = ap.parse_args(_preprocess_argv(sys.argv[1:]))
    if a.asm_output and not a.summary_json:
        ap.error("--asm-output requires --summary-json")
    if a.asm_output and a.sweep:
        ap.error("--asm-output is ambiguous with --sweep")
    if a.asm_output and a.psyq:
        ap.error("--asm-output is unavailable with --psyq")
    if a.as_flags is None:
        a.as_flags = DEFAULT_FUNC_AS_FLAGS.get(a.name, "")
    # A byte-match built on inline-asm instruction fragments is a transcription,
    # not a decompilation -> downgrade it (every lane greps ^MATCH). --allow-asm
    # opts back in for the rare owner-approved case (e.g. src/w_80041E70.c).
    asm_frags = [] if a.allow_asm else asm_instruction_fragments(a.cfile)
    tgt, start, length = target_bytes(a.name)
    vram = vram_of(start)
    if a.summary_json:
        rc = _summary_main(a, tgt, length, vram, asm_frags)
        if rc:
            raise SystemExit(rc)
        return
    print(f"target {a.name} @0x{start:X} (vram 0x{vram:08X}) len {length}B: {tgt.hex()}")
    if a.sweep:
        opts = ["O2", "O1", "O0"] if a.opt == "all" else [a.opt]
        asps = ["2.34", "2.56", "2.79", "2.86"] if a.aspsx == "all" else [a.aspsx]
        # `--gcc-flags all` also sweeps the known per-TU flag sets (code3/4/5/6 configs),
        # so flag-dependent matches surface in one pass instead of a manual second sweep.
        FLAG_SETS = ["", "-fno-delayed-branch", "-fno-expensive-optimizations",
                     "-G0", "-G0 -fno-schedule-insns",
                     "-fno-schedule-insns -fno-schedule-insns2", "-fno-schedule-insns2"]
        flagsets = FLAG_SETS if a.gcc_flags == "all" else [a.gcc_flags]
        n = 0
        best = None  # (mismatch_count, label, got_hex) of the closest NO-MATCH config
        best_by_gcc = {}  # basename(gccdir) -> closest NO-MATCH config for that compiler version
        built_any = False   # did ANY config even produce bytes? (vs failing to compile everywhere)
        last_err = None     # (label, err) of the last build failure, for the all-failed warning
        for g in COMPILERS:
            gcc_name = os.path.basename(g)
            for opt in opts:
                for asp in asps:
                    for fl in flagsets:
                        ok, info = check(a.cfile, a.name, tgt, length, g, opt, asp, fl,
                                         a.as_flags, vram, as_path=a.as_path)
                        label = f"{os.path.basename(g)} -{opt} aspsx={asp} flags='{fl}'"
                        if ok:
                            n += 1; print(f"  MATCH  {label}")
                        elif ok is not None:  # build succeeded but bytes differ
                            built_any = True
                            mc = word_mismatch_count(info, tgt)
                            if mc is not None and (best is None or mc < best[0]):
                                best = (mc, label, info)
                            if (mc is not None
                                    and (gcc_name not in best_by_gcc
                                         or mc < best_by_gcc[gcc_name][0])):
                                best_by_gcc[gcc_name] = (mc, label, info)
                        else:  # build failed for this config
                            last_err = (label, info)
        print(f"[{n} matching configs]")
        _beacon(a.name, "sweep", "MATCH" if (n and not asm_frags) else "NOMATCH", a.cfile)
        if n and asm_frags:
            _print_asm_alert(asm_frags, byte_matched=True)
        # "[0 matching configs]" with NO closest line used to be ambiguous: a C file that doesn't
        # COMPILE anywhere (e.g. C89 decls-after-statements on old gcc) looked identical to a genuine
        # all-config codegen miss. Make the all-failed case loud so nobody chases phantom NO-MATCHes.
        if n == 0 and not built_any:
            print("  WARNING: every config FAILED TO BUILD (compile/assemble/link error) — this is a")
            print("  broken C file (e.g. C89 mixed decls-after-statements), NOT a codegen NO-MATCH.")
            if last_err is not None:
                print(f"  last error ({last_err[0]}): {last_err[1]}")
        # When nothing matches, surface the closest config + its diff so the analyst
        # can triage "1 word off = backend/toolchain gap" vs "many off = wrong C shape"
        # without re-running a single config by hand (the recurring close-miss workflow).
        if n == 0 and best is not None and a.disasm:
            print_closest_block("closest", best, tgt)
            for gcc_name in sorted(best_by_gcc):
                print_closest_block("closest-per-gcc", best_by_gcc[gcc_name], tgt)
    else:
        g = next((x for x in COMPILERS if a.gcc in x), COMPILERS[0]) if a.gcc else COMPILERS[0]
        ok, info = check(a.cfile, a.name, tgt, length, g, a.opt, a.aspsx, a.gcc_flags,
                         a.as_flags, vram, psyq=a.psyq, as_path=a.as_path,
                         psyq_cpp=None if a.psyq_cpp == "decompals" else a.psyq_cpp)
        label = (f"psyq{a.psyq} (SN cc1{', CPPPSX production' if a.psyq_cpp == 'production' else ''})"
                 if a.psyq else f"{os.path.basename(g)} -{a.opt} aspsx={a.aspsx}")
        _beacon(a.name, label, "MATCH" if (ok and not asm_frags) else "NOMATCH", a.cfile)
        if ok is None:
            print(f"BUILD FAILED  {label}")
            print(f"  error: {info}")
            sys.exit(1)
        if ok and asm_frags:
            print(f"NO MATCH (asm)  {label}")
            _print_asm_alert(asm_frags, byte_matched=True)
            return
        print(f"{'MATCH' if ok else 'NO MATCH'}  {label}")
        if not ok:
            print(f"  got: {info}\n  tgt: {tgt.hex()}")
            ln = length_note(info, tgt)
            if ln:
                print(ln)
            print(word_diff(info, tgt))
            if a.disasm:
                dd = disasm_diff(info, tgt)
                if dd:
                    print(dd)
            if asm_frags:
                _print_asm_alert(asm_frags, byte_matched=False)

if __name__ == "__main__":
    main()
