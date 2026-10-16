"""Derive declarations for relocated direct callees from matched body definitions.
Unchanged resident calls preserve the matched donor's existing declarations.
Pointer pointee identities are opaque across independent translation units.
"""
import re
from pathlib import Path
HEADER=Path(__file__).resolve().parents[3]/'include/m2c_compat.h'
ALIASES=dict((alias,scalar) for scalar,alias in re.findall(r'typedef\s+(s8|u8|s16|u16|s32|u32|s64|u64)\s+(M2C_UNK\w*)\s*;',HEADER.read_text()))
SCALARS={'void','s8','u8','s16','u16','s32','u32','s64','u64','char','signed char','unsigned char','short','unsigned short','int','unsigned int','long','unsigned long','float','double'}
def type_of(s,parameter=False):
 s=' '.join(s.split())
 if '*' in s:
  if '(' in s or ')' in s:raise ValueError('relocated callee has a function-pointer formal')
  return 'void *'
 if s in ALIASES:s=ALIASES[s]
 if s in SCALARS:return s
 # Strip an optional parameter identifier, retaining the definition's scalar type.
 if parameter:
  s=re.sub(r'\s+[A-Za-z_]\w*\s*$','',s)
  if s in ALIASES:s=ALIASES[s]
  if s in SCALARS:return s
 if s=='M2C_UNK':raise ValueError('relocated callee has unresolved M2C_UNK formal')
 raise ValueError('relocated callee has unresolved scalar type '+s)
def declaration(contract,newname):
 d=contract['definition'];name=contract['name'];m=re.fullmatch(r'(.*?)\b'+re.escape(name)+r'\((.*)\)',d)
 if not m:raise ValueError('cannot parse matched callee definition')
 ret=type_of(m[1]);params=m[2].strip()
 if not params:raise ValueError('relocated callee has old-style unspecified parameters')
 args=[type_of(p.strip(),True) for p in params.split(',')]
 return f'extern {ret} {newname}('+', '.join(args)+');'
def bind(text,contracts):
 edits={}
 for call in contracts:
  if call['source_callee']==call['encoded_callee']:
   sdk=call.get('contract') or {}
   if sdk.get('decision')==54:
    call['declaration_policy']=sdk['declaration_policy']
    if sdk['declaration_policy']=='canonical-PsyQ-dominant-matched':
     address=int(call['source_callee'],16)
     alias='func_%08X'%address
     names=[name for name in (sdk['name'],alias) if re.search(r'\b'+re.escape(name)+r'\s*\(',text)] or [sdk['name']]
     for name in names:
      definition=re.sub(r'\b'+re.escape(sdk['name'])+r'\b',name,sdk['definition'])
      edits[name]='extern '+definition+';'
   else:call['declaration_policy']='unchanged matched-template declaration'
   continue
  newname='func_%08X'%int(call['encoded_callee'],16);decl=declaration(call['contract'],newname)
  definition=re.search(r'^[ \t]*([A-Za-z_][A-Za-z0-9_ \t*]*?)\b'+re.escape(newname)+r'\s*\(([^;{}]*)\)\s*\{',text,re.M)
  if definition:
   actual=dict(name=newname,definition=definition[1]+newname+'('+definition[2]+')')
   if declaration(actual,'callee')!=declaration(call['contract'],'callee'):
    raise ValueError('relocated self definition conflicts with matched callee prototype')
   call['declaration_policy']='derived from matched self definition';call['derived_declaration']=decl
   continue
  if newname in edits and edits[newname]!=decl:raise ValueError('relocated callee has conflicting matched declarations')
  edits[newname]=decl;call['declaration_policy']='derived from matched callee body';call['derived_declaration']=decl
 for name,decl in edits.items():
  pattern=r'^[ \t]*(?!return\b)(?:extern\s+)?[A-Za-z_][A-Za-z_0-9 \t*]*?\b'+name+r'\s*\([^;{}]*\)\s*;'
  text,count=re.subn(pattern,decl,text,flags=re.M)
  if not count:
   # The original declaration may live in an unchanged shared header. The
   # renamed direct symbol has its own body-derived translation-unit prototype.
   includes=list(re.finditer(r'^[ \t]*#[ \t]*include[^\n]*\n',text,re.M))
   position=includes[-1].end() if includes else 0
   text=text[:position]+decl+'\n'+text[position:]
 return text
