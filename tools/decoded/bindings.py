"""Check decoded binding names against their registered targets."""
import csv
import re

from tools.decoded import import_ranges


SYMBOL_DEFINITION = re.compile(r'(\w+)\s*=\s*(0x[0-9a-fA-F]+);')
FIELDS = ('symbol', 'address', 'size', 'sha256')


def external_symbols(root):
    """Read the ordinary names and linker symbol registries."""
    homes = set()
    names = root / 'config/names.tsv'
    if names.is_file():
        for line in names.read_text().splitlines():
            address, *symbols = line.split('\t')
            if address.startswith('0x') and len(symbols) >= 2:
                homes.update((symbol, int(address, 16)) for symbol in symbols[:2])
    for suffix in ('symbols', 'c_syms'):
        path = root / f'config/slus_006.14.{suffix}.txt'
        if path.is_file():
            for line in path.read_text().splitlines():
                match = SYMBOL_DEFINITION.match(line)
                if match:
                    homes.add((match[1], int(match[2], 16)))
    return homes


def read_evidence(path):
    """Read fallbacks for identities outside the ordinary registries."""
    evidence = {}
    with path.open(newline='') as source:
        rows = csv.DictReader(source, delimiter='\t')
        if tuple(rows.fieldnames or ()) != FIELDS:
            raise ValueError('invalid decoded binding evidence header')
        for row in rows:
            key = (row['symbol'], int(row['address'], 16))
            size, sha = int(row['size']), row['sha256']
            if key in evidence or size < 0 or not import_ranges.valid_digest(size, sha):
                raise ValueError(f'invalid decoded binding evidence for {key[0]}')
            evidence[key] = size, sha
    return evidence


def audit(image, homes, evidence, *, data=None, number=int):
    """Validate each binding and, when available, the decoded evidence extents."""
    base, end = number(image['address']), number(image['address']) + number(image['size'])
    exports = {number(f['address']): f.get('symbol', f['name'])
               for unit in image['units'] for f in unit['functions']}
    used = set()
    counts = {'placement': 0, 'global': 0}

    def check(scope, symbol, target):
        address = number(target)
        key = symbol, address
        if address in exports:
            if exports[address] != symbol:
                raise ValueError(f'{scope}: {symbol} points to the decoded export {exports[address]}')
            return
        inside = base <= address < end
        if not inside and key in homes:
            return
        if key not in evidence:
            raise ValueError(f'{scope}: no binding identity for {symbol} at {address:#010x}')
        size, sha = evidence[key]
        if inside != bool(size) or (inside and address + size > end):
            raise ValueError(f'{scope}: invalid binding extent for {symbol}')
        if data is not None and inside:
            start = address - base
            if import_ranges.range_digest(data[start:start+size]) != sha:
                raise ValueError(f'{scope}: binding extent differs for {symbol}')
        used.add(key)

    for symbol, address in image['symbols'].items():
        check(image['image'], symbol, address)
        counts['global'] += 1
    for unit in image['units']:
        for symbol, address in unit.get('bindings', {}).items():
            check(unit['placement'], symbol, address)
            counts['placement'] += 1
    if evidence.keys() - used:
        symbol, address = min(evidence.keys() - used)
        raise ValueError(f'unused binding evidence for {symbol} at {address:#010x}')
    return counts
