#!/usr/bin/env python3
"""Plan/export a directory move of one currently certified overlay module.

Default: print a guarded dry-run plan. --package DIR exports a separate package;
no source is moved by this command. Apply the package in a quiet landing
transaction, rebuild the views/graph and renew its certificate before landing.
Shared headers remain shared; module-specific headers mirror the proposed tree.
"""
from __future__ import annotations
import argparse
import csv
import json
import os
from pathlib import Path
import re
from source_layout import ROOT, row_relative, validate
from guarded_package import export, sha, safe


def plan(module_key, root=ROOT, mapping_file=None):
    root = Path(root).resolve()
    validate(root)
    # Selection is deliberately fail closed: ledger-only groups and SLUS
    # partitions need their own reviewed physical proof before moving.
    from gate.overlay_module_gate import load_modules, all_members
    from overlay_module_evidence import certificate_reason
    modules = load_modules(root)
    hits = [m for m in modules if m["key"] == module_key]
    if len(hits) != 1:
        raise ValueError("unknown physical overlay module: " + module_key)
    module = hits[0]
    cp = root / "ledger/modules" / ("overlay_" + module_key + ".json")
    cert = json.loads(cp.read_text())
    reason = certificate_reason(module, cert, root)
    if reason:
        raise ValueError("module requires certification before planning: " + reason)
    mapping_file = mapping_file or root / "config/layout_proposal.tsv"
    with Path(mapping_file).open() as f:
        matches = [r for r in csv.DictReader(f, delimiter="\t")
                   if r["container"] == module["container"] and r["module_group"] == module["name"]]
    if len(matches) != 1:
        raise ValueError("module has no unique proposed directory")
    directory = Path(matches[0]["proposed_dir"])
    safe(root, (directory / "placeholder.c").as_posix())
    if directory.parts[:2] != ("src", module["container"]):
        raise ValueError("proposal crosses containers")
    moves = {}
    for member in all_members(module):
        old = row_relative(member["id"], root)
        if member["source"] != old:
            raise ValueError("manifest/layout member differs: " + member["id"])
        moves[old] = (directory / Path(old).name).as_posix()
    moves[module["source"]] = (directory / Path(module["source"]).name).as_posix()
    for header in module["headers"]:
        if header.startswith("include/modules/"):
            moves[header] = (Path("include") / Path(*directory.parts[1:]) / Path(header).name).as_posix()
    if any(old == new for old, new in moves.items()) or len(set(moves.values())) != len(moves):
        raise ValueError("module is already moved or destinations collide")
    for new in moves.values():
        if safe(root, new).exists():
            raise ValueError("move destination exists: " + new)
    # Rewrite quoted includes by resolved identity, preserving system/include
    # spelling except for references to moved files. Outside consumers are
    # rejected; this package must never silently broaden to another module.
    def rewrite(old, text):
        new = moves[old]
        def replace(match):
            token = match[2]
            choices = [Path(old).parent / token, Path("include") / token, Path(token)]
            target = next((os.path.normpath(p) for p in choices if (root / p).is_file()), None)
            if target is None:
                return match[0]
            target = moves.get(target, target)
            new_choices = [Path(new).parent / token, Path("include") / token, Path(token)]
            if target in {os.path.normpath(p) for p in new_choices}:
                return match[0]
            spelling = (Path(target).relative_to("include").as_posix() if target.startswith("include/")
                        else os.path.relpath(target, Path(new).parent))
            return match[1] + spelling + match[3]
        return re.sub(r'(?m)^(\s*#\s*include\s+")([^"\n]+)(")', replace, text)
    changes = {}
    for old, new in moves.items():
        text = safe(root, old).read_text()
        if re.search(r"\b__FILE__\b", text):
            raise ValueError("path-sensitive __FILE__ requires separate review: " + old)
        changes[old] = None
        changes[new] = rewrite(old, text).encode()
    # An external include of a moved file would become stale. Bound this scan
    # to source/header trees only; never inspect work/ or archived experiments.
    for subtree in (root / "src", root / "include"):
        for p in subtree.rglob("*"):
            if p.suffix not in {".c", ".h"} or not p.is_file() or p.stat().st_size > 4 * 1024 * 1024:
                continue
            rel = p.relative_to(root).as_posix()
            if rel in moves:
                continue
            for token in re.findall(r'(?m)^\s*#\s*include\s+"([^"\n]+)"', p.read_text()):
                if any(os.path.normpath(v) in moves for v in [Path(rel).parent / token, Path("include") / token, Path(token)]):
                    raise ValueError("outside consumer needs separate review: " + rel)
    doc = json.loads((root / "config/overlays/modules.json").read_text())
    updated = next(m for m in doc["modules"] if m["key"] == module_key)
    updated["source"] = moves[module["source"]]
    updated["headers"] = [moves.get(h, h) for h in module["headers"]]
    for a in updated.get("data_members", []) + updated["members"]:
        a["source"] = moves[a["source"]]
    changes["config/overlays/modules.json"] = (json.dumps(doc, indent=2) + "\n").encode()
    # Preserve order and formatting of untouched layout records exactly.
    layout = root / "ledger/layout.jsonl"
    pending = {a["id"]: moves[a["source"]] for a in all_members(module)}
    output = []
    for line in layout.read_text().splitlines(keepends=True) if layout.exists() else []:
        record = json.loads(line) if line.strip() else None
        if record and record["id"] in pending:
            record["path"] = pending.pop(record["id"])
            line = json.dumps(record, separators=(",", ":")) + "\n"
        output.append(line)
    output.extend(json.dumps({"id": rid, "path": p}, separators=(",", ":")) + "\n" for rid, p in sorted(pending.items()))
    changes["ledger/layout.jsonl"] = "".join(output).encode()
    return changes, {"kind": "layout-move-pilot", "module": module_key,
                     "moves": moves, "certificates_requiring_renewal": [module_key],
                     "reviewer": module["review"]["reviewer"],
                     "base_certificate_sha256": sha(cp),
                     "protected_inputs": {"tools/gate/source_layout.py": sha(root / "tools/gate/source_layout.py")}, "proposed_directory": directory.as_posix()}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("module")
    ap.add_argument("--root", type=Path, default=ROOT)
    ap.add_argument("--mapping", type=Path)
    ap.add_argument("--package", type=Path)
    args = ap.parse_args()
    changes, metadata = plan(args.module, args.root, args.mapping)
    if args.package:
        records = export(args.package, args.root, changes, metadata)
    else:
        import hashlib
        records = [{"path": rel, "before": sha(safe(args.root, rel)),
                    "after": hashlib.sha256(data).hexdigest() if data is not None else None}
                   for rel, data in sorted(changes.items())]
    print(json.dumps({"dry_run": True, "metadata": metadata, "files": records}, indent=2))


if __name__ == "__main__":
    main()
