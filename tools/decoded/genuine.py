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
import tempfile
ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT))
from tools import decoded_images as D


def linked_data(view, section, resolve, anchors):
    data = bytearray(view.obj.sections[section])
    for (source, offset), (relocation, (kind, name, addend)) in view.rel.items():
        if source != section:
            continue
        if relocation != '32' or offset % 4 or not 0 <= offset <= len(data) - 4:
            raise ValueError(f'unhandled decoded data relocation {section}+{offset:#x}: {relocation}')
        if kind in ('abs', 'addr'):
            target = 0
        elif kind == 'sec':
            target = anchors.get(name)
        elif kind in ('sym', 'fn'):
            target = resolve(name)
        else:
            target = None
        if target is None:
            raise ValueError(f'unbound decoded data relocation {section}+{offset:#x}: {name}')
        struct.pack_into('<I', data, offset, (target + addend) & 0xffffffff)
    return bytes(data)


def verify(root, work, scratch):
    root, work, scratch = root.resolve(), work.resolve(), scratch.resolve()
    work.mkdir(parents=True, exist_ok=True)
    scratch.mkdir(parents=True, exist_ok=True)
    sys.path.insert(0, str(root/'tools/fidelity'))
    import aspsx_diff as A

    class PlacementView(A.View):
        def canon(self, target, addend):
            kind, name = target
            if kind == 'sym' and name not in self.obj.symbols and name not in self.absmap:
                return ('sym', name, addend)
            return super().canon(target, addend)

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
                if len(cols)>3 and cols[3].strip().startswith('copy_of='):
                    continue  # placed copy: its canonical row binds the name
                if len(cols)>=3:
                    for name in cols[1:3]:
                        if name in addresses:
                            addresses.update({alias:addresses[name] for alias in cols[1:3]})
        aliases = {n:'func_'+f'{a:08X}' for n,a in addresses.items()
                   if re.fullmatch(r'func_[0-9A-Fa-f]{8}',n) and int(n[5:],16)!=a}
        for unit in image['units']:
            placement = unit.get('placement')
            stem = placement or Path(unit['source']).stem
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
            asflags = unit.get('genuine_asflags', [])
            run(['nice','-n','10',root/'toolchain/genuine/bin/wibo',root/'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE',
                 '-q','-G0',*asflags,'-o','OUT.OBJ','IN.S'],stem+'.aspsx.log',cwd=scratch)
            ordinary = A.View(A.read_elf(obj.read_bytes()))
            genuine = A.View(A.read_lnk((scratch/'OUT.OBJ').read_bytes()),ref=ordinary)
            if ordinary.obj.unknown or genuine.obj.unknown:
                raise ValueError('unclassified assembler records')
            exports = {D.source_symbol(f): f for f in unit['functions']}
            comparison = A.compare_units(ordinary, genuine, scope=sorted(exports) if placement else None)
            if not comparison['exact']:
                raise ValueError('genuine and ordinary decoded sections differ: ' + unit['source'])
            data_extents = {d['section']: d for d in unit.get('data', [])}
            section_anchors = {section: D.number(d['address']) for section, d in data_extents.items()}
            if placement:
                genuine = PlacementView(genuine.obj, ref=ordinary)
                bindings = {n: D.number(a) for n, a in unit['bindings'].items()}
                bindings.update({n: D.number(f['address']) for n, f in exports.items()})
            else:
                genuine = A.View(genuine.obj, ref=ordinary, alias=aliases)
            if (set(exports) - genuine.funcs.keys()
                    or (not placement and set(genuine.funcs) != exports.keys())):
                raise ValueError('unaccounted complete-TU exports')
            def resolve(symbol):
                if placement:
                    return bindings.get(symbol)
                if symbol in addresses:
                    return addresses[symbol]
                if re.fullmatch(r'(D|func)_[0-9A-Fa-f]{8}', symbol):
                    return int(symbol.split('_')[1], 16)
                return None

            functions = []
            for symbol, function in exports.items():
                name = function['name']
                address, size = table[name]
                words,masked = A.resolve_tokens(genuine,symbol,address,resolve,0x80080994,
                                               section_anchors=section_anchors)
                actual = struct.pack('<'+'I'*len(words),*words)
                if masked or len(actual)!=size or actual!=data[address-base:address-base+size]:
                    raise ValueError('complete decoded genuine function differs: '+name)
                functions.append(dict(name=name,address=hex(address),size=size,sha256=D.extent_digest(actual)))
            if not placement:
                if len(genuine.obj.sections['.text']) != sum(f['size'] for f in functions):
                    raise ValueError('unaccounted complete-TU text')
                actual_data = {'.rodata' if k == '.rdata' else k: k for k, v in genuine.obj.sections.items()
                               if k != '.text' and v}
                if actual_data.keys() != data_extents.keys():
                    raise ValueError('unaccounted complete-TU data')
                for section, datum in data_extents.items():
                    address, size = D.number(datum['address']), D.number(datum['size'])
                    actual = linked_data(genuine, actual_data[section], resolve, section_anchors)
                    if actual != data[address-base:address-base+size]:
                        raise ValueError('complete decoded genuine data differs: ' + unit['source'])
            results.append(dict(image=image['image'],source=unit['source'],source_sha256=D.digest(source.read_bytes()),
                                comparison=comparison,functions=functions,complete_tu=not placement,
                                genuine_asflags=asflags,
                                **({'placement': placement} if placement else {})))
    return dict(result='PASS',genuine_aspsx='2.79',masked_relocations=0,units=results,
                functions=sum(len(r['functions']) for r in results),text_bytes=sum(f['size'] for r in results for f in r['functions']))


def check(root, work=None, scratch=None, output=None, *, optional=False):
    root = root.resolve()
    assembler = root / 'toolchain/genuine/psyq/psyq4.4/ASPSX.EXE'
    runner = root / 'toolchain/genuine/bin/wibo'
    if not assembler.is_file() or not os.access(runner, os.X_OK):
        if optional:
            print('Genuine ASPSX 2.79 SKIP: assembler or runner unavailable')
            return
        raise ValueError('genuine ASPSX 2.79 and wibo are required')
    if optional and not all((root / s['container']).is_file()
                            for image in D.manifests(root) for s in image['streams']):
        print('Genuine ASPSX 2.79 SKIP: extracted retail inputs unavailable')
        return

    work = work or (root / 'build/decoded/genuine')
    output = output or work / 'proof.json'
    if scratch is None:
        (root / 'build').mkdir(exist_ok=True)
        # ASPSX needs a short working path and fixed DOS-compatible filenames.
        with tempfile.TemporaryDirectory(prefix='as', dir=root / 'build') as scratch_dir:
            result = verify(root, work, Path(scratch_dir))
    else:
        result = verify(root, work, scratch)
    output.write_text(json.dumps(result, indent=2) + '\n')
    print(f"Genuine ASPSX 2.79 PASS: {result['functions']} functions, "
          f"{result['masked_relocations']} masked relocations")


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=ROOT)
    for name in ('work', 'scratch', 'output'):
        parser.add_argument('--' + name, type=Path)
    parser.add_argument('--if-available', action='store_true',
                        help='print a skip when the original assembler or retail inputs are absent')
    args = parser.parse_args()
    check(args.root, args.work, args.scratch, args.output, optional=args.if_available)


if __name__ == '__main__':
    main()
