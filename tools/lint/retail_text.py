#!/usr/bin/env python3
"""Flag suspect retail text encodings without echoing their contents.

The required document check covers designated payload fields and marked
display quotations or byte runs in tracked files up to four MiB. Generic
JSON keys and ordinary Markdown quotes are outside that check. TSV files
need named payload columns. The optional document audit also inspects
generic payload keys like `text` and `bytes`, but arbitrary fields still
need review.
"""
from __future__ import annotations

import argparse
import csv
import hashlib
import io
import json
from pathlib import Path
import re
import subprocess

TOKEN = re.compile(r'//[^\n]*|/\*[\s\S]*?\*/|"(?:\\[\s\S]|[^"\\])*"|\'(?:\\[\s\S]|[^\'\\])*\'')
INCLUDE = re.compile(r'^\s*#\s*(?:include|include_next|line)\b')
C_INTEGER = (r'[us](?:8|16|32|64)|u?int(?:8|16|32|64)_t|'
             r'(?:unsigned\s+|signed\s+)?(?:char|short(?:\s+int)?|int|long(?:\s+int)?)')
ARRAY = re.compile(
    rf'\b(?P<type>{C_INTEGER}|(?:struct\s+)?[A-Za-z_]\w*)'
    r'\s+(?:(?:const|volatile)\s+)*(?P<name>\w+)\s*(?:\[[^\]\n]*\]\s*)+'
    r'(?:__attribute__\(\(aligned\(\d+\)\)\)\s*)?=\s*\{'
)
ARRAY_TOKEN = re.compile(r"'(?:\\[\s\S]|[^'\\])*'|[{},]")
INTEGER = re.compile(r'([+-]?(?:0[xX][a-fA-F0-9]+|0[0-7]+|[0-9]+))[uUlL]*\Z')
ESCAPE = re.compile(r'\\(?:x[0-9a-fA-F]+|[0-7]{1,3}|(?:\r?\n)|.)', re.S)
SIMPLE_ESCAPES = dict(zip("abfnrtv", b"\a\b\f\n\r\t\v"))
ASCII_RUN = re.compile(rb'[ -~]{4,}')
EXPLICIT_FIELDS = {'retail_text', 'encoded_text', 'message_text', 'retail_bytes', 'payload_bytes',
                   'encoded_bytes'}
PAYLOAD_FIELDS = EXPLICIT_FIELDS | {'text', 'bytes', 'payload'}
HEX_BYTES = re.compile(r'(?<![\w-])(?:(?:[a-fA-F0-9]{2}[ \t]+){3,}[a-fA-F0-9]{2}|[a-fA-F0-9]{8,})(?![\w-])')
TEXT_QUOTE = re.compile(r'\b(?:on[- ]screen text|displayed text|message reads|text reads|trace prints)\b'
                        r'[^\n"\x60]{0,22}(["\x60])([^"\x60\n]+)\1', re.I)


def decode_literal(token):
    body = token[1:-1]
    result = bytearray()
    end = 0
    for match in ESCAPE.finditer(body):
        result.extend(body[end:match.start()].encode('utf-8', errors='surrogateescape'))
        value = match.group()[1:]
        if value.startswith('x') and len(value) > 1:
            result.append(int(value[1:], 16) & 255)
        elif value[0] in '01234567':
            result.append(int(value, 8) & 255)
        elif value not in ('\n', '\r\n'):
            result.append(SIMPLE_ESCAPES.get(value, ord(value)) & 255)
        end = match.end()
    result.extend(body[end:].encode('utf-8', errors='surrogateescape'))
    return bytes(result)


def japanese(character):
    return ('\u3000' <= character <= '\u30ff' or '\u3400' <= character <= '\u9fff'
            or '\uff01' <= character <= '\uffee')


def looks_like_text(payload):
    if any(re.search(rb'[A-Za-z]', run[0]) for run in ASCII_RUN.finditer(payload)):
        return True
    for encoding in ('utf-8', 'shift_jis'):
        decoded = payload.decode(encoding, errors='replace')
        run = wide = letters = 0
        for character in decoded:
            is_wide = japanese(character)
            if ' ' <= character <= '~' or is_wide:
                run += 1
                wide += is_wide
                letters += character.isalpha()
                if run >= 4 and wide >= 2 and letters:
                    return True
            else:
                run = wide = letters = 0
    return False


def integer_width(ctype):
    if not re.fullmatch(C_INTEGER, ctype):
        return None
    return (1 if '8' in ctype or 'char' in ctype else
            2 if '16' in ctype or 'short' in ctype else
            8 if '64' in ctype else 4)


