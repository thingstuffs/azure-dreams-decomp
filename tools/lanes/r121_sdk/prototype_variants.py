"""Prove C interface variants from an existing matched caller interface.

The original matched C is never edited. A C copy changes unused formals or
preserves original word conversions explicitly at the interface, then passes
the ordinary score and a production --stage-match window. Its source and
target callees each bind to complete matched bodies. SDK conflicts
are excluded. These are prototype-only proofs, with no coverage credit.
"""
import argparse,collections,fcntl,functools,hashlib,json,os,re,shutil,subprocess,sys
from pathlib import Path
from contracts import declaration,type_of


def canonical(kind):
    return {'int':'s32','unsigned int':'u32','short':'s16','unsigned short':'u16',
            'signed char':'s8','unsigned char':'u8'}.get(kind,kind)


def parts(signature):
    match=re.fullmatch(r'extern (.*?) callee\((.*)\);',signature)
    if not match:raise ValueError('unsupported caller prototype')
    params=match[2].split(', ')
    return canonical(match[1]),[] if params==['void'] else [canonical(p) for p in params]


def word_conversion(before,after):
    words={'void *','s8','u8','s16','u16','s32','u32'}
    if before not in words or after not in words:return False
    if 'void *' in (before,after):return before in ('void *','s32','u32') and after in ('void *','s32','u32')
    return True


def cast_returns(body,before,after):
    """Preserve the old return conversion before the new public conversion."""
    masked=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
        lambda m:''.join('\n' if c=='\n' else ' ' for c in m[0]),body,flags=re.S)
    replacements=[]
    for match in re.finditer(r'\breturn\b',masked):
        cursor=match.end();depth=0
        while cursor<len(masked):
            char=masked[cursor]
            if char in '([':depth+=1
            elif char in ')]':depth-=1
            elif char in '{}':return None
            elif char==';' and depth==0:break
            if depth<0:return None
            cursor+=1
        if cursor==len(masked) or not masked[match.end():cursor].strip():return None
        expression=body[match.end():cursor].strip()
        replacements.append((match.start(),cursor+1,'return ('+after+')('+before+')('+expression+');'))
    if not replacements:return None
    for start,end,replacement in reversed(replacements):body=body[:start]+replacement+body[end:]
    return body


