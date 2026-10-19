#!/usr/bin/env python3
"""census.py - byte-accounting census: every byte of every container gets exactly one label.

Labels (owner evidence ladder 2026-10-16), first match wins, each byte carries one evidence kind:
  1 proven_code   c_row (func_ rows; SLUS: src .text from the link map), instance_proven, instance_partial
  2 library_code  sdk_asm regions, ledger/sdk_objects.jsonl extents, SLUS PsyQ .text
  4 proven_data   ledger data (non-func_ rows, data_excluded, split data/data_segment, rodata_owners; SLUS c_data,
                  psyq_data, exe header, name strings) then binary formats (TIM, VAB, SEQ/SEP, TMD, VB-ADPCM runs,
                  pointer tables, SJIS text, ASCII string pools)
  3 strongly_code binary detectors, only tiers admitted at the precision measured by --validate (see ADMIT)
  5 padding       zero fill (>=16 B runs, or shorter zero gaps between labelled bytes)
  6 unknown       everything else, characterised (code-like / pointer-ish / text-ish / zero-ish / other)
(Data precedes strongly_code: a code detector firing on ledger/format data is reported as a conflict, not applied.)

Read-only. Inputs (repo-relative under --root): ledger/{rows,instances,coverage_regions,sdk_objects}.jsonl,
ledger/splits/<c>.jsonl, config/overlays/*.rodata_owners.jsonl, work/disc/containers/*.BIN, baserom/slus_006.14,
and config/census/slus_layout.json. Pure python3, no numpy; ~1-3 min with 5 processes.

  python3 -I census.py --root . [--json census.json] [--md census.md] [--spans-dir DIR]

Every run writes the confusion tables (detectors run blind: no ledger input reaches the code/data detectors
except D5's shingle set, which is built 2-fold for validation). --spans-dir writes the full per-label interval lists
(multi-MB; point it outside searched work/ trees or at a directory with a .ignore).
"""
from __future__ import annotations
import argparse, bisect, collections, gzip, hashlib, json, pickle, re, struct, sys, zlib
from array import array
from pathlib import Path
from multiprocessing import Pool

HERE = Path(__file__).resolve().parent
# -I omits the script directory; expose only the committed detector helpers.
if str(HERE) not in sys.path: sys.path.insert(0, str(HERE))
# Gate helpers may expose tools/census.py; detector helpers must bind this module.
if __name__ == '__main__': sys.modules['census'] = sys.modules[__name__]
CONTS = ['main', 'town', 'dungeon', 'ovmovie', 'slus']
FILES = {'main': 'work/disc/containers/MAIN_MAIN.BIN', 'town': 'work/disc/containers/TOWN_TOWN.BIN',
         'dungeon': 'work/disc/containers/DUNGEON_DUNGEON.BIN', 'ovmovie': 'work/disc/containers/OVMOVIE.BIN',
         'slus': 'baserom/slus_006.14'}
ENGINE_MAXSPAN = 8192
# tiers of label 3 admitted into the census; set from the --validate precision (REPORT.md "Admission")
ADMIT = ('T1_twin', 'T2_framed_ref', 'T3_leaf_ref', 'T4_shape_noref', 'T5_shape_noeval')
ADMIT_PRECISION = 0.999

# ---------------------------------------------------------------- interval algebra (as remaining.py)
def merge(iv):
    out = []
    for a, b in sorted((int(a), int(b)) for a, b in iv):
        if a >= b: continue
        if out and a <= out[-1][1]: out[-1][1] = max(b, out[-1][1])
        else: out.append([a, b])
    return out
def subtract(a, b):
    out = []; b = merge(b); j = 0
    for s, e in merge(a):
        while j < len(b) and b[j][1] <= s: j += 1
        cur = s; k = j
        while k < len(b) and b[k][0] < e:
            lo, hi = b[k]
            if lo > cur: out.append([cur, lo])
            cur = max(cur, hi); k += 1
            if cur >= e: break
        if cur < e: out.append([cur, e])
    return out
def inter(a, b): return subtract(a, subtract(a, b))
def size(iv): return sum(b - a for a, b in merge(iv))
def recs(p):
    p = Path(p)
    records = [json.loads(s) for s in p.read_text().splitlines() if s.strip() and not s.startswith('#')] if p.exists() else []
    # Import from the requested repository root, not a live checkout.
    if any('revision_of_sha256' in r for r in records):
        root = p.parents[1] if p.parent.name == 'ledger' else p.parents[2]
        helper = root / 'tools/common.py'
        # The helper imports source_layout; expose only this root's tools.
        sys.path.insert(0, str(root / 'tools'))
        from common import effective_jsonl
        return effective_jsonl(records)
    return records
def num(x):
    x = str(x).strip()
    return int(x, 16) if x.lower().startswith('0x') else int(x)
def ext(r, f='foff', s='size'): return [num(r[f]), num(r[f]) + num(r[s])]
def truthy(v): return v is True or str(v).lower() == 'true'

# ---------------------------------------------------------------- ledger layers
def ledger_layers(root):
    root = Path(root)
    rows = recs(root / 'ledger/rows.jsonl'); inst = recs(root / 'ledger/instances.jsonl')
    reg = recs(root / 'ledger/coverage_regions.jsonl'); sdk = recs(root / 'ledger/sdk_objects.jsonl')
    splits = {c: recs(root / f'ledger/splits/{c}.jsonl') for c in CONTS + ['dungeon_engine']}
    rod = {c: recs(root / f'config/overlays/{c}.rodata_owners.jsonl') for c in CONTS}
    slus = json.loads((Path(root) / 'config/census/slus_layout.json').read_text())['kinds']
    L = {c: collections.defaultdict(list) for c in CONTS}
    rowmeta = {c: [] for c in CONTS}
    for r in rows:
        c = r.get('container')
        if c not in L or c == 'slus' or r.get('foff') is None: continue
        e = ext(r)
        if (r.get('func') or '').startswith('func_'):
            L[c]['c_row'].append(e); rowmeta[c].append((e[0], e[1], r['id']))
        else:
            dk = r.get('data_kind') or ''
            L[c]['leftover_row' if dk in ('stale_image', 'prior_image_tail') else 'padding_row' if dk in ('zero_padding', 'padding', 'alignment')
              else 'data_row'].append(e)
    latest = {}
    for r in reg: latest[(r['container'], r['foff'], r['size'], r['category'])] = r
    reg = [r for r in latest.values() if r.get('active', True)]
    blocked = {(r['container'], num(r['foff']), num(r['size'])) for r in reg if r['category'] == 'instance_excluded'}
    rank = {'proven': 2, 'partial': 1}
    best = {}
    for r in inst:
        k = (r['container'], num(r['foff']), num(r['size'])); v = rank.get(r.get('result'), 0)
        best[k] = v  # latest record per span wins (as remaining.py)
    for (c, f, s), v in best.items():
        if c in L and v and (c, f, s) not in blocked:
            L[c]['instance_proven' if v == 2 else 'instance_partial'].append([f, f + s])
    for r in reg:
        c = r['container']
        if c not in L: continue
        cat = r['category']
        if cat in ('data_excluded', 'sdk_asm', 'estimated_code', 'window', 'unported'): L[c]['reg_' + cat].append(ext(r))
    byfunc = {}
    for key, ss in splits.items():
        c = 'dungeon' if key == 'dungeon_engine' else key
        if c not in L: continue
        for s in ss:
            if s.get('foff') is None: continue
            e = ext(s); byfunc[(key, s.get('func_vram'))] = e
            if truthy(s.get('data_segment')) or s.get('result') == 'data': L[c]['split_data'].append(e)
            elif s.get('result') == 'MERGE_FAIL' or (s.get('result') in ('CFAIL', 'M2C_FAIL') and num(s['size']) > ENGINE_MAXSPAN): pass
            elif c != 'slus': L[c]['split_code'].append(e)
    for r in sdk:
        c, fn = r['id'].split('/', 1)
        e = ext(r) if r.get('foff') is not None and r.get('size') is not None else byfunc.get((c, fn))
        if e is None:
            for rr in rows:
                if rr.get('container') == c and fn in (rr.get('func'), rr.get('true_name')) and rr.get('foff') is not None: e = ext(rr); break
        if e and c in L: L[c]['sdk_object'].append(e)
    for c, rr in rod.items():
        for r in rr:
            k = 'leftover_row' if str(r.get('rodata', '')).startswith(('stale_image', 'prior_image_tail')) else 'rodata_owner'
            L[c][k].append([num(r['foff']), num(r['foff']) + int(r['rodata_size'])])
    # Decision 68c: linker-owned words replace C data rows. Load and validate the
    # production catalogue; these witnesses carry no instruction or retail payload.
    from importlib.util import spec_from_file_location, module_from_spec
    spec = spec_from_file_location('census_linklist', root/'tools/gate/linklist.py')
    linklist = module_from_spec(spec); spec.loader.exec_module(linklist)
    for image in linklist.load(root)[0].values():
        for entry in image['entries']:
            if entry.get('kind') in ('data', 'padding') and entry.get('extractor'):
                key = 'linklist_padding' if entry['kind'] == 'padding' else 'linklist_data'
                L[image['container']][key].append(ext(entry))
    for k, v in slus.items():
        kk = {'c_text': 'c_row', 'psyq_text': 'psyq_text', 'c_data': 'slus_c_data', 'psyq_data': 'psyq_data',
              'exe_header': 'exe_header', 'asm_main': 'slus_asm_main', 'blob': 'slus_blob'}.get(k)
        if kk is None: kk = 'slus_strings' if k.startswith('other:build/asm/str/') else 'slus_other'
        L['slus'][kk] += v
    for c in L:
        for k in list(L[c]): L[c][k] = merge(L[c][k])
    return L, rowmeta

