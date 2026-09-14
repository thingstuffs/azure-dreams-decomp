"""Natural producer/consumer histories. No compiler calls or row identities.

The branch transformations distribute existing work over an existing predicate.
They do not introduce a predicate, a dummy statement, or a compiler-only scope.
All matches are conservative syntax proposals; the caller must verify bytes.
"""
import collections
from pathlib import Path
import re
import sys

ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
if str(ROOT / 'tools') not in sys.path:
    sys.path.insert(0, str(ROOT / 'tools'))
from pin_census import arm_labels, sites_of
from pin_sites import erase_many, fn_bounds, params_of
from xform.t29_addrsym import mask_comments, decls_of, sym_expr
from xform.t41b_gotoloop_while import _close
from xform.t51_sched_order import declarations, candidates as order_candidates
from xform import natural, t41_gotoloop, t41b_gotoloop_while, t44_doloop_greedy
from xform import t42_sinkcopy

ID = r'[A-Za-z_]\w*'
ASSIGN = re.compile(r'(?m)^(?P<ind>[ \t]*)(?P<v>'+ID+r')\s*(?P<op>=|\|=|&=|\+=|-=|<<=|>>=)\s*(?P<rhs>[^;\n]+);')
CONTROL = re.compile(r'\b(?:if|else|while|for|do|goto|return|break|continue|case|switch)\b|[{}#]')
SIDE = re.compile(r'\+\+|--|(?<![=!<>])=(?!=)|\b(?:func_\w+|abs)\s*\(')


def masked(text):
    t = mask_comments(text)
    t = re.sub(r'//[^\n]*', lambda m: ' '*len(m[0]), t)
    return ''.join(re.sub(r'[^\n]', ' ', s) if lab in ('port', 'dead') else s
                   for s, lab in zip(t.splitlines(True), arm_labels(text)))


def unscored_bytes(text):
    return tuple(s for s, lab in zip(text.splitlines(True), arm_labels(text)) if lab in ('port', 'dead'))


def edits(text, changes):
    for a, b, val in sorted(changes, reverse=True):
        text = text[:a] + val + text[b:]
    return text


def var_of(site):
    m = re.match(ID, site[2])
    return m[0] if m else None


def erase_sites(text, chosen):
    m = masked(text)
    safe = []
    for s in chosen:
        if re.search(r'\b(?:if|while|for)\s*\([^;{}]*\)\s*$|\b(?:else|do)\s*$|\b'+ID+r'\s*:\s*$', m[:s[3]]):
            # STMT_RE spans start at '^': keep the pin's own indentation on the null statement.
            ind = re.match(r'[ \t]*', text[s[3]:s[4]])[0]
            s = tuple(s[:6])+(ind + ';' + ('\n' if text[s[4]-1:s[4]] == '\n' else ''),)
        safe.append(s)
    return erase_many(text, safe, clean_notes=True)


def admissible(before, after):
    """Stricter than evaluator: byte-identical unscored arms, no growing pin kind.

    Check token counts as well as census sites, so an uncounted wrapper/asm cannot
    evade the rule. Existing scaffolding is preserved or removed, never expanded.
    """
    if unscored_bytes(before) != unscored_bytes(after):
        return False
    old = collections.Counter(s[1] for s in sites_of(before))
    new = collections.Counter(s[1] for s in sites_of(after))
    if new-old:
        return False
    patterns = (r'\bASM_\w+\b', r'\b(?:__asm__|__asm|asm|volatile|__volatile__)\b',
                r'\bwhile\s*\(\s*0\s*\)', r'\bfor\s*\(\s*;\s*0\s*;',
                r'\bif\s*\(\s*[01]\s*\)', r'\(\s*\{')
    for pat in patterns:
        if collections.Counter(re.findall(pat, mask_comments(after)))-collections.Counter(re.findall(pat, mask_comments(before))):
            return False
    return True


def branches(text):
    m = masked(text)
    for k in re.finditer(r'\bif\s*\(', m):
        p = k.end()-1; pe = _close(m, p, '(', ')')
        if pe is None: continue
        b = re.match(r'\s*\{', m[pe:])
        if not b: continue
        o = pe+b.end()-1; c = _close(m, o, '{', '}')
        if c is None: continue
        eo = ec = None; end = c
        e = re.match(r'\s*else\s*\{', m[c:])
        if e:
            eo = c+e.end()-1; ec = _close(m, eo, '{', '}')
            if ec is None: continue
            end = ec
        elif re.match(r'\s*else\b', m[c:]): continue
        yield dict(start=k.start(), p=p, pe=pe, o=o, c=c, eo=eo, ec=ec, end=end)


