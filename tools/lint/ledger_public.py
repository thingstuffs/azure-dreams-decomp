#!/usr/bin/env python3
"""Lane-local strings in public ledgers (audit rule R12): census, a re-runnable scrub, and a fail-new check.

    ledger_public.py census [--root DIR] [--top N]        per-file counts of lane-local strings (all public files)
    ledger_public.py scrub [--root DIR] [--write]          rewrite them in SCRUB_FILES (dry run without --write)
    ledger_public.py check BASE [--root DIR]               fail on strings that are on the working tree but not on BASE

Public files: ledger/*.jsonl and ledger/*.json (top level), tools/**/*baseline*.json and config/*.tsv.

A lane-local string is one of (PATTERNS):
  abs    a home-directory path or an editor session scratch path
  work   a work/... path (work/ is git-ignored: the file is not in the repo)
  out    an out/... path (a lane's private output directory)
  lane   a lane name: r1NNw_<x> / rNN_<x> / r1NN-<x> (round-prefixed), cNNN_<x>, a model-prefixed name
         (opus_<x>, sonnet_<x>, sol61_<x>, luna_<x>, astra_<x>, fable_<x>, gemini_<x>, terra_<x>), batchAC<N>
A match preceded by `/`, `.`, `-` or a word character is part of a repo path or a longer identifier and is not
counted (docs/evidence/r121_remnants.md is a published file); a match followed by `":` is a JSON key (tools read
keys such as r86_census) and is not counted either.  ALLOW lists exact tokens that are not lane names.

`scrub` rewrites each lane-local string in SCRUB_FILES to a neutral description of the evidence kind: first the
exact VALUE_MAP / PHRASE_MAP entries (whole JSON string values, then substrings), then a generic description (a
round-NNN lane, an Opus lane, candidate <file> (not published), ...).  It edits the raw line text in place, so every
other byte of a row stays identical and the transformation can be re-applied to a ledger another lane edited
(it is idempotent: the replacements contain no lane-local strings).  Ledgers outside SCRUB_FILES (the pin-campaign
journals, whose `lane`/`event_id` columns are cross-referenced keys, and the configure/levels inputs such as
rows.jsonl and instances.jsonl) keep their strings; `check` keeps them from growing.

`check BASE` compares, per public file that differs from BASE, the multiset of lane-local strings: a string whose
count rises is NEW and fails (exit 1).  tools/lint/ledger_integrity.py runs it in --fail-new/--fail-all mode.

Private commit hashes (kind `tree`): a 40-hex `"tree": "<sha>"` value (the commit a prototype-floor row was measured
on) must name a commit in public history, an ancestor of HEAD, of a local `master`/`origin/master` branch, of
LEDGER_PUBLIC_REF or of a `--public-ref`.  A lane or batch root's own commits never become public, so citing one leaves
a hash nobody can resolve.  A shorter hex value (7-39 digits) in a "tree" field is always counted: an abbreviated hash
is ambiguous and cannot be checked against public history, so a row records the full hash or null.  `check` fails on
a rise of such hashes in a changed public file (the ones already on BASE are reported by `census` only).

A lane root (a checkout that tools/lanes/mk_scratch_root.py made: it carries SCRATCH_HEAD) has its own history: HEAD
and its local `master` are the lane's private commits, so there neither counts as public; only `origin/master`, the
SCRATCH_HEAD commit (when the root's object store has it), LEDGER_PUBLIC_REF and `--public-ref` do.  Pass the master
commit the root was made from as `--public-ref` (or set LEDGER_PUBLIC_REF, which is not an AZURE_* name and so stays
out of the configure checkpoint guard) so hashes of master commits are recognised.

`check` fails closed: when `git diff BASE` (or listing the untracked files) fails, for example on an unknown BASE,
nothing is compared and the check fails.
"""
from __future__ import annotations

import argparse
import collections
import fnmatch
import os
from pathlib import Path
import re
import subprocess
import sys

