#!/usr/bin/env python3
"""D0 rename proof primitives: C preprocessing tokens and strict ELF32 identity.

No compiler, checkout, lane, or third-party module is loaded at import time.
The lane command is tools/lanes/lanekit/rename_proof.py.
"""
from __future__ import annotations

import hashlib
import re
import struct


class Refusal(ValueError):
    """An input outside the proof's supported, fail-closed subset."""


KEYWORDS = set(('auto break case char const continue default do double else enum '
    'extern float for goto if inline int long register restrict return short signed '
    'sizeof static struct switch typedef union unsigned void volatile while '
    '_Alignas _Alignof _Atomic _Bool _Complex _Generic _Imaginary _Noreturn '
    '_Static_assert _Thread_local asm __asm __asm__ __attribute __attribute__ '
    '__const __const__ __inline __inline__ __restrict __restrict__ __signed '
    '__signed__ __typeof __typeof__ typeof __volatile __volatile__ __extension__ '
    '__label__ __alignof __alignof__ __thread __auto_type __real__ __imag__ '
    '__real __imag __complex __complex__ __typeof_unqual__ typeof_unqual '
    'alignas alignof bool true false nullptr static_assert thread_local '
    '_BitInt _Decimal32 _Decimal64 _Decimal128').split())
IDENT = re.compile(r'[A-Za-z_][A-Za-z_0-9]*\Z')
NUMBER = re.compile(r'(?:[0-9]|\.[0-9])(?:[eEpP][+-]|[A-Za-z_0-9.]|\\u[0-9a-fA-F]{4}|\\U[0-9a-fA-F]{8})*')
PUNCT = re.compile(r'%:%:|>>=|<<=|\.\.\.|->|\+\+|--|<<|>>|<=|>=|==|!=|&&|\|\||\*=|/=|%=|\+=|-=|&=|\^=|\|=|##|<:|:>|<%|%>|%:|[\[\](){}.&*+\-~!/%<>^|?:;=,#]')
LITERAL = re.compile(r'''(?:u8|u|U|L)?(?:"(?:\\[^\n]|[^"\\\n])*"|'(?:\\[^\n]|[^'\\\n])*')''')
ID_START = re.compile(r'[A-Za-z_][A-Za-z_0-9]*')


def sha(data):
    return hashlib.sha256(data).hexdigest()


def tokens(text):
    """Preprocessing tokens, with directives frozen and comments as whitespace.

    Splicing precedes comment removal (C phases 2/3). Directive newlines and
    #define function-like adjacency matter even when ordinary whitespace does
    not. Trigraphs, UCN identifiers and non-ASCII source are refused rather than
    guessed. Digraph directive introducers are recognized.
    """
    if not text.isascii() or '\x00' in text or re.search(r'\?\?[=/\'()!<>-]', text):
        raise Refusal('unsupported non-ASCII, NUL or trigraph source')
    text = re.sub(r'\\\r?\n', '', text.replace('\r\n', '\n'))
    out = []; i = 0; line = 1; bol = True; directive = False; macro_name_end = None
    while i < len(text):
        c = text[i]
        if c.isspace():
            if c == '\n':
                if directive:
                    out.append(('directive-end', '', line))
                line += 1; bol = True; directive = False; macro_name_end = None
            i += 1; continue
        if text.startswith('//', i):
            end = text.find('\n', i)
            i = len(text) if end < 0 else end
            continue
        if text.startswith('/*', i):
            end = text.find('*/', i + 2)
            if end < 0:
                raise Refusal('unterminated comment at line %d' % line)
            # Block comments become one space, but preserve internal newlines.
            n = text[i:end+2].count('\n')
            if n and directive:
                raise Refusal('multiline comment within a directive is unsupported')
            if n:
                if directive:
                    out.append(('directive-end', '', line))
                line += n; bol = True; directive = False; macro_name_end = None
            i = end + 2; continue
        start = i
        # Header-name is a preprocessing token, including its internal spaces.
        directive_words = [t[1] for t in out if t[0] == 'directive' and t[2] == line] if directive else []
        if directive_words in (['#', 'include'], ['#', 'include_next'], ['%:', 'include'], ['%:', 'include_next']) and c == '<':
            end = text.find('>', i + 1)
            if end < 0 or '\n' in text[i:end]:
                raise Refusal('unterminated header name')
            out.append(('directive', text[i:end+1], line)); i = end + 1; bol = False
            continue
        hit = LITERAL.match(text, i)
        if hit:
            kind = 'literal'
        else:
            hit = NUMBER.match(text, i)
            if hit:
                kind = 'number'
            else:
                hit = ID_START.match(text, i)
                if hit:
                    kind = 'keyword' if hit[0] in KEYWORDS else 'identifier'
                else:
                    hit = PUNCT.match(text, i); kind = 'punct'
        if not hit:
            raise Refusal('unsupported token at line %d: %r' % (line, text[i:i+20]))
        value = hit[0]; i = hit.end()
        if bol and value in ('#', '%:'):
            directive = True
        if directive:
            # Freeze operands and directive spelling. Retain the one whitespace
            # distinction which changes macro grammar: NAME( vs NAME (.
            previous = [t[1] for t in out if t[0] == 'directive' and t[2] == line]
            if previous in (['#', 'define'], ['%:', 'define']):
                macro_name_end = i
            elif macro_name_end is not None:
                out.append(('directive-adjacency', str(start == macro_name_end), line))
                macro_name_end = None
            out.append(('directive', value, line))
        else:
            out.append((kind, value, line))
        bol = False
    if directive:
        out.append(('directive-end', '', line))
    return out


