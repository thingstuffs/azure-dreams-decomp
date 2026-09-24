#!/usr/bin/env python3
"""Private end-to-end proof of the optional SLUS module build path.

All generated inputs and build roots stay under work/native_lane/slus_module_build/.
No production manifest, source, ledger, or pinned build output is modified.
"""

from __future__ import annotations

import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
HERE = ROOT / "work/native_lane/slus_module_build"
STAGE = HERE / "stage"
SCORER = HERE / "scorer_view"
SOURCE = ROOT / "docs/evidence/gp_data_module_pilot"
STEMS = ("konami_runtime_w_8003C634", "konami_runtime_w_8003C758",
         "konami_runtime_w_8003C920")
FUNCTIONS = ("func_8003C634", "func_8003C758", "func_8003C920")

sys.path.insert(0, str(ROOT / "tools/fidelity"))
sys.path.insert(0, str(ROOT / "tools/build"))
from slus_iso import SlusView  # noqa: E402
from slus_modules import load_manifest, logical_edges  # noqa: E402


def command(args, *, cwd=STAGE, env=None):
    result = subprocess.run(args, cwd=cwd, env=env, text=True, capture_output=True)
    if result.returncode:
        raise RuntimeError(f"{' '.join(map(str, args))} exited {result.returncode}:\n"
                           + (result.stdout + result.stderr)[-3000:])
    return result.stdout + result.stderr


def replace_private(path, value):
    """Replace a staged symlink before writing so production targets stay untouched."""
    path.parent.mkdir(parents=True, exist_ok=True)
    if path.is_symlink() or path.exists():
        path.unlink()
    path.write_text(value)


def recipe_edges(ninja):
    pattern = re.compile(r"^build (build/src/[^\s:]+\.o): cc (src/[^\s]+\.c) \|[^\n]*\n"
                         r"  ccver = ([^\n]*)\n  ccflags = ([^\n]*)\n  asflags = ([^\n]*)", re.M)
    return sorted(({"out": m[1], "src": m[2], "ccver": m[3], "ccflags": m[4], "asflags": m[5]}
                   for m in pattern.finditer(ninja)), key=lambda edge: edge["src"])


def defined_symbols(elf):
    output = command(("mipsel-linux-gnu-nm", "-S", "--defined-only", str(elf)))
    names = set(FUNCTIONS) | {"D_80080A6C"}
    symbols = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) == 4 and fields[3] in names:
            symbols[fields[3]] = {"address": int(fields[0], 16), "size": int(fields[1], 16),
                                  "nm_type": fields[2]}
    return symbols


