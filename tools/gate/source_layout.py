"""Current row locations, independent of immutable c_path lineage and staging names.

ledger/layout.jsonl contains {"id": row_id, "path": "src/<container>/.../<stem>.c"}.
Missing entries (and an absent ledger) use the historical flat path. This first
stage moves whole row files only; merging rows into one TU is deliberately a
separate operation. Raw sources and lane base/out names never use this map.

A link-list placement row (registry `source_row`, derived by tools/registry.py from config/link/,
docs/LINK_LISTS.md) has no file of its own: it resolves to its home row's source.
"""
from __future__ import annotations
import argparse
import hashlib
import re
import json
import os
from pathlib import Path, PurePosixPath
from functools import lru_cache

ROOT = Path(__file__).resolve().parents[1]
if ROOT.name == "tools":
    ROOT = ROOT.parent
CONTAINERS = {"main", "town", "dungeon", "ovmovie", "slus", "dungeon_engine"}
SUBSYSTEMS = {"engine", "frontend", "town", "dungeon", "movie", *CONTAINERS}
# Shared homes a row may move into from any container. A row never lands under
# ANOTHER container's directory (flat src/<container>/ listings collect TUs).
SHARED_SUBSYSTEMS = {"engine", "frontend", "movie"}


def _home_dirs(container):
    return {container} | SHARED_SUBSYSTEMS | ({"dungeon"} if container == "dungeon_engine" else set())


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
            or len(p.parts) < 3 or p.parts[0] != "src" or p.parts[1] not in _home_dirs(container)
            or p.suffix != ".c" or "\\" in value):
        raise ValueError("unsafe source path: " + value)
    return value


def flat_relative(row):
    return "src/" + row["container"] + "/" + Path(row["c_path"]).name


@lru_cache(maxsize=16)
def _load(path, stamp, rows_path, rows_stamp, inline_path, inline_stamp):
    if stamp is None:
        return {}
    reg = _registry(rows_path, rows_stamp)
    mapping = {}
    paths = {}
    inlined = {}
    if inline_stamp is not None:
        for record in map(json.loads, filter(str.strip, Path(inline_path).read_text().splitlines())):
            inlined[record['member_id']] = record['tu_new']
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
        if row.get("source_row"):
            raise ValueError("a link-list placement has no source path of its own: " + rid)
        value = _safe_path(record["path"], row["container"])
        if value in paths and not (inlined.get(rid) == value and inlined.get(paths[value]) == value):
            raise ValueError("two rows share a source path: " + value)
        mapping[rid] = value
        paths[value] = rid
    # A sparse map must not collide with any row left at its default location.
    effective = [mapping.get(rid, flat_relative(r)) for rid, r in reg.items() if rid not in inlined]
    if len(effective) != len(set(effective)):
        raise ValueError("layout collides with a default row path")
    return mapping


def mapping(root=ROOT):
    root = Path(root).absolute()
    p, rp = root / "ledger/layout.jsonl", root / "ledger/rows.jsonl"
    ip = root / "ledger/layout_inline.jsonl"
    return _load(str(p), _stamp(p), str(rp), _stamp(rp), str(ip), _stamp(ip))


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
    # Link-list placement row: no file of its own; it compiles its home row's TU (docs/LINK_LISTS.md).
    ref = registry(root).get(rid, {}).get("source_row")
    if ref:
        if ref == rid or registry(root).get(ref, {}).get("source_row"):
            raise ValueError("placement must reference an own-file home row: " + rid)
        return row_relative(ref, root, layout=layout)
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
    # A placement shares its home's file: the file belongs to the home row (counted once).
    by_path = {row_path(r, root): rid for rid, r in reg.items() if not r.get("source_row")}
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
    old = "src/slus/" + Path(*p.parts[1:]).as_posix()
    return Path(root) / tu_moves(root).get(old, old)


