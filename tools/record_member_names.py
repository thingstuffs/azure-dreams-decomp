"""Durable evidence-backed top-level record names, shared by generation and migration."""
import csv,re
from pathlib import Path
ROOT=Path(__file__).resolve().parents[1]

def load_names(root=ROOT):
 p=Path(root)/'config/member_names.tsv'
 if not p.exists():return {}
 result={}
 for row in csv.DictReader(p.open(),delimiter='\t'):
  if not row['header'].startswith('include/records/'):continue
  group=result.setdefault(row['struct'],{});old=row['old_member'];new=row['new_member']
  if old in group or not re.fullmatch('[A-Za-z_][A-Za-z0-9_]*',new):raise ValueError('invalid record member name: '+str(row))
  if int(row['offset'],16)!=int(old.removeprefix('unk_'),16):raise ValueError('record member offset drift: '+str(row))
  group[old]=new
 return result

def rename_generated(name,lines,paths,table=None):
 """Rename only outer declarations and the root of each generated accessor path."""
 renames=(load_names() if table is None else table).get(name,{})
 seen=set();out=[]
 for line in lines:
  depth=0;edits=[]
  for m in re.finditer(r'/\*.*?\*/|[{}]|\b[A-Za-z_][A-Za-z0-9_]*\b',line):
   token=m.group()
   if token=='{':depth+=1
   elif token=='}':depth-=1
   elif depth==0 and token in renames:
    if token in seen:raise ValueError('duplicate generated member: '+name+'.'+token)
    seen.add(token);edits.append((m.start(),m.end(),renames[token]))
  for start,end,new in reversed(edits):line=line[:start]+new+line[end:]
  out.append(line)
 missing=set(renames)-seen
 if missing:raise ValueError('named record layout changed: '+name+' '+repr(sorted(missing)))
 mapped={}
 for key,value in paths.items():
  head,sep,tail=value.partition('.');mapped[key]=renames.get(head,head)+sep+tail
 return out,mapped
