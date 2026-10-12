#!/usr/bin/env python3
"""Numeric-target 2.6.3 adapter for the prerequisite allocator oracle.

The verified symbol-only i386 local/global allocator ABI is shared with CDK:
refs/life/qty arrays are i32; reg_n_deaths and reg_renumber are i16; qsort gets
qty_compare_1/qty_sugg_compare_1. Actual 808119EC traces prove the adapter. Names
are refused at 2.6.3 because its DECL_RTL observer has not been verified.
"""
import argparse,json
from pathlib import Path
import alloc_oracle as original,kitlib,sncheck
def validate_change(change):
    if change is None:return
    expected={'kind'} if change.get('kind')=='global' else {'kind','value'}
    if set(change)!=expected:raise ValueError('one allocator input with its exact fields required')
    original.validate_change(change)


def trace(row,text,pseudo,change=None,timeout=60,keep=None):
    validate_change(change)
    kitlib.add_paths();from common import parse_cfg
    cell,_=parse_cfg(row['cfg'])
    if cell=='2.6.3' and not str(pseudo).isdigit():raise ValueError('2.6.3 requires an explicit numeric pseudo')
    # Extend the imported runtime policy, never edit the prerequisite tool.
    if '2.6.3' not in original.SUPPORTED:original.SUPPORTED=(*original.SUPPORTED,'2.6.3')
    return original.trace(row,text,pseudo,change,timeout,keep)

def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('row');ap.add_argument('text');ap.add_argument('--pseudo',required=True)
    ap.add_argument('--change',required=True,help='one allocator-input JSON');ap.add_argument('--out',required=True,type=Path)
    ap.add_argument('--timeout',type=float,default=60)
    a=ap.parse_args(argv);lane=kitlib.bootstrap();row=kitlib.row_of(a.row);text=sncheck.input_text(a.text,row,lane)
    import pass_oracle
    try:
        if not a.out.resolve().is_relative_to(lane):raise ValueError('output must be lane-owned')
        a.out.mkdir(parents=True,exist_ok=True);ch=json.loads(a.change);validate_change(ch)
        base=trace(row,text,a.pseudo,None,a.timeout,a.out/'baseline');forced=trace(row,text,a.pseudo,ch,a.timeout,a.out/'forced')
        if base['errors'] or forced['errors']:raise ValueError('; '.join(base['errors']+forced['errors']))
        plain=kitlib.dumps(row,text,want=set(),timeout=a.timeout)
        if plain.get('error') or sncheck.normalize(plain['asm'])!=sncheck.normalize(base['asm']):raise ValueError('uninjected debugger differs from plain cc1')
        control=kitlib.base_text(row,lane);control_asm=kitlib.dumps(row,control,want=set(),timeout=a.timeout)
        if control_asm.get('error'):raise ValueError('pinned control failed to compile')
        calibration=pass_oracle.raw_bytes(row,control,control_asm['asm'],a.out/'calibration')
        if not calibration['raw_equal']:raise ValueError('pinned raw-byte control failed')
        rec={'row':row['id'],'change':ch,'baseline_trace_faithful':True,'calibration':calibration,
             'baseline':pass_oracle.compact(base),'forced':pass_oracle.compact(forced),
             'raw':pass_oracle.raw_bytes(row,text,forced['asm'],a.out/'raw'),'reviewer':'pending','stageable':False}
        (a.out/'result.json').write_text(json.dumps(rec,indent=2)+'\n');print(json.dumps(rec['raw'],indent=2));return 0
    except (ValueError,RuntimeError,OSError) as e:ap.exit(2,'alloc263_oracle: '+str(e)+'\n')
if __name__=='__main__':raise SystemExit(main())
