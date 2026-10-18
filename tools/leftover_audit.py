#!/usr/bin/env python3
"""Bound development metadata without exporting names, values or retail bytes."""
import hashlib
from pathlib import Path
import re
import struct


def sha(blob):
    return hashlib.sha256(blob).hexdigest()


def symbol_tables(blob, start=0x80c000, end=0x82b914):
    """Validate complete fixed-width records; keep separators explicitly opaque."""
    identifier = re.compile(rb'[A-Za-z_][A-Za-z0-9_()]*')
    def record(at):
        name = blob[at:at+32]
        text = name.split(b'\0', 1)[0]
        return (len(name)==32 and 0 < len(text) < 32
                and identifier.fullmatch(text) is not None
                and name[len(text):] == bytes(32-len(text)))
    if not 0 <= start < end <= len(blob):
        raise ValueError('symbol dump outside container')
    regions = []
    at = start
    while at < end:
        first = at
        is_record = at+36 <= end and record(at)
        if is_record:
            while at+36 <= end and record(at):
                at += 36
            regions.append(dict(foff=first,size=at-first,records=(at-first)//36,stride=36,
                                format='char name[32], NUL-terminated and zero-filled; little-endian u32 value',
                                sha256=sha(blob[first:at])))
        else:
            at += min(4,end-at)
            while at < end and not (at+36 <= end and record(at)):
                at += min(4,end-at)
            regions.append(dict(foff=first,size=at-first,format='opaque inter-table region; no padding claim',
                                sha256=sha(blob[first:at])))
    return dict(foff=start,size=end-start,sha256=sha(blob[start:end]),
                records=sum(r.get('records',0) for r in regions),regions=regions,
                scope='Structural format validation only; symbol names and values are not exported.')


def audit(root, town, slus, disc_path=None):
    from gate.disc_slice import Disc
    with Disc(disc_path or Path(root)/'bin/Azure Dreams.bin') as disc:
        lba,n = disc.locate('TOWN/TOWN.BIN')
    if n != len(town):
        raise ValueError('TOWN disc length differs')
    symbols = symbol_tables(town)
    if [r.get('records',0) for r in symbols['regions']] != [678,0,2909]:
        raise ValueError('symbol table structure differs from the reviewed two-table witness')
    optional = []
    for off,expected in ((0x54ac8,0x868000),(0x54ad0,0x80b800)):
        word,sector = struct.unpack_from('<II',slus,off)
        a,size = (sector-lba)*2048,(word>>23)*2048
        if (a,size,word&0x7fffff) != (expected,2048,0x16000):
            raise ValueError('optional descriptor differs from bounded loader witness')
        target = town[a:a+size]
        copies = [];cursor = 0
        while True:
            cursor = town.find(target,cursor)
            if cursor < 0:
                break
            copies.append(cursor)
            cursor += 1
        optional.append(dict(descriptor_container='slus',descriptor_foff=off,descriptor_size=8,
                             descriptor_sha256=sha(slus[off:off+8]),
                             container='town',foff=a,size=size,sha256=sha(target),
                             load_vma='0x80016000',identical_slice_foffs=copies,
                             scope='Descriptor bounds one complete load; other occurrences prove exact slice identity, not enclosing allocations or a shared compiled TU.'))
    return dict(schema='azure-clean.leftover-audit.v1',symbol_dump=symbols,optional_loads=optional,
                town_sha256=sha(town),slus_sha256=sha(slus),
                reproduction='python3 tools/census/regenerate.py --disc DISC --output TEMP --check',
                static_loading_evidence='docs/evidence/r121w_ll6/LEFTOVERS_REPORT.md')
