"""Atomic file replacement for ledgers and name tables.

A tool that rewrites ledger/*.jsonl or config/names.tsv with open(path, 'w') truncates the file first: a crash, a
kill or a full disk in the middle leaves a short file, and every reader (another tool, a build, a landing) sees it.
write_text / write_bytes write a temporary file in the SAME directory, flush and fsync it, copy the old file's
permissions, then os.replace it over the target (atomic on POSIX within one filesystem). The target is either the old
file or the new one, never a mix. A symlink target is followed, so the link itself is kept. On any error the temporary
file is removed and the target is untouched."""
from __future__ import annotations
import fcntl
import os
import shutil
import tempfile


def _replace(path, blob: bytes, take_lock: bool = True) -> None:
    path = os.path.realpath(os.fspath(path))
    directory, name = os.path.split(path)
    fd, tmp = tempfile.mkstemp(dir=directory or '.', prefix='.' + name + '.', suffix='.tmp')
    try:
        with os.fdopen(fd, 'wb') as handle:
            handle.write(blob)
            handle.flush()
            os.fsync(handle.fileno())
        try:
            shutil.copymode(path, tmp)
        except FileNotFoundError:
            os.chmod(tmp, 0o666 & ~_umask())
        # common.append_text_locked appends under an flock on the target: take the same lock around the rename so an
        # appender that already passed its inode check cannot write into the file we are replacing
        lock = None
        try:
            if not take_lock:   # the caller (update_bytes) already holds the flock on this file
                raise OSError
            lock = os.open(path, os.O_RDONLY)
            fcntl.flock(lock, fcntl.LOCK_EX)
        except OSError:
            if lock is not None:
                os.close(lock)
            lock = None
        try:
            os.replace(tmp, path)
        finally:
            if lock is not None:
                os.close(lock)
    except BaseException:
        try:
            os.unlink(tmp)
        except OSError:
            pass
        raise


def _umask() -> int:
    mask = os.umask(0)
    os.umask(mask)
    return mask


def write_bytes(path, data: bytes) -> None:
    _replace(path, bytes(data))


def write_text(path, text: str, encoding: str = 'utf-8', errors: str = 'strict') -> None:
    _replace(path, text.encode(encoding, errors))


def update_bytes(path, fn) -> None:
    """Read-modify-write under the flock that common.append_text_locked takes: new = fn(current bytes) replaces the file, and
    an append that arrives between the read and the replace waits on the lock, then retries on the NEW file (never lost).
    The file is created empty when missing. fn returns the new bytes, or None to leave the file alone."""
    path = os.path.realpath(os.fspath(path))
    while True:
        fd = os.open(path, os.O_RDWR | os.O_CREAT, 0o666)
        try:
            fcntl.flock(fd, fcntl.LOCK_EX)
            try:
                a, b = os.stat(path), os.fstat(fd)
                same = (a.st_ino, a.st_dev) == (b.st_ino, b.st_dev)
            except FileNotFoundError:
                same = False
            if not same:
                continue
            with open(path, 'rb') as handle:
                current = handle.read()
            new = fn(current)
            if new is not None and new != current:
                _replace(path, bytes(new), take_lock=False)
            return
        finally:
            os.close(fd)


def append_rows(path, rows) -> None:
    """append whole lines (bytes, each ending in a newline) to a file, repairing a missing final newline first"""
    blob = b''.join(rows)
    update_bytes(path, lambda cur: cur + (b'' if not cur or cur.endswith(b'\n') else b'\n') + blob)


def remove_rows(path, rows) -> int:
    """remove exactly these lines (the LAST occurrence of each) and keep everything else, including lines other tools
    appended meanwhile: the undo of our own appends. Returns how many were removed."""
    removed = [0]
    def fn(cur):
        lines = cur.splitlines(keepends=True)
        for r in rows:
            for i in range(len(lines) - 1, -1, -1):
                if lines[i] == r:
                    del lines[i]; removed[0] += 1; break
        return b''.join(lines)
    update_bytes(path, fn)
    return removed[0]
