"""Build a class-grouped, exemplar-briefed model pack with the round-60 residue screen (moved from the session scratchpad; inputs in ledger/pack_inputs/).
    python3 tools/lanes/build_class_pack.py <lane> <L0 class,class> [n] --pins A-B --exemplars N [--solved "N of M rows"] [--only-served-by r58_order] [--dry-run]  python3 build_pack.py <lane> <class,class> [n] [--solved 'N of M rows']
Round 62 adds two flags, both off by default (the flagless output is byte-identical to every earlier run):
    --rows id,id,...   build a pack of exactly these rows, whatever their class, pin count or served history
                       (a whole-function or family pack); rows.md then notes which lanes already served each row
    --duck             append each row's rubber-duck brief (tools/lanes/duck_brief.py) under its rows.md section
Round 68 adds one more, also off by default:
    --paragraphs a,b   append tools/lanes/brief_paragraphs/<a>.md ... to BRIEF.md after the standard brief
                       (big_rows, new_findings, a filled copy of class_question): the blocks rounds 63-67
                       pasted onto each BRIEF.md by hand out of the session scratchpad
Round 76 adds, also off by default:
    --served-guard off|ever|tier   refuse the pack when a row was already served (tools/lanes/served.py):
                       `ever` = any lane ever (round 26); `tier` = a launched lane of the SAME tier (--tier) at
                       the SAME row text (round 76: kit-era retries of other tiers paid 61-72%). --repack overrides.
    --tier T           astra|opus|sonnet|sol6|luna6|sol|luna: the model tier this pack is for (guard `tier`)"""
import json, sys, difflib, shutil, glob; sys.path.insert(0,'tools'); sys.path.insert(0,'tools/xform'); sys.path.insert(0,'tools/lanes')
from pathlib import Path
from common import rows, clean_path, sha_text
from pin_census import sites_of
from pin_sites import erase_many
import residue
import screen
from served import served_rows as _sr
SERVED_BASE=_sr()
S='ledger/pack_inputs'; MY=S
VALOPTS={'--solved','--pins','--exemplars','--only-served-by','--rows','--notes','--paragraphs','--served-guard','--tier'}
def opt(name, default=None):
    return sys.argv[sys.argv.index(name)+1] if name in sys.argv else default
lane=sys.argv[1]
pos=[]; i=2                                        # positionals, skipping option values (argv[1] is the lane)
while i<len(sys.argv):
    a=sys.argv[i]
    if a.startswith('--'): i+=2 if a in VALOPTS else 1; continue
    pos.append(a); i+=1
classes=set(pos[0].split(',')) if pos else set()
n=int(pos[1]) if len(pos)>1 else 12
solved=opt('--solved')
pr=opt('--pins','1-2')
pmin,pmax=(int(pr.split('-')[0]),int(pr.split('-')[-1]))
nex=int(opt('--exemplars',0))
only_rows=[x.strip() for x in opt('--rows','').split(',') if x.strip()]
duck_on='--duck' in sys.argv
note_files=[x.strip() for x in opt('--notes','').split(',') if x.strip()]   # hand probe notes quoted in the ducks
paragraphs=[x.strip() for x in opt('--paragraphs','').split(',') if x.strip()]  # tools/lanes/brief_paragraphs/<name>.md
by={r['id']:r for r in rows()}
census=[json.loads(l) for l in open(f'{S}/erase_r56.jsonl')]
cls={}; dmax={}; ccls={}
for r in census:
    cls.setdefault(r['id'], r['fp'].get('L0')); dmax[r['id']]=max(dmax.get(r['id'],0), r['fp'].get('d',0)); ccls.setdefault(r['id'], r['fp'].get('cls'))