def validate(root=ROOT, *, require_files=True):
    root = Path(root).absolute()
    reg, current = registry(root), mapping(root)
    inlined = inline_records(root)
    wrappers = tu_moves(root)
    relative = {rid: current.get(rid, _safe_path(flat_relative(row), row['container']))
                for rid, row in reg.items() if not row.get('source_row')}
    for rid, row in reg.items():
        home = row.get('source_row')
        if home and (home == rid or home not in relative):
            raise ValueError('placement must reference an own-file home row: ' + rid)
    owned = {}
    for rid, rel in relative.items():
        owned.setdefault(rel, set()).add(rid)
    inline_owners = {}
    for record in inlined:
        inline_owners.setdefault(record['tu_new'], set()).add(record['member_id'])
    source_root = (root / 'src').resolve()
    aliases = {flat_relative(row) for row in reg.values() if not row.get('source_row')}
    for old, new in wrappers.items():
        if old in aliases or new in aliases or old in owned or (new in owned and owned[new] != inline_owners.get(new)):
            raise ValueError('TU layout collides with row path: ' + new)
        if not (root / new).resolve().is_relative_to(source_root):
            raise ValueError('TU source symlink escapes src: ' + new)
        if require_files and not (root / new).is_file():
            raise ValueError('missing TU layout destination: ' + new)
    source_root = (root / 'src').resolve()
    for rel in owned:
        p = root / rel
        if not p.resolve().is_relative_to(source_root):
            raise ValueError('source symlink escapes src: ' + rel)
        if require_files and not p.is_file():
            raise ValueError('missing source for ' + ','.join(sorted(owned[rel])) + ': ' + rel)
    return len(reg)


def tu_moves(root=ROOT):
    """Old physical TU path -> new TU path, for wrappers outside the row ledger."""
    path = Path(root).absolute() / "ledger/tu_layout.jsonl"
    result = {}
    if not path.exists():
        return result
    for line in path.read_text().splitlines():
        if not line.strip():
            continue
        record = json.loads(line)
        if set(record) != {"old", "new"}:
            raise ValueError("TU layout record requires old and new")
        old, new = record["old"], record["new"]
        for value in (old, new):
            if not isinstance(value, str):
                raise ValueError('unsafe TU layout path: ' + str(value))
            p = PurePosixPath(value)
            if (str(p) != value or p.is_absolute() or ".." in p.parts or len(p.parts) < 3
                    or p.parts[0] != "src" or p.parts[1] not in SUBSYSTEMS or p.suffix != ".c" or "\\" in value):
                raise ValueError("unsafe TU layout path: " + str(value))
        if old in result or new in result.values():
            raise ValueError("duplicate TU layout path")
        result[old] = new
    return result


def inline_records(root=ROOT):
    """Validate inlined member identity against the actual embedded source bytes.

    Include spellings may change during relocation. Restore the original tokens
    before rechecking source_sha256; all other bytes must match the reviewed
    fragment. The old member file must be absent and its row must own the TU.
    """
    root = Path(root)
    path = root / 'ledger/layout_inline.jsonl'
    if not path.exists():
        return []
    records = [json.loads(line) for line in path.read_text().splitlines() if line.strip()]
    seen, extents, orders = set(), {}, set()
    reg = registry(root)
    include = re.compile(r'(?m)^([ \t]*#[ \t]*include[ \t]*[<"])([^">\n]+)([>"])')
    for r in records:
        required = {'tu_old', 'tu_new', 'member', 'member_id', 'manifest_key', 'order',
                    'offset', 'source_sha256', 'bytes', 'inlined_bytes', 'original_includes'}
        if set(r) != required or r['member_id'] in seen:
            raise ValueError('invalid or duplicate inline provenance')
        seen.add(r['member_id'])
        row = reg.get(r['member_id'])
        if row is None or row.get('source_row'):
            raise ValueError('inline member requires an own-file row')
        target = _safe_path(r['tu_new'], row['container'])
        member = _safe_path(r['member'], row['container'])
        if (root / member).exists() or (root / member).is_symlink():
            raise ValueError('retired inline member still exists: ' + member)
        if row_relative(row, root) != target:
            raise ValueError('inline row does not point to physical TU')
        if any(type(r[k]) is not int or r[k] < 0 for k in ('offset', 'bytes', 'inlined_bytes', 'order')):
            raise ValueError('invalid inline extent/order')
        key = (target, r['order'])
        if key in orders:
            raise ValueError('duplicate inline order')
        orders.add(key)
        data = row_path(row, root).read_bytes()
        start, end = r['offset'], r['offset'] + r['inlined_bytes']
        if end > len(data) or any(start < b and a < end for a, b in extents.get(target, [])):
            raise ValueError('invalid/overlapping inline extent')
        extents.setdefault(target, []).append((start, end))
        piece = data[start:end].decode('utf-8', 'surrogateescape')
        tokens = r['original_includes']
        hits = list(include.finditer(piece))
        if not isinstance(tokens, list) or len(hits) != len(tokens) or any(not isinstance(t, str) for t in tokens):
            raise ValueError('inline source_sha256 include mismatch')
        originals = iter(tokens)
        restored = include.sub(lambda m: m[1] + next(originals) + m[3], piece).encode('utf-8', 'surrogateescape')
        if (restored[r['bytes']:] not in (b'', b'\n') or
                hashlib.sha256(restored[:r['bytes']]).hexdigest() != r['source_sha256']):
            raise ValueError('inline source_sha256 mismatch: ' + r['member_id'])
    return records


