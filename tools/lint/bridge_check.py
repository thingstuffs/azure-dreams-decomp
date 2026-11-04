"""Check stable-site bridge-cast ledger rows against current function bodies."""
from __future__ import annotations

from collections import Counter
import json
from pathlib import Path
import sys

sys.path.insert(0, str(Path(__file__).resolve().parents[1] / 'readability'))
import score


REQUIRED = {'site_id', 'file', 'function', 'cast_text', 'reason', 'evidence',
            'status', 'retired_by', 'ordinal'}


def function_texts(text):
    tokens = score.lex(text)
    pairs = score.pairs_of(tokens)[0]
    result = {}
    for start, name, body, end, _ in score.definitions(tokens, pairs):
        symbol = tokens[name].value
        result.setdefault(symbol, []).append(text[tokens[start].pos:tokens[end].pos + 1])
    return result


def check_bridges(root: Path, ledger: Path):
    """Return (status counts, errors). An absent literal must be explicitly retired."""
    rows = [json.loads(line) for line in ledger.read_text().splitlines() if line.strip()]
    counts, errors, seen, cache = Counter(), [], set(), {}
    for number, row in enumerate(rows, 1):
        label = f'bridge row {number}'
        if not isinstance(row, dict) or not REQUIRED <= row.keys():
            errors.append(f'{label}: missing required fields')
            continue
        site = row['site_id']
        if not isinstance(site, str) or not site or site in seen:
            errors.append(f'{label}: duplicate or invalid site_id')
            continue
        seen.add(site)
        status = row['status']
        if status not in {'open', 'retired'}:
            errors.append(f'{site}: invalid status {status!r}')
            continue
        counts[status] += 1
        rel = row['file']
        if (not isinstance(rel, str) or not rel.startswith('src/') or not rel.endswith('.c')
                or any(part in {'', '.', '..'} for part in rel.split('/'))):
            errors.append(f'{site}: invalid source path')
            continue
        if status == 'retired':
            if not row['reason']:
                errors.append(f'{site}: retirement needs a reason')
            continue
        cast = row['cast_text']
        ordinal = row['ordinal']
        if (not isinstance(cast, str) or not cast
                or type(ordinal) is not int or ordinal < 1):
            errors.append(f'{site}: open row needs a literal cast and positive ordinal')
            continue
        path = root / rel
        if rel not in cache:
            if not path.is_file() or path.is_symlink() or path.stat().st_size > 4 * 1024 * 1024:
                cache[rel] = None
            else:
                cache[rel] = function_texts(path.read_text())
        functions = cache[rel]
        if functions is None or row['function'] not in functions:
            errors.append(f'{site}: source function is missing')
            continue
        occurrences = sum(body.count(cast) for body in functions[row['function']])
        if occurrences < ordinal:
            errors.append(f'{site}: cast absent in function (found {occurrences}, need {ordinal}): {cast}')
    return counts, errors