def array_elements(widths, values, align=False):
    elements, start = [], 0
    for delimiter in ARRAY_TOKEN.finditer(values):
        if delimiter.group() in ('{', '}', ','):
            elements.append(values[start:delimiter.start()])
            start = delimiter.end()
    elements.append(values[start:])
    numbers = []
    for value in elements:
        token = INTEGER.fullmatch(value.strip())
        if token:
            spelling = token[1]
            digits = spelling.lstrip('+-')
            base = 16 if digits.lower().startswith('0x') else 8 if digits.startswith('0') else 10
            number = int(spelling, base)
        elif value.strip().startswith("'"):
            data = decode_literal(value.strip())
            if len(data) != 1:
                return None
            number = data[0]
        elif value.strip():
            return None
        else:
            continue
        numbers.append(number)
    if len(numbers) % len(widths):
        return None
    return pack_numbers(numbers, widths, align)


def pack_numbers(numbers, widths, align=False):
    result = bytearray()
    for index, number in enumerate(numbers):
        slot = index % len(widths)
        width = widths[slot]
        if align:
            result.extend(b'\0' * (-len(result) % (max(widths) if slot == 0 else width)))
        result.extend((number % (1 << (width * 8))).to_bytes(width, 'little'))
    if align:
        result.extend(b'\0' * (-len(result) % max(widths)))
    return bytes(result)


def integer_types(source):
    aliases = {}
    for ctype, alias in re.findall(r'\btypedef\s+([^;{}]+?)\s+(\w+)\s*;', source):
        if width := integer_width(ctype) or aliases.get(ctype):
            aliases[alias] = width
    records = {}
    structs = r'\b(?:(typedef)\s+)?struct\s*(\w*)\s*\{([^{}]*)\}\s*(\w*)\s*;'
    for typedef, tag, body, name in re.findall(structs, source):
        widths = []
        for field in filter(str.strip, body.split(';')):
            match = re.fullmatch(r'\s*(.+?)\s+\w+(?:\[([1-9]\d{0,2})\])?\s*', field)
            if not match or not (width := integer_width(match[1]) or aliases.get(match[1])):
                break
            widths.extend([width] * int(match[2] or 1))
        else:
            if tag and widths:
                records['struct ' + tag] = widths
            if typedef and name and widths:
                records[name] = widths
    return aliases, records


def candidates(source):
    # Preserve coordinates, including escaped string newlines.
    masked = list(source)
    array_source = list(source)
    literals = []
    for token in TOKEN.finditer(source):
        start, end = token.span()
        if source[start] == '"' and not INCLUDE.match(source[source.rfind('\n', 0, start)+1:start]):
            literals.append(token)
        if token[0].startswith(('//', '/*')):
            yield from ((start + offset, kind, data) for offset, kind, data in quoted_text(token[0]))
        # Keep a separate marker for character/string initializers so they
        # cannot look like empty values in an integer-array initializer.
        marker = 'X' if source[start] in ('"', "'") else ' '
        replacement = [c if c == '\n' else marker for c in token.group()]
        masked[start:end] = replacement
        if source[start] != "'":
            array_source[start:end] = replacement
    neutral = ''.join(masked)
    index = 0
    while index < len(literals):
        first = literals[index]
        index += 1
        last = first
        payload = decode_literal(first.group())
        while index < len(literals) and not neutral[last.end():literals[index].start()].strip():
            last = literals[index]
            payload += decode_literal(last.group())
            index += 1
        if looks_like_text(payload) or any(
                part.isprintable() and len(part) >= 4 and any(c.isalpha() for c in part)
                for part in payload.decode('utf-8', errors='replace').split('\0')
                if '\ufffd' not in part):
            yield first.start(), 'literal', payload
    array_source = ''.join(array_source)
    aliases, records = integer_types(neutral)
    end = 0
    for match in ARRAY.finditer(array_source):
        if match.start() < end:
            continue
        width = integer_width(match['type']) or aliases.get(match['type'])
        record = records.get(match['type'])
        if not width and not record:
            continue
        depth = 1
        for brace in ARRAY_TOKEN.finditer(array_source, match.end()):
            if brace.group() not in ('{', '}'):
                continue
            depth += 1 if brace.group() == '{' else -1
            if depth == 0:
                end = brace.end()
                payload = array_elements([width] if width else record,
                                         array_source[match.end():brace.start()], align=not width)
                if payload is not None and looks_like_text(payload):
                    yield match.start(), 'integer array' if width else 'record array', payload
                break


def quoted_text(source):
    for match in TEXT_QUOTE.finditer(source):
        payload = decode_literal(match[1] + match[2] + match[1])
        if looks_like_text(payload):
            yield match.start(), 'quoted display text', payload


