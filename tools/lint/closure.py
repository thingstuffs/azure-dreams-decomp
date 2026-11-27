#!/usr/bin/env python3
"""Ownership check: every byte of the game's program files and decoded images is compiled C, or sits in one
declared line of config/closure/, or is a run of zero bytes. See docs/CLOSURE.md.

    python3 tools/lint/closure.py landing|batch|report [--out DIR]

`landing` compares the lines with those of HEAD, `batch` with those of the root commit, `report` with HEAD and
never exits 1. There is no other argument: no flag accepts, tightens, rewrites or baselines anything, and no base
is named by the caller (it is read from git).

Exit codes: 0 no refusal; 1 a refusal (a byte with no owner, an open detector hit, a line that fails its test);
2 an input is missing, stale or malformed (a refusal to look, not a finding).

The tool only reads. Its output holds offsets, sizes, classes and hashes, never bytes.
"""
import argparse
import bisect
import hashlib
import json
import re
import struct
import subprocess
import sys
import time
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOL_ROOT = HERE.parents[1]
sys.path.insert(0, str(HERE))
sys.path.insert(0, str(TOOL_ROOT))
import closure_detect as D  # noqa: E402
import closure_v6 as V6  # noqa: E402

# The tool reports and never fails a landing until the owner flips this in a reviewed one-line change.
GATING = False

FILES = ('main', 'town', 'dungeon', 'ovmovie', 'slus')
DISC_PATHS = {'main': 'work/disc/containers/MAIN_MAIN.BIN', 'town': 'work/disc/containers/TOWN_TOWN.BIN',
              'dungeon': 'work/disc/containers/DUNGEON_DUNGEON.BIN', 'ovmovie': 'work/disc/containers/OVMOVIE.BIN',
              'slus': 'baserom/slus_006.14'}
LINE_DIR = 'config/closure'
SCHEMA = 'closure.v1'
OWN_CLASSES = ('own:code', 'own:vendor', 'own:stream', 'own:data', 'own:padding', 'own:untyped')
VERDICTS = {'D1': ('data', 'other_program', 'code_in_c_data'), 'D2': ('data', 'other_program', 'code_in_c_data'),
            'D4': ('data', 'other_program', 'code_in_c_data'), 'D5': ('data', 'other_program', 'code_in_c_data'),
            'D3': ('cross_image_call', 'stale_relocation', 'midbody_entry'), 'D6': ('not_code_stream',),
            'D7': ('older_build_same_calls',)}
DATA_LABELS = ('proven_data', 'noncode_typing_pending', 'padding_leftover')
PAGE = 12
MAX_LIST = 60


class InputError(Exception):
    """an input is missing, stale or malformed (exit 2)"""


def hx(n):
    return '0x%X' % n


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def total(iv):
    return sum(b - a for a, b in iv)


class Index:
    """Merged sorted intervals with point and clip queries."""

    def __init__(self, iv):
        self.v = D.merge(iv)
        self.s = [a for a, _ in self.v]

    def has(self, x):
        i = bisect.bisect_right(self.s, x) - 1
        return i >= 0 and x < self.v[i][1]

    def clip(self, a, b):
        i = max(0, bisect.bisect_right(self.s, a) - 1)
        out = []
        while i < len(self.v) and self.v[i][0] < b:
            x, y = self.v[i]
            if y > a:
                out.append([max(a, x), min(b, y)])
            i += 1
        return out

    def bytes(self, a, b):
        return total(self.clip(a, b))


def count_cover(intervals):
    """(union, bytes covered two or more times) of a list of [a, b)."""
    events = []
    for a, b in intervals:
        events.append((a, 1))
        events.append((b, -1))
    events.sort()
    union, multi, depth, last = [], [], 0, 0
    for pos, delta in events:
        if depth >= 1 and pos > last:
            union.append([last, pos])
            if depth >= 2:
                multi.append([last, pos])
        depth += delta
        last = pos
    return D.merge(union), D.merge(multi)


ZERO_LEAST = 16
ZERO_RUN = re.compile(rb'\x00{%d,}' % ZERO_LEAST)


def zero_runs_fast(data, least=ZERO_LEAST):
    """Automatic zero: maximal runs of zero bytes, trimmed inward to word boundaries, at least `least` bytes long.
    (A shorter run, or a zero byte inside a nonzero word, is an ordinary byte that needs an owner.)"""
    out = []
    for m in ZERO_RUN.finditer(data):
        a, b = (m.start() + 3) & ~3, m.end() & ~3
        if b - a >= least:
            out.append([a, b])
    return out


