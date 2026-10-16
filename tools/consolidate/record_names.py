"""Preserve evidence-backed semantic record headers during record regeneration."""
import hashlib
import json
from pathlib import Path


def preserved_records(root, records):
    root=Path(root); p=root/'ledger/type_unification.jsonl'
    if not p.exists(): return {}
    renamed={}
    for line in p.read_text().splitlines():
        if not line.strip(): continue
        entry=json.loads(line)
        if entry.get('operation') != 'rename-record': continue
        old=entry['old']; rec=records.get(old)
        if not rec or rec.get('canonical_type') != entry['type']:
            raise ValueError('semantic record metadata missing/inconsistent: '+old)
        for header,hashkey in ((rec['header'],'sha256'),(rec['canonical_header'],'canonical_sha256')):
            rel=Path(header)
            if rel.is_absolute() or '..' in rel.parts: raise ValueError('unsafe record header: '+header)
            target=root/'include'/rel
            if hashlib.sha256(target.read_bytes()).hexdigest() != rec[hashkey]:
                raise ValueError('semantic record changed; reconcile its evidence before regeneration: '+header)
        renamed[old]=rec
    return renamed
