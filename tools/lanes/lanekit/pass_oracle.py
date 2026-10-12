#!/usr/bin/env python3
"""Single, named compiler intervention; observations and raw bytes, never stageable C.

Use --discover to enumerate observed sites. Change JSON has a kind plus numeric
UID/pseudo selectors. Each run calibrates the uninjected debugger against plain
cc1. A no-op, absent target, failed compiler, or ambiguous MEM pair is invalid.
"""
from __future__ import annotations
import argparse, difflib, hashlib, json, os, re, shutil, subprocess, tempfile, signal, threading
from pathlib import Path
import kitlib, sncheck

SUPPORTED = ('2.7.2-cdk', '2.7.2', '2.6.3', '2.8.0')
# 2.8.x keeps per-pseudo flow facts in reg_n_info (struct reg_info_def, regs.h): byte offsets.
REGINFO_28 = {'stride': 40, 'refs': 16, 'deaths': 20, 'live': 24, 'block': 32}
ALLOC_NAMES = ('reg_qty','qty_n_refs','qty_birth','qty_death','next_qty','max_regno','update_equiv_regs','block_alloc','qsort',
               'qty_sugg_compare','qty_compare','qty_sugg_compare_1','qty_compare_1','reg_renumber')
KINDS = {
    'sched-priority': ('uid', 'phase', 'value'),
    'sched-birth': ('uid', 'phase', 'value'),
    'sched-luid': ('uid', 'phase', 'value'),
    'combine-veto': ('uids',),
    'combine-crosses': ('uids',),
    'cse-copy-swap': ('uid',),
    'cse-substitution': ('uid', 'occurrence'),
    'alias': ('uids', 'phase', 'value'),
    'loop-hoist': ('uid',),
    'loop-biv': ('pseudo', 'uid'),
    'keep-dead': ('uid',),
    'reload-equiv': ('uid', 'occurrence'),
    'reload-cse': ('uid',),
    'reload-reuse': ('uid', 'occurrence', 'value'),
    'reload-noop': ('uid', 'value'),
    'global-avoid': ('pseudo', 'hardreg'),
    'reorg-fill': ('uid', 'candidate_uid', 'value'),
    'reorg-merge': ('uid', 'thread_uid', 'value'),
    'reorg-delete': ('uid', 'value'),
    'jump-cross': ('uids', 'value'),
    'frame-offset': ('occurrence', 'value'),
    'cse-eqv-head': ('new', 'old', 'occurrence', 'head'),
}
FAMILIES = ('sched', 'combine', 'cse', 'alias', 'loop', 'dead', 'reload', 'reorg', 'jump', 'frame', 'refs', 'global')
MAX_COMPOSITE = 4

def family_of(change):
    if change['kind']=='alloc': return 'alloc'
    return {'keep':'dead','sched':'sched','cse':'cse','combine':'combine','loop':'loop','reload':'reload',
            'alias':'alias','global':'global','reorg':'reorg','jump':'jump','frame':'frame'}[change['kind'].split('-')[0]]

def members(change):
    return [] if change is None else list(change) if isinstance(change, list) else [change]

def validate(change):
    """One change (dict) or a composite: a list of 2..MAX_COMPOSITE distinct changes."""
    if change is None: return
    if isinstance(change, list):
        if not 2 <= len(change) <= MAX_COMPOSITE: raise ValueError('composite needs 2..%d changes' % MAX_COMPOSITE)
        seen = set()
        for c in change:
            validate_one(c); k = json.dumps(c, sort_keys=True)
            if k in seen: raise ValueError('duplicate composite member')
            seen.add(k)
        return
    validate_one(change)

