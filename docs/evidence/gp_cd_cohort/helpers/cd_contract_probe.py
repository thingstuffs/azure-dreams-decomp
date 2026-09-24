"""Compare fresh baseline/candidate CD declarations at registered recipes."""
from pathlib import Path
import json
import os
import subprocess
import sys

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
sys.path.insert(0, str(ROOT / 'work/native_lane/gp_cd_partition'))
import baseline_probe as B
A, V = B.A, B.verify
V.VENV_PY = B.PY
A.TMP = ROOT / 'work/native_lane/cdcontract_aspsx'
A.TMP.mkdir(exist_ok=True)
A.SLUS_ELF = ROOT / 'build_slus/build/slus_006.14.elf'
A.SLUS_BIN = ROOT / 'baserom/slus_006.14'
A._SLUS = None
ALIGN = B.canonical_alignment()[0]
EXTENTS = B.linked_extents()
RECIPES = B.registry()


def compile_legs(stem, source, label):
    out = HERE / 'objects' / stem / label
    out.mkdir(parents=True, exist_ok=True)
    recipe = RECIPES['src/' + stem + '.c']
    obj, error = V._compile_slus_source(
        {'cell': recipe['ccver'], 'flags': recipe['ccflags'], 'row_asflags': recipe['asflags']},
        source, out, HERE / 'include' if label == 'candidate' else ROOT / 'include')
    assert not error, error
    stock = A.View(A.read_elf(obj.read_bytes()))
    asm = V.postprocess_slus((out / 'a.s').read_text(), names_only=True)
    (out / 'genuine_input.s').write_text(asm)
    env = dict(os.environ)
    env.pop('AZURE_MASPSX', None)
    env.pop('AZURE_MASPSX_COMPANION', None)
    generic_path = out / 'generic.o'
    command = [str(B.PY), str(B.GENERIC), '--aspsx-version=2.79', '--dont-force-G0',
               '--run-assembler', '--gnu-as-path=mipsel-linux-gnu-as',
               '-I' + str(ROOT / 'raw'), '-I' + str(ROOT / 'include'),
               '-EL', '-march=r3000', '-G8', *recipe['asflags'].split(), '-o', str(generic_path)]
    result = subprocess.run(command, input=(out / 'a.proc.s').read_text(),
                            capture_output=True, text=True, env=env, cwd=ROOT)
    (out / 'generic.log').write_text(result.stdout + result.stderr)
    assert result.returncode == 0, result.stderr
    generic = A.View(A.read_elf(generic_path.read_bytes()))
    lnk, error = A.run_aspsx(A.aspsx_input(asm), '2.79', ['-q'], out)
    assert not error, error
    (out / 'genuine.lnk').write_bytes(lnk)
    genuine = A.View(A.read_lnk(lnk), generic, A.aliases(asm))
    scope = sorted(stock.funcs)
    assert set(generic.funcs) == set(genuine.funcs) == set(scope)
    legs = {'stock': stock, 'generic': generic, 'genuine': genuine}
    report = {'source_sha256': B.digest(source), 'recipe': recipe, 'functions': scope,
              'hashes': {name: B.digest(path) for name, path in
                         [('stock', obj), ('generic', generic_path), ('genuine', out / 'genuine.lnk')]},
              'retail': {name: {f: B.retail_detail(view, f, EXTENTS[f], out, name, ALIGN)
                                for f in scope} for name, view in legs.items()},
              'generic_vs_genuine': B.compare(generic, genuine, scope)}
    return legs, report


def main():
    stems = sys.argv[1:] or ['w_8003F368', 'w_8003E758']
    results = []
    for stem in stems:
        base_source = ROOT / 'src/slus' / (stem + '.c')
        candidate = HERE / 'candidates' / (stem + '.c')
        before = B.digest(base_source)
        base, baseline = compile_legs(stem, base_source, 'baseline')
        after, changed = compile_legs(stem, candidate, 'candidate')
        assert B.digest(base_source) == before
        scope = baseline['functions']
        assert changed['functions'] == scope
        result = {'row': 'slus/' + stem, 'baseline': baseline, 'candidate': changed,
                  'comparison': {name: B.compare(base[name], after[name], scope) for name in base},
                  'header_sha256': B.digest(HERE / 'include/slus/cd_state.h'),
                  'production_source_unchanged': True}
        (HERE / (stem + '_receipt.json')).write_text(json.dumps(result, indent=2) + '\n')
        results.append(result)
        print(stem, json.dumps({name: report['exact'] for name, report in result['comparison'].items()}),
              'stock retail', all(x['exact_unmasked'] for x in changed['retail']['stock'].values()), flush=True)
    return results


if __name__ == '__main__':
    main()