def prepare(world,contract,interface):
    import twins
    if not interface or not interface.get('prototype'):return None
    desired_return,desired=parts(interface['prototype'])
    word_types={'void *','s8','u8','s16','u16','s32','u32'}
    if desired_return not in word_types|{'void'} or any(p not in word_types for p in desired):return None
    original=world.text.get(contract['row'])
    if original is None:return None
    from pin_census import sites_of
    if sites_of(original) or re.search(r'\b(?:asm|__asm__|volatile|goto|NON_MATCHING|ASM_\w+)\b',twins.strip(original)):return None
    masked=re.sub(r'/\*.*?\*/|//[^\n]*|"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'',
        lambda m:''.join('\n' if c=='\n' else ' ' for c in m[0]),original,flags=re.S)
    definition=next((m for m in twins.DEF.finditer(masked) if m[2]==contract['name']),None)
    if definition is None:return None
    original_return=canonical(type_of(definition[1]));typed=interface.get('typed_boundary_conversions',False)
    if original_return!=desired_return and not (typed and word_conversion(original_return,desired_return)):return None
    parameters=[p.strip() for p in definition[3].split(',')]
    if parameters==['void']:parameters=[]
    if not all(parameters):return None
    # Only the selected function's body owns parameter-use evidence.
    depth=1;end=definition.end()
    while end<len(original) and depth:
        if masked[end]=='{':depth+=1
        elif masked[end]=='}':depth-=1
        end+=1
    if depth:return None
    body=masked[definition.end():end-1];kept=[];changes=[];locals=[];casts={};views={}
    for i,param in enumerate(parameters):
        match=re.search(r'\b([A-Za-z_]\w*)\s*$',param)
        if not match:return None
        name=match[1];used=bool(re.search(r'\b'+re.escape(name)+r'\b',body))
        old=canonical(type_of(param,True))
        if old not in word_types:return None
        if i<len(desired) and old==desired[i]:kept.append(param)
        elif used:
            if i>=len(desired) or not typed or not word_conversion(old,desired[i]):return None
            temporary='abi_input_'+str(i)
            if re.search(r'\b'+temporary+r'\b',original):return None
            oldtype=re.sub(r'\bregister\s+','',param[:match.start()].strip())
            if not oldtype:return None
            if interface.get('parameter_conversion_style')=='scalar-interface' and old in ('s8','u8','s16','u16','s32','u32') and desired[i] in ('s8','u8','s16','u16','s32','u32'):
                kept.append(desired[i]+' '+name)
                changes.append(dict(index=i,kind='used-word-parameter-direct-interface-type',before=param,after=kept[-1]))
            elif interface.get('parameter_conversion_style')=='stack-byte-local' and i>=4 and old in ('s8','u8') and desired[i] in ('s32','u32'):
                kept.append(desired[i]+' '+temporary)
                locals.append(oldtype+' '+name+' = *('+oldtype+' *)&'+temporary+';')
                changes.append(dict(index=i,kind='used-word-parameter-original-stack-byte-conversion',before=param,after=kept[-1],local=locals[-1]))
            elif interface.get('parameter_conversion_style') in ('cast-uses','stack-byte-view','stack-byte-local','scalar-interface'):
                kept.append(desired[i]+' '+name)
                if interface.get('parameter_conversion_style')=='stack-byte-view' and i>=4 and old in ('s8','u8') and desired[i] in ('s32','u32'):
                    views[name]=oldtype
                    changes.append(dict(index=i,kind='used-word-parameter-original-stack-byte-conversion',before=param,after=kept[-1],byte_type=oldtype))
                else:
                    casts[name]=oldtype
                    changes.append(dict(index=i,kind='used-word-parameter-original-use-conversion',before=param,after=kept[-1],cast=oldtype))
            else:
                kept.append(desired[i]+' '+temporary)
                locals.append(oldtype+' '+name+' = ('+oldtype+')'+temporary+';')
                changes.append(dict(index=i,kind='used-word-parameter-original-local-conversion',before=param,after=kept[-1],local=locals[-1]))
        elif i<len(desired):
            kept.append(desired[i]+' '+name);changes.append(dict(index=i,kind='unused-type',before=param,after=kept[-1]))
        else:changes.append(dict(index=i,kind='unused-trailing-parameter-removed',before=param))
    for i in range(len(parameters),len(desired)):
        name='abi_unused_'+str(i)
        if re.search(r'\b'+name+r'\b',original):return None
        kept.append(desired[i]+' '+name);changes.append(dict(index=i,kind='unused-parameter-added',after=kept[-1]))
    prefix=definition[1]
    if original_return!=desired_return:
        prefix=desired_return+' '
        changes.append(dict(kind='return-original-then-public-word-conversion',before=definition[1].strip(),after=desired_return))
    if not changes:return None
    replacement=prefix+definition[2]+'('+(', '.join(kept) if kept else 'void')+')'
    variant=dict(name=definition[2],definition=' '.join(replacement.split()))
    expected_return,expected=parts(declaration(variant,'callee'))
    if (expected_return,expected)!=(desired_return,desired):return None
    start,end_signature=definition.start(),definition.end()-1
    text=original[:start]+replacement+' '+original[end_signature:]
    if locals or casts or views or original_return!=desired_return:
        new_body=original[definition.end():end-1]
        replacements=[]
        for name,oldtype in (casts|views).items():
            for use in re.finditer(r'\b'+re.escape(name)+r'\b',body):
                # Address-taking, writes and shadowing are outside this
                # read-conversion idiom. A cast is deliberately no lvalue.
                if re.search(r'(?:&|\+\+|--|\.|->)\s*$',body[:use.start()]):return None
                if re.match(r'\s*(?:\+\+|--|[+*/%&|^<>-]?=(?!=))',body[use.end():]):return None
                expression='*('+oldtype+' *)&'+name if name in views else '('+oldtype+')'+name
                replacements.append((use.start(),use.end(),expression))
        for a,b,replacement_use in sorted(replacements,reverse=True):new_body=new_body[:a]+'('+replacement_use+')'+new_body[b:]
        if original_return!=desired_return:
            new_body=cast_returns(new_body,definition[1].strip(),desired_return)
            if new_body is None:return None
        if locals:new_body='\n    '+'\n    '.join(locals)+'\n'+new_body
        text=original[:start]+replacement+' {'+new_body+original[end-1:]
    if '#include "common.h"' not in text:text='#include "common.h"\n'+text
    return text,variant,changes


