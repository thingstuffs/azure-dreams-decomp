"""Resolve menu calls to function entries in their decoded and ordinary load images."""
from collections import defaultdict
from contextlib import ExitStack
import csv
import json
import re
import struct

from tools.gate import linklist


def records(path):
    with path.open() as stream:
        return [json.loads(line) for line in stream if line.strip() and not line.startswith('#')]


def call_address(data, offset, pc):
    word, = struct.unpack_from('<I', data, offset)
    if word >> 26 not in (2, 3):
        raise ValueError('compiled call site does not contain a direct transfer')
    return ((pc + 4) & 0xf0000000) | ((word & 0x03ffffff) << 2)


def require_identity(symbol, actual, where):
    if symbol != actual:
        raise ValueError(f'{where}: expected function {symbol}, found {actual or "no function entry"}')


class OrdinaryFunctions:
    def __init__(self, root):
        self.root = root
        self.links = linklist.load(root)
        self.rows = {row['id']: row for row in records(root / 'ledger/rows.jsonl')}
        paths = {row['id']: row['path'] for row in records(root / 'ledger/layout.jsonl')}
        self.by_offset = {}
        self.by_source = defaultdict(list)
        self.copies = defaultdict(set)
        self.resident = {}
        for row in self.rows.values():
            if row['container'] == 'slus':
                for name in row.get('defs', []):
                    if re.fullmatch('func_[0-9A-Fa-f]{8}', name):
                        self.resident[int(name[5:], 16)] = name
                continue
            if not (row.get('func') or '').startswith('func_'):
                continue
            self.by_offset[row['container'], row['foff']] = row
            self.by_source[paths.get(row['id']), row['true_name']].append(row)
        for entry in self.links[2].values():
            self.copies[entry['home']].add(entry['row'])
        # Some resident owners keep their entry in the source row ID and their
        # other exports in defs. The resident function-size registry pins the start.
        sizes = json.loads((root / 'config/func_sizes.json').read_text())
        for row_id in paths:
            match = re.fullmatch(r'slus/w_([0-9A-Fa-f]{8})', row_id)
            if match and sizes.get('func_' + match[1], 0) > 0:
                self.resident[int(match[1], 16)] = 'func_' + match[1]
        for line in (root / 'config/slus_006.14.symbols.txt').read_text().splitlines():
            match = re.match(r'(\w+)\s*=\s*(0x[\da-fA-F]+);\s*//\s*type:func\b', line)
            if match:
                self.resident[int(match[2], 16)] = match[1]
        self.banks = {r['region']: r for r in records(root / 'config/overlays/dungeon.rowbase.jsonl')
                      if r['base_confidence'] == 'proven'}

    def identity(self, container, file_offset):
        row = self.by_offset.get((container, file_offset))
        if row:
            entry = self.links[2].get(row['id'])
            home = self.rows[entry['home']] if entry else row
            return home['true_name'] or home['func']
        return None

    def in_view(self, view, address):
        image = self.links[0][view]
        if image['vma'] <= address < image['vma'] + image['size']:
            return self.identity(image['container'], image['foff'] + address - image['vma'])
        return self.resident.get(address)

    def menu_target(self, context, symbol, address):
        region = context['bank_calls'].get(symbol)
        if region:
            bank = self.banks[region]
            offset = address - int(bank['delta'], 0)
            if int(bank['foff_start'], 0) <= offset < int(bank['foff_end'], 0):
                return self.identity('dungeon', offset)
            return None
        return self.in_view(context['engine'], address)

    def ordinary_callers(self, source, symbol):
        for home in self.by_source[source, symbol]:
            for row_id in {home['id']} | self.copies[home['id']]:
                row = self.rows[row_id]
                for view in linklist.caller_images(self.links, row['container'], row['foff']):
                    yield row, view


