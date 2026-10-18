"""Lossless compact TSV storage for validated linklist.v1 documents.

One interval per line; repeated metadata attributes live in per-image profiles.
Rules remain readable IDs in every metadata row. No retail bytes are stored.
"""
from __future__ import annotations
import json
import re
from pathlib import Path

SCHEMA = 'azure-clean.bytemap.tsv.v1'
COLUMNS = 'o\tn\tk\tr\th\tx\n'
MAX_BYTES = 2_000_000
PART_BYTES = 1_500_000
LABELS = ('proven_code', 'library_code', 'strongly_code', 'proven_data',
          'noncode_typing_pending', 'padding_leftover', 'unknown')
HEADER = dict(image='i', container='c', foff='o', size='n', vma='v', layout='l',
              evidence='e', symbols='y', census='t', provenance='p')
KINDS = dict(code_region='r', data='d', asset='a', padding='p', leftover='l',
             unresolved='u', image='i')


def compact(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=True)


def invert(mapping):
    return {v: k for k, v in mapping.items()}


def encode_header(doc):
    out = {HEADER[k]: v for k, v in doc.items() if k not in ('schema', 'entries')}
    out['t'] = [doc['census'][k] for k in LABELS]
    if 'provenance' in doc:
        p = doc['provenance']
        out['p'] = [p['labels_sha256'], p['coverage_sha256'], p['source']]
    return out


def decode_header(value):
    if set(value) - set(HEADER.values()):
        raise ValueError('unknown compact header keys')
    out = {invert(HEADER)[k]: v for k, v in value.items()}
    if not re.fullmatch(r'[a-z][a-z0-9_]*/[A-Za-z0-9_]+', out.get('image', '')):
        raise ValueError('unsafe compact image identity')
    if not isinstance(out['census'], list) or len(out['census']) != len(LABELS):
        raise ValueError('invalid compact census totals')
    out['census'] = dict(zip(LABELS, out['census']))
    if 'provenance' in out:
        p = out['provenance']
        if not isinstance(p, list) or len(p) != 3:
            raise ValueError('invalid compact provenance')
        out['provenance'] = dict(zip(('labels_sha256', 'coverage_sha256', 'source'), p))
    return dict(out, schema='azure-clean.linklist.v1')


def encode(doc):
    profiles, by_profile, rows = [], {}, []
    def profile(extra):
        signature = compact(extra)
        if signature not in by_profile:
            by_profile[signature] = len(profiles)
            profiles.append(extra)
        return by_profile[signature]
    def short_id(value):
        prefix = doc['container']+'/'
        return value[len(prefix):] if value.startswith(prefix) else value
    for e in doc['entries']:
        o, n = e['foff'], e['size']
        # The TU path convention is lossless; exceptions remain explicit profiles.
        if 'kind' not in e:
            extra = {k:v for k,v in e.items() if k not in ('row','home','tu','vma','foff','size')}
            if 'work/' in str(extra.get('evidence', '')):
                extra['evidence'] = {'from':'config/link/'+doc['image']+'.json'}
            if e['tu'] != 'src/'+e['home']+'.c':
                extra['tu'] = e['tu']
            values = [short_id(e['row']), None if e['home'] == e['row'] else short_id(e['home']),
                      e['vma'], profile(extra)]
            rows.append([compact(o), compact(n), 'c', 'census:registered_tu', '', compact(values)])
            continue
        extra = {k: v for k, v in e.items() if k not in ('kind', 'foff', 'size', 'evidence', 'sha256')}
        rows.append([compact(o), compact(n), KINDS[e['kind']], e['evidence'],
                     e.get('sha256', ''), str(profile(extra))])
    text_rows = []
    for row in rows:
        if any('\t' in v or '\n' in v or '\r' in v for v in row):
            raise ValueError('tab/newline in compact interval')
        text_rows.append('\t'.join(row)+'\n')
    groups, current, length = [], [], 0
    for row in text_rows:
        if current and length + len(row.encode()) > PART_BYTES:
            groups.append(current); current, length = [], 0
        current.append(row); length += len(row.encode())
    if current:
        groups.append(current)
    result = []
    for part, rows in enumerate(groups):
        header = dict(s=SCHEMA, d=encode_header(doc), p=profiles, a=part, z=len(groups))
        blob = ('#'+compact(header)+'\n'+COLUMNS+''.join(rows)).encode()
        if len(blob) > MAX_BYTES:
            raise ValueError('compact map part exceeds 2 MB')
        result.append(blob)
    return result


