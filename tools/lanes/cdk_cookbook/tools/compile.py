#!/usr/bin/env python3
"""Compile one header-free C probe on the copied CDK compiler; retain RTL and bytes."""
from pathlib import Path
import argparse, hashlib, json, os, shutil, subprocess
L = Path(__file__).resolve().parents[1]
D = L / 'scratch/toolchain/compilers/gcc-2.7.2-cdk'

def compile_one(src, tag=None, extra=()):
    src=Path(src).resolve()
    if not src.is_relative_to(L): raise SystemExit('source must be lane-owned')
    tag=tag or src.stem
    out=L/'tmp/build'/tag
    out.mkdir(parents=True,exist_ok=True)
    shutil.copy2(src,out/'f.i')
    env=dict(os.environ,PYTHONDONTWRITEBYTECODE='1',TMPDIR=str(L/'tmp'))
    cmd=[str(D/'cc1'),'f.i','-quiet','-O2','-G0','-msoft-float','-da','-dp',*extra,'-o','f.s']
    with (out/'compile.log').open('w') as log:
        subprocess.run(cmd,cwd=out,env=env,stdout=log,stderr=subprocess.STDOUT,check=True,timeout=60)
    with (out/'f.gnu.s').open('w') as f:
        subprocess.run(['python3',str(L/'scratch/toolchain/maspsx/maspsx.py'),'--aspsx-version=2.56'],cwd=out,env=env,input=(out/'f.s').read_bytes(),stdout=f,check=True,timeout=60)
    subprocess.run(['mipsel-linux-gnu-as','-EL','-march=r3000','-mabi=32','-G0','-o','f.o','f.gnu.s'],cwd=out,env=env,check=True,timeout=60)
    subprocess.run(['mipsel-linux-gnu-ld','-Ttext','0x80010000','-e','probe',
                    '--defsym=consume=0x80020000','--defsym=sink=0x80020020',
                    '--defsym=step=0x80020040','--defsym=other=0x80020060',
                    '--defsym=tick=0x80020080','--defsym=flags=0x80030000',
                    '-o','f.elf','f.o'],cwd=out,env=env,check=True,timeout=60)
    subprocess.run(['mipsel-linux-gnu-objcopy','-O','binary','-j','.text','f.elf','f.text.bin'],cwd=out,check=True)
    with (out/'f.dis').open('w') as f:
        subprocess.run(['mipsel-linux-gnu-objdump','-dr','f.elf'],cwd=out,stdout=f,check=True)
    result={'source':str(src.relative_to(L)), 'directory':str(out.relative_to(L)),
            'flags':['-O2','-G0','-msoft-float',*extra],
            'text_bytes':(out/'f.text.bin').stat().st_size,
            'text_sha256':hashlib.sha256((out/'f.text.bin').read_bytes()).hexdigest(),
            'source_sha256':hashlib.sha256(src.read_bytes()).hexdigest()}
    (out/'result.json').write_text(json.dumps(result,indent=2)+'\n')
    return result
if __name__=='__main__':
    p=argparse.ArgumentParser();p.add_argument('sources',nargs='+');p.add_argument('--flag',action='append',default=[]);p.add_argument('--tag')
    a=p.parse_args()
    for s in a.sources: print(json.dumps(compile_one(s,a.tag,a.flag)))
