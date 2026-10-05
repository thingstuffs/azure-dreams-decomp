#!/usr/bin/env python3
"""frame_slack.py [--container dungeon] [--cfg 2.7.2-cdk-G0] [--max N] [--minslack 4]
Census of UNREFERENCED frame bytes in pin-free rows compiled at their own recipe: compiles each row's src text
(kitlib.dumps, asm only), parses the frame size, the callee-saved block, the referenced N($sp) offsets and
address-takes (addiu $x,$sp,N), and reports rows whose local area has >= minslack bytes nobody touches.
Purpose: find source shapes that make gcc 2.7.2-cdk reserve frame space without referencing it."""
import json, re, sys
from pathlib import Path
from concurrent.futures import ThreadPoolExecutor
_ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(_ROOT / "tools/lanes/lanekit")); sys.path.insert(0, str(_ROOT / "tools"))
import kitlib
lane = kitlib.bootstrap()
from pathlib import Path
args = sys.argv[1:]
def opt(name, default):
    return args[args.index(name) + 1] if name in args else default
container = opt("--container", "dungeon"); cfg = opt("--cfg", "2.7.2-cdk-G0"); maxn = int(opt("--max", "400")); minslack = int(opt("--minslack", "4"))
rows = [json.loads(l) for l in open(_ROOT / "ledger/rows.jsonl")]
rows = [r for r in rows if r["container"] == container and r["cfg"] == cfg and r.get("exists", True)]
def pins(rid):
    try: return len(re.findall(r"\bASM_[A-Z_0-9]*\(", (_ROOT / ("src/%s.c" % rid)).read_text()))
    except Exception: return 99
rows = [r for r in rows if r["size"] <= 1400]
rows.sort(key=lambda r: r["size"])
rows = [r for r in rows if pins(r["id"]) == 0][:maxn]
SP = re.compile(r"\b(-?\d+)\(\$sp\)")
def analyse(r):
    text = (_ROOT / ("src/%s.c" % r["id"])).read_text()
    d = kitlib.dumps(r, text, want=[])
    if not d or d.get("error"): return (r["id"], "nobuild")
    asm = d["asm"]
    m = re.search(r"\.frame\s+\$sp,(\d+),\$31", asm) or re.search(r"subu\s+\$sp,\$sp,(\d+)", asm)
    if not m: return (r["id"], "noframe")
    frame = int(m.group(1))
    if frame == 0: return (r["id"], "leaf0")
    mm = re.search(r"\.mask\s+(0x[0-9a-fA-F]+),(-?\d+)", asm)
    nsave = bin(int(mm.group(1), 16)).count("1") if mm else 0
    saves_start = frame - ((nsave * 4 + 7) // 8) * 8
    refs = set(); addr = set()
    for line in asm.splitlines():
        if line.lstrip().startswith(("#", ".")): continue
        for a in SP.finditer(line):
            off = int(a.group(1))
            w = 4
            if re.search(r"\b(lh|lhu|sh)\b", line): w = 2
            elif re.search(r"\b(lb|lbu|sb)\b", line): w = 1
            elif re.search(r"\b(ldc1|sdc1|ld|sd)\b", line): w = 8
            for k in range(w): refs.add(off + k)
        a2 = re.search(r"addiu\s+\$\w+,\$sp,(\d+)", line)
        if a2: addr.add(int(a2.group(1)))
    calls = "jal" in asm
    args_end = 0
    if calls:
        # outgoing args: 16 minimum when any call has args; stack args stores sw N($sp) with N>=16 before a jal are args
        args_end = 16
        for off in sorted(refs):
            if off >= 16 and off < saves_start and off in refs:
                break
    # local area = [args_end, saves_start)
    unref = [o for o in range(args_end, saves_start) if o not in refs]
    # address-taken blocks: from an addiu base up to the next referenced/addr offset - treat as covered
    covered = set()
    for base in sorted(addr):
        nxt = min([o for o in sorted(refs | addr) if o > base] + [saves_start])
        for o in range(base, nxt): covered.add(o)
    unref = [o for o in unref if o not in covered]
    return (r["id"], frame, args_end, saves_start, sorted(refs & set(range(args_end, saves_start))), sorted(addr), unref)
with ThreadPoolExecutor(max_workers=4) as ex:
    res = list(ex.map(analyse, rows))
n = 0
for x in res:
    if len(x) == 2: continue
    rid, frame, args_end, saves_start, refs, addr, unref = x
    if len(unref) >= minslack:
        n += 1
        print("%-28s frame %-3d locals [%d,%d) refs %s addr %s UNREF %d bytes at %s" % (rid, frame, args_end, saves_start, refs[:12], addr, len(unref), unref[:8]))
print("# %d of %d rows with >= %d unreferenced local bytes" % (n, len(res), minslack))
