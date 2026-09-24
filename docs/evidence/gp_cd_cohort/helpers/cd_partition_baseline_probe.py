#!/usr/bin/env python3
"""Fresh diagnostic baseline for seven unchanged CD whole sources.

Use only their registered compiler recipes. Keep stock, private generic, and
genuine ASPSX 2.79 -q results separate; an assembler error or unresolved
relocation is evidence, not an inferred code mismatch.
"""

from __future__ import annotations

import ast
from difflib import SequenceMatcher
import hashlib
import json
import os
from pathlib import Path
import struct
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
PY = Path("<reference-repo>/.venv/bin/python")
GENERIC = ROOT / "work/native_lane/selfinc_local_guard/candidate/maspsx.py"
ALIGN_SOURCE = ROOT / "tools/gate/match.py"
ALIGN_CALLER = ROOT / "tools/gate/aligned_score.py"
STEMS = ("w_8003E34C", "w_8003E4FC", "w_8003E758", "w_8003F2A4",
         "w_8003F368", "w_8003F5AC", "w_8003F624")
sys.path[:0] = [str(ROOT / "tools"), str(ROOT / "tools/fidelity"),
                str(ROOT / "tools/build")]

from common import rows  # noqa: E402
from fidelity import aspsx_diff as A  # noqa: E402
from fidelity.objread import read_elf  # noqa: E402
import verify  # noqa: E402


def digest(path: Path) -> str:
    return hashlib.sha256(path.read_bytes()).hexdigest()


def sanitize(text: str) -> str:
    return text.replace(str(ROOT), "<repo>").replace("<reference-repo>", "<toolchain>")


def registry() -> dict[str, dict]:
    wanted = {f"src/{stem}.c" for stem in STEMS}
    matches = [json.loads(line) for line in
               (ROOT / "ledger/splits/slus.jsonl").read_text().splitlines() if line]
    selected = {edge["src"]: edge for edge in matches if edge["src"] in wanted}
    if set(selected) != wanted or len(matches) != 884:
        raise RuntimeError("seven current logical recipes are not registered")
    return selected


def linked_extents() -> dict[str, dict]:
    output = subprocess.check_output(
        ["mipsel-linux-gnu-nm", "-S", "--defined-only",
         str(ROOT / "build_slus/build/slus_006.14.elf")], text=True)
    result = {}
    for line in output.splitlines():
        fields = line.split()
        if len(fields) == 4 and fields[2].upper() == "T" and fields[3].startswith("func_"):
            result[fields[3]] = {"address": int(fields[0], 16),
                                 "bytes": int(fields[1], 16)}
    return result


def tokens(view: A.View, func: str) -> list:
    return view.tokens(func) if func in view.funcs else []


def term(token) -> dict:
    return {"word": f"{token[0]:08x}", "relocation": token[1], "target": token[2]}


def compare(left: A.View, right: A.View, scope: list[str]) -> dict:
    if not set(scope) <= set(left.funcs):
        return {"error": "left view lacks declared emitted function", "missing_left": sorted(set(scope)-set(left.funcs))}
    summary = A.compare_units(left, right, scope)
    return {
        "exact": summary["exact"], "pair_token_diff_diagnostic": summary["diff"],
        "left_words": summary["len_m"], "right_words": summary["len_g"],
        "missing_right": summary["missing"], "delay_only": summary["delay_only"],
        "classes": A.classify(summary["regions"], left, summary["delay_only"]),
        "regions": [{"function": func, "op": op, "left_index": index,
                     "left_length": len(a), "right_length": len(b),
                     "left": [term(t) for t in a[:8]],
                     "right": [term(t) for t in b[:8]]}
                    for func, op, a, b, index in summary["regions"]],
    }