def unused_machine_args_strict(world,row,changes):
    """Strong leaf-only proof: changed argument registers are never read.

    No call/tailcall/computed transfer can forward an implicit argument.
    Stack-argument changes additionally require no stack accesses or frame.
    Local reuse of a changed argument register is conservatively refused.
    """
    assert all(c['kind'].startswith('unused-') or c['kind'] in ('used-word-parameter-original-local-conversion','used-word-parameter-original-use-conversion','used-word-parameter-original-stack-byte-conversion','used-word-parameter-direct-interface-type','return-original-then-public-word-conversion') for c in changes)
    changes=[c for c in changes if c['kind'].startswith('unused-')]
    if not changes:return dict(basis='typed-C-copy-original-local-and-return-conversions',passed=True)
    words=world.words(row['container'],row['foff'],row['size'])
    from function_boundaries import terminal_return
    if terminal_return(words) is None:return None
    registers={4+c['index'] for c in changes if c['index']<4}
    stack=any(c['index']>=4 for c in changes)
    true=row.get('true_name');vram=int(true[5:],16) if true and true.startswith('func_') else None
    read=set()
    for i,word in enumerate(words):
        op=word>>26;rs=word>>21&31;rt=word>>16&31;rd=word>>11&31;fn=word&63
        if op==3 or (op==0 and fn==9) or (op==1 and rt in (16,17,18,19)):return None
        if op==2:
            target=0x80000000|((word&0x3ffffff)<<2)
            if vram is None or not vram<=target<vram+row['size']:return None
            continue
        if op==0:
            if fn==8:
                if rs!=31:return None
                read.add(rs)
            elif fn in (0,2,3):read.add(rt)
            elif fn in (4,6,7,24,25,26,27,32,33,34,35,36,37,38,39,42,43):read.update((rs,rt))
            elif fn in (17,19):read.add(rs)
            elif fn not in (16,18):return None
            if stack and rd==29:return None
        elif op in (4,5):read.update((rs,rt))
        elif op in (34,38):read.update((rs,rt))
        elif op in (1,6,7,8,9,10,11,12,13,14,32,33,35,36,37):read.add(rs)
        elif op==15:pass
        elif op in (40,41,42,43,46):read.update((rs,rt))
        else:return None
        if op in (1,4,5,6,7):
            offset=word&65535;offset-=65536 if offset&32768 else 0
            if not 0<=i+1+offset<len(words):return None
        if stack and (rs==29 or (op in (8,9,10,11,12,13,14,15,32,33,34,35,36,37,38) and rt==29)):return None
    if read&registers:return None
    return dict(changed_argument_registers=sorted(registers),read_registers=sorted(read),
                changed_stack_arguments=stack,calls=False,computed_transfers=False,passed=True)


def unused_incoming_flow(world,row,changes):
    """Refuse every read of an incoming changed argument before overwrite.

    All argument registers are implicit reads at an external transfer after
    its delay slot. Thus a non-leaf can pass only after every changed input
    has been overwritten on every reaching path. No tainted value is copied
    or stored, and stack arguments remain outside this fallback.
    """
    if any(c['index']>=4 for c in changes):return None
    changed={4+c['index'] for c in changes}
    words=world.words(row['container'],row['foff'],row['size']);count=len(words)
    true=row.get('true_name')
    if not true or not true.startswith('func_'):return None
    vram=int(true[5:],16)
    from function_boundaries import terminal_return
    if terminal_return(words) is None:return None
    reads={};writes={};load_writes={};successors={i:[i+1] if i+1<count else [] for i in range(count)}
    observers=set();slots=set();branches=[]
    for i,w in enumerate(words):
        op=w>>26;rs=w>>21&31;rt=w>>16&31;rd=w>>11&31;fn=w&63
        r=set();d=set();control=False
        if op==0:
            if fn in (0,2,3):r.add(rt);d.add(rd)
            elif fn in (4,6,7,32,33,34,35,36,37,38,39,42,43):r.update((rs,rt));d.add(rd)
            elif fn in (24,25,26,27):r.update((rs,rt))
            elif fn in (16,18):d.add(rd)
            elif fn in (17,19):r.add(rs)
            elif fn in (8,9):
                r.add(rs);control=True
                if fn==9:d.add(rd)
                if i+1>=count:return None
                slots.add(i+1)
                if fn==9:
                    observers.add(i+1);successors[i+1]=[i+2] if i+2<count else []
                else:
                    successors[i+1]=[]
                    if rs!=31:observers.add(i+1)
            else:return None
        elif op in (1,4,5,6,7):
            if op==1 and rt not in (0,1):return None
            r.add(rs)
            if op in (4,5):r.add(rt)
            if i+1>=count:return None
            offset=w&65535;offset-=65536 if offset&32768 else 0
            target=i+1+offset
            if not 0<=target<count:return None
            control=True;slots.add(i+1);branches.append(target)
            successors[i+1]=[j for j in (target,i+2) if j<count]
        elif op in (2,3):
            if i+1>=count:return None
            control=True;slots.add(i+1)
            if op==3:
                d.add(31);observers.add(i+1);successors[i+1]=[i+2] if i+2<count else []
            else:
                target=((vram+i*4+4)&0xf0000000)|((w&0x3ffffff)<<2)
                index=(target-vram)//4
                if vram<=target<vram+count*4 and (target-vram)%4==0:
                    successors[i+1]=[index];branches.append(index)
                else:observers.add(i+1);successors[i+1]=[]
        elif op in (8,9,10,11,12,13,14,32,33,34,35,36,37,38):
            r.add(rs);d.add(rt)
            if op in (34,38):r.add(rt)
        elif op==15:d.add(rt)
        elif op in (40,41,42,43,46):r.update((rs,rt))
        else:return None
        if control and i in slots:return None
        reads[i]=r-{0};writes[i]=d-{0}
        load_writes[i]=writes[i] if op in (32,33,34,35,36,37,38) else set()
    if any(target in slots for target in branches):return None
    # Keep path states separate: a pending load on one predecessor must not
    # erase an incoming argument that survives on another predecessor.
    initial=sum(1<<r for r in changed);queue=collections.deque([(0,initial,0)])
    visited=set();covered=set();all_reads=set();overwrites=set()
    while True:
        while queue:
            i,state,pending=queue.popleft();key=(i,state,pending)
            if key in visited:continue
            visited.add(key);covered.add(i)
            read_mask=sum(1<<r for r in reads[i])
            if state&read_mask:return None
            all_reads|=reads[i]
            # Reads see the old register in the load-delay instruction.
            # The preceding load commits only after those reads.
            state&=~pending
            write_mask=sum(1<<r for r in writes[i]);load_mask=sum(1<<r for r in load_writes[i])
            if state&write_mask:overwrites.add(i)
            result=state&~(write_mask&~load_mask)
            next_pending=result&load_mask
            if i in observers and result:return None
            for j in successors[i]:
                queue.append((j,result,next_pending))
        missing=next((i for i in range(count) if i not in covered),None)
        if missing is None:break
        queue.append((missing,initial,0))
    return dict(basis='incoming-changed-register-def-use-with-delay-slots',changed_argument_registers=sorted(changed),
        read_registers=sorted(all_reads),changed_stack_arguments=False,external_transfer_delay_slots=sorted(observers),
        overwrite_words=sorted(overwrites),passed=True)


