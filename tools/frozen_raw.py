"""Small, immutable facts derived from the retired raw C archive."""
from __future__ import annotations

import json
from functools import lru_cache
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
TABLE = "config/frozen_raw.jsonl"


@lru_cache(maxsize=16)
def records(root: Path = ROOT) -> dict[str, dict]:
    path = Path(root) / TABLE
    return {r["path"]: r for r in
            (json.loads(line) for line in path.read_text().splitlines() if line)}


def entry(relative: str | Path, root: Path = ROOT) -> dict | None:
    return records(Path(root)).get(str(relative))


def sha(relative: str | Path, root: Path = ROOT) -> str | None:
    rec = entry(relative, root)
    return rec["sha256"] if rec else None


def names(relative: str | Path, root: Path = ROOT) -> set[str]:
    rec = entry(relative, root)
    return set(rec.get("noreturn", ())) if rec else set()
