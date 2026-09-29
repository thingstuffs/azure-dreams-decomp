"""fmt_c.py - whitespace-only C reformatter (round 80, written by lane r80_sonnet_fmt1): 4-space K&R, one statement
per line, spaces around binary operators, goto labels at column 0, lines wrapped at 120. The C token sequence,
comment text and preprocessor lines are unchanged by construction (callers must still check: tools/fmt_c.py is
used by tools/fmt_tree.py, which refuses any file whose tokens change and gates the tree).

    python3 tools/fmt_c.py SRC DST
"""
import re, sys
W = 120
TOK = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\d[\w.]*|>>=|<<=|->|\+\+|--|&&|\|\||<<|>>|[<>=!+\-*/%&|^]=|\.\.\.|\S')

def scan(line, in_c):
    toks = []; i = 0; n = len(line)
    while i < n:
        if in_c:
            j = line.find('*/', i)
            if j < 0:
                toks.append(('c', line[i:], i, n)); return toks, True
            toks.append(('c', line[i:j+2], i, j+2)); i = j+2; in_c = False; continue
        if line[i].isspace(): i += 1; continue
        if line.startswith('/*', i):
            j = line.find('*/', i+2)
            if j < 0:
                toks.append(('c', line[i:], i, n)); return toks, True
            toks.append(('c', line[i:j+2], i, j+2)); i = j+2; continue
        if line.startswith('//', i):
            toks.append(('lc', line[i:], i, n)); return toks, False
        m = TOK.match(line, i)
        t = m.group(0)
        k = 'str' if t[0] in '"\'' else 'id' if (t[0].isalpha() or t[0] == '_') else 'num' if t[0].isdigit() else 'p'
        toks.append((k, t, i, m.end())); i = m.end()
    return toks, False

def code(toks):
    return [t for t in toks if t[0] not in ('c', 'lc')]

# ---------- pass 1: split crammed lines ----------
HDR = ('if', 'for', 'while', 'switch')

def split_line(line, st):
    toks, st['inc'] = scan(line, st['inc0'])
    ct = code(toks)
    if not ct:
        return [line]
    match = {}; stk = []
    for idx, t in enumerate(ct):
        if t[1] == '{': stk.append(idx)
        elif t[1] == '}' and stk: match[stk.pop()] = idx
    short = len(line.rstrip()) <= W
    stack = st['braces']
    par = st['paren']
    cuts = []
    ternary = 0
    inline_until = -1
    expanded = 0
    n = len(ct)
    # paren open positions for header detection
    popen = []
    for idx, t in enumerate(ct):
        s = t[1]
        nxt = ct[idx+1] if idx+1 < n else None
        if inline_until >= 0:
            if idx == inline_until:
                inline_until = -1; stack.pop()
            elif s == '{': stack.append('init')
            elif s == '}': stack.pop()
            continue
        if s in '([':
            par += 1; popen.append(idx); continue
        if s in ')]':
            par -= 1
            o = popen.pop() if popen else -1
            if par == 0 and s == ')' and nxt is not None:
                hdr = o > 0 and ct[o-1][1] in HDR
                if hdr and nxt[1] not in ('{', ';'):
                    cuts.append(nxt[2])
            continue
        if par > 0:
            continue
        if s == ';':
            ternary = 0
            if nxt: cuts.append(nxt[2])
        elif s == '?': ternary += 1
        elif s == ':':
            if ternary: ternary -= 1
            elif nxt:
                j = idx
                while j > 0 and ct[j-1][1] not in (';', '{', '}', ':'): j -= 1
                if ct[j][1] in ('case', 'default') or (ct[j][0] == 'id' and j == idx-1):
                    cuts.append(nxt[2])
        elif s == '{':
            p = ct[idx-1][1] if idx > 0 else None
            if p in (')', 'else', 'do', ':', ';', '}') or p is None:
                k = 'block'
            elif p in ('=', ',', '{'): k = 'init'
            else: k = 'type'
            if k != 'block' and idx in match and (short or expanded > 0):
                inline_until = match[idx]; stack.append(k); continue
            if k != 'block': expanded += 1
            if k == 'block' and not stack and idx > 0 and p == ')' and nxt is not None:
                cuts.append(t[2])
            if nxt: cuts.append(nxt[2])
            stack.append(k)
        elif s == '}':
            k = stack.pop() if stack else 'block'
            if k != 'block' and expanded > 0: expanded -= 1
            if idx > 0: cuts.append(t[2])
            if nxt and k == 'block' and nxt[1] not in ('else', 'while', ';', ',', ')'):
                cuts.append(nxt[2])
        elif s == 'else':
            if nxt and nxt[1] not in ('{', 'if'): cuts.append(nxt[2])
        elif s == 'do':
            if nxt and nxt[1] != '{': cuts.append(nxt[2])
    st['paren'] = par
    lim = len(line.rstrip())
    cuts = sorted(set(c for c in cuts if 0 < c < lim))
    out = []; prev = 0
    for c in cuts:
        out.append(line[prev:c]); prev = c
    out.append(line[prev:])
    return [o.strip() for o in out if o.strip()]

