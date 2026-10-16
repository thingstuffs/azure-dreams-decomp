"""Cumulative, repository-relative receipts and patch for decision 54 admissions."""
import collections,csv,gzip,hashlib,json,re,shutil,struct,subprocess,os
from pathlib import Path
from twins import L,R,save,sha,jl,strip
PREFIXES=[(str(R)+'/', ''), (str((R/'toolchain').resolve())+'/', 'toolchain/'), (str((R/'.venv').resolve())+'/', '.venv/')]

def relative(value):
    if isinstance(value,str):
        for old,new in PREFIXES:value=value.replace(old,new)
        return value.replace(str(R),'.')
    if isinstance(value,list):return [relative(v) for v in value]
    if isinstance(value,dict):return {k:relative(v) for k,v in value.items()}
    return value

def committed(value):
    """Root-relative file fields and argv relative to an explicit command cwd."""
    if isinstance(value,list):return [committed(v) for v in value]
    if isinstance(value,dict):
        out={}
        for key,item in value.items():
            if key in ('command','disasm_command','m2c_command') and isinstance(item,list):
                build=key=='command' and any(str(a) in ('tools/rowbase.py','tools/overlay_local_gate.py') for a in item)
                cwd=R/'build_ovl' if build else R
                out[key]=[os.path.relpath(str(a),cwd) if str(a).startswith(str(R)+'/') else relative(a) for a in item]
                out[key+'_cwd']='build_ovl' if build else '.'
            else:out[key]=committed(item)
        return out
    if isinstance(value,str):
        value=relative(value)
        if value.startswith('evidence/'):return str(L.relative_to(R))+'/'+value
        return value
    return value

def portable_object(source, target):
    """Make only ELF STT_FILE metadata relative; preserve every other byte.

    The production object remains untouched and is the audit authority. The
    archive copy has identical code, relocation records, and symbol indices.
    """
    before=source.read_bytes();data=bytearray(before);changes=[]
    assert data[:6]==b'\x7fELF\x01\x01'
    start=struct.unpack_from('<I',data,0x20)[0]
    ents,count=struct.unpack_from('<HH',data,0x2e)
    sections=[struct.unpack_from('<10I',data,start+i*ents) for i in range(count)]
    for section in sections:
        if section[1]!=2:continue
        strings=sections[section[6]]
        for off in range(section[4],section[4]+section[5],section[9]):
            name,_,_,info,_,_=struct.unpack_from('<IIIBBH',data,off)
            if info&15!=4:continue
            begin=strings[4]+name;end=data.index(0,begin)
            old=bytes(data[begin:end]);new=relative(old.decode()).encode()
            if old==new:continue
            assert len(new)<=len(old)
            data[begin:end]=new+b'\0'*(len(old)-len(new))
            changes.append(dict(offset=begin,length=len(old),before_sha256=hashlib.sha256(old).hexdigest(),after=new.decode()))
    assert ('/'+ 'home/').encode() not in data,'unhandled absolute path outside STT_FILE metadata'
    target.write_bytes(data)
    return dict(production_sha256=hashlib.sha256(before).hexdigest(),archive_sha256=sha(target),file_metadata_changes=changes)

