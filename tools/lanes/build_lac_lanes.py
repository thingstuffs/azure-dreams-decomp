#!/usr/bin/env python3
"""Build codex packs of label-as-call rows (pseudo-calls to a `noreturn` symbol that is really an intra-function
jump), for the honest goto/return rewrite that round 25 landed on 104 rows.

    python3 tools/lanes/build_lac_lanes.py --pool ROWS.txt [--per 12] [--model sol|astra|luna] [--no-verify] LANE...

ROWS.txt lists row ids (first whitespace-separated field per line). Each row needs a rowbase record
(config/overlays/<family>.rowbase.jsonl: solved or proven) so the pack can name the true base and the offset of
every pseudo-callee inside the row; rows without one are skipped and listed. Each lane gets base/ (current src
text + .base_sha), out/, rows.md (per row: cell, true base, delta, every pseudo-call site with its in-row
offset and thread-fill flag, pin sites), BRIEF.md (tools/lanes/lac_lane_brief.md) and PROMPT.txt; launch with
tools/lanes/launch_lane.sh <lane> sol|astra.
"""
import argparse
import hashlib
import json
import re
import struct
import sys
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "build_ovl/tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import rows, clean_path
from pin_census import sites_of
from verify import verify
from served import served_rows, assert_unserved
import rowbase

R = {r["id"]: r for r in rows()}
NR_DECL = re.compile(r"\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*__attribute__\s*\(\s*\(\s*noreturn")
NR_DECL2 = re.compile(r"__attribute__\s*\(\s*\(\s*noreturn\s*\)\s*\)\s*(?:void\s+)?(func_[0-9A-F]{8})")
CALL = re.compile(r"\b(func_[0-9A-F]{8})\s*\(")
CONTAINERS = {"dungeon": "DUNGEON_DUNGEON.BIN", "town": "TOWN_TOWN.BIN", "main": "MAIN_MAIN.BIN"}


def region_of(fam, foff):
    for g in rowbase._records(fam):
        if g["start"] <= foff < g["end"]:
            return g
    return None