def validate_one(change):
    if isinstance(change, dict) and change.get('kind') == 'alloc':
        if set(change) != {'kind', 'pseudo', 'input'}: raise ValueError('alloc change needs kind, pseudo, input')
        if type(change['pseudo']) is not int or change['pseudo'] < 1: raise ValueError('pseudo must be a positive integer')
        import alloc263_oracle
        if not isinstance(change['input'], dict): raise ValueError('alloc input must be an object')
        alloc263_oracle.validate_change(change['input'])
        return
    if not isinstance(change, dict) or change.get('kind') not in KINDS:
        raise ValueError('unknown intervention kind')
    kind = change['kind']
    allowed = {'kind', *KINDS[kind]}
    if set(change) != allowed: raise ValueError('expected fields '+str(sorted(allowed)))
    if 'hardreg' in change and (type(change['hardreg']) is not int or not 0 <= change['hardreg'] < 64):
        raise ValueError('hardreg must be a hard register number 0..63')
    for k in ('uid', 'candidate_uid', 'thread_uid', 'pseudo', 'occurrence', 'new', 'old', 'head'):
        if k in change and (type(change[k]) is not int or change[k] < (0 if k == 'occurrence' else 1)):
            raise ValueError(k+' must be a non-negative integer')
    if 'uids' in change:
        u = change['uids']
        n = 2 if kind in ('alias', 'jump-cross') else 3
        if not isinstance(u, list) or len(u) != n or any(type(x) is not int or x < 0 for x in u):
            raise ValueError('uids must have '+str(n)+' integer entries (i3,i2,i1; 0 = absent i1)')
        if any(x == 0 for x in u[:2]) or len(set(u[:2])) != 2: raise ValueError('two distinct positive UIDs required')
    if 'phase' in change and change['phase'] not in ('sched1', 'sched2'): raise ValueError('invalid scheduler phase')
    if 'value' in change and (type(change['value']) is not int or not -(2**30) < change['value'] < 2**30):
        raise ValueError('value must be a bounded integer')
    if kind in ('alias', 'sched-birth', 'reload-reuse', 'reload-noop', 'reorg-fill', 'reorg-merge', 'reorg-delete', 'jump-cross') and change['value'] not in (0, 1):
        raise ValueError('value must be 0 or 1')

def symbol_table(cc1):
    elf = cc1.read_bytes()[:20]
    if elf[:6] != b'\x7fELF\x01\x01' or elf[18:20] != b'\x03\x00': raise ValueError('requires i386 little-endian ELF')
    result = {}
    for line in subprocess.run(['nm', '-S', '-n', str(cc1)], capture_output=True, text=True, check=True).stdout.splitlines():
        p = line.split()
        if len(p) == 4: result.setdefault(p[3], []).append((int(p[0],16), int(p[1],16), p[2]))
    return result

def addresses(cc1):
    syms = symbol_table(cc1)
    # Unique runtime symbols only; duplicate local names require explicit ownership.
    names = ('current_function_name', 'reload_completed', 'rtx_name', 'rtx_format', 'rtx_length',
             'mode_name', 'mode_size', 'insn_priority', 'insn_luid', 'sched_analyze', 'adjust_priority',
             'birthing_insn_p', 'priority', 'rank_for_schedule', 'try_combine', 'use_crosses_set_p',
             'cse_insn', 'validate_change', 'true_dependence', 'memrefs_conflict_p', 'move_movables',
             'basic_induction_var', 'insn_dead_p', 'find_equiv_reg', 'reload_cse_simplify_set',
             'reload_cse_noop_set_p', 'mark_used_regs', 'mark_set_regs', 'reg_n_refs', 'reg_live_length',
             'max_regno', 'local_alloc', 'global_alloc', 'flow_analysis', 'delete_insn', 'rest_of_compilation', 'reg_basic_block', 'reg_n_deaths',
             'reg_renumber', 'reg_allocno', 'hard_reg_conflicts', 'max_allocno', 'prune_preferences', 'reload', 'reg_n_info',
             'eligible_for_delay', 'try_merge_delay_insns', 'find_cross_jump', 'do_cross_jump',
             'assign_stack_local', 'frame_offset', 'make_regs_eqv', 'canon_reg', 'qty_last_reg', 'reg_next_eqv', 'reg_prev_eqv')
    out = {}; sizes = {}
    for n in names:
        candidates = syms.get(n, [])
        if len(candidates) == 1: out[n], sizes[n], _ = candidates[0]
        elif len(candidates) > 1: raise ValueError('ambiguous symbol '+n)
    for n in ('rtx_name', 'rtx_format', 'mode_name', 'current_function_name', 'reload_completed'):
        if n not in out: raise ValueError('missing runtime symbol '+n)
    # Detect the adjacent-copy group from THREE validate_change calls followed
    # immediately by apply_change_group. This selects no fixed binary offset.
    code = subprocess.run(['objdump','-d','--no-show-raw-insn','--disassemble=cse_insn',str(cc1)],
                          capture_output=True,text=True,check=True).stdout
    ins = []
    for line in code.splitlines():
        m = re.match(r'\s*([0-9a-f]+):\s+(\S+)\s*(.*)', line)
        if m: ins.append((int(m[1],16),m[2],m[3]))
    calls = [(i, v) for i,v in enumerate(ins) if v[1].startswith('call')]
    matches = []
    for j in range(3,len(calls)):
        prev = calls[j-3:j]; here = calls[j]
        if '<apply_change_group>' in here[1][2] and all('<validate_change>' in v[2] for _,v in prev):
            # Preceding find_reg_note belongs to the copy-swap block and supplies
            # its REG_EQUIV lookup. Skip the whole group including note edits by
            # jumping to the final this_insn assignment's successor condition.
            start_j = prev[0][0]
            following = ins[here[0]+1:]
            end = next((a for a,m,o in following if m == 'movl' and o.startswith('$0x0,')),None)
            if end: matches.append({'first_call': ins[start_j][0], 'end': end,
                                    'calls': [v[0] for _,v in prev]})
    if len(matches) == 1: out['copy_swap_site'] = matches[0]['first_call']; out['copy_swap_end'] = matches[0]['end']
    # cse.c and local-alloc.c both have file-static reg_qty/qty_first_reg.
    # The CSE copies sit beside its unique equivalence-chain arrays in BSS.
    anchor = out.get('reg_next_eqv')
    if anchor is not None:
        for n in ('reg_qty', 'qty_first_reg'):
            candidates = syms.get(n, [])
            if candidates: out[n], sizes[n], _ = min(candidates, key=lambda x: abs(x[0] - anchor))
    return out, sizes

