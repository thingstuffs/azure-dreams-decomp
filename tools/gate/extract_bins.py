#!/usr/bin/env python3
"""Extract MAIN.BIN/TOWN.BIN/DUNGEON.BIN/OVMOVIE.BIN from the MODE2/2352 disc image
by parsing ISO9660. Data area of each 2352-byte sector = bytes [24:24+2048]."""
import sys, struct, os

DISC = sys.argv[1] if len(sys.argv)>1 else "bin/Azure Dreams.bin"
OUT  = sys.argv[2] if len(sys.argv)>2 else "/tmp/ov"
SECT = 2352
DATA_OFF = 24
DATA_SZ = 2048

def read_sector_data(f, lba):
    f.seek(lba*SECT + DATA_OFF)
    return f.read(DATA_SZ)

def read_logical(f, lba, nbytes):
    out = bytearray()
    while len(out) < nbytes:
        out += read_sector_data(f, lba)
        lba += 1
    return bytes(out[:nbytes])

def parse_dir(f, extent_lba, extent_len):
    """Yield (name, lba, length, is_dir) from a directory extent."""
    data = read_logical(f, extent_lba, extent_len)
    i = 0
    while i < len(data):
        rec_len = data[i]
        if rec_len == 0:
            # advance to next sector boundary
            i = ((i // DATA_SZ) + 1) * DATA_SZ
            continue
        ext_lba = struct.unpack_from('<I', data, i+2)[0]
        ext_len = struct.unpack_from('<I', data, i+10)[0]
        flags   = data[i+25]
        name_len = data[i+32]
        name = data[i+33:i+33+name_len]
        yield name, ext_lba, ext_len, bool(flags & 0x02)
        i += rec_len

def main():
    f = open(DISC, 'rb')
    pvd = read_sector_data(f, 16)
    assert pvd[1:6] == b'CD001', "not ISO9660"
    # root dir record at offset 156 in PVD data
    root = pvd[156:156+34]
    root_lba = struct.unpack_from('<I', root, 2)[0]
    root_len = struct.unpack_from('<I', root, 10)[0]
    print(f"root dir lba={root_lba} len={root_len}")
    os.makedirs(OUT, exist_ok=True)
    # walk root; recurse into dirs
    def walk(lba, length, prefix=""):
        for name, elba, elen, isdir in parse_dir(f, lba, length):
            nm = name.split(b';')[0].decode('latin1')
            if nm in ('','\x00','\x01'): continue
            if isdir:
                walk(elba, elen, prefix+nm+"/")
            else:
                print(f"  FILE {prefix}{nm}  lba={elba} len={elen} (0x{elen:x})")
                if nm.upper().endswith('.BIN'):
                    outp = os.path.join(OUT, prefix.replace('/','_')+nm)
                    with open(outp,'wb') as o:
                        o.write(read_logical(f, elba, elen))
                    print(f"    -> wrote {outp}")
    walk(root_lba, root_len)

if __name__=='__main__':
    main()
