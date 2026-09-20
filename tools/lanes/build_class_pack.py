"""Build a class-grouped, exemplar-briefed model pack with the round-60 residue screen (moved from the session scratchpad; inputs in ledger/pack_inputs/).
    python3 tools/lanes/build_class_pack.py <lane> <L0 class,class> [n] --pins A-B --exemplars N [--solved "N of M rows"] [--dry-run]  python3 build_pack.py <lane> <class,class> [n] [--solved 'N of M rows']"""
import json, sys, difflib, shutil, glob; sys.path.insert(0,'tools'); sys.path.insert(0,'tools/xform'); sys.path.insert(0,'tools/lanes')
from pathlib import Path
from common import rows, clean_path, sha_text
from pin_census import sites_of
from pin_sites import erase_many
import screen
S='ledger/pack_inputs'; MY=S
lane=sys.argv[1]; classes=set(sys.argv[2].split(',')); n=int(sys.argv[3]) if len(sys.argv)>3 and not sys.argv[3].startswith('--') else 12
solved=sys.argv[sys.argv.index('--solved')+1] if '--solved' in sys.argv else None
pr=sys.argv[sys.argv.index('--pins')+1] if '--pins' in sys.argv else '1-2'
pmin,pmax=(int(pr.split('-')[0]),int(pr.split('-')[-1]))
nex=int(sys.argv[sys.argv.index('--exemplars')+1]) if '--exemplars' in sys.argv else 0
by={r['id']:r for r in rows()}
census=[json.loads(l) for l in open(f'{S}/erase_r56.jsonl')]
cls={}; dmax={}; ccls={}
for r in census:
    cls.setdefault(r['id'], r['fp'].get('L0')); dmax[r['id']]=max(dmax.get(r['id'],0), r['fp'].get('d',0)); ccls.setdefault(r['id'], r['fp'].get('cls'))
def screened(rid, r):
    # 2026-09-20 calibration over 235 served sol rows: RECOLOURED with erase distance >= 0.3 x instruction count = 18 served, 0 solved
    return ccls.get(rid)=='RECOLOURED' and r['size'] and dmax.get(rid,0)/(r['size']//4 or 1) >= 0.3
screened_out=0
served=set()
for f in glob.glob('work/native_lane/r[56]*_*/rows.md'):
    for l in open(f):
        if l.startswith('## '): served.add(l[3:].strip())
cand=[]
for rid,r in by.items():
    if r['container'] in ('slus','ovmovie') or rid in served or not clean_path(r).exists(): continue
    t=clean_path(r).read_text(errors='replace'); k=len(sites_of(t))
    if pmin<=k<=pmax and cls.get(rid) in classes:
        if screened(rid, r): screened_out+=1; continue
        cand.append((k,len(t.splitlines()),rid))
cand.sort(); ids=[c[2] for c in cand[:n]]
if '--dry-run' in sys.argv:
    print('pool', len(cand), 'screened out', screened_out, 'first', ids[:n]); sys.exit(0)
L=Path('work/native_lane')/lane; shutil.rmtree(L, ignore_errors=True); (L/'out').mkdir(parents=True); (L/'.ignore').write_text('*\n')
md=["# Rows (the residue is the cc1 listing diff of erasing every pin; retail order = the pinned listing)\n"]
for rid in ids:
    r=by[rid]; t=clean_path(r).read_text(errors='replace'); c,nm=rid.split('/')
    (L/'base'/c).mkdir(parents=True, exist_ok=True); (L/'base'/c/(nm+'.c')).write_text(t); (L/'base'/c/(nm+'.c.base_sha')).write_text(sha_text(t)+'\n')
    sites=sites_of(t); e=erase_many(t,sites,clean_notes=True); la=screen.compile_s(r,t); lb=screen.compile_s(r,e)
    d='\n'.join(x for x in difflib.unified_diff(la,lb,lineterm='',n=4) if not x.startswith(('---','+++'))) if la and lb else '(no listing)'
    md.append(f"\n## {rid}\n- recipe `{r['cfg']}`, {len(t.splitlines())} lines, {len(sites)} pin(s): "+'; '.join(f"`{s[1]}({s[2]})` at line {s[5]}" for s in sites)+f"; erase-census class {cls.get(rid)}\n- cc1 listing, pinned -> every pin erased:\n```\n"+d+"\n```\n")
(L/'rows.md').write_text(''.join(md))
b=open('work/native_lane/r58_order5/BRIEF.md').read().replace('r58_order5',lane)
if solved: b=b.replace('solved thirteen of 36 rows', 'solved '+solved)
if nex:
    exs=json.load(open(f'{S}/solved_exemplars.json'))
    want={c.split('|')[0]+'|'+c.split('|')[1] for c in classes}
    pick=sorted([e for e in exs if set(e['L0'])&want], key=lambda e:(len(e['diff']), -(e['pins'][0]-e['pins'][1])))[:nex]
    em=["# Solved exemplars of this pack's residue classes (this week's landed rows: the diff that made each byte-exact)\n"]
    for e in pick: em.append(f"\n## {e['id']} ({e['cfg']}; pins {e['pins'][0]} -> {e['pins'][1]}; classes {', '.join(e['classes'])})\n```diff\n{e['diff']}\n```\n")
    (L/'exemplars.md').write_text(''.join(em))
    b=b.replace('What the generators cannot do, and what you are asked to find:', 'Read `exemplars.md` in this directory first: it holds the exact diffs that made rows of THESE residue classes byte-exact this week; try each exemplar\'s move on every row here before anything else. What the generators cannot do, and what you are asked to find:')
(L/'BRIEF.md').write_text(b); (L/'PROMPT.txt').write_text(open('work/native_lane/r58_order/PROMPT.txt').read().replace('r58_order',lane))
print('built', lane, len(ids), 'pool', len(cand))
