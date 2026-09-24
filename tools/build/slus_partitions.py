"""Explicit function provenance and source views for SLUS collector partitions.

This planning/rendering layer is intentionally independent of registry migration.
It does not activate modules, change recipes, or certify byte fidelity. Build and
verification consumers must validate the emitted object coverage before using it.
"""
from __future__ import annotations
import hashlib
import json
from pathlib import Path, PurePosixPath
import re

class PartitionError(ValueError):
    pass

IDENT = re.compile(r'[A-Za-z_][A-Za-z0-9_]*\Z')
CANONICAL = re.compile(r'func_[0-9A-F]{8}\Z')
RECIPE_KEYS = {'ccver', 'ccflags', 'asflags'}

def keys(value, expected, where):
    if not isinstance(value, dict) or set(value) != set(expected):
        raise PartitionError(f'{where}: expected keys {sorted(expected)}')

def path(value, where, prefix, suffix):
    if not isinstance(value, str) or not re.fullmatch(r'[A-Za-z0-9_./-]+', value):
        raise PartitionError(f'{where}: unsafe path')
    p = PurePosixPath(value)
    if p.is_absolute() or str(p) != value or not p.parts or any(x in ('.', '..') for x in p.parts) or p.parts[0] != prefix or p.suffix != suffix:
        raise PartitionError(f'{where}: unsafe path')
    return value

def functions(value, where):
    if not isinstance(value, list) or not value or any(not isinstance(x,str) or not CANONICAL.fullmatch(x) for x in value) or len(set(value)) != len(value):
        raise PartitionError(f'{where}: expected unique canonical functions')
    return list(value)

def recipe(value, where):
    keys(value, RECIPE_KEYS, where)
    if not isinstance(value['ccver'], str) or not re.fullmatch(r'[A-Za-z0-9_.-]+', value['ccver']):
        raise PartitionError(f'{where}: invalid compiler')
    for k in ('ccflags', 'asflags'):
        if not isinstance(value[k], str) or not re.fullmatch(r'[-A-Za-z0-9_./=+ ]*', value[k]):
            raise PartitionError(f'{where}: unsafe flags')
    return dict(value)

def load_plan(file):
    """Missing optional plans mean no partitions. Reject ambiguous provenance."""
    file = Path(file)
    if not file.exists():
        return []
    doc = json.loads(file.read_text())
    keys(doc, {'version','parents'}, 'plan')
    if type(doc['version']) is not int or doc['version'] != 1 or not isinstance(doc['parents'],list):
        raise PartitionError('plan: expected version 1 and parents list')
    ids, sources, owned = set(), set(), set()
    result = []
    for parent in doc['parents']:
        keys(parent, {'id','source','raw_sha256','recipe','functions','parts'}, 'parent')
        src = path(parent['source'], 'parent.source', 'src', '.c')
        rid = parent['id']
        if rid != 'slus/' + PurePosixPath(src).stem or rid in ids or src in sources:
            raise PartitionError('parent: duplicate or mismatched identity')
        ids.add(rid); sources.add(src)
        if not isinstance(parent['raw_sha256'],str) or not re.fullmatch(r'[0-9a-f]{64}',parent['raw_sha256']):
            raise PartitionError('parent: invalid frozen source hash')
        base = functions(parent['functions'],'parent.functions')
        if owned.intersection(base):
            raise PartitionError('parent: overlapping original emitted functions')
        owned.update(base)
        recipe(parent['recipe'],'parent.recipe')
        if not isinstance(parent['parts'],list) or not parent['parts']:
            raise PartitionError('parent: expected parts')
        moved, owners = set(), set()
        for part in parent['parts']:
            keys(part, {'module','functions'}, 'part')
            module = part['module']
            if not isinstance(module,str) or not re.fullmatch(r'[A-Za-z0-9_-]+',module) or module in owners:
                raise PartitionError('part: duplicate or invalid module')
            owners.add(module)
            selected = functions(part['functions'],'part.functions')
            if not set(selected) <= set(base) or moved.intersection(selected):
                raise PartitionError('part: unknown or duplicate function ownership')
            moved.update(selected)
        if moved == set(base):
            raise PartitionError('parent: empty remainder requires an explicit row-retirement migration')
        result.append(parent)
    return result

