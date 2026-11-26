"""Digest policy for evidence derived from disc extents."""
import hashlib
import re


def extent_digest(data):
    return hashlib.sha256(data).hexdigest() if len(data) >= 16 else '-'


def valid_digest(size, value):
    return value == '-' if size < 16 else bool(re.fullmatch('[0-9a-f]{64}', value))
