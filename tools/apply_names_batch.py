"""Atomic naming batch: one alias-table update, one SLUS gate, each touched row once."""
import json,re,time,subprocess,concurrent.futures
from pathlib import Path
from source_layout import row_path, own_source, row_ids_for_paths
from layout_dependencies import consumer_paths
from apply_names_data import inline_plan

def rewrite(text,pattern,mapping,code_only=False):
 if code_only:
  tokens=re.compile(r"/\*.*?\*/|//[^\n]*|\"(?:\\.|[^\"\\])*\"|'(?:\\.|[^'\\])*'|"+pattern.pattern,re.S)
  return tokens.sub(lambda m:mapping.get(m[0],m[0]),text)
 # Function file stems stay stable, including module-wrapper include strings.
 return ''.join(line if re.match(r'\s*#\s*include\b',line) else pattern.sub(lambda m:mapping[m[0]],line) for line in text.splitlines(keepends=True))

def scoped_rewrites(root,texts,mapping,scope_map):
 """Restrict reused overlay spellings without changing their canonical assembly names."""
 if not isinstance(scope_map,dict) or set(scope_map)!=set(mapping):raise ValueError('scope map must cover exactly the proposed symbols')
 per_path={}
 for old,paths in scope_map.items():
  if not isinstance(paths,list) or not paths:raise ValueError('empty scope: '+old)
  for rel in paths:
   p=Path(rel)
   if p.is_absolute() or not p.parts or '..' in p.parts or p.parts[0] not in ('src','include'):
    raise ValueError('scope must be a repository source/header path: '+str(rel))
   p=root/p
   if p not in texts:raise ValueError('scope path is not a loaded source/header: '+str(rel))
   per_path.setdefault(p,{})[old]=mapping[old]
 changed={}
 for p,local in per_path.items():
  pat=re.compile(r'\b(?:'+'|'.join(map(re.escape,local))+r')\b')
  fresh=rewrite(texts[p],pat,local,True)
  if fresh!=texts[p]:changed[p]=fresh
 return changed,per_path

def validate_renamed_alias_consumers(root,texts,renames,scopes):
 """A global alias replacement must retain every existing readable consumer."""
 for old,(previous,name) in renames.items():
  allowed={root/rel for rel in scopes.get(old,[])}
  pat=re.compile(r'\b'+re.escape(previous)+r'\b')
  outside=[p.relative_to(root).as_posix() for p,t in texts.items()
           if p not in allowed and pat.search(t) and rewrite(t,pat,{previous:name},True)!=t]
  if outside:raise ValueError('scoped alias rename leaves existing readable consumers outside scope: '+previous+': '+','.join(sorted(outside)))

def reference_mappings(root, texts, mapping, path):
 """Bind explicit sites without conflating symbols in separately linked overlays."""
 sites=json.loads(Path(path).read_text())
 if not isinstance(sites,dict) or set(sites)!=set(mapping):
  raise ValueError('reference map must cover exactly the proposed symbols')
 per_file={}
 for old,paths in sites.items():
  if not isinstance(paths,list) or not paths or any(not isinstance(p,str) for p in paths):
   raise ValueError('reference map needs nonempty path lists: '+old)
  for rel in paths:
   p=Path(rel)
   if not p.parts or p.is_absolute() or '..' in p.parts or p.as_posix()!=rel or p.parts[0] not in ('src','include'):
    raise ValueError('invalid reference path: '+rel)
   p=root/p
   if p not in texts or p.is_symlink():raise ValueError('unknown reference source: '+rel)
   per_file.setdefault(p,{})[old]=mapping[old]
 return per_file

