"""Hash-checked linker-owned words (decision 68c); no payloads in the catalogue.

The container is produced by the disc extractor. Each word is checked and
published atomically before the window linker consumes it. Accounting metadata
without an extractor never supplies build bytes.
"""
from __future__ import annotations
import dataclasses
import hashlib
from pathlib import Path
import tempfile

import linklist


def entries(root, container, start=None, end=None):
    """Canonical emission intervals; reject conflicting/overlapping ownership."""
    found = {}
    for image in linklist.load(root)[0].values():
        if image['container'] != linklist.family(container):
            continue
        for entry in image['entries']:
            if entry.get('kind') not in ('data', 'padding') or not entry.get('extractor'):
                continue
            a, b = entry['foff'], entry['foff'] + entry['size']
            if start is not None and (b <= start or a >= end):
                continue
            if start is not None and not start <= a < b <= end:
                raise ValueError('window cuts a linker-owned word')
            key = (a, b)
            current = dict(entry, path=image['path'])
            if key in found:
                raise ValueError('linker-owned word listed twice')
            found[key] = current
    result = [found[k] for k in sorted(found)]
    if any(a['foff'] + a['size'] > b['foff'] for a, b in zip(result, result[1:])):
        raise ValueError('overlapping linker-owned words')
    return result


def window_files(root, container, start, end):
    base = Path(root).absolute()
    return sorted({Path(e['path']).absolute().relative_to(base).as_posix()
                   for e in entries(root, container, start, end)})


def extract_slice(container, entry, target):
    """Publish one verified extractor slice; a bad hash preserves prior output."""
    target = Path(target)
    with Path(container).open('rb') as stream:
        stream.seek(entry['foff'])
        blob = stream.read(entry['size'])
    if len(blob) != entry['size'] or hashlib.sha256(blob).hexdigest() != entry['sha256']:
        raise ValueError('linker-owned word SHA-256 differs at 0x%X' % entry['foff'])
    target.parent.mkdir(parents=True, exist_ok=True)
    with tempfile.NamedTemporaryFile(dir=target.parent, prefix='.word-', delete=False) as stream:
        temp = Path(stream.name)
        try:
            stream.write(blob)
            stream.close()
            temp.replace(target)
        finally:
            temp.unlink(missing_ok=True)
    return target


def project_segments(segments, container, build_dir, root, family, start, end):
    """Replace only raw gaps with verified data; never cover a compiled payload."""
    emitted = entries(root, family, start, end)
    output = list(segments)
    receipts = []
    symbols = {}
    for entry in emitted:
        a, b = entry['foff'], entry['foff'] + entry['size']
        touched = [s for s in output if s.start < b and a < s.end]
        if len(touched) != 1 or touched[0].kind != 'raw':
            raise ValueError('linker-owned word overlaps a source/module/split payload at 0x%X' % a)
        old = touched[0]
        path = extract_slice(container, entry, Path(build_dir) / ('word_%08x.bin' % a))
        pieces = []
        if old.start < a:
            pieces.append(dataclasses.replace(old, end=a))
        pieces.append(dataclasses.replace(old, start=a, end=b, vram=old.vram + a-old.start,
                                         kind='link_data', name='word_%08x' % a, bytes_path=path))
        if b < old.end:
            pieces.append(dataclasses.replace(old, start=b, vram=old.vram + b-old.start))
        pos = output.index(old)
        output[pos:pos+1] = pieces
        for name, value in entry['symbols'].items():
            value = linklist.num(value)
            if name in symbols and symbols[name] != value:
                raise ValueError('conflicting linker-owned symbol: ' + name)
            symbols[name] = value
        receipts.append(dict(foff=a, size=entry['size'], kind=entry['kind'], sha256=entry['sha256'],
                             symbols=entry['symbols'], verified=True))
    if emitted:
        # Fresh unique sections avoid duplicating a split raw segment's section.
        segments[:] = [dataclasses.replace(s, index=i, section=f'.ovlseg_{i:04d}')
                       if s.kind in ('raw', 'link_data', 'asm') else dataclasses.replace(s, index=i)
                       for i, s in enumerate(output)]
    return dict(entries=receipts, symbols=symbols, bytes=sum(e['size'] for e in receipts))


def write_symbols(receipt, target):
    """Canonical address identities work in both true-base and synthetic mini-links."""
    Path(target).write_text(''.join('%s = 0x%08X;\n' % item
                                  for item in sorted(receipt['symbols'].items())))
