"""Atomic, explicitly unverified staging for data naming cohorts.

The caller must bind complete physical TUs, actual -M header consumers,
allocated object identity, row measurements and final image/window gates.
Staging never claims exactness and never supplies fabricated verifier results.
"""
import csv
import hashlib
import json
from pathlib import Path
import re
import time

NONCODE = re.compile(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'', re.S)
INCLUDE = re.compile(r'(?m)^([ \t]*#[ \t]*include[ \t]*[<"])([^">\n]+)([>"])')

def identifiers(text):
    return re.findall(r'\b[A-Za-z_]\w*\b', NONCODE.sub(' ', text))

def rewrite(text, pattern, mapping):
    parts = []
    offset = 0
    for m in NONCODE.finditer(text):
        parts.append(pattern.sub(lambda h: mapping[h[0]], text[offset:m.start()]))
        parts.append(m[0])
        offset = m.end()
    parts.append(pattern.sub(lambda h: mapping[h[0]], text[offset:]))
    return ''.join(parts)

def inline_plan(root, texts, changed, pattern, mapping):
    """Rebind reviewed inline fragments to the same lines after a spelling edit.

    Original include spellings and the optional inlining newline are restored
    before hashing. A stale original fragment or any edit beyond this map
    refuses; ownership, member order and include provenance stay fixed.
    """
    path = root / 'ledger/layout_inline.jsonl'
    if not path.exists() or not changed:
        return {}, []
    before = path.read_bytes()
    sources = {p.relative_to(root).as_posix(): (texts[p].encode(), text.encode())
               for p, text in changed.items()}
    offsets, updates, output = {}, [], []
    def line_offsets(data):
        return [0] + [m.end() for m in re.finditer(b'\n', data)]
    def restore(piece, tokens):
        text = piece.decode('utf-8')
        if len(INCLUDE.findall(text)) != len(tokens):
            raise ValueError('inline include provenance differs')
        original = iter(tokens)
        return INCLUDE.sub(lambda m: m[1] + next(original) + m[3], text).encode()
    fields = ('offset', 'inlined_bytes', 'bytes', 'source_sha256')
    for raw in before.splitlines(keepends=True):
        if not raw.strip():
            output.append(raw)
            continue
        rec = json.loads(raw)
        name = rec['tu_new']
        if name not in sources:
            output.append(raw)
            continue
        old, new = sources[name]
        if name not in offsets:
            a, b = line_offsets(old), line_offsets(new)
            if len(a) != len(b):
                raise ValueError('inline rewrite changed line count: ' + name)
            offsets[name] = dict(zip(a, b))
        start, end = rec['offset'], rec['offset'] + rec['inlined_bytes']
        if start not in offsets[name] or end not in offsets[name] or end > len(old):
            raise ValueError('stale inline line boundary: ' + rec['member_id'])
        original = restore(old[start:end], rec['original_includes'])
        suffix = original[rec['bytes']:]
        if suffix not in (b'', b'\n') or hashlib.sha256(original[:rec['bytes']]).hexdigest() != rec['source_sha256']:
            raise ValueError('stale inline original hash: ' + rec['member_id'])
        new_start, new_end = offsets[name][start], offsets[name][end]
        current = restore(new[new_start:new_end], rec['original_includes'])
        expected = rewrite(original.decode(), pattern, mapping).encode()
        if current != expected:
            raise ValueError('inline fragment differs beyond the spelling map: ' + rec['member_id'])
        size = len(current) - len(suffix)
        fresh = dict(rec, offset=new_start, inlined_bytes=new_end-new_start,
            bytes=size, source_sha256=hashlib.sha256(current[:size]).hexdigest())
        if fresh == rec:
            output.append(raw)
        else:
            output.append((json.dumps(fresh, separators=(',', ':')) + '\n').encode())
            updates.append(dict(member_id=rec['member_id'], tu=name,
                before={k: rec[k] for k in fields}, after={k: fresh[k] for k in fields}))
    after = b''.join(output)
    return ({path: (before, after)} if after != before else {}), updates

def proposals(path):
    raw = Path(path).read_text()
    first = raw.splitlines()[0].split('\t') if raw else []
    if 'symbol' in first and 'evidence' in first:
        for row in csv.DictReader(raw.splitlines(), delimiter='\t'):
            symbol = row['symbol']
            yield ('0x' + symbol[2:], symbol, row.get('new_name') or row.get('new name'), row['evidence'])
    else:
        for line in raw.splitlines():
            cols = [c.strip() for c in line.split('#', 1)[0].rstrip().split('\t')]
            if len(cols) >= 4 and cols[1]:
                yield tuple(cols[:4])