def stage_sources():
    combined = (SOURCE / "gp_data_module.c").read_text()
    markers = ("/* Return the index", "/* Returns the key's index", "/* Initializes runtime state")
    starts = [combined.index(marker) for marker in markers]
    assert starts == sorted(starts)
    bodies = (combined[starts[0]:starts[1]], combined[starts[1]:starts[2]], combined[starts[2]:])
    header = (SOURCE / "gp_data_module.h").read_text()

    # SlusView makes src/ a directory of symlinks. include/ remains a directory
    # symlink to production, so detach the entire small tree before adding a header.
    include = STAGE / "include"
    if include.is_symlink():
        original = Path(os.path.realpath(include))
        include.unlink()
        shutil.copytree(original, include, symlinks=True)
    if (STAGE / "config").is_symlink():
        config = STAGE / "config"
        original = Path(os.path.realpath(config))
        config.unlink()
        shutil.copytree(original, config, symlinks=True)
    assert not (STAGE / "src").is_symlink()
    assert not (STAGE / "include").is_symlink()
    assert not (STAGE / "config").is_symlink()
    replace_private(include / "slus/runtime_directory.h", header)
    for stem, body in zip(STEMS, bodies):
        replace_private(STAGE / "src" / f"{stem}.c", '#include "slus/runtime_directory.h"\n\n' + body)
    aggregator = ('#include "slus/runtime_directory.h"\n\n'
                  '/* PS-X EXE payload at VMA 0x80080A6C: 04 00 00 00. */\n'
                  's32 D_80080A6C = 4;\n\n'
                  + "".join(f'#include "{stem}.c"\n' for stem in STEMS))
    replace_private(STAGE / "src/konami_runtime_directory.c", aggregator)

    manifest_path = STAGE / "config/slus_modules.json"
    manifest = json.loads(manifest_path.read_text())
    runtime_indices = [i for i, module in enumerate(manifest["modules"])
                       if module["name"] == "runtime_directory"]
    assert len(runtime_indices) == 1, runtime_indices
    runtime = {
        "name": "runtime_directory", "source": "src/konami_runtime_directory.c",
        "members": [{"id": f"slus/{stem}", "source": f"src/{stem}.c", "functions": [function]}
                    for stem, function in zip(STEMS, FUNCTIONS)],
        "headers": ["include/common.h", "include/slus/runtime_directory.h"],
        "recipe": {"ccver": "2.7.2-cdk", "ccflags": "", "asflags": ""},
        "data": [{"symbol": "D_80080A6C", "asset": "assets/54240.bin", "offset": 44,
                  "size": 4, "vram": 0x80080A6C, "bytes": "04000000", "section": ".sdata"}],
        "evidence": "docs/evidence/fidelity_gp_repair_progress.md",
    }
    manifest["modules"][runtime_indices[0]] = runtime
    replace_private(manifest_path, json.dumps(manifest, indent=2) + "\n")
    samples = HERE / "sources"
    samples.mkdir(exist_ok=True)
    for file in [STAGE / "src/konami_runtime_directory.c",
                 *(STAGE / "src" / f"{stem}.c" for stem in STEMS),
                 STAGE / "include/slus/runtime_directory.h", STAGE / "config/slus_modules.json"]:
        (samples / file.name).write_bytes(file.read_bytes())


def dependency_dry_run(relative):
    path = STAGE / relative
    stat = path.stat()
    future = max(time.time_ns(), (STAGE / "build/slus_006.14").stat().st_mtime_ns) + 2_000_000_000
    try:
        os.utime(path, ns=(stat.st_atime_ns, future))
        return command(("ninja", "-n", "-j", "4", "build/slus_006.14"))
    finally:
        os.utime(path, ns=(stat.st_atime_ns, stat.st_mtime_ns))


def genuine_comparison():
    """Compare the staged module's three functions with genuine ASPSX 2.79."""
    import verify
    import aspsx_diff as A
    from slus_module_context import compilation_source

    dest = HERE / "context_genuine"
    if dest.exists():
        shutil.rmtree(dest)  # private probe output, regenerated from the staged tree
    project = dest / "project"
    (project / "src").mkdir(parents=True)
    (project / "src/slus").symlink_to(STAGE / "src", target_is_directory=True)
    (project / "include").symlink_to(STAGE / "include", target_is_directory=True)
    (project / "config").symlink_to(STAGE / "config", target_is_directory=True)
    (dest / "tmp").mkdir()
    A.TMP = dest / "tmp"
    A.SLUS_ELF = STAGE / "build/slus_006.14.elf"
    A._SLUS = None

    row = next(json.loads(line) for line in (ROOT / "ledger/rows.jsonl").open()
               if '"id":"slus/konami_runtime_w_8003C634"' in line)
    source = project / "src/slus" / f"{STEMS[0]}.c"
    # compile_slus wraps the member exactly once, using this private project.
    # Passing an already-wrapped aggregate would wrap it again once the live
    # tree also declares the module, creating a self-include.
    from unittest.mock import patch
    def staged_source(row, candidate, outdir):
        return compilation_source(row, candidate, outdir, root=project)
    with patch("slus_module_context.compilation_source", side_effect=staged_source):
        compiled, error = verify.compile_slus(row, source, dest, include_root=STAGE / "include")
    assert compiled is not None, error
    maspsx = A.View(A.read_elf(compiled.read_bytes()))
    assembly = verify.postprocess_slus((dest / "a.s").read_text(), names_only=True)
    lnk, error = A.run_aspsx(A.aspsx_input(assembly), "2.79", ["-q", "-0"], dest)
    assert lnk is not None, error
    (dest / "genuine.lnk").write_bytes(lnk)
    genuine = A.View(A.read_lnk(lnk), maspsx)
    compared = A.compare_units(maspsx, genuine, FUNCTIONS)
    retail = A.retail_compare(genuine, FUNCTIONS, "slus")
    words = {function: len(maspsx.tokens(function)) for function in FUNCTIONS}
    result = {"version": "2.79", "flags": ["-q", "-0"],
              "exact": compared["exact"], "diff": compared["diff"],
              "retail": retail, "word_counts": words,
              "pipeline": "compilation_source -> compile_slus -> names-only postprocess -> genuine ASPSX"}
    assert result["exact"] and result["diff"] == 0
    assert retail == {"diff": 0, "masked": 0, "checked": 3}
    assert words == dict(zip(FUNCTIONS, (18, 32, 54)))
    (dest / "receipt.json").write_text(json.dumps(result, indent=2) + "\n")
    return result


