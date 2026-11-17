#!/usr/bin/env python3
"""Placed-copy families: one name for the same function placed at several addresses.

A config/names.tsv row whose evidence starts with `copy_of=0x<addr>` records that the function at its address is
the same function as the name's ordinary (canonical) row at <addr>, compiled from a separate source in another
image (tools/build/name_inputs.py). This check refuses a family whose bodies differ.

For every family address the check finds the one row at that address whose source defines the family name, takes
its retail words (a native module member's extent from config/overlays/modules.json, else the ledger row's) and
compares them with the canonical row's words. The sizes must be equal and every word identical, except a J/JAL
whose target lies inside its own function at the same offset on both sides (a branch within the body, the only
field that moves with the placement).

A copy whose words differ elsewhere is still the same function when they differ only in relocated fields and the
relocations correspond (relocated()).  The fields are read from the words alone: the 26-bit J/JAL target, a lui
immediate (%hi), and the immediate of a load, store or addiu whose base register holds that lui's value (%lo; a
forward dataflow over the body's blocks pairs each %lo with its lui, through an addu with an unrelocated index).
The opcode and registers of every word must be equal.  Each relocation is then a pair, canonical target -> copy
target, and the pairs must map one-to-one (no two canonical targets on one copy target, no canonical target on
two), and each pair whose targets differ must be:
  * the body's own address at the same offset; or
  * the base shift (tried first): the copy's image is the canonical's linked at another base, so the target moves
    by exactly the base delta (the copy's address minus the canonical's) and the copy's image holds there what the
    canonical's holds at its target.  The images qualify when canonical and copy are members at the same index of
    two native modules with one layout (member count, offsets and sizes), or when they lie in different load
    images (the file does not hold the copy where the canonical's image puts that address) and the delta is at
    least MIN_BASE_SHIFT (different load slots).  What a shifted target reaches is checked in
    the retail bytes, each image read as one load at its row's base: a code target must be one function by
    this same check (a cycle counts as passing; a target the ledger does not list as a function start is read
    at the other side's size), and a data target's DATA_WINDOW bytes must be equal word for word or differ by
    exactly the delta (a pointer the relink moved).  So a template body that installs a different callback, or
    reads a different object that merely sits at the same distance, refuses; or
  * (only where the delta is not the base delta, which the base shift decides alone) one symbol in both images: the
    same config/names.tsv name at both addresses, resolved per image. A code name counts only where the function
    each image holds at its address has a source that defines it (names.tsv keys by address, and an address is a
    different function in another image); a data name only where each address carries a single names.tsv row.
Anything else refuses, with the reason: a differing word that is not a relocated field, a lui with no %lo use,
a code target that is not one function by name or base shift, a target shifted by another delta (or shifted
where no base shift applies), or a map that is not one-to-one.

The copy's name binds to its own address only where the native module gate compiles its TU, so every copy must be
a native module member (config/overlays/modules.json). A TU that config/link
also places in other images (an entry whose row is not its home) is compiled there through ccproc's global table,
which spells the name as the canonical address. So a copy is refused when such a placement places the copy itself
or a function of its TU that references the name.

The word comparison reads the retail containers (work/disc/containers, extracted locally and never published).
Without them (a public checkout) the structural checks still run (the copy rows, one defining row per family
address, native module membership and the placement refusal) and the comparison is reported as skipped.

    python3 tools/lint/placed_copies.py [--root .]      # prints the families; rc 1 on a problem
    python3 tools/lint/placed_copies.py --pair CANONICAL_ROW COPY_ROW   # one comparison (ledger/rows.jsonl ids)
"""
from __future__ import annotations

import argparse
import json
import re
import struct
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
CONTAINER_DIR = 'work/disc/containers'
SKIPPED = 'skipped: retail containers absent'
CONTAINERS = {'dungeon': 'DUNGEON_DUNGEON.BIN', 'town': 'TOWN_TOWN.BIN', 'main': 'MAIN_MAIN.BIN',
              'ovmovie': 'OVMOVIE.BIN'}


def _name_inputs():
    sys.path.insert(0, str(ROOT / 'tools/build'))
    try:
        import name_inputs
    finally:
        sys.path.pop(0)
    return name_inputs


