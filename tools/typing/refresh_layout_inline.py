#!/usr/bin/env python3
"""Refresh ledger/layout_inline.jsonl after source edits to merged (LL7) TUs.

A layout_inline record locates one member's own text inside its merged TU (offset, inlined_bytes) and
binds it with source_sha256 over that text with the member's original #include tokens restored.  Any
edit to a merged TU (typing, naming, declarations) moves those extents.  This tool diffs every merged TU
against its text at --base (a git revision), maps each record's extent through the line diff, maps the
known includes back to their original tokens, records new includes verbatim, and rewrites the ledger.

  python3 tools/typing/refresh_layout_inline.py --root . --base HEAD [--check]

--check reports how many records would change and exits 1 if any would, without writing.

Self-healing (a lane that committed its sources but not the refreshed ledger): every record is bound to
the text it describes by `source_sha256`, so a record is never mapped from a text it does not verify
against.  Per merged TU the refresh takes, in order:
  1. the working-tree record when it already verifies against the current text (already fresh);
  2. the first (record, text) pair that verifies, over the working-tree and --base records and the TU's text
     at --base, then at each earlier revision that changed the TU (`git rev-list --first-parent`, at most
     --max-walk), and maps it to the current text.
A TU renamed since --base (git mv after a function rename) is paired with the member's one --base record whose
TU path no longer exists, and its --base text is read from that old path.
A TU none of whose candidates verify stops the refresh with the member, the TU and the revisions tried
(never a KeyError from a stale extent).  `stale_records(root, rev)` lists the records of a revision whose
ledger does not describe its own text (affected.py accepts their repair on unedited TUs).
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


class StaleRecord(Exception):
    """No candidate (record, text) pair verifies for a merged TU."""


def restored_own(record, text):
    """The member's own bytes as `record` locates them in `text`, original #include tokens restored; None when
    the extent does not fit the text or its include count differs from the record's."""
    start, size = record.get('offset'), record.get('inlined_bytes')
    if not isinstance(start, int) or not isinstance(size, int) or start < 0 or start + size > len(text):
        return None
    piece = text[start:start + size]
    tokens = record.get('original_includes') or []
    if len(INCLUDE.findall(piece)) != len(tokens):
        return None
    it = iter(tokens)
    restored = INCLUDE.sub(lambda m: m[1] + next(it).encode() + m[3], piece)
    return restored[:record['bytes']]


def verifies(record, text):
    """True when `record` describes `text`: its extent's own bytes hash to its source_sha256."""
    own = restored_own(record, text)
    return own is not None and hashlib.sha256(own).hexdigest() == record.get('source_sha256')


def line_starts_ok(record, text):
    """The extent starts and ends on line boundaries of `text` (line_map maps line starts only)."""
    starts = {0}
    pos = 0
    for line in text.splitlines(True):
        pos += len(line)
        starts.add(pos)
    return record['offset'] in starts and record['offset'] + record['inlined_bytes'] in starts


def history(root, rev, rel, limit):
    """Revisions before `rev` (first parent) that changed `rel`, newest first, at most `limit`."""
    res = subprocess.run(['git', '-C', str(root), 'rev-list', '--first-parent', '-n', str(limit + 1), rev, '--', rel],
                         capture_output=True, text=True)
    revs = res.stdout.split() if res.returncode == 0 else []
    head = subprocess.run(['git', '-C', str(root), 'rev-parse', rev], capture_output=True, text=True).stdout.strip()
    # rev-list includes `rev` itself when it changed `rel`; its text is tried first anyway.
    return [r for r in revs if r != head][:limit]


def text_at(root, rev, rel, cache):
    key = (rev, rel)
    if key not in cache:
        try:
            cache[key] = git_show(root, rev, rel)
        except subprocess.CalledProcessError:
            cache[key] = None
    return cache[key]


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


def stale_records(root, rev):
    """{(member_id, tu_new)} of the records in `rev`'s ledger that do not describe `rev`'s own text of their TU."""
    blob = git_show(root, rev, LEDGER).decode()
    cache, out = {}, set()
    for line in blob.splitlines():
        if not line.strip():
            continue
        r = json.loads(line)
        text = text_at(root, rev, r['tu_new'], cache)
        if text is not None and not verifies(r, text):
            out.add((r['member_id'], r['tu_new']))
    return out


