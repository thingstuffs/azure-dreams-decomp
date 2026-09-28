"""sites10.py: every use of a census view (views10.jsonl) in its row: the cast expression and the member chain.
   -> census/sites10.jsonl ; prints a shape histogram per object."""
import json, re, sys, collections
from pathlib import Path
sys.path.insert(0, str(Path(__file__).parent))
from consolidate import code_spans
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
def prim(t, i):
    """end of a primary/postfix expression starting at i (skipping spaces)."""
    n = len(t)
    while i < n and t[i] in " \t\n": i += 1
    j = i
    if j < n and t[j] in "&*": j += 1
    while j < n and t[j] in " \t": j += 1
    if j < n and t[j] == "(":
        d = 0
        while j < n:
            if t[j] == "(": d += 1
            elif t[j] == ")":
                d -= 1
                if d == 0: j += 1; break
            j += 1
    else:
        m = re.match(r"\w+", t[j:]); j += m.end() if m else 0
    while True:
        m = re.match(r"\s*(\.|->)\s*\w+|\s*\[[^\]]*\]", t[j:])
        if not m: break
        j += m.end()
    return i, j
out = []
for l in open(LANE / "census/views10.jsonl"):
    r = json.loads(l); t = (REPO / "src" / (r["id"] + ".c")).read_text(errors="replace")
    spans = code_spans(t)
    for o, V, n in r["hits"]:
        for m in re.finditer(r"\(\s*(?:struct\s+)?%s\s*\*\s*\)" % re.escape(V), t):
            if not any(a <= m.start() < b for a, b in spans): continue
            a, b = prim(t, m.end())
            expr = t[a:b]
            tail = re.match(r"\s*\)\s*(->\s*\w+(?:\s*(?:\.|->)\s*\w+|\s*\[[^\]]*\])*)|\s*\)\s*(\[[^\]]*\](?:\s*(?:\.|->)\s*\w+)*)", t[b:])
            pre = t[max(0, m.start() - 3):m.start()]
            out.append({"id": r["id"], "obj": o, "view": V, "expr": re.sub(r"\s+", " ", expr), "tail": re.sub(r"\s+", "", (tail.group(1) or tail.group(2))) if tail else None, "pos": m.start()})
        for m in re.finditer(r"^\s*(?:register\s+)?(?:struct\s+)?%s\s*\*\s*(\w+)\s*(=[^;]*)?;" % re.escape(V), t, re.M):
            out.append({"id": r["id"], "obj": o, "view": V, "decl": m.group(1), "init": (m.group(2) or "").strip(), "pos": m.start()})
with open(LANE / "census/sites10.jsonl", "w") as fh:
    for s in out: fh.write(json.dumps(s) + "\n")
def shape(s):
    if "decl" in s: return "DECL " + ("init" if s["init"] else "noinit")
    e = s["expr"]; e = re.sub(r"\b(D_800814A8|D_800E3D7C|gameWork|dungeonStatus|D_80082E80|D_80083780|objectFlagBlock|D_800E2970|D_80083498|D_80016000|D_80082660)\b", "OBJ", e)
    e = re.sub(r"\b(?!OBJ\b)[a-z_]\w*", "v", e); e = re.sub(r"\b(0x[0-9A-Fa-f]+|\d+)\b", "K", e)
    tl = s["tail"] or "NONE"
    tl = re.sub(r"->\w+", "->m", tl); tl = re.sub(r"\.\w+", ".s", tl); tl = re.sub(r"\[[^\]]*\]", "[i]", tl)
    return "%s  %s" % (e, tl)
H = collections.defaultdict(collections.Counter)
for s in out: H[s["obj"]][shape(s)] += 1
for o, c in sorted(H.items(), key=lambda x: -sum(x[1].values())):
    print("==", o, sum(c.values()))
    for k, v in c.most_common(12): print("   %4d  %s" % (v, k))
