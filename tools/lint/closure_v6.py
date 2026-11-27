"""Ownership check, v6: the tests of the declared classes and what a landing's reader sees.

Everything here is a pure function of the units, the lines and git (the base of the comparison is read by the
caller, never named by an argument). Nothing reads bytes into the output; the output holds offsets, sizes, ids and
hashes. Called from closure.analyse(); the findings it adds are refusal-class lines that the landing prints in full.

Declared classes tested here (a line can be true or false; each test refuses what a machine can tell):
  region:unreached   evidence must be `config/closure_rulings.tsv#<ruling id>` and the id must be a row of that file
  region lines       refused inside a decoded image (this build's own code: it has no foreign program)
  ack:...:data       over a run the detector reads as a function body with a return: needs a reason from a fixed
                     list, and never over a run that has the shape of a function (frame and saved return, a
                     restored return before a return word, two calls to known function starts)
  own:stream         a minimum compressed size; outside a decoded manifest (no recompression proof) a larger one
  own:vendor         the SDK object record it cites must be unchanged since the base (rows added or changed in
                     the landing are listed and refused)
  region:*           over a range that had load evidence at the base is refused, and each demoted or removed load
                     record is printed as a refusal-class line
No machine test can tell whether a `region:other` line over a fragment in no image is true, or whether a ruling row
says what it claims: every added line and ruling row is printed in full instead (see landing_lines).
"""
import hashlib
import json
import struct
import subprocess
from collections import defaultdict
from pathlib import Path

import closure_detect as D

RULINGS = 'config/closure_rulings.tsv'
ACK_DATA_REASONS = ('jump_table', 'command_table', 'coordinate_table', 'text_words', 'coincidental_words')
MIN_STREAM = 0x40            # compressed bytes of any registered stream
MIN_STREAM_UNPROVEN = 0x200  # a stream with no recompression proof (a streams.tsv row)
TOOL_GLOBS = ('tools/lint/closure*.py', 'tools/lint/test_closure*.py', 'config/closure/*', 'config/closure_rulings.tsv',
              'config/asm_templates.tsv', 'docs/CLOSURE.md', 'tools/build/cover.py', 'tools/build/land_make.py',
              'tools/decoded_images.py', 'Makefile')
LEDGERS = ('ledger/sdk_objects.jsonl', 'ledger/coverage_residue.jsonl')
LOADS = 'ledger/instance_load_regions.jsonl'


def sha256(data):
    return hashlib.sha256(data).hexdigest()


def hx(n):
    return '0x%x' % n


def git(root, *argv):
    return subprocess.run(['git', *argv], cwd=root, capture_output=True, text=True)


def git_bytes(root, base, path):
    done = subprocess.run(['git', 'show', '%s:%s' % (base, path)], cwd=root, capture_output=True)
    return done.stdout if done.returncode == 0 else None


# ---- rulings ----
def ruling_ids(text):
    ids = set()
    for raw in text.splitlines():
        if raw.strip() and not raw.startswith('#'):
            ids.add(raw.split('\t')[0])
    return ids


def load_rulings(root):
    path = Path(root) / RULINGS
    return ruling_ids(path.read_text()) if path.is_file() else set()


# ---- tests of the declared classes ----
def function_shaped(words, starts):
    """The triage's function-shape test over the words of a run: a frame word with a saved return address within 8
    words, a restored return address (load into $31 from $29) followed within 4 words by a return word, or two calls
    to known function starts."""
    n = len(words)
    for i, w in enumerate(words):
        if D.is_frame(w) and any(D.is_ra_save(words[j]) for j in range(i + 1, min(i + 9, n))):
            return 'frame'
        if w >> 26 == 35 and (w >> 16) & 31 == 31 and (w >> 21) & 31 == 29 and D.JR in words[i + 1:i + 5]:
            return 'restored_return'
    calls = sum(1 for w in words if w >> 26 == 3 and (0x80000000 | (w & 0x3ffffff) << 2) in starts)
    return 'calls' if calls >= 2 else ''


