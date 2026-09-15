"""Depth-2, rename-invariant menu reachability over lane-won exemplar diffs (text only, no compiles).

Round 28 (2026-09-15). Round 27's depth-1 replay counted renames against the candidate and reached 1 of 120 lane-won
register texts; with the skeleton below and one more depth the same menu reaches 13 of 120 (7 at depth 1: t51 single-set
4, gotoloop, move, fuse; 6 at depth 2). The replay ranks by distance to the KNOWN landed text, which the search cannot do,
so its rate is an upper bound on what any ranking of the current menu could find; the search's assembly-distance beam
found none of these rows when it ran on them. Use it BEFORE building a generator: add the generator's *_candidates to
menu() (or run it on a copy) and report the delta on the same rows and seed.

    python3 tools/lanes/reach.py <exemplar dir from build_exemplars.py> <limit> <out.json> [--beam 12] [--menu-cap 400] [--procs 12]

<exemplar dir> needs INDEX.md and lane_won.txt (the r27 split of INDEX rows into lane-won and generator-won names).
Reads git (read-only) and tools/xform; writes only <out.json>. Each row costs 1-500 s of pure Python (the largest
functions dominate); 120 rows take ~25 min at 12 processes on an otherwise idle box.

For each lane-won diff: pre = text before the lane's commit, post = the landed text. The WHOLE current
menu (natural GENERATORS, t15 shapes, basesym, t51 candidates at every pin site, t53 extra/page,
t60 reuse, t42 sinkcopy, t63 memdep) is applied to pre (depth 1) and to the B nearest depth-1 texts
(depth 2). Distance = token edit distance between SKELETONS: pins erased, comments/whitespace gone,
local identifiers alpha-renamed by first appearance in the statements, declaration lines sorted per
block (so a split whose fresh name or declaration position differs from the lane's still counts).

    python3 reach2.py <exemplar dir> <limit> <out.json> [--beam 12] [--menu-cap 400] [--procs 12]
"""
import sys, re, json, subprocess, collections, random, difflib, argparse, time
from pathlib import Path
from multiprocessing import Pool
ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools')); sys.path.insert(0, str(ROOT / 'tools/xform'))
from pin_census import sites_of
from pin_sites import erase_many
from xform import natural as N
from xform import t15_shapes as SH
from xform import t51_sched_order as T51
from xform import t53_reg_state as T53
from xform import t60_alloc_inputs as T60
from xform import t42_sinkcopy as T42
try:
    from xform import t63_memdep as T63
except Exception:
    T63 = None

CMT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
TOK = re.compile(r"[A-Za-z_]\w*|0x[0-9A-Fa-f]+|\d+|->|\S")
KW = set("""auto break case char const continue default do double else enum extern float for goto if int long
register return short signed sizeof static struct switch typedef union unsigned void volatile while
u8 s8 u16 s16 u32 s32 u64 s64 M2C_UNK M2C_UNK8 M2C_UNK16 M2C_UNK32 NULL BODY_NAME""".split())
DECL = re.compile(r"^\s*(?:register\s+)?(?:const\s+)?(?:struct\s+\w+|\w+)\s*\**\s*\w+\s*(?:\[[^\]]*\])?\s*;\s*$")


def skeleton(text):
    """Tokens of the pinless, commentless text with locals alpha-renamed and declarations sorted per block."""
    t = CMT.sub("", erase_many(text, sites_of(text), clean_notes=True))
    # sort bare declaration lines within each run of consecutive declaration lines, but only inside
    # function bodies: struct/union/enum bodies keep their member order and their member names
    lines = t.split("\n"); out = []; run = []; declared = set()
    agg = 0          # brace depth inside a struct/union/enum body
    depth = 0        # overall brace depth
    for ln in lines + [None]:
        if ln is None:
            if run: out.extend(sorted(run)); run = []
            break
        opens = ln.count("{"); closes = ln.count("}")
        in_agg = agg > 0
        if not in_agg and re.match(r"^\s*(?:typedef\s+)?(?:struct|union|enum)\b[^;]*\{", ln):
            agg = 1 + opens - closes - 1 if opens else 0
            in_agg = True
        elif in_agg:
            agg += opens - closes
        is_local_decl = (not in_agg and depth >= 1 and DECL.match(ln)
                         and not ln.strip().startswith(("extern", "static", "typedef")))
        if is_local_decl:
            run.append(ln.strip())
            name = re.findall(r"(\w+)\s*(?:\[[^\]]*\])?\s*;", ln)
            if name: declared.add(name[-1])
        else:
            if run: out.extend(sorted(run)); run = []
            out.append(ln)
        depth += opens - closes
        if agg < 0: agg = 0
    t = "\n".join(out)
    toks = TOK.findall(t)
    ren = {}; res = []
    prev = None
    for tk in toks:
        if tk in declared and prev not in ("->", ".") and tk not in KW:
            res.append(ren.setdefault(tk, "L%d" % len(ren)))
        else:
            res.append(tk)
        prev = tk
    return res


