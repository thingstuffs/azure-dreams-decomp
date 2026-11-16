#!/usr/bin/env python3
"""Clone transplant: one source text for every copy of one retail function body.

The same retail function is often kept as several separately edited C definitions (a monster module linked at
several load addresses, an effect helper placed in several images).  Their bytes are one body; their texts drift
apart, so a type or cast fixed in one copy stays debt in the others.  This tool rewrites each copy from the best
copy's text.

    clone_transplant.py confirm --members TSV --out DIR [--family N ...] [--workers 2]
    clone_transplant.py apply   --out DIR [--family ID ...] [--port PORT] [--skip-list F] [--dry-run]
                                [--ledger ledger/clone_sources.jsonl]

**confirm** takes candidate families (a TSV with columns family, address_symbol and file; one row per copy, the
fingerprint census's format) and checks each copy against the others in *masked retail bytes*: every copy's
object is compiled at its production recipe (the build's gcc, ccproc and maspsx, as tu_identity captures it) and
its `.text.func_<addr>` section read with tools/fidelity/objread.py; two copies are one body when their sizes are
equal, their relocation layouts (offset and type of every relocation) are equal, every word is equal outside the
relocated fields (HI16/LO16/GPREL16 immediates, the 26-bit J/JAL field, R_MIPS_32 words), and the retail words of
both rows (tools/lint/placed_copies.py's reader) are equal under the same mask.  A candidate family splits into
the confirmed sub-families (`<family>.<k>`); copies that match no other copy are dropped.  Zipping the two
relocation lists gives the *symbol map* donor -> recipient: each pair of named targets (an `.text.func_X` section
counts as the symbol func_X), refused unless the map is one-to-one, the addends agree, and section-relative data
targets are only `.rodata` (compiler tables and literals; a static data object cannot be renamed).

**apply** picks per family the donor: the copy with the fewest pointer casts plus weak parameters (void *, byte
pointer or generated view; tools/lint/debt_check.py), ties to the copy whose name is the canonical row of a
config/names.tsv placed-copy family, then the lowest address.  Each other copy (the recipient) has its definition
rewritten from the donor's text:

  * object symbols are spelled back as C identifiers through config/names.tsv (ccproc's table); a donor
    identifier whose symbol maps to another recipient symbol takes the recipient's spelling (the spelling the
    recipient file already uses, else the donor's when the symbol is the same, else the name table's one name
    for it, else the address symbol), whole identifiers only and never a member name after `.` or `->`;
  * the donor's file-scope declarations that the new definition needs (typedefs, tag definitions, extern
    declarations and prototypes, transitively) are carried over, mapped, before the definition; one the recipient
    already declares the same way is kept; one it declares differently is replaced when nothing else in the
    recipient uses it, else the copy is refused (`declaration_conflict`); a carried static or global storage
    definition refuses (`storage_reference`);
  * recipient declarations left without a user (they served only the old definition) are removed;
  * a compile failure is retried once with the donor's missing #include lines added after the recipient's last;
  * a rewrite that spells a named member of the copy (`entity->pending_turn_updates`, `g_game_work.draw_buffer`)
    fewer times, with a generated member (`unk_9B`), a raw offset or a pointer cast in its place, is refused
    (`loses_named_member`), as is one that declares a parameter the copy types as a record with a generated or
    address-named layout, a file-local view, a byte pointer or void * (`weakens_parameter`): fewer casts are
    not a better text when the donor reads the record through a worse view.

Each recipient file is then proven: every physical TU that compiles it must stay identical (raw object,
canonical assembly, canonical object; layout_compile_identity.capture_one, as local_type_trial proves), no debt
class (tools/lint/debt_check.py) may rise in the file, and with --port no GCC warning group may rise
(tools/lint/lint_closure.py).  A refused copy keeps its text; every file is restored on --dry-run, an error or
SIGTERM.  Kept families are written to the --ledger (ledger/clone_sources.jsonl): per family the donor and every
copy's address, file, function name and symbol map, which tools/lint/clone_sources.py checks for drift.

Outputs under --out: objects/ (compiled objects, keyed by source sha), families.jsonl (confirm), receipt.jsonl
(apply: one row per recipient with verdict, casts before/after, weak parameters before/after).
"""
from __future__ import annotations

import argparse
import collections
from concurrent.futures import ProcessPoolExecutor
import csv
import hashlib
import json
import os
from pathlib import Path
import re
import signal
import subprocess
import sys
import tempfile

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(HERE), str(TOOLS), str(TOOLS / 'lint'), str(TOOLS / 'build'), str(TOOLS / 'readability'),
                str(TOOLS / 'fidelity')]

MASKS = {'HI16': 0xFFFF, 'LO16': 0xFFFF, 'GPREL16': 0xFFFF, '26': 0x03FFFFFF, '32': 0xFFFFFFFF}
DATA_SECTIONS = ('.data', '.bss', '.sdata', '.sbss')
SECTION = re.compile(r'^\.text\.(func_[0-9A-Fa-f]{8})$')
IDENT_RE = re.compile(r'[A-Za-z_]\w*')
KEYWORDS = {'auto', 'break', 'case', 'char', 'const', 'continue', 'default', 'do', 'double', 'else', 'enum',
            'extern', 'float', 'for', 'goto', 'if', 'inline', 'int', 'long', 'register', 'return', 'short',
            'signed', 'sizeof', 'static', 'struct', 'switch', 'typedef', 'union', 'unsigned', 'void',
            'volatile', 'while', '__attribute__', 'asm', '__asm__'}


# ------------------------------------------------------------------------------------------------ objects

def compile_object(root, rel, recipe):
    """Raw object bytes of the physical TU `rel` at its primary production compile (capture_one's path)."""
    import layout_compile_identity as L
    from layout_identity import reassemble
    root = Path(root).resolve()
    source = root / rel
    (root / 'build_ovl').mkdir(exist_ok=True)
    with tempfile.TemporaryDirectory(prefix='clone-obj-', dir=root / 'build_ovl') as td:
        work = Path(td)
        if recipe['container'] == 'slus':
            import verify
            from source_layout import registry
            row = registry(root)[recipe['row_id']]
            row = dict(row, cell=recipe['cell'], flags=' '.join(recipe['flags']),
                       row_asflags=' '.join(recipe['asflags']))
            with L.compilation_input(root, rel, recipe, work / 'context') as cfile:
                out, error = verify._compile_slus_source(row, cfile, work / 'raw', root / 'include', root)
            if error:
                raise ValueError(rel + ': ' + error)
            return out.read_bytes()
        c = L.production_compiles(root, rel, recipe)[0]
        cc = root / 'toolchain/compilers' / ('gcc-' + c['cell'])
        flags = c['flags'] if '-O2' in c['flags'] else ['-O2', *c['flags']]
        asm = work / 'source.s'
        L.command([cc / 'gcc', '-B' + str(cc) + '/', '-S', *flags, '-I' + str(root / 'include'), '-w', source,
                   '-o', asm], cwd=root)
        stream = L.command([sys.executable, root / 'tools/build/ccproc.py', '--names-tsv',
                            root / 'config/names.tsv'], cwd=root, data=asm.read_bytes())
        (work / 'raw').mkdir()
        reassemble(root, stream, work / 'raw', recipe['container'], c['asflags'], c['evidence'])
        return (work / 'raw' / 'canonical.o').read_bytes()


def function_view(data, func):
    """(words, relocations) of the `.text.<func>` section: relocations are (offset, type, target, addend)."""
    import objread
    obj = objread.read_elf(data)
    name = '.text.' + func
    if name not in obj.sections:
        raise KeyError(func)
    body = obj.sections[name]
    words = [int.from_bytes(body[i:i + 4], 'little') for i in range(0, len(body) - len(body) % 4, 4)]
    relocs = sorted((off, rtype, target, addend) for sec, off, rtype, target, addend in obj.relocs if sec == name)
    return words, relocs


def target_symbol(target, addend):
    """('sym', name) for a named target or a function section; ('sec', name, addend) otherwise."""
    kind, name = target
    if kind == 'sym':
        return ('sym', name)
    m = SECTION.match(name or '')
    if m and not addend:
        return ('sym', m[1])
    return ('sec', name)


