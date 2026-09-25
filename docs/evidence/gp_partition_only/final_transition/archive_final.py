from pathlib import Path
import hashlib
import json

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[2]
OUT = ROOT / 'docs/evidence/gp_partition_only/final_transition'

def sha(data):
    return hashlib.sha256(data).hexdigest()

def scrub(data):
    return (data.replace(b'<repo>', b'<repo>')
                .replace(b'<reference-repo>', b'<reference-repo>')
                .replace(b'<user-home>/', b'<user-home>/')
                .replace(b'<reference-repo>', b'<reference-repo>'))

assert not OUT.exists()
names = ['transition_final/combined.patch', 'transition_final/inventory.json',
         'transition_final/prepare.py', 'transition_final/review_receipt.json',
         'final_root_review.json', 'activate_transition.py', 'ACTIVATION.md',
         'archive_final.py', 'activation_review/cache_plan.json']
for name in ['controls_refresh/REPORT.md', 'controls_refresh/controls.patch',
             'controls_refresh/root_review.json', 'controls_refresh/prepare.py',
             'controls_refresh/prepare_receipt.json', 'controls_refresh/run.py',
             'controls_refresh/run.log', 'controls_refresh/run_receipt.json',
             'controls_refresh/run_final.py', 'controls_refresh/prepare_final.py',
             'controls_refresh/prepare_final_receipt.json',
             'controls_refresh/final_run.log', 'controls_refresh/final_run_receipt.json']:
    if (HERE/name).is_file(): names.append(name)
names += [str(p.relative_to(HERE)) for p in (HERE/'retire_sink').glob('final*') if p.is_file()]
for module in ['list_cursor_e0', 'runtime_directory']:
    names.append(f'retire_sink/combined_final_fixture/ledger/modules/{module}.json')
for name in ['activation_final_check.json', 'activation_final_check.log']:
    if (HERE/name).is_file(): names.append(name)
artifacts=[]
for name in sorted(set(names)):
    original=(HERE/name).read_bytes()
    archived=scrub(original)
    assert (b'/' + b'home/') not in archived, name
    target=OUT/name
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(archived)
    artifacts.append(dict(source=name,source_sha256=sha(original),archive_sha256=sha(archived),bytes=len(archived)))
(OUT/'archive.json').write_text(json.dumps(dict(schema=1,scope='Final60 proposal; private proof, no production activation',
    path_scrubbing='Original source hashes and archived text hashes are distinct. Expand placeholders and restore original work paths for replay.',artifacts=artifacts),indent=2)+'\n')
print('Archived',len(artifacts),'final proposal/proof artifacts')
