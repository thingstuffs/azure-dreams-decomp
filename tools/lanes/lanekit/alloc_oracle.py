#!/usr/bin/env python3
"""ONE allocator-input intervention in the real cc1 under GDB, never a C candidate.

alloc_oracle.py ROW TEXT --pseudo NAME|NUMBER (ONE intervention) [--json FILE] [--keep DIR]
  --refs N / --refs-add N / --live N      pseudo REG_N_REFS / live length
  --force-global / --force-local BLOCK  pseudo reg_basic_block
  --qty-refs N / --qty-life N           local quantity refs / death-birth
  --qty-rank N                         target qty position in priority order (0 first)

Refs/live/block interventions occur after update_equiv_regs and before local allocation.
Qty interventions occur before sorting; qty-life changes death (geometry AND priority).
qty-rank overrides the priority qsort result only; blocks of <=3 quantities fail closed.
Runs baseline + forced compiler, compares both with the calibrated pinned listing,
and reports final pre-reload colours. --retail-set PSEUDO=REG supplies a documented
colour target for compiler-created pseudos. This counterfactual cannot be staged.
Supported: symbol-only i386 cc1 for 2.7.2-cdk, 2.8.0, 2.8.1. Other ABIs fail closed.
"""
from __future__ import annotations
import argparse
import difflib
import hashlib
import json
import re
from pathlib import Path
import shutil
import subprocess
import tempfile
import kitlib
import sncheck

SUPPORTED=('2.7.2-cdk','2.8.0','2.8.1')
REQUIRED=('reg_qty','qty_n_refs','qty_birth','qty_death','next_qty','reg_basic_block','reg_n_refs',
          'reg_live_length','reg_n_deaths','reg_renumber','max_regno','current_function_name',
          'update_equiv_regs','local_alloc','global_alloc','block_alloc','qsort',
          'qty_sugg_compare','qty_compare','qty_sugg_compare_1','qty_compare_1')

def validate_change(change):
    if change is None: return
    kind=change['kind']; n=change.get('value')
    if kind not in ('refs','refs-add','live','global','local','qty-refs','qty-life','qty-rank'):
        raise ValueError('unknown allocator input')
    if kind!='global' and (not isinstance(n,int) or not -(2**31)<=n<2**31): raise ValueError('input must be an i32')
    if kind in ('refs','live','qty-refs','qty-life') and n<=0: raise ValueError('refs/life must be positive')
    if kind in ('local','qty-rank') and n<0: raise ValueError('block/rank must be non-negative')

def resolve_pseudo(text,token,first,observed=None):
    kitlib.add_paths(); import alloc_sim
    dp=alloc_sim.decl_pseudos(text,first)
    if not dp: raise ValueError('oracle needs one function (no module/multi-function inputs)')
    pinned={n for n in re.findall(r'\b(\w+)\s+ASM_REG\(',text)}
    if token in pinned: raise ValueError('named target is pinned to a hard register; erase it before intervening')
    if str(token).isdigit(): p=int(token)
    elif observed is not None:
        if token not in observed or observed[token] is None: raise ValueError('no unambiguous register DECL_RTL for '+str(token))
        p=observed[token]
    elif token in dp['map']: p=dp['map'][token]
    else: raise ValueError('no named pseudo '+str(token)+'; use a numeric compiler-created pseudo')
    if p<first: raise ValueError('intervention target must be a pseudo, not a hard register')
    return p,dp

def observed_names(row,text):
    import value_luid
    observation=value_luid.observe_luids(row,text)
    if observation['errors']: raise RuntimeError('DECL_RTL observer failed: '+'; '.join(observation['errors']))
    mapping,ambiguous=value_luid.declaration_registers(observation)
    # Shadowed declarations require numeric targets; never guess which one.
    return mapping

def symbols(cc1):
    # Static i386 GCC has duplicate file-local reg_qty/qty_first_reg names.
    # Choose the instance nearest local-alloc's UNIQUE qty_n_refs anchor.
    with cc1.open('rb') as f: elf=f.read(20)
    if len(elf)<20 or elf[:4]!=b'\x7fELF' or elf[4]!=1 or elf[5]!=1 or elf[18:20]!=b'\x03\x00':
        raise ValueError('oracle requires a little-endian i386 ELF cc1')
    output=subprocess.run(['nm','-S',str(cc1)],capture_output=True,text=True,check=True).stdout
    found={}
    for line in output.splitlines():
        parts=line.split()
        if len(parts)>=3:
            try: addr=int(parts[0],16)
            except ValueError: continue
            found.setdefault(parts[-1],[]).append(addr)
    missing=set(REQUIRED)-found.keys()
    if missing: raise ValueError('cc1 lacks allocator symbols: '+', '.join(sorted(missing)))
    anchor=found['qty_n_refs'][0]
    return {name:min(found[name],key=lambda x:abs(x-anchor)) for name in REQUIRED}

