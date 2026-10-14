#!/usr/bin/env python3
"""Find shared MIPS-I retail windows and recover their C provenance.

All writes are below --workspace. No gates, git writes, or tree mutation.
Build an inventory once, then reuse it for single or batch queries. Retrieval
uses address/branch-masked instruction seeds; verification requires a bijective
register renaming across the ENTIRE returned block (zero/gp/sp/ra stay fixed).
Constants and member offsets survive unless --ignore-field-offsets is selected.
External compiled objects are shape evidence, never retail match certificates.
"""
from __future__ import annotations
import argparse
import bisect
import collections
import difflib
import gzip
import hashlib
import json
import os
from pathlib import Path
import re
import shlex
import shutil
import struct
import subprocess
import sys
import time

sys.dont_write_bytecode = True
VERSION = 'sibling-find-2'
REGS = 'zero at v0 v1 a0 a1 a2 a3 t0 t1 t2 t3 t4 t5 t6 t7 s0 s1 s2 s3 s4 s5 s6 s7 t8 t9 k0 k1 gp sp fp ra'.split()
FIXED = {0, 28, 29, 31}
PIN_RE = re.compile(r'\bASM_(?:REG|KEEP|KEEP_NV|USE|USE_NV|KEEP_DEP_NV|MEM_BARRIER|SCHED_BARRIER|TAILSLOT_PIN)\s*\(')
TOKEN_RE = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|/\*.*?\*/|//[^\n]*', re.S)
CONTAINERS = {'main': 'MAIN_MAIN.BIN', 'town': 'TOWN_TOWN.BIN',
              'dungeon': 'DUNGEON_DUNGEON.BIN', 'ovmovie': 'OVMOVIE_OVMOVIE.BIN'}


def sha(b):
    return hashlib.sha256(b).hexdigest()


def stripped(text):
    # Blank comments AND literal contents, preserving positions and newlines.
    # A printf("ASM_KEEP(x)") is not a pin; braces in strings are not C scopes.
    return TOKEN_RE.sub(lambda m: ''.join('\n' if c=='\n' else ' ' for c in m[0]),text)


def c89(text):
    return TOKEN_RE.sub(lambda m: '/*' + m[0][2:].replace('*/', '* /') + ' */'
                       if m[0].startswith('//') else m[0], text)