def dist(a, b):
    sm = difflib.SequenceMatcher(None, a, b, autojunk=False)
    return sum(max(i2 - i1, j2 - j1) for tag, i1, i2, j1, j2 in sm.get_opcodes() if tag != 'equal')


def bag_dist(ca, cb):
    return sum((ca - cb).values()) + sum((cb - ca).values())


def menu(text, slus, cap):
    gens = {}
    for g in N.GENERATORS:
        gens[g.__name__.removesuffix("_candidates")] = g
    for n in ("narrow", "dup_after_if", "mask2cast", "maskfold", "litsym", "fold_load", "fold_temp", "commute",
              "inplace_update", "deadstore", "loop_counter_merge", "dowhile2for", "collapse_selfassign",
              "hoist_from_goto_arm"):
        f = getattr(SH, n + "_candidates", None)
        if f: gens[n] = f
    if not slus:
        gens["basesym"] = N.basesym_candidates
    gens["reuse"] = T60.reuse_candidates
    gens["sinkcopy"] = T42.candidates
    if T63 is not None and hasattr(T63, "memdep_candidates"):
        gens["memdep"] = T63.memdep_candidates
    out = []; seen = {text}
    def add(k, lab, c):
        if c not in seen:
            seen.add(c); out.append((k, lab, c))
    for k, g in gens.items():
        try:
            for lab, c in g(text):
                add(k, lab, c)
        except Exception:
            pass
    # pin-site directed menus (t51 candidates, t53 extra/page) at each live pin site
    pins = sites_of(text)          # (kind, macro, arg, start, end, line_no, replacement_text)
    sites = []
    for s in pins[:12]:
        var = None
        if s[0] == "reg" and s[6]:
            var = s[6].split()[-1].lstrip("*")
        elif s[1].startswith("ASM_KEEP") and s[2]:
            var = s[2].split(",")[0].strip().lstrip("*")
        sites.append((s[5], var))
    for line, var in sites:
        try:
            for lab, c in T51.candidates(text, line, var):
                add("t51:" + lab.split(":")[0], lab, c)
        except Exception:
            pass
        if var:
            try:
                for lab, c in T53.extra_candidates(text, var):
                    add("t53:" + lab.split(":")[0], lab, c)
            except Exception:
                pass
            try:
                for lab, c in T53.page_candidates(text, var):
                    add("t53:page-or", lab, c)
            except Exception:
                pass
    # round-robin across families so the cap is fair
    byfam = collections.defaultdict(list)
    for k, lab, c in out:
        byfam[k].append((k, lab, c))
    rr = []
    for level in range(10000):
        any_left = False
        for k in sorted(byfam):
            if level < len(byfam[k]):
                any_left = True; rr.append(byfam[k][level])
                if len(rr) >= cap: return rr
        if not any_left: break
    return rr


