"""Read actual INSN_LUID values just after sched_analyze, without interventions."""
import gdb,json,struct
with open('luid_cfg.json') as f: C=json.load(f)
A=C['addresses']; INF=gdb.selected_inferior(); out={'blocks':[],'declarations':[],'errors':[]}
def mem(a,n): return bytes(INF.read_memory(a,n))
def u32(a): return struct.unpack('<I',mem(a,4))[0]
def i32(a): return struct.unpack('<i',mem(a,4))[0]
def ptr(n): return u32(A[n])
def arg(i): return u32(int(gdb.parse_and_eval('$esp'))+4*(i+1))
def active():
    p=ptr('current_function_name')
    return p and mem(p,160).split(b'\0')[0].decode(errors='replace')==C['function']
# i386 tree.h layout, verified against expand_decl disassembly in cdk/2.8.x:
# common=12 bytes; decl.name=36, arguments=44, rtl=72; identifier.pointer=16.
def declaration(node):
    if not node: return
    code=mem(node+8,1)[0]
    table=ptr('tree_code_name')
    kind=mem(u32(table+4*code),40).split(b'\0')[0].decode(errors='replace')
    if kind not in ('var_decl','parm_decl'): return
    ident=u32(node+36);rtl=u32(node+72)
    if not ident or not rtl: return
    length=i32(ident+12)
    if not 0<length<4096: raise ValueError('invalid declaration identifier length')
    name=mem(u32(ident+16),length).decode(errors='replace')
    def rcode(x):
        n=struct.unpack('<H',mem(x,2))[0]
        return mem(u32(A['rtx_name']+4*n),40).split(b'\0')[0].decode(errors='replace')
    rkind=rcode(rtl)
    if rkind=='subreg': rtl=u32(rtl+4);rkind=rcode(rtl)
    out['declarations'].append({'name':name,'register':i32(rtl+4) if rkind=='reg' else None,
                                'rtl_kind':rkind,'line':i32(node+16),'decl_address':node,'decl_uid':u32(node+20)})
class DeclEnd(gdb.FinishBreakpoint):
    def __init__(self,node=None,params=False):
        super().__init__(gdb.newest_frame(),internal=True);self.node=node;self.params=params
    def stop(self):
        try:
            if self.params:
                node=u32(ptr('current_function_decl')+44);seen=set()
                while node and node not in seen:
                    seen.add(node);declaration(node);node=u32(node)
            else: declaration(self.node)
        except Exception as e:out['errors'].append('DECL_RTL: '+str(e))
        return False
class DeclStart(gdb.Breakpoint):
    def __init__(self,name):super().__init__('*'+str(A[name]),internal=True);self.name=name
    def stop(self):
        try:
            if active():DeclEnd(params=True) if self.name=='assign_parms' else DeclEnd(arg(0))
        except Exception as e:out['errors'].append('DECL_RTL: '+str(e))
        return False
for name in ('expand_decl','make_decl_rtl','assign_parms'):DeclStart(name)
class End(gdb.FinishBreakpoint):
    def __init__(self,head,tail,phase): super().__init__(gdb.newest_frame(),internal=True);self.head=head;self.tail=tail;self.phase=phase
    def stop(self):
        try:
            x=self.head; seen=set(); rows=[]; lp=ptr('insn_luid')
            while x and x not in seen:
                seen.add(x);uid=i32(x+4);rows.append({'uid':uid,'luid':i32(lp+4*uid)})
                if x==self.tail: break
                x=u32(x+12)
            if x!=self.tail: raise ValueError('scheduler chain did not reach tail')
            out['blocks'].append({'phase':self.phase,'from':i32(self.head+4),'to':i32(self.tail+4),'insns':rows})
        except Exception as e: out['errors'].append(str(e))
        return False
class Start(gdb.Breakpoint):
    def stop(self):
        try:
            if active(): End(arg(0),arg(1),'sched2' if i32(A['reload_completed']) else 'sched')
        except Exception as e: out['errors'].append(str(e))
        return False
Start('*'+str(A['sched_analyze']),internal=True)
gdb.execute('run')
try: out['inferior_exit']=int(gdb.parse_and_eval('$_exitcode'))
except Exception: out['inferior_exit']=None
with open('luid_trace.json','w') as f: json.dump(out,f,indent=2)