def simple_stmt(s):
    # Complete one-line expression statement, no declarations or asm.
    q = s.strip()
    if not q or not q.endswith(';') or q.count(';') != 1 or CONTROL.search(q) or 'ASM_' in q:
        return False
    return not re.match(r'(?:register\s+)?'+ID+r'\s+\**\s*'+ID+r'\s*(?:=|;)', q)


def branch_insert(text, brace, body, ind):
    start=text.rfind('\n',0,brace)+1
    lines='\n'.join(ind+'    '+s.strip() for s in body.splitlines() if s.strip())+'\n'
    if text[start:brace].strip():return (brace,brace,'\n'+lines+ind)
    return (start,start,lines)


def branch_shapes(text, focus):
    m = masked(text)
    for br in sorted(branches(text), key=lambda b: min(abs(b['start']-focus), abs(b['end']-focus))):
        if min(abs(br['start']-focus), abs(br['end']-focus)) > 1600: continue
        lo, end = br['start'], br['end']
        ind=re.match(r'[ \t]*',text[text.rfind('\n',0,lo)+1:])[0]
        if '#' in m[lo:end]: continue
        cond = m[br['p']+1:br['pe']-1]
        # Distribute a real suffix through the join, including an implicit else.
        # Existing arms must reach that join on every path.
        if not re.search(r'\b(?:goto|return|break|continue)\b|\b'+ID+r'\s*:', m[br['o']:end]):
            pos = end; span = ''
            for n in range(1, 4):
                nxt = re.match(r'\s*[^\n;{}]+;', m[pos:])
                if not nxt or not simple_stmt(nxt[0]): break
                stop = pos+nxt.end()
                span += text[pos:stop]; pos = stop
                if not span.strip(): break
                ch = [(end, stop, ''), branch_insert(text,br['c']-1,span,ind)]
                if br['eo'] is not None:
                    ch.append(branch_insert(text,br['ec']-1,span,ind))
                else:
                    body='\n'.join(ind+'    '+s.strip() for s in span.splitlines() if s.strip())
                    ch.append((end, end, ' else {\n'+body+'\n'+ind+'}'))
                yield 'join-consumer:%d:%d' % (m.count('\n', 0, lo)+1, n), edits(text, ch)
        # Move an existing prefix into both arms, before their work. The branch
        # condition must be pure and independent of all the prefix's SETs.
        if SIDE.search(cond) or re.search(ID+r'\s*\(', cond): continue
        tail = m[:lo]
        ps = list(re.finditer(r'(?m)^[ \t]*[^\n;{}]+;[ \t]*\n?', tail))
        span_start = lo
        for n, pr in enumerate(reversed(ps[-3:]), 1):
            if m[pr.end():span_start].strip() or not simple_stmt(pr[0]): break
            a = ASSIGN.match(pr[0])
            # Prefix stores could affect a memory-valued predicate. Only local
            # assignments are moved, with distinct predicate input identifiers.
            if not a or a['op'] != '=' or re.search(r'\b'+a['v']+r'\b', cond): break
            if re.search(ID+r'\s*\(|\+\+|--|\bvolatile\b', a['rhs']): break
            span_start = pr.start(); span = text[span_start:lo].strip()
            body='\n'.join(ind+'    '+s.strip() for s in span.splitlines() if s.strip())
            ch = [(span_start, lo, ind), (br['o']+1, br['o']+1, '\n'+body)]
            if br['eo'] is not None:
                ch.append((br['eo']+1, br['eo']+1, '\n'+body))
            else:
                ch.append((end, end, ' else {\n'+body+'\n'+ind+'}'))
            yield 'branch-producer:%d:%d' % (m.count('\n', 0, lo)+1, n), edits(text, ch)