def one(job):
    rid, commit, beam, cap = job
    path = 'src/%s.c' % rid
    pre = subprocess.run(['git', '-C', str(ROOT), 'show', f'{commit}~1:{path}'], capture_output=True, text=True).stdout
    post = subprocess.run(['git', '-C', str(ROOT), 'show', f'{commit}:{path}'], capture_output=True, text=True).stdout
    if not pre or not post:
        return dict(rid=rid, commit=commit, status='missing')
    t0 = time.time()
    sp, tp = skeleton(pre), skeleton(post)
    d_base = dist(sp, tp)
    if d_base == 0:
        return dict(rid=rid, commit=commit, status='pins-only')
    ctp = collections.Counter(tp)
    slus = rid.startswith('slus/')
    m1 = menu(pre, slus, cap)
    # rank depth-1 by bag distance, exact-check the top by real distance
    ranked = sorted(((bag_dist(collections.Counter(sk := skeleton(c)), ctp), k, lab, c, sk) for k, lab, c in m1), key=lambda z: z[0])
    best1 = (d_base, None); hit1 = None
    scored1 = []
    for bd, k, lab, c, sk in ranked[:max(beam * 3, 40)]:
        d = dist(sk, tp); scored1.append((d, k, lab, c))
        if d == 0: hit1 = k; break
        if d < best1[0]: best1 = (d, k)
    scored1.sort(key=lambda z: z[0])
    hit2 = None; best2 = best1; expanded = 0; n2 = 0
    if not hit1:
        for d1, k1, lab1, c1 in scored1[:beam]:
            m2 = menu(c1, slus, cap); expanded += 1; n2 += len(m2)
            r2 = sorted(((bag_dist(collections.Counter(sk := skeleton(c)), ctp), k, lab, c, sk) for k, lab, c in m2), key=lambda z: z[0])
            for bd, k, lab, c, sk in r2[:40]:
                d = dist(sk, tp)
                if d == 0: hit2 = (k1, k); break
                if d < best2[0]: best2 = (d, k1 + '>' + k)
            if hit2: break
    return dict(rid=rid, commit=commit, status='ok', d_base=d_base, menu1=len(m1), menu2=n2, expanded=expanded,
                hit1=hit1, best1=best1[0], fam1=best1[1], hit2=list(hit2) if hit2 else None, best2=best2[0], fam2=best2[1],
                seconds=round(time.time() - t0, 1))


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument('exdir'); ap.add_argument('limit', type=int); ap.add_argument('out')
    ap.add_argument('--beam', type=int, default=12); ap.add_argument('--menu-cap', type=int, default=400)
    ap.add_argument('--procs', type=int, default=12); ap.add_argument('--seed', type=int, default=1)
    a = ap.parse_args()
    EXD = Path(a.exdir)
    lw = set((EXD / 'lane_won.txt').read_text().split())
    rows = [l for l in (EXD / 'INDEX.md').read_text().splitlines() if l.startswith('| ') and '.diff' in l
            and l.strip('|').split('|')[4].strip() in lw]
    random.seed(a.seed); random.shuffle(rows); rows = rows[:a.limit]
    jobs = []
    for l in rows:
        cells = [c.strip() for c in l.strip('|').split('|')]
        jobs.append((cells[1], cells[0], a.beam, a.menu_cap))
    res = []
    with Pool(a.procs) as p:
        for r in p.imap_unordered(one, jobs):
            res.append(r); print(len(res), r.get('rid'), r.get('status'), 'd_base', r.get('d_base'), 'best1', r.get('best1'),
                                 'hit1', r.get('hit1'), 'best2', r.get('best2'), 'hit2', r.get('hit2'), r.get('seconds'), flush=True)
            Path(a.out).write_text(json.dumps(res, indent=0))
    ok = [r for r in res if r['status'] == 'ok']
    c = collections.Counter()
    for r in ok:
        c['depth1-exact' if r['hit1'] else 'depth2-exact' if r['hit2'] else 'closer' if r['best2'] < r['d_base'] else 'no-closer'] += 1
    print(json.dumps(dict(c), indent=0), 'n', len(ok), 'other', collections.Counter(r['status'] for r in res if r['status'] != 'ok'))
    print('depth1 fams', collections.Counter(r['hit1'] for r in ok if r['hit1']).most_common())
    print('depth2 fams', collections.Counter(tuple(r['hit2']) for r in ok if r['hit2']).most_common())
    print('closest fams', collections.Counter(r['fam2'] for r in ok if not r['hit1'] and not r['hit2'] and r['fam2']).most_common(15))
    red = [(r['d_base'] - r['best2']) / r['d_base'] for r in ok if not r['hit1'] and not r['hit2']]
    import statistics
    print('median reduction (unreached)', statistics.median(red) if red else None, 'halfway+', sum(x >= 0.5 for x in red))


if __name__ == '__main__':
    main()
