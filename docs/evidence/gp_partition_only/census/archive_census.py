#!/usr/bin/env python3
"""Archive frozen private evidence; never rewrite measured source artifacts."""
import gzip
import hashlib
import json
from pathlib import Path

LANE = Path(__file__).resolve().parent
ROOT = LANE.parents[2]
DEST = ROOT / 'docs/evidence/gp_partition_only/census'

def digest(data):
    return hashlib.sha256(data).hexdigest()

def scrub(data):
    return data.replace(b'<repo>', b'<repo>').replace(b'<reference-repo>', b'<reference-repo>')

assert not DEST.exists(), 'refusing to replace a frozen archive'
summary = json.loads((LANE / 'census_report/summary.json').read_text())
assert digest((LANE / 'census_report/summary.json').read_bytes()) == '239cd089390ca6f06e9c6ce163e216326476fabfa21fd047f19a890ddfc1a1f6'
journal = [json.loads(line) for line in (LANE / 'census_reconciled/journal.jsonl').read_text().splitlines()]
assert len(journal) == len({r['row'] for r in journal}) == 6767
assert all(r['status'] == 'ok' and r['maspsx_exact'] and r['selfcheck'] for r in journal)
assert sum(bool(r['exact_versions']) for r in journal) == 6600
assert all('_sink_call_separated_la' not in r.get('fired', []) for r in journal)
assert summary['retail_scope']['masked_words'] == 872
assert summary['retail_scope']['rows_with_masked_words'] == 302
old = {r['id'] for r in map(json.loads, (ROOT/'ledger/maspsx_dependence.jsonl').read_text().splitlines())}
new = {r['row'] for r in journal if not r['exact_versions']}
assert len(old) == 189 and len(new) == 167 and not new-old and len(old-new) == 22

files = [LANE / name for name in [
    'CENSUS_EVIDENCE.md', 'census_report.md', 'census_setup.py', 'census_runner.py',
    'census_compatibility.py', 'census_final_source.py', 'census_reconcile.py',
    'census_report.py', 'census_transition_compatibility.json',
    'census_fixture/census_setup_receipt.json',
    'census_fixture/production_before_census.json', 'census_fixture/production_after_census.json',
    'census_final_fixture/final_source_fixture_receipt.json', 'archive_census.py',
]]
for name in ['census_full', 'census_final_two', 'census_reconciled', 'census_report', 'census_original_report', 'code_metadata_probe']:
    files.extend(p for p in (LANE/name).iterdir() if p.is_file() and not p.name.startswith('.'))
index=[]
for source in sorted(files):
    rel=source.relative_to(LANE)
    original=source.read_bytes()
    content=original if source.suffix == '.o' else scrub(original)
    compressed=len(content)>1000000
    archived=gzip.compress(content,mtime=0) if compressed else content
    target=DEST / (str(rel)+('.gz' if compressed else ''))
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(archived)
    index.append(dict(source=str(rel), archived=str(target.relative_to(DEST)),
                      source_sha256=digest(original), content_sha256=digest(content),
                      archived_sha256=digest(archived), source_bytes=len(original),
                      archived_bytes=len(archived), gzip=compressed))
(DEST/'archive.json').write_text(json.dumps(dict(schema=1, status='ARCHIVED',
    interpretation='Source receipt hashes refer to original private artifacts. Archived text paths are scrubbed; archive hashes bind the stored bytes. Decompress .gz journals before replay. No production census keys were installed.',
    production_dependencies=189,candidate_dependencies=167,removed_rows=sorted(old-new),new_rows=sorted(new-old),
    artifacts=index),indent=2)+'\n')
print(f'Archived {len(index)} artifacts; 189 -> 167 private dependencies, 22 removed and zero added.')
