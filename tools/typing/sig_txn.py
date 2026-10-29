#!/usr/bin/env python3
"""One owning-header transaction of the signature-consensus solver: write, prove, back off.

    sig_txn.py --decisions DIR/decisions.json --out DIR [--affected tools/build/affected.py]
               [--names N...] [--no-partial] [--dry-run] [--workers 8]

From `sig_solver.py solve` decisions for one owning feature header H:
  * H gains (append-only block, or in-place respelling of its own declaration) the canonical prototype of
    every unified name, with the type includes / tag declarations it needs;
  * every other declaration of those names is removed: local externs and empty `()` declarations in .c
    files and stale prototypes in other headers; each TU that uses or defines the name and does not
    already see H gains `#include "H"` (rewrite.edit_tu insertion rules).  A TU that cannot include H
    (missing common.h, a conflicting local declaration of another name H declares, a static/macro name
    clash) keeps a local declaration respelled to the canonical prototype instead;
  * the width rule: a 'W' decision respells the definition's return ABI-wide and narrows each returned
    value in the body (`return (s16)index;`);
  * partial decisions (owner ruling (b), per site): a blocking TU that will not see H keeps its own
    declaration, marked `/* Unprototyped: <reason> */`
    (owner wording for every floored local declaration), and is recorded in the floors ledger;
  * proof = build-graph truth: tools/build/affected.py `prove` over the edited files (every recipe whose
    production closure or own source contains an edited file, placement copies and image relinks
    included).  A non-PASS recipe drops the names whose edits reach it (its own source first, then
    headers in its closure) and the transaction is rewritten and re-proved (greedy back-off).
Writes DIR/txn.json (yield, proof, back-offs), DIR/txn.patch and DIR/floors.jsonl; tracked files are
restored on --dry-run, an error or an interrupt.  Requires src/ and include/ committed (the proof reads
the baseline text with `git show HEAD:path`).
"""
from __future__ import annotations

import argparse
from collections import defaultdict
import difflib
import json
from pathlib import Path
import re
import subprocess
import sys
import time

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
for p in (str(HERE.parent), str(TOOLS), str(TOOLS / 'headers'), str(TOOLS / 'lint')):
    if p not in sys.path:
        sys.path.insert(0, p)

import cscan  # noqa: E402
import plan as P  # noqa: E402
import rewrite as R  # noqa: E402
import sig_census as C  # noqa: E402
import sig_consensus as K  # noqa: E402
import sig_probe as S  # noqa: E402

FLOOR_TAG = re.compile(r'/\*\s*Unprototyped:')
GENERATED_TYPE = re.compile(r'\bS_(?:func_)?[0-9A-Fa-f]{8}\w*')
FLOOR_TEXT = {
    'param_width': 'retail call narrows its arguments to this declaration; no shared prototype keeps it',
    'return_width': 'retail call extends the result to this declared width; no shared prototype keeps it',
    'phantom_arguments': 'retail call passes more arguments than the callee reads',
    'varying_arity': 'retail call passes a different argument count',
    'pointer_kind': 'uses the value as a pointer where the definition has an integer (or the reverse)',
}


# ------------------------------------------------------------------------------------- pure editing

def pointer_kind_mismatch(site_key, def_key):
    """True when a declaration treats the return or a parameter as a pointer where the definition has an
    integer, or the reverse (a plain `void` return is the 'result unused' spelling and never counts)."""
    ret, ps, _ = site_key
    dret, dps, _ = def_key
    bad = (ret[1] > 0) != (dret[1] > 0) and (ret[0], ret[1]) != ('void', 0) and (dret[0], dret[1]) != ('void', 0)
    if ps is not None and len(ps) == len(dps):
        bad = bad or any((a[1] > 0) != (b[1] > 0) for a, b in zip(ps, dps))
    return bad


def apply_spans(text, edits):
    """Apply [(start, end, replacement)] (original offsets, non-overlapping); removals take whole lines."""
    norm = []
    for s, e, rep in edits:
        if rep == '':
            s, e = S._line_span(text, s, e)
        norm.append((s, e, rep))
    norm.sort(key=lambda x: (x[0], x[1]))
    for (a, b, _), (c, d, _) in zip(norm, norm[1:]):
        if c < b:
            raise ValueError('overlapping edits')
    out, pos = [], 0
    for s, e, rep in norm:
        out.append(text[pos:s])
        out.append(rep if rep else R.SENTINEL)
        pos = e
    out.append(text[pos:])
    return R._collapse(''.join(out)).replace(R.SENTINEL, '')


