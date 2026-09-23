#!/usr/bin/env python3
"""The lane ledger: every model lane with what it was served, what it made exact, what landed, and its rate.

    python3 tools/lanes/ledger.py build       # (re)write ledger/lanes.jsonl (incremental)
    python3 tools/lanes/ledger.py build --force   # rescan every lane, ignoring the cache
    python3 tools/lanes/ledger.py             # one markdown line per lane, newest first
    python3 tools/lanes/ledger.py --by stratum|tier|family|model|tier,stratum   # aggregate, best rate first
    python3 tools/lanes/ledger.py --closed 0.2   # (family, stratum) groups under that rate over >= 20
                                                 # served rows: CLOSED, do not build another pack there

Until round 26 the rate tables in `docs/HANDOVER.md` were written by hand. This reads them off the disk.

What it reads, per lane directory `work/native_lane/<lane>/`:
  `base/<container>/<name>.c`   the rows the lane was SERVED (`served.served_rows()` is the one glob;
                                a lane with no `base/` served an unrecorded list: served is unknown, not 0)
  `out/<container>/<name>.c`    its EXACT outputs (each with a `.base_sha`, the sha256 of its base)
  `candidates/...`              non-exact tries (counted, never scored)
  `codex.log`                   header line `model: gpt-5.6-sol` -> model, and the tier from its suffix
  `BRIEF.md`                    title line -> the family, and the tier in parentheses when there is no log
  `rows.md`                     per-row `stratum **allocN**` for the diagnosed register packs
and, for the landings: every `ledger/sweeps/lane_*.jsonl` journal (`"outcome":"applied"`), plus
`ledger/rows.jsonl` and the row's file under `src/` - the tree text today.

Definitions, because the columns are easy to misread:
  served  rows in `base/`;  exact  files in `out/`.
  landed  a row this lane's own exact output is responsible for, by either of two witnesses:
          (a) its journal `ledger/sweeps/lane_<lane>.jsonl` says `"outcome":"applied"`, or
          (b) `out/<rid>.c` is byte-identical to the row's text in the tree today and differs from the
              base it was made from - the lane's output IS what is in the tree, whatever path put it
              there (a generator, a hand landing, a sweep with no lane journal: 19 lanes, 221 outputs
              had no journal at all, and 71 of those outputs are the tree text). (b) is credited only
              for ids that no lane journal claims, so a row is never counted twice; it decays as later
              rounds edit the file further, which is why the journal stays the primary witness.
  rate    landed / served - what the pack actually paid, which is what `--closed` decides on.
  pins -  pins the lane's OWN output removed at its own base: `sites_of(base) - sites_of(out)` summed over
          the landed rows. The cascade that follows a landing is NOT in it, so this runs below the pin
          counts quoted in HANDOVER (alloc66-71: 19 here, 28 with the cascade).

What it writes: `ledger/lanes.jsonl`, one record per lane:
  {lane, at, tier, model, family, stratum, served, served_known, exact, candidates, landed,
   landed_journal, landed_tree, refused, pins_removed, pins_unknown_rows, journal, rate, fp}
`fp` is a hash of the base/out/candidates listing (path + size), the journal size, the sizes of
BRIEF.md/rows.md/codex.log, the size+mtime of the tree file of every exact row, the applied ids any
journal claims among them, AND a hash of this file's own classification tables and code (with
`pin_census.py`, which counts the pins): a lane whose fp is unchanged is copied from the existing
file, unscanned. Because the code is in the fp, correcting FAMILY_WORDS or a parser rebuilds by
itself; `build --force` rescans regardless.
"""
import hashlib
import json
import re
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(ROOT / "tools" / "lanes"))
from pin_census import sites_of          # noqa: E402
import served as served_mod              # noqa: E402

