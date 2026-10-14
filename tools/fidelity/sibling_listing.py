"""Broader cc1-listing adapter; pseudo-instruction evidence is kept separate.

Uses the 16,553-body PSX corpus plus the 22-body FFVII side index. Locations
are cc1 emission notes. A listing hit is never called a machine-byte match.
"""
from __future__ import annotations
import collections
import gzip
import json
from pathlib import Path
import re
try:
    from .sibling_find import FIXED, REGS, agree, seed_key, function_excerpt
except ImportError:
    from sibling_find import FIXED, REGS, agree, seed_key, function_excerpt

ALIASES={n:i for i,n in enumerate(REGS)}
ALIASES['s8']=30
REGISTER=re.compile(r'\$(\d+|zero|at|v[01]|a[0-3]|t[0-9]|s[0-8]|k[01]|gp|sp|fp|ra)\b')
BRANCHES={'j','jr','jal','jalr','b','beq','bne','beqz','bnez','bgez','bltz','blez','bgtz','bltzal','bgezal','bc1t','bc1f'}


def parse_listing(path, symbol):
    files={};source='';line=0;active=False;instructions=[];locations=[]
    for s in Path(path).read_text(errors='replace').splitlines():
        m=re.match(r'\s*\.file\s+(\d+)\s+"([^"]+)"',s)
        if m:files[int(m[1])]=m[2]
        m=re.match(r'\s*\.loc\s+(\d+)\s+(\d+)',s)
        if m:source=files.get(int(m[1]),'');line=int(m[2])
        m=re.match(r'\s*\.ent\s+(\S+)',s)
        if m:active=m[1]==symbol
        if re.match(r'\s*\.end\b',s):active=False
        s=s.split('#',1)[0].strip()
        if active and s and re.match(r'^[a-z][a-z0-9]*(?:\s|$)',s) and not s.endswith(':'):
            instructions.append(re.sub(r'\s+',' ',s));locations.append(line if Path(source).name=='input.c' else None)
    return instructions,locations


def address_definitions(instructions):
    origins={};admitted=set()
    memory={'lw','lhu','lh','lb','lbu','sw','sh','sb','lwl','lwr','swl','swr','lwc2','swc2'}
    for i,s in enumerate(instructions):
        op,_,arg=s.partition(' ')
        rr=[int(m[1]) if m[1].isdigit() else ALIASES[m[1]] for m in REGISTER.finditer(arg)]
        if op in memory and '(' in arg and rr:admitted.update(origins.get(rr[-1],()))
        if op in ('jr','jalr') and rr:admitted.update(origins.get(rr[-1],()))
        if op in ('li','la','lui') and rr:
            tail=arg.split(',')[-1].strip();origins.pop(rr[0],None)
            try:v=int(tail,0)&0xffffffff
            except ValueError:v=None
            candidate=v is not None and (0x8000<=v<=0x81ff or 0xa000<=v<=0xa1ff or v in (0x1f00,0x1f80)) if op=='lui' else v is not None and (0x80000000<=v<0x82000000 or 0xa0000000<=v<0xa2000000 or 0x1f800000<=v<0x1f810000)
            if candidate or op=='la' or '%' in tail:origins[rr[0]]={i}
            if op=='la' or '%' in tail:admitted.add(i)
        elif op in ('move','addu','addiu','or','ori','subu') and rr:
            have=set().union(*(origins.get(r,set()) for r in rr[1:]));origins.pop(rr[0],None)
            if have:origins[rr[0]]=have
        elif rr and op not in BRANCHES and op not in ('mult','multu','div','divu') and op not in memory:
            origins.pop(rr[0],None)
        elif rr and op in memory and op.startswith('l'):origins.pop(rr[0],None)
        if i and instructions[i-1].split()[0] in ('jal','jalr'):
            for r in (1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,24,25,31):origins.pop(r,None)
        origins.pop(0,None)
    return admitted


def listing_norm(instructions, ignore_fields=False):
    out=[];pages=set()
    address_defs=address_definitions(instructions)
    for index,s in enumerate(instructions):
        s=s.split('#',1)[0].strip();op,_,arg=s.partition(' ')
        rr=[]
        def reg(m):
            name=m[1];r=int(name) if name.isdigit() else ALIASES[name]
            rr.append(r);return '@'
        code=REGISTER.sub(reg,arg)
        code=re.sub(r'\s+','',code)
        if op in BRANCHES and op not in ('jr','jalr'):
            chunks=code.split(',')
            if chunks and chunks[-1]!='@':chunks[-1]='TARGET'
            code=','.join(chunks)
        code=re.sub(r'%(?:hi|lo)\([^)]*\)','ADDRESS',code)
        if op=='lui':
            tail=arg.split(',')[-1].strip()
            try:value=int(tail,0)
            except ValueError:value=None
            if value is not None and index in address_defs:
                code=code.rsplit(',',1)[0]+',ADDRESS'
            if rr:
                pages.discard(rr[0])
                if 'ADDRESS' in code:pages.add(rr[0])
        elif op in ('li','la'):
            tail=arg.split(',')[-1].strip()
            try:value=int(tail,0)&0xffffffff
            except ValueError:value=None
            if value is None or index in address_defs:
                code=code.split(',')[0]+',ADDRESS'
            if rr:pages.discard(rr[0])
        elif op in ('lw','lhu','lh','lb','lbu','sw','sh','sb','lwl','lwr','swl','swr'):
            base=rr[-1] if '(' in code and rr else None
            if base in pages or base==28 or ignore_fields and base!=29:
                code=re.sub(r',-?(?:0x[0-9a-fA-F]+|\d+)\(@\)',',OFFSET(@)',code)
            if op.startswith('l') and rr:pages.discard(rr[0])
        elif op in ('addiu','addu','ori','or','move'):
            if len(rr)>1 and rr[1] in pages and op in ('addiu','ori'):
                code=re.sub(r',-?(?:0x[0-9a-fA-F]+|\d+)$',',ADDRESS',code)
            if rr and not (op=='move' and len(rr)>1 and rr[1] in pages):pages.discard(rr[0])
            if op=='move' and len(rr)>1 and rr[1] in pages:pages.add(rr[0])
        elif rr and op not in BRANCHES and op not in ('mult','multu','div','divu'):pages.discard(rr[0])
        # Canonical numeric spellings (hex vs decimal); preserve all data values.
        def number(m):
            try:return str(int(m[0],16) if '0x' in m[0].lower() else int(m[0]))
            except ValueError:return m[0]
        code=re.sub(r'(?<![A-Za-z_])-?(?:0x[0-9a-fA-F]+|\d+)(?![A-Za-z_])',number,code)
        out.append((op+' '+code,tuple(rr)))
    return out


