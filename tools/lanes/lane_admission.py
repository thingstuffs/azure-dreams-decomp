"""Shared land_lanes admission; counters and exceptions retained verbatim."""
import collections, glob, hashlib, json, os, re, shutil, sys
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from source_layout import row_path as layout_row_path
from pin_census import sites_of
import land_admit
# round 96: `\basm\s*\(` = plain register asm (`register T x asm("$4")`, LOCAL_ASM_REG macros) - a pin pin_census does not count
bad = re.compile(r"ASM_[A-Z0-9_]+(?=\()|ODDITY_[A-Z_]+(?=\()|while\s*\(\s*0\s*\)|__asm__|\basm\s*\(|\bvolatile\b")
# a computed goto counts once plus once per `&&label` address it can reach (a label array is a jump site per entry)
gotos = lambda t: (lambda c: len(re.findall(r"\bgoto\s+\w+\s*;", c)) + len(re.findall(r"\bgoto\s*\*", c)) + len(re.findall(r"[{,=]\s*&&\s*[A-Za-z_]\w*", c)))(re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S)))
# round 96: S_<addr> address-named struct views count as decompiler leftovers too (typing lanes replace them)
m2c = lambda t: len(re.findall(r"\bM2C_[A-Z_]+\b|\b(?:temp|var|phi)_[a-z][a-z0-9_]*\b|\barg[0-9]\b|\bsp[0-9A-F]{2,3}\b|\bNON_MATCHING\b|\bS_[0-9A-F]{8}\w*", re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))))
# r117: a volatile-bodied accessor macro counts once per invocation (land_admit.macro_volatile_uses)
# r118: union sites count as a kind (tracked trades, ledger/union_trades.jsonl): fewer unions is a fidelity gain
kinds = lambda t: +(collections.Counter(m.group(0).replace(" ", "") for m in bad.finditer(re.sub(r"/\*.*?\*/", "", t, flags=re.S))) + collections.Counter(volatile=land_admit.macro_volatile_uses(t), union=len(re.findall(r"\bunion\b", re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))))))