def declared_tests(root, units, streams, base, findings, known_starts):
    """Findings for the declared classes (see the module text). `streams` is closure.load_streams' result."""
    rulings = load_rulings(root)
    ack_data = defaultdict(list)
    for unit in units.values():
        for ln in unit.lines:
            if ln.cls.startswith('region:') and unit.kind == 'decoded':
                findings.append(('region_decoded', 'region_decoded %s %s %s..%s: a decoded image is this build\'s own code; '
                                 'a region line is refused there' % (unit.key, ln.cls, hx(ln.start), hx(ln.end))))
            if ln.cls.startswith('region:unreached:'):
                path, _, key = ln.evidence.partition('#')
                if path != RULINGS or key not in rulings:
                    findings.append(('region_unreached', 'region_unreached %s %s..%s: the evidence must be %s#<ruling id> '
                                     'of a row of that file; no ruling, no line (got %s)' % (
                                         unit.key, hx(ln.start), hx(ln.end), RULINGS, ln.evidence)))
            if ln.layer == 'ack' and ln.cls.endswith(':data'):
                rule = ln.cls.split(':')[1]
                span = unit.data[ln.start:ln.end]
                words = struct.unpack_from('<%dI' % (len(span) // 4), span) if len(span) >= 4 else ()
                has_return = D.JR in words
                if rule == 'D1' or has_return:
                    path, _, reason = ln.evidence.partition('#')
                    if reason not in ACK_DATA_REASONS:
                        findings.append(('ack_data_reason', 'ack_data_reason %s %s..%s %s: data over a body with a return needs '
                                         'a reason from %s after # in the evidence (got %s)' % (
                                             unit.key, hx(ln.start), hx(ln.end), rule, ', '.join(ACK_DATA_REASONS),
                                             ln.evidence)))
                    ack_data[reason or '-'].append((unit.key, ln.start, ln.end))
                shape = function_shaped(words, known_starts)
                if shape:
                    findings.append(('ack_data_function', 'ack_data_function %s %s..%s %s: the run has the shape of a function '
                                     '(%s); it cannot be acknowledged as data' % (unit.key, hx(ln.start), hx(ln.end), rule, shape)))
            if ln.cls.startswith('own:stream:') and unit.kind == 'file':
                hit = next(((used, size, ssha, cmd) for (fam, off), (used, size, ssha, cmd) in streams.items()
                            if fam == unit.key and off == ln.start), None)
                if hit is not None:
                    used, size, _s, cmd = hit
                    least = MIN_STREAM if cmd is not None else MIN_STREAM_UNPROVEN
                    if used < least or size < used // 2:
                        findings.append(('stream_short', 'stream_short %s %s..%s: a registered stream %s is at least 0x%x '
                                         'compressed bytes (this one: 0x%x, decoded 0x%x)' % (
                                             unit.key, hx(ln.start), hx(ln.end),
                                             'with a recompression proof' if cmd is not None else 'without one', least, used, size)))
    if base:
        ledger = ledger_delta(root, base)
        for unit in units.values():
            for ln in unit.lines:
                if ln.cls == 'own:vendor':
                    path, _, key = ln.evidence.partition('#')
                    if path in ledger and key in ledger[path]['added'] | ledger[path]['changed']:
                        findings.append(('vendor_row_new', 'vendor_row_new %s %s..%s: the SDK record %s#%s was added or '
                                         'changed in this landing' % (unit.key, hx(ln.start), hx(ln.end), path, key)))
                    for other in LEDGERS:
                        if path != other and key and key in (ledger.get(other, {}).get('added', set()) | ledger.get(other, {}).get('changed', set())):
                            findings.append(('vendor_row_new', 'vendor_row_new %s %s..%s: the row %s was added or changed in %s in this '
                                             'landing' % (unit.key, hx(ln.start), hx(ln.end), key, other)))
    return dict(ack_data=dict(ack_data), rulings=rulings)


# ---- ledgers ----
def jsonl_by_id(text):
    out = {}
    for raw in text.splitlines():
        if raw.strip():
            try:
                row = json.loads(raw)
            except ValueError:
                continue
            out[row.get('id') if isinstance(row, dict) else raw] = raw
    return out


def ledger_delta(root, base):
    """{ledger path: dict(sha, base_sha, added, changed, removed)} for the SDK ledgers (rows by id)."""
    out = {}
    for path in LEDGERS:
        now = (Path(root) / path).read_bytes() if (Path(root) / path).is_file() else b''
        old = git_bytes(root, base, path) or b''
        a, b = jsonl_by_id(now.decode()), jsonl_by_id(old.decode())
        out[path] = dict(sha=sha256(now), base_sha=sha256(old),
                         added=set(a) - set(b), removed=set(b) - set(a),
                         changed={k for k in set(a) & set(b) if a[k] != b[k]})
    return out


# ---- load evidence at the base ----
def base_load_records(root, base):
    """[(container, foff, size, record json)] of the load records that establish a retail load at the base, and the
    link documents' load ranges at the base: list of (family, start, end, description)."""
    import closure
    out = []
    text = git_bytes(root, base, LOADS)
    records = {}
    for raw in (text.decode().splitlines() if text else []):
        if raw.strip():
            rec = json.loads(raw)
            records[sha256(raw.encode())] = rec
            if closure.establishes_load(rec):
                out.append((rec['container'], rec['foff'], rec['foff'] + rec['size'], 'load record ' + raw))
    listing = git(root, 'ls-tree', '-r', '--name-only', base, 'config/link').stdout.split()
    for name in sorted(n for n in listing if n.endswith('.json') and n.count('/') == 3):
        blob = git_bytes(root, base, name)
        try:
            doc = json.loads(blob)
        except (TypeError, ValueError):
            continue
        if doc.get('load_evidence'):
            start = int(doc['foff'], 0) if isinstance(doc['foff'], str) else doc['foff']
            size = int(doc['size'], 0) if isinstance(doc['size'], str) else doc['size']
            rec = records.get(doc['load_evidence'].get('record_sha256'))
            vma = int(doc['vma'], 0) if isinstance(doc.get('vma'), str) else doc.get('vma')
            ok = closure.establishes_load(rec) if rec is not None else (
                vma is None or closure.RETAIL_RAM[0] <= vma < closure.RETAIL_RAM[1]) and 'not established' not in doc.get('evidence', '')
            if ok:
                out.append((doc['container'], start, start + size, 'image document ' + name))
    return out


def load_changes(root, base, regions, units, findings):
    """Load evidence that held at the base and no longer does (a demoted or removed record, a changed link
    document), and region lines over such a range. Returns (demoted lines, changed link documents)."""
    demoted, linkdocs = [], []
    if not base:
        return demoted, linkdocs
    now = {(fam, a, b) for fam, a, b in regions}
    for fam, a, b, what in base_load_records(root, base):
        if (fam, a, b) in now:
            continue
        text = 'load_demoted %s %s..%s: load evidence of the base no longer holds: %s' % (fam, hx(a), hx(b), what)
        findings.append(('load_demoted', text))
        demoted.append((fam, a, b, text))
    for fam, a, b, text in demoted:
        unit = units.get(fam)
        if unit is None:
            continue
        for ln in unit.lines:
            if ln.cls.startswith('region:') and ln.start < b and a < ln.end:
                findings.append(('region_demoted', 'region_demoted %s %s %s..%s lies over a range that had load evidence at '
                                 'the base (%s..%s)' % (fam, ln.cls, hx(ln.start), hx(ln.end), hx(a), hx(b))))
    listing = git(root, 'ls-tree', '-r', '--name-only', base, 'config/link').stdout.split()
    for name in sorted(n for n in listing if n.endswith('.json') and n.count('/') == 3):
        path = Path(root) / name
        old = git_bytes(root, base, name)
        if path.is_file() and old is not None and path.read_bytes() != old:
            try:
                a, b = json.loads(path.read_bytes()), json.loads(old)
                keys = sorted(k for k in set(a) | set(b) if a.get(k) != b.get(k))
            except ValueError:
                keys = ['(unreadable)']
            linkdocs.append('LINKDOC changed %s: %s' % (name, ', '.join(keys) or 'bytes'))
    return demoted, linkdocs


# ---- the tool's own files ----
def tool_changes(root, base):
    """(changed tool files, changed rule constants) against the base: one landing line."""
    if not base:
        return [], []
    names = set(git(root, 'diff', '--name-only', base, '--', *TOOL_GLOBS).stdout.split())
    names |= set(git(root, 'ls-files', '--others', '--exclude-standard', '--', *TOOL_GLOBS).stdout.split())
    constants = []
    for name in sorted(n for n in names if n.startswith('tools/lint/closure') and n.endswith('.py')):
        diff = git(root, 'diff', '-U0', base, '--', name).stdout
        for raw in diff.splitlines():
            if raw[:1] in '+-' and raw[:3] not in ('+++', '---'):
                token = raw[1:].split('=')[0].strip() if '=' in raw else ''
                if token.isidentifier() and token.upper() == token and not raw[1:2].isspace():
                    constants.append('%s %s:%s' % (raw[0], name.rsplit('/', 1)[1], token))
    return sorted(names), sorted(set(constants))


# ---- what the landing's reader sees ----
def changed_pairs(added, removed):
    """Lines that changed in place (same unit and extent, another class, evidence or hash): [(old, new)]."""
    old = {(ln.unit, ln.start, ln.end): ln for ln in removed}
    pairs = []
    for ln in added:
        o = old.get((ln.unit, ln.start, ln.end))
        if o is not None:
            pairs.append((o, ln))
    return pairs


def gained(units, removed):
    """Compiled functions over the extents of removed own:code lines: [(unit, start, size, name)]."""
    out = []
    for ln in removed:
        if ln.cls != 'own:code':
            continue
        unit = units.get(ln.unit)
        if unit is None:
            continue
        names = {}
        if unit.kind == 'decoded':
            names = {f['offset']: f['name'] for f in unit.proof.get('functions', ())}
        for a, b in unit.funcs:
            if a < ln.end and ln.start < b:
                out.append((ln.unit, a, b - a, names.get(a, '')))
    return sorted(set(out))


def landing_lines(res):
    """Every line a landing's reader needs, in full and uncut."""
    units = res['units']
    added, removed, newly = res['delta']
    lines = []
    files, constants = res.get('tool_changes', ([], []))
    if files or constants:
        lines.append('TOOLFILES changed in this landing: %s | rule constants: %s' % (
            ', '.join(files) or 'none', ', '.join(constants) or 'none'))
    pairs = changed_pairs(added, removed)
    paired_new = {id(n) for _, n in pairs}
    paired_old = {id(o) for o, _ in pairs}
    for ln in added:
        if id(ln) not in paired_new:
            lines.append('ADDED %s %s' % (ln.unit, ln.text()))
    for o, n in pairs:
        lines.append('CHANGED %s %s -> %s' % (n.unit, o.text(), n.text()))
    for ln in removed:
        if id(ln) not in paired_old:
            lines.append('REMOVED %s %s' % (ln.unit, ln.text()))
    h = res['headline'][0]
    fell = res['base_headline'] is not None and h < res['base_headline']
    if fell or any(ln.cls == 'own:code' for ln in removed):
        got = gained(units, removed)
        covered = sum(n for _u, _a, n, _name in got)
        lines.append('GAINED C in this landing, over removed own:code lines: %d functions, %d B (headline %s -> %s)%s' % (
            len(got), covered, res['base_headline'], h,
            '' if not fell or covered else ' UNMATCHED: the headline falls and no compiled function lies over a removed line'))
        for unit, a, n, name in got:
            lines.append('GAINED %s %s %d B%s' % (unit, hx(a), n, ' ' + name if name else ''))
    for text in res['region_delta'][0]:
        lines.append('LOADREGION added: ' + text)
    for text in res['region_delta'][1]:
        lines.append('LOADREGION removed: ' + text)
    for _f, _a, _b, text in res.get('demoted', ()):
        lines.append('REFUSAL ' + text)
    lines += res.get('linkdocs', [])
    ledger = res.get('ledger')
    if ledger:
        lines.append('LEDGER ' + ' | '.join('%s sha256 %s (base %s)' % (p.rsplit('/', 1)[1], v['sha'][:16], v['base_sha'][:16])
                                              for p, v in sorted(ledger.items())))
        for path, v in sorted(ledger.items()):
            for kind in ('added', 'changed', 'removed'):
                for key in sorted(v[kind]):
                    lines.append('LEDGER row %s %s: %s' % (kind, path.rsplit('/', 1)[1], key))
    for row in res.get('stream_rows', ()):
        lines.append(row)
    for row in res.get('ruling_rows', ()):
        lines.append(row)
    for row in res.get('template_rows', ()):
        lines.append(row)
    extra = res.get('declared')
    if extra and extra['ack_data']:
        lines.append('ACKDATA %d lines over bodies with a return, by reason: %s' % (
            sum(len(v) for v in extra['ack_data'].values()),
            ', '.join('%s %d' % (k, len(v)) for k, v in sorted(extra['ack_data'].items()))))
    refusal_kinds = ('region_decoded', 'region_unreached', 'ack_data_reason', 'ack_data_function', 'stream_short',
                     'vendor_row_new', 'region_demoted', 'load_demoted', 'entry_over_c', 'entry_overlap', 'unknown',
                     'own_data', 'stale_test', 'ack_stale', 'region_in_load', 'stream', 'vendor_extent', 'vendor_calls_game')
    for kind, text in res['findings']:
        if kind in refusal_kinds and not text.startswith('load_demoted'):
            lines.append('REFUSAL ' + text)
    return lines


def text_delta(root, base, path):
    """Rows added and removed in one tab file against the base: (added, removed)."""
    old = git_bytes(root, base, path) if base else None
    now = (Path(root) / path).read_text() if (Path(root) / path).is_file() else ''
    a = {l for l in now.splitlines() if l.strip() and not l.startswith('#')}
    b = {l for l in (old.decode().splitlines() if old else []) if l.strip() and not l.startswith('#')}
    return sorted(a - b), sorted(b - a)


def row_changes(root, base, path, tag):
    """Landing lines for the rows of one allowlist file against the base, each in full, uncut: `<TAG> added|removed|changed <row>`.
    A row whose first cell (for the templates file: its first two cells) is the same in an added and a removed row is `changed`."""
    added, removed = text_delta(root, base, path)
    def key(row):
        cells = row.split('\t')
        return tuple(cells[:2]) if path.endswith('asm_templates.tsv') and cells[0] != 'template' else (cells[0],)
    old = {key(r): r for r in removed}
    lines, paired = [], set()
    for row in added:
        if key(row) in old and old[key(row)] != row:
            lines.append('%s changed %s -> %s' % (tag, old[key(row)], row))
            paired.add(key(row))
        else:
            lines.append('%s added %s' % (tag, row))
    for row in removed:
        if key(row) not in paired:
            lines.append('%s removed %s' % (tag, row))
    return lines
