"""GDB half of pass_oracle. Never calls inferior functions; selectors are explicit."""
import gdb, json, struct
with open('pass_cfg.json') as f: C=json.load(f)
A=C['addresses']; SZ=C['sizes']; F=set(C['families'])
# One change (dict) or a composite (list of changes, applied together in one run).
CHANGES=C['change'] if isinstance(C['change'],list) else ([C['change']] if C['change'] else [])
INF=gdb.selected_inferior(); R={'missing_hooks':[],'events':[],'mutations':[],'errors':[],'applied':False,'applied_changes':[],'truncated':False,'refs':[],'stats':[],
                               'hook_counts':{},'skipped_hooks':[],'skipped_sites':[]}
rtx_names=[]; formats=[]; modes=[]; sched_context=[]; combine_context=[]; cse_context=[]; ref_depth=0
mem_insns={}; hook_names=[]; occurrences={}; ACTIVE=False
def mem(a,n): return bytes(INF.read_memory(a,n))
def u32(a):return struct.unpack('<I',mem(a,4))[0]
def i32(a):return struct.unpack('<i',mem(a,4))[0]
def put(a,v):INF.write_memory(a,struct.pack('<i',v))
def ptr(n):return u32(A[n])
def reg(n):return int(gdb.parse_and_eval('$'+n))&0xffffffff
def arg(i):return u32(reg('esp')+4*(i+1))
def cstr(a,n=160):return mem(a,n).split(b'\0')[0].decode(errors='replace') if a else ''
def active():
    # assign_stack_local runs during expansion, before rest_of_compilation's
    # one-time RTX-table initializer.  current_function_name is already set.
    try:return bool(ptr('current_function_name')) and cstr(ptr('current_function_name'))==C['function']
    except Exception:return ACTIVE
def phase():return 'sched2' if i32(A['reload_completed']) else 'sched1'
def field(x,i):return u32(x+4+4*i)
def uid(x):return i32(x+4) if x else 0
def name(x):
    if not x:return 'nil'
    code=struct.unpack('<H',mem(x,2))[0]
    return rtx_names[code] if code<len(rtx_names) else 'unknown'
def walk(x,depth=0):
    if not x or depth>32:return
    yield x
    if name(x) in ('insn','jump_insn','call_insn','note','code_label','barrier'):return
    code=struct.unpack('<H',mem(x,2))[0]
    if code>=len(formats):raise ValueError('invalid RTX code')
    for i,f in enumerate(formats[code]):
        v=field(x,i)
        if f=='e':yield from walk(v,depth+1)
        elif f=='E' and v:
            n=i32(v)
            if not 0<=n<=4096:raise ValueError('invalid RTX vector')
            for j in range(n):yield from walk(u32(v+4+4*j),depth+1)
def brief(x,depth=0):
    if not x:return 'nil'
    n=name(x)
    if n=='reg':return 'p'+str(i32(x+4))
    if n=='const_int':return str(i32(x+4))
    if n=='symbol_ref':return cstr(field(x,0),80)
    if depth>4:return n
    code=struct.unpack('<H',mem(x,2))[0]
    children=[brief(field(x,i),depth+1) for i,f in enumerate(formats[code]) if f=='e']
    return n+'('+','.join(children)+')'
def record(k,**kw):
    if len(R['events'])<C['max_events']:R['events'].append(dict(kind=k,**kw))
    else:R['truncated']=True
def mutation(k,before,after,**kw):
    if before==after:return
    R['mutations'].append(dict(kind=k,before=before,after=after,**kw));R['applied']=True
    for i,c in enumerate(CHANGES):
        if c['kind']==k and all(c[n]==v for n,v in kw.items() if n in c) and i not in R['applied_changes']:R['applied_changes'].append(i)
def matches(k,**kw):
    # The matching change (truthy) or None; a composite matches any member.
    return next((c for c in CHANGES if c['kind']==k and all(c.get(n)==v for n,v in kw.items())),None)
def wants(k):return any(c['kind']==k for c in CHANGES)
def ret(value):
    # At function ENTRY before prologue. Emulate cdecl ret without running it.
    sp=reg('esp');pc=u32(sp)
    gdb.execute('set $eax = '+str(value),to_string=True)
    gdb.execute('set $esp = '+str(sp+4),to_string=True)
    gdb.execute('set $eip = '+str(pc),to_string=True)
