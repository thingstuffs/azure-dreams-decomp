"""Local import closure of the make compile entry points.

Only executed module bodies and reachable function/class bodies contribute
imports. Scanning every function of a multi-command module would pull in the
certification/reporting commands that compile never calls. Shell front ends and
file-loaded native helpers have explicit entry points; tests are never scanned.
"""
import ast
from pathlib import Path


ENTRY_POINTS = (
    'tools/build/mkbuild.py', 'tools/build/ccproc.py', 'tools/build/asproc.py',
    'tools/build/slus_rodata_trim.py', 'tools/build/slus_data_pieces.py',
    'tools/gate/overlay_module_gate.py', 'tools/gate/gen_noreturn_syms.py',
    'tools/gate/overlay_local_gate.py', 'toolchain/maspsx/maspsx.py',
)
FUNCTIONS = {
    'tools/build/mkbuild.py': ('compile_one', 'build_native', 'slus_compile_one'),
    'tools/build/slus_rodata_trim.py': ('main',),
    'tools/build/slus_data_pieces.py': ('main',),
    # The native builder calls through a module passed as G to allocation code.
    'tools/gate/overlay_module_gate.py': ('build', 'sections', 'payload_spec'),
    # overlay_evidence loads this module by filename and calls through its result.
    'tools/gate/gen_noreturn_syms.py': ('scan_text',),
    # load_gate imports this module by name, rather than a Python import statement.
    'tools/gate/overlay_local_gate.py': (),
    'toolchain/maspsx/maspsx.py': ('main',),
}
SHELL_SCRIPTS = ('tools/build/cc.sh', 'tools/build/as.sh')