def alloc_symbols(cc1):
    """local-alloc statics, duplicates resolved as alloc_oracle.symbols does (nearest to the
    unique qty_n_refs anchor), without requiring the 2.7-only reg_n_* arrays."""
    syms = symbol_table(cc1)
    missing = [n for n in ALLOC_NAMES if n not in syms]
    if missing: raise ValueError('cc1 lacks allocator symbols: ' + ', '.join(missing))
    anchor = syms['qty_n_refs'][0][0]
    return {n: min((a for a, _, _ in syms[n]), key=lambda a: abs(a - anchor)) for n in ALLOC_NAMES}

def function_name(text):
    kitlib.add_paths(); import alloc_sim
    dp = alloc_sim.decl_pseudos(text, 76)
    if not dp: raise ValueError('one standalone function required')
    return dp['fname']

def run_bounded(cmd,cwd,timeout):
    proc=subprocess.Popen(cmd,cwd=cwd,stdout=subprocess.PIPE,stderr=subprocess.PIPE,text=True,start_new_session=True)
    try:
        stdout,stderr=proc.communicate(timeout=timeout)
    except subprocess.TimeoutExpired:
        os.killpg(proc.pid,signal.SIGKILL)
        stdout,stderr=proc.communicate()
        raise subprocess.TimeoutExpired(cmd,timeout,output=stdout,stderr=stderr)
    return subprocess.CompletedProcess(cmd,proc.returncode,stdout,stderr)