class Finish(gdb.FinishBreakpoint):
    def __init__(self,fn):super().__init__(gdb.newest_frame(),internal=True);self.fn=fn
    def stop(self):
        try:self.fn()
        except Exception as e:R['errors'].append(str(e))
        return False
class Hook(gdb.Breakpoint):
    def __init__(self,n,fn,address=None):
        super().__init__('*'+str(address or A[n]),internal=True);self.fn=fn;self.hook_name=n;hook_names.append(n)
    def stop(self):
        try:
            if active():
                count=R['hook_counts'].get(self.hook_name,0)+1;R['hook_counts'][self.hook_name]=count
                cap=C.get('hook_cap')
                if cap and count>cap:
                    self.enabled=False;R['truncated']=True
                    R['skipped_hooks'].append({'hook':self.hook_name,'observed_calls':cap,'skipped_calls_at_least':1,
                                               'remaining_calls':'unknown (breakpoint disabled)','reason':'discovery hook cap reached'})
                else:self.fn()
        except Exception as e:R['errors'].append(str(e))
        return False

def hook(n,fn,address=None):
    # A cell whose cc1 lacks a hooked function (e.g. reload_cse_* before 2.7.2-cdk/2.8)
    # simply has no such sites: record it, never guess an address.
    if address is None and n not in A:
        R.setdefault('missing_hooks',[]).append(n);return None
    return Hook(n,fn,address)

