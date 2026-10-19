"""Resolve a ledger ``asm_path`` (e.g. ``asm/psyq/libcard/A74.s``) to the real file.

Ledger records name production assembly relative to the repository root, but the SLUS split
regenerates it under ``build_slus/asm``.  Lane and gate roots carry an ``asm -> build_slus/asm``
symlink (mk_scratch_root.sh, mk_ovl_root.sh); a canonical checkout may not.  Every reader goes
through this module so that both layouts resolve to the same file.

The LOGICAL name (the ledger string, ``asm/...``) is what inputs_sha keys and hashes use; only the
file read is redirected, so digests are identical with or without the symlink.
"""
from pathlib import Path

FALLBACK_PREFIX = 'build_slus'


def _fallback(root, rel):
    return Path(root) / FALLBACK_PREFIX / rel if rel.startswith('asm/') else None


def resolve(root, name):
    """root/name if it is a file, else root/build_slus/name for ``asm/`` names, else root/name."""
    root = Path(root)
    name = str(name)
    p = root / name
    if p.is_file():
        return p
    q = _fallback(root, name)
    if q is not None and q.is_file():
        return q
    return p


def is_file(root, path):
    """is_file() for an absolute path under root, honouring the build_slus/asm fallback."""
    root = Path(root)
    path = Path(path)
    if path.is_file():
        return True
    try:
        rel = path.relative_to(root).as_posix()
    except ValueError:
        return False
    return resolve(root, rel).is_file()


def logical(root, path):
    """Map a path under root/build_slus/asm back to its ``asm/`` name when root/asm is absent."""
    root = Path(root)
    try:
        rel = Path(path).relative_to(root).as_posix()
    except ValueError:
        return None
    pre = FALLBACK_PREFIX + '/'
    if rel.startswith(pre + 'asm/') and not (root / rel[len(pre):]).is_file():
        return rel[len(pre):]
    return rel