def closure(root, starts=ENTRY_POINTS):
    root = Path(root)
    searches = [root, root/'tools', root/'tools/build', root/'tools/gate',
                root/'tools/fidelity', root/'tools/link', root/'toolchain/maspsx']
    modules, pending, activated = {}, [], set()

    def resolve(name, parent=None):
        suffix = name.replace('.', '/')
        for directory in ([parent] if parent else []) + searches:
            # A package wins over a sibling script (maspsx is both).
            for candidate in (directory/suffix/'__init__.py', directory/(suffix+'.py')):
                if candidate.is_file():
                    return candidate
        return None

    def load(path):
        name = path.relative_to(root).as_posix()
        if name in modules:
            return name
        if 'tests' in path.parts or path.name.startswith('test_'):
            raise ValueError('compile entry point imports a test: ' + name)
        tree = ast.parse(path.read_text(), filename=name)
        definitions = {n.name: n for n in tree.body
                       if isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef))}
        modules[name] = dict(path=path, definitions=definitions, aliases={})
        pending.append((name, tree))
        parent = path.parent
        while parent != root:
            init = parent/'__init__.py'
            if init.is_file():
                load(init)
            parent = parent.parent
        return name

    def activate(name, member):
        key = (name, member)
        if key in activated:
            return
        activated.add(key)
        node = modules[name]['definitions'].get(member)
        if node is not None:
            pending.append((name, node))

    def alias(name, local, dep, member=None):
        if dep is None:
            return
        target = load(dep)
        modules[name]['aliases'].setdefault(local, set()).add((target, member))

    def imports(name, node):
        if isinstance(node, ast.Import):
            for item in node.names:
                # Without 'as', Python binds the first component of a dotted import.
                bound = item.asname or item.name.split('.')[0]
                dep = resolve(item.name)
                if dep is not None:
                    load(dep)
                alias(name, bound, resolve(item.name if item.asname else bound))
        elif isinstance(node, ast.ImportFrom):
            parent = modules[name]['path'].parent if node.level else None
            for _ in range(max(0, node.level-1)):
                parent = parent.parent
            module = node.module or ''
            dep = resolve(module, parent) if module else None
            if dep is not None:
                load(dep)
            for item in node.names:
                if item.name == '*':
                    if dep is not None:
                        # A wildcard can expose any callable; retain all its bodies.
                        target = load(dep)
                        for member in modules[target]['definitions']:
                            activate(target, member)
                    continue
                child = resolve('.'.join(filter(None, (module, item.name))), parent)
                alias(name, item.asname or item.name, child or dep,
                      None if child else item.name)

    def expression(name, node):
        # Calling or passing a local function can execute its lazy imports.
        # Attribute receivers resolve through Python import bindings. Native G
        # is the overlay_module_gate namespace passed explicitly to Z.build.
        if isinstance(node, ast.Name) and isinstance(node.ctx, ast.Load):
            if node.id in modules[name]['definitions']:
                activate(name, node.id)
            for target, member in modules[name]['aliases'].get(node.id, ()):
                if member is not None:
                    activate(target, member)
        elif isinstance(node, ast.Attribute):
            chain, receiver = [node.attr], node.value
            while isinstance(receiver, ast.Attribute):
                chain.insert(0, receiver.attr)
                receiver = receiver.value
            if isinstance(receiver, ast.Name):
                bindings = modules[name]['aliases'].get(receiver.id, set())
                if receiver.id == 'G' and name in (
                        'tools/gate/overlay_native_allocations.py',
                        'tools/gate/overlay_switch_allocations.py',
                        'tools/gate/overlay_module_placements.py'):
                    bindings = {('tools/gate/overlay_module_gate.py', None)}
                for target, member in bindings:
                    if member is not None:
                        activate(target, member)
                        continue
                    current = target
                    for part in chain[:-1]:
                        refs = modules[current]['aliases'].get(part, set())
                        choices = [n for n, m in refs if m is None]
                        if not choices:
                            break
                        current = choices[0]
                    else:
                        activate(current, chain[-1])

    def walk(name, node, outer=False):
        if not outer and isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef)):
            # Defaults/decorators execute at definition time, bodies do not.
            for item in node.decorator_list:
                walk(name, item)
            if isinstance(node, ast.ClassDef):
                for item in node.bases + [k.value for k in node.keywords]:
                    walk(name, item)
                for item in node.body:
                    walk(name, item)
            if isinstance(node, (ast.FunctionDef, ast.AsyncFunctionDef)):
                for item in node.args.defaults + [n for n in node.args.kw_defaults if n is not None]:
                    walk(name, item)
            return
        if isinstance(node, ast.If) and isinstance(node.test, ast.Compare):
            if (isinstance(node.test.left, ast.Name) and node.test.left.id == '__name__'
                    and any(isinstance(c, ast.Constant) and c.value == '__main__' for c in node.test.comparators)):
                return  # Script roots select their concrete subcommands above.
        imports(name, node)
        expression(name, node)
        for child in ast.iter_child_nodes(node):
            # Activating a class conservatively activates every method. Python
            # dispatch/self calls need not be resolved by this import scanner.
            walk(name, child, outer=isinstance(node, ast.ClassDef))

    for item in starts:
        name = load(root/item)
        for member in FUNCTIONS.get(item, ()):
            activate(name, member)
    while pending:
        name, node = pending.pop(0)
        walk(name, node, outer=True)
    # Alias bindings can be discovered after a caller (mutually imported
    # modules). Revisit the executed scopes until the closure stabilizes.
    previous = None
    while previous != (len(modules), len(activated)):
        previous = len(modules), len(activated)
        for name, member in list(activated):
            node = modules[name]['definitions'].get(member)
            if node is not None:
                walk(name, node, outer=True)
        while pending:
            name, node = pending.pop(0)
            walk(name, node, outer=True)
    return sorted(modules)


def view_copies(root, sources):
    root = Path(root)
    result = {}
    frontends = {'cc.sh', 'ccproc.py', 'as.sh', 'asproc.py', 'name_inputs.py', 'compile_slots.py'}
    for name in sources:
        if name.startswith('tools/gate/'):
            result['build_ovl/tools/' + name[len('tools/gate/'):]] = name
        elif name.startswith('tools/build/') and Path(name).name in frontends:
            result['build_ovl/tools/' + Path(name).name] = name
        elif name == 'tools/overlay_module_evidence.py':
            result['build_ovl/tools/overlay_module_evidence.py'] = name
    return result


def inputs(root):
    sources = set(closure(root)) | set(SHELL_SCRIPTS)
    return sorted(sources | set(view_copies(root, sources)))


def verify(root, names):
    expected = inputs(root)
    if sorted(names) != expected:
        raise ValueError('stale compiletools list; run make configure')
    sources = [n for n in expected if not n.startswith('build_ovl/')]
    for exported, authority in view_copies(root, sources).items():
        if (Path(root)/exported).read_bytes() != (Path(root)/authority).read_bytes():
            raise ValueError('stale exported compiler tool: ' + exported + '; run make configure')