def check_renames(before, after, renames=None):
    """Only identifier spelling may differ; one simultaneous bijection per file.

    An explicit map is an allow-list: partial application, unused entries,
    captures, swaps and identifier merges all refuse. Inferred maps have the
    same restrictions. Unrelated same-spelling fields may be left alone by
    using separate per-file proofs; this intentionally is not a C name resolver.
    """
    a, b = tokens(before), tokens(after)
    if len(a) != len(b):
        raise Refusal('token count changed: %d -> %d' % (len(a), len(b)))
    mapping = {}; reverse = {}; changed = {}
    for index, (old, new) in enumerate(zip(a, b)):
        ak, av, line = old; bk, bv, _ = new
        if ak != bk or (ak != 'identifier' and av != bv):
            raise Refusal('non-rename token change at token %d, before line %d: %r -> %r'
                          % (index, line, av, bv))
        if ak != 'identifier':
            continue
        if av in mapping and mapping[av] != bv:
            raise Refusal('inconsistent rename of %s at line %d' % (av, line))
        if bv in reverse and reverse[bv] != av:
            raise Refusal('identifier capture/merge into %s at line %d' % (bv, line))
        mapping[av] = bv; reverse[bv] = av
        if av != bv:
            changed[av] = bv
    old_names = {v for k, v, _ in a if k == 'identifier'}
    # Swaps and chains are disallowed, even if there is no remaining old use.
    if set(changed.values()) & old_names:
        raise Refusal('rename target already exists in before identifiers')
    if renames is not None:
        if not isinstance(renames, dict) or any(not isinstance(k, str) or not isinstance(v, str)
                or not IDENT.fullmatch(k) or not IDENT.fullmatch(v) or k in KEYWORDS
                or v in KEYWORDS or k == v for k, v in renames.items()):
            raise Refusal('renames must be a JSON object of distinct C identifiers')
        if changed != renames:
            raise Refusal('inferred renames differ from the explicit allow-list: %r' % changed)
    return dict(renames=dict(sorted(changed.items())), tokens=len(a),
                before_sha256=sha(before.encode()), after_sha256=sha(after.encode()))


