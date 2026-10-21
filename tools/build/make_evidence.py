"""Read current make image proof for quality accounting, without module certificates."""
import hashlib
import json
from pathlib import Path


def digest(path):
    return hashlib.sha256(path.read_bytes()).hexdigest()


def checked_receipt(root):
    root = Path(root)
    receipt = json.loads((root/'build/check.json').read_text())
    if (receipt.get('schema') != 'azure-clean.make-check.v2' or not receipt.get('images')
            or receipt['matched'] != receipt['images'] or len(receipt['results']) != receipt['images']
            or any(r['result'] != 'MATCH' for r in receipt['results'])):
        raise ValueError('make check has no complete matching image proof')
    for field in ('inputs', 'outputs'):
        if not receipt.get(field):
            raise ValueError('make check proof lacks '+field)
        for name, expected in receipt[field].items():
            p = Path(name)
            if p.is_absolute() or '..' in p.parts:
                raise ValueError('unsafe make proof input')
            if digest(root/p) != expected:
                raise ValueError('stale make check proof: '+name)
    return receipt


def placements(root):
    """Checked placement + a registered physical module with a consumed shared header."""
    root = Path(root)
    proof = checked_receipt(root)
    generic = {'include/common.h', 'include/game.h', 'include/globals.h', 'include/include_asm.h', 'include/m2c_compat.h'}
    result = {}
    from gate.overlay_module_gate import closure
    def add(module, members, view=None):
        headers = [h for h in module.get('headers', []) if h not in generic and h.endswith('.h') and (root/h).is_file()]
        consumed = closure(view or root, [module['source']])
        headers = sorted(set(headers) & consumed)
        if not headers:
            return
        for member in members:
            rid = member['id']
            if rid in proof.get('rows', {}):
                result[rid] = dict(module=module.get('key', module.get('name')), outcome='applied',
                                   images=proof['rows'][rid], shared_headers=headers)
    overlay = json.loads((root/'config/overlays/modules.json').read_text())['modules']
    for m in overlay:
        add(m, m.get('data_members', [])+m['members'])
    # Placement manifests carry the projected row identities of the same physical TU.
    from gate import overlay_module_placements as P
    for p in P.load(root, overlay):
        add(next(m for m in overlay if m['key']==p['module']), p['projected'])
    slus = json.loads((root/'config/slus_modules.json').read_text())['modules']
    for m in slus:
        if not m.get('partition_only'):
            add(m, m['members'], root/'build_slus')
    return result
