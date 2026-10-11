#!/usr/bin/env python3
"""Read-only gdb observers for the copied static i386 cc1. Never write inferior state."""
import json, os, sys
try:
    import gdb
except ImportError:
    gdb=None
if gdb:
    A=json.load(open(os.environ['COOK_SYMBOLS']))
    out=open(os.environ['COOK_TRACE'],'w')
    inf=gdb.selected_inferior()
    def u(p): return int.from_bytes(bytes(inf.read_memory(p,4)),'little')
    def s(p):
        v=u(p);return v-(1<<32) if v & (1<<31) else v
    def arg(n): return u(int(gdb.parse_and_eval('$esp'))+4*(n+1))
    def val(n): return u(A[n])
    def elem(n,i): return s(val(n)+4*i)
    def emit(t,**kw): out.write(json.dumps({'event':t,**kw})+'\n');out.flush()
    def ptr(x,i):return u(x+4+4*i)
    def fmt(x,depth=0):
        if not x or depth>7:return None
        code=u(x)&65535
        name=A['_codes'][code] if code<len(A['_codes']) else 'unknown'
        if name=='reg':return ['reg',ptr(x,0),bytes(inf.read_memory(x+3,1))[0]]
        if name=='const_int':return ['const',s(x+4)]
        if name in ('set','plus','minus','mult','and','ior','xor','ashift','ashiftrt','lshiftrt'):
            return [name,fmt(ptr(x,0),depth+1),fmt(ptr(x,1),depth+1)]
        if name in ('mem','sign_extend','zero_extend','subreg','high','const'):
            return [name,fmt(ptr(x,0),depth+1)]
        return [name]
    def pattern(x):return ptr(x,3)
    def rtx(x):
        if not x:return None
        raw=bytes(inf.read_memory(x,4));return {'ptr':x,'code':int.from_bytes(raw[:2],'little'), 'mode':raw[2], 'field0':ptr(x,0)}
    class BP(gdb.Breakpoint):
        def __init__(self,name,fn):
            super().__init__('*0x%x'%A[name],internal=True);self.fn=fn
        def stop(self):
            try:self.fn()
            except Exception as e:emit('error',message=str(e))
            return False
    class Done(gdb.FinishBreakpoint):
        def __init__(self,fn):super().__init__(internal=True);self.fn=fn
        def stop(self):
            try:self.fn(int(gdb.parse_and_eval('$eax')))
            except Exception as e:emit('error',message=str(e))
            return False
    def local():
        nq=val('next_qty')
        tab=[{'q':q,'pseudo':elem('qty_first_reg',q),'refs':elem('qty_n_refs',q),
              'birth':elem('qty_birth',q),'death':elem('qty_death',q),'size':elem('qty_size',q)} for q in range(nq)]
        emit('local_request',q=arg(2),suggested=arg(4),next_qty=nq,table=tab)
        Done(lambda ret:emit('local_return',hard=ret))
    def glob():
        ids=[s(arg(i)) for i in range(2)]
        tab=[{'a':q,'pseudo':elem('allocno_reg',q),'refs':elem('allocno_n_refs',q),
              'length':elem('allocno_live_length',q),'size':elem('allocno_size',q)} for q in ids]
        emit('global_compare',table=tab)
        Done(lambda ret:emit('global_return',value=ret if ret < 1<<31 else ret-(1<<32)))
    def birth():
        p=arg(0); code=u(p)&65535
        details={'pattern':rtx(p),'reload_completed':val('reload_completed')}
        # The code table is derived from the copied compiler's rtl.def.
        if code==A['_set_code']:
            dst=ptr(p,0);details['dest']=rtx(dst)
            if (u(dst)&65535)==A['_reg_code']:
                reg=ptr(dst,0);details['reg']=reg
                details['sets']=int.from_bytes(bytes(inf.read_memory(val('reg_n_sets')+2*reg,2)),'little',signed=True)
                live=val('bb_live_regs')
                details['live']=bool(u(live+4*(reg//32)) & (1<<(reg%32)))
        emit('birth_test',**details)
        Done(lambda ret:emit('birth_return',value=ret))
    def cse():
        new,old=arg(0),arg(1)
        details=dict(new=new,old=old,
             block_start=val('cse_basic_block_start'),block_end=val('cse_basic_block_end'),
             new_first=elem('uid_cuid',elem('regno_first_uid',new)),
             new_last=elem('uid_cuid',elem('regno_last_uid',new)),
             old_last=elem('uid_cuid',elem('regno_last_uid',old)))
        q=elem('_cse_reg_qty',old)
        details['head_before']=elem('_cse_qty_first_reg',q)
        Done(lambda ret:emit('cse_equivalence',head_after=elem('_cse_qty_first_reg',q),**details))
    def simplify():
        setp,insn=arg(0),arg(1);src0=rtx(ptr(setp,1));dest0=rtx(ptr(setp,0));uid=ptr(insn,0)
        def done(ret):emit('reload_simplify',uid=uid,dest=dest0,before=src0,after=rtx(ptr(setp,1)))
        Done(done)
    def compare_qty():
        q1,q2=arg(0),arg(1)
        emit('qty_compare',q1=q1,q2=q2)
        Done(lambda ret:emit('qty_compare_return',value=ret if ret<1<<31 else ret-(1<<32)))
    def used():
        x,final=arg(2),arg(3)
        if not final or (u(x)&65535)!=A['_reg_code']:return
        reg=ptr(x,0)
        if reg<A['_first_pseudo']:return
        before=elem('reg_n_refs',reg);depth=val('loop_depth')
        Done(lambda ret:emit('flow_reference',reg=reg,depth=depth,before=before,after=elem('reg_n_refs',reg)))
    def tc():
        i3,i2,i1=arg(0),arg(1),arg(2)
        before={'i3':fmt(pattern(i3)),'i2':fmt(pattern(i2))}
        def done(ret):
            emit('combine_attempt',i3=ptr(i3,0),i2=ptr(i2,0),i1=ptr(i1,0) if i1 else None,success=bool(ret),before=before,
                 after={'i3':fmt(pattern(i3)),'i2':fmt(pattern(i2))})
        Done(done)
    def referenced():
        caller=gdb.newest_frame().older().pc()
        if not (A['try_combine']<=caller<A['_try_end']):return
        reg,pat=arg(0),arg(1)
        details={'dest':fmt(reg),'pattern':fmt(pat)}
        Done(lambda ret:emit('combine_i2dest_referenced',result=ret,**details))
    def split():
        loc=arg(0);insn=arg(1)
        emit('combine_split_enter',pattern=rtx(u(loc)),uid=ptr(insn,0))
        Done(lambda ret:emit('combine_split_return',location=ret,pattern=rtx(u(ret)) if ret else None))
    for name,fn in [('find_free_reg',local),('qty_compare',compare_qty),('allocno_compare',glob),('birthing_insn_p',birth),
                     ('make_regs_eqv',cse),('reload_cse_simplify_set',simplify),('find_split_point',split),
                     ('try_combine',tc),('reg_referenced_p',referenced),('mark_used_regs',used)]:BP(name,fn)
    exitcode=[]
    gdb.events.exited.connect(lambda e:exitcode.append(e.exit_code))
    gdb.execute('run',to_string=True)
    emit('end',exit_code=exitcode[-1] if exitcode else None)
    out.close()
else:
    from pathlib import Path
    import argparse,subprocess,struct
    L=Path(__file__).resolve().parents[1]
    CC=L/'scratch/toolchain/compilers/gcc-2.7.2-cdk/cc1'
    def symbols():
        tab={}
        duplicates={}
        for line in subprocess.check_output(['nm','-n',str(CC)],text=True).splitlines():
            p=line.split()
            if len(p)==3:
                tab[p[2]]=int(p[0],16)
                duplicates.setdefault(p[2],[]).append(int(p[0],16))
        textaddrs=[]
        for line in subprocess.check_output(['nm','-n',str(CC)],text=True).splitlines():
            p=line.split()
            if len(p)==3 and p[1] in ('t','T'):textaddrs.append(int(p[0],16))
        tab['_try_end']=min(x for x in textaddrs if x>tab['try_combine'])
        # cse.c and combine.c both define uid_cuid. Pick cse's adjacent table.
        tab['uid_cuid']=min(duplicates['uid_cuid'], key=lambda x:abs(x-tab['cse_basic_block_end']))
        tab['_cse_reg_qty']=min(duplicates['reg_qty'], key=lambda x:abs(x-tab['cse_basic_block_end']))
        tab['_cse_qty_first_reg']=min(duplicates['qty_first_reg'], key=lambda x:abs(x-tab['cse_basic_block_end']))
        tab['loop_depth']=min(duplicates['loop_depth'], key=lambda x:abs(x-tab['basic_block_loop_depth']))
        # GCC 2.7.2 rtl.def lists the codes in order. Store explicit code names for audit.
        import re
        defs=(L/'scratch/toolchain/gcc-src/2.7.2-cdk/rtl.def').read_text()
        codes=re.findall(r'DEF_RTL_EXPR\s*\(\s*(\w+)\s*,\s*"([^"]*)"',defs)
        tab['_first_pseudo']=int(re.search(r'^#define FIRST_PSEUDO_REGISTER (\d+)',(L/'scratch/toolchain/gcc-src/2.7.2-cdk/config/mips/mips.h').read_text(),re.M).group(1))
        tab['_set_code']=[a for a,b in codes].index('SET')
        tab['_reg_code']=[a for a,b in codes].index('REG')
        tab['_codes']=[b for a,b in codes]
        return tab
    p=argparse.ArgumentParser();p.add_argument('tags',nargs='+');a=p.parse_args()
    config=L/'evidence/observer_symbols.json';config.write_text(json.dumps(symbols(),indent=2)+'\n')
    for tag in a.tags:
        out=L/'tmp/build'/tag
        env=dict(os.environ,COOK_SYMBOLS=str(config),COOK_TRACE=str(out/'observe.jsonl'),TMPDIR=str(L/'tmp'),PYTHONDONTWRITEBYTECODE='1')
        argv=['gdb','-batch','-nx','-iex','set pagination off','-iex','set confirm off','-iex','set debuginfod enabled off',
              '-iex','set startup-with-shell off','-x',str(Path(__file__).resolve()),'--args',str(CC),'f.i',
              '-quiet','-O2','-G0','-msoft-float','-da','-dp','-o','observed.s']
        with (out/'gdb.log').open('w') as f:
            subprocess.run(argv,cwd=out,env=env,stdout=f,stderr=subprocess.STDOUT,check=True,timeout=60)
        events=[json.loads(l) for l in (out/'observe.jsonl').read_text().splitlines()]
        assert events[-1]['event']=='end' and events[-1]['exit_code']==0
        assert not any(e['event']=='error' for e in events),events
        assert (out/'f.s').read_bytes()==(out/'observed.s').read_bytes(), 'observer changed compiler assembly'
        print(tag, 'observer faithful', len(events),'events')