def masked_compare(a, b):
    """Problems between two function views (empty when they are one body)."""
    (wa, ra), (wb, rb) = a, b
    if len(wa) != len(wb):
        return ['size %d != %d' % (4 * len(wa), 4 * len(wb))]
    if [(o, t) for o, t, _, _ in ra] != [(o, t) for o, t, _, _ in rb]:
        return ['relocation layout differs']
    mask = collections.defaultdict(int)
    for o, t, _, _ in ra:
        mask[o // 4] |= MASKS.get(t, 0xFFFFFFFF)
    problems = []
    for k, (x, y) in enumerate(zip(wa, wb)):
        m = ~mask[k] & 0xFFFFFFFF
        if x & m != y & m:
            problems.append('word %d: %08x != %08x' % (k, x, y))
    return problems


def symbol_map(donor, recipient, donor_func, recipient_func):
    """{donor symbol: recipient symbol} from the zipped relocations; raises ValueError when it is not one-to-one."""
    (_, ra), (_, rb) = donor, recipient
    forward, backward = {donor_func: recipient_func}, {recipient_func: donor_func}
    for (o, t, ta, aa), (_, _, tb, ab) in zip(ra, rb):
        sa, sb = target_symbol(ta, aa), target_symbol(tb, ab)
        if sa[0] != sb[0]:
            raise ValueError('relocation %#x: %s against %s' % (o, sa, sb))
        if sa[0] == 'sec':
            if sa[1] in DATA_SECTIONS or sb[1] in DATA_SECTIONS:
                raise ValueError('relocation %#x: static data %s/%s' % (o, sa[1], sb[1]))
            if sa[1] != sb[1] and not (SECTION.match(sa[1] or '') and SECTION.match(sb[1] or '')):
                raise ValueError('relocation %#x: section %s against %s' % (o, sa[1], sb[1]))
            continue
        if aa != ab and t != '26':
            raise ValueError('relocation %#x: %s%+d against %s%+d' % (o, sa[1], aa, sb[1], ab))
        x, y = sa[1], sb[1]
        if forward.setdefault(x, y) != y or backward.setdefault(y, x) != x:
            raise ValueError('symbol map not one-to-one at %s -> %s' % (x, y))
    return forward


# ------------------------------------------------------------------------------------------------ C text

def lex(text):
    import score
    return score.lex(text)


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m[0]), text, flags=re.S)
    return re.sub(r'//[^\n]*', '', text)


class Unit:
    """Top-level items of one C file: function definitions and declarations, with character spans."""

    def __init__(self, text):
        import score
        self.text = text
        self.tokens = score.lex(text)
        self.pairs, _ = score.pairs_of(self.tokens)
        self.defs = {}
        spans = []
        for start, name, body, end, style in score.definitions(self.tokens, self.pairs):
            fn = self.tokens[name].value
            self.defs.setdefault(fn, (start, end))
            spans.append((start, end, fn))
        self.items = []  # dicts: kind, start/end char positions, names, refs
        by_start = {s: (e, fn) for s, e, fn in spans}
        i, n = 0, len(self.tokens)
        while i < n:
            if i in by_start:
                end, fn = by_start[i]
                self.items.append(self._item('definition', i, end, {fn}))
                i = end + 1
                continue
            j, depth = i, 0
            while j < n:
                v = self.tokens[j].value
                if v in '([{':
                    j = self.pairs.get(j, j)
                elif v == ';':
                    break
                j += 1
            self.items.append(self._classify(i, min(j, n - 1)))
            i = j + 1

    def _item(self, kind, a, b, names):
        start, end = self.tokens[a].pos, self.tokens[b].pos + len(self.tokens[b].value)
        refs = {t.value for t in self.tokens[a:b + 1] if t.kind == 'id'}
        return dict(kind=kind, a=a, b=b, start=start, end=end, names=set(names), refs=refs - set(names))

    def _classify(self, a, b):
        vals = [t.value for t in self.tokens[a:b + 1]]
        names = set()
        if 'typedef' in vals or 'extern' in vals or self._prototype(a, b):
            kind = 'typedef' if 'typedef' in vals else 'declaration'
        elif vals and vals[0] in ('struct', 'union', 'enum') and (self._tag_only(a, b) or len(vals) == 3):
            kind = 'tag'
        else:
            kind = 'storage'
        if kind == 'tag':
            # `struct X;` and `struct X { ... };` declare only the tag (and enum constants, below)
            if len(vals) == 3:
                names.add('tag:' + vals[1])
        else:
            for d0, d1 in self._declarators(a, b):
                name = self._declared(d0, d1)
                if name:
                    names.add(name)
        # tag names and enum constants
        for k in range(a, b):
            if self.tokens[k].value in ('struct', 'union', 'enum') and self.tokens[k + 1].kind == 'id' and \
                    k + 2 <= b and self.tokens[k + 2].value == '{':
                names.add('tag:' + self.tokens[k + 1].value)
            if self.tokens[k].value == 'enum':
                brace = k + 1 if self.tokens[k + 1].value == '{' else k + 2
                if brace <= b and self.tokens[brace].value == '{':
                    close = self.pairs.get(brace, brace)
                    m = brace + 1
                    while m < close:
                        if self.tokens[m].kind == 'id':
                            names.add(self.tokens[m].value)
                        while m < close and self.tokens[m].value != ',':
                            m = self.pairs.get(m, m) + 1 if self.tokens[m].value in '([' else m + 1
                        m += 1
        item = self._item(kind, a, b, names)
        item['refs'] |= {'tag:' + self.tokens[k + 1].value for k in range(a, b)
                         if self.tokens[k].value in ('struct', 'union', 'enum') and self.tokens[k + 1].kind == 'id'}
        item['refs'] -= names
        return item

    def _prototype(self, a, b):
        for k in range(a, b):
            if self.tokens[k].kind == 'id' and self.tokens[k + 1].value == '(' and \
                    self.tokens[k].value not in KEYWORDS:
                close = self.pairs.get(k + 1)
                return close is not None and close + 1 == b
        return False

    def _tag_only(self, a, b):
        k = a + 1
        if k <= b and self.tokens[k].kind == 'id':
            k += 1
        return k <= b and self.tokens[k].value == '{' and self.pairs.get(k) == b - 1

    def _declarators(self, a, b):
        """Spans of the comma-separated declarators (the first includes the specifiers)."""
        out, start, k = [], a, a
        while k < b:
            v = self.tokens[k].value
            if v in '([{':
                k = self.pairs.get(k, k) + 1
                continue
            if v == ',':
                out.append((start, k - 1))
                start = k + 1
            if v == '=':
                # skip the initializer up to the next comma at depth 0
                out.append((start, k - 1))
                k += 1
                while k < b and self.tokens[k].value != ',':
                    k = self.pairs.get(k, k) + 1 if self.tokens[k].value in '([{' else k + 1
                start = k + 1
                k += 1
                continue
            k += 1
        if start < b:
            out.append((start, b - 1))
        seen, uniq = set(), []
        for d in out:
            if d not in seen:
                seen.add(d)
                uniq.append(d)
        return uniq

    def _declared(self, a, b):
        toks = self.tokens
        k = a
        while k <= b:
            v = toks[k].value
            if v == '{':
                k = self.pairs.get(k, k) + 1
                continue
            if v == '(' and k + 1 <= b and toks[k + 1].value == '*':
                m = k + 2
                while m <= b and toks[m].value in ('const', 'volatile', '*'):
                    m += 1
                if m <= b and toks[m].kind == 'id':
                    return toks[m].value
            k += 1
        last = None
        k = a
        while k <= b:
            v = toks[k].value
            if v in ('[', '(', '='):
                break
            if v == '{':
                k = self.pairs.get(k, k) + 1
                continue
            if toks[k].kind == 'id' and v not in KEYWORDS and v != '__attribute__':
                last = v
            k += 1
        return last

    def definition_span(self, name):
        start, end = self.defs[name]
        return self.tokens[start].pos, self.tokens[end].pos + 1

    def users(self, name, exclude=()):
        """Occurrences of identifier `name` (not as a member) outside the char spans in `exclude`."""
        count = 0
        if name.startswith('tag:'):
            tag = name[4:]
            for k, t in enumerate(self.tokens):
                if t.value == tag and k and self.tokens[k - 1].value in ('struct', 'union', 'enum') and \
                        not any(s <= t.pos < e for s, e in exclude):
                    count += 1
            return count
        for k, t in enumerate(self.tokens):
            if t.kind == 'id' and t.value == name and not (k and self.tokens[k - 1].value in ('.', '->')) \
                    and not any(s <= t.pos < e for s, e in exclude):
                count += 1
        for m in re.finditer(r'^[ \t]*#(?:[^\n\\]|\\[^\n]|\\\n)*', self.text, re.M):
            if re.search(r'\b' + re.escape(name) + r'\b', m[0]) and not any(s <= m.start() < e for s, e in exclude):
                count += 1
        return count