def trace(row, text, change=None, families=None, timeout=60, keep=None):
    validate(change); kitlib.add_paths()
    from common import parse_cfg
    cell,_ = parse_cfg(row['cfg'])
    if cell not in SUPPORTED: raise ValueError('unverified pass-oracle ABI for '+cell)
    if kitlib.module_fingerprint(row) is not None: raise ValueError('grouped SLUS context unsupported')
    fam = list(FAMILIES if families is None else families)
    if set(fam)-set(FAMILIES): raise ValueError('unknown discovery family')
    with tempfile.TemporaryDirectory(prefix='passoracle_') as td:
        d=Path(td); cc,flags,cpp=sncheck.preprocess(row,text,d)
        addrs,sizes=addresses(cc/'cc1')
        args=['in.i','-quiet','-O2',*flags,'-w','-da','-o','out.s']
        plain=subprocess.run(['nice','-n','10',str(cc/'cc1'),*args[:-1],'plain.s'],cwd=d,capture_output=True,text=True,timeout=timeout)
        if plain.returncode or not (d/'plain.s').is_file(): raise RuntimeError('plain cc1 failed: '+plain.stderr[-1000:])
        plain_asm=(d/'plain.s').read_text()
        ents=re.findall(r'^\s*\.ent\s+(\S+)',plain_asm,re.M)
        if len(ents)!=1: raise ValueError('exactly one preprocessed function required')
        import alloc_sim
        cfg={'addresses':addrs,'sizes':sizes,'function':ents[0],'change':change,'families':fam,'max_events':12000,
             'first':alloc_sim.FIRST[cell]}
        if 'reg_n_refs' not in addrs:
            if 'reg_n_info' not in addrs: raise ValueError('cc1 has neither reg_n_refs nor reg_n_info')
            cfg['reginfo']=REGINFO_28
        if any(c['kind']=='alloc' for c in members(change)):
            cfg['alloc_addresses']=alloc_symbols(cc/'cc1')
        (d/'pass_cfg.json').write_text(json.dumps(cfg))
        shutil.copy2(Path(__file__).with_name('pass_oracle_gdb.py'),d/'trace.py')
        (d/'trace.gdb').write_text('set pagination off\nset confirm off\nset debuginfod enabled off\nset startup-with-shell off\nsource trace.py\n')
        args=['in.i','-quiet','-O2',*flags,'-w','-da','-o','out.s']
        cmd=['nice','-n','10','gdb','--batch','--nx','-x','trace.gdb','--args',str(cc/'cc1'),*args]
        try: run=run_bounded(cmd,d,timeout)
        except subprocess.TimeoutExpired as e:
            (d/'gdb.log').write_text((e.stdout or '')+(e.stderr or ''))
            if keep:
                target=Path(keep).resolve()
                if not target.is_relative_to(kitlib.lane_dir()): raise ValueError('--keep must be lane-owned')
                target.mkdir(parents=True,exist_ok=True)
                for p in d.iterdir():
                    if p.is_file():shutil.copy2(p,target/p.name)
            raise
        (d/'gdb.log').write_text(run.stdout+run.stderr)
        if not (d/'pass_trace.json').is_file(): raise RuntimeError('no trace: '+(run.stdout+run.stderr)[-1600:])
        rec=json.loads((d/'pass_trace.json').read_text())
        rec.update(row=row['id'],cfg=row['cfg'],change=change,cc1_sha256=hashlib.sha256((cc/'cc1').read_bytes()).hexdigest(),
                   input_sha256=hashlib.sha256((d/'in.i').read_bytes()).hexdigest(),commands=[cpp,cmd])
        if run.returncode or rec['inferior_exit'] != 0 or not (d/'out.s').is_file(): rec['errors'].append('compiler/debugger failed')
        if change and not rec['applied']: rec['errors'].append('no effective intervention at selected site')
        elif isinstance(change,list):
            missing=[i for i in range(len(change)) if i not in rec.get('applied_changes',[])]
            if missing: rec['errors'].append('composite member(s) never applied: '+','.join(map(str,missing)))
        rec['asm']=(d/'out.s').read_text() if (d/'out.s').is_file() else ''
        if change is None:
            rec['faithful']=sncheck.normalize(rec['asm'])==sncheck.normalize(plain_asm)
            if not rec['faithful']: rec['errors'].append('uninjected debugger differs from plain compiler')
        rec['dumps']={p.suffix[1:]:p.read_text(errors='replace') for p in d.iterdir() if p.suffix[1:] in kitlib.PASS_SUFFIX}
        if keep:
            target=Path(keep).resolve()
            if not target.is_relative_to(kitlib.lane_dir()): raise ValueError('--keep must be lane-owned')
            target.mkdir(parents=True,exist_ok=True)
            for p in d.iterdir():
                if p.is_file(): shutil.copy2(p,target/p.name)
        return rec

_SLUS_REF = {}
_SLUS_LOCK = threading.Lock()

def slus_reference(row):
    """Production object of the row's PINNED text (verify.compile_slus, the SLUS build's own
    recipe). The pinned text is certified by the SLUS full-image SHA-1 gate, so an object whose
    allocated sections and symbolic relocations equal this one links to the same retail bytes."""
    kitlib.add_paths(); import verify
    from common import parse_cfg
    pinned = kitlib.base_text(row, kitlib.lane_dir()); k = (row['id'], hashlib.sha256(pinned.encode()).hexdigest())
    with _SLUS_LOCK:
        if k not in _SLUS_REF:
            d = kitlib.lane_dir() / 'slus_reference' / (row['id'].replace('/', '__') + '_' + k[1][:12])
            d.mkdir(parents=True, exist_ok=True); (d.parent / '.ignore').write_text('*\n')
            src = d / Path(row.get('c_path') or (row['id'].split('/')[1] + '.c')).name; src.write_text(pinned)
            reg = kitlib.row_of(row['id'])          # the pinned text is certified at the REGISTERED cfg
            cell, flags = parse_cfg(reg['cfg'])
            r = dict(reg, cell=cell, flags=' '.join(flags), row_asflags=reg.get('row_asflags') or '')
            obj, err = verify.compile_slus(r, src, d, include_root=kitlib.ROOT / 'include')
            if obj is None: raise RuntimeError('production SLUS compile of the pinned text failed: ' + str(err))
            _SLUS_REF[k] = obj.read_bytes()
        return _SLUS_REF[k]

