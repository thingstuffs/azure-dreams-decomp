#!/usr/bin/env python3
"""Lossless link-list projection from a declarative graph (no authority switch).

Bootstrap once from the current checkout with ``capture``; ``generate`` reads only
that graph. JSONL shards separate physical files, load views, TU homes, ordered
placements/intervals and symbol owners. Numeric spellings and optional-field
presence survive projection; sorted JSON keys are the comparison contract.
"""
from __future__ import annotations

import argparse
from collections import Counter
from copy import deepcopy
import hashlib
import json
from pathlib import Path, PurePosixPath
import re
import sys

ROOT = Path(__file__).resolve().parents[2]
SCHEMA = 'azure-clean.link-graph.v1'
LIMIT = 1_900_000
KINDS = {'tu', 'unresolved', 'padding', 'code_region', 'data', 'asset', 'image', 'leftover'}
TABLES = ('files', 'views', 'tus', 'entries', 'owners')
DISC = {'main': 'MAIN/MAIN.BIN', 'town': 'TOWN/TOWN.BIN',
        'dungeon': 'DUNGEON/DUNGEON.BIN', 'ovmovie': 'OVMOVIE.BIN', 'slus': 'SLUS_006.14'}
# Selection is a diagnostic build plan, not a claim that these are all load phases.
SLICE = [('main/main_bin', 'main_boot'),
         ('town/image_3ef000', 'town_cohort_3ef1c8'),
         ('town/image_437800', 'town_ll34_439000_truebase_80017800'),
         ('town/image_49e800', 'town_ll34_49ffe4_truebase_800177e4'),
         ('dungeon/bank_9b9000', 'dungeon_deep_9b9060_truebase_8014c860'),
         ('dungeon/bank_9e3000', 'dungeon_deep_9e3294_truebase_8014ca94'),
         ('dungeon/bank_a0d000', 'dungeon_deep_a0d054_truebase_8014c854')]


def canonical(value):
    return json.dumps(value, sort_keys=True, separators=(',', ':'), ensure_ascii=True)


def digest(value):
    return hashlib.sha256(value).hexdigest()


def number(value):
    if type(value) is int:
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise ValueError('expected integer or base-prefixed integer string')


def safe(value):
    p = PurePosixPath(value)
    if (not value or str(p) != value or p.is_absolute() or '..' in p.parts
            or '\\' in value or any(c in value for c in '\n\r\t"')):
        raise ValueError('unsafe relative path: ' + str(value))
    return value


def write_json(path, value):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, sort_keys=True, indent=2) + '\n')


def records(path):
    return [json.loads(line) for line in Path(path).read_text().splitlines() if line.strip()]


def key_order(value):
    """Object-key traversal for the census provenance's byte-hashed inputs."""
    if isinstance(value, dict):
        return [list(value), {k: key_order(v) for k, v in value.items()
                             if isinstance(v, (dict, list))}]
    if isinstance(value, list):
        return [key_order(v) if isinstance(v, (dict, list)) else None for v in value]
    return None


def ordered(value, order):
    if isinstance(value, dict):
        keys, children = order
        if set(keys) != set(value) or len(keys) != len(value):
            raise ValueError('serialization keys disagree with graph projection')
        return {k: ordered(value[k], children[k]) if k in children else value[k] for k in keys}
    if isinstance(value, list):
        if len(value) != len(order):
            raise ValueError('serialization array length changed')
        return [ordered(v, o) if o is not None else v for v, o in zip(value, order)]
    return value


def shard(directory, name, values):
    out, block, size = [], [], 0
    def flush():
        path = directory / f'{name}.{len(out):03}.jsonl'
        path.write_text(''.join(block))
        out.append({'path': path.name, 'sha256': digest(path.read_bytes()), 'records': len(block)})
    for value in values:
        line = canonical(value) + '\n'
        length = len(line.encode())
        if length >= LIMIT:
            raise ValueError('single graph record exceeds shard limit')
        if size + length >= LIMIT and block:
            flush()
            block, size = [], 0
        block.append(line)
        size += length
    if block:
        flush()
    return out