def strip_comments(text):
    text = re.sub(r'/\*.*?\*/', lambda m: re.sub(r'[^\n]', ' ', m[0]), text, flags=re.S)
    return re.sub(r'//[^\n]*', '', text)


def defines(text, name):
    """True when the C text has a function definition (not a declaration) of name."""
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', text):
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        rest = text[i:i + 400].lstrip()
        # K&R parameter declarations may sit between ')' and '{'
        if rest.startswith('{') or re.match(r'(?:[^;{}()]*;\s*)+\{', rest):
            line = text[text.rfind('\n', 0, m.start()) + 1:m.start()]
            if not re.search(r'[=,(]\s*$', line) and 'return' not in line:
                return True
    return False


def definition(text, name):
    """Body text of name's definition in comment-stripped C text, or None."""
    for m in re.finditer(r'\b' + re.escape(name) + r'\s*\(', text):
        line = text[text.rfind('\n', 0, m.start()) + 1:m.start()]
        if re.search(r'[=,(]\s*$', line) or 'return' in line:
            continue
        depth, i = 1, m.end()
        while i < len(text) and depth:
            depth += {'(': 1, ')': -1}.get(text[i], 0)
            i += 1
        rest = re.match(r'\s*(?:[^;{}()]*;\s*)*\{', text[i:])
        if not rest:
            continue
        brace = i + rest.end() - 1
        depth, j = 0, brace
        while j < len(text):
            depth += {'{': 1, '}': -1}.get(text[j], 0)
            j += 1
            if depth == 0:
                return text[brace:j]
    return None


def compare(canonical, copy, start_a, start_b):
    """Problems between two word lists (empty when they are the same function)."""
    if len(canonical) != len(copy):
        return [f'size {4 * len(canonical)} != {4 * len(copy)}']
    problems = []
    for k, (a, b) in enumerate(zip(canonical, copy)):
        if a == b:
            continue
        op = a >> 26
        if op in (2, 3) and b >> 26 == op:
            ta = ((start_a + 4 * k + 4) & 0xF0000000) | ((a & 0x03FFFFFF) << 2)
            tb = ((start_b + 4 * k + 4) & 0xF0000000) | ((b & 0x03FFFFFF) << 2)
            ra, rb = ta - start_a, tb - start_b
            if ra == rb and 0 <= ra < 4 * len(canonical):
                continue
        problems.append(f'word {k}: {a:08x} != {b:08x}')
    return problems


# ---------------------------------------------------------------------------------------- relocated fields

LUI = 0x0F
# I-type instructions whose 16-bit immediate is a %lo() field when their base register holds a %hi() part:
# addiu, the loads, the stores, lwc1/lwc2, swc1/swc2
LO16_OPS = {0x09, 0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x28, 0x29, 0x2A, 0x2B, 0x2E, 0x31, 0x32, 0x39, 0x3A}
LOADS = {0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26}
# Two placements of one module sit in different load slots.  Outside a pair of same-layout native modules a base
# shift smaller than this is neighbouring code of one image, where a target moved by the same amount is another
# object, so it is not accepted as a relink.
MIN_BASE_SHIFT = 0x1000
# Bytes of a shifted data target compared between the two images.
DATA_WINDOW = 16
# at, v0-v1, a0-a3, t0-t9, ra: what a call may change
CALL_CLOBBERED = frozenset([*range(1, 16), 24, 25, 31])


def written(w):
    """General registers instruction w writes ($zero never)."""
    op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
    out = set()
    if op == 0:
        # jr, syscall, break, mthi, mtlo, mult(u), div(u) write no general register
        if w & 0x3F not in (0x08, 0x0C, 0x0D, 0x11, 0x13, 0x18, 0x19, 0x1A, 0x1B):
            out.add(rd)
    elif op == 1:
        if rt in (0x10, 0x11):  # bltzal, bgezal
            out.add(31)
    elif op == 3:
        out.add(31)
    elif 0x08 <= op <= 0x0F or op in LOADS:
        out.add(rt)
    elif op in (0x10, 0x12) and rs in (0, 2):  # mfc0/cfc0, mfc2/cfc2
        out.add(rt)
    out.discard(0)
    return out


