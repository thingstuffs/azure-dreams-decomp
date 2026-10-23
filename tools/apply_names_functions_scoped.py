"""Stage bank-specific function aliases without replacing earlier bank identities.

New-name scope keys and explicit {row, symbol} identities distinguish functions
that share a runtime address. The compiler already canonicalizes each readable
name independently. This path stages only; complete-TU and image proof remain
the caller's responsibility, just as for scoped data aliases.
"""
import json
import re
import time
from pathlib import Path

from apply_names_data import identifiers, inline_plan, rewrite
from source_layout import own_source, row_path, row_ids_for_paths
from layout_dependencies import consumer_paths


def definition(symbol, text):
    return re.search(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t*]*?\b' +
                     re.escape(symbol) + r'\s*\([^;{]*\)\s*\{', text, re.M)


def main(a, N, complete, scopes):
    if not a.defer_verification or not a.identity_map:
        raise ValueError('bank function scopes require --defer-verification and --identity-map')
    if a.rename_existing or a.reference_map or a.hold_unproven_references:
        raise ValueError('bank function scopes append independent aliases; incompatible batch option')
    if set(scopes) != {r[2] for r in complete}:
        raise ValueError('bank function scopes must cover exactly the proposed new names')
    if len(scopes) != len(complete):
        raise ValueError('duplicate proposed function name')
    identities = json.loads(a.identity_map.read_text())
    if not isinstance(identities, dict):
        raise ValueError('identity map must be an object')
    paths = [p for folder in ('src', 'include') for p in (N.ROOT/folder).rglob('*')
             if p.suffix in ('.c', '.h') and p.is_file()]
    if any(p.is_symlink() or p.stat().st_size > 4*1024*1024 for p in paths):
        raise ValueError('source symlink or oversized source')
    texts = {p: p.read_text() for p in paths}
    configured = {(r[1], r[2]) for r in N.read_names()}
    aliases = {new: old for old, new in configured}
    idents = {i for t in texts.values() for i in identifiers(t)}
    by_id = {r['id']: r for r in N.rows()}
    per_path, additions, seen = {}, [], set()
    # Validate the complete cohort before --only/--limit, so filtering cannot
    # conceal ambiguous scopes. No mutation happens until every guard passes.
    for addr, old, new, evidence in complete:
        if not re.fullmatch(r'func_[0-9A-Fa-f]{8}', old) or addr.lower() != '0x'+old[5:].lower():
            raise ValueError('function address mismatch: ' + old)
        if not re.fullmatch(r'[a-z][a-z0-9_]*', new) or not evidence:
            raise ValueError('invalid snake_case function name/evidence: ' + new)
        if new in seen:
            raise ValueError('duplicate proposed function name: ' + new)
        seen.add(new)
        if (old, new) not in configured and (new in aliases or new in idents):
            raise ValueError('identifier collision: ' + new)
        if new in aliases and aliases[new] != old:
            raise ValueError('configured name has a different identity: ' + new)
        rels = scopes[new]
        if not isinstance(rels, list) or not rels or not all(isinstance(p, str) for p in rels):
            raise ValueError('bank scope needs nonempty path lists: ' + new)
        selected = {}
        for rel in rels:
            p = Path(rel)
            if (p.is_absolute() or '..' in p.parts or not p.parts or
                    p.parts[0] not in ('src', 'include') or p.as_posix() != rel or
                    N.ROOT/p not in texts):
                raise ValueError('unknown or noncanonical bank scope path: ' + rel)
            selected[N.ROOT/p] = texts[N.ROOT/p]
        if a.path_prefix and set(selected) - set(N.scoped_texts(selected, a.path_prefix, N.ROOT)):
            raise ValueError('path prefix excludes a bank scope: ' + new)
        identity = identities.get(new)
        if not isinstance(identity, dict) or identity.get('symbol') != old:
            raise ValueError('bank scope needs a new-name definition identity: ' + new)
        row = by_id.get(identity.get('row'))
        source = row_path(row, N.ROOT) if row else None
        if source not in selected:
            raise ValueError('bank scope omits the defining source: ' + new)
        own = own_source(row, N.ROOT)[0]
        if not (definition(old, own) or ((old, new) in configured and definition(new, own))):
            raise ValueError('identity does not name a current definition: ' + new)
        for p in selected:
            local = per_path.setdefault(p, {})
            if old in local and local[old] != new:
                raise ValueError('overlapping bank scopes: ' + old + ': ' + p.relative_to(N.ROOT).as_posix())
            local[old] = new
        if (old, new) not in configured:
            additions.append((addr, old, new, evidence))
    proposed = complete
    if a.only:
        proposed = [r for r in proposed if r[1] in set(a.only.split(',')) or r[2] in set(a.only.split(','))]
    if a.limit:
        proposed = proposed[:a.limit]
    selected_names = {r[2] for r in proposed}
    additions = [r for r in additions if r[2] in selected_names]
    per_path = {p: {o:n for o,n in local.items() if n in selected_names} for p,local in per_path.items()}
    per_path = {p:local for p,local in per_path.items() if local}
    changed = {}
    for p, local in per_path.items():
        pat = re.compile(r'\b(?:'+'|'.join(map(re.escape,local))+r')\b')
        fresh = rewrite(texts[p], pat, local)
        if fresh != texts[p]:
            changed[p] = fresh
    metadata, rebases = inline_plan(N.ROOT, texts, changed, None, {}, path_mappings=per_path)
    affected = consumer_paths(N.ROOT, {p.relative_to(N.ROOT).as_posix() for p in changed})
    touched = sorted(row_ids_for_paths(affected, N.ROOT))
    receipt = dict(status='UNVERIFIED', new_aliases=len(additions),
                   files=sorted(p.relative_to(N.ROOT).as_posix() for p in changed),
                   rows=touched, map=None, aliases={r[2]:r[1] for r in proposed},
                   scopes={r[2]:scopes[r[2]] for r in proposed}, inline_rebases=rebases,
                   required='independent complete-TU object identity and final scoped image proof')
    print(f"bank function batch: {len(additions)} new aliases; {len(changed)} files; UNVERIFIED staging", flush=True)
    if a.dry_run:
        return receipt
    names_before = N.NAMES.read_bytes()
    journal_before = N.JOURNAL.read_bytes() if N.JOURNAL.exists() else None
    try:
        if additions:
            N.NAMES.write_bytes(names_before.rstrip(b'\n')+b'\n'+''.join('\t'.join(r)+'\n' for r in additions).encode())
        for p,t in changed.items():
            p.write_text(t)
        for p,pair in metadata.items():
            p.write_bytes(pair[1])
        for addr,old,new,evidence in additions:
            N.append_jsonl(N.JOURNAL, dict(addr=addr, old=old, new=new,
                identity_row=identities[new]['row'], rewrite_paths=scopes[new],
                outcome='staged-unverified', batch=True,
                at=time.strftime('%Y-%m-%dT%H:%M:%SZ',time.gmtime())))
        if a.proof_log:
            a.proof_log.write_text(json.dumps(receipt,indent=2)+'\n')
    except BaseException:
        N.NAMES.write_bytes(names_before)
        for p in changed:
            p.write_text(texts[p])
        for p,pair in metadata.items():
            p.write_bytes(pair[0])
        if journal_before is None:
            N.JOURNAL.unlink(missing_ok=True)
        else:
            N.JOURNAL.write_bytes(journal_before)
        raise
    return receipt