def add_include(text, header):
    return R.edit_tu(text, {'add': [header], 'remove': [], 'drop': []})


def append_to_header(text, lines):
    """Header text with `lines` appended in the APPEND_MARK block before the include guard's #endif."""
    lines = [l for i, l in enumerate(lines) if l not in text and l not in lines[:i]]
    if not lines:
        return text
    m = None
    for m in re.finditer(r'^[ \t]*#[ \t]*endif\b[^\n]*\n?', text, re.M):
        pass
    end = m.start() if m else len(text)
    head, tail = text[:end], text[end:]
    if R.APPEND_MARK not in head:
        head = head.rstrip('\n') + '\n\n' + R.APPEND_MARK + '\n'
    elif not head.endswith('\n'):
        head += '\n'
    return head + '\n'.join(lines) + '\n' + ('\n' if tail and not tail.startswith('\n') else '') + tail


def mark_floor(text, start, end, reason, unprototyped=True):
    """Declaration item [start, end) followed by the owner's floor marker `/* Unprototyped: <reason> */`
    (ruling (b); the same wording for empty and prototyped floor declarations; idempotent)."""
    le = text.find('\n', end)
    le = len(text) if le < 0 else le
    if FLOOR_TAG.search(text[start:le]):
        return text
    return text[:end] + ' /* Unprototyped: %s */' % reason + text[end:]


# ----------------------------------------------------------------------------------------- planning