def pass1(text):
    st = {'paren': 0, 'braces': [], 'inc': False, 'inc0': False}
    res = []
    for line in text.split('\n'):
        if st['inc0']:
            toks, st['inc'] = scan(line, True)
            res.append((line, None, True)); st['inc0'] = st['inc']; continue
        if line.lstrip().startswith('#') and st['paren'] == 0:
            res.append((line.strip(), 0, False)); continue
        if not line.strip():
            res.append(('', 0, False)); continue
        oi = len(line) - len(line.lstrip())
        pieces = split_line(line, st)
        st['inc0'] = st['inc']
        crammed = len(pieces) > 1 or re.search(r'\b(if|for|while|switch)\(|\)\{|\w(==|&&|\|\|)\w|\w=[\w(*]|\{\w|\w\}|;\w', line)
        for p in pieces:
            if crammed and not p.startswith('#'): p = fix_space(p)
            res.append((p, oi, False))
    return res

# ---------- spacing fixer (only zero-gap pairs) ----------
KW = {'if', 'for', 'while', 'switch', 'return', 'else', 'do', 'case'}
BIN = {'=', '==', '!=', '<=', '>=', '<', '>', '&&', '||', '+', '/', '%', '|', '^', '<<', '>>', '+=', '-=', '*=', '/=', '%=', '&=', '|=', '^=', '<<=', '>>=', '?', ':', '*', '&', '-'}
VAL = ('id', 'num', 'str')