_PROJECTION_DIRECTIVE = re.compile(rb'^[ \t]*#[ \t]*([A-Za-z_]*)')


@lru_cache(maxsize=16)
def _projection_index(path, stamp):
    """Index provenance only; member_projection still validates the current TU bytes.

    Keep duplicates so the existing per-member duplicate check cannot be hidden
    by a dictionary overwrite. The identity includes ctime (see _stamp).
    """
    members, first = {}, {}
    if stamp is not None:
        for line in Path(path).read_text().splitlines():
            if not line.strip():
                continue
            rec = json.loads(line)
            members.setdefault(rec['member_id'], []).append(rec)
            tu = rec['tu_new']
            first[tu] = min(first.get(tu, rec['offset']), rec['offset'])
    return members, first


def member_projection(row_id, root=ROOT):
    """Span-aware compile unit for an inlined member, or None for an own-file row.

    A link-list placement compiles its home row's text (docs/LINK_LISTS.md). After its home
    fragment is inlined, row_path() names the whole owner TU, whose siblings must not enter the
    placement object. The unit is the owner's leading depth-0 #include lines (the bytes before its
    first inline extent; other prefix text such as entry tables is not this member's) followed by
    the member's own extent. Every check fails closed; nothing falls back to the whole owner.
    """
    root = Path(root).absolute()
    path = root / 'ledger/layout_inline.jsonl'
    members, first_offsets = _projection_index(str(path), _stamp(path))
    mine = members.get(row_id, ())
    if not mine:
        return None
    if len(mine) != 1:
        raise ValueError('duplicate inline provenance: ' + row_id)
    rec = mine[0]
    row = registry(root).get(row_id)
    if row is None or row.get('source_row') or row_relative(row, root) != rec['tu_new']:
        raise ValueError('inline member does not own its physical TU: ' + row_id)
    owner = _safe_path(rec['tu_new'], row['container'])
    data = row_path(row, root).read_bytes()
    start, end = rec['offset'], rec['offset'] + rec['inlined_bytes']
    if not 0 <= start < end <= len(data) or (start and data[start - 1:start] != b'\n'):
        raise ValueError('inline extent is not a line span of its TU: ' + row_id)
    piece = data[start:end]
    include = re.compile(r'(?m)^([ \t]*#[ \t]*include[ \t]*[<"])([^">\n]+)([>"])')
    text = piece.decode('utf-8', 'surrogateescape')
    tokens = rec['original_includes']
    if not isinstance(tokens, list) or len(include.findall(text)) != len(tokens):
        raise ValueError('inline source_sha256 include mismatch: ' + row_id)
    originals = iter(tokens)
    restored = include.sub(lambda m: m[1] + next(originals) + m[3], text).encode('utf-8', 'surrogateescape')
    if (restored[rec['bytes']:] not in (b'', b'\n')
            or hashlib.sha256(restored[:rec['bytes']]).hexdigest() != rec['source_sha256']):
        raise ValueError('inline source_sha256 mismatch: ' + row_id)
    first = first_offsets[rec['tu_new']]
    context = []
    for line in data[:first].splitlines(keepends=True):
        hit = _PROJECTION_DIRECTIVE.match(line)
        if hit is None:
            continue
        if hit[1] != b'include' or include.match(line.decode('utf-8', 'surrogateescape')) is None:
            raise ValueError('owner prefix directive needs review before projection: ' + owner)
        context.append(line if line.endswith(b'\n') else line + b'\n')
    unit = b''.join(context) + piece
    for hit in include.finditer(unit.decode('utf-8', 'surrogateescape')):
        token = hit[2]
        if token.endswith('.c') or (hit[1].endswith('"') and (root / owner).parent.joinpath(token).exists()):
            raise ValueError('owner-relative include in projected member: ' + owner + ': ' + token)
    return unit