class Transaction:
    def __init__(self, root, header, decisions, census=None, log=print, partial=True):
        self.root = Path(root).resolve()
        self.header = header
        self.log = log
        self.partial = partial
        self.census = census or C.Census(self.root, log=log)
        self.decisions = {d['name']: d for d in decisions}
        self.originals = {}
        self.no_include = set()      # TUs whose #include of H the proof refused (conflicting declarations)

    def text(self, rel):
        if rel not in self.originals:
            p = self.root / rel
            self.originals[rel] = p.read_bytes().decode('utf-8', 'surrogateescape') if p.exists() else None
        return self.originals[rel]

    def candidates(self, names=None):
        """Names with a usable decision: unified everywhere, or (partial) unified with floor sites."""
        out = {}
        for n, d in self.decisions.items():
            if names is not None and n not in names:
                continue
            kinds = [] if d['status'] == 'refused' and d.get('floor_class') == 'name_hold' else \
                self.pointer_kind_sites(n)
            if kinds:
                # pointer/integer disagreement: the sites become floors (or, with a header site, the
                # TUs that see that header); never unified by respelling
                extra = []
                for s in kinds:
                    paths = [s.path] if not s.in_header else \
                        [u for u in self.census.info(n).users if s.path in self.census.corpus.closure(u)]
                    extra += [dict(path=p, is_def=False, spelling=' '.join(s.text.split())[:120],
                                   reason='pointer_kind') for p in paths]
                d = dict(d, blocking=d.get('blocking', []) + [e for e in extra if e['path'] not in
                                                               {b['path'] for b in d.get('blocking', [])}])
                if d['status'] == 'unified':
                    d = dict(d, status='refused', best=d['choice'], floor_class='pointer_kind')
                self.decisions[n] = d
            if d['status'] == 'unified':
                out[n] = dict(d, floors=[])
            elif self.partial and d['status'] == 'refused' and d.get('best') and d.get('floor_class') != 'name_hold':
                blockers = d.get('blocking', [])
                if blockers and all(not b['is_def'] and b['reason'].split(':')[0] in
                                    ('phantom_arguments', 'varying_arity', 'param_width', 'return_width',
                                     'pointer_kind')
                                    for b in blockers):
                    ret = d['definition']['ret'] if d['best'] == 'D' else K.wide_return(d['definition']['ret'])
                    out[n] = dict(d, status='partial', choice=d['best'], ret=ret,
                                  narrowing=d['definition']['ret'] if d['best'] == 'W' else None,
                                  floors=[b for b in blockers])
        return out

    def pointer_kind_sites(self, name):
        """Declaration sites whose return or a parameter is a pointer where the definition has an integer
        (or the reverse).  Bytes agree, but unifying would turn a pointer use into an integer one: the
        definition needs a type change (holder retype) first, so such a site is a floor, not a removal."""
        info = self.census.info(name)
        if not info.def_keys:
            return []
        return [s for s in info.sites if pointer_kind_mismatch(s.key, info.def_keys[0])]

    def canonical(self, d):
        return S.proto(d['ret'], d['name'], d['definition']['params'])

    def plan(self, chosen):
        """({path: new text}, report).  Names that cannot be written are returned in report['held']."""
        H = self.header
        h_text = self.text(H)
        report = dict(header=H, names={}, held={}, files={}, respelled=[], includes_added=[], floors=[])
        if h_text is None:
            report['held'] = {n: 'no_owner_header_file' for n in chosen}
            return {}, report
        h_closure = set(self.census.corpus.closure(H))
        edits = defaultdict(list)            # path -> [(start, end, replacement)]
        need_include = defaultdict(set)      # TU -> names that need H
        def_rewrites = []                    # (path, name, wide, narrow)
        h_append, h_inline = [], []
        file_names = defaultdict(set)        # path -> names whose edits touch it
        infos = {n: self.census.info(n) for n in chosen}
        unified_names = set(chosen)
        # names H declares after the transaction, with their keys (for the include-conflict check)
        h_decl = {}
        for it in self.census.corpus.scan(H).items:
            if it.kind == 'decl':
                for d in it.decls:
                    if d.is_function and d.name:
                        h_decl[d.name] = it
        for n in sorted(chosen):
            d, info = chosen[n], infos[n]
            if any(s.ndecl > 1 for s in info.sites):
                report['held'][n] = 'multi_declarator_site'
                continue
            # a header's include guard is one conditional level; anything deeper is a real #if site
            if any(s.cond > (1 if s.in_header else 0) for s in info.sites):
                report['held'][n] = 'conditional_site'
                continue
            floor_paths = {b['path']: b for b in d.get('floors', [])}
            # floor sites must not see H after the transaction and must keep their own declaration: a local
            # one, or a header declaration whose every user of the name is itself a floor site
            bad = None
            kept_headers, kept_by_path = {}, {}
            for path, b in floor_paths.items():
                local = [s for s in info.sites if s.path == path]
                if H in self.census.corpus.closure(path):
                    bad = 'floor_site_sees_owner_header:' + path
                elif not local:
                    closure = self.census.corpus.closure(path)
                    hs = [s for s in info.sites if s.in_header and s.path in closure]
                    if len(hs) != 1:
                        bad = 'floor_site_without_local_declaration:' + path
                    else:
                        h2 = hs[0].path
                        # every TU that sees the kept header must be a floor site of this name and must
                        # never see H (H declares the name differently)
                        others = [u for u in self.census.corpus.c_files if h2 in self.census.corpus.closure(u)
                                  and (u not in floor_paths or H in self.census.corpus.closure(u))]
                        if others:
                            bad = 'floor_header_shared:%s:%s' % (h2, others[0])
                        else:
                            kept_headers[h2] = (hs[0], b)
                            kept_by_path[path] = h2
                if bad:
                    break
            if bad:
                report['held'][n] = bad
                continue
            proto = self.canonical(d)
            row = info.row
            if GENERATED_TYPE.search(proto):
                # publishing a generated S_<addr> layout name in a feature header raises the debt the
                # ratchet counts; such a name waits for its type to get an owner
                report['held'][n] = 'generated_layout_in_prototype'
                continue
            # 1. owner header
            own = [s for s in info.sites if s.path == H]
            if own:
                edits[H].append((own[0].start, own[0].end, proto + ';'))
                for s in own[1:]:
                    edits[H].append((s.start, s.end, ''))
            else:
                th = [t for t in row.type_headers if t not in h_closure and t not in P.TYPE_ALWAYS]
                defined = set()
                for f in h_closure:
                    from model import file_tags
                    defined |= file_tags(self.census.corpus, f)
                h_inline += ['#include "%s"' % P.include_token(t) for t in th]
                h_inline += ['%s;' % t for t in row.tags if t not in defined]
                h_append.append(proto + ';')
            file_names[H].add(n)
            # 2. every other declaration site
            for s in info.sites:
                if s.path == H or s.path in floor_paths or s.path in kept_headers:
                    continue
                edits[s.path].append((s.start, s.end, ''))
                file_names[s.path].add(n)
            for h2, (s2, b) in kept_headers.items():
                edits[h2].append(('floor', s2, b['reason']))
                file_names[h2].add(n)
            # 3. users and definitions must see H
            def_paths = {x.path for x in info.definitions if not x.static}
            for path in sorted(set(info.users) | def_paths):
                if path in floor_paths:
                    continue
                file_names[path].add(n)
                if H not in self.census.corpus.closure(path):
                    need_include[path].add(n)
            if d.get('choice') == 'W':
                for path in def_paths:
                    def_rewrites.append((path, n, d['ret'], d['narrowing']))
                    file_names[path].add(n)
            for path, b in floor_paths.items():
                local = [s for s in info.sites if s.path == path]
                report['floors'].append(dict(name=n, path=path, reason=b['reason'], spelling=b.get('spelling'),
                                             declaration=local[0].path if local else kept_by_path[path]))
                if local:
                    edits[path].append(('floor', local[0], b['reason']))
                file_names[path].add(n)
            report['names'][n] = dict(choice=d['choice'], status=d['status'], prototype=proto,
                                      sites=len(info.sites), floors=sorted(floor_paths))
        # the owner header must be self-contained for every type its declarations name (old and new): a TU
        # that newly includes it may not have the typedef in scope (e.g. DungeonItemEntry in item.h)
        if h_append or h_inline or edits.get(H):
            h_inline = self._self_contained(H, h_inline + h_append) + h_inline
        # include feasibility per TU (static checks; the proof is the final word)
        floor_tus = {f['path'] for f in report['floors']}
        for path, names in sorted(need_include.items()):
            reason = 'proof_conflict' if path in self.no_include else 'floor_site' if path in floor_tus else \
                self._include_problem(path, H, h_decl, unified_names, infos)
            if reason is None:
                report['includes_added'].append(path)
                continue
            # fallback: the TU keeps the declaration it sees today - its own, or the header one - respelled
            # to the canonical prototype (identical duplicates are compatible with H wherever both meet)
            closure = self.census.corpus.closure(path)
            for n in sorted(names):
                if n not in report['names']:
                    continue
                local = [s for s in infos[n].sites if s.path == path]
                seen = local or [s for s in infos[n].sites if s.in_header and s.path in closure and s.path != H]
                if seen and not self._types_visible(self.canonical(chosen[n]), seen[0].path):
                    report['held'][n] = 'respell_type_not_visible:' + seen[0].path
                    continue
                if seen:
                    s0 = seen[0]
                    edits[s0.path] = [e for e in edits[s0.path]
                                      if not (e[0] == s0.start and e[1] == s0.end)]
                    lead = 'extern ' if s0.storage == 'extern' else ''
                    edits[s0.path].append((s0.start, s0.end, lead + self.canonical(chosen[n]) + ';'))
                    report['respelled'].append(dict(path=s0.path, name=n, why='%s:%s' % (path, reason)))
                else:
                    report['held'][n] = 'cannot_include_owner:%s:%s' % (path, reason)
            need_include[path] = set()
        for r in report['respelled']:
            fl = [f['path'] for f in report['floors'] if f['name'] == r['name']]
            if r['path'].endswith('.h') and any(r['path'] in self.census.corpus.closure(f) for f in fl):
                report['held'][r['name']] = 'respelled_header_reaches_floor:' + r['path']
        held = set(report['held'])
        if held:
            remaining = {n: d for n, d in chosen.items() if n not in held}
            if remaining and len(remaining) < len(chosen):
                texts, sub = self.plan(remaining)
                sub['held'] = dict(report['held'], **sub['held'])
                return texts, sub
            if not remaining:
                return {}, report
        # 4. render
        texts = {}
        paths = set(edits) | {p for p, ns in need_include.items() if ns} | {r[0] for r in def_rewrites}
        if h_append or h_inline:
            paths.add(H)
        for path in sorted(paths):
            text = self.text(path)
            spans = [e for e in edits.get(path, []) if e[0] != 'floor']
            new = apply_spans(text, spans) if spans else text
            if need_include.get(path):
                new = add_include(new, H)
            for p_, n, wide, narrow in def_rewrites:
                if p_ == path:
                    new, added = S.retype_definition(new, n, wide, narrow)
                    report.setdefault('narrowing_casts', 0)
                    report['narrowing_casts'] += added
            floors = [e for e in edits.get(path, []) if e[0] == 'floor']
            for _, site, reason in floors:
                # re-find the kept declaration in the new text by its exact text
                at = new.find(site.text)
                if at >= 0:
                    new = mark_floor(new, at, at + len(site.text), FLOOR_TEXT.get(reason, reason))
            if path == H and (h_append or h_inline):
                new = append_to_header(new, h_inline + h_append)
            if new != text:
                texts[path] = new
        report['file_names'] = {p: sorted(ns) for p, ns in file_names.items() if p in texts}
        return texts, report

    def _types_visible(self, proto, path):
        """Every typedef name the prototype spells is in scope at `path` (a respelled declaration stays there)."""
        tindex = self.census.tindex
        vis = tindex.visible(path)
        return all(t in vis for t in cscan.IDENT.findall(proto) if t in tindex.global_defs)

    def _self_contained(self, H, new_lines):
        """`#include` lines for shared type headers whose typedefs H's declarations use but H's own include
        closure does not define (one unambiguous shared/records type header per name)."""
        corpus, tindex = self.census.corpus, self.census.tindex
        vis = tindex.visible(H)
        masked = corpus.scan(H).masked + '\n' + '\n'.join(new_lines)
        out = []
        for t in sorted(set(cscan.IDENT.findall(masked))):
            if t in vis or t in cscan.BASE_TYPES or t in cscan.QUALIFIERS or t in cscan.STORAGE:
                continue
            homes = [h for h in tindex.global_defs.get(t, ()) if P.type_header_ok(h) and h not in P.TYPE_ALWAYS]
            if len(homes) == 1 and homes[0] != H:
                line = '#include "%s"' % P.include_token(homes[0])
                if line not in out:
                    out.append(line)
        return out

    def _include_problem(self, path, H, h_decl, unified, infos):
        corpus, tindex = self.census.corpus, self.census.tindex
        closure = corpus.closure(path)
        if 'include/common.h' not in closure:
            return 'tu_without_common_h'
        own = P._file_level_names(corpus, path) | P._macros(corpus, path)
        clash = sorted((set(h_decl) | set(unified)) & own)
        if clash:
            return 'name_clash:' + clash[0]
        # local declarations of other names H declares must agree with H's spelling
        vis = tindex.visible(path)
        hvis = tindex.visible(H)
        rows = [r for f in closure for r in self.census.plan.sites_by_path.get(f, []) if f != H]
        for r in rows:
            s = r.site
            if getattr(s, 'kind', '') == 'data' or s.name in unified or s.name not in h_decl:
                continue
            it = h_decl[s.name]
            d = next(x for x in it.decls if x.name == s.name)
            hk = C.site_key(P.M.proto_params(d.params), tuple(it.spec), d.ptr, hvis)
            sk = C.site_key(s.params, s.ret_spec, s.ret_ptr, vis)
            if hk != sk and not (sk[1] is None and sk[0] == hk[0]):
                return 'declaration_conflicts_with_owner:%s@%s' % (s.name, s.path)
        # typedefs H's closure brings must not clash with the TU's own
        vis_files = {}
        for f in closure:
            for n in tindex.typedefs(f):
                vis_files.setdefault(n, f)
        for f in corpus.closure(H):
            if f in closure:
                continue
            for n in tindex.typedefs(f):
                if vis_files.get(n) not in (None, f):
                    return 'typedef_clash:' + n
        return None


