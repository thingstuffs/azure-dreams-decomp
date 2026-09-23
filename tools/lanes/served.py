#!/usr/bin/env python3
"""Which rows a lane has already served, and the guard every pack builder calls before it writes.

    python3 tools/lanes/served.py                       # every served row: `row  lane1,lane2`
    python3 tools/lanes/served.py dungeon/func_80089F8C # just these ids
    python3 tools/lanes/served.py --count               # served rows and their live pin sites
    python3 tools/lanes/served.py --strong-kit [--count] [--band 8-] [--json]
                                  # pinned rows NO kit-era strong lane (astra/opus, lane r68_* on) has served
                                  # at their CURRENT text; `older-text` marks rows served only at an older text

A row that has been in any lane's pack has a copy of its text under
`work/native_lane/<lane>/base/<container>/<name>.c`; that glob is the record of what has been
served (round 25: one builder bug sent six packs of already-served rows to sol).

Two notions of "served" (round 76, 2026-09-23):

  ever  (the round-26 doctrine, `served_rows()`, `assert_unserved(mode="ever")`): any lane, any model,
        any text, launched or not.  It was written when retries paid about 3% (rounds 25-60, pre-kit
        luna/sol packs: a row that resisted one pack resisted the next).
  tier  (`serve_records()`, `assert_unserved(mode="tier", tier=...)`): a serve is keyed on
        (model tier, kit era, row text sha256, scope).  The guard refuses a row only when a LAUNCHED lane
        of the SAME tier already served it at the SAME text (and the same scope: whole function, or the
        same pin cluster of a cluster pack, `cluster.json`).  A different model, a newer kit or a text
        that changed since (a partial landing, a generator sweep) is a new experiment, not a repeat.

Why the doctrine changed: the r73-r75 wave was ALL retries of older lanes, served with the round-68 kit
(duck brief v2 + lanekit), and paid (`python3 tools/lanes/ab_report.py --glob 'r7[345]_*' --ok-only`,
2026-09-23): claude-opus-5-5 132/215 rows exact (61.4%, 251 pins), gpt-6-astra 70/97 (72.2%, 154 pins),
gpt-6-sol 20/106 (18.9%), gpt-6-luna 10/70 (14.3%).  "Retries pay ~3%" was a statement about pre-kit
same-tier retries, which the tier guard still refuses.

Tier = `ledger.tier_of_model` on the lane's model (usage.json, then the codex.log header, then a tier
token in the lane name: `r73_opus_s11_arms` -> opus).  Kit era = lane name `r<N>_...` with N >= 68.
Launched = the lane has codex.log, agy.log, last_message.txt, lane.pid or usage.json, no limit_cut.txt,
AND (round 76) its own agy.log/codex.log carries no provider quota/capacity error (`lane_limit.py`,
read directly -- not just when a launcher script happened to mark limit_cut.txt); a built pack that
never ran, died on a usage limit, or was cut off by a quota/capacity error served no model (it still
counts under `ever`).
"""
import hashlib
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(Path(__file__).resolve().parent))
import lane_limit

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


KIT_ERA = 68                      # lane names r68_* on carry the lane kit (duck brief v2, lanekit)
STRONG = ("astra", "opus")        # the tiers that paid 61-72% on kit retries (r73-r75)
LAUNCH_MARKS = ("codex.log", "agy.log", "last_message.txt", "lane.pid", "usage.json")
_ROUND_RE = re.compile(r"^r(\d+)[a-z]*_")   # r76_..., and r76o_/r76g_ (overlap, Gemini feed)
_TIER_TOKENS = ("opus", "sonnet", "astra", "sol6", "luna6", "sol", "luna", "agy")
_RECS = {}


def lane_round(name):
    m = _ROUND_RE.match(name)
    return int(m.group(1)) if m else None


def lane_model(d):
    """The model id a lane ran on: usage.json `model`, else the codex.log header, else None."""
    d = Path(d)
    try:
        m = json.loads((d / "usage.json").read_text()).get("model")
        if m:
            return m
    except (OSError, ValueError):
        pass
    try:
        with (d / "codex.log").open("rb") as fh:
            head = fh.read(8192).decode("utf-8", "replace")
    except OSError:
        return None
    for line in head.splitlines()[:40]:
        line = re.sub(r"\x1b\[[0-9;]*m", "", line).strip()
        if line.startswith("model:"):
            return line.split(":", 1)[1].strip() or None
        if line == "user":
            break
    return None