def is_call(w):
    op = w >> 26
    return op == 3 or (op == 0 and w & 0x3F == 0x09) or (op == 1 and (w >> 16) & 31 in (0x10, 0x11))


def jump_target(w, k, start):
    return ((start + 4 * k + 4) & 0xF0000000) | ((w & 0x03FFFFFF) << 2)


def branch_index(w, k, n, start):
    """Word index a conditional branch or a J within the body at word k goes to, else None."""
    op = w >> 26
    if op in (1, 4, 5, 6, 7) or (op in (0x10, 0x11, 0x12, 0x13) and (w >> 21) & 31 == 8):
        imm = w & 0xFFFF
        t = k + 1 + (imm - 0x10000 if imm & 0x8000 else imm)
        return t if 0 <= t < n else None
    if op == 2:
        off = jump_target(w, k, start) - start
        return off // 4 if 0 <= off < 4 * n and not off % 4 else None
    return None


def ends_block(w):
    op = w >> 26
    return op in (1, 2, 3, 4, 5, 6, 7) or (op == 0 and w & 0x3F in (0x08, 0x09)) or \
        (op in (0x10, 0x11, 0x12, 0x13) and (w >> 21) & 31 == 8)


def hi_sources(words, start):
    """Per word index, {register: frozenset of lui word indices whose %hi part it may hold} before the word runs.

    A forward dataflow over the body's blocks: block leaders are word 0, every branch or own-body jump target and
    the word after each control transfer's delay slot.  A lui sets its register; an addu of a register holding a
    %hi part with one that holds none keeps the part (an indexed %lo access); any other write ends it; a call
    ends it in the caller-saved registers once its delay slot has run.  A block no branch reaches (a switch case
    reached through a jump table) starts from what the registers held at any `jr` other than `jr $ra`."""
    n = len(words)
    leaders = {0}
    for k, w in enumerate(words):
        if ends_block(w):
            if k + 2 < n:
                leaders.add(k + 2)
            t = branch_index(w, k, n, start)
            if t is not None:
                leaders.add(t)
    leaders = sorted(leaders)
    blocks = [(s, leaders[i + 1] if i + 1 < len(leaders) else n) for i, s in enumerate(leaders)]
    block_of = {s: i for i, (s, _) in enumerate(blocks)}
    succ, jr_blocks = [], []
    for i, (s, e) in enumerate(blocks):
        out, falls = set(), True
        c = e - 2
        if c >= s and ends_block(words[c]):
            w = words[c]
            op = w >> 26
            t = branch_index(w, c, n, start)
            if t is not None:
                out.add(block_of[t])
            if op == 2 or (op == 4 and (w >> 16) & 0x3FF == 0):     # j, b (beq $zero, $zero)
                falls = False
            elif op == 0 and w & 0x3F == 0x08:                      # jr
                falls = False
                if (w >> 21) & 31 != 31:
                    jr_blocks.append(i)
        if falls and e < n:
            out.add(block_of[e])
        succ.append(out)
    reached = {0} | {j for out in succ for j in out}

    def step(state, k):
        w = words[k]
        op, rs, rt, rd = w >> 26, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31
        carried = None
        if op == 0 and w & 0x3F == 0x21 and (rs in state) != (rt in state):
            carried = state[rs] if rs in state else state[rt]
        state = {r: v for r, v in state.items() if r not in written(w)}
        if op == LUI and rt:
            state[rt] = frozenset([k])
        elif carried is not None and rd:
            state[rd] = carried
        if k and is_call(words[k - 1]):
            state = {r: v for r, v in state.items() if r not in CALL_CLOBBERED}
        return state

    def meet(a, b):
        out = dict(a)
        for r, v in b.items():
            out[r] = out.get(r, frozenset()) | v
        return out

    entry = [None] * len(blocks)
    entry[0] = {}
    before = {}
    changed = True
    while changed:
        changed = False
        exits = [None] * len(blocks)
        for i, (s, e) in enumerate(blocks):
            if entry[i] is None:
                continue
            state = entry[i]
            for k in range(s, e):
                before[k] = state
                state = step(state, k)
            exits[i] = state
            for j in succ[i]:
                merged = state if entry[j] is None else meet(entry[j], state)
                if merged != entry[j]:
                    entry[j], changed = merged, True
        at_jr = {}
        for i in jr_blocks:
            if exits[i] is not None:
                at_jr = meet(at_jr, exits[i])
        for i in range(1, len(blocks)):
            if i not in reached and jr_blocks:
                merged = meet(entry[i] or {}, at_jr)
                if merged != entry[i]:
                    entry[i], changed = merged, True
    return before