def assess(row, cand, cur, base, lane, *, oddity_ok=(), onetrip_ok=(), readable_lanes=()):
    rid = row['id'] if row else ''
    kc, ku = kinds(cand), kinds(cur); grew = [k for k in kc if kc[k] > ku[k]]
    # round 95 (owner 2026-10-06, decisions item 19): a one-trip `do { } while (0)` that removes pins lands ONLY for rows listed
    # in ledger/onetrip_barrier_rows.jsonl (tracked: a loop note is a full sched barrier, the macro-body pattern) - never silently
    # round 95 (owner 2026-10-06, decisions item 21): ODDITY_* fences are orchestrator-placed oddities - growth refused unless the
    # row is listed in ledger/oddities.jsonl
    grew = [k for k in grew if not (k.startswith("ODDITY_") and rid in oddity_ok)]
    if "while(0)" in grew and rid in onetrip_ok and len(sites_of(cand)) < len(sites_of(cur)): grew.remove("while(0)")
    if hashlib.sha256(cur.encode()).hexdigest() != base:
        return dict(accepted=False, reason='stale base')
    fell = [k for k in ku if kc[k] < ku[k]]
    # round 80 (readability lanes): with pins equal, fewer `goto` statements (and none added) is a landing too
    gc, gu = gotos(cand), gotos(cur)
    if gc < gu: fell.append("goto")
    # round 91 (luna cleanup lanes): with pins equal, fewer decompiler leftovers (M2C_* tokens, temp_/var_/phi_
    # locals, argN, spXX, NON_MATCHING; comments excluded) is a landing too, and none may be added
    # round 93: fake dependencies (`+ v - v`, `v ^ v`, `& m & m`) falling is a landing; growing is refused
    # round 96: also `x = x;` and the split pair `d += h; d -= h;` (same patterns as kitlib._FAKEDEP)
    fd = lambda x: (lambda c: len(re.findall(r"\+\s*(\w+)\s*-\s*\1\b(?!\s*[\[(.]|\s*->)|-\s*(\w+)\s*\+\s*\2\b(?!\s*[\[(.]|\s*->)|\b(\w+)\s*\^\s*\3\b|&\s*(\w+)\s*&\s*\4\b|(?<![\w.>\]])\b(\w+)\s*=\s*\5\s*;|(?<![\w.>\]])\b(\w+)\s*\+=\s*(\w+)\s*;\s*\6\s*-=\s*\7\s*;", c)))(re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", x, flags=re.S)))
    if fd(cand) < fd(cur): fell.append("fakedep")
    if fd(cand) > fd(cur): grew.append("fakedep")
    mc, mu = m2c(cand), m2c(cur)
    if mc < mu: fell.append("m2c")
    if len(sites_of(cand)) == len(sites_of(cur)) and mc > mu: grew.append("m2c")
    # round 80 (format lanes): a candidate that differs from the current text ONLY in whitespace outside string
    # literals and preprocessor lines is a formatting landing (C tokens and comment text identical; the byte gate decides)
    TOK = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|[A-Za-z_]\w*|\d[\w.]*|>>=|<<=|->|\+\+|--|&&|\|\||<<|>>|[<>=!+\-*/%&|^]=|\.\.\.|\S')
    ws = lambda t: TOK.findall("\n".join(l for l in t.split("\n") if not l.lstrip().startswith("#")))
    pp = lambda t: [l.strip() for l in t.split("\n") if l.lstrip().startswith("#")]
    if cand != cur and not fell and ws(cand) == ws(cur) and pp(cand) == pp(cur): fell.append("format")
    # round 78: a byte-exact candidate that removes scaffolding (volatile, while(0), __asm__, an ASM_* kind)
    # with no pin growth lands too - r78_opus_b1's `volatile ShortArg` parameter was refused for "no pin fell"
    if len(sites_of(cand)) == len(sites_of(cur)) and gc > gu: grew.append("goto")
    # round 93 (readability lanes named in READABLE_LANES, e.g. struct assignments for m2c's unrolled copies,
    # callee-typed spellings at equal pins): an equal-pin, nothing-grown candidate lands; the byte gate decides
    if cand != cur and not fell and lane in readable_lanes: fell.append("readability")
    # round 99: the LIVE fidelity-site count (levels.live_fidelity_sites, the L5 `fidelity_site` predicate that levels.jsonl and
    # STATUS use) falling is a landing at equal pins (78 call-arity / prototype fixes were hand-applied in round 98 for want of
    # this); it rising at equal pins is refused.  Rows outside rows() (no census record) are not measured.
    if cand != cur and row is not None and len(sites_of(cand)) <= len(sites_of(cur)):
        land_admit.admit(fell, grew, len(sites_of(cand)) == len(sites_of(cur)), *land_admit.fidelity_counts(row, cand, cur))
    if len(sites_of(cand)) > len(sites_of(cur)) or grew or (len(sites_of(cand)) == len(sites_of(cur)) and not fell):
        return dict(accepted=False, reason='admission', pins_before=len(sites_of(cur)), pins_after=len(sites_of(cand)), fell=fell, grew=grew)
    return dict(accepted=True, reason='admitted', pins_before=len(sites_of(cur)),
                pins_after=len(sites_of(cand)), fell=fell, grew=grew)


def context(root):
    from common import rows
    def ids(name):
        p = root/'ledger'/name
        return {json.loads(line)['id'] for line in p.read_text().splitlines() if line.strip()} if p.exists() else set()
    return ({r['id']:r for r in rows()}, dict(oddity_ok=ids('oddities.jsonl'),
        onetrip_ok=ids('onetrip_barrier_rows.jsonl'),
        readable_lanes=os.environ.get('READABLE_LANES', '').split(',')))


def stage(stage, lanes):
    root = Path.cwd(); rows, policy = context(root)
    for lane in lanes:
        for f in sorted((root/'work/native_lane'/lane/'out').glob('*/*.c')):
            rid = f.parent.name+'/'+f.stem
            cur = (layout_row_path(rid, root)).read_text()
            base = Path(str(f)+'.base_sha')
            result = assess(rows.get(rid), f.read_text(), cur,
                            base.read_text().strip() if base.exists() else '', lane, **policy)
            print('keep' if result['accepted'] else 'skip', lane, rid, result)
            if result['accepted']:
                d = Path(stage)/lane/f.parent.name; d.mkdir(parents=True,exist_ok=True)
                shutil.copy2(f,d/f.name); shutil.copy2(base,d/base.name)