def lane_tier(d):
    """(tier, model) of a lane directory; the tier falls back to a token in the lane name."""
    from ledger import tier_of_model
    d = Path(d)
    model = lane_model(d)
    tier = tier_of_model(model)
    if tier is None and (d / "agy.log").exists():
        tier = "agy"
    if tier is None:
        toks = d.name.lower().split("_")
        tier = next((t for t in _TIER_TOKENS if any(x.startswith(t) for x in toks)), None)
    return tier, model


def cluster_scope(sites):
    """The scope key of a cluster serve: its pin sites as `line:MACRO(arg)` sorted, joined by `;`."""
    return "cluster:" + ";".join(sorted("%s:%s(%s)" % (s[0], s[1], s[2]) for s in sites))


def lane_scopes(d):
    """{row: scope key} for a built lane directory (its cluster.json); rows absent are 'whole'."""
    try:
        return {rid: cluster_scope(c["sites"]) for rid, c in json.loads((Path(d) / "cluster.json").read_text()).items()}
    except (OSError, ValueError, KeyError, TypeError):
        return {}


def serve_records(root=ROOT):
    """[{row, lane, round, tier, model, sha, scope, launched}] - one per base copy; cached per root.
    sha = sha256 of the served text (the base copy, as `.base_sha` records it); scope = 'whole', or the
    cluster key from the lane's cluster.json ({row: {"sites": [[line, macro, arg], ...]}})."""
    key = str(Path(root).resolve())
    if key in _RECS:
        return _RECS[key]
    out = []
    base = Path(root) / "work/native_lane"
    lanes = sorted({f.parent.parent.parent for f in base.glob("*/base/*/*.c")})
    for d in lanes:
        tier, model = lane_tier(d)
        # limit_cut.txt: a launcher script marked the lane cut on its model's usage limit (gemini_feed.sh);
        # lane_hit_limit: read the lane's own logs directly for the same condition, so a lane a launcher
        # missed (round 76: mark_limit_cut skips any lane with an out/ file) is still excluded.
        launched = (any((d / m).exists() for m in LAUNCH_MARKS) and not (d / "limit_cut.txt").exists()
                    and not lane_limit.lane_hit_limit(d))
        clusters = {}
        try:
            clusters = json.loads((d / "cluster.json").read_text())
        except (OSError, ValueError):
            pass
        for f in sorted(d.glob("base/*/*.c")):
            rid = f.parent.name + "/" + f.stem
            c = clusters.get(rid)
            out.append({"row": rid, "lane": d.name, "round": lane_round(d.name), "tier": tier, "model": model,
                        "sha": hashlib.sha256(f.read_bytes()).hexdigest(),
                        "scope": cluster_scope(c["sites"]) if c else "whole", "launched": launched})
    _RECS[key] = out
    return out


def strong_kit_serves(root=ROOT, strong=STRONG, era=KIT_ERA):
    """{row: [record]} of launched kit-era lanes on a strong tier."""
    out = {}
    for r in serve_records(root):
        if r["launched"] and r["tier"] in strong and (r["round"] or 0) >= era:
            out.setdefault(r["row"], []).append(r)
    return out


def current_texts(root=ROOT):
    """{row id: (sha256 of the current clean text, live pin sites)} for every row with a clean file."""
    sys.path.insert(0, str(Path(root) / "tools"))
    from common import rows, clean_path
    from pin_census import sites_of
    out = {}
    for r in rows():
        p = clean_path(r)
        if not p.exists():
            continue
        t = p.read_text(errors="replace")
        out[r["id"]] = (hashlib.sha256(t.encode()).hexdigest(), len(sites_of(t)), r["container"])
    return out


def tier_overlap(row_ids, tier, texts, root=ROOT, scopes=None, skip_lane=None):
    """[(row, lanes)] of rows a launched lane of `tier` served at the row's current text and scope.
    texts: {row: sha} (or {row: (sha, ...)}); scopes: {row: scope key} for a cluster pack (default 'whole')."""
    by = {}
    for r in serve_records(root):
        if r["launched"] and r["tier"] == tier and r["lane"] != skip_lane:
            by.setdefault(r["row"], []).append(r)
    seen, overlap = set(), []
    for rid in row_ids:
        if rid in seen:
            continue
        seen.add(rid)
        cur = texts.get(rid)
        cur = cur[0] if isinstance(cur, tuple) else cur
        scope = (scopes or {}).get(rid, "whole")
        hit = sorted({r["lane"] for r in by.get(rid, []) if r["sha"] == cur and r["scope"] == scope})
        if hit:
            overlap.append((rid, hit))
    return overlap