def capture(root, directory):
    """Migration input: current lists + current ledger/source facts; no old TSVs."""
    root, directory = Path(root).resolve(), Path(directory).resolve()
    if directory.exists() and any(directory.iterdir()):
        raise ValueError('capture requires a new or empty graph directory')
    directory.mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(root / 'tools'))
    from gate import linklist
    from gate.source_layout import row_relative
    registry = {r['id']: r for r in records(root / 'ledger/rows.jsonl')}
    tables = {k: [] for k in TABLES}
    for r in records(root / 'ledger/containers.jsonl'):
        c = r['container']
        tables['files'].append({'id': c, 'disc_path': DISC[c], 'size': r['bytes'],
                                'sha1': r['retail_sha1'], 'evidence': 'ledger/containers.jsonl'})
    slus = root / 'baserom/slus_006.14'
    tables['files'].append({'id': 'slus', 'disc_path': DISC['slus'], 'size': slus.stat().st_size,
                            'sha1': hashlib.sha1(slus.read_bytes()).hexdigest(),
                            'evidence': 'config/slus_006.14.sha1'})
    tus = {}
    sources = {}
    for path in sorted((root / 'config/link').glob('*/*.json')):
        doc = json.loads(path.read_text())
        linklist.validate_image(doc, path.relative_to(root))
        image = doc['image']
        if path.relative_to(root / 'config/link').as_posix() != image + '.json':
            raise ValueError('image/file identity mismatch')
        view = {'id': image, 'file': doc['container'], 'phase': 'view:' + image,
                'attributes': {k: v for k, v in doc.items() if k not in ('image', 'container', 'entries', 'symbols')}}
        styles = [n for n in (1, 2, 4) if json.dumps(doc, indent=n) + '\n' == path.read_text()]
        if not styles:
            raise ValueError('unsupported census-hashed JSON serialization')
        view['serialization'] = {'indent': styles[0], 'order': key_order(doc),
                                 'sha256': digest(path.read_bytes())}
        def owners(scope, values, kind='address_witness'):
            ids = []
            for symbol, address in sorted(values.items()):
                oid = scope + '::' + symbol
                tables['owners'].append({'id': oid, 'scope': scope, 'symbol': symbol,
                                         'address': address, 'kind': kind})
                ids.append(oid)
            return ids
        if 'symbols' in doc:
            view['symbol_owners'] = owners(image, doc['symbols'])
        tables['views'].append(view)
        for index, raw in enumerate(doc['entries']):
            eid = image + '@' + str(index)
            entry = {'id': eid, 'view': image, 'order': index,
                     'kind': raw.get('kind', 'tu'),
                     'attributes': {k: v for k, v in raw.items() if k not in ('tu', 'home', 'symbols')}}
            if 'tu' in raw:
                home, source = raw['home'], safe(raw['tu'])
                if home not in registry or row_relative(home, root) != source or not (root / source).is_file():
                    raise ValueError('TU home/source disagrees with current ledger: ' + home)
                if home in tus and tus[home]['source'] != source:
                    raise ValueError('conflicting TU home paths: ' + home)
                if source not in sources:
                    sources[source] = digest((root / source).read_bytes())
                recipe = {k: registry[home][k] for k in ('cfg', 'row_asflags', 'gate_config') if k in registry[home]}
                tus[home] = {'id': home, 'source': source, 'source_sha256': sources[source], 'recipe_witness': recipe}
                entry['tu'] = home
            if 'symbols' in raw:
                entry['symbol_owners'] = owners(eid, raw['symbols'], 'linker_word')
            tables['entries'].append(entry)
    # Include native rows outside sparse placement lists: MAIN and SLUS source
    # objects still need a home identity in the combined-link namespace. Inlined
    # rows can share one physical source; a complete module has its own identity.
    for rid, row in sorted(registry.items()):
        if row.get('source_row') or rid in tus:
            continue
        source = row_relative(row, root)
        if not (root / source).is_file():
            raise ValueError('registered source absent: ' + rid)
        if source not in sources:
            sources[source] = digest((root / source).read_bytes())
        tus[rid] = {'id': rid, 'source': source, 'source_sha256': sources[source],
                    'recipe_witness': {k: row[k] for k in ('cfg', 'row_asflags', 'gate_config') if k in row}}
    for module in json.loads((root / 'config/overlays/modules.json').read_text())['modules']:
        source = safe(module['source'])
        tus['module/' + module['key']] = {'id': 'module/' + module['key'], 'source': source,
            'source_sha256': digest((root / source).read_bytes()), 'recipe_witness': module['recipe']}
        if module.get('allocation_model'):
            tus['module/' + module['key']].update(allocation_model=module['allocation_model'],
                allocations=[{k:a[k] for k in ('section','foff','vma','size','link_alignment')}
                             for a in module['allocations']])
    tables['tus'] = [tus[k] for k in sorted(tus)]
    base = (root / 'SCRATCH_HEAD').read_text().strip() if (root / 'SCRATCH_HEAD').exists() else 'unspecified'
    manifest = {'schema': SCHEMA, 'base': base, 'tables': {},
                'build': {'slus': {'file': 'slus', 'image': 'slus/slus_bin',
                                    'recipe': 'build_slus/build/slus_006.14_ordered.ld',
                                    'ninja': 'build_slus/build.ninja',
                                    'elf': 'build_slus/build/slus_006.14.elf',
                                    'binary': 'build_slus/build/slus_006.14',
                                    'sections': ['.header', '._800']},
                          'slice': [{'view': image, 'window': window} for image, window in SLICE],
                          'extensions': [{'file': 'ovmovie', 'view': 'ovmovie/ovmovie_bin', 'window': 'ovmovie'}]},
                'inputs': {p: digest((root / p).read_bytes()) for p in
                           ('ledger/rows.jsonl', 'ledger/layout.jsonl', 'ledger/layout_inline.jsonl',
                            'ledger/containers.jsonl', 'ledger/splits/slus.jsonl', 'config/overlays/modules.json',
                            'ledger/instance_load_regions.jsonl')}}
    for name in TABLES:
        manifest['tables'][name] = shard(directory, name, tables[name])
    write_json(directory / 'graph.json', manifest)
    graph = Graph(directory)
    graph.documents(validate=True)
    return graph.stats()


