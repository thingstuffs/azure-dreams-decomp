#!/usr/bin/env python3
"""Production gate windows covering a list of edited TUs (for one scoped gate_all.py run).

    python3 tools/headers/windows.py --tus edited.txt [--args]

Every registered row whose physical TU is in the list (overlay rows, module members) contributes the
windows whose file range covers it (common.covering_windows); superseded synthetic-base seeds are
dropped exactly as gate_all.py drops them.  SLUS TUs have no overlay window: their proof is the SLUS
SHA-1 build (tools/build/build_slus.sh --fresh).  --args prints `--only-window X` arguments.
"""
import argparse
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path[:0] = [str(ROOT / 'tools'), str(ROOT / 'tools/build')]


def windows_for(root, tus):
    import layout_compile_identity as L
    from common import covering_windows
    from source_layout import registry, row_relative
    from gate import overlay_module_gate as G
    import gate_all
    tus = set(tus)
    reg = registry(root)
    rows = set()
    for rid, row in reg.items():
        try:
            if row_relative(row, root) in tus:
                rows.add(rid)
        except Exception:
            continue
    for module in G.load_modules(root):
        if module['source'] in tus:
            for x in G.all_members(module):
                rid = x.get('id') or x.get('row_id')
                if rid:
                    rows.add(rid)
    names = set()
    for rid in rows:
        row = reg.get(rid)
        if not row or row.get('foff') is None or row.get('container') == 'slus':
            continue
        for w in covering_windows(row['container'], row['foff'], row['size']):
            names.add(w[0])
    yamls = sorted((Path(root) / 'config/overlays').glob('*.overlay.yaml'))
    sup = gate_all.superseded(yamls)
    return sorted('config/overlays/' + n for n in names if n not in sup)


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', default=str(ROOT))
    ap.add_argument('--tus', required=True, help='file with one TU path per line')
    ap.add_argument('--args', action='store_true')
    a = ap.parse_args()
    tus = [l.strip() for l in Path(a.tus).read_text().splitlines() if l.strip()]
    ws = windows_for(Path(a.root).resolve(), tus)
    if a.args:
        print(' '.join('--only-window ' + w for w in ws))
    else:
        print('\n'.join(ws))
        print(f'{len(ws)} windows', file=sys.stderr)


if __name__ == '__main__':
    main()