def slus_view(data):
    kitlib.add_paths(); import sys
    sys.path.insert(0, str(kitlib.ROOT / 'tools'))
    from fidelity.objread import read_elf
    o = read_elf(data)
    keep = ('.text', '.rodata', '.rdata', '.data', '.sdata', '.sbss', '.bss')
    secs = {n: b for n, b in o.sections.items() if any(n == k or n.startswith(k + '.') for k in keep)}
    return secs, sorted(map(repr, o.relocs))

def slus_text(secs):
    t = b''.join(b for n, b in sorted(secs.items()) if n == '.text' or n.startswith('.text.'))
    if not t: raise ValueError('SLUS object has no text section')
    return t

def raw_slus(row, text, asm, directory):
    """SLUS rows: assemble the emitted stream exactly as verify._compile_slus_source does
    (ccproc names, maspsx 2.79 -G8), then compare allocated sections + symbolic relocations
    with the production object of the certified pinned text. Equal => same linked bytes."""
    kitlib.add_paths(); import verify
    out = Path(directory).resolve()
    if not out.is_relative_to(kitlib.lane_dir()): raise ValueError('raw output must be lane-owned')
    out.mkdir(parents=True, exist_ok=True)
    ref = slus_reference(row)
    processed = verify.postprocess_slus(asm, root=kitlib.ROOT)
    (out / 'forced.s').write_text(asm); (out / 'forced.proc.s').write_text(processed)
    cmd = [str(verify.VENV_PY), str(verify.MASPSX), '--aspsx-version=2.79', '--dont-force-G0', '--run-assembler',
           '--gnu-as-path=mipsel-linux-gnu-as', f"-I{kitlib.ROOT / 'raw'}", f"-I{kitlib.ROOT / 'include'}",
           '-EL', '-march=r3000', '-G8', *(row.get('row_asflags') or '').split(), '-o', str(out / 'forced.o')]
    run = subprocess.run(cmd, input=processed, capture_output=True, text=True, cwd=kitlib.ROOT, env=verify._env())
    if run.returncode or not (out / 'forced.o').is_file(): raise RuntimeError('maspsx replay failed: ' + (run.stderr or run.stdout)[-600:])
    got = (out / 'forced.o').read_bytes(); (out / 'reference.o').write_bytes(ref)
    gs, gr = slus_view(got); rs, rr = slus_view(ref)
    gt, rt = slus_text(gs), slus_text(rs)
    (out / 'forced.bin').write_bytes(gt); (out / 'retail.bin').write_bytes(rt)
    equal = gs == rs and gr == rr
    rec = {'kind': 'COUNTERFACTUAL_OBJECT_VS_CERTIFIED_PINNED_SLUS', 'raw_equal': equal, 'aligned_distance': aligned_distance(gt, rt),
           'sections_equal': gs == rs, 'relocations_equal': gr == rr,
           'bytes_generated': len(gt), 'bytes_retail': len(rt),
           'word_mismatches': sum(gt[i:i+4] != rt[i:i+4] for i in range(0, max(len(gt), len(rt)), 4)),
           'forced_sha256': hashlib.sha256(gt).hexdigest(), 'retail_sha256': hashlib.sha256(rt).hexdigest(),
           'error': None, 'reviewer': 'pending', 'stageable': False}
    (out / 'receipt.json').write_text(json.dumps(rec, indent=2) + '\n')
    return rec

