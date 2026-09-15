"""Control-flow move inventory over lane-won exemplar diffs: what did the lane change in labels, gotos, returns,
loops and arms?  Text only, on the pinless comment-free texts.

  GOTO2RET     a `goto L;` became `return ...;` / `break;` / `continue;` (gotos down, returns/breaks up, labels down)
  TAILDUP      a statement run that stood once after a label now appears in two or more places (label gone or its
               goto count dropped): the shared tail duplicated into its predecessors (GCC cross-jumps it back)
  TAILMERGE    the reverse: a run duplicated in two places now stands once after a new/existing label
  LOOPFORM     goto loop <-> do/while/for (loop keywords change while gotos/labels change the other way)
  ARMSWAP      an if condition negated (`!`, `==`<->`!=`, `<`<->`>=`) with the arms exchanged
  EARLYRET     a `return` added or removed inside an if without other statement changes (guard inversion)
  SWITCHFORM   case/switch/default lines change
  LABELMOVE    a label line moved (same label, different position) without duplication
  RETSPLIT     one `return` statement became two or more (or the reverse)
  OTHER-CTRL   control keywords changed but none of the above explains it

    cd <exemplar dir> && python3 tools/lanes/ctrlmoves.py . lane_won.txt [limit]

Round 29 (2026-09-15) over the lane-won diffs with a control-flow change (REG 76 / KEEP 64 / FENCE ~62): TAILMERGE 35/30/36,
TAILDUP 19/15/27, LOOPFORM 35/19/10, RETSPLIT 17/17/6, GOTO2RET 9/4/8, ARMSWAP 9/4/5, EARLYRET 6/9/4, OTHER 35/39/30 - the brief
of t67_tailform.  Writes <names>.ctrlmoves.json beside the names file.
"""
import re, sys, json, subprocess, collections
from pathlib import Path
ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools'))
from pin_census import sites_of
from pin_sites import erase_many
CMT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
LABEL = re.compile(r"^\s*([A-Za-z_]\w*)\s*:\s*$")
GOTO = re.compile(r"\bgoto\s+([A-Za-z_]\w*)\s*;")


def clean(t):
    t = CMT.sub("", erase_many(t, sites_of(t), clean_notes=True))
    return [re.sub(r"\s+", " ", l).strip() for l in t.split("\n")]


def stats(lines):
    txt = "\n".join(lines)
    return dict(goto=len(GOTO.findall(txt)), label=sum(1 for l in lines if LABEL.match(l)),
                ret=len(re.findall(r"\breturn\b", txt)), brk=len(re.findall(r"\bbreak\s*;", txt)),
                cont=len(re.findall(r"\bcontinue\s*;", txt)),
                loop=len(re.findall(r"\b(?:while|for|do)\b", txt)), case=len(re.findall(r"\b(?:case|default)\b", txt)),
                ifs=len(re.findall(r"\bif\s*\(", txt)), sw=len(re.findall(r"\bswitch\s*\(", txt)))


def tails(lines):
    """label -> the run of statement lines that follows it (until the next label/closing brace at depth 0 of the run)."""
    out = {}
    for i, l in enumerate(lines):
        m = LABEL.match(l)
        if not m: continue
        run = []
        for k in range(i + 1, min(len(lines), i + 12)):
            s = lines[k]
            if not s or LABEL.match(s) or s in ("}", "{"): break
            run.append(s)
            if re.match(r"(goto |return\b|break;|continue;)", s): break
        if run: out[m.group(1)] = tuple(run)
    return out


def runs(lines, n=2):
    c = collections.Counter()
    seq = [l for l in lines if l and not LABEL.match(l) and l not in ("{", "}")]
    for i in range(len(seq) - n + 1):
        c[tuple(seq[i:i + n])] += 1
    return c