def assert_unserved(row_ids, repack=False, root=ROOT, mode="ever", tier=None, texts=None, scopes=None,
                    skip_lane=None):
    """The overlap between `row_ids` and the served rows, as [(row id, lanes)] in the caller's order.
    Unless `repack`, a non-empty overlap is fatal: no pack may re-serve a row by accident.
    mode 'ever' (default, round 26): any lane ever.  mode 'tier': only a launched lane of the SAME tier
    at the SAME text and scope (round 76); needs `tier`, `texts` defaults to the tree's clean texts.
    mode 'off': no guard."""
    if mode == "off":
        return []
    if mode == "tier":
        if not tier:
            raise SystemExit("served guard 'tier' needs the model tier (astra|opus|sonnet|sol6|luna6|sol|luna)")
        overlap = tier_overlap(row_ids, tier, texts if texts is not None else current_texts(root), root,
                               scopes, skip_lane)
        if overlap and not repack:
            msg = ["%d row(s) in this pack were already served by a %s lane at the same text:" % (len(overlap), tier)]
            msg += ["  %s  %s" % (rid, ",".join(lanes)) for rid, lanes in overlap]
            msg.append("a same-tier same-text retry is a repeat experiment; pass --repack to build it anyway.")
            raise SystemExit("\n".join(msg))
        return overlap
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
        msg.append("pass --repack to build a deliberate retry pack (or --served-guard tier: same tier + text only).")
        raise SystemExit("\n".join(msg))
    return overlap


def band_of(pins, edges=(2, 7)):
    """The pin band label of a row: 1-2, 3-7, 8+ by default (the r76 A/B bands)."""
    lo = 1
    for e in edges:
        if pins <= e:
            return "%d-%d" % (lo, e)
        lo = e + 1
    return "%d+" % lo


def strong_kit_pool(root=ROOT, texts=None, strong=STRONG, era=KIT_ERA):
    """[{row, pins, band, status, lanes}] for every pinned row (ovmovie parked) with no kit-era strong serve
    at its current text; status 'never' or 'older-text' (served only at a text that has changed since)."""
    texts = texts if texts is not None else current_texts(root)
    sk = strong_kit_serves(root, strong, era)
    out = []
    for rid, (sha, pins, container) in sorted(texts.items()):
        if pins == 0 or container == "ovmovie":
            continue
        recs = sk.get(rid, [])
        if any(r["sha"] == sha for r in recs):
            continue
        out.append({"row": rid, "pins": pins, "band": band_of(pins),
                    "status": "older-text" if recs else "never", "lanes": sorted({r["lane"] for r in recs})})
    return out


def _band_ok(pins, spec):
    if not spec:
        return True
    lo, _, hi = spec.partition("-")
    return pins >= int(lo or 0) and (not hi or pins <= int(hi))


def main():
    argv = sys.argv[1:]
    count = "--count" in argv
    band = argv[argv.index("--band") + 1] if "--band" in argv else None
    args = [a for i, a in enumerate(argv) if not a.startswith("--") and not (i and argv[i - 1] == "--band")]
    if "--strong-kit" in argv:
        pool = [p for p in strong_kit_pool() if _band_ok(p["pins"], band)]
        if "--json" in argv:
            print(json.dumps(pool, indent=0))
            return
        if count:
            by = {}
            for p in pool:
                b = by.setdefault(p["band"], [0, 0, 0, 0])
                b[0] += 1
                b[1] += p["pins"]
                if p["status"] == "never":
                    b[2] += 1
                    b[3] += p["pins"]
            for b, (n, k, nn, nk) in sorted(by.items(), key=lambda kv: int(kv[0].split("-")[0].rstrip("+"))):
                print("band %-5s %4d rows %5d pins  (never strong-kit served: %d rows %d pins)" % (b, n, k, nn, nk))
            print("total      %4d rows %5d pins  (never: %d rows %d pins)" % (
                len(pool), sum(p["pins"] for p in pool), sum(p["status"] == "never" for p in pool),
                sum(p["pins"] for p in pool if p["status"] == "never")))
            return
        for p in pool:
            print("%s  %d  %s  %s" % (p["row"], p["pins"], p["status"], ",".join(p["lanes"])))
        return
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