_HOME = '/ho' 'me/'  # split so the prepublish scan does not flag this file
_SCRATCH = '/tmp/' 'claude-'
MODELS = ('opus', 'sonnet', 'sol', 'luna', 'astra', 'fable', 'gemini', 'terra')
_PRE = r'(?<![\w./-])'
_POST = r'(?!\w|":)'
PATTERNS = {
    'abs': re.compile(r'(?:' + re.escape(_HOME) + r'|/Users/|' + re.escape(_SCRATCH) + r')[^\s"\'\\;,)|]*'),
    'work': re.compile(_PRE + r'work/[\w./-]*'),
    'out': re.compile(_PRE + r'out/[\w./-]*'),
    'lane': re.compile(_PRE + r'(?:_?r\d{2,3}[a-z]?w?[_-][A-Za-z0-9](?:\w|-(?=\w))*|c1\d\d_[a-z]\w*|'
                       r'(?:' + '|'.join(MODELS) + r')\d*_[a-z0-9]\w*|_?batchAC\d+)' + _POST),
}
# tokens that match a pattern but are not lane-local: identifiers in debt baselines, the extracted-disc tree every
# checkout has (work/disc/ is made by the build setup, not by a lane) and prose such as "r86-era"
ALLOW = {'sol9_copy8'}
ALLOW_RE = re.compile(r'work/disc/[\w./-]*|r\d+-era')
PUBLIC_GLOBS = ('ledger/*.jsonl', 'ledger/*.json', 'tools/**/*baseline*.json', 'config/*.tsv')

# Ledgers the scrub rewrites: accuracy-era review ledgers and small evidence journals whose strings are free text
# (or a provenance column no tool keys on).  Checked readers: affected.py/mkbuild.py (fields, bridge_casts: never
# read for content), status.py (counts and ids only), levels.py (split_audit row/target/status), apply_names.py
# (names.jsonl is append-only, never read back).
SCRUB_FILES = (
    'ledger/fields.jsonl', 'ledger/bridge_casts.jsonl', 'ledger/names.jsonl', 'ledger/union_trades.jsonl',
    'ledger/real_volatiles.jsonl', 'ledger/spelling_revisits.jsonl', 'ledger/type_consolidation.jsonl',
    'ledger/hard_basket.jsonl', 'ledger/split_audit.jsonl', 'ledger/maspsx_dependence.jsonl',
    'ledger/pin_evidence.jsonl', 'ledger/refused_trades.jsonl', 'ledger/recipe_evidence.jsonl',
    'ledger/sdk_objects.jsonl', 'ledger/coverage_regions.jsonl', 'ledger/module_recipe_census.jsonl',
    'ledger/clone_families.jsonl', 'ledger/slus_rebaseline_landings.jsonl', 'ledger/onetrip_loadbearing.jsonl',
    'ledger/onetrip_barrier_rows.jsonl',
    'ledger/unions.jsonl', 'ledger/prototype_floors.jsonl', 'ledger/records.json', 'ledger/prototype_identities.jsonl',
)

# Whole JSON string values (quotes included in the match), mapped to the landing that recorded them.
VALUE_MAP = {
    'r121w_typesA-final': 'r121 B21 types census, final pass',
    'r121w_typesA-pass2': 'r121 B21 types census, second pass',
    'r121-types-design': 'r121 B21 types design',
    'decision-69; r121w_typesA': 'decision-69; r121 B21 types census',
    'r124w_fields1': 'r121 READABILITY BATCH 3 field naming',
    'r121-opus_entity2': 'r121 TYPES EntityRec split',
    'r121w_tnode1': 'r121 BATCH 2b node naming',
    'r121-opus_place1 (decision 73/75)': 'r121 PLACEMENTS (decision 73/75)',
    'r124w_naudit3': 'name audit 3',
    '498e6f5fa30cb872de0db470cbff1431fcd50805': 'd144d5f1b',  # a lane-root commit: the landing that carried it
}
# Substrings, applied longest first after VALUE_MAP.
PHRASE_MAP = {
    'r121w_entity1 out/field_roles.tsv + naming_decisions.tsv':
        'field-role census and naming decisions (r121 TYPES landing)',
    'opus_place1 tools/typing/rename_field.py': 'tools/typing/rename_field.py (r121 PLACEMENTS landing)',
    '+opus_entity2': '+EntityRec split patch',
    'during r150w_audit_fixes run': 'during the approach-audit fixes run',
    'r150w_audit_fixes': 'the approach-audit fixes',
    'keep_astra lane': 'an Astra lane',
    'r96_sonnet_ot1..ot7 REPORT.md': 'r96 one-trip unwrap measurements',
    'r86_opus_census tmp/scores.jsonl': 'r86 module recipe census scores',
    'r121_remnants_continue4': 'r121 remnants census',
    'r121_remnants_continue3': 'r121 remnants census',
    'r121_remnants_continue2': 'r121 remnants census',
    'r121_remnants_continue': 'r121 remnants census',
    'r121_remnants': 'r121 remnants census',
    'r121_rem_li': 'r121 remnants census',
    'r121_census2': 'r121 coverage census',
    'r121w_heur3': 'r121 placement heuristics census',
    'r120_ovm': 'r120 ovmovie attribution',
    'r120_tailjump': 'r120 tail-jump audit',
    'r84_fable_build': 'r84 module build census',
    'r83_sonnet_modsplit': 'r83 module split',
    'r95_sonnet_vol': 'r95 volatile-removal trials',
}
# PHRASE_MAP keys match only where a lane-local string could start and end (not inside a repo path such as
# docs/evidence/r121_remnants.md)
_PHRASES = [(re.compile((r'(?<![\w./-])' if k[:1].isalnum() else '') + re.escape(k) +
                        (r'(?![\w-])' if k[-1:].isalnum() else '')), v)
            for k, v in sorted(PHRASE_MAP.items(), key=lambda kv: -len(kv[0]))]