def validate_context(plan, modules, logical_edges, raw_root, aliases=None):
    """Validate original recipe/raw provenance and known destination modules."""
    by_module = {m['name']:m for m in modules}
    if len(by_module) != len(modules):
        raise PartitionError('duplicate destination module')
    by_source = {e['src']:e for e in logical_edges}
    if len(by_source) != len(logical_edges):
        raise PartitionError('duplicate logical source')
    module_sources = {m['source'] for m in modules}
    whole_rows = {m['id'] for module in modules for m in module['members']}
    whole_functions = {f for module in modules for m in module['members'] for f in m['functions']}
    for parent in plan:
        if parent['source'] in module_sources:
            raise PartitionError('partition parent source is also a module aggregator')
        if parent['id'] in whole_rows:
            raise PartitionError('partition parent is also a whole module member')
        e = by_source.get(parent['source'])
        if not e or {k:e[k] for k in RECIPE_KEYS} != parent['recipe']:
            raise PartitionError('partition parent recipe drift: '+parent['id'])
        raw = Path(raw_root) / PurePosixPath(parent['source']).name
        if not raw.is_file() or hashlib.sha256(raw.read_bytes()).hexdigest() != parent['raw_sha256']:
            raise PartitionError('partition frozen source mismatch: '+parent['id'])
        if set(spans(raw.read_text(),aliases)) != set(parent['functions']):
            raise PartitionError('partition functions differ from frozen definitions: '+parent['id'])
        if whole_functions.intersection(parent['functions']):
            raise PartitionError('partition function is also owned by a whole module member')
        for part in parent['parts']:
            if part['module'] not in by_module:
                raise PartitionError('unknown destination module: '+part['module'])
    return True

def lexical_mask(source):
    """Blank comments/literals/directives while retaining byte offsets and lines."""
    chars=list(source); i=0; directives=[]
    def blank(a,b):
        for j in range(a,b):
            if chars[j] != '\n': chars[j]=' '
    while i<len(source):
        if source.startswith('//',i):
            end=source.find('\n',i);end=len(source) if end<0 else end;blank(i,end);i=end
        elif source.startswith('/*',i):
            end=source.find('*/',i+2)
            if end<0: raise PartitionError('unterminated C comment')
            end+=2;blank(i,end);i=end
        elif source[i] in ('"', "'"):
            quote=source[i];end=i+1
            while end<len(source):
                if source[end]=='\\':end+=2;continue
                if source[end]==quote:break
                if source[end]=='\n':raise PartitionError('unterminated C literal')
                end+=1
            if end>=len(source):raise PartitionError('unterminated C literal')
            end+=1;blank(i,end);i=end
        elif source[i]=='#' and not source[source.rfind('\n',0,i)+1:i].strip():
            end=i
            while True:
                end=source.find('\n',end)
                if end<0:end=len(source);break
                if source[end-1:end]=='\\':end+=1;continue
                break
            directives.append((i,end,source[i:end]));blank(i,end);i=end
        else:i+=1
    return ''.join(chars),directives

def spans(source, aliases=None):
    """Find ordinary top-level canonical definitions, rejecting ambiguous syntax.

    This is a conservative source-view extractor, not a complete C parser.
    Conditional definitions, unrecognized canonical definitions, and macro C
    includes require a separately reviewed source representation.
    """
    aliases=aliases or {};masked,directives=lexical_mask(source)
    if any(re.match(r'#\s*include\s*["<][^">]*\.c[">]',d) for _,_,d in directives):
        raise PartitionError('nested C includes are unsupported in partition parents')
    depth=[];level=0
    for c in masked:
        depth.append(level)
        if c=='{':level+=1
        elif c=='}':level-=1
        if level<0:raise PartitionError('unbalanced C braces')
    if level:raise PartitionError('unbalanced C braces')
    pattern=re.compile(r'^[ \t]*[A-Za-z_][A-Za-z0-9_ \t\n*]*?\b([A-Za-z_][A-Za-z0-9_]*)\s*\([^;{}]*\)\s*\{',re.M)
    result={}
    for m in pattern.finditer(masked):
        name=aliases.get(m.group(1),m.group(1))
        if not CANONICAL.fullmatch(name):continue
        if depth[m.start()] != 0:continue
        brace=m.end()-1;end=brace+1;balance=1
        while balance:
            if masked[end]=='{':balance+=1
            elif masked[end]=='}':balance-=1
            end+=1
        nesting=0
        for a,b,d in directives:
            if a>=m.start():break
            if re.match(r'#\s*(if|ifdef|ifndef)\b',d):nesting+=1
            elif re.match(r'#\s*endif\b',d):nesting-=1
        if nesting or any(m.start()<=a<end for a,b,d in directives):
            raise PartitionError('preprocessor-dependent function is unsupported: '+name)
        if name in result:raise PartitionError('duplicate C definition: '+name)
        result[name]=(m.start(),brace,end)
    return result