# -------------------------------------------------------------------------------------------- proof

def run_proof(root, files, affected, out, workers=8, log=print):
    """affected.py prove over `files`; returns the parsed report."""
    report_path = out / ('proof-%d.json' % int(time.time()))
    cmd = ['nice', '-n', '10', sys.executable, str(affected), 'prove', '--root', str(root), '--workers', str(workers),
           '--json', str(report_path), *files]
    log('proof: ' + ' '.join(cmd[3:7]) + ' ... (%d files)' % len(files))
    res = subprocess.run(cmd, cwd=root, capture_output=True, text=True)
    (out / 'proof.log').open('a').write(res.stdout + res.stderr)
    if not report_path.is_file():
        return dict(verdict='ERROR', error=(res.stderr or res.stdout)[-2000:], recipes={}, images={})
    return json.loads(report_path.read_text())


LAYOUT_INLINE = 'ledger/layout_inline.jsonl'


def refresh_layout(root, log=print):
    """Re-map merged-TU member extents (ledger/layout_inline.jsonl) to the edited text, as a landing does;
    placement copies are projected from them, so the proof must see the refreshed ledger."""
    tool = Path(root) / 'tools/typing/refresh_layout_inline.py'
    res = subprocess.run(['nice', '-n', '10', sys.executable, str(tool), '--root', str(root), '--base', 'HEAD'],
                         cwd=root, capture_output=True, text=True)
    if res.returncode:
        raise RuntimeError('refresh_layout_inline failed: ' + (res.stderr or res.stdout)[-800:])
    log('layout_inline: ' + (res.stdout.strip().splitlines() or [''])[-1][:160])


