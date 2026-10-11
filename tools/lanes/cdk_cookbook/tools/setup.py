#!/usr/bin/env python3
"""Copy the small compiler/data inputs used by the cookbook into the lane."""
from pathlib import Path
import hashlib, json, shutil
L = Path(__file__).resolve().parents[1]
R = L.parents[2]
S = L / 'scratch'

def main():
    for name in ('evidence','tmp','scratch'):
        (L/name).mkdir(exist_ok=True)
        (L/name/'.ignore').write_text('*\n')
    copied = {}
    for rel in ['toolchain/compilers/gcc-2.7.2-cdk/' + n for n in ('cc1', 'gcc', 'cpp')] + [
        'toolchain/gcc-src/2.7.2-cdk/' + n for n in
        ('sched.c','global.c','local-alloc.c','cse.c','reload1.c','combine.c','flow.c','rtl.def','rtl.h','machmode.def','version.c','config/mips/mips.h')]:
        src = R / rel
        if not src.exists():
            continue
        dst = S / rel
        dst.parent.mkdir(parents=True, exist_ok=True)
        shutil.copy2(src, dst)
        copied[rel] = hashlib.sha256(dst.read_bytes()).hexdigest()
    shutil.copytree(R / 'toolchain/maspsx', S / 'toolchain/maspsx',
                    ignore=shutil.ignore_patterns('__pycache__','.git','tests'), dirs_exist_ok=True)
    (S / '.ignore').write_text('*\n')
    (L / 'evidence/input_hashes.json').write_text(json.dumps(copied, indent=2)+'\n')
    print('Copied compiler and pass sources into scratch; no shared writes.')
if __name__ == '__main__': main()
