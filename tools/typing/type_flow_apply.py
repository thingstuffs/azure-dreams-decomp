#!/usr/bin/env python3
"""Apply type_flow_solve transactions (parameter / local / local-slot nodes); refuse unsafe closure.

    type_flow_apply.py --graph G --solve SOLVE_DIR --rt RTDIR --ids C0001 C0002 ... --out DIR [--allow-zero]
                       [--allow-modules]

Each transaction's declarations change together (callee prototype, every declaration of it, caller locals, local
slot parameters); param_retype plans the expression rewrites, cast_fold folds the touched functions and
clean_views drops view chains the new types make redundant.  The transaction is kept only when every direct
consumer's native diagnostics are unchanged and the measured pointer casts fall (or stay equal with --allow-zero,
for a runtime-backed prototype settle inside a falling batch); otherwise every file is restored.  With --members a
record member (F:Rec.m) or a function-pointer member's parameter (F:Rec.m#i) is respelled in its record definition
and every function using it is folded and compared; global and return nodes are refused (manual_node).  The byte proof (tools/lanes/prove_batch.sh) is still required before
committing a batch.  Results: DIR/results.json (per transaction status, reason, measured delta, files).
(Harvested from the r136w_flow2 lane's private helper.)
"""
import argparse, collections, csv, json, re, sys
from pathlib import Path
ROOT=Path(__file__).resolve().parents[2]
sys.path[:0]=[str(ROOT/'tools/typing'),str(ROOT/'tools'),str(ROOT/'tools/lint'),str(ROOT)]
import param_retype as P
import type_flow_solve as S
import cast_ast as A
import field_census as C


def slot_edit(text, decl, index, spelling):
    loc=(decl.get('loc') or {}).get('offset')
    span=A.node_range(decl,text)
    if loc is None or span is None:raise ValueError('slot_in_macro')
    if not text.isascii():loc=len(text.encode()[:loc].decode())
    opening=text.find('(',loc,span[1])
    if opening<0:raise ValueError('slot_signature_absent')
    depth=1;closing=opening+1
    while closing<span[1] and depth:
        depth += (text[closing]=='(')-(text[closing]==')');closing+=1
    if depth:raise ValueError('slot_signature_unbalanced')
    original='void lane_slot'+text[opening:closing]+';'
    changed=P.respell_in_text(original,'lane_slot',index,spelling)
    if changed is None:raise ValueError('slot_parameter_unchanged')
    return opening,closing,changed[len('void lane_slot'):-1]


def _close(masked, open_at, a='{', b='}'):
    depth = 0
    for pos in range(open_at, len(masked)):
        depth += masked[pos] == a
        depth -= masked[pos] == b
        if not depth:
            return pos
    raise ValueError('unbalanced')


def record_body(masked, rec):
    """(open, close) brace offsets of the definition of record `rec` (tag or typedef name), or None."""
    m = re.search(r'\b(?:struct|union)\s+' + re.escape(rec) + r'\s*\{', masked)
    if m:
        o = m.end() - 1
        return o, _close(masked, o)
    for m in re.finditer(r'\}\s*' + re.escape(rec) + r'\s*;', masked):
        close, depth = m.start(), 0
        for pos in range(close, -1, -1):
            depth += masked[pos] == '}'
            depth -= masked[pos] == '{'
            if not depth:
                return pos, close
    return None


