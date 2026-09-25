#!/usr/bin/env python3
"""Generate build.ninja for the Azure Dreams matching build.

Pipeline: src/*.c -> tools/cc.sh -> code.o ; split asm -> tools/as.sh ; bin -> objbin ;
link via splat's linker script (post-processed to sort per-function .text.* sections
into address order) -> objcopy -> sha1 gate. Re-run after `splat split` or adding files.

`--non-matching` emits an ALTERNATE build file (build_nm.ninja) that compiles every TU with
-DNON_MATCHING into a separate build dir (build_nm/) and drops the sha1 gate — so functions
that are byte-unmatchable (Type-4 walls, e.g. func_8004E8D8) can ship functional C under
`#ifdef NON_MATCHING`. The default (no-flag) build.ninja is untouched and stays byte-exact.
Build it with: `ninja -f build_nm.ninja`."""
import os, glob, argparse, re
import slus_partitions as partition_support

ap = argparse.ArgumentParser(description=__doc__)
ap.add_argument("--non-matching", action="store_true",
                help="emit build_nm.ninja: -DNON_MATCHING, build_nm/ outputs, no sha1 gate")
args = ap.parse_args()
NM = args.non_matching
BUILDDIR = "build_nm" if NM else "build"
OUTFILE = "build_nm.ninja" if NM else "build.ninja"

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
os.chdir(ROOT)
BASE = "slus_006.14"
LD = f"build/{BASE}.ld"
UF = f"config/generated/{BASE}.undefined_funcs.txt"
US = f"config/generated/{BASE}.undefined_syms.txt"
LDSCRIPTS = [UF, US]
MODULE_MANIFEST = "config/slus_modules.json"
MODULES = []
if os.path.exists(MODULE_MANIFEST):
    import slus_modules as module_support

    MODULES = module_support.load_manifest(MODULE_MANIFEST)
DATA_PIECE_MODULES = {m["source"]: m for m in MODULES if module_support.data_piece_plan(m)} if MODULES else {}
if MODULES:
    if NM:
        raise RuntimeError("SLUS modules are not supported in --non-matching builds")
    MODULE_SYMS = f"{BUILDDIR}/{BASE}.undefined_syms.modules.txt"
    LDSCRIPTS = [UF, MODULE_SYMS]

# Extra `c` subsegments in the splat yaml, i.e. every `c` segment that is NOT the main
# `code` one (currently: konami_runtime, the carved 0x72a8 Konami/SN runtime block).
# Each owns exactly one TU (src/<name>.c, splat-generated INCLUDE_ASM stubs) and gets its
# own slot in the linker script, so it must be expanded — and excluded from `code`'s slot —
# independently. See the EXCLUDE_FILE note below.
def _extra_c_segments(path=f"config/{BASE}.yaml"):
    names = []
    try:
        text = open(path, encoding="utf-8").read()
    except OSError:
        return names
    for m in re.finditer(r"^\s*-\s*\[\s*0x[0-9a-fA-F]+\s*,\s*c\s*,\s*([A-Za-z0-9_./-]+)\s*\]",
                         text, re.M):
        name = m.group(1).strip()
        if name != "code" and name not in names:
            names.append(name)
    return names


EXTRA_C = _extra_c_segments()

# The splat linker script (build/{BASE}.ld) hardcodes build/ object paths and a
# build/src/code.o(.text) placeholder we expand into the per-function SORT glob. In NM
# mode every object lives in build_nm/, so also redirect all remaining build/ -> build_nm/.
# NM also wildcards .bss/.sbss/COMMON: the script's trailing /DISCARD/ *(*) otherwise
# drops NM-only storage from non-code.o TUs (e.g. g_gte in gte_port_state.o -> link error).
#
# WHY EXCLUDE_FILE: `code`'s slot must gather the per-function `.text.func_*` sections of
# ALL 590 src/*.c objects in ONE `SORT_BY_NAME(...)` spec, because the decompiled functions
# from code.c / code2.c / w_*.c interleave by address and only a single sorted spec puts
# them back in address order. Splitting that into several per-glob specs (code*.o, w_*.o, …)
# concatenates the groups instead of merging them and mis-links the image. So an extra `c`
# segment cannot be kept out of `code`'s slot by narrowing the glob — it has to be removed
# from the one wide glob with EXCLUDE_FILE, and expanded again in its own slot.
def _orderld(bd):
    # `{n}*.o` so that per-function wave TUs of an extra segment (integrate.py names them
    # src/{n}_w_<addr>.c) sort into THAT segment's slot together with {n}.o's own
    # INCLUDE_ASM functions -- one SORT spec per slot, merged by address.
    excl = " ".join(f"{bd}/src/{n}*.o" for n in EXTRA_C)
    ex = f"EXCLUDE_FILE({excl}) " if excl else ""
    parts = []
    for n in EXTRA_C:
        parts.append(f"s|build/src/{n}.o(\\.text)|{bd}/src/{n}*.o(SORT_BY_NAME(.text.func_*)) "
                     f"{bd}/src/{n}*.o(.text)|")
    parts.append(f"s|build/src/code.o(\\.text)|{bd}/src/*.o(SORT_BY_NAME({ex}.text.func_*)) "
                 f"{bd}/src/*.o({ex}.text)|")
    if bd != "build":
        parts.append(f"s|build/src/code.o(\\.bss)|{bd}/src/*.o(.bss) {bd}/src/*.o(.sbss) "
                     f"{bd}/src/*.o(COMMON)|")
        parts.append(f"s|build/|{bd}/|g")
    return "sed '" + "; ".join(parts) + "' $in > $out"


orderld_cmd = _orderld(BUILDDIR)
if MODULES:
    orderld_cmd += (f" && python3 tools/slus_modules.py orderld --manifest {MODULE_MANIFEST}"
                    f" --input $out --output $out --out-dir {BUILDDIR}/module_assets")

out = ["# GENERATED by tools/configure.py — do not edit by hand", f"builddir = {BUILDDIR}", ""]
cc_piece_suffix = "$data_piece_step" if DATA_PIECE_MODULES else ""
out += [
    f"rule cc\n  command = tools/cc.sh $in $out $ccver \"$ccflags\" \"$asflags\"{cc_piece_suffix}\n  description = CC $in (gcc $ccver $ccflags $asflags)\n",
    "rule as\n  command = tools/as.sh $in $out\n  description = AS $in\n",
    "rule objbin\n  command = mipsel-linux-gnu-ld --relocatable --format=binary -o $out $in\n  description = BIN $in\n",
    # Gather every per-function section from ALL src objects and sort by name (== by
    # address) so decompiled C from different TU files (different gcc versions) lands
    # interleaved in the correct order. Residual non-func .text follows.
    f"rule orderld\n  command = {orderld_cmd}\n  description = LD-SCRIPT $out\n",
    f"rule link\n  command = mipsel-linux-gnu-ld -EL -T {BUILDDIR}/{BASE}_ordered.ld "
    + "".join(f"-T {p} " for p in LDSCRIPTS)
    + f"--no-check-sections -o $out $in\n  description = LINK $out\n",
    "rule objcopy\n  command = mipsel-linux-gnu-objcopy -O binary $in $out\n  description = OBJCOPY $out\n",
    "rule sha1\n  command = sha1sum -c $in && touch $out\n  description = SHA1 $in\n",
]
if MODULES:
    out += [
        f"rule module_assets\n  command = python3 tools/slus_modules.py assets --manifest {MODULE_MANIFEST}"
        f" --out-dir {BUILDDIR}/module_assets > /dev/null\n  description = MODULE-ASSETS $out\n",
        f"rule module_syms\n  command = python3 tools/slus_modules.py symbols --manifest {MODULE_MANIFEST}"
        " --input $in --output $out\n  description = MODULE-SYMS $out\n",
    ]
if DATA_PIECE_MODULES:
    out.append("rule data_piece_verify\n"
               "  command = python3 tools/slus_data_pieces.py --verify "
               "--manifest config/slus_modules.json --module $module_name "
               "--object $in --stamp $out\n"
               "  description = DATA-PIECE-VERIFY $in\n")