def unused_machine_args(world,row,changes):
    result=unused_machine_args_strict(world,row,changes)
    if result is not None:return result
    unused=[c for c in changes if c['kind'].startswith('unused-')]
    return unused_incoming_flow(world,row,unused) if unused else None


def root_path():
    import twins
    return twins.HOME_LANE/'evidence/continue3/prototype_variants'


@functools.lru_cache(maxsize=1)
def header_digest():
    import twins
    headers={str(p.relative_to(twins.BASE)):twins.sha(p) for p in (twins.BASE/'include').rglob('*.h')}
    assert all(twins.sha(twins.R/p)==h for p,h in headers.items())
    return hashlib.sha256(json.dumps(headers,sort_keys=True).encode()).hexdigest()


def prove(request_path):
    import twins
    from verify import verify_overlay
    request=json.loads(request_path.read_text());out=request_path.parent
    world=twins.World();row=world.byid[request['callee']['row']]
    assert twins.sha(twins.R/request['callee']['source'])==twins.sha(twins.BASE/request['callee']['source'])
    result=prepare(world,request['callee'],request['interface']);assert result is not None
    text,variant,changes=result;source=out/'variant.c';source.write_text(text)
    assert twins.sha(source)==request['source_sha256'] and variant==request['variant'] and changes==request['changes']
    machine=unused_machine_args(world,row,changes);assert machine and machine==request['unused_machine_args']
    headers={str(p.relative_to(twins.BASE)):twins.sha(p) for p in (twins.BASE/'include').rglob('*.h')}
    assert all(twins.sha(twins.R/p)==h for p,h in headers.items())
    score=verify_overlay(row,source)
    gate_hash=twins.sha(twins.BASE/'tools/gate/overlay_local_gate.py')
    assert twins.sha(twins.R/'build_ovl/tools/overlay_local_gate.py')==gate_hash
    receipt=dict(request,score=score,source=str(source.relative_to(twins.HOME_LANE)),status='HOLD',
        prototype_only=True,additional_c_rows=0,additional_c_bytes=0,
        production_gate_sha256=gate_hash,
        headers_sha256=hashlib.sha256(json.dumps(headers,sort_keys=True).encode()).hexdigest())
    if score.get('exact') and score.get('total')==0:
        command=[twins.PY,'tools/overlay_local_gate.py','--config',row['gate_config'],'--clean',
                 '--stage-match',row['func'],source,row['cfg']]
        p=twins.command(command,cwd=twins.R/'build_ovl',log=out/'window.log',timeout=3600)
        receipt['window_gate']=dict(command=list(map(str,command)),returncode=p.returncode,
            stdout=p.stdout[-1800:],stderr=p.stderr[-1800:])
        if p.returncode==0 and any(line.startswith('MATCH') for line in p.stdout.splitlines()):
            import yaml
            cfg=yaml.safe_load((twins.R/row['gate_config']).read_text());name=cfg['name']
            directory=twins.R/'build_ovl/work/s3_splat'/name
            manifest=json.loads((directory/(name+'_manifest.json')).read_text())
            entries=[e for e in manifest['c_segments'] if int(e['file_start'],0)==row['foff'] and e['size']==row['size']]
            assert len(entries)==1;entry=entries[0]
            assert (twins.R/'build_ovl'/entry['source']).resolve()==source.resolve() and entry['config']==row['cfg']
            expected=row.get('true_name',row['func']);assert entry['func']==expected
            duplicate=sum(e['func']==expected for e in manifest['c_segments'])>1
            key=expected+(f"__{row['foff']:06X}" if duplicate else '')
            obj=directory/'build/obj'/(key+'.o');assert obj.is_file()
            shutil.copyfile(obj,out/'variant.o')
            receipt.update(status='PROVED',manifest_entry=entry,object_sha256=twins.sha(out/'variant.o'),
                object=str((out/'variant.o').relative_to(twins.HOME_LANE)),
                retail_sha256=hashlib.sha256(world.B[row['container']][row['foff']:row['foff']+row['size']]).hexdigest())
    twins.save(out/'result.json',receipt)
    print('PROTOTYPE',request['id'],receipt['status'],score,flush=True)