def member_retype_text(text, rec, member, spelling, slot=None):
    """Respell the top-level member `member` of record `rec` in `text` as `spelling` (slot=None), or parameter
    `slot` of a function-pointer member `ret (*member)(...)`.  Returns the new text, None when the declaration is
    not found in that shape (arrays, bit-fields, several declarators, typedef'd function types are refused)."""
    import tools.proto.prototypes as PP
    scan = PP.cscan.scan(text)
    masked = scan.masked
    body = record_body(masked, rec)
    if not body:
        return None
    o, c = body
    depth, start = 0, o + 1
    for pos in range(o + 1, c):
        ch = masked[pos]
        depth += ch in '{('
        depth -= ch in '})'
        if ch != ';' or depth:
            continue
        stmt = masked[start:pos]
        a = start
        start = pos + 1
        if slot is None:
            m = re.match(r'^(\s*)([^,:\[\]{}()]*?[\s*])' + re.escape(member) + r'\s*$', stmt)
            if not m:
                continue
            ta, tb = a + m.start(2), a + m.end(2)
            new = spelling if spelling.endswith('*') else spelling + ' '
            return text[:ta] + new + text[tb:]
        m = re.search(r'\(\s*\*\s*' + re.escape(member) + r'\s*\)\s*\(', stmt)
        if not m:
            continue
        lp = a + m.end() - 1
        rp = PP.balanced(masked, lp)
        d, cuts = 0, [lp + 1]
        for j in range(lp + 1, rp):
            ch = masked[j]
            d += ch == '('
            d -= ch == ')'
            if ch == ',' and d == 0:
                cuts.append(j + 1)
        cuts.append(rp + 1)
        if slot >= len(cuts) - 1:
            return None
        x, y = cuts[slot], cuts[slot + 1] - 1
        ptext = text[x:y]
        lead = ptext[:len(ptext) - len(ptext.lstrip())]
        trail = ptext[len(ptext.rstrip()):]
        toks = PP.cscan.tokens(ptext.strip())
        name = PP.M.param_parts(toks)[2] if toks and ptext.strip() != 'void' else ''
        new = spelling.rstrip() if not name else (spelling if spelling.endswith('*') else spelling + ' ') + name
        return text[:x] + lead + new + trail + text[y:]
    return None


def match_note(text, fn):
    """True when function `fn`'s definition in `text` carries a MATCH: note (views kept for byte identity)."""
    for m in re.finditer(r'\b' + re.escape(fn) + r'\s*\([^;{]*\)\s*\{', text):
        o = m.end() - 1
        try:
            c = _close(text, o)
        except ValueError:
            return False
        return 'MATCH:' in text[o:c]
    return False


def member_sites(g):
    """F:Rec.m (and F:Rec.m#i slot parameter) -> {(file, function)} that read, write or call through it."""
    out = collections.defaultdict(set)
    for e in g.edges:
        for end in (e.get('dst'), e.get('src')):
            if end and end.startswith('F:'):
                out[re.sub(r'#(\d+|ret)$', '', end)].add((e['file'], e['fn']))
    for u in g.uses:
        if u.get('node', '').startswith('F:'):
            out[u['node']].add((u['file'], u['fn']))
    return out