def role_shapes(text, focus_var):
    """Exchange saved/source roles only when a real later assignment exists."""
    m = masked(text)
    ds = declarations(text)
    for d in ASSIGN.finditer(m):
        v, a = d['v'], d['rhs'].strip()
        if d['op'] != '=' or not re.fullmatch(ID, a) or v == a: continue
        if focus_var not in (v, a): continue
        bounds = fn_bounds(m, d.start())
        if not bounds: continue
        params = params_of(m, bounds[0]); types = []
        for name in (v, a):
            decs = decls_of(m, name)
            if len(decs) == 1:
                ty, ptr, (st, en) = decs[0]
                if st > d.start() or m[bounds[0]:st].count('{')-m[bounds[0]:st].count('}') != 1: break
                types.append((ty, ptr))
            elif not decs and name in params:
                ty, ptr = params[name]; types.append((ty, int(ptr)))
            else: break
        if len(types) != 2 or types[0] != types[1]: continue
        body = m[bounds[0]:bounds[1]]
        if re.search(r'\bgoto\b|(?m:^\s*'+ID+r'\s*:)', body): continue
        if any(re.search(r'&\s*\b'+x+r'\b', body) for x in (v, a)): continue
        if m[bounds[0]:d.start()].count('{')-m[bounds[0]:d.start()].count('}') != 1: continue
        tail = m[d.end():bounds[1]]
        if not re.search(r'\b(?:'+v+'|'+a+r')\s*(?:\+\+|--|(?:[-+*/&|^]|<<|>>)?=(?!=))', tail): continue
        changes = []
        for k in re.finditer(r'\b(?:'+v+'|'+a+r')\b', tail):
            p = d.end()+k.start()
            if re.search(r'(?:\.|->)\s*$', m[max(0,p-12):p]): continue
            changes.append((p, d.end()+k.end(), a if k[0] == v else v))
        yield 'source-role:'+v+':'+a, edits(text, changes)


def source_update_shapes(text,focus_var):
    """m2c's later local receives a real update that can belong to the source.

    saved = source; next = source + e; ...use(next,saved)...
    becomes saved = source; source = source + e; ...use(source,saved)...
    The original source must be dead after next's definition; no invented tie.
    """
    m=masked(text)
    for d in ASSIGN.finditer(m):
        v,a=d['v'],d['rhs'].strip()
        if d['op']!='=' or not re.fullmatch(ID,a) or v==a or focus_var not in (v,a):continue
        bounds=fn_bounds(m,d.start())
        if not bounds:continue
        body=m[bounds[0]:bounds[1]]
        if re.search(r'\bgoto\b|\b(?:while|for|do)\b',body):continue
        pars=params_of(m,bounds[0]);ad=decls_of(m,a)
        if len(ad)==1:aty=ad[0][:2]
        elif not ad and a in pars:aty=(pars[a][0],int(pars[a][1]))
        else:continue
        for n in ASSIGN.finditer(m,d.end(),bounds[1]):
            w=n['v'];wd=decls_of(m,w)
            if w in (a,v) or n['op']!='=' or len(wd)!=1 or wd[0][:2]!=aty:continue
            if not re.search(r'\b(?:'+a+'|'+v+r')\b',n['rhs']):continue
            if re.fullmatch(ID,n['rhs'].strip()):continue
            if any(re.search(r'&\s*\b'+x+r'\b',body) for x in (a,v,w)):continue
            if re.search(r'\b'+a+r'\b',m[n.end():bounds[1]]):continue
            if re.search(r'[{}]|\b(?:if|else|return)\b',m[d.end():n.start()]):continue
            tail=m[n.start():bounds[1]];changes=[]
            for k in re.finditer(r'\b'+w+r'\b',tail):
                p=n.start()+k.start()
                if re.search(r'(?:\.|->)\s*$',m[max(0,p-12):p]):continue
                changes.append((p,n.start()+k.end(),a))
            out=edits(text,changes)
            # Drop the now-unused declaration only when the declaration is its
            # sole remaining mention and had no initializer/runtime work.
            dec=decls_of(masked(out),w)
            if len(dec)==1 and len(re.findall(r'\b'+w+r'\b',masked(out)))==1:
                st,en=dec[0][2]
                if '=' not in out[st:en] and 'ASM_' not in out[st:en]:out=edits(out,[(st,en,'')])
            yield 'source-update:'+v+':'+a+':'+w,out