def main(a,N):
 if a.data or a.rewrite:raise ValueError('--batch currently supports function aliases only')
 identities=json.loads(a.identity_map.read_text()) if a.identity_map else {}
 proposed=[]
 for raw in Path(a.tsv).read_text().splitlines():
  cols=[c.strip() for c in raw.split('#',1)[0].rstrip().split('\t')]
  if len(cols)>=4 and cols[1]:proposed.append(cols[:4])
 scope_path=getattr(a,'scope_map',None) or getattr(a,'symbol_scope_map',None)
 scopes=json.loads(scope_path.read_text()) if scope_path else {}
 if not isinstance(scopes,dict) or set(scopes)-{r[1] for r in proposed}:raise ValueError('symbol scope does not name a proposal')
 for paths in scopes.values():
  if not isinstance(paths,list) or not paths or not all(isinstance(p,str) for p in paths):raise ValueError('symbol scope must contain relative rewrite paths')
  N.scoped_texts({},paths,N.ROOT)
 if a.only:proposed=[p for p in proposed if p[1] in set(a.only.split(','))]
 if a.limit:proposed=proposed[:a.limit]
 rs=N.rows();by_id={r['id']:r for r in rs};by_file={row_path(r,N.ROOT):r for r in rs}
 defined={}
 for r in rs:
  for name in {r.get('func'),r.get('true_name')}|set(r.get('defs') or []):
   if name:defined[name]=r
 texts,idents=N.load_tree()
 for p in (N.ROOT/'include').rglob('*.h'):texts[p]=p.read_text()
 for p in sorted((N.ROOT/'src').rglob('*')):
  if p.suffix in('.c','.h') and p not in texts and p.is_file():texts[p]=p.read_text()
 if any(p.is_symlink() or p.stat().st_size>4*1024*1024 for p in texts):raise ValueError('source symlink or oversized source')
 texts=N.scoped_texts(texts,getattr(a,'path_prefix',[]),N.ROOT)
 applied={r[1]:r[2] for r in N.read_names()};taken=set(applied.values());plan=[];mapping={};new=[];renames={};rewrite_scopes={}
 for addr,old,name,evidence in proposed:
  proposal_old=old;paths=scopes.get(proposal_old)
  rec=dict(addr=addr,old=old,new=name,at=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime()))
  identity=identities.get(name) or identities.get(old)
  if identity:
   r=by_id.get(identity.get('row'));symbol=identity.get('symbol','');p=row_path(r,N.ROOT) if r else None
   pat=r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t*]*?\b'+re.escape(symbol)+r'\s*\([^;{]*\)[^{;]*\{'
   if not re.fullmatch(r'func_[0-9A-Fa-f]{8}',symbol) or p not in texts:raise ValueError('invalid explicit identity: '+old)
   if paths and p not in N.scoped_texts({p:texts[p]},paths,N.ROOT):raise ValueError('symbol scope excludes its definition: '+old)
   # An already-renamed definition is valid only under that exact configured alias.
   current=applied.get(symbol,symbol)
   source=own_source(r,N.ROOT)[0]
   current_definition=re.search(pat.replace(re.escape(symbol),re.escape(current)),source,re.M)
   # Merged exports can retain the address spelling after the alias was configured.
   # Only replaying that exact existing alias may normalize such a definition.
   legacy_definition=(applied.get(symbol)==name or getattr(a,'scope_map',None)) and re.search(pat,source,re.M)
   if not (current_definition or legacy_definition):raise ValueError('identity does not name a current definition: '+old)
   if getattr(a,'scope_map',None) and (not paths or p.relative_to(N.ROOT).as_posix() not in paths):raise ValueError('scope omits the defining source: '+old)
   old=symbol;rec['identity_row']=r['id']
  elif old in defined and old not in applied:
   r=defined[old];old=r.get('true_name') or r.get('func') or old
  addr='0x'+old[5:];rec.update(old=old,addr=addr)
  if old in applied:
   if applied[old]!=name:
    if not getattr(a,'rename_existing',False):raise ValueError('alias identity conflict: '+old+' -> '+applied[old]+' vs '+name)
    if not N.IDENT.fullmatch(name) or name.startswith('func_') or name in idents or name in taken:raise ValueError('name collision or invalid identifier: '+name)
    renames[old]=(applied[old],name);mapping[applied[old]]=name;taken.discard(applied[old]);taken.add(name)
    if getattr(a,'scope_map',None):mapping[old]=name;rewrite_scopes[old]=paths
    rec.update(renamed_from=applied[old],rename=True);applied[old]=name
   rec['existing']=True
  else:
   if not N.IDENT.fullmatch(name) or name.startswith('func_') or name in idents or name in taken:raise ValueError('name collision or invalid identifier: '+name)
   if old not in defined and not identity:raise ValueError('no defining row: '+old)
   new.append((addr,old,name,evidence));taken.add(name);applied[old]=name;rec['existing']=False
  if not rec.get('rename'):
   if old in mapping and mapping[old]!=name:raise ValueError('conflicting aliases: '+old)
   mapping[old]=name
  if paths:
   key=rec.get('renamed_from',old)
   if key in rewrite_scopes and rewrite_scopes[key]!=paths:raise ValueError('conflicting symbol scopes: '+old)
   rewrite_scopes[key]=paths;rec['rewrite_paths']=paths
  plan.append(rec)
 if getattr(a,'scope_map',None):
  for rec in plan:
   if not (identities.get(rec['new']) or identities.get(rec['old'])):raise ValueError('scoped alias requires an explicit definition identity: '+rec['old'])
  validate_renamed_alias_consumers(N.ROOT,texts,renames,scopes)
 pattern=re.compile(r'\b(?:'+'|'.join(map(re.escape,mapping))+r')\b')
 held={row_path(r,N.ROOT):r for r in rs if a.hold_unproven_references and r.get('placement')=='unproven'}
 holds=[dict(row=r['id'],path=str(p.relative_to(N.ROOT)),aliases=sorted(set(pattern.findall(texts[p]))),reason='pre-existing placement-unproven source; preserve legacy alias references') for p,r in held.items() if p in texts and pattern.search(texts[p])]
 for p in held:
  if p in texts:
   for old in set(pattern.findall(texts[p])):
    if re.search(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t*]*?\b'+re.escape(old)+r'\s*\([^;{]*\)[^{;]*\{',texts[p],re.M):raise ValueError('cannot alias an excluded definition: '+old)
 if a.holds_log:Path(a.holds_log).write_text(json.dumps(holds,indent=1)+'\n')
 sites=getattr(a,'reference_map',None)
 if sites:
  per_file=reference_mappings(N.ROOT,texts,mapping,sites)
  ref_scopes=json.loads(Path(sites).read_text())
  for rec in plan:
   symbol=rec.get('renamed_from') or rec['old']
   if not rec['existing'] and not any(p in per_file and symbol in per_file[p] and re.search(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t*]*?\b'+re.escape(symbol)+r'\s*\([^;{]*\)\s*\{',t,re.M) for p,t in texts.items()):raise ValueError('reference map omits the definition: '+symbol)
  rewrite_scopes.update(ref_scopes)
 allowed_paths={old:set(N.scoped_texts(texts,paths,N.ROOT)) for old,paths in rewrite_scopes.items()}
 changed={};file_rules={};rule_cache={}
 for p,t in texts.items():
  if p in held:continue
  keys=tuple(old for old in mapping if old not in allowed_paths or p in allowed_paths[old])
  if not keys:continue
  if keys not in rule_cache:
   local={old:mapping[old] for old in keys};rule_cache[keys]=(re.compile(r'\b(?:'+'|'.join(map(re.escape,keys))+r')\b'),local)
  local_pattern,local_mapping=rule_cache[keys]
  if local_pattern.search(t):
   current=rewrite(t,local_pattern,local_mapping,True)
   if current!=t:changed[p]=current;file_rules[p.relative_to(N.ROOT).as_posix()]=(local_pattern,local_mapping)
 if not changed and not new and not renames:
  deferred=getattr(a,'defer_verification',False)
  print('batch: 0 new aliases, 0 files, 0 rows'+('; UNVERIFIED staging' if deferred else ''),flush=True)
  receipt=dict(status='UNVERIFIED' if deferred else 'UNCHANGED',new_aliases=0,files=[],rows=[],map=mapping,inline_rebases=[])
  if not a.dry_run and a.proof_log:Path(a.proof_log).write_text(json.dumps(receipt,indent=2)+'\n')
  return receipt
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
 affected=consumer_paths(N.ROOT,{p.relative_to(N.ROOT).as_posix() for p in changed})
 touched_rows.update(row_ids_for_paths(affected,N.ROOT))
 metadata,rebases=inline_plan(N.ROOT,texts,changed,pattern,mapping,file_rules=file_rules) if rewrite_scopes else inline_plan(N.ROOT,texts,changed,pattern,mapping)
 # A changed wrapper affects every registered member in that physical TU.
 module_file=N.ROOT/'config/overlays/modules.json'
 if module_file.exists():
  for m in json.loads(module_file.read_text()).get('modules',[]):
   if N.ROOT/m['source'] in changed:touched_rows.update(x['id'] for x in m['members'])
 deferred=getattr(a,'defer_verification',False)
 print(f"batch: {len(new)} new aliases, {len(changed)} files, {len(touched_rows)} rows"+('; UNVERIFIED staging' if deferred else ''),flush=True)
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
  for p,pair in metadata.items():p.write_bytes(pair[1])
  written=True
  if deferred:
   receipt=dict(status='UNVERIFIED',new_aliases=len(new),files=[str(p.relative_to(N.ROOT)) for p in changed],
                rows=sorted(touched_rows),map=mapping,inline_rebases=rebases,
                required='independent complete-TU object identity, SLUS SHA-1 and scoped overlay gates')
   if a.proof_log:Path(a.proof_log).write_text(json.dumps(receipt,indent=2)+'\n')
   for rec in plan:
    if not rec['existing'] or changed:N.append_jsonl(N.JOURNAL,dict(rec,outcome='staged-unverified',batch=True))
   return receipt
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
   for p,pair in metadata.items():p.write_bytes(pair[0])
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
