#!/usr/bin/env python3
"""One-time import of the first exception files (config/closure/*.tsv). Never run in a landing.

    python3 tools/lint/closure_bootstrap.py [--out DIR]

It reads what the check reads (the full make check receipt, the cover lists, the physical byte maps and their
census labels, the SDK object ledger, the decoded image manifests) and writes lines for every byte that no
compiled function emits. It acknowledges nothing: a detector hit inside a line it writes, or in compiled C data, stays an open hit of the
check and is listed by it. The summary names, per class and per file, the lines and bytes, and which evidence each line came from.

Evidence of a line is a tracked path (a physical byte map part, the SDK object ledger, a decoded image manifest, an
import header named by the foreign program table). Each line carries the sha256 of its bytes, or for an extent under 16 bytes the digest of an enclosing window
of at least 16 bytes (stated in the line).
"""
import argparse
import json
import sys
from collections import Counter, defaultdict
from pathlib import Path

HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(HERE))
import closure as C  # noqa: E402
import closure_detect as D  # noqa: E402

# Foreign programs that share the program files with the game: header evidence names them. They are region lines
# (the bytes stay accounted by ownership lines like any other byte).
FOREIGN = (
    ('dungeon', 0, 86016, 'head_bank', 'include/dungeon/effect/head_bank_imports.h'),
    ('dungeon', 19509248, 19681280, 'stale_bank', 'include/dungeon/stale_bank_imports.h'),
    ('main', 2527232, 2578432, 'card_server', 'include/frontend/card/server_imports.h'),
    ('town', 2547712, 2564096, 'card_server', 'include/frontend/card/server_imports.h'),
    ('town', 7911424, 7954432, 'old_minigame', 'include/town/devkit/old_minigame_imports.h'),
    ('town', 8339456, 8404992, 'flag_test', 'include/town/devkit/flag_test_imports.h'),
    ('town', 8574976, 8675328, 'flag_test', 'include/town/devkit/flag_test_imports.h'),
)
# Windows of the DUNGEON file that repeat TOWN sectors at the same offsets (stale copies): the `bank_d0a0` view, the
# head bank's part below 0xF800 and three sectors of the scene area. A `region:stale:town:0` line is written only for
# a maximal run inside a window that is word for word equal to TOWN at the same offset.
STALE_WINDOWS = {'dungeon': [(0xC000, 0xF800), (0x51E000, 0x51E800), (0x8D1000, 0x8D1800), (0x8EB000, 0x8EB800)]}
STALE_VIEWS = {'dungeon': ('dungeon/bank_d0a0',)}
STALE_SOURCE = 'town'
STALE_LEAST_WORDS = 16
STALE_EVIDENCE = 'ledger/containers.jsonl'
PART_LIMIT = 900_000       # bytes of one exception file part
ASSEMBLY_EVIDENCE = {
    'platform_asm': ('own:vendor', 'ledger/sdk_objects.jsonl'),
    'sdk_assembly': ('own:vendor', 'config/slus_partitions.json'),
    'game_asm': ('own:code', 'ledger/rows.jsonl'),
    'game_assembly': ('own:code', 'config/slus_006.14.yaml'),
}
# library code the build and the SDK object ledger do not prove vendor is not called vendor: it is code
LABEL_CLASS = (('code', 'own:code'), ('library', 'own:code'), ('data', 'own:data'))


def table_number(text):
    """A number of a byte map row: decimal, or hex (0x...) and either of them JSON-quoted, which the current
    format uses for some offsets and sizes."""
    return int(text.strip().strip('"'), 0)


def part_ranges(root, fam):
    """(start, end, relative path) of each physical byte map part of one program file."""
    out = []
    for path in sorted((root / 'link' / fam).glob('%s_bin*.tsv' % fam)):
        rows = [ln for ln in path.read_text().splitlines() if ln and not ln.startswith('#') and not ln.startswith('o\t')]
        first = table_number(rows[0].split('\t')[0])
        o, n = rows[-1].split('\t')[:2]
        out.append((first, table_number(o) + table_number(n), path.relative_to(root).as_posix()))
    return out


