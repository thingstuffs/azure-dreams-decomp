#!/usr/bin/env python3
"""Conservative decision-72(d) signature triage. Emits reviewable proposals; never edits C.

Only unanimous direct-call arity, unanimous explicit caller types, no address
uses, and unused removed formals qualify. Return fixes require explicit value
returns already in the body. Whole-TU identity is still required before use.
"""
import argparse
from collections import defaultdict, Counter
import json
from pathlib import Path
import re
import sys
sys.path.insert(0,str(Path(__file__).resolve().parent))
import cscan as C
import model as M
from extra import alias_groups


def calls_in(body, names):
    toks=C.tokens(body)
    for i,t in enumerate(toks):
        if t not in names:
            continue
        if i and toks[i-1] in ('.','->'):
            continue                         # member field, not the global name
        if i+1 < len(toks) and toks[i+1]=='(':
            end=C._close(toks,i+1)
            args=C._split_top(toks[i+2:end])
            yield t,len(args) if args != [[]] else 0,False
        else:
            yield t,None,True


def analyze(root, source_overrides=None):
    corpus=M.Corpus(root)
    corpus._text.update(source_overrides or {})
    # Generated declarations repeat the current definition; they are not
    # independent caller evidence for correcting that definition.
    corpus.h_files=[h for h in corpus.h_files if 'maintained by tools/headers' not in corpus.text(h)[:400]]
    ti=M.TypeIndex(corpus); M._TINDEX[0]=ti
    defs,sites,_=M.collect(corpus,ti)
    aliases,resident_aliases=alias_groups(corpus.root,defs)
    resolved={}
    def bind_all(path,name):
        key=(path,name)
        if key in resolved:return resolved[key]
        direct,why=M.bind(path,name,defs)
        if why in ('same_file_static','static_only'):
            resolved[key]=((),False);return resolved[key]
        found={(direct.path,direct.name):direct} if direct else {}
        ambiguous=why=='multi_definition_conflict'
        for target in aliases.get(name,()):
            if target==name:continue
            if name in resident_aliases:
                ds=[d for d in defs.get(target,()) if not d.static and d.container==M.RESIDENT]
                d,reason=M.pick_multi(ds) if ds else (None,'')
            else:d,reason=M.bind(path,target,defs)
            ambiguous |= reason=='multi_definition_conflict'
            if d:found[(d.path,d.name)]=d
        resolved[key]=(tuple(found.values()),ambiguous or len(found)>1)
        return resolved[key]
    by_def=defaultdict(list)
    ambiguous_defs=set()
    candidates=set()
    for s in sites:
        ds,ambiguous=bind_all(s.path,s.name)
        for d in ds:
            by_def[(d.path,d.name)].append(s)
            if ambiguous:ambiguous_defs.add((d.path,d.name))
            cls,_=M.classify(s,d,ti)
            if not s.in_header and (cls=='arity' or (d.ret_spec==('void',) and d.ret_ptr==0 and
                               (s.ret_spec!=('void',) or s.ret_ptr))):
                candidates.add(d.name)
    spellings=set(candidates)
    spellings.update(n for n,targets in aliases.items() if targets & candidates)
    calls=defaultdict(list)
    for rel in corpus.c_files + corpus.h_files:
        sc=corpus.scan(rel)
        for directive in sc.directives:
            if directive.kind == 'define':
                for name in set(C.IDENT.findall(C.mask(directive.arg))) & spellings:
                    ds,ambiguous=bind_all(rel,name)
                    for d in ds:
                        if ambiguous:ambiguous_defs.add((d.path,d.name))
                        calls[(d.path,d.name)].append((rel,None,True))
        for it in sc.items:
            shadow=set()
            if it.kind=='def':
                body=sc.masked[it.body[0]:it.body[1]]
                shadow={M.param_parts(p)[2] for p in it.decls[0].params or []}
            elif it.kind=='decl' and '=' in sc.masked[it.start:it.end]:
                body=sc.masked[it.start:it.end].split('=',1)[1]
            else:
                continue
            for name,n,addr in calls_in(body,spellings):
                ds,ambiguous=bind_all(rel,name)
                for d in ds:
                    if ambiguous:ambiguous_defs.add((d.path,d.name))
                    calls[(d.path,d.name)].append((rel,n,addr or ambiguous or name in shadow))
    results=[]
    for name in sorted(candidates):
        for d in defs[name]:
            if d.static: continue
            ss=by_def.get((d.path,name),[])
            if not ss: continue
            cs=calls.get((d.path,name),[])
            counts=Counter(n for p,n,addr in cs if not addr)
            reason=''; proposed=''; params=list(d.params)
            if d.knr or d.varargs or d.complex:
                reason='unsupported_definition'
            elif (d.path,name) in ambiguous_defs:
                reason='alias_binding_ambiguous'
            elif sum(not x.static and x.container==d.container for x in defs[name])>1:
                reason='multiple_definition_ownership'
            elif not cs: reason='no_direct_call_evidence'
            elif any(addr for _,_,addr in cs): reason='address_taken_or_noncall_use'
            elif len(counts)!=1: reason='call_arity_disagrees'
            else:
                desired=next(iter(counts))
                explicit=[s for s in ss if s.params is not None]
                if any(len(s.params)!=desired for s in explicit):
                    reason='explicit_declarations_disagree_with_calls'
                elif desired!=len(d.params):
                    if desired<len(d.params):
                        sc=corpus.scan(d.path)
                        it=next(i for i in sc.items if i.kind=='def' and i.decls[0].name==name)
                        body=sc.masked[it.body[0]:it.body[1]]
                        removed=[M.param_parts(p)[2] for p in d.params[desired:]]
                        if any(not n or re.search(r'\b'+re.escape(n)+r'\b',body) for n in removed):
                            reason='removed_formal_is_used'
                        else: params=d.params[:desired]
                    else:
                        agreeing=[s for s in explicit if len(s.params)==desired and not s.complex]
                        keys={tuple(M.canon(*M.param_parts(p)[:2],ti.visible(s.path)) for p in s.params) for s in agreeing}
                        if len(keys)!=1: reason='missing_or_conflicting_formal_types'
                        else:
                            sample=agreeing[0]
                            # New unused words need no foreign typedefs in the definition.
                            for i in range(len(d.params),desired):
                                spec,ptr,n,cx,ell=M.param_parts(sample.params[i])
                                can=M.canon(spec,ptr,ti.visible(sample.path))
                                if cx or ell or can[2] not in ('int','ptr') or can[0] in ('s64','u64'):
                                    reason='unsupported_added_formal'; break
                                typ='void *' if can[1] else {'s32':'s32','u32':'u32','s16':'s16','u16':'u16','s8':'s8','u8':'u8','char':'char'}.get(can[0])
                                if not typ: reason='unsupported_added_formal'; break
                                if typ != 'void *' and typ != 'char' and typ not in ti.visible(d.path):
                                    typ={'s32':'int','u32':'unsigned int','s16':'short','u16':'unsigned short',
                                         's8':'signed char','u8':'unsigned char'}[typ]
                                params.append(C.tokens(typ+f' unused_arg{i}'))
                else:
                    reason='body_has_no_value_return' if d.ret_spec==('void',) and d.ret_ptr==0 else \
                           'actual_calls_match_definition_arity'
            if not reason:
                ret=' '.join(d.ret_spec)+' '+'*'*d.ret_ptr
                args=', '.join(' '.join(p) for p in params) if params else 'void'
                proposed=f'{ret}{name}({args})'
            results.append({'name':name,'definition':d.path,'old':d.proto,'proposed':proposed,
                            'status':'candidate' if proposed else 'hold','reason':reason or 'unanimous_calls_unused_formals',
                            'calls':len(cs),'arities':dict(counts),'sites':len(ss),
                            'caller_paths':sorted({p for p,n,a in cs})})
    return results


def main():
    ap=argparse.ArgumentParser(description=__doc__)
    ap.add_argument('--root',type=Path,default=Path(__file__).resolve().parents[2]);ap.add_argument('--out',type=Path,required=True)
    a=ap.parse_args(); results=analyze(a.root)
    a.out.mkdir(parents=True,exist_ok=True)
    (a.out/'triage.json').write_text(json.dumps(results,indent=1)+'\n')
    with (a.out/'triage.tsv').open('w') as f:
        fields=('name','definition','status','reason','calls','sites','old','proposed')
        f.write('\t'.join(fields)+'\n')
        for r in results: f.write('\t'.join(str(r[k]) for k in fields)+'\n')
    print(json.dumps(Counter(r['reason'] for r in results),indent=1))
if __name__=='__main__': main()
