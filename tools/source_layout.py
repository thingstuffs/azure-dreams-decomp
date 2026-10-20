#!/usr/bin/env python3
"""Public CLI/import facade for the gate-compatible source layout resolver."""
from gate.source_layout import *  # noqa: F401,F403
from gate.source_layout import _registry, _stamp
import json, re
from functools import lru_cache
from pathlib import Path

def physical_owner(row_or_id, root=ROOT):
    """Bootstrap the canonical gate imports for callers using only tools/."""
    from gate import overlay_module_gate  # installs the flat exported-gate import path
    from gate.source_layout import physical_owner as resolve
    rid = row_or_id if isinstance(row_or_id, str) else row_or_id['id']
    home = registry(root).get(rid, {}).get('source_row')
    if home:
        row_relative(rid, root)  # validate the same own-file home rule as source resolution
    return resolve(home or row_or_id, root)


# ---- a row's OWN source text inside a merged TU (ledger/layout_inline.jsonl) ----------------------
# LL7 inlines member fragments into one physical TU, so row_path() of every member is that TU.  A
# per-row scan (levels.py, census.void_exact_targets) must read the member's own fragment, not the
# whole TU (its siblings' bodies, pins, asm and includes are not this row's text).
_INCLUDE_RE = re.compile(r'(?m)^([ \t]*#[ \t]*include[ \t]*[<"])([^">\n]+)([>"])')


@lru_cache(maxsize=16)
def _inline_index(rows_path, rows_stamp, layout_path, layout_stamp, inline_path, inline_stamp):
    """({member id: record}, {TU relative path: [record, ...] by offset}, {relative path: own-file row id}).
    Unvalidated extents -- gate.source_layout.inline_records() validates them against the bytes."""
    members, by_tu = {}, {}
    if inline_stamp is not None:
        for line in Path(inline_path).read_text().splitlines():
            if line.strip():
                rec = json.loads(line)
                members[rec["member_id"]] = rec
                by_tu.setdefault(rec["tu_new"], []).append(rec)
    for recs in by_tu.values():
        recs.sort(key=lambda rec: rec["offset"])
    root = Path(rows_path).parents[1]
    owners = {}
    for rid, r in _registry(rows_path, rows_stamp).items():
        if not r.get("source_row") and rid not in members:
            owners[row_relative(r, root)] = rid
    return members, by_tu, owners


def inline_index(root=ROOT):
    root = Path(root).absolute()
    paths = [root / "ledger/rows.jsonl", root / "ledger/layout.jsonl", root / "ledger/layout_inline.jsonl"]
    return _inline_index(*(v for p in paths for v in (str(p), _stamp(p))))


def _fragment(data, rec):
    start, end = rec["offset"], rec["offset"] + rec["inlined_bytes"]
    if end > len(data) or (start and data[start - 1:start] != b"\n"):
        raise ValueError("inline extent is not a line span of its TU: " + rec["member_id"])
    return data[start:end]


def own_source(row_or_id, root=ROOT):
    """(current text, first-written bytes or None) of the row's OWN source.

    An inlined member (or a placement whose home is one) reads its fragment of the TU; the second
    value is that fragment with its original include spellings restored (the bytes the member file
    had before LL7, comparable with config/frozen_raw.jsonl), or None if the fragment no longer
    restores.  Any other row reads its whole file, both values from the same bytes."""
    root = Path(root).absolute()
    rid = row_or_id if isinstance(row_or_id, str) else row_or_id.get("id")
    home = registry(root).get(rid or "", {}).get("source_row") or rid
    data = row_path(row_or_id, root).read_bytes()
    rec = inline_index(root)[0].get(home)
    if rec is None:
        return data.decode("utf-8", "replace"), data
    piece = _fragment(data, rec)
    text = piece.decode("utf-8", "surrogateescape")
    tokens = rec.get("original_includes") or []
    hits = _INCLUDE_RE.findall(text)
    original = None
    if len(hits) == len(tokens):
        it = iter(tokens)
        restored = _INCLUDE_RE.sub(lambda m: m[1] + next(it) + m[3], text).encode("utf-8", "surrogateescape")
        if restored[rec["bytes"]:] in (b"", b"\n"):
            original = restored[:rec["bytes"]]
    return piece.decode("utf-8", "replace"), original


def source_segments(path, root=ROOT):
    """[(owner row id or None, text)] of one source file: each inlined member's fragment owned by
    that member, the rest of the file (or the whole of an ordinary file) owned by the own-file row
    mapped to it, None for an auxiliary file no row owns."""
    root = Path(root).absolute()
    path = Path(path).absolute()
    try:
        rel = path.relative_to(root).as_posix()
    except ValueError:
        rel = None
    _, by_tu, owners = inline_index(root)
    data = path.read_bytes()
    out, rest, cur = [], [], 0
    for rec in by_tu.get(rel, ()):
        piece = _fragment(data, rec)
        rest.append(data[cur:rec["offset"]])
        out.append((rec["member_id"], piece.decode("utf-8", "replace")))
        cur = rec["offset"] + rec["inlined_bytes"]
    rest.append(data[cur:])
    return [(owners.get(rel), b"".join(rest).decode("utf-8", "replace"))] + out


if __name__ == "__main__":
    main()