def _get(world,donor,old,new,source_context,target_context,contract,container,conversion_style=None):
    import twins
    from callsite_contracts import caller_interface
    world.prototype_last_hold=None
    if old==new or old in world.sdk.symbols or new in world.sdk.symbols or not contract or contract.get('prototype_variant'):return None
    caller=caller_interface(world,donor,old)
    if not caller:return None
    start,end,vram=source_context
    if not vram<=old<vram+end-start:return None
    source_offset=start+old-vram
    source_contract=world.contract(donor['container'],old,start,vram,end-start)
    if not source_contract:return None
    try:source_signature=declaration(source_contract,'callee');source_return,source_params=parts(source_signature)
    except ValueError:return None
    interface=dict(caller)
    mode='matched-source-callee-body'
    typed=os.environ.get('TWINS_TYPED_INTERFACE','1' if os.environ.get('TWINS_CONTINUE3_ITEM') in ('1','2') else '0')=='1'
    same_body=False
    if typed and caller.get('prototype'):
        callee=world.byid[contract['row']]
        same_body=source_offset+callee['size']<=end and twins.proof(world.words(callee['container'],callee['foff'],callee['size']),
            world.words(donor['container'],source_offset,callee['size'])) is not None
    if same_body:
        mode='same-complete-body-matched-caller-interface'
    elif len(source_params)==caller['arity'] and source_return==canonical(caller['return_type']):
        interface['prototype']=source_signature
    elif caller.get('prototype'):
        # For a true source/target body twin, the same fully gated unused-
        # formal variant proves both interfaces. No alternate implementation
        # is allowed down this fallback path.
        mode='same-complete-body-matched-caller-interface'
        callee=world.byid[contract['row']]
        if source_offset+callee['size']>end or twins.proof(world.words(callee['container'],callee['foff'],callee['size']),
            world.words(donor['container'],source_offset,callee['size'])) is None:return None
    else:return None
    if typed:
        interface['typed_boundary_conversions']=True
        style=conversion_style or os.environ.get('TWINS_TYPE_CONVERSION_STYLE','cast-uses')
        if style in ('cast-uses','stack-byte-view','stack-byte-local','scalar-interface'):interface['parameter_conversion_style']=style
    try:
        if len(parts(interface['prototype'])[1])!=caller['arity']:return None
        if parts(declaration(contract,'callee'))==parts(interface['prototype']):return None
        result=prepare(world,contract,interface)
    except ValueError:return None
    if result is None:return None
    text,variant,changes=result;callee=world.byid[contract['row']];size=callee['size']
    if callee['container'] not in world.B or callee.get('row_kind')=='data':return None
    machine=unused_machine_args(world,callee,changes)
    if not machine:return None
    source_proof=world.target_contract_proof(donor['container'],old,start,vram,end-start,source_contract,old)
    if not source_proof or source_offset+source_proof.get('bytes',0)>end:return None
    target_proof=world.target_contract_proof(container,new,target_context['start'],target_context['vram'],
        target_context['end']-target_context['start'],contract,old)
    if not target_proof or target_proof['row']!=callee['id'] or target_proof['binding'] not in (
        'complete-target-callee-retail-twin','complete-target-callee-flow-retail-twin'):return None
    target_offset=target_context['start']+new-target_context['vram']
    if target_offset+size>target_context['end']:return None
    target_row=dict(callee,container=container,foff=target_offset,true_name=f'func_{new:08X}')
    target_machine=unused_machine_args(world,target_row,changes)
    if not target_machine:return None
    if mode=='same-complete-body-matched-caller-interface':
        source_row=dict(callee,container=donor['container'],foff=source_offset,true_name=f'func_{old:08X}')
        if unused_machine_args(world,source_row,changes) is None:return None
    identity=dict(row=callee['id'],original_sha256=twins.sha(twins.BASE/contract['source']),
                  source_sha256=hashlib.sha256(text.encode()).hexdigest(),cfg=callee['cfg'])
    key=hashlib.sha256(json.dumps(identity,sort_keys=True).encode()).hexdigest()[:20]
    out=root_path()/key;out.mkdir(parents=True,exist_ok=True)
    path=out/'result.json'
    # One dedicated, idle proof tree. It is outside the five mutable family
    # workers; the global lock bounds total active compiler jobs at seven.
    with (root_path()/'proof.lock').open('w') as lock:
        fcntl.flock(lock,fcntl.LOCK_EX)
        if path.exists():
            previous=json.loads(path.read_text())
            if previous['status']=='PROVED' and 'production_gate_sha256' not in previous:
                path.rename(out/'pilot_result.json')
        if not path.exists():
            request=dict(id=key,**identity,callee={k:contract[k] for k in ('row','source','name','definition')},
                variant=variant,changes=changes,interface=interface,unused_machine_args=machine,
                source_authority=source_contract,authority_mode=mode,
                caller=dict(row=donor['id'],source=f"src/{donor['id']}.c"))
            twins.save(out/'request.json',request)
            lane=twins.HOME_LANE/'staging/workers/w06';assert (lane/'ready.json').exists()
            env=dict(os.environ,TWINS_LANE=str(lane),TWINS_WORKERS='1',TWINS_NO_PACKAGE='1')
            with (out/'prove.log').open('w') as log:
                p=subprocess.run(['nice','-n','15',sys.executable,str(twins.HOME_LANE/'scripts/prototype_variants.py'),
                                  '--prove',str(out/'request.json')],cwd=twins.HOME_LANE,env=env,stdout=log,stderr=subprocess.STDOUT)
            if p.returncode:
                twins.save(path,dict(request,status='HOLD',reason='normal prototype proof command failed; see prove.log'))
        record=json.loads(path.read_text())
    if record['status']!='PROVED':
        world.prototype_last_hold=record
        return None
    if 'unused_machine_args' not in record:
        record['unused_machine_args']=machine
        import twins
        twins.save(path,record)
    changed=dict(contract,name=variant['name'],definition=variant['definition'],
        binding='unused-formal-variant-proved-in-production-window',prototype_variant=key,
        original_definition=contract['definition'],prototype_variant_source_sha256=identity['source_sha256'])
    if any(not c['kind'].startswith('unused-') for c in changes):changed['binding']='word-interface-variant-proved-in-production-window'
    if mode=='same-complete-body-matched-caller-interface':
        source_contract=changed
        source_proof=world.target_contract_proof(donor['container'],old,start,vram,end-start,changed,old)
        assert source_proof is not None
    evidence=dict(id=key,interface=interface,caller_interface=caller,mode=mode,source_context=dict(start=start,end=end,vram=vram),
        source_callee_foff=source_offset,source_contract=source_contract,source_body_proof=source_proof,
        target_unused_machine_args=target_machine)
    probes=[dict(index=i,kind='unused-register-probe') for i in range(4)]
    all_canonical=unused_machine_args(world,callee,probes)
    all_target=unused_machine_args(world,target_row,probes) if all_canonical else None
    if all_canonical and all_target:
        changed=dict(changed,proved_ignored_argument_indices=list(range(4)))
        evidence['all_argument_registers_unused']=dict(canonical=all_canonical,target=all_target)
    return changed,evidence