_ART = {'opus': 'an Opus', 'astra': 'an Astra'}


def _model(token):
    low = token.lower()
    for m in MODELS:
        if re.search(r'(?:^|[_-])' + m + r'(?:\d|_|$)', low) or low.startswith(m):
            return m
    return None


def lane_phrase(token):
    """A neutral description of a lane name."""
    m = re.match(r'_?batchAC(\d+)$', token)
    if m:
        return f'the ACCURACY {m.group(1)} batch'
    m = re.match(r'_?r\d{2,3}_types_(?:phase(\d+)|(pilot))$', token)
    if m:
        return f'type consolidation phase {m.group(1)}' if m.group(1) else 'type consolidation pilot'
    if re.match(r'c1\d\d_', token):
        return 'an accuracy lane'
    model = _model(token)
    m = re.match(r'_?r(\d{2,3})', token)
    who = (f'{model.capitalize()} lane' if model else 'lane')
    if m:
        return f'a round-{m.group(1)} {who}'
    return (_ART.get(model, 'a ' + model.capitalize()) + ' lane') if model else 'a lane'


def path_phrase(path):
    """A neutral description of a lane-local file path (the file is not in the repo)."""
    base = path.rstrip('/.').rsplit('/', 1)[-1]
    if not base or base in ('out', 'work', 'evidence', 'cand', 'holds') or count_tokens(base) or base.startswith('_r'):
        base = ''
    sfx = f' {base}' if base else ''
    if base.endswith(('.c', '.h', '.s')):
        return f'candidate{sfx} (not published)'
    if base.endswith('.md'):
        return f'agent report{sfx} (not published)'
    return f'working data{sfx} (not published)'


def count_tokens(text):
    """Counter of (kind, token) lane-local strings in text."""
    found = collections.Counter()
    taken = set()  # start offsets inside an earlier kind's match (a lane name inside a work/ path)
    for kind in ('abs', 'work', 'out', 'lane'):
        spans = []
        for m in PATTERNS[kind].finditer(text):
            if m.group(0) in ALLOW or ALLOW_RE.fullmatch(m.group(0)) or m.start() in taken:
                continue
            spans.append(m.span())
            found[(kind, m.group(0))] += 1
        for a, b in spans:
            taken.update(range(a, b))
    return found


def scrub_text(text):
    """Return text with every lane-local string replaced (idempotent)."""
    for old, new in VALUE_MAP.items():
        text = text.replace(f'"{old}"', f'"{new}"')
    for pat, new in _PHRASES:
        text = pat.sub(lambda m, new=new: new, text)

    def sub(kind, phrase):
        nonlocal text

        def repl(m):
            return m.group(0) if m.group(0) in ALLOW or ALLOW_RE.fullmatch(m.group(0)) else phrase(m.group(0))
        text = PATTERNS[kind].sub(repl, text)
    sub('abs', path_phrase)
    sub('work', path_phrase)
    sub('out', path_phrase)
    sub('lane', lane_phrase)
    return text