class Graph:
    def __init__(self, directory):
        self.directory = Path(directory).resolve()
        self.manifest = json.loads((self.directory / 'graph.json').read_text())
        if self.manifest.get('schema') != SCHEMA or set(self.manifest.get('tables', {})) != set(TABLES):
            raise ValueError('unsupported graph schema/tables')
        for name in TABLES:
            values = []
            seen_parts = set()
            for part in self.manifest['tables'][name]:
                rel = safe(part['path'])
                if rel in seen_parts:
                    raise ValueError('duplicate graph shard')
                seen_parts.add(rel)
                path = self.directory / rel
                if not path.resolve().is_relative_to(self.directory) or path.stat().st_size >= 2_000_000:
                    raise ValueError('unsafe or oversize graph shard')
                if digest(path.read_bytes()) != part['sha256']:
                    raise ValueError('graph shard hash mismatch: ' + rel)
                block = records(path)
                if len(block) != part['records']:
                    raise ValueError('graph shard record count mismatch')
                values.extend(block)
            indexed = {r['id']: r for r in values}
            if len(indexed) != len(values):
                raise ValueError('duplicate graph ' + name + ' identity')
            setattr(self, name, indexed)
        self._validate()

    def _validate(self):
        for f in self.files.values():
            safe(f['disc_path'])
            if number(f['size']) <= 0:
                raise ValueError('empty physical file')
        for tu in self.tus.values():
            if not safe(tu['source']).startswith('src/'):
                raise ValueError('TU source outside src')
        for view in self.views.values():
            safe(view['id'])
            if view['file'] not in self.files or view['phase'] != 'view:' + view['id']:
                raise ValueError('unknown physical file/phase')
            if set(view['attributes']) & {'image', 'container', 'entries', 'symbols'}:
                raise ValueError('duplicate view authority')
            a = view['attributes']
            if number(a['foff']) < 0 or number(a['foff']) + number(a['size']) > number(self.files[view['file']]['size']):
                raise ValueError('view outside physical file')
        for entry in self.entries.values():
            if entry['view'] not in self.views or type(entry['order']) is not int or entry['order'] < 0:
                raise ValueError('unknown view or invalid entry order')
            if entry['id'] != entry['view'] + '@' + str(entry['order']):
                raise ValueError('entry identity/order mismatch')
            if entry['kind'] not in KINDS:
                raise ValueError('unsupported entry kind')
            if set(entry['attributes']) & {'tu', 'home', 'symbols'}:
                raise ValueError('duplicate entry authority')
            if entry['kind'] == 'tu':
                if entry.get('tu') not in self.tus or 'kind' in entry['attributes']:
                    raise ValueError('unknown TU or conflicting kind')
            elif entry['attributes'].get('kind') != entry['kind'] or 'tu' in entry:
                raise ValueError('metadata kind disagreement')
        used = set()
        for scope in [*self.views.values(), *self.entries.values()]:
            names = set()
            for oid in scope.get('symbol_owners', []):
                owner = self.owners.get(oid)
                if owner is None or owner['scope'] != scope['id'] or oid in used:
                    raise ValueError('unknown, duplicate or cross-scope symbol owner')
                if owner['kind'] not in ('address_witness', 'linker_word') or owner['symbol'] in names:
                    raise ValueError('unsupported or duplicate symbol owner')
                if owner['kind'] == 'linker_word' and (scope['id'] not in self.entries
                        or scope['kind'] not in ('data', 'padding')
                        or not {'sha256', 'extractor'} <= scope['attributes'].keys()):
                    raise ValueError('linker-word owner lacks an emitting extent')
                names.add(owner['symbol'])
                used.add(oid)
        if used != self.owners.keys():
            raise ValueError('orphan symbol owner')

    def documents(self, validate=False):
        grouped = {v: [] for v in self.views}
        for entry in self.entries.values():
            grouped[entry['view']].append(entry)
        def restore_symbols(record, out):
            if 'symbol_owners' in record:
                out['symbols'] = {self.owners[o]['symbol']: self.owners[o]['address'] for o in record['symbol_owners']}
        documents = {}
        for image, view in sorted(self.views.items()):
            doc = dict(deepcopy(view['attributes']), image=image, container=view['file'], entries=[])
            restore_symbols(view, doc)
            for order, record in enumerate(sorted(grouped[image], key=lambda r: r['order'])):
                if record['order'] != order:
                    raise ValueError('missing or duplicate entry order in ' + image)
                entry = deepcopy(record['attributes'])
                if record['kind'] == 'tu':
                    entry.update(home=record['tu'], tu=self.tus[record['tu']]['source'])
                restore_symbols(record, entry)
                doc['entries'].append(entry)
            documents[image] = doc
        if validate:
            sys.path.insert(0, str(ROOT / 'tools'))
            from gate import linklist
            images = {i: linklist.validate_image(d, i) for i, d in documents.items()}
            linklist.coverage(images)
        return documents

    def stats(self):
        return {'schema': SCHEMA, 'base': self.manifest['base'],
                'identities': {k: len(getattr(self, k)) for k in TABLES},
                'placement_homes': len({e['tu'] for e in self.entries.values() if e['kind'] == 'tu'}),
                'list_schemas': dict(sorted(Counter(v['attributes']['schema'] for v in self.views.values()).items())),
                'owners_by_kind': dict(sorted(Counter(o['kind'] for o in self.owners.values()).items())),
                'entries_by_kind': dict(sorted(Counter(e['kind'] for e in self.entries.values()).items()))}

    def verify_sources(self, root):
        root = Path(root).resolve()
        checked = set()
        for tu in self.tus.values():
            path = root / tu['source']
            if (tu['source'], tu['source_sha256']) in checked:
                continue
            if not path.resolve().is_relative_to(root) or digest(path.read_bytes()) != tu['source_sha256']:
                raise ValueError('TU source witness changed: ' + tu['id'])
            checked.add((tu['source'], tu['source_sha256']))

    def verify_inputs(self, root):
        """Witnesses for adapting external build artifacts, not list generation."""
        root = Path(root).resolve()
        for name, expected in self.manifest.get('inputs', {}).items():
            path = root / safe(name)
            if not path.resolve().is_relative_to(root) or digest(path.read_bytes()) != expected:
                raise ValueError('graph input witness changed: ' + name)

    def generate(self, output):
        output = Path(output).resolve()
        # Protect authority in this checkout even when explicitly named as output.
        if output == ROOT / 'config/link' or (ROOT / 'config/link') in output.parents:
            raise ValueError('no authority switch: use a scratch output')
        docs = self.documents(validate=True)
        if output.exists() and any(output.iterdir()):
            raise ValueError('generation requires a new or empty output directory')
        for image, doc in docs.items():
            path = output / (safe(image) + '.json')
            style = self.views[image].get('serialization')
            if style:
                text = json.dumps(ordered(doc, style['order']), indent=style['indent']) + '\n'
                if digest(text.encode()) != style['sha256']:
                    raise ValueError('census input byte identity changed: ' + image)
                path.parent.mkdir(parents=True, exist_ok=True)
                path.write_text(text)
            else:
                write_json(path, doc)
        return self.stats()


