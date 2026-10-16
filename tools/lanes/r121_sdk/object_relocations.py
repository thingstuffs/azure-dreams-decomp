"""Independently bind every differing word to the production compiler's ELF relocation."""
import json,struct,sys,hashlib,os,functools
from pathlib import Path
from twins import L,R

@functools.lru_cache(maxsize=None)
def window_split_source(window):
 import yaml
 document=yaml.safe_load((R/'config/overlays'/window).read_text())
 return document['standalone_build']['split_results']

def split_preflight(r):
 """An append to one container cannot silently change a mirror's splits."""
 from common import covering_windows
 canonical=f"overlays/{r['container']}/overlay_first_pass_results.json"
 windows={r['window']}|{w[0] for w in covering_windows(r['container'],r['foff'],r['size'])}
 bad=[]
 for window in sorted(windows):
  split=window_split_source(window)
  if Path(split).as_posix()==canonical:continue
  rows=json.loads((R/'build_ovl'/split).read_text())
  matches=[s for s in rows if not s.get('rerun') and s.get('foff')==r['foff'] and s.get('size')==r['size']]
  from mirror_splits import plan as mirror_plan
  planned=mirror_plan(R,r,{window}) if r.get('mirror_split_ledgers') else []
  if len(matches)!=1 and not (planned and set(planned)<=set(r.get('mirror_split_ledgers',[]))):
   bad.append(dict(window=window,split_results=split,reason='independent production split source lacks the exact C extent'))
 return bad

def production_object(r):
 """Bind the native artifact to the measured extent, owner and compiler recipe."""
 name=r['window'].removesuffix('.overlay.yaml')
 directory=R/'build_ovl/work/s3_splat'/name
 manifest=json.loads((directory/(name+'_manifest.json')).read_text())
 matches=[s for s in manifest['c_segments'] if int(s['file_start'],0)==r['foff'] and s['size']==r['size']]
 if len(matches)!=1:raise ValueError('production window does not compile this exact C extent')
 segment=matches[0]
 if segment['func']!=r['true_name']:raise ValueError('production C symbol differs from the admitted true name')
 if segment['config']!=r['cfg']:raise ValueError('production C recipe differs from the admitted recipe')
 source=R/'build_ovl'/segment['source'];expected=R/'src'/r['container']/(r['func']+'.c')
 if source.resolve()!=expected.resolve():raise ValueError('production C extent belongs to another source')
 if hashlib.sha256(source.read_bytes()).hexdigest()!=r['source_sha256']:raise ValueError('production source hash drift')
 duplicates=sum(s['func']==segment['func'] for s in manifest['c_segments'])>1
 key=segment['func']+(f"__{r['foff']:06X}" if duplicates else '')
 return directory/'build/obj'/(key+'.o')

def relocations(path,symbol):
 b=path.read_bytes();assert b[:6]==b'\x7fELF\x01\x01'
 off=struct.unpack_from('<I',b,0x20)[0];ents,num,strings=struct.unpack_from('<HHH',b,0x2e);sections=[struct.unpack_from('<10I',b,off+i*ents) for i in range(num)];s=sections[strings];names=b[s[4]:s[4]+s[5]]
 def name(s):return names[s[0]:].split(b'\0',1)[0].decode()
 target=next(i for i,s in enumerate(sections) if name(s)=='.text.'+symbol);out={}
 for s in sections:
  if s[1]!=9 or s[7]!=target:continue
  for pos in range(s[4],s[4]+s[5],s[9]):
   loc,info=struct.unpack_from('<II',b,pos);out[loc]=dict(type=info&255,symbol_index=info>>8)
 return out
def row_failures(r):
 try:p=production_object(r);rels=relocations(p,r['true_name'])
 except (OSError,ValueError,StopIteration,AssertionError,struct.error) as error:
  return [dict(reason='production C object binding failed',details=str(error))]
 bad=[]
 for d in r['relocation_proof']:
  expected=4 if d['kind'] in ('j','jal') else 5 if d['kind']=='lui' else 6;actual=rels.get(d['word']*4)
  if actual is None or actual['type']!=expected:bad.append(dict(word=d['word'],expected=expected,actual=actual))
 return bad

def main():
 out=[];bad=[]
 for resultfile in sorted((L/'evidence').glob('*/result.json')):
  result=json.loads(resultfile.read_text())
  for bank in result['banks']:
   for r in bank['rows']:
    try:p=production_object(r);rels=relocations(p,r['true_name'])
    except (OSError,ValueError,StopIteration,AssertionError,struct.error) as error:
     bad.append(dict(id=r['id'],reason='production C object binding failed',details=str(error)));continue
    proved=[]
    for d in r['relocation_proof']:
     expected=4 if d['kind'] in ('j','jal') else 5 if d['kind']=='lui' else 6;actual=rels.get(d['word']*4)
     if actual is None or actual['type']!=expected:bad.append(dict(id=r['id'],word=d['word'],expected=expected,actual=actual))
     else:proved.append(dict(word=d['word'],retail_difference=d['kind'],elf_relocation=actual))
    out.append(dict(id=r['id'],object=str(p.relative_to(L)),object_sha256=hashlib.sha256(p.read_bytes()).hexdigest(),relocations=proved))
 (L/'evidence/object_relocations.json').write_text(json.dumps(dict(rows=out,failures=bad),indent=1)+'\n');print('OBJECT RELOCATIONS',len(out),'rows',sum(len(r['relocations']) for r in out),'words',len(bad),'failures');print(bad[:20]);sys.exit(bool(bad))

if __name__=='__main__':main()