def main():
    ap=argparse.ArgumentParser();ap.add_argument('--graph',required=True);ap.add_argument('--solve',type=Path,required=True);ap.add_argument('--rt',type=Path,required=True);ap.add_argument('--ids',nargs='+',required=True);ap.add_argument('--out',type=Path,required=True);ap.add_argument('--allow-zero',action='store_true');ap.add_argument('--allow-modules',action='store_true');ap.add_argument('--members',action='store_true',help='also retype record members and function-pointer member parameters (F: nodes)');ap.add_argument('--scope',nargs='*',help='path prefixes this lane may edit: a transaction that changes any other file is restored');a=ap.parse_args();a.out=a.out.resolve();a.out.mkdir(parents=True,exist_ok=True)
    g=S.Graph(a.graph);rt=S.Runtime(a.rt,g);ix=P.Index(ROOT);units=P.Units(ROOT)
    msites=member_sites(g) if a.members else {}
    P.BYTE_ARITH=True;P.BYTE_MACROS=True;P.COMPARE_UNCAST=True
    real_assign=P.assignable;real_value=P.value_into
    # A simultaneously retyped destination may still have its old AST type here.
    # These temporary relaxations never add a conversion; the strict native
    # diagnostic comparison below validates the final transaction.
    target_canons=set(); old_canons=set()
    P.assignable=lambda dst,src,null=False: real_assign(dst,src,null) or (src in target_canons and dst in old_canons)
    P.value_into=lambda unit,rhs,target,text,edits: 0
    result=[]
    for cid in a.ids:
        data=json.load(open(a.solve/'components'/(cid+'.json')))
        comp={n:v for n,v in data['comp'].items() if v['st']=='retype'}
        target_canons.clear();old_canons.clear()
        for node,info in comp.items():
            target_canons.add(P.decay(g.resolve(info['t'])))
            old_canons.add(P.decay(g.resolve(info.get('from',''))))
        backups={};touched=collections.defaultdict(set);edits=collections.defaultdict(list);texts={};headers=collections.defaultdict(set)
        try:
            if data['verdict']=='hold':raise ValueError('solver_hold')
            if not a.allow_modules and any(g.home(n).startswith('src/dungeon/modules/') for n in comp):raise ValueError('module_source_without_allow_modules')
            members=[]
            for n,v in comp.items():
                if n.startswith('F:') and a.members:members.append((n,v));continue
                if not n.startswith(('P:','L:')):raise ValueError('manual_node:'+n)
                f=g.home(n)
                if not f or (f.startswith('src/dungeon/modules/') and not a.allow_modules):raise ValueError('module_or_missing_home:'+n)
                u=units.get(f)
                if not u:raise ValueError('parse:'+f)
                slot_index=None; holder=n
                if n.startswith('L:') and '#' in n:
                    holder,_,raw_index=n.rpartition('#')
                    if not raw_index.isdigit():raise ValueError('manual_slot_return:'+n)
                    slot_index=int(raw_index)
                key=n[2:].rpartition('#')[0] if n.startswith('P:') else holder[2:].split(':')[0]
                if len({d['file'] for d in g.functions.get(key,[])})>1:raise ValueError('ambiguous_definition:'+n)
                fn=P.find_function(u,f,key.split('@')[0])
                if not fn:raise ValueError('function_absent:'+n)
                parents,nodes=P.parents_of(fn)
                if n.startswith('P:'):
                    i=int(n.rpartition('#')[2]);decl=P.params_of(fn)[i]
                    weak_seed=any(seed.get('node')==n and seed.get('hold')=='weak' for seed in data['seeds'])
                    if weak_seed and rt.cast_ok(rt.pointer_cells(n),0,v['t'])!='correct':raise ValueError('weak_seed_without_runtime_agreement:'+n)
                    if rt.scalar_share(n) not in (None,0.0) and '*' in v['t']:raise ValueError('mixed_runtime:'+n)
                    if g.cls(v['t'])=='gen' and rt.node_type(n)[0]:raise ValueError('generated_target_despite_named_runtime_identity:'+n)
                    if rt.pointer_cells(n) and rt.cast_ok(rt.pointer_cells(n),0,v['t'])=='wrong':raise ValueError('runtime_contradiction:'+n)
                else:
                    name=holder.rsplit(':',1)[1].rpartition('@')[0]
                    ds=[d for d in nodes if d.get('kind')=='VarDecl' and d.get('name')==name]
                    if len(ds)>1:
                        wanted_line=int(holder.rpartition('@')[2]);ds=[d for d in ds if u.text(f).count('\n',0,A.node_range(d,u.text(f))[0])+1==wanted_line]
                    if len(ds)!=1:raise ValueError('ambiguous_local:'+n)
                    decl=ds[0]
                spelling=v['t'];rec=g.record_of(spelling);home=(g.records.get(rec) or {}).get('file','')
                if rec and home and not home.startswith('include/'):raise ValueError('private_target:'+spelling)
                if slot_index is not None:
                    edits[f].append(slot_edit(u.text(f),decl,slot_index,spelling))
                    touched[f].add(fn['name'])
                    if home and P.Target(u,spelling).key is None:headers[f].add(home)
                    continue
                target=P.Target(u,spelling)
                if rec and not target.key:
                    # Parse a tiny private probe to obtain the owning layout.
                    probe=(a.out if a.out.is_relative_to(ROOT) else ROOT/'build')/'type_flow_apply_probe.c';probe.write_text('#include "'+home.removeprefix('include/')+'"\n')
                    tu,err=A.clang_unit(ROOT,str(probe.relative_to(ROOT)))
                    target=P.target_in(u,P.Target(tu,spelling))
                    if not target.key:raise ValueError('target_not_visible:'+spelling)
                plan=P.plan_retype(u,f,fn,decl,target)
                if plan.get('refused'):raise ValueError(n+':'+plan['refused'])
                edits[f].extend(plan['edits']);touched[f].add(fn['name'])
                if home and P.Target(u,spelling).key is None:headers[f].add(home)
            for f,es in edits.items():texts[f]=P.apply_text_edits((ROOT/f).read_text(),es)
            for n,v in members:
                key=n[2:];slot=None
                if '#' in key:
                    key,_,si=key.rpartition('#')
                    if not si.isdigit():raise ValueError('manual_slot_return:'+n)
                    slot=int(si)
                rec,_,member=key.partition('.')
                if not re.fullmatch(r'[A-Za-z_]\w*',member) or rec in g.ambiguous_records or rec.startswith('@'):raise ValueError('nested_or_anonymous_member:'+n)
                f=(g.records.get(rec) or {}).get('file','')
                if not f or (f.startswith('src/dungeon/modules/') and not a.allow_modules):raise ValueError('record_home:'+n)
                spelling=v['t'];trec=g.record_of(spelling);thome=(g.records.get(trec) or {}).get('file','')
                if trec and thome and not thome.startswith('include/'):raise ValueError('private_target:'+spelling)
                if trec and thome and thome!=f and thome not in P.header_closure(ROOT,f):
                    if f.endswith('.h'):raise ValueError('target_not_visible_in_record_header:'+f)
                    headers[f].add(thome)
                new=member_retype_text(texts.get(f,(ROOT/f).read_text()),rec,member,spelling,slot)
                if new is None:raise ValueError('member_declaration_shape:'+n)
                texts[f]=new
                for sf,fn in msites.get(n if slot is None else re.sub(r'#\d+$','',n),()):
                    if sf.startswith('src/') and (a.allow_modules or not sf.startswith('src/dungeon/modules/')):
                        touched[sf].add(fn.split('@')[0])
            for n,v in comp.items():
                if not n.startswith('P:'):continue
                key=n[2:].rpartition('#')[0];name=key.split('@')[0];idx=int(n.rpartition('#')[2]);rec=g.record_of(v['t']);home=(g.records.get(rec) or {}).get('file','')
                for f in sorted(ix.typed.get(name,())):
                    old=texts.get(f,(ROOT/f).read_text())
                    spelling=v['t']
                    if f.endswith('.h') and rec and re.fullmatch(r'[A-Za-z_]\w*',rec):
                        spelling='struct '+rec+' *'
                    new=P.respell_in_text(old,name,idx,spelling)
                    if new is not None and spelling.startswith('struct '):
                        forward='struct '+rec+';\n'
                        guard=re.search(r'(?m)^#define [A-Za-z_]\w*[^\n]*\n',new)
                        at=guard.end() if guard else 0
                        if forward not in new[:at+len(forward)+2]:
                            new=new[:at]+forward+new[at:]
                    if new is not None:
                        if f.startswith('src/dungeon/modules/') and not a.allow_modules:raise ValueError('module_declaration:'+f)
                        texts[f]=new
                        if home and home!=f and not (f.endswith('.h') and spelling.startswith('struct ')):headers[f].add(home)
            for f,hs in headers.items():
                for h in hs:
                    # Existing include closure already provides the type in most declarations.
                    text=texts.get(f,(ROOT/f).read_text())
                    inc='#include \"'+h.removeprefix('include/')+'\"'
                    if f.endswith('.h'):
                        text=re.sub(r'(?m)^'+re.escape(inc)+r'\s*\n', '', text)
                    elif h in P.header_closure(ROOT,f):
                        continue
                    texts[f]=P.ensure_include(text,h)
            texts={f:t for f,t in texts.items() if t!=(ROOT/f).read_text()}
            if not texts:raise ValueError('no_changes')
            # Compare every direct source consumer of a changed declaration.
            consumers=set(f for f in texts if f.endswith('.c'))|{f for f in touched if f.endswith('.c')}
            clean_touched=collections.defaultdict(set,{f:set(names) for f,names in touched.items()})
            for n in comp:
                if not n.startswith('P:'):continue
                for call in g.calls_to.get(n[2:].rpartition('#')[0],()):
                    f=call['file']
                    if f.startswith('src/') and f.endswith('.c') and (a.allow_modules or not f.startswith('src/dungeon/modules/')):
                        clean_touched[f].add(call['caller'].split('@')[0]);consumers.add(f)
            for n in comp:
                if n.startswith('P:'):consumers.update(ix.callers.get(n[2:].rpartition('#')[0].split('@')[0],()))
            for f in sorted(consumers):
                if f.startswith('src/dungeon/modules/') and not a.allow_modules:continue
                backups[f]=(ROOT/f).read_text()
            before_native={f:P.native_keys(ROOT,f)[1] for f in sorted(consumers) if f in backups}
            for f,t in texts.items():backups.setdefault(f,(ROOT/f).read_text());(ROOT/f).write_text(t)
            units.drop(texts)
            # functions that keep views on purpose ("MATCH:" notes: the views are what retail's bytes need) are
            # retyped but not folded
            for f in list(touched):
                text=(ROOT/f).read_text() if (ROOT/f).exists() else ''
                touched[f]={fn for fn in touched[f] if not match_note(text,fn)}
                if not touched[f]:del touched[f]
            for iteration in range(2):
                folded=P.fold_touched(ROOT,sorted(touched),touched)
                if not folded:break
                for f,t in folded.items():(ROOT/f).write_text(t)
            import clean_views
            for f,t in clean_views.clean(ROOT,clean_touched).items():(ROOT/f).write_text(t)
            for f in before_native:
                now=P.native_keys(ROOT,f)[1]
                bc=collections.Counter((e[0],P.native_kind(e[3])) for e in before_native[f]);ac=collections.Counter((e[0],P.native_kind(e[3])) for e in now)
                extra=list((ac-bc).elements())
                if extra:
                    (a.out/(cid+'.native.json')).write_text(json.dumps(dict(file=f,before=before_native[f],after=now),indent=1))
                    raise ValueError('new_native:'+f+':'+str(extra[:3]))
            changed={f:(ROOT/f).read_text() for f in backups if (ROOT/f).read_text()!=backups[f]}
            outside=sorted(f for f in changed if a.scope and not f.startswith(tuple(a.scope)))
            if outside:raise ValueError('outside_scope:'+','.join(outside[:3])+(' +%d'%(len(outside)-3) if len(outside)>3 else ''))
            delta=sum(P.casts_of(f,t)-P.casts_of(f,backups[f]) for f,t in changed.items())
            if delta>=0 and not (a.allow_zero and delta==0):
                raise ValueError('no_measured_cast_reduction:'+str(delta))
            record=dict(transaction=cid,status='applied',reason='',delta=delta,verdict='bridge' if delta==0 else data['verdict'],files=list(changed),nodes=list(comp))
            (a.out/(cid+'.before.json')).write_text(json.dumps({f:backups[f] for f in changed}))
        except Exception as exc:
            for f,t in backups.items():(ROOT/f).write_text(t)
            record=dict(transaction=cid,status='hold',reason=str(exc).replace(str(ROOT)+'/', ''),delta=0)
        units.drop(backups);result.append(record);print(json.dumps(record),flush=True)
        (a.out/'results.json').write_text(json.dumps(result,indent=1))
    P.assignable=real_assign;P.value_into=real_value
if __name__=='__main__':main()
