#!/usr/bin/env python3
"""Bind the census's exceptional comparison counts to actual private objects."""
import json
from pathlib import Path
import dependency_import as D
from fidelity import aspsx_diff as A
HERE = Path(__file__).resolve().parent
_, records = D.load_run(HERE/'census_reconciled')
fixture = HERE/'retire_sink/combined_final_fixture'
elf_path = fixture/'build_slus/build/slus_006.14.elf'
linked = A.read_elf(elf_path.read_bytes())
rows = []
for rid, record in records.items():
    if record['funcs'] == record['maspsx_retail']['checked']:
        continue
    obj_path = fixture/'build_slus/build/src'/f'{rid.split("/")[1]}.o'
    funcs = A.functions(A.read_elf(obj_path.read_bytes()))
    mapped = sorted(set(funcs) & set(linked.symbols))
    unmapped = sorted(set(funcs) - set(linked.symbols))
    assert len(funcs) == record['funcs'] and len(mapped) == record['maspsx_retail']['checked']
    rows.append({'row': rid, 'object': str(obj_path.relative_to(D.ROOT)),
                 'object_sha256': D.sha(obj_path), 'object_function_extents': funcs,
                 'mapped_symbols': {name: linked.symbols[name] for name in mapped},
                 'unmapped_symbols': unmapped, 'census_retail': record['maspsx_retail']})
data_only = [r['row'] for r in records.values() if r['funcs'] == r['words'] == 0]
assert len(rows) == 2 and data_only == ['slus/gte_port_state']
result = {'status': 'PASS', 'scope': 'private final fixture; symbol presence only',
          'journal_sha256': D.sha(HERE/'census_reconciled/journal.jsonl'),
          'linked_elf': str(elf_path.relative_to(D.ROOT)), 'linked_elf_sha256': D.sha(elf_path),
          'reader_sha256': D.sha(D.ROOT/'tools/fidelity/objread.py'),
          'comparator_sha256': D.sha(D.ROOT/'tools/fidelity/aspsx_diff.py'),
          'rows': rows, 'data_only_rows': data_only,
          'limitation': 'Missing linked symbols do not establish whether helper instruction bytes occur elsewhere. Data-only rows provide no instruction comparison.'}
(HERE/'dependency_projection/scope_check.json').write_text(json.dumps(result, indent=2)+'\n')
print(json.dumps(result, indent=2))