LEDGER = "ledger/lanes.jsonl"
NOT_LANES = {"out", "scratchpad"}
SUBDIRS = ("base", "out", "candidates")
# sol6/luna6 (gpt-6-sol/-luna) before sol/luna: parse_title matches "(sol" as a prefix, so "(sol6)" must hit first.
TIERS = ("sol6", "luna6", "luna", "sol", "astra", "opus", "agy")
ANSI_RE = re.compile(r"\x1b\[[0-9;]*m")

# Title keywords in order; the first hit wins (label-as-call before keep: "lackeep" briefs say both).
FAMILY_WORDS = [
    ("label-as-call", "LAC"), ("computed-goto", "SWITCH"), ("switch", "SWITCH"),
    ("allocator", "REG"), ("register pin", "REG"), ("register a symbol", "SYMHI"),
    ("page-base", "PAGE"), ("page base", "PAGE"),
    ("fence", "FENCE"), ("barrier", "FENCE"), ("scheduling", "FENCE"), ("ordering oracle", "FENCE"),
    ("keep", "KEEP"),
    ("fake dependency", "FAKEDEP"), ("fake construct", "FAKEDEP"), ("byte-exact fake", "FAKEDEP"),
    ("argument move", "ARG"), ("argument constant", "ARG"),
    ("multidimensional", "GRID"), ("largest pinned rows", "BIGROW"), ("42 pins", "BIGROW"),
    ("many pins", "BIGROW"), ("statements that move", "CODEMOTION"), ("cross-jump", "CROSSJUMP"),
    ("one hard pin", "HARD"),
]
# Fallback for the lanes with no BRIEF.md, by lane-name prefix (longest prefix wins).
FAMILY_PREFIX = [
    ("alloc", "REG"), ("probe", "REG"), ("noknob", "REG"), ("regrename", "REG"), ("luirename", "SYMHI"),
    ("fences", "FENCE"), ("fx", "FENCE"), ("sched", "FENCE"),
    ("lackeep", "KEEP"), ("loadkeep", "KEEP"), ("keep", "KEEP"),
    ("lac", "LAC"), ("honest", "LAC"), ("sw", "SWITCH"), ("grid", "GRID"),
    ("fakedep", "FAKEDEP"), ("argmove", "ARG"), ("argconst", "ARG"),
    ("crossjump", "CROSSJUMP"), ("codemotion", "CODEMOTION"), ("bigrow", "BIGROW"),
    ("func_", "HARD"), ("angle", "HARD"), ("template", "HARD"),
]


# ---------------------------------------------------------------- parsing (unit-tested)

def parse_model(header):
    """`model: gpt-5.6-sol` out of a codex.log header (the first 40 lines are all it ever needs)."""
    for line in header.splitlines()[:40]:
        line = ANSI_RE.sub("", line).strip()     # codex >= 0.154 bolds the keys: "\x1b[1mmodel:\x1b[0m gpt-6-astra"
        if line.startswith("model:"):
            return line.split(":", 1)[1].strip() or None
        if line.startswith("user"):       # past the header block
            break
    return None


def tier_of_model(model):
    """The tier is the model's suffix: gpt-5.6-luna -> luna, gemini-3.8-flash-high -> None.
    The gpt-6 generation of sol/luna is its own tier (gpt-6-sol -> sol6), so an A/B against gpt-5.6-sol
    does not lump them; gpt-6-astra stays astra (there is no 5.6 astra)."""
    if not model:
        return None
    tail = model.rsplit("-", 1)[-1].lower()
    if tail in ("sol", "luna") and model.lower().startswith("gpt-6"):
        return tail + "6"
    return tail if tail in TIERS else None


def parse_title(title):
    """(tier or None, family) from a BRIEF.md title line."""
    low = (title or "").lower()
    tier = None
    for t in TIERS:
        if "(%s" % t in low or ", %s)" % t in low:
            tier = t
            break
    family = None
    for word, fam in FAMILY_WORDS:
        if word in low:
            family = fam
            break
    return tier, family