# ---------------------------------------------------------------- MIPS decode
SPECIAL_OK = {0, 2, 3, 4, 6, 7, 8, 9, 12, 13, 16, 17, 18, 19, 24, 25, 26, 27, 32, 33, 34, 35, 36, 37, 38, 39, 42, 43}
OP_OK = {2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46, 50, 58}
GTE_OK = {0x01, 0x06, 0x0C, 0x10, 0x11, 0x12, 0x13, 0x14, 0x16, 0x1B, 0x1C, 0x1E, 0x20, 0x28, 0x29, 0x2A, 0x2D, 0x2E, 0x30, 0x3D, 0x3E, 0x3F}
LOADS = {32, 33, 34, 35, 36, 37, 38}; STORES = {40, 41, 42, 43, 46}
def valid(w):
    """strict compiler-plausible R3000 word (0 = nop is valid). Writes to $zero other than nop count as invalid."""
    if w == 0: return True
    op = w >> 26
    if op == 0:
        f = w & 63
        if f not in SPECIAL_OK: return False
        if f in (8,): return (w & 0x001FFFC0) == 0               # jr: rt=rd=sa=0
        if f in (12, 13): return True
        if f in (24, 25, 26, 27): return ((w >> 6) & 0x3FF) == 0     # mult/div: rd=sa=0
        if f in (16, 18): return ((w >> 11) & 31) != 0 and (w >> 16) & 0x3FF == 0   # mfhi/mflo
        if f in (17, 19): return (w & 0x1FFFC0) == 0               # mthi/mtlo
        if f == 9: return (w >> 16) & 31 == 0                     # jalr
        if ((w >> 11) & 31) == 0: return False                    # ALU writing $zero
        if f in (0, 2, 3): return (w >> 21) & 31 == 0             # shifts: rs=0
        return (w >> 6) & 31 == 0                                 # other ALU: sa=0
    if op == 1: return ((w >> 16) & 31) in (0, 1, 16, 17)
    if op == 16:
        rs = (w >> 21) & 31
        return rs in (0, 4) and (w & 0x7FF) == 0 or w == 0x42000010
    if op == 18:
        if w & (1 << 25): return (w & 63) in GTE_OK
        return ((w >> 21) & 31) in (0, 2, 4, 6) and (w & 0x7FF) == 0
    if op not in OP_OK: return False
    if op in (2, 3): return ((w & 0x3FFFFFF) << 2) < 0x00800000   # j/jal target inside the 8 MB RAM window of its segment
    if (op in LOADS or op in STORES or op in (50, 58)) and ((w >> 21) & 31) == 0: return False   # $zero-based access (pointer words)
    if op in (8, 9, 10, 11, 12, 13, 14, 15) or op in LOADS: return ((w >> 16) & 31) != 0   # no writes to $zero
    return True

def regs_written(w):
    op = w >> 26
    if op == 0:
        f = w & 63
        if f in (8, 12, 13, 17, 19, 24, 25, 26, 27): return ()
        return ((w >> 11) & 31,)
    if op == 3: return (31,)
    if op in (8, 9, 10, 11, 12, 13, 14, 15) or op in LOADS: return ((w >> 16) & 31,)
    if op == 18 and not (w & (1 << 25)) and ((w >> 21) & 31) in (0, 2): return ((w >> 16) & 31,)
    return ()