def write(directory, doc):
    directory = Path(directory)
    directory.mkdir(parents=True, exist_ok=True)
    name = doc['image'].split('/')[1]
    blobs = encode(doc)
    paths = []
    for i, blob in enumerate(blobs):
        suffix = '' if len(blobs) == 1 else '.%03d' % i
        path = directory/(name+suffix+'.tsv')
        path.write_bytes(blob); paths.append(path)
    return paths


def read_parts(paths, source_root=None):
    """Decode and reassemble exactly one image; refuse missing/reordered parts."""
    doc, profiles, entries, count = None, None, [], None
    paths = sorted(map(Path, paths))
    inherited = None
    for index, path in enumerate(paths):
        if path.stat().st_size > MAX_BYTES:
            raise ValueError('compact map part exceeds 2 MB')
        with path.open() as f:
            first = f.readline()
            if not first.startswith('#'):
                raise ValueError('missing compact map header')
            h = json.loads(first[1:])
            if set(h) != {'s', 'd', 'p', 'a', 'z'} or h['s'] != SCHEMA:
                raise ValueError('invalid compact map header')
            if doc is None:
                doc, profiles, count = decode_header(h['d']), h['p'], h['z']
            if type(h['a']) is not int or type(h['z']) is not int or h['a'] != index or h['z'] != len(paths):
                raise ValueError('missing/duplicate compact map part')
            if decode_header(h['d']) != doc or h['p'] != profiles or h['z'] != count:
                raise ValueError('compact parts disagree on image metadata')
            if f.readline() != COLUMNS:
                raise ValueError('invalid compact map columns')
            for line in f:
                values = line.rstrip('\n').split('\t')
                if len(values) != 6:
                    raise ValueError('invalid compact interval columns')
                o, n, k, r, sha, x = values
                entry = dict(foff=json.loads(o), size=json.loads(n))
                if k == 'c':
                    if r != 'census:registered_tu' or sha:
                        raise ValueError('invalid compact TU rule/hash')
                    values = json.loads(x)
                    if not isinstance(values, list) or len(values) != 4:
                        raise ValueError('invalid compact TU tuple')
                    row, home, vma, at = values
                    if type(at) is not int or not 0 <= at < len(profiles):
                        raise ValueError('invalid compact TU profile')
                    def full_id(value):
                        if not isinstance(value, str) or not value:
                            raise ValueError('invalid compact TU identity')
                        return value if '/' in value else doc['container']+'/'+value
                    row = full_id(row)
                    home = row if home is None else full_id(home)
                    extra = profiles[at]
                    if set(extra) - {'tu', 'bindings', 'evidence'}:
                        raise ValueError('unknown compact TU profile keys')
                    entry.update(row=row, home=home, vma=vma, tu='src/'+home+'.c')
                    entry.update(extra)
                    if isinstance(entry.get('evidence'), dict):
                        expected = 'config/link/'+doc['image']+'.json'
                        if entry['evidence'] != {'from':expected} or source_root is None:
                            raise ValueError('TU evidence reference needs its committed source root')
                        if inherited is None:
                            original = json.loads((Path(source_root)/expected).read_text())
                            inherited = {e['row']:e for e in original['entries'] if 'kind' not in e}
                        entry['evidence'] = inherited[row]['evidence']
                else:
                    if k not in invert(KINDS) or not x.isdecimal() or int(x) >= len(profiles):
                        raise ValueError('invalid compact kind/profile')
                    extra = profiles[int(x)]
                    if set(extra) & {'kind', 'foff', 'size', 'evidence', 'sha256'}:
                        raise ValueError('compact profile overwrites interval identity')
                    entry.update(extra, kind=invert(KINDS)[k], evidence=r)
                    if sha:
                        entry['sha256'] = sha
                entries.append(entry)
    if doc is None:
        raise ValueError('empty compact image')
    return dict(doc, entries=entries)


def load_documents(directory, source_root=None):
    groups = {}
    for path in sorted(Path(directory).glob('*/*.tsv')):
        name = path.stem.split('.')[0]
        groups.setdefault((path.parent.name, name), []).append(path)
    docs = []
    for (container, name), paths in sorted(groups.items()):
        doc = read_parts(paths, source_root)
        if doc['image'] != container+'/'+name or doc['container'] != container:
            raise ValueError('compact map lives outside its container/image path')
        docs.append((doc, str(paths[0])))
    return docs