def parse_stratum(rows_md):
    """The `stratum **allocN**` marker of a diagnosed register pack; '+'-joined if a pack ever mixes."""
    out, seen = [], set()
    for chunk in (rows_md or "").split("stratum **")[1:]:
        name = chunk.split("**", 1)[0].strip()
        if name and name not in seen:
            seen.add(name)
            out.append(name)
    return "+".join(sorted(out)) or None


def parse_journal(text):
    """(distinct applied row ids in order, refused count) from a lane journal's jsonl."""
    applied, seen, refused = [], set(), 0
    for line in (text or "").splitlines():
        line = line.strip()
        if not line:
            continue
        try:
            rec = json.loads(line)
        except ValueError:
            continue
        outcome = rec.get("outcome")
        if outcome == "applied":
            rid = rec.get("id")
            if rid and rid not in seen:
                seen.add(rid)
                applied.append(rid)
        elif outcome:
            refused += 1
    return applied, refused


def fingerprint(entries):
    """Stable hash of [(name, size)] pairs: the lane's listing plus the sizes that feed the record."""
    h = hashlib.sha256()
    for name, size in sorted(entries):
        h.update(("%s\t%s\n" % (name, size)).encode())
    return h.hexdigest()[:16]


def code_fingerprint():
    """Hash of what in the TOOL decides a record: the classification tables (read live, so a corrected
    table invalidates the cache even when it was patched in memory) and the two source files. Without
    this in the lane fp, a code fix would never reach an existing ledger/lanes.jsonl."""
    h = hashlib.sha256()
    h.update(repr((FAMILY_WORDS, FAMILY_PREFIX, TIERS, SUBDIRS)).encode())
    for p in (Path(__file__).resolve(), ROOT / "tools" / "pin_census.py"):
        try:
            h.update(p.read_bytes())
        except OSError:
            h.update(b"?")
    return h.hexdigest()[:16]


# ---------------------------------------------------------------- scanning

def is_evaluator_dir(d):
    """A `lane_eval.py` working directory (evidence/ and out/, but no brief, prompt or model log) is not a model
    lane: t63_dev/t63_fence (round 27) and noknob (round 26) hold generator measurements, not served rows."""
    return (d / "evidence").is_dir() and not any((d / n).exists() for n in ("BRIEF.md", "PROMPT.txt", "codex.log", "agy.log"))


def lane_dirs(root):
    base = Path(root) / "work" / "native_lane"
    if not base.is_dir():
        return []
    return sorted((d for d in base.iterdir() if d.is_dir() and d.name not in NOT_LANES and not is_evaluator_dir(d)),
                  key=lambda d: d.name)


def _size(path):
    try:
        return path.stat().st_size
    except OSError:
        return -1


_ROW_PATHS = {}


def tree_path(root, row):
    """The row's file in the tree. Mirrors tools.common.clean_path, but rooted, so a test can point the
    whole tool at a tempdir (common.clean_path is nailed to the real repository)."""
    return Path(root) / "src" / row["container"] / Path(row["c_path"]).name


def row_paths(root):
    """{row id: tree path} from ledger/rows.jsonl; cached per root, missing db -> no tree witnesses."""
    key = str(Path(root).resolve())
    if key not in _ROW_PATHS:
        db = Path(root) / "ledger" / "rows.jsonl"
        out = {}
        for line in (db.read_text(errors="replace").splitlines() if db.exists() else []):
            if line.strip():
                rec = json.loads(line)
                out[rec["id"]] = tree_path(root, rec)
        _ROW_PATHS[key] = out
    return _ROW_PATHS[key]


def applied_anywhere(root):
    """Every id any lane journal reports applied: an id with a journal witness is never tree-credited."""
    out = set()
    for j in sorted((Path(root) / "ledger" / "sweeps").glob("lane_*.jsonl")):
        applied, _ = parse_journal(j.read_text(errors="replace"))
        out.update(applied)
    return out