def get(world,donor,old,new,source_context,target_context,contract,container):
    result=_get(world,donor,old,new,source_context,target_context,contract,container)
    if result is not None:return result
    held=getattr(world,'prototype_last_hold',None)
    if held and held.get('score',{}).get('total') and any(c['kind']=='used-word-parameter-original-use-conversion' for c in held['changes']):
        result=_get(world,donor,old,new,source_context,target_context,contract,container,conversion_style='local')
        if result is not None:return result
        held=getattr(world,'prototype_last_hold',None)
    if held and held.get('score',{}).get('total') and any(c.get('index',0)>=4 and c['kind'].startswith('used-word-parameter-') and canonical(type_of(c['before'],True)) in ('s8','u8') and canonical(type_of(c['after'],True)) in ('s32','u32') for c in held['changes']):
        result=_get(world,donor,old,new,source_context,target_context,contract,container,conversion_style='stack-byte-view')
        if result is not None:return result
        held=getattr(world,'prototype_last_hold',None)
    # A forced matched header can forbid a new formal list for this source
    # symbol. Keep that header. Another complete matched body may provide the
    # C copy using its ordinary recipe. Original-interface disagreements must
    # be confined to inputs independently proved ignored by the native code.
    if not held or 'conflicting types' not in (held.get('score',{}).get('err') or ''):return None
    import twins
    from callsite_contracts import header_text
    try:signature=parts(declaration(contract,'callee'))
    except ValueError:return None
    offset=target_context['start']+new-target_context['vram']
    if not target_context['start']<=offset<target_context['end']:return None
    options=[]
    for row,_ in world.twins_at(container,offset):
        if row['id']==contract['row'] or row['container'] not in world.B or not row.get('gate_config'):continue
        if row['size']!=world.byid[contract['row']]['size']:continue
        definitions=world.byrow.get(row['id'],[])
        if len(definitions)!=1:continue
        definition=definitions[0]
        try:
            alternative_signature=parts(declaration(definition,'callee'))
            if alternative_signature!=signature:
                if alternative_signature[0]!=signature[0]:continue
                intermediate=prepare(world,definition,dict(prototype=declaration(contract,'callee')))
                if intermediate is None or any(not c['kind'].startswith('unused-') for c in intermediate[2]):continue
                if unused_machine_args(world,row,intermediate[2]) is None:continue
        except ValueError:continue
        text=world.text.get(row['id'],'');bare=twins.strip(text)
        if not text or re.search(r'\b(?:goto|asm|__asm__|volatile|NON_MATCHING)\b',bare):continue
        headers=list(world.module_headers.get(row['id'],[]))
        headers+=['include/'+s for s in re.findall(r'^\s*#\s*include\s*"([^"\n]+)"',text,re.M)]
        context=twins.strip(header_text(str(twins.BASE),tuple(sorted(set(headers)))))
        own=next((m for m in twins.DEF.finditer(bare) if m[2]==definition['name']),None)
        if own is None:continue
        context+='\n'+bare[:own.start()]
        if re.search(r'\b'+re.escape(definition['name'])+r'\s*\(',context):continue
        options.append(definition)
    for definition in sorted(options,key=lambda d:(len(world.text[d['row']]),d['row']))[:3]:
        alternative=dict(definition,binding='complete-target-callee-retail-twin-proved-unused-interface')
        result=_get(world,donor,old,new,source_context,target_context,alternative,container)
        if result is not None and compatible(result[0],contract):return result
    return None


