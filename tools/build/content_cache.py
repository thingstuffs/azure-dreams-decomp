"""Content-bound reuse for generated build views and accounting, never proof verdicts."""
import hashlib
import json
import os
from pathlib import Path


def inventory(root, directories, exclude=()):
    """Enumerate only explicitly named input trees; never traverse build/work caches."""
    names = set()
    prefix = os.path.abspath(root) + os.sep
    for directory in directories:
        for parent, dirs, files in os.walk(prefix + directory):
            dirs[:] = sorted(d for d in dirs if d not in {'__pycache__', '.git', 'cache'})
            for name in files:
                relative = os.path.join(parent, name)[len(prefix):]
                if relative not in exclude and not name.endswith(('.pyc', '.tmp')):
                    names.add(relative)
    return names


def hashes(root, names):
    result = {}
    root = os.fspath(root)
    for name in sorted(names):
        if os.path.isabs(name) or '..' in name.split('/'):
            raise ValueError('unsafe cache input: ' + name)
        try:
            with open(os.path.join(root, name), 'rb') as stream:
                result[name] = hashlib.file_digest(stream, 'sha256').hexdigest()
        except FileNotFoundError:
            result[name] = None
    return result


class Snapshot:
    """Hash bytes on first read in this invocation; re-read any changed identity.

    This never trusts a stamp from another process/run. ctime and inode bind
    same-mtime writes and atomic replacements, as in mkbuild.hash_inputs.
    """
    def __init__(self, root):
        self.root = os.fspath(root)
        self.values = {}

    @staticmethod
    def identity(path):
        try:
            s = os.stat(path)
            return s.st_dev, s.st_ino, s.st_size, s.st_mtime_ns, s.st_ctime_ns
        except FileNotFoundError:
            return None

    def hashes(self, names):
        result = {}
        for name in sorted(names):
            if os.path.isabs(name) or '..' in name.split('/'):
                raise ValueError('unsafe cache input: ' + name)
            path = os.path.join(self.root, name)
            stamp = self.identity(path)
            old = self.values.get(name)
            if old is not None and old[0] == stamp:
                result[name] = old[1]
                continue
            try:
                with open(path, 'rb') as stream:
                    digest = hashlib.file_digest(stream, 'sha256').hexdigest()
            except FileNotFoundError:
                digest = None
            if stamp != self.identity(path):
                raise ValueError('input changed while hashing: ' + name)
            self.values[name] = stamp, digest
            result[name] = digest
        return result


def links(root, directories, prune=()):
    """Bind managed symlink destinations, including directory links we do not walk."""
    result = {}
    prefix = os.path.abspath(root) + os.sep
    for directory in directories:
        start = prefix + directory
        for parent, dirs, files in os.walk(start):
            dirs[:] = sorted(d for d in dirs if d not in {'__pycache__', '.git', 'cache', *prune})
            for name in dirs + files:
                path = os.path.join(parent, name)
                if os.path.islink(path):
                    result[path[len(prefix):]] = os.readlink(path)
        if os.path.islink(start):
            result[directory] = os.readlink(start)
    return result


def load(path):
    try:
        return json.loads(path.read_text())
    except (FileNotFoundError, ValueError):
        return {}


def save(path, value):
    blob = json.dumps(value, sort_keys=True, indent=1) + '\n'
    if path.exists() and path.read_text() == blob:
        return
    path.parent.mkdir(parents=True, exist_ok=True)
    temporary = path.with_name(path.name + '.tmp')
    temporary.write_text(blob)
    temporary.replace(path)