def main(a, N):
    if not a.rewrite or not a.defer_verification:
        raise ValueError('data batches require --rewrite --defer-verification; this path stages only, and an independent complete-TU proof is mandatory')
    proposed = list(proposals(a.tsv))
    if a.only:
        proposed = [p for p in proposed if p[1] in set(a.only.split(','))]
    if a.limit:
        proposed = proposed[:a.limit]
    if not proposed:
        raise ValueError('empty data batch')
    root = N.ROOT
    paths = sorted(p for folder in ('src', 'include') for p in (root / folder).rglob('*')
                   if p.suffix in ('.c', '.h') and p.is_file())
    if any(p.is_symlink() or p.stat().st_size > 4 * 1024 * 1024 for p in paths):
        raise ValueError('source symlink or oversized source: refuses incomplete inventory')
    texts = {p: p.read_bytes().decode('utf-8') for p in paths}
    idents = {i for t in texts.values() for i in identifiers(t)}
    configured = {r[1]: r[2] for r in N.read_names()}
    taken = set(configured.values())
    mapping = {}
    additions = []
    for addr, old, new, evidence in proposed:
        if not N.DATA_NAME.fullmatch(old) or addr.lower() != '0x' + old[2:].lower():
            raise ValueError('data address mismatch: ' + old)
        if not new or not re.fullmatch(r'[a-z][a-z0-9_]*', new) or not evidence or '\n' in evidence or '\t' in evidence:
            raise ValueError('invalid snake_case name/evidence: ' + old)
        if old in mapping:
            raise ValueError('duplicate original symbol: ' + old)
        if old in configured and configured[old] != new:
            raise ValueError('existing alias differs: ' + old)
        if old not in configured:
            if new in taken or new in idents:
                raise ValueError('identifier collision: ' + new)
            additions.append((addr, old, new, evidence))
        if old not in idents and new not in idents:
            raise ValueError('symbol has no source consumer: ' + old)
        if new in mapping.values():
            raise ValueError('non-injective data map: ' + new)
        mapping[old] = new
        taken.add(new)
    pattern = re.compile(r'\b(?:' + '|'.join(map(re.escape, mapping)) + r')\b')
    changed = {p: rewrite(t, pattern, mapping) for p, t in texts.items() if pattern.search(t)}
    changed = {p: t for p, t in changed.items() if t != texts[p]}
    guards = [{'path': p.relative_to(root).as_posix(),
               'before_sha256': hashlib.sha256(texts[p].encode()).hexdigest(),
               'after_sha256': hashlib.sha256(t.encode()).hexdigest()}
              for p, t in changed.items()]
    metadata, rebases = inline_plan(root, texts, changed, pattern, mapping)
    metadata_guards = [{'path': p.relative_to(root).as_posix(),
        'before_sha256': hashlib.sha256(pair[0]).hexdigest(),
        'after_sha256': hashlib.sha256(pair[1]).hexdigest()}
        for p, pair in metadata.items()]
    plan = {'status': 'UNVERIFIED', 'new_aliases': len(additions), 'files': guards,
            'metadata_files': metadata_guards, 'inline_rebases': rebases,
            'map': mapping, 'required': 'complete-TU object and dependency proof, row verification, final scoped gate and SLUS SHA-1'}
    print(f'data batch: {len(additions)} new aliases; {len(changed)} physical files; UNVERIFIED staging', flush=True)
    if a.dry_run:
        return plan
    names_before = N.NAMES.read_bytes()
    journal_before = N.JOURNAL.read_bytes() if N.JOURNAL.exists() else None
    try:
        N.NAMES.write_bytes(names_before.rstrip(b'\n') + b'\n' + ''.join('\t'.join(r) + '\n' for r in additions).encode())
        for p, t in changed.items():
            p.write_bytes(t.encode())
        for p, pair in metadata.items():
            p.write_bytes(pair[1])
        for addr, old, new, evidence in additions:
            N.append_jsonl(N.JOURNAL, dict(addr=addr, old=old, new=new, evidence=evidence,
                outcome='staged-unverified', data_batch=True,
                at=time.strftime('%Y-%m-%dT%H:%M:%SZ', time.gmtime())))
        if a.proof_log:
            Path(a.proof_log).write_text(json.dumps(plan, indent=2) + '\n')
    except BaseException:
        for p in changed:
            p.write_bytes(texts[p].encode())
        for p, pair in metadata.items():
            p.write_bytes(pair[0])
        N.NAMES.write_bytes(names_before)
        if journal_before is None:
            N.JOURNAL.unlink(missing_ok=True)
        else:
            N.JOURNAL.write_bytes(journal_before)
        raise
    return plan