def fix_space(piece):
    toks, _ = scan(piece, False)
    if any(t[0] in ('c', 'lc') for t in toks):
        # split off trailing comment(s) only
        first = next(i for i, t in enumerate(toks) if t[0] in ('c', 'lc'))
        head = piece[:toks[first][2]]
        tail = piece[toks[first][2]:]
        if any(t[0] not in ('c', 'lc') for t in toks[first:]):
            return piece
        return fix_space(head.rstrip()) + piece[len(head.rstrip()):]
    tern = any(t[1] == '?' for t in toks)
    res = piece[:toks[0][2]] if toks else piece
    for i, t in enumerate(toks):
        if i == 0:
            res += t[1]; continue
        p = toks[i-1]
        gap = piece[p[3]:t[2]] if False else piece[p[2]+len(p[1]):t[2]]
        if gap == '':
            pp = toks[i-2] if i >= 2 else None
            ps, ts = p[1], t[1]
            need = False
            unary_prev = pp is None or pp[1] in ('(', '[', ',', ';', '{', '}', '=', 'return', '?', ':', '!', '~') or (pp[0] == 'p' and pp[1] not in (')', ']', '++', '--')) or (pp[0]=='id' and pp[1] in KW)
            if ps in KW and ts != ';': need = True
            elif ts == '{' and ps != '(': need = True
            elif ps == '{' and ts != '}': need = True
            elif ts == '}' and ps != '{': need = True
            elif ps == '}' and (t[0] == 'id'): need = True
            elif ps in (',', ';') and ts not in (')', ';'): need = True
            elif (ts == ':' or ps == ':') and not tern: pass
            elif ts in BIN or ps in BIN:
                # decide binary-ness of operator token
                if ts in BIN and ps not in BIN:
                    # ts is operator following a value
                    if p[0] in VAL or ps in (')', ']'):
                        if ts in ('*', '&', '-') and ps == ')': need = False
                        elif ts == '*' and p[0] == 'id' and i+1 < len(toks) and toks[i+1][1] in (')', '*'):
                            need = True   # pointer star: space before
                        elif ts == '*' and p[0] == 'id' and i+1 < len(toks) and toks[i+1][0] == 'id' and pp is not None and pp[1] in ('(', ',', ';', '{'):
                            need = True
                        else: need = True
                elif ps in BIN and ts not in BIN:
                    # after operator: space unless unary or pointer star
                    if ps in ('*', '&', '-'):
                        if unary_prev: need = False
                        elif ps == '*' and pp is not None and pp[0] == 'id' and (ts in (')', '*') ):
                            need = False
                        elif ps == '*' and pp is not None and pp[0] == 'id' and t[0] == 'id' and i >= 3 and toks[i-3][1] in ('(', ',', ';', '{'):
                            need = False
                        else: need = True
                    else: need = True
                elif ps in BIN and ts in BIN:
                    need = ps not in ('*', '&', '-', '!')
            if need: res += ' '
        else:
            pass
        res += gap + t[1]
    return res

# ---------- pass 2: indent ----------
CONT_END = {'=', '+', '-', '*', '/', '%', '&', '|', '^', '&&', '||', '<<', '>>', '==', '!=', '<', '>', '<=', '>=', '?', '+=', '-=', '*=', '/=', '|=', '&=', '^=', ',', '<<=', '>>='}
CONT_START = {'&&', '||', '?'}
CTL = ('if', 'for', 'while', 'else', 'do')

class E:
    def __init__(s, base, close, kind):
        s.base = base; s.close = close; s.kind = kind; s.bl = 0