def value_shapes(text, v):
    m = masked(text)
    if not v: return
    ds = decls_of(m, v)
    for d in ASSIGN.finditer(m):
        if d['v'] != v or d['op'] != '=': continue
        rhs = text[d.start('rhs'):d.end('rhs')].strip()
        low = re.fullmatch(r'(.+?)\s*&\s*(0[xX][fF]{2}|255|0[xX][fF]{4}|65535)[UuLl]*', rhs)
        if low:
            ty = 'u8' if int(low[2],0) == 255 else 'u16'
            # The same cast is already in the value: do not emit a doubled cast.
            if not re.match(r'\(\s*'+ty+r'\s*\)', low[1].strip()):
                yield 'producer-mode:'+v, edits(text, [(d.start('rhs'),d.end('rhs'),'('+ty+')('+low[1]+')')])
        # A real truncation is already in the value. Try giving that producer's
        # destination the corresponding declared mode; vf rejects other uses
        # whose values need a wider lifetime.
        narrow = re.match(r'^\((u8|s8|u16|s16)\)', rhs)
        if narrow and len(ds) == 1 and ds[0][1] == 0:
            ty, _, (a,b) = ds[0]
            if ty in ('s32','u32','int','short','u16','s16') and ty != narrow[1]:
                seg=text[a:b]; t=re.search(r'\b'+re.escape(ty)+r'\b',seg)
                if t: yield 'declared-producer-mode:'+v, edits(text,[(a+t.start(),a+t.end(),narrow[1])])
        # Non-page literal addresses retain their local; page literals are
        # deliberately outside this tool's family.
        addr = re.fullmatch(r'(?:\([^()]+\)\s*)?(0x8[0-9A-Fa-f]{7})[uUlL]*',rhs)
        if addr and int(addr[1],16)&65535 and len(ds)==1:
            ty, ptr, _ = ds[0]; ext=set()
            # sym_expr's `want` is spelled 'u8 *' everywhere else (t29:253/269, t54:137).
            val=sym_expr(text,int(addr[1],16),ty+(' '+'*'*ptr if ptr else ''),ext)
            out=edits(text,[(d.start('rhs'),d.end('rhs'),val)])
            if ext:
                inc=list(re.finditer(r'(?m)^#include[^\n]*\n',out))
                if not inc: continue
                p=inc[-1].end();out=out[:p]+''.join(sorted(ext))+out[p:]
            yield 'address-symbol:'+v,out
        # load, update, store -> assignment from a real field update. Adjacent
        # statements only: one existing read and one existing write remain.
        tail=m[d.end():]
        store=re.match(r'\s*(?P<field>[^;\n]+?)\s*=\s*'+v+r'\s*;',tail)
        op=re.fullmatch(r'(?:\((?:u16|s16|u8|s8)\)\s*)?(?P<field>.+?)\s*(?P<op>[+-])\s*1',rhs)
        if store and op and re.sub(r'\s','',store['field'])==re.sub(r'\s','',op['field']):
            field=store['field'].strip()
            if not re.search(r'\+\+|--|'+ID+r'\s*\(',field):
                code=d['ind']+v+' = '+('++' if op['op']=='+' else '--')+'('+field+');'
                yield 'field-update:'+v, edits(text,[(d.start(),d.end()+store.end(),code)])
        # Distribution of an existing ternary is a real reaching-definition
        # join, provided the arms actually differ.
        q=re.fullmatch(r'([^?]+)\?([^?:]+):([^?:]+)',rhs)
        if q and q[2].strip()!=q[3].strip() and not re.search(r'\bASM_|[{}]',rhs):
            code=d['ind']+'if ('+q[1].strip()+') { '+v+' = '+q[2].strip()+'; } else { '+v+' = '+q[3].strip()+'; }'
            yield 'reaching-def:'+v,edits(text,[(d.start(),d.end(),code)])


def loop_shapes(text, pos):
    m=masked(text)
    for mod,kind in ((t41_gotoloop,'real-do-goto'),(t41b_gotoloop_while,'real-while-goto')):
        for k,lp in enumerate(mod.loops(text)):
            if not lp[0]-800<pos<lp[2]+800 or '#' in m[lp[0]:lp[2]]: continue
            label='keep_loop_'+str(k)
            while re.search(r'\b'+label+r'\b',m): label+='x'
            yield kind,mod.rewrite(text,lp,label)
    for lp in t44_doloop_greedy.loops(text):
        if not lp[0]-800<pos<lp[5]+800 or lp[6] in ('0','1'): continue
        if re.search(r'\b(?:break|continue)\b|#',m[lp[0]:lp[5]]): continue
        yield 'real-goto-do',t44_doloop_greedy.rewrite(text,lp)


def local_shapes(text, pos, v):
    # Mechanism families interleaved by caller; no huge allocation menu.
    yield from branch_shapes(text,pos)
    yield from role_shapes(text,v)
    yield from source_update_shapes(text,v)
    yield from value_shapes(text,v)
    yield from loop_shapes(text,pos)


def natural_shapes(text):
    gens=(natural.armstore_candidates,natural.dropcopy_candidates,natural.ret2break_candidates,
          natural.ptr2index_candidates,natural.postinc_candidates,natural.gotoloop_candidates,
          natural.splitcursor_candidates,natural.realloop_candidates,t42_sinkcopy.candidates)
    for gen in gens:
        yield from gen(text)


def order_shapes(text,line,v):
    for tag,t in order_candidates(text,line,v):
        if tag.startswith(('move:','fuse:','single-set:','commute:')):
            yield tag,t