def audit(root, image, objects, aliases, data, number):
    base = number(image['address'])
    end = base + number(image['size'])
    context = image['call_context']
    registry = OrdinaryFunctions(root)
    exports = {number(f['address']): f.get('symbol', f['name'])
               for u in image['units'] for f in u['functions']}
    globals_ = {aliases.get(k, k): number(v) for k, v in image['symbols'].items()}
    globals_.update({aliases.get(f['name'], f['name']): number(f['address'])
                     for u in image['units'] for f in u['functions']})
    exceptions = {(e['image'], e['caller'], number(e['site'])): e for e in context['exceptions']}
    with (root / image['import_layout']['holds']).open() as stream:
        held = {base + int(row['offset'], 16) for row in csv.DictReader(stream, delimiter='\t')}
    decoded_homes = {(u['source'], f.get('symbol', f['name'])) for u in image['units']
                     if 'placement' not in u for f in u['functions']}
    outside, placed_sites, used_banks = set(), set(), set()
    with ExitStack() as stack:
        files = {}
        def ordinary_target(view, row, site):
            container = row['container']
            if container not in files:
                path = root / 'work/disc/containers' / f'{container.upper()}_{container.upper()}.BIN'
                files[container] = stack.enter_context(path.open('rb'))
            src = files[container]
            src.seek(row['foff'] + site)
            geometry = registry.links[0][view]
            pc = geometry['vma'] + row['foff'] - geometry['foff'] + site
            return call_address(src.read(4), 0, pc)

        # Verify the exact ordinary caller and the interior owner on both documented town paths.
        for (view, row_id, site), entry in exceptions.items():
            row, owner = registry.rows[row_id], registry.rows[entry['owner']]
            geometry = registry.links[0][view]
            if (view not in linklist.caller_images(registry.links, row['container'], row['foff'])
                    or site < 0 or site % 4 or site + 4 > row['size']):
                raise ValueError('invalid caller in decoded binding exception')
            target = ordinary_target(view, row, site)
            dest = target - geometry['vma'] + geometry['foff']
            if (target != number(entry['address']) or owner['container'] != geometry['container']
                    or not owner['foff'] < dest < owner['foff'] + owner['size']):
                raise ValueError('ordinary exception differs from its registered interior target')

        for unit in image['units']:
            scoped = 'placement' in unit
            local = {v.get('symbol', v['name']): number(v['address']) for v in unit['functions']}
            funcs = {'.text.' + f.get('symbol', f['name']): f for f in unit['functions']}
            bindings = {k: number(v) for k, v in unit.get('bindings', {}).items()}
            for section, off, kind, (target_type, name), addend in objects[unit['source']].relocs:
                if section not in funcs or kind != '26' or target_type != 'sym':
                    continue
                f = funcs[section]
                pc = number(f['address']) + off
                target = call_address(data, pc - base, pc)
                source_symbol = f.get('symbol', f['name'])
                if addend:
                    if (name == source_symbol and 0 < addend < number(f['size'])
                            and target == number(f['address']) + addend):
                        continue
                    raise ValueError(f'{source_symbol}: transfer to a function interior')
                address = local.get(name, (bindings if scoped else globals_).get(name))
                if address != target:
                    raise ValueError(f'{f["name"]}: unbound or misdirected call to {name}')
                if base <= target < end:
                    if target not in exports and target not in held:
                        raise ValueError('decoded call does not target a registered function start')
                    identity = exports.get(target, name)
                else:
                    identity = registry.menu_target(context, name, target)
                    require_identity(name, identity, image['image'])
                    outside.add((name, target))
                    if name in context['bank_calls']:
                        used_banks.add(name)
                if not scoped:
                    continue
                callers = list(registry.ordinary_callers(unit['source'], source_symbol))
                if not callers and (unit['source'], source_symbol) not in decoded_homes:
                    raise ValueError(f'{source_symbol}: ordinary placement has no registered load image')
                for row, view in callers:
                    actual = ordinary_target(view, row, off)
                    key = view, row['id'], off
                    if key in exceptions:
                        if actual != target:
                            raise ValueError('decoded and ordinary exception target addresses differ')
                    else:
                        require_identity(identity, registry.in_view(view, actual), f'{view}/{row["id"]}')
                    placed_sites.add(key)
    if used_banks != context['bank_calls'].keys():
        raise ValueError('unused decoded call bank')
    return len(outside), len(placed_sites), len(exceptions)