def identifiers(text):
    """Identifier tokens (code only, not after `.`/`->`)."""
    toks = lex(text)
    return {t.value for k, t in enumerate(toks)
            if t.kind == 'id' and not (k and toks[k - 1].value in ('.', '->'))}


def rename(text, mapping):
    """Replace whole identifiers in code and comments; never a member name after `.` or `->`."""
    if not mapping:
        return text
    pattern = re.compile(r'(?<![\w.])(?<!->)(' + '|'.join(sorted(map(re.escape, mapping), key=len, reverse=True))
                         + r')(?!\w)')
    return pattern.sub(lambda m: mapping[m[1]], text)


def normalise(text):
    """Comment-free, whitespace-collapsed C text (the drift check's equality)."""
    return ' '.join(t.value for t in lex(text))


def weak_params(text, name, rel='x.c'):
    """Parameters of `name`'s definition declared void *, a byte pointer, a generated view or a file-local
    struct typedef (tools/lint/readcounts.py's weak parameter census)."""
    import readcounts as RC
    _, rows, _ = RC.weak_parameters({rel: RC.file_facts(text, True)})
    return sum(1 for r in rows if r[2] == name)


def function_casts(rel, text, name):
    import debt_check as D
    res = D.analyze(rel, text)
    return sum(v['counts'].get('pointer_casts', 0) for k, v in res['scopes'].items() if v['symbol'] == name)


def file_debt(rel, text):
    import debt_check as D
    res = D.analyze(rel, text)
    total = collections.Counter()
    for v in res['scopes'].values():
        total.update(v['counts'])
    return total


# ------------------------------------------------------------------------------------------------ rewrite

class Refused(Exception):
    pass


def names_table(root):
    import name_inputs
    return name_inputs.table(Path(root) / 'config/names.tsv')


def reverse_names(table):
    out = collections.defaultdict(set)
    for new, old in table.items():
        out[old].add(new)
    return out


def spell(symbol, recipient_text, old_def, donor_spelling, donor_symbol, table, reverse):
    """The C identifier the recipient file uses for object symbol `symbol`."""
    def canon(x):
        return table.get(x, x)
    in_def = sorted(i for i in identifiers(old_def) if canon(i) == symbol)
    if len(in_def) == 1:
        return in_def[0]
    in_file = sorted(i for i in identifiers(recipient_text) if canon(i) == symbol)
    if len(in_file) == 1:
        return in_file[0]
    if in_def or in_file:
        named = [i for i in (in_def or in_file) if not i.startswith('func_')]
        return (named or in_def or in_file)[0]
    if donor_symbol == symbol:
        return donor_spelling
    names = sorted(reverse.get(symbol, ()))
    if len(names) == 1:
        return names[0]
    return symbol


INCLUDE_NAME = re.compile(r'^[ \t]*#[ \t]*include[ \t]+"([^"]+)"', re.M)


def header_text(include_dir, text, seen=None):
    """Concatenated text of every quoted header `text` includes, transitively (resolved under include/)."""
    include_dir = Path(include_dir)
    seen = set() if seen is None else seen
    out = []
    for name in INCLUDE_NAME.findall(text):
        path = include_dir / name
        if name in seen or not path.is_file():
            continue
        seen.add(name)
        body = path.read_text(errors='replace')
        out.append(body)
        out.append(header_text(include_dir, body, seen))
    return '\n'.join(out)


def declared_in(headers, name):
    """True when an identifier is declared (as data, a function or a type) in the header text."""
    return bool(re.search(r'\b' + re.escape(name) + r'\b', headers))


MODULE_FILE = re.compile(r'(?:^|/)ovl_([0-9a-f]{6})\.c$')


def module_tag(path):
    """`CB9000` for src/dungeon/modules/ovl_cb9000.c: the tag of the module's generated view types
    (CL_CB9000_<addr>_...) and their members, which are one layout per module copy."""
    m = MODULE_FILE.search(path or '')
    return m[1].upper() if m else None


def retag(text, donor_tag, recipient_tag):
    """Module view type and member spellings of the donor module respelled with the recipient module's tag."""
    if not donor_tag or not recipient_tag or donor_tag == recipient_tag:
        return text
    return re.sub(r'\bCL_' + donor_tag + r'_', 'CL_' + recipient_tag + '_', text)


def transplant(donor_text, donor_name, recipient_text, recipient_name, symmap, table, reverse=None,
               add_includes=False, include_dir=None, tags=(None, None)):
    """New recipient text with `recipient_name`'s definition rewritten from the donor's.  Raises Refused."""
    reverse = reverse if reverse is not None else reverse_names(table)
    donor_text = retag(donor_text, *tags)

    def canon(x):
        return table.get(x, x)
    donor, recipient = Unit(donor_text), Unit(recipient_text)
    if donor_name not in donor.defs:
        raise Refused('donor_definition_missing')
    if recipient_name not in recipient.defs:
        raise Refused('recipient_definition_missing')
    ds, de = donor.definition_span(donor_name)
    rs, re_ = recipient.definition_span(recipient_name)
    donor_def, old_def = donor_text[ds:de], recipient_text[rs:re_]
    # identifier map (donor spelling -> recipient spelling)
    donor_ids = identifiers(donor_text)
    mapping = {donor_name: recipient_name}
    for ident in sorted(donor_ids):
        sym = canon(ident)
        if ident == donor_name or sym not in symmap:
            continue
        target = symmap[sym]
        new = spell(target, recipient_text, old_def, ident, sym, table, reverse)
        if new != ident:
            mapping[ident] = new
    if len(set(mapping.values())) != len(mapping):
        raise Refused('spelling_map_not_one_to_one')
    new_def = rename(donor_def, mapping)
    # file-scope declarations the new definition needs (transitively), from the donor
    donor_items = [it for it in donor.items if it['kind'] != 'definition']
    need = identifiers(new_def) | {'tag:' + t for t in re.findall(r'\b(?:struct|union|enum)\s+(\w+)', new_def)}
    carried, changed = [], True
    while changed:
        changed = False
        for it in donor_items:
            if it in carried:
                continue
            mapped_names = {mapping.get(n, n) if not n.startswith('tag:') else n for n in it['names']}
            if mapped_names & need:
                carried.append(it)
                mapped_refs = {mapping.get(r, r) if not r.startswith('tag:') else r for r in it['refs']}
                need |= mapped_refs
                changed = True
    carried.sort(key=lambda it: it['start'])
    rec_items = [it for it in recipient.items if it['kind'] != 'definition']
    rec_by_name = collections.defaultdict(list)
    for it in rec_items:
        for n in it['names']:
            rec_by_name[n].append(it)
    inserts, replace, keep_equal = [], {}, []
    headers = header_text(include_dir, recipient_text) if include_dir else ''
    for it in carried:
        if it['kind'] == 'storage':
            raise Refused('storage_reference:' + ','.join(sorted(it['names'])))
        text = rename(donor_text[it['start']:it['end']], mapping)
        names = {mapping.get(n, n) if not n.startswith('tag:') else n for n in it['names']}
        existing = {id(r): r for n in names for r in rec_by_name.get(n, ())}
        if not existing:
            # an extern or prototype the recipient's headers already declare stays the header's
            if names and all(declared_in(headers, n[4:] if n.startswith('tag:') else n) for n in names):
                continue
            inserts.append(text)
            continue
        same = [r for r in existing.values() if normalise(recipient_text[r['start']:r['end']]) == normalise(text)]
        if same:
            keep_equal.extend(same)
            continue
        if len(existing) != 1:
            raise Refused('declaration_conflict:' + ','.join(sorted(names)))
        (r,) = existing.values()
        if r['kind'] == 'storage':
            raise Refused('declaration_conflict_storage:' + ','.join(sorted(names)))
        replace[id(r)] = (r, text)
    # a replaced recipient declaration may only serve the old definition (and other replaced/equal items)
    exclude = [(rs, re_)] + [(r['start'], r['end']) for r, _ in replace.values()] + \
              [(r['start'], r['end']) for r in keep_equal]
    for r, _ in replace.values():
        for n in r['names']:
            if recipient.users(n, exclude):
                raise Refused('declaration_conflict:' + n)
    # assemble: replace items, insert carried items and the new definition
    edits = [(r['start'], r['end'], text) for r, text in replace.values()]
    lead = leading_comment_start(recipient_text, rs)
    block = ''.join(t + '\n' for t in inserts)
    edits.append((rs, re_, new_def))
    if block:
        edits.append((lead, lead, block + '\n'))
    out = apply_edits(recipient_text, edits)
    out = drop_unused(out, recipient_text, old_def)
    if add_includes:
        out = add_missing_includes(donor_text, out)
    return out, mapping