def encoded_field(value):
    if isinstance(value, str):
        if re.fullmatch(r'(?:[0-9a-fA-F]{2}[ \t]*)+', value):
            payload = bytes.fromhex(value)
            return payload if looks_like_text(payload) else None
        for match in HEX_BYTES.finditer(value):
            hex_run = ''.join(match[0].split())
            if len(hex_run) % 2 == 0:
                payload = bytes.fromhex(hex_run)
                if looks_like_text(payload):
                    return payload
        payload = decode_literal('"' + value + '"')
        if looks_like_text(payload):
            return payload
    elif isinstance(value, list) and value:
        if all(type(n) is int for n in value):
            for width in (1, 2, 4):
                if all(-(1 << (width * 8 - 1)) <= n < 1 << (width * 8) for n in value):
                    payload = pack_numbers(value, [width])
                    if looks_like_text(payload):
                        return payload
                    break
    return None


def json_fields(value, strict=False, text_table=False):
    if isinstance(value, dict):
        text_table = text_table or value.get('kind') in ('typed_string', 'message_bytes', 'text')
        fields = PAYLOAD_FIELDS if text_table or not strict else EXPLICIT_FIELDS
        for key, element in value.items():
            if key in fields and (payload := encoded_field(element)):
                yield key, payload
            yield from json_fields(element, strict, text_table)
    elif isinstance(value, list):
        for element in value:
            yield from json_fields(element, strict, text_table)


def document_candidates(path, source, strict=False):
    if path.suffix == '.md':
        yield from quoted_text(source)
        for match in HEX_BYTES.finditer(source):
            if strict:
                line_start = source.rfind('\n', 0, match.start()) + 1
                preceding = source[line_start:match.start()]
                if not re.search(r'\b(?:encoded|displayed|on[- ]screen)\s+(?:text|label|message)\b', preceding, re.I):
                    continue
            if ' ' in match[0] or '\t' in match[0]:
                payload = encoded_field(match[0])
                if payload:
                    yield match.start(), 'hex byte run', payload
    if path.suffix == '.tsv':
        reader = csv.DictReader(io.StringIO(source), delimiter='\t')
        fields = EXPLICIT_FIELDS if strict else PAYLOAD_FIELDS
        for row in reader:
            for key in sorted(fields.intersection(row)):
                field = row[key]
                if field is None:
                    continue
                try:
                    field = json.loads(field)
                except json.JSONDecodeError:
                    pass
                if payload := encoded_field(field):
                    yield reader.line_num, key, payload
    if path.suffix in ('.json', '.jsonl'):
        records = enumerate(source.splitlines(), 1) if path.suffix == '.jsonl' else [(1, source)]
        for line, record in records:
            if not record.strip() or record.startswith('#'):
                continue
            try:
                fields = json_fields(json.loads(record), strict)
            except json.JSONDecodeError:
                continue
            for key, payload in fields:
                yield line, key, payload


def documents(root, strict=False):
    """Scan public evidence and build data paths listed by Git."""
    tracked = subprocess.check_output(
        ['git', '-C', str(root), 'ls-files', '-z', '--', 'config', 'docs', 'ledger', 'link'],
        text=True).split('\0')
    for name in tracked:
        path = root / name
        if path.suffix not in ('.json', '.jsonl', '.tsv', '.md') or not path.is_file():
            continue
        if path.stat().st_size > 4 * 1024 * 1024:
            continue
        source = path.read_text(errors='surrogateescape')
        for position, kind, _ in document_candidates(path, source, strict):
            line = source.count('\n', 0, position) + 1 if path.suffix == '.md' else position
            yield name, line, kind


def check(root):
    allow_path = root / 'config/lint/retail_text.allow'
    allow = set()
    if allow_path.is_file():
        for line in allow_path.read_text().splitlines():
            if line.strip() and not line.startswith('#'):
                path, digest, reason = line.split('\t', 2)
                if not re.fullmatch(r'[0-9a-f]{64}', digest) or not reason.strip():
                    raise ValueError('invalid retail text allow-list entry')
                allow.add((path, digest))
    problems, seen = [], set()
    paths = sorted(path for name in ('src', 'include') for path in (root / name).rglob('*')
                   if path.suffix in ('.c', '.h') and path.is_file())
    for path in paths:
        rel = path.relative_to(root).as_posix()
        source = path.read_text(errors='surrogateescape')
        for offset, description, payload in candidates(source):
            digest = hashlib.sha256(payload).hexdigest()
            key = rel, digest
            if key in allow:
                seen.add(key)
            else:
                problems.append(f"{rel}:{source.count(chr(10), 0, offset)+1}: {description}")
    return problems + [f'{path}: unused text exception ({digest})' for path, digest in sorted(allow-seen)]


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    parser.add_argument('--documents', action='store_true', help='also audit historical evidence encodings')
    args = parser.parse_args()
    problems = check(args.root)
    problems.extend(f'{name}:{line}: {kind}' for name, line, kind in documents(args.root, strict=not args.documents))
    for problem in problems:
        print(problem)
    return bool(problems)


if __name__ == '__main__':
    raise SystemExit(main())
