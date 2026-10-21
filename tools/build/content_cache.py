"""Content-bound reuse for generated build views and accounting, never proof verdicts."""
import hashlib
import json
import os
from pathlib import Path


def inventory(root, directories, exclude=()):
    """Enumerate only explicitly named input trees; never traverse build/work caches."""
    names = set()
    for directory in directories:
        for parent, dirs, files in os.walk(root/directory):
            dirs[:] = sorted(d for d in dirs if d not in {'__pycache__', '.git', 'cache'})
            for name in files:
                relative = (Path(parent)/name).relative_to(root).as_posix()
                if relative not in exclude and not name.endswith(('.pyc', '.tmp')):
                    names.add(relative)
    return names


def hashes(root, names):
    result = {}
    for name in sorted(names):
        path = Path(name)
        if path.is_absolute() or '..' in path.parts:
            raise ValueError('unsafe cache input: ' + name)
        try:
            with (root/path).open('rb') as stream:
                result[name] = hashlib.file_digest(stream, 'sha256').hexdigest()
        except FileNotFoundError:
            result[name] = None
    return result


def links(root, directories, prune=()):
    """Bind managed symlink destinations, including directory links we do not walk."""
    result = {}
    for directory in directories:
        for parent, dirs, files in os.walk(root/directory):
            dirs[:] = sorted(d for d in dirs if d not in {'__pycache__', '.git', 'cache', *prune})
            for name in dirs + files:
                path = Path(parent)/name
                if path.is_symlink():
                    result[path.relative_to(root).as_posix()] = os.readlink(path)
        path = root/directory
        if path.is_symlink():
            result[directory] = os.readlink(path)
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
