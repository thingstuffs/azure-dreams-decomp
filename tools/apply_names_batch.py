"""Atomic naming batch: one alias-table update, one SLUS gate, each touched row once."""
import json,re,time,subprocess,concurrent.futures
from pathlib import Path

def rewrite(text,pattern,mapping,code_only=False):
 if code_only:
  tokens=re.compile(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'|"+pattern.pattern,re.S)
  return tokens.sub(lambda m:mapping.get(m[0],m[0]),text)
 # Function file stems stay stable, including module-wrapper include strings.
 return ''.join(line if re.match(r'\s*#\s*include\b',line) else pattern.sub(lambda m:mapping[m[0]],line) for line in text.splitlines(keepends=True))

def main(a,N):
 if a.data or a.rewrite:raise ValueError('--batch currently supports function aliases only')
 identities=json.loads(a.identity_map.read_text()) if a.identity_map else {}
 proposed=[]
 for raw in Path(a.tsv).read_text().splitlines():
  cols=[c.strip() for c in raw.split('#',1)[0].rstrip().split('\t')]
  if len(cols)>=4 and cols[1]:proposed.append(cols[:4])
 if a.only:proposed=[p for p in proposed if p[1] in set(a.only.split(','))]
 if a.limit:proposed=proposed[:a.limit]
 rs=N.rows();by_id={r['id']:r for r in rs};by_file={N.ROOT/'src'/r['container']/Path(r['c_path']).name:r for r in rs}
 defined={}
 for r in rs:
  for name in {r.get('func'),r.get('true_name')}|set(r.get('defs') or []):
   if name:defined[name]=r
 texts,idents=N.load_tree()
 for p in (N.ROOT/'include').rglob('*.h'):texts[p]=p.read_text()
 for c in N.CONTAINERS:
  for p in sorted((N.ROOT/'src'/c).rglob('*')):
   if p.suffix in('.c','.h') and p not in texts and p.is_file():texts[p]=p.read_text()  # modules, native_candidates, ... included by wrappers
 applied={r[1]:r[2] for r in N.read_names()};taken=set(applied.values());plan=[];mapping={};new=[];renames={}
 for addr,old,name,evidence in proposed:
  rec=dict(addr=addr,old=old,new=name,at=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()))
  identity=identities.get(name) or identities.get(old)
  if identity:
   r=by_id.get(identity.get('row'));symbol=identity.get('symbol','');p=N.ROOT/'src'/r['container']/Path(r['c_path']).name if r else None
   pat=r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t*]*?\b'+re.escape(symbol)+r'\s*\([^;{]*\)[^{;]*\{'
   if not re.fullmatch(r'func_[0-9A-Fa-f]{8}',symbol) or p not in texts:raise ValueError('invalid explicit identity: '+old)
   # An already-renamed definition is valid only under that exact configured alias.
   current=applied.get(symbol,symbol)
   if not re.search(pat.replace(re.escape(symbol),re.escape(current)),texts[p],re.M):raise ValueError('identity does not name a current definition: '+old)
   old=symbol;rec['identity_row']=r['id']
  elif old in defined and old not in applied:
   r=defined[old];old=r.get('true_name') or r.get('func') or old
  addr='0x'+old[5:];rec.update(old=old,addr=addr)
  if old in applied:
   if applied[old]!=name:
    if not getattr(a,'rename_existing',False):raise ValueError('alias identity conflict: '+old+' -> '+applied[old]+' vs '+name)
    if not N.IDENT.fullmatch(name) or name.startswith('func_') or name in idents or name in taken:raise ValueError('name collision or invalid identifier: '+name)
    renames[old]=(applied[old],name);mapping[applied[old]]=name;taken.discard(applied[old]);taken.add(name)
    rec.update(renamed_from=applied[old],rename=True);applied[old]=name
   rec['existing']=True
  else:
   if not N.IDENT.fullmatch(name) or name.startswith('func_') or name in idents or name in taken:raise ValueError('name collision or invalid identifier: '+name)
   if old not in defined and not identity:raise ValueError('no defining row: '+old)
   new.append((addr,old,name,evidence));taken.add(name);applied[old]=name;rec['existing']=False
  if not rec.get('rename'):
   if old in mapping and mapping[old]!=name:raise ValueError('conflicting aliases: '+old)
   mapping[old]=name
  plan.append(rec)
 pattern=re.compile(r'\b(?:'+'|'.join(map(re.escape,mapping))+r')\b')
 held={N.ROOT/'src'/r['container']/Path(r['c_path']).name:r for r in rs if a.hold_unproven_references and r.get('placement')=='unproven'}
 holds=[dict(row=r['id'],path=str(p.relative_to(N.ROOT)),aliases=sorted(set(pattern.findall(texts[p]))),reason='pre-existing placement-unproven source; preserve legacy alias references') for p,r in held.items() if p in texts and pattern.search(texts[p])]
 for p in held:
  if p in texts:
   for old in set(pattern.findall(texts[p])):
    if re.search(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t*]*?\b'+re.escape(old)+r'\s*\([^;{]*\)[^{;]*\{',texts[p],re.M):raise ValueError('cannot alias an excluded definition: '+old)
 if a.holds_log:Path(a.holds_log).write_text(json.dumps(holds,indent=1)+'\n')
 changed={p:rewrite(t,pattern,mapping,p.suffix=='.h' or p not in by_file) for p,t in texts.items() if p not in held and pattern.search(t)}
 changed={p:t for p,t in changed.items() if t!=texts[p]}
 # Include transitive users of rewritten headers; all per-row C keeps its own declarations.
 inc=re.compile(r'^\s*#\s*include\s*["<]([^">]+)[">]',re.M);headers={p for p in texts if p.suffix=='.h' or p not in by_file}
 def closure(p,seen=None):
  seen=set() if seen is None else seen
  for h in inc.findall(texts[p]):
   q=p.parent/h
   if q not in headers:q=N.ROOT/'include'/h
   if q in headers and q not in seen:seen.add(q);closure(q,seen)
  return seen
 dependencies={p:closure(p) for p in by_file if p in texts}
 changed_headers=set(changed)&headers
 touched_rows={r['id'] for p,r in by_file.items() if p in changed or dependencies.get(p,set())&changed_headers}
 # A changed wrapper affects every registered member in that physical TU.
 module_file=N.ROOT/'config/overlays/modules.json'
 if module_file.exists():
  for m in json.loads(module_file.read_text()).get('modules',[]):
   if N.ROOT/m['source'] in changed:touched_rows.update(x['id'] for x in m['members'])
 print(f"batch: {len(new)} new aliases, {len(changed)} files, {len(touched_rows)} rows",flush=True)
 if a.dry_run:return
 if a.proof_log:Path(a.proof_log).write_text('')
 names_before=N.NAMES.read_text();written=False;bad=[];proofs=[]
 try:
  written=True
  lines=[]
  for ln in names_before.splitlines():
   c=ln.split('\t')
   if len(c)>=3 and c[1] in renames and c[2]==renames[c[1]][0]:c[2]=renames[c[1]][1];ln='\t'.join(c)
   lines.append(ln)
  N.NAMES.write_text('\n'.join(lines).rstrip('\n')+'\n'+''.join('\t'.join(x)+'\n' for x in new))
  for p,t in changed.items():p.write_text(t)
  written=True
  if any(p.parts[-2]=='slus' and p.suffix=='.c' for p in changed):
   gate=subprocess.run(['bash',str(N.ROOT/'tools/build/build_slus.sh'),'-j',str(a.workers)],cwd=N.ROOT,capture_output=True,text=True)
   print(gate.stdout[-3000:],flush=True)
   if gate.returncode:raise ValueError('batch SLUS SHA-1 gate failed: '+gate.stderr[-1000:])
  from verify_batch import measure,context
  reused={}
  if a.resume_proof:
   if not a.resume_context or json.loads(a.resume_context.read_text())['sha256']!=context(N.ROOT):raise ValueError('resume proof source/build context drift')
   for line in a.resume_proof.read_text().splitlines():
    rec=json.loads(line)
    if rec['result'].get('exact') is True and rec['id'] in touched_rows:reused[rec['id']]=rec['result']
  print('batch resumed receipts',len(reused),flush=True)
  def all_results():
   yield from reused.items()
   yield from measure([by_id[rid] for rid in sorted(touched_rows) if rid not in reused],a.workers,N.verify,N.ROOT)
  for i,(rid,v) in enumerate(all_results(),1):
   record=dict(id=rid,result=v);proofs.append(record)
   if a.proof_log:N.append_jsonl(Path(a.proof_log),record)
   if v.get('exact') is not True:bad.append((rid,v));print('not exact:',rid,v,flush=True)
   if i%50==0:print('batch verify',i,'/',len(touched_rows),'bad',len(bad),flush=True)
  if bad and getattr(a,'bad_report',None):
   Path(a.bad_report).write_text(json.dumps([dict(id=i,result=v) for i,v in bad],indent=1)+'\n');print('bad rows reported (caller must show them to be failing at the base too):',len(bad),flush=True)
  elif bad:raise ValueError(str(len(bad))+' touched rows not exact')
  if any(p.read_text()!=t for p,t in changed.items()):raise ValueError('source inputs changed during batch')
 except BaseException:
  if written:
   for p in changed:p.write_text(texts[p])
  N.NAMES.write_text(names_before)
  for rec in plan:
   if not rec['existing'] or rec.get('rename'):N.append_jsonl(N.JOURNAL,dict(rec,outcome='reverted',reason='atomic batch failed',failures=[(rid,v.get('status'),v.get('class'),v.get('total'),v.get('err')) for rid,v in bad[:5]]))
  raise
 for rec in plan:
  old=rec.get('renamed_from') or rec['old'];pat=re.compile(r'\b'+re.escape(old)+r'\b')
  direct={p for p in changed if pat.search(texts[p])};h=direct&headers
  ids={r['id'] for p,r in by_file.items() if p in direct or h and dependencies.get(p,set())&h}
  if not rec['existing'] or direct:
   rec.update(files=len(direct),rows=sorted(ids),outcome='renamed' if rec.get('rename') else 'references-rewritten' if rec['existing'] else 'applied',batch=True)
   rec.pop('existing');rec.pop('rename',None);N.append_jsonl(N.JOURNAL,rec)
 print('batch applied:',len(new),'new aliases;',len(touched_rows),'rows exact',flush=True)