def initialize():
    global rtx_names,formats,modes
    if rtx_names:return
    rtx_names=[cstr(u32(A['rtx_name']+i*4),64) for i in range(SZ['rtx_name']//4)]
    formats=[cstr(u32(A['rtx_format']+i*4),64) for i in range(SZ['rtx_format']//4)]
    modes=[cstr(u32(A['mode_name']+i*4),64) for i in range(SZ['mode_name']//4)]
class Init(gdb.Breakpoint):
    def stop(self):
        global ACTIVE
        try:
            initialize()
            ACTIVE=bool(ptr('current_function_name')) and cstr(ptr('current_function_name'))==C['function']
        except Exception as e:R['errors'].append('RTX init: '+str(e))
        return False
Init('*'+str(A['rest_of_compilation']),internal=True)

def sched_start():
    mem_insns.clear()
    head,tail=arg(0),arg(1);ph=phase();chain=[];p=head;seen=set()
    # Collect original MEM pointers BEFORE dependency analysis.
    while p and p not in seen:
        seen.add(p);chain.append(p)
        if name(p) in ('insn','jump_insn','call_insn'):
            for m in walk(field(p,3)):
                if name(m)=='mem':mem_insns.setdefault(m,set()).add(uid(p))
        if p==tail:break
        p=field(p,2)
    if p!=tail:raise ValueError('scheduler chain has no selected tail')
    if 'sched' not in F and not wants('sched-luid'):return
    def after():
        lp=ptr('insn_luid')
        for p in chain:
            u=uid(p);v=i32(lp+4*u)
            if 'sched' in F:record('sched-luid',uid=u,phase=ph,value=v)
            m=matches('sched-luid',uid=u,phase=ph)
            if m:put(lp+4*u,m['value']);mutation('sched-luid',v,m['value'],uid=u,phase=ph)
    Finish(after)
def adjust():
    insn=arg(0);u=uid(insn);ph=phase();p=ptr('insn_priority')+4*u;before=i32(p)
    # Trials record nothing: only a matching priority or any birth change needs the return.
    if 'sched' not in F and not matches('sched-priority',uid=u,phase=ph) and not wants('sched-birth'):return
    sched_context.append(u)
    def after():
        natural=i32(p)
        if 'sched' in F:record('sched-priority',uid=u,phase=ph,before=before,value=natural,pattern=brief(field(insn,3)))
        m=matches('sched-priority',uid=u,phase=ph)
        if m:put(p,m['value']);mutation('sched-priority',natural,m['value'],uid=u,phase=ph)
        sched_context.pop()
    Finish(after)
def birth():
    if not sched_context:return
    u=sched_context[-1];ph=phase()
    if 'sched' not in F and not matches('sched-birth',uid=u,phase=ph):return
    def after():
        before=reg('eax')
        if 'sched' in F:record('sched-birth',uid=u,phase=ph,value=before)
        m=matches('sched-birth',uid=u,phase=ph)
        if m and before!=m['value']:
            gdb.execute('set $eax = '+str(m['value']),to_string=True)
            mutation('sched-birth',before,m['value'],uid=u,phase=ph)
    Finish(after)
def combine():
    ps=[arg(i) for i in range(3)];us=[uid(p) for p in ps]
    pats=[brief(field(p,3)) if p and name(p) in ('insn','jump_insn','call_insn') else name(p) for p in ps]
    if matches('combine-veto',uids=us):
        mutation('combine-veto','attempt','veto',uids=us);ret(0);return
    if 'combine' not in F and not wants('combine-crosses'):return
    combine_context.append(us)
    def after():
        if 'combine' in F:record('combine-veto',uids=us,success=bool(reg('eax')),patterns=pats)
        combine_context.pop()
    Finish(after)
def crosses():
    if not combine_context:return
    us=combine_context[-1]
    if 'combine' not in F and not matches('combine-crosses',uids=us):return
    def after():
        before=reg('eax')
        if 'combine' in F:record('combine-crosses',uids=us,value=before)
        if matches('combine-crosses',uids=us) and before==0:
            gdb.execute('set $eax = 1',to_string=True);mutation('combine-crosses',0,1,uids=us)
    Finish(after)
def cse():
    u=uid(arg(0));cse_context.append(u)
    Finish(lambda:cse_context.pop())
def copy_swap():
    u=uid(u32(reg('ebp')+8))
    if 'cse' in F:record('cse-copy-swap',uid=u)
    if matches('cse-copy-swap',uid=u):
        # Four cdecl arguments are currently pushed. Skip the complete atomic
        # rewrite AND associated REG_EQUIV/WAS_0 note edits; preserve all else.
        gdb.execute('set $esp = '+str(reg('esp')+16),to_string=True)
        gdb.execute('set $eip = '+str(A['copy_swap_end']),to_string=True)
        mutation('cse-copy-swap','allowed','veto',uid=u)
def validate_sub():
    caller=u32(reg('esp'))
    if not A['cse_insn']<=caller<A['cse_insn']+SZ['cse_insn']:return
    frame=gdb.newest_frame().older()
    u=uid(u32((int(frame.read_register('ebp'))&0xffffffff)+8))
    # The copy swap is atomic and has its own selector, never veto a fragment.
    if A.get('copy_swap_site',0)<=caller<=A.get('copy_swap_end',0):return
    key=('cse',u);oc=occurrences.get(key,0);occurrences[key]=oc+1
    before=u32(arg(1));after=arg(2)
    if 'cse' in F and before!=after:record('cse-substitution',uid=u,occurrence=oc,target_uid=uid(arg(0)),from_value=brief(before),to_value=brief(after))
    if matches('cse-substitution',uid=u,occurrence=oc):mutation('cse-substitution','validate','veto',uid=u,occurrence=oc);ret(0)
def dependence():
    m1,m2=arg(0),arg(1);us1=mem_insns.get(m1,set());us2=mem_insns.get(m2,set());ph=phase()
    if len(us1)!=1 or len(us2)!=1:return
    us=[next(iter(us1)),next(iter(us2))]
    if 'alias' not in F and not matches('alias',uids=us,phase=ph):return
    def after():
        before=reg('eax')
        if 'alias' in F:record('alias',uids=us,phase=ph,value=before,memory=[brief(m1),brief(m2)])
        m=matches('alias',uids=us,phase=ph)
        if m and before!=m['value']:
            gdb.execute('set $eax = '+str(m['value']),to_string=True);mutation('alias',before,m['value'],uids=us,phase=ph)
    Finish(after)
def hoist():
    p=arg(0);seen=set()
    while p and p not in seen:
        seen.add(p);insn=u32(p);u=uid(insn);flags=u32(p+28)
        if 'loop' in F:record('loop-hoist',uid=u,pseudo=i32(p+20),done=bool(flags&8),pattern=brief(field(insn,3)))
        if matches('loop-hoist',uid=u) and not flags&8:
            # cdk i386 struct movable: done bit is byte28 bit3, next=byte44.
            put(p+28,flags|8);mutation('loop-hoist',False,True,uid=u)
        p=u32(p+44)
def biv():
    dest=arg(2);insn=arg(3);u=uid(insn);p=i32(dest+4) if name(dest)=='reg' else None
    if 'loop' in F:record('loop-biv',uid=u,pseudo=p)
    if matches('loop-biv',uid=u,pseudo=p):mutation('loop-biv','recognize','veto',uid=u,pseudo=p);ret(0)
def dead():
    # insn_dead_p(x,needed,strict_low): no UID argument. Associate pattern with
    # the current RTL chain; do not guess UIDs from pointer values.
    x=arg(0)
    # Actual signature is (x,needed,call_ok). Find pattern's unique UID using
    # get_insns' stored global first_insn (not available): maintain from flow
    # mark_set_regs/mark_used_regs and use a host supplied pre-flow pattern map.
    u=pattern_uids.get(x)
    if u is None:return
    if 'dead' not in F and not matches('keep-dead',uid=u):return
    def after():
        before=reg('eax')
        if 'dead' in F and before:record('keep-dead',uid=u)
        if matches('keep-dead',uid=u) and before:
            gdb.execute('set $eax = 0',to_string=True);mutation('keep-dead',before,0,uid=u)
    Finish(after)

def deleted():
    insn=arg(0)
    if name(insn)!='insn' or name(field(insn,3))!='set':return
    if name(field(field(insn,3),0))!='reg':return
    caller=gdb.newest_frame().older().name()
    u=uid(insn)
    if caller=='try_merge_delay_insns':
        if 'reorg' in F:record('reorg-delete',uid=u,value=True,caller=caller,pattern=brief(field(insn,3)))
        m=matches('reorg-delete',uid=u)
        if m is not None and m['value']==0:
            mutation('reorg-delete',True,False,uid=u);ret(field(insn,2));return
    if 'dead' in F:record('deleted-set',uid=uid(insn),caller=caller,pattern=brief(field(insn,3)))
    if caller not in ('delete_dead_from_cse','delete_dead_insn','flow_delete_insn','delete_computation','delete_trivially_dead_insns','jump_optimize'):return
    if 'dead' in F:record('keep-dead',uid=u,caller=caller,pattern=brief(field(insn,3)))
    if matches('keep-dead',uid=u):
        mutation('keep-dead','delete','keep',uid=u,caller=caller);ret(field(insn,2))

pattern_uids={}
def flow_start():
    p=arg(0);seen=set()
    while p and p not in seen:
        seen.add(p)
        if name(p) in ('insn','jump_insn','call_insn'):pattern_uids[field(p,3)]=uid(p)
        p=field(p,2)
def equiv():
    u=uid(arg(1));key=('equiv',u);oc=occurrences.get(key,0);occurrences[key]=oc+1
    if 'reload' not in F and not matches('reload-equiv',uid=u,occurrence=oc) and not matches('reload-reuse',uid=u,occurrence=oc):return
    def after():
        got=reg('eax');p=i32(got+4) if got and name(got)=='reg' else None
        if 'reload' in F and got:record('reload-equiv',uid=u,occurrence=oc,register=p)
        if 'reload' in F:record('reload-reuse',uid=u,occurrence=oc,value=bool(got),register=p)
        if matches('reload-equiv',uid=u,occurrence=oc) and got:
            gdb.execute('set $eax = 0',to_string=True);mutation('reload-equiv',p,None,uid=u,occurrence=oc)
        m=matches('reload-reuse',uid=u,occurrence=oc)
        if m and bool(got)!=bool(m['value']) and m['value']==0:
            gdb.execute('set $eax = 0',to_string=True);mutation('reload-reuse',True,False,uid=u,occurrence=oc)
    Finish(after)
def reload_simplify():
    u=uid(arg(1))
    if 'reload' in F:record('reload-cse',uid=u,pattern=brief(arg(0)))
    if matches('reload-cse',uid=u):mutation('reload-cse','simplify','veto',uid=u);ret(0)
def reload_noop():
    u=uid(arg(1))
    if 'reload' in F or matches('reload-cse',uid=u) or matches('keep-dead',uid=u) or matches('reload-noop',uid=u):
        def after():
            before=reg('eax')
            if 'reload' in F:record('reload-noop',uid=u,value=bool(before),pattern=brief(arg(0)))
            m=matches('reload-noop',uid=u)
            if m is not None and bool(before)!=bool(m['value']):
                gdb.execute('set $eax = '+str(m['value']),to_string=True);mutation('reload-noop',bool(before),bool(m['value']),uid=u)
            elif before and (matches('reload-cse',uid=u) or matches('keep-dead',uid=u)):
                gdb.execute('set $eax = 0',to_string=True);mutation('reload-cse',before,0,uid=u)
        Finish(after)

# reorg.c: invert the target's delay-slot eligibility result at an executed
# (delay insn, candidate insn) site, or skip one executed merge scan.  The
# former supports both force and forbid; the latter is the safe counterfactual
# for try_merge_delay_insns, whose destructive work cannot be reconstructed.
def reorg_eligible():
    d,c=arg(0),arg(2);du,cu=uid(d),uid(c)
    if not d or not c:
        if 'reorg' in F:R['skipped_sites'].append({'family':'reorg','hook':'eligible_for_delay','uid':du,'candidate_uid':cu,
                                                   'reason':'null delay or candidate has no selectable RTL site'})
        return
    if 'reorg' not in F and not matches('reorg-fill',uid=du,candidate_uid=cu):return
    def after():
        before=bool(reg('eax'))
        if 'reorg' in F:record('reorg-fill',uid=du,candidate_uid=cu,value=before,
                               delay=brief(field(d,3)),candidate=brief(field(c,3)))
        m=matches('reorg-fill',uid=du,candidate_uid=cu)
        if m is not None and before!=bool(m['value']):
            gdb.execute('set $eax = '+str(m['value']),to_string=True)
            mutation('reorg-fill',before,bool(m['value']),uid=du,candidate_uid=cu)
    Finish(after)
def reorg_merge():
    d,t=arg(0),arg(1);du,tu=uid(d),uid(t)
    if not d or not t:
        if 'reorg' in F:R['skipped_sites'].append({'family':'reorg','hook':'try_merge_delay_insns','uid':du,'thread_uid':tu,
                                                   'reason':'null delay or thread has no selectable RTL site'})
        return
    if 'reorg' in F:record('reorg-merge',uid=du,thread_uid=tu,value=True,
                           delay=brief(field(d,3)),thread=brief(field(t,3)))
    m=matches('reorg-merge',uid=du,thread_uid=tu)
    if m is not None and m['value']==0:
        mutation('reorg-merge',True,False,uid=du,thread_uid=tu);ret(0)

# jump.c: find_cross_jump writes its selected tail heads through arguments 3
# and 4.  A veto clears them.  A force is allowed only when a simple backward
# scan finds `minimum` exactly equal RTL patterns; otherwise it fails closed.
def prev_real(x):
    x=field(x,1) if x else 0;seen=set()
    while x and x not in seen and name(x) in ('note','code_label'):
        seen.add(x);x=field(x,1)
    return x
def force_cross_tails(e1,e2,minimum):
    a,b=e1,e2;last=None
    for _ in range(max(1,minimum)):
        a,b=prev_real(a),prev_real(b)
        if not a or not b or name(a)!=name(b) or name(a) not in ('insn','jump_insn','call_insn'):return None
        if brief(field(a,3))!=brief(field(b,3)):return None
        last=(a,b)
    return last
def jump_cross():
    e1,e2,minimum,p1,p2=arg(0),arg(1),i32(reg('esp')+12),arg(3),arg(4)
    ends=[uid(e1),uid(e2)];forced=force_cross_tails(e1,e2,minimum)
    if 'jump' not in F and not matches('jump-cross',uids=ends):return
    def after():
        a,b=u32(p1),u32(p2);before=bool(a and b)
        tails=[uid(a),uid(b)] if before else ([uid(forced[0]),uid(forced[1])] if forced else [])
        if 'jump' in F:record('jump-cross',uids=ends,value=before,forceable=bool(forced),tails=tails,minimum=minimum)
        m=matches('jump-cross',uids=ends)
        if m is None or before==bool(m['value']):return
        if m['value']==0:
            put(p1,0);put(p2,0);mutation('jump-cross',True,False,uids=ends)
        elif forced:
            put(p1,forced[0]);put(p2,forced[1]);mutation('jump-cross',False,True,uids=ends)
    Finish(after)

# function.c: select an executed stack-slot allocation by occurrence and set
# the pre-allocation frame cursor.  The normal allocator still performs all
# alignment, size, virtual-register and list bookkeeping.
def frame_slot():
    key=('frame',);oc=occurrences.get(key,0);occurrences[key]=oc+1
    mode,size,align=arg(0),i32(reg('esp')+8),i32(reg('esp')+12);before=i32(A['frame_offset'])
    m=matches('frame-offset',occurrence=oc)
    if m is not None and before!=m['value']:
        put(A['frame_offset'],m['value']);mutation('frame-offset',before,m['value'],occurrence=oc)
    def after():
        if 'frame' in F:record('frame-offset',occurrence=oc,mode=mode,size=size,align=align,
                               before=before,after=i32(A['frame_offset']),result=brief(reg('eax')) if rtx_names else None)
    Finish(after)

# cse.c: move an observed member of an equivalence chain to its head while
# maintaining both links and qty_first/qty_last.  canon_reg then consumes the
# selected head through the compiler's ordinary path.
def eqv_chain(q):
    first=i32(ptr('qty_first_reg')+4*q);out=[];seen=set();p=first
    while p>=0 and p not in seen and len(out)<4096:
        seen.add(p);out.append(p);p=i32(ptr('reg_next_eqv')+4*p)
    return out
def eqv_make_head(q,target):
    chain=eqv_chain(q)
    if target not in chain:raise ValueError('cse head target is not in observed equivalence chain')
    first=chain[0]
    if target==first:return False
    prev=i32(ptr('reg_prev_eqv')+4*target);nxt=i32(ptr('reg_next_eqv')+4*target)
    put(ptr('reg_next_eqv')+4*prev,nxt)
    if nxt>=0:put(ptr('reg_prev_eqv')+4*nxt,prev)
    else:put(ptr('qty_last_reg')+4*q,prev)
    put(ptr('reg_prev_eqv')+4*target,-1);put(ptr('reg_next_eqv')+4*target,first)
    put(ptr('reg_prev_eqv')+4*first,target);put(ptr('qty_first_reg')+4*q,target)
    return True
def cse_eqv():
    new,old=i32(reg('esp')+4),i32(reg('esp')+8)
    key=('cse-eqv',new,old);oc=occurrences.get(key,0);occurrences[key]=oc+1
    def after():
        q=i32(ptr('reg_qty')+4*old);chain=eqv_chain(q);head=chain[0] if chain else -1
        if 'cse' in F:record('cse-eqv-head',new=new,old=old,occurrence=oc,head=head,chain=chain[:32])
        m=matches('cse-eqv-head',new=new,old=old,occurrence=oc)
        if m is not None and m['head']!=head and eqv_make_head(q,m['head']):
            mutation('cse-eqv-head',head,m['head'],new=new,old=old,occurrence=oc,head=m['head'])
    Finish(after)
# Per-pseudo flow facts. 2.6.3/2.7.2(-cdk): parallel arrays (deaths are shorts).
# 2.8.x: reg_n_info, an array of struct reg_info_def (host-supplied offsets).
RI=C.get('reginfo')
FIELD_ARRAY={'refs':'reg_n_refs','live':'reg_live_length','block':'reg_basic_block','deaths':'reg_n_deaths'}
def raddr(f,p):
    if RI:return ptr('reg_n_info')+RI['stride']*p+RI[f]
    return ptr(FIELD_ARRAY[f])+(2 if f=='deaths' else 4)*p
def rget(f,p):
    if f=='deaths' and not RI:return struct.unpack('<h',mem(raddr(f,p),2))[0]
    return i32(raddr(f,p))
def rput(f,p,v):
    if f=='deaths':raise ValueError('deaths are never written')
    INF.write_memory(raddr(f,p),struct.pack('<i',v))
def all_refs(count):
    if RI:
        b=ptr('reg_n_info');st=RI['stride'];raw=mem(b,st*count)
        return [struct.unpack_from('<i',raw,st*p+RI['refs'])[0] for p in range(count)]
    return list(struct.unpack('<'+'i'*count,mem(ptr('reg_n_refs'),4*count)))
def ref_mark(n):
    global ref_depth
    # Only outermost call owns the aggregate delta; recursive visits are not
    # counted twice. mark_set_regs insn arg3; mark_used_regs final arg3/insn arg4.
    insn=arg(3 if n=='mark_set_regs' else 4)
    final=bool(insn) if n=='mark_set_regs' else bool(arg(3))
    if not final or ref_depth:return
    ref_depth+=1;count=i32(A['max_regno'])
    before=all_refs(count);u=uid(insn)
    def after():
        global ref_depth
        after=all_refs(count)
        for p,(v,w) in enumerate(zip(before,after)):
            if v!=w:R['refs'].append(dict(uid=u,pseudo=p,weight=w-v,role='set' if n=='mark_set_regs' else 'use'))
        ref_depth-=1
    Finish(after)
def stats(stage):
    count=i32(A['max_regno'])
    R['stats'].append({'stage':stage,'pseudos':[{'pseudo':p,'refs':rget('refs',p),'life':rget('live',p),'block':rget('block',p),'deaths':rget('deaths',p)} for p in range(C.get('first',76),count) if rget('refs',p)>0]})

# Allocator inputs inside a composite: the same writes alloc_oracle_gdb makes
# (reg arrays after update_equiv_regs; qty arrays at the block's priority sort),
# with the host-resolved alloc_oracle symbol table (nearest-anchor statics).
AA=C.get('alloc_addresses') or {}; alloc_done=set(); alloc_block=[None]
def aptr(n):return u32(AA[n])
def aget(n,i):return i32(aptr(n)+4*i)
def aput(n,i,v):INF.write_memory(aptr(n)+4*i,struct.pack('<i',v))
def alloc_mark(idx,field,index,before,after,**kw):
    R['mutations'].append(dict(kind='alloc',field=field,index=index,before=before,after=after,**kw));R['applied']=True
    if idx not in R['applied_changes']:R['applied_changes'].append(idx)
    alloc_done.add(idx)
def alloc_reg():
    for idx,c in enumerate(CHANGES):
        if c['kind']!='alloc' or idx in alloc_done:continue
        k=c['input']['kind'];P=c['pseudo']
        if k not in ('refs','refs-add','live','global','local'):continue
        if P<C['first'] or P>=i32(AA['max_regno']) or rget('refs',P)<=0:
            R['errors'].append('alloc target pseudo %d absent/dead at allocator entry'%P);alloc_done.add(idx);continue
        if k in ('refs','refs-add'):field='refs';before=rget(field,P);after=before+c['input']['value'] if k=='refs-add' else c['input']['value']
        elif k=='live':field='live';before=rget(field,P);after=c['input']['value']
        else:
            field='block';before=rget(field,P);after=-2 if k=='global' else c['input']['value']
            if k=='local' and rget('deaths',P)!=1:
                R['errors'].append('force-local needs one death');alloc_done.add(idx);continue
        rput(field,P,after)
        if before!=after:alloc_mark(idx,FIELD_ARRAY[field],P,before,after,pseudo=P)
        else:alloc_done.add(idx)
def alloc_qty_of(P):
    if alloc_block[0]!=rget('block',P):return None
    q=aget('reg_qty',P)
    return q if 0<=q<i32(AA['next_qty']) else None
def alloc_qty():
    for idx,c in enumerate(CHANGES):
        if c['kind']!='alloc' or idx in alloc_done or c['input']['kind'] not in ('qty-refs','qty-life'):continue
        q=alloc_qty_of(c['pseudo'])
        if q is None:continue
        field='qty_n_refs' if c['input']['kind']=='qty-refs' else 'qty_death'
        before=aget(field,q);after=c['input']['value'] if field=='qty_n_refs' else aget('qty_birth',q)+c['input']['value']
        aput(field,q,after);alloc_mark(idx,field,q,before,after,pseudo=c['pseudo'],block=alloc_block[0])
def alloc_sort():
    cmp=arg(3)
    if cmp not in (AA['qty_sugg_compare_1'],AA['qty_compare_1']):return
    alloc_qty()
    if cmp!=AA['qty_compare_1']:return
    pending=[(idx,c) for idx,c in enumerate(CHANGES) if c['kind']=='alloc' and idx not in alloc_done and c['input']['kind']=='qty-rank']
    pending=[(idx,c,alloc_qty_of(c['pseudo'])) for idx,c in pending]
    pending=[x for x in pending if x[2] is not None]
    if not pending:return
    addr=arg(0);count=arg(1)
    def after():
        order=list(struct.unpack('<'+'i'*count,mem(addr,4*count)))
        for idx,c,q in pending:
            rank=c['input']['value']
            if not 0<=rank<count:R['errors'].append('qty rank outside this block');alloc_done.add(idx);continue
            before=order[:];order.remove(q);order.insert(rank,q)
            INF.write_memory(addr,struct.pack('<'+'i'*count,*order))
            if before!=order:alloc_mark(idx,'qty_order',q,before,order,pseudo=c['pseudo'])
            else:alloc_done.add(idx)
    Finish(after)
if any(c['kind']=='alloc' for c in CHANGES):
    if not AA:R['errors'].append('alloc change without allocator symbols')
    else:
        hook('update_equiv_regs',lambda:Finish(alloc_reg),address=AA['update_equiv_regs'])
        hook('block_alloc',lambda:alloc_block.__setitem__(0,arg(0)),address=AA['block_alloc'])
        if any(c['kind']=='alloc' and c['input']['kind'].startswith('qty-') for c in CHANGES):
            hook('qty_sugg_compare',alloc_qty,address=AA['qty_sugg_compare']);hook('qty_compare',alloc_qty,address=AA['qty_compare'])
            hook('qsort',alloc_sort,address=AA['qsort'])

# global.c: an allocno's hard-register conflict set (HARD_REG_SET = 3 x u32 for
# 67..76 hard regs on the i386 host, all cells). Set at prune_preferences entry: conflicts are
# complete, preferences not yet pruned, nothing allocated. Colours are read at
# reload entry, while global_alloc's alloca'd reg_allocno is still live.
HRS=12
def global_avoid():
    for c in CHANGES:
        if c['kind']!='global-avoid':continue
        P,H=c['pseudo'],c['hardreg']
        if not 0<=P<i32(A['max_regno']):R['errors'].append('global-avoid pseudo out of range');continue
        a=i32(ptr('reg_allocno')+4*P)
        if not 0<=a<i32(A['max_allocno']):R['errors'].append('pseudo %d has no global allocno'%P);continue
        w=ptr('hard_reg_conflicts')+HRS*a+4*(H//32);old=u32(w);new=old|(1<<(H%32))
        if new!=old:INF.write_memory(w,struct.pack('<I',new));mutation('global-avoid',False,True,pseudo=P,hardreg=H)
def global_colours():
    # Every allocated pseudo's colour (local ones carry allocno -1).
    n=i32(A['max_regno']);ren=ptr('reg_renumber');al=ptr('reg_allocno');na=i32(A['max_allocno'])
    for p in range(C.get('first',76),n):
        a=i32(al+4*p);h=struct.unpack('<h',mem(ren+2*p,2))[0]
        if 0<=a<na or h>=0:record('global-colour',pseudo=p,allocno=a if 0<=a<na else -1,hardreg=h)

# All hooks necessary for the selected mutation are enabled even in narrow discovery.
KINDS_ON={c['kind'] for c in CHANGES}
needs=lambda f:f in F or any(k==f or k.startswith(f+'-') or (f=='dead' and k=='keep-dead') for k in KINDS_ON)
if needs('sched') or needs('alias'):
    hook('sched_analyze',sched_start)
if needs('sched'):
    hook('adjust_priority',adjust);hook('birthing_insn_p',birth)
if needs('combine'):
    hook('try_combine',combine);hook('use_crosses_set_p',crosses)
if needs('cse'):
    hook('validate_change',validate_sub)
    hook('make_regs_eqv',cse_eqv)
    if 'copy_swap_site' in A:hook('copy_swap_site',copy_swap)
    elif 'cse-copy-swap' in KINDS_ON:R['errors'].append('copy-swap site layout not recognized')
if needs('alias'):hook('true_dependence',dependence)
if needs('loop'):hook('move_movables',hoist);hook('basic_induction_var',biv)
if needs('dead'):
    if not needs('reload'):hook('reload_cse_noop_set_p',reload_noop)
    # flow_analysis's first argument is the RTL chain; map UIDs before deletion.
    hook('flow_analysis',flow_start);hook('insn_dead_p',dead);hook('delete_insn',deleted)
if needs('reload'):
    hook('find_equiv_reg',equiv);hook('reload_cse_simplify_set',reload_simplify);hook('reload_cse_noop_set_p',reload_noop)
if needs('reorg'):
    hook('eligible_for_delay',reorg_eligible);hook('try_merge_delay_insns',reorg_merge)
    if not needs('dead'):hook('delete_insn',deleted)
if needs('jump'):
    hook('find_cross_jump',jump_cross)
if needs('frame'):
    hook('assign_stack_local',frame_slot)
if needs('global'):
    hook('prune_preferences',global_avoid);hook('reload',global_colours)
if 'refs' in F:
    hook('mark_set_regs',lambda:ref_mark('mark_set_regs'));hook('mark_used_regs',lambda:ref_mark('mark_used_regs'))
    hook('local_alloc',lambda:stats('before-local'));hook('global_alloc',lambda:stats('before-global'))
gdb.execute('run')
try:R['inferior_exit']=int(gdb.parse_and_eval('$_exitcode'))
except Exception:R['inferior_exit']=None
R['hooks']=hook_names
with open('pass_trace.json','w') as f:json.dump(R,f,indent=2)