def screened(rid, r):
    # 2026-09-20 calibration over 235 served sol rows: RECOLOURED with erase distance >= 0.3 x instruction count = 18 served, 0 solved
    return ccls.get(rid)=='RECOLOURED' and r['size'] and dmax.get(rid,0)/(r['size']//4 or 1) >= 0.3
screened_out=0
served={}
for f in glob.glob('work/native_lane/r[56]*_*/rows.md'):
    for l in open(f):
        if l.startswith('## '): served.setdefault(l[3:].strip(), set()).add(f.split('/')[2])
# --only-served-by PREFIX: a RETRY pool = rows every serving lane of which starts with PREFIX (e.g. r58_order = Gemini only)
only_by=opt('--only-served-by')
def admissible(rid):
    lanes=served.get(rid, set())
    if only_by: return bool(lanes) and all(l.startswith(only_by) for l in lanes)
    return not lanes
cand=[]
if only_rows:
    # an explicit row list: no class, pin-count, container or served-state screen at all
    ids=[rid for rid in only_rows if rid in by and clean_path(by[rid]).exists()]
    missing=[rid for rid in only_rows if rid not in ids]
    if missing: print('WARNING: no clean file / unknown row:', ','.join(missing))
    cand=[(len(sites_of(clean_path(by[rid]).read_text(errors='replace'))), 0, rid) for rid in ids]
else:
    for rid,r in by.items():
        if r['container'] in ('slus','ovmovie') or not admissible(rid) or not clean_path(r).exists(): continue
        t=clean_path(r).read_text(errors='replace'); k=len(sites_of(t))
        if pmin<=k<=pmax and cls.get(rid) in classes:
            if screened(rid, r): screened_out+=1; continue
            cand.append((k,len(t.splitlines()),rid))
    cand.sort(); ids=[c[2] for c in cand[:n]]
guard=opt('--served-guard','off')
if guard!='off':                                                   # round 76: tools/lanes/served.py assert_unserved
    import served as _served
    _served.assert_unserved(ids, repack='--repack' in sys.argv, mode=guard, tier=opt('--tier'), skip_lane=lane)
if '--dry-run' in sys.argv:
    print('pool', len(cand), 'screened out', screened_out, 'first', ids[:n]); sys.exit(0)
L=Path('work/native_lane')/lane; shutil.rmtree(L, ignore_errors=True); (L/'out').mkdir(parents=True); (L/'.ignore').write_text('*\n')
if duck_on:
    import duck_brief
    duck_brief.prime_sweeps(ids)
md=["# Rows (the residue is the cc1 listing diff of erasing every pin; retail order = the pinned listing)\n"]
fresh={}
for rid in ids:
    r=by[rid]; t=clean_path(r).read_text(errors='replace'); c,nm=rid.split('/')
    (L/'base'/c).mkdir(parents=True, exist_ok=True); (L/'base'/c/(nm+'.c')).write_text(t); (L/'base'/c/(nm+'.c.base_sha')).write_text(sha_text(t)+'\n')
    sites=sites_of(t); e=erase_many(t,sites,clean_notes=True); la=screen.compile_s(r,t); lb=screen.compile_s(r,e)
    d='\n'.join(x for x in difflib.unified_diff(la,lb,lineterm='',n=4) if not x.startswith(('---','+++'))) if la and lb else '(no listing)'
    if only_rows and d.count('\n')>200:                            # a 40-pin row's joint diff is thousands of lines
        dl=d.split('\n'); d='\n'.join(dl[:200])+f"\n... {len(dl)-200} more listing lines (recompile the erased text yourself: the duck's per-pin residues below are the tractable view)"
    fresh[rid]=residue.fingerprint(la,lb).get('L0') if (la and lb) else None
    md.append(f"\n## {rid}\n- recipe `{r['cfg']}`, {len(t.splitlines())} lines, {len(sites)} pin(s): "+'; '.join(f"`{s[1]}({s[2]})` at line {s[5]}" for s in sites)+f"; erase-census class {cls.get(rid)}\n- cc1 listing, pinned -> every pin erased:\n```\n"+d+"\n```\n")
    if only_rows:
        sv=sorted(served.get(rid, set())-{lane})                   # a rebuild must not count this lane's own previous rows.md
        old=sorted(set(SERVED_BASE.get(rid, []))-{lane}-set(sv))   # the other served definition: a base/*.c copy in any older lane
        md.append(f"- served history: {', '.join(sv) if sv else 'never served by an r5*/r6* model lane'}"
                  +(f"; older lanes holding a base copy: {', '.join(old)}" if old else "")
                  +" (this pack is a deliberate row list, not a fresh-row pool)\n")
    if duck_on:
        md.append('\n'+duck_brief.duck(rid, notes=note_files, row=r, text=t, skip_lane=lane)+'\n')
(L/'rows.md').write_text(''.join(md))
for nf in note_files:                                              # LANE_KIT 4: the evidence lives in the lane
    if Path(nf).exists(): (L/'evidence').mkdir(exist_ok=True); shutil.copy(nf, L/'evidence'/Path(nf).name)
b=open('work/native_lane/r58_order5/BRIEF.md').read().replace('r58_order5',lane)
if solved: b=b.replace('solved thirteen of 36 rows', 'solved '+solved)
if nex:
    exs=json.load(open(f'{S}/solved_exemplars.json'))
    want={c.split('|')[0]+'|'+c.split('|')[1] for c in classes} or {v for v in fresh.values() if v}
    pick=sorted([e for e in exs if set(e['L0'])&want], key=lambda e:(len(e['diff']), -(e['pins'][0]-e['pins'][1])))[:nex]
    em=["# Solved exemplars of this pack's residue classes (this week's landed rows: the diff that made each byte-exact)\n"]
    for e in pick: em.append(f"\n## {e['id']} ({e['cfg']}; pins {e['pins'][0]} -> {e['pins'][1]}; classes {', '.join(e['classes'])})\n```diff\n{e['diff']}\n```\n")
    (L/'exemplars.md').write_text(''.join(em))
    b=b.replace('What the generators cannot do, and what you are asked to find:', 'Read `exemplars.md` in this directory first: it holds the exact diffs that made rows of THESE residue classes byte-exact this week; try each exemplar\'s move on every row here before anything else. What the generators cannot do, and what you are asked to find:')
p=open('work/native_lane/r58_order/PROMPT.txt').read().replace('r58_order',lane)
if only_rows or duck_on:
    dp=open('tools/lanes/duck_pack_brief.md').read()
    head,_,rest=b.partition('\n')                                  # the brief's own title stays line 1
    if only_rows: head=f"# Lane: {lane} - {len(ids)} rows chosen by hand (a family / whole-function pack, not a class pool)"
    b=head+'\n\n'+dp.rstrip()+'\n'+rest
    p=p.rstrip('\n')+"\nBefore compiling anything for a row, restate that row's DUCK brief in `rows.md` in your own words (state, issue, what must happen), and end REPORT.md with the duck answered per row: what was tried, the distances reached, which pins fell, and what you would need to know next.\n"
for name in paragraphs:                                             # LANE_KIT "Orchestration kit": named brief paragraphs
    pf=Path('tools/lanes/brief_paragraphs')/(name+'.md')
    if not pf.exists(): print('WARNING: no brief paragraph', pf); continue
    if '<<' in pf.read_text(): print('WARNING:', pf, 'still has unfilled <<...>> slots')
    b=b.rstrip('\n')+'\n\n\n'+pf.read_text().strip('\n')+'\n'
(L/'BRIEF.md').write_text(b); (L/'PROMPT.txt').write_text(p)
print('built', lane, len(ids), 'pool', len(cand))
