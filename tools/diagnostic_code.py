"""Check diagnostic code extents reached from registered callers."""

import hashlib

CLASS = 'linked_diagnostic_code'
LOAD_LEDGER = 'ledger/instance_load_regions.jsonl'
LOAD_METHOD = 'internal link-evidence; documented devkit-linked image'


def word(retail, offset):
    return int.from_bytes(retail[offset:offset + 4], 'little')


def address_reference(upper, lower):
    base = (upper & 0xffff) << 16
    displacement = (lower & 0xffff) - (0x10000 if lower & 0x8000 else 0)
    if upper >> 26 != 15 or (upper >> 16) & 31 != (lower >> 21) & 31:
        raise ValueError('registered instruction pair does not materialize an address')
    if lower >> 26 == 13:
        return base | (lower & 0xffff)
    if lower >> 26 in (9, 35):
        return base + displacement
    raise ValueError('registered instruction pair does not materialize an address')


def table_target(record, retail, delta, low, high):
    table = record['table_foff']
    slot = record['entry_foff']
    if not low <= table <= slot <= high - 4 or table % 4 or slot % 4:
        raise ValueError('callback table witness lies outside the diagnostic image')
    upper, lower = (word(retail, site) for site in record['table_reader'])
    if address_reference(upper, lower) != table + delta:
        raise ValueError('registered reader does not reference the callback table')
    return word(retail, slot)


def span(record, image, caller, retail, *, checked_caller=None):
    """Verify the image identity, caller's target and the claimed code boundary."""
    start, end = record['foff'], record['foff'] + record['size']
    low, high = image['foff'], image['foff'] + image['size']
    if 'call_foff' in record:
        sites = (record['call_foff'],)
    elif 'jump_foff' in record:
        jump = record['jump_foff']
        sites = (jump - 8, jump - 4, jump)
    else:
        sites = record['table_reader']
    if (image['schema'] != 'azure-clean.instance-load-region.v1' or image['method'] != LOAD_METHOD
            or image['container'] != record['container'] or image['foff'] != record['image_foff']
            or image['base'] - low != image['delta']
            or not 0 <= low <= start < end <= high <= len(retail)
            or any(off % 4 for off in (start, end, *sites)) or end - start < 8):
        raise ValueError('extent lies outside the documented diagnostic image')
    if checked_caller is None:
        if (caller is None or caller['id'] != record['caller'] or caller['container'] != record['container']
                or caller.get('row_kind') == 'data' or not caller['func'].startswith('func_')):
            raise ValueError('diagnostic caller is not a registered code row')
        caller_start, caller_end = caller['foff'], caller['foff'] + caller['size']
    else:
        caller_start, caller_end = checked_caller
        if ('call_foff' not in record or 'caller' in record or caller_start != record['caller_foff']
                or not (caller_end <= start or end <= caller_start)):
            raise ValueError('diagnostic caller is not a disjoint, checked direct caller')
    if any(not low <= caller_start <= site <= caller_end - 4 < high or start <= site < end for site in sites):
        raise ValueError('call witness lies outside its registered or checked caller')

    delta = image['delta']
    if 'call_foff' in record:
        site, = sites
        command = word(retail, site)
        target = ((site + delta + 4) & 0xf0000000) | ((command & 0x03ffffff) << 2)
        if command >> 26 != 3:
            raise ValueError('registered caller has no direct call at the witness')
    elif 'jump_foff' in record:
        upper, lower, jump = (word(retail, site) for site in sites)
        if lower >> 26 not in (9, 13) or jump >> 26 or jump & 0x1fffff != 8 or (lower >> 16) & 31 != (jump >> 21) & 31:
            raise ValueError('registered wrapper does not jump to its materialized address')
        target = address_reference(upper, lower)
    else:
        target = table_target(record, retail, delta, low, high)
    if target != start + delta:
        raise ValueError('registered caller does not target the classified entry')
    terminal = word(retail, end - 8)
    if terminal >> 26 != 0 or (terminal >> 21) & 31 != 31 or terminal & 0x1fffff != 8:
        raise ValueError('classified extent has no terminal return')
    if hashlib.sha256(retail[low:high]).hexdigest() != image['image_sha256']:
        raise ValueError('diagnostic image differs from the disc-backed placement record')
    return [start, end]


def checked_spans(records, images, registry, retail):
    """Follow same-image edges only after a registered caller anchors the chain."""
    pending = list(records)
    checked = {}
    while pending:
        deferred = []
        for record in pending:
            image_key = record['container'], record['image_foff']
            key = (*image_key, record['foff'])
            if key in checked:
                raise ValueError('duplicate diagnostic code entry')
            caller_span = None
            caller = None
            if 'caller_foff' in record:
                caller_span = checked.get((*image_key, record['caller_foff']))
                if caller_span is None:
                    deferred.append(record)
                    continue
            else:
                caller = registry.get(record['caller'])
            checked[key] = span(record, images[image_key], caller, retail, checked_caller=caller_span)
        if len(deferred) == len(pending):
            raise ValueError('diagnostic caller chain has no registered anchor')
        pending = deferred
    return checked.values()