def render_parent(parent, source, aliases=None):
    """Return remainder plus function-only include fragments, with total coverage."""
    found=spans(source,aliases)
    if set(found)!=set(parent['functions']):
        raise PartitionError('source definition coverage differs: missing='+str(sorted(set(parent['functions'])-set(found)))+' extra='+str(sorted(set(found)-set(parent['functions']))))
    moved={f for part in parent['parts'] for f in part['functions']}
    chunks=[];last=0
    for f,(a,b,c) in sorted(found.items(),key=lambda item:item[1][0]):
        if f not in moved:continue
        # Keep the declaration so remaining functions retain the original type.
        replacement=source[a:b].rstrip()+';'
        replacement+='\n'*(source[a:c].count('\n')-replacement.count('\n'))
        chunks.extend((source[last:a],replacement));last=c
    chunks.append(source[last:])
    parts={part['module']:'\n\n'.join(source[found[f][0]:found[f][2]] for f in part['functions'])+'\n' for part in parent['parts']}
    return {'remainder':''.join(chunks),'parts':parts}

def expected_units(plan, modules):
    """Expected complete canonical function sets, keyed by physical source."""
    expected={m['source']:set(f for member in m['members'] for f in member['functions']) for m in modules}
    module_source={m['name']:m['source'] for m in modules}
    for parent in plan:
        moved=set()
        for part in parent['parts']:
            expected[module_source[part['module']]].update(part['functions']);moved.update(part['functions'])
        expected[parent['source']]=set(parent['functions'])-moved
    return expected

def check_emitted(expected, emitted):
    """Fail closed on absent units, missing/extra functions, or duplicate owners."""
    if set(expected)!=set(emitted):raise PartitionError('emitted physical unit set differs')
    owner={}
    for unit, wanted in expected.items():
        got=list(emitted[unit])
        if len(set(got))!=len(got) or set(got)!=set(wanted):
            raise PartitionError('emitted function coverage differs: '+unit)
        for f in got:
            if f in owner:raise PartitionError('function emitted by multiple physical owners: '+f)
            owner[f]=unit
    return owner

def fingerprint(plan, modules, sources, headers, aliases=None):
    """Hash the complete connected input closure supplied by a build consumer."""
    required_sources={p['source'] for p in plan} | {m['source'] for m in modules} | {member['source'] for m in modules for member in m['members']}
    required_headers={header for m in modules for header in m['headers']}
    if not required_sources <= set(sources) or not required_headers <= set(headers):
        raise PartitionError('fingerprint input closure is incomplete')
    h=hashlib.sha256(json.dumps({'parents':plan,'modules':modules,'aliases':aliases or {}},sort_keys=True).encode())
    h.update(Path(__file__).read_bytes())
    for kind, files in [('source',sources),('header',headers)]:
        for name,content in sorted(files.items()):
            h.update(json.dumps([kind,name,content],ensure_ascii=True).encode())
    return h.hexdigest()

def connected_context(row_id, plan, modules):
    """Return all parent/module inputs connected to a logical row.

    A parent's several destinations and each destination's other contributors
    must travel together for evidence freshness. This does not merge their C TUs.
    """
    rows={row_id}; selected_modules=set(); selected_parents=set()
    while True:
        before=(len(rows),len(selected_modules),len(selected_parents))
        for parent in plan:
            owners={part['module'] for part in parent['parts']}
            if parent['id'] in rows or owners & selected_modules:
                selected_parents.add(parent['id']);rows.add(parent['id']);selected_modules.update(owners)
        for module in modules:
            members={m['id'] for m in module['members']}
            if module['name'] in selected_modules or members & rows:
                selected_modules.add(module['name']);rows.update(members)
        if before==(len(rows),len(selected_modules),len(selected_parents)):break
    return ([p for p in plan if p['id'] in selected_parents],
            [m for m in modules if m['name'] in selected_modules])