def choose_source(root, base, tu, candidates, new, cache, max_walk):
    """(record_by_member, old_text) for one TU: the candidate record set and the text it describes.

    `candidates` is a list of {member_id: record} sets for this TU (working tree first, then --base).
    The --base text is tried first, then earlier revisions that changed the TU."""
    tried = []

    def revisions():
        yield base
        yield from history(root, base, tu, max_walk)
    for rev in revisions():
        tried.append(rev if rev == base else rev[:12])
        old = text_at(root, rev, tu, cache)
        if old is None:
            continue
        for recs in candidates:
            if recs and all(verifies(r, old) and line_starts_ok(r, old) for r in recs.values()):
                return recs, old, rev
    members = sorted({m for recs in candidates for m in recs})
    raise StaleRecord('%s: no ledger record set verifies against its text at %s (members %s); the ledger was '
                      'edited by hand or the TU history is not in this repository' % (tu, ', '.join(tried), ', '.join(members[:4])))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default='.')
    ap.add_argument('--base', required=True, help='git revision whose text the current records describe')
    ap.add_argument('--check', action='store_true')
    ap.add_argument('--max-walk', type=int, default=20, help='earlier revisions of a TU tried when no record set '
                    'verifies against its --base text (default 20)')
    args = ap.parse_args()
    root = Path(args.root)
    base_ledger = git_show(root, args.base, LEDGER).decode()
    base_records = [json.loads(line) for line in base_ledger.splitlines() if line.strip()]
    current = (root / LEDGER).read_text()
    records = [json.loads(line) for line in current.splitlines() if line.strip()]
    base_by_key = {(r['member_id'], r['tu_new']): r for r in base_records}
    # Installs since --base add records and may retire old TUs. Refresh only surviving baseline records,
    # retaining the current ledger's full roster.
    by_tu = {}
    renamed = {}                                            # TU path now -> its path at --base
    base_by_member = {}
    for r in base_records:
        base_by_member.setdefault(r['member_id'], []).append(r)
    for i, cur in enumerate(records):
        key = (cur['member_id'], cur['tu_new'])
        if key not in base_by_key:
            # A TU renamed since --base (a file named after a renamed function): the member's one --base record
            # whose TU no longer exists describes the old path's text.
            gone = [r for r in base_by_member.get(cur['member_id'], ()) if not (root / r['tu_new']).exists()]
            if len(gone) != 1 or renamed.get(cur['tu_new'], gone[0]['tu_new']) != gone[0]['tu_new']:
                continue
            renamed[cur['tu_new']] = gone[0]['tu_new']
            base_by_key[key] = gone[0]
        by_tu.setdefault(cur['tu_new'], []).append(i)
    cache, changed, healed = {}, 0, []
    try:
        for tu, idxs in by_tu.items():
            new = (root / tu).read_bytes()
            work = {records[i]['member_id']: records[i] for i in idxs}
            base = {records[i]['member_id']: base_by_key[(records[i]['member_id'], tu)] for i in idxs}
            if all(verifies(r, new) for r in work.values()):
                continue                                    # already describes the current text
            recs, old, rev = choose_source(root, args.base, renamed.get(tu, tu), [work, base], new, cache,
                                           args.max_walk)
            if recs != base or rev != args.base:
                healed.append('%s (from %s %s)' % (tu, 'working-tree records' if recs is work else 'base records',
                                                   'at base' if rev == args.base else 'at ' + rev[:12]))
            mp = line_map(old, new) if old != new else None
            for i in idxs:
                record = recs[records[i]['member_id']]
                out = refresh(record, old, new, mp) if mp else dict(record)
                out['tu_new'] = tu
                if out != records[i]:
                    changed += 1
                    records[i] = out
    except StaleRecord as exc:
        print('refresh_layout_inline: ' + str(exc), file=sys.stderr)
        return 2
    text = ''.join(json.dumps(r, separators=(',', ':')) + '\n' for r in records)
    for line in healed:
        print('healed: ' + line)
    print(f'{changed} records refreshed against {args.base}; ledger {"unchanged" if text == current else "differs"}'
          + (f'; {len(healed)} TUs healed (ledger was not committed with an earlier batch)' if healed else ''))
    if args.check:
        return 1 if text != current else 0
    (root / LEDGER).write_text(text)
    return 0


if __name__ == '__main__':
    sys.exit(main())
