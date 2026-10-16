"""Bounded process-local file cache; changes and replacements invalidate entries.

No verdicts are cached. The caller still runs every validation. Parsed values
are copied so caller mutation never alters future reads. Only the newest
identity is retained for a path, including ctime to catch restored mtime edits.
"""
from collections import OrderedDict
from contextlib import contextmanager
import os
import pickle
import hashlib
import json
import sys
from pathlib import Path
from threading import RLock, local

_LOCK = RLock()
_CACHE = OrderedDict()
_LIMIT = 16384

# --- input observation (used by overlay_scoped_fingerprint.memo) --------------------------------
# While observing() is active on a thread, every input identity the computation probes is recorded
# once, at FIRST probe, as {absolute path: stamp} (None = absent), into every active observer:
#  * all reads through this module (cache hits included), and explicit observe() probes;
#  * the parent directory of each observed path, so creating or removing a sibling (an optional
#    input another module only tested with exists()) changes a recorded identity;
#  * reads/listings that bypass this module (plain open(), os.scandir/os.listdir from glob,
#    rglob, iterdir, os.walk) through an audit hook. CPython cannot remove an audit hook; it is
#    installed on the first observing() call and returns after one thread-local lookup when no
#    observer is active.
_OBS = local()
_HOOKED = False

def stamp_of(path):
    try:
        st = os.stat(path)
    except (FileNotFoundError, NotADirectoryError):
        return None
    return (st.st_dev, st.st_ino, st.st_mtime_ns, st.st_ctime_ns, st.st_size)

def observe(path, stamp=False):
    stack = getattr(_OBS, "stack", None)
    if not stack:
        return
    path = os.path.abspath(os.fsdecode(path))
    if path in stack[-1]:
        return
    value = stamp_of(path) if stamp is False else stamp
    for seen in stack:
        seen.setdefault(path, value)
    parent = os.path.dirname(path)
    if parent != path and parent not in stack[-1]:
        value = stamp_of(parent)
        for seen in stack:
            seen.setdefault(parent, value)

VOLATILE = "\0volatile"

def volatile():
    """The running computation read something identities cannot describe (e.g. a -M scan over a
    custom include search path): no enclosing memo may store it."""
    for seen in getattr(_OBS, "stack", None) or ():
        seen[VOLATILE] = None

def merge_observed(seen):
    """Re-record an earlier computation's identities (a memo hit) into the active observers."""
    for current in getattr(_OBS, "stack", None) or ():
        for path, value in seen.items():
            current.setdefault(path, value)

def _audit(event, args):
    if event != "open" and event != "os.scandir" and event != "os.listdir":
        return
    if not getattr(_OBS, "stack", None):
        return
    path = args[0] if args else None
    if isinstance(path, int):
        return
    observe("." if path is None else path)

@contextmanager
def observing(seed=None):
    """Collect the identities probed on this thread; seed with an enclosing computation's."""
    global _HOOKED
    if not _HOOKED:
        sys.addaudithook(_audit)
        _HOOKED = True
    stack = getattr(_OBS, "stack", None)
    if stack is None:
        stack = _OBS.stack = []
    seen = dict(seed or {})
    stack.append(seen)
    try:
        yield seen
    finally:
        stack.pop()
        for outer in stack:
            for path, value in seen.items():
                outer.setdefault(path, value)

def observers():
    return list(getattr(_OBS, "stack", None) or ())

def _read(path, kind, parse):
    with _LOCK:
        path = Path(path).absolute()
        st = path.stat()
        stamp = (st.st_dev, st.st_ino, st.st_mtime_ns, st.st_ctime_ns, st.st_size)
        observe(path, stamp)
        key = (path, kind)
        previous = _CACHE.get(key)
        if previous is None or previous[0] != stamp:
            value = parse(path)
            _CACHE[key] = (stamp, value)
            if len(_CACHE) > _LIMIT: _CACHE.popitem(last=False)
        else:
            value = previous[1]
        _CACHE.move_to_end(key)
        return value

def read_text(path):
    return _read(path, "text", lambda p: p.read_text())

# The serialized values contain only primitives from json.loads. They are
# produced here, never read from an external pickle file. The C decoder gives
# callers independent nested values without expensive Python deepcopy loops.
def read_json(path):
    return pickle.loads(_read(path, "json", lambda p: pickle.dumps(json.loads(p.read_text()), protocol=5)))

def read_jsonl(path):
    return pickle.loads(_read(path, "jsonl", lambda p: pickle.dumps(tuple(json.loads(l) for l in p.read_text().splitlines() if l.strip()), protocol=5)))

def digest(path, algorithm="sha256"):
    return _read(path, algorithm, lambda p: hashlib.new(algorithm, p.read_bytes()).hexdigest())


def read_records(path):
    """Comment-bearing JSONL, with the same identity/copy guarantees."""
    return pickle.loads(_read(path, "records", lambda p: pickle.dumps(
        tuple(json.loads(l) for l in p.read_text().splitlines()
              if l.strip() and not l.lstrip().startswith("#")), protocol=5)))
