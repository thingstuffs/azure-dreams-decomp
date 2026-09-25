"""Keep logical SLUS rows editable while compiling their declared module context.

Rows retain their original C paths and identities. A module is an ordinary C
translation unit that includes those row files in order and owns shared data.
This module never synthesizes symbol declarations or assembler exceptions.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path, PurePosixPath
import posixpath
import re
import sys

from common import ROOT

sys.path.insert(0, str(Path(__file__).resolve().parent / "build"))
from slus_modules import load_manifest, module_for_row  # noqa: E402
import slus_partitions as partitions  # noqa: E402


def modules(root=ROOT):
    return load_manifest(Path(root) / "config/slus_modules.json")


def module_anchor(module, root=ROOT):
    """Choose a real logical contributor for context; never invent a member row.

    This is a fingerprint/compilation entry point, not a placement grant.
    A partition-only destination must be reachable from an actual parent.
    """
    if module["members"]:
        return {"kind": "slus", "id": module["members"][0]["id"]}
    if module.get("partition_only") is not True:
        raise partitions.PartitionError("empty module lacks partition-only opt-in")
    plan = partitions.load_plan(Path(root) / "config/slus_partitions.json")
    parent = next((p for p in plan if any(part["module"] == module["name"]
                                        for part in p["parts"])), None)
    if parent is None:
        raise partitions.PartitionError("partition-only owner has no incoming functions: " + module["name"])
    row = {"kind": "slus", "id": parent["id"]}
    _, owners, _ = partition_context(row, root)
    if module not in owners:
        raise partitions.PartitionError("partition-only owner is absent from contributor context")
    return row


def partition_context(row, root=ROOT):
    """Return the validated connected parent/owner closure for a live row."""
    if row.get("kind") != "slus":
        return [], [], {}
    root = Path(root)
    plan = partitions.load_plan(root / "config/slus_partitions.json")
    if not plan:
        return [], [], {}
    all_modules = modules(root)
    parents, owners = partitions.connected_context(row["id"], plan, all_modules)
    if not parents:
        return [], [], {}
    aliases = partitions.read_aliases(root / "config/names.tsv")
    edges = [json.loads(line) for line in (root / "ledger/splits/slus.jsonl").read_text().splitlines() if line.strip()]
    partitions.validate_context(plan, all_modules, edges, root / "raw/slus", aliases)
    return parents, owners, aliases


def _require_singular(row, root):
    if partition_context(row, root)[0]:
        raise partitions.PartitionError(row["id"] + ": partition context requires plural compilation and verification")


def membership(row, root=ROOT):
    if row.get("kind") != "slus":
        return None
    _require_singular(row, root)
    return module_for_row(modules(root), row["id"])


def source_path(source, root=ROOT):
    """Manifest source paths are relative to the exported build's src/ directory."""
    return Path(root) / "src/slus" / Path(source).relative_to("src")


def input_paths(module, root=ROOT):
    return ([source_path(module["source"], root)]
            + [source_path(m["source"], root) for m in module["members"]]
            + [Path(root) / header for header in module["headers"]])


def _data_piece_code(owners):
    """Only opted-in owners depend on the binary transformation implementation."""
    if not any(owner.get("data_pieces") for owner in owners):
        return b""
    import slus_data_pieces
    return Path(slus_data_pieces.__file__).read_bytes()


def fingerprint(row, root=ROOT):
    parents, owners, aliases = partition_context(row, root)
    if parents:
        sources = {p["source"] for p in parents}
        sources.update(m["source"] for m in owners)
        sources.update(member["source"] for m in owners for member in m["members"])
        headers = {h for m in owners for h in m["headers"]}
        value = partitions.fingerprint(parents, owners,
            {s: source_path(s, root).read_text() for s in sources},
            {h: (Path(root) / h).read_text() for h in headers}, aliases)
        # Include the adapter itself: its include rewriting is part of the input.
        return hashlib.sha256(value.encode() + Path(__file__).read_bytes()
                              + _data_piece_code(owners)).hexdigest()
    module = membership(row, root)
    if module is None:
        return None
    h = hashlib.sha256(json.dumps(module, sort_keys=True).encode())
    for path in input_paths(module, root):
        h.update(str(path.relative_to(root)).encode())
        h.update(path.read_bytes())
    h.update(_data_piece_code([module]))
    return h.hexdigest()


def compilation_source(row, candidate, outdir, root=ROOT):
    """Use the real module, substituting the candidate for exactly one row include.

    Historical raw baselines continue to compile independently. Live candidates
    include all siblings and the module's actual data definition, so source edits
    cannot be scored against invented ownership context.
    """
    candidate = Path(candidate).resolve()
    if candidate == (Path(root) / "raw/slus" / Path(row["c_path"]).name).resolve():
        return candidate
    module = membership(row, root)
    if module is None:
        return candidate
    module_path = source_path(module["source"], root)
    text = module_path.read_text()
    member_by_source = {m["source"]: m for m in module["members"]}
    seen = []
    include = re.compile(r'^([ \t]*#include[ \t]+)"([^"\n]+\.c)"[ \t]*$', re.M)

    def replace(match):
        source = str(Path(module["source"]).parent / match.group(2))
        if source not in member_by_source:
            raise ValueError(f"{module['name']}: undeclared C include {source}")
        member = member_by_source[source]
        seen.append(member["id"])
        path = candidate if member["id"] == row["id"] else source_path(source, root)
        return match.group(1) + json.dumps(str(path.resolve()))

    text = include.sub(replace, text)
    if seen != [m["id"] for m in module["members"]]:
        raise ValueError(f"{module['name']}: C includes must match declared member order exactly")
    target = Path(outdir) / module_path.name
    target.write_text(text)
    return target