def out_changed_the_base(lane, rid, data):
    """Did this exact output differ from the base it was made from? `.base_sha` (the sha256 of the base)
    answers it even for lanes that kept no base/ copy; with neither witness there is no answer (None),
    and an output that changed nothing is no evidence that anything landed."""
    sha = lane / "out" / (rid + ".c.base_sha")
    if sha.exists():
        return sha.read_text(errors="replace").strip() != hashlib.sha256(data).hexdigest()
    base = lane / "base" / (rid + ".c")
    return base.read_bytes() != data if base.exists() else None


def tree_landed(lane, root, skip=()):
    """Rows whose exact output is byte-identical to the tree text today and changed its base: the lane's
    output is what is in the tree. `skip` holds the ids a journal already claims."""
    paths, out = row_paths(root), []
    for f in sorted((lane / "out").glob("*/*.c")):
        rid = f.parent.name + "/" + f.stem
        p = paths.get(rid)
        if rid in skip or p is None or not p.exists():
            continue
        data = f.read_bytes()
        if p.read_bytes() == data and out_changed_the_base(lane, rid, data):
            out.append(rid)
    return out


def lane_fingerprint(lane, journal, root, claimed=frozenset(), code=None):
    entries = []
    for sub in SUBDIRS:
        for f in sorted((lane / sub).glob("*/*.c")):
            entries.append((sub + "/" + f.parent.name + "/" + f.name, _size(f)))
    entries.append(("@journal", _size(journal)))
    for name in ("BRIEF.md", "rows.md", "codex.log", "agy.log"):
        entries.append(("@" + name, _size(lane / name)))
    # A tree edit, or another lane's journal claiming one of these rows, changes what `landed` means.
    paths = row_paths(root)
    for f in sorted((lane / "out").glob("*/*.c")):
        rid = f.parent.name + "/" + f.stem
        p = paths.get(rid)
        try:
            st = p.stat()
            entries.append(("@tree/" + rid, "%d:%d" % (st.st_size, st.st_mtime_ns)))
        except (AttributeError, OSError):
            entries.append(("@tree/" + rid, "-"))
        if rid in claimed:
            entries.append(("@claimed/" + rid, 1))
    entries.append(("@code", code if code is not None else code_fingerprint()))
    return fingerprint(entries)


def lane_mtime(lane):
    """When the pack was built: PROMPT.txt/BRIEF.md are stamped at launch; else the directory itself."""
    for name in ("PROMPT.txt", "BRIEF.md", "rows.md"):
        p = lane / name
        if p.exists():
            return p.stat().st_mtime
    return lane.stat().st_mtime


def _rows_in(d):
    return sorted(f.parent.name + "/" + f.stem for f in d.glob("*/*.c")) if d.is_dir() else []


