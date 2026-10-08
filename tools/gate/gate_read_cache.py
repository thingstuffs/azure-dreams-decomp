"""Bounded process-local file cache; changes and replacements invalidate entries.

No verdicts are cached. The caller still runs every validation. Parsed values
are copied so caller mutation never alters future reads. Only the newest
identity is retained for a path, including ctime to catch restored mtime edits.
"""
from collections import OrderedDict
import pickle
import hashlib
import json
from pathlib import Path
from threading import RLock

_LOCK = RLock()
_CACHE = OrderedDict()
_LIMIT = 16384

def _read(path, kind, parse):
    with _LOCK:
        path = Path(path).absolute()
        st = path.stat()
        stamp = (st.st_dev, st.st_ino, st.st_mtime_ns, st.st_ctime_ns, st.st_size)
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
