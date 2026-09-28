"""layout.py CENSUS BASE END [--name X --var Y] : derive a struct layout from a census of pinned listings.
   Every access (direct, or through a base of any symbol in [BASE, END)) is placed at its absolute address;
   width from the opcode, sign from lh/lb vs lhu/lbu (a load-modify-store lhu does not count against s16).
   Prints the field table (offset, width, ops) and writes objects/<var>.json + a header draft."""
import json, sys, re
from collections import Counter, defaultdict
cen, base, end = sys.argv[1], int(sys.argv[2], 16), int(sys.argv[3], 16)
W = {"lb": 1, "lbu": 1, "sb": 1, "lh": 2, "lhu": 2, "sh": 2, "lw": 4, "sw": 4}
acc = defaultdict(Counter); rows = defaultdict(set)
for l in open(cen):
    r = json.loads(l)
    if r.get("error"): continue
    for f, s, o, op, how in r["acc"]:
        if how in ("indexed", "addr-use", "addr-stored") or op not in W: continue
        a = int(s[2:], 16) + o
        if base <= a < end: acc[a - base][op] += 1; rows[a - base].add(r["id"])
out = []
for off in sorted(acc):
    ops = acc[off]; w = Counter()
    for op, n in ops.items(): w[W[op]] += n
    out.append((off, ops, len(rows[off]), w))
for off, ops, n, w in out:
    print("0x%03X rows=%-4d %s" % (off, n, dict(ops)))
json.dump([[off, dict(ops), n] for off, ops, n, w in out], open(sys.argv[4] if len(sys.argv) > 4 else "/dev/null", "w"))
