#!/usr/bin/env python3
"""Apply evidence-backed function renames (L4 names) through the alias mechanism, verified.

    python3 tools/apply_names.py ledger/evidence/names_proposed.tsv [--limit N] [--only func_X,..] [--dry-run] [--workers 6]

Input rows have the config/names.tsv columns: addr, old (func_<addr>), new (readable identifier),
evidence.  For each row, in order:
  1. refuse when `old` is already renamed, `new` is already taken (names.tsv, any identifier in
     the tree), `old` has no defining row in the tree, or `new` is not a C identifier;
  2. append the row to config/names.tsv (tools/build/ccproc.py then keeps the defining TU's
     section `.text.func_<addr>` and emits the `func_<addr> = new` alias; the gate's linker
     script and the scorer resolve the readable name through the same table);
  3. rewrite every `\\bold\\b` in every src/ file that mentions it (definition, prototypes, calls,
     comments) - the per-row files each carry their own declarations, so every mention is a
     separate TU;
  4. verify every touched row through tools/verify.py (the per-row scorer; SLUS rows by object
     identity with symbol names masked).  Any failure reverts every file of the name and the
     names.tsv line; the outcome is journalled either way in ledger/names.jsonl.
Touched windows still need the window gate afterwards (tools/build/gate_all.py) and SLUS its
SHA-1 gate (tools/build/build_slus.sh); both are the proof of record.
"""
import argparse, json, re, sys, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, append_jsonl, sha_text
from verify import verify

NAMES = ROOT / "config" / "names.tsv"
INCLUDE = ROOT / "include"
JOURNAL = LEDGER / "names.jsonl"
IDENT = re.compile(r"^[A-Za-z_][A-Za-z0-9_]*$")
CONTAINERS = ("slus", "main", "town", "dungeon", "ovmovie")

def read_names():
    out = []
    for raw in NAMES.read_text().splitlines():
        line = raw.split("#", 1)[0].rstrip()
        cols = line.split("\t")
        if len(cols) >= 3 and cols[1].strip():
            out.append([c.strip() for c in cols[:4]] + [""] * (4 - len(cols)))
    return out

def load_tree():
    """{path: text} for every src/ file, and the set of identifiers the tree uses."""
    texts = {}
    for c in CONTAINERS:
        for p in sorted((ROOT / "src" / c).glob("*.c")):
            texts[p] = p.read_text(errors="replace")
    idents = set()
    for t in texts.values():           # code only: a developer name quoted in a summary comment is not a collision
        code = re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", t, flags=re.S))
        idents.update(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", code))
    for p in (ROOT / "include").rglob("*.h"):
        code = re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", p.read_text(errors="replace"), flags=re.S))
        idents.update(re.findall(r"\b[A-Za-z_][A-Za-z0-9_]*\b", code))
    return texts, idents

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("tsv"); ap.add_argument("--limit", type=int); ap.add_argument("--only")
    ap.add_argument("--dry-run", action="store_true"); ap.add_argument("--workers", type=int, default=6)
    a = ap.parse_args()
    proposed = []
    for raw in Path(a.tsv).read_text().splitlines():
        line = raw.split("#", 1)[0].rstrip()
        cols = [c.strip() for c in line.split("\t")]
        if len(cols) >= 4 and cols[1]:
            proposed.append(cols[:4])
    if a.only:
        keep = set(a.only.split(",")); proposed = [p for p in proposed if p[1] in keep]
    if a.limit:
        proposed = proposed[:a.limit]
    applied = {r[1]: r[2] for r in read_names()}
    taken = set(applied.values())
    texts, idents = load_tree()
    by_file = {}
    for r in rows():
        by_file[ROOT / "src" / r["container"] / Path(r["c_path"]).name] = r
    defined = {}
    for r in rows():
        for n in {r["func"], r.get("true_name")} | set(r.get("defs") or []):
            if n:
                defined.setdefault(n, r)
    done = {j["old"] for j in (json.loads(l) for l in JOURNAL.read_text().splitlines() if l.strip()) if j.get("outcome") == "applied"} if JOURNAL.exists() else set()
    print(f"{len(proposed)} proposed, {len(applied)} already in names.tsv", flush=True)
    tally = {}
    for addr, old, new, evidence in proposed:
        rec = {"addr": addr, "old": old, "new": new, "at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}
        why = None
        if old in defined:      # the C defines the function under its true-space symbol; the evidence may name the row
            drow = defined[old]; old = drow.get("true_name") or drow.get("func") or old; addr = "0x" + old[5:]
            rec.update({"old": old, "addr": addr})
        if old in applied or old in done:
            why = "already renamed to %s" % applied.get(old, new)
        elif not IDENT.match(new) or new.startswith("func_"):
            why = "not a readable identifier"
        elif new in taken or new in idents:
            why = "identifier already used in the tree"
        elif old not in defined:
            why = "no defining row in the tree"
        if why:
            tally["refused"] = tally.get("refused", 0) + 1
            if not a.dry_run: append_jsonl(JOURNAL, dict(rec, outcome="refused", reason=why))
            print(f"refuse {old} -> {new}: {why}"); continue
        pat = re.compile(r"\b" + re.escape(old) + r"\b")
        touched = {p: t for p, t in texts.items() if pat.search(t)}
        touched_rows = sorted({by_file[p]["id"] for p in touched if p in by_file})
        rec.update({"files": len(touched), "rows": touched_rows})
        if a.dry_run:
            print(f"would rename {old} -> {new}: {len(touched)} files, {len(touched_rows)} rows"); continue
        # 2. names.tsv first: the scorer and the gate read the alias table when they compile
        NAMES.write_text(NAMES.read_text().rstrip("\n") + f"\n{addr}\t{old}\t{new}\t{evidence}\n")
        # 3. rewrite
        new_texts = {p: pat.sub(new, t) for p, t in touched.items()}
        for p, t in new_texts.items(): p.write_text(t)
        # 4. verify every touched row
        def one(rid):
            r = next(r for r in rows() if r["id"] == rid)
            p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            v = verify(r, p, include_root=INCLUDE)
            return rid, v
        bad = []
        with ThreadPoolExecutor(max_workers=a.workers) as ex:
            for rid, v in ex.map(one, touched_rows):
                if not v.get("exact"):
                    bad.append((rid, v.get("status"), v.get("class"), v.get("total"), (v.get("err") or "")[-160:]))
        if bad:
            for p, t in touched.items(): p.write_text(t)
            NAMES.write_text("".join(l for l in NAMES.read_text().splitlines(keepends=True) if not l.startswith(f"{addr}\t{old}\t{new}\t")))
            tally["reverted"] = tally.get("reverted", 0) + 1
            append_jsonl(JOURNAL, dict(rec, outcome="reverted", failures=bad[:5]))
            print(f"REVERT {old} -> {new}: {len(bad)} of {len(touched_rows)} rows not exact: {bad[:2]}", flush=True)
            continue
        texts.update(new_texts); idents.add(new); taken.add(new); applied[old] = new
        tally["applied"] = tally.get("applied", 0) + 1
        append_jsonl(JOURNAL, dict(rec, outcome="applied"))
        print(f"applied {old} -> {new}: {len(touched)} files, {len(touched_rows)} rows exact", flush=True)
    print("done:", tally)

if __name__ == "__main__":
    main()
