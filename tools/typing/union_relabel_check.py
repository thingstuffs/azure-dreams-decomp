#!/usr/bin/env python3
"""Flag old union member spellings left in a file after an access relabel.

Run against the batch base, before committing: python3 tools/typing/union_relabel_check.py --base HEAD
This is a lexical guard. A flagged mixed use needs a whole-file review before landing.
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import difflib
from pathlib import Path
import re
import subprocess

ACCESS = re.compile(r'(?P<field>(?:->|\.)[A-Za-z_]\w*\.)(?P<member>[A-Za-z_]\w*)')
INLINE_UNION = re.compile(r'\bunion\s*\{([^{}]*)\}\s*([A-Za-z_]\w*)\s*;', re.S)


def swaps_from_diff(patch: str) -> set[tuple[str, str, str]]:
    swaps = set()
    removed: list[str] = []
    added: list[str] = []

    def finish() -> None:
        normalize = lambda line: ACCESS.sub(lambda m: m['field'] + '*', line)
        matcher = difflib.SequenceMatcher(None, list(map(normalize, removed)),
                                          list(map(normalize, added)), autojunk=False)
        pairs = [(a + k, b + k) for a, b, n in matcher.get_matching_blocks() for k in range(n)]
        if not pairs and len(removed) == len(added):
            pairs = list(zip(range(len(removed)), range(len(added))))
        for a, b in pairs:
            before = list(ACCESS.finditer(removed[a]))
            after = list(ACCESS.finditer(added[b]))
            before_fields, after_fields = defaultdict(list), defaultdict(list)
            for match in before:
                before_fields[match['field']].append(match['member'])
            for match in after:
                after_fields[match['field']].append(match['member'])
            for field, old_members in before_fields.items():
                new_members = after_fields.get(field, ())
                # A removed access to the same field leaves its occurrence
                # mapping ambiguous. Other fields can still be checked.
                if len(old_members) != len(new_members):
                    continue
                for old, new in zip(old_members, new_members):
                    if old != new:
                        swaps.add((field, old, new))
        removed.clear()
        added.clear()

    for line in patch.splitlines():
        if line.startswith('@@'):
            finish()
        elif line.startswith('-') and not line.startswith('---'):
            removed.append(line[1:])
        elif line.startswith('+') and not line.startswith('+++'):
            added.append(line[1:])
    finish()
    return swaps


def stale_uses(text: str, swaps: set[tuple[str, str, str]]) -> list[tuple[int, str, str, str]]:
    stale = []
    for match in ACCESS.finditer(text):
        for field, old, new in swaps:
            if match['field'] == field and match['member'] == old:
                stale.append((text.count('\n', 0, match.start()) + 1, field, old, new))
    return stale


def unchanged_uses(base: str, current: str,
                   swaps: set[tuple[str, str, str]]) -> list[tuple[int, str, str, str]]:
    """Find member accesses left on identical lines after a two-way label swap."""
    old_lines, new_lines = base.splitlines(), current.splitlines()
    matcher = difflib.SequenceMatcher(None, old_lines, new_lines, autojunk=False)
    stale = []
    for _, start, count in matcher.get_matching_blocks():
        for index in range(start, start + count):
            for match in ACCESS.finditer(new_lines[index]):
                for field, old, new in swaps:
                    if match['field'] == field and match['member'] == old:
                        stale.append((index + 1, field, old, new))
    return stale


def declaration_swaps(base: str, current: str) -> set[tuple[str, str, str]]:
    """Type-preserving member-name swaps in simple inline union declarations."""
    def fields(text: str) -> dict[str, dict[str, str]]:
        result = {}
        for body, field in INLINE_UNION.findall(text):
            members = {}
            for part in body.split(';'):
                part = part.strip()
                match = re.fullmatch(r'(.*?)([A-Za-z_]\w*)', part)
                if match:
                    members[re.sub(r'\s+', '', match[1])] = match[2]
            if members:
                result[field] = members
        return result

    previous, updated = fields(base), fields(current)
    swaps = set()
    for field, members in previous.items():
        other = updated.get(field)
        if other and members.keys() == other.keys():
            swaps.update((field, old, other[typ]) for typ, old in members.items()
                         if old != other[typ])
    return swaps


def missing_declaration_edits(
    declarations: list[tuple[str, str, str, str]],
    files_data: dict[str, tuple[str, str, set[tuple[str, str, str]]]],
) -> list[str]:
    all_swaps = {(field[:-1].removeprefix('->').removeprefix('.'), old, new)
                 for _, (_, _, swaps) in files_data.items()
                 for field, old, new in swaps}
    missing = []
    for rel, field, old, new in declarations:
        if (field, old, new) in all_swaps:
            continue
        field_edited = any(name == field for name, _, _ in all_swaps)
        old_used = any(match['field'][len('->') if match['field'].startswith('->') else 1:-1] == field
                       and match['member'] == old
                       for source, _, _ in files_data.values() for match in ACCESS.finditer(source))
        if old_used or not field_edited:
            missing.append(f'{rel}: {field}.{old} declaration relabel to {new} has no use-site edit')
    return missing


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--base', default='HEAD', help='committed batch base')
    parser.add_argument('files', nargs='*', help='changed source files (default: Git diff)')
    args = parser.parse_args()
    root = Path(__file__).resolve().parents[2]
    if args.files:
        files = args.files
    else:
        files = subprocess.check_output(
            ['git', 'diff', '--name-only', args.base, '--', 'src', 'include'], cwd=root,
            text=True).splitlines()
    failures = []
    files_data = {}
    declarations = []
    for rel in files:
        path = root / rel
        if path.suffix not in {'.c', '.h'} or not path.is_file():
            continue
        try:
            base_text = subprocess.check_output(['git', 'show', f'{args.base}:{rel}'],
                                                cwd=root, text=True)
        except subprocess.CalledProcessError:
            base_text = ''
        current_text = path.read_text()
        patch = subprocess.check_output(
            ['git', 'diff', '--unified=0', args.base, '--', rel], cwd=root, text=True)
        swaps = swaps_from_diff(patch)
        files_data[rel] = (base_text, current_text, swaps)
        declarations += [(rel, field, old, new) for field, old, new
                         in declaration_swaps(base_text, current_text)]
    for rel, (base_text, current_text, swaps) in files_data.items():
        two_way = {swap for swap in swaps if (swap[0], swap[2], swap[1]) in swaps}
        stale = stale_uses(current_text, swaps - two_way)
        stale += unchanged_uses(base_text, current_text, two_way)
        for line, field, old, new in stale:
            failures.append(f'{rel}:{line}: {field}{old} remains after relabel to {field}{new}')
    failures.extend(missing_declaration_edits(declarations, files_data))
    for failure in failures:
        print(failure)
    return bool(failures)


if __name__ == '__main__':
    raise SystemExit(main())