def trace(row,text,pseudo,change=None,timeout=180,keep=None):
    validate_change(change); kitlib.add_paths(); import alloc_sim
    from common import parse_cfg
    cell,_=parse_cfg(row['cfg'])
    if cell not in SUPPORTED: raise ValueError('unverified allocator ABI for '+cell)
    if kitlib.module_fingerprint(row) is not None: raise ValueError('oracle does not build grouped SLUS modules')
    first=alloc_sim.FIRST[cell]; observed=observed_names(row,text) if not str(pseudo).isdigit() else None
    p,dp=resolve_pseudo(text,pseudo,first,observed)
    with tempfile.TemporaryDirectory(prefix='allocoracle_') as td:
        d=Path(td); cc,flags,cpp=sncheck.preprocess(row,text,d)
        config={'addresses':symbols(cc/'cc1'),'first':first,'pseudo':p,'function':dp['fname'],'change':change}
        (d/'oracle_cfg.json').write_text(json.dumps(config))
        shutil.copy2(Path(__file__).with_name('alloc_oracle_gdb.py'),d/'trace.py')
        (d/'trace.gdb').write_text('set pagination off\nset confirm off\nset debuginfod enabled off\nset startup-with-shell off\nsource trace.py\n')
        cmd=['gdb','--batch','--nx','-x','trace.gdb','--args',str(cc/'cc1'),'in.i','-quiet','-O2',*flags,'-w','-da','-o','out.s']
        run=subprocess.run(cmd,cwd=d,capture_output=True,text=True,timeout=timeout)
        (d/'gdb.log').write_text(run.stdout+run.stderr)
        if not (d/'oracle_trace.json').is_file(): raise RuntimeError('gdb produced no trace: '+(run.stdout+run.stderr)[-2000:])
        r=json.loads((d/'oracle_trace.json').read_text()); r.update(pseudo=p,function=dp['fname'],change=change,
              commands=[cpp,cmd],cc1_sha256=hashlib.sha256((cc/'cc1').read_bytes()).hexdigest())
        if run.returncode or r['inferior_exit']!=0 or not (d/'out.s').is_file(): r['errors'].append('cc1/gdb did not exit successfully')
        if change and not r['applied']: r['errors'].append('intervention never applied (target absent/not eligible or <=3 qty-rank block)')
        if not r['stages']: r['errors'].append('target function never reached allocator hooks')
        r['asm']=(d/'out.s').read_text() if (d/'out.s').exists() else ''
        r['dumps']={f.suffix[1:]:f.read_text(errors='replace') for f in d.iterdir() if f.suffix[1:] in kitlib.PASS_SUFFIX}
        if keep:
            target=Path(keep).resolve()
            if not target.is_relative_to(kitlib.lane_dir()): raise ValueError('--keep must be inside this lane')
            target.mkdir(parents=True,exist_ok=True)
            for f in d.iterdir():
                if f.is_file(): shutil.copy2(f,target/f.name)
        return r

def last_colours(r):
    return next((s['colours'] for s in reversed(r['stages']) if s['stage']=='after-global'),[])

def distance(a,b):
    return sum(max(i2-i1,j2-j1) for tag,i1,i2,j1,j2 in difflib.SequenceMatcher(None,a,b,autojunk=False).get_opcodes() if tag!='equal')