def _sext(x):
    return x - 0x10000 if x & 0x8000 else x


def relocations(a_words, b_words, start_a, start_b):
    """(problems, pairs) for two bodies that are one instruction stream apart from relocated fields.

    pairs are (kind, word index, canonical target, copy target): 'jump' for a J/JAL leaving the body's own
    extent, 'hilo' for the address a lui and a %lo use of its register form; equal pairs too (the one-to-one
    check needs them).  A differing word that is not a relocated field, or a differing lui no %lo use reads, is
    a problem."""
    if len(a_words) != len(b_words):
        return ['size %d != %d' % (4 * len(a_words), 4 * len(b_words))], []
    size = 4 * len(a_words)
    problems, pairs, used = [], [], set()
    sources = hi_sources(a_words, start_a)
    for k, (a, b) in enumerate(zip(a_words, b_words)):
        op = a >> 26
        if op in (2, 3) and b >> 26 == op:
            ta, tb = jump_target(a, k, start_a), jump_target(b, k, start_b)
            if not (ta - start_a == tb - start_b and 0 <= ta - start_a < size):
                pairs.append(('jump', k, ta, tb))
            continue
        fields_equal = a >> 16 == b >> 16
        luis = sources.get(k, {}).get((a >> 21) & 31) if op in LO16_OPS else None
        if luis and fields_equal:
            for j in sorted(luis):
                used.add(j)
                ta = (((a_words[j] & 0xFFFF) << 16) + _sext(a & 0xFFFF)) & 0xFFFFFFFF
                tb = (((b_words[j] & 0xFFFF) << 16) + _sext(b & 0xFFFF)) & 0xFFFFFFFF
                pairs.append(('hilo', k, ta, tb))
        elif a != b and not (op == LUI and fields_equal):
            problems.append('word %d: %08x != %08x is not a relocated field' % (k, a, b))
    for j, (a, b) in enumerate(zip(a_words, b_words)):
        if a >> 26 == LUI and a != b and j not in used:
            problems.append('word %d: lui %08x != %08x has no %%lo use' % (j, a, b))
    return problems, pairs


def judge(pairs, start_a, start_b, size, same_symbol, is_code, shift=None, shifted=None):
    """Problems of one copy's relocation pairs (the rules in the module docstring).

    same_symbol(kind, a, b): one name at both addresses ('code' or 'data'), tried only where the base shift does
    not apply to the pair (the shift rule compares the target's bytes, a name does not); is_code(kind, a, b): the pair is a
    code target; shift: the base delta when Rows.module_shift allows one, else None; shifted(code, a, b): problems
    unless the copy's image holds at b what the canonical's holds at a (Rows.shifted_target)."""
    problems, forward, backward = [], {}, {}
    for kind, k, ta, tb in pairs:
        if forward.setdefault(ta, tb) != tb or backward.setdefault(tb, ta) != ta:
            problems.append('word %d: %08x -> %08x is not one-to-one (%08x -> %08x, %08x -> %08x)'
                            % (k, ta, tb, ta, forward[ta], backward[tb], tb))
            continue
        if ta == tb or (0 <= ta - start_a < size and tb - start_b == ta - start_a):
            continue
        code = is_code(kind, ta, tb)
        if shift is not None and tb - ta == shift:
            # The exact rule first: the target moved with the base, and its bytes are compared.
            bad = shifted(code, ta, tb) if shifted else []
            if not bad:
                continue
            problems.append('word %d: %s %08x -> %08x moves with the base delta but %s'
                            % (k, 'code' if code else 'data', ta, tb, bad[0]))
        elif same_symbol('code' if code else 'data', ta, tb):
            continue
        elif shift is not None:
            problems.append('word %d: %s %08x -> %08x shifts by %+#x, not the base delta %+#x'
                            % (k, 'code' if code else 'data', ta, tb, tb - ta, shift))
        else:
            problems.append('word %d: %s %08x -> %08x is not one %s by name and no base shift applies (one load image, '
                            'or a delta below %#x)' % (k, 'code' if code else 'data', ta, tb,
                                                      'function' if code else 'symbol', MIN_BASE_SHIFT))
    return problems