def target_words(extent: dict, image: bytes, load: int) -> list[int]:
    if extent["bytes"] % 4:
        raise RuntimeError("linked function has a non-word extent")
    offset = extent["address"] - load + 0x800
    return [struct.unpack_from("<I", image, offset + 4 * i)[0]
            for i in range(extent["bytes"] // 4)]


def words_blob(words: list[int]) -> bytes:
    return b"".join(struct.pack("<I", word) for word in words)


def canonical_alignment():
    """Load the exact canonical helpers without running the relocated CLI initializer."""
    source = ALIGN_SOURCE.read_text()
    tree = ast.parse(source, filename=str(ALIGN_SOURCE))
    names = ("_normalized_words", "aligned_word_stats")
    nodes = [node for node in tree.body if isinstance(node, ast.FunctionDef) and node.name in names]
    if [node.name for node in nodes] != list(names):
        raise RuntimeError("canonical aligned-score helper definitions changed")
    module = ast.Module(body=nodes, type_ignores=[])
    scope = {"SequenceMatcher": SequenceMatcher}
    exec(compile(module, str(ALIGN_SOURCE), "exec"), scope)
    proof = {"implementation": "tools/gate/match.py:aligned_word_stats",
             "caller": "tools/gate/aligned_score.py:aligned_stats",
             "source_sha256": hashlib.sha256(source.encode()).hexdigest(),
             "caller_sha256": digest(ALIGN_CALLER),
             "selected_ast_sha256": hashlib.sha256(ast.dump(module).encode()).hexdigest()}
    return scope["aligned_word_stats"], proof


def retail_detail(view: A.View, func: str, extent: dict,
                  output: Path, leg: str, aligned_score) -> dict:
    addrs, gp, image, load = A.slus_image()
    if func not in view.funcs:
        return {"present": False, "retail_words": extent["bytes"] // 4}
    if addrs.get(func) != extent["address"]:
        raise RuntimeError("retail symbol address disagrees with nm extent: " + func)
    actual, masks = A.resolve_tokens(view, func, extent["address"], addrs.get, gp)
    target = target_words(extent, image, load)
    (output / f"{leg}_{func}_resolved.bin").write_bytes(words_blob(actual))
    (output / f"{func}_retail.bin").write_bytes(words_blob(target))
    result = {"present": True, "address": f"0x{extent['address']:08x}",
              "actual_words": len(actual), "retail_words": len(target),
              "length_equal": len(actual) == len(target),
              "masked_indices": masks,
              "masked_relocations": [{"index": i, **term(view.tokens(func)[i])} for i in masks],
              "exact_unmasked": len(actual) == len(target) and not masks and actual == target}
    if len(actual) == len(target):
        sites = [{"index": i, "address": f"0x{extent['address'] + 4*i:08x}",
                  "actual": f"{got:08x}", "retail": f"{want:08x}"}
                 for i, (got, want) in enumerate(zip(actual, target)) if got != want]
        result["unmasked_mismatch_sites"] = [site for site in sites
                                             if site["index"] not in masks]
        result["masked_disagreement_sites"] = [site for site in sites
                                              if site["index"] in masks]
    elif not masks:
        subs, indels = aligned_score(words_blob(actual), words_blob(target),
                                    mask_relocations=True)
        regions = []
        for op, a0, a1, b0, b1 in SequenceMatcher(
                None, actual, target, autojunk=False).get_opcodes():
            if op != "equal":
                regions.append({"op": op, "actual_index": a0, "retail_index": b0,
                                "actual_length": a1-a0, "retail_length": b1-b0,
                                "actual": [f"{w:08x}" for w in actual[a0:min(a1,a0+8)]],
                                "retail": [f"{w:08x}" for w in target[b0:min(b1,b0+8)]]})
        result["aligned_lcs"] = {"substitutions": subs, "indels": indels,
                                 "total": subs + indels,
                                 "jump_targets_normalized": True,
                                 "regions": regions}
    else:
        result["aligned_lcs"] = {"status": "withheld: unresolved relocations"}
    return result


def gp_externs(view: A.View, scope: list[str]) -> list[dict]:
    result = []
    for func in scope:
        for i, token in enumerate(view.tokens(func)):
            if token[1] != "GPREL16" or not token[2]:
                continue
            key = token[2]
            if key[0] == "addr" or (key[0] == "sym" and key[1] not in view.obj.symbols):
                result.append({"function": func, "index": i, "target": key})
    return result


def snapshot(sources: dict[str, Path], recipes: dict[str, dict]) -> dict:
    fixed = [ROOT / "ledger/splits/slus.jsonl", ROOT / "ledger/splits/slus.build.ninja",
             ROOT / "config/slus_modules.json", ROOT / "config/slus_partitions.json",
             ROOT / "build_slus/build/slus_006.14", ROOT / "baserom/slus_006.14"]
    files = {str(path.relative_to(ROOT)): digest(path) for path in fixed}
    for stem, source in sources.items():
        files[str(source.relative_to(ROOT))] = digest(source)
        obj = ROOT / "build_slus" / recipes[f"src/{stem}.c"]["out"]
        files[str(obj.relative_to(ROOT))] = digest(obj)
    return files


def run_probe() -> dict:
    HERE.mkdir(parents=True, exist_ok=True)
    A.TMP = HERE / "aspsx_tmp"
    A.TMP.mkdir(exist_ok=True)
    A.SLUS_ELF = ROOT / "build_slus/build/slus_006.14.elf"
    A.SLUS_BIN = ROOT / "baserom/slus_006.14"
    A._SLUS = None
    verify.VENV_PY = PY
    aligned_score, alignment_proof = canonical_alignment()
    recipes = registry()
    extents = linked_extents()
    row_map = {row["id"]: row for row in rows()}
    sources = {stem: ROOT / "src/slus" / f"{stem}.c" for stem in STEMS}
    before = snapshot(sources, recipes)
    if (ROOT / "build_slus/build/slus_006.14").read_bytes() != A.SLUS_BIN.read_bytes():
        raise RuntimeError("active whole image is not retail exact")
    receipt = {"schema": 1, "purpose": "unchanged CD whole-source direct diagnostic",
               "recipe_scope": "registered recipes only; stock, private generic, genuine 2.79 -q",
               "generic_cli_sha256": digest(GENERIC),
               "generic_package_sha256": digest(GENERIC.parent / "maspsx/__init__.py"),
               "aligned_score_provenance": alignment_proof,
               "production_before": before, "rows": []}
    env = dict(os.environ)
    env.pop("AZURE_MASPSX", None)
    env.pop("AZURE_MASPSX_COMPANION", None)
    for stem in STEMS:
        edge = recipes[f"src/{stem}.c"]
        row = row_map[f"slus/{stem}"]
        if row["cell"] != edge["ccver"] or row["flags"] != edge["ccflags"] or (row.get("row_asflags") or "") != edge["asflags"]:
            raise RuntimeError("cached row differs from current registered recipe: " + stem)
        source = sources[stem]
        output = HERE / "raw" / stem
        output.mkdir(parents=True, exist_ok=True)
        record = {"row": row["id"], "registered_recipe": edge,
                  "source_sha256": digest(source),
                  "pinned_object_sha256": digest(ROOT / "build_slus" / edge["out"]),
                  "raw_artifacts": str(output.relative_to(HERE))}
        receipt["rows"].append(record)
        compile_row = {"cell": edge["ccver"], "flags": edge["ccflags"],
                       "row_asflags": edge["asflags"]}
        stock_obj, error = verify._compile_slus_source(
            compile_row, source, output, ROOT / "include")
        if error:
            record["stock_error"] = sanitize(error)
            continue
        record["stock_object_sha256"] = digest(stock_obj)
        stock = A.View(read_elf(stock_obj.read_bytes()))
        pinned = A.View(read_elf((ROOT / "build_slus" / edge["out"]).read_bytes()))
        scope = sorted(stock.funcs)
        record["raw_function_sets"] = {"stock": scope, "pinned": sorted(pinned.funcs)}
        record["pinned_comparison"] = compare(stock, pinned, scope)
        record["stock_gp_extern_relocations"] = gp_externs(stock, scope)
        for func in scope:
            if func not in extents:
                raise RuntimeError("linked retail function extent missing: " + func)
        record["retail_lengths"] = {func: extents[func]["bytes"] // 4 for func in scope}
        record["stock_retail"] = {func: retail_detail(stock, func, extents[func], output, "stock", aligned_score)
                                  for func in scope}
        asm = verify.postprocess_slus((output / "a.s").read_text(), names_only=True)
        (output / "genuine_input.s").write_text(asm)
        generic_obj = output / "generic.o"
        command = [str(PY), str(GENERIC), "--aspsx-version=2.79", "--dont-force-G0",
                   "--run-assembler", "--gnu-as-path=mipsel-linux-gnu-as",
                   f"-I{ROOT / 'raw'}", f"-I{ROOT / 'include'}", "-EL", "-march=r3000",
                   "-G8", *edge["asflags"].split(), "-o", str(generic_obj)]
        generic_run = subprocess.run(command, input=(output / "a.proc.s").read_text(),
                                     text=True, capture_output=True, cwd=ROOT, env=env)
        (output / "generic.log").write_text(sanitize(generic_run.stdout + generic_run.stderr))
        if generic_run.returncode or not generic_obj.is_file():
            record["generic_error"] = {"exit_code": generic_run.returncode,
                                       "log": "generic.log"}
        else:
            generic = A.View(read_elf(generic_obj.read_bytes()))
            record["generic_object_sha256"] = digest(generic_obj)
            record["raw_function_sets"]["generic"] = sorted(generic.funcs)
            record["stock_generic"] = compare(stock, generic, scope)
            record["generic_retail"] = {func: retail_detail(generic, func, extents[func], output, "generic", aligned_score)
                                        for func in scope}
        input_bytes = A.aspsx_input(asm)
        (output / "genuine_input_bytes.s").write_bytes(input_bytes)
        lnk, genuine_error = A.run_aspsx(input_bytes, "2.79", ["-q"], output)
        if genuine_error:
            record["genuine"] = {"status": "assembler_error", "mode": ["-q"],
                                 "error": sanitize(genuine_error),
                                 "stock_has_gp_extern_relocations": bool(record["stock_gp_extern_relocations"]),
                                 "interpretation": "no code comparison possible"}
        else:
            lnk_path = output / "genuine_q.lnk"
            lnk_path.write_bytes(lnk)
            reference = generic if "generic" in record["raw_function_sets"] else stock
            genuine = A.View(A.read_lnk(lnk), reference, A.aliases(asm))
            raw = sorted(genuine.funcs)
            missing_raw = sorted(set(scope) - set(raw))
            for func in scope:
                genuine.add_unit(func, reference)
            comparison = compare(reference, genuine, scope)
            gre = {func: retail_detail(genuine, func, extents[func], output, "genuine", aligned_score)
                   for func in scope}
            unresolved = any(detail.get("masked_indices") for detail in gre.values())
            stock_generic = record.get("stock_generic", {})
            gp_model = stock_generic.get("classes", {}).get("gp-extern", 0) > 0
            if unresolved:
                interpretation = "unresolved relocation masks; code verdict withheld at masked sites"
            elif comparison.get("exact") and gp_model:
                interpretation = ("genuine matches private generic; stock-to-generic has extern-GP "
                                  "regions; other aligned regions remain unassigned")
            elif comparison.get("exact") and all(d["exact_unmasked"] for d in gre.values()):
                interpretation = "unmasked exact at this registered recipe"
            elif gp_model:
                interpretation = "extern-GP difference present; genuine-only regions remain separately classified"
            else:
                interpretation = "unmasked code or emission difference"
            record["genuine"] = {
                "status": "assembled", "mode": ["-q"], "lnk_sha256": digest(lnk_path),
                "raw_functions": raw, "raw_missing": missing_raw,
                "comparison_reference": "generic" if reference is not stock else "stock",
                "reference_comparison": comparison, "retail": gre,
                "stock_generic_gp_extern_regions": stock_generic.get("classes", {}).get("gp-extern", 0),
                "stock_generic_other_classes": {name: count for name, count in
                                                   stock_generic.get("classes", {}).items()
                                                   if name != "gp-extern"},
                "interpretation": interpretation,
            }
        (HERE / "baseline_receipt.json").write_text(
            json.dumps(receipt, indent=2).replace(str(ROOT), "<repo>") + "\n")
        print(stem, "stock", len(scope), "generic", record.get("raw_function_sets", {}).get("generic"),
              "genuine", record.get("genuine", {}).get("status"), flush=True)
    after = snapshot(sources, recipes)
    receipt["production_after"] = after
    receipt["production_unchanged"] = before == after
    if not receipt["production_unchanged"]:
        raise RuntimeError("production inputs changed during private CD measurement")
    (HERE / "baseline_receipt.json").write_text(
        json.dumps(receipt, indent=2).replace(str(ROOT), "<repo>") + "\n")
    return receipt


if __name__ == "__main__":
    report = run_probe()
    print(json.dumps({"rows": len(report["rows"]),
                      "genuine_assembled": sum(r.get("genuine", {}).get("status") == "assembled"
                                               for r in report["rows"]),
                      "production_unchanged": report["production_unchanged"]}, indent=2))