def object_identity(data):
    """Strict link-relevant ELF32 LE MIPS ET_REL identity, without masking bytes.

    Section indexes / symbol indexes are resolved, never ignored. REL order is
    retained (HI16/LO16 pairing matters). FILE symbols, debug sections and .pdr
    describe source/debugging rather than loaded storage. All allocated section
    bytes and geometry, every symbol except FILE, and relocations targeting
    allocated storage are compared. Unknown non-debug sections fail closed.
    """
    def fail(message):
        raise Refusal('ELF: ' + message)
    def unpack(fmt, offset):
        try:
            return struct.unpack_from(fmt, data, offset)
        except (struct.error, OverflowError):
            fail('truncated structure')
    def blob(offset, size):
        if offset < 0 or size < 0 or offset + size > len(data):
            fail('section out of bounds')
        return data[offset:offset+size]
    def string(table, offset):
        if not 0 <= offset < len(table) or b'\0' not in table[offset:]:
            fail('invalid string offset')
        return table[offset:table.index(b'\0', offset)].decode('latin1')
    if len(data) < 52 or data[:7] != b'\x7fELF\x01\x01\x01':
        fail('requires ELF32 little-endian version 1')
    typ, machine, version, entry, phoff, shoff, flags, ehsize, phsize, phnum, shsize, shnum, shstr = unpack('<HHIIIIIHHHHHH', 16)
    if typ != 1 or machine != 8 or version != 1 or entry or phoff or phnum or ehsize != 52 or shsize != 40:
        fail('requires a MIPS relocatable object without program headers')
    if not 0 < shstr < shnum or not shnum:
        fail('extended/missing section table unsupported')
    sections = [unpack('<IIIIIIIIII', shoff + i * shsize) for i in range(shnum)]
    def body(s):
        return b'' if s[1] == 8 else blob(s[4], s[5])
    if sections[shstr][1] != 3:
        fail('invalid section-name table')
    strings = body(sections[shstr])
    names = [string(strings, s[0]) for s in sections]
    if len(set(names)) != len(names):
        fail('duplicate section names unsupported')
    def section_ref(index):
        if index == 0: return 'UND'
        if index in (0xfff1, 0xfff2): return {0xfff1: 'ABS', 0xfff2: 'COMMON'}[index]
        if not 0 < index < shnum: fail('unsupported symbol section index')
        return names[index]
    allocated = {}; tables = {}; symbols = []; allocation_order = []; payloads = {}
    for i, s in enumerate(sections):
        name, stype, sf, addr, offset, size, link, info, align, entsize = s
        body(s)  # Validate every file-backed extent, even ignored debug content.
        if sf & 2:
            allocation_order.append(names[i])
            payloads[names[i]] = body(s)
            if stype not in (1, 8, 0x70000006, 0x7000002a):
                fail('unknown allocated section type in ' + names[i])
            if sf & (0x40 | 0x80 | 0x200):
                fail('link-order, group or TLS allocation unsupported')
            allocated[names[i]] = dict(type=stype, flags=sf, address=addr, size=size,
                alignment=align, entsize=entsize, link=section_ref(link) if link else None,
                info=info, sha256=sha(body(s)))
        elif stype not in (0, 2, 3, 4, 9) and not (
                names[i] in ('.pdr', '.comment', '.gnu.attributes')
                or names[i].startswith(('.debug', '.mdebug', '.stab', '.note'))):
            fail('unknown non-allocated section: ' + names[i])
        if stype != 2:
            continue
        if entsize != 16 or size % 16 or not 0 < link < shnum or sections[link][1] != 3:
            fail('invalid symbol table')
        tab = body(sections[link]); entries = []
        for pos in range(offset, offset + size, 16):
            nm, value, sz, sinfo, other, index = unpack('<IIIBBH', pos)
            symbol = (string(tab, nm), value, sz, sinfo, other, section_ref(index))
            entries.append(symbol)
            if sinfo & 15 != 4:  # FILE only; retain local/static and undefined symbols.
                symbols.append(symbol)
        tables[i] = entries
    if not tables:
        fail('missing symbol table')
    relocations = []
    for i, s in enumerate(sections):
        _, stype, sf, addr, offset, size, link, info, align, entsize = s
        if stype not in (4, 9):
            continue
        if not 0 < info < shnum or link not in tables:
            fail('invalid relocation section target/table')
        if names[info] not in allocated:
            # Debug-only relocation sections are not loaded.
            if names[info] != '.pdr' and not names[info].startswith(('.debug', '.mdebug', '.stab')):
                fail('relocations to unknown non-allocated section')
            continue
        stride = 12 if stype == 4 else 8
        if entsize != stride or size % stride:
            fail('invalid relocation record size')
        records = []
        for pos in range(offset, offset + size, stride):
            rel = unpack('<IIi' if stype == 4 else '<II', pos)
            where, ri = rel[:2]; symbol_index = ri >> 8
            if symbol_index >= len(tables[link]) or where >= sections[info][5]:
                fail('relocation out of bounds')
            records.append((where, ri & 255, tables[link][symbol_index], *rel[2:]))
        relocations.append((names[i], names[info], stype, sf, align, records))
    return dict(abi=data[7:16].hex(), flags=flags, sections=allocated, allocation_order=allocation_order, payloads=payloads,
                symbols=sorted(symbols), relocations=relocations)


def compare_objects(before, after):
    a, b = object_identity(before), object_identity(after)
    differences = []
    for key in a:
        if a[key] != b[key]:
            if key in ('sections', 'payloads'):
                for name in sorted(a[key].keys() | b[key].keys()):
                    if a[key].get(name) != b[key].get(name):
                        if 'section ' + name not in differences:
                            differences.append('section ' + name)
            else:
                differences.append(key)
    return dict(equal=not differences, differences=differences,
                sections=a['sections'], before_object_sha256=sha(before),
                after_object_sha256=sha(after))


if __name__ == '__main__':
    # One public entry point, whether called through tools/ or the lane kit.
    import runpy
    import sys
    from pathlib import Path
    kit = Path(__file__).resolve().parent / 'lanes/lanekit'
    sys.path.insert(0, str(kit))
    runpy.run_path(str(kit / 'rename_proof.py'), run_name='__main__')