def sdk_extents(root):
    """{container: [(start, end, id)]} of the SDK object rows."""
    ids = set()
    for line in (root / 'ledger/sdk_objects.jsonl').read_text().splitlines():
        if line.strip():
            ids.add(json.loads(line)['id'])
    out, seen = defaultdict(list), set()
    for name in ('ledger/rows.jsonl', 'ledger/coverage_residue.jsonl'):
        path = root / name
        if not path.is_file():
            continue
        for line in path.read_text().splitlines():
            if not line.strip():
                continue
            row = json.loads(line)
            if row['id'] in ids and row.get('size') and row['id'] not in seen:
                seen.add(row['id'])
                out[row['container']].append((row['foff'], row['foff'] + row['size'], row['id']))
    return out


class Plan:
    """Lines of one unit while they are being decided."""

    def __init__(self, unit):
        self.unit = unit
        self.lines = []          # (start, end, cls, evidence)
        self.source = Counter()  # evidence source label -> bytes

    def add(self, iv, cls, evidence, source=None):
        for a, b in iv:
            if b > a:
                self.lines.append((a, b, cls, evidence))
                self.source[source or evidence] += b - a


def split_by(iv, parts):
    """Pieces of the intervals cut at part boundaries: (a, b, path)."""
    out = []
    for a, b in iv:
        for pa, pb, path in parts:
            lo, hi = max(a, pa), min(b, pb)
            if lo < hi:
                out.append((lo, hi, path))
    return out


def stale_runs(data, source, windows, least_words=STALE_LEAST_WORDS):
    """Maximal word-aligned runs inside the windows that are word for word equal to `source` at the same offsets,
    trimmed to non-zero words at both ends, of at least `least_words` words. The test is the one the check applies to
    a `region:stale` line, so a run listed here passes it."""
    out = []
    for lo, hi in D.merge([list(w) for w in windows]):
        lo, hi = (lo + 3) & ~3, min(hi, len(data), len(source)) & ~3
        i = lo
        while i < hi:
            if data[i:i + 4] != source[i:i + 4]:
                i += 4
                continue
            j = i
            while j < hi and data[j:j + 4] == source[j:j + 4]:
                j += 4
            a, b = i, j
            while a < b and data[a:a + 4] == b'\0\0\0\0':
                a += 4
            while b > a and data[b - 4:b] == b'\0\0\0\0':
                b -= 4
            if (b - a) // 4 >= least_words:
                out.append([a, b])
            i = j
    return out


def retype_code_lines(unit, plan):
    """A code line that comes from a census label is a run of whole instruction words: bytes of it that are not
    word aligned, or a run shorter than one word, cannot be instructions and become `own:untyped`; a leading or
    trailing header of pointers to this image's function starts (with a zero word beside one) is data."""
    out = []
    moved = Counter()
    for a, b, cls, ev in plan.lines:
        if cls != 'own:code' or not ev.startswith('link/'):
            out.append((a, b, cls, ev))
            continue
        a2, b2 = (a + 3) & ~3, b & ~3
        if b2 <= a2:
            out.append((a, b, 'own:untyped', ev))
            moved['untyped (shorter than a word)'] += b - a
            continue
        for x, y in ((a, a2), (b2, b)):
            if y > x:
                out.append((x, y, 'own:untyped', ev))
                moved['untyped (not word aligned)'] += y - x
        edges = C.pointer_edges(unit, a2, b2)
        rest = D.subtract([[a2, b2]], edges)
        for x, y in edges:
            out.append((x, y, 'own:data', ev))
            moved['data (pointer words to function starts)'] += y - x
        for x, y in rest:
            out.append((x, y, 'own:code', ev))
    plan.lines = out
    for label, n in moved.items():
        plan.source['retyped code label -> ' + label] += n
        plan.source['census label code'] -= n


