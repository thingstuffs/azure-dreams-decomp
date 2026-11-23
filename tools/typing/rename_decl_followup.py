#!/usr/bin/env python3
"""Declaration follow-up for symbol renames: make the other declarations of a renamed symbol agree with its definition.

    rename_decl_followup.py --symbols TABLE [--symbols MORE ...] [--names a,b] [--root R] [--dry-run]
                            [--report REPORT.tsv] [--workers N] [--tu T ...] [--max-tus N] [--allow-width-changes]
                            [--no-clang]

A symbol rename (apply_names, a rename package's reapply) rewrites the old spelling everywhere, including the
declarations that spelled it.  Those declarations were written for an address-named alias and never had to agree
with the definition (header `void func_80159590(void*, int, void*, void*)` beside a definition
`void advance_block_path_slot_c(void*, ObjectPosition*, void*, void*)`).  Once both carry the same name the compiler
reports conflicting types, and tools/lint/decl_agreement.py --fail-new fails.  rename_members_batch's route is used
here too: the tree's own declaration scan finds the stale declarations, the compiler front end (clang -fsyntax-only,
mipsel target, over the consumer TUs of the edited files) judges each edit, and a declaration whose rewrite makes
the compiler report a NEW error is put back and held.

For every name in the table that has a definition, each declaration that disagrees with it (decl_agreement's
normalisation: whitespace, parameter names, scalar typedefs, an empty `()` agrees with anything) is rewritten to the
definition's return type and parameter list:
  * a declaration `f(void)` or `f()` of a definition that takes parameters becomes `f()` (an unprototyped
    declaration: byte-neutral for every caller);
  * otherwise it takes the definition's spelling.  An edit is byte-neutral when every changed position keeps the
    32-bit register class (pointer, int, unsigned, long) and the return stays value-or-void; an edit that changes a
    short/char/struct/float position, a return between void and a value, or the argument count is WIDTH-RISK: held,
    unless --allow-width-changes (then it still needs the scoped proof of its consumers).
The compiler pass compares each consumer TU's error lines with its own error lines before the edit (position
stripped): a new line is blamed on the edited names it mentions (else on the edited file it is reported in), those
edits are reverted and held, and the pass repeats (3 rounds).  --no-clang skips the compiler pass (unit tests).

Data externs (`extern u8 dir_step_x[]` against `short dir_step_x[8]`) are never rewritten: two typed views of one
address cannot be merged by a text edit without changing how every consumer reads it.  They are listed with every
declaration, its type, the symbol's address and size so that each can be settled by name or by type.

Report TSV: name, file, line, status (applied|held|planned), class (neutral|width-risk|data), declared, definition, reason.
"""
from __future__ import annotations

import argparse
import collections
import re
import subprocess
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
TOOLS = HERE.parent
sys.path[:0] = [str(TOOLS), str(TOOLS / 'lint'), str(HERE)]

import decl_agreement as D  # noqa: E402
import lint_closure as C  # noqa: E402
import ledger_rekey as K  # noqa: E402
from rename_members_batch import consumers, other_key, read_text, write_atomic  # noqa: E402

STORAGE = ('extern', 'static', 'inline', '__inline', '__inline__', 'register', 'auto')
REG32 = {'int', 'unsigned', 'long', 'unsigned long', 'signed', 'unsigned int'}
SMALL = {'char', 'signed char', 'unsigned char', 'short', 'unsigned short', 'short int', 'unsigned short int'}


class Occurrence:
    def __init__(self, **kw):
        self.__dict__.update(kw)


def mask(text):
    """Comments, strings and preprocessor lines blanked; same length and same newlines as the text."""
    text = text.replace('\\\n', ' \n')
    blank = lambda m: re.sub(r'[^\n]', ' ', m.group(0))
    text = C.COMMENT_OR_STRING.sub(blank, text)
    return '\n'.join(' ' * len(line) if line.lstrip().startswith('#') else line for line in text.split('\n'))


def occurrences(masked, name):
    """Declarations and definitions of `name` in a masked text (decl_agreement.declarations' rules, with spans)."""
    found = []
    for match in re.finditer(r'\b' + re.escape(name) + r'\s*\(', masked):
        open_paren = match.end() - 1
        close = D.find_matching(masked, open_paren)
        if close < 0:
            continue
        tail = masked[close + 1:close + 200].lstrip()
        tail = re.sub(r'^(?:__attribute__\s*\(\(.*?\)\)\s*)+', '', tail)
        if not tail or tail[0] not in ';{':
            continue
        begin = max(masked.rfind(c, 0, match.start()) for c in ';{}')
        raw = masked[begin + 1:match.start()]
        head = raw.strip()
        words = D.TOKEN.findall(head)
        if not words or any(w in D.KEYWORD_HEADS for w in words) or any(c in head for c in '=(:,?!+-/&|'):
            continue
        if not any(re.match(r'[A-Za-z_]', w) and w not in D.STORAGE for w in words):
            continue
        found.append(Occurrence(name=name, start=begin + 1 + len(raw) - len(raw.lstrip()), open=open_paren,
                                close=close, kind='def' if tail[0] == '{' else 'decl', words=words,
                                line=masked.count('\n', 0, match.start()) + 1))
    return found