def projection_plan(root=ROOT, source_root=None):
    """{"<container>/<entry name>": target} of the managed flat projection over source_root."""
    root = Path(root).absolute()
    canonical = root / "src"
    source_root = Path(source_root).absolute() if source_root else canonical
    reg = registry(root)
    wanted = {}
    for container_dir in source_root.iterdir():
        if not container_dir.is_dir():
            continue
        for entry in container_dir.iterdir():
            # Preserve nested manifest/wrapper paths as well as flat aliases.
            if entry.is_file() or entry.is_dir():
                wanted[container_dir.name + "/" + entry.name] = entry
    for old, new in tu_moves(root).items():
        # Legacy build recipes still name flat src/<container>/<stem>.c;
        # expose moved physical wrappers under that spelling.
        if len(PurePosixPath(old).parts) != 3:
            continue
        target = source_root / Path(new).relative_to("src")
        if target.is_file():
            wanted[Path(old).relative_to("src").as_posix()] = target
    for r in reg.values():
        target = row_path(r, root) if source_root == canonical else source_root / Path(row_relative(r, root)).relative_to("src")
        if source_root != canonical and not target.is_file():
            target = source_root / r["container"] / Path(r["c_path"]).name
        wanted[r["container"] + "/" + Path(r["c_path"]).name] = target
    return wanted


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
    if not moved and not tu_moves(root):
        return source_root
    if source_root != canonical and not any(
            (source_root / Path(row_relative(r, root)).relative_to("src")).is_file() for r in moved):
        return source_root
    destination = Path(destination).absolute()
    if destination.is_symlink() or not destination.resolve().is_relative_to(root.resolve()):
        raise ValueError("projection must be a private directory inside root")
    marker = destination / ".source_layout_projection"
    if destination.exists() and not marker.is_file():
        raise ValueError("refusing unmanaged projection: " + str(destination))
    wanted = projection_plan(root, source_root)
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
    text = "source_layout v1 live symlinks\n"
    if not marker.exists() or marker.read_text() != text:
        marker.write_text(text)
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
    return tuple(_stamp(root / ('ledger/' + name)) for name in
                 ('rows.jsonl', 'layout.jsonl', 'tu_layout.jsonl', 'layout_inline.jsonl'))


def row_ids_for_paths(paths, root=ROOT):
    """Inverse for git/package paths. Also recognize the immutable flat aliases."""
    root = Path(root).absolute()
    # A shared TU (link-list home) maps to its home row AND every placement compiled from it.
    inverse = {}
    for rid, row in registry(root).items():
        inverse.setdefault(flat_relative(row), set()).add(rid)
        inverse.setdefault(row_relative(row, root), set()).add(rid)
    result = set()
    for name in paths:
        p = Path(name.strip())
        if p.is_absolute():
            try:
                p = p.relative_to(root)
            except ValueError:
                continue
        result.update(inverse.get(p.as_posix(), ()))
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


def physical_owner(row_or_id, root=ROOT):
    """Reviewed physical module for a home/member/admitted placement, else None."""
    import overlay_module_placements as P
    rid = row_or_id if isinstance(row_or_id, str) else row_or_id['id']
    return P.owner(root, rid)
