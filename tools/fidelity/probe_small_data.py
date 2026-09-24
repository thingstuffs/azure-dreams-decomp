"""Isolated genuine-ASPSX small-data experiment; never edits production tools."""
import argparse
import hashlib
import json
from pathlib import Path
import shutil
import subprocess
import sys

ROOT = Path(__file__).resolve().parents[2]
ap = argparse.ArgumentParser(description=__doc__)
ap.add_argument('--out', type=Path, default=ROOT / 'work/fidelity/small_data_probe')
ap.add_argument('--versions', default='2.79', help='comma-separated genuine ASPSX versions')
args = ap.parse_args()
HERE = args.out.resolve()
HERE.mkdir(parents=True, exist_ok=True)
sys.path.insert(0, str(ROOT / 'tools/fidelity'))
import aspsx_diff as ad
from objread import read_elf, read_lnk

ad.TMP = HERE / 'tmp'
ad.TMP.mkdir(exist_ok=True)
candidate = HERE / 'candidate'
candidate.mkdir(exist_ok=True)
(candidate / 'maspsx').mkdir(exist_ok=True)
cli = (ROOT / 'tools/maspsx/maspsx.py').read_text()
(candidate / 'maspsx.py').write_text(cli.replace('if not args.dont_force_G0:', 'if True:  # isolate ASPSX small-data selection from GNU as'))
source = (ROOT / 'tools/maspsx/maspsx/__init__.py').read_text()
old = '''                    or (
                        symbol in self.extern_sizes
                        and 0 < self.extern_sizes[symbol] <= self.sdata_limit
                    )'''
assert source.count(old) == 1
patched = source.replace(old, '')
old = 'symbol in self.sdata_entries or symbol in self.sbss_entries'
assert patched.count(old) == 2
patched = patched.replace(old, 'self.sdata_limit > 0 and (symbol in self.sdata_entries or symbol in self.sbss_entries)')
old = '''            elif line.startswith(".data"):
                res.append(".section .data")'''
assert patched.count(old) == 1
patched = patched.replace(old, '''            elif line.startswith(".extern"):
                # Genuine ASPSX does not use extern sizes to select $gp addressing.
                # Retain the metadata internally, but do not let GNU as reinterpret it.
                pass

''' + old)
(candidate / 'maspsx/__init__.py').write_text(patched)

definitions = {
    'extern4': '\t.extern\tprobe_data,4\n',
    'extern16': '\t.extern\tprobe_data,16\n',
    'unknown': '',
    'comm4': '\t.comm\tprobe_data,4\n',
    'comm16': '\t.comm\tprobe_data,16\n',
    'lcomm4': '\t.lcomm\tprobe_data,4\n',
    'sdata4': '\t.sdata\n\t.align\t2\nprobe_data:\n\t.word\t1\n',
}
operations = {
    'load': '\tlw\t$2,probe_data\n\tnop\n',
    'store': '\tsw\t$4,probe_data\n',
    'load_offset': '\tlw\t$2,probe_data+2\n\tnop\n',
    'address': '\tla\t$2,probe_data\n',
    'hazard': '\tlw\t$2,0($4)\n\t#nop\n\tsw\t$2,probe_data\n',
}
records = []
for defname, definition in definitions.items():
    for opname, operation in operations.items():
        text = definition + '\t.text\n\t.align\t2\n\t.globl\tprobe_fn\n\t.ent\tprobe_fn\nprobe_fn:\n' + operation + '\t.end\tprobe_fn\n'
        for version in args.versions.split(','):
            for limit in [0, 8]:
                name = f'{defname}_{opname}_{version}_G{limit}'
                td = HERE / name
                td.mkdir(exist_ok=True)
                (td / 'input.s').write_text(text)
                genuine, error = ad.run_aspsx(ad.aspsx_input(text), version, ['-q', f'-G{limit}'], td)
                rec = dict(case=name, genuine_error=error, legs={})
                if genuine:
                    (td / 'genuine.obj').write_bytes(genuine)
                for label, script in [('stock', ROOT / 'tools/maspsx/maspsx.py'), ('candidate', candidate / 'maspsx.py')]:
                    objpath = td / f'{label}.o'
                    cmd = [str(ad.VENV_PY), str(script), f'--aspsx-version={version}', '--dont-force-G0', '--run-assembler', '--gnu-as-path=mipsel-linux-gnu-as', '-EL', '-march=r3000', f'-G{limit}', '-o', str(objpath)]
                    result = subprocess.run(cmd, input=text, capture_output=True, text=True)
                    if result.returncode:
                        rec['legs'][label] = {'error': result.stderr[-400:]}
                    elif genuine:
                        ma = ad.View(read_elf(objpath.read_bytes()))
                        ge = ad.View(read_lnk(genuine), ref=ma)
                        diff = ad.compare_units(ma, ge, ['probe_fn'])
                        rec['legs'][label] = {k:v for k,v in diff.items() if k != 'regions'}
                        rec['legs'][label]['regions'] = diff['regions']
                records.append(rec)
(HERE / 'results.json').write_text(json.dumps(records, indent=2) + '\n')
print('cases', len(records), 'genuine errors', sum(bool(r['genuine_error']) for r in records))
for label in ['stock', 'candidate']:
    failures = [r['case'] for r in records if not r['legs'].get(label, {}).get('exact')]
    print(label, 'failures', len(failures), failures)
print('source sha256', hashlib.sha256(source.encode()).hexdigest())

if any(not r['legs'].get('candidate', {}).get('exact') for r in records):
    sys.exit(1)
