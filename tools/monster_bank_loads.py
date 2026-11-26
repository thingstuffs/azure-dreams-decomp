"""Check loader-derived extents for Dungeon monster banks.

The older receipts pin the disc bytes and check that the entry pointer lies
inside the load window. Review of those receipts is pending. A different
resource and slot pair allowed by the formula can satisfy those checks if
its first word also points inside its load window. Registered-entry records
add a check against the production entry row.

The two fixed-size exceptions bind the first pointer to a registered C body
at the corresponding disc offset and runtime address.
"""
from __future__ import annotations

import hashlib
import json
from pathlib import Path
import re
from tools.build.retail_spans import check_span, hash_extent, validate_span

MANIFEST = 'docs/evidence/dungeon_monster_bank_loads.json'
LOADER = 'src/dungeon/item/load_monster_resource_data.c'
WITNESS = re.compile(r'dungeon_(?:slot_[a-z0-9_]+\.load|[a-z0-9_]+\.slot_load)\.json\Z')
PLACEMENT = re.compile(r'dungeon_resource_(\d{2})_slot_([0-6])\.placement\.json\Z')
LOADER_RECEIPT = 'docs/evidence/dungeon_normal_resource_loader.json'
DISC_FILE = 'DUNGEON/DUNGEON.BIN'
DISC_LBA = 0x3016
BANK_BYTES = 12 * 0x800
# The fixed read branches in load_monster_code_module bypass cache slot geometry.
EXCEPTIONAL_BANKS = {49: (0x569c, 0x8016a800, 24), 56: (0x56b1, 0x80164800, 36)}


def digest(data):
    return hashlib.sha256(data).hexdigest()


def check_volume(iso, retail):
    if (iso['path'], iso['lba'], iso['size']) != (DISC_FILE, DISC_LBA, len(retail)):
        raise ValueError('monster bank witness disagrees with the disc volume')


def normal_geometry(resource, slot):
    if not (type(resource) is int and 1 <= resource <= 56 and resource not in (49, 56)
            and type(slot) is int and 0 <= slot <= 6):
        raise ValueError('monster bank witness is outside the normal loader domain')
    lba = 0x4340 + (resource - 1) * 0x54 + slot * 12
    destination = 0x80170800 - slot * BANK_BYTES
    start = (lba - DISC_LBA) * 0x800
    return lba, destination, start


def normal_interval(region, retail, payload_sha256):
    lba, destination, start = normal_geometry(region['resource_id'], region['slot'])
    end = start + BANK_BYTES
    if (region['sectors'], region['lba'], region['destination'], region['file_start'],
            region['file_end'], region['delta']) != (12, lba, destination, start, end, destination-start):
        raise ValueError('monster bank transfer differs from the loader formula')
    if (not 0 <= start < end <= len(retail) or region['disc_container_equal'] is not True
            or digest(retail[start:end]) != payload_sha256):
        raise ValueError('monster bank transfer differs from the disc bytes')
    entry = int.from_bytes(retail[start:start+4], 'little')
    if not destination <= entry < destination + BANK_BYTES or entry % 4:
        raise ValueError('monster bank entry points outside its load window')
    return start, end


def transfer_interval(record, retail, loader):
    if record['schema'] != 'r121m.slot-loader-authentication.v1':
        raise ValueError('unknown monster bank witness schema')
    check_volume(record['iso_extent'], retail)
    if record['iso_record_verified'] is not True:
        raise ValueError('missing monster bank witness disc volume verification')
    original = record['loader']
    if dict(foff=original['foff'], size=original['size'], sha256=original['sha256']) != loader:
        raise ValueError('monster bank witness names a different retail loader')
    region = record['slot_load']
    return normal_interval(region, retail, region['bank_sha256'])


def check_placement_loader(receipt, retail, slus_retail, loader):
    check_volume(receipt['iso'], retail)
    if (receipt['schema'] != 'azure-clean.resource-loader-static.v1' or receipt['source'] != LOADER
            or receipt['iso_directory_record_verified'] is not True or not receipt['words']):
        raise ValueError('missing normal placement loader evidence')
    inputs = {DISC_FILE: retail, 'SLUS_006.14': slus_retail}
    seen = set()
    for entry in receipt['words']:
        witness = entry['word']['$retail']
        validate_span(witness)
        file, offset = witness['file'], witness['offset']
        data = inputs.get(file)
        if (data is None or witness['length'] != 4 or int(entry['foff'], 16) != offset
                or not 0 <= offset <= len(data)-4 or (file, offset) in seen
                or (file == DISC_FILE and not loader['foff'] <= offset <= loader['foff'] + loader['size'] - 4)):
            raise ValueError('normal placement loader evidence differs from disc')
        start, size = hash_extent(offset, witness['length'])
        check_span(witness, data[start:start+size])
        seen.add((file, offset))
    if {file for file, _ in seen} != inputs.keys():
        raise ValueError('missing loader or resident helper evidence')


