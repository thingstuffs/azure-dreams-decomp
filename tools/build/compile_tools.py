"""Local import closure of the make compile entry points.

Only executed module bodies and reachable function/class bodies contribute
imports. Scanning every function of a multi-command module would pull in the
certification/reporting commands that compile never calls. Shell front ends and
file-loaded native helpers have explicit entry points; tests are never scanned.
"""
import ast
import hashlib
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


# The object key (tools/build/object_cache.py) binds only the tools that turn a
# source into object bytes; docs/OBJECT_CACHE.md "Tools in the object key" gives
# the evidence. Placement, link, layout and gate tools stay in compiletools.list
# (they still schedule every compile rule) and in linktools.list, which every
# image rule depends on, so an edit to one of them reruns the gates and relinks
# while identical objects are restored. Native module recipes and recipes on the
# live noreturn path run gate code inside the compile and keep the whole list.
#
# Subprocess front ends of every object: cc.sh -> ccproc.py (+ name_inputs.py)
# -> maspsx -> GNU as, as.sh -> asproc.py, and the SLUS post-compile scripts.
# tools/build/tests/test_object_cache.py checks this list against the static import closure of
# FRONTEND_SCRIPTS. The compile-time guard sees only code run in the compile process, so a module a
# subprocess front end imports is caught by that unit test, not at compile time.
OBJECT_FRONTENDS = (
    'tools/build/cc.sh', 'tools/build/as.sh', 'tools/build/ccproc.py', 'tools/build/asproc.py',
    'tools/build/name_inputs.py', 'tools/build/compile_slots.py',
    'tools/build/slus_rodata_trim.py', 'tools/build/slus_data_pieces.py', 'tools/build/slus_modules.py',
    'tools/build/retail_spans.py', 'toolchain/maspsx/maspsx.py', 'toolchain/maspsx/maspsx/__init__.py',
)
FRONTEND_SCRIPTS = ('tools/build/ccproc.py', 'tools/build/asproc.py', 'toolchain/maspsx/maspsx.py',
                    'tools/build/slus_rodata_trim.py', 'tools/build/slus_data_pieces.py',
                    'tools/build/compile_slots.py')
# The cache's own key, witness and projection rules: a change re-keys every object.
OBJECT_MACHINERY = ('tools/build/object_cache.py', 'tools/build/content_cache.py',
                    'tools/build/declaration_projection.py', 'tools/build/compile_tools.py')
# mkbuild.py runs in process. Its compile path is these functions and every
# mkbuild function they name; main() is kept but not followed (it also names
# the generator). The other top-level functions (recipe and image generation,
# check) are left out of the object key: the recipe JSON and the generated
# files they write are key inputs already.
DRIVER = 'tools/build/mkbuild.py'
DRIVER_ENTRIES = {'overlay': ('compile_one', 'compile_uncached'),
                  'slus': ('slus_compile_one', 'slus_compile_uncached')}
DRIVER_KEPT = ('main',)


def driver_functions(tree, kind):
    """Top-level mkbuild definitions an object compile of `kind` can run."""
    definitions = {n.name: n for n in tree.body
                   if isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef))}
    reached, pending = set(), list(DRIVER_ENTRIES[kind])
    while pending:
        name = pending.pop()
        if name in reached or name not in definitions:
            continue
        reached.add(name)
        pending.extend(n.id for n in ast.walk(definitions[name])
                       if isinstance(n, ast.Name) and n.id in definitions)
    return reached | {n for n in DRIVER_KEPT if n in definitions}


def driver_digest(root, kind):
    """Python syntax of mkbuild's module statements and of its compile path for `kind`.

    Returns (digest, functions). A file that does not parse returns its raw
    digest and None: every function then counts as compile path."""
    data = (Path(root)/DRIVER).read_bytes()
    try:
        tree = ast.parse(data.decode('utf-8'), filename=DRIVER)
    except (SyntaxError, UnicodeDecodeError):
        return hashlib.sha256(data).hexdigest(), None
    functions = driver_functions(tree, kind)
    kept = [n for n in tree.body if not isinstance(n, (ast.FunctionDef, ast.AsyncFunctionDef, ast.ClassDef))
            or n.name in functions]
    syntax = ast.dump(ast.Module(body=kept, type_ignores=[]), include_attributes=False).encode()
    return hashlib.sha256(b'python-ast-compile-path-v1\0' + kind.encode() + b'\0' + syntax).hexdigest(), functions


def object_tools(root):
    """Tool files an object key binds by raw bytes: front ends, their build-view copies, cache rules."""
    names = set(OBJECT_FRONTENDS) | set(OBJECT_MACHINERY)
    return sorted(names | set(view_copies(root, names)))


def semantic_digest(root, name):
    """Bind executed Python syntax for the monolithic compile driver.

    A comment/format-only edit to mkbuild.py changes neither its Python code
    nor an object. Other compile tools keep raw-byte identities. If parsing
    fails, the raw digest is the conservative fallback.
    """
    data = (Path(root)/name).read_bytes()
    if name == 'tools/build/mkbuild.py':
        try:
            tree = ast.parse(data.decode('utf-8'), filename=name)
        except (SyntaxError, UnicodeDecodeError):
            pass
        else:
            syntax = ast.dump(tree, include_attributes=False).encode()
            return hashlib.sha256(b'python-ast-v1\0' + syntax).hexdigest()
    return hashlib.sha256(data).hexdigest()


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
