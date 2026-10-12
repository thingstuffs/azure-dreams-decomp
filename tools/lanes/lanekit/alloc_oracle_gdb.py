"""GDB-only half of alloc_oracle; symbol addresses/ABI are supplied by the host."""
import gdb, json, struct
with open('oracle_cfg.json') as f: C=json.load(f)
A=C['addresses']; P=C['pseudo']; change=C.get('change')
INF=gdb.selected_inferior(); result={'events':[], 'stages':[], 'errors':[], 'applied':False}; current_block=None

def mem(a,n): return bytes(INF.read_memory(a,n))
def i32(a): return struct.unpack('<i',mem(a,4))[0]
def ptr(n): return struct.unpack('<I',mem(A[n],4))[0]
def scalar(n): return i32(A[n])
def slot(n,i): return ptr(n)+4*i
def get(n,i): return i32(slot(n,i))
def put(n,i,v): INF.write_memory(slot(n,i),struct.pack('<i',v))
def arg(i): return i32(int(gdb.parse_and_eval('$esp'))+4*(i+1))
def fname(): return mem(ptr('current_function_name'),160).split(b'\0')[0].decode(errors='replace')
def active(): return bool(ptr('current_function_name')) and fname()==C['function']
def renumbers():
    return list(struct.unpack('<'+'h'*scalar('max_regno'),mem(ptr('reg_renumber'),2*scalar('max_regno'))))
def event(field,index,before,after,stage,**kw):
    result['events'].append(dict(field=field,index=index,before=before,after=after,stage=stage,**kw)); result['applied']=True

def patch_reg():
    if not active() or not change or result['applied']: return
    kind=change['kind']
    if kind not in ('refs','refs-add','live','global','local'): return
    if P<C['first'] or P>=scalar('max_regno') or get('reg_n_refs',P)<=0: raise ValueError('target pseudo is absent/dead at allocator entry')
    if kind in ('refs','refs-add'): field='reg_n_refs'; before=get(field,P); after=before+change['value'] if kind=='refs-add' else change['value']
    elif kind=='live': field='reg_live_length'; before=get(field,P); after=change['value']
    else:
        field='reg_basic_block'; before=get(field,P); after=-2 if kind=='global' else change['value']
        if kind=='local' and struct.unpack('<h',mem(ptr('reg_n_deaths')+2*P,2))[0]!=1: raise ValueError('force-local needs one death; changing deaths would be a second input')
    put(field,P,after); event(field,P,before,after,'after update_equiv_regs')

def qty_target():
    if not active() or current_block!=get('reg_basic_block',P): return None
    q=get('reg_qty',P)
    return q if 0<=q<scalar('next_qty') else None

def patch_qty():
    if not change or result['applied'] or change['kind'] not in ('qty-refs','qty-life'): return
    q=qty_target()
    if q is None: return
    field='qty_n_refs' if change['kind']=='qty-refs' else 'qty_death'
    before=get(field,q); after=change['value'] if field=='qty_n_refs' else get('qty_birth',q)+change['value']
    put(field,q,after); event(field,q,before,after,'before local suggestion/priority sort',block=current_block,pseudo=P,
                              birth=get('qty_birth',q),life=get('qty_death',q)-get('qty_birth',q),refs=get('qty_n_refs',q))

class Finish(gdb.FinishBreakpoint):
    def __init__(self,fn): super().__init__(gdb.newest_frame(),internal=True); self.fn=fn
    def stop(self):
        try: self.fn()
        except Exception as e: result['errors'].append(str(e))
        return False

class Hook(gdb.Breakpoint):
    def __init__(self,name,fn): super().__init__('*'+str(A[name]),internal=True); self.fn=fn
    def stop(self):
        try:
            if active(): self.fn()
        except Exception as e: result['errors'].append(str(e))
        return False

def begin_block():
    global current_block
    current_block=arg(0)

def snapshot(stage):
    result['stages'].append({'stage':stage,'colours':renumbers(),'pseudo':P,'refs':get('reg_n_refs',P),
                             'live':get('reg_live_length',P),'block':get('reg_basic_block',P)})

def sort_entry():
    cmp=arg(3)
    if cmp not in (A['qty_sugg_compare_1'],A['qty_compare_1']): return
    patch_qty()
    q=qty_target()
    if q is None: return
    addr=arg(0) & 0xffffffff; count=arg(1); block=current_block
    def after():
        order=list(struct.unpack('<'+'i'*count,mem(addr,4*count)))
        if change and change['kind']=='qty-rank' and cmp==A['qty_compare_1'] and not result['applied']:
            rank=change['value']
            if not 0<=rank<count: raise ValueError('qty rank outside this block')
            before=order[:]; order.remove(q); order.insert(rank,q)
            INF.write_memory(addr,struct.pack('<'+'i'*count,*order))
            event('qty_order',q,before,order,'after local priority sort',block=block,pseudo=P)
        result['stages'].append({'stage':'local-priority-order' if cmp==A['qty_compare_1'] else 'local-suggestion-order',
                                 'block':block,'order':order,'qty':q,'refs':get('qty_n_refs',q),
                                 'birth':get('qty_birth',q),'death':get('qty_death',q)})
    Finish(after)

Hook('update_equiv_regs',lambda: Finish(patch_reg))
Hook('block_alloc',begin_block)
Hook('qty_sugg_compare',patch_qty) # 0..3 qtys: GCC's inline sort path (no qsort).
Hook('qty_compare',patch_qty)
Hook('qsort',sort_entry)
Hook('local_alloc',lambda: Finish(lambda: snapshot('after-local')))
Hook('global_alloc',lambda: Finish(lambda: snapshot('after-global')))
gdb.execute('run')
# GDB --batch may return success even when the inferior aborted. Host verifies this.
result['inferior_exit']=None
try: result['inferior_exit']=int(gdb.parse_and_eval('$_exitcode'))
except Exception: pass
with open('oracle_trace.json','w') as f: json.dump(result,f,indent=2)
