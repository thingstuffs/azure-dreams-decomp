"""Text generation: interface headers and .c edits (remove declaration items, add #include lines)."""
from __future__ import annotations

import re

try:
    from . import plan as P
except ImportError:
    import plan as P

BANNER = 'Prototypes of the functions defined in {src}/ (one true prototype each; maintained by tools/headers).'


def header_text(plan, h):
    rows = plan.headers[h]
    data_rows = sorted((r for r in rows if getattr(r, 'kind', '') == 'data'), key=lambda r: r.name)
    rows = [r for r in rows if getattr(r, 'kind', '') != 'data']
    if h.startswith('include/sdk/'):
        rows = sorted(rows, key=lambda r: r.name)
    th, tags = plan.header_types[h]
    guard = P.guard_for(h)
    src = 'src/' + h[len('include/'):-2]
    if h.startswith('include/sdk/'):
        lib = h.rsplit('/', 1)[1][:-2]
        out = [f'/* Stand-in declarations for the Psy-Q SDK library {lib}. The SDK is copyrighted and not distributed here; builders who own it can replace this file with the SDK header. */',
               '/* Generated call contracts; maintained by tools/headers. */',
               f'#ifndef {guard}', f'#define {guard}', '', '#include "common.h"']
    else:
        banner = BANNER.format(src=src) if not h.endswith('/data.h') else \
            'Imported data declarations for this image; maintained by tools/headers.'
        out = [f'#ifndef {guard}', f'#define {guard}', '/* ' + banner + ' */', '', '#include "common.h"']
    for t in th:
        out.append(f'#include "{t[len("include/"):]}"')
    out.append('')
    if tags:
        for t in tags:
            out.append(f'{t};')
        out.append('')
    cur = None
    for r in rows:
        f = r.definition.path.rsplit('/', 1)[1]
        if f != cur and not h.startswith('include/sdk/'):
            if cur is not None:
                out.append('')
            out.append(f'/* {f} */')
            cur = f
        out.append((r.proto or r.definition.proto) + ';')
    if data_rows:
        out.extend(['', '/* Data declarations. */'])
        out.extend(r.proto + ';' for r in data_rows)
    out.append('')
    out.append(f'#endif')
    return '\n'.join(out) + '\n'


def _line_span(text, start, end):
    """Extend [start,end) to whole lines when the item stands alone on its lines (trailing
    '/* extern */' marker included)."""
    ls = text.rfind('\n', 0, start) + 1
    le = text.find('\n', end)
    le = len(text) if le < 0 else le + 1
    before = text[ls:start]
    after = text[end:le].rstrip('\n')
    if before.strip() == '' and (after.strip() == '' or P.TRIVIAL_TRAILING.match(after)):
        return ls, le
    return start, end


def tu_edit(tp, header_of):
    """Picklable edit description of a TuPlan: {'add': [headers], 'remove': [(header, start, end)]}."""
    return {'add': sorted(tp.add), 'remove': sorted((header_of(r), r.site.start, r.site.end) for r in tp.remove),
            'drop': sorted(getattr(tp, 'stale', []))}


def edit_tu(text, edit, only=None):
    """New text of a TU for edit (see tu_edit) restricted to headers `only` (default all).  Pure."""
    from cscan import scan as _scan
    add = [h for h in edit['add'] if only is None or h in only]
    drop = edit.get('drop', [])
    if not add and not drop:
        return text
    sc = _scan(text)
    drop_spans = [(d.start, d.end) for d in sc.directives if d.kind == 'include'
                  and d.arg.strip() in {f'"{P.include_token(h)}"' for h in drop}]
    spans = sorted({_line_span(text, s, e) for h, s, e in edit['remove'] if h in add} | set(drop_spans))
    merged = []
    for s, e in spans:
        if merged and s <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(e, merged[-1][1]))
        else:
            merged.append((s, e))
    incs = [d for d in sc.directives if d.kind == 'include' and d.depth == 0
            and (d.start, d.end) not in set(drop_spans)]
    existing = {d.arg.strip() for d in incs}
    new_lines = [f'#include "{P.include_token(h)}"' for h in sorted(add)
                 if f'"{P.include_token(h)}"' not in existing]
    if incs:
        ins = incs[-1].end
        if not text[:ins].endswith('\n'):
            new_lines = [''] + new_lines
    else:
        ins = 0
    ins_text = '\n'.join(new_lines) + ('\n' if new_lines else '')
    if not incs and new_lines:
        ins_text += '\n'
    pieces = []
    pos = 0
    events = [(s, e, SENTINEL) for s, e in merged] + [(ins, ins, ins_text)]
    events.sort(key=lambda x: (x[0], x[1]))
    for s, e, rep in events:
        if s < pos:
            raise ValueError('overlapping edit')
        pieces.append(text[pos:s])
        pieces.append(rep)
        pos = e
    pieces.append(text[pos:])
    return _collapse(''.join(pieces))


SENTINEL = '\x00'


def _collapse(text):
    """Blank-line runs that touch a removal point shrink to one blank line; nothing else moves."""
    def fix(m):
        k = m.group(0).count('\n')
        return '\n' * min(k, 2)
    return re.sub(r'\n*(?:\x00\n*)+', fix, text)