def pass2(entries):
    out = []   # list of dict(text, level or None(raw), cont(bool))
    stack = [E(0, 0, 'top')]
    paren = 0
    cont = False        # inside a multi-line statement
    stmt_level = 0; stmt_oi = 0
    last_hdr = None     # 'ctl' | 'switch' | None
    last_level = 0
    prev_case = False
    stmt_first = None
    inc = False
    pstack = []
    for text, oi, rawc in entries:
        if rawc:
            out.append({'raw': text}); continue
        if text == '':
            out.append({'raw': ''}); continue
        if text.startswith('#') :
            out.append({'raw': text}); continue
        toks, inc = scan(text, False)
        ct = code(toks)
        if not ct:
            # comment-only line
            lvl = stack[-1].base + (1 if stack[-1].kind == 'switch' else 0) + stack[-1].bl
            if cont: lvl = None
            out.append({'text': text, 'level': stmt_level if False else lvl, 'cont': cont, 'oi': oi, 'stmt_oi': stmt_oi, 'stmt_level': stmt_level, 'comment_only': True, 'label': False})
            continue
        f = ct[0][1]; l = ct[-1][1]
        Et = stack[-1]
        continuing = cont
        if not continuing and f in CONT_START and out:
            continuing = True
        entry = None
        if continuing:
            X = oi
            cand = X + (stmt_level * 4 - stmt_oi)
            newind = cand
            for (oc, nc, li) in pstack[-1:]:
                if 1 <= abs(cand - (nc + 1)) <= 4:
                    newind = nc + 1
            newind = max(newind, stmt_level * 4 + 4)
            out.append({'text': text, 'level': stmt_level, 'cont': True, 'oi': oi, 'stmt_oi': stmt_oi, 'label': False, 'ind': newind})
            for t in ct:
                if t[1] in '([': pstack.append((oi + t[2], newind + t[2], newind))
                elif t[1] in ')]' and pstack: pstack.pop()
            pa = paren + sum(1 if t[1] in '([' else -1 if t[1] in ')]' else 0 for t in ct)
            if pa == 0 and l == '{':
                if any(t[1] == 'switch' for t in ct) or stmt_first == 'switch':
                    stack.append(E(stmt_level, stmt_level, 'switch'))
                else:
                    stack.append(E(stmt_level + 1, stmt_level, 'block'))
        else:
            label = False
            # lone '{' join
            if f == '{' and len(ct) == 1 and last_hdr and len(stack) > 1 and out and 'text' in out[-1] and not out[-1].get('has_c') and not toks[-1][0] in ('c','lc'):
                prevo = out[-1]
                prevo['text'] += ' {'
                if last_hdr == 'ctl': Et.bl -= 1
                kind = 'switch' if last_hdr == 'switch' else 'block'
                lv = last_level
                stack.append(E(lv if kind == 'switch' else lv + 1, lv, kind))
                last_hdr = None; prev_case = False
                cont = False
                continue
            if f == '}':
                e = stack.pop() if len(stack) > 1 else stack[-1]
                level = e.close
                Et = stack[-1]
            elif f in ('case', 'default') and Et.kind == 'switch':
                level = Et.base
            elif len(ct) >= 2 and ct[0][0] == 'id' and ct[1][1] == ':' and f not in ('case', 'default'):
                label = True; level = 0
            else:
                level = Et.base + (1 if Et.kind == 'switch' else 0) + Et.bl
                if f == '{' and prev_case and Et.kind == 'switch':
                    level = Et.base
                if f == '{' and last_hdr and Et.kind != 'init':
                    pass
            if f == '{' and last_hdr == 'ctl' and len(stack) >= 1 and False:
                pass
            stmt_level = level; stmt_oi = oi; last_level = level
            out.append({'text': text, 'level': level, 'cont': False, 'oi': oi, 'stmt_oi': oi, 'label': label, 'ind': (0 if label else level * 4)})
            pstack = []
            for t in ct:
                if t[1] in '([': pstack.append((oi + t[2], (0 if label else level * 4) + t[2], (0 if label else level*4)))
                elif t[1] in ')]' and pstack: pstack.pop()
            # braces effect
            loc = 0
            n = len(ct)
            for idx, t in enumerate(ct):
                s = t[1]
                if s == '{':
                    if idx == n-1:
                        pk = ct[idx-1][1] if idx > 0 else None
                        if pk in ('=', ',', '{') or (Et.kind == 'init' and pk not in (')', 'else', 'do')):
                            kd = 'init'
                        else:
                            kd = 'switch' if 'switch' in [x[1] for x in ct[:idx]] and ct[0][1] in ('switch', '}') else 'block'
                        if kd == 'switch':
                            stack.append(E(level, level, 'switch'))
                        elif f == '{' and prev_case and Et.kind == 'switch':
                            stack.append(E(level + 1, level, 'block'))
                        else:
                            stack.append(E(level + 1, level, kd))
                        if f != '}' and idx == 0: pass
                    else:
                        loc += 1
                elif s == '}':
                    if idx == 0 and f == '}':
                        pass
                    elif loc > 0:
                        loc -= 1
            Et = stack[-1]
            if f == '{' and False: pass
        # statement-level state updates
        # paren tracking over line
        for t in ct:
            if t[1] in '([': paren += 1
            elif t[1] in ')]': paren -= 1
        if paren > 0:
            cont = True
        else:
            Et = stack[-1]
            lc = l
            if lc in CONT_END and Et.kind != 'init' and not (lc == ',' and False):
                cont = True
            else:
                cont = False
        if not cont:
            Et = stack[-1]
            first = None
            if not continuing:
                first = f
            # header detection: use statement first token(s)
            sf = ct[0][1] if not continuing else stmt_first
            if not continuing:
                stmt_first = f
                if f == '}' and len(ct) > 1: stmt_first = ct[1][1]
            sf = stmt_first
            last_hdr = None
            prev_case = False
            if l == '{':
                pass
            elif l == ';' or (l == '}'):
                if Et.kind != 'init':
                    Et.bl = 0
            elif l == ':' and (f in ('case', 'default')):
                prev_case = True
            elif Et.kind != 'init' and ((l == ')' and sf in ('if', 'for', 'while', 'else')) or l in ('else', 'do')):
                Et.bl += 1
                last_hdr = 'ctl'
            elif l == ')' and sf == 'switch':
                last_hdr = 'switch'
    return out