def row_units(row_id, plan, modules):
    """Physical compilation contexts and exact function scopes for one row."""
    by_name={m['name']:m for m in modules}
    parent=next((p for p in plan if p['id']==row_id),None)
    if parent:
        moved={f for part in parent['parts'] for f in part['functions']}
        result=[{'source':parent['source'],'recipe':parent['recipe'],
                 'functions':sorted(set(parent['functions'])-moved),'role':'remainder'}]
        for part in parent['parts']:
            module=by_name[part['module']]
            result.append({'source':module['source'],'recipe':module['recipe'],
                           'functions':list(part['functions']),'role':'module','module':module['name']})
        return result
    for module in modules:
        for member in module['members']:
            if member['id']==row_id:
                return [{'source':module['source'],'recipe':module['recipe'],
                         'functions':list(member['functions']),'role':'module','module':module['name']}]
    return []

def output_paths(plan, out_dir='build/partition_sources'):
    """Deterministic build-root-relative paths; logical identities stay separate."""
    if not isinstance(out_dir,str) or not re.fullmatch(r'[A-Za-z0-9_./-]+',out_dir):
        raise PartitionError('unsafe partition output directory')
    out=PurePosixPath(out_dir)
    if out.is_absolute() or str(out)!=out_dir or len(out.parts)<2 or out.parts[0] not in ('build','build_nm') or any(p in ('.','..') for p in out.parts):
        raise PartitionError('unsafe partition output directory')
    remainders={}; parts={}; seen=set()
    for parent in plan:
        stem=PurePosixPath(parent['source']).stem
        remainder=str(out/(stem+'.c'));remainders[parent['source']]=remainder
        one={part['module']:str(out/(stem+'__'+part['module']+'.c')) for part in parent['parts']}
        paths=[remainder,*one.values()]
        if seen.intersection(paths) or len(paths)!=len(set(paths)):
            raise PartitionError('generated partition path collision')
        seen.update(paths);parts[parent['id']]=one
    return {'remainders':remainders,'parts':parts}

def project_edges(edges, plan, out_dir='build/partition_sources'):
    """Recover one original logical edge per parent without concealing drift."""
    paths=output_paths(plan,out_dir)
    generated={paths['remainders'][p['source']]:p for p in plan}
    originals={p['source'] for p in plan};seen=set();result=[]
    for edge in edges:
        if edge['src'] in originals:
            raise PartitionError('partition parent bypasses generated remainder')
        parent=generated.get(edge['src'])
        if parent:
            if parent['id'] in seen:raise PartitionError('duplicate partition remainder edge')
            seen.add(parent['id'])
            if {k:edge[k] for k in RECIPE_KEYS}!=parent['recipe']:
                raise PartitionError('partition remainder recipe drift')
            if edge['out']!=str(PurePosixPath(out_dir).parts[0]+'/src/'+PurePosixPath(parent['source']).stem+'.o'):
                raise PartitionError('partition remainder object identity drift')
            edge=dict(edge,src=parent['source'])
        result.append(edge)
    if seen!={p['id'] for p in plan}:raise PartitionError('missing partition remainder edge')
    return result

def read_aliases(file):
    aliases={}
    for line in Path(file).read_text().splitlines():
        columns=line.split('#',1)[0].split('\t')
        if len(columns)<3:continue
        canonical,renamed=columns[1].strip(),columns[2].strip()
        # The table contains non-function metadata too; only SLUS-style names
        # participate in this source-definition extractor.
        if not CANONICAL.fullmatch(canonical):continue
        if canonical==renamed:continue
        if not IDENT.fullmatch(renamed) or CANONICAL.fullmatch(renamed):
            raise PartitionError('invalid canonical name alias target: '+renamed)
        if renamed in aliases and aliases[renamed]!=canonical:
            raise PartitionError('ambiguous canonical name alias: '+renamed)
        aliases[renamed]=canonical
    return aliases