def compare(graph, catalogue):
    """Compare full file sets and canonical JSON; classify every held list by kind."""
    docs = graph.documents(validate=True)
    expected = {p.relative_to(catalogue).as_posix()[:-5]: json.loads(p.read_text())
                for p in Path(catalogue).glob('*/*.json')}
    holds, held_kinds = [], Counter()
    for image in sorted(docs.keys() | expected.keys()):
        actual, want = docs.get(image), expected.get(image)
        if canonical(actual) == canonical(want):
            continue
        kinds = set()
        if actual is None or want is None:
            kinds.add('list')
            why = 'missing or extra image'
        else:
            why = 'canonical JSON differs'
            if canonical({k:v for k,v in actual.items() if k != 'entries'}) != canonical({k:v for k,v in want.items() if k != 'entries'}):
                kinds.add('list')
            ae, we = actual['entries'], want['entries']
            for n in range(max(len(ae), len(we))):
                a, w = ae[n] if n < len(ae) else None, we[n] if n < len(we) else None
                if canonical(a) != canonical(w):
                    kinds.update(e.get('kind', 'tu') for e in (a,w) if e is not None)
        for kind in sorted(kinds):
            holds.append({'image': image, 'kind': kind, 'reason': why})
            held_kinds[kind] += 1
    total = len(docs.keys() | expected.keys())
    summary = dict(graph.stats(), lists_compared=total,
                   lists_equal=total - len({h['image'] for h in holds}),
                   lists_held=len({h['image'] for h in holds}),
                   held_by_kind={k: held_kinds[k] for k in sorted(KINDS | {'list'})},
                   canonicalisation='sorted JSON object keys; arrays, values and absent fields preserved')
    return summary, holds