def emit(out):
    lines = []
    for o in out:
        if 'raw' in o:
            lines.append(o['raw']); continue
        t = o['text']
        if o.get('label'):
            lines.append(t); continue
        if 'ind' in o:
            lines.append(' ' * o['ind'] + t); continue
        if o.get('comment_only') and o['level'] is None:
            lines.append(' ' * (o['stmt_level'] * 4 + 4) + t); continue
        if o['cont']:
            rel = o['oi'] - o['stmt_oi']
            if rel < 4: rel = 4
            ind = o['level'] * 4 + rel
        else:
            ind = o['level'] * 4
        if o.get('comment_only') and o['level'] is None:
            ind = o['stmt_level'] * 4 + 4
        lines.append(' ' * ind + t)
    return lines


# ---------- wrap ----------
def wrap_line(line):
    if len(line) <= W: return [line]
    toks, _ = scan(line, False)
    ct = code(toks)
    if not ct: return [line]
    lastcode_end = ct[-1][3] if len(ct[-1]) > 3 else ct[-1][2] + len(ct[-1][1])
    if lastcode_end <= W: return [line]
    ind = len(line) - len(line.lstrip())
    cind = ind + 4
    lines = []
    cur = line
    curind = ind
    first = True
    while True:
        toks, _ = scan(cur, False)
        ct = code(toks)
        end = ct[-1][2] + len(ct[-1][1])
        if end <= W or not ct: lines.append(cur); break
        # candidates: (pos, depth) where we cut before token idx
        depth = 0; cands = []
        for i, t in enumerate(ct):
            s = t[1]
            if s in '([{': depth += 1
            elif s in ')]}': depth -= 1
            if i+1 < len(ct):
                nx = ct[i+1]
                if s == ',' : cands.append((nx[2], depth))
                elif nx[1] in ('&&', '||', '?') : cands.append((nx[2], depth))
                elif s in ('=',) and depth == 0: cands.append((nx[2], depth))
                elif nx[1] in ('==','!=','<=','>=','+','-','|','^','<<','>>','<','>') and (t[0] in ('id','num','str') or s in (')',']')): cands.append((nx[2], depth + 1))
        good = [c for c in cands if c[0] <= W and c[0] > curind + 8 and c[0] > len(cur) - len(cur.lstrip()) + 10]
        if not good:
            good = [c for c in cands if c[0] > curind + 8]
            if not good: lines.append(cur); break
            pos = good[0][0]
        else:
            m = min(c[1] for c in good)
            # prefer shallowest depth but not absurdly early: choose rightmost with depth <= m+1... use rightmost among min depth if it uses >60% width else rightmost overall
            shallow = [c for c in good if c[1] == m]
            pos = shallow[-1][0]
            if pos < W * 0.55:
                pos = good[-1][0]
        head = cur[:pos].rstrip(); rest = cur[pos:].lstrip()
        lines.append(head)
        cur = ' ' * cind + rest; curind = cind
    return lines

def format_text(text):
    text = text.replace('\t', '    ') if False else text
    ents = pass1(text)
    out = pass2(ents)
    lines = emit(out)
    res = []
    for l in lines:
        res.extend(wrap_line(l))
    # collapse >2 blank lines
    o2 = []; b = 0
    for l in res:
        if l.strip() == '': b += 1
        else: b = 0
        if b <= 2: o2.append(l.rstrip() if l.strip()=='' else l)
    return '\n'.join(o2)

if __name__ == '__main__':
    src, dst = sys.argv[1:3]
    open(dst, 'w').write(format_text(open(src).read()))