def regs_any(w):
    op = w >> 26
    if op == 0: return ((w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31)
    if op in (2, 3): return ()
    if op in (16, 17, 19): return ((w >> 16) & 31,)
    if op == 18: return () if w & (1 << 25) else ((w >> 16) & 31,)
    return ((w >> 21) & 31, (w >> 16) & 31)
def is_branch(w):
    op = w >> 26
    return op in (1, 2, 3, 4, 5, 6, 7) or (op == 0 and (w & 63) in (8, 9)) or (op == 18 and not (w & (1 << 25)) and ((w >> 21) & 31) == 8)
def is_call(w): return (w >> 26) == 3 or ((w >> 26) == 0 and (w & 63) == 9)
def is_prologue(w): return (w >> 16) == 0x27BD and (w & 0x8000) and (w & 7) == 0
def mask_word(w):
    op = w >> 26
    if op in (2, 3): return w & 0xFC000000
    if op == 15: return w & 0xFFFF0000
    if (op in LOADS or op in STORES or op in (50, 58) or op == 9) and ((w >> 21) & 31) not in (0, 29): return w & 0xFFFF0000
    return w

# ---------------------------------------------------------------- segmentation + criteria (blind)
def segments(W, V):
    """-> list of [s, t, kind, d2, d3, ncall] in word indices; s..t-1 all valid, t-2 = jr ra."""
    n = len(W); jr = [i for i in range(n - 1) if W[i] == 0x03E00008]
    inv = [i for i in range(n) if not V[i]]; pro = [i for i in range(n) if is_prologue(W[i])]
    segs = []; prev = 0
    for e in jr:
        stop = e + 2
        if stop > n or not V[e + 1]: prev = stop; continue
        k = bisect.bisect_left(inv, stop) - 1
        lo = max(prev, inv[k] + 1 if k >= 0 else 0)
        if lo > e: prev = stop; continue
        k = bisect.bisect_left(pro, e) - 1
        if k >= 0 and pro[k] >= lo: s = pro[k]
        else:
            s = lo
            while s < e and W[s] == 0: s += 1
        segs.append(analyse_seg(W, s, stop)); prev = stop
    return segs

def analyse_seg(W, s, t):
    body = W[s:t]; n = len(body); ncall = sum(1 for w in body if is_call(w))
    d3 = True; why = ''
    # frame
    if is_prologue(body[0]):
        N = 0x10000 - (body[0] & 0xFFFF)
        epi = 0x27BD0000 | N
        ok = any(w == epi for w in body[max(1, n - 12):])
        saved = set()
        for w in body[1:min(n, 40)]:
            if (w >> 26) == 43 and ((w >> 21) & 31) == 29: saved.add((w >> 16) & 31)
        if ncall and not (31 in saved and any((w >> 16) == (0x8FBF) for w in body[max(1, n - 24):])): ok = False
        d2 = 'framed' if ok else 'bad_frame'
        spw = [i for i, w in enumerate(body) if 29 in regs_written(w)]
        if spw and set(spw) - {0} - {i for i in range(max(1, n - 12), n) if body[i] == epi}: d3 = False; why = 'sp'
    else:
        saved = set()
        uses_sp = any(29 in regs_any(w) for w in body)
        d2 = 'leaf' if not uses_sp and not ncall else 'bad_frame'
    if d3:
        for i, w in enumerate(body):
            ra = regs_any(w)
            if 26 in ra or 27 in ra: d3 = False; why = 'k0k1'; break
            if (w >> 26) == 16: d3 = False; why = 'cop0'; break
            for r in regs_written(w):
                if (16 <= r <= 23 or r == 30) and r not in saved: d3 = False; why = 'sreg'; break
            if not d3: break
            if is_branch(w):
                if i + 1 < n and is_branch(body[i + 1]): d3 = False; why = 'delay'; break
                op = w >> 26
                if op in (1, 4, 5, 6, 7) or (op == 18 and ((w >> 21) & 31) == 8):
                    off = w & 0xFFFF; off = off - 0x10000 if off & 0x8000 else off
                    tgt = i + 1 + off
                    if not (0 <= tgt < n): d3 = False; why = 'branch_out'; break
    return [s, t, d2, d3, why, ncall]

def deltas_and_refs(W, segs):
    """Delta vote and per-segment D4 (reference) evidence; blocks of 16 KB.
    Vote: distinct jal targets of block b vs entries of good segments (framed/leaf + D3) in b-1..b+1, d = (t - foff) mod 2^28;
    a block accepts every d with >= 3 votes (top 6). D4 for a segment with entry s: for an accepted d of its block,
    s+d is a jal target / pointer word / lui+addiu address in blocks b-4..b+4, or a pointer word hits inside the body (jtbl)."""
    n = len(W); BLK = 0x1000
    good = [g for g in segs if g[2] in ('framed', 'leaf') and g[3]]
    jal = collections.defaultdict(set); ent = collections.defaultdict(list); pair = collections.defaultdict(set)
    for g in good: ent[g[0] // BLK].append(g[0] * 4)
    for g in segs:
        s, t = g[0], g[1]
        for i in range(s, t):
            w = W[i]; op = w >> 26
            if op == 3: jal[i // BLK].add((w & 0x3FFFFFF) << 2)
            elif op == 15:
                rt = (w >> 16) & 31; hi = (w & 0xFFFF) << 16
                for j in range(i + 1, min(t, i + 12)):
                    x = W[j]
                    if (x >> 26) == 9 and ((x >> 21) & 31) == rt:
                        lo = x & 0xFFFF; lo = lo - 0x10000 if lo & 0x8000 else lo
                        a = (hi + lo) & 0xFFFFFFFF
                        if a >> 28 in (8, 0xA): pair[i // BLK].add(a & 0x0FFFFFFF)
                        break
                    if rt in regs_written(x): break
    ptr = collections.defaultdict(set)
    for i in range(n):
        w = W[i]
        if (w >> 28) in (8, 0xA) and (w & 0x0F000000) == 0 and (w & 3) == 0: ptr[i // BLK].add(w & 0x0FFFFFFF)
    deltas = {}
    for b in set(jal) | set(ent):
        T = jal.get(b); E = ent.get(b - 1, []) + ent.get(b, []) + ent.get(b + 1, [])
        if not T or not E: continue
        cnt = collections.Counter(((t - e) & 0x0FFFFFFF) for t in T for e in E)
        for d, c in cnt.most_common(6):
            if c >= 3:
                for x in (b - 1, b, b + 1): deltas.setdefault(x, set()).add(d)
    cache = {}
    def nb(b):
        if b not in cache:
            bs = range(b - 4, b + 5)
            cache[b] = (set().union(*(jal.get(x, ()) for x in bs)), set().union(*(ptr.get(x, ()) for x in bs)),
                        set().union(*(pair.get(x, ()) for x in bs)))
        return cache[b]
    refs = []
    for g in segs:
        s, t = g[0], g[1]; b = s // BLK; D = deltas.get(b)
        if not D: refs.append('not_evaluable'); continue
        J, P, Q = nb(b); kinds = set()
        for d in D:
            v = (s * 4 + d) & 0x0FFFFFFF
            if v in J: kinds.add('jal')
            if v in P: kinds.add('ptr')
            if v in Q: kinds.add('lui_pair')
            if any(((i * 4 + d) & 0x0FFFFFFF) in P for i in range(s + 1, t)): kinds.add('jtbl')
        refs.append('+'.join(sorted(kinds)) if kinds else 'none')
    return refs, deltas

# ---------------------------------------------------------------- shingles (D5)
K = 12
def shingles_of(W, s, t):
    M = [mask_word(w) for w in W[s:t]]; out = []
    for i in range(0, len(M) - K + 1):
        win = M[i:i + K]
        if sum(1 for x in win if x == 0) >= 6: continue
        if any(((x >> 26) in LOADS or (x >> 26) in STORES) and ((x >> 21) & 31) == 0 for x in win): continue
        out.append(hash(tuple(win)))
    return out
def whole_hash(W, s, t): return hash(tuple(mask_word(w) for w in W[s:t]))

# ---------------------------------------------------------------- data format detectors (blind)
def u32(b, o): return struct.unpack_from('<I', b, o)[0]
def u16(b, o): return struct.unpack_from('<H', b, o)[0]
def find_all(b, pat, align=4):
    o = b.find(pat)
    while o >= 0:
        if o % align == 0: yield o
        o = b.find(pat, o + 1)

def det_tim(b):
    out = []; n = len(b)
    for o in find_all(b, b'\x10\x00\x00\x00'):
        if o + 20 > n: continue
        fl = u32(b, o + 4)
        if fl & ~0xF or (fl & 7) > 3: continue
        p = o + 8
        if fl & 8:
            if p + 12 > n: continue
            cl = u32(b, p); cw, ch = u16(b, p + 8), u16(b, p + 10)
            if not (0 < cw <= 1024 and 0 < ch <= 512 and cl == 12 + cw * ch * 2): continue
            p += cl
        if p + 12 > n: continue
        il = u32(b, p); x, y, iw, ih = u16(b, p + 4), u16(b, p + 6), u16(b, p + 8), u16(b, p + 10)
        if not (0 < iw <= 1024 and 0 < ih <= 512 and x < 1024 and y < 512 and il == 12 + iw * ih * 2): continue
        if p + il > n: continue
        out.append([o, p + il])
    return out

def det_vab(b):
    out = []; n = len(b)
    for o in find_all(b, b'pBAV'):
        if o + 32 > n: continue
        fs = u32(b, o + 12); ps, ts, vs = u16(b, o + 18), u16(b, o + 20), u16(b, o + 22)
        if not (0 < ps <= 128 and vs <= 254): continue
        vh = 0x820 + ps * 0x200 + 0x200
        if o + vh > n: continue
        tab = o + vh - 0x200
        vb = sum(u16(b, tab + 2 * i) for i in range(1, vs + 1)) << 3
        if fs == vh + vb and o + fs <= n and vb_ok(b, o + vh, o + fs): out.append([o, o + fs])
        else: out.append([o, o + vh])      # VH only: the VB body is stored elsewhere (or not contiguous)
    return out

ADPCM_FLAGS = {0, 1, 2, 3, 4, 6, 7}
def adpcm_block(b, j): return (b[j] >> 4) <= 4 and (b[j] & 15) <= 12 and b[j + 1] in ADPCM_FLAGS
def vb_ok(b, s, e):
    """VB body: first 16-byte block all zero, >= 98% of blocks valid SPU-ADPCM, >= 1 end flag."""
    if e - s < 32 or any(b[s:s + 16]): return False
    nb = (e - s) // 16; ok = sum(1 for j in range(s, s + nb * 16, 16) if adpcm_block(b, j))
    return ok >= 0.98 * nb and any(b[j + 1] in (1, 3) for j in range(s, s + nb * 16, 16))

def det_entropy(b, win=512, step=64, thr=7.0):
    """random-like bytes: Shannon entropy >= thr bits/byte in a 512-B window (C rows: max 5.84 over 8,349 dungeon windows).
    Only the central 128 B of each passing window is marked, so edges next to code stay out. Proves non-code only; the
    content (compressed / encrypted / filler) stays untyped."""
    import math
    out = []; n = len(b); lg = [0.0] + [k * math.log2(k) for k in range(1, win + 1)]; L2 = math.log2(win)
    core0 = (win - 128) // 2
    for o in range(0, n - win + 1, step):
        h = L2 - sum(lg[c] for c in collections.Counter(b[o:o + win]).values()) / win
        if h >= thr: out.append([o + core0, o + core0 + 128])
    return out

def det_offtab(W):
    """relative offset tables: >= 8 consecutive words, strictly increasing, each < 16 MB, steps < 1 MB, word-aligned values."""
    out = []; n = len(W); i = 0
    while i < n:
        j = i + 1
        while j < n and W[j - 1] < W[j] < 0x01000000 and W[j] - W[j - 1] < 0x100000 and (W[j] & 3) == 0: j += 1
        if j - i >= 8 and W[i] < 0x01000000: out.append([i * 4, j * 4]); i = j
        else: i += 1
    return out

def is_terminator(w):
    """unconditional transfer that can end a function body: j, jal (noreturn callee), jr, jalr, b (beq $0,$0)."""
    op = w >> 26
    return op in (2, 3) or (op == 0 and (w & 63) in (8, 9)) or (w >> 16) == 0x1000
def cond_target(w, k):
    op = w >> 26
    if op in (1, 4, 5, 6, 7) or (op == 18 and not (w & (1 << 25)) and ((w >> 21) & 31) == 8):
        off = w & 0xFFFF; off = off - 0x10000 if off & 0x8000 else off
        return k + 1 + off
    return None

def noncode_decode(W, V):
    """bytes no gcc function can contain. A function is a run of valid words that ends with an unconditional transfer
    (+ delay slot) and whose PC-relative branches stay inside the run. So, within each maximal valid run: (1) a branch
    whose target leaves the run is impossible (split there; 2 rounds), (2) words after the last terminator's delay slot,
    and whole runs without a terminator, are non-code. Invalid words are non-code."""
    n = len(W); bad = bytearray(0 if V[i] else 1 for i in range(n))
    for _ in range(2):
        i = 0; changed = False
        while i < n:
            if bad[i]: i += 1; continue
            j = i
            while j < n and not bad[j]: j += 1
            for k in range(i, j):
                tg = cond_target(W[k], k)
                if tg is not None and not (i <= tg < j): bad[k] = 1; changed = True
            i = j
        if not changed: break
    out = []; i = 0
    while i < n:
        if bad[i]:
            j = i
            while j < n and bad[j]: j += 1
            out.append([i * 4, j * 4]); i = j; continue
        j = i; last = -1
        while j < n and not bad[j]:
            if j > i and is_terminator(W[j - 1]): last = j - 1      # terminator whose delay slot is in the run
            j += 1
        if last < 0: out.append([i * 4, j * 4])
        elif last + 2 < j: out.append([(last + 2) * 4, j * 4])
        i = j
    return out

def det_seq(b):
    out = []; n = len(b)
    for o in find_all(b, b'pQES', 1):
        if o + 15 > n: continue
        ver = struct.unpack_from('>I', b, o + 4)[0]
        if ver == 1:
            e = b.find(b'\xFF\x2F\x00', o + 15, min(n, o + 0x40000))
            if e > 0: out.append([o, e + 3])
        elif ver == 0:
            p = o + 8; last = None
            while p + 13 <= n:
                sid = struct.unpack_from('>H', b, p)[0]; ln = struct.unpack_from('>I', b, p + 9)[0]
                if sid > 255 or ln == 0 or p + 13 + ln > n or b[p + 13 + ln - 3:p + 13 + ln] != b'\xFF\x2F\x00': break
                p += 13 + ln; last = p
            if last: out.append([o, last])
    return out

def det_tmd(b):
    out = []; n = len(b)
    for o in find_all(b, b'\x41\x00\x00\x00'):
        if o + 40 > n: continue
        fl, nobj = u32(b, o + 4), u32(b, o + 8)
        if fl not in (0, 1) or not (0 < nobj <= 512): continue
        top = o + 12; end = top + 28 * nobj; ok = True
        if end > n: continue
        for k in range(nobj):
            vt, nv, nt, nn, pt, np_, sc = struct.unpack_from('<IIIIIIi', b, top + 28 * k)
            if fl == 0: vt += top; nt += top; pt += top
            if not (0 < nv < 65536 and nn < 65536 and 0 < np_ < 65536 and -16 < sc < 16): ok = False; break
            if not (top <= vt < n and top <= nt < n and top <= pt < n): ok = False; break
            q = pt
            for _ in range(np_):
                if q + 4 > n: ok = False; break
                il = b[q + 1]; q += 4 + il * 4
            if not ok or q > n: ok = False; break
            end = max(end, vt + nv * 8, nt + nn * 8, q)
        if ok and end <= n and end - o <= 0x100000: out.append([o, end])
    return out

def det_adpcm(b):
    """runs of >=64 valid 16-byte SPU-ADPCM blocks (16-aligned), high-entropy sample bytes, >=1 end flag."""
    out = []; n = len(b) // 16 * 16; i = 0
    FL = {0, 1, 2, 3, 4, 6, 7}
    while i < n:
        j = i
        while j < n and (b[j] >> 4) <= 4 and (b[j] & 15) <= 12 and b[j + 1] in FL: j += 16
        nb = (j - i) // 16
        if nb >= 64:
            seg = b[i:j]
            samples = bytearray(x for k in range(0, len(seg), 16) for x in seg[k + 2:k + 16])
            nz = sum(1 for x in samples if x) / len(samples)
            ends = sum(1 for k in range(0, len(seg), 16) if seg[k + 1] in (1, 3))
            if nz >= 0.8 and len(set(samples)) >= 200 and ends >= 1: out.append([i, j])
        i = j + 16 if j == i else j
    return out

def det_ptrtab(W):
    out = []; n = len(W); i = 0
    def isp(w): return (w >> 28) in (8, 0xA) and (w & 0x0F800000) == 0 and (w & 3) == 0 and (w & 0x0FFFFFFF) >= 0x10000
    while i < n:
        if isp(W[i]):
            j = i
            while j < n and isp(W[j]): j += 1
            if j - i >= 4: out.append([i * 4, j * 4])
            i = j
        else: i += 1
    return out

SJ = re.compile(rb'(?:[\x81-\x9f\xe0-\xef][\x40-\x7e\x80-\xfc]|[\x20-\x7e\x0a\x0d])+')
def det_sjis(b):
    out = []
    for m in SJ.finditer(b):
        s, e = m.span()
        if e - s < 16: continue
        t = m.group(); k = 0; dbl = 0
        while k < len(t):
            if 0x81 <= t[k] <= 0x9f or 0xe0 <= t[k] <= 0xef: dbl += 1; k += 2
            else: k += 1
        if dbl >= 8 and dbl * 2 >= 0.6 * (e - s): out.append([s, e])
    # merge runs separated by <= 8 bytes of control bytes (script bytecode)
    m2 = []
    for s, e in out:
        if m2 and s - m2[-1][1] <= 8: m2[-1][1] = e
        else: m2.append([s, e])
    return m2

AS = re.compile(rb'[\x20-\x7e\x0a\x0d\x09]{8,}\x00')
def det_ascii(b):
    out = []
    for m in AS.finditer(b):
        s, e = m.span(); t = m.group()[:-1]
        letters = sum(1 for x in t if 65 <= x <= 90 or 97 <= x <= 122 or 48 <= x <= 57 or x in b' _.,:/!?\'-%')
        if letters >= 0.8 * len(t) and sum(1 for x in t if 65 <= x <= 90 or 97 <= x <= 122) >= 3:
            e2 = e
            while e2 % 4 and e2 < len(b) and b[e2] == 0: e2 += 1
            out.append([s, e2])
    m2 = []
    for s, e in out:
        if m2 and s - m2[-1][1] <= 4: m2[-1][1] = e
        else: m2.append([s, e])
    return m2

def det_zero(b):
    return [list(m.span()) for m in re.finditer(rb'\x00{16,}', b)]

# ---------------------------------------------------------------- per-container binary pass
G = {}   # shingle sets, set before the Pool forks: S0, S1 (12-word masked shingles per fold), H0, H1 (whole-row masked hashes)

def shingle_sets(root, rowmeta):
    S = [set(), set()]; H = [set(), set()]
    for c, rows in rowmeta.items():
        if not rows: continue
        b = (Path(root) / FILES[c]).read_bytes(); W = array('I'); W.frombytes(b[:len(b) // 4 * 4])
        for s, e, rid in rows:
            f = zlib.crc32(rid.encode()) & 1
            S[f].update(shingles_of(W, s // 4, e // 4)); H[f].add(whole_hash(W, s // 4, e // 4))
    return S, H

def d5(W, segs):
    """-> dict fold0/fold1 -> merged byte intervals covered by a twin hit using that fold's rows (whole-segment or shingle)."""
    S0, S1, H0, H1 = G['S0'], G['S1'], G['H0'], G['H1']
    out = {0: [], 1: []}
    for g in segs:
        s, t = g[0], g[1]
        M = [mask_word(w) for w in W[s:t]]; h = hash(tuple(M))
        c0 = bytearray(t - s); c1 = bytearray(t - s)
        if h in H0: c0 = bytearray(b'\x01' * (t - s))
        if h in H1: c1 = bytearray(b'\x01' * (t - s))
        for i in range(0, len(M) - K + 1):
            win = M[i:i + K]
            if sum(1 for x in win if x == 0) >= 6: continue
            if any(((x >> 26) in LOADS or (x >> 26) in STORES) and ((x >> 21) & 31) == 0 for x in win): continue
            hh = hash(tuple(win))
            if hh in S0: c0[i:i + K] = b'\x01' * K
            if hh in S1: c1[i:i + K] = b'\x01' * K
        for f, cv in ((0, c0), (1, c1)):
            st = None
            for k in range(len(cv) + 1):
                if k < len(cv) and cv[k]:
                    if st is None: st = k
                elif st is not None: out[f].append([(s + st) * 4, (s + k) * 4]); st = None
    return {f: merge(v) for f, v in out.items()}

def binary_pass(args):
    c, path = args
    b = Path(path).read_bytes(); n4 = len(b) // 4
    W = array('I'); W.frombytes(b[:n4 * 4])
    if sys.byteorder != 'little': W.byteswap()
    V = bytearray(1 if valid(w) else 0 for w in W)
    segs = segments(W, V)
    refs, deltas = deltas_and_refs(W, segs)
    crit = collections.defaultdict(list); tk = collections.defaultdict(lambda: collections.defaultdict(list))
    for g, r in zip(segs, refs):
        e = [g[0] * 4, g[1] * 4]
        crit['D1_seg'].append(e)
        crit['D2_' + g[2]].append(e)
        crit['D3_ok' if g[3] else 'D3_fail:' + g[4]].append(e)
        crit['D4_' + ('ref' if r not in ('none', 'not_evaluable') else r)].append(e)
        for k in r.split('+'):
            if r not in ('none', 'not_evaluable'): crit['D4k_' + k].append(e)
        if g[3] and r not in ('none', 'not_evaluable'):
            if g[2] == 'framed': crit['T2_framed_ref'].append(e); tk['T2_framed_ref']['T2_framed_ref:' + r].append(e)
            elif g[2] == 'leaf': crit['T3_leaf_ref'].append(e); tk['T3_leaf_ref']['T3_leaf_ref:' + r].append(e)
        elif g[3] and g[2] in ('framed', 'leaf'): crit['T4_shape_noref' if r == 'none' else 'T5_shape_noeval'].append(e)
    dd = d5(W, segs)
    from masked_prefix_probe import detect as detect_prefix
    prefix, prefix_hits = detect_prefix(W, segs, (G['H0'], G['H1']))
    crit['D5_prefix_fold0'] = prefix[0]; crit['D5_prefix_fold1'] = prefix[1]
    crit['D5_fold0'] = dd[0]; crit['D5_fold1'] = dd[1]
    fmt = dict(tim=det_tim(b), vab=det_vab(b), seq=det_seq(b), tmd=det_tmd(b), adpcm=det_adpcm(b),
               ptrtab=det_ptrtab(W), offtab=det_offtab(W), sjis=det_sjis(b), ascii=det_ascii(b), entropy=det_entropy(b),
               noncode_decode=noncode_decode(W, V))
    # per-4-byte characterisation arrays are too big to ship; ship compact summaries for unknown spans later via char_spans
    entries = sorted(g[0] * 4 for g in segs)
    tim_cand = sum(1 for o in find_all(b, b'\x10\x00\x00\x00') if o + 8 <= len(b) and not (u32(b, o + 4) & ~0xF) and (u32(b, o + 4) & 7) <= 3)
    vab_full = sum(1 for s, e in fmt['vab'] if e - s != 0xA20 + u16(b, s + 18) * 0x200)
    return c, dict(prefix_hits=prefix_hits, n=len(b), nseg=len(segs), ndelta_blocks=len(deltas), entries=entries,
                   tier_kinds={k: {kk: merge(vv) for kk, vv in d.items()} for k, d in tk.items()},
                   stats=dict(tim_header_candidates=tim_cand, vab_spans=len(fmt['vab']), vab_full=vab_full,
                              seq_spans=len(fmt['seq']), segments=len(segs), delta_blocks=len(deltas)),
                   crit={k: merge(v) for k, v in crit.items()}, fmt={k: merge(v) for k, v in fmt.items()}, zero=merge(det_zero(b)))

def characterise(args):
    """unknown spans -> (bucket, stats); bucket by dominant evidence."""
    c, path, spans = args
    b = Path(path).read_bytes(); out = []
    for s, e in spans:
        s4 = (s + 3) // 4 * 4; e4 = e // 4 * 4; n = max(1, (e4 - s4) // 4)
        ws = struct.unpack_from('<%dI' % ((e4 - s4) // 4), b, s4) if e4 > s4 else ()
        z = sum(1 for w in ws if w == 0) / n; v = sum(1 for w in ws if w and valid(w)) / n
        jr = sum(1 for w in ws if w == 0x03E00008); pt = sum(1 for w in ws if (w >> 28) in (8, 0xA) and (w & 0x0F800000) == 0) / n
        sj = len(re.findall(rb'[\x81-\x9f\xe0-\xef][\x40-\x7e\x80-\xfc]', b[s:e])) * 2 / max(1, e - s)
        ff = b[s:e].count(0xFF) / max(1, e - s)
        if z >= 0.9: k = 'zero-ish (short zero runs)'
        elif ff >= 0.5: k = '0xFF fill'
        elif jr and v + z >= 0.9: k = 'code-like (jr ra, valid decode)'
        elif v + z >= 0.9: k = 'code-like, no jr ra'
        elif pt >= 0.3: k = 'pointer-ish'
        elif sj >= 0.3: k = 'SJIS-ish text/bytecode'
        else: k = 'other data-like'
        out.append([s, e, k, round(z, 2), round(v, 2), jr, round(pt, 2), round(sj, 2)])
    return c, out

# ---------------------------------------------------------------- assembly
LEDGER_TYPED = ['linklist_data', 'matched_c_read', 'data_row', 'rodata_owner', 'exe_header', 'psyq_data', 'slus_c_data', 'slus_strings']   # C-owned / linker-placed data
LEDGER_AUDIT = ['reg_data_excluded', 'split_data']   # split-audit data_segment flags: contested where code detectors fire
FMT = ['tim', 'vab', 'seq', 'tmd', 'adpcm', 'ptrtab', 'offtab', 'sjis', 'ascii']
TIERS = ['T1_twin', 'T2_framed_ref', 'T3_leaf_ref', 'T4_shape_noref', 'T5_shape_noeval']
CRITS = ['D1_seg', 'D2_framed', 'D2_leaf', 'D2_bad_frame', 'D3_ok', 'D4_ref', 'D4_none', 'D4_not_evaluable',
         'D4k_jal', 'D4k_ptr', 'D4k_lui_pair', 'D4k_jtbl', 'D5_fold0', 'D5_fold1']

def fold_ivs(rowmeta):
    F = {c: ([], []) for c in rowmeta}
    for c, rows in rowmeta.items():
        for s, e, rid in rows: F[c][zlib.crc32(rid.encode()) & 1].append([s, e])
    return {c: (merge(a), merge(b)) for c, (a, b) in F.items()}

def pct(a, b): return round(100.0 * a / b, 3) if b else None

def validate(L, B, folds):
    """confusion tables over all containers. Positives P = C rows minus typed data; INS = proven/partial instances.
    Clean negatives: N_struct = typed ledger data + typed format detections (hard negatives), N_entropy = random-like bytes.
    N_audit (split-audit data_segment flags) is NOT a negative: hits there are reported as contested bytes."""
    tot = collections.Counter(); per = {}
    for c in CONTS:
        Lc, Bc = L[c], B[c]
        ltyped = merge([x for k in LEDGER_TYPED for x in Lc.get(k, [])])
        P = subtract(Lc.get('c_row', []), ltyped)
        INS = subtract(merge(Lc.get('instance_proven', []) + Lc.get('instance_partial', [])), ltyped + P)
        code = merge(P + INS)
        fmt_all = merge([x for k in FMT for x in Bc['fmt'][k]])
        N_struct = subtract(merge(ltyped + fmt_all), code)
        N_ent = subtract(Bc['fmt']['entropy'], code + N_struct)
        N_audit = subtract(merge([x for k in LEDGER_AUDIT for x in Lc.get(k, [])]), code + N_struct + N_ent)
        f0, f1 = folds.get(c, ([], []))
        f0 = inter(f0, P); f1 = inter(f1, P); fl = subtract(P, f0 + f1)   # fl = SLUS c_text (no rows): out-of-sample for D5
        cr = dict(Bc['crit'])
        cr['T1_twin'] = merge(cr.get('D5_fold0', []) + cr.get('D5_fold1', []))
        res = {'P': size(P), 'INS': size(INS), 'N_struct': size(N_struct), 'N_entropy': size(N_ent), 'N_audit': size(N_audit)}
        for X in CRITS + TIERS:
            iv = cr.get(X, [])
            if X == 'T1_twin':
                tp = size(inter(f0, cr.get('D5_fold1', []))) + size(inter(f1, cr.get('D5_fold0', []))) + size(inter(fl, iv))
            else: tp = size(inter(P, iv))
            res[X] = dict(tp=tp, ins=size(inter(INS, iv)), fp_struct=size(inter(N_struct, iv)), fp_entropy=size(inter(N_ent, iv)),
                          audit=size(inter(N_audit, iv)))
        Pc = inter(P, merge(cr.get('D2_framed', []) + cr.get('D2_leaf', [])))   # code-shaped C bytes (rows also hold tables)
        res['P_code'] = size(Pc)
        # union recall of the admitted rule (T1 fold-crossed on P) and misses by first cause
        UP = merge(inter(f0, cr.get('D5_fold1', [])) + inter(f1, cr.get('D5_fold0', [])) + inter(fl, cr['T1_twin'])
                   + inter(P, merge(cr.get('T2_framed_ref', []) + cr.get('T3_leaf_ref', []))))
        res['union_P'] = size(UP); res['union_P_code'] = size(inter(Pc, UP))
        miss = subtract(P, UP); mc = collections.OrderedDict()
        for k, nm in (('T4_shape_noref', 'shape ok, no reference (T4)'), ('T5_shape_noeval', 'shape ok, no base to test refs (T5)'),
                      ('D2_bad_frame', 'frame not gcc-shaped'), ('D1_seg', 'segment fails ABI (D3)')):
            x = inter(miss, cr.get(k, [])); mc[nm] = size(x); miss = subtract(miss, x)
        mc['outside detected segments (tables in rows, headless pieces)'] = size(miss); res['union_miss'] = mc
        for k in FMT + ['entropy', 'noncode_decode']:
            v = Bc['fmt'][k]
            res['fmt_' + k] = dict(total=size(v), on_P=size(inter(P, v)), on_P_code=size(inter(Pc, v)), on_INS=size(inter(INS, v)),
                                   on_audit=size(inter(N_audit, v)))
        per[c] = res
        for k in ('P', 'P_code', 'INS', 'N_struct', 'N_entropy', 'N_audit', 'union_P', 'union_P_code'): tot[k] += res[k]
        for k, v in res['union_miss'].items(): tot['miss|' + k] += v
        for X in CRITS + TIERS:
            for k, v in res[X].items(): tot[X + '|' + k] += v
        for k in FMT + ['entropy', 'noncode_decode']:
            for kk, v in res['fmt_' + k].items(): tot['fmt_' + k + '|' + kk] += v
    # entry hits: overlay C rows whose start is a detected segment entry
    eh = [0, 0]
    for c in CONTS:
        ent = set(B[c]['entries'])
        for s, e, rid in G['rowmeta'].get(c, []): eh[1] += 1; eh[0] += s in ent
    summ = {}
    for X in CRITS + TIERS:
        tp, fs, fe, ins, au = (tot[X + '|' + k] for k in ('tp', 'fp_struct', 'fp_entropy', 'ins', 'audit'))
        summ[X] = dict(recall_P=pct(tp, tot['P']), recall_INS=pct(ins, tot['INS']), tp=tp, fp_struct=fs, fp_entropy=fe, audit_hits=au,
                       precision=tp / (tp + fs + fe) if tp + fs + fe else None)
    fm = {k: {kk: tot['fmt_' + k + '|' + kk] for kk in ('total', 'on_P', 'on_P_code', 'on_INS', 'on_audit')} for k in FMT + ['entropy', 'noncode_decode']}
    union = dict(recall_P=pct(tot['union_P'], tot['P']), recall_P_code=pct(tot['union_P_code'], tot['P_code']),
                 misses={k[5:]: v for k, v in tot.items() if k.startswith('miss|')})
    return dict(admitted_union=union, totals=dict(P=tot['P'], P_code=tot['P_code'], INS=tot['INS'], N_struct=tot['N_struct'], N_entropy=tot['N_entropy'], N_audit=tot['N_audit'],
                            row_entry_hits=eh), detectors=summ, formats=fm, per_container=per)

def label(L, B, admitted, decision57=True):
    out = {}; spans = {}; conflicts = collections.defaultdict(dict)
    for c in CONTS:
        Lc, Bc = L[c], B[c]; n = Bc['n']; rest = [[0, n]]
        lab = collections.OrderedDict(); kinds = collections.defaultdict(collections.Counter); sp = collections.defaultdict(list)
        def take(lbl, kind, iv):
            nonlocal rest
            got = inter(rest, iv); s = size(got)
            if s: lab[lbl] = lab.get(lbl, 0) + s; kinds[lbl][kind] += s; sp[lbl] += [[a, b, kind] for a, b in got]
            rest = subtract(rest, got)
        for k in ('c_row', 'instance_proven', 'instance_partial'): take('1 proven_code', k, Lc.get(k, []))
        for k in ('psyq_text', 'reg_sdk_asm', 'sdk_object'): take('2 library_code', k, Lc.get(k, []))
        for k in LEDGER_TYPED: take('4 proven_data', 'ledger:' + k, Lc.get(k, []))
        take('5 padding_leftover', 'ledger:linklist_padding', Lc.get('linklist_padding', []))
        for k in FMT: take('4 proven_data', 'format:' + k, Bc['fmt'][k])
        # ledger-recorded stale / prior images (disc leftover per the ladder) before the code tiers: code-shaped, not shipped role
        take('5 padding_leftover', 'ledger:stale_or_prior_image_row', Lc.get('leftover_row', []))
        cr = dict(Bc['crit']); cr['T1_twin'] = merge(cr.get('D5_fold0', []) + cr.get('D5_fold1', []))
        audit = merge([x for k in LEDGER_AUDIT for x in Lc.get(k, [])])
        for k in TIERS:
            if k in admitted:
                conflicts[c][k] = size(inter(rest, inter(audit, cr.get(k, []))))
                for kind, iv in (Bc['tier_kinds'].get(k, {}).items() if k in ('T2_framed_ref', 'T3_leaf_ref') else ((('strongly code (shape only):' + k) if k.startswith(('T4_', 'T5_')) else k, cr.get(k, [])),)):
                    take('3 strongly_code', kind, iv)
        if 'T1_twin' in admitted:
            conflicts[c]['replayed_twin_prefix'] = size(inter(rest, inter(audit, Lc.get('replayed_twin_prefix', []))))
            take('3 strongly_code', 'T1_twin:strict_replayed_prefix', Lc.get('replayed_twin_prefix', []))
        # split-audit data flags count as proven data only where an independent non-code detector agrees
        noncode = merge(Bc['fmt']['noncode_decode'] + Bc['fmt']['entropy'])
        take('4 proven_data', 'audit+noncode_confirmed', inter(audit, noncode))
        take('5 padding_leftover', 'ledger:padding_row', Lc.get('padding_row', []))
        take('5 padding_leftover', 'zero_fill>=16B', Bc['zero'])
        # short zero gaps (4-15 B, 4-aligned) between labelled bytes
        if rest:
            b = Path(G['root'], FILES[c]).read_bytes(); gaps = []
            for s, e in rest:
                if e - s < 16 and s % 4 == 0 and e % 4 == 0 and not any(b[s:e]) and s > 0 and e < n: gaps.append([s, e])
            take('5 padding_leftover', 'zero_gap<16B', gaps)
        pending = '4 noncode_typing_pending' if decision57 else '6 unknown'
        if decision57:
            take(pending, 'noncode:high_entropy;conditional loader read extent', inter(Bc['fmt']['entropy'], G.get('loaded_extents', {}).get(c, [])))
        take(pending, 'noncode:high_entropy;disc content, placement unproven' if decision57 else 'noncode:high_entropy', Bc['fmt']['entropy'])
        take(pending, 'noncode:decode', Bc['fmt']['noncode_decode'])
        take('6 unknown', 'unresolved:audit_data_unconfirmed', audit)
        take('6 unknown', 'unresolved:ledger_listed_unported', merge(Lc.get('reg_unported', []) + inter(Lc.get('split_code', []), Lc.get('reg_window', []))))
        take('6 unknown', 'unresolved:shape_no_ref(T4)', cr.get('T4_shape_noref', []))
        take('6 unknown', 'unresolved:shape_no_base(T5)', cr.get('T5_shape_noeval', []))
        take('6 unknown', 'unknown', rest)
        assert sum(lab.values()) == n, (c, sum(lab.values()), n)
        out[c] = dict(file_bytes=n, labels=dict(lab), kinds={k: dict(v) for k, v in kinds.items()},
                      code_over_audit_data=conflicts[c])
        spans[c] = sp
    return out, spans

# Neighbour inference is deliberately one round: newly admitted slivers never
# become witnesses for other slivers. Validation removes the labels in each hole
# and uses only the two immediate surviving bytes, exactly as production does.
NONCODE_LABELS = {'4 proven_data', '4 noncode_typing_pending', '5 padding_leftover'}

def neighbour_choice(b, s, e, left, right):
    if not (0 < s < e < len(b) and e - s < 16): return None
    if left not in NONCODE_LABELS or right not in NONCODE_LABELS: return None
    # Also protect a return instruction split by an unaligned hole boundary.
    if any(u32(b, at) == 0x03E00008 for at in range(s // 4 * 4, (e + 3) // 4 * 4, 4)
           if at + 4 <= len(b)): return None
    target = left if left == right else '4 noncode_typing_pending'
    return target

def flat_spans(sp):
    return sorted((s, e, label, kind) for label, rs in sp.items() for s, e, kind in rs)

def neighbour_candidates(b, sp):
    flat = flat_spans(sp); found = []
    for i, (s, e, label, kind) in enumerate(flat):
        if label != '6 unknown' or not i or i + 1 == len(flat): continue
        left, right = flat[i - 1], flat[i + 1]
        if left[1] != s or right[0] != e: continue
        target = neighbour_choice(b, s, e, left[2], right[2])
        if target: found.append((s, e, target, left[2], right[2]))
    return found

def validate_neighbours(L, B, spans, root):
    import random
    rng = random.Random(0x121C2)
    per = {}; total = collections.Counter(); targets = collections.defaultdict(collections.Counter)
    for c in CONTS:
        b = (Path(root) / FILES[c]).read_bytes(); flat = flat_spans(spans[c]); starts = [x[0] for x in flat]
        # C extent bytes (including tables) are conservatively code for this check.
        proven = merge(L[c].get('c_row', [])); ps = [x[0] for x in proven]
        prefix = [0]
        for a, z in proven: prefix.append(prefix[-1] + z - a)
        def before(at):
            i = bisect.bisect_right(ps, at) - 1
            return prefix[i] + min(at - proven[i][0], proven[i][1] - proven[i][0]) if i >= 0 else 0
        def label_at(at):
            if not (0 <= at < len(b)): return None
            i = bisect.bisect_right(starts, at) - 1
            return flat[i][2] if i >= 0 and at < flat[i][1] else None
        classes = collections.defaultdict(collections.Counter)
        def trial(s, e, cls):
            if not (0 < s < e < len(b)): return
            code = before(e) - before(s); n = e - s
            rec = classes[cls]; rec['holes'] += 1; rec['bytes'] += n; rec['proven_C_bytes'] += code
            target = neighbour_choice(b, s, e, label_at(s - 1), label_at(e))
            if target:
                rec['admitted_holes'] += 1; rec['admitted_bytes'] += n
                rec['mislabelled_proven_C_bytes'] += code; rec['noncode_bytes'] += n - code
                targets[target]['tp'] += n - code; targets[target]['fp'] += code
        # Independent holes, no training/validation contamination or propagation.
        row_holes = [(s, e) for s, e, rid in G.get('rowmeta', {}).get(c, [])] or proven
        for a, z in row_holes:
            for n in (4, 8, 12):
                if z - a >= n + 2:
                    for _ in range(2):
                        s = rng.randrange(a + 1, z - n); trial(s, s + n, 'proven_C_interior')
            if z - a < 16: trial(a, z, 'whole_short_C')
        typed = merge([iv for k in LEDGER_TYPED for iv in L[c].get(k, [])]
                      + [iv for k in FMT for iv in B[c]['fmt'][k]])
        typed = subtract(typed, proven)
        for a, z in typed:
            for n in (4, 8, 12):
                if z - a >= n + 2:
                    s = rng.randrange(a + 1, z - n); trial(s, s + n, 'typed_data_interior')
        # Test all C/non-code borders and non-code/non-code class borders.
        for left, right in zip(flat, flat[1:]):
            if left[1] != right[0]: continue
            lc, rc = left[2], right[2]
            if lc[0] == '1' and rc in NONCODE_LABELS or rc[0] == '1' and lc in NONCODE_LABELS:
                cls = 'C_data_border'
            elif lc in NONCODE_LABELS and rc in NONCODE_LABELS and lc != rc:
                cls = 'noncode_class_border'
            else: continue
            at = right[0]
            for n in (4, 8, 12):
                for k in range(1, n): trial(at - k, at - k + n, cls)
        # These classes exercise the same-padding and same-pending branches.
        for a, z, label, kind in flat:
            if label not in ('5 padding_leftover', '4 noncode_typing_pending'): continue
            for n in (4, 8, 12):
                if z - a >= n + 2:
                    s = rng.randrange(a + 1, z - n); trial(s, s + n, 'padding_interior' if label[0] == '5' else 'pending_noncode_interior')
        per[c] = {k: dict(v) for k, v in sorted(classes.items())}
        for cls, counts in classes.items():
            for k, v in counts.items(): total[cls + '|' + k] += v
    class_names = sorted({k.split('|')[0] for k in total})
    classes = {cls: {k.split('|')[1]: v for k, v in total.items() if k.startswith(cls + '|')} for cls in class_names}
    bytarget = {}
    for target, counts in sorted(targets.items()):
        n = counts['tp'] + counts['fp']; precision = counts['tp'] / n if n else None
        bytarget[target] = dict(counts, precision=precision, admitted=bool(n and precision >= ADMIT_PRECISION))
    return dict(schema='azure-clean.census-neighbour-validation.v1', seed='0x121C2',
                rule='independent 4/8/12-byte holes; immediate neighbours; no overlapping aligned jr ra; no propagation',
                minimum_precision=ADMIT_PRECISION, classes=classes, per_container=per, targets=bytarget,
                mislabelled_proven_C_bytes=sum(v.get('mislabelled_proven_C_bytes', 0) for v in classes.values()),
                admitted_labels=[k for k, v in bytarget.items() if v['admitted']])

def apply_neighbours(lab, spans, validation, root):
    applied = {}
    for c in CONTS:
        b = (Path(root) / FILES[c]).read_bytes()
        candidates = [x for x in neighbour_candidates(b, spans[c]) if x[2] in validation['admitted_labels']]
        taken = { (s, e) for s, e, *_ in candidates }
        sp = spans[c]
        sp['6 unknown'] = [x for x in sp.get('6 unknown', []) if tuple(x[:2]) not in taken]
        for s, e, label, left, right in candidates:
            sp[label].append([s, e, 'sliver_between_noncode'])
        counts = collections.Counter(); kinds = collections.defaultdict(collections.Counter)
        for label, rows in sp.items():
            for s, e, kind in rows: counts[label] += e - s; kinds[label][kind] += e - s
        lab[c]['labels'] = dict(counts); lab[c]['kinds'] = {k: dict(v) for k, v in kinds.items()}
        applied[c] = dict(spans=len(candidates), bytes=sum(e - s for s, e, *_ in candidates),
                          labels=dict(collections.Counter({label: sum(e - s for s, e, t, *_ in candidates if t == label)
                                                           for label in validation['admitted_labels']})))
    return applied

def heur_only(L):
    """remaining.py's 'heuristic-only (estimated_code)' set, recomputed (live ledger, no hold lists)."""
    H = {}
    for c in CONTS:
        Lc = L[c]
        data_all = merge(Lc.get('reg_data_excluded', []) + Lc.get('data_row', []) + Lc.get('split_data', []))  # as remaining.py
        occ = merge(Lc.get('c_row', []) + Lc.get('instance_proven', []) + inter(Lc.get('split_code', []), Lc.get('reg_window', []))
                    + Lc.get('reg_unported', []) + Lc.get('reg_sdk_asm', []) + data_all)
        H[c] = subtract(Lc.get('reg_estimated_code', []), occ)
    return H

def admitted_tiers(validation):
    """Gate on exact counts; displayed rounded precision is not an admission test."""
    out = []
    for tier in ADMIT:
        d = validation['detectors'][tier]
        n = d['tp'] + d['fp_struct'] + d['fp_entropy']
        if n and d['tp'] / n >= ADMIT_PRECISION:
            out.append(tier)
    return out


def apply_read_evidence(L, root, binroot, paths):
    """Check proposed bounded read records against source and retail bytes."""
    binaries = {}; source_hashes = {}; receipts = []
    for path in paths:
        path = Path(path); records = recs(path)
        for r in records:
            c = r['container']; s = num(r['foff']); e = s + num(r['size'])
            if c not in binaries: binaries[c] = (Path(binroot) / FILES[c]).read_bytes()
            b = binaries[c]
            assert 0 <= s < e <= len(b), 'read evidence out of bounds'
            assert hashlib.sha256(b[s:e]).hexdigest() == r['bytes_sha256'], 'read evidence bytes changed'
            source = r['source']; sourcepath = Path(root) / source
            assert not Path(source).is_absolute() and '..' not in Path(source).parts
            if source not in source_hashes: source_hashes[source] = hashlib.sha256(sourcepath.read_bytes()).hexdigest()
            assert source_hashes[source] == r['source_sha256'], 'read evidence source changed'
            if r.get('read_foff') is not None:
                at = num(r['read_foff'])
                assert size(inter([[at, at + 4]], L[c].get('c_row', []))) == 4, 'read is outside matched C'
                word = u32(b, at)
                assert hashlib.sha256(b[at:at + 4]).hexdigest() == r['read_sha256'] and word >> 26 in LOADS, 'read instruction changed'
            L[c]['matched_c_read'].append([s, e])
        receipts.append(dict(path=path.name, sha256=hashlib.sha256(path.read_bytes()).hexdigest(), records=len(records)))
    return receipts


def apply_masked_prefixes(lab, spans, L, prefix_sets, validation, admitted):
    """Recover only unresolved bytes, preserving all established label precedence.

    The mask is code evidence. A differing ordinary member offset remains a C
    transfer hold even when this independently measured detector admits code.
    """
    result = {}; enabled = validation['admitted'] and 'T1_twin' in admitted
    for c in CONTS:
        sp = spans[c]; unknown = merge([r[:2] for r in sp.get('6 unknown', [])])
        got = inter(unknown, merge(prefix_sets[c][0] + prefix_sets[c][1])) if enabled else []
        sp['6 unknown'] = [[a, b, k] for s, e, k in sp.get('6 unknown', []) for a, b in subtract([[s, e]], got)]
        for a, b in got: sp['3 strongly_code'].append([a, b, 'T1_twin:complete_masked_prologue_prefix'])
        counts = collections.Counter(); kinds = collections.defaultdict(collections.Counter)
        for label, rows in sp.items():
            for a, b, k in rows: counts[label] += b - a; kinds[label][k] += b - a
        lab[c]['labels'] = dict(counts); lab[c]['kinds'] = {k: dict(v) for k, v in kinds.items()}
        audit = merge([x for k in LEDGER_AUDIT for x in L[c].get(k, [])])
        lab[c]['code_over_audit_data']['complete_masked_prefix'] = size(inter(got, audit))
        result[c] = dict(spans=len(got), bytes=size(got), intervals=got)
    return result

def apply_replayed_code(L, root, binroot, paths):
    """Admit only the recorded prefix of a checked complete compiled twin.

    Existing short C rows can overlap the donor's return, preventing a new full
    C row. The full strict replay still proves the missing prefix is code.
    """
    binaries = {}; source_hashes = {}; receipts = []
    rows = {r['id']: r for r in recs(Path(root) / 'ledger/rows.jsonl')}
    for path in paths:
        records = recs(path)
        for r in records:
            c = r['container']; s = num(r['foff']); e = s + num(r['size']); end = s + num(r['complete_size'])
            assert r['size'] < 16 and e < end and r['strict_replay'] == 'MATCH'
            donor = rows[r['donor']]; source = r['source']
            assert source == 'src/' + c + '/' + donor['func'] + '.c'
            if source not in source_hashes: source_hashes[source] = hashlib.sha256((Path(root) / source).read_bytes()).hexdigest()
            assert source_hashes[source] == r['source_sha256'], 'replayed donor source changed'
            if c not in binaries: binaries[c] = (Path(binroot) / FILES[c]).read_bytes()
            b = binaries[c]
            assert 0 <= s < e < end <= len(b)
            assert hashlib.sha256(b[s:end]).hexdigest() == r['complete_bytes_sha256'], 'replayed complete body changed'
            assert end - s == num(donor['size']), 'not a complete donor extent'
            ds = num(donor['foff']); original = b[ds:ds + end - s]; target = b[s:end]
            assert hashlib.sha256(original).hexdigest() == r['donor_bytes_sha256']
            reloc = {num(v['offset']): v for v in r['relocations']}
            for at in range(0, len(target), 4):
                a, z = u32(original, at), u32(target, at)
                if a == z: continue
                v = reloc.get(at); assert v, 'changed word is not an ELF relocation'
                mask = 0xffff if v['type'] in (5, 6) else 0x3ffffff if v['type'] == 4 else 0
                assert mask and a & ~mask == z & ~mask, 'non-relocation instruction bits changed'
            assert is_prologue(u32(b, e)), 'prefix no longer precedes the compiled prologue'
            L[c]['replayed_twin_prefix'].append([s, e])
        receipts.append(dict(path=Path(path).name, sha256=hashlib.sha256(Path(path).read_bytes()).hexdigest(), records=len(records)))
    return receipts

def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default='.'); ap.add_argument('--bin-root', help='where work/disc/containers + baserom live (default --root)')
    ap.add_argument('--json'); ap.add_argument('--md'); ap.add_argument('--spans-dir')
    ap.add_argument('--typed-data', action='append', default=[], help='checked proposed matched-C read records')
    ap.add_argument('--replayed-code', action='append', default=[], help='checked strict full-body twin prefix evidence')
    ap.add_argument('--bank-map', help='checked loader map produced by bankmap.py')
    ap.add_argument('--analysis-cache', help='gzip pickle of detector output; keep under ignored spans/')
    ap.add_argument('--baseline-json'); ap.add_argument('--baseline-md')
    ap.add_argument('--procs', type=int, default=5); ap.add_argument('--top', type=int, default=25)
    a = ap.parse_args(); root = Path(a.bin_root or a.root)   # binaries
    L, rowmeta = ledger_layers(Path(a.root))
    applied_reads = apply_read_evidence(L, a.root, root, a.typed_data)
    applied_code = apply_replayed_code(L, a.root, root, a.replayed_code)
    if a.bank_map:
        bankmaps = json.loads(Path(a.bank_map).read_text())['maps']
        G['loaded_extents'] = {c: merge([[m['foff'], m['end']] for m in bankmaps if m['container'] == c and m.get('admissible', True)]) for c in CONTS}
    S, H = shingle_sets(root, rowmeta)
    G.update(S0=S[0], S1=S[1], H0=H[0], H1=H[1], root=str(root), rowmeta=rowmeta)
    with Pool(a.procs) as pool:
        B = dict(pool.map(binary_pass, [(c, str(root / FILES[c])) for c in CONTS]))
    V = validate(L, B, fold_ivs(rowmeta))
    admitted = admitted_tiers(V)
    if a.analysis_cache:
        with gzip.open(a.analysis_cache, 'wb') as f: pickle.dump(dict(B=B, L=L, rowmeta=rowmeta, V=V), f, protocol=5)
    from masked_prefix_probe import validate as validate_prefix
    prefix_sets = {c: {f: B[c]['crit'].get('D5_prefix_fold' + str(f), []) for f in (0, 1)} for c in CONTS}
    prefix_validation = validate_prefix(L, B, rowmeta, prefix_sets)
    lab, spans = label(L, B, admitted)
    prefix_applied = apply_masked_prefixes(lab, spans, L, prefix_sets, prefix_validation, admitted)
    neighbour_validation = validate_neighbours(L, B, spans, root)
    neighbour_applied = apply_neighbours(lab, spans, neighbour_validation, root)
    # unknown characterisation
    with Pool(a.procs) as pool:
        ch = dict(pool.map(characterise, [(c, str(root / FILES[c]), [s[:2] for s in spans[c]['6 unknown'] if s[2] == 'unknown' or s[2].startswith('unresolved:')]) for c in CONTS]))
    unk = {}
    for c in CONTS:
        bk = collections.Counter()
        for s in ch[c]: bk[s[2]] += s[1] - s[0]
        top = sorted(ch[c], key=lambda s: -(s[1] - s[0]))[:a.top]
        unk[c] = dict(buckets=dict(bk.most_common()), top=[dict(foff=hex(s[0]), bytes=s[1] - s[0], kind=s[2], zero=s[3], valid=s[4],
                      jrra=s[5], ptr=s[6], sjis=s[7]) for s in top])
    def landing(sets):
        out = {}
        for c in CONTS:
            cc = collections.Counter()
            for lbl, iv in spans[c].items():
                bykind = collections.defaultdict(list)
                for s, e, k in iv: bykind[k].append([s, e])
                for k, v in bykind.items():
                    x = size(inter(sets[c], v))
                    if x: cc[lbl + ' / ' + k] += x
            out[c] = dict(total=size(sets[c]), labelled=dict(cc.most_common()))
        return out
    LU = {c: merge(L[c].get('reg_unported', []) + subtract(inter(L[c].get('split_code', []), L[c].get('reg_window', [])),
                                                         L[c].get('c_row', []))) for c in CONTS}
    lu = landing(LU)
    # heuristic-only bytes: how each is labelled now
    HO = heur_only(L); hb = {}
    for c in CONTS:
        cc = collections.Counter()
        for lbl, iv in spans[c].items():
            bykind = collections.defaultdict(list)
            for s, e, k in iv: bykind[k].append([s, e])
            for k, v in bykind.items():
                x = size(inter(HO[c], v))
                if x: cc[lbl + ' / ' + k] += x
        hb[c] = dict(total=size(HO[c]), labelled=dict(cc.most_common()))
    # unresolved unknown bytes by the best code evidence the detectors have for them
    ub = {}
    for c in CONTS:
        U = merge([s[:2] for s in spans[c]['6 unknown'] if s[2] == 'unknown' or s[2].startswith('unresolved:')]); cr = B[c]['crit']; cc = collections.OrderedDict()
        for k in ('T4_shape_noref', 'T5_shape_noeval', 'D2_bad_frame', 'D1_seg'):
            x = inter(U, cr.get(k, [])); cc[k] = size(x); U = subtract(U, x)
        cc['no segment (valid run, no jr ra)'] = size(U); ub[c] = cc
    # overlaps between evidence layers (precedence hides them in the label table)
    ov = {}
    pairs = [('c_row', 'instance_proven'), ('c_row', 'instance_partial'), ('c_row', 'reg_data_excluded'), ('c_row', 'split_data'),
             ('c_row', 'data_row'), ('c_row', 'rodata_owner'), ('c_row', 'sdk_object'), ('instance_proven', 'reg_data_excluded'),
             ('instance_partial', 'reg_data_excluded'), ('instance_proven', 'instance_partial')]
    for c in CONTS:
        d = {f'{x}&{y}': size(inter(L[c].get(x, []), L[c].get(y, []))) for x, y in pairs}
        ov[c] = {k: v for k, v in d.items() if v}
    snapshot = Path(a.root) / 'config/census/snapshot.json'
    rev = json.loads(snapshot.read_text())['base'] if snapshot.exists() else 'working tree'
    res = dict(schema='azure-clean.byte-census.v2', ledger_rev=rev, applied_read_evidence=applied_reads, applied_replayed_code=applied_code, policy='OWNER decision 57 (2026-10-16)', admitted_tiers=admitted, admit_precision=ADMIT_PRECISION,
               unknown_by_code_evidence=ub, layer_overlaps=ov, ledger_listed_unported=lu,
               binary_stats={c: B[c]['stats'] for c in CONTS},
               census=lab, validation=V, neighbour_validation=neighbour_validation, neighbour_applied=neighbour_applied, masked_prefix_validation=prefix_validation, masked_prefix_applied=prefix_applied, unknown=unk, heuristic_only=hb)
    if a.baseline_json or a.baseline_md:
        before, _ = label(L, B, [t for t in admitted if t in ADMIT[:3]], decision57=False)
        br = dict(res, census=before, neighbour_validation=None, neighbour_applied=None, admitted_tiers=[t for t in admitted if t in ADMIT[:3]], policy='reference policy before decision 57')
        if a.baseline_json: Path(a.baseline_json).write_text(json.dumps(br, indent=1) + '\n')
        if a.baseline_md: Path(a.baseline_md).write_text(render_md(br))
    if a.json: Path(a.json).write_text(json.dumps(res, indent=1) + '\n')
    if a.md: Path(a.md).write_text(render_md(res))
    if a.spans_dir:
        d = Path(a.spans_dir); d.mkdir(parents=True, exist_ok=True)
        for c in CONTS: (d / f'{c}.spans.json').write_text(json.dumps(spans[c]))
    if not a.json and not a.md: sys.stdout.write(render_md(res))

def render_md(r):
    LB = ['1 proven_code', '2 library_code', '3 strongly_code', '4 proven_data', '4 noncode_typing_pending', '5 padding_leftover', '6 unknown']
    o = ['# Byte census', '', f"ledger inputs: {r['ledger_rev']}", '', f"admitted label-3 tiers: {', '.join(r['admitted_tiers']) or '(none)'} (precision >= {r['admit_precision']})", '',
         '| container | bytes | ' + ' | '.join(LB) + ' |', '|---|---:|' + '---:|' * len(LB)]
    tot = collections.Counter()
    for c, x in r['census'].items():
        o.append(f"| {c} | {x['file_bytes']:,} | " + ' | '.join(f"{x['labels'].get(l, 0):,}" for l in LB) + ' |')
        tot['n'] += x['file_bytes']; tot.update({l: x['labels'].get(l, 0) for l in LB})
    o.append(f"| **total** | {tot['n']:,} | " + ' | '.join(f"{tot[l]:,}" for l in LB) + ' |')
    o += ['', r.get('policy', ''), '', 'Decision 57: label 4 noncode_typing_pending is terminal non-code; label 6 is the unresolved remainder. High entropy alone does not prove runtime placement or leftover status. T4/T5 remain visible as strongly code (shape only) evidence kinds; partial instances stay in label 1.', '',
          '| container | non-code pending: high entropy | non-code pending: decode | unresolved |', '|---|---:|---:|---:|']
    t6 = collections.Counter()
    for c, x in r['census'].items():
        k6 = x['kinds'].get('6 unknown', {}); kp = x['kinds'].get('4 noncode_typing_pending', k6)
        v6 = [sum(v for k, v in kp.items() if k.startswith('noncode:high_entropy')), kp.get('noncode:decode', 0),
              sum(b for k, b in k6.items() if k == 'unknown' or k.startswith('unresolved:'))]
        t6.update({0: v6[0], 1: v6[1], 2: v6[2]})
        o.append(f"| {c} | {v6[0]:,} | {v6[1]:,} | {v6[2]:,} |")
    o.append(f"| **total** | {t6[0]:,} | {t6[1]:,} | {t6[2]:,} |")
    o += ['', '## Strongly code sub-tiers', '', '| container | reference/twin | shape only |', '|---|---:|---:|']
    for c, x in r['census'].items():
        shape = sum(v for k, v in x['kinds'].get('3 strongly_code', {}).items() if k.startswith('strongly code (shape only):'))
        o.append(f"| {c} | {x['labels'].get('3 strongly_code', 0) - shape:,} | {shape:,} |")
    o += ['', '## Evidence kinds per label (all containers)', '']
    kk = collections.defaultdict(collections.Counter)
    for c, x in r['census'].items():
        for l, d in x['kinds'].items(): kk[l].update(d)
    for l in LB:
        if l in kk: o.append(f"- **{l}**: " + '; '.join(f"{k} {v:,}" for k, v in kk[l].most_common()))
    o += ['', '## Code over split-audit data (admitted tiers on reg_data_excluded/split_data bytes: ledger fix items)', '']
    for c, x in r['census'].items():
        if any(x['code_over_audit_data'].values()): o.append(f"- **{c}**: " + '; '.join(f"{k} {b:,}" for k, b in x['code_over_audit_data'].items() if b))
    nv = r.get('neighbour_validation')
    if nv:
        o += ['', '## Neighbour rule validation', '', 'Independent holes use immediate surviving neighbours; no iterative propagation. A return word overlapping a hole blocks admission.', '',
              '| class | holes | tested bytes | admitted bytes | mislabelled proven-C bytes |', '|---|---:|---:|---:|---:|']
        for cls, d in nv['classes'].items():
            o.append(f"| {cls} | {d['holes']:,} | {d['bytes']:,} | {d.get('admitted_bytes', 0):,} | {d.get('mislabelled_proven_C_bytes', 0):,} |")
        o += ['', 'Targets: ' + '; '.join(f"{k}: precision={d['precision']}, admitted={d['admitted']}" for k, d in nv['targets'].items()), '',
              'Production: ' + '; '.join(f"{c}: {d['spans']:,} spans / {d['bytes']:,} B" for c, d in r['neighbour_applied'].items())]
    pv = r.get('masked_prefix_validation')
    if pv:
        o += ['', '## Complete masked prologue prefixes', '',
              f"Cross-fold proven-C bytes {pv['totals']['tp']:,}; structured FP {pv['totals']['fp_struct']:,}; entropy FP {pv['totals']['fp_entropy']:,}; precision {pv['precision']}; admitted {pv['admitted']}.", '',
              'Only unresolved bytes are recovered; C transfer still requires every differing word to be an actual ELF relocation.']
    v = r['validation']; t = v['totals']
    o += ['', '## Validation (detectors blind)', '',
          f"P (C rows minus typed data) {t['P']:,} B; INS (proven+partial instances) {t['INS']:,} B; negatives: N_struct (typed ledger + "
          f"format data) {t['N_struct']:,} B, N_entropy {t['N_entropy']:,} B; N_audit (contested split-audit data) {t['N_audit']:,} B. "
          f"Overlay C-row starts that are detected segment entries: {t['row_entry_hits'][0]:,}/{t['row_entry_hits'][1]:,}", '',
          '| detector | recall P % | recall INS % | FP struct B | FP entropy B | audit-data hits B | precision |', '|---|---:|---:|---:|---:|---:|---:|']
    for k, d in v['detectors'].items():
        o.append(f"| {k} | {d['recall_P']} | {d['recall_INS']} | {d['fp_struct']:,} | {d['fp_entropy']:,} | {d['audit_hits']:,} | {d['precision']} |")
    u = v['admitted_union']
    o += ['', f"Reference-backed rule (T1 or T2 or T3) validation recall: P {u['recall_P']}%, P_code {u['recall_P_code']}%. Misses on P by first cause: "
          + '; '.join(f"{k} {b:,}" for k, b in u['misses'].items())]
    o += ['', f"Data / non-code detectors. on P = inside C-row extents (rows also hold jump tables and rodata); on P_code = inside "
          f"code-shaped C bytes (P within framed/leaf segments, {t['P_code']:,} B): the real false-positive measure.", '',
          '| data detector | total B | on P | on P_code (FP) | on INS | on audit data |', '|---|---:|---:|---:|---:|---:|']
    for k, d in v['formats'].items():
        o.append(f"| {k} | {d['total']:,} | {d['on_P']:,} | {d['on_P_code']:,} | {d['on_INS']:,} | {d['on_audit']:,} |")
    o += ['', '## Unknown, by characterisation', '']
    for c, u in r['unknown'].items():
        o.append(f"- **{c}**: " + '; '.join(f"{k} {b:,}" for k, b in u['buckets'].items()))
    o += ['', '## Overlaps between ledger layers (bytes; precedence resolves them, listed so none is hidden)', '']
    for c, d in r['layer_overlaps'].items():
        if d: o.append(f"- **{c}**: " + '; '.join(f"{k} {v:,}" for k, v in d.items()))
    o += ['', '## Unresolved unknown bytes by best code evidence (first match: T4 shape+no ref, T5 shape+no base, bad frame, other segment)', '']
    for c, u in r['unknown_by_code_evidence'].items():
        o.append(f"- **{c}**: " + '; '.join(f"{k} {b:,}" for k, b in u.items() if b))
    o += ['', '## Heuristic-only (estimated_code, as remaining.py) -> census label', '']
    for c, h in r['heuristic_only'].items():
        if h['total']: o.append(f"- **{c}** {h['total']:,} B: " + '; '.join(f"{k} {b:,}" for k, b in h['labelled'].items()))
    o += ['', '## Ledger-listed unported code (coverage_regions unported + split code outside C, in windows) -> census label', '']
    for c, h in r['ledger_listed_unported'].items():
        if h['total']: o.append(f"- **{c}** {h['total']:,} B: " + '; '.join(f"{k} {b:,}" for k, b in h['labelled'].items()))
    o += ['', '## Top unknown spans', '', '| container | foff | bytes | kind | zero | valid | jr ra | ptr | sjis |', '|---|---|---:|---|---:|---:|---:|---:|---:|']
    for c, u in r['unknown'].items():
        for s in u['top'][:10]:
            o.append(f"| {c} | {s['foff']} | {s['bytes']:,} | {s['kind']} | {s['zero']} | {s['valid']} | {s['jrra']} | {s['ptr']} | {s['sjis']} |")
    return '\n'.join(o) + '\n'

if __name__ == '__main__':
    main()
