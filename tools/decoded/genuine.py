#!/usr/bin/env python3
"""Independent genuine-ASPSX comparison of every complete decoded-image TU."""
import argparse
import hashlib
import json
import os
from pathlib import Path
import re
import struct
import subprocess
import sys
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from tools import decoded_images as D


def verify(root, work, scratch):
    root, work, scratch = root.resolve(), work.resolve(), scratch.resolve()
    work.mkdir(parents=True, exist_ok=True)
    scratch.mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(root/'tools/fidelity'))
    import aspsx_diff as A
    results = []
    for image in D.manifests(root):
        data, _ = D.reproduce(root, image)
        base = D.number(image['address'])
        addresses = {k:D.number(v) for k,v in image['symbols'].items()}
        table = {f['name']:(D.number(f['address']),f['size']) for u in image['units'] for f in u['functions']}
        addresses.update({k:v[0] for k,v in table.items()})
        if (root/'config/names.tsv').is_file():
            for line in (root/'config/names.tsv').read_text().splitlines():
                cols = line.split('\t')
                if len(cols)>=3:
                    for name in cols[1:3]:
                        if name in addresses:
                            addresses.update({alias:addresses[name] for alias in cols[1:3]})
        aliases = {n:'func_'+f'{a:08X}' for n,a in addresses.items()
                   if re.fullmatch(r'func_[0-9A-Fa-f]{8}',n) and int(n[5:],16)!=a}
        for unit in image['units']:
            stem = Path(unit['source']).stem
            source, asm, obj = root/unit['source'], work/(stem+'.s'), work/(stem+'.o')
            def run(command, log, stdin=None, cwd=root):
                with (work/log).open('wb') as err:
                    return subprocess.run(list(map(str,command)),cwd=cwd,input=stdin,
                        env=dict(os.environ,TMPDIR=str(scratch),TMP=str(scratch),TEMP=str(scratch)),
                        stdout=subprocess.PIPE,stderr=err,check=True).stdout
            gcc = root/'build_ovl/toolchain/compilers'/('gcc-'+unit['compiler'])
            run(['nice','-n','10',gcc/'gcc','-B'+str(gcc)+'/', '-S','-O2',unit['flags'],
                 '-I'+str(root/'include'),'-w',source,'-o',asm],stem+'.gcc.log')
            run(['nice','-n','10','bash',root/'build_ovl/tools/cc.sh',source,obj,unit['compiler'],unit['flags']],stem+'.ordinary.log')
            canonical = run([sys.executable,root/'build_ovl/tools/ccproc.py','--names-only','--names-tsv',root/'config/names.tsv'],stem+'.names.log',asm.read_bytes())
            (scratch/'IN.S').write_bytes(A.aspsx_input(canonical.decode()))
            run(['nice','-n','10',root/'toolchain/genuine/bin/wibo',root/'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE',
                 '-q','-G0','-o','OUT.OBJ','IN.S'],stem+'.aspsx.log',cwd=scratch)
            ordinary = A.View(A.read_elf(obj.read_bytes()))
            genuine = A.View(A.read_lnk((scratch/'OUT.OBJ').read_bytes()),ref=ordinary)
            if ordinary.obj.unknown or genuine.obj.unknown:
                raise ValueError('unclassified assembler records')
            comparison = A.compare_units(ordinary,genuine)
            if not comparison['exact']:
                raise ValueError('complete genuine and ordinary TUs differ')
            genuine = A.View(genuine.obj,ref=ordinary,alias=aliases)
            expected_names = {f['name'] for f in unit['functions']}
            if set(genuine.funcs)!=expected_names:
                raise ValueError('unaccounted complete-TU exports')
            functions = []
            for name in genuine.funcs:
                address,size = table[name]
                def resolve(symbol):
                    if symbol in addresses:return addresses[symbol]
                    if re.fullmatch(r'(D|func)_[0-9A-Fa-f]{8}',symbol):return int(symbol.split('_')[1],16)
                    return None
                words,masked = A.resolve_tokens(genuine,name,address,resolve,0x80080994)
                actual = struct.pack('<'+'I'*len(words),*words)
                if masked or len(actual)!=size or actual!=data[address-base:address-base+size]:
                    raise ValueError('complete decoded genuine function differs: '+name)
                functions.append(dict(name=name,address=hex(address),size=size,sha256=D.digest(actual)))
            if len(genuine.obj.sections['.text'])!=sum(f['size'] for f in functions) or any(v for k,v in genuine.obj.sections.items() if k!='.text'):
                raise ValueError('unaccounted complete-TU text or data')
            results.append(dict(image=image['image'],source=unit['source'],source_sha256=D.digest(source.read_bytes()),
                                comparison=comparison,functions=functions,complete_tu=True))
    return dict(result='PASS',genuine_aspsx='2.79',masked_relocations=0,units=results,
                functions=sum(len(r['functions']) for r in results),text_bytes=sum(f['size'] for r in results for f in r['functions']))


if __name__=='__main__':
    parser = argparse.ArgumentParser(description=__doc__)
    for name in ('root','work','scratch','output'):
        parser.add_argument('--'+name,type=Path,required=True)
    args = parser.parse_args()
    args.output.write_text(json.dumps(verify(args.root,args.work,args.scratch),indent=2)+'\n')