def retail_words(fam, foff, size):
    p = next(q for q in (ROOT / "work/disc/containers" / CONTAINERS[fam], ROOT / "build_ovl/work/s3_splat/extract" / CONTAINERS[fam],
                         ROOT / "work/s3_splat/extract" / CONTAINERS[fam]) if q.exists())
    with open(p, "rb") as f:
        f.seek(foff)
        b = f.read(size)
    return list(struct.unpack("<%dI" % (len(b) // 4), b[: len(b) // 4 * 4]))


def sites(rid, text):
    r = R[rid]
    if r.get("size") is None or r.get("foff") is None:
        return None
    fam, foff, size = r["container"], int(r["foff"]), int(r["size"])
    g = region_of(fam, foff)
    if g is None:
        return None
    base = foff + g["delta"]
    words = retail_words(fam, foff, size)
    decl = set(NR_DECL.findall(text)) | set(NR_DECL2.findall(text))
    out = []
    for m in CALL.finditer(text):
        name = m.group(1)
        if name not in decl:
            continue
        addr = int(name[5:], 16)
        off = addr - base
        line = text.count("\n", 0, m.start()) + 1
        kind = "inside" if 0 <= off < size else "OUTSIDE the row"
        fill = ""
        if 0 < off < size and off % 4 == 0:
            i = off // 4
            # thread fill: the word before the callee equals some j's delay word (the j itself targets addr)
            js = [k for k, w in enumerate(words) if (w >> 26) == 2 and (0x80000000 | ((w & 0x3FFFFFF) << 2)) == addr]
            if js and any(k + 1 < len(words) and words[k + 1] == words[i - 1] for k in js):
                fill = " THREAD FILL: source label at offset 0x%X" % (off - 4)
        out.append("- line %d: `%s(...)` -> offset **0x%X** (%s)%s" % (line, name, off, kind, fill))
    return dict(base=base, delta=g["delta"], region=g["rec"]["region"], conf=g["rec"].get("base_confidence"), calls=out)


def render(rid, text, info):
    r = R[rid]
    s = sites_of(text)
    fam_counts = {}
    for x in s:
        fam_counts[x[1]] = fam_counts.get(x[1], 0) + 1
    lines = ["## %s" % rid,
             "- cell `%s`, %d B retail, `src/%s.c`, true base 0x%08X (delta 0x%X, region `%s`, %s)"
             % (r["cfg"], int(r["size"]), rid, info["base"], info["delta"], info["region"], info["conf"]),
             "- pin sites: %d (%s)" % (len(s), ", ".join("%s %d" % kv for kv in sorted(fam_counts.items()))),
             "- pseudo-calls (%d):" % len(info["calls"])] + info["calls"]
    return "\n".join(lines) + "\n"


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("lanes", nargs="+")
    ap.add_argument("--pool", required=True)
    ap.add_argument("--per", type=int, default=12)
    ap.add_argument("--model", default="sol")
    ap.add_argument("--no-verify", action="store_true")
    ap.add_argument("--repack", action="store_true", help="admit rows already served by a lane (retry packs)")
    ap.add_argument("--dry-run", action="store_true", help="print the pack composition and the stats; write nothing")
    a = ap.parse_args()
    ids = [l.split()[0] for l in open(a.pool) if l.strip() and not l.startswith("#")]
    packed = set()
    for f in (ROOT / "work/native_lane").glob("lac*/base/*/*.c"):
        packed.add(f.parent.name + "/" + f.stem)
    served = served_rows()
    nserved = 0
    pool, skipped = [], []
    for rid in ids:
        if (rid in packed and not a.repack) or rid not in R or not clean_path(R[rid]).exists():
            skipped.append((rid, "packed or unknown")); continue
        if rid in served:
            nserved += 1
            if not a.repack:
                skipped.append((rid, "served by an earlier lane")); continue
        text = clean_path(R[rid]).read_text(errors="replace")
        info = sites(rid, text)
        if info is None:
            skipped.append((rid, "no rowbase record")); continue
        if not info["calls"]:
            skipped.append((rid, "no pseudo-call")); continue
        pool.append((rid, text, info))
    if not a.no_verify:
        with ThreadPoolExecutor(max_workers=3) as ex:
            ok = list(ex.map(lambda p: bool(verify(R[p[0]], clean_path(R[p[0]])).get("exact")), pool))
        bad = [p[0] for p, o in zip(pool, ok) if not o]
        pool = [p for p, o in zip(pool, ok) if o]
        if bad:
            print("base not exact, dropped:", bad)
    print("pool %d rows | skipped %d | served by an earlier lane: %d" % (len(pool), len(skipped), nserved))
    brief = (ROOT / "tools/lanes/lac_lane_brief.md").read_text()
    i = 0
    for name in a.lanes:
        chunk = pool[i:i + a.per]; i += a.per
        if not chunk:
            print(name, "no rows left"); continue
        assert_unserved([rid for rid, _, _ in chunk], a.repack)   # never re-serve a row by accident
        if a.dry_run:
            print(name, len(chunk), "rows (dry run, nothing written):",
                  ", ".join(rid for rid, _, _ in chunk))
            continue
        L = ROOT / "work/native_lane" / name
        assert not (L / "last_message.txt").exists(), name
        (L / "out").mkdir(parents=True, exist_ok=True)
        md = ["# Rows (label-as-call sites with their in-row offsets)\n"]
        for rid, text, info in chunk:
            md.append(render(rid, text, info))
            cont, nm = rid.split("/")
            (L / "base" / cont).mkdir(parents=True, exist_ok=True)
            (L / "base" / cont / (nm + ".c")).write_text(text)
            (L / "base" / cont / (nm + ".c.base_sha")).write_text(hashlib.sha256(text.encode()).hexdigest() + "\n")
        (L / "rows.md").write_text("\n".join(md))
        b = (brief.replace("@ROOT@", str(ROOT)).replace("@LANE@", name).replace("@NROWS@", str(len(chunk)))
             .replace("@HOME@", str(Path.home())).replace("@MODEL@", a.model))
        (L / "BRIEF.md").write_text(b)
        (L / "PROMPT.txt").write_text(
            f"FIRST RULE: run every compiler command as `cd work/native_lane/{name} && ...`; gcc -da writes its "
            f"dumps into the current directory, and lanes have left dozens of dump files at the repo root.\n"
            f"Read work/native_lane/{name}/BRIEF.md and follow it exactly. Work only inside work/native_lane/{name}/ "
            f"and never write files at the repo root. Never add ASM_* macros, __asm__, volatile, fake dependencies or "
            f"one-trip blocks. When done, end with one line per row: row, result, what each pseudo-call was, the "
            f"change in one sentence, pins before -> after, and what did not work.\n")
        print(name, len(chunk), "rows:", ", ".join(rid for rid, _, _ in chunk))
    for s in skipped:
        print("skipped", s)


if __name__ == "__main__":
    main()