def padding_ok(data, a, b):
    if b <= a or len(set(data[a:b])) != 1:
        return False
    align = 1
    while align < 0x800 and b % (align * 2) == 0:
        align *= 2
    return align >= 2 and b % align == 0 and b - a < align


def plan_file(root, unit, labels, parts, sdk, streams, foreign, stale=()):
    plan = Plan(unit)
    n = unit.size
    # zero bytes inside a labelled range stay in its line (a function holds zero words); a range that is zero
    # all the way needs no line at all, the check counts it as zero itself
    left = D.subtract(D.subtract([[0, n]], D.merge(unit.c_code + unit.c_data)), unit.zero_all)
    for start, end, program, evidence in foreign:
        plan.add(D.subtract([[start, end]], stale), 'region:other:' + program, evidence, 'foreign program table')
    plan.add(stale, 'region:stale:%s:0' % STALE_SOURCE, STALE_EVIDENCE, 'stale %s sectors (word for word equal)' % STALE_SOURCE)
    # compressed streams (decoded manifests and the stream census)
    for (fam, off), (used, size, ssha, command, name) in sorted(streams.items()):
        if fam == unit.key and off + used <= n:
            take = D.intersect(left, [[off, off + used]])
            if take == [[off, off + used]]:
                plan.add(take, 'own:stream:' + name, 'config/decoded/menu_cache.json' if name == 'menu_cache' else 'config/closure/streams.tsv', 'stream registry')
                left = D.subtract(left, take)
    # assembled units of the build
    for kind, iv in sorted(unit.asm_kinds.items()):
        cls, evidence = ASSEMBLY_EVIDENCE.get(kind, ('own:code', 'ledger/rows.jsonl'))
        take = D.intersect(left, iv)
        plan.add(take, cls, evidence, 'build assembly (%s)' % kind)
        left = D.subtract(left, take)
    # SDK object rows
    for a, b, rid in sorted(sdk.get(unit.key, ())):
        take = D.intersect(left, [[a, b]])
        plan.add(take, 'own:vendor', 'ledger/sdk_objects.jsonl#' + rid, 'sdk object row')
        left = D.subtract(left, take)
    # census labels of the physical map
    lab = labels[unit.key]
    for key, cls in LABEL_CLASS:
        take = D.intersect(left, lab[key] if key != 'code' else lab['code'])
        for a, b, path in split_by(take, parts):
            plan.add([[a, b]], cls, path, 'census label %s' % key)
        left = D.subtract(left, take)
    take = D.intersect(left, lab['padding'])
    for a, b, path in split_by(take, parts):
        if padding_ok(unit.data, a, b):
            plan.add([[a, b]], 'own:padding', path, 'census label padding (fill test)')
        else:
            plan.add([[a, b]], 'own:untyped', path, 'census label padding (fails fill test)')
    left = D.subtract(left, take)
    for a, b, path in split_by(left, parts):
        plan.add([[a, b]], 'own:untyped', path, 'census label unknown')
    return plan


def decoded_plan(unit):
    """Decoded gaps: bodies the detector finds are own:code; other non-zero bytes are untyped (not in the headline)."""
    plan = Plan(unit)
    gaps = D.subtract([[0, unit.size]], D.merge(unit.c_code + unit.c_data))   # compiled code and compiled C data are owned
    gaps = D.subtract(gaps, unit.zero_all)
    hits = D.d1_hits(unit.data, gaps)
    hits += D.d2_hits(unit.data, gaps, [[a, b] for a, b, _ in hits])
    body = D.merge([[a, b] for a, b, _ in hits])
    body = D.intersect(body, gaps)
    evidence = unit.manifest.get('evidence', 'docs/DECODED_IMAGES.md')
    plan.add(body, 'own:code', evidence, 'decoded gap bodies found by the detector')
    plan.add(D.subtract(gaps, body), 'own:untyped', evidence, 'decoded gap bytes outside a detected body')
    return plan