class ListingFinder:
    def __init__(self, external, seed=4, ignore_fields=False):
        root=Path(external);self.seed=seed;self.ignore_fields=ignore_fields
        self.records=json.load(gzip.open(root/'evidence/functions.json.gz','rt'))
        side=root/'evidence/ffvii_functions.json.gz'
        if side.exists():self.records+=json.load(gzip.open(side,'rt'))
        self.norm=[];self.index=collections.defaultdict(list)
        for fi,f in enumerate(self.records):
            seq=listing_norm(f['instructions'],ignore_fields);self.norm.append(seq)
            for i in range(len(seq)-seed+1):self.index[seed_key(seq[i:i+seed])].append((fi,i))

    def search(self,instructions,locations,wanted_lines=(),top=12):
        q=listing_norm(instructions,self.ignore_fields);k=self.seed;hits=[];seen=set()
        for i in range(len(q)-k+1):
            for fi,j in self.index.get(seed_key(q[i:i+k]),()):
                if (fi,j-i,i) in seen:continue
                a=self.norm[fi];m={};r={}
                if not all(agree(q[i+h],a[j+h],m,r) for h in range(k)):continue
                qs,ss,qe,se=i,j,i+k,j+k
                while qs and ss and agree(q[qs-1],a[ss-1],m,r):qs-=1;ss-=1
                while qe<len(q) and se<len(a) and agree(q[qe],a[se],m,r):qe+=1;se+=1
                seen.update((fi,j-i,x) for x in range(qs,qe-k+1))
                if wanted_lines and not set(locations[qs:qe])&set(wanted_lines):continue
                f=self.records[fi];loc=f['locations'][ss:se];paths=collections.defaultdict(set)
                for p,line,_ in loc:
                    if line:paths[p].add(line)
                excerpts=[]
                for path,nums in paths.items():
                    p=Path(path)
                    if not p.exists():continue
                    lines=p.read_text(errors='replace').splitlines();nums=sorted(n for n in nums if 0<n<=len(lines))
                    if not nums:continue
                    ranges=[]
                    for n in nums:
                        lo,hi=max(1,n-1),min(len(lines),n+1)
                        if ranges and lo<=ranges[-1][1]+1:ranges[-1][1]=max(hi,ranges[-1][1])
                        else:ranges.append([lo,hi])
                    excerpts.append({'source':path,'emission_lines':nums,'ranges':ranges,
                                     'text':'\n'.join(f'{n}: {lines[n-1]}' for lo,hi in ranges for n in range(lo,hi+1))})
                if not excerpts and loc:excerpts=[function_excerpt(loc[0][0],f['name'],limit=80)]
                block=instructions[qs:qe]
                generic=sum(x.strip()=='nop' or re.search(r'^(?:lw|sw)\s+.*\(\$(?:29|sp)\)',x) is not None for x in block)
                hits.append({'corpus':'external-cc1','row':f['project']+'/'+f['name'],'function':f['name'],
                             'project':f['project'],'listing_instructions':qe-qs,'query_start':qs,'query_end':qe,
                             'sibling_start':ss,'sibling_end':se,'query_lines':sorted({n for n in locations[qs:qe] if n}),
                             'source':loc[0][0] if loc else None,'C':excerpts,
                             'query_listing':instructions[qs:qe],'sibling_listing':f['instructions'][ss:se],
                             'pin_free':True,'tree_byte_exact':None,'evidence':'cc1 pseudo-instruction listing; no machine byte certificate'})
                hits[-1]['generic_fraction']=round(generic/max(len(block),1),4)
        hits.sort(key=lambda h:(h['generic_fraction']<.6,h['listing_instructions']),reverse=True);unique=[];keys=set()
        for h in hits:
            key=(h['project'],h['source'],h['function'])
            if key not in keys:unique.append(h);keys.add(key)
        return {'corpus_functions':len(self.records),'matches':len(unique),'hits':unique[:top]}