def experiment(row,text,pseudo,change,base,lane,keep=None,retail_set=None,timeout=180):
    kitlib.add_paths(); import alloc_sim
    from common import parse_cfg
    first=alloc_sim.FIRST[parse_cfg(row['cfg'])[0]]; mapping=observed_names(row,text)
    p,dp=resolve_pseudo(text,pseudo,first,mapping)
    # Never silently equate a pinned listing with retail when its byte control failed.
    calibration=kitlib.score_fields(kitlib.score_at(row,base))
    if not calibration.get('exact'): raise RuntimeError('pinned retail control failed: '+json.dumps(calibration))
    refmap=observed_names(row,base)
    pinned=kitlib.dumps(row,base,want={'greg'})
    if pinned.get('error'): raise RuntimeError(pinned['error'])
    _,refdisp=alloc_sim.parse_greg(pinned.get('greg',''))
    refs={name:reg if reg<first else refdisp.get(reg) for name,reg in refmap.items() if reg is not None}
    ref_ok=True
    a=trace(row,text,p,timeout=timeout,keep=Path(keep)/'baseline' if keep else None)
    b=trace(row,text,p,change,timeout=timeout,keep=Path(keep)/'forced' if keep else None)
    if a['errors'] or b['errors']: raise RuntimeError('oracle invalid: '+json.dumps({'baseline':a['errors'],'forced':b['errors']}))
    plain=kitlib.dumps(row,text,want=set())
    if plain.get('error') or alloc_sim.norm_asm(plain['asm'])!=alloc_sim.norm_asm(a['asm']):
        raise RuntimeError('uninjected GDB baseline differs from the plain compiler')
    ca,cb=last_colours(a),last_colours(b); colours=[]
    names={v:k for k,v in mapping.items() if v is not None}
    for i in range(first,min(len(ca),len(cb))):
        name=names.get(i,''); target=(retail_set or {}).get(str(i),(retail_set or {}).get(name,refs.get(name)))
        if i==p or ca[i]!=cb[i] or target is not None:
            colours.append({'pseudo':i,'name':name,'baseline':ca[i],'forced':cb[i],'retail':target,
                            'matches_retail':cb[i]==target if target is not None else None,
                            'retail_evidence':'explicit target' if str(i) in (retail_set or {}) or name in (retail_set or {}) else 'calibrated pinned name' if target is not None else 'unknown'})
    la,lb,lr=(alloc_sim.norm_asm(s) for s in (a['asm'],b['asm'],pinned['asm']))
    return {'row':row['id'],'cfg':row['cfg'],'pseudo':p,'change':change,'calibration':calibration,
            'baseline_distance':distance(la,lr),'forced_distance':distance(lb,lr),'listing_identical_to_retail_control':lb==lr,
            'baseline_trace_faithful':True,'reference_names_available':ref_ok,'colours':colours,'baseline':a,'forced':b,
            'reviewer':'pending','counterfactual':True,'stageable':False}

def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__); ap.add_argument('row'); ap.add_argument('text'); ap.add_argument('--pseudo',required=True)
    g=ap.add_mutually_exclusive_group(required=True)
    for flag in ('refs','refs-add','live','qty-refs','qty-life','qty-rank','force-local'): g.add_argument('--'+flag,type=int)
    g.add_argument('--force-global',action='store_true')
    ap.add_argument('--cfg'); ap.add_argument('--json'); ap.add_argument('--keep'); ap.add_argument('--timeout',type=float,default=180)
    ap.add_argument('--retail-set',action='append',default=[],metavar='PSEUDO=REG')
    a=ap.parse_args(argv); lane=kitlib.bootstrap(); row=kitlib.row_of(a.row)
    if a.cfg: row=kitlib.row_at_cfg(row,a.cfg)
    try:
        kind=next(k for k in ('refs','refs-add','live','qty-refs','qty-life','qty-rank','force-local','force-global') if getattr(a,k.replace('-','_')) is not None and getattr(a,k.replace('-','_')) is not False)
        change={'kind':{'force-local':'local','force-global':'global'}.get(kind,kind)}
        if kind!='force-global': change['value']=getattr(a,kind.replace('-','_'))
        validate_change(change); hand={}
        import alloc_sim
        for item in a.retail_set:
            key,reg=item.split('=',1); token=reg.lstrip('$'); names={v.lstrip('$'):i for i,v in enumerate(alloc_sim.GPR)}
            value=int(token) if token.isdigit() else names[token]
            if not 0<=value<alloc_sim.FIRST.get(row.get('cell'),76): raise ValueError('retail register outside target register file')
            hand[key]=value
        r=experiment(row,sncheck.input_text(a.text,row,lane),a.pseudo,change,kitlib.base_text(row,lane),lane,a.keep,hand,a.timeout)
    except (ValueError,KeyError,RuntimeError,OSError,subprocess.TimeoutExpired) as e: ap.exit(2,'alloc_oracle: '+str(e)+'\n')
    print('# COUNTERFACTUAL, not a stageable candidate: '+json.dumps(change))
    print('listing distance vs calibrated retail control: %d -> %d' % (r['baseline_distance'],r['forced_distance']))
    print('IDENTICAL to retail control' if r['listing_identical_to_retail_control'] else 'listing differs from retail control')
    for c in r['colours']:
        if c['pseudo']==r['pseudo'] or c['baseline']!=c['forced']:
            print('p%d %s: %s -> %s; retail %s' % (c['pseudo'],c['name'],alloc_sim.reg_name(c['baseline']),alloc_sim.reg_name(c['forced']),alloc_sim.reg_name(c['retail']) if c['retail'] is not None else '?'))
    if a.json: Path(a.json).write_text(json.dumps(r,indent=2)+'\n')
    return 0
if __name__=='__main__': raise SystemExit(main())
