#!/usr/bin/env python3
"""reload_cse_trace.py - what cdk's post-reload CSE (reload1.c reload_cse_regs) did to every load of a text.

For each `(set (reg) (mem ...))` insn in the .lreg dump (pre-reload), print what the same uid looks like in the
.greg dump (post-reload, after reload_cse_regs): still a load, a register copy (`(set (reg) (reg))`: the MEM was
recorded in reg_values[] for that register by an earlier store/load, reload1.c reload_cse_simplify_set), or
DELETED (reload_cse_noop_set_p: the destination already held the value).  Retail `move` next to field stores on
cdk rows are usually such converted loads: field re-reads the source made and cse could not fold (cse.c
note_mem_written/invalidate_memory drop every pseudo-based MEM equivalence on any store).

usage: python3 reload_cse_trace.py <dumps_dir>/<stem>      (stem = the dump.py file stem, e.g. dumps/final/func_81876014)
"""
import re, sys

def insns(path):
    out = {}
    for blk in re.split(r'\n(?=\()', open(path).read()):
        m = re.match(r'\((?:insn|insn:HI) (\d+) ', blk)
        if m:
            out[int(m.group(1))] = ' '.join(blk.split())
    return out

def main():
    stem = sys.argv[1]
    l, g = insns(stem + '.lreg'), insns(stem + '.greg')
    pat = re.compile(r'\(set (\(reg[^()]*\)) (\((?:mem|zero_extend|sign_extend)[^;]*)\) \d+ \{')
    n = c = d = 0
    for uid in sorted(l):
        m = re.search(r'\(set (\(reg[^()]*\)) \((mem|zero_extend:SI \(mem|sign_extend:SI \(mem)', l[uid])
        if not m:
            continue
        n += 1
        gg = g.get(uid)
        if gg is None:
            verdict = 'DELETED (reload_cse_noop_set_p or dead)'; d += 1
        else:
            gm = re.search(r'\(set (\(reg[^()]*\)) (\(reg[^()]*\))\) \d+ \{', gg)
            if gm:
                verdict = 'COPY  %s <- %s   (reload_cse_simplify_set)' % (gm.group(1), gm.group(2)); c += 1
            else:
                verdict = 'load  ' + re.sub(r'\) -?\d+ \{.*', ')', gg[gg.find('(set'):])[:90]
        src = re.sub(r'\) -?\d+ \{.*', ')', l[uid][l[uid].find('(set'):])[:100]
        print('%4d  lreg %-100s  greg %s' % (uid, src, verdict))
    print('# %d loads in .lreg: %d became register copies, %d deleted' % (n, c, d))

if __name__ == '__main__':
    main()
