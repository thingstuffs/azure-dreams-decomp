#!/usr/bin/env python3
"""Pin patterns: the tables behind docs/PIN_PATTERNS.md, regenerated from the per-site ledgers.

    python3 tools/pin_patterns.py > docs/PIN_PATTERNS_DATA.md
    python3 tools/pin_patterns.py --history > docs/PIN_PATTERNS_DATA.md   # + replay every landed
                                                                          #   pin removal from git

Inputs: ledger/pins_site.jsonl and ledger/pins_subsets.jsonl (tools/pin_sites.py).  Only records
whose in_sha is the row's CURRENT text count, so re-run `pin_sites.py --sites` (and --subsets) on
the rows that changed before reading a table as today's.  docs/PIN_PATTERNS.md carries the
narrative - what each number means and what to do about it; this tool owns the numbers.

  coverage      how many clusters cover 50/80/90 % of the live sites at four granularities:
                residue class, macro family x class, residue signature (the exact instruction
                change: one token per aligned region - rename / operand / move:<mnem> /
                +<mnem> / -<mnem>), family x signature
  rename kinds  inside the rename cluster, per instruction: which operand differs, and the two
                directional kinds that name a mechanism - FOLD (retail computes in place, gcc reads
                the copy's source: cse folded a copy) and SPLIT (the reverse)
  linkage       per pin pair of the 2..5-pin rows: joint cost against the two single costs
  --history     every t15 / depin-lane / cell-fix / t9 / t16 / t17 / subset landing replayed from git:
                which fix removed which kind of pin
"""
import argparse, collections, difflib, json, re, subprocess, sys, time
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, sha_text, current_text, PARKED_CONTAINERS
from pin_census import sites_of

REG_RE = re.compile(r"\$(?:[a-z]+\d*|\d+)")
NO_DEST = {"sw", "sh", "sb", "swl", "swr", "beq", "bne", "beqz", "bnez", "bltz", "bgez", "blez", "bgtz",
           "jr", "jalr", "mult", "multu", "div", "divu", "mtlo", "mthi"}
HISTORY_TFS = ("t15_shapes", "t13_depin", "t13_cellfix", "t9_regpins", "t16_absidiom", "t17_divpow2", "pin_subsets")


def family(m):
    m = m or ""
    if m == "ASM_REG":
        return "REG"
    if m.startswith("ASM_KEEP"):
        return "KEEP_NV" if m.endswith("_NV") else "KEEP"
    if m.startswith("ASM_USE"):
        return "USE"
    if m in ("ASM_SCHED_BARRIER", "ASM_MEM_BARRIER"):
        return "BARRIER"
    if any(k in m for k in ("TAILSLOT", "PAGEBASE", "JALDELAY")):
        return "MARKER"
    return m.replace("ASM_", "")


def _mn(w):
    return w.split()[0]


def _shape(w):
    return re.sub(r"-?0x[0-9a-f]+|\b\d+\b", "K", REG_RE.sub("R", w))


def signature(regions):
    """The residue as a sorted multiset of per-region tokens (repeats collapse to `tok*`)."""
    toks, ins, dels = [], collections.Counter(), collections.Counter()
    for r in regions:
        g, t = r["got"], r["tgt"]
        if r["op"] == "r" and len(g) == len(t) and [_mn(x) for x in g] == [_mn(x) for x in t]:
            toks.append("rename" if [_shape(x) for x in g] == [_shape(x) for x in t] else "operand")
            continue
        for x in g:
            dels[_mn(x)] += 1
        for x in t:
            ins[_mn(x)] += 1
    moved = ins & dels
    for m, k in moved.items():
        toks += ["move:" + m] * k
    for m, k in (ins - moved).items():
        toks += ["+" + m] * k
    for m, k in (dels - moved).items():
        toks += ["-" + m] * k
    c = collections.Counter(toks)
    return " ".join(sorted(f"{k}{'*' if v > 1 else ''}" for k, v in c.items()))


def current_shas():
    """({row id: sha of its current text}, number of rows that still carry a live pin)."""
    out, pinned = {}, 0
    for r in rows():
        if r.get("exists") and r["container"] not in PARKED_CONTAINERS:
            try:
                t = current_text(r)
            except OSError:
                continue
            out[r["id"]] = sha_text(t)
            pinned += "ASM_" in t and bool(sites_of(t))
    return out, pinned