def scan_lane(lane, served_ids, journal, root=ROOT, claimed=None):
    """One ledger record, read from the lane directory, its journal and the tree (`claimed` = the ids
    every lane journal reports applied; it defaults to this lane's own)."""
    name = lane.name
    model = tier = family = stratum = None
    log = lane / "codex.log"
    if log.exists():
        with log.open(errors="replace") as fh:
            model = parse_model("".join(fh.readline() for _ in range(40)))
        tier = tier_of_model(model)
    # An agy lane's BRIEF still says "(luna)" - the pack was built before launch_lane.sh sent it to agy -
    # so the empty agy.log outranks the title. The codex.log model line outranks both.
    if tier is None and (lane / "agy.log").exists():
        tier = "agy"
    brief = lane / "BRIEF.md"
    if brief.exists():
        with brief.open(errors="replace") as fh:
            btier, family = parse_title(fh.readline())
        tier = tier or btier
    rows_md = lane / "rows.md"
    if rows_md.exists():
        stratum = parse_stratum(rows_md.read_text(errors="replace"))
    if family is None:
        for prefix, fam in sorted(FAMILY_PREFIX, key=lambda kv: -len(kv[0])):
            if name.startswith(prefix):
                family = fam
                break
    exact_rows = _rows_in(lane / "out")
    applied, refused = parse_journal(journal.read_text(errors="replace") if journal.exists() else "")
    tree = tree_landed(lane, root, set(applied) if claimed is None else claimed)
    landed_rows = applied + tree

    pins, unknown = 0, 0
    for rid in landed_rows:
        b, o = lane / "base" / (rid + ".c"), lane / "out" / (rid + ".c")
        if b.exists() and o.exists():
            pins += (len(sites_of(b.read_text(errors="replace")))
                     - len(sites_of(o.read_text(errors="replace"))))
        else:
            unknown += 1
    served_known = (lane / "base").is_dir()
    served = len(served_ids) if served_known else 0
    return {"lane": name,
            "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime(lane_mtime(lane))),
            "tier": tier, "model": model, "family": family or "other", "stratum": stratum,
            "served": served, "served_known": served_known,
            "exact": len(exact_rows), "candidates": len(_rows_in(lane / "candidates")),
            "landed": len(landed_rows), "landed_journal": len(applied), "landed_tree": len(tree),
            "refused": refused, "pins_removed": pins, "pins_unknown_rows": unknown,
            "journal": journal.exists(),
            "rate": round(len(landed_rows) / served, 4) if (served_known and served) else None}


def build(root=ROOT, force=False):
    root = Path(root)
    old = {} if force else {r["lane"]: r for r in load(root, quiet=True)}
    by_lane = {}
    for rid, lanes in served_mod.served_rows(root).items():
        for lane in lanes:
            by_lane.setdefault(lane, []).append(rid)
    claimed, code = applied_anywhere(root), code_fingerprint()
    recs, reused = [], 0
    for lane in lane_dirs(root):
        journal = root / "ledger" / "sweeps" / ("lane_%s.jsonl" % lane.name)
        fp = lane_fingerprint(lane, journal, root, claimed, code)
        prev = old.get(lane.name)
        if prev and prev.get("fp") == fp:
            recs.append(prev)
            reused += 1
            continue
        rec = scan_lane(lane, by_lane.get(lane.name, []), journal, root, claimed)
        rec["fp"] = fp
        recs.append(rec)
    recs.sort(key=lambda r: (r.get("at") or "", r["lane"]), reverse=True)
    out = root / LEDGER
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_text("".join(json.dumps(r, sort_keys=True) + "\n" for r in recs))
    return recs, reused


def load(root=ROOT, quiet=False):
    path = Path(root) / LEDGER
    if not path.exists():
        if not quiet:
            raise SystemExit("no %s yet: run `python3 tools/lanes/ledger.py build` first" % LEDGER)
        return []
    recs = []
    for line in path.read_text().splitlines():
        if line.strip():
            recs.append(json.loads(line))
    return recs


# ---------------------------------------------------------------- reports

def _fmt_rate(landed, served):
    return "%.2f" % (landed / served) if served else "-"


def table(recs):
    head = ["lane", "tier", "model", "family", "stratum", "served", "exact", "landed", "pins -", "rate"]
    lines = ["| " + " | ".join(head) + " |", "|" + "---|" * len(head)]
    for r in recs:
        lines.append("| %s | %s | %s | %s | %s | %s | %d | %d | %d | %s |" % (
            r["lane"], r["tier"] or "?", r["model"] or "-", r["family"], r["stratum"] or "-",
            r["served"] if r["served_known"] else "?", r["exact"], r["landed"], r["pins_removed"],
            "%.2f" % r["rate"] if r["rate"] is not None else "-"))
    return "\n".join(lines)


def group_key(rec, fields):
    return tuple(str(rec.get(f) or "-") for f in fields)