def placement_interval(record, retail, identity, historical_hash):
    if (record['resource_id'], record['slot']) != identity or record['loader_receipt'] != LOADER_RECEIPT:
        raise ValueError('monster bank placement names a different transfer or loader')
    # The historic receipts pin the original serialization. The current
    # receipt's code span is checked against disc after its raw words were removed.
    if record['loader_receipt_sha256'] != historical_hash or record['runtime_observed'] is not False:
        raise ValueError('monster bank placement loader provenance differs')
    schema = record.get('schema')
    if (schema not in (None, 'azure-clean.resource-loader-union.v1')
            or (schema is None and (record.get('status') != 'PROVEN_STATIC_TRANSFER'
                                    or record.get('all_sector_payloads_equal') is not True))):
        raise ValueError('monster bank placement is missing proof of static transfer')
    return normal_interval(record, retail, record['loaded_bank_sha256'])


def registered_interval(record, retail, images):
    """Bind the loader-selected bank's first pointer to its production entry row."""
    _, destination, start = normal_geometry(record['resource_id'], record['slot'])
    end = start + BANK_BYTES
    image = images.get(f'dungeon/bank_{start:x}')
    if (not 0 <= start < end <= len(retail) or image is None
            or (image['foff'], image['vma']) != (start, destination)):
        raise ValueError('registered monster bank lacks its expected production view')
    address = int.from_bytes(retail[start:start + 4], 'little')
    if not destination <= address < destination + BANK_BYTES or address % 4:
        raise ValueError('registered monster bank entry lies outside its load window')
    entry = next((row for row in image['entries'] if row.get('row') == record['entry']), None)
    if entry is None or not entry['row'].startswith('dungeon/func_'):
        raise ValueError('registered monster bank entry is missing from its production view')
    prefix = entry.get('body_offset', 0)
    if entry['vma'] + prefix != address or entry['foff'] + prefix != start + address - destination:
        raise ValueError('registered monster bank pointer differs from its production entry')
    return start, end


def exceptional_interval(record, retail, registry):
    resource_id = record['resource_id']
    if resource_id not in EXCEPTIONAL_BANKS or 'slot' in record:
        raise ValueError('resource ID does not select a fixed monster bank')
    lba, destination, sectors = EXCEPTIONAL_BANKS[resource_id]
    start = (lba - DISC_LBA) * 0x800
    size = sectors * 0x800
    end = start + size
    if not 0 <= start < end <= len(retail):
        raise ValueError('fixed monster bank lies outside the Dungeon container')
    address = int.from_bytes(retail[start:start + 4], 'little')
    if not destination + 4 <= address < destination + size or address % 4:
        raise ValueError('fixed monster bank entry points outside its load window')
    entry = registry.get(record['entry'])
    if (entry is None or entry.get('kind') != 'overlay' or entry.get('row_kind') == 'data'
            or entry.get('container') != 'dungeon' or not entry.get('exists') or not entry.get('c_path')
            or entry.get('true_name') != f'func_{address:08X}'
            or entry.get('foff') != start + address - destination
            or not 0 < entry['size'] <= destination + size - address):
        raise ValueError('fixed monster bank pointer differs from its registered C entry')
    return start, end


def intervals(root, retail, slus_retail, images=None, registry=None):
    root = Path(root)
    path = root / MANIFEST
    if not path.is_file():
        raise ValueError('monster bank load manifest is missing')
    manifest = json.loads(path.read_text())
    source = manifest['loader_source']
    loader = manifest['retail_loader']
    start, size = loader['foff'], loader['size']
    if (manifest['schema'] != 'azure-clean.monster-bank-loads.v1' or source != LOADER
            or manifest['loader_source_sha256'] != digest((root / source).read_bytes())
            or not 0 <= start < start+size <= len(retail)
            or loader['sha256'] != digest(retail[start:start+size])):
        raise ValueError('monster bank load manifest disagrees with the loader')
    result = []
    for name in manifest['witnesses']:
        if not isinstance(name, str) or not WITNESS.fullmatch(name):
            raise ValueError('invalid monster bank witness path')
        try:
            record = json.loads((path.parent / name).read_text())
            result.append(transfer_interval(record, retail, loader))
        except (OSError, ValueError, TypeError, KeyError) as error:
            raise ValueError(f'{name}: {error}') from error
    for record in manifest.get('registered_entries', []):
        result.append(registered_interval(record, retail, images or {}))
    placements = manifest.get('placements', [])
    if placements:
        receipt = json.loads((root / LOADER_RECEIPT).read_text())
        check_placement_loader(receipt, retail, slus_retail, loader)
        historical_hash = manifest['historical_loader_receipt_sha256']
        for name in placements:
            match = PLACEMENT.fullmatch(name) if isinstance(name, str) else None
            if not match:
                raise ValueError('invalid monster bank placement path')
            try:
                record = json.loads((path.parent / name).read_text())
                result.append(placement_interval(record, retail, tuple(map(int, match.groups())), historical_hash))
            except (OSError, ValueError, TypeError, KeyError) as error:
                raise ValueError(f'{name}: {error}') from error
    result.sort()
    if not result or any(end > start for (_, end), (start, _) in zip(result, result[1:])):
        raise ValueError('monster bank loads are missing, overlapping or repeated')
    exceptional = manifest.get('exceptional_entries', [])
    if len({record['resource_id'] for record in exceptional}) != len(exceptional):
        raise ValueError('fixed monster bank load is repeated')
    # Fixed branches can read the same sectors at different times. The
    # physical census unions the transfer windows before assigning ownership.
    return sorted(result + [exceptional_interval(record, retail, registry or {}) for record in exceptional])
