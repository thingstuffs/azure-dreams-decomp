"""Current row locations, independent of immutable c_path lineage and staging names.

ledger/layout.jsonl contains {"id": row_id, "path": "src/<container>/.../<stem>.c"}.
Missing entries (and an absent ledger) use the historical flat path. This first
stage moves whole row files only; merging rows into one TU is deliberately a
separate operation. Raw sources and lane base/out names never use this map.
"""
from __future__ import annotations
import argparse
import json
import os
from pathlib import Path, PurePosixPath
from functools import lru_cache

ROOT = Path(__file__).resolve().parents[1]
if ROOT.name == "tools":
    ROOT = ROOT.parent
CONTAINERS = {"main", "town", "dungeon", "ovmovie", "slus", "dungeon_engine"}


def _stamp(path):
    try:
        s = path.stat()
        return (s.st_dev, s.st_ino, s.st_size, s.st_mtime_ns, s.st_ctime_ns)
    except FileNotFoundError:
        return None


@lru_cache(maxsize=16)
def _registry(path, stamp):
    if stamp is None:
        return {}
    records = [json.loads(s) for s in Path(path).read_text().splitlines() if s.strip()]
    result = {r["id"]: r for r in records}
    if len(result) != len(records):
        raise ValueError("duplicate row id in registry")
    return result


def registry(root=ROOT):
    p = Path(root).absolute() / "ledger/rows.jsonl"
    return _registry(str(p), _stamp(p))


def _safe_path(value, container):
    if not isinstance(value, str):
        raise ValueError("source path must be a string")
    p = PurePosixPath(value)
    if (str(p) != value or p.is_absolute() or ".." in p.parts
            or len(p.parts) < 3 or p.parts[:2] != ("src", container)
            or p.suffix != ".c" or "\\" in value):
        raise ValueError("unsafe source path: " + value)
    return value


def flat_relative(row):
    return "src/" + row["container"] + "/" + Path(row["c_path"]).name


@lru_cache(maxsize=16)
def _load(path, stamp, rows_path, rows_stamp):
    if stamp is None:
        return {}
    reg = _registry(rows_path, rows_stamp)
    mapping = {}
    paths = set()
    for line in Path(path).read_text().splitlines():
        if not line.strip():
            continue
        record = json.loads(line)
        if set(record) != {"id", "path"}:
            raise ValueError("layout record requires exactly id and path")
        rid = record["id"]
        if not isinstance(rid, str) or rid not in reg or rid in mapping:
            raise ValueError("unknown or duplicate layout row: " + str(rid))
        row = reg[rid]
        value = _safe_path(record["path"], row["container"])
        if Path(value).name != Path(row["c_path"]).name:
            raise ValueError("layout must preserve the row filename: " + rid)
        if value in paths:
            raise ValueError("two rows share a source path: " + value)
        mapping[rid] = value
        paths.add(value)
    # A sparse map must not collide with any row left at its default location.
    effective = [mapping.get(rid, flat_relative(r)) for rid, r in reg.items()]
    if len(effective) != len(set(effective)):
        raise ValueError("layout collides with a default row path")
    return mapping


def mapping(root=ROOT):
    root = Path(root).absolute()
    p, rp = root / "ledger/layout.jsonl", root / "ledger/rows.jsonl"
    return _load(str(p), _stamp(p), str(rp), _stamp(rp))


def row_relative(row_or_id, root=ROOT, *, layout=None):
    if isinstance(row_or_id, str):
        row = registry(root).get(row_or_id)
        if row is None:
            # Old staging readers sometimes ask for an unregistered auxiliary TU.
            container, name = row_or_id.split("/", 1)
            if container not in CONTAINERS or "/" in name or not name or name in {".", ".."}:
                raise ValueError("invalid row id: " + row_or_id)
            row = {"id": row_or_id, "container": container, "c_path": name + ".c"}
    else:
        row = row_or_id
        if "c_path" not in row and row.get("id"):
            return row_relative(row["id"], root, layout=layout)
    rid = row.get("id")
    if rid is None:
        rid = row["container"] + "/" + Path(row["c_path"]).stem
    current = mapping(root) if layout is None else layout
    if rid in current:
        return current[rid]  # Already validated when this map was loaded.
    return _safe_path(flat_relative(row), row["container"])


def row_path(row_or_id, root=ROOT):
    root = Path(root).absolute()
    p = root / row_relative(row_or_id, root)
    # View roots may symlink src to their authority. Reject escapes from that
    # source tree, including a malicious existing destination ancestor.
    if not p.resolve().is_relative_to((root / "src").resolve()):
        raise ValueError("source symlink escapes src: " + str(p))
    return p


def source_files(container, root=ROOT):
    """Row and auxiliary C files; exclude aggregator TUs as the old flat glob did."""
    root = Path(root).absolute()
    directory = root / "src" / container
    files = set(directory.glob("*.c"))
    files.update(row_path(r, root) for r in registry(root).values() if r["container"] == container)
    return sorted(files)



def source_items(root=ROOT):
    """Stable (row id, current path) pairs, including historical flat auxiliaries."""
    root = Path(root).absolute()
    reg = registry(root)
    by_path = {row_path(r, root): rid for rid, r in reg.items()}
    items = []
    for container in sorted(CONTAINERS - {"dungeon_engine"}):
        for p in source_files(container, root):
            if p.is_file():
                items.append((by_path.get(p, container + "/" + p.stem), p))
    return sorted(items)