def type_class(t):
    t = t.strip()
    if t == 'void':
        return 'void'
    if t.endswith('*') or '(*)' in t or t.endswith(']'):
        return 'reg32'
    if t in REG32:
        return 'reg32'
    if t in SMALL:
        return 'small'
    return 'other'


def edit_class(declared, expected):
    """neutral | width-risk for a rewrite from the declared signature to the expected one (decl_agreement forms)."""
    def split(sig):
        m = re.match(r'(.*?)\b[A-Za-z_]\w*\((.*)\)$', sig)
        ret, params = m.group(1).strip(), m.group(2).strip()
        return ret, [] if params in ('', 'void') else [p.strip() for p in params.split(',')]
    (ra, pa), (rb, pb) = split(declared), split(expected)
    if not pa and declared.endswith('(void)'):
        return 'neutral'                  # becomes an unprototyped declaration
    if len(pa) != len(pb):
        return 'width-risk'
    if ra != rb:
        ca, cb = type_class(ra), type_class(rb)
        if not (ca == cb == 'reg32'):
            return 'width-risk'
    for a, b in zip(pa, pb):
        if a != b and not (type_class(a) == type_class(b) == 'reg32'):
            return 'width-risk'
    return 'neutral'


class Edit:
    def __init__(self, name, rel, line, declared, expected, expected_at):
        self.name, self.rel, self.line = name, rel, line
        self.declared, self.expected, self.expected_at = declared, expected, expected_at
        self.klass = edit_class(declared, expected)
        self.status, self.reason = 'planned', ''
        self.span = None            # (start, end) in the file text
        self.new = None


def definition_spelling(root, expected_at, name):
    """(return type text, parameter text) as the definition spells them, or (None, reason)."""
    rel, _, line = expected_at.rpartition(':')
    if not line.isdigit():
        rel, line = expected_at, None
    path = Path(root) / rel
    if not path.is_file():
        return None, f'definition file {rel} not found'
    text = read_text(path)
    masked = mask(text)
    for occ in occurrences(masked, name):
        if occ.kind == 'def' and 'static' not in occ.words and (line is None or occ.line == int(line)):
            head = ' '.join(text[occ.start:masked.index(name, occ.start)].split())
            head = re.sub(r'^(?:(?:extern|static|inline|__inline|__inline__|register|auto)\s+)+', '', head)
            params = text[occ.open + 1:occ.close]
            if '/*' in params or '//' in params:
                return None, 'definition parameter list holds a comment'
            return (head, ' '.join(params.split())), None
    return None, f'definition of {name} not found at {expected_at}'


def new_since(root, base, names):
    """decl_agreement's own split: the declarations that disagree on the tree but did not on --base, plus the
    `void *` stand-ins it reports separately (void_pointer_stale): GCC converts a data pointer to void * silently, but
    two declarations of one function with void * and a record pointer conflict, so they follow the definition too."""
    import tempfile
    with tempfile.TemporaryDirectory(prefix='decl_followup.') as temporary:
        base_tree = C.materialize(root, base, Path(temporary) / 'base')
        new = D.new_problems(base_tree, root, names, None, D.function_renames(root, base, root))[0]
        return new + D.void_pointer_stale(base_tree, root, names, None)