def leading_comment_start(text, pos):
    """Start of the comment lines directly above position `pos` (the definition's own comment block)."""
    line_start = text.rfind('\n', 0, pos) + 1
    k = line_start
    while k > 0:
        prev = text.rfind('\n', 0, k - 1) + 1
        line = text[prev:k - 1].strip()
        if line.startswith('/*') or line.startswith('*') or line.startswith('//') or line.endswith('*/'):
            k = prev
            continue
        break
    return k


def apply_edits(text, edits):
    for start, end, new in sorted(edits, key=lambda e: (e[0], e[1]), reverse=True):
        text = text[:start] + new + text[end:]
    return text


def drop_unused(text, original, old_def):
    """Remove declarations that served the old definition only and now have no user."""
    old_ids = identifiers(old_def) | {'tag:' + t for t in re.findall(r'\b(?:struct|union|enum)\s+(\w+)', old_def)}
    for _ in range(8):
        unit = Unit(text)
        dead = []
        for it in unit.items:
            if it['kind'] not in ('typedef', 'declaration', 'tag') or not it['names']:
                continue
            if not it['names'] <= old_ids and not any(n in old_ids for n in it['names']):
                continue
            if all(unit.users(n, [(it['start'], it['end'])]) == 0 for n in it['names']):
                dead.append(it)
        if not dead:
            break
        edits = []
        for it in dead:
            start = text.rfind('\n', 0, it['start']) + 1
            line_end = text.find('\n', it['end'])
            line_end = len(text) if line_end < 0 else line_end
            tail = text[it['end']:line_end]
            if text[start:it['start']].strip() == '' and re.fullmatch(r'\s*(?:/\*.*?\*/\s*)?', tail):
                stop = min(line_end + 1, len(text))
                # a blank line left between two blank lines goes with the declaration
                if text[stop:stop + 1] == '\n' and (start < 2 or text[start - 2:start] == '\n\n'):
                    stop += 1
                edits.append((start, stop, ''))
            else:
                edits.append((it['start'], it['end'], ''))
            old_ids |= it['refs']
        text = apply_edits(text, edits)
    return text


INCLUDE = re.compile(r'^[ \t]*#[ \t]*include[ \t]+[<"][^>"]+[>"][^\n]*$', re.M)


def add_missing_includes(donor_text, text):
    have = {m[0].strip() for m in INCLUDE.finditer(text)}
    missing = []
    for m in INCLUDE.finditer(donor_text):
        line = m[0].strip()
        if line not in have:  # each donor include once, even when the donor repeats it
            have.add(line)
            missing.append(line)
    if not missing:
        return text
    last = None
    for m in INCLUDE.finditer(text):
        last = m
    pos = last.end() + 1 if last else 0
    return text[:pos] + ''.join(x + '\n' for x in missing) + text[pos:]


# ------------------------------------------------------------------------------------------------ families

def read_members(path):
    with open(path) as f:
        rows = list(csv.DictReader(f, delimiter='\t'))
    fams = collections.defaultdict(list)
    for r in rows:
        fams[r['family']].append(dict(address=r['address_symbol'], file=r['file'], name=r.get('name', '')))
    return fams


def defined_name(text, address, table):
    """The function name in `text` whose name-table symbol is `address`."""
    unit = Unit(text)
    hits = [n for n in unit.defs if table.get(n, n) == address]
    return hits[0] if len(hits) == 1 else None


def _object_job(args):
    root, rel, recipe, cache = args
    sha = hashlib.sha256((Path(root) / rel).read_bytes()).hexdigest()[:24]
    key = Path(cache) / (rel.replace('/', '__') + '.' + sha + '.o')
    if key.is_file():
        return rel, str(key), None
    try:
        data = compile_object(root, rel, recipe)
    except Exception as exc:  # noqa: BLE001 - recorded
        return rel, None, str(exc)[-300:]
    key.parent.mkdir(parents=True, exist_ok=True)
    key.write_bytes(data)
    return rel, str(key), None


_PHYSICAL = {}


def physical_for(root, files):
    """{file: {physical TU: recipe}} (cast_fold.physical_for for many files with one recipe scan)."""
    import layout_compile_identity as L
    root = Path(root).resolve()
    if root not in _PHYSICAL:
        physical, _ = L.recipes(root)
        modules = {tu: (root / tu).read_text(errors='replace') for tu, r in physical.items()
                   if r['kind'] in ('overlay_module', 'slus_module')}
        _PHYSICAL[root] = (physical, modules)
    physical, modules = _PHYSICAL[root]
    out = {}
    for f in files:
        if f in physical:
            out[f] = {f: physical[f]}
            continue
        out[f] = {tu: physical[tu] for tu, text in modules.items() if Path(f).name in text}
    return out


def objects_for(root, files, cache, workers=2):
    tus = physical_for(root, sorted(set(files)))
    jobs = {(tu, json.dumps(r, sort_keys=True)) for f in tus for tu, r in tus[f].items()}
    out, errors = {}, {}
    args = [(str(root), tu, json.loads(r), str(cache)) for tu, r in sorted(jobs)]
    import layout_compile_identity as L
    L.production_recipes(root)  # loaded once; forked workers inherit it
    with ProcessPoolExecutor(max_workers=workers) as ex:
        for rel, path, err in ex.map(_object_job, args):
            if path:
                out[rel] = path
            else:
                errors[rel] = err
    return tus, out, errors


def view_of(member, tus, objects):
    """The function view of a member from the first object of a TU compiling its file that has it."""
    for tu in sorted(tus.get(member['file'], {})):
        path = objects.get(tu)
        if not path:
            continue
        try:
            return function_view(Path(path).read_bytes(), member['address']), tu
        except KeyError:
            continue
    return None, None


def row_of(rows, address, file):
    """The retail row (ledger/rows.jsonl) at `address` whose source is `file`: its layout path or, for a native
    module member, the member's source.  None unless exactly one."""
    cands = []
    for r in rows.rows.get(address, []):
        member = rows.members.get(r['id'])
        if (member['source'] if member else rows.paths.get(r['id'])) == file:
            cands.append(r)
    if not cands:
        cands = [rows.by_id[i] for i, m in rows.members.items()
                 if m.get('function') == address and m.get('source') == file and i in rows.by_id]
    return cands[0] if len(cands) == 1 else None


def retail_words(rows, address, file, name=None):
    """Retail words of the row at `address` whose source is `file` (placed_copies' reader), or None."""
    row = row_of(rows, address, file)
    return rows.words(row) if row else None