def one(pre, post):
    a, b = clean(pre), clean(post)
    sa, sb = stats(a), stats(b)
    k = set(); notes = []
    d = {x: sb[x] - sa[x] for x in sa}
    if not any(d.values()) and a != b:
        return set(), notes, d
    # GOTO2RET
    if d['goto'] < 0 and (d['ret'] > 0 or d['brk'] > 0 or d['cont'] > 0) and d['label'] <= 0:
        k.add('GOTO2RET')
    # LOOPFORM
    if d['loop'] != 0 and (d['goto'] != 0 or d['label'] != 0):
        k.add('LOOPFORM')
    if d['case'] != 0 or d['sw'] != 0:
        k.add('SWITCHFORM')
    # TAILDUP / TAILMERGE: runs of >=2 statements whose multiplicity changed
    ra, rb = runs(a), runs(b)
    dup = [r for r in rb if rb[r] >= 2 and ra.get(r, 0) < rb[r] and any(x in r for x in ra) ]
    dup = [r for r in rb if rb[r] >= 2 and ra.get(r, 0) < rb[r]]
    mer = [r for r in ra if ra[r] >= 2 and rb.get(r, 0) < ra[r]]
    if dup and d['label'] <= 0:
        k.add('TAILDUP'); notes.append(('TAILDUP', dup[0][:2]))
    if mer and d['label'] >= 0:
        k.add('TAILMERGE'); notes.append(('TAILMERGE', mer[0][:2]))
    # RETSPLIT
    if d['ret'] > 0 and d['goto'] == 0 and d['label'] == 0 and 'GOTO2RET' not in k:
        k.add('RETSPLIT' if d['ret'] > 0 and any('return' in l for l in set(b) - set(a)) else 'EARLYRET')
    # ARMSWAP: an if condition negated
    conds_a = set(re.findall(r"if \((.*?)\) \{?$", "\n".join(a), re.M)); conds_b = set(re.findall(r"if \((.*?)\) \{?$", "\n".join(b), re.M))
    for c in conds_b - conds_a:
        neg = c[1:] if c.startswith('!') else '!' + c
        swap = {'==': '!=', '!=': '==', '<': '>=', '>=': '<', '>': '<=', '<=': '>'}
        alt = [re.sub(r"(==|!=|<=|>=|<|>)", lambda m: swap[m.group(1)], c, count=1)]
        if neg in conds_a or any(x in conds_a for x in alt) or (c.startswith('!(') and c[2:-1] in conds_a):
            k.add('ARMSWAP'); break
    # LABELMOVE
    la = [(i, LABEL.match(l).group(1)) for i, l in enumerate(a) if LABEL.match(l)]; lb = [(i, LABEL.match(l).group(1)) for i, l in enumerate(b) if LABEL.match(l)]
    if d['label'] == 0 and la and [n for _, n in la] != [n for _, n in lb] and set(n for _, n in la) == set(n for _, n in lb):
        k.add('LABELMOVE')
    if not k and any(d.values()):
        k.add('OTHER-CTRL')
    return k, notes, d


def main():
    EXD = Path(sys.argv[1]); names = (EXD / sys.argv[2]).read_text().split()
    limit = int(sys.argv[3]) if len(sys.argv) > 3 else 10 ** 9
    tot = collections.Counter(); combos = collections.Counter(); per = []; nctrl = 0
    for n in names[:limit]:
        m = re.match(r"(\w+?)_(func_[0-9A-F]+|w_[0-9A-F]+)\.([0-9a-f]+)\.diff", n)
        cont, fn, commit = m.groups(); rid = cont + "/" + fn
        pre = subprocess.run(['git', '-C', str(ROOT), 'show', f'{commit}~1:src/{rid}.c'], capture_output=True, text=True).stdout
        post = subprocess.run(['git', '-C', str(ROOT), 'show', f'{commit}:src/{rid}.c'], capture_output=True, text=True).stdout
        if not pre or not post: continue
        k, notes, d = one(pre, post)
        if not k: continue
        nctrl += 1
        for x in k: tot[x] += 1
        combos[tuple(sorted(k))] += 1
        per.append(dict(name=n, rid=rid, kinds=sorted(k), delta=d, notes=[list(map(str, x)) for x in notes]))
    print('n', len(names[:limit]), 'with a control-flow change', nctrl)
    for a, b in tot.most_common(): print('  %-12s %d' % (a, b))
    print('top combos:')
    for a, b in combos.most_common(12): print('  %3d  %s' % (b, '+'.join(a)))
    Path(sys.argv[2] + '.ctrlmoves.json').write_text(json.dumps(per, indent=0))


if __name__ == '__main__':
    main()
