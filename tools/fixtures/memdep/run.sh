#!/bin/bash
# Microcompile fixture (round 27): the MEM_IN_STRUCT_P dependence exemption in gcc 2.x's scheduler.
#   bash tools/fixtures/memdep/run.sh          -> one line per stock cell: load/store order per shape
# sched.c true_dependence/anti_dependence/output_dependence (2.7.2 lines 815-880, byte-identical in 2.8.1):
# two memory refs that memrefs_conflict_p cannot separate are STILL assumed independent when one is a
# struct-member access through a varying address (MEM_IN_STRUCT_P, not QImode) and the other is a
# non-struct access at a fixed address (a bare global scalar, a stack slot). cse.c (invalidate, 7571) and
# loop.c (2682) consult the same flag. So the SPELLING of one access - `p->f` vs `*(T *)((u8 *)p + off)`,
# `G` vs `G[0]` vs `GS.f` - changes which instructions the scheduler may reorder, which loads CSE keeps and
# what loop.c hoists, at identical address arithmetic. Shapes A-H in memdep.c; expected in every cell but
# 2.91.66 (haifa): A,F,G LOAD-FIRST (the exemption fired), B,C,D,E,H store-first.
set -u
cd "$(dirname "$0")/../../.."
R=$PWD; T=$(mktemp -d); trap 'rm -rf "$T"' EXIT
for cell in 2.6.3 2.7.2 2.7.2-cdk 2.8.0 2.8.1 2.91.66 2.95.2; do D=$R/toolchain/compilers/gcc-$cell; for fl in "" "-G0"; do
  out=$T/${cell}${fl}.s
  ( cd tools/fixtures/memdep && $D/gcc -B$D/ -S -O2 $fl -w memdep.c -o $out 2>$out.err )
  [ -s $out ] || { echo "$cell$fl: no output: $(head -c 200 $out.err)"; continue; }
  python3 - $out "$cell$fl" <<'PY'
import sys,re
s=open(sys.argv[1]).read(); res=[]
for fn in "ABCDEFGH":
    m=re.search(r"\nf%s:\n(.*?)\n\s*\.end\s+f%s"%(fn,fn),s,re.S) or re.search(r"\nf%s:\n(.*?)(?=\n\w+:|\Z)"%fn,s,re.S)
    body=[l.strip() for l in m.group(1).splitlines() if l.strip() and not l.strip().startswith(('.','#'))] if m else []
    try:
        st=next(i for i,l in enumerate(body) if l.startswith(('sw','sh','sb')))
        ld=next(i for i,l in enumerate(body) if l.startswith(('lw','lh','lb')))
        res.append("%s:%s"%(fn,"LOAD-FIRST" if ld<st else "store-first"))
    except StopIteration: res.append("%s:?"%fn)
print("%-14s %s"%(sys.argv[2]," ".join(res)))
PY
done; done
