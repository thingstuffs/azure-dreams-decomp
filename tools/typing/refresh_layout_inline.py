#!/usr/bin/env python3
"""Refresh ledger/layout_inline.jsonl after source edits to merged (LL7) TUs.

A layout_inline record locates one member's own text inside its merged TU (offset, inlined_bytes) and
binds it with source_sha256 over that text with the member's original #include tokens restored.  Any
edit to a merged TU (typing, naming, declarations) moves those extents.  This tool diffs every merged TU
against its text at --base (a git revision), maps each record's extent through the line diff, maps the
known includes back to their original tokens, records new includes verbatim, and rewrites the ledger.

  python3 tools/typing/refresh_layout_inline.py --root . --base HEAD [--check]

--check reports how many records would change and exits 1 if any would, without writing.
"""
import argparse
import difflib
import hashlib
import json
import re
import subprocess
import sys
from pathlib import Path

INCLUDE = re.compile(rb'(?m)^([ \t]*#[ \t]*include[ \t]*[<"])([^">\n]+)([>"])')
LEDGER = 'ledger/layout_inline.jsonl'


def git_show(root, rev, rel):
    return subprocess.run(['git', '-C', str(root), 'show', f'{rev}:{rel}'],
                          check=True, capture_output=True).stdout


def line_map(old, new):
    ol, nl = old.splitlines(True), new.splitlines(True)
    oo, no = [0], [0]
    for line in ol:
        oo.append(oo[-1] + len(line))
    for line in nl:
        no.append(no[-1] + len(line))
    ops = difflib.SequenceMatcher(None, ol, nl, autojunk=False).get_opcodes()
    starts = {x: i for i, x in enumerate(oo)}

    def mp(offset, end=False):
        li = starts[offset]
        for tag, i1, i2, j1, j2 in ops:
            if tag == 'equal' and i1 <= li <= i2:
                return no[j1 + (li - i1)]
        for tag, i1, i2, j1, j2 in ops:
            if i1 <= li <= i2:
                return no[j2] if end else no[j1]
        raise ValueError(offset)
    return mp


def refresh(record, old, new, mp):
    start = mp(record['offset'])
    end = mp(record['offset'] + record['inlined_bytes'], True)
    piece = new[start:end]
    tokens = record['original_includes']
    old_piece = old[record['offset']:record['offset'] + record['inlined_bytes']]
    old_includes = [m[2] for m in INCLUDE.finditer(old_piece)]
    if len(old_includes) != len(tokens):
        raise SystemExit(f"{record['tu_new']} {record['member_id']}: base text has {len(old_includes)} includes, "
                         f"record has {len(tokens)}")
    mapping = {}
    for current, original in zip(old_includes, tokens):
        mapping.setdefault(current, original.encode())
    it = iter(tokens)
    old_restored = INCLUDE.sub(lambda m: m[1] + next(it).encode() + m[3], old_piece)
    restored = INCLUDE.sub(lambda m: m[1] + mapping.get(m[2], m[2]) + m[3], piece)
    tail = old_restored[record['bytes']:]
    own = len(restored) - len(tail)
    if restored[own:] != tail:
        raise SystemExit(f"{record['tu_new']} {record['member_id']}: text after the member's own bytes changed")
    out = dict(record)
    out['original_includes'] = [mapping.get(m[2], m[2]).decode() for m in INCLUDE.finditer(piece)]
    out['offset'] = start
    out['inlined_bytes'] = end - start
    out['bytes'] = own
    out['source_sha256'] = hashlib.sha256(restored[:own]).hexdigest()
    return out


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default='.')
    ap.add_argument('--base', required=True, help='git revision whose text the current records describe')
    ap.add_argument('--check', action='store_true')
    args = ap.parse_args()
    root = Path(args.root)
    base_ledger = git_show(root, args.base, LEDGER).decode()
    base_records = [json.loads(line) for line in base_ledger.splitlines() if line.strip()]
    current = (root / LEDGER).read_text()
    records = [json.loads(line) for line in current.splitlines() if line.strip()]
    base_by_key = {(r['member_id'], r['tu_new']): r for r in base_records}
    texts, maps, changed = {}, {}, 0
    for i, current_record in enumerate(records):
        # Installs since --base add records and may retire old TUs. Refresh only
        # surviving baseline records, retaining the current ledger's full roster.
        record = base_by_key.get((current_record['member_id'], current_record['tu_new']))
        if record is None:
            continue
        tu = record['tu_new']
        if tu not in texts:
            old = git_show(root, args.base, tu)
            new = (root / tu).read_bytes()
            texts[tu] = (old, new)
            maps[tu] = line_map(old, new) if old != new else None
        old, new = texts[tu]
        if maps[tu] is None:
            continue
        out = refresh(record, old, new, maps[tu])
        if out != current_record:
            changed += 1
            records[i] = out
    text = ''.join(json.dumps(r, separators=(',', ':')) + '\n' for r in records)
    print(f'{changed} records refreshed against {args.base}; ledger {"unchanged" if text == current else "differs"}')
    if args.check:
        return 1 if text != current else 0
    (root / LEDGER).write_text(text)
    return 0


if __name__ == '__main__':
    sys.exit(main())
