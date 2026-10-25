#!/usr/bin/env python3
"""Inventory bounded LZ streams in retail resource commands and CD sectors.

Code signatures are discovery evidence. Only a reviewed loader or native
write witness establishes a decoded executable image; no rows are inferred.
"""
import argparse
import hashlib
import json
import re
import struct
import sys
from collections import Counter
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[2]))
from tools.decoded.lz import decode

FILES = {'main': 'MAIN_MAIN.BIN', 'town': 'TOWN_TOWN.BIN',
         'dungeon': 'DUNGEON_DUNGEON.BIN', 'ovmovie': 'OVMOVIE.BIN'}


def discover(data):
    starts = {o: [dict(kind='sector', base=o)] for o in range(0, len(data), 0x800)}
    command_roots = 0
    # A command's offset is relative to the entire resource's base, including
    # when it is the second command in a list. Do not assume offset == 20.
    for hit in re.finditer(b'[\x01-\x09]\x00(?:\x00|\x10)\x00', data):
        root = hit.start()
        if root & 3:
            continue
        cursor, pending, chain = root, [], []
        for _ in range(64):
            if cursor + 16 > len(data):
                break
            command, step, offset, a, b, c, d = struct.unpack_from('<HHIhhhh', data, cursor)
            if command == 0:
                if pending and root + min(p[0] for p in pending) >= cursor + 4:
                    command_roots += 1
                    for source, evidence in pending:
                        starts.setdefault(root + source, []).append(dict(kind='command', base=root, **evidence))
                break
            if command not in range(1, 10) or step not in (0, 16):
                break
            if not 16 <= offset <= 0x100000 or root + offset >= len(data):
                break
            evidence = dict(command=command, command_offset=cursor, offset=offset,
                            destination=hex((b & 0xffff) << 16 | (a & 0xffff)))
            if command in (1, 5):
                if not (0 <= a < 1024 and 0 <= b < 512 and 0 < c <= 1024 and 0 < d <= 512):
                    break
                evidence['rectangle'] = [a, b, c, d]
                evidence['input_limit'] = min(0x10000, c*d*2) if command == 5 else 0x8000
            if command in (1, 3, 5):
                pending.append((offset, evidence))
            chain.append(cursor)
            if not step:
                if pending and root + min(p[0] for p in pending) >= cursor + 16:
                    command_roots += 1
                    for source, evidence in pending:
                        starts.setdefault(root + source, []).append(dict(kind='command', base=root, **evidence))
                break
            cursor += step
    return starts, command_roots


def signatures(data):
    phases = []
    # A stream may end in the middle of a word. The next stream's dictionary
    # resets but its output appends without alignment (legacy split: +0x82C2).
    for phase in range(4):
        count = max(0, (len(data)-phase)//4)
        words = struct.unpack('<' + 'I'*count, data[phase:phase+count*4])
        returns = sum(w == 0x03e00008 for w in words)
        frames = sum(w & 0xffff0000 == 0x27bd0000 and bool(w & 0x8000) for w in words)
        calls = sum(w >> 26 == 3 and 0x80010000 <= (0x80000000 | ((w & 0x3ffffff) << 2)) < 0x80200000 for w in words)
        phases.append(dict(returns=returns, frames=frames, calls=calls, phase=phase))
    return max(phases, key=lambda s: min(s[k] for k in ('returns', 'frames', 'calls')))


def census(root):
    results, summary = [], {}
    for family, filename in FILES.items():
        data = (root/'work/disc/containers'/filename).read_bytes()
        starts, commands = discover(data)
        status, successful = Counter(), 0
        for offset, contexts in sorted(starts.items()):
            limit = max([c.get('input_limit', 0x8000) for c in contexts])
            try:
                decoded, used = decode(data[offset:offset+limit], 0x100000)
            except ValueError:
                continue
            if len(decoded) < 64:
                continue
            successful += 1
            sig = signatures(decoded)
            code = min(sig[k] for k in ('returns', 'frames', 'calls')) >= 3
            status['code_candidates' if code else 'other_decoded'] += 1
            if code:
                results.append(dict(container=family, offset=hex(offset), used=used, size=len(decoded),
                                    source_sha256=hashlib.sha256(data[offset:offset+used]).hexdigest(),
                                    decoded_sha256=hashlib.sha256(decoded).hexdigest(), signatures=sig,
                                    contexts=contexts, status='CODE_CANDIDATE_REQUIRES_LOADER_ATTRIBUTION'))
        summary[family] = dict(container_bytes=len(data), candidate_starts=len(starts),
                               command_roots=commands, successful_streams=successful, **status)
    return dict(schema='azure.compressed-code-census.v1', containers=summary, streams=results,
                method='4-byte aligned resource command lists (1/3/5); every 0x800-byte CD sector; bounded resident LZ decode; >=3 returns, negative stack frames and resident JALs',
                limitations=['Signature hits alone do not prove executable ownership or entry boundaries.',
                             'Arbitrarily unaligned or headerless embedded streams outside CD-sector starts are not exhaustively searched.',
                             'This is an asset-layout census, not proof that no other packing format exists.'])


if __name__ == '__main__':
    p = argparse.ArgumentParser(description=__doc__)
    p.add_argument('--root', type=Path, required=True)
    p.add_argument('--output', type=Path, required=True)
    a = p.parse_args()
    result = census(a.root)
    a.output.write_text(json.dumps(result, indent=2)+'\n')
    print(json.dumps(dict(containers=result['containers'], code_streams=len(result['streams']))))