def render_files(plan, root, out_dir='build/partition_sources', aliases=None):
    """Render canonical source inputs into explicit Ninja outputs, never inputs."""
    root=Path(root).resolve();paths=output_paths(plan,out_dir);pending={}
    for parent in plan:
        rendered=render_parent(parent,(root/parent['source']).read_text(),aliases)
        pending[paths['remainders'][parent['source']]]=rendered['remainder']
        for module,text in rendered['parts'].items():pending[paths['parts'][parent['id']][module]]=text
    # Complete coverage and destination checks precede every write.
    for relative in pending:
        target=root/relative
        if target.is_symlink() or not target.parent.resolve().is_relative_to(root):
            raise PartitionError('partition output escapes build root: '+relative)
    for relative,text in pending.items():
        target=root/relative;target.parent.mkdir(parents=True,exist_ok=True)
        if target.is_symlink() or not target.parent.resolve().is_relative_to(root):
            raise PartitionError('partition output escapes build root: '+relative)
        if not target.exists() or target.read_text()!=text:target.write_text(text)
    return paths


def emitted_functions(file, aliases=None):
    """Read defined ELF STT_FUNC symbols, including local functions and duplicates.

    Use the already-required MIPS binutils rather than relying on C syntax or
    `nm` global-only filters. Retain a list so duplicate symbols cannot collapse.
    """
    import os
    import subprocess
    aliases = aliases or {}
    env = dict(os.environ, LC_ALL='C')
    result = subprocess.run(['mipsel-linux-gnu-readelf', '--wide', '--symbols', str(file)],
                            capture_output=True, text=True, env=env)
    if result.returncode:
        raise PartitionError('cannot read emitted functions: ' + str(file) + ': ' + result.stderr[-300:])
    found = []
    for line in result.stdout.splitlines():
        fields = line.split()
        if len(fields) >= 8 and fields[0].endswith(':') and fields[3] == 'FUNC':
            if fields[6].isdigit() and int(fields[6]) != 0:
                found.append(aliases.get(fields[7], fields[7]))
    return found


def check_emitted_objects(plan, modules, root, aliases=None):
    """Check every partition remainder and destination, not just edited rows."""
    names = {part['module'] for parent in plan for part in parent['parts']}
    owners = [module for module in modules if module['name'] in names]
    if {m['name'] for m in owners} != names:
        raise PartitionError('unknown destination in emitted coverage plan')
    expected = expected_units(plan, owners)
    actual = {source: emitted_functions(Path(root) / 'build/src' / (PurePosixPath(source).stem + '.o'), aliases)
              for source in expected}
    check_emitted(expected, actual)
    return actual


def main():
    import argparse
    parser=argparse.ArgumentParser(description=__doc__)
    sub=parser.add_subparsers(dest='command',required=True)
    render=sub.add_parser('render')
    render.add_argument('--plan',required=True)
    render.add_argument('--output-dir',default='build/partition_sources')
    render.add_argument('--names',required=True)
    emitted=sub.add_parser('check-emitted')
    emitted.add_argument('--plan',required=True)
    emitted.add_argument('--manifest',required=True)
    emitted.add_argument('--names',required=True)
    emitted.add_argument('--stamp',required=True)
    args=parser.parse_args()
    try:
        if not Path(args.plan).is_file():
            raise PartitionError('partition plan is missing: '+args.plan)
        plan = load_plan(args.plan)
        aliases = read_aliases(args.names)
        if args.command == 'render':
            render_files(plan,Path.cwd(),args.output_dir,aliases)
        else:
            from slus_modules import load_manifest
            stamp = Path(path(args.stamp, 'coverage stamp', 'build', '.ok'))
            if stamp.is_symlink() or not stamp.parent.resolve().is_relative_to(Path.cwd().resolve()):
                raise PartitionError('coverage stamp escapes build root')
            stamp.unlink(missing_ok=True)
            if not plan:
                raise PartitionError('emitted coverage requires a nonempty partition plan')
            actual = check_emitted_objects(plan,load_manifest(args.manifest),Path.cwd(),aliases)
            stamp.parent.mkdir(parents=True,exist_ok=True)
            stamp.write_text(json.dumps(actual,sort_keys=True)+'\n')
    except (OSError,ValueError) as exc:
        parser.exit(1,str(exc)+'\n')

if __name__=='__main__':
    main()
