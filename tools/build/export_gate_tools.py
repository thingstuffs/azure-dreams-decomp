"""Synchronize the disposable gate tool view without rewriting identical files."""
import argparse
import os
from pathlib import Path
import stat
import tempfile


def inputs(root):
    root = Path(root).absolute()
    wanted, source_directories = {}, set()

    def collect(source, target, active=()):
        if source.name in {'__pycache__', '.git', 'cache'} or source.suffix in {'.pyc', '.tmp'}:
            return
        if source.is_dir():
            source_directories.add(target)
            identity = source.resolve()
            if identity in active:
                raise ValueError('cyclic gate tool source: ' + str(source))
            for child in sorted(source.iterdir()):
                collect(child, target/child.name, (*active, identity))
        elif source.is_file():
            wanted[target] = source
        else:
            raise ValueError('missing gate export input: ' + str(source))

    collect(root/'tools/gate', Path('tools'))
    # Compile front ends import this build authority from the flat tool view.
    # Keep the source tree free of a second copy or a symlink in tools/gate.
    if (root/'tools/build/name_inputs.py').is_file():
        wanted[Path('tools/name_inputs.py')] = root/'tools/build/name_inputs.py'
    for name in ('cc.sh', 'ccproc.py', 'as.sh', 'compile_slots.py'):
        if (root/'tools/build'/name).is_file():
            wanted[Path('tools')/name] = root/'tools/build'/name
    if (root/'tools/learnings').is_dir():
        collect(root/'tools/learnings', Path('tools/learnings'))
    for name in ('aspsx_diff.py', 'objread.py', 'certify_overlay_module.py'):
        wanted[Path('tools/fidelity')/name] = root/'tools/fidelity'/name
    wanted[Path('tools/build/slus_rodata_trim.py')] = root/'tools/build/slus_rodata_trim.py'
    wanted[Path('tools/overlay_module_evidence.py')] = root/'tools/overlay_module_evidence.py'
    wanted[Path('work/g3/overlay_func_compare.py')] = root/'tools/gate/overlay_func_compare.py'

    directories = source_directories | {p for name in wanted for p in name.parents if p != Path('.')}
    return wanted, directories


def export(root, view):
    root, view = Path(root).absolute(), Path(view).absolute()
    if view.is_symlink() or view.resolve() == root.resolve() or not view.resolve().is_relative_to(root.resolve()):
        raise ValueError('gate tool view must be inside its build root')
    wanted, directories = inputs(root)
    for name in sorted(directories, key=lambda p: len(p.parts)):
        path = view/name
        if path.is_symlink():
            raise ValueError('gate export directory is a symlink: ' + str(path))
        path.mkdir(parents=True, exist_ok=True)
    written = removed = 0
    for name, source in sorted(wanted.items()):
        path = view/name
        if path.is_symlink():
            raise ValueError('gate export file is a symlink: ' + str(path))
        blob = source.read_bytes()
        mode = stat.S_IMODE(source.stat().st_mode)
        if not path.exists() or path.read_bytes() != blob:
            fd, temporary_name = tempfile.mkstemp(prefix='.export-', dir=path.parent)
            temporary = Path(temporary_name)
            try:
                with os.fdopen(fd, 'wb') as stream:
                    stream.write(blob)
                temporary.chmod(mode)
                temporary.replace(path)
            finally:
                temporary.unlink(missing_ok=True)
            written += 1
        elif stat.S_IMODE(path.stat().st_mode) != mode:
            path.chmod(mode)
    # The tool directory is wholly managed by mk_ovl_root. Include every extra
    # fidelity/review file above before pruning, so a repeated export is a no-op.
    for parent, dirs, files in os.walk(view/'tools', topdown=False, followlinks=False):
        for filename in files:
            path = Path(parent)/filename
            if path.relative_to(view) not in wanted:
                path.unlink()
                removed += 1
        for dirname in dirs:
            path = Path(parent)/dirname
            if path.relative_to(view) not in directories:
                if path.is_symlink():
                    path.unlink()
                else:
                    path.rmdir()
    return dict(written=written, removed=removed, unchanged=len(wanted)-written)


def verify(root, view):
    view = Path(view)
    wanted, directories = inputs(root)
    for name in directories:
        path = view/name
        if path.is_symlink() or not path.is_dir():
            raise ValueError('stale exported tool directory: ' + str(name) + '; run make configure')
    for name, source in wanted.items():
        path = view/name
        if path.is_symlink() or not path.is_file() or path.read_bytes() != source.read_bytes():
            raise ValueError('stale exported tool: ' + str(name) + '; run make configure')
    for parent, dirs, files in os.walk(view/'tools', followlinks=False):
        dirs[:] = [n for n in dirs if n != '__pycache__']
        for dirname in dirs:
            path = Path(parent)/dirname
            if path.is_symlink() or path.relative_to(view) not in directories:
                raise ValueError('unexpected exported tool directory: ' + str(path.relative_to(view)))
        for filename in files:
            path = Path(parent)/filename
            if path.relative_to(view) not in wanted:
                raise ValueError('unexpected exported tool: ' + str(path.relative_to(view)))


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument('root', type=Path)
    parser.add_argument('view', type=Path)
    args = parser.parse_args()
    export(args.root, args.view)


if __name__ == '__main__':
    main()
