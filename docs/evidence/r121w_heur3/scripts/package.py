"""Emit a text-only delta against the frozen B13 before-images, then reconstruct it."""
from pathlib import Path
import collections,csv,difflib,hashlib,json,re,shutil,subprocess,sys
LANE=Path(__file__).resolve().parents[1];ROOT=LANE.parents[2]
sys.path[:0]=[str(ROOT/'tools'),str(LANE/'scripts')]
import common
from finalize import digest,dump,table

def proof():
 ps=json.loads((LANE/'evidence/staged.json').read_text());directory=ROOT/'build_ovl/work/s3_splat/town_scene'
 manifest=directory/'town_scene_manifest.json';m=json.loads(manifest.read_text());segments=m['c_segments'];out=[]
 for p in ps:
  a=int(p['foff'],0);n=p['size'];hits=[s for s in segments if int(str(s['file_start']),0)==a and s['size']==n]
  assert len(hits)==1,(p['id'],hits)
  s=hits[0];assert s['func']==p['true_name'] and s['config']==p['cfg'],(p['id'],s)
  assert (ROOT/'build_ovl'/s['source']).resolve()==(ROOT/p['clean_source']).resolve()
  assert digest(ROOT/p['clean_source'])==p['clean_sha256']
  key=s['func']+(f'__{a:06X}' if sum(x['func']==s['func'] for x in segments)>1 else '')
  obj=directory/'build/obj'/(key+'.o');assert obj.is_file(),obj
  out.append(dict(id=p['id'],foff=p['foff'],size=n,func=s['func'],cfg=s['config'],source=p['clean_source'],source_sha256=digest(ROOT/p['clean_source']),native_object_sha256=digest(obj),target_sha256=p['target_sha256']))
 receipts=[]
 for rp in sorted((LANE/'scratch/final_gate').rglob('*.json')):
  doc=json.loads(rp.read_text());receipts.append(dict(file=str(rp.relative_to(LANE)),sha256=digest(rp),bytes=rp.stat().st_size,summary=doc.get('gate',doc.get('fingerprint','full receipt retained in ignored scratch; digest binds its unchanged bytes')) if isinstance(doc,dict) else dict(items=len(doc),type='list')))
 log=(LANE/'gate.log').read_text();assert 'MATCH' in log and not re.search(r'NO MATCH|ERROR|Traceback',log),log[-3000:]
 r=dict(windows=1,workers=4,gate_invocations=1,scope=(LANE/'touched_windows.txt').read_text().splitlines(),result='MATCH',manifest_sha256=digest(manifest),production_compiled_C_rows=out,raw_receipts=receipts,source_scores=json.loads((LANE/'evidence/scores.json').read_text()),negative_control=json.loads((LANE/'evidence/negative_control.json').read_text()),status_after=json.loads((LANE/'evidence/status_after.json').read_text()),source_debt=0,new_C_bytes=sum(p['size'] for p in ps),new_C_rows=len(ps),base=(ROOT/'SCRATCH_HEAD').read_text().strip(),graph=dict(file='ledger/splits/overlay_modules.build.json',sha256=digest(ROOT/'ledger/splits/overlay_modules.build.json'),delivery='regenerate; derived receipt exceeds 2 MB'))
 canonical=LANE/'scratch/final_gate/town_scene/receipt.json'
 assert (chr(47)+'home'+chr(47)) not in canonical.read_text()
 shutil.copyfile(canonical,LANE/'evidence/production_receipt.json')
 r['inputs_sha']=json.loads(canonical.read_text())['gate']['inputs_sha']
 dump(LANE/'evidence/final_gate.json',r)
 print('production exact C extents',len(out))