def word_align_code(unit, plan):
    """A code body is word aligned: zero bytes between a code line and its word boundary belong to the word (a
    function starting with a zero immediate), so the line takes them when no other line or C byte does."""
    taken = D.merge([[a, b] for a, b, _, _ in plan.lines] + unit.c_code + unit.c_data)
    index = C.Index(taken)
    grown = []
    for a, b, cls, ev in plan.lines:
        if cls in ('own:code', 'own:vendor'):
            floor, ceiling = a & ~3, (b + 3) & ~3
            lo2 = a
            while lo2 > floor and not index.has(lo2 - 1) and unit.data[lo2 - 1] == 0:
                lo2 -= 1
            hi2 = b
            while hi2 < ceiling and hi2 < unit.size and not index.has(hi2) and unit.data[hi2] == 0:
                hi2 += 1
            a, b = lo2, hi2
        grown.append((a, b, cls, ev))
    plan.lines = grown


def _group(lines):
    groups = defaultdict(list)
    for a, b, cls, ev in sorted(lines):
        groups[(cls, ev)].append((a, b))
    return groups


def write_lines(root, units, plans):
    directory = root / C.LINE_DIR
    directory.mkdir(exist_ok=True)
    written = {}
    for key, plan in plans.items():
        unit = units[key]
        name = key if unit.kind == 'file' else 'decoded_' + key[len('decoded:'):].replace('/', '_')
        merged = []
        for (cls, ev), group in sorted(_group(plan.lines).items()):
            current = None
            for a, b in group:
                if current is not None and current[1] == a and not cls.startswith('own:stream:'):
                    current[1] = b
                else:
                    current = [a, b, cls, ev]
                    merged.append(current)
        merged.sort(key=lambda x: (x[0], x[1], x[2], x[3]))
        parts, text, size = [], ['# schema ' + C.SCHEMA], 0
        for a, b, cls, ev in merged:
            row = '%s\t%s\t%s\t%s\t%s' % (C.hx(a), C.hx(b), cls, ev, C.line_digest(unit.data, a, b))
            if size + len(row) > PART_LIMIT:      # a file stays under the publish scan's size rule
                parts.append(text)
                text, size = ['# schema ' + C.SCHEMA], 0
            text.append(row)
            size += len(row) + 1
        parts.append(text)
        for old in directory.glob(name + '*.tsv'):
            if old.stem.split('.')[0] == name:
                old.unlink()
        for index, text in enumerate(parts):
            suffix = '' if len(parts) == 1 else '.%03d' % index
            (directory / (name + suffix + '.tsv')).write_text('\n'.join(text) + '\n')
        written[key] = merged
    return written


def run(root, labels=None, census=None):
    """Plan and write the exception files; returns (units, plans, written lines, carved bytes, census)."""
    root = Path(root)
    receipt = C.load_proof(root)
    data = C.load_disc(root)
    units = {fam: C.Unit(fam, data[fam]) for fam in C.FILES}
    C.load_cover(root, receipt, units)
    decoded = C.load_decoded(root, receipt)
    units.update(decoded)
    if labels is None:
        labels = C.default_labels(root)
    if census is None:
        sys.path.insert(0, str(C.TOOL_ROOT / 'tools'))
        from decoded import census as CE
        census = CE.census_files({f: data[f] for f in ('main', 'town', 'dungeon', 'ovmovie')}, extended=False)
    streams = {}
    for unit in decoded.values():
        for s in unit.manifest['streams']:
            fam = Path(s['container']).name.split('_')[0].lower()
            streams[(fam, int(s['offset'], 0))] = (s['used'], s['size'], s['source_sha256'], s.get('command'), unit.key.split('/')[-1])
    for r in census['streams']:
        streams.setdefault((r['container'], int(r['offset'], 16)), (r['used'], r['size'], r['source_sha256'], None, 'census'))
    sdk = sdk_extents(root) if (root / 'ledger/sdk_objects.jsonl').is_file() else {}
    plans = {}
    stale = {}
    for fam in C.FILES:
        windows = list(STALE_WINDOWS.get(fam, ()))
        for image, start, end, _d in units[fam].images:
            if image in STALE_VIEWS.get(fam, ()):
                windows.append((start, end))
        stale[fam] = stale_runs(units[fam].data, units[STALE_SOURCE].data, windows) if windows else []
    for fam in C.FILES:
        foreign = [(a, b, p, e) for f, a, b, p, e in FOREIGN if f == fam and b <= units[fam].size]
        plans[fam] = plan_file(root, units[fam], labels, part_ranges(root, fam), sdk, streams, foreign, stale[fam])
    for key, unit in decoded.items():
        plans[key] = decoded_plan(unit)
    carved = Counter()      # nothing is cut: a hit inside a line stays an open hit of the check
    for key, unit in units.items():
        word_align_code(unit, plans[key])
        if unit.kind == 'file':
            retype_code_lines(unit, plans[key])
    written = write_lines(root, units, plans)
    return units, plans, written, carved, census