def run_natcheck(root, natcheck, out, log=print):
    """The port's native check (read-only on the game root); returns its JSON report."""
    report_path = out / ('natcheck-%d.json' % int(time.time()))
    cmd = ['nice', '-n', '10', sys.executable, str(natcheck), '--root', str(root), '--jobs', '4',
           '--report', str(report_path)]
    res = subprocess.run(cmd, capture_output=True, text=True)
    (out / 'natcheck.log').open('a').write(res.stdout[-4000:] + res.stderr[-4000:])
    tail = (res.stdout.strip().splitlines() or [''])[-1]
    log('natcheck: ' + tail[:200])
    if not report_path.is_file():
        return dict(unit_failures=[dict(unit='?', errors=[res.stderr[-500:]])], adaptation_errors=[])
    return json.loads(report_path.read_text())


def native_culprits(report, file_names, names):
    """Names to drop for natcheck failures: edits in the failing unit, else names its errors mention."""
    drop = set()
    for item in report.get('unit_failures', []) + report.get('adaptation_errors', []):
        unit = item.get('unit', '')
        hit = set(file_names.get(unit, ()))
        text = '\n'.join(item.get('errors', [])) + str(item.get('error', ''))
        hit |= {n for n in names if re.search(r'\b%s\b' % re.escape(n), text)}
        for f, ns in file_names.items():
            if f.endswith('.h') and f in text:
                hit |= {n for n in ns if re.search(r'\b%s\b' % re.escape(n), text)} or set()
        drop |= hit
    return drop