def publish(state,world=None):
    rows=[];windows={};transactions=[]
    for t in state['transactions']:
        result=json.loads((L/t['result']).read_text());transactions.append(result)
        for b in result['banks']:
            rows.extend(b['rows'])
            if b['status']=='MATCH':
                for g in b['gates']:windows[g['window']]=g
    byid={r['id']:r for r in rows};assert len(byid)==len(rows)
    from twins import World
    from audit_sdk import audit as audit_sdk
    world=world or World()
    from entry_scope import qualify
    for transaction,record in zip(state['transactions'],transactions):
        changed=False
        for bank in record['banks']:
            for row in bank['rows']:changed=qualify(world,row) or changed
        if changed:
            save(L/transaction['result'],record)
            save((L/transaction['result']).with_name('checkpoint.json'),record['banks'])
    # All row metadata shares the qualified transaction objects from here on.
    rows=[r for result in transactions for b in result['banks'] for r in b['rows']]
    body_audit=audit_sdk(world,rows)
    preflight_path=L/'evidence/preflight/summary.json'
    preflight=json.loads(preflight_path.read_text()) if preflight_path.exists() else dict(windows=[],complete=False)
    from window_holds import classify
    from run_sdk import excluded
    prerequisites=[dict(banks=[dict(window=r['window'],gates=[r])]) for r in preflight['windows'] if not r['ok']]
    window_holds=relative(classify(world,transactions+prerequisites,excluded()))
    save(R/'docs/evidence/r121_sdk_window_holds.json',window_holds)
    from object_relocations import row_failures,production_object,relocations
    from pin_census import sites_of
    audit=[]
    for r in rows:
        source=R/'src'/r['container']/(r['func']+'.c');raw=R/'raw'/r['container']/(r['func']+'.c')
        assert sha(source)==r['source_sha256'] and sha(raw)==r['raw_sha256']
        assert not sites_of(source.read_text())
        assert not re.search(r'\b(?:ASM_\w+|NON_MATCHING|__asm__|asm|volatile|goto)\b',strip(source.read_text()))
        assert r['source_score']['exact'] and r['source_score']['total']==0 and r['first_pass']['ok']
        assert not row_failures(r),(r['id'],row_failures(r))
        obj=production_object(r)
        target=R/'docs/evidence/r121_sdk_objects'/r['container']/(r['func']+'.o')
        target.parent.mkdir(parents=True,exist_ok=True)
        metadata=portable_object(obj,target)
        assert relocations(target,r['true_name'])==relocations(obj,r['true_name'])
        audit.append(dict(id=r['id'],object=str(target.relative_to(R)),**metadata,relocations=relocations(obj,r['true_name'])))
    # Append actual measured raw outcomes and exact admitted source evidence.
    for ledger,key,kind in [('baseline','raw_score','baseline'),('promotions','source_score','promotion'),('reverify','source_score','reverify')]:
        path=R/'ledger'/(ledger+'.jsonl');old=jl(path);seen={e.get('event_id') for e in old}
        with path.open('a') as f:
            for r in rows:
                event='r121_sdk:'+kind+':'+r['id']
                if event in seen:continue
                digest=r['raw_sha256'] if kind=='baseline' else r['source_sha256']
                record=dict(r[key],id=r['id'],event_id=event,at='2026-10-16',lane='r121_sdk',reviewer='pending',evidence='docs/evidence/r121_sdk.receipt.json',source_sha=digest,src_sha=digest)
                if kind=='baseline':record['source_kind']='raw-generated-first-pass'
                if kind=='promotion':record.update(body_sha=digest,out_sha=digest,source='new-row:r121_sdk',outcome='landed',size=r['size'])
                f.write(json.dumps(relative(record),separators=(',',':'))+'\n')
    receipt=dict(schema='azure-clean.r121-sdk.v1',base=(L/'BASE_COMMIT').read_text().strip(),decision=54,status=state['status'],rounds=state['rounds'],rows=rows,windows=list(windows.values()),object_audit=audit,body_audit=body_audit,holds=state['holds'],m2c_commit=(R/'toolchain/genuine/m2c/PINNED_COMMIT.txt').read_text().strip(),source_rules='zero pins/asm/volatile/NON_MATCHING/goto; complete unmasked production byte comparison',transactions=transactions)
    save(R/'docs/evidence/r121_sdk.receipt.json',committed(receipt))
    survey=dict(symbols=world.sdk.report,authorities=world.sdk.authorities)
    save(L/'evidence/sdk_contracts.json',survey)
    save(R/'docs/evidence/r121_sdk_contracts.json',relative(survey))
    save(R/'docs/evidence/r121_sdk_preflight.json',relative(preflight))
    from run_sdk import targets
    grouped,banks,families=targets();registered=jl(R/'ledger/rows.jsonl')
    outcomes=[];delivered={(r['container'],r['foff']):r for r in rows}
    extents=collections.defaultdict(list)
    for r in registered:
        if r.get('foff') is not None:extents[r['container']].append((r['foff'],r['foff']+r['size']))
    for c in extents:extents[c].sort()
    def covered(c,o,n):
        cursor=o
        for start,end in extents[c]:
            if end<=cursor:continue
            if start>cursor:return False
            cursor=max(cursor,end)
            if cursor>=o+n:return True
        return False
    for (c,o),item in sorted(grouped.items()):
        n=max(item['sizes']);complete=covered(c,o,n)
        changed=any(r['container']==c and r['foff']<o+n and o<r['foff']+r['size'] for r in rows)
        hold=state['holds'].get(c+':'+hex(o),{})
        status=('COVERED_BY_DELIVERY' if changed else 'COVERED_AT_BASE') if complete else 'HOLD'
        fallback='no further complete eligible function in bounded SDK hold' if state['status']=='FIXED POINT' else 'callee-contract/bank plan still pending'
        outcomes.append(dict(kind='target_span',container=c,foff=hex(o),bytes=n,status=status,reason='' if complete else hold.get('reason',fallback),window=','.join(sorted(item['windows'])),template=''))
    for (c,o),r in sorted(delivered.items()):
        outcomes.append(dict(kind='admission',container=c,foff=hex(o),bytes=r['size'],status='MATCH',reason='bank-chain propagation' if r.get('bank_chain') else 'bounded SDK-hold function entry',window=r['window'],template=r['template']))
    for hold in state['holds'].values():
        c,o=hold['container'],hold['foff']
        if (c,o) in grouped or (c,o) in delivered:continue
        if covered(c,o,hold.get('size',0)):continue
        outcomes.append(dict(kind='function_hold',container=c,foff=hex(o),bytes=hold.get('size',0),status='HOLD',reason=hold['reason'],window=hold['window'],template=hold.get('template','')))
    empty_windows={r['window'] for r in csv.DictReader((L/'sdk_targets.tsv').open(),delimiter='\t') if not r['foff']}
    for name in sorted(empty_windows):
        bank=banks[name];c=bank['container'];preceding=bank['start']-0x6000
        available=any(r['container']==c and preceding<=r.get('foff',-1)<bank['start'] and r['foff']+r['size']<=bank['start'] for r in registered)
        intrinsic=name not in windows and any(r['window']==name and r.get('intrinsic_existing_failure') for r in preflight['windows'])
        outcomes.append(dict(kind='bank',container=c,foff='',bytes='',status='BANK_PREDECESSOR_AVAILABLE' if available and not intrinsic else 'BANK_HOLD',reason='existing matched source/extent blocks production window' if intrinsic else '' if available else 'no matched complete donor rows at preceding 0x6000 bank',window=name,template=''))
    fields=['kind','container','foff','bytes','status','reason','window','template']
    for name,records in [('results.tsv',outcomes),('next.tsv',[r for r in outcomes if r['status'] in ('HOLD','BANK_HOLD')])]:
        with (L/name).open('w') as f:
            w=csv.DictWriter(f,fieldnames=fields,delimiter='\t');w.writeheader();w.writerows(records)
    with (L/'levels_seed_needed.tsv').open('w') as f:
        f.write('id\tsource_sha256\traw_sha256\n')
        for r in rows:f.write('\t'.join((r['id'],r['source_sha256'],r['raw_sha256']))+'\n')
    def category(reason):
        for prefix,label in [('production window gate failed:','production window gate failed'),('rowbase promotion refused:','rowbase promotion refused'),('existing matched source/extent blocks','existing matched source/extent blocks production'),('overlaps twins2','overlaps twins2 source-score/nonrelocation scope')]:
            if reason.startswith(prefix):return label
        return reason
    reasons=collections.Counter(category(r['reason']) for r in outcomes if r['status'] in ('HOLD','BANK_HOLD'))
    symbols=collections.Counter(r['status'] for r in survey['symbols'])
    window_reasons=collections.Counter(r['classification'] for r in window_holds)
    preflight_counts=dict(checked=len(preflight['windows']),matched=sum(r['ok'] for r in preflight['windows']),intrinsic_existing_failures=sum(r.get('intrinsic_existing_failure',False) for r in preflight['windows']),complete=preflight['complete'])
    rounds='\n'.join(f"| {r['round']} | {r['rows']} | {r['bytes']} |" for r in state['rounds'])
    if len(rows)>sum(r['rows'] for r in state['rounds']):
        rounds+=f"\n| {len(state['rounds'])+1} (partial) | {len(rows)-sum(r['rows'] for r in state['rounds'])} | {sum(r['size'] for r in rows)-sum(r['bytes'] for r in state['rounds'])} |"
    rounds=rounds.lstrip('\n')
    canonical=', '.join(r['names'][0] for r in survey['symbols'] if r['status']=='BOUND_CANONICAL')
    sdk_held='; '.join(r['names'][0]+': '+r['status'] for r in survey['symbols'] if r.get('prior_header_status')=='CONFLICT' and r['status']!='BOUND_CANONICAL')
    report=f'''# r121_sdk — decision 54

Base: `{receipt['base']}`. Status: **{state['status']}**.

Delivered {len(rows):,} new complete C rows / {sum(r['size'] for r in rows):,} bytes; {len(windows)} production windows MATCH. Genuine spimdisasm/m2c first passes are in raw/. Source scores are exact; every changed word is independently bound to a production ELF relocation. No admission uses pins, asm, volatile, NON_MATCHING, masks, or goto. Static placement does not assert runtime residency.

| round | unlocked rows | unlocked bytes |
|---:|---:|---:|
{rounds}

Input: 23,972 attempt records, {len(grouped)} distinct container/offset targets, and {len(banks)} supplied windows. Targets already covered at the base contribute no delivery rows. Source-score and nonrelocation overlaps are held for twins2. Existing rowbase extents and deltas stay fixed; solved-to-proven changes use the normal promotion hook.

SDK survey: {dict(symbols)}. A matched donor's explicit declaration takes precedence, including local outliers and old-style declarations. Without one, only an unchanged resident SDK symbol with an approved canonical declaration binds. `rand` uses s32 rand(void), `rsin` uses s32 rsin(s32). The other canonical declarations require a uniquely dominant matched source/header ABI agreeing with the PsyQ archive prototype. Old-style declarations support a unique C89-compatible typed signature; ambiguous signatures retain separate vote buckets. Pointer pointees are opaque across translation units, following the inherited contract rule. Full symbol evidence is in docs/evidence/r121_sdk_contracts.json.

Canonical symbols bound: {canonical}.

Conflicting symbols without a canonical fallback (a donor's own declaration can still bind): {sdk_held}.

Remaining holds (deduplicated physical offsets and bank windows): {dict(reasons)}.

Production window blockers: {dict(window_reasons)}. Exact existing rows, source hashes, compiler diagnostics, and overlap with twins2's frozen scope are listed in docs/evidence/r121_sdk_window_holds.json. Existing source failures remain holds in this lane.

Starting-tree production checks: {preflight_counts}. These are normal clean production gates on the unchanged source tree, run concurrently with no admission runner active. Only a recorded intrinsic compile failure in an existing matched file, or a fixed-extent length failure, can block further proposals. Such holds require the same source hash and interface/compiler guard. Other failed checks remain eligible for ordinary admission attempts. Complete records are in docs/evidence/r121_sdk_preflight.json.

Deliveries: delivery.patch, results.tsv, next.tsv, levels_seed_needed.tsv; src/raw pairs, append-only split/baseline/promotion/reverify records, registry/graph changes, production object copies and receipts under docs/evidence/r121_sdk*. The patch is cumulative against the base SHA. Raw measurements retain failures; no exact L0 baseline policy is silently imposed. Integration must seed levels under its policy.

The archived native objects change only ELF STT_FILE filename strings to repository-relative metadata. The production objects remain untouched; all code bytes, relocation records and symbol indices are preserved. Both hashes and the metadata byte ranges are recorded.

Per-item status: tooling and decision 54 binding implemented; contract and bank closure {state['status']}; production/source/raw/object gates required per admission. Other twins2 classes are held outside this lane.

HOW TO CONTINUE: from this private root run `python3 tools/lanes/r121_sdk/run_sdk.py apply` with no second mutation runner. Check state/progress.json and evidence/run.log in the lane. Refresh prerequisite checks with `python3 tools/lanes/r121_sdk/preflight_windows.py` only while the mutation runner is stopped. Existing source-score and nonrelocation repairs belong to twins2; after their integration, refresh the base/donor snapshot and scope, then rerun all affected gates. After a code fix, retry failed transactions only when inputs or dependencies change. Re-publish with `python3 tools/lanes/r121_sdk/run_sdk.py publish`. Do not bypass base guards.
'''
    (L/'REPORT.md').write_text(report);(R/'docs/evidence/r121_sdk.md').write_text(report)
    # Intent-to-add includes new files in the requested ordinary binary diff.
    subprocess.run(['git','add','-N','--','src','raw','include','config','ledger','tools/lanes/r121_sdk','docs/evidence/r121_sdk.md','docs/evidence/r121_sdk.receipt.json','docs/evidence/r121_sdk_contracts.json','docs/evidence/r121_sdk_window_holds.json','docs/evidence/r121_sdk_preflight.json',*(['docs/evidence/r121_sdk_objects'] if rows else [])],cwd=R,check=True)
    with (L/'delivery.patch').open('wb') as f:subprocess.run(['git','diff','--binary',receipt['base'],'--','src','raw','include','config','ledger','tools','docs'],cwd=R,stdout=f,check=True)
    subprocess.run(['git','-c','core.whitespace=-blank-at-eof','diff','--check'],cwd=R,check=True)
    changed=subprocess.check_output(['git','diff','--name-only','--','src','raw','include','config','ledger','tools','docs'],cwd=R).decode().splitlines()
    for name in changed:
        if ('/'+'home/').encode() in (R/name).read_bytes():raise ValueError('absolute home path in '+name)
    if changed:
        subprocess.run(['git','add','--',*changed],cwd=R,check=True)
        subprocess.run(['git','commit','-m',f'r121_sdk: checkpoint {len(rows)} exact C rows / {sum(r["size"] for r in rows)} bytes'],cwd=R,check=True,stdout=subprocess.DEVNULL)
    print('PUBLISHED',len(rows),sum(r['size'] for r in rows),len(windows),'windows',flush=True)