def pointer_kinds(unit, a, b):
    """(first word offset, kinds) of the words of [a, b): 'p' a word that is the load address (cached or not) of a
    compiled function start of this unit, 'z' a zero word, '-' any other."""
    a, b = (a + 3) & ~3, b & ~3
    if b <= a:
        return a, []
    kinds = []
    for w in struct.unpack_from('<%dI' % ((b - a) // 4), unit.data, a):
        if w == 0:
            kinds.append('z')
        elif w & 3 == 0 and w >> 29 in (4, 5) and ((w & 0x1fffffff) | 0x80000000) in unit.vma_starts:
            kinds.append('p')
        else:
            kinds.append('-')
    return a, kinds


def pointer_words(unit, a, b):
    """Intervals of [a, b) that are pointer words to function starts of the unit, with the zero words that touch
    one (a header of function pointers and a terminating zero word)."""
    base, kinds = pointer_kinds(unit, a, b)
    out = []
    n = len(kinds)
    for i, k in enumerate(kinds):
        if k == 'p' or (k == 'z' and ((i and kinds[i - 1] == 'p') or (i + 1 < n and kinds[i + 1] == 'p'))):
            out.append([base + 4 * i, base + 4 * i + 4])
    return D.merge(out)


def pointer_edges(unit, a, b):
    """The leading and the trailing run of [a, b) made only of pointer words and zero words, when it holds at least
    one pointer word: the part of a code-labelled run that is a header of function pointers."""
    base, kinds = pointer_kinds(unit, a, b)
    n = len(kinds)
    out = []
    lead = 0
    while lead < n and kinds[lead] != '-':
        lead += 1
    if 'p' in kinds[:lead]:
        out.append([base, base + 4 * lead])
    trail = n
    while trail > lead and kinds[trail - 1] != '-':
        trail -= 1
    if trail < n and 'p' in kinds[trail:]:
        out.append([base + 4 * trail, base + 4 * n])
    return out


# ------------------------------------------------------------------ lines
class Line:
    __slots__ = ('unit', 'start', 'end', 'cls', 'evidence', 'sha', 'where', 'layer', 'window')

    def __init__(self, unit, start, end, cls, evidence, sha, where, window=None):
        self.unit, self.start, self.end, self.cls, self.evidence, self.sha, self.where = (
            unit, start, end, cls, evidence, sha, where)
        self.window = window      # (offset, length) of the digest's window for an extent under DIGEST_LEAST bytes
        self.layer = 'own' if cls.startswith('own:') else 'region' if cls.startswith('region:') else 'ack'

    def key(self):
        return (self.unit, self.start, self.end, self.cls, self.evidence, self.sha)

    def digest_text(self):
        if self.window is None:
            return self.sha
        return 'w%s+%s:%s' % (hx(self.window[0]), hx(self.window[1]), self.sha)

    def text(self):
        return '%s\t%s\t%s\t%s\t%s' % (hx(self.start), hx(self.end), self.cls, self.evidence, self.digest_text())


# A line never carries a digest of fewer than DIGEST_LEAST bytes of a program file. An extent that long or longer
# carries the sha256 of its own bytes. A shorter extent carries `w<offset>+<length>:<sha256>`: the digest of an
# enclosing window of at least DIGEST_LEAST bytes inside the same file, recomputed by the check. The window binds the
# bytes around the extent (a change of any byte in it is detected, the short extent's own bytes included); it does not
# bind where inside the window the extent lies.
DIGEST_LEAST = 16
DIGEST_RX = re.compile(r'^(?:([0-9a-f]{64})|w(0x[0-9A-Fa-f]+)\+(0x[0-9A-Fa-f]+):([0-9a-f]{64}))$')


def enclosing_window(start, end, size):
    """(offset, length) of the smallest 16-aligned window of at least DIGEST_LEAST bytes that holds [start, end) and
    lies inside [0, size)."""
    offset = start & ~(DIGEST_LEAST - 1)
    length = max(DIGEST_LEAST, -(-(end - offset) // DIGEST_LEAST) * DIGEST_LEAST)
    if offset + length > size:
        offset = size - length
    return offset, length


def line_digest(data, start, end):
    """The digest column a line over data[start:end] carries."""
    if end - start >= DIGEST_LEAST:
        return sha256(data[start:end])
    offset, length = enclosing_window(start, end, len(data))
    return 'w%s+%s:%s' % (hx(offset), hx(length), sha256(data[offset:offset + length]))


def digest_matches(data, ln):
    """True when the bytes the line's digest covers still hash to it."""
    if ln.window is None:
        return sha256(data[ln.start:ln.end]) == ln.sha
    return sha256(data[ln.window[0]:ln.window[0] + ln.window[1]]) == ln.sha


CLASS_RX = re.compile(r'^(?:own:(?:code|vendor|data|padding|untyped)|own:stream:[A-Za-z0-9_/]+|'
                      r'region:other:[A-Za-z0-9_]+|region:stale:[a-z]+:\d+|region:unreached:[A-Za-z0-9_]+|'
                      r'ack:D[1-7]:[a-z_]+)$')


def unit_key(name):
    """Unit key of a line file stem: a program file, or `decoded_<family>_<image>` for a decoded image."""
    return name if name in FILES else 'decoded:' + name[len('decoded_'):].replace('_', '/', 1) if name.startswith('decoded_') else None


def parse_lines(text, unit, where, findings):
    out = []
    seen_schema = False
    for number, raw in enumerate(text.splitlines(), 1):
        if not raw.strip():
            continue
        if raw.startswith('#'):
            if 'schema ' + SCHEMA in raw:
                seen_schema = True
            continue
        cols = raw.split('\t')
        loc = '%s:%d' % (where, number)
        if len(cols) != 5:
            findings.append(('schema', '%s: %d columns, 5 expected' % (loc, len(cols))))
            continue
        try:
            start, end = int(cols[0], 16), int(cols[1], 16)
        except ValueError:
            findings.append(('schema', '%s: offsets are not hex' % loc))
            continue
        match = DIGEST_RX.match(cols[4])
        if not CLASS_RX.match(cols[2]) or start >= end or not match:
            findings.append(('schema', '%s: bad class, extent or hash' % loc))
            continue
        window = None
        if match.group(1) is None:
            window = (int(match.group(2), 16), int(match.group(3), 16))
            if (end - start >= DIGEST_LEAST or window[1] < DIGEST_LEAST
                    or not window[0] <= start or not end <= window[0] + window[1]):
                findings.append(('schema', '%s: a window digest is for an extent under %d bytes and the window of at '
                                 'least %d bytes must hold the extent' % (loc, DIGEST_LEAST, DIGEST_LEAST)))
                continue
        elif end - start < DIGEST_LEAST:
            findings.append(('schema', '%s: an extent under %d bytes carries no digest of its own bytes (use a window)'
                             % (loc, DIGEST_LEAST)))
            continue
        out.append(Line(unit, start, end, cols[2], cols[3], match.group(1) or match.group(4), loc, window))
    if not seen_schema:
        findings.append(('schema', '%s: no "# schema %s" line' % (where, SCHEMA)))
    for a, b in zip(out, out[1:]):
        if (b.start, b.end, b.cls) < (a.start, a.end, a.cls):
            findings.append(('order', '%s: lines are not sorted' % b.where))
            break
    return out


def work_label(text):
    try:
        import prepublish_scan as P
    except ImportError:  # the scan tool lives in tools/
        sys.path.insert(0, str(TOOL_ROOT / 'tools'))
        import prepublish_scan as P
    return bool(P.R_PROV_CS.search(text) or P.R_PROV_CI.search(text))


def evidence_ok(root, evidence, cache):
    path, _, key = evidence.partition('#')
    p = Path(path)
    if not path or p.is_absolute() or '..' in p.parts or path.startswith('work/') or '\t' in evidence:
        return 'evidence path is not a tracked repository path'
    target = root / p
    if not target.is_file():
        return 'evidence file does not exist'
    if key:
        if path not in cache:
            cache[path] = target.read_bytes()
        if key.encode() not in cache[path]:
            return 'evidence key not found in file'
    return None


# ------------------------------------------------------------------ the world
class Unit:
    """One program file or decoded image: bytes, compiled map, lines."""

    def __init__(self, key, data, kind='file'):
        self.key, self.data, self.kind, self.size = key, data, kind, len(data)
        self.zero_all = zero_runs_fast(data)
        self.c_code = self.c_data = self.c_asm = self.c_import = None
        self.funcs = []
        self.starts = set()
        self.allocations = []
        self.extents = []
        self.lines = []
        self.conflicts = []
        self.images = []
        self.chunk_deltas = []
        self.vma_starts = set()
        self.vma_extent = [1 << 40, 0]
        self.image_loaded = {}        # image -> {delta: (merged load ranges, their starts)}
        self.image_vma = {}           # image -> load address of its start
        self.image_vma_starts = {}    # image -> load addresses of its compiled function starts
        self.named = {}               # named exceptions: symbol -> file offset (the executable's main)
        self.members = Counter()      # images read from a link map, chunks split, chunks left whole
        self.table_clipped = []       # noload table bytes that overlapped compiled code and were clipped

def read_json(path):
    try:
        return json.loads(Path(path).read_text())
    except (OSError, ValueError) as exc:
        raise InputError('cannot read %s: %s' % (path, exc))


def load_proof(root):
    """The full make check receipt, its inputs hashes current. A scoped check file is never read."""
    path = root / 'build/check.json'
    if not path.is_file():
        raise InputError('no_full_proof: build/check.json is missing (a scoped proof writes scope-check.json)')
    try:
        sys.path.insert(0, str(TOOL_ROOT / 'tools'))
        from build.make_evidence import checked_receipt
        receipt = checked_receipt(root)
    except (ValueError, OSError, KeyError) as exc:
        raise InputError('no_full_proof: %s' % exc)
    return receipt


def load_disc(root):
    files = {}
    for line in (root / 'config/link_graph/files.000.jsonl').read_text().splitlines():
        rec = json.loads(line)
        files[rec['id']] = rec
    data = {}
    for fam in FILES:
        rec = files.get(fam)
        path = root / DISC_PATHS[fam]
        if rec is None or not path.is_file():
            raise InputError('program file missing: ' + fam)
        blob = path.read_bytes()
        if len(blob) != rec['size'] or hashlib.sha1(blob).hexdigest() != rec['sha1']:
            raise InputError('program file differs from its recorded identity: ' + fam)
        data[fam] = blob
    return data


def link_sections(root, image, origin):
    """Input sections per piece of an image's linker map (build/.state/link/<image>/image.map), or None when the
    link state is not there. The map is not bound by check.json; its linker script is (a stale link state is an
    input error), and each chunk's sections must tile exactly the code ranges of its cover list or the chunk stays
    whole (see split_members)."""
    base = root / 'build/.state/link' / image.replace('/', '_')
    if not (base / 'image.map').is_file():
        return None
    ld = base / 'image.ld'
    if ld.is_file() and origin.get('linker_script_sha256') and sha256(ld.read_bytes()) != origin['linker_script_sha256']:
        raise InputError('link state differs from the origin file of check.json: ' + image)
    sys.path.insert(0, str(TOOL_ROOT / 'tools'))
    from build import cover as cover_module
    return cover_module.piece_sections((base / 'image.map').read_text())


def split_members(ch, sections):
    """([[file offset, size]] of the compiled functions of one chunk, split) : the `.text.<name>` sections of the
    chunk's piece that lie wholly inside its code ranges, when they tile those ranges exactly; else the code ranges
    as the cover list gives them (a module object records one range for all its member functions)."""
    spans = [[c, c + n] for c, n in ch['code']]
    members = []
    for section, address, size, _path in sections or ():
        if size and section.startswith('.text.'):
            foff = ch['foff'] + address - ch['vma']
            if any(a <= foff and foff + size <= b for a, b in spans):
                members.append([foff, foff + size])
    if sections and members and D.merge(members) == D.merge(spans):
        return sorted(set((a, b - a) for a, b in members)), True
    return [tuple(x) for x in ch['code']], False


def load_cover(root, receipt, units):
    """C map: labels per file from the cover lists named by check.json, each origin file bound by its sha256."""
    bits = {fam: dict(code=[], data=[], tables=[], asm=[], imp=[], kinds=defaultdict(list)) for fam in units}
    for result in receipt['results']:
        image = result['image']
        fam = image.split('/')[0]
        if fam not in units:
            raise InputError('image of an unknown file: ' + image)
        origin_path = root / 'build/.state/origins' / (image.replace('/', '_') + '.json')
        if not origin_path.is_file():
            raise InputError('origin file missing: ' + image)
        blob = origin_path.read_bytes()
        if result.get('origin_sha256') != sha256(blob):
            raise InputError('origin file differs from check.json: ' + image)
        origin = json.loads(blob)
        cover = origin.get('cover')
        if not cover or cover.get('schema') != 'closure.cover.v1':
            raise InputError('origin file has no cover list (run make with the current build tools): ' + image)
        unit = units[fam]
        start, end = cover['start'], cover['start'] + cover['size']
        delta = None if cover.get('vma') is None else cover['vma'] - cover['start']
        unit.images.append((image, start, end, delta))
        if cover.get('vma') is not None:
            unit.image_vma[image] = cover['vma']
        pieces = link_sections(root, image, origin) if fam != 'slus' else None
        if pieces is not None:
            unit.members['images'] += 1
        loaded = defaultdict(list)
        starts_here = unit.image_vma_starts.setdefault(image, set())
        b = bits[fam]
        for index, ch in enumerate(cover['chunks']):
            a, e = ch['foff'], ch['foff'] + ch['size']
            if a < 0 or e > unit.size or ch['size'] <= 0:
                raise InputError('cover chunk outside its file: ' + image)
            kind = ch['class']
            if pieces is not None and ch['code'] and ch.get('origin') != 'noload_table':
                code, split = split_members(ch, pieces.get(index))
                unit.members['split' if split else 'whole'] += 1
            else:
                code = [tuple(x) for x in ch['code']]
            if ch.get('vma') is not None:
                unit.chunk_deltas.append((a, e, ch['vma'] - a))
                loaded[ch['vma'] - a].append([ch['vma'], ch['vma'] + ch['size']])
                if ch['class'] != 'import':
                    unit.vma_extent[0] = min(unit.vma_extent[0], ch['vma'])
                    unit.vma_extent[1] = max(unit.vma_extent[1], ch['vma'] + ch['size'])
                for c, n in code:
                    unit.vma_starts.add(ch['vma'] + c - a)
                    starts_here.add(ch['vma'] + c - a)
            if kind == 'c_data':
                spans = [[c, c + n] for c, n in code]
                if ch.get('origin') == 'noload_table':
                    b['tables'].append([a, e])
                else:
                    b['data'] += D.subtract([[a, e]], spans)
                b['code'] += spans
                for c, n in code:
                    unit.funcs.append((c, c + n))
                if code and ch.get('vma') is not None:
                    unit.allocations.append(D.Allocation(a, ch['vma'], ch['size'], start, end, image))
            elif kind == 'assembly':
                b['asm'].append([a, e])
                b['kinds'][ch.get('kind', 'assembly')].append([a, e])
            else:
                b['imp'].append([a, e])
        unit.image_loaded[image] = {d: (D.merge(iv), [x for x, _ in D.merge(iv)]) for d, iv in loaded.items()}
        if fam == 'slus':
            unit.named.update(slus_named(root, origin, cover))
    for fam, unit in units.items():
        b = bits[fam]
        code = D.merge(b['code'])
        # a noload table record carries the table's size rounded to 8 bytes and can run into the first word of the
        # next compiled function: the table stops at the compiled code
        tables = D.subtract(D.merge(b['tables']), code)
        unit.table_clipped = D.intersect(D.merge(b['tables']), code)
        data = D.merge(b['data'] + tables)
        unit.conflicts = D.intersect(code, data)
        unit.c_data = data
        unit.c_code = D.subtract(code, data)
        unit.c_asm = D.subtract(D.merge(b['asm']), D.merge(code + data))
        unit.c_import = D.merge(b['imp'])
        unit.asm_kinds = {k: D.subtract(D.merge(v), D.merge(code + data)) for k, v in b['kinds'].items()}
        unit.funcs = sorted(set(unit.funcs))
        unit.starts = {a for a, _ in unit.funcs}
        pages = defaultdict(set)
        for a, e, delta in unit.chunk_deltas:
            for page in range(a >> PAGE, ((e - 1) >> PAGE) + 1):
                pages[page].add(delta)
        unit.pages = pages


def slus_named(root, origin, cover):
    """Named exceptions of the executable: {'main': file offset of the game's `main`}. Read from the executable's
    linker map when its sha256 is the one the origin file names (the SDK startup entry always calls main)."""
    path = root / 'build_slus/build/slus_006.14.map'
    if not path.is_file() or not origin.get('map_sha256') or sha256(path.read_bytes()) != origin['map_sha256']:
        return {}
    sys.path.insert(0, str(TOOL_ROOT / 'tools'))
    from build import cover as cover_module
    for _o, _oa, _l, section, address, size, obj in cover_module.map_sections(path.read_text(), lambda name: True):
        if section == '.text.main' and size and obj.endswith('/src/main.o'):
            for ch in cover['chunks']:
                if ch.get('vma') == address:
                    return {'main': ch['foff']}
    return {}


def load_decoded(root, receipt):
    """Decoded images named by config/decoded: proof file bound by check.json, bytes by the proof's sha256."""
    out = {}
    bound = receipt.get('decoded', {})
    for manifest in sorted((root / 'config/decoded').glob('*.json')):
        doc = read_json(manifest)
        image = doc['image']
        proof_path = root / 'build/decoded' / image / 'proof.json'
        if not proof_path.is_file():
            raise InputError('decoded proof missing: ' + image)
        blob = proof_path.read_bytes()
        if bound.get(image) != sha256(blob):
            raise InputError('decoded proof differs from check.json: ' + image)
        proof = json.loads(blob)
        retail = root / 'build/decoded' / image / 'retail.bin'
        data = retail.read_bytes() if retail.is_file() else b''
        if sha256(data) != proof['sha256'] or len(data) != proof['size']:
            raise InputError('decoded bytes differ from their proof: ' + image)
        for rel, expected in proof.get('source_sha256', {}).items():
            p = root / rel
            if not p.is_file() or sha256(p.read_bytes()) != expected:
                raise InputError('decoded proof source is stale: ' + rel)
        unit = Unit('decoded:' + image, data, 'decoded')
        spans = [[f['offset'], f['offset'] + f['size']] for f in proof['functions'] if f.get('func_symbol')]
        unit.funcs = [tuple(s) for s in spans]
        unit.starts = {a for a, _ in spans}
        unit.c_code = D.merge(spans)
        # compiled C data of the image: a section of a compiled unit that the build found with exactly the registered
        # size; a data entry without that record (or from an older proof) stays unowned and is reported
        unit.c_data = D.merge([[d['offset'], d['offset'] + d['size']] for d in proof.get('data', ())
                               if d.get('compiled_section')])
        unit.c_asm = []
        unit.c_import = []
        unit.pages = {}
        unit.manifest = doc
        unit.proof = proof
        out[unit.key] = unit
    return out


RETAIL_RAM = (0x80010000, 0x80200000)
LOAD_KINDS = ('retail loader destination',)


def establishes_load(rec):
    """A load record is load evidence when it records a retail load (a validated loader record, which names its
    method and no placement kind, or a retail loader destination) at a base inside retail RAM. A record that says
    link evidence only, or a linked base only, or has a base outside the retail RAM (above it, or in the kernel
    area) is not."""
    kind = rec.get('placement_kind')
    if kind is not None and not any(kind.startswith(k) for k in LOAD_KINDS):
        return False
    base = rec.get('base')
    return base is None or RETAIL_RAM[0] <= base < RETAIL_RAM[1]


def load_regions(root, dropped=None):
    """Load regions with load evidence: (family, start, end) from the link documents that carry `load_evidence` and
    from the instance load records, keeping only records that establish a retail load (`establishes_load`). An image
    is not a load region because it is an image: whole-file views and banks that overlap foreign ranges carry no
    load evidence. Records and documents that are left out are appended to `dropped` when it is a list."""
    out = []
    records = {}
    rec_path = root / 'ledger/instance_load_regions.jsonl'
    if rec_path.is_file():
        for line in rec_path.read_text().splitlines():
            if line.strip():
                rec = json.loads(line)
                records[sha256(line.encode())] = rec
                if establishes_load(rec):
                    out.append((rec['container'], rec['foff'], rec['foff'] + rec['size']))
                elif dropped is not None:
                    dropped.append((rec['container'], rec['foff'], rec['foff'] + rec['size']))
    for path in sorted((root / 'config/link').glob('*/*.json')):
        doc = read_json(path)
        if doc.get('load_evidence'):
            fam = doc['container']
            start = int(doc['foff'], 0) if isinstance(doc['foff'], str) else doc['foff']
            size = int(doc['size'], 0) if isinstance(doc['size'], str) else doc['size']
            rec = records.get(doc['load_evidence'].get('record_sha256'))
            vma = int(doc['vma'], 0) if isinstance(doc.get('vma'), str) else doc.get('vma')
            ok = establishes_load(rec) if rec is not None else (
                vma is None or RETAIL_RAM[0] <= vma < RETAIL_RAM[1]) and 'not established' not in doc.get('evidence', '')
            if ok:
                out.append((fam, start, start + size))
            elif dropped is not None:
                dropped.append((fam, start, start + size))
    return out


def load_lines(root, units, findings):
    cache = {}
    directory = root / LINE_DIR
    if not directory.is_dir():
        return
    by_unit = {u.key: u for u in units.values()}
    groups = defaultdict(list)
    for path in sorted(directory.glob('*.tsv')):
        groups[path.stem.split('.')[0]].append(path)     # town.tsv, or town.000.tsv, town.001.tsv in sequence
    for name, paths in groups.items():
        if name in ('streams', 'disc_files'):
            continue
        unit = by_unit.get(unit_key(name))
        if unit is None:
            findings.append(('schema', '%s: no such program file or decoded image' % paths[0].name))
            continue
        lines = []
        for path in paths:
            lines += parse_lines(path.read_text(), unit.key, path.name, findings)
        for a, b in zip(lines, lines[1:]):
            if (b.start, b.end, b.cls) < (a.start, a.end, a.cls) and a.where.split(':')[0] != b.where.split(':')[0]:
                findings.append(('order', '%s: lines are not sorted across parts' % b.where))
                break
        for ln in lines:
            if ln.end > unit.size:
                findings.append(('schema', '%s: line past the end of %s' % (ln.where, unit.key)))
                continue
            if ln.window is not None and ln.window[0] + ln.window[1] > unit.size:
                findings.append(('schema', '%s: digest window past the end of %s' % (ln.where, unit.key)))
            elif not digest_matches(unit.data, ln):
                findings.append(('sha', '%s: sha256 differs from the bytes at %s..%s' % (ln.where, hx(ln.start), hx(ln.end))))
            problem = evidence_ok(root, ln.evidence, cache)
            if problem:
                findings.append(('evidence', '%s: %s (%s)' % (ln.where, problem, ln.evidence)))
            if work_label(ln.evidence):
                findings.append(('work_label', '%s: the evidence text carries a work label' % ln.where))
            unit.lines.append(ln)
        for layer in ('own', 'region'):
            ls = sorted((ln for ln in unit.lines if ln.layer == layer), key=lambda x: (x.start, x.end))
            for a, b in zip(ls, ls[1:]):
                if b.start < a.end:
                    findings.append(('overlap', '%s: %s %s..%s overlaps line %s' % (
                        unit.key, layer, hx(b.start), hx(b.end), a.where)))
        acks = defaultdict(list)
        for ln in unit.lines:
            if ln.layer == 'ack':
                acks[ln.cls.split(':')[1]].append(ln)
        for rule, ls in acks.items():
            ls.sort(key=lambda x: (x.start, x.end))
            for a, b in zip(ls, ls[1:]):
                if b.start < a.end:
                    findings.append(('overlap', '%s: acknowledgement %s..%s overlaps line %s' % (
                        unit.key, hx(b.start), hx(b.end), a.where)))
        for ln in unit.lines:
            if ln.layer == 'ack':
                rule, verdict = ln.cls.split(':')[1:3]
                if verdict not in VERDICTS[rule]:
                    findings.append(('schema', '%s: verdict %s is not allowed for %s' % (ln.where, verdict, rule)))


DISC_ROOT = 'work/disc/extract'


def load_disc_files(root, findings):
    """Whole-file lines for the disc files that are not program files (movies, system files): path, size, class,
    evidence, sha1. A file that is present is checked against its line; a file that is not is listed as unverified."""
    path = root / LINE_DIR / 'disc_files.tsv'
    rows = []
    if not path.is_file():
        return rows
    cache = {}
    for number, raw in enumerate(path.read_text().splitlines(), 1):
        if not raw.strip() or raw.startswith('#'):
            continue
        cols = raw.split('\t')
        where = 'disc_files.tsv:%d' % number
        if len(cols) != 5 or cols[2] != 'own:media' or not cols[1].isdigit() or not re.fullmatch(r'[0-9a-f]{40}', cols[4]):
            findings.append(('schema', '%s: expected path, size, own:media, evidence, sha1' % where))
            continue
        problem = evidence_ok(root, cols[3], cache)
        if problem:
            findings.append(('evidence', '%s: %s (%s)' % (where, problem, cols[3])))
        target = root / DISC_ROOT / cols[0]
        state = 'unverified'
        if target.is_file():
            blob = target.read_bytes()
            state = 'verified'
            if len(blob) != int(cols[1]) or hashlib.sha1(blob).hexdigest() != cols[4]:
                findings.append(('disc_file', '%s: %s differs from its line' % (where, cols[0])))
                state = 'differs'
        rows.append((cols[0], int(cols[1]), state))
    return rows


def load_streams(root, receipt_manifests):
    """Registered compressed streams: config/decoded manifests plus config/closure/streams.tsv.
    {(family, offset): (used, decoded size, source sha256, command or None)}"""
    out = {}
    for unit in receipt_manifests.values():
        for s in unit.manifest['streams']:
            fam = Path(s['container']).name.split('_')[0].lower()
            out[(fam, int(s['offset'], 0))] = (s['used'], s['size'], s['source_sha256'], s.get('command'))
    path = root / LINE_DIR / 'streams.tsv'
    if path.is_file():
        for raw in path.read_text().splitlines():
            if not raw.strip() or raw.startswith('#'):
                continue
            cols = raw.split('\t')
            if len(cols) != 5:
                raise InputError('streams.tsv: 5 columns expected')
            out[(cols[0], int(cols[1], 16))] = (int(cols[2], 16), int(cols[3], 16), cols[4], None)
    return out


# ------------------------------------------------------------------ analysis
def class_index(unit):
    """Point index per byte class of one unit, for the detector and the report."""
    ix = dict(code=Index(unit.c_code), data=Index(unit.c_data), asm=Index(unit.c_asm))
    for cls in OWN_CLASSES + ('own:stream',):
        ix[cls] = Index([[ln.start, ln.end] for ln in unit.lines if ln.layer == 'own' and
                         (ln.cls == cls or (cls == 'own:stream' and ln.cls.startswith('own:stream:')))])
    return ix


def class_at(unit, ix, pos):
    if ix['code'].has(pos):
        return 'C code'
    if ix['data'].has(pos):
        return 'C data'
    for cls in OWN_CLASSES:
        if ix[cls].has(pos) or (cls == 'own:stream' and ix['own:stream'].has(pos)):
            return cls
    if ix['asm'].has(pos):
        return 'assembly'
    return 'none'


def account(unit, findings):
    """Ownership of one unit: a class for every byte, unknown bytes, overlaps, own lines over C."""
    n = unit.size
    own = [ln for ln in unit.lines if ln.layer == 'own']
    union, multi = count_cover([[ln.start, ln.end] for ln in own])
    c_all = D.merge(unit.c_code + unit.c_data)
    nonc = D.subtract([[0, n]], c_all)
    zero = D.intersect(nonc, unit.zero_all)
    unit.zero = zero
    unknown = D.subtract(D.subtract(nonc, union), zero)
    unknown = D.merge(unknown + D.intersect(multi, nonc))
    unit.unknown = unknown
    for ln in own:
        over = D.intersect([[ln.start, ln.end]], c_all)
        if over:
            rest = D.subtract([[ln.start, ln.end]], c_all)
            findings.append(('entry_over_c', 'entry_over_c %s %s..%s %s covers %d B of compiled C: replace with %s' % (
                unit.key, hx(ln.start), hx(ln.end), ln.cls, total(over),
                ', '.join('%s..%s' % (hx(a), hx(b)) for a, b in rest[:6]) or 'nothing (delete the line)')))
    if multi:
        findings.append(('entry_overlap', 'a byte is in two own lines in %s: %d B' % (unit.key, total(multi))))
    by_class = {}
    left = list(nonc)
    for cls in OWN_CLASSES:
        iv = D.merge([[ln.start, ln.end] for ln in own if ln.cls == cls or (cls == 'own:stream' and ln.cls.startswith('own:stream:'))])
        mine = D.intersect(left, iv)
        by_class[cls] = mine
        left = D.subtract(left, mine)
    unit.by_class = by_class
    unit.left = left
    return unit


def regions_of(unit):
    return [ln for ln in unit.lines if ln.layer == 'region']


def region_index(unit, prefix=None):
    return Index([[ln.start, ln.end] for ln in unit.lines
                  if ln.layer == 'region' and (prefix is None or ln.cls.startswith(prefix))])


def region_tests(units, regions, findings):
    """Kf: a region other line never lies inside a load region with load evidence. Ks: a stale line is word for word the named program file at the same offset."""
    for unit in units.values():
        for ln in regions_of(unit):
            if unit.kind != 'file':
                continue
            if ln.cls.startswith('region:other:'):
                for fam, a, b in regions:
                    if fam == unit.key and a < ln.end and ln.start < b:
                        findings.append(('region_in_load', 'region_in_load %s %s %s covers %d B of a load region (%s..%s)' % (
                            unit.key, ln.cls, hx(ln.start), total(D.intersect([[ln.start, ln.end]], [[a, b]])), hx(a), hx(b))))
                        break
            elif ln.cls.startswith('region:stale:'):
                _, _, src, k = ln.cls.split(':')
                other = units.get(src)
                if other is None or other.size < ln.end or other.kind != 'file':
                    findings.append(('stale_test', 'stale_test %s %s: source file %s has no such range' % (unit.key, hx(ln.start), src)))
                    continue
                if (ln.end - ln.start) % 4 or ln.start % 4 or int(k) != 0:
                    findings.append(('stale_test', 'stale_test %s %s: a stale line is word aligned and byte-identical, its count is 0' % (unit.key, hx(ln.start))))
                    continue
                if unit.data[ln.start:ln.end] != other.data[ln.start:ln.end]:
                    words = (ln.end - ln.start) // 4
                    a = struct.unpack_from('<%dI' % words, unit.data, ln.start)
                    b = struct.unpack_from('<%dI' % words, other.data, ln.start)
                    findings.append(('stale_test', 'stale_test %s %s..%s: %d of %d words differ from %s at the same offset' % (
                        unit.key, hx(ln.start), hx(ln.end), sum(1 for x, y in zip(a, b) if x != y), words, src)))
                owned = D.merge(other.c_code + other.c_data + [[x.start, x.end] for x in other.lines if x.layer == 'own'] + other.zero
                                if hasattr(other, 'zero') else other.c_code + other.c_data)
                if D.subtract([[ln.start, ln.end]], owned):
                    findings.append(('stale_test', 'stale_test %s %s: the source bytes in %s are neither C nor in a line' % (
                        unit.key, hx(ln.start), src)))


def class_tests(units, labels, streams, root, findings):
    sdk_rows = load_sdk_rows(root)
    not_data = {}
    for unit in units.values():
        for ln in unit.lines:
            if ln.layer != 'own':
                continue
            span = unit.data[ln.start:ln.end]
            if ln.cls == 'own:padding':
                if len(set(span)) != 1:
                    findings.append(('padding', 'padding %s %s..%s is not one fill value' % (unit.key, hx(ln.start), hx(ln.end))))
                align = 1
                while align < 0x800 and ln.end % (align * 2) == 0:
                    align *= 2
                if ln.end % align or ln.end - ln.start >= align or align < 2:
                    findings.append(('padding', 'padding %s %s..%s does not end on an alignment boundary it is shorter than' % (
                        unit.key, hx(ln.start), hx(ln.end))))
            elif ln.cls == 'own:data' and unit.kind == 'file' and labels is not None:
                lab = labels.get(unit.key)
                if lab is not None:
                    if unit.key not in not_data:
                        not_data[unit.key] = (Index(lab['code'] + lab['unknown']), Index(unit.zero_all))
                    bad = D.subtract(not_data[unit.key][0].clip(ln.start, ln.end), not_data[unit.key][1].clip(ln.start, ln.end))
                    if bad:
                        bad = D.subtract(bad, pointer_words(unit, ln.start, ln.end))
                    if bad:
                        findings.append(('own_data', 'own_data %s %s..%s: %d B carry a code or unknown census label' % (
                            unit.key, hx(ln.start), hx(ln.end), total(bad))))
            elif ln.cls.startswith('own:stream:'):
                image = ln.cls.split(':', 2)[2]
                hit = None
                for (fam, off), (used, size, ssha, command) in streams.items():
                    if fam == unit.key and off == ln.start and off + used == ln.end:
                        hit = (used, size, ssha, command)
                if hit is None:
                    findings.append(('stream', 'stream %s %s..%s is not a registered compressed stream' % (unit.key, hx(ln.start), hx(ln.end))))
                else:
                    if sha256(span) != hit[2]:
                        findings.append(('stream', 'stream %s %s: source sha256 differs from the registry' % (unit.key, hx(ln.start))))
                    try:
                        sys.path.insert(0, str(TOOL_ROOT))
                        from tools.decoded.lz import decode
                        decoded, consumed = decode(unit.data[ln.start:ln.end + 0x800], hit[1])
                        if consumed != hit[0] or len(decoded) != hit[1]:
                            raise ValueError('length')
                    except ValueError:
                        findings.append(('stream', 'stream %s %s: the stream does not decode to its registered length at its own offset' % (
                            unit.key, hx(ln.start))))
                    if hit[3] is not None:
                        cmd = unit.data[ln.start - 20:ln.start]
                        if len(cmd) != 20 or list(struct.unpack('<HHIhhhhI', cmd)) != hit[3]:
                            findings.append(('stream', 'stream %s %s: the 20-byte command before it differs' % (unit.key, hx(ln.start))))
            elif ln.cls == 'own:vendor' and unit.kind == 'file':
                vendor_test(unit, ln, findings, sdk_rows)


def load_sdk_rows(root):
    """{id: (container, foff, size)} of the SDK object records that have an extent in the row ledger or the coverage
    residue ledger."""
    ids = set()
    path = root / 'ledger/sdk_objects.jsonl'
    if not path.is_file():
        return {}
    for line in path.read_text().splitlines():
        if line.strip():
            ids.add(json.loads(line)['id'])
    rows = {}
    for name in ('ledger/rows.jsonl', 'ledger/coverage_residue.jsonl'):
        path = root / name
        if path.is_file():
            for line in path.read_text().splitlines():
                if line.strip():
                    row = json.loads(line)
                    if row['id'] in ids and row.get('size') and row['id'] not in rows:
                        rows[row['id']] = (row['container'], row['foff'], row['size'])
    return rows


def vendor_extent_ok(unit, ln, sdk_rows):
    """Kv, first half: the line lies on assembled SDK bytes of the build, or on the extent of the SDK object record
    its evidence names."""
    asm = D.merge(unit.asm_kinds.get('platform_asm', []) + unit.asm_kinds.get('sdk_assembly', []))
    if not D.subtract([[ln.start, ln.end]], asm):
        return True
    path, _, key = ln.evidence.partition('#')
    row = sdk_rows.get(key) if path == 'ledger/sdk_objects.jsonl' else None
    return bool(row and row[0] == unit.key and row[1] <= ln.start and ln.end <= row[1] + row[2])


def vendor_test(unit, ln, findings, sdk_rows=None):
    """Kv: assembled SDK bytes (or the extent of an SDK object record) in which no call reaches a game C function."""
    if sdk_rows is not None and not vendor_extent_ok(unit, ln, sdk_rows):
        findings.append(('vendor_extent', 'vendor_extent %s %s..%s is neither assembled SDK code of the build nor inside the SDK object record its evidence names' % (
            unit.key, hx(ln.start), hx(ln.end))))
    base = unit.data
    a, b = (ln.start + 3) & ~3, ln.end & ~3
    calls = 0
    for pos in range(a, b, 4):
        w = struct.unpack_from('<I', base, pos)[0]
        if w >> 26 != 3:
            continue
        for delta in unit.pages.get(pos >> PAGE, ()):
            vma = pos + delta
            target = (((vma + 4) & 0xf0000000) | ((w & 0x3ffffff) << 2)) - delta
            if target in unit.starts and target != getattr(unit, 'named', {}).get('main'):
                calls += 1
                findings.append(('vendor_calls_game', 'vendor_calls_game %s %s: call at %s reaches the compiled function at %s' % (
                    unit.key, hx(ln.start), hx(pos), hx(target))))
                break


def load_has(iv, starts, x):
    i = bisect.bisect_right(starts, x) - 1
    return i >= 0 and x < iv[i][1]


def engine_info(units):
    """(load address, function start load addresses) of the engine images the executable's calls reach: the images
    named <file>/engine, which load over the executable's own data block."""
    base, starts = None, set()
    for unit in units.values():
        if unit.kind != 'file':
            continue
        for image, vma in unit.image_vma.items():
            if image.split('/', 1)[1:] == ['engine']:
                base = vma if base is None else min(base, vma)
                starts |= unit.image_vma_starts.get(image, set())
    return base, starts


def d5_note(unit, units, a, b):
    """A dense run (report only) becomes an open hit when it contains a call that lands on a compiled function start
    of the build, or lies in no image of its file (a function-shaped fragment that nothing loads)."""
    if unit.kind != 'file':
        return ''
    notes = []
    for pos, w in D.calls_in(unit.data, a, b):
        target = ((0x80000000 | (w & 0x3ffffff) << 2))
        if any(target in other.vma_starts for other in units.values() if other.kind == 'file'):
            notes.append('call_to_start')
            break
    if not any(s < b and a < e for _i, s, e, _d in unit.images):
        # a run in no image opens only with a call to a known start or register dataflow (a grounded access path);
        # dense words that only look like code stay listed and report-only
        words = struct.unpack_from('<%dI' % ((b - a) // 4), unit.data, a)
        grounded = D.grounded_memory_ops(words) >= D.D5_GROUNDED
        notes.append('no_image' if grounded or 'call_to_start' in notes else 'no_image_ungrounded')
    return ','.join(notes)


def detect(unit, units, regions, sdk_range, exe_starts, census, findings):
    """All detector rules over one unit; returns hit tuples (start, end, rule, note)."""
    ix = class_index(unit)
    scan = D.merge([[ln.start, ln.end] for ln in unit.lines if ln.layer == 'own' and ln.cls in
                    ('own:data', 'own:padding', 'own:untyped')] + unit.c_data)
    hits = [(a, b, r, '') for a, b, r in D.d1_hits(unit.data, scan)]
    d1 = [(a, b, r) for a, b, r, _ in hits]
    hits += [(a, b, r, '') for a, b, r in D.d2_hits(unit.data, scan, [[a, b] for a, b, _ in d1])]
    taken = [[a, b] for a, b, _, _ in hits]
    rescue = (lambda a, b: 'call_to_start' in d5_note(unit, units, a, b)) if unit.kind == 'file' else None
    hits += [(a, b, r, d5_note(unit, units, a, b)) for a, b, r in D.d5_hits(unit.data, scan, taken=taken, rescue=rescue)]
    tail_targets = set()
    for other in units.values():
        if other.kind == 'file':
            tail_targets |= other.vma_starts
    hits += [(a, b, r, '') for a, b, r in D.d8_hits(unit.data, scan, taken=[[a, b] for a, b, _, _ in hits], starts=tail_targets)]
    notes = {}
    if unit.kind == 'file':
        engine_base, engine_starts = engine_info(units)

        def resolve(alloc, target_vma):
            loaded = unit.image_loaded.get(alloc.image)
            own = alloc.vma - alloc.foff
            if not loaded:
                return target_vma - own
            inside = [d for d, (iv, starts) in loaded.items() if load_has(iv, starts, target_vma)]
            if own in inside:
                return target_vma - own
            return target_vma - inside[0] if len(inside) == 1 else None

        def cross(alloc, kind, target_vma):
            if unit.key == 'slus' and engine_base is not None and target_vma >= engine_base and target_vma in engine_starts:
                return True
            return kind == 'midbody' and any(target_vma in other.vma_starts for other in units.values()
                                             if other.kind == 'file' and other is not unit)
        def classify(pos):
            if ix['code'].has(pos):
                return 'c_code'
            if ix['data'].has(pos) or any(ix[c].has(pos) for c in ('own:data', 'own:padding', 'own:stream', 'own:untyped')):
                return 'noncode'
            return 'other'
        d3, notes, weak = D.d3_hits(unit.data, unit.allocations, unit.funcs, classify, unit.starts, resolve, cross)
        hits += [(a, b, r, k) for a, b, r, k in d3]
        notes['weak_images'] = weak
        runs = [a for a, b, r, _ in hits if r in ('D1', 'D2')]

        def deltas_at(pos):
            return unit.pages.get(pos >> PAGE, ())
        hits += [(a, b, r, '') for a, b, r in D.d4_hits(unit.data, scan, runs, deltas_at)]
        other = [(ln.start, ln.end) for ln in regions_of(unit) if ln.cls.startswith('region:other:')]
        if other and sdk_range:
            bodies = D.d1_hits(unit.data, D.merge([list(x) for x in other]))   # bodies of the other program, whatever their class
            hits += [(a, b, r, '') for a, b, r in D.d7_hits(unit.data, bodies, sdk_range, exe_starts)]
        own_data = {unit.key: D.merge([[ln.start, ln.end] for ln in unit.lines if ln.cls == 'own:data'])}
        own_stream = {unit.key: D.merge([[ln.start, ln.end] for ln in unit.lines if ln.cls.startswith('own:stream:')])}
        for _c, a, b, r in D.d6_hits([s for s in census if s[0] == unit.key], own_data, own_stream):
            hits.append((a, b, r, ''))
    return hits, notes


def match_hits(unit, hits, findings, resolved_by_region=True):
    """Each hit needs one ack with its exact extent and rule, or lies wholly inside a region line."""
    ix = region_index(unit)
    acks = {}
    for ln in unit.lines:
        if ln.layer == 'ack':
            acks[(ln.start, ln.end, ln.cls.split(':')[1])] = ln
    used, open_hits, resolved = set(), [], []
    for a, b, rule, note in sorted(hits):
        ack = acks.get((a, b, rule))
        if ack is not None:
            used.add((a, b, rule))
            resolved.append((a, b, rule, note, ack.cls.split(':')[2]))
        elif (rule in ('D1', 'D2', 'D4', 'D5') or (rule == 'D3' and note.startswith('call_into_noncode'))) \
                and resolved_by_region and not D.subtract([[a, b]], ix.v):
            resolved.append((a, b, rule, note, 'region'))
        else:
            open_hits.append((a, b, rule, note))
    for key, ln in acks.items():
        if key not in used:
            findings.append(('ack_stale', 'ack_stale %s %s..%s %s: no detector hit has this extent and rule' % (
                unit.key, hx(key[0]), hx(key[1]), key[2])))
        elif not digest_matches(unit.data, ln):
            findings.append(('ack_stale', 'ack_stale %s %s: bytes changed' % (unit.key, hx(ln.start))))
    return open_hits, resolved


def headline(units, regions_game=True):
    """H and its parts, from the lines alone (nothing here reads bytes)."""
    phys = code_c = dec = 0
    for unit in units.values():
        region = D.merge([[ln.start, ln.end] for ln in unit.lines if ln.layer == 'region'])
        own_code = D.merge([[ln.start, ln.end] for ln in unit.lines if ln.cls == 'own:code'])
        if unit.kind == 'decoded':
            dec += total(D.subtract(own_code, region))
            continue
        phys += total(D.subtract(own_code, region))
        ack = D.merge([[ln.start, ln.end] for ln in unit.lines if ln.layer == 'ack' and ln.cls.endswith(':code_in_c_data')])
        code_c += total(D.subtract(ack, region))
    return phys + code_c + dec, phys, code_c, dec


def headline_from_text(texts):
    """Headline of line files given as {unit key: text}; used for the base of a delta."""
    class _U:
        pass
    units = {}
    for key, text in texts.items():
        u = _U()
        u.kind = 'decoded' if key.startswith('decoded:') else 'file'
        u.lines = parse_lines(text, key, key, [])
        units[key] = u
    return headline(units)


def git(root, *argv):
    return subprocess.run(['git', *argv], cwd=root, capture_output=True, text=True)


def base_texts(root, mode):
    """(base sha, {unit key: text of its lines at the base}); base computed here, never named by the caller."""
    if mode == 'batch':
        roots = git(root, 'rev-list', '--max-parents=0', 'HEAD').stdout.split()
        if len(roots) != 1:
            raise InputError('batch mode needs exactly one root commit')
        base = roots[0]
    else:
        base = git(root, 'rev-parse', 'HEAD').stdout.strip()
        if not base:
            return None, {}
    listing = git(root, 'ls-tree', '-r', '--name-only', base, LINE_DIR).stdout.split()
    texts = {}
    for name in sorted(listing):
        stem = Path(name).stem.split('.')[0]
        if not name.endswith('.tsv') or stem in ('streams', 'disc_files'):
            continue
        texts[unit_key(stem)] = texts.get(unit_key(stem), '') + git(root, 'show', '%s:%s' % (base, name)).stdout
    return base, texts


def delta(units, base, texts):
    """Lines added and removed against the base, and bytes put in a line that no line held at the base."""
    added, removed, newly = [], [], 0
    for key, unit in units.items():
        old = parse_lines(texts.get(key, '# schema ' + SCHEMA + '\n'), key, 'base', [])
        old_keys = {ln.key() for ln in old}
        new_keys = {ln.key() for ln in unit.lines}
        added += [ln for ln in unit.lines if ln.key() not in old_keys]
        removed += [ln for ln in old if ln.key() not in new_keys]
        before = D.merge([[ln.start, ln.end] for ln in old if ln.layer == 'own'])
        newly += total(D.subtract(D.merge([[ln.start, ln.end] for ln in added if ln.unit == key and ln.layer == 'own']), before))
    return added, removed, newly


def region_delta(root, base):
    """Rule I, report only: link documents and load records added or removed against the base. A removal moves no
    byte by itself; using one needs an added region line."""
    if not base:
        return [], []
    now = {p.relative_to(root).as_posix() for p in (root / 'config/link').glob('*/*.json')}
    listing = git(root, 'ls-tree', '-r', '--name-only', base, 'config/link').stdout.split()
    then = {n for n in listing if n.endswith('.json') and n.count('/') == 3}
    added = ['image document ' + n for n in sorted(now - then)]
    removed = ['image document ' + n for n in sorted(then - now)]
    path = 'ledger/instance_load_regions.jsonl'
    old = git(root, 'show', '%s:%s' % (base, path)).stdout.splitlines()
    new = (root / path).read_text().splitlines() if (root / path).is_file() else []
    for rec in sorted(set(new) - set(old)):
        r = json.loads(rec)
        added.append('load record %s %s+%s' % (r['container'], hx(r['foff']), hx(r['size'])))
    for rec in sorted(set(old) - set(new)):
        r = json.loads(rec)
        removed.append('load record %s %s+%s' % (r['container'], hx(r['foff']), hx(r['size'])))
    return added, removed


def default_labels(root):
    """Census label per byte of each physical root, as {'code': iv, 'unknown': iv} per file."""
    sys.path.insert(0, str(TOOL_ROOT / 'tools'))
    sys.path.insert(0, str(TOOL_ROOT / 'tools/gate'))
    import byte_map as BM
    roots = json.loads((root / 'link/physical_roots.json').read_text())
    images = BM.load_maps(root, 'link')[0]
    # The physical-root part of the byte map check (a complete, disjoint tiling of each program file by the five
    # roots). The comparison of every overlapping view with the roots stays in `tools/byte_map.py check`: it costs
    # about 100 s and the labels this tool reads come from the roots alone.
    BM.describe(images, roots, roots)
    sizes = {r['container']: r['bytes'] for r in map(json.loads, (root / 'ledger/containers.jsonl').read_text().splitlines())}
    sizes['slus'] = 524288
    for fam in FILES:
        last = 0
        for start, size in sorted((images[k]['foff'], images[k]['size']) for k in roots if images[k]['container'] == fam):
            if start != last:
                raise InputError('physical roots do not tile %s' % fam)
            last += size
        if last != sizes[fam]:
            raise InputError('physical roots do not cover %s' % fam)
    out = {}
    for image in roots:
        fam = image.split('/')[0]
        code, unknown, library, data, padding = [], [], [], [], []
        for span in BM.flatten(images, image):
            iv = [span['foff'], span['foff'] + span['size']]
            if span['label'] in ('proven_code', 'strongly_code'):
                code.append(iv)
            elif span['label'] == 'library_code':
                library.append(iv)
            elif span['label'] == 'unknown':
                unknown.append(iv)
            elif span['label'] == 'padding_leftover':
                padding.append(iv)
            else:
                data.append(iv)
        out[fam] = dict(code=D.merge(code + library), unknown=D.merge(unknown), library=D.merge(library),
                        data=D.merge(data), padding=D.merge(padding))
    return out


def default_census(root, data):
    sys.path.insert(0, str(TOOL_ROOT / 'tools'))
    from decoded import census as C
    result = C.census_files({fam: data[fam] for fam in ('main', 'town', 'dungeon', 'ovmovie')}, extended=False)
    return [(r['container'], int(r['offset'], 16), r['used']) for r in result['streams']]


def report_only(hit):
    """A hit of a report-only rule is listed and never open, except a dense run that holds a call to a function start
    or lies in no image (its note says so)."""
    return hit[2] in D.REPORT_ONLY_RULES and not (hit[2] == 'D5' and hit[3] and hit[3] != 'no_image_ungrounded')


def analyse(root, mode, labels=None, census=None, clock=time.monotonic):
    """Run the whole check; returns a result object (no printing, no exit)."""
    root = Path(root)
    started = clock()
    res = dict(findings=[], root=root, mode=mode, phases=[])
    findings = res['findings']

    def phase(name, last=[started]):
        now = clock()
        res['phases'].append((name, now - last[0]))
        last[0] = now
    receipt = load_proof(root)
    phase('proof')
    data = load_disc(root)
    units = {fam: Unit(fam, data[fam]) for fam in FILES}
    phase('program files')
    load_cover(root, receipt, units)
    phase('cover lists')
    decoded = load_decoded(root, receipt)
    units.update(decoded)
    load_lines(root, units, findings)
    phase('decoded images and lines')
    for unit in units.values():
        account(unit, findings)
    res['load_dropped'] = []
    regions = load_regions(root, res['load_dropped'])
    region_tests(units, regions, findings)
    streams = load_streams(root, decoded)
    phase('ownership and regions')
    if labels is None:
        labels = default_labels(root)
    phase('census labels')
    class_tests(units, labels, streams, root, findings)
    phase('class tests')
    if census is None:
        census = default_census(root, data)
    phase('stream census')
    slus = units['slus']
    exe_starts = slus.vma_starts
    sdk_range = tuple(slus.vma_extent) if slus.vma_extent[1] else None
    res['hits'], res['open'], res['resolved'], res['notes'] = {}, {}, {}, {}
    for key, unit in units.items():
        hits, notes = detect(unit, units, regions, sdk_range, exe_starts, census, findings)
        extents = {image: (s, e) for image, s, e, _ in unit.images}
        for image in notes.get('weak_images', ()):
            hits.append((extents[image][0], extents[image][1], 'D3B', image))
        ix = class_index(unit)
        open_hits, resolved = match_hits(unit, [h for h in hits if not report_only(h)], findings)
        res['hits'][key] = hits
        res['open'][key] = [(a, b, r, k, class_at(unit, ix, a)) for a, b, r, k in open_hits]
        res['resolved'][key] = resolved
        res['notes'][key] = notes
        for a, b, r, k, c in res['open'][key]:
            findings.append(('hit', 'hit %s %s %s %s..%s in %s%s: add C, a line, or: %s\t%s\tack:%s:<verdict>\t<evidence>\t<sha256>' % (
                r, key, '', hx(a), hx(b), c, ' (%s)' % k if k else '', hx(a), hx(b), r)))
    for key, unit in units.items():
        for n, (a, b) in enumerate(unit.unknown):
            image = next((i for i, s, e, _ in unit.images if s <= a < e), '') if n < MAX_LIST else ''
            findings.append(('unknown', 'unknown %s +%s..+%s %d B%s: no C, no line' % (
                key, hx(a)[2:], hx(b)[2:], b - a, ' (image %s)' % image if image else '')))
    phase('detector')
    base, texts = base_texts(root, mode)
    res['base'] = base
    res['disc_files'] = load_disc_files(root, findings)
    res['delta'] = delta(units, base, texts) if base else ([], [], 0)
    res['base_headline'] = headline_from_text(texts)[0] if base and texts else None
    res['region_delta'] = region_delta(root, base)
    res['units'] = units
    known = set()
    for other in units.values():
        if other.kind == 'file':
            known |= other.vma_starts
    res['declared'] = V6.declared_tests(root, units, streams, base, findings, known)
    res['demoted'], res['linkdocs'] = V6.load_changes(root, base, regions, units, findings)
    res['tool_changes'] = V6.tool_changes(root, base)
    res['ledger'] = V6.ledger_delta(root, base) if base else None
    added_rows, removed_rows = V6.text_delta(root, base, LINE_DIR + '/streams.tsv') if base else ([], [])
    res['stream_rows'] = ['STREAMROW added ' + r for r in added_rows] + ['STREAMROW removed ' + r for r in removed_rows]
    res['ruling_rows'] = V6.row_changes(root, base, V6.RULINGS, 'RULING') if base else []
    res['template_rows'] = V6.row_changes(root, base, 'config/asm_templates.tsv', 'TEMPLATE') if base else []
    res['headline'] = headline(units)
    phase('delta and headline')
    res['elapsed'] = clock() - started
    res['receipt'] = receipt
    return res


def fmt(n):
    return '{:,}'.format(n)


def summary(res):
    units = res['units']
    h, p, q, d = res['headline']
    unknown = sum(total(u.unknown) for u in units.values())
    open_hits = sum(len(v) for v in res['open'].values())
    lines = ['HEADLINE game code without C: %s B (physical %s, C-data bodies %s, decoded %s) | unknown %s | open hits %s' % (
        fmt(h), fmt(p), fmt(q), fmt(d), fmt(unknown), fmt(open_hits))]
    added, removed, newly = res['delta']
    lines.append('LINES +%d -%d against %s; headline %s -> %s%s' % (
        len(added), len(removed), (res['base'] or 'none')[:9],
        '-' if res['base_headline'] is None else fmt(res['base_headline']), fmt(h),
        '; %s B newly in a line that no line held at the base' % fmt(newly) if newly else ''))
    for key, u in units.items():
        if u.kind != 'file':
            continue
        cols = [('C code', total(u.c_code)), ('C data', total(u.c_data))]
        cols += [(c, total(u.by_class[c])) for c in OWN_CLASSES] + [('zero', total(u.zero)), ('unknown', total(u.unknown))]
        lines.append('FILE %s %s B: %s' % (key, fmt(u.size), ' | '.join('%s %s' % (n, fmt(v)) for n, v in cols)))
        reg = Counter()
        for ln in regions_of(u):
            reg[':'.join(ln.cls.split(':')[:3] if ln.cls.count(':') > 1 and not ln.cls.startswith('region:stale') else ln.cls.split(':')[:3])] += ln.end - ln.start
        lines.append('  REGION game | ' + ' | '.join('%s %s' % (k, fmt(v)) for k, v in sorted(reg.items())) if reg else '  REGION game only')
        lines.append('  assembly %s B (of it in own lines %s B); cover conflicts %s B; compiled functions %d' % (
            fmt(total(u.c_asm)), fmt(total(D.intersect(u.c_asm, [[ln.start, ln.end] for ln in u.lines if ln.layer == 'own']))),
            fmt(total(u.conflicts)), len(u.funcs)))
        if u.members:
            lines.append('  compiled functions read from %d link maps: %d chunks split into member functions, %d kept whole; '
                         'noload table bytes clipped at compiled code %s; calls to other programs not judged %d' % (
                             u.members['images'], u.members['split'], u.members['whole'], fmt(total(u.table_clipped)),
                             res['notes'].get(key, {}).get('cross_image', 0)))
    fragments = [(key, a, b) for key, opened in res['open'].items() for a, b, r, k, _c in opened if r == 'D5' and 'no_image' in k.split(',')]
    if fragments:
        lines.append('OPEN code_fragment_in_no_image: %d runs, %s B (function-shaped, no entry, no return, in no image; '
                     'no ownership line): %s' % (len(fragments), fmt(sum(b - a for _k, a, b in fragments)),
                                                 ', '.join('%s %s+%d' % (k, hx(a), b - a) for k, a, b in fragments[:8])))
    lines.append('LOADRECORDS left out as load evidence (not a retail load, or a base outside retail RAM): %d' % len(res.get('load_dropped', ())))
    media = res['disc_files']
    lines.append('DISCFILES %d whole-file lines, %s B (%d verified against the extracted disc)' % (
        len(media), fmt(sum(n for _, n, _ in media)), sum(1 for _, _, st in media if st == 'verified')))
    for key, u in units.items():
        if u.kind != 'decoded':
            continue
        lines.append('DECODED %s %s B: C functions %s | own:code %s | own:data %s | unknown %s' % (
            key[len('decoded:'):], fmt(u.size), fmt(total(u.c_code)), fmt(total(u.by_class['own:code'])),
            fmt(total(u.by_class['own:data'])), fmt(total(u.unknown))))
    return lines


def write_report(res, out):
    out = Path(out)
    out.mkdir(parents=True, exist_ok=True)
    lines = summary(res)
    counts = Counter()
    for kind, text in res['findings']:
        counts[kind] += 1
    lines.append('FINDINGS ' + (', '.join('%s %d' % kv for kv in sorted(counts.items())) or 'none'))
    shown = Counter()
    for kind, text in res['findings']:
        shown[kind] += 1
        if shown[kind] <= MAX_LIST:
            lines.append('CLOSURE FAIL ' + text)
    for kind, n in sorted(counts.items()):
        if n > MAX_LIST:
            lines.append('CLOSURE FAIL %s: %d more not listed (see the report files)' % (kind, n - MAX_LIST))
    added_regions, removed_regions = res['region_delta']
    for text in added_regions:
        lines.append('LOADREGION added: ' + text)
    for text in removed_regions:
        lines.append('LOADREGION removed: ' + text)
    lines.append('RUN %.1f s: %s' % (res['elapsed'], ', '.join('%s %.1f' % p for p in res['phases'])))
    (out / 'report.txt').write_text('\n'.join(lines) + '\n')
    with (out / 'hits.tsv').open('w') as fh:
        fh.write('file\toffset\tsize\trule\tclass\tstate\tnote\n')
        for key, hits in res['hits'].items():
            open_set = {(a, b, r) for a, b, r, _k, _c in res['open'][key]}
            ix = class_index(res['units'][key])
            for a, b, r, k in sorted(hits):
                state = 'open' if (a, b, r) in open_set else 'report-only' if report_only((a, b, r, k)) else 'resolved'
                fh.write('%s\t%s\t%d\t%s\t%s\t%s\t%s\n' % (key, hx(a), b - a, r, class_at(res['units'][key], ix, a), state, k))
    with (out / 'unknown.tsv').open('w') as fh:
        fh.write('file\toffset\tsize\n')
        for key, u in res['units'].items():
            for a, b in u.unknown:
                fh.write('%s\t%s\t%d\n' % (key, hx(a), b - a))
    added, removed, _ = res['delta']
    with (out / 'lines_delta.tsv').open('w') as fh:
        fh.write('change\tfile\tline\n')
        for ln in added:
            fh.write('added\t%s\t%s\n' % (ln.unit, ln.text()))
        for ln in removed:
            fh.write('removed\t%s\t%s\n' % (ln.unit, ln.text()))
    return lines


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('mode', choices=('landing', 'batch', 'report'))
    parser.add_argument('--out', default='build/closure')
    args = parser.parse_args(argv)
    root = Path.cwd() if (Path.cwd() / 'config/link_graph').is_dir() else TOOL_ROOT
    try:
        res = analyse(root, args.mode)
    except InputError as exc:
        print('CLOSURE INPUT %s' % exc)
        return 2
    out = Path(args.out)
    out = out if out.is_absolute() else root / out
    lines = write_report(res, out)
    if args.mode == 'report':
        print('\n'.join(lines[:40] if len(lines) > 40 else lines))
    else:
        # What a landing's reader sees: the summary, then every changed line, load record, link document,
        # ledger row and refusal in full (no cut), then the findings by kind.
        shown = [l for l in lines if l.startswith(('HEADLINE', 'LINES', 'FILE ', 'FINDINGS', 'LOADRECORDS', 'OPEN '))]
        landing = shown + V6.landing_lines(res)
        (out / 'landing.txt').write_text('\n'.join(landing) + '\n')
        print('\n'.join(landing))
    refused = [f for f in res['findings']]
    if refused and args.mode != 'report' and GATING:
        return 1
    if refused and not GATING:
        print('CLOSURE report only: %d findings, exit 0' % len(refused))
    return 0


if __name__ == '__main__':
    sys.exit(main())