def public_files(root):
    root = Path(root)
    out = set()
    for g in PUBLIC_GLOBS:
        out.update(str(p.relative_to(root)) for p in root.glob(g) if p.is_file())
    return sorted(p for p in out if '__pycache__' not in p)


def is_public(path):
    parts = path.split('/')
    if parts[0] in ('ledger', 'config') and len(parts) == 2:
        return path.endswith(('.jsonl', '.json') if parts[0] == 'ledger' else ('.tsv',))
    return parts[0] == 'tools' and fnmatch.fnmatch(parts[-1], '*baseline*.json') and '__pycache__' not in parts


def census(root):
    root = Path(root)
    res = {}
    for rel in public_files(root):
        found = count_tokens((root / rel).read_text(errors='replace'))
        if found:
            res[rel] = found
    return res


def _git(root, *args):
    return subprocess.run(['git', *args], cwd=root, capture_output=True)


TREE_RE = re.compile(r'"tree":\s*"([0-9a-f]{7,40})"')


def lane_root(root):
    """The base commit of a lane root (tools/lanes/mk_scratch_root.py writes SCRATCH_HEAD), or None."""
    marker = Path(root) / 'SCRATCH_HEAD'
    if not marker.is_file():
        return None
    return marker.read_text().strip() or 'unknown'


def public_refs(root, extra=()):
    """Refs whose ancestry is public history: HEAD, a local master/origin/master, LEDGER_PUBLIC_REF and EXTRA.

    In a lane root HEAD and the local master are the lane's own commits: only origin/master, the SCRATCH_HEAD
    commit (when this object store has it), LEDGER_PUBLIC_REF and EXTRA count."""
    lane = lane_root(root)
    refs = [] if lane else ['HEAD']
    for name in (('origin/master',) if lane else ('master', 'origin/master')):
        if _git(root, 'rev-parse', '--verify', '--quiet', name + '^{commit}').returncode == 0:
            refs.append(name)
    if lane and _git(root, 'rev-parse', '--verify', '--quiet', lane + '^{commit}').returncode == 0:
        refs.append(lane)
    env = os.environ.get('LEDGER_PUBLIC_REF')
    refs += [r for r in (env, *extra) if r]
    return refs


def unreachable_trees(root, text, refs, cache=None):
    """Counter of the "tree" commit hashes in TEXT outside public history: a full hash that is not an ancestor of any
    of REFS, and every abbreviated (7-39 hex) hash."""
    cache = {} if cache is None else cache
    res = collections.Counter()
    for sha, n in collections.Counter(TREE_RE.findall(text)).items():
        if sha not in cache:
            cache[sha] = len(sha) == 40 and any(
                _git(root, 'merge-base', '--is-ancestor', sha, ref).returncode == 0 for ref in refs)
        if not cache[sha]:
            res[sha] = n
    return res


class DiffFailed(RuntimeError):
    """`git diff BASE` (or the untracked listing) failed: the check cannot know which files changed."""


def changed_paths(root, base):
    """Paths that differ from BASE plus untracked public candidates; raises DiffFailed when git fails."""
    diff = _git(root, 'diff', '--name-only', '--no-renames', base, '--')
    if diff.returncode != 0:
        raise DiffFailed(f'git diff {base} failed: ' + diff.stderr.decode(errors='replace').strip())
    others = _git(root, 'ls-files', '--others', '--exclude-standard', '--', 'ledger', 'tools', 'config')
    if others.returncode != 0:
        raise DiffFailed('git ls-files failed: ' + others.stderr.decode(errors='replace').strip())
    return sorted(set(diff.stdout.decode().split()) | set(others.stdout.decode().split()))


def new_strings(root, base):
    """{path: Counter((kind, token) -> rise)} for public files that gained lane-local strings since BASE."""
    root = Path(root)
    res = {}
    for rel in changed_paths(root, base):
        if not is_public(rel) or not (root / rel).is_file():
            continue
        head = count_tokens((root / rel).read_text(errors='replace'))
        if not head:
            continue
        shown = _git(root, 'show', f'{base}:{rel}')
        old = count_tokens(shown.stdout.decode(errors='replace')) if shown.returncode == 0 else collections.Counter()
        rise = collections.Counter({k: n - old[k] for k, n in head.items() if n > old[k]})
        if rise:
            res[rel] = rise
    return res


