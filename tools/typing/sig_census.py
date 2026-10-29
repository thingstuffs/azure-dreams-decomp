#!/usr/bin/env python3
"""Source-side signature census for the signature-consensus solver (tools/typing/sig_solver.py).

Built on the header planner (tools/headers/plan.py: definitions, every file-scope declaration site,
owning folder header, publishable prototype text and its type needs).  Per function name:

  * `definitions` (all copies) and the planner row (owning header, prototype text, hold reason);
  * `sites`: every declaration (local extern, empty `()` declaration, header prototype) with its
    canonical signature key (typedefs expanded: return, parameters, varargs; `None` parameters for an
    unprototyped declaration);
  * `users`: .c files that mention the name outside declarations (calls, address-taking, initialisers);
    `header_users`: headers that mention it outside a declaration (macros, inline bodies);
  * `conflict`: two or more distinct keys over the definition and the sites.

    sig_census.py [--root R] [--header include/dungeon/item.h] [--name N...] [--json OUT]

Read-only.  Block-scope declarations are not modelled (none in the tree when written: 0 indented
`extern` function declarations under src/).
"""
from __future__ import annotations

import argparse
from collections import defaultdict
from dataclasses import dataclass, field
import json
from pathlib import Path
import re
import sys

HERE = Path(__file__).resolve()
TOOLS = HERE.parents[1]
for p in (str(TOOLS), str(TOOLS / 'headers')):
    if p not in sys.path:
        sys.path.insert(0, p)

import cscan  # noqa: E402
import model as M  # noqa: E402
import plan as P  # noqa: E402

NARROW_INT = ('s8', 'u8', 's16', 'u16')


@dataclass
class SiteInfo:
    path: str
    start: int
    end: int
    line: int
    text: str
    in_header: bool
    storage: str
    key: tuple                 # (ret canon, params canon tuple | None, varargs)
    cls: str                   # planner classification against the bound definition
    ndecl: int
    cond: int
    arity: int | None          # declared parameter count (None: unprototyped)


@dataclass
class NameInfo:
    name: str
    row: object                # plan.FnRow or None
    definitions: list
    def_keys: list
    sites: list = field(default_factory=list)
    users: list = field(default_factory=list)
    header_users: list = field(default_factory=list)

    @property
    def owner(self):
        return self.row.header if self.row is not None and self.row.status == 'header' else None

    @property
    def keys(self):
        return sorted({s.key for s in self.sites} | set(self.def_keys), key=repr)

    @property
    def conflict(self):
        return len(self.keys) > 1

    def to_json(self):
        return dict(name=self.name, owner=self.owner, hold=None if self.owner else
                    (self.row.reason if self.row is not None else 'no_definition'),
                    definitions=[dict(path=d.path, proto=d.proto, static=d.static) for d in self.definitions],
                    distinct=len(self.keys), sites=[dict(path=s.path, line=s.line, header=s.in_header,
                                                         cls=s.cls, text=' '.join(s.text.split())[:160])
                                                    for s in self.sites],
                    users=self.users, header_users=self.header_users)


# Ghidra/PsyQ-signature matches known to hit game wrappers, not library code (sonnet_ghidra1 trial).
SDK_FALSE_POSITIVES = {'80048D00', '80048D20', '80047714'}


def sdk_evidence(path):
    """{name: {'ret', 'params', 'addr'}} from a Ghidra PsyQ-signature export (JSON lines: name, addr, ret,
    params, cdecl).  Only rows whose declaration names a library function (not FUN_<addr>) and is not a
    known false positive.  Evidence for SDK names only: object bytes still decide, and no SDK header text
    is ever copied (include/sdk stand-ins are independently written, decision 74)."""
    out = {}
    p = Path(path) if path else None
    if not p or not p.is_file():
        return out
    for line in p.read_text().splitlines():
        if not line.strip():
            continue
        r = json.loads(line)
        if r.get('err') or not r.get('cdecl') or str(r.get('addr', '')).upper() in SDK_FALSE_POSITIVES:
            continue
        m = re.search(r'([A-Za-z_]\w*)\s*\(', r['cdecl'])
        if not m or m.group(1).startswith('FUN_'):
            continue
        out[m.group(1)] = dict(ret=r.get('ret'), params=r.get('params'), addr=r.get('addr'),
                               varargs=r.get('varargs'))
    return out


def site_key(params, ret_spec, ret_ptr, vis):
    ret = M.canon(ret_spec, ret_ptr, vis)
    if params is None:
        return (ret, None, False)
    ps = [p for p in params if p != ['void']]
    varargs = any(p == ['...'] for p in ps)
    return (ret, tuple(M.canon(*M.param_parts(p)[:2], vis) for p in ps if p != ['...']), varargs)


def key_text(key):
    ret, params, varargs = key
    r = ret[0] + '*' * ret[1]
    if params is None:
        return r + ' ()'
    ps = [p[0] + '*' * p[1] for p in params] + (['...'] if varargs else [])
    return r + ' (' + ', '.join(ps or ['void']) + ')'