def summarize(units, plans, written, carved):
    lines = []
    per = defaultdict(lambda: [0, 0])
    for key, merged in written.items():
        for a, b, cls, ev in merged:
            k = (key, cls.split(':')[0] + ':' + cls.split(':')[1])
            per[k][0] += 1
            per[k][1] += b - a
    lines.append('BOOTSTRAP lines per file and class (lines, bytes)')
    for (key, cls), (n, b) in sorted(per.items()):
        lines.append('  %-28s %-14s %7d lines %14s B' % (key, cls, n, C.fmt(b)))
    lines.append('BOOTSTRAP lines per evidence source (bytes)')
    src = Counter()
    for key, plan in plans.items():
        for label, b in plan.source.items():
            src[label] += b
    for label, b in sorted(src.items()):
        lines.append('  %-60s %14s B' % (label, C.fmt(b)))
    return lines


def write_disc_files(root):
    """One whole-file line per disc file that is not a program file (class own:media), by size and sha1."""
    import hashlib
    base = root / C.DISC_ROOT
    skip = {'MAIN/MAIN.BIN', 'TOWN/TOWN.BIN', 'DUNGEON/DUNGEON.BIN', 'OVMOVIE.BIN', 'SLUS_006.14'}
    rows = ['# schema closure.disc.v1: path, size, class, evidence, sha1 (disc files that are not program files)']
    if base.is_dir():
        for path in sorted(p for p in base.rglob('*') if p.is_file()):
            rel = path.relative_to(base).as_posix()
            if rel in skip:
                continue
            blob = path.read_bytes()
            rows.append('%s\t%d\town:media\tledger/containers.jsonl\t%s' % (rel, len(blob), hashlib.sha1(blob).hexdigest()))
    (root / C.LINE_DIR / 'disc_files.tsv').write_text('\n'.join(rows) + '\n')
    return len(rows) - 1


def write_streams(root, census):
    rows = ['# schema closure.streams.v1: file, offset, used, decoded size, source sha256 (the committed code stream census)']
    for r in sorted(census['streams'], key=lambda r: (r['container'], int(r['offset'], 16))):
        rows.append('%s\t%s\t%s\t%s\t%s' % (r['container'], r['offset'], hex(r['used']), hex(r['size']), r['source_sha256']))
    (root / C.LINE_DIR / 'streams.tsv').write_text('\n'.join(rows) + '\n')


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--out', default='build/closure_bootstrap')
    args = parser.parse_args(argv)
    root = Path.cwd() if (Path.cwd() / 'config/link_graph').is_dir() else C.TOOL_ROOT
    units, plans, written, carved, census = run(root)
    out = Path(args.out)
    out = out if out.is_absolute() else root / out
    out.mkdir(parents=True, exist_ok=True)
    lines = summarize(units, plans, written, carved)
    (out / 'summary.txt').write_text('\n'.join(lines) + '\n')
    print('\n'.join(lines))
    write_streams(root, census)
    print('BOOTSTRAP disc_files.tsv: %d whole-file lines' % write_disc_files(root))
    return 0


if __name__ == '__main__':
    sys.exit(main())