CONFLICT = re.compile(r"(?:previous declaration of|conflicting types for) `([A-Za-z_]\w*)'")


def culprits(report, file_names, root, chosen=(), included=(), no_include=None):
    """Names to drop for a failed proof.  A compile error naming a conflicting declaration drops that name
    when it is being unified; when it names another declaration the owner header brought into a TU that
    gained `#include H`, that TU stops including H instead (no_include).  Otherwise the names with edits in
    the recipe's own source, else in its closure, are dropped."""
    drop = set()
    for rid, rec in report.get('recipes', {}).items():
        if rec.get('verdict') == 'PASS':
            continue
        own = rec.get('owner') or rec.get('source') or ''
        named = set(CONFLICT.findall(rec.get('error', '')))
        if named & set(chosen):
            drop |= named & set(chosen)
            continue
        if named and own in included and no_include is not None:
            no_include.add(own)
            continue
        hit = set(file_names.get(own, ()))
        if not hit:
            deps = []
            for folder in ('recipes', 'slus-recipes'):
                spec = root / 'build/.state' / folder / (rid + '.json')
                if spec.is_file():
                    deps = json.loads(spec.read_text()).get('dependencies', [])
            for d in deps:
                # SLUS recipes see src/ and include/ through the build_slus views
                d = d[len('build_slus/'):] if d.startswith('build_slus/') else d
                hit |= set(file_names.get(d, ()))
        drop |= hit
    return drop


def debt_counts(rel, text):
    import debt_check as D
    if text is None:
        return {}
    res = D.analyze(rel, text)
    out = defaultdict(int)
    for v in res['scopes'].values():
        for k, n in v['counts'].items():
            out[k] += n
    return dict(out)