def md_table(head, body):
    print("| " + " | ".join(head) + " |")
    print("|" + "|".join("---:" if i else "---" for i in range(len(head))) + "|")
    for row in body:
        print("| " + " | ".join(str(x) for x in row) + " |")
    print()


def coverage(items, keyf):
    c = collections.Counter(keyf(s) for s in items)
    n, cum, cov = len(items), 0, {}
    for i, (_, v) in enumerate(c.most_common(), 1):
        cum += v
        for t in (50, 80, 90):
            if t not in cov and cum >= t / 100 * n:
                cov[t] = i
    return [len(c), cov.get(50, "-"), cov.get(80, "-"), cov.get(90, "-"), sum(1 for v in c.values() if v == 1)], c


def rename_kinds(sites):
    kinds, per_site, directional = collections.Counter(), collections.Counter(), collections.Counter()
    for s in sites:
        if not signature(s["regions"]).startswith("rename"):
            continue
        mine = set()
        for r in s["regions"]:
            if r["op"] != "r" or len(r["got"]) != len(r["tgt"]):
                continue
            for g, t in zip(r["got"], r["tgt"]):
                if g == t or " " not in g:
                    continue
                (mg, rest_g), (mt, rest_t) = g.split(None, 1), t.split(None, 1)
                og, ot = [x.strip() for x in rest_g.split(",")], [x.strip() for x in rest_t.split(",")]
                if mg != mt or len(og) != len(ot):
                    continue
                diff = [i for i, (a, b) in enumerate(zip(og, ot)) if a != b]
                if not diff:
                    continue
                if mg in NO_DEST:
                    k = "a store/branch reads another register"
                elif diff == [0]:
                    k = "destination only"
                elif 0 in diff:
                    k = "destination and a source"
                elif ot[0] in ot[1:] and og[0] not in og[1:]:
                    k = "FOLD: retail in place, gcc reads the copy's source"
                    directional[("FOLD", mg)] += 1
                elif og[0] in og[1:] and ot[0] not in ot[1:]:
                    k = "SPLIT: gcc in place, retail reads another register"
                    directional[("SPLIT", mg)] += 1
                else:
                    k = "a source only"
                kinds[k] += 1
                mine.add(k)
        per_site.update(mine)
    return kinds, per_site, directional


def linkage(sites, subsets):
    single = {(s["id"], s["site"]): (s.get("total"), s.get("line")) for s in sites}
    kinds, bygap, exact = collections.Counter(), collections.defaultdict(collections.Counter), collections.Counter()
    for r in subsets:
        if r.get("exact") and len(r["s"]) < r["n"]:
            exact[(len(r["s"]), r["n"])] += 1
        if len(r["s"]) != 2 or r.get("total") is None:
            continue
        (a, la), (b, lb) = (single.get((r["id"], i), (None, None)) for i in r["s"])
        if a is None or b is None:
            continue
        j = r["total"]
        k = ("cancel (joint < either single)" if j < min(a, b) else "overlap (joint < sum)" if j < a + b - 1
             else "additive (joint = sum)" if abs(j - (a + b)) <= 1 else "synergy (joint > sum)")
        kinds[k] += 1
        if la and lb:
            g = abs(la - lb)
            bygap["<= 3 lines" if g <= 3 else "4-15" if g <= 15 else "16+"][k] += 1
    return kinds, bygap, exact


DECL_RE = re.compile(r"^(?:register\s+)?(?:(?:unsigned|signed|const|volatile|struct|union)\s+)*[A-Za-z_]\w*\s*\**\s*([A-Za-z_]\w*)\s*(=.*)?;$")


def _hunk_class(old, new):
    o, n = " ".join(old), " ".join(new)
    cls = []
    if "while (0)" in n and "while (0)" not in o:
        cls.append("fence")
    if old and new and len(old) == len(new) and all(DECL_RE.match(a) and DECL_RE.match(b) for a, b in zip(old, new)):
        cls.append("retype")
    if sorted(old) == sorted(new) and old != new:
        cls.append("reorder")
    if re.search(r"\babs\s*\(", n) and not re.search(r"\babs\s*\(", o):
        cls.append("abs")
    if not old and new:
        cls.append("insert")
    if old and not new:
        cls.append("delete")
    return cls or ["rewrite"]