def plan_edits(root, names, log=print, base=None):
    if base:
        problems = new_since(root, base, names)
    else:
        found, void = D.scan_tree(root, names)
        problems = found + void
    problems = sorted(problems, key=lambda p: (p['file'], p['line'], p['name']))
    edits, seen = [], set()
    for p in problems:
        key = (p['file'], p['line'], p['name'])
        if key in seen:
            continue
        seen.add(key)
        edits.append(Edit(p['name'], p['file'], p['line'], p['declared'], p['expected'], p['expected_at']))
    texts, masks = {}, {}
    for e in edits:
        text = texts.setdefault(e.rel, read_text(Path(root) / e.rel))
        masked = masks.setdefault(e.rel, mask(text))
        found = [o for o in occurrences(masked, e.name) if o.line == e.line and o.kind == 'decl']
        if len(found) != 1:
            e.status, e.reason = 'held', f'declaration not located ({len(found)} candidates at line {e.line})'
            continue
        occ = found[0]
        if '/*' in text[occ.start:occ.close + 1] or '//' in text[occ.start:occ.close + 1]:
            e.status, e.reason = 'held', 'a comment sits inside the declaration'
            continue
        spelled = definition_spelling(root, e.expected_at, e.name)
        if spelled[0] is None:
            e.status, e.reason = 'held', spelled[1]
            continue
        ret, params = spelled[0]
        old_params = ' '.join(text[occ.open + 1:occ.close].split())
        kept = ' '.join(w for w in occ.words if w in ('extern', 'static'))
        new_params = '' if old_params in ('', 'void') else params
        e.new = (kept + ' ' if kept else '') + f'{ret} {e.name}({new_params})'
        e.span = (occ.start, occ.close + 1)
    return edits


def materialize(root, edits, originals):
    """Write every touched file from its original text with the active edits applied (atomic per file)."""
    by_file = collections.defaultdict(list)
    for e in edits:
        if e.span and e.status == 'applied':
            by_file[e.rel].append(e)
    for rel in originals:
        text = originals[rel]
        for e in sorted(by_file.get(rel, []), key=lambda x: -x.span[0]):
            text = text[:e.span[0]] + e.new + text[e.span[1]:]
        path = Path(root) / rel
        if read_text(path) != text:
            write_atomic(path, text)


def clang_errors(root, rel):
    """[(error line, error line plus its notes)]: the notes name the functions an error is about."""
    res = subprocess.run(['nice', '-n', '10', 'clang', '--target=mipsel-unknown-none', '-w', '-fsyntax-only',
                          '-ferror-limit=0', '-I', 'include', rel], cwd=str(root), capture_output=True, text=True)
    out, block = [], None
    head = re.compile(r'^[^\s:][^:]*:\d+:\d+: ')
    for line in res.stderr.splitlines():
        if ': error:' in line or ': fatal error:' in line:
            block = [line, line]
            out.append(block)
        elif block is not None and head.match(line) and not re.match(r'^[^\s:][^:]*:\d+:\d+: (?:note|warning):', line):
            block = None
        elif block is not None:
            block[1] += '\n' + line          # notes, the source excerpt and the caret line
    return [tuple(b) for b in out]


def error_pass(root, tus, workers):
    with ThreadPoolExecutor(max_workers=workers) as pool:
        return dict(zip(tus, pool.map(lambda t: clang_errors(root, t), tus)))


def validation_tus(root, edits, names, explicit, max_tus, log):
    if explicit:
        return sorted(explicit)
    files = {e.rel for e in edits if e.span}
    headers = {f for f in files if not f.endswith('.c')}
    tus = {f for f in files if f.endswith('.c')}
    if headers:
        tus |= set(consumers(root, headers))
    tus = sorted(t for t in tus if (Path(root) / t).is_file())
    if len(tus) > max_tus:
        words = re.compile(r'\b(?:' + '|'.join(re.escape(n) for n in sorted(names)) + r')\b')
        kept = [t for t in tus if t in files or words.search(read_text(Path(root) / t))]
        log(f'{len(tus)} consumer TUs; {len(kept)} that spell an edited name are compiled (--max-tus {max_tus})')
        tus = kept
    return tus