def aggregate(recs, fields):
    """{key tuple: totals}. served (and the rate's numerator) count only lanes whose served is known."""
    agg = {}
    for r in recs:
        a = agg.setdefault(group_key(r, fields), dict(lanes=0, nobase=0, served=0, served_landed=0,
                                                      exact=0, landed=0, pins=0))
        a["lanes"] += 1
        a["exact"] += r["exact"]
        a["landed"] += r["landed"]
        a["pins"] += r["pins_removed"]
        if r["served_known"]:
            a["served"] += r["served"]
            a["served_landed"] += r["landed"]
        else:
            a["nobase"] += 1
    return agg


def by_table(recs, fields):
    agg = aggregate(recs, fields)
    rows = sorted(agg.items(),
                  key=lambda kv: (-(kv[1]["served_landed"] / kv[1]["served"]) if kv[1]["served"] else 1,
                                  -kv[1]["served"]))
    head = [",".join(fields), "lanes", "served", "exact", "landed", "pins -", "rate", "no base"]
    lines = ["| " + " | ".join(head) + " |", "|" + "---|" * len(head)]
    tot = dict(lanes=0, nobase=0, served=0, served_landed=0, exact=0, landed=0, pins=0)
    for key, a in rows:
        for k in tot:
            tot[k] += a[k]
        lines.append("| %s | %d | %d | %d | %d | %d | %s | %d |" % (
            " ".join(key), a["lanes"], a["served"], a["exact"], a["landed"], a["pins"],
            _fmt_rate(a["served_landed"], a["served"]), a["nobase"]))
    lines.append("| **total** | %d | %d | %d | %d | %d | %s | %d |" % (
        tot["lanes"], tot["served"], tot["exact"], tot["landed"], tot["pins"],
        _fmt_rate(tot["served_landed"], tot["served"]), tot["nobase"]))
    lines.append("")
    lines.append("`served` and `rate` count only the lanes that have a `base/` listing (`no base` counts "
                 "the rest); `exact`, `landed` and `pins -` count every lane, so a group holding base-less "
                 "lanes can show landed > served.")
    return "\n".join(lines)


def closed(recs, threshold, minserved=20):
    """(family, stratum) groups measured on >= minserved served rows that paid under `threshold`.
    Groups with no stratum are included as `-`: a whole family can be closed too."""
    out = []
    for key, a in aggregate(recs, ["family", "stratum"]).items():
        if a["served"] < minserved:
            continue
        rate = a["served_landed"] / a["served"]
        if rate < threshold:
            out.append((key[0], key[1], rate, a["served"]))
    out.sort(key=lambda t: (t[2], -t[3]))
    return out


def main(argv):
    args = list(argv)
    if args[:1] == ["build"]:
        force = bool({"--force", "--rebuild"} & set(args[1:]))
        recs, reused = build(force=force)
        print("%d lanes in %s (%d reused, %d rescanned%s)" % (
            len(recs), LEDGER, reused, len(recs) - reused, ", forced" if force else ""))
        tree = sum(r.get("landed_tree", 0) for r in recs)
        print("%d landed rows, %d of them witnessed by the tree rather than a journal"
              % (sum(r["landed"] for r in recs), tree))
        return
    recs = load()
    if "--closed" in args:
        thr = float(args[args.index("--closed") + 1])
        rows = closed(recs, thr)
        print("CLOSED (rate < %.2f over >= 20 served rows): %d group(s)" % (thr, len(rows)),
              file=sys.stderr)      # stdout stays exactly the list, for a pack builder's exclusions
        for fam, stratum, rate, n in rows:
            print("%s %s %.2f %d" % (fam, stratum, rate, n))
        return
    if "--by" in args:
        fields = [f.strip() for f in args[args.index("--by") + 1].split(",") if f.strip()]
        bad = [f for f in fields if f not in ("tier", "model", "family", "stratum")]
        if bad:
            raise SystemExit("--by takes tier|model|family|stratum (comma-separated), not %s" % bad[0])
        print(by_table(recs, fields))
        return
    print(table(recs))


if __name__ == "__main__":
    main(sys.argv[1:])