def confirm(root, members_tsv, out, families=None, workers=2):
    import placed_copies as P
    root = Path(root).resolve()
    out = Path(out)
    table = names_table(root)
    fams = read_members(members_tsv)
    if families:
        fams = {k: v for k, v in fams.items() if k in set(families)}
    files = [m['file'] for v in fams.values() for m in v if (root / m['file']).is_file()]
    tus, objects, errors = objects_for(root, files, out / 'objects', workers)
    rows = P.Rows(root)
    result = []
    for fam, mems in sorted(fams.items(), key=lambda kv: int(kv[0]) if kv[0].isdigit() else kv[0]):
        views = []
        for m in mems:
            p = root / m['file']
            if not p.is_file():
                result.append(dict(family=fam, address=m['address'], file=m['file'], dropped='file_missing'))
                continue
            text = p.read_text(errors='replace')
            name = defined_name(text, m['address'], table)
            if not name:
                result.append(dict(family=fam, address=m['address'], file=m['file'], dropped='definition_missing'))
                continue
            view, tu = view_of(m, tus, objects)
            if view is None:
                result.append(dict(family=fam, address=m['address'], file=m['file'], dropped='object_missing'))
                continue
            words = retail_words(rows, m['address'], m['file'], name)
            views.append(dict(m, name=name, view=view, tu=tu, retail=words))
        groups = []
        for v in views:
            for g in groups:
                if not masked_compare(g[0]['view'], v['view']):
                    g.append(v)
                    break
            else:
                groups.append([v])
        k = 0
        for g in groups:
            if len(g) < 2:
                for v in g:
                    result.append(dict(family=fam, address=v['address'], file=v['file'], name=v['name'],
                                       dropped='no_match'))
                continue
            k += 1
            fid = '%s.%d' % (fam, k)
            base = g[0]
            for v in g:
                rec = dict(family=fid, address=v['address'], file=v['file'], name=v['name'], tu=v['tu'],
                           size=4 * len(v['view'][0]))
                # retail words agree with the object's under the relocation mask
                mask = collections.defaultdict(int)
                for o, t, _, _ in v['view'][1]:
                    mask[o // 4] |= MASKS.get(t, 0xFFFFFFFF)
                if v['retail'] is None:
                    rec['retail'] = 'unread'
                elif len(v['retail']) != len(v['view'][0]):
                    rec['retail'] = 'size %d' % (4 * len(v['retail']))
                else:
                    bad = [i for i, (x, y) in enumerate(zip(v['retail'], base['retail'] or v['retail']))
                           if (x ^ y) & ~mask[i] & 0xFFFFFFFF]
                    obj_bad = [i for i, (x, y) in enumerate(zip(v['retail'], v['view'][0]))
                               if (x ^ y) & ~mask[i] & 0xFFFFFFFF]
                    rec['retail'] = 'match' if not bad and not obj_bad else 'differs %s' % (bad or obj_bad)[:4]
                if v is not base:
                    try:
                        rec['map'] = symbol_map(base['view'], v['view'], base['address'], v['address'])
                    except ValueError as exc:
                        rec['map_error'] = str(exc)
                result.append(rec)
    out.mkdir(parents=True, exist_ok=True)
    with (out / 'families.jsonl').open('w') as f:
        for r in result:
            f.write(json.dumps(r, sort_keys=True) + '\n')
    if errors:
        (out / 'compile_errors.json').write_text(json.dumps(errors, indent=1, sort_keys=True))
    return result, errors


# ------------------------------------------------------------------------------------------------ apply

class Prover:
    """Identity of every physical TU compiling one file, plus warning groups (local_type_trial's model)."""

    def __init__(self, root, file, port=None):
        import layout_compile_identity as L
        self.L, self.root, self.file, self.port = L, Path(root), file, port
        self.tus = physical_for(root, [file])[file]
        self.before = {tu: L.capture_one(root, tu, r) for tu, r in self.tus.items()}
        self.lint_before = self.lint() if port else None

    def identical(self):
        """Every TU raw- and canonical-object equal, its assembly equal up to `$L<n>` numbering (tu_identity's
        --ignore-local-labels: a rewritten body can renumber compiler-local labels without changing a byte)."""
        import tu_identity as T
        for tu, r in self.tus.items():
            try:
                now = self.L.capture_one(self.root, tu, r)
            except Exception as exc:  # noqa: BLE001
                return False, '%s: %s' % (tu, str(exc)[-300:])
            rec, ok = T.verdict(self.before[tu], now, ignore_local_labels=True)
            if not ok:
                return False, tu + ': ' + ('object differs' if not rec.get('raw_equal') else 'assembly differs')
        return True, ''

    def lint(self):
        import lint_closure as LC
        findings, failures = LC.lint_tree(self.root, sorted(self.tus), self.port, jobs=2)
        return LC.group_sites(findings), failures

    def warning_rises(self):
        if not self.port:
            return []
        (b, bf), (a, af) = self.lint_before, self.lint()
        bad = sorted('%s:%s' % (k[0], k[1]) for k, row in a.items() if row[0] > b.get(k, (0,))[0])
        if len(af) > len(bf):
            bad.append('compile')
        return bad


ADDRESS_ID = re.compile(r'\b(?:func|D)_[0-9A-Fa-f]{8}\b')
FENCE = re.compile(r'\bdo\s*\{|/\*\s*BYTES:')
UNTYPED_LOCAL = re.compile(r'^\s*(?:register\s+)?(?:void|u8|s8|char)\s*\*\s*\w+\s*[;=]', re.M)


def function_debt(rel, text, name):
    """Debt class counts of `name`'s own scope (tools/lint/debt_check.py)."""
    import debt_check as D
    total = collections.Counter()
    for v in D.analyze(rel, text)['scopes'].values():
        if v['symbol'] == name:
            total.update(v['counts'])
    return total


def text_score(rel, text, name):
    """Ranking of one copy's text, lower is better: (pointer casts + weak parameters, scheduling fences and BYTES
    markers, other debt of the function, untyped pointer locals, address-named identifiers)."""
    unit = Unit(text)
    a, b = unit.definition_span(name) if name in unit.defs else (0, 0)
    body = text[a:b]
    debt = function_debt(rel, text, name)
    casts = debt.get('pointer_casts', 0)
    weak = weak_params(text, name, rel)
    other = sum(n for k, n in debt.items() if k != 'pointer_casts')
    code = strip_comments(body)
    return casts, weak, (casts + weak, len(FENCE.findall(body)), other, len(UNTYPED_LOCAL.findall(code)),
                         len(ADDRESS_ID.findall(code)))


def pick_donor(root, members, skip, canonical_names):
    """The copy with the best text_score; ties to the canonical copy, then the lowest address."""
    scored = []
    for m in members:
        text = (Path(root) / m['file']).read_text(errors='replace')
        casts, weak, score = text_score(m['file'], text, m['name'])
        m.update(casts=casts, weak=weak, score=score)
        if m['file'] in skip:
            continue
        canonical = 0 if canonical_names.get(m['name']) == m['address'] else 1
        scored.append((score + (canonical, m['address']), m))
    if not scored:
        return None
    return min(scored, key=lambda s: s[0])[1]


def apply(root, out, family_ids=None, port=None, skip=(), dry_run=False, ledger=None, log=print):
    import name_inputs
    root = Path(root).resolve()
    out = Path(out)
    _SKIP.clear()
    _SKIP.update(skip)
    rows = [json.loads(x) for x in (out / 'families.jsonl').read_text().splitlines() if x.strip()]
    fams = collections.defaultdict(list)
    for r in rows:
        if 'dropped' not in r:
            fams[r['family']].append(r)
    if family_ids:
        want = set(family_ids)
        fams = {k: v for k, v in fams.items() if k in want or k.split('.')[0] in want}
    table = names_table(root)
    reverse = reverse_names(table)
    canonical_names = {n: f['canonical'] for n, f in name_inputs.copies(root / 'config/names.tsv').items()}
    import placed_copies as P
    retail = P.Rows(root)
    objects = {}
    for p in (out / 'objects').glob('*.o'):
        objects.setdefault(p.name.rsplit('.', 2)[0].replace('__', '/'), []).append(p)
    receipts, kept_families = [], []
    originals = {}

    def restore_all(*_):
        for path, text in list(originals.items()) + list(_PENDING.items()):
            path.write_text(text)
        if _:
            sys.exit(1)
    signal.signal(signal.SIGTERM, restore_all)
    try:
        for fid, members in sorted(fams.items()):
            members = [m for m in members if (root / m['file']).is_file()]
            for m in members:
                text = (root / m['file']).read_text(errors='replace')
                if defined_name(text, m['address'], table) != m['name']:
                    m['name'] = defined_name(text, m['address'], table) or m['name']
                row = row_of(retail, m['address'], m['file'])
                m['row'] = row['id'] if row else None
            members = [m for m in members if m['row']]
            donor = pick_donor(root, members, skip, canonical_names)
            if donor is None:
                receipts.append(dict(family=fid, verdict='refused', reason='every copy held'))
                continue
            fam_recs = {}

            def attempt(dn, m, rec):
                """Rewrite copy m from donor dn; returns the verdict dict (the file holds the result)."""
                try:
                    dview, rview = fresh_view(root, dn, out), fresh_view(root, m, out)
                    if masked_compare(dview, rview):
                        raise Refused('masked_bytes_differ')
                    symmap = symbol_map(dview, rview, dn['address'], m['address'])
                except (Refused, ValueError, KeyError) as exc:
                    return dict(verdict='refused', reason='map: %s' % exc)
                donor_text = (root / dn['file']).read_text()
                path = root / m['file']
                original = path.read_text()
                fam = fam_recs.setdefault(dn['row'], dict(family=fid, donor=dn['address'], row=dn['row'],
                                                         donor_file=dn['file'], donor_name=dn['name'], members=[]))
                m['tags'] = (module_tag(dn['file']), module_tag(m['file']))
                if normalise(transplant_or_none(donor_text, dn['name'], original, m['name'], symmap, table,
                                                reverse, False, root / 'include', m['tags']) or '') == \
                        normalise(original):
                    fam['members'].append(member_record(m, symmap, table))
                    return dict(verdict='same_text', casts_after=m['casts'], weak_after=m['weak'])
                originals[path] = original
                verdict = prove_one(root, m, donor_text, dn['name'], original, symmap, table, reverse, port, log)
                if verdict['verdict'] == 'kept':
                    fam['members'].append(member_record(m, symmap, table))
                    if dry_run:
                        path.write_text(original)
                else:
                    path.write_text(original)
                originals.pop(path, None)
                return verdict

            retry = []
            for m in members:
                if m is donor:
                    continue
                rec = dict(family=fid, address=m['address'], file=m['file'], name=m['name'], donor=donor['address'],
                           donor_file=donor['file'], casts_before=m['casts'], weak_before=m['weak'])
                receipts.append(rec)
                if m['file'] in skip:
                    rec.update(verdict='skipped', reason='file held by an unharvested lane')
                    continue
                if tuple(m['score']) < tuple(donor['score']):
                    rec.update(verdict='refused', reason='copy text scores better than the donor %s' % (
                        list(m['score']),))
                else:
                    rec.update(attempt(donor, m, rec))
                if rec['verdict'] == 'refused' and rec.get('reason', '').startswith('prototype_'):
                    retry.append((m, rec))
                log('%s %s %s: %s %s' % (fid, m['address'], m['file'], rec['verdict'], rec.get('reason', '')))
            # copies whose signature cannot change unproven: one source per signature, from the best such copy
            groups = collections.defaultdict(list)
            for m, rec in retry:
                groups[signature_types((root / m['file']).read_text(errors='replace'), m['name'])].append((m, rec))
            for group in groups.values():
                if len(group) < 2:
                    continue
                alt = pick_donor(root, [m for m, _ in group], skip, canonical_names)
                for m, rec in group:
                    if m is alt:
                        continue
                    first = rec['reason']
                    rec.update(attempt(alt, m, rec), donor=alt['address'], donor_file=alt['file'],
                               first_donor_refusal=first)
                    if rec['verdict'] != 'refused':
                        rec.pop('reason', None)
                    log('%s %s %s: %s %s (same-signature donor %s)' % (fid, m['address'], m['file'], rec['verdict'],
                                                                       rec.get('reason', ''), alt['address']))
            kept_families += [f for f in fam_recs.values() if f['members']]
    finally:
        restore_all()
    with (out / 'receipt.jsonl').open('a') as f:
        for r in receipts:
            f.write(json.dumps(r, sort_keys=True) + '\n')
    if ledger and not dry_run and kept_families:
        write_ledger(root, Path(ledger), kept_families)
    return receipts, kept_families


def fresh_view(root, member, out):
    """The member's function view from an object compiled from the file's current text."""
    tus = physical_for(root, [member['file']])[member['file']]
    for tu, recipe in sorted(tus.items()):
        _, path, err = _object_job((str(root), tu, recipe, str(Path(out) / 'objects')))
        if path:
            try:
                return function_view(Path(path).read_bytes(), member['address'])
            except KeyError:
                continue
    raise KeyError('no object holds ' + member['address'])


def transplant_or_none(*args):
    try:
        return transplant(*args)[0]
    except Refused:
        return None


def _param_type(param):
    """A parameter's type with its name dropped (`ActorRecord *body` -> `ActorRecord *`)."""
    toks = re.findall(r'[A-Za-z_]\w*|\S', param)
    if '(' in toks or len(toks) < 2 or not re.match(r'[A-Za-z_]', toks[-1]) or toks[-2] in ('struct', 'union',
                                                                                           'enum'):
        return ' '.join(toks)
    if all(re.match(r'[A-Za-z_]', t) for t in toks) and len(toks) == 2 and toks[0] in ('unsigned', 'signed'):
        return ' '.join(toks)
    return ' '.join(toks[:-1])


def signature(text, name):
    """The definition's return type and parameter types (names dropped), whitespace-collapsed, or None."""
    unit = Unit(text)
    if name not in unit.defs:
        return None
    start, end = unit.definition_span(name)
    head = strip_comments(text[start:end]).split('{', 1)[0]
    m = re.match(r'(.*?)\b' + re.escape(name) + r'\s*\((.*)\)\s*$', head, re.S)
    if not m:
        return ' '.join(head.split())
    depth, cur, params = 0, '', []
    for ch in m[2]:
        if ch == ',' and depth == 0:
            params.append(cur)
            cur = ''
            continue
        depth += {'(': 1, ')': -1}.get(ch, 0)
        cur += ch
    params.append(cur)
    ret = ' '.join(re.findall(r'[A-Za-z_]\w*|\S', m[1]))
    return ret + ' ' + name + '(' + ', '.join(_param_type(p) for p in params) + ')'


def signature_types(text, name):
    """signature() without the function's own name (copies of one body have different names)."""
    sig = signature(text, name)
    return sig.replace(' ' + name + '(', ' (', 1) if sig else sig


def definition_head(text, name):
    """The definition's spelled head (`void f(ActorRecord *body, ...)`), whitespace-collapsed."""
    unit = Unit(text)
    start, end = unit.definition_span(name)
    return ' '.join(strip_comments(text[start:end]).split('{', 1)[0].split())


def prototype_sites(root, name, own_file):
    """[(file, start, end)] of file-scope prototypes of `name` outside `own_file` (include/ and src/)."""
    res = subprocess.run(['git', 'grep', '-l', '-w', '-e', name, '--', 'include', 'src'], cwd=root,
                         capture_output=True, text=True)
    sites = []
    for rel in sorted(res.stdout.split()):
        if rel == own_file:
            continue
        p = Path(root) / rel
        if not p.is_file():
            continue
        text = p.read_text(errors='replace')
        for it in Unit(text).items:
            if it['kind'] == 'declaration' and it['names'] == {name}:
                sites.append((rel, it['start'], it['end']))
    return sites


def includers(root, header_rel):
    """Files that include `header_rel` (the path relative to include/) by a quoted include."""
    pattern = r'#[[:space:]]*include[[:space:]]*"' + re.escape(header_rel) + '"'
    res = subprocess.run(['git', 'grep', '-l', '-E', '-e', pattern, '--', 'include', 'src'], cwd=root,
                         capture_output=True, text=True)
    return sorted(res.stdout.split())


_SKIP = set()  # files held by unharvested lanes (apply's skip list): never rewritten, headers included
_PENDING = {}  # header path -> original text while a copy's proof is open (restored on SIGTERM)


CONSTANT = re.compile(r'^[A-Z][A-Z0-9_]*$')


def lost_constants(original, new, name):
    """Macro and enum constant names (NODE_BODY, MONSTER_BLOCK, ...) the copy's definition spells today and the
    rewritten one would not: a donor that writes the literal is not the better text there."""
    def names(text):
        unit = Unit(text)
        if name not in unit.defs:
            return set()
        a, b = unit.definition_span(name)
        return {i for i in identifiers(text[a:b]) if CONSTANT.match(i) and not re.search(r'[0-9A-F]{8}', i)}
    return sorted(names(original) - names(new))


# a member name a generator wrote (unk_9B, pad_06, an address-named or module-prefixed CL_ member)
GENERATED_MEMBER = re.compile(r'^(?:unk|pad|field)_?[0-9A-Fa-f]+(?:_|$)|[0-9A-Fa-f]{8}|^CL_')


def _definition_tokens(text, name):
    unit = Unit(text)
    if name not in unit.defs:
        return []
    a, b = unit.definition_span(name)
    return [t.value for t in lex(text[a:b])]


def _named_members(toks, weak_types=None):
    """Named member tokens after `.`/`->` (not generated names).  With `weak_types` (a predicate on a type name),
    accesses through a variable declared, or an expression cast, as such a type (an address-named or file-local
    view) are left out: renaming those members is what a better donor does."""
    declared = {}
    if weak_types:
        for k in range(1, len(toks) - 2):
            if re.match(r'[A-Za-z_]\w*$', toks[k - 1]) and toks[k] == '*':
                j = k
                while j < len(toks) and toks[j] == '*':
                    j += 1
                if j + 1 < len(toks) and re.match(r'[A-Za-z_]\w*$', toks[j]) and toks[j + 1] in (';', ',', '=', ')', '['):
                    declared.setdefault(toks[j], toks[k - 1])
    out = collections.Counter()
    for k, t in enumerate(toks):
        if not (k and toks[k - 1] in ('.', '->') and re.match(r'[A-Za-z_]', t) and not GENERATED_MEMBER.search(t)):
            continue
        if weak_types:
            start = k
            while start >= 2 and toks[start - 1] in ('.', '->') and re.match(r'[A-Za-z_]\w*$', toks[start - 2]):
                start -= 2
            base = toks[start] if start != k else None
            via = declared.get(base) if base else None
            if start >= 2 and toks[start - 1] in ('.', '->') and toks[start - 2] == ')':
                depth, j = 0, start - 2
                while j >= 0:
                    depth += {')': 1, '(': -1}.get(toks[j], 0)
                    if depth == 0:
                        break
                    j -= 1
                via = next((x for x in toks[j:start - 1] if re.match(r'[A-Za-z_]\w*$', x) and weak_types(x)), via)
            if via and weak_types(via):
                continue
        out[t] += 1
    return out


def _lowerings(toks):
    """Spellings that stand in for a named member: generated members, and pointer casts `(T *)` / `(T **)` (a raw
    offset read `*((u8 *)p + 0x6D)` and a reinterpretation `(GpuContext **)&g` both carry one)."""
    out = collections.Counter()
    for k, t in enumerate(toks):
        if k and toks[k - 1] in ('.', '->') and GENERATED_MEMBER.search(t):
            out[t] += 1
        if t == '(' and k + 1 < len(toks) and re.match(r'[A-Za-z_]\w*$', toks[k + 1]) and toks[k + 1] != 'sizeof':
            j = k + 1
            while j < len(toks) and re.match(r'[A-Za-z_]\w*$', toks[j]):
                j += 1
            if j < len(toks) and toks[j] == '*':
                while j < len(toks) and toks[j] == '*':
                    j += 1
                if j < len(toks) and toks[j] == ')':
                    out[' '.join(toks[k:j + 1])] += 1
    return out


def _dropped_view_members(original, new):
    """Member names declared by the copy's own file-scope struct or union views that the rewritten file no longer
    defines (a file-local `Scratch` or `Packet` view replaced by a shared record): renaming those is the point."""
    old_unit, new_unit = Unit(original), Unit(new)
    kept = set()
    for item in new_unit.items:
        if item['kind'] in ('typedef', 'tag'):
            kept |= item['names']
    out = set()
    for item in old_unit.items:
        if item['kind'] in ('typedef', 'tag') and item['names'] and not item['names'] & kept and \
                any(t.value == '{' for t in old_unit.tokens[item['a']:item['b'] + 1]):
            out |= {t.value for t in old_unit.tokens[item['a']:item['b'] + 1] if t.kind == 'id'}
    return out


def lost_members(original, new, name, gap=3):
    """Named members the copy's definition spells (`entity->pending_turn_updates`, `g_game_work.draw_buffer`) that
    the rewritten one spells fewer times, where the rewritten text in their place reads a generated member
    (`unk_9B`), a raw offset or a pointer cast that the copy's text there does not: sorted [(member, replacement spelling)].  A donor that
    spells the access another named way (`x = x & m` -> `x &= m`) is not refused."""
    import difflib
    import readcounts as RC
    a, b = _definition_tokens(original, name), _definition_tokens(new, name)
    local = {alias for alias, *_ in RC.file_facts(original, True)['structs']}

    def weak(type_name):
        return type_name in local or bool(RC.GENERATED_VIEW.search(type_name))
    before, after = _named_members(a, weak), _named_members(b)
    lost = {m for m, n in before.items() if after.get(m, 0) < n} - _dropped_view_members(original, new)
    if not lost:
        return []
    regions = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes():
        if tag == 'equal':
            continue
        if regions and i1 - regions[-1][1] <= gap and j1 - regions[-1][3] <= gap:
            regions[-1] = (regions[-1][0], i2, regions[-1][2], j2)
        else:
            regions.append((i1, i2, j1, j2))
    out = set()
    for i1, i2, j1, j2 in regions:
        gone = lost & set(_named_members(a[max(i1 - 1, 0):i2]))
        added = _lowerings(b[max(j1 - 1, 0):j2]) - _lowerings(a[max(i1 - 1, 0):i2])
        if gone and added:
            out.update((m, spelling) for m in gone for spelling in sorted(added)[:1])
    return sorted(out)


def _param_types(text, name):
    sig = signature(text, name)
    if not sig or name + '(' not in sig:
        return None
    inner = sig.split(name + '(', 1)[1].rsplit(')', 1)[0]
    depth, cur, params = 0, '', []
    for ch in inner:
        if ch == ',' and depth == 0:
            params.append(cur.strip())
            cur = ''
            continue
        depth += {'(': 1, ')': -1}.get(ch, 0)
        cur += ch
    params.append(cur.strip())
    return params


def weakened_parameters(original, new, name):
    """Parameters the copy declares with a real type that the rewritten definition declares as a generated or
    address-named layout, a file-local view, a byte pointer or void * (readcounts' weak parameter kinds):
    [(index, old type, new type)]."""
    import readcounts as RC
    old, cur = _param_types(original, name), _param_types(new, name)
    if old is None or cur is None or len(old) != len(cur):
        return []
    local_old = {alias for alias, *_ in RC.file_facts(original, True)['structs']}
    local_new = {alias for alias, *_ in RC.file_facts(new, True)['structs']}
    return [(k, o, c) for k, (o, c) in enumerate(zip(old, cur))
            if o != c and not RC.parameter_kind(o + ' p', local_old) and RC.parameter_kind(c + ' p', local_new)]


def check_prototypes(root, m, original, new, tus):
    """Refuse a signature change whose prototype sits in another .c file or in a header that a TU outside the
    proof set `tus` includes (its callers' types would change unproven)."""
    old_sig, new_sig = signature(original, m['name']), signature(new, m['name'])
    if old_sig == new_sig or new_sig is None:
        return
    for rel, start, end in prototype_sites(root, m['name'], m['file']):
        if not rel.endswith('.h'):
            raise Refused('prototype_in_other_source:' + rel)
        if rel in _SKIP:
            raise Refused('prototype_header_held:' + rel)
        users = includers(root, Path(rel).relative_to('include').as_posix()) if rel.startswith('include/') else []
        outside = [u for u in users if u != m['file'] and u not in tus]
        if outside or not users:
            raise Refused('prototype_header_shared:%s (%s)' % (rel, ', '.join(outside[:3]) or 'no includer'))


def sync_prototypes(root, m, original, new, prover):
    """Header prototypes of the copy rewritten to its new signature (checked by check_prototypes first):
    {path: original text}."""
    old_sig, new_sig = signature(original, m['name']), signature(new, m['name'])
    if old_sig == new_sig or new_sig is None:
        return {}
    changed = {}
    sites = prototype_sites(root, m['name'], m['file'])
    by_file = collections.defaultdict(list)
    for rel, start, end in sites:
        by_file[rel].append((start, end))
    for rel, spans in by_file.items():
        path = Path(root) / rel
        text = path.read_text()
        changed[path] = text
        _PENDING[path] = text
        head = definition_head(new, m['name'])
        path.write_text(apply_edits(text, [(a, b, head + ';') for a, b in spans]))
    return changed


def prove_one(root, m, donor_text, donor_name, original, symmap, table, reverse, port, log):
    path = Path(root) / m['file']
    try:
        new, mapping = transplant(donor_text, donor_name, original, m['name'], symmap, table, reverse,
                                  include_dir=Path(root) / 'include', tags=m['tags'])
    except Refused as exc:
        return dict(verdict='refused', reason=str(exc))
    lost = lost_constants(original, new, m['name'])
    if lost:
        return dict(verdict='refused', reason='loses_named_constant:' + ','.join(lost))
    members = lost_members(original, new, m['name'])
    if members:
        return dict(verdict='refused', reason='loses_named_member:' + ','.join(
            '%s->%s' % (a, b) for a, b in members[:8]))
    weakened = weakened_parameters(original, new, m['name'])
    if weakened:
        return dict(verdict='refused', reason='weakens_parameter:' + ','.join(
            '%d %s->%s' % w for w in weakened))
    tus = physical_for(root, [m['file']])[m['file']]
    try:
        check_prototypes(root, m, original, new, tus)
    except Refused as exc:
        return dict(verdict='refused', reason=str(exc))
    prover = Prover(root, m['file'], port)
    headers = sync_prototypes(root, m, original, new, prover)
    result = _prove(root, m, path, original, new, donor_text, donor_name, symmap, table, reverse, prover, mapping)
    for hp, text in headers.items():
        rel = str(hp.relative_to(root))
        before, after = file_debt(rel, text), file_debt(rel, hp.read_text())
        rises = {k: (before.get(k, 0), n) for k, n in after.items() if n > before.get(k, 0)}
        if rises and result['verdict'] == 'kept':
            path.write_text(original)
            result = dict(verdict='refused', reason='debt_rise %s: %s' % (rel, rises))
    if result['verdict'] != 'kept':
        for hp, text in headers.items():
            hp.write_text(text)
    for hp in headers:
        _PENDING.pop(hp, None)
    else:
        result['headers'] = sorted(str(hp.relative_to(root)) for hp in headers)
    return result


def drop_unneeded_includes(without, with_includes, identical):
    """`with_includes` less the include lines it adds to `without` that the unit does not need: groups of added
    lines are dropped by bisection while `identical(text)` holds (every TU byte-identical)."""
    lines = with_includes.splitlines(keepends=True)
    have = collections.Counter(m[0].strip() for m in INCLUDE.finditer(without))
    added = []
    for i, line in enumerate(lines):
        if INCLUDE.match(line):
            key = line.strip()
            if have[key] > 0:
                have[key] -= 1
            else:
                added.append(i)
    drop = set()

    def text(skip):
        return ''.join(x for i, x in enumerate(lines) if i not in skip)

    def solve(group):
        if not group:
            return
        if identical(text(drop | set(group))):
            drop.update(group)
        elif len(group) > 1:
            solve(group[:len(group) // 2])
            solve(group[len(group) // 2:])
    solve(added)
    return text(drop)


def _prove(root, m, path, original, new, donor_text, donor_name, symmap, table, reverse, prover, mapping):
    full = None
    path.write_text(new)
    ok, why = prover.identical()
    if not ok:
        try:
            new2, mapping = transplant(donor_text, donor_name, original, m['name'], symmap, table, reverse,
                                       add_includes=True, include_dir=Path(root) / 'include', tags=m['tags'])
        except Refused as exc:
            path.write_text(original)
            return dict(verdict='refused', reason=str(exc))
        if new2 != new:
            path.write_text(new2)
            ok, why2 = prover.identical()
            if ok:
                new = drop_unneeded_includes(new, new2, lambda text: path.write_text(text) or prover.identical()[0])
                path.write_text(new)
                full = new2
            else:
                why = why + ' / with includes: ' + why2
    if not ok:
        path.write_text(original)
        return dict(verdict='refused', reason='not_identical: ' + why[-300:])
    before, after = file_debt(m['file'], original), file_debt(m['file'], new)
    rises = {k: (before.get(k, 0), n) for k, n in after.items() if n > before.get(k, 0)}
    if rises:
        path.write_text(original)
        return dict(verdict='refused', reason='debt_rise %s' % rises)
    warn = prover.warning_rises()
    if warn and full not in (None, new):
        # an include dropped as byte-neutral may still have declared a callee: retry with every donor include
        path.write_text(full)
        new, warn = full, prover.warning_rises()
    if warn:
        path.write_text(original)
        return dict(verdict='refused', reason='warning_rise %s' % warn[:5])
    return dict(verdict='kept', casts_after=function_casts(m['file'], new, m['name']),
                weak_after=weak_params(new, m['name'], m['file']), file_casts=(before.get('pointer_casts', 0),
                                                                    after.get('pointer_casts', 0)),
                mapping=mapping)


def member_record(m, symmap, table):
    """Ledger row part for one copy: address and the symbol map (object symbols, not spellings)."""
    return dict(address=m['address'], row=m['row'], map={k: v for k, v in sorted(symmap.items()) if k != v})


def merge_families(rows):
    """One ledger row per connected family: copies recorded under several donors (a later run picks a donor
    that is itself a copy) join one row whose donor is the one with the most copies, each copy's map composed
    along the recorded donor -> copy edges (a map omits symbols that are the same on both sides)."""
    edges = collections.defaultdict(list)
    address = {}
    for r in rows.values():
        address[r['row']] = r['donor']
        for c in r['copies']:
            address[c['row']] = c['address']
            edges[r['row']].append((c['row'], c.get('map', {})))
            edges[c['row']].append((r['row'], {v: k for k, v in c.get('map', {}).items()}))
    seen, out = set(), {}
    for start in sorted(rows, key=lambda k: (-len(rows[k]['copies']), k)):
        if start in seen:
            continue
        seen.add(start)
        maps, queue = {start: {}}, [start]
        while queue:
            node = queue.pop(0)
            for nxt, m in edges[node]:
                if nxt in seen:
                    continue
                seen.add(nxt)
                prev = maps[node]
                # symbols of the root -> symbols of nxt: through node's map, then this edge's
                composed = {}
                for k in set(prev) | {v for v in m if v not in prev.values()}:
                    mid = prev.get(k, k)
                    composed[k] = m.get(mid, mid)
                for k, v in prev.items():
                    composed[k] = m.get(v, v)
                maps[nxt] = {k: v for k, v in composed.items() if k != v}
                queue.append(nxt)
        copies = [dict(address=address[n], row=n, map=dict(sorted(maps[n].items())))
                  for n in sorted(maps) if n != start]
        out[start] = dict(donor=address[start], row=start, copies=copies)
    return out


def write_ledger(root, path, families):
    """Merge kept families into the clone-sources ledger (one row per donor row)."""
    path = Path(root) / path if not Path(path).is_absolute() else Path(path)
    rows = {}
    if path.is_file():
        for line in path.read_text().splitlines():
            if line.strip():
                r = json.loads(line)
                rows[r['row']] = r
    for fam in families:
        row = rows.get(fam['row'], dict(donor=fam['donor'], row=fam['row'], copies=[]))
        have = {c['row']: c for c in row['copies']}
        for c in fam['members']:
            have[c['row']] = c
        row['copies'] = [have[a] for a in sorted(have)]
        rows[fam['row']] = row
    rows = merge_families(rows)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(''.join(json.dumps(rows[k], sort_keys=True) + '\n' for k in sorted(rows)))


# ------------------------------------------------------------------------------------------------ main

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest='cmd', required=True)
    c = sub.add_parser('confirm')
    c.add_argument('--members', required=True)
    c.add_argument('--out', required=True)
    c.add_argument('--family', nargs='*')
    c.add_argument('--workers', type=int, default=2)
    a = sub.add_parser('apply')
    a.add_argument('--out', required=True)
    a.add_argument('--family', nargs='*')
    a.add_argument('--port')
    a.add_argument('--skip-list')
    a.add_argument('--dry-run', action='store_true')
    a.add_argument('--ledger', default='ledger/clone_sources.jsonl')
    for p in (c, a):
        p.add_argument('--root', default='.')
    args = ap.parse_args(argv)
    root = Path(args.root).resolve()
    if args.cmd == 'confirm':
        result, errors = confirm(root, args.members, args.out, args.family, args.workers)
        kept = [r for r in result if 'dropped' not in r]
        print('confirm: %d copies in %d families; %d dropped; %d compile errors' % (
            len(kept), len({r['family'] for r in kept}), len(result) - len(kept), len(errors)))
        return 0
    skip = set()
    if args.skip_list:
        skip = {x.strip() for x in Path(args.skip_list).read_text().splitlines() if x.strip()}
    receipts, kept = apply(root, args.out, args.family, args.port, skip, args.dry_run, args.ledger)
    counts = collections.Counter(r.get('verdict') for r in receipts)
    print('apply: ' + ', '.join('%s %d' % kv for kv in sorted(counts.items())))
    return 0


if __name__ == '__main__':
    sys.exit(main())
