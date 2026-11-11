"""Child-process half of mkbuild.unread_inputs_enforced (configure and bootstrap put this directory first on
PYTHONPATH while they run): a python subprocess that opens one of the files named in MKBUILD_UNREAD_INPUTS
(os.pathsep-separated real paths) fails, the same way an in-process open does.  Nothing binds those files' content,
so a reader would go stale silently.  Any other sitecustomize on the path still runs afterwards."""
import importlib.machinery
import importlib.util
import os
import sys

_HERE = os.path.dirname(os.path.realpath(__file__))


def _install():
    value = os.environ.get('MKBUILD_UNREAD_INPUTS')
    if not value:
        return
    paths = frozenset(p for p in value.split(os.pathsep) if p)
    bases = frozenset(os.path.basename(p) for p in paths)

    def hook(event, args):
        if event != 'open' or not args or args[0] is None or isinstance(args[0], int):
            return
        try:
            path = os.fsdecode(args[0])
        except TypeError:
            return
        if os.path.basename(path) in bases and os.path.realpath(path) in paths:
            raise ValueError(f'a configure/bootstrap subprocess ({os.path.basename(sys.argv[0] or "python")}) read '
                             f'{path}, which mkbuild.UNREAD_LEDGERS leaves out of the configure and bootstrap inputs; '
                             'move it back into the inventory before reading it')
    sys.addaudithook(hook)


def _chain():
    rest = [p for p in sys.path if os.path.realpath(p or '.') != _HERE]
    spec = importlib.machinery.PathFinder.find_spec('sitecustomize', rest)
    if spec is not None and spec.loader is not None:
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)


_install()
_chain()