def compatible(contract,definition):
    if parts(declaration(contract,'callee'))==parts(declaration(definition,'callee')):return True
    key=contract.get('prototype_variant')
    if not key:return False
    record=json.loads((root_path()/key/'result.json').read_text())
    if record['status']!='PROVED':return False
    actual_return,actual=parts(declaration(definition,'callee'))
    if parts(declaration(record['callee'],'callee'))==(actual_return,actual):return True
    public_return,public=parts(declaration(contract,'callee'))
    words={'void *','s8','u8','s16','u16','s32','u32'}
    if actual_return!=public_return or any(p not in words for p in actual+public):return False
    ignored={c['index'] for c in record['changes'] if c['kind'].startswith('unused-')}
    if contract.get('proved_ignored_argument_indices')==list(range(4)):ignored.update(range(4))
    for index in range(max(len(actual),len(public))):
        if index<len(actual) and index<len(public) and actual[index]==public[index]:continue
        if index not in ignored:return False
    return bool(record['unused_machine_args']['passed'])


def validate(world,donor,call,context,container):
    """Independently bind the interface, complete callees and native artifact."""
    import twins
    from callsite_contracts import caller_interface
    contract=call['contract'];evidence=call['prototype_variant_proof'];key=contract['prototype_variant']
    assert key==evidence['id']
    record=json.loads((root_path()/key/'result.json').read_text());assert record['status']=='PROVED'
    original=record['callee'];callee=world.byid[original['row']]
    identity={k:record[k] for k in ('row','original_sha256','source_sha256','cfg')}
    assert identity['row']==callee['id'] and identity['cfg']==callee['cfg']
    assert hashlib.sha256(json.dumps(identity,sort_keys=True).encode()).hexdigest()[:20]==key==record['id']
    definitions=world.byrow[callee['id']];assert len(definitions)==1
    assert all(definitions[0][k]==original[k] for k in ('row','source','name','definition'))
    assert record['original_sha256']==twins.sha(twins.BASE/original['source'])==twins.sha(twins.R/original['source'])
    prepared=prepare(world,original,record['interface']);assert prepared is not None
    text,variant,changes=prepared
    assert variant==record['variant'] and changes==record['changes']
    assert hashlib.sha256(text.encode()).hexdigest()==record['source_sha256']==contract['prototype_variant_source_sha256']
    assert twins.sha(twins.HOME_LANE/record['source'])==record['source_sha256']
    assert all(contract[k]==variant[k] for k in ('name','definition')) and contract['original_definition']==original['definition']
    assert unused_machine_args(world,callee,changes)==record['unused_machine_args']
    assert record['score']['exact'] and record['score']['total']==0
    assert record['score']['gen_words']==record['score']['tgt_words']==callee['size']//4
    gate=record['window_gate'];assert gate['returncode']==0 and any(s.startswith('MATCH') for s in gate['stdout'].splitlines())
    assert record['production_gate_sha256']==twins.sha(twins.BASE/'tools/gate/overlay_local_gate.py')
    assert record['headers_sha256']==header_digest()
    command=gate['command'];assert command[1:5]==['tools/overlay_local_gate.py','--config',callee['gate_config'],'--clean']
    assert command[5]=='--stage-match' and command[6]==callee['func'] and command[8]==callee['cfg']
    assert Path(command[7]).resolve()==(twins.HOME_LANE/record['source']).resolve()
    entry=record['manifest_entry'];assert int(entry['file_start'],0)==callee['foff'] and entry['size']==callee['size'] and entry['config']==callee['cfg']
    assert entry['func']==callee.get('true_name',callee['func'])
    proof_build=twins.HOME_LANE/'staging/workers/w06/staging/root/build_ovl'
    assert (proof_build/entry['source']).resolve()==(twins.HOME_LANE/record['source']).resolve()
    assert twins.sha(twins.HOME_LANE/record['object'])==record['object_sha256']
    from object_relocations import relocations
    relocations(twins.HOME_LANE/record['object'],entry['func'])  # ELF/section sanity, not a masked comparison.
    assert record['retail_sha256']==hashlib.sha256(world.B[callee['container']][callee['foff']:callee['foff']+callee['size']]).hexdigest()
    old=int(call['source_callee'],0);new=int(call['encoded_callee'],0)
    assert old not in world.sdk.symbols and new not in world.sdk.symbols and old!=new
    caller=caller_interface(world,donor,old);assert caller==evidence['caller_interface']
    effective=evidence['interface'];source=evidence['source_contract'];ctx=evidence['source_context']
    regions=[r for r in twins.jl(twins.BASE/f"config/overlays/{donor['container']}.rowbase.jsonl")
             if int(r['foff_start'],0)<=donor['foff'] and donor['foff']+donor['size']<=int(r['foff_end'],0)
             and r.get('base_confidence') in ('proven','solved')]
    assert len(regions)==1;region=regions[0]
    assert ctx==dict(start=int(region['foff_start'],0),end=int(region['foff_end'],0),vram=int(region['foff_start'],0)+int(region['delta'],0))
    source_offset=ctx['start']+old-ctx['vram'];assert source_offset==evidence['source_callee_foff']
    if evidence['mode']=='matched-source-callee-body':
        source_defs=world.byrow[source['row']];assert len(source_defs)==1
        assert all(source_defs[0][k]==source[k] for k in ('row','name','source','definition'))
        assert parts(declaration(source,'callee'))==parts(effective['prototype'])
    else:
        assert evidence['mode']=='same-complete-body-matched-caller-interface'
        assert source['prototype_variant']==key and source['definition']==contract['definition']
        assert parts(effective['prototype'])==parts(caller['prototype'])
        source_row=dict(callee,container=donor['container'],foff=source_offset,true_name=f'func_{old:08X}')
        assert unused_machine_args(world,source_row,changes) is not None
    ret,params=parts(effective['prototype']);assert len(params)==caller['arity'] and ret==canonical(caller['return_type'])
    assert parts(declaration(contract,'callee'))==(ret,params)
    recomputed=world.target_contract_proof(donor['container'],old,ctx['start'],ctx['vram'],ctx['end']-ctx['start'],source,old,recorded=evidence['source_body_proof'])
    assert recomputed==evidence['source_body_proof'] and source_offset+recomputed['bytes']<=ctx['end']
    offset=context['start']+new-context['vram'];assert offset+callee['size']<=context['end']
    target=dict(callee,container=container,foff=offset,true_name=f'func_{new:08X}')
    assert unused_machine_args(world,target,changes)==evidence['target_unused_machine_args']
    if 'proved_ignored_argument_indices' in contract:
        assert contract['proved_ignored_argument_indices']==list(range(4))
        probes=[dict(index=i,kind='unused-register-probe') for i in range(4)]
        assert evidence['all_argument_registers_unused']==dict(canonical=unused_machine_args(world,callee,probes),target=unused_machine_args(world,target,probes))
        assert all(evidence['all_argument_registers_unused'].values())
    else:assert 'all_argument_registers_unused' not in evidence
    return record


if __name__=='__main__':
    parser=argparse.ArgumentParser(description=__doc__);parser.add_argument('--prove',type=Path,required=True)
    prove(parser.parse_args().prove)
