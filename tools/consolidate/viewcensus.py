"""viewcensus.py: local struct typedefs (defined in a row's .c) cast onto a shared object's address/pointer, directly or
   through a local pointer initialised from it.  -> census/views10.jsonl + a summary by object."""
import re, json, collections, sys
from pathlib import Path
LANE = Path(__file__).resolve().parent.parent; REPO = LANE.parent.parent.parent
OBJ = ["gameWork", "dungeonStatus", "objectFlagBlock", "D_800E3D7C", "D_800814A8", "D_80083780", "D_80083498",
       "D_80082E80", "D_800E2970", "D_80082660", "D_80083120", "D_80016000"]
STR = re.compile(r'"(?:[^"\\\n]|\\.)*"|/\*.*?\*/|//[^\n]*', re.S)
out = []; summ = collections.defaultdict(lambda: collections.Counter())
for p in sorted((REPO / "src").glob("*/*.c")):
    t = STR.sub(" ", p.read_text(errors="replace"))
    local = set(re.findall(r"typedef\s+struct\s+\w*\s*\{[^{}]*(?:\{[^{}]*\}[^{}]*)*\}\s*(\w+)\s*;", t)) | set(re.findall(r"\}\s*(\w+)\s*;", t)) | set(re.findall(r"typedef struct (\w+) \1;", t))
    local = {x for x in local if not x.startswith(("u", "s")) or x.startswith("S_")}
    if not local: continue
    objs = "|".join(OBJ)
    ptrs = {}
    for m in re.finditer(r"\b(\w+)\s*=\s*\(?\s*(?:\(\s*[\w\s]+\*\s*\)\s*)*\(?\s*&?\s*(%s)\b" % objs, t):
        ptrs[m.group(1)] = m.group(2)
    hits = collections.Counter()
    for m in re.finditer(r"\(\s*(?:struct\s+)?(\w+)\s*\*\s*\)\s*\(?\s*(?:\(\s*(?:u8|s8|char)\s*\*\s*\)\s*)?&?\s*(\w+)", t):
        ty, base = m.group(1), m.group(2)
        if ty not in local: continue
        o = base if base in OBJ else ptrs.get(base)
        if o: hits[(o, ty)] += 1
    for m in re.finditer(r"^\s*(?:register\s+)?(?:struct\s+)?(\w+)\s*\*\s*(\w+)\s*=\s*\(?\s*(?:\(\s*[\w\s]+\*\s*\)\s*)*\(?\s*&?\s*(%s)\b" % objs, t, re.M):
        if m.group(1) in local: hits[(m.group(3), m.group(1))] += 1
    if hits:
        rid = "%s/%s" % (p.parent.name, p.stem)
        out.append({"id": rid, "hits": [[o, ty, n] for (o, ty), n in hits.items()]})
        for (o, ty), n in hits.items(): summ[o][rid.split("/")[0]] += 1
(LANE / "census").mkdir(exist_ok=True)
with open(LANE / "census/views10.jsonl", "w") as fh:
    for r in out: fh.write(json.dumps(r) + "\n")
print(len(out), "rows")
for o, c in sorted(summ.items(), key=lambda x: -sum(x[1].values())): print(o, sum(c.values()), dict(c))