def main():
    HERE.mkdir(parents=True, exist_ok=True)
    for dest in (STAGE, SCORER):
        if dest.exists():
            shutil.rmtree(dest)  # exact private paths owned by this probe
    initial = SlusView(STAGE)
    calibration = initial.calibrate()
    assert calibration["result"] == "MATCH", calibration
    pristine = defined_symbols(STAGE / "build/slus_006.14.elf")
    stage_sources()
    modules = load_manifest(STAGE / "config/slus_modules.json")
    production_modules = load_manifest(ROOT / "config/slus_modules.json")
    assert [m["name"] for m in modules] == [m["name"] for m in production_modules]
    for staged, production in zip(modules, production_modules):
        if staged["name"] == "runtime_directory":
            continue
        assert staged == production, staged["name"]
        for source in [staged["source"], *(m["source"] for m in staged["members"])]:
            assert (STAGE / source).read_bytes() == (ROOT / "src/slus" / Path(source).name).read_bytes(), source
        for header in staged["headers"]:
            assert (STAGE / header).read_bytes() == (ROOT / header).read_bytes(), header

    # Use the current configure and stock Ninja rules, without an assembler
    # companion override; unrelated TUs and the module compile at the stock recipe.
    env = dict(os.environ)
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    configure_out = command(("python3", "tools/configure.py"), env=env)
    stock_edges = [json.loads(line) for line in (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line.strip()]
    physical = recipe_edges((STAGE / "build.ninja").read_text())
    logical = logical_edges(physical, modules)
    ledger_rows = [json.loads(line) for line in (ROOT / "ledger/rows.jsonl").read_text().splitlines() if line.strip()]
    ledger_ids = {row["id"] for row in ledger_rows if row["kind"] == "slus"}
    assert len(logical) == len(stock_edges)
    assert len(physical) == len(stock_edges) - sum(len(m["members"]) - 1 for m in modules)
    assert logical == stock_edges
    assert {"slus/" + Path(edge["src"]).stem for edge in logical} == ledger_ids

    build_out = command(("ninja", "-j", "4", "build/slus_006.14"), env=env)
    image = (STAGE / "build/slus_006.14").read_bytes()
    retail = (ROOT / "baserom/slus_006.14").read_bytes()
    linked = defined_symbols(STAGE / "build/slus_006.14.elf")
    symbol_lines = [line.strip() for line in command(("mipsel-linux-gnu-readelf", "-Ws",
                    "build/slus_006.14.elf")).splitlines() if line.split()[-1:] == ["D_80080A6C"]]
    assert len(symbol_lines) == 1, symbol_lines
    fields = symbol_lines[0].split()
    obj_sections = command(("mipsel-linux-gnu-objdump", "-h", "build/src/konami_runtime_directory.o"))
    assert re.search(r"\s\.sdata\s+00000004\s", obj_sections), obj_sections[-1200:]
    assert image == retail
    assert fields[6] != "ABS" and int(fields[1], 16) == 0x80080A6C
    assert image[0x5426C:0x54270] == bytes.fromhex("04000000")
    assert all(pristine[f] == linked[f] for f in FUNCTIONS)

    rebuilds = {}
    for label, relative in (("source", f"src/{STEMS[0]}.c"),
                            ("header", "include/slus/runtime_directory.h"),
                            ("data", "assets/54240.bin"),
                            ("manifest", "config/slus_modules.json")):
        output = dependency_dry_run(relative)
        rebuilds[label] = {"cc": "CC src/konami_runtime_directory.c" in output,
                           "asset_chunks": "MODULE-ASSETS" in output,
                           "ordered_script": "LD-SCRIPT" in output,
                           "filtered_symbols": "MODULE-SYMS" in output,
                           "link": "LINK build/slus_006.14.elf" in output}
    assert rebuilds["source"]["cc"] and rebuilds["header"]["cc"]
    assert rebuilds["data"]["asset_chunks"] and rebuilds["data"]["ordered_script"]
    assert rebuilds["manifest"]["cc"] and rebuilds["manifest"]["filtered_symbols"]
    helper_query = command(("ninja", "-t", "query", "build/slus_006.14_ordered.ld"))
    assert "tools/slus_modules.py" in helper_query
    assert "no work to do" in command(("ninja", "-n", "build/slus_006.14"))

    scorer = SlusView(SCORER, source=STAGE)
    scorer_calibration = scorer.calibrate()
    assert scorer_calibration["result"] == "MATCH", scorer_calibration
    row_text = (STAGE / "src" / f"{STEMS[0]}.c").read_text()
    same = scorer.gate({STEMS[0]: (row_text, "2.7.2-cdk", "")})
    altered_text = row_text.replace("entry_index = 0;", "entry_index = 1;", 1)
    assert altered_text != row_text
    altered = scorer.gate({STEMS[0]: (altered_text, "2.7.2-cdk", "")})
    # A candidate can leave its own function unchanged while affecting a later
    # included sibling. A per-function-only score must not certify this edit.
    sibling_text = row_text + '\n#define func_8003C634 func_8003C7D8\n'
    sibling_regression = scorer.gate({STEMS[0]: (sibling_text, "2.7.2-cdk", "")})
    assert sibling_regression["result"] == "NO MATCH", sibling_regression
    assert sibling_regression["per_fn"][FUNCTIONS[0]] == 0, sibling_regression
    assert sibling_regression["per_fn"][FUNCTIONS[1]] > 0, sibling_regression
    conflict = scorer.gate({STEMS[0]: (None, "2.7.2-cdk", ""),
                            STEMS[1]: (None, "2.8.1", "")})
    partial_recipe = scorer.gate({STEMS[0]: (None, "2.8.1", "")})
    restored = scorer.calibrate()
    assert [r["result"] for r in (same, altered, conflict, partial_recipe, restored)] == [
        "MATCH", "NO MATCH", "ERROR", "ERROR", "MATCH"]
    genuine = genuine_comparison()

    receipt = {
        "calibration": calibration, "configure": configure_out.strip(),
        "ninja_tail": build_out.splitlines()[-8:],
        "edges": {"physical": len(physical), "logical": len(logical), "ledger_rows": len(ledger_ids),
                  "logical_equal_to_pinned_recipe": logical == stock_edges},
        "modules": {"active": len(modules), "other_inputs_preserved": len(modules) - 1},
        "image": {"match_retail": image == retail, "size": len(image),
                  "sha1": hashlib.sha1(image).hexdigest(), "retail_sha1": hashlib.sha1(retail).hexdigest()},
        "data": {"symbol": "D_80080A6C", "vma": fields[1], "section_index": fields[6],
                 "object_section": ".sdata", "bytes": image[0x5426C:0x54270].hex(),
                 "readelf": symbol_lines[0]},
        "functions": {f: {"pristine": pristine[f], "linked": linked[f]} for f in FUNCTIONS},
        "dependencies": rebuilds,
        "scorer": {"calibration": scorer_calibration, "same": same, "altered": altered,
                   "sibling_regression": sibling_regression,
                   "conflict": conflict, "partial_recipe": partial_recipe, "restored": restored},
        "genuine_aspsx": genuine,
    }
    (HERE / "receipt.json").write_text(json.dumps(receipt, indent=2) + "\n")
    print(json.dumps({"image": receipt["image"], "edges": receipt["edges"],
                      "scorer_results": {k: v["result"] for k, v in receipt["scorer"].items()},
                      "genuine_aspsx": genuine}, indent=2))


if __name__ == "__main__":
    main()