def raw_bytes(row, text, asm, directory):
    """Replay emitted assembly through the ordinary overlay assembler/linker.

    No relocation masking. SLUS rows go through raw_slus (object equality with the
    certified pinned object). Both binaries are retained alongside receipt.
    """
    if row['container']=='slus': return raw_slus(row, text, asm, directory)
    out=Path(directory).resolve()
    if not out.is_relative_to(kitlib.lane_dir()): raise ValueError('raw output must be lane-owned')
    out.mkdir(parents=True,exist_ok=True)
    kitlib.add_paths()
    import sys
    sys.path.insert(0,str(kitlib.ROOT/"tools/fidelity"))
    import aspsx_diff as A
    cand=out/'input.c'; cand.write_text(text)
    ctx,error=A.prepare_overlay(row,cand,row['cfg'],None,str(out))
    if not ctx: raise RuntimeError(str(error))
    ents=re.findall(r'^\s*\.ent\s+(\S+)',asm,re.M)
    if len(ents)!=1: raise ValueError('raw replay needs one function')
    asm=re.sub(r'(?<![A-Za-z0-9_])'+re.escape(ents[0])+r'(?![A-Za-z0-9_])',ctx['symbol'],asm)
    (out/'forced.s').write_text(asm)
    driver=out/'assembly_replay'; driver.mkdir(exist_ok=True)
    script=driver/'gcc'
    script.write_text('#!/usr/bin/env python3\nimport shutil,sys\nfrom pathlib import Path\na=sys.argv[1:];shutil.copyfile(Path(__file__).resolve().parents[1]/"forced.s",a[a.index("-o")+1])\n')
    script.chmod(0o755)
    ofc,_=A._ofc()
    got,error=ofc.M.build_text(str(cand),str(driver),'O2','2.79',' '.join(ctx['flags']),ctx['as_flags'],ctx['link_vram'],
                              target=ctx['symbol'],retail_text=ctx['retail'],asm_output=str(out/'replayed.latest.s'))
    if got is None: raise RuntimeError(str(error))
    (out/'forced.bin').write_bytes(got); (out/'retail.bin').write_bytes(ctx['retail'])
    rec={'kind':'COUNTERFACTUAL_ASSEMBLY_ONLY','raw_equal':got==ctx['retail'],'aligned_distance':aligned_distance(got,ctx['retail']),
         'bytes_generated':len(got),'bytes_retail':len(ctx['retail']),
         'word_mismatches':sum(got[i:i+4]!=ctx['retail'][i:i+4] for i in range(0,max(len(got),len(ctx['retail'])),4)),
         'forced_sha256':hashlib.sha256(got).hexdigest(),'retail_sha256':hashlib.sha256(ctx['retail']).hexdigest(),
         'error':error,'reviewer':'pending','stageable':False}
    (out/'receipt.json').write_text(json.dumps(rec,indent=2)+'\n')
    return rec

def words(b):
    return [b[i:i+4] for i in range(0,len(b),4)]

def aligned_distance(got, retail):
    """Word edit distance after alignment: an inserted/deleted insn costs 1, not every later word."""
    ops=difflib.SequenceMatcher(None,words(got),words(retail),autojunk=False).get_opcodes()
    return sum(max(i2-i1,j2-j1) for tag,i1,i2,j1,j2 in ops if tag!='equal')

def compact(rec):
    return {k:v for k,v in rec.items() if k not in ('asm','dumps')}

def main(argv=None):
    ap=argparse.ArgumentParser(description=__doc__);ap.add_argument('row');ap.add_argument('text')
    g=ap.add_mutually_exclusive_group(required=True);g.add_argument('--discover',action='store_true');g.add_argument('--change',help='JSON object or @file')
    ap.add_argument('--families',default=','.join(FAMILIES));ap.add_argument('--timeout',type=float,default=60)
    ap.add_argument('--keep',required=True,type=Path);ap.add_argument('--json',required=True,type=Path);ap.add_argument('--cfg')
    a=ap.parse_args(argv); lane=kitlib.bootstrap();row=kitlib.row_of(a.row)
    if a.cfg: row=kitlib.row_at_cfg(row,a.cfg)
    try:
        text=sncheck.input_text(a.text,row,lane)
        change=json.loads(Path(a.change[1:]).read_text() if a.change.startswith('@') else a.change) if a.change else None
        baseline=trace(row,text,families=[f for f in a.families.split(',') if f],timeout=a.timeout,keep=a.keep/'baseline')
        if baseline['errors']: raise RuntimeError('; '.join(baseline['errors']))
        out={'baseline':compact(baseline),'counterfactual':True,'stageable':False,'reviewer':'pending'}
        if change:
            forced=trace(row,text,change,[f for f in a.families.split(',') if f],a.timeout,a.keep/'forced')
            out['forced']=compact(forced)
            if not forced['errors']: out['raw']=raw_bytes(row,text,forced['asm'],a.keep/'raw')
            else: out['raw']=None
        a.json.write_text(json.dumps(out,indent=2)+'\n')
        print(json.dumps({'row':row['id'],'events':len(baseline['events']),'applied':out.get('forced',{}).get('applied'),'raw':out.get('raw')},indent=2))
        return 0 if not out.get('forced',{}).get('errors') else 2
    except (ValueError,RuntimeError,OSError,subprocess.TimeoutExpired) as e: ap.exit(2,'pass_oracle: '+str(e)+'\n')
if __name__=='__main__':raise SystemExit(main())
