#!/usr/bin/env python3
"""Flag evidence text that quotes values read from the disc, without echoing them.

Rows that a batch adds to config/names.tsv (evidence column) and ledger/names.jsonl (evidence field)
may say who reads a table, how it is indexed, its element size and count and what kind of values it
holds. They may not list the values: no byte or halfword lists, numeric table contents, coordinate
pairs, glyph or character codes, or quoted game words. Offsets, sizes, counts and addresses of
symbols are fine. Forms caught: runs of three or more numbers separated by space, comma, semicolon or slash,
byte/hex runs, coordinate pairs, brace lists, `bytes are|is|hold(s)|=` followed by a value, labelled values
(`x 5 y 6`), `all N bytes are <value>`, parenthesised or plain lists of two or more 0x8....... addresses after
`retail bytes` or `pointers`, glyph/entry values and quoted strings.  Exempt: offsets (+0x..), counts and sizes
(a number followed by bytes, entries, elements ...), addresses of symbols (0x8.......), D_/func_ names, container
offsets that locate bytes (TOWN 0xBBA8, offset 0x..), file paths, bank and image names, and index/flag constants
spelled as `kind 0x..` words.  Only rows absent from the base revision are checked; older rows are not.

    python3 tools/lint/evidence_values.py BASE [--root DIR]     # exit 1 on any finding
"""
from __future__ import annotations

import argparse
import json
from pathlib import Path
import re
import subprocess
import sys

NUM = r'(?:0[xX][0-9A-Fa-f]+|-?\d+|[0-9A-Fa-f]*\d[0-9A-Fa-f]*)'
ADDR = re.compile(r'(?:0[xX]8[0-9A-Fa-f]{7}|[+]?0[xX][0-9A-Fa-f]{5,}|\bD_[0-9A-F]{8}\b|\bfunc_[0-9A-F]{8}\b)')
RULES = [
    ('number run', re.compile(r'(?<![\w.])(?:' + NUM + r')(?:\s*[ ,;]\s*(?:' + NUM + r')){1,}(?![\w])')),
    ('coordinate pair', re.compile(r'\(\s*-?\d+\s*,\s*-?\d+\s*\)')),
    ('hex digits run', re.compile(r'\b[0-9A-Fa-f]{2,4}(?:\s+[0-9A-Fa-f]{2,4}){2,}\b')),
    ('value after bytes/word', re.compile(r'\b(?:retail|bank|engine|bound|image)\s+(?:\w+\s+){0,2}(?:bytes|words?|halfwords?)\s+(?:are\s+|=\s*)?(?:\(\w+ )?(?:0[xX][0-9A-Fa-f]+|-?\d+)\b(?!\s*(?:\w+-byte\s+)?(?:bytes?|words?|entries|-byte|elements?|halfwords?)\b)', re.I)),
    ('quoted string', re.compile(r'"[^"]{2,}"|(?<![A-Za-z])\'[^\']{2,}\'')),
    ('rgb/colour value', re.compile(r'\b(?:rgb|word|bytes)\s+0[xX][0-9A-Fa-f]{4,}', re.I)),
    ('glyph or entry value', re.compile(r'\b(?:glyph|entries|entry|sprite entries)\s+0[xX][0-9A-Fa-f]+(?:-0[xX][0-9A-Fa-f]+)?')),
    ('bytes value', re.compile(r'\bbytes?\s+0[xX][0-9A-Fa-f]{3,}')),
    ('brace record', re.compile(r'\{\d+,\s*(?:ptr|\.\.\.)')),
    ('repeat count', re.compile(r'\(\d+ x\d+\)')),
    ('flags word value', re.compile(r'\(0[xX][0-9A-Fa-f]{4} (?:flags )?word')),
    ('and value pair', re.compile(r'\(0[xX][0-9A-Fa-f]+ and \d+\)')),
    ('slash run', re.compile(r'(?<![\w.])' + NUM + r'(?:\s*/\s*' + NUM + r'){2,}(?![\w])')),
    ('value after bytes are', re.compile(r'\bbytes?\b[^;.()]{0,20}?\b(?:are|is|holds?|=)\s+(?:the\s+|one\s+)?(?:0[xX][0-9A-Fa-f]+|\d+|[0-9a-f]{2,8})\b(?!\s*(?:\w+-byte\s+)?(?:bytes?|words?|entries|elements?|halfwords?|pointers?|frames?|types|directions|of|and|to|in|per)\b)', re.I)),
    ('labelled values', re.compile(r'\b(?:are|is)\s+[a-z]\s+(?:0[xX][0-9A-Fa-f]+|\d+)\s+[a-z]\s+(?:0[xX][0-9A-Fa-f]+|\d+)')),
    ('all N bytes are value', re.compile(r'\ball\s+\w+\s+bytes\s+(?:are|is)\s+(?:0[xX])?[0-9A-Fa-f]{1,8}\b')),
    ('signed list', re.compile(r'-\d+\s*,\s*-?\d+')),
]

