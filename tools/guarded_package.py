"""Small guarded file transaction, also copied verbatim as package apply.py.

SHA-256 guards for every before/after file; null means absent. Deletions carry
an empty payload bound by package.sha256.json. --dry-run wins over --live.
Proofs run separately under the landing transaction, never from this installer.
"""
from __future__ import annotations
import argparse
import hashlib
import json
import os
from pathlib import Path
import tempfile


def sha(path):
    return hashlib.sha256(path.read_bytes()).hexdigest() if path.is_file() else None


def safe(root, name):
    rel = Path(name)
    if (not isinstance(name, str) or not name or str(rel) != name
            or rel.is_absolute() or ".." in rel.parts):
        raise ValueError("unsafe package path: " + str(name))
    p = root / rel
    if p.is_symlink() or not p.parent.resolve().is_relative_to(root.resolve()):
        raise ValueError("package path escapes root: " + name)
    if p.exists() and not p.is_file():
        raise ValueError("not a regular file: " + name)
    return p


def export(destination, root, changes, metadata=None):
    """changes is {relative_path: bytes_or_None}; root is read-only here."""
    destination, root = Path(destination), Path(root).resolve()
    if destination.exists():
        raise ValueError("package output already exists")
    # All destination guards are checked before creating any package output.
    entries = []
    for rel, data in sorted(changes.items()):
        p = safe(root, rel)
        before = sha(p)
        after = hashlib.sha256(data).hexdigest() if data is not None else None
        if before == after:
            continue
        entries.append({"path": rel, "file": "records/" + rel,
                        "before": before, "after": after,
                        "mode": (p.stat().st_mode & 0o777) if p.exists() else 0o644})
    destination.mkdir(parents=True)
    for rec in entries:
        p = destination / rec["file"]
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_bytes(changes[rec["path"]] or b"")
    (destination / "files.json").write_text(json.dumps(entries, indent=2) + "\n")
    (destination / "manifest.json").write_text(json.dumps(metadata or {}, indent=2) + "\n")
    (destination / "apply.py").write_bytes(Path(__file__).read_bytes())
    bound = ["apply.py", "files.json", "manifest.json", *(r["file"] for r in entries)]
    (destination / "package.sha256.json").write_text(json.dumps({n: sha(destination / n) for n in sorted(bound)}, indent=2) + "\n")
    return entries


def apply(package, root, *, live=False, dry_run=False):
    package, root = Path(package).resolve(), Path(root).resolve()
    canonical = os.environ.get("LAND_LIVE_ROOT")
    if canonical and root == Path(canonical).resolve() and not live:
        raise ValueError("canonical root requires --live; --live --dry-run previews safely")
    inventory = json.loads((package / "package.sha256.json").read_text())
    for name, expected in inventory.items():
        if sha(safe(package, name)) != expected:
            raise ValueError("package integrity drift: " + name)
    if not {"apply.py", "files.json", "manifest.json"} <= inventory.keys():
        raise ValueError("incomplete package integrity inventory")
    metadata = json.loads((package / "manifest.json").read_text())
    for name, expected in metadata.get("protected_inputs", {}).items():
        if sha(safe(root, name)) != expected:
            raise ValueError("protected input guard mismatch: " + name)
    records = json.loads((package / "files.json").read_text())
    paths = set()
    prepared = []
    for rec in records:
        rel = rec["path"]
        if rel in paths:
            raise ValueError("duplicate package destination: " + rel)
        paths.add(rel)
        src, dst = safe(package, rec["file"]), safe(root, rel)
        if rec["file"] not in inventory:
            raise ValueError("unbound payload: " + rec["file"])
        data = src.read_bytes()
        if (rec["after"] is None and data) or (rec["after"] is not None and sha(src) != rec["after"]):
            raise ValueError("payload hash mismatch: " + rel)
        current = sha(dst)
        if current not in (rec["before"], rec["after"]):
            raise ValueError("before/after guard mismatch: " + rel)
        prepared.append((rec, dst, data if rec["after"] is not None else None, current))
    if prepared and all(current == rec["after"] for rec, _, _, current in prepared):
        return {"status": "already-applied", "files": len(prepared), "dry_run": dry_run}
    if any(current != rec["before"] for rec, _, _, current in prepared):
        raise ValueError("partially applied package; restore or regenerate")
    if dry_run:
        return {"status": "dry-run", "files": len(prepared), "dry_run": True}
    if not live:
        raise ValueError("writing requires --live; inspect with --dry-run")
    undo = []
    try:
        for rec, dst, data, _ in prepared:
            undo.append((dst, dst.read_bytes() if dst.exists() else None,
                         dst.stat().st_mode & 0o777 if dst.exists() else None))
            if data is None:
                dst.unlink()
            else:
                dst.parent.mkdir(parents=True, exist_ok=True)
                with tempfile.NamedTemporaryFile(dir=dst.parent, prefix=".layout-", delete=False) as f:
                    tmp = Path(f.name)
                    try:
                        f.write(data)
                        f.flush()
                        os.fsync(f.fileno())
                    except BaseException:
                        tmp.unlink(missing_ok=True)
                        raise
                try:
                    tmp.chmod(rec.get("mode", 0o644))
                    tmp.replace(dst)
                finally:
                    tmp.unlink(missing_ok=True)
        if any(sha(dst) != rec["after"] for rec, dst, _, _ in prepared):
            raise ValueError("post-install hash mismatch")
    except BaseException:
        for dst, old, mode in reversed(undo):
            if old is None:
                dst.unlink(missing_ok=True)
            else:
                dst.write_bytes(old)
                dst.chmod(mode)
        raise
    return {"status": "applied", "files": len(prepared), "dry_run": False}


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, required=True)
    ap.add_argument("--live", action="store_true")
    ap.add_argument("--dry-run", action="store_true")
    args = ap.parse_args()
    print(json.dumps(apply(Path(__file__).resolve().parent, args.root,
                           live=args.live, dry_run=args.dry_run), sort_keys=True))


if __name__ == "__main__":
    main()
