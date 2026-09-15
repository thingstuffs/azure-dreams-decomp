"""Declaration-level move inventory over lane-won exemplar diffs: what happened to each local the lane
removed, added or retyped?  Text only.  Round 28 (2026-09-15) over 403 lane-won REG diffs: RETYPE-int 50, SPLIT 43,
INLINE 31 (+47 probable), MERGE-local 24, MERGE-param 8, RENAME 9, CTRL 76, PARAM 13, no declaration change 113; over 220
KEEP diffs: CTRL 64, RETYPE-int 39, INLINE 19+31, SPLIT 11, none 51.  Writes <names>.declmoves.json beside the names
file (per diff: kinds and notes).  For each diff (pre = commit~1, post = commit):

  INLINE     a removed local V whose defining expression E (from `V = E;` in pre) appears in post where V was used
  MERGE      a removed local V whose uses in post read another local or parameter W (same context tokens)
  SPLIT      an added local W in post whose definition `W = E;` was `V = E;` in pre for a local V that survives
  RENAME     a removed local V and an added local W with V's every use rewritten as W (a pure rename or retype-by-rename)
  RETYPE     the same name declared with another type (int width, pointer type, other)
  PARAM      a parameter list change
  CTRL       labels/gotos/loops added or removed
  OTHER      none of the above explains a removed or added declaration

    cd <exemplar dir> && python3 tools/lanes/declmoves.py . lane_won.txt [limit]
"""
import re, sys, json, subprocess, collections
from pathlib import Path
ROOT = next(p for p in Path(__file__).resolve().parents if (p / 'tools/common.py').is_file())
sys.path.insert(0, str(ROOT / 'tools'))
from pin_census import sites_of
from pin_sites import erase_many
CMT = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
DECL = re.compile(r"^\s*(?:register\s+)?(?:const\s+)?(?P<ty>(?:struct\s+\w+|\w+)(?:\s*\*+)?)\s*(?P<name>\w+)\s*(?:\[[^\]]*\])?\s*;\s*$")
INT = {"s8", "u8", "s16", "u16", "s32", "u32", "int", "short", "char", "unsigned", "long", "M2C_UNK", "M2C_UNK8", "M2C_UNK16", "M2C_UNK32"}


def clean(t):
    return CMT.sub("", erase_many(t, sites_of(t), clean_notes=True))


def locals_of(t):
    """name -> type for bare declarations inside function bodies (brace depth >= 1, not in struct bodies)."""
    out = {}; depth = 0; agg = 0
    for ln in t.split("\n"):
        o, c = ln.count("{"), ln.count("}")
        if agg > 0:
            agg += o - c
        elif re.match(r"^\s*(?:typedef\s+)?(?:struct|union|enum)\b[^;]*\{", ln):
            agg = 1 + o - c - 1 if o else 0
        elif depth >= 1:
            m = DECL.match(ln)
            if m and not ln.strip().startswith(("extern", "static", "typedef", "return", "goto")):
                out[m["name"]] = re.sub(r"\s+", " ", m["ty"]).replace(" *", "*")
        depth += o - c
    return out


def defs_of(t, v):
    return [m.group(1).strip() for m in re.finditer(r"(?<![\w.>])" + re.escape(v) + r"\s*=(?!=)\s*([^;]+);", t)]


def uses_ctx(t, v, w=4):
    """Token contexts around each use of v: (prev tokens, next tokens)."""
    toks = re.findall(r"[A-Za-z_]\w*|0x[0-9A-Fa-f]+|\d+|->|\S", t)
    out = []
    for i, tk in enumerate(toks):
        if tk == v and (i == 0 or toks[i - 1] not in ("->", ".")):
            out.append((tuple(toks[max(0, i - w):i]), tuple(toks[i + 1:i + 1 + w])))
    return out, toks