class Rows:
    def __init__(self, root):
        self.root = root
        self.rows = {}
        for line in (root / 'ledger/rows.jsonl').read_text().splitlines():
            if line.strip():
                row = json.loads(line)
                self.rows.setdefault(row.get('true_name'), []).append(row)
        self.paths = {}
        for line in (root / 'ledger/layout.jsonl').read_text().splitlines():
            if line.strip():
                row = json.loads(line)
                self.paths[row['id']] = row['path']
        self.members = {}
        self.module_of = {}      # member id -> (module key, member index)
        self.layouts = {}        # module key -> (layout, member ids): layout = (offset, size, body offset) per member
        modules = root / 'config/overlays/modules.json'
        if modules.is_file():
            for number, m in enumerate(json.loads(modules.read_text())['modules']):
                key = m.get('key', '#%d' % number)
                for index, a in enumerate(m['members']):
                    self.members[a['id']] = a
                    self.module_of[a['id']] = (key, index)
                if m['members'] and all('function' in a for a in m['members']):
                    first = int(m['members'][0]['function'][5:], 16)
                    self.layouts[key] = (
                        tuple((int(a['function'][5:], 16) - first, a['size'], a.get('body_offset', 0))
                              for a in m['members']),
                        [a['id'] for a in m['members']])
        self.texts = {}
        self.placed = {}
        for path in sorted((root / 'config/link').glob('*/*.json')):
            for entry in json.loads(path.read_text()).get('entries', []):
                if 'tu' in entry and entry.get('row') != entry.get('home'):
                    self.placed.setdefault(entry['tu'], set()).add(entry['home'])
        self.names = {}
        self.name_rows = {}      # old name -> number of config/names.tsv rows for it
        names = root / 'config/names.tsv'
        for raw in (names.read_text().splitlines() if names.is_file() else []):
            cols = raw.split('#', 1)[0].split('\t')
            if len(cols) >= 3 and cols[1].strip() and cols[2].strip():
                self.names.setdefault(cols[1].strip(), set()).add(cols[2].strip())
                self.name_rows[cols[1].strip()] = self.name_rows.get(cols[1].strip(), 0) + 1
        self.by_id = {r['id']: r for rows in self.rows.values() for r in rows}
        self.symbols = {}        # (kind, address) -> names config/names.tsv gives it; kind 'code' or 'data'
        self.symbol_rows = {}    # (kind, address) -> number of config/names.tsv rows at it
        for old, new in self.names.items():
            m = re.fullmatch(r'(func|D)_([0-9A-Fa-f]{8})', old)
            if m:
                key = ('code' if m[1] == 'func' else 'data', int(m[2], 16))
                self.symbols.setdefault(key, set()).update(new)
                self.symbol_rows[key] = self.name_rows[old]
        self._at = None

    def text(self, path):
        if path not in self.texts:
            p = self.root / path
            self.texts[path] = strip_comments(p.read_text(errors='replace')) if p.is_file() else ''
        return self.texts[path]

    def find(self, address, name):
        """(row, path) of the one row at address whose source defines name (a native member whose body starts
        past a data prefix is found by its function address)."""
        rows = list(self.rows.get(address, []))
        rows += [self.by_id[i] for i, m in self.members.items()
                 if m.get('function') == address and i in self.by_id and self.by_id[i] not in rows]
        hits = [(r, self.paths.get(r['id']) or (self.members.get(r['id']) or {}).get('source')) for r in rows]
        hits = [(r, p) for r, p in hits if p and defines(self.text(p), name)]
        return hits

    def placed_users(self, path, name):
        """Placed functions of the TU at path (link-list entries other than their home) that are, or reference, name."""
        text = self.text(path)
        hits = []
        for home in sorted(self.placed.get(path, ())):
            row = self.by_id.get(home)
            if row is None:
                continue
            for fn in sorted((self.names.get(row.get("true_name"), set()) | {row.get("true_name")}) - {None}):
                body = definition(text, fn)
                if body is not None and (fn == name or re.search(r'\b' + re.escape(name) + r'\b', body)):
                    hits.append(f'{home} ({fn})')
                    break
        return hits

    def start(self, row):
        """Runtime address of the row's body (a native member's function, else the row's true name)."""
        if 'start' in row:
            return row['start']
        member = self.members.get(row['id']) or {}
        return int(member.get('function', row['true_name'])[5:], 16)

    def home(self, row):
        """The row whose image a row lies in (itself, or for a mapped row the row it was mapped from)."""
        return self.by_id.get(row.get('image_of'), row)

    def function_at(self, row, address):
        """The row of the function that starts at address in the row's image, or None: the row whose body lies at
        the file offset the image puts address at (the image read as one load at the row's base)."""
        if self._at is None:
            self._at = {}
            for r in self.by_id.values():
                if re.fullmatch(r'func_[0-9A-Fa-f]{8}', r.get('true_name') or '') and 'foff' in r:
                    self._at.setdefault((r['container'], self.body_foff(r), self.start(r)), []).append(r)
        hits = self._at.get((row['container'], self.body_foff(row) + address - self.start(row), address), [])
        return hits[0] if hits else None

    def defines_name(self, row, name):
        """True when the source of the row's function defines name."""
        path = self.paths.get(row['id']) or (self.members.get(row['id']) or {}).get('source')
        return bool(path) and defines(self.text(path), name)

    def same_symbol(self, kind, a, b, row_a=None, row_b=None):
        """One symbol in both images. config/names.tsv keys a name by address alone, but an address is a
        different function in each image, so a code name counts only where the function the canonical's image
        (row_a) holds at a and the function the copy's image (row_b) holds at b each have a source that defines
        it. A data name has no function to resolve, so it counts only where each address carries exactly one
        names.tsv row (an address with several names is ambiguous) and the two rows give the same name."""
        shared = self.symbols.get((kind, a), set()) & self.symbols.get((kind, b), set())
        if not shared:
            return False
        if kind == 'data':
            return self.symbol_rows.get((kind, a)) == 1 and self.symbol_rows.get((kind, b)) == 1
        if row_a is None or row_b is None:
            return False
        fa, fb = self.function_at(row_a, a), self.function_at(row_b, b)
        return fa is not None and fb is not None and any(
            self.defines_name(fa, n) and self.defines_name(fb, n) for n in shared)

    def module_shift(self, row_a, row_b):
        """The base delta (the copy's address minus the canonical's) when the copy's image can be the canonical's
        linked at another base, else None: the rows are members at one index of two native modules with one
        layout, or they lie in different load images (the file does not hold the copy where the canonical's
        image would put its address) and the delta is at least MIN_BASE_SHIFT."""
        delta = self.start(row_b) - self.start(row_a)
        a, b = self.module_of.get(row_a['id']), self.module_of.get(row_b['id'])
        if a and b and a[1] == b[1] and a[0] != b[0] and a[0] in self.layouts and b[0] in self.layouts \
                and self.layouts[a[0]][0] == self.layouts[b[0]][0]:
            return delta
        one_load = self.body_foff(row_b) - self.body_foff(row_a) == delta and row_a['container'] == row_b['container']
        if not one_load and abs(delta) >= MIN_BASE_SHIFT:
            return delta
        return None

    def body_foff(self, row):
        member = self.members.get(row['id'])
        return member['foff'] + member.get('body_offset', 0) if member else row['foff']

    def mapped(self, row, address, size):
        """A row for the `size` bytes at `address` in the row's image, read as one load at the row's base."""
        return dict(id='@%s+%08x' % (self.home(row)['id'], address), container=row['container'], size=size,
                    foff=self.body_foff(row) + address - self.start(row), start=address,
                    image_of=self.home(row)['id'], true_name='func_%08X' % address)

    def read(self, container, foff, size):
        path = self.root / CONTAINER_DIR / CONTAINERS[container]
        if foff < 0 or foff + size > path.stat().st_size:
            return None
        with path.open('rb') as f:
            f.seek(foff)
            return f.read(size)

    def shifted_target(self, row_a, row_b, code, ta, tb, shift, memo):
        """Problems unless the copy's image holds at tb what the canonical's holds at ta, moved by shift.

        A code target must be one function by this check (a target the ledger does not list as a function
        start is read from the image at the other side's size); a data target's DATA_WINDOW bytes must be equal
        word for word, or differ by exactly the delta (a pointer the relink moved)."""
        if code:
            fa, fb = self.function_at(row_a, ta), self.function_at(row_b, tb)
            if fa is None and fb is None:
                return ['neither target is a known function start']
            fa = fa or self.mapped(row_a, ta, self.size(fb))
            fb = fb or self.mapped(row_b, tb, self.size(fa))
            bad = compare(self.words(fa) or [], self.words(fb) or [], ta, tb)
            return self.relocated(fa, fb, memo=memo) if bad else []
        da = self.read(row_a['container'], self.body_foff(row_a) + (ta & ~3) - self.start(row_a), DATA_WINDOW)
        db = self.read(row_b['container'], self.body_foff(row_b) + (tb & ~3) - self.start(row_b), DATA_WINDOW)
        if da is None or db is None:
            return ['the data lies outside the container']
        for k in range(0, DATA_WINDOW, 4):
            x, y = (int.from_bytes(d[k:k + 4], 'little') for d in (da, db))
            if x != y and (y - x) & 0xFFFFFFFF != shift & 0xFFFFFFFF:
                return ['the data differs (%08x: %08x, %08x: %08x)' % ((ta & ~3) + k, x, (tb & ~3) + k, y)]
        return []

    def relocated(self, row_a, row_b, start_a=None, start_b=None, memo=None):
        """Problems unless the two rows' retail words are one function apart from corresponding relocations."""
        memo = {} if memo is None else memo
        key = (row_a['id'], row_b['id'])
        if key in memo:
            return memo[key] or []          # None: being checked further up (a cycle passes)
        memo[key] = None
        start_a = self.start(row_a) if start_a is None else start_a
        start_b = self.start(row_b) if start_b is None else start_b
        a_words, b_words = self.words(row_a), self.words(row_b)
        if a_words is None or b_words is None:
            problems, pairs = ['the body lies outside the container'], []
        else:
            problems, pairs = relocations(a_words, b_words, start_a, start_b)
        if not problems:
            shift = self.module_shift(row_a, row_b)
            problems = judge(pairs, start_a, start_b, 4 * len(a_words),
                             lambda kind, ta, tb: self.same_symbol(kind, ta, tb, row_a, row_b),
                             lambda kind, ta, tb: kind == 'jump' or self.function_at(row_a, ta) is not None
                             or self.function_at(row_b, tb) is not None, shift,
                             lambda code, ta, tb: self.shifted_target(row_a, row_b, code, ta, tb, shift, memo))
        memo[key] = problems
        return problems

    def size(self, row):
        member = self.members.get(row['id'])
        return (member['size'] if member else row['size']) - (member.get('body_offset', 0) if member else 0)

    def words(self, row):
        """The row's retail words (None when the row lies outside its container)."""
        member = self.members.get(row['id'])
        offset = member.get('body_offset', 0) if member else 0
        foff = (member['foff'] if member else row['foff']) + offset
        size = (member['size'] if member else row['size']) - offset
        data = self.read(row['container'], foff, size)
        return None if data is None else list(struct.unpack('<%dI' % (len(data) // 4), data))


def malformed_rows(path):
    """Rows whose evidence starts with `copy_of=` but is not a record name_inputs.COPY_OF accepts.

    The gate and lane readers skip every row that starts with `copy_of=`, while the build's name table
    (name_inputs.table) treats a row COPY_OF does not match as an ordinary row that rebinds its name, so such a
    row would be read two ways."""
    pattern = _name_inputs().COPY_OF
    out = []
    lines = Path(path).read_text().splitlines() if Path(path).is_file() else []
    for number, raw in enumerate(lines, 1):
        cols = raw.split('#', 1)[0].split('\t')
        if len(cols) >= 4 and cols[3].strip().startswith('copy_of=') and not pattern.match(cols[3].strip()):
            out.append(f'config/names.tsv:{number}: malformed copy_of record (want copy_of=0x<8 uppercase hex>): '
                       + cols[3].strip()[:40])
    return out


def missing_containers(root):
    return sorted(c for c in CONTAINERS.values() if not (Path(root) / CONTAINER_DIR / c).is_file())


def check(root=ROOT, notes=None, details=None):
    """(report, problems) for every recorded family; report maps name -> [(address, path, bytes)].

    Without the retail containers the word comparison is skipped and, when notes is a list, the skip is appended
    to it; it is not a problem.  The structural checks run either way.  When details is a dict, every copy the
    relocation rule accepts (its words are not equal) maps (name, address) to a description."""
    root = Path(root)
    malformed = malformed_rows(root / 'config/names.tsv')
    families = _name_inputs().copies(root / 'config/names.tsv')
    if not families:
        return {}, malformed
    missing = missing_containers(root)
    if missing and notes is not None:
        notes.append(f'{SKIPPED} ({", ".join(missing)}); word comparison not run for {len(families)} families')
    rows = Rows(root)
    problems, report = list(malformed), {}
    for name, family in sorted(families.items()):
        found = {}
        for address in [family['canonical'], *family['copies']]:
            hits = rows.find(address, name)
            if len(hits) != 1:
                problems.append(f'{name}: {len(hits)} rows at {address} define it '
                                f'({", ".join(p for _, p in hits) or "none"})')
                continue
            found[address] = hits[0]
        if family['canonical'] not in found:
            continue
        base_row, base_path = found[family['canonical']]
        base = None if missing else rows.words(base_row)
        size = 4 * len(base) if base is not None else rows.size(base_row)
        start = int(family['canonical'][5:], 16)
        report[name] = [(family['canonical'], base_path, size)]
        for address in family['copies']:
            if address not in found:
                continue
            row, path = found[address]
            if row['id'] not in rows.members:
                problems.append(f'{name}: {address} ({path}) is not a native module entry; only the native module '
                                'gate binds a family name to a copy\'s own address')
            users = rows.placed_users(path, name)
            if users:
                problems.append(f'{name}: {address} ({path}) is also placed through config/link, where the name binds '
                                f'to {family["canonical"]}: ' + ', '.join(users[:3]))
            report[name].append((address, path, size))
            if base is None:
                continue
            words = rows.words(row)
            bad = compare(base, words, start, int(address[5:], 16))
            if bad:
                bad = rows.relocated(base_row, row, start, int(address[5:], 16))
                if not bad and details is not None:
                    shift = rows.module_shift(base_row, row)
                    details[(name, address)] = 'words differing in relocated fields: %d%s' % (
                        sum(a != b for a, b in zip(base, words)),
                        '' if shift is None else ', base delta %+#x' % shift)
            problems += [f'{name}: {address} ({path}) differs from {family["canonical"]}: {p}' for p in bad[:3]]
    return report, problems


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--root', type=Path, default=ROOT)
    parser.add_argument('--pair', nargs=2, metavar=('CANONICAL_ROW', 'COPY_ROW'),
                        help='compare two ledger/rows.jsonl rows (no names.tsv record needed); rc 1 unless they '
                             'are one function')
    args = parser.parse_args(argv)
    if args.pair:
        rows = Rows(args.root.resolve())
        a, b = (rows.by_id[i] for i in args.pair)
        bad = compare(rows.words(a), rows.words(b), rows.start(a), rows.start(b))
        bad = bad and rows.relocated(a, b)
        print('\n'.join(bad) if bad else 'one function')
        return 1 if bad else 0
    notes, details = [], {}
    report, problems = check(args.root.resolve(), notes, details)
    for name, members in report.items():
        print(name + ': ' + ', '.join(f'{a} {p}' + (f' [{details[(name, a)]}]' if (name, a) in details else '')
                                      for a, p, _ in members) + f' ({members[0][2]} bytes)')
    for note in notes:
        print('placed copies ' + note)
    for p in problems:
        print('PLACED COPY ' + p)
    print(f'placed copies: {len(report)} families, {sum(len(v) - 1 for v in report.values())} copies, '
          f'{len(problems)} problems')
    return 1 if problems else 0


if __name__ == '__main__':
    sys.exit(main())