objs = []
# Per-file compiler config = (gcc version, extra flags). Azure Dreams links object
# files from multiple gcc versions AND per-TU flags; each distinct config gets a TU file.
CC_VER = {
    "src/code2.c": ("2.8.1", ""),
    "src/code3.c": ("2.95.2", "-fno-delayed-branch"),
    "src/code4.c": ("2.7.2", "-fno-expensive-optimizations"),
    "src/code5.c": ("2.7.2", "-G0 -fno-schedule-insns"),
    "src/code6.c": ("2.7.2", "-fno-schedule-insns -fno-schedule-insns2"),
    "src/code7.c": ("2.8.1", "-fno-schedule-insns2"),
    "src/code8.c": ("2.7.2-cdk", ""),
    "src/code9.c": ("2.95.2", "-fstrict-aliasing"),
    "src/code10.c": ("2.8.1", "-G0"),
    "src/code11.c": ("2.7.2", "-G0"),
    "src/code12.c": ("2.7.2", ""),
    "src/code13.c": ("2.8.1", ""),
    "src/code14.c": ("2.8.1", ""),
    "src/code15.c": ("2.7.2", ""),
    "src/w_8005A3F0.c": ("2.7.2-cdk", ""),
    "src/w_8004DCA8.c": ("2.7.2-cdk", ""),
    "src/w_8005AC30.c": ("2.7.2", ""),
    "src/w_8005B2C8.c": ("2.7.2", ""),
    "src/w_80040454.c": ("2.7.2", ""),
    "src/w_800439BC.c": ("2.8.1", ""),
    "src/w_80047A68.c": ("2.7.2", ""),
    "src/w_80049F2C.c": ("2.7.2", ""),
    "src/w_8004FC2C.c": ("2.7.2", ""),
    "src/w_800509C4.c": ("2.7.2", ""),
    "src/w_800510A0.c": ("2.7.2", ""),
    "src/w_8005D63C.c": ("2.7.2", ""),
    "src/w_8004397C.c": ("2.7.2", ""),
    "src/w_80047B80.c": ("2.8.1", ""),
    "src/w_80047BC0.c": ("2.8.1", ""),
    "src/w_80047DF0.c": ("2.7.2", ""),
    "src/w_80048D60.c": ("2.7.2", ""),
    "src/w_8004A534.c": ("2.7.2-cdk", ""),
    "src/w_8004AFE8.c": ("2.7.2", ""),
    "src/w_8004B324.c": ("2.7.2", ""),
    "src/w_8004DCEC.c": ("2.7.2-cdk", "-fno-schedule-insns -fno-delayed-branch"),
    "src/w_8004EEBC.c": ("2.7.2", ""),
    "src/w_8004F3D8.c": ("2.7.2", ""),
    "src/w_800541E8.c": ("2.7.2", ""),
    "src/w_8005A2FC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005A33C.c": ("2.7.2-cdk", ""),
    "src/w_8005A5C8.c": ("2.7.2", ""),
    "src/w_8003CAC4.c": ("2.8.1", ""),
    "src/w_800481E0.c": ("2.8.1", ""),
    "src/w_80049330.c": ("2.7.2", ""),
    "src/w_8004B2E0.c": ("2.7.2", "-G0 -fno-schedule-insns"),
    "src/w_8004CAE8.c": ("2.7.2", ""),
    "src/w_8004EBDC.c": ("2.7.2", ""),
    "src/w_8004F5B0.c": ("2.7.2", ""),
    "src/w_80053D64.c": ("2.7.2", ""),
    "src/w_800543C8.c": ("2.7.2", ""),
    "src/w_80057A50.c": ("2.8.1", ""),
    "src/w_800587B4.c": ("2.7.2-cdk", ""),
    "src/w_80058B2C.c": ("2.7.2", ""),
    "src/w_80059D1C.c": ("2.8.1", ""),
    "src/w_8003F320.c": ("2.7.2", ""),
    "src/w_8004AE68.c": ("2.8.1", ""),
    "src/w_80041AB0.c": ("2.7.2", ""),
    "src/w_80043CD0.c": ("2.7.2", ""),
    "src/w_80043868.c": ("2.7.2", ""),
    "src/w_8004A6C0.c": ("2.7.2", ""),
    "src/w_8004D5D0.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004D7A8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004D7E8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003E188.c": ("2.95.2", "-G0 -fno-schedule-insns"),
    "src/w_80042640.c": ("2.7.2-cdk", ""),
    "src/w_800422DC.c": ("2.7.2", ""),
    "src/w_80042518.c": ("2.7.2", ""),
    "src/w_80047E30.c": ("2.7.2", ""),
    "src/w_80047AB0.c": ("2.7.2", ""),
    "src/w_80048FBC.c": ("2.7.2", ""),
    "src/w_8004E928.c": ("2.7.2", ""),
    "src/w_80049150.c": ("2.7.2", ""),
    "src/w_8004B42C.c": ("2.7.2-cdk", "-G0 -fno-schedule-insns"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004DC14.c": ("2.7.2", ""),
    "src/w_80048EE4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80049004.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800494B4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80049D80.c": ("2.7.2", ""),
    "src/w_80049E1C.c": ("2.7.2", ""),
    "src/w_800497F4.c": ("2.7.2", ""),
    "src/w_8004E21C.c": ("2.7.2", ""),
    "src/w_8004E478.c": ("2.7.2", ""),
    "src/w_8004E5A0.c": ("2.7.2", ""),
    "src/w_8004E5E8.c": ("2.7.2", ""),
    "src/w_8004E634.c": ("2.7.2", ""),
    "src/w_8005D550.c": ("2.7.2", ""),
    "src/w_8003E70C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003F688.c": ("2.7.2-cdk", ""),
    "src/w_80041B98.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80043DB8.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80047D44.c": ("2.7.2", ""),
    "src/w_80047E78.c": ("2.7.2", ""),
    "src/w_80041E28.c": ("2.7.2", ""),
    "src/w_8004B298.c": ("2.7.2", "-G0 -fno-schedule-insns"),
    "src/w_80047738.c": ("2.7.2", ""),
    "src/w_8004A0C0.c": ("2.7.2-cdk", ""),
    "src/w_8004D75C.c": ("2.7.2-cdk", ""),
    "src/w_8004ED5C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80051164.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004FFA8.c": ("2.7.2", ""),
    "src/w_80058850.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80058940.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005AE90.c": ("2.7.2-cdk", ""),
    "src/w_80056A08.c": ("2.7.2-cdk", ""),
    "src/w_8005B27C.c": ("2.7.2", ""),
    "src/w_8005AE08.c": ("2.7.2-cdk", ""),
    "src/w_8005C5D0.c": ("2.7.2-cdk", ""),
    "src/w_8005C668.c": ("2.7.2-cdk", ""),
    "src/w_800563B0.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80056DB4.c": ("2.7.2-cdk", ""),
    "src/w_8005C6B4.c": ("2.7.2-cdk", ""),
    "src/w_80056D44.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003F55C.c": ("2.7.2", ""),
    "src/w_80041C64.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80043E60.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80047C8C.c": ("2.7.2", ""),
    "src/w_800498A0.c": ("2.7.2-cdk", "-G0"),
    "src/w_8005405C.c": ("2.8.1", ""),
    "src/w_80058B70.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003F794.c": ("2.7.2-cdk", ""),
    "src/w_80041BE4.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_800411AC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80041134.c": ("2.8.1", ""),
    "src/w_80048190.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80047C00.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80047CD8.c": ("2.7.2", ""),
    "src/w_800489F4.c": ("2.7.2", ""),
    "src/w_8004A4E4.c": ("2.7.2", ""),
    "src/w_8004B248.c": ("2.7.2", ""),
    "src/w_80049790.c": ("2.7.2", ""),
    "src/w_8004B1DC.c": ("2.7.2-cdk", ""),
    "src/w_8004D45C.c": ("2.7.2", ""),
    "src/w_8004D70C.c": ("2.7.2", ""),
    "src/w_8004DA24.c": ("2.7.2", ""),
    "src/w_8004EB3C.c": ("2.7.2", ""),
    "src/w_8004EB8C.c": ("2.7.2", ""),
    "src/w_80050EA8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800401FC.c": ("2.7.2", ""),
    "src/w_8004FDE0.c": ("2.7.2-cdk", ""),
    "src/w_80044AAC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003FB98.c": ("2.7.2", ""),
    "src/w_80058494.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80056408.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800564A8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80056948.c": ("2.7.2-cdk", ""),
    "src/w_800565D8.c": ("2.7.2", ""),
    "src/w_800586B0.c": ("2.7.2-cdk", ""),
    "src/w_8005863C.c": ("2.7.2-cdk", ""),
    "src/w_800585A0.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80058800.c": ("2.7.2-cdk", ""),
    "src/w_8005E450.c": ("2.7.2", ""),
    "src/w_8005E7E0.c": ("2.7.2", ""),
    "src/w_8003FFF0.c": ("2.7.2", ""),
    "src/w_80040BB4.c": ("2.7.2-cdk", ""),
    "src/w_8004A784.c": ("2.7.2", ""),
    "src/w_8004D98C.c": ("2.7.2", ""),
    "src/w_8004E884.c": ("2.7.2", ""),
    "src/w_8004DA74.c": ("2.7.2-cdk", ""),
    "src/w_8004EA70.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004EAC4.c": ("2.7.2", ""),
    "src/w_8004ECAC.c": ("2.7.2-cdk", ""),
    "src/w_80050640.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800505BC.c": ("2.7.2", ""),
    "src/w_800504B4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800546B0.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800540A8.c": ("2.7.2-cdk", ""),
    "src/w_80054C58.c": ("2.7.2-cdk", ""),
    "src/w_8004F95C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005D838.c": ("2.7.2", ""),
    "src/w_8005ECA0.c": ("2.7.2", ""),
    "src/w_8005D4E8.c": ("2.7.2", ""),
    "src/w_8005D95C.c": ("2.7.2-cdk", ""),
    "src/w_8005D460.c": ("2.7.2", ""),
    "src/w_8005D9DC.c": ("2.7.2", ""),
    "src/w_8005CA90.c": ("2.7.2", ""),
    "src/w_80040060.c": ("2.7.2", ""),
    "src/w_800403BC.c": ("2.7.2", "-G0"),
    "src/w_80040190.c": ("2.7.2", ""),
    "src/w_8004027C.c": ("2.7.2", ""),
    "src/w_8003FA44.c": ("2.7.2", ""),
    "src/w_8003FC64.c": ("2.7.2", ""),
    "src/w_8004E130.c": ("2.7.2-cdk", ""),
    "src/w_8004E69C.c": ("2.7.2-cdk", ""),
    "src/w_8004E188.c": ("2.7.2-cdk", ""),
    "src/w_8004F558.c": ("2.7.2", "-G0"),
    "src/w_80050A00.c": ("2.7.2", ""),
    "src/w_8005537C.c": ("2.7.2-cdk", ""),
    "src/w_8005440C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005560C.c": ("2.7.2-cdk", ""),
    "src/w_800559B4.c": ("2.7.2-cdk", "-G0"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005B418.c": ("2.7.2-cdk", ""),
    "src/w_80056C30.c": ("2.7.2-cdk", ""),
    "src/w_8005ACDC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005BAB0.c": ("2.7.2-cdk", ""),
    "src/w_80040FDC.c": ("2.7.2-cdk", ""),
    "src/w_80041038.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800411FC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80040F2C.c": ("2.7.2-cdk", ""),
    "src/w_80043E04.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80044A50.c": ("2.8.1", ""),
    "src/w_80048998.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80048B28.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800491F4.c": ("2.7.2", ""),
    "src/w_8004B6BC.c": ("2.7.2", ""),
    "src/w_8005A56C.c": ("2.7.2", ""),
    "src/w_8005A4E8.c": ("2.7.2", ""),
    "src/w_80042984.c": ("2.7.2", ""),
    "src/w_800448BC.c": ("2.7.2", ""),
    "src/w_80048AC8.c": ("2.7.2", ""),
    "src/w_8004CAA0.c": ("2.7.2", "-fno-schedule-insns2"),
    "src/w_8004B718.c": ("2.7.2", ""),
    "src/w_8004B774.c": ("2.7.2", ""),
    "src/w_8004B7D0.c": ("2.7.2-cdk", "-G0"),
    "src/w_80041284.c": ("2.7.2", ""),
    "src/w_80053E90.c": ("2.7.2", ""),
    "src/w_80054D64.c": ("2.7.2-cdk", ""),
    "src/w_800552C8.c": ("2.7.2-cdk", ""),
    "src/w_8005B470.c": ("2.7.2", ""),
    "src/w_8005D678.c": ("2.7.2", ""),
    "src/w_8005D7BC.c": ("2.7.2", "-G0"),
    "src/w_8005D88C.c": ("2.7.2", ""),
    "src/w_8005EB78.c": ("2.7.2", ""),
    "src/w_8005EC40.c": ("2.7.2", ""),
    "src/w_8005ECF8.c": ("2.7.2", ""),
    "src/w_8003F9E0.c": ("2.7.2", "-G0 -fno-schedule-insns"),
    "src/w_8004846C.c": ("2.7.2", ""),
    "src/w_800483AC.c": ("2.7.2", ""),
    "src/w_8004A10C.c": ("2.7.2", ""),
    "src/w_8004B028.c": ("2.7.2", ""),
    "src/w_8004CE68.c": ("2.7.2", ""),
    "src/w_8004EF90.c": ("2.8.1", ""),
    "src/w_8003DF0C.c": ("2.7.2-cdk", ""),
    "src/w_8003E0C4.c": ("2.7.2", ""),
    "src/w_80040490.c": ("2.7.2", ""),
    "src/w_800404F8.c": ("2.7.2", ""),
    "src/w_8004878C.c": ("2.7.2", "-G0"),
    "src/w_80041094.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80041818.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800482C8.c": ("2.7.2-cdk", ""),
    "src/w_80044B48.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80048500.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004A658.c": ("2.7.2-cdk", ""),
    "src/w_8004B854.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004B8DC.c": ("2.7.2", ""),
    "src/w_8004FD78.c": ("2.7.2-cdk", ""),
    "src/w_800479D4.c": ("2.7.2", ""),
    "src/w_8004425C.c": ("2.7.2", ""),
    "src/w_8004437C.c": ("2.7.2-cdk", ""),
    "src/w_80054E00.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005AC68.c": ("2.7.2-cdk", ""),
    "src/w_8005A428.c": ("2.7.2-cdk", ""),
    "src/w_8003F624.c": ("2.7.2", ""),
    "src/w_80048118.c": ("2.7.2", ""),
    "src/w_80048224.c": ("2.7.2", ""),
    "src/w_80048088.c": ("2.7.2", ""),
    "src/w_8004450C.c": ("2.7.2", ""),
    "src/w_8004CCBC.c": ("2.8.1", ""),
    "src/w_8004EEFC.c": ("2.7.2-cdk", ""),
    "src/w_80050550.c": ("2.7.2", ""),
    "src/w_800590E0.c": ("2.7.2", ""),
    "src/w_80058ABC.c": ("2.7.2", ""),
    "src/w_80058A04.c": ("2.7.2", ""),
    "src/w_8003D5A4.c": ("2.7.2-cdk", "-G0"),
    "src/w_80047784.c": ("2.7.2", ""),
    "src/w_80048A44.c": ("2.7.2", ""),
    "src/w_8004A940.c": ("2.7.2-cdk", ""),
    "src/w_80052A20.c": ("2.8.1", ""),
    "src/w_80053E20.c": ("2.7.2-cdk", ""),
    "src/w_800553D4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80054F9C.c": ("2.7.2-cdk", ""),
    "src/w_8003E2D8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80040574.c": ("2.7.2", "-G0"),
    "src/w_800405E8.c": ("2.7.2", ""),
    "src/w_80047270.c": ("2.7.2", "-G0"),
    "src/w_8004EFF4.c": ("2.7.2-cdk", ""),
    "src/w_8004F068.c": ("2.8.1", ""),
    "src/w_800511B4.c": ("2.7.2-cdk", ""),
    "src/w_8004B364.c": ("2.7.2", ""),
    "src/w_8004EDA8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800525D4.c": ("2.7.2-cdk", ""),
    "src/w_80054A7C.c": ("2.7.2", ""),
    "src/w_80053F98.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005C710.c": ("2.7.2-cdk", "-G0 -fno-schedule-insns"),
    "src/w_8005C784.c": ("2.7.2-cdk", ""),
    "src/w_8004761C.c": ("2.7.2", ""),
    "src/w_80050308.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80054228.c": ("2.7.2", ""),
    "src/w_800549FC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80055C50.c": ("2.7.2-cdk", ""),
    "src/w_80055D84.c": ("2.7.2-cdk", ""),
    "src/w_8005D730.c": ("2.7.2", ""),
    "src/w_8004C010.c": ("2.7.2", ""),
    "src/w_80047EEC.c": ("2.7.2-cdk", ""),
    "src/w_800475A4.c": ("2.7.2", ""),
    "src/w_80054CD4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80055CF4.c": ("2.7.2-cdk", ""),
    "src/w_80055B44.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800588C8.c": ("2.7.2-cdk", ""),
    "src/w_8004D690.c": ("2.7.2", ""),
    "src/w_80050EF8.c": ("2.7.2-cdk", ""),
    "src/w_80051708.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80051E94.c": ("2.7.2-cdk", ""),
    "src/w_80051BFC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005AFF4.c": ("2.7.2-cdk", ""),
    "src/w_8005AF74.c": ("2.7.2-cdk", ""),
    "src/w_8005A26C.c": ("2.7.2-cdk", "-O1"),
    "src/w_800599B0.c": ("2.7.2-cdk", "-G0 -fno-strength-reduce"),
    "src/w_80059F8C.c": ("2.7.2-cdk", "-G0"),
    "src/w_8005A608.c": ("2.7.2-cdk", "-fno-cse-follow-jumps"),
    "src/w_8005A90C.c": ("2.7.2-cdk", "-O1 -fschedule-insns2"),
    "src/w_8005C130.c": ("2.7.2-cdk", ""),
    "src/w_80044618.c": ("2.7.2", ""),
    "src/w_80047694.c": ("2.7.2-cdk", ""),
    "src/w_80048870.c": ("2.7.2", ""),
    "src/w_8005497C.c": ("2.7.2", ""),
    "src/w_8004A9B0.c": ("2.7.2-cdk", ""),
    "src/w_8004CC38.c": ("2.8.1", ""),
    "src/w_8004E0AC.c": ("2.7.2", ""),
    "src/w_8004FE78.c": ("2.7.2", "-G0"),
    "src/w_800510DC.c": ("2.7.2", "-G0"),
    "src/w_8004FF20.c": ("2.7.2-cdk", ""),
    "src/w_800537D0.c": ("2.7.2", "-fno-strength-reduce"),
    "src/w_80044698.c": ("2.7.2", ""),
    "src/w_8004EC20.c": ("2.7.2-cdk", ""),
    "src/w_80049CF4.c": ("2.7.2", ""),
    "src/w_800508F0.c": ("2.7.2", ""),
    "src/w_80050AF0.c": ("2.7.2", ""),
    "src/w_80043674.c": ("2.7.2-cdk", ""),
    "src/w_80045C34.c": ("2.7.2-cdk", ""),
    "src/w_80045340.c": ("2.7.2-cdk", ""),  # fidelity step 4 (gp_81510): retail-proven splitting recipe
    "src/w_8004A030.c": ("2.7.2-cdk", "-fno-schedule-insns"),
    "src/w_8003E240.c": ("2.91.66", "-G0"),
    "src/w_800418B4.c": ("2.6.3", "-G0"),
    "src/w_80047F90.c": ("2.7.2", ""),
    "src/w_8004B660.c": ("2.7.2", ""),
    "src/w_8004D12C.c": ("2.7.2", ""),
    "src/w_8004ED00.c": ("2.7.2-cdk", "-G0"),
    "src/w_80053DF0.c": ("2.7.2-cdk", "-G0"),
    "src/w_800558FC.c": ("2.7.2-cdk", "-G0"),
    "src/w_8005DF80.c": ("2.6.3", "-G0"),
    "src/w_80048734.c": ("2.7.2", ""),
    "src/w_8003F2A4.c": ("2.6.3", "-fno-schedule-insns"),
    "src/w_80048224.c": ("2.7.2", ""),
    "src/w_8005D598.c": ("2.7.2", ""),
    "src/w_8004AB7C.c": ("2.7.2", ""),
    "src/w_8004D91C.c": ("2.7.2", ""),
    "src/w_80054788.c": ("2.7.2-cdk", ""),
    "src/w_8004B568.c": ("2.7.2", ""),
    "src/w_8004FA2C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80054704.c": ("2.7.2-cdk", ""),
    "src/w_80043704.c": ("2.7.2", ""),
    "src/w_800437A4.c": ("2.7.2", ""),
    "src/w_80056800.c": ("2.7.2-cdk", ""),
    "src/w_8004A7D8.c": ("2.7.2-cdk", ""),
    "src/w_80048734.c": ("2.7.2", ""),
    "src/w_80043914.c": ("2.7.2-cdk", "-G16"),
    "src/w_8003D8B0.c": ("2.7.2-cdk", "-G12"),
    "src/w_80059D60.c": ("2.7.2-cdk", ""),
    "src/w_80056558.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004A700.c": ("2.7.2-cdk", ""),
    "src/w_800520B4.c": ("2.7.2-cdk", "-G0"),
    "src/w_800544A4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800568B4.c": ("2.7.2-cdk", ""),
    "src/w_8003E02C.c": ("2.7.2-cdk", ""),
    "src/w_80041E70.c": ("2.7.2", ""),
    "src/w_8004A83C.c": ("2.7.2", ""),
    "src/w_8004F330.c": ("2.8.1", ""),
    "src/w_8004CB2C.c": ("2.7.2-cdk", ""),
    "src/w_80042560.c": ("2.7.2-cdk", ""),
    "src/w_8004DE88.c": ("2.7.2-cdk", ""),
    "src/w_8004C080.c": ("2.7.2-cdk", "-G0"),
    "src/w_8003CB08.c": ("2.7.2-cdk", ""),
    "src/w_80059E94.c": ("2.7.2-cdk", "-fno-schedule-insns"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005A778.c": ("2.7.2-cdk", ""),
    "src/w_800429E4.c": ("2.7.2-cdk", ""),
    "src/w_8005A1D0.c": ("2.7.2-cdk", ""),  # r77: C at the retail-proven splitting cell (was a .word paste)
    "src/w_80059DAC.c": ("2.7.2-cdk", ""),
    "src/w_80046A5C.c": ("2.7.2", ""),
    "src/w_80044BB0.c": ("2.7.2", ""),
    "src/w_80044C54.c": ("2.7.2-cdk", ""),
    "src/w_80049E88.c": ("2.7.2-cdk", ""),
    "src/w_8004A574.c": ("2.7.2-cdk", ""),
    "src/w_800488F0.c": ("2.7.2", ""),
    "src/w_8004D1EC.c": ("2.7.2-cdk", ""),
    "src/w_8005AAA8.c": ("2.7.2", ""),
    "src/w_8005AB50.c": ("2.7.2-cdk", ""),
    "src/w_800485E0.c": ("2.7.2", ""),
    "src/w_80058700.c": ("2.7.2-cdk", ""),
    "src/w_8005B16C.c": ("2.7.2-cdk", ""),
    "src/w_80055864.c": ("2.7.2-cdk", ""),
    "src/w_80053EF0.c": ("2.7.2-cdk", ""),
    "src/w_8003DE58.c": ("2.7.2", ""),
    "src/w_80054538.c": ("2.7.2", ""),
    "src/w_800545F4.c": ("2.7.2-cdk", ""),
    "src/w_8004FFF4.c": ("2.7.2", "-fno-strength-reduce"),
    "src/w_8003FF2C.c": ("2.7.2", ""),
    "src/w_8003FD64.c": ("2.7.2", ""),
    "src/w_80052C10.c": ("2.7.2-cdk", ""),
    "src/w_80054104.c": ("2.7.2-cdk", "-G0"),
    "src/w_8003D7DC.c": ("2.7.2-cdk", "-fno-expensive-optimizations"),
    "src/w_8003CCB0.c": ("2.7.2-cdk", ""),
    "src/w_8003D0F0.c": ("2.7.2-cdk", ""),
    "src/w_8003E39C.c": ("2.7.2-cdk", "-mmips-as -G0"),
    "src/w_8003E758.c": ("2.7.2-cdk", "-G32 -fno-expensive-optimizations"),
    "src/w_8003DBD0.c": ("2.7.2-cdk", ""),
    "src/w_8003D760.c": ("2.7.2-cdk", "-G16"),
    "src/w_80046D64.c": ("2.7.2-cdk", ""),
    "src/w_80048660.c": ("2.7.2-cdk", ""),
    "src/w_80047338.c": ("2.7.2-cdk", ""),
    "src/w_8004F884.c": ("2.7.2-cdk", ""),
    "src/w_8004F780.c": ("2.7.2-cdk", ""),
    "src/w_80043A68.c": ("2.7.2-cdk", ""),
    "src/w_80043B4C.c": ("2.7.2-cdk", ""),
    "src/w_80048E00.c": ("2.7.2", ""),
    "src/w_8003F80C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80041900.c": ("2.8.1", "-G0"),
    "src/w_800557C8.c": ("2.8.1", ""),
    "src/w_80053374.c": ("2.7.2-cdk", ""),
    "src/w_8003DF74.c": ("2.7.2-cdk", ""),
    "src/w_8004713C.c": ("2.7.2", ""),
    "src/w_80048B8C.c": ("2.7.2", ""),
    "src/w_800478E8.c": ("2.7.2", ""),
    "src/w_80046F88.c": ("2.7.2", ""),
    "src/w_8005552C.c": ("2.7.2", ""),
    "src/w_8004F684.c": ("2.7.2-cdk", ""),
    "src/w_8004AA78.c": ("2.7.2-cdk", ""),
    "src/w_8004AEC4.c": ("2.7.2", "-fno-schedule-insns"),
    "src/w_80043568.c": ("2.8.1", ""),
    "src/w_8004F0DC.c": ("2.7.2", ""),
    "src/w_800542BC.c": ("2.7.2-cdk", "-G0"),
    "src/w_8004B08C.c": ("2.7.2-cdk", ""),
    "src/w_80049374.c": ("2.7.2-cdk", ""),
    "src/w_80046AFC.c": ("2.7.2", ""),
    "src/w_8004068C.c": ("2.7.2", ""),
    "src/w_8004CD28.c": ("2.7.2", ""),
    "src/w_80056098.c": ("2.7.2", "-fno-schedule-insns"),
    "src/w_80046C20.c": ("2.7.2", ""),
    "src/w_80052A90.c": ("2.7.2", ""),
    "src/w_8004951C.c": ("2.7.2-cdk", ""),
    "src/w_800500B4.c": ("2.7.2", "-fno-strength-reduce"),
    "src/w_80053858.c": ("2.7.2-cdk", ""),
    "src/w_8004BDDC.c": ("2.7.2", ""),
    "src/w_8003E1FC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8005B378.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003D468.c": ("2.7.2-cdk", "-G0"),
    "src/w_80047200.c": ("2.7.2", ""),
    "src/w_8004D614.c": ("2.7.2-cdk", ""),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_800434E4.c": ("2.7.2-cdk", "-G0"),
    "src/w_80058510.c": ("2.7.2-cdk", ""),
    "src/w_8005B070.c": ("2.7.2-cdk", ""),
    "src/w_8004F418.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003FE78.c": ("2.7.2", ""),
    "src/w_800402F4.c": ("2.7.2-cdk", "-G0"),
    "src/w_8004F1E8.c": ("2.7.2", ""),
    "src/w_8004FC98.c": ("2.7.2-cdk", ""),
    "src/w_80047468.c": ("2.7.2-cdk", ""),
    "src/w_80059BC4.c": ("2.7.2-cdk", "-fno-strength-reduce"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003F368.c": ("2.7.2", ""),
    "src/w_8003F5AC.c": ("2.7.2-cdk", ""),
    "src/w_80042B68.c": ("2.7.2", ""),
    "src/w_8005500C.c": ("2.7.2-cdk", ""),
    "src/w_8003F8F8.c": ("2.7.2", "-G0"),
    "src/w_80047FF4.c": ("2.7.2", ""),
    "src/w_80050A58.c": ("2.7.2-cdk", ""),
    "src/w_800477F4.c": ("2.7.2", ""),
    "src/w_8004A170.c": ("2.7.2-cdk", ""),
    "src/w_80044144.c": ("2.7.2-cdk", "-G16"),
    "src/w_8004A330.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004DF8C.c": ("2.7.2-cdk", ""),
    "src/w_80053428.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80050E20.c": ("2.7.2-cdk", ""),
    "src/w_80041AE4.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80052FE8.c": ("2.7.2-cdk", ""),
    "src/w_800595C0.c": ("2.7.2-cdk", ""),
    "src/w_80057A94.c": ("2.7.2-cdk", ""),
    "src/w_8003F270.c": ("2.6.3", "-O1"),
    "src/w_80053CFC.c": ("2.7.2", ""),
    "src/w_80043D04.c": ("2.7.2-cdk", "-G16"),  # fidelity step 4 (gp_ownership_wave): retail-proven splitting recipe
    "src/w_80040AA0.c": ("2.7.2-cdk", ""),
    "src/w_80043FD0.c": ("2.7.2-cdk", "-G0"),
    "src/w_80042710.c": ("2.7.2", ""),
    "src/w_8005914C.c": ("2.7.2-cdk", "-fno-strength-reduce"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80055E84.c": ("2.7.2-cdk", ""),
    "src/w_80042A80.c": ("2.7.2-cdk", ""),
    "src/w_8003E34C.c": ("2.7.2-cdk", ""),
    "src/w_8004A464.c": ("2.7.2-cdk", ""),
    "src/w_80055ADC.c": ("2.7.2", ""),
    "src/w_80040CBC.c": ("2.7.2-cdk", "-G16"),
    "src/w_800407C0.c": ("2.7.2-cdk", ""),
    "src/w_80042BDC.c": ("2.7.2-cdk", "-G16"),
    "src/w_800453E0.c": ("2.7.2-cdk", ""),
    "src/w_80045CC4.c": ("2.7.2-cdk", ""),
    "src/w_8004B954.c": ("2.7.2-cdk", ""),
    "src/w_8004C36C.c": ("2.7.2-cdk", ""),
    "src/w_8004CECC.c": ("2.7.2-cdk", ""),
    "src/w_8004E298.c": ("2.7.2-cdk", "-O1 -fschedule-insns2"),
    "src/w_8004E6F4.c": ("2.6.3", ""),
    "src/w_800499E8.c": ("2.7.2-cdk", ""),
    "src/w_8004FAA4.c": ("2.7.2-cdk", ""),
    "src/w_80050BA4.c": ("2.7.2-cdk", ""),
    "src/w_80050DA8.c": ("2.7.2-cdk", ""),
    "src/w_800530C4.c": ("2.7.2", "-G0"),
    "src/w_80055BD8.c": ("2.7.2-cdk", "-G0"),
    "src/w_80043EB8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_80041CBC.c": ("2.7.2-cdk", "-G0"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004F9AC.c": ("2.7.2-cdk", ""),
    "src/w_8004F5F4.c": ("2.7.2-cdk", "-G0"),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8003F6F4.c": ("2.6.3", ""),
    "src/w_8005084C.c": ("2.7.2-cdk", ""),
    "src/w_80050FF4.c": ("2.7.2-cdk", "-G0"),
    "src/w_80048C3C.c": ("2.7.2", ""),
    "src/w_80051228.c": ("2.7.2", ""),
    "src/w_800400B8.c": ("2.7.2-cdk", "-fno-cse-skip-blocks"),
    "src/w_80047054.c": ("2.8.1", ""),
    "src/w_800423C0.c": ("2.7.2-cdk", ""),  # fidelity step 4 (step4): retail-proven splitting recipe
    "src/w_8004D294.c": ("2.7.2-cdk", ""),
    "src/w_80059814.c": ("2.7.2-cdk", ""),
    "src/w_80053604.c": ("2.7.2-cdk", ""),
    "src/w_80051CC4.c": ("2.7.2-cdk", "-G0"),
    "src/w_8004D4AC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_8004AC3C.c": ("2.7.2-cdk", ""),
    "src/w_800589B8.c": ("2.7.2-cdk", ""),
    "src/w_800492B0.c": ("2.7.2-cdk", ""),
    "src/w_80042900.c": ("2.7.2", ""),
    "src/w_80043458.c": ("2.8.1", ""),
    "src/w_8004A24C.c": ("2.7.2", ""),
    "src/w_80058E6C.c": ("2.7.2-cdk", "-fno-strength-reduce"),
    "src/w_80057948.c": ("2.7.2-cdk", "-fno-strength-reduce"),
    "src/w_80051548.c": ("2.7.2-cdk", "-O1 -fschedule-insns2"),
    "src/w_80051F58.c": ("2.7.2-cdk", ""),
    "src/w_80052144.c": ("2.7.2", "-G0"),
    "src/w_80052774.c": ("2.7.2-cdk", ""),
    "src/w_80052CE0.c": ("2.7.2-cdk", ""),
    "src/w_80053A88.c": ("2.7.2-cdk", ""),
    "src/w_80054B08.c": ("2.7.2-cdk", ""),
    "src/w_80056654.c": ("2.7.2-cdk", ""),
    "src/w_80056E10.c": ("2.7.2-cdk", "-G0"),
    "src/w_80057D20.c": ("2.7.2-cdk", "-G0"),
    "src/w_800550E8.c": ("2.7.2-cdk", ""),
    "src/w_8005313C.c": ("2.7.2-cdk", ""),
    "src/w_8005947C.c": ("2.7.2-cdk", ""),
    "src/w_800561D8.c": ("2.8.1", ""),
    "src/w_80041344.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/w_800506BC.c": ("2.7.2-cdk", ""),
    "src/w_800463EC.c": ("2.7.2-cdk", "-O2"),
    "src/w_80044D24.c": ("2.7.2-cdk", "-O2"),
    "src/w_8003E14C.c": ("2.7.2-cdk", "-G0"),
    "src/w_8004D828.c": ("2.95.2", "-fno-schedule-insns2"),
    "src/w_8004DD2C.c": ("2.7.2-cdk", ""),
    "src/w_8004E9EC.c": ("2.7.2-cdk", ""),
    "src/w_8004491C.c": ("2.7.2-cdk", ""),
    "src/w_800597A8.c": ("2.7.2", ""),
    "src/w_800439F8.c": ("2.7.2-cdk", "-G16"),
    "src/w_8004D880.c": ("2.7.2", "-fno-cse-follow-jumps -fno-cse-skip-blocks"),
    "src/w_8005C2C0.c": ("2.7.2-cdk", ""),
    "src/w_8005CC04.c": ("2.7.2", "-G0"),
    "src/w_8005CE98.c": ("2.7.2", "-G0"),
    "src/w_8005D1D0.c": ("2.7.2", "-G0"),
    "src/w_8005DA88.c": ("2.7.2", "-G0"),
    "src/w_8005E97C.c": ("2.7.2", "-G0"),
    "src/w_8005E4C4.c": ("2.7.2", "-G0 -fno-cse-follow-jumps"),
    "src/w_8005EDA0.c": ("2.7.2", "-G0"),
    "src/w_8005B4D0.c": ("2.7.2-cdk", ""),
    "src/w_8005BBFC.c": ("2.7.2-cdk", ""),
    "src/w_8005CB88.c": ("2.7.2", ""),
    "src/w_8005C4D0.c": ("2.7.2-cdk", ""),
    "src/w_8005F740.c": ("2.7.2", ""),
    "src/w_80050CDC.c": ("2.7.2", "-G0"),
    "src/w_8005D124.c": ("2.7.2", "-G0"),
    "src/w_8005D064.c": ("2.7.2", "-G0"),
    "src/w_8003FAD4.c": ("2.7.2", ""),
    "src/w_80040C08.c": ("2.7.2-cdk", "-fno-schedule-insns -G16"),
    "src/w_80046E38.c": ("2.6.3", "-G0"),
    "src/w_8003E4FC.c": ("2.7.2-cdk", ""),
    "src/w_80046884.c": ("2.7.2-cdk", ""),
    "src/w_800517CC.c": ("2.7.2-cdk", "-G16"),
    "src/w_80044724.c": ("2.7.2-cdk", ""),
    "src/w_80049F68.c": ("2.7.2-cdk", "-fno-strength-reduce"),
    "src/w_8004DDE4.c": ("2.7.2-cdk", ""),
    "src/w_80041A10.c": ("2.7.2-cdk", "-G12"),
    "src/w_80043C30.c": ("2.7.2-cdk", "-G12"),
    "src/konami_runtime_w_80033B78.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033B9C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033BC0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033C1C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033C84.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033CD8.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033D08.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033D38.c": ("2.7.2", ""),
    "src/konami_runtime_w_80034EB4.c": ("2.7.2", ""),
    "src/konami_runtime_w_80034F88.c": ("2.7.2", ""),
    "src/konami_runtime_w_80034F9C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80034FD0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035060.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035068.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035090.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035208.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035234.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035260.c": ("2.7.2", ""),
    "src/konami_runtime_w_800355EC.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035820.c": ("2.7.2", ""),
    "src/konami_runtime_w_80036988.c": ("2.7.2", ""),
    "src/konami_runtime_w_800374F4.c": ("2.7.2", ""),
    "src/konami_runtime_w_800382F0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80038478.c": ("2.7.2", ""),
    "src/konami_runtime_w_800384F8.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039208.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039640.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003965C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039760.c": ("2.7.2", ""),
    "src/konami_runtime_w_800399EC.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039A88.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039ED0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039F28.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A288.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AB14.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AEC8.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AEF8.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AF58.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AF8C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B06C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B0B4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B1B4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B210.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B264.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B2C4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B42C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B988.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B9B8.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003BAD8.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C0A4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C0C0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80033BE4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80033C8C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80033D44.c": ("2.8.1", ""),  # fidelity step 4 (gp_8099c): retail-proven splitting recipe
    "src/konami_runtime_w_80034E48.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80034F58.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80034FE4.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800350D4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003528C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800352B4.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800352D8.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800352FC.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80035320.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80035614.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003566C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003571C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80035760.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800357B0.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800357D0.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80035AAC.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80035ABC.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80035C44.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80035D40.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036110.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036154.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036210.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003626C.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800362A0.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036434.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036484.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800364BC.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003661C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036880.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80036C44.c": ("2.7.2", ""),
    "src/konami_runtime_w_80036D4C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003719C.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80038000.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800381A4.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800381D0.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80038288.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003832C.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80038368.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80038394.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80038464.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800384A8.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80038538.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80038570.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80038588.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800385D0.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800385E8.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80038630.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80038648.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_80038708.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_800389B4.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800390D0.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80039148.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80039568.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800395F0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039A08.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80039ACC.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80039B84.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_8003AAC4.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_8003AAD4.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_8003AAE4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003ACC0.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003ADF4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AEA8.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B034.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_8003B188.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003B1E4.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003B238.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003B298.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003B2F8.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003B324.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B35C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B400.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003B8DC.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_8003B9E8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003BA24.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003BA60.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003BA9C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C128.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003C2B8.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_8003C890.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039ED8.c": ("2.7.2", ""),
    "src/konami_runtime_w_800350B0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039B94.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039BE4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80035348.c": ("2.8.1", ""),
    "src/konami_runtime_w_800383D4.c": ("2.8.1", ""),
    "src/konami_runtime_w_80039C44.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039D10.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039578.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800395B0.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800391EC.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AAF8.c": ("2.8.1", ""),
    "src/konami_runtime_w_800368D0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039BBC.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A9B8.c": ("2.7.2", ""),
    "src/konami_runtime_w_800391BC.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80034EC4.c": ("2.8.1", ""),
    "src/konami_runtime_w_80039EF4.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039884.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80039C0C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C06C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003ADB4.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/konami_runtime_w_8003C488.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C8E4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A7BC.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039214.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A01C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AE60.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C634.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037D50.c": ("2.8.1", ""),
    "src/konami_runtime_w_8003C5F0.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80039730.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039F4C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039AF0.c": ("2.8.1", ""),
    "src/konami_runtime_w_8003AE28.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C450.c": ("2.7.2", "-O2"),
    "src/konami_runtime_w_80039B28.c": ("2.7.2", ""),
    "src/konami_runtime_w_80038240.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/konami_runtime_w_8003AA84.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039258.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A29C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003BD34.c": ("2.7.2-cdk", "-O1"),
    "src/konami_runtime_w_80033AA8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80033AE8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80033B2C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A248.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A468.c": ("2.7.2", ""),
    "src/konami_runtime_w_80036F24.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037090.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037394.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80036B10.c": ("2.7.2-cdk", "-G0"),
    "src/konami_runtime_w_80035484.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800387D0.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800375C0.c": ("2.7.2", "-O2"),
    "src/konami_runtime_w_8003BE1C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039F80.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A4B4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A500.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AF94.c": ("2.7.2", ""),
    "src/konami_runtime_w_80036ED4.c": ("2.7.2", ""),
    "src/konami_runtime_w_80037030.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A9E4.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AA34.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C0C8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C24C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C2F8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80035CE4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B7C8.c": ("2.7.2", ""),
    "src/konami_runtime_w_80038408.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003875C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80038690.c": ("2.7.2", ""),
    "src/konami_runtime_w_80038128.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80039FC0.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A7FC.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039DBC.c": ("2.7.2", ""),
    "src/konami_runtime_w_80034FFC.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80035BE0.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035C80.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A54C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A5B4.c": ("2.7.2", "-O2"),
    "src/konami_runtime_w_8003A61C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A684.c": ("2.7.2", "-O2"),
    "src/konami_runtime_w_8003A754.c": ("2.7.2", ""),
    "src/konami_runtime_w_800397A8.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039814.c": ("2.7.2", ""),
    "src/konami_runtime_w_80039D48.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80038C40.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80036900.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003BFE4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C520.c": ("2.7.2", "-G0"),
    "src/konami_runtime_w_800364EC.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037534.c": ("2.7.2", ""),
    "src/konami_runtime_w_800353F4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037F70.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003BD84.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035DBC.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/konami_runtime_w_80039694.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C3B4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80036A70.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80036574.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800369C8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80038A10.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800359FC.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003B820.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B64C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C920.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C160.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037D9C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/konami_runtime_w_80036C7C.c": ("2.7.2", ""),
    "src/konami_runtime_w_80037C7C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003AB44.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035AF8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80035E58.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80038CB8.c": ("2.7.2", ""),
    "src/konami_runtime_w_80037714.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C5A4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C364.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003AFE0.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003C4C8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B92C.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/konami_runtime_w_80034EF8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C6F8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C67C.c": ("2.7.2-cdk", "-fno-strength-reduce"),
    "src/konami_runtime_w_8003C758.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A6EC.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035D4C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A374.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800392A4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80035378.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800362D0.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A3E8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003666C.c": ("2.7.2-cdk", "-fno-schedule-insns"),
    "src/konami_runtime_w_8003A2E0.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A10C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80039C74.c": ("2.7.2", ""),
    "src/konami_runtime_w_80035164.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A1A4.c": ("2.7.2-cdk", "-fno-expensive-optimizations"),
    "src/konami_runtime_w_8003AC1C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A060.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003A858.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003AD08.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003605C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80039E1C.c": ("2.7.2", ""),
    "src/konami_runtime_w_8003A904.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B714.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003C7D8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80036350.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80039470.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80035888.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80038F48.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800366F4.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003B470.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80038AB8.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003931C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003800C.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_800398BC.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_80037E58.c": ("2.7.2-cdk", ""),
    "src/konami_runtime_w_8003BAF8.c": ("2.7.2-cdk", ""),  # fidelity step 4 (cdk211): retail-proven splitting recipe
    "src/konami_runtime_w_80033D54.c": ("2.8.1", ""),
    "src/konami_runtime_w_800345B8.c": ("2.7.2-cdk", ""),
}
DEFAULT_CC = ("2.7.2", "")
AS_FLAGS = {
    # func_8005D598 needs maspsx's checked div/mod expansion. Keep this scoped:
    # enabling --expand-div globally changes already-matched runtime-div functions.
    "src/w_8005D598.c": "--expand-div",
    "src/w_8005CB88.c": "--preserve-immediate-funcaddr-la",
}
# Explicit partition build adapter. The original CC_VER row recipe stays
# authoritative even while its compiler input is a generated remainder view.
PARTITION_PLAN_FILE = "config/slus_partitions.json"
PARTITIONS = partition_support.load_plan(PARTITION_PLAN_FILE)
PARTITION_PATHS = partition_support.output_paths(PARTITIONS)
PARTITION_MODULE_DEPS = {}
PARTITION_COVERAGE_STAMP = f"{BUILDDIR}/partition_sources/coverage.ok"
if not PARTITIONS and any(module.get("partition_only") is True for module in MODULES):
    # An owner with no whole rows cannot be anchored by the logical ledger.
    # Even an absent optional plan must go through the incoming-part check.
    partition_support.validate_context([], MODULES, [], "raw/slus")
if PARTITIONS:
    if NM:
        raise RuntimeError("SLUS partitions are not supported in --non-matching builds")
    partition_aliases = partition_support.read_aliases("config/names.tsv")
    original_parent_edges = []
    for parent in PARTITIONS:
        source = parent["source"]
        if not os.path.isfile(source):
            raise RuntimeError(f"partition parent is not a current C source: {source}")
        ccver, ccflags = CC_VER.get(source, DEFAULT_CC)
        original_parent_edges.append({"src": source, "ccver": ccver,
                                      "ccflags": ccflags, "asflags": AS_FLAGS.get(source, "")})
        for part in parent["parts"]:
            PARTITION_MODULE_DEPS.setdefault(part["module"], []).append(
                PARTITION_PATHS["parts"][parent["id"]][part["module"]])
    partition_support.validate_context(PARTITIONS, MODULES, original_parent_edges,
                                       "raw/slus", partition_aliases)
    outputs = sorted([*PARTITION_PATHS["remainders"].values(),
                      *(path for row in PARTITION_PATHS["parts"].values() for path in row.values())])
    original_sources = sorted(PARTITION_PATHS["remainders"])
    out.append("rule partition_render\n"
               "  command = python3 tools/slus_partitions.py render --plan config/slus_partitions.json "
               "--output-dir build/partition_sources --names config/names.tsv\n"
               "  description = PARTITION-RENDER $out\n"
               "  restat = 1\n\n")
    out.append("build " + " ".join(outputs) + ": partition_render " + " ".join(original_sources)
               + " | config/slus_partitions.json config/names.tsv tools/slus_partitions.py\n")
    out.append("rule partition_coverage\n"
               "  command = python3 tools/slus_partitions.py check-emitted "
               "--plan config/slus_partitions.json --manifest config/slus_modules.json "
               "--names config/names.tsv --stamp $out\n"
               "  description = PARTITION-COVERAGE $out\n\n")

# C translation units — recompile if the .c OR any INCLUDE_ASM'd nonmatching asm changes
nonmatch = " ".join(sorted(glob.glob("asm/nonmatchings/**/*.s", recursive=True)))
CC_VER.update({
    "src/w_8003D92C.c": ("2.7.2-cdk", ""),
    "src/w_8003FAD4.c": ("2.7.2-cdk", ""),
    "src/w_80041588.c": ("2.7.2-cdk", ""),
    "src/w_80041AB0.c": ("2.7.2-cdk", ""),
    "src/w_80043CD0.c": ("2.7.2-cdk", ""),
    "src/w_8004AB7C.c": ("2.7.2-cdk", ""),
    "src/w_8004450C.c": ("2.7.2-cdk", ""),
    "src/w_8004DCEC.c": ("2.7.2-cdk", ""),
})
CC_VER.update({
    "src/w_8003E34C.c": ("2.7.2-cdk", "-G32"),
    "src/w_8003E4FC.c": ("2.7.2-cdk", "-G32"),
    "src/w_8003E758.c": ("2.7.2-cdk", "-G32"),
    "src/w_8003F2A4.c": ("2.7.2-cdk", "-G32"),
    "src/w_8003F368.c": ("2.7.2-cdk", "-G32"),
    "src/w_8003F5AC.c": ("2.7.2-cdk", "-G32"),
    "src/w_8003F624.c": ("2.7.2-cdk", "-G32"),
})
cfiles = sorted(glob.glob("src/*.c"))
module_by_source = {}
member_sources = set()
carve_plans = []
data_piece_stamps = []
if MODULES:
    for module in MODULES:
        source = module["source"]
        if source not in cfiles:
            raise RuntimeError(f"module aggregator is not a current C source: {source}")
        for header in module["headers"]:
            if not os.path.isfile(header):
                raise RuntimeError(f"module header does not exist: {header}")
        if source in CC_VER and CC_VER[source] != (module["recipe"]["ccver"], module["recipe"]["ccflags"]):
            raise RuntimeError(f"module aggregator recipe conflicts with CC_VER: {source}")
        if source in AS_FLAGS and AS_FLAGS[source] != module["recipe"]["asflags"]:
            raise RuntimeError(f"module aggregator assembler flags conflict with AS_FLAGS: {source}")
        for member in module["members"]:
            member_source = member["source"]
            if member_source not in cfiles:
                raise RuntimeError(f"module member is not a current C source: {member_source}")
            ver, flags = CC_VER.get(member_source, DEFAULT_CC)
            actual = {"ccver": ver, "ccflags": flags, "asflags": AS_FLAGS.get(member_source, "")}
            if actual != module["recipe"]:
                raise RuntimeError(f"module member recipe differs from current build: {member_source}: {actual}")
            member_sources.add(member_source)
        module_by_source[source] = module
    carve_plans = module_support.plan_asset_carves(MODULES, out_dir=f"{BUILDDIR}/module_assets")
for cfile in cfiles:
    if cfile in member_sources:
        continue
    o = f"{BUILDDIR}/" + cfile[:-2] + ".o"
    module = module_by_source.get(cfile)
    if module:
        ver, flags = module["recipe"]["ccver"], module["recipe"]["ccflags"]
        asflags = module["recipe"]["asflags"]
    else:
        ver, flags = CC_VER.get(cfile, DEFAULT_CC)
        asflags = AS_FLAGS.get(cfile, "")
    if NM:
        flags = (flags + " -DNON_MATCHING").strip()
    deps = (" ".join([*(m["source"] for m in module["members"]), *module["headers"], MODULE_MANIFEST,
                      *PARTITION_MODULE_DEPS.get(module["name"], [])])
            if module else "")
    piece_module = DATA_PIECE_MODULES.get(cfile)
    if piece_module:
        deps += " tools/slus_data_pieces.py tools/slus_modules.py"
    source_input = PARTITION_PATHS["remainders"].get(cfile, cfile)
    out.append(f"build {o}: cc {source_input} | tools/cc.sh tools/ccproc.py {nonmatch}"
               + (f" {deps}" if deps else "")
               + f"\n  ccver = {ver}\n  ccflags = {flags}\n  asflags = {asflags}\n"
               + (f"  data_piece_step =  && python3 tools/slus_data_pieces.py"
                  f" --manifest {MODULE_MANIFEST} --module {piece_module['name']} --object {o}\n"
                  if piece_module else ""))
    if piece_module:
        sidecars = [o[:-2] + ".unsplit.o", o[:-2] + ".data-pieces.json"]
        stamp = o[:-2] + ".data-pieces.ok"
        for sidecar in sidecars:
            # The compiler edge creates these as side effects. An inputless phony
            # makes a missing sidecar dirty even after the verification stamp exists.
            out.append(f"build {sidecar}: phony\n")
        out.append(f"build {stamp}: data_piece_verify {o} | {' '.join(sidecars)}"
                   f" tools/slus_data_pieces.py tools/slus_modules.py {MODULE_MANIFEST}\n"
                   f"  module_name = {piece_module['name']}\n")
        data_piece_stamps.append(stamp)
    objs.append(o)
# split asm (psyq libs, data) — everything except the .included nonmatchings
for s in sorted(glob.glob("asm/**/*.s", recursive=True)):
    if s.startswith("asm/nonmatchings/"):
        continue
    o = f"{BUILDDIR}/" + s[:-2] + ".o"
    out.append(f"build {o}: as {s} | tools/as.sh tools/asproc.py\n")
    objs.append(o)
# raw bin assets
carved_assets = {plan["asset"]: plan for plan in carve_plans}
chunk_slots = [slot for plan in carve_plans for slot in plan["slots"] if slot["kind"] == "chunk"]
if chunk_slots:
    chunk_inputs = " ".join(slot["input"] for slot in chunk_slots)
    source_assets = " ".join(plan["asset"] for plan in carve_plans)
    out.append(f"build {chunk_inputs}: module_assets {source_assets} | tools/slus_modules.py {MODULE_MANIFEST}\n")
for b in sorted(glob.glob("assets/**/*.bin", recursive=True)):
    if b in carved_assets:
        for slot in carved_assets[b]["slots"]:
            if slot["kind"] == "chunk":
                out.append(f"build {slot['object']}: objbin {slot['input']}\n")
                objs.append(slot["object"])
        continue
    o = f"{BUILDDIR}/" + b[:-4] + ".o"
    out.append(f"build {o}: objbin {b}\n")
    objs.append(o)

out.append(f"build {BUILDDIR}/{BASE}_ordered.ld: orderld {LD}"
           + (f" | tools/slus_modules.py {MODULE_MANIFEST}"
              + "".join(f" {plan['asset']}" for plan in carve_plans) if MODULES else "") + "\n")
if MODULES:
    out.append(f"build {MODULE_SYMS}: module_syms {US} | tools/slus_modules.py {MODULE_MANIFEST}\n")
if PARTITIONS:
    physical_sources = {parent["source"] for parent in PARTITIONS}
    module_by_name = {module["name"]: module for module in MODULES}
    physical_sources.update(module_by_name[part["module"]]["source"]
                            for parent in PARTITIONS for part in parent["parts"])
    coverage_objects = sorted(f"{BUILDDIR}/" + source[:-2] + ".o"
                              for source in physical_sources)
    out.append(f"build {PARTITION_COVERAGE_STAMP}: partition_coverage " + " ".join(coverage_objects)
               + f" | tools/slus_partitions.py tools/slus_modules.py {PARTITION_PLAN_FILE} {MODULE_MANIFEST} config/names.tsv\n")
out.append(f"build {BUILDDIR}/{BASE}.elf: link " + " ".join(objs)
           + f" | {BUILDDIR}/{BASE}_ordered.ld " + " ".join(LDSCRIPTS)
           + (f" {PARTITION_COVERAGE_STAMP}" if PARTITIONS else "")
           + (" " + " ".join(data_piece_stamps) if data_piece_stamps else "") + "\n")
out.append(f"build {BUILDDIR}/{BASE}: objcopy {BUILDDIR}/{BASE}.elf\n")
if NM:
    # No sha1 gate: NON_MATCHING output is intentionally not byte-identical to retail.
    out.append(f"default {BUILDDIR}/{BASE}\n")
else:
    out.append(f"build build/{BASE}.ok: sha1 config/{BASE}.sha1 | build/{BASE}\n")
    out.append(f"default build/{BASE}.ok\n")

with open(OUTFILE, "w") as f:
    f.write("\n".join(out))
print(f"wrote {OUTFILE} ({len(objs)} objects)")
