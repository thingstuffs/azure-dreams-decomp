"""Strict two-placement witness for a row whose recipe names another VMA."""
import hashlib
import json
from pathlib import Path
import re
import subprocess


def number(value):
    return int(value, 0) if isinstance(value, str) else value


def digest(blob):
    return hashlib.sha256(blob).hexdigest()


def prove_invariant_placement(root, document, original, rules, old_vma, new_vma, wanted, stem):
    """Accept only a loader-bound view and identical independent original-object links.

    No tables/allocations are moved and no relocation or output bytes are patched.
    A self-address relocation, missing load proof or any byte difference rejects it.
    """
    matches = list(re.finditer(r'^\s*\.out_\w+\s+(0x[0-9A-Fa-f]+)\s*:', rules, re.M))
    if len(matches) != 1 or number(matches[0][1]) != old_vma or '(NOLOAD)' in rules:
        return None
    proof = document.get('load_evidence')
    if not proof:
        return None
    evidence_path = (root/proof['path']).resolve()
    if not evidence_path.is_relative_to(root.resolve()):
        return None
    records = [json.loads(line) for line in evidence_path.read_text().splitlines() if line.strip()]
    records = [r for r in records if digest(json.dumps(r,sort_keys=True,separators=(',',':')).encode()) == proof['record_sha256']]
    if len(records) != 1:
        return None
    record = records[0]
    start, size, base = (number(document[k]) for k in ('foff','size','vma'))
    if (not base <= new_vma < new_vma+len(wanted) <= base+size
            or record.get('schema') != 'azure-clean.instance-load-region.v1'
            or record.get('container') != document['container']
            or not str(record.get('method','')).startswith(('validated ', 'internal link-evidence'))
            or not record.get('evidence')
            or not number(record['foff']) <= start < start+size <= number(record['foff'])+number(record['size'])
            or number(record['base'])-number(record['foff']) != number(record['delta'])
            or base-start != number(record['delta'])):
        return None
    outputs = []
    for label, vma in (('recipe',old_vma),('selected',new_vma)):
        match = matches[0]
        script = rules[:match.start(1)] + f'0x{vma:08X}' + rules[match.end(1):]
        ld, elf, binary = (Path(str(stem)+'.'+label+suffix) for suffix in ('.ld','.elf','.bin'))
        ld.write_text(script)
        argv = ['mipsel-linux-gnu-ld','-EL','--no-check-sections','-T',str(ld),'-o',str(elf),str(original)]
        result = subprocess.run(argv,cwd=root,capture_output=True,text=True)
        if result.returncode:
            return None
        result = subprocess.run(['mipsel-linux-gnu-objcopy','-O','binary','--only-section=.out_0000',str(elf),str(binary)],cwd=root,capture_output=True,text=True)
        if result.returncode:
            return None
        outputs.append(binary.read_bytes())
    if outputs[0] != wanted or outputs[1] != wanted:
        return None
    return dict(method='independent GNU links at recipe and selected VMAs; both exact against retail',
                recipe_vma=hex(old_vma), selected_vma=hex(new_vma), bytes=len(wanted),
                original_object_sha256=digest(original.read_bytes()), recipe_bytes_sha256=digest(outputs[0]),
                selected_bytes_sha256=digest(outputs[1]), retail_sha256=digest(wanted),
                load_record_sha256=proof['record_sha256'])
