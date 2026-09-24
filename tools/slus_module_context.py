"""Keep logical SLUS rows editable while compiling their declared module context.

Rows retain their original C paths and identities. A module is an ordinary C
translation unit that includes those row files in order and owns shared data.
This module never synthesizes symbol declarations or assembler exceptions.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
import sys

from common import ROOT

sys.path.insert(0, str(Path(__file__).resolve().parent / "build"))
from slus_modules import load_manifest, module_for_row  # noqa: E402


def modules(root=ROOT):
    return load_manifest(Path(root) / "config/slus_modules.json")


def membership(row, root=ROOT):
    if row.get("kind") != "slus":
        return None
    return module_for_row(modules(root), row["id"])


def source_path(source, root=ROOT):
    """Manifest source paths are relative to the exported build's src/ directory."""
    return Path(root) / "src/slus" / Path(source).relative_to("src")


def input_paths(module, root=ROOT):
    return ([source_path(module["source"], root)]
            + [source_path(m["source"], root) for m in module["members"]]
            + [Path(root) / header for header in module["headers"]])


def fingerprint(row, root=ROOT):
    module = membership(row, root)
    if module is None:
        return None
    h = hashlib.sha256(json.dumps(module, sort_keys=True).encode())
    for path in input_paths(module, root):
        h.update(str(path.relative_to(root)).encode())
        h.update(path.read_bytes())
    return h.hexdigest()


def compilation_source(row, candidate, outdir, root=ROOT):
    """Use the real module, substituting the candidate for exactly one row include.

    Historical raw baselines continue to compile independently. Live candidates
    include all siblings and the module's actual data definition, so source edits
    cannot be scored against invented ownership context.
    """
    candidate = Path(candidate).resolve()
    module = membership(row, root)
    if module is None or candidate == (Path(root) / "raw/slus" / Path(row["c_path"]).name).resolve():
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
    module = module_for_row(modules(root), "slus/" + stem)
    return Path(module["source"]).stem if module else stem


def require_individual_recipe(row, root=ROOT):
    module = membership(row, root)
    if module:
        raise ValueError(f"{row['id']} belongs to {module['name']}; change the module recipe and verify all members together")