def strip_addr(t):
    t = re.sub(r'(?:0[xX][0-9A-Fa-f]+)\s*\.\.\s*(?:0[xX][0-9A-Fa-f]+)', 'ADDR', t)
    t = ADDR.sub('ADDR', t)
    # offsets such as +0x3716, file offset 0xF77B4, TOWN 0x795384
    t = re.sub(r'(?:offset|at|TOWN|DUNGEON|MAIN|image|bank|\+)\s*\(?0[xX][0-9A-Fa-f]+', 'ADDR', t)
    t = re.sub(r'[+]0[xX][0-9A-Fa-f]+', 'ADDR', t)
    t = re.sub(r'\bat\s+\+?0[xX][0-9A-Fa-f]+', 'at ADDR', t)
    t = re.sub(r'\b(?:status_flags|flags\w*|bit|state|phase|action|kind|case|index|slot|style|variant|element|row|page)\s+(?:bit\s+)?(?:0[xX][0-9A-Fa-f]+|\d+)\b', 'IDX', t)
    t = re.sub(r'\b(?:src|include|config|ledger)/[\w./-]+', 'PATH', t)
    t = re.sub(r'\b(?:image_|ll34_|bank_|ovl_|g0|g)[0-9a-f_]+\b', 'NAME', t)
    t = re.sub(r'\b[0-9a-f]{6,7}\b', 'ADDR', t)
    return t

POINTER_LIST = re.compile(r'(?:retail bytes|pointers)[^;]*?(?:\([^)]*0[xX]8[0-9A-Fa-f]{7}[^)]*0[xX]8[0-9A-Fa-f]{7}[^)]*\)|0[xX]8[0-9A-Fa-f]{7}[ ,]+0[xX]8[0-9A-Fa-f]{7})', re.I)


def findings(text):
    t = strip_addr(text)
    out = []
    for m in POINTER_LIST.finditer(text):
        out.append('pointer address list: ' + m.group(0)[:40])
    for name, rx in RULES:
        for m in rx.finditer(t):
            out.append(f'{name}: {m.group(0)[:60]}')
    return out


def _show(root, base, path):
    done = subprocess.run(['git', '-C', str(root), 'show', f'{base}:{path}'], capture_output=True, text=True)
    return done.stdout if done.returncode == 0 else ''


def added_evidence(root, base):
    """Yield (path, line number, evidence text) for the rows of the two files that BASE does not have."""
    root = Path(root)
    old_tsv = set(_show(root, base, 'config/names.tsv').splitlines())
    old_jsonl = set(_show(root, base, 'ledger/names.jsonl').splitlines())
    tsv = root / 'config/names.tsv'
    if tsv.is_file():
        for number, line in enumerate(tsv.read_text(errors='surrogateescape').splitlines(), 1):
            if line in old_tsv or line.startswith('#'):
                continue
            fields = line.split('\t')
            if len(fields) > 3:
                yield 'config/names.tsv', number, fields[3]
    jsonl = root / 'ledger/names.jsonl'
    if jsonl.is_file():
        for number, line in enumerate(jsonl.read_text(errors='surrogateescape').splitlines(), 1):
            if not line.strip() or line in old_jsonl:
                continue
            try:
                record = json.loads(line)
            except json.JSONDecodeError:
                continue
            if isinstance(record, dict):
                yield 'ledger/names.jsonl', number, ' '.join(str(record.get(key, '')) for key in ('evidence', 'note', 'notes'))


def check(root, base):
    """['path:line: kind', ...] for added evidence text that quotes values (the text itself is not echoed)."""
    problems = []
    for path, number, text in added_evidence(root, base):
        kinds = sorted({finding.split(':')[0] for finding in findings(text)})
        if kinds:
            problems.append(f"{path}:{number}: evidence quotes values ({', '.join(kinds)})")
    return problems


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('base')
    parser.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    args = parser.parse_args(argv)
    problems = check(args.root, args.base)
    for problem in problems:
        print(problem)
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