def write(root, rel, text):
    p = Path(root) / rel
    if text is None:
        p.unlink(missing_ok=True)
    else:
        p.write_bytes(text.encode('utf-8', 'surrogateescape'))


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    ap.add_argument('--decisions', type=Path, required=True)
    ap.add_argument('--out', type=Path, required=True)
    ap.add_argument('--names', nargs='*')
    ap.add_argument('--affected', type=Path, help='tools/build/affected.py (default: the root\'s own)')
    ap.add_argument('--natcheck', type=Path, help='port natcheck.py: run after a PASS byte proof, back off on failures')
    ap.add_argument('--no-partial', action='store_true')
    ap.add_argument('--dry-run', action='store_true', help='write, prove, then restore every file')
    ap.add_argument('--no-proof', action='store_true', help='write only (the caller proves)')
    ap.add_argument('--workers', type=int, default=8)
    ap.add_argument('--max-rounds', type=int, default=6)
    args = ap.parse_args(argv)
    if not 1 <= args.workers <= 8:
        ap.error('between 1 and 8 workers on this host')
    root = args.root.resolve()
    affected = args.affected or root / 'tools/build/affected.py'
    if not args.no_proof and not affected.is_file():
        ap.error('no tools/build/affected.py in the root; pass --affected PATH')
    dirty = subprocess.run(['git', '-C', str(root), 'status', '--porcelain', '-uno', '--', 'src', 'include'],
                           capture_output=True, text=True).stdout.strip()
    if dirty:
        raise SystemExit('src/ or include/ has uncommitted changes; commit first:\n' + dirty[:600])
    data = json.loads(args.decisions.read_text())
    out = args.out
    out.mkdir(parents=True, exist_ok=True)
    logf = open(out / 'txn.log', 'a')

    def log(msg):
        line = time.strftime('%H:%M:%S ') + msg
        print(line, flush=True)
        logf.write(line + '\n')
        logf.flush()

    txn = Transaction(root, data['header'], data['decisions'], log=log, partial=not args.no_partial)
    chosen = txn.candidates(set(args.names) if args.names else None)
    log('%s: %d candidate names (%d unified, %d partial)' % (data['header'], len(chosen),
        sum(d['status'] == 'unified' for d in chosen.values()), sum(d['status'] == 'partial' for d in chosen.values())))
    backoffs, rounds, report, proof = [], 0, {}, None
    written = {}
    try:
        while chosen:
            rounds += 1
            for rel in list(written):
                write(root, rel, txn.originals[rel])
            written = {}
            texts, report = txn.plan(chosen)
            for n, why in report['held'].items():
                backoffs.append(dict(round=rounds, name=n, why=why))
                chosen.pop(n, None)
            if not texts:
                break
            for rel, t in texts.items():
                write(root, rel, t)
                written[rel] = t
            log('round %d: %d names, %d files written' % (rounds, len(report['names']), len(texts)))
            txn.text(LAYOUT_INLINE)
            refresh_layout(root, log)
            if (root / LAYOUT_INLINE).read_text() != txn.originals[LAYOUT_INLINE]:
                written[LAYOUT_INLINE] = (root / LAYOUT_INLINE).read_text()
            # debt ratchet: no class may rise in a source; a header may gain prototypes (the checker counts
            # header declarations as local_externs: owning them there is the point of the transaction)
            rises = {rel for rel, t in texts.items() if rel.endswith(('.c', '.h'))
                     and any(v > debt_counts(rel, txn.originals[rel]).get(k, 0)
                             for k, v in debt_counts(rel, t).items()
                             if not (rel.endswith('.h') and k == 'local_externs'))}
            if rises and rounds < args.max_rounds:
                drop = {n for rel in rises for n in report.get('file_names', {}).get(rel, ())}
                for n in sorted(drop):
                    backoffs.append(dict(round=rounds, name=n, why='debt_rise', files=sorted(rises)[:10]))
                    chosen.pop(n, None)
                log('debt rise in %s: back off %s' % (sorted(rises)[:5], sorted(drop)))
                continue
            if args.no_proof:
                break
            proof = run_proof(root, sorted(r for r in texts if r.endswith(('.c', '.h'))), affected, out,
                              args.workers, log)
            log('proof: %s %s (%.0f s)' % (proof.get('verdict'), proof.get('counts'), proof.get('seconds', 0)))
            if proof.get('verdict') == 'PASS':
                if not args.natcheck:
                    break
                nat = run_natcheck(root, args.natcheck, out, log)
                proof['natcheck'] = dict(unit_failures=len(nat.get('unit_failures', [])),
                                         adaptation_errors=len(nat.get('adaptation_errors', [])),
                                         contract_errors=len(nat.get('contract_errors', [])))
                if not nat.get('unit_failures') and not nat.get('adaptation_errors'):
                    break
                drop = native_culprits(nat, report.get('file_names', {}), set(chosen))
                if not drop or rounds >= args.max_rounds:
                    log('natcheck: cannot back off further: restoring')
                    for rel in list(written):
                        write(root, rel, txn.originals[rel])
                    written = {}
                    break
                for n in sorted(drop):
                    backoffs.append(dict(round=rounds, name=n, why='natcheck',
                                         units=[u['unit'] for u in nat.get('unit_failures', [])][:10],
                                         errors=[e for u in nat.get('unit_failures', []) for e in u['errors'][:2]][:6]))
                    chosen.pop(n, None)
                log('natcheck back off %d names: %s' % (len(drop), ', '.join(sorted(drop))[:300]))
                proof = None
                continue
            before_ni = len(txn.no_include)
            drop = culprits(proof, report.get('file_names', {}), root, chosen, set(report.get('includes_added', [])),
                            txn.no_include)
            if len(txn.no_include) > before_ni and not drop and rounds < args.max_rounds:
                log('stop including the owner header in %d TUs: %s' % (
                    len(txn.no_include) - before_ni, ', '.join(sorted(txn.no_include))[:300]))
                continue
            if not drop or rounds >= args.max_rounds:
                log('cannot back off further (%s): restoring' % (proof.get('error') or 'no culprit'))
                for rel in list(written):
                    write(root, rel, txn.originals[rel])
                written = {}
                break
            bad = [dict(recipe=r, source=v.get('source'), verdict=v['verdict'],
                        why=v.get('difference') or v.get('error', '')[-300:])
                   for r, v in proof.get('recipes', {}).items() if v['verdict'] != 'PASS'][:20]
            for n in sorted(drop):
                backoffs.append(dict(round=rounds, name=n, why='proof', recipes=bad))
                chosen.pop(n, None)
            log('back off %d names: %s' % (len(drop), ', '.join(sorted(drop))[:300]))
        if written and not args.no_proof and (proof or {}).get('verdict') != 'PASS':
            for rel in list(written):
                write(root, rel, txn.originals[rel])
            written = {}
            log('no proven state: every file restored')
        # receipt
        changed = sorted(written)
        patch = []
        yields = defaultdict(int)
        for rel in changed:
            old, new = txn.originals[rel], written[rel]
            patch.extend(difflib.unified_diff((old or '').splitlines(True), new.splitlines(True), 'a/' + rel, 'b/' + rel))
            if not rel.endswith(('.c', '.h')):
                continue
            b, a = debt_counts(rel, old), debt_counts(rel, new)
            for k in set(b) | set(a):
                yields[k + '_delta'] += a.get(k, 0) - b.get(k, 0)
        (out / 'txn.patch').write_text(''.join(patch))
        names = report.get('names', {}) if written else {}
        removed_local = removed_empty = removed_header = 0
        for n in names:
            info = txn.census.info(n)
            floors = set(names[n]['floors'])
            for s in info.sites:
                if s.path == txn.header or s.path in floors:
                    continue
                if any(r['path'] == s.path and r['name'] == n for r in report.get('respelled', [])):
                    continue
                if s.in_header:
                    removed_header += 1
                else:
                    removed_local += 1
                    removed_empty += s.arity is None
        floors = []
        for f in report.get('floors', []) if written else []:
            d = txn.decisions[f['name']]
            floors.append(f)
        receipt = dict(header=txn.header, tree=data.get('tree'), rounds=rounds, verdict=(proof or {}).get('verdict'),
                       names=names, unified=sum(1 for v in names.values() if v['status'] == 'unified'),
                       partial=sum(1 for v in names.values() if v['status'] == 'partial'),
                       local_declarations_removed=removed_local, empty_declarations_removed=removed_empty,
                       header_declarations_removed=removed_header, respelled=report.get('respelled', []),
                       includes_added=report.get('includes_added', []) if written else [],
                       narrowing_casts_added=report.get('narrowing_casts', 0) if written else 0,
                       debt=dict(yields), files=changed, floor_sites=floors, backoffs=backoffs,
                       proof=dict(verdict=(proof or {}).get('verdict'), counts=(proof or {}).get('counts'),
                                  natcheck=(proof or {}).get('natcheck'),
                                  scope={k: (len(v) if isinstance(v, list) else v)
                                         for k, v in (proof or {}).get('scope', {}).items()
                                         if k in ('recipes', 'slus_recipes', 'images', 'kinds')},
                                  seconds=(proof or {}).get('seconds')))
        (out / 'txn.json').write_text(json.dumps(receipt, indent=1, default=str) + '\n')
        log('result: %s; %d unified + %d partial names, %d local / %d empty / %d header declarations removed, '
            '%d floor sites, debt %s' % (receipt['verdict'], receipt['unified'], receipt['partial'], removed_local,
                                         removed_empty, removed_header, len(floors), dict(yields)))
        if args.dry_run:
            raise KeyboardInterrupt
        return 0 if (proof or {}).get('verdict') == 'PASS' or args.no_proof else 1
    except KeyboardInterrupt:
        for rel in list(written):
            write(root, rel, txn.originals[rel])
        log('dry run / interrupted: every file restored')
        return 0 if args.dry_run else 130
    except BaseException:
        for rel in list(written):
            write(root, rel, txn.originals[rel])
        log('failed: every file restored')
        raise


if __name__ == '__main__':
    sys.exit(main())