def report():
 ps=json.loads((LANE/'evidence/staged.json').read_text());h=list(csv.DictReader((LANE/'holds.tsv').open(),delimiter='\t'));reasons=collections.Counter();items=collections.Counter()
 for r in h:
  if r['queue']=='holds2':reasons[r['reason']]+=int(r['size']);items[r['reason']]+=1
 byreason='\n'.join(f'| {reason} | {items[reason]} | {n:,} |' for reason,n in reasons.most_common())
 body=f'''# r121w_heur3 — partial delivery against B13

Base: `{(ROOT/'SCRATCH_HEAD').read_text().strip()}`. **36 new C rows / 3,520 bytes**, all in TOWN. **One scoped production invocation, four workers, one window MATCH**. Canonical source scores: 36 exact, zero substitutions or indels. Genuine raw baselines: 36 compiling but different; all raw differences remain measured differences. No compiler, assembler, scorer, window, existing C source, source recipe or rowbase changes.

## Per-item status

| Item | Status | Delivery / remaining |
|---|---|---|
| Heuristic-only spans | Partial C delivery | 52,508 -> 48,988 B; 3,520 new C bytes |
| MAIN heuristic | Held | 3,924 B; no new C |
| TOWN heuristic | Partial | 13,464 -> 9,944 B; 36 new C rows |
| DUNGEON heuristic | Held after bounded donor replay | 35,120 B; no new C |
| Undecompiled split bucket | SDK classification reconciled | 1,396 -> 0 B in that bucket; library code rises by 1,396 B, C credit zero |
| SLUS other bucket | Audited, held | 204 B startup assembly; 24 B already declared data/padding in its historical 228 B bucket |
| Census handoffs | Audited, held | All 67 supplied records reconciled; 45 placed handoffs remain. The 84-B TOWN caller at 0x5c70c8 has an exact clean candidate but its true-address name is already used by another scene |
| Census next queue | Reconciled, held | 647 supplied records retained, including 16 terminal non-code aggregates; 18,954 residual positional bytes across the queue and repeated handoff holds |
| Prior heur holds | Partial | All 742 supplied records reconciled against B13 and this delivery; 48,988 B remain |

The queues overlap. Do not add their byte totals. `measure.tsv` covers the 337 original STATUS intervals and four SLUS pieces; `results.tsv` covers those plus every supplied TSV record. Each result partitions its own bytes into prior C, new C, SDK library, inherited non-code and held bytes. `holds.tsv` retains queue identity and exact residual extents. No data is promoted to C. No new non-code type is claimed.

## C behavior and proof

The new callbacks configure distinct slot/table/state values, copy global state, reset object handlers, update alternate menu bounds, arrange ten objects in columns and write alternate menu coordinates. Semantic constants and structure-member offsets differ from the existing donor bodies, so link-list rebinding cannot represent them. Each is a new home TU with its own genuine spimdisasm/m2c raw first pass and a snake_case function name. Existing donor text is unchanged. No copied relink or hand-copy source is modified or created.

Each new body has an independently matched C caller or an interior callback-table entry in its independently bounded proven load context. Existing donor declarations retain their interface. Aliased callee contexts require complete matched source/target callee bodies; their witnesses are in `evidence/staged.json`. Source and target instruction bodies are compared without admission masks. The final production manifest independently confirms that every one of the 36 exact extents is compiled from its registered source rather than supplied by raw fill.

The source scorer rejects a negative control that changes slot 28 to 29: one substitution, zero indels. All 36 clean source scores are zero; all 36 genuine raw first passes compile with differences. The raw files contain only the unchanged generator output behind the standard compatibility preamble. Baseline, promotion and reverify facts are appended; levels are left for ordinary integration policy.

## Classification correction

The 420 MAIN, 96 TOWN and 880 OVMOVIE split bytes were already identified as Sony SDK code in `docs/evidence/r121_remnants.sdk.json` and its report. The reporting path preferred historical raw splits, and then unported regions, over this library evidence. Five append-only coverage events reconcile 1,228 B from that existing evidence into the interval ledger. The other 168 B already had SDK intervals. STATUS now gives evidenced SDK intervals priority over raw split/unported views while retaining compiled-C/copy priority. The focused 10-test STATUS suite includes overlapping C, SDK, raw-split and unported witnesses. No SDK bytes are credited as C.

The SLUS 228-B bucket is 204 B at 0x101f8 plus three existing 8-B bin spans at 0x37e80, 0x39788 and 0x3d608. Those are two SDK header/data fragments and alignment padding; their declarations are preserved. This checkout has no complete linked SLUS executable proof, and no SLUS C or executable claim is made.

## Deliveries

- `delivery.patch`: text delta against B13, including the 36 source/raw pairs, append-only ledgers, names, SDK reporting correction and compact evidence under docs/evidence/r121w_heur3. No binaries or retail payloads.
- `measure.tsv`, `results.tsv`, `holds.tsv`, `touched_windows.txt`, `gate.log`, this report, `levels_seed_needed.tsv`.
- `evidence/final_gate.json`: exact production extents and source/object/target hashes, normal source/raw scores and the semantic negative control. `evidence/verification.json`: source debt, ledger prefixes and patch reconstruction.
- `evidence/discovery_summary.json`: summary plus SHA-256 of the large ignored donor-discovery receipt; masked leads remain discovery only. `evidence/large_entry_audit.json` records seven omitted eight-byte prefixes. All multi-megabyte receipts remain under ignored scratch or are regenerated.
- `scripts/`: bounded survey, native replay, semantic/layout reconstruction, staging, raw measurement, classification and packaging recipes. Discovery inputs are frozen; do not rerun the original inventory on the delivered tree.

The sole touched production config is `config/overlays/town_scene.overlay.yaml`. The source projection, row database and module graph are refreshed. The large derived graph is excluded from the patch and must be regenerated. Source/row/module identity tools and production gate implementations are unchanged. No module ownership or L4/L5 certificate is manufactured.

## Holds by reason

This table partitions the remaining original heuristic hold queue (48,988 B); the census and SLUS queues remain separate.

| Reason | Pieces | Bytes |
|---|---:|---:|
{byreason}

Census placed handoffs still require complete clean C and actual entry/placement evidence. Seven 1,144-B DUNGEON detector starts omit an eight-byte load-before-prologue prefix; the complete candidates are 1,152 B and cannot be registered at the detector starts. Two 468-B handoffs have current clean donor leads but their leading extents lack a proven production rowbase. Tiny return tails are not minted as functions. No version-wall, data or leftover verdict is inferred from these holds.

## HOW TO CONTINUE

1. Apply `delivery.patch` at the recorded B13 contents. Run `bash tools/build/mk_ovl_root.sh`, `python3 tools/row_db.py export build_ovl`, and `python3 tools/row_db.py check`. Regenerate the module graph and derive the 36 levels listed in `levels_seed_needed.tsv` under integration policy. Re-gate the listed window if any bound inputs change during integration.
2. Freeze a new incremental base before more admissions. Use the remaining `holds2` rows in `holds.tsv` as the physical heuristic partition; census queues overlap it and each other. Do not rerun `survey.py` on a changed tree to replace the original inventory. Regenerate discovery from the corresponding base or retain the ignored scratch receipt, whose digest is delivered.
3. Largest remaining families: the 1,420/1,400-B volatile donors need a natural source lifetime/scheduling repair; the 724/708-B animation families need genuine symbolic relocations. Preserve existing exact homes and the prior reports. A native relocation hit is insufficient where even one differing word lacks an ELF relocation.
4. For the seven large census handoffs, start eight bytes before the detector entry as recorded in `large_entry_audit.json`. Recover the complete renderer C and its typed scratchpad/callee contracts, prove the entry, then register the entire 1,152-B extent. The two 468-B initializer copies need independently evidenced leading rowbase records and normal solved-to-proven promotion before link-list admission.
5. For the exact 84-B candidate at TOWN 0x5c70c8, resolve region-specific readable naming without changing the existing unrelated scene's alias. The candidate is reproducible with `variants.py`; keep it held until its definition can retain both correct semantics and the required production identity. Other small entries still need independent callers or bounded callback tables.
6. Preserve genuine raw generator output and actual failing baseline measurements. Require exact canonical source scores, compiled extent ownership and a single final gate with four workers over the new touched-window closure. Continue SDK/data typing from the existing evidence without calling it C. SLUS startup requires the complete ordinary executable link/SHA1 proof.
7. `package.py` rebuilds the text patch using local frozen before-images and reconstructs every file in an ignored check tree. A fresh checkout can apply and gate the delivered change; re-emitting the exact original patch also requires those ignored B13 before-images. The held donor caches and binaries are intentionally not distributed.
'''
 (LANE/'REPORT.md').write_text(body)


