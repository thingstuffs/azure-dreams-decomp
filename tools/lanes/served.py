#!/usr/bin/env python3
"""Which rows a lane has already served, and the guard every pack builder calls before it writes.

    python3 tools/lanes/served.py                       # every served row: `row  lane1,lane2`
    python3 tools/lanes/served.py dungeon/func_80089F8C # just these ids
    python3 tools/lanes/served.py --count               # served rows and their live pin sites

A row that has been in any lane's pack has a copy of its text under
`work/native_lane/<lane>/base/<container>/<name>.c`; that glob is the record of what has been
served (round 25: one builder bug sent six packs of already-served rows to sol). Retries have paid
about 3% - a row that resists one pack resists the next - so a new pack must contain NO served row
unless the caller deliberately asks for a retry pack with `--repack`.
"""
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]

_CACHE = {}


def served_rows(root=ROOT):
    """{row id: sorted lane names} from `work/native_lane/*/base/*/*.c`; one pass, cached per root."""
    key = str(Path(root).resolve())
    if key not in _CACHE:
        out = {}
        for f in Path(root).glob("work/native_lane/*/base/*/*.c"):
            rid = f.parent.name + "/" + f.stem
            out.setdefault(rid, set()).add(f.parent.parent.parent.name)
        _CACHE[key] = {rid: sorted(lanes) for rid, lanes in out.items()}
    return _CACHE[key]


def assert_unserved(row_ids, repack=False, root=ROOT):
    """The overlap between `row_ids` and the served rows, as [(row id, lanes)] in the caller's order.
    Unless `repack`, a non-empty overlap is fatal: no pack may re-serve a row by accident."""
    served = served_rows(root)
    seen, overlap = set(), []
    for rid in row_ids:
        if rid in seen:
            continue
        seen.add(rid)
        if rid in served:
            overlap.append((rid, served[rid]))
    if overlap and not repack:
        msg = ["%d row(s) in this pack have already been served by a lane:" % len(overlap)]
        msg += ["  %s  %s" % (rid, ",".join(lanes)) for rid, lanes in overlap]
        msg.append("pass --repack to build a deliberate retry pack (retries have paid about 3%).")
        raise SystemExit("\n".join(msg))
    return overlap


def main():
    args = [a for a in sys.argv[1:] if a != "--count"]
    count = "--count" in sys.argv[1:]
    served = served_rows()
    if count:
        sys.path.insert(0, str(ROOT / "tools"))
        from common import rows, clean_path
        from pin_census import sites_of
        R = {r["id"]: r for r in rows()}
        npins = 0
        for rid in served:
            r = R.get(rid)
            if not r or not clean_path(r).exists():
                continue
            npins += len(sites_of(clean_path(r).read_text(errors="replace")))
        print("%d served rows, %d live pin sites" % (len(served), npins))
        return
    for rid in (args or sorted(served)):
        print("%s  %s" % (rid, ",".join(served.get(rid, []))))


if __name__ == "__main__":
    main()