def new_trees(root, base, refs):
    """{path: Counter(sha -> rise)} for public files that gained commit hashes outside public history since BASE."""
    root = Path(root)
    res, cache = {}, {}
    for rel in changed_paths(root, base):
        if not is_public(rel) or not (root / rel).is_file():
            continue
        head = unreachable_trees(root, (root / rel).read_text(errors='replace'), refs, cache)
        if not head:
            continue
        shown = _git(root, 'show', f'{base}:{rel}')
        old = (unreachable_trees(root, shown.stdout.decode(errors='replace'), refs, cache)
               if shown.returncode == 0 else collections.Counter())
        rise = collections.Counter({k: n - old[k] for k, n in head.items() if n > old[k]})
        if rise:
            res[rel] = rise
    return res


def check(root, base, out=None, public_ref=()):
    out = out or sys.stdout
    try:
        rises = new_strings(root, base)
    except DiffFailed as error:
        print(f'public ledgers: FAILED, nothing compared ({error})', file=out)
        return 1
    total = sum(sum(c.values()) for c in rises.values())
    for rel, rise in rises.items():
        for (kind, tok), n in sorted(rise.items()):
            print(f'  NEW {kind} {rel}: {tok!r} (+{n})', file=out)
    print(f'public ledgers: {total} new lane-local strings in {len(rises)} files', file=out)
    refs = public_refs(root, public_ref)
    trees = new_trees(root, base, refs)
    ntrees = sum(sum(c.values()) for c in trees.values())
    for rel, rise in trees.items():
        for sha, n in sorted(rise.items()):
            why = ('is abbreviated (record the full hash or null)' if len(sha) < 40 else
                   'is not an ancestor of ' + (', '.join(refs) or 'any public ref (lane root: pass --public-ref)'))
            print(f'  NEW tree {rel}: {sha} (+{n}) {why}', file=out)
    print(f'public ledgers: {ntrees} new private commit hashes in {len(trees)} files', file=out)
    return total + ntrees


def scrub(root, write=False, files=SCRUB_FILES):
    root = Path(root)
    report = []
    for rel in files:
        p = root / rel
        if not p.is_file():
            continue
        text = p.read_text()
        new = scrub_text(text)
        before, after = sum(count_tokens(text).values()), sum(count_tokens(new).values())
        lines = sum(1 for a, b in zip(text.split('\n'), new.split('\n')) if a != b)
        report.append((rel, before, after, lines))
        if write and new != text:
            p.write_text(new)
    return report


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('cmd', choices=('census', 'scrub', 'check'))
    ap.add_argument('base', nargs='?')
    ap.add_argument('--root', type=Path, default=Path(__file__).resolve().parents[2])
    ap.add_argument('--write', action='store_true')
    ap.add_argument('--top', type=int, default=3)
    ap.add_argument('--public-ref', action='append', default=[],
                    help='a ref whose ancestors are public history (repeatable; HEAD and master always count)')
    a = ap.parse_args(argv)
    root = a.root.resolve()
    if a.cmd == 'census':
        res = census(root)
        tot = collections.Counter()
        for rel, found in res.items():
            kinds = collections.Counter()
            for (k, _), n in found.items():
                kinds[k] += n
            tot.update(kinds)
            top = ', '.join(f'{t} x{n}' for (_, t), n in found.most_common(a.top))
            print(f'{rel}: ' + ' '.join(f'{k} {n}' for k, n in sorted(kinds.items())) + f' | {top}')
        print(f'total: {sum(tot.values())} in {len(res)} files (' + ', '.join(f'{k} {n}' for k, n in sorted(tot.items())) + ')')
        refs, cache = public_refs(root, a.public_ref), {}
        for rel in public_files(root):
            trees = unreachable_trees(root, (root / rel).read_text(errors='replace'), refs, cache)
            if trees:
                print(f'{rel}: {sum(trees.values())} "tree" commit hashes outside public history '
                      f'({len(trees)} distinct; refs {", ".join(refs)})')
        return 0
    if a.cmd == 'scrub':
        for rel, before, after, lines in scrub(root, a.write):
            print(f'{rel}: {before} -> {after} lane-local strings, {lines} lines changed')
        print('written' if a.write else 'dry run (--write to apply)')
        return 0
    if not a.base:
        ap.error('check needs BASE')
    return 1 if check(root, a.base, public_ref=a.public_ref) else 0


if __name__ == '__main__':
    sys.exit(main())
