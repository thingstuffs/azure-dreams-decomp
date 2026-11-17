"""Child-process half of mkbuild.unread_inputs_enforced (configure and bootstrap put this directory first on
PYTHONPATH while they run): a python subprocess that opens a ledger file of the root MKBUILD_UNREAD_ROOT names
(its real path, ending in a separator) outside the entries MKBUILD_CONFIGURE_LEDGERS lists (os.pathsep-separated,
relative to ledger/, directories ending in '/') fails, the same way an in-process open does.  Nothing binds those
files' content, so a reader would go stale silently.  Any other sitecustomize on the path still runs afterwards."""
import importlib.machinery
import importlib.util
import os
import sys

_HERE = os.path.dirname(os.path.realpath(__file__))


def _install():
    root = os.environ.get('MKBUILD_UNREAD_ROOT')
    if not root:
        return
    entries = [e for e in os.environ.get('MKBUILD_CONFIGURE_LEDGERS', '').split(os.pathsep) if e]
    files = frozenset(e for e in entries if not e.endswith('/'))
    directories = tuple(e for e in entries if e.endswith('/'))
    prefix = root + 'ledger/'

    def hook(event, args):
        if event != 'open' or not args or args[0] is None or isinstance(args[0], int):
            return
        try:
            path = os.fsdecode(args[0])
        except TypeError:
            return
        if 'ledger' not in path:
            return
        physical = os.path.realpath(path)
        if physical.startswith(prefix):
            relative = physical[len(prefix):]
            if relative not in files and relative + '/' not in directories and not relative.startswith(directories):
                raise ValueError(f'a configure/bootstrap subprocess ({os.path.basename(sys.argv[0] or "python")}) '
                                 f'read {path}, which mkbuild.CONFIGURE_LEDGERS leaves out of the configure and '
                                 'bootstrap inputs; add it there before reading it')
    sys.addaudithook(hook)


def _chain():
    rest = [p for p in sys.path if os.path.realpath(p or '.') != _HERE]
    spec = importlib.machinery.PathFinder.find_spec('sitecustomize', rest)
    if spec is not None and spec.loader is not None:
        module = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(module)


_install()
_chain()