def slus_source(source, root=ROOT):
    """Translate an exported SLUS src/... token to the canonical tree."""
    p = PurePosixPath(source)
    if (p.is_absolute() or ".." in p.parts or str(p) != source
            or len(p.parts) < 2 or p.parts[0] != "src"):
        raise ValueError("unsafe SLUS source: " + source)
    rid = "slus/" + p.stem
    if rid in registry(root):
        return row_path(rid, root)
    return Path(root) / "src/slus" / Path(*p.parts[1:])


def validate(root=ROOT, *, require_files=True):
    reg = registry(root)
    mapping(root)
    for row in reg.values():
        p = row_path(row, root)
        if require_files and not p.is_file():
            raise ValueError("missing source for " + row["id"] + ": " + str(p))
    return len(reg)


def materialize_flat(destination, root=ROOT, source_root=None):
    """Managed live symlink projection for legacy gates. Never copy row bytes.

    Flat alternate SRCROOTs (raw and older experiments) pass through. A
    nested experiment projects its own row bytes, never the live sources.
    """
    root = Path(root).absolute()
    canonical = root / "src"
    source_root = Path(source_root).absolute() if source_root else canonical
    reg = registry(root)
    moved = [r for r in reg.values() if row_relative(r, root) != flat_relative(r)]
    if not moved or (source_root != canonical and not any(
            (source_root / Path(row_relative(r, root)).relative_to("src")).is_file() for r in moved)):
        return source_root
    destination = Path(destination).absolute()
    if destination.is_symlink() or not destination.resolve().is_relative_to(root.resolve()):
        raise ValueError("projection must be a private directory inside root")
    marker = destination / ".source_layout_projection"
    if destination.exists() and not marker.is_file():
        raise ValueError("refusing unmanaged projection: " + str(destination))
    wanted = {}
    for container_dir in source_root.iterdir():
        if not container_dir.is_dir():
            continue
        for entry in container_dir.iterdir():
            # Preserve nested manifest/wrapper paths as well as flat aliases.
            if entry.is_file() or entry.is_dir():
                wanted[container_dir.name + "/" + entry.name] = entry
    for r in reg.values():
        target = row_path(r, root) if source_root == canonical else source_root / Path(row_relative(r, root)).relative_to("src")
        if source_root != canonical and not target.is_file():
            target = source_root / r["container"] / Path(r["c_path"]).name
        wanted[r["container"] + "/" + Path(r["c_path"]).name] = target
    # Validate every existing entry BEFORE changing any of the view.
    if destination.exists():
        for folder in destination.iterdir():
            if folder == marker:
                continue
            if folder.is_symlink() or not folder.is_dir():
                raise ValueError("unmanaged projection entry: " + str(folder))
            for entry in folder.iterdir():
                if not entry.is_symlink():
                    raise ValueError("unmanaged projection entry: " + str(entry))
    destination.mkdir(parents=True, exist_ok=True)
    marker.write_text("source_layout v1 live symlinks\n")
    for folder in destination.iterdir():
        if folder == marker:
            continue
        for entry in folder.iterdir():
            if entry.relative_to(destination).as_posix() not in wanted:
                entry.unlink()
    for rel, target in sorted(wanted.items()):
        p = destination / rel
        p.parent.mkdir(parents=True, exist_ok=True)
        if p.is_symlink() and os.readlink(p) == str(target):
            continue
        if p.is_symlink():
            p.unlink()
        elif p.exists():
            raise ValueError("refusing projection overwrite: " + str(p))
        p.symlink_to(target)
    return destination



def revision(root=ROOT):
    root = Path(root).absolute()
    return (_stamp(root / "ledger/rows.jsonl"), _stamp(root / "ledger/layout.jsonl"))


def row_ids_for_paths(paths, root=ROOT):
    """Inverse for git/package paths. Also recognize the immutable flat aliases."""
    root = Path(root).absolute()
    inverse = {}
    for rid, row in registry(root).items():
        inverse[flat_relative(row)] = rid
        inverse[row_relative(row, root)] = rid
    result = set()
    for name in paths:
        p = Path(name.strip())
        if p.is_absolute():
            try:
                p = p.relative_to(root)
            except ValueError:
                continue
        rid = inverse.get(p.as_posix())
        if rid:
            result.add(rid)
    return sorted(result)


def main():
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument("--root", type=Path, default=ROOT)
    sub = ap.add_subparsers(dest="command", required=True)
    sub.add_parser("check")
    locate = sub.add_parser("path")
    locate.add_argument("row_id")
    identify = sub.add_parser("ids")
    identify.add_argument("paths", nargs="*")
    sub.add_parser("identity", help="print the identity ledger without writing it")
    project = sub.add_parser("project")
    project.add_argument("destination", type=Path)
    project.add_argument("--source-root", type=Path)
    args = ap.parse_args()
    if args.command == "check":
        print("layout OK: " + str(validate(args.root)) + " rows")
    elif args.command == "path":
        print(row_path(args.row_id, args.root))
    elif args.command == "ids":
        import sys
        print(",".join(row_ids_for_paths(args.paths or sys.stdin.read().splitlines(), args.root)))
    elif args.command == "identity":
        for r in registry(args.root).values():
            print(json.dumps({"id": r["id"], "path": flat_relative(r)}, separators=(",", ":")))
    else:
        print(materialize_flat(args.destination, args.root, args.source_root))


if __name__ == "__main__":
    main()
