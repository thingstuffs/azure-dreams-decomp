# Scan of the compiled script modules for TownState->field20[n] calls (lw 0x6000 / lw 0x20 / lw 4n) against the
# TOWN.BIN symbol dump (name[32] + u32 value). Run from the repo root after tools/setup.sh; output: script_call_sites_20260928.txt.
# Written for the 2026-09-28 symbol-dump parse correction (docs/evidence/script_call_table_20260908.md).
import struct, collections, json, sys
sym = collections.defaultdict(list)
t = open('work/disc/containers/TOWN_TOWN.BIN','rb').read()
import re
NAME = re.compile(rb"^[A-Za-z_][A-Za-z0-9_]*$")
for base,cnt in ((0x80C000,678),(0x812000,2909)):
    for k in range(cnt):
        o=base+36*k; n=t[o:o+32].split(b'\0')[0].decode(); v=struct.unpack_from('<I',t,o+32)[0]
        if n.startswith(('S_','FNO_')) and not n.startswith(('S_ARG','S_AEG')): sym[v].append(n)
ws = struct.unpack_from('<213I', t, 0x56568)
for fn in ('TOWN_TOWN.BIN','DUNGEON_DUNGEON.BIN','MAIN_MAIN.BIN','OVMOVIE_OVMOVIE.BIN'):
    b = open('work/disc/containers/'+fn,'rb').read(); n=len(b)//4
    w = struct.unpack_from('<%dI'%n, b, 0)
    hist = collections.Counter()
    for i in range(n-8):
        x=w[i]
        if x>>26==0x23 and (x&0xffff)==0x6000:          # lw rt,0x6000(rs)
            rt=(x>>16)&31
            # next lw rt2,0x20(rt) within 3 insns
            for j in range(i+1,i+4):
                y=w[j]
                if y>>26==0x23 and (y>>21)&31==rt and (y&0xffff)==0x20:
                    r2=(y>>16)&31
                    for k in range(j+1,j+5):
                        z=w[k]
                        if z>>26==0x23 and (z>>21)&31==r2:
                            off=z&0xffff
                            if off%4==0 and off<0x354: hist[off//4]+=1
                            break
                    break
    print(fn, sum(hist.values()), 'sites')
    for idx,c in sorted(hist.items()):
        print('  field20[%d] x%d -> %s  %s' % (idx, c, '/'.join(sym.get(idx,['(no name)'])), hex(ws[idx])))
