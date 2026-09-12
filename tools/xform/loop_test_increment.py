"""A conservative do-loop scheduling idiom; enabled only by fence search."""
import re
from xform.natural import _T, _close, _decl, _occ, ID, NUM

def ordinary_type(ty, pointer=False):
    """Reject unknown typedef qualifiers; cursor pointers to ordinary scalars are safe."""
    ty = re.sub(r'\bregister\b', '', ty or '').strip()
    if pointer:
        ty = ty.replace('*', '').strip()
    return bool(re.fullmatch(r'(?:[su](?:8|16|32|64)|(?:signed|unsigned)(?:\s+(?:char|short|int|long)(?:\s+int)?)?|(?:char|short|int|long)(?:\s+int)?)', ty))

def loop_test_increment_candidates(text):
    """Move a local counter's tail increment to its do/while comparison."""
    t=_T(text); out=[]
    for start,line in enumerate(t.m):
        if not re.fullmatch(r'\s*do\s*\{\s*',line): continue
        end=_close(t.m,start)
        if end is None: continue
        test=re.fullmatch(r'\s*}\s*while\s*\(\s*('+ID+r')\s*(<|<=|!=|>|>=)\s*('+ID+'|'+NUM+r')\s*\)\s*;\s*',t.m[end])
        if not test: continue
        name=test[1]; sp=t.span(start)
        if not sp: continue
        decl,ty,init=_decl(t.m,*sp,name)
        if decl is None or not ordinary_type(ty) or test[3] == name: continue
        body='\n'.join(t.m[start+1:end]); scope='\n'.join(t.m[sp[0]:sp[1]+1])
        if re.search(r'\b(?:continue|goto|break|return|if|else|switch|case|for|while|do)\b|^\s*(?:#|'+ID+r'\s*:)',body,re.M): continue
        if re.search(r'&\s*'+re.escape(name)+r'\b',scope): continue
        if len(_occ(name).findall(body)) != 1: continue
        for inc in range(end-1,start,-1):
            if not re.fullmatch(r'\s*(?:'+re.escape(name)+r'\s*\+\+|\+\+\s*'+re.escape(name)+r'|'+re.escape(name)+r'\s*\+=\s*1)\s*;\s*',t.m[inc]): continue
            prefix='\n'.join(t.m[start+1:inc])
            if prefix.count('{')!=prefix.count('}'): continue
            safe=True
            for tail in t.m[inc+1:end]:
                if not tail.strip(): continue
                step=re.fullmatch(r'\s*('+ID+r')\s*(?:\+\+|--|[+-]=\s*'+NUM+r')\s*;\s*',tail)
                if not step or step[1]==name: safe=False; break
                dk,dty,_=_decl(t.m,*sp,step[1])
                if dk is None or not ordinary_type(dty, pointer=True) or re.search(r'&\s*'+re.escape(step[1])+r'\b',scope): safe=False; break
            if not safe: continue
            hit=_occ(name).search(t.m[end]); old=t.lines[end].rstrip('\n')
            edited=old[:hit.start()]+'++'+old[hit.start():]
            comment=t.lines[inc][t.lines[inc].find(';')+1:].strip(); drop=() if comment else (inc,)
            edits={end:edited}
            if comment: edits[inc]=re.match(r'\s*',t.lines[inc]).group()+comment
            out.append(('loop_test_increment:'+name,t.build(edits,drop))); break
    return out