def physical_stem(stem, root=ROOT):
    _require_singular({"id": "slus/" + stem, "kind": "slus"}, root)
    module = module_for_row(modules(root), "slus/" + stem)
    return Path(module["source"]).stem if module else stem


def require_individual_recipe(row, root=ROOT):
    module = membership(row, root)
    if module:
        raise ValueError(f"{row['id']} belongs to {module['name']}; change the module recipe and verify all members together")


def _relative_headers(text, original):
    """Preserve quoted header lookup when a source view changes directory."""
    def replace(match):
        relative = original.parent / match.group(2)
        if relative.is_file():
            return match.group(1) + json.dumps(str(relative.resolve()))
        return match.group(0)
    return re.sub(r'(^[ \t]*#include[ \t]+)"([^"\n]+\.h)"', replace, text, flags=re.M)


def compilation_sources(row, candidate, outdir, root=ROOT):
    """Prepare all physical streams of a row, with explicit recipe and scopes.

    `functions` scopes the original row within each stream; `expected_functions`
    scopes the complete emitted TU including siblings. Neither is a byte proof.
    Source views are private outputs; canonical files are never overwritten.
    Raw historical sources keep their independent original compilation contract.
    """
    root = Path(root).resolve()
    candidate = Path(candidate).resolve()
    outdir = Path(outdir).resolve()
    raw = root / "raw/slus" / Path(row["c_path"]).name
    recipe = {"ccver": row.get("cell", row.get("cfg")),
              "ccflags": row.get("flags", ""), "asflags": row.get("row_asflags", "")}
    if candidate == raw.resolve():
        return [{"source": row["c_path"], "cfile": candidate, "recipe": recipe,
                 "functions": None, "expected_functions": None, "role": "raw"}]
    parents, owners, aliases = partition_context(row, root)
    if not parents:
        module = membership(row, root)
        outdir.mkdir(parents=True, exist_ok=True)
        cfile = compilation_source(row, candidate, outdir, root)
        if module:
            unit = partitions.row_units(row["id"], [], [module])[0]
            unit["expected_functions"] = sorted(partitions.expected_units([], [module])[module["source"]])
            return [dict(unit, cfile=cfile)]
        return [{"source": row["c_path"], "cfile": cfile, "recipe": recipe,
                 "functions": None, "expected_functions": None, "role": "standalone"}]

    # All generated paths are owned by this call. Refuse a caller accidentally
    # targeting the editable or frozen source trees.
    for protected in (root / "src", root / "raw", root / "include", root / "config", root / "ledger"):
        if outdir == protected or outdir.is_relative_to(protected):
            raise partitions.PartitionError("partition output overlaps repository inputs")
    workspace = outdir / "partition_context"
    paths = partitions.output_paths(parents)
    pending = {}
    for parent in parents:
        original = source_path(parent["source"], root)
        source = candidate if parent["id"] == row["id"] else original
        rendered = partitions.render_parent(parent, source.read_text(), aliases)
        pending[paths["remainders"][parent["source"]]] = _relative_headers(rendered["remainder"], original)
        for module_name, text in rendered["parts"].items():
            pending[paths["parts"][parent["id"]][module_name]] = text

    for module in owners:
        original = source_path(module["source"], root)
        text = original.read_text()
        declared = {m["source"]: candidate if m["id"] == row["id"] else source_path(m["source"], root)
                    for m in module["members"]}
        whole = list(declared)
        for parent in parents:
            part = paths["parts"][parent["id"]].get(module["name"])
            if part:
                declared[part] = workspace / part
        seen = []
        def replace(match):
            source = posixpath.normpath(str(PurePosixPath(module["source"]).parent / match.group(2)))
            if source not in declared:
                raise partitions.PartitionError(module["name"] + ": undeclared C include " + source)
            seen.append(source)
            return match.group(1) + json.dumps(str(declared[source].resolve()))
        text = re.sub(r'(^[ \t]*#include[ \t]+)"([^"\n]+\.c)"[ \t]*$', replace, text, flags=re.M)
        if set(seen) != set(declared) or len(seen) != len(declared) or [s for s in seen if s in whole] != whole:
            raise partitions.PartitionError(module["name"] + ": C includes must cover declared parts and ordered members exactly")
        pending[module["source"]] = _relative_headers(text, original)

    # Validate the whole candidate before writing any source views. Symlinked
    # outputs must not redirect writes back into the canonical tree.
    for relative in pending:
        target = workspace / relative
        if target.is_symlink() or not target.parent.resolve().is_relative_to(outdir):
            raise partitions.PartitionError("partition output escapes private directory")
    for relative, text in pending.items():
        target = workspace / relative
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_text(text)
    expected = partitions.expected_units(parents, owners)
    result = []
    for unit in partitions.row_units(row["id"], parents, owners):
        generated = paths["remainders"].get(unit["source"], unit["source"])
        result.append(dict(unit, cfile=workspace / generated,
                           expected_functions=sorted(expected[unit["source"]])))
    return result