def qualification(image, tu, placement=None):
    """Stable image/home namespace; repeated homes also need their placement row."""
    def token(value):
        return re.sub(r'[^A-Za-z0-9_]', '_', value) + '_' + digest(value.encode())[:12]
    return ('lg_' + token(image) + '__' + token(tu) + '__'
            + (token(placement) + '__' if placement else ''))


def emit_global(slus_script, standalone, banks, symbols=(), noloads=()):
    """Flatten a SLUS recipe + file phases + arbitrary shared-VMA OVERLAY groups.

    banks: (image, VMA, size, body lines). LMAs are artificial extraction positions.
    Each group is NOCROSSREFS. Script guards record exact declared output extents.
    """
    groups = {}
    for image, base, size, lines in banks:
        groups.setdefault(base, []).append((image, size, lines))
    out = ['/* Generated experimental graph projection. No production authority switch. */',
           '/* LMAs are extraction coordinates; file-only VMAs are diagnostic. */',
           'OUTPUT_FORMAT("elf32-tradlittlemips")', 'OUTPUT_ARCH(mips)', slus_script,
           *sorted(set(symbols)), 'SECTIONS', '{', *standalone]
    lma = 0x10000000
    for base, members in sorted(groups.items()):
        out += [f'  OVERLAY 0x{base:X} : NOCROSSREFS AT(0x{lma:X}) SUBALIGN(1)', '  {']
        for image, size, lines in sorted(members):
            section = '.' + image.replace('/', '_')
            out += [f'    {section}', '    {', *lines, '    }']
            lma += size
        out.append('  }')
        for image, size, _ in members:
            section = '.' + image.replace('/', '_')
            out.append(f'  ASSERT(SIZEOF({section}) == 0x{size:X}, "graph extent: {image}")')
        lma = (lma + 0xFFFF) & ~0xFFFF
    out += list(noloads)
    out += ['  /DISCARD/ : { *(*) }', '}']
    return '\n'.join(out) + '\n'


def main():
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', type=Path, default=ROOT)
    p.add_argument('--graph', type=Path, default=ROOT / 'config/link_graph')
    sub = p.add_subparsers(dest='action', required=True)
    sub.add_parser('capture')
    sub.add_parser('validate')
    gen = sub.add_parser('generate'); gen.add_argument('--output', type=Path, required=True)
    cmp = sub.add_parser('compare'); cmp.add_argument('--catalogue', type=Path)
    cmp.add_argument('--report', type=Path, required=True); cmp.add_argument('--holds', type=Path, required=True)
    a = p.parse_args()
    try:
        if a.action == 'capture':
            result = capture(a.root, a.graph)
        else:
            g = Graph(a.graph)
            if a.action == 'generate':
                result = g.generate(a.output)
            elif a.action == 'compare':
                result, holds = compare(g, a.catalogue or a.root / 'config/link')
                write_json(a.report, result)
                a.holds.parent.mkdir(parents=True, exist_ok=True)
                a.holds.write_text('image\tkind\treason\n' + ''.join('\t'.join(h[k] for k in ('image', 'kind', 'reason')) + '\n' for h in holds))
                print(json.dumps(result, indent=2))
                return int(bool(holds))
            else:
                g.documents(validate=True); g.verify_inputs(a.root); g.verify_sources(a.root); result = g.stats()
        print(json.dumps(result, indent=2))
        return 0
    except (ValueError, OSError, KeyError, TypeError) as exc:
        p.exit(1, 'link graph: ' + str(exc) + '\n')


if __name__ == '__main__':
    sys.exit(main())