def history():
    """[(fix label, macro family)] per removed site, from each landing's pre- and post-fix text."""
    from pin_sites import erase_many
    from xform.t12_stmtorder import mask
    by = {r["id"]: r for r in rows()}
    per_file = collections.defaultdict(list)
    for tf in HISTORY_TFS:
        for j in read_jsonl(LEDGER / f"sweeps/{tf}.jsonl"):
            if j.get("outcome") == "applied" and j.get("in_sha") and j.get("out_sha") and j["id"] in by:
                r = by[j["id"]]
                per_file[f"src/{r['container']}/{Path(r['c_path']).name}"].append((tf, j))
    out, missing = [], 0
    for rel, items in per_file.items():
        texts = {}
        hs = subprocess.run(["git", "log", "--format=%H", "--since=2026-09-06", "--", rel], cwd=ROOT,
                            capture_output=True, text=True).stdout.split()
        for h in hs:
            for ref in (f"{h}:{rel}", f"{h}^:{rel}"):
                p = subprocess.run(["git", "show", ref], cwd=ROOT, capture_output=True)
                if p.returncode == 0:
                    t = p.stdout.decode("utf-8", "replace")
                    texts[sha_text(t)] = t
        cur = (ROOT / rel).read_text(errors="replace")
        texts[sha_text(cur)] = cur
        for tf, j in items:
            pre, post = texts.get(j["in_sha"]), texts.get(j["out_sha"])
            if pre is None or post is None:
                missing += 1
                continue
            spre, spost = sites_of(pre), sites_of(post)
            key = lambda s: (s[1], s[2], s[6].split()[-1] if s[0] == "reg" and s[6] else "")
            left = collections.Counter(key(s) for s in spost)
            removed = []
            for s in spre:
                if left[key(s)]:
                    left[key(s)] -= 1
                else:
                    removed.append(s)
            if not removed:
                continue
            a = [" ".join(l.split()) for l in mask(erase_many(pre, removed, clean_notes=True)).splitlines() if l.strip()]
            b = [" ".join(l.split()) for l in mask(post).splitlines() if l.strip()]
            cls = sorted({c for op, a1, a2, b1, b2 in difflib.SequenceMatcher(None, a, b, autojunk=False).get_opcodes()
                          if op != "equal" for c in _hunk_class(a[a1:a2], b[b1:b2])})
            if tf == "t15_shapes":
                parts = sorted({p.split(":")[0] for p in (j.get("step") or "").split("+") if p and p != "partial"})
                label = "t15 " + ("+".join(parts) or "partial-strip")
            elif tf in ("t16_absidiom", "t17_divpow2", "pin_subsets", "t13_cellfix"):
                label = tf
            else:
                label = tf + " " + (",".join(cls) if cls else "pure erasure")
            out += [(label, family(s[1]), "fence" in label or "fence" in cls) for s in removed]
    return out, missing


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--history", action="store_true")
    a = ap.parse_args()
    cur, live_rows = current_shas()
    site_recs = {}
    for s in read_jsonl(LEDGER / "pins_site.jsonl"):
        if cur.get(s["id"]) == s["in_sha"]:
            site_recs[(s["id"], s["site"])] = s
    sites = list(site_recs.values())
    subsets = {}
    for r in read_jsonl(LEDGER / "pins_subsets.jsonl"):
        if cur.get(r["id"]) == r["in_sha"]:
            subsets[(r["id"], tuple(r["s"]))] = r
    subsets = list(subsets.values())
    nm =[s for s in sites if family(s.get("macro")) != "MARKER"]
    print("# Pin pattern tables\n")
    print(f"Generated {time.strftime('%Y-%m-%dT%H:%MZ', time.gmtime())} by `tools/pin_patterns.py` - do not edit; "
          f"the narrative is `docs/PIN_PATTERNS.md`.  Site records at the current text: {len(sites):,} in "
          f"{len({s['id'] for s in sites}):,} rows (of {live_rows:,} pinned rows); marker pins "
          f"(TAILSLOT/PAGEBASE/JALDELAY) left out below: {len(sites) - len(nm):,}.  Singly exact: "
          f"{sum(1 for s in sites if s.get('exact'))}.\n")
    print("## Damage when a site is erased alone\n")
    b = collections.Counter("fail" if s.get("total") is None else "1-2" if s["total"] <= 2 else "3-5" if s["total"] <= 5
                            else "6-12" if s["total"] <= 12 else "13+" for s in nm if not s.get("exact"))
    md_table(["words", "sites"], [(k, f"{b[k]:,}") for k in ("1-2", "3-5", "6-12", "13+", "fail") if b[k]])
    sig = lambda s: signature(s["regions"]) if s.get("regions") else ("(no regions: > 12 words)" if (s.get("total") or 0) > 12 else "?")
    for band, sel in (("within 5 words", [s for s in nm if s.get("total") is not None and s["total"] <= 5]),
                      ("within 12 words", [s for s in nm if s.get("total") is not None and s["total"] <= 12]),
                      ("every non-marker site", nm)):
        print(f"## Coverage - {band} ({len(sel):,} sites)\n")
        body = []
        for label, kf in (("residue class", lambda s: s.get("class")),
                          ("macro family x class", lambda s: (family(s["macro"]), s.get("class"))),
                          ("residue signature", sig),
                          ("macro family x signature", lambda s: (family(s["macro"]), sig(s)))):
            nums, c = coverage(sel, kf)
            body.append([label] + nums)
            if band == "within 12 words" and label == "residue signature":
                top = c.most_common(30)
        md_table(["granularity", "clusters", "cover 50 %", "cover 80 %", "cover 90 %", "singletons"], body)
    print("## Top residue signatures (within 12 words)\n")
    md_table(["sites", "signature"], [(f"{v:,}", f"`{k}`") for k, v in top])
    kinds, per_site, directional = rename_kinds([s for s in nm if s.get("regions") and (s.get("total") or 99) <= 12])
    print("## Inside the rename cluster (within 12 words)\n")
    md_table(["which operand differs", "instructions", "sites"], [(k, f"{v:,}", f"{per_site[k]:,}") for k, v in kinds.most_common()])
    md_table(["directional kind", "mnemonic", "instructions"], [(d, m, v) for (d, m), v in directional.most_common(16)])
    lk, bygap, exact = linkage(sites, subsets)
    tot = sum(lk.values())
    print(f"## Linkage - {tot:,} pin pairs in {len({r['id'] for r in subsets}):,} rows\n")
    md_table(["relation", "pairs", "share"], [(k, f"{v:,}", f"{100 * v / tot:.0f} %") for k, v in lk.most_common()] if tot else [])
    md_table(["line gap", "pairs", "overlap", "synergy", "cancel"],
             [(g, sum(bygap[g].values()),
               f"{100 * bygap[g]['overlap (joint < sum)'] / max(1, sum(bygap[g].values())):.0f} %",
               f"{100 * bygap[g]['synergy (joint > sum)'] / max(1, sum(bygap[g].values())):.0f} %",
               f"{100 * bygap[g]['cancel (joint < either single)'] / max(1, sum(bygap[g].values())):.0f} %")
              for g in ("<= 3 lines", "4-15", "16+") if bygap[g]])
    print("Exact proper subsets still open at the current text (size of n): "
          + (", ".join(f"{k[0]} of {k[1]}: {v}" for k, v in sorted(exact.items())) or "none") + "\n")
    if a.history:
        h, missing = history()
        print(f"## What has ever freed a pin - {len(h):,} removed sites (pre-fix text not in git: {missing})\n")
        c = collections.Counter(lbl for lbl, _, _ in h)
        md_table(["fix", "removed sites"], [(k, v) for k, v in c.most_common(30)])
        fence = sum(1 for _, _, f in h if f)
        print(f"Replaced by a fence or fence variant: {fence} of {len(h)} ({100 * fence / max(1, len(h)):.0f} %).  "
              "Macro family of the removed sites: "
              + ", ".join(f"{k} {v}" for k, v in collections.Counter(f for _, f, _ in h).most_common()) + ".\n")


if __name__ == "__main__":
    main()