class Census:
    """Whole-tree census (one planner build, ~1-2 min); query per name or per owning header."""

    def __init__(self, root, plan=None, log=lambda m: None):
        self.root = Path(root).resolve()
        log('census: planning declarations over src/ and include/')
        if plan is None:
            corpus = M.Corpus(self.root)
            # probe variants (.sigprobe_<pid>_*.c) and other dot files are never part of the tree
            corpus.c_files = [f for f in corpus.c_files if not Path(f).name.startswith('.')]
            plan = P.build(self.root, corpus=corpus)
        self.plan = plan
        self.corpus, self.tindex = self.plan.corpus, self.plan.tindex
        self._mentions = {}
        self._hmentions = None
        self._users = None

    # ---- references
    def mentions(self, rel):
        if rel not in self._mentions:
            self._mentions[rel] = P._mentions(self.corpus, rel)
        return self._mentions[rel]

    def users_index(self):
        if self._users is None:
            idx = defaultdict(set)
            for rel in self.corpus.c_files:
                for n in self.mentions(rel):
                    idx[n].add(rel)
            self._users = idx
        return self._users

    def header_mentions(self):
        """{name: {header}} for identifiers a header uses outside a declaration of that name."""
        if self._hmentions is None:
            idx = defaultdict(set)
            files = list(self.corpus.h_files) + list(getattr(self.corpus, 'h_files_generated', []))
            for h in files:
                sc = self.corpus.scan(h)
                counts = defaultdict(int)
                for m in cscan.IDENT.finditer(sc.masked):
                    counts[m.group(0)] += 1
                for d in sc.directives:          # macro bodies are blanked in the masked text
                    if d.kind == 'define':
                        for m in cscan.IDENT.finditer(d.arg):
                            counts[m.group(0)] += 1
                declared = defaultdict(int)
                for it in sc.items:
                    if it.kind == 'decl':
                        for d in it.decls:
                            if d.name:
                                declared[d.name] += 1
                    elif it.kind == 'def' and it.decls:
                        declared[it.decls[0].name] += 1
                for n, k in counts.items():
                    if k > declared.get(n, 0):
                        idx[n].add(h)
            self._hmentions = idx
        return self._hmentions

    # ---- per name
    def info(self, name):
        defs = [d for d in self.plan.defs.get(name, []) if not getattr(d, 'kind', '')]
        row = self.plan.functions.get(name)
        def_keys = [site_key(d.params, d.ret_spec, d.ret_ptr, self.tindex.visible(d.path)) for d in defs
                    if not d.static]
        info = NameInfo(name, row, defs, def_keys)
        for r in self.plan.sites_by_name.get(name, []):
            s = r.site
            if getattr(s, 'kind', '') == 'data' or s.storage == 'static':
                continue
            vis = self.tindex.visible(s.path)
            params = s.params
            arity = None if params is None else len([p for p in params if p not in (['void'], ['...'])])
            info.sites.append(SiteInfo(s.path, s.start, s.end, s.line, s.text, s.in_header, s.storage,
                                       site_key(params, s.ret_spec, s.ret_ptr, vis), r.cls, s.ndecl, s.cond,
                                       arity))
        own = {d.path for d in defs}
        info.users = sorted(self.users_index().get(name, ()))
        del own
        info.header_users = sorted(self.header_mentions().get(name, ()))
        return info

    def names_owned_by(self, header):
        return sorted(n for n, r in self.plan.functions.items()
                      if '@' not in n and r.status == 'header' and r.header == header)

    def conflicts(self):
        """Names with two or more distinct signature keys over definitions and declaration sites."""
        out = []
        for name in sorted(set(self.plan.sites_by_name) | set(self.plan.defs)):
            if not re.fullmatch(r'[A-Za-z_]\w*', name):
                continue
            info = self.info(name)
            if info.definitions or info.sites:
                if info.conflict:
                    out.append(info)
        return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument('--root', type=Path, default=HERE.parents[2])
    ap.add_argument('--header', help='names owned by this header')
    ap.add_argument('--name', nargs='*', default=[])
    ap.add_argument('--conflicts', action='store_true', help='summarise every conflicting name')
    ap.add_argument('--json', type=Path)
    args = ap.parse_args(argv)
    c = Census(args.root, log=lambda m: print(m, file=sys.stderr))
    names = list(args.name)
    if args.header:
        names += c.names_owned_by(args.header)
    rows = []
    if args.conflicts:
        infos = c.conflicts()
        owners = defaultdict(int)
        for i in infos:
            owners[i.owner or 'hold:' + (i.row.reason if i.row else 'no_definition')] += 1
        print(json.dumps(dict(conflicting_names=len(infos), sites=sum(len(i.sites) for i in infos),
                              top_owners=sorted(owners.items(), key=lambda kv: -kv[1])[:30]), indent=1))
        rows = [i.to_json() for i in infos]
    for n in names:
        info = c.info(n)
        rows.append(info.to_json())
        print('%s: %d keys, %d sites, %d users, owner %s' % (n, len(info.keys), len(info.sites), len(info.users),
                                                              info.owner))
        for k in info.keys:
            print('   ', key_text(k))
    if args.json:
        args.json.write_text(json.dumps(rows, indent=1) + '\n')
    return 0


if __name__ == '__main__':
    sys.exit(main())