def run(root, names, dry_run=False, workers=2, explicit_tus=None, max_tus=600, allow_width=False, use_clang=True,
        log=print, base=None):
    root = Path(root).resolve()
    edits = plan_edits(root, names, log, base)
    for e in edits:
        if e.status == 'planned' and e.klass == 'width-risk' and not allow_width:
            e.status, e.reason = 'held', 'width-risk: the rewrite changes a short/char/struct position, a void/value ' \
                                         'return or the argument count; needs the scoped proof of its consumers'
    active = [e for e in edits if e.status == 'planned' and e.span]
    log(f'{len(edits)} stale declarations of {len({e.name for e in edits})} names; {len(active)} editable, '
        f'{len([e for e in edits if e.status == "held"])} held before the compiler pass')
    if dry_run:
        return edits, []
    originals = {e.rel: read_text(root / e.rel) for e in active}
    tus, before = [], {}
    if use_clang and active:
        tus = validation_tus(root, active, {e.name for e in active}, explicit_tus, max_tus, log)
        log(f'baseline compiler pass over {len(tus)} TUs')
        before = error_pass(root, tus, workers)
    for e in active:
        e.status = 'applied'
    materialize(root, edits, originals)
    unattributed = []
    try:
        for round_no in range(1, 4):
            if not (use_clang and active):
                break
            live = [e for e in active if e.status == 'applied']
            if not live:
                break
            after = error_pass(root, tus, workers)
            revert, unattributed = set(), []
            for tu in tus:
                new = collections.Counter(other_key(x[0]) for x in after[tu]) - collections.Counter(
                    other_key(x[0]) for x in before[tu])
                for line, block in after[tu]:
                    key = other_key(line)
                    if new[key] <= 0:
                        continue
                    new[key] -= 1
                    blamed = {e.name for e in live if re.search(r"\b" + re.escape(e.name) + r"\b", block)}
                    if not blamed:
                        blamed_files = {e.rel for e in live if line.startswith(e.rel + ':')}
                        blamed = {e.name for e in live if e.rel in blamed_files}
                    if blamed:
                        revert |= blamed
                        for e in live:
                            if e.name in blamed and not e.reason:
                                e.reason = f'{tu}: {key[:160]}'
                    else:
                        unattributed.append(f'{tu}: {key[:160]}')
            log(f'round {round_no}: {len(revert)} names reverted, {len(unattributed)} unattributed new error lines')
            if not revert:
                break
            for e in live:
                if e.name in revert:
                    e.status = 'held'
                    e.reason = 'compiler: new error: ' + e.reason
            materialize(root, edits, originals)
    except BaseException:
        for e in edits:
            if e.status == 'applied':
                e.status = 'planned'
        materialize(root, edits, originals)
        raise
    return edits, unattributed


def data_report(root, names):
    """Per data name: every declaration and definition type, with the symbol's address and size."""
    root = Path(root)
    result, _ = D.data_census(root)
    addresses = D.name_addresses(root)
    out = []
    for name in sorted(n for n in result if n.split('@')[0] in names):
        row = result[name]
        out.append((name, D.address_of(name, addresses), row['klass'], row['rows']))
    return out


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument('--root', type=Path, default=TOOLS.parent)
    parser.add_argument('--symbols', action='append', default=[], metavar='TABLE')
    parser.add_argument('--names', help='comma-separated new names instead of (or beside) a table')
    parser.add_argument('--base', help='revision before the renames: only declarations that did not disagree there '
                        '(the ones decl_agreement --fail-new counts) are edited; without it every disagreeing '
                        'declaration of the names is')
    parser.add_argument('--dry-run', action='store_true')
    parser.add_argument('--report', type=Path)
    parser.add_argument('--workers', type=int, default=2)
    parser.add_argument('--tu', action='append', default=[], help='compile exactly these TUs for the compiler pass')
    parser.add_argument('--max-tus', type=int, default=600)
    parser.add_argument('--allow-width-changes', action='store_true')
    parser.add_argument('--no-clang', action='store_true')
    parser.add_argument('--no-data', action='store_true')
    args = parser.parse_args(argv)
    names = set()
    for table in args.symbols:
        names |= {new for _, new, _ in K.read_symbols(table)}
    if args.names:
        names |= set(args.names.split(','))
    if not names:
        parser.error('no names: give --symbols or --names')
    edits, unattributed = run(args.root, names, args.dry_run, args.workers, args.tu, args.max_tus,
                              args.allow_width_changes, not args.no_clang, log=lambda s: print(s, flush=True), base=args.base)
    counts = collections.Counter(e.status for e in edits)
    print('declarations: ' + ', '.join(f'{k} {v}' for k, v in sorted(counts.items())))
    for e in edits:
        if e.status == 'held':
            print(f'HELD {e.rel}:{e.line} {e.name} [{e.klass}]: {e.reason}')
    for line in unattributed:
        print('UNATTRIBUTED new compiler error: ' + line)
    data = [] if args.no_data or args.dry_run else data_report(args.root, names)
    for name, address, klass, rows in data:
        print(f'DATA HELD {name} {address} ({klass}): two or more typed views of one address; not rewritten')
        for role, site, shown in rows:
            print(f'    {role} {site}: {shown}')
    if args.report:
        with args.report.open('w') as out:
            out.write('name\tfile\tline\tstatus\tclass\tdeclared\tdefinition\treason\n')
            for e in edits:
                out.write(f'{e.name}\t{e.rel}\t{e.line}\t{e.status}\t{e.klass}\t{e.declared}\t{e.expected_at}\t'
                          f'{e.reason}\n')
            for name, address, klass, rows in data:
                out.write(f'{name}\t{address}\t-\theld\tdata\t{"; ".join(f"{r} {s}: {t}" for r, s, t in rows)}\t-\t'
                          f'typed views of one address\n')
    return 0


if __name__ == '__main__':
    sys.exit(main())