def one(pre, post):
    pre, post = clean(pre), clean(post)
    lp, lo = locals_of(pre), locals_of(post)
    removed = [v for v in lp if v not in lo]; added = [v for v in lo if v not in lp]
    kinds = collections.Counter(); notes = []
    for v in lp:
        if v in lo and lp[v] != lo[v]:
            a, b = lp[v], lo[v]
            k = "RETYPE-int" if a.rstrip("*") in INT and b.rstrip("*") in INT and "*" not in a + b else "RETYPE-ptr" if "*" in a + b else "RETYPE-other"
            kinds[k] += 1; notes.append((k, v, a, b))
    ctx_post_all = {}
    for v in removed:
        explained = False
        # RENAME / MERGE: v's use contexts appear in post around some other identifier
        uc, _ = uses_ctx(pre, v)
        if uc:
            cand = collections.Counter()
            for w in set(list(lo) + re.findall(r"\b\w+\b", " ".join(re.findall(r"\(([^)]*)\)\s*\{", post)[:1]))):
                if w == v or w in ("void",): continue
                if w not in ctx_post_all:
                    ctx_post_all[w] = set(uses_ctx(post, w)[0])
                hits = sum(1 for c in uc if c in ctx_post_all[w])
                if hits: cand[w] = hits
            if cand:
                w, h = cand.most_common(1)[0]
                if h >= max(1, len(uc) // 2):
                    k = "RENAME" if w in added else "MERGE-param" if w not in lp and w not in lo else "MERGE-local"
                    kinds[k] += 1; notes.append((k, v, "->", w, "%d/%d uses" % (h, len(uc)))); explained = True
        if not explained:
            ds = defs_of(pre, v)
            if ds and any(re.sub(r"\s+", "", d) in re.sub(r"\s+", "", post) and re.sub(r"\s+", "", d) not in re.sub(r"\s+", "", pre.replace(v + " = " + d, "")) for d in ds if len(d) > 3):
                kinds["INLINE"] += 1; notes.append(("INLINE", v, ds[:2])); explained = True
            elif ds and any(re.sub(r"\s+", "", d) in re.sub(r"\s+", "", post) for d in ds if len(d) > 3):
                kinds["INLINE?"] += 1; notes.append(("INLINE?", v, ds[:2])); explained = True
        if not explained:
            kinds["REMOVED-other"] += 1; notes.append(("REMOVED-other", v, lp[v], defs_of(pre, v)[:2]))
    for w in added:
        if any(n[0] == "RENAME" and n[3] == w for n in notes): continue
        ds = defs_of(post, w)
        src = None
        for v in lo:
            if v == w: continue
            if any(re.sub(r"\s+", "", d) in {re.sub(r"\s+", "", x) for x in defs_of(pre, v)} for d in ds if len(d) > 2):
                src = v; break
        if src:
            kinds["SPLIT"] += 1; notes.append(("SPLIT", src, "+", w, ds[:2]))
        else:
            kinds["ADDED-other"] += 1; notes.append(("ADDED-other", w, lo[w], ds[:2]))
    ppre = re.findall(r"^\w[\w\s\*]*\b\w+\s*\(([^)]*)\)\s*\{", pre, re.M); ppost = re.findall(r"^\w[\w\s\*]*\b\w+\s*\(([^)]*)\)\s*\{", post, re.M)
    if ppre != ppost: kinds["PARAM"] += 1
    if len(re.findall(r"\bgoto\b|^\s*\w+:\s*$|\bwhile\b|\bfor\b|\bdo\b", pre, re.M)) != len(re.findall(r"\bgoto\b|^\s*\w+:\s*$|\bwhile\b|\bfor\b|\bdo\b", post, re.M)):
        kinds["CTRL"] += 1
    return kinds, notes, removed, added


def main():
    EXD = Path(sys.argv[1]); names = (EXD / sys.argv[2]).read_text().split()
    limit = int(sys.argv[3]) if len(sys.argv) > 3 else 10 ** 9
    tot = collections.Counter(); per = []; combos = collections.Counter(); onlyk = collections.Counter()
    for n in names[:limit]:
        m = re.match(r"(\w+?)_(func_[0-9A-F]+|w_[0-9A-F]+)\.([0-9a-f]+)\.diff", n)
        cont, fn, commit = m.groups(); rid = cont + "/" + fn
        pre = subprocess.run(['git', '-C', str(ROOT), 'show', f'{commit}~1:src/{rid}.c'], capture_output=True, text=True).stdout
        post = subprocess.run(['git', '-C', str(ROOT), 'show', f'{commit}:src/{rid}.c'], capture_output=True, text=True).stdout
        if not pre or not post: continue
        k, notes, rem, add = one(pre, post)
        for x in k: tot[x] += 1
        combos[tuple(sorted(k))] += 1
        per.append(dict(name=n, rid=rid, kinds=dict(k), notes=[list(map(str, x)) for x in notes]))
    print('n', len(per)); print('diffs carrying each kind:')
    for a, b in tot.most_common(): print('  %-14s %d' % (a, b))
    print('top combos:')
    for a, b in combos.most_common(20): print('  %3d  %s' % (b, '+'.join(a) or '(none)'))
    Path(sys.argv[2] + '.declmoves.json').write_text(json.dumps(per, indent=0))


if __name__ == '__main__':
    main()