def words(blob):
    return list(struct.unpack('<' + 'I' * (len(blob) // 4), blob[:len(blob)//4*4]))


def packed(seq):
    return struct.pack('<' + 'I' * len(seq), *seq)


def jsonl(path):
    with Path(path).open() as f:
        for line in f:
            if line.strip():
                yield json.loads(line)


def read_elf(path):
    """ELF32 LE symbols/alloc sections/REL records; no external imports."""
    b = Path(path).read_bytes()
    if b[:6] != b'\x7fELF\x01\x01':
        raise ValueError('expected ELF32 little endian: ' + str(path))
    off, = struct.unpack_from('<I', b, 0x20)
    width, n, si = struct.unpack_from('<HHH', b, 0x2e)
    hdr = [struct.unpack_from('<10I', b, off + i*width) for i in range(n)]
    def payload(h):
        return b[h[4]:h[4]+h[5]] if h[1] != 8 else bytes(h[5])
    def name(tab, start):
        return tab[start:tab.index(b'\0', start)].decode('latin1')
    tab = payload(hdr[si])
    names = [name(tab, h[0]) for h in hdr]
    sections = {names[i]: payload(h) for i, h in enumerate(hdr) if h[2] & 2 and h[1] in (1, 8)}
    syms, symbols = [], {}
    for h in hdr:
        if h[1] != 2:
            continue
        tab = payload(hdr[h[6]])
        raw = payload(h)
        for j in range(0, len(raw), 16):
            ni, val, size, info, other, sec = struct.unpack_from('<IIIBBH', raw, j)
            nm = name(tab, ni) if ni else ''
            sc = names[sec] if 0 < sec < n else None
            s = {'name': nm, 'value': val, 'size': size, 'type': info & 15,
                 'bind': info >> 4, 'section': sc, 'shndx': sec}
            syms.append(s)
            if nm and (info & 15) not in (3, 4):
                symbols[nm] = s
    relocs = []
    types = {2: '32', 4: '26', 5: 'HI16', 6: 'LO16', 7: 'GPREL16'}
    for h in hdr:
        if h[1] != 9:
            continue
        sec = names[h[7]]
        if sec not in sections:
            continue
        raw = payload(h)
        rr = [struct.unpack_from('<II', raw, j) for j in range(0, len(raw), 8)]
        for j, (loc, info) in enumerate(rr):
            s, typ = syms[info >> 8], types.get(info & 255, 'unknown')
            w, = struct.unpack_from('<I', sections[sec], loc)
            a = w if typ == '32' else ((w & 0x3ffffff) << 2 if typ == '26' else sext(w & 65535))
            if typ == 'HI16':
                lo = next((struct.unpack_from('<I', sections[sec], q)[0] & 65535
                           for q, k in rr[j+1:] if k >> 8 == info >> 8 and k & 255 == 6), None)
                a = ((w & 65535) << 16) + (sext(lo) if lo is not None else 0)
            relocs.append({'section': sec, 'offset': loc, 'type': typ, 'symbol': s, 'addend': a})
    return {'sections': sections, 'symbols': symbols, 'relocs': relocs}


def sext(x):
    return x - 65536 if x & 32768 else x


def regfields(w):
    """Register-bearing bitfields ONLY. shamt/REGIMM/cop selectors are data."""
    op, fn = w >> 26, w & 63
    if op == 0:
        if fn in (0, 2, 3): return (16, 11)
        if fn in (4, 6, 7): return (21, 16, 11)
        if fn == 8: return (21,)
        if fn == 9: return (21, 11)
        if fn in (12, 13): return ()
        if fn in (16, 18): return (11,)
        if fn in (17, 19): return (21,)
        if fn in (24, 25, 26, 27): return (21, 16)
        if fn in (32, 33, 34, 35, 36, 37, 38, 39, 42, 43): return (21, 16, 11)
        return ()                       # unknown encodings are literal
    if op in (2, 3): return ()
    if op in (1, 6, 7): return (21,)
    if op in (4, 5): return (21, 16)
    if op == 15: return (16,)
    if op in (16, 17, 18, 19):
        return (16,) if ((w >> 21) & 31) in (0, 2, 4, 6) else ()
    if op in (8, 9, 10, 11, 12, 13, 14): return (21, 16)
    if op in (32, 33, 34, 35, 36, 37, 38, 40, 41, 42, 43, 46): return (21, 16)
    if op in (48, 49, 50, 51, 56, 57, 58, 59): return (21,)  # cop register index survives
    return ()


def decode(w, i=0):
    op, rs, rt, rd, sa, fn, imm = w >> 26, (w >> 21)&31, (w >> 16)&31, (w >> 11)&31, (w >> 6)&31, w&63, w&65535
    r = lambda x: REGS[x]
    if w == 0: return 'nop'
    if op == 0:
        shifts = {0:'sll',2:'srl',3:'sra'}
        if fn in shifts: return f'{shifts[fn]} {r(rd)},{r(rt)},{sa}'
        shifts = {4:'sllv',6:'srlv',7:'srav'}
        if fn in shifts: return f'{shifts[fn]} {r(rd)},{r(rt)},{r(rs)}'
        if fn == 8: return f'jr {r(rs)}'
        if fn == 9: return f'jalr {r(rd)},{r(rs)}'
        if fn in (16,18): return f'{"mfhi" if fn==16 else "mflo"} {r(rd)}'
        if fn in (17,19): return f'{"mthi" if fn==17 else "mtlo"} {r(rs)}'
        ops = {24:'mult',25:'multu',26:'div',27:'divu'}
        if fn in ops: return f'{ops[fn]} {r(rs)},{r(rt)}'
        ops = {32:'add',33:'addu',34:'sub',35:'subu',36:'and',37:'or',38:'xor',39:'nor',42:'slt',43:'sltu'}
        if fn in ops: return f'{ops[fn]} {r(rd)},{r(rs)},{r(rt)}'
    if op in (2,3): return f'{"jal" if op==3 else "j"} 0x{(w&0x3ffffff)<<2:08x}'
    if op in (4,5): return f'{"beq" if op==4 else "bne"} {r(rs)},{r(rt)},word {i+1+sext(imm)}'
    if op in (1,6,7):
        mn = {0:'bltz',1:'bgez',16:'bltzal',17:'bgezal'}.get(rt,'regimm') if op==1 else ('blez' if op==6 else 'bgtz')
        return f'{mn} {r(rs)},word {i+1+sext(imm)}'
    if op == 15: return f'lui {r(rt)},0x{imm:04x}'
    ops = {8:'addi',9:'addiu',10:'slti',11:'sltiu',12:'andi',13:'ori',14:'xori'}
    if op in ops: return f'{ops[op]} {r(rt)},{r(rs)},{hex(imm) if op in (12,13,14) else sext(imm)}'
    ops = {32:'lb',33:'lh',34:'lwl',35:'lw',36:'lbu',37:'lhu',38:'lwr',40:'sb',41:'sh',42:'swl',43:'sw',46:'swr'}
    if op in ops: return f'{ops[op]} {r(rt)},{sext(imm)}({r(rs)})'
    return f'.word 0x{w:08x}'


def address_luis(ws,rm):
    """A numeric RAM-shaped high half alone is not address evidence.
    In particular 0x80000000 is commonly a data/sign mask. Follow candidate
    definitions to an actual memory base or indirect jump before erasing them.
    Relocations remain authoritative even without a dereference in this body.
    """
    origins={};admitted=set()
    for i,w in enumerate(ws):
        op,rs,rt,rd,fn=w>>26,(w>>21)&31,(w>>16)&31,(w>>11)&31,w&63
        if op in (32,33,34,35,36,37,38,40,41,42,43,46,48,49,50,51,56,57,58,59):
            admitted.update(origins.get(rs,()))
        if op==0 and fn in (8,9):admitted.update(origins.get(rs,()))
        if op==15:
            imm=w&65535;origins.pop(rt,None)
            candidate=0x8000<=imm<=0x81ff or 0xa000<=imm<=0xa1ff or imm in (0x1f00,0x1f80)
            if candidate or rm.get(i)=='HI16':origins[rt]={i}
            if rm.get(i)=='HI16':admitted.add(i)
        elif op in (8,9,13):
            have=set(origins.get(rs,()));origins.pop(rt,None)
            if have:origins[rt]=have
        elif op==0 and fn in (33,35,37):
            have=origins.get(rs,set())|origins.get(rt,set());origins.pop(rd,None)
            if have:origins[rd]=have
        elif op==0 and fn not in (8,9,12,13,17,19,24,25,26,27):origins.pop(rd,None)
        elif op in (10,11,12,14,32,33,34,35,36,37,38):origins.pop(rt,None)
        if i and (ws[i-1]>>26==3 or ws[i-1]>>26==0 and ws[i-1]&63==9):
            for r in (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31):origins.pop(r,None)
        origins.pop(0,None)
    return admitted


def normalise(ws, relocs=(), ignore_fields=False, preserve_branch_distance=False):
    """Preserve address provenance through moves/adds, consume a LUI page once.

    A resolved pointer is *not* a page: member offsets on it survive. Unknown
    RAM pointer arithmetic is conservative (false negatives preferred to hiding
    data constants). Relocations are authoritative. This is retrieval, not proof
    that two fields, globals, callees, or CFGs denote the same entities.
    """
    rm = {int(o)//4: t for o,t in relocs}
    address_defs=address_luis(ws,rm)
    pages = set()
    out, reasons = [], {}
    for i, w in enumerate(ws):
        op, rs, rt, rd, fn = w>>26,(w>>21)&31,(w>>16)&31,(w>>11)&31,w&63
        hi = op==15 and i in address_defs
        typ = rm.get(i)
        mask, reason = 0xffffffff, None
        if op in (2,3): mask,reason=0xfc000000,'absolute_target'
        elif op in (1,4,5,6,7) and not preserve_branch_distance: mask,reason=0xffff0000,'branch_target'
        elif typ in ('HI16','LO16','GPREL16'): mask,reason=0xffff0000,'reloc_'+typ
        elif hi: mask,reason=0xffff0000,'literal_address_hi'
        elif op in (8,9,13) and rs in pages: mask,reason=0xffff0000,'literal_address_lo'
        elif op in (32,33,34,35,36,37,38,40,41,42,43,46,48,49,50,51,56,57,58,59) and (rs in pages or rs==28):
            mask,reason=0xffff0000,'page_or_gp_access'
        elif ignore_fields and op in (32,33,34,35,36,37,38,40,41,42,43,46) and rs!=29:
            mask,reason=0xffff0000,'optional_member_offset'
        regmask = sum(31<<shift for shift in regfields(w))
        out.append((w & mask & ~regmask, tuple((w>>shift)&31 for shift in regfields(w))))
        if reason: reasons[i] = reason
        if op==15:
            pages.discard(rt)
            if hi or typ=='HI16': pages.add(rt)
        elif op==0 and fn in (33,35,37):
            have = (rs in pages and rt==0) or (rt in pages and rs==0)
            # Adding an index to a page also leaves the low address unresolved.
            have = have or fn==33 and (rs in pages or rt in pages)
            pages.discard(rd)
            if have: pages.add(rd)
        elif op==0 and fn not in (8,9,12,13,17,19,24,25,26,27): pages.discard(rd)
        elif op in (8,9,10,11,12,13,14,32,33,34,35,36,37,38): pages.discard(rt)
        if i and (ws[i-1]>>26==3 or ws[i-1]>>26==0 and ws[i-1]&63==9):
            pages.difference_update({1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31})
    return out,reasons


def seed_key(seq):
    """Alpha-normalised seed encodes repeated registers, not just opcodes."""
    mapping = {}
    result = []
    for code, rr in seq:
        ns = []
        for r in rr:
            if r in FIXED: ns.append(r)
            else:
                if r not in mapping: mapping[r] = 32+len(mapping)
                ns.append(mapping[r])
        result.append((code, tuple(ns)))
    return tuple(result)


def agree(a,b,mapping,reverse):
    if a[0]!=b[0] or len(a[1])!=len(b[1]): return False
    additions=[]
    for x,y in zip(a[1],b[1]):
        if (x in FIXED or y in FIXED) and x!=y: break
        if x in mapping and mapping[x]!=y or y in reverse and reverse[y]!=x: break
        if x not in mapping:
            mapping[x]=y;reverse[y]=x;additions.append((x,y))
    else: return True
    for x,y in additions: del mapping[x];del reverse[y]
    return False


def memory_accesses(ws):
    """Straight-line constant-base provenance, with caller-clobber handling.
    These are *access* leads, separate from contiguous block matches. Address
    equality is meaningful within the US image; JP/external equality is weaker.
    No speculative CFG merge, unknown arithmetic, or loaded pointer is followed.
    """
    known={0:(0,[])};out=[]
    for i,w in enumerate(ws):
        op,rs,rt,rd,fn=w>>26,(w>>21)&31,(w>>16)&31,(w>>11)&31,w&63
        if op in (32,33,34,35,36,37,38,40,41,42,43,46) and rs in known:
            a,defs=known[rs];address=(a+sext(w&65535))&0xffffffff
            if 0x80000000<=address<0x82000000 or 0x1f800000<=address<0x1f810000 or 0xa0000000<=address<0xa2000000:
                out.append({'index':i,'opcode':op,'address':address,'base_definitions':defs})
        if op==15:known[rt]=((w&65535)<<16,[i])
        elif op in (8,9,13):
            value=known.get(rs);known.pop(rt,None)
            if value:
                v,d=value;v=(v|(w&65535)) if op==13 else (v+sext(w&65535))&0xffffffff
                known[rt]=(v,d+[i])
        elif op==0 and fn in (33,35,37):
            a,b=known.get(rs),known.get(rt);known.pop(rd,None)
            if a and b:
                value=(a[0]+b[0]) if fn==33 else (a[0]-b[0] if fn==35 else a[0]|b[0])
                known[rd]=(value&0xffffffff,sorted(set(a[1]+b[1]+[i])))
        elif op==0 and fn not in (8,9,12,13,17,19,24,25,26,27):known.pop(rd,None)
        elif op in (10,11,12,14,32,33,34,35,36,37,38):known.pop(rt,None)
        if i and (ws[i-1]>>26==3 or ws[i-1]>>26==0 and ws[i-1]&63==9):
            for r in (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31):known.pop(r,None)
        known[0]=(0,[])
    return out


class Finder:
    def __init__(self, records, seed=4, ignore_fields=False, branch_distance=False):
        self.records=records;self.seed=seed;self.index=collections.defaultdict(list)
        self.norm=[];self.reasons=[];self.access_index=collections.defaultdict(list);self.accesses=[]
        t=time.monotonic()
        for fi,f in enumerate(records):
            seq,reason=normalise(f['words'],f.get('relocs',()),ignore_fields,branch_distance)
            self.norm.append(seq);self.reasons.append(reason)
            for i in range(len(seq)-seed+1): self.index[seed_key(seq[i:i+seed])].append((fi,i))
            accesses=memory_accesses(f['words']);self.accesses.append(accesses)
            if f['corpus'] in ('US','JP'):
                for access in accesses:self.access_index[(access['opcode'],access['address'])].append((fi,access))
        self.index_seconds=round(time.monotonic()-t,3)

    def near_search(self,target,start,end,top=10,anchors=(),minimum=.55):
        """Seed-anchored positional near matches, with one consistent renaming.
        Exact seed fields/roles establish the map; every extension mismatch is
        recorded, not hidden. This is bounded to 96-word site windows. It does
        not claim edit-distance optimality or bridge instruction insertions.
        """
        q=self.norm[target];f=self.records[target];k=self.seed
        if end-start>96:return {'status':'window_too_large','hits':[]}
        candidates={}
        for i in range(start,end-k+1):
            for fi,j in self.index.get(seed_key(q[i:i+k]),()):
                if fi==target:continue
                diagonal=j-i;a=self.norm[fi]
                lo=max(start,-diagonal);hi=min(end,len(a)-diagonal)
                if hi-lo<k or (hi-lo)/(end-start)<.6:continue
                m={};r={}
                if not all(agree(q[i+h],a[j+h],m,r) for h in range(k)):continue
                matched=[];mismatches=[]
                for x in range(lo,hi):
                    if agree(q[x],a[x+diagonal],m,r):matched.append(x)
                    else:mismatches.append(x)
                ratio=len(matched)/(end-start)
                if ratio<minimum:continue
                if anchors and not any(lo<=x<hi for x in anchors):continue
                key=(fi,diagonal);g=self.records[fi]
                h={'corpus':g['corpus'],'row':g['row'],'function':g['function'],'record_index':fi,
                   'query_start':lo,'query_end':hi,'sibling_start':lo+diagonal,'sibling_end':hi+diagonal,
                   'words':hi-lo,'matching_words':len(matched),'query_fraction_equal':round(ratio,4),
                   'equal_positions':matched,'mismatch_positions':mismatches,
                   'anchor_equal_positions':[x for x in anchors if x in matched],
                   'pin_free':g.get('pin_free'),'tree_byte_exact':g.get('tree_byte_exact'),
                   'register_map':{REGS[x]:REGS[y] for x,y in sorted(m.items())},
                   'evidence':'seed-anchored positional similarity; mismatches retained; not an exact block'}
                if key not in candidates or len(matched)>candidates[key]['matching_words']:candidates[key]=h
        ranked=sorted(candidates.values(),key=lambda h:(h['query_fraction_equal'],len(h['anchor_equal_positions']),h['matching_words'],h['pin_free'] is True),reverse=True)
        unique=[];seen=set()
        for h in ranked:
            key=(h['corpus'],h['row'],h['function'])
            if key not in seen:unique.append(h);seen.add(key)
        return {'status':'ok','candidates':len(candidates),'matched_functions':len(unique),'hits':unique[:top]}

    def search(self, target, start=0, end=None, top=15, min_words=None, anchors=(), include_self_jp=True):
        end=len(self.norm[target]) if end is None else end
        q=self.norm[target];f=self.records[target];k=self.seed
        if not 0<=start<end<=len(q): raise ValueError('invalid instruction window')
        seen=set();hits=[];candidates=0
        for i in range(start,end-k+1):
            for fi,j in self.index.get(seed_key(q[i:i+k]),()):
                g=self.records[fi]
                if fi==target or (not include_self_jp and g['row']==f['row']): continue
                key=(fi,j-i,i)
                if key in seen: continue
                # Cache diagonal only after a verified run; another disconnected
                # block on this diagonal must still be retrieved.
                a=self.norm[fi];mapping={};reverse={}
                if not all(agree(q[i+h],a[j+h],mapping,reverse) for h in range(k)): continue
                qs,ss,qe,se=i,j,i+k,j+k
                while qs>start and ss>0 and agree(q[qs-1],a[ss-1],mapping,reverse): qs-=1;ss-=1
                while qe<end and se<len(a) and agree(q[qe],a[se],mapping,reverse): qe+=1;se+=1
                n=qe-qs
                # Suppress re-testing seeds contained in this verified run, but
                # do not discard later blocks with a different renaming.
                for x in range(qs,qe-k+1): seen.add((fi,j-i,x))
                candidates+=1
                if n<(min_words or k): continue
                if anchors and not any(qs<=x<qe for x in anchors): continue
                rawq=f['words'][qs:qe];raws=g['words'][ss:se]
                exact=sum(x==y for x,y in zip(rawq,raws))
                branch_shape=all((x&65535)==(y&65535) for x,y in zip(rawq,raws) if x>>26 in (1,4,5,6,7))
                generic=sum(w==0 or w>>26 in (35,43) and (w>>21)&31==29 for w in rawq)
                hits.append({'corpus':g['corpus'],'row':g['row'],'function':g['function'],
                             'record_index':fi,'query_start':qs,'query_end':qe,'sibling_start':ss,'sibling_end':se,
                             'words':n,'raw_equal_words':exact,'byte_exact_window':rawq==raws,
                             'normalised_exact_window':True,'relative_branches_agree':branch_shape,
                             'coverage':round(n/(end-start),4),'generic_fraction':round(generic/n,4),
                             'register_map':{REGS[x]:REGS[y] for x,y in sorted(mapping.items())},
                             'pin_free':g.get('pin_free'),'tree_byte_exact':g.get('tree_byte_exact'),
                             'source':g.get('source'),'source_sha256':g.get('source_sha256'),
                             'pair_confidence':g.get('pair_confidence'),'pair_status':g.get('pair_status'),
                             'query_mask_reasons':{str(x):self.reasons[target][x] for x in range(qs,qe) if x in self.reasons[target]},
                             'sibling_mask_reasons':{str(x):self.reasons[fi][x] for x in range(ss,se) if x in self.reasons[fi]}})
        # One best block per function; generic prologues rank below useful code.
        hits.sort(key=lambda h:(h['generic_fraction']<.6,h['words'],h['byte_exact_window'],
                                h['relative_branches_agree'],h['raw_equal_words'],h['pin_free'] is True),reverse=True)
        unique=[];keys=set()
        for h in hits:
            key=(h['corpus'],h['row'],h['function'])
            if key not in keys: unique.append(h);keys.add(key)
        accesses=[];unique_access=set()
        for access in self.accesses[target]:
            if not start<=access['index']<end:continue
            for fi,other in self.access_index[(access['opcode'],access['address'])]:
                g=self.records[fi]
                if fi==target or g['corpus']!='US':continue
                key=(fi,access['index'],other['index'])
                if key in unique_access:continue
                unique_access.add(key)
                accesses.append({'corpus':g['corpus'],'row':g['row'],'function':g['function'],'record_index':fi,
                                 'query_index':access['index'],'sibling_index':other['index'],
                                 'address':hex(access['address']),'opcode':decode(f['words'][access['index']]).split()[0],
                                 'query_base_definitions':access['base_definitions'],'sibling_base_definitions':other['base_definitions'],
                                 'pin_free':g.get('pin_free'),'tree_byte_exact':g.get('tree_byte_exact'),
                                 'evidence':'same opcode and inferred absolute address; not a contiguous block match'})
        accesses.sort(key=lambda h:(h['pin_free'] is not True,
                                   min((abs(h['query_index']-a) for a in anchors),default=0),
                                   len(self.records[h['record_index']]['words'])>=40,
                                   len(h['sibling_base_definitions'])!=1,h['row']))
        return {'row':f['row'],'function':f['function'],'query_start':start,'query_end':end,
                'query_words':end-start,'query_disassembly':[decode(w,i) for i,w in enumerate(f['words']) if start<=i<end],
                'anchors':list(anchors),'candidate_runs':candidates,'matched_functions':len(unique),'hits':unique[:top],
                'address_access_hits':accesses[:max(top,50)],'address_access_hit_count':len(accesses)}


class Workspace:
    def __init__(self, repo, workspace, rows_path=None):
        self.repo=Path(repo).resolve();self.path=Path(workspace).resolve()
        self.path.mkdir(parents=True,exist_ok=True)
        self.big=self.path/'out_big';self.big.mkdir(exist_ok=True)
        (self.big/'.ignore').write_text('*\n')
        self.env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1',TMPDIR=str(self.big))
        for k in list(self.env):
            if k in ('AZURE_MASPSX','AZURE_MASPSX_COMPANION') or k.startswith('MASPSX_'):self.env.pop(k,None)
        self.rows={r['id']:r for r in jsonl(rows_path or self.repo/'ledger/rows.jsonl')}
        self.link=read_elf(self.repo/'build_slus/build/slus_006.14.elf')
        self.addresses={n:s['value'] for n,s in self.link['symbols'].items()}
        self.names={}
        for line in (self.repo/'config/names.tsv').read_text().splitlines():
            cols=line.split('#',1)[0].split('\t')
            if len(cols)>=3:
                self.names[cols[2].strip()]=cols[1].strip()
                m=re.fullmatch(r'(?:func|D)_([0-9A-Fa-f]{8})',cols[1].strip())
                if m:self.addresses.setdefault(cols[2].strip(),int(m[1],16))
        self._context_identity=None;self._compiler_identities={}

    def context_identity(self):
        if self._context_identity is None:
            files=sorted(p for p in (self.repo/'include').rglob('*') if p.is_file())
            files += [self.repo/'tools/build/ccproc.py',self.repo/'tools/maspsx/maspsx.py',
                      self.repo/'tools/maspsx/maspsx/__init__.py',self.repo/'config/names.tsv',
                      self.repo/'config/func_sizes.json',self.repo/'build_slus/build/slus_006.14.elf']
            files += sorted((self.repo/'config').glob('*syms*.txt'))
            hashes=[(str(p.relative_to(self.repo)),sha(p.read_bytes())) for p in files]
            assembler=shutil.which('mipsel-linux-gnu-as')
            if not assembler:raise RuntimeError('mipsel-linux-gnu-as not found')
            hashes.append(('gnu-as-executable',sha(Path(assembler).read_bytes())))
            self._context_identity=sha(json.dumps(hashes).encode())
        return self._context_identity

    def write_json(self, rel, obj):
        p=(self.path/rel).resolve()
        if not p.is_relative_to(self.path): raise ValueError('output escapes workspace')
        p.parent.mkdir(parents=True,exist_ok=True)
        p.write_text(json.dumps(obj,indent=2)+'\n');return p

    def run(self, args, cwd, inp=None):
        cwd=Path(cwd).resolve()
        if not cwd.is_relative_to(self.path): raise ValueError('build cwd escapes workspace')
        z=subprocess.run(['nice','-n','10',*map(str,args)],cwd=cwd,env=self.env,input=inp,
                         capture_output=True,text=True,timeout=180)
        with (cwd/'commands.jsonl').open('a') as log:
            log.write(json.dumps({'argv':list(map(str,args)),'returncode':z.returncode,'stderr':z.stderr[-3000:]})+'\n')
        if z.returncode: raise RuntimeError(z.stderr[-3000:] or z.stdout[-3000:])
        return z.stdout

    def source(self, row):
        return self.repo/'src'/row['container']/Path(row['c_path']).name

    def build_inventory(self, jp_lane=None, external=None):
        records=[];missing=[];source_dir=self.big/'sources';source_dir.mkdir(exist_ok=True)
        containers={k:(self.repo/'work/disc/containers'/v).read_bytes() for k,v in CONTAINERS.items()}
        slus=(self.repo/'baserom/slus_006.14').read_bytes();load=struct.unpack_from('<I',slus,0x18)[0]
        sizes=json.loads((self.repo/'config/func_sizes.json').read_text())
        for row in self.rows.values():
            if row.get('row_kind')=='data': continue
            p=self.source(row)
            text=p.read_text(errors='replace') if p.exists() else ''
            snap=source_dir/(row['id']+'.c');snap.parent.mkdir(exist_ok=True);snap.write_text(text)
            common={'row':row['id'],'cfg':row['cfg'],'source':str(snap),'original_source':str(p),
                    'source_sha256':sha(text.encode()),'pin_free':not bool(PIN_RE.search(stripped(text))),
                    'has_oddity':'ODDITY_' in stripped(text),'tree_byte_exact':None,
                    'tree_exact_basis':'unmeasured; STATUS baseline is not a fresh current-source certificate'}
            if row['container']!='slus':
                off,size=row['foff'],row['size'];b=containers[row['container']][off:off+size]
                if len(b)!=size or size%4: missing.append({'row':row['id'],'reason':'invalid retail extent'});continue
                records.append({**common,'corpus':'US','function':row.get('true_name') or row['func'],
                                'foff':off,'words':words(b),'retail_sha256':sha(b)})
            else:
                # Historical defs may include prototypes. Admit definitions only
                # from linked STT_FUNC symbols whose C source owns a real body.
                active=stripped(text)
                kr=r'(?:\s*[A-Za-z_][^;{}()]*;)*'
                defs=set(re.findall(r'^\s*[\w *]+\b(\w+)\s*\([^;{}]*\)'+kr+r'\s*\{',active,re.M))
                functions=set(row.get('defs',())) | {self.names.get(x,x) for x in defs}
                functions &= {self.names.get(x,x) for x in defs}
                for nm in sorted(functions):
                    s=self.link['symbols'].get(nm)
                    if not s or s['type']!=2: continue
                    size=s['size'] or sizes.get(nm,0);addr=s['value'];off=addr-load+0x800
                    if not size or off<0x800 or off+size>len(slus): continue
                    b=slus[off:off+size]
                    records.append({**common,'corpus':'US','function':nm,'foff':off,'vram':addr,
                                    'words':words(b),'retail_sha256':sha(b)})
                if not any(f['row']==row['id'] for f in records):missing.append({'row':row['id'],'reason':'no linked owned C function'})
        if jp_lane:
            jp_lane=Path(jp_lane).resolve()
            for pair in jsonl(jp_lane/'out_big/pairings.jsonl'):
                p=pair.get('jp_bin')
                if not p: continue
                p=jp_lane/p
                if not p.exists(): missing.append({'row':pair['id'],'reason':'missing JP bin'});continue
                b=p.read_bytes()
                records.append({'corpus':'JP','row':pair['id'],'function':pair.get('symbol') or pair['func'],
                                'words':words(b),'retail_sha256':sha(b),'source':None,'pin_free':None,
                                'tree_byte_exact':None,'pair_confidence':pair.get('confidence'),'pair_status':pair['status'],
                                'pair_method':pair.get('method'),'foff':pair.get('jp_foff')})
        if external:
            external=Path(external).resolve()
            for f in json.load(gzip.open(external/'evidence/machine_functions.json.gz','rt')):
                obj=read_elf(external/f['object']);start=f['start'];size=f['size']
                rel=[(r['offset']-start,r['type']) for r in obj['relocs'] if r['section']=='.text' and start<=r['offset']<start+size]
                records.append({'corpus':'external-machine','row':f['project']+'/'+f['name'],'function':f['name'],
                                'words':f['words'],'relocs':rel,'source':f['source'],'pin_free':True,
                                'tree_byte_exact':None,'external_basis':'assembled C only; no fresh retail verification',
                                'object':str(external/f['object']),'cc1_asm':str(external/f['cc1_asm'])})
        target=self.big/'inventory.json.gz'
        with gzip.open(target,'wt') as g:json.dump(records,g,separators=(',',':'))
        summary={'version':VERSION,'records':len(records),'counts':dict(collections.Counter(f['corpus'] for f in records)),
                 'us_rows':len({f['row'] for f in records if f['corpus']=='US'}),'ledger_rows':len(self.rows),
                 'instructions':sum(len(f['words']) for f in records),'missing':missing,
                 'inventory_sha256':sha(target.read_bytes()),'captured_utc':time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime())}
        self.write_json('out_big/inventory_summary.json',summary)
        return records,summary

    def compile_map(self, record, text=None, label='current'):
        """Production and -g compiles. Instrument AFTER maspsx, then require
        identical relocated words before transferring post-assembly .loc notes.
        Debug notes describe compiler emission attribution, not source semantics.
        """
        row=self.rows[record['row']]
        text=Path(record['source']).read_text() if text is None else text
        d=self.repo/'toolchain/compilers'/('gcc-'+row['cell'])
        if row['cell'] not in self._compiler_identities:
            self._compiler_identities[row['cell']]=sha(b''.join((d/n).read_bytes() for n in ('gcc','cpp','cc1')))
        compiler_identity=self._compiler_identities[row['cell']]
        context_identity=self.context_identity()
        key=sha(json.dumps([VERSION,sha(Path(__file__).read_bytes()),context_identity,compiler_identity,
                            row['cfg'],row.get('row_asflags'),record['function'],text,label]).encode())[:20]
        out=self.big/'maps'/key;out.mkdir(parents=True,exist_ok=True)
        receipt=out/'map.json'
        if receipt.exists():return json.loads(receipt.read_text())
        (out/'input.c').write_text(c89(text));commands=[]
        cell=row['cell'];d=self.repo/'toolchain/compilers'/('gcc-'+cell)
        flags=shlex.split(row.get('flags') or '')
        if not any(x.startswith('-O') for x in flags):flags=['-O2',*flags]
        asmflags=shlex.split(row.get('row_asflags') or '')
        maps=[];objs=[]
        try:
            for debug in (False,True):
                tag='debug' if debug else 'production'
                argv=[d/'gcc','-B'+str(d)+'/', '-S',*flags,*(['-g'] if debug else []),
                      '-I'+str(self.repo/'include'),'-I'+str(self.repo/'src'/row['container']),'-w',out/'input.c','-o',out/(tag+'.cc1.s')]
                self.run(argv,out)
                s=(out/(tag+'.cc1.s')).read_text()
                s=self.run([sys.executable,self.repo/'tools/build/ccproc.py'],out,s)
                (out/(tag+'.sectioned.s')).write_text(s)
                a=self.run([self.repo/'.venv/bin/python',self.repo/'tools/maspsx/maspsx.py',
                            '--aspsx-version=2.79','--dont-force-G0','-G8',*asmflags],out,s)
                # .loc anchors inserted only AFTER all assembler scheduling and
                # pseudo rewrites. GAS receives explicit noreorder instructions.
                notes={};lines=[];active=False;index=0;files={}
                for line in a.splitlines():
                    fm=re.match(r'\s*\.file\s+(\d+)\s+"([^"]+)"',line)
                    if fm:files[int(fm[1])]=fm[2]
                    if re.match(r'\s*\.ent\b',line):active=True
                    if re.match(r'\s*\.end\b',line):active=False
                    m=re.match(r'\s*\.loc\s+(\d+)\s+(\d+)',line)
                    if m:
                        if debug and active and Path(files.get(int(m[1]),'')).name=='input.c':
                            nm='__sibling_note_'+str(index);index+=1
                            notes[nm]={'file_number':int(m[1]),'line':int(m[2])};lines.append(nm+':')
                        continue
                    if re.match(r'\s*\.file\b',line):continue
                    lines.append(line)
                final='\n'.join(lines)+'\n';(out/(tag+'.gas.s')).write_text(final)
                self.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-G0','-I'+str(self.repo),
                          '-I'+str(self.repo/'include'),'-o',out/(tag+'.o'),'-'],out,final)
                obj=read_elf(out/(tag+'.o'));objs.append(obj);maps.append(notes)
            symbol=record['function'];s=objs[0]['symbols'].get(symbol);symbol_selection='registered_symbol'
            if not s:
                # Some overlay ledger symbols predate a load-base/name repair.
                # Read the single real emitted body; never silently pick one of
                # several functions. Retail equality still decides admission.
                candidates=[n for n,v in objs[0]['symbols'].items() if v['type']==2 and v['size'] and
                            v['section'] and v['section'].startswith('.text')]
                if len(candidates)!=1:raise ValueError('symbol not emitted and body ambiguous: '+symbol)
                symbol=candidates[0];s=objs[0]['symbols'][symbol];symbol_selection='single_emitted_body_alias'
            def unit(o):
                v=o['symbols'][symbol];sec=v['section'];start=v['value'];size=v['size']
                ws=words(o['sections'][sec][start:start+size])
                rel=[(r['offset']-start,r['type'],r['symbol']['name'],r['symbol']['section'],r['addend'])
                     for r in o['relocs'] if r['section']==sec and start<=r['offset']<start+size]
                return ws,rel
            prod,pr=unit(objs[0]);dbg,dr=unit(objs[1])
            debug_same=prod==dbg and pr==dr
            obj=objs[0];sec=s['section'];start=s['value']
            anchors=[]
            for nm,note in maps[1].items():
                a=objs[1]['symbols'].get(nm)
                if a and a['section']==sec:anchors.append(((a['value']-start)//4,note['line']))
            anchors.sort();locs=[None]*len(prod)
            if debug_same:
                for z,(begin,line) in enumerate(anchors):
                    end=anchors[z+1][0] if z+1<len(anchors) else len(prod)
                    for i in range(max(0,begin),min(len(prod),end)):locs[i]=line
            linked,unknown=self.resolve(obj,symbol,record)
            retail=record['words'];diff=sum((linked[i] if i<len(linked) else None)!=(retail[i] if i<len(retail) else None)
                                           for i in range(max(len(linked),len(retail))) if i not in unknown)
            exact=(linked==retail) if not unknown else (False if diff else None)
            # Transfer notes through an instruction alignment if the current C
            # misses retail. Such notes are explicitly approximate, never exact.
            retail_locs=[None]*len(retail)
            method='exact_positional' if exact else 'instruction_alignment_approximate'
            if exact:retail_locs=locs
            elif debug_same:
                pn=normalise(prod,[(x[0],x[1]) for x in pr])[0];rn=normalise(retail)[0]
                for block in difflib.SequenceMatcher(None,pn,rn,autojunk=False).get_matching_blocks():
                    for j in range(block.size):retail_locs[block.b+j]=locs[block.a+j]
            result={'status':'ok','row':record['row'],'function':record['function'],'emitted_symbol':symbol,
                    'symbol_selection':symbol_selection,'cfg':row['cfg'],'label':label,
                    'source_sha256':sha(text.encode()),'debug_machine_identical':debug_same,
                    'production_words':len(prod),'retail_words':len(retail),'retail_diff_words':diff,
                    'unresolved_relocations':unknown,'tree_byte_exact':exact,'retail_line_notes':retail_locs,
                    'mapping_method':method,'debug_note_coverage':sum(x is not None for x in retail_locs),
                    'path':str(out),'production_sha256':sha(packed(prod)),'linked_sha256':sha(packed(linked))}
            result.update(context_sha256=context_identity,compiler_sha256=compiler_identity,
                          sibling_tool_sha256=sha(Path(__file__).read_bytes()))
        except (RuntimeError,ValueError,KeyError,subprocess.TimeoutExpired) as e:
            result={'status':'error','row':record['row'],'function':record['function'],'error':str(e),'path':str(out)}
        receipt.write_text(json.dumps(result,indent=2)+'\n');return result

    def resolve(self,obj,symbol,record):
        s=obj['symbols'][symbol];sec=s['section'];start=s['value'];size=s['size']
        ws=words(obj['sections'][sec][start:start+size]);unknown=[]
        base=record.get('vram')
        true_name=self.rows.get(record['row'],{}).get('true_name')
        if base is None and true_name:
            m=re.fullmatch(r'func_([0-9A-Fa-f]{8})',true_name)
            if m:base=int(m[1],16)
        if base is None:
            m=re.search(r'([0-9A-Fa-f]{8})$',symbol)
            if m:base=int(m[1],16)
        gp=self.addresses.get('_gp',0x80080994)
        def address(n):
            m=re.fullmatch(r'(?:func|D|jtbl|jumptable|w)_([0-9A-Fa-f]{8})',n)
            return int(m[1],16) if m else self.addresses.get(n)
        bases={sec:base-start} if base is not None else {}
        for n,v in obj['symbols'].items():
            a=address(n)
            if v['section'] and a is not None:bases.setdefault(v['section'],a-v['value'])
        for r in obj['relocs']:
            if r['section']!=sec or not start<=r['offset']<start+size:continue
            i=(r['offset']-start)//4;t=r['symbol'];a=r['addend'];v=None
            if t['shndx']==0xfff1:v=t['value']+a
            elif t['type']==3 and t['section'] in bases:v=bases[t['section']]+a
            elif t['section'] in bases:v=bases[t['section']]+t['value']+a
            elif address(t['name']) is not None:v=address(t['name'])+a
            if v is None:unknown.append(i);continue
            v&=0xffffffff;typ=r['type'];w=ws[i]
            if typ=='HI16':w=(w&0xffff0000)|(((v+0x8000)>>16)&65535)
            elif typ=='LO16':w=(w&0xffff0000)|(v&65535)
            elif typ=='GPREL16':w=(w&0xffff0000)|((v-gp)&65535)
            elif typ=='26':w=(w&0xfc000000)|((v>>2)&0x3ffffff)
            elif typ=='32':w=v
            else:unknown.append(i)
            ws[i]=w
        return ws,unknown


def excerpt(record, mapping, start, end, context=2):
    p=record.get('source')
    if not p:return {'status':'no_C_source','reason':'JP retail window; US paired C is not JP source'}
    text=Path(p).read_text(errors='replace');lines=text.splitlines()
    notes=(mapping or {}).get('retail_line_notes',[])
    selected=sorted({n for n in notes[start:end] if n and 0<n<=len(lines)})
    if not selected:return {'status':'unmapped','source':p,'reason':'no validated line notes for this window'}
    ranges=[]
    for n in selected:
        a,b=max(1,n-context),min(len(lines),n+context)
        if ranges and a<=ranges[-1][1]+1:ranges[-1][1]=max(ranges[-1][1],b)
        else:ranges.append([a,b])
    return {'status':'mapped','source':p,'mapping_method':mapping['mapping_method'],'emission_lines':selected,
            'ranges':ranges,'text':'\n'.join(f'{i}: {lines[i-1]}' for a,b in ranges for i in range(a,b+1))}


def function_excerpt(path,symbol,limit=100):
    """Fallback source body, explicitly NOT an instruction-window line map."""
    p=Path(path)
    if not p.exists():return {'status':'missing_source','source':str(p)}
    text=p.read_text(errors='replace');active=stripped(text)
    matches=list(re.finditer(r'\b'+re.escape(symbol)+r'\s*\([^;{}]*\)\s*\{',active))
    if not matches:return {'status':'unmapped','source':str(p),'reason':'no unambiguous C definition found'}
    m=matches[0];begin=m.end()-1;depth=0;finish=begin
    for i in range(begin,len(active)):
        if active[i]=='{':depth+=1
        elif active[i]=='}':
            depth-=1
            if depth==0:finish=i;break
    a=active[:m.start()].count('\n')+1;b=active[:finish].count('\n')+1
    lines=text.splitlines();end=min(b,a+limit-1)
    return {'status':'function_extent_only','mapping_method':'source_function_extent_NOT_window_mapping',
            'source':str(p),'source_sha256':sha(text.encode()),'range':[a,b],'truncated':end<b,
            'text':'\n'.join(f'{i}: {lines[i-1]}' for i in range(a,end+1))}


def site_windows(record,mapping,text,radius=8,oddities=False):
    active=stripped(text);lines=active.splitlines();notes=mapping.get('retail_line_notes',[]);queries=[]
    pattern=re.compile(PIN_RE.pattern+(r'|\bODDITY_\w+\s*\(' if oddities else ''))
    for m in pattern.finditer(active):
        line=active[:m.start()].count('\n')+1;want={line};variable=None
        if m[0].startswith('ASM_REG'):
            var=re.search(r'(\w+)\s+ASM_REG',lines[line-1]);variable=var[1] if var else None
            if variable:want.update(i+1 for i,s in enumerate(lines) if re.search(r'\b'+re.escape(variable)+r'\b',s))
        positions=[i for i,n in enumerate(notes) if n in want];method='emission_line_or_variable_use'
        if not positions:
            known=[(abs(n-line),i) for i,n in enumerate(notes) if n is not None]
            if not known:continue
            positions=[min(known)[1]];method='nearest_emission_note_for_zero_byte_site'
        groups=[]
        for i in positions:
            a,b=max(0,i-radius),min(len(notes),i+radius+1)
            if groups and a<=groups[-1][1]:groups[-1][1]=max(groups[-1][1],b)
            else:groups.append([a,b])
        for a,b in groups:
            queries.append((a,b,[i for i in positions if a<=i<b],
                            {'pin_line':line,'variable':variable,'site_mapping':method,'site_lines':sorted(want),
                             'statement':text.splitlines()[line-1],'macro':m[0].split('(')[0].strip()}))
    return queries


def main():
    ap=argparse.ArgumentParser(description=__doc__,formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--repo',required=True);ap.add_argument('--workspace',required=True)
    ap.add_argument('--rows',help='optional frozen ledger/rows.jsonl for reproducible compiler recipes')
    ap.add_argument('--inventory');ap.add_argument('--build-inventory',action='store_true')
    ap.add_argument('--jp-lane');ap.add_argument('--external')
    ap.add_argument('--row');ap.add_argument('--function');ap.add_argument('--window',help='half-open instruction indices START:END')
    ap.add_argument('--pins',action='store_true',help='map statement sites and register-variable uses with -g notes')
    ap.add_argument('--oddities',action='store_true',help='include ODDITY_* zero-byte sites')
    ap.add_argument('--radius',type=int,default=8);ap.add_argument('--seed',type=int,default=4)
    ap.add_argument('--top',type=int,default=15);ap.add_argument('--ignore-field-offsets',action='store_true')
    ap.add_argument('--near',action='store_true',help='seed-anchored positional near matches for <=96-word windows')
    ap.add_argument('--preserve-branch-distance',action='store_true');ap.add_argument('--map-top',type=int,default=3)
    ap.add_argument('--out',default='out_big/single_result.json')
    args=ap.parse_args()
    if not 2<=args.seed<=16:ap.error('--seed must be between 2 and 16')
    w=Workspace(args.repo,args.workspace,args.rows)
    if args.build_inventory:
        records,summary=w.build_inventory(args.jp_lane,args.external);print(json.dumps(summary,indent=2))
    else:
        p=Path(args.inventory) if args.inventory else w.big/'inventory.json.gz'
        records=json.load(gzip.open(p,'rt'))
    if not args.row:return
    target=next(i for i,f in enumerate(records) if f['corpus']=='US' and f['row']==args.row and
                (not args.function or f['function']==args.function))
    finder=Finder(records,args.seed,args.ignore_field_offsets,args.preserve_branch_distance)
    f=records[target];queries=[];mapping=None
    if args.pins or args.oddities or args.external:
        mapping=w.compile_map(f)
        if mapping.get('status')!='ok':raise RuntimeError(mapping)
    if args.pins or args.oddities:
        queries=site_windows(f,mapping,Path(f['source']).read_text(),args.radius,args.oddities)
    elif args.window:
        a,b=map(int,args.window.split(':'));queries=[(a,b,[],{})]
    else:queries=[(0,len(f['words']),[],{})]
    results=[];maps={};listing=None;listing_instructions=[];listing_locations=[]
    if args.external:
        try:from .sibling_listing import ListingFinder,parse_listing
        except ImportError:from sibling_listing import ListingFinder,parse_listing
        listing=ListingFinder(args.external,args.seed,args.ignore_field_offsets)
        listing_instructions,listing_locations=parse_listing(Path(mapping['path'])/'debug.sectioned.s',f['function'])
    for a,b,anchors,meta in queries:
        result=finder.search(target,a,b,args.top,anchors=anchors);result.update(meta)
        if args.near:result['near_matches']=finder.near_search(target,a,b,args.top,anchors)
        if listing:
            wanted={n for n in mapping['retail_line_notes'][a:b] if n}
            result['external_listing']=listing.search(listing_instructions,listing_locations,wanted,args.top)
        for h in result['hits'][:args.map_top]:
            g=records[h['record_index']]
            if g['corpus']=='US':
                if h['record_index'] not in maps:maps[h['record_index']]=w.compile_map(g)
                mp=maps[h['record_index']];h['tree_byte_exact']=mp.get('tree_byte_exact')
                h['C']=excerpt(g,mp,h['sibling_start'],h['sibling_end'])
        for h in result['address_access_hits'][:args.map_top]:
            g=records[h['record_index']]
            if h['record_index'] not in maps:maps[h['record_index']]=w.compile_map(g)
            mp=maps[h['record_index']];h['tree_byte_exact']=mp.get('tree_byte_exact')
            h['C']=excerpt(g,mp,h['sibling_index'],h['sibling_index']+1)
        for h in [x for x in result.get('near_matches',{}).get('hits',[]) if x['corpus']=='US'][:args.map_top]:
            g=records[h['record_index']]
            if h['record_index'] not in maps:maps[h['record_index']]=w.compile_map(g)
            mp=maps[h['record_index']];h['tree_byte_exact']=mp.get('tree_byte_exact')
            h['C']=excerpt(g,mp,h['sibling_start'],h['sibling_end'])
        results.append(result)
    w.write_json(args.out,{'version':VERSION,'options':vars(args),'query_mapping':mapping,
                           'inventory_records':len(records),'index_seconds':finder.index_seconds,'results':results})
    print(json.dumps({'output':str(w.path/args.out),'windows':len(results),'best':[
        {'query':[r['query_start'],r['query_end']],'hits':[(h['row'],h['words']) for h in r['hits'][:3]]} for r in results]},indent=2))


if __name__=='__main__':main()
