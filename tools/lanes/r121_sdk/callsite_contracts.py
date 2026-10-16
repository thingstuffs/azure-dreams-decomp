"""Disambiguate callee C twins using an existing matched caller declaration.

Never invent a prototype. This only selects among complete registered C bodies
which both source and encoded target callees reproduce in full. An explicit
caller prototype must agree exactly. An old-style declaration supplies only
its return type; default-promoted parameters and the actual matched call arity
filter the body-backed alternatives. The compiler and native gates decide.
"""
import functools,re
from contracts import declaration,type_of


def arities(text,name):
    result=[]
    for match in re.finditer(r'\b'+re.escape(name)+r'\s*\(',text):
        start=match.end();depth=1;count=0;cursor=start
        while cursor<len(text) and depth:
            char=text[cursor]
            if char=='(':depth+=1
            elif char==')':depth-=1
            elif char==',' and depth==1:count+=1
            cursor+=1
        if depth:continue
        result.append(count+1 if text[start:cursor-1].strip() else 0)
    return set(result)


@functools.lru_cache(maxsize=2048)
def header_text(base,headers):
    from pathlib import Path
    root=Path(base);texts=[];seen=set();todo=[root/h for h in headers]
    while todo:
        path=todo.pop()
        if path in seen or not path.is_file():continue
        seen.add(path);text=path.read_text();texts.append(text)
        for name in re.findall(r'^\s*#\s*include\s*"([^"\n]+)"',text,re.M):
            todo.append(root/'include'/name)
    return '\n'.join(texts)


def caller_interface(world,donor,address):
    import twins
    text=world.text[donor['id']];bare=twins.strip(text)
    names={s for s in re.findall(r'\b\w+\b',bare) if
           (re.fullmatch(r'func_[\da-fA-F]{8}',s) and int(s[5:],16)==address) or world.alias.get(s)==address}
    definitions=list(twins.DEF.finditer(bare))
    if len(definitions)!=1:return None
    body=bare[definitions[0].end():]
    headers=list(world.module_headers.get(donor['id'],[]))
    headers+=['include/'+s for s in re.findall(r'^\s*#\s*include\s*"([^"\n]+)"',text,re.M)]
    context=twins.strip(header_text(str(twins.BASE),tuple(sorted(set(headers)))))+'\n'+bare[:definitions[0].start()]
    choices=[]
    for name in names:
        counts=arities(body,name)
        if len(counts)!=1:continue
        count=next(iter(counts));found=[]
        pattern=r'^[ \t]*(?:extern\s+)?([A-Za-z_][\w \t*]*?)\b'+re.escape(name)+r'\s*\(([^;{}]*)\)\s*;'
        for match in re.finditer(pattern,context,re.M):
            try:ret=type_of(match[1])
            except ValueError:continue
            contract=dict(name=name,definition=match[1]+name+'('+match[2]+')')
            if match[2].strip():
                try:signature=declaration(contract,'callee')
                except ValueError:continue
            else:signature=None
            found.append(dict(name=name,return_type=ret,arity=count,prototype=signature,definition=contract['definition']))
        explicit=[d for d in found if d['prototype']]
        chosen=explicit or found
        if len({(d['return_type'],d['arity'],d['prototype']) for d in chosen})==1 and chosen:choices.append(chosen[0])
    if len({(d['return_type'],d['arity'],d['prototype']) for d in choices})!=1:return None
    return choices[0] if choices else None


def choose(world,donor,old,new,source_context,target_context,contract,container):
    import twins
    if old==new or old in world.sdk.symbols or not contract or source_context is None:return None
    interface=caller_interface(world,donor,old)
    if not interface:return None
    source_start,source_end,source_vram=source_context
    if not source_vram<=old<source_vram+source_end-source_start:return None
    if not target_context['vram']<=new<target_context['vram']+target_context['end']-target_context['start']:return None
    source_offset=source_start+old-source_vram
    target_offset=target_context['start']+new-target_context['vram']
    canonical=world.byid.get(contract['row'])
    if not canonical:return None
    size=canonical['size'];options=[]
    for row,proof in world.twins_at(container,target_offset):
        if row['size']!=size or source_offset+size>source_end or target_offset+size>target_context['end']:continue
        dd=world.byrow.get(row['id'],[])
        if len(dd)!=1:continue
        definition=dd[0]
        try:signature=declaration(definition,'callee')
        except ValueError:continue
        if interface['prototype']:
            if signature!=interface['prototype']:continue
        else:
            params=signature[signature.index('(')+1:-2].split(', ')
            if params==['void']:params=[]
            ret=type_of(signature[len('extern '):signature.index('callee')].strip())
            if ret!=interface['return_type'] or len(params)!=interface['arity']:continue
            if any(p not in ('s32','u32','int','unsigned int','long','unsigned long','double','void *') for p in params):continue
        source_proof=twins.proof(world.words(row['container'],row['foff'],size),world.words(donor['container'],source_offset,size))
        if source_proof is None:continue
        options.append((definition,source_proof))
    if not options:return None
    current=declaration(contract,'callee')
    agreeing=[option for option in options if declaration(option[0],'callee')==current]
    if agreeing:return None
    definition,source_proof=min(options,key=lambda option:(declaration(option[0],'callee'),option[0]['row']))
    selected=dict(definition,binding='complete-source-and-target-callee-twin-matched-caller-interface')
    evidence=dict(interface=interface,source_context=dict(start=source_start,end=source_end,vram=source_vram),
        source_callee_foff=source_offset,target_callee_foff=target_offset,bytes=size,source_body_proof=source_proof,
        previous_body_row=contract['row'],selected_body_row=selected['row'],selected_prototype=declaration(selected,'callee'))
    return selected,evidence