def package():
 base=json.loads((LANE/'scratch/base_manifest.json').read_text());ps=json.loads((LANE/'evidence/staged.json').read_text());changed={}
 for p in (LANE/'scratch/preimage').rglob('*'):
  if p.is_file():
   rel=str(p.relative_to(LANE/'scratch/preimage'));assert digest(p)==base[rel],rel
   if p.read_bytes()!=(ROOT/rel).read_bytes():changed[rel]=p.read_text()
 for p in ps:
  for key in ['clean_source','raw_source']:
   rel=p[key];assert rel not in base;changed[rel]=''
 # All lane documents are new at B13. Runtime logs, objects and scratch stay local.
 names=['BRIEF.md','REPORT.md','inventory.tsv','measure.tsv','results.tsv','holds.tsv','levels_seed_needed.tsv','touched_windows.txt','gate.log']
 names += [str(p.relative_to(LANE)) for d in ['scripts','refs','evidence'] for p in (LANE/d).glob('*') if p.is_file() and p.suffix in ('.py','.json','.md','.tsv','.log') and p.name not in ['verification.json','facts_appended.json','input_reconciliation.json']]
 docroot=ROOT/'docs/evidence/r121w_heur3';docroot.mkdir(parents=True,exist_ok=True)
 shutil.copyfile(LANE/'evidence/final_gate.json',docroot/'receipts.json');changed[str((docroot/'receipts.json').relative_to(ROOT))]=''
 for n in names:
  p=LANE/n
  if p.stat().st_size>2_000_000:raise ValueError('oversized receipt '+n)
  destination=docroot/n;destination.parent.mkdir(parents=True,exist_ok=True)
  destination.write_text(p.read_text())
  changed[str(destination.relative_to(ROOT))]=''
 # Keep the package reconstruction receipt outside the patch to avoid a hash cycle.
 manifest=[];patch=[]
 for rel,before in sorted(changed.items()):
  p=ROOT/rel;after=p.read_text();assert '\x00' not in after,rel
  if not before:assert (chr(47)+'home'+chr(47)) not in after,rel
  if before==after:continue
  if before:assert (LANE/'scratch/preimage'/rel).read_text()==before
  piece=list(difflib.unified_diff(before.splitlines(True),after.splitlines(True),fromfile='a/'+rel if before else '/dev/null',tofile='b/'+rel,n=3))
  if any((chr(47)+'home'+chr(47)) in line for line in piece):
   piece=list(difflib.unified_diff(before.splitlines(True),after.splitlines(True),fromfile='a/'+rel if before else '/dev/null',tofile='b/'+rel,n=0))
  assert not any((chr(47)+'home'+chr(47)) in line for line in piece),rel
  patch.extend(piece)
  manifest.append(dict(path=rel,before_sha256=hashlib.sha256(before.encode()).hexdigest() if before else None,after_sha256=digest(p),bytes=p.stat().st_size))
 target=LANE/'delivery.patch';target.write_text(''.join(patch));check=LANE/'scratch/patch_check'
 if check.exists():shutil.rmtree(check)
 check.mkdir()
 for r in manifest:
  if r['before_sha256']:
   p=check/r['path'];p.parent.mkdir(parents=True,exist_ok=True);shutil.copyfile(LANE/'scratch/preimage'/r['path'],p)
 proc=subprocess.run(['patch','-s','-p1','--batch','-i',str(target)],cwd=check,capture_output=True,text=True)
 assert proc.returncode==0,proc.stdout+proc.stderr
 assert all(digest(check/r['path'])==r['after_sha256'] for r in manifest)
 # No existing home source changed; all append-only authoritative ledgers retain B13 prefixes.
 for rel in changed:
  if rel.startswith(('src/','raw/')):assert rel not in base
 for rel in ['ledger/rows.jsonl','ledger/splits/town.jsonl','ledger/coverage_regions.jsonl','ledger/baseline.jsonl','ledger/promotions.jsonl','ledger/reverify.jsonl']:
  original=(LANE/'scratch/preimage'/rel).read_bytes();assert (ROOT/rel).read_bytes().startswith(original),rel
 for p in ps:
  source=(ROOT/p['clean_source']).read_text();s=re.sub(r'/\*.*?\*/|//[^\n]*','',source,flags=re.S)
  assert not re.search(r'\b(?:volatile|goto|NON_MATCHING)\b|\b(?:asm|__asm__)\s*\(|#\s*pragma|ASM_(?:KEEP|REG|USE|SET)',s),p['id']
  assert re.search(r'void\s+'+p['alias']+r'\s*\(',s)
  raw=(ROOT/p['raw_source']).read_text();assert raw=='#include "common.h"\n#include "m2c_compat.h"\n\n'+(LANE/p['raw']).with_name('m2c_stdout.c').read_text()
 v=dict(base=(ROOT/'SCRATCH_HEAD').read_text().strip(),patch_sha256=digest(target),patch_bytes=target.stat().st_size,files=len(manifest),reconstruction='PASS',new_C_rows=len(ps),new_C_bytes=sum(p['size'] for p in ps),ledger_prefixes='PASS',source_debt='zero',existing_src_raw_changed=0,binary_payloads=0,absolute_home_paths=0,files_manifest=manifest)
 dump(LANE/'evidence/verification.json',v);dump(LANE/'delivery_manifest.json',dict(base=v['base'],patch_sha256=v['patch_sha256'],files=manifest))
 print('PATCH',v['files'],'files',v['patch_bytes'],'bytes',v['patch_sha256'],'reconstructed exactly')

if __name__=='__main__':
 if sys.argv[1]=='proof':proof()
 elif sys.argv[1]=='report':report()
 elif sys.argv[1]=='patch':package()
