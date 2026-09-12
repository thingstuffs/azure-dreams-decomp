#!/usr/bin/env python3
"""Per-site pin census over the CURRENT text, and the linkage between a row's pins.

    python3 tools/pin_sites.py --sites   [--workers 10] [--only ids|file] [--skip file]
    python3 tools/pin_sites.py --subsets [--max-pins 5] [--workers 10] [--only ...] [--skip ...]
                                         [--land-dir DIR]
    python3 tools/pin_sites.py --subsets --min-pins 6 --max-pins 10 --max-k 2     # pairs only

Why this exists.  `ledger/pins.jsonl` (tools/pin_census.py) measured one pin at a time against the
text frozen at the pin: 22,505 sites, half of them since removed, every body since rewritten by the
Layer-2 campaign.  `ledger/pins_strip.jsonl` erases all of a row's pins at once.  Neither says what
a single LIVE pin holds in place today, or which of a row's pins hold the SAME instructions - and a
pin set that only falls together is invisible to T2 (greedy, one site at a time) and to the strip
(everything at once) alike.

--sites    every live site: erase it alone, score it with the aligned-regions view (one scorer
           call for an overlay row), and record what the site IS - macro, pinned variable, its
           declared type, how it is defined (load / constant / call / parameter / arithmetic /
           address / copy), where it sits - next to what erasing it DOES: residue class, total, and
           the retail word ranges that move.                              -> ledger/pins_site.jsonl
--subsets  every row with 2..N live pins: erase every subset of two or more of them.  The totals are
           the linkage (two pins whose joint erasure costs less than the sum of their single costs
           hold the same instructions), and an exact proper subset is a partial removal nobody has
           tried: T2 walks singles, the strip takes all, and t15's partial path keeps exactly one pin
           and only when its probe budget lasts.  The largest exact subset per row is written to
           --land-dir for tools/apply_candidates.py.                   -> ledger/pins_subsets.jsonl

Totals here are the regions view's GLOBAL-LCS distance, which can sit a few points above the
`--summary-json` total the strip ledger stores: compare singles and subsets with each other (the
full set is re-scored as a subset for exactly that reason), never against pins_strip.jsonl.
"""
import argparse, collections, itertools, json, re, sys, tempfile, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, append_jsonl, sha_text, clean_path
from pin_census import sites_of, erase, context_of, arm_labels, HAS_PP_RE
from verify import verify
from xform.t12_stmtorder import mask

INCLUDE = ROOT / "include"
SITES_OUT = LEDGER / "pins_site.jsonl"
SUBSETS_OUT = LEDGER / "pins_subsets.jsonl"
REGION_RE = re.compile(r"^--- (insert|delete|replace) got\[(\d+):(\d+)\] tgt\[(\d+):(\d+)\]")
TOTAL_RE = re.compile(r"\bTOTAL\s+(\d+)\s+class\s+(\S+)")
KEEP_TEXT_REGIONS = 8          # a residue this small keeps its instruction text, not just mnemonics
MAX_REGIONS = 24


# ------------------------------------------------------------------------------------ scoring

def regions_of(text):
    out = []
    for line in text.splitlines():
        m = REGION_RE.match(line)
        if m:
            out.append({"op": m.group(1)[0], "g": [int(m.group(2)), int(m.group(3))],
                        "t": [int(m.group(4)), int(m.group(5))], "got": [], "tgt": []})
            continue
        if not out or "|" not in line:
            continue
        left, _, right = line.partition("|")
        for side, txt in (("got", left), ("tgt", right)):
            w = " ".join(txt.split())
            if w:
                out[-1][side].append(w)
    return out


def compact(regs):
    """Positions always; instruction text only for a small residue, mnemonics otherwise."""
    full = len(regs) <= KEEP_TEXT_REGIONS
    out = []
    for r in regs[:MAX_REGIONS]:
        c = {"op": r["op"], "g": r["g"], "t": r["t"]}
        for side in ("got", "tgt"):
            c[side] = r[side][:6] if full else [w.split()[0] for w in r[side][:6]]
        out.append(c)
    return out


def score(row, text):
    """{status, exact, total, class, regions, secs} for one candidate text."""
    t0 = time.time()
    with tempfile.TemporaryDirectory() as td:
        f = Path(td) / Path(row["c_path"]).name
        f.write_text(text)
        if row["kind"] == "slus":
            v = verify(row, f, include_root=INCLUDE)
            rec = {"status": "ok" if v.get("status") == "ok" else "failed", "exact": bool(v.get("exact")),
                   "total": 0 if v.get("exact") else v.get("total"), "class": "match" if v.get("exact") else v.get("class")}
            if rec["status"] == "ok" and not rec["exact"]:
                d = verify(row, f, include_root=INCLUDE, regions=True)
                rec["regions"] = regions_of(d.get("text", "") or "")
            rec["secs"] = round(time.time() - t0, 2)
            return rec
        d = verify(row, f, include_root=INCLUDE, regions=True)
    txt = d.get("text", "") or ""
    if "*** MATCH ***" in txt:
        return {"status": "ok", "exact": True, "total": 0, "class": "match", "secs": round(time.time() - t0, 2)}
    m = TOTAL_RE.search(txt)
    if not m:
        # no TOTAL line and no MATCH: the candidate did not build - never read that as a win
        return {"status": "failed", "exact": False, "total": None, "class": None, "secs": round(time.time() - t0, 2)}
    total = int(m.group(1))
    return {"status": "ok", "exact": total == 0, "total": total, "class": "match" if total == 0 else m.group(2),
            "regions": regions_of(txt), "secs": round(time.time() - t0, 2)}


# ------------------------------------------------------------------------------ static facts

CAST_RE = re.compile(r"^\(\s*(?:(?:unsigned|signed|const|volatile|struct|union)\s+)*[A-Za-z_]\w*\s*\**\s*\)\s*")
ARITH_RE = re.compile(r"(?<![-=!<>&|])(?:[+\-/%^|]|<<|>>|(?<![&(,])&(?!&)|(?<=[\w)\]])\s*\*)")
WIDTH = {"u8": "u8", "s8": "s8", "char": "s8", "u16": "u16", "s16": "s16", "short": "s16",
         "u32": "u32", "s32": "s32", "int": "s32", "unsigned": "u32", "long": "s32", "void": "void"}


def fn_bounds(masked, pos):
    """(index of the opening brace, index of the closing brace) of the top-level block around pos."""
    depth, start = 0, None
    for i, c in enumerate(masked):
        if c == "{":
            if depth == 0:
                start = i
            depth += 1
        elif c == "}":
            depth -= 1
            if depth == 0 and start is not None:
                if start <= pos <= i:
                    return start, i
                start = None
    return None


def params_of(masked, open_brace):
    head = masked[max(0, masked.rfind(";", 0, open_brace), masked.rfind("}", 0, open_brace)):open_brace]
    lo, hi = head.find("("), head.rfind(")")
    if lo < 0 or hi < lo:
        return {}
    out = {}
    for part in head[lo + 1:hi].split(","):
        m = re.search(r"([A-Za-z_][\w\s]*?)\s*(\**)\s*\b([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*$", part.strip())
        if m and m.group(3) not in ("void",):
            out[m.group(3)] = (m.group(1).split()[-1], bool(m.group(2) or m.group(4)))
    return out


def type_class(base, ptr):
    if ptr:
        return "ptr"
    if base in WIDTH:
        return WIDTH[base]
    if base in ("struct", "union"):
        return "struct"
    return "typedef"


def decl_of(body, var, params):
    if var in params:
        base, ptr = params[var]
        return type_class(base, ptr), True
    m = re.search(r"(?:^|[;{}])\s*(?:register\s+)?(?:static\s+)?(?P<ty>(?:(?:unsigned|signed|const|volatile|struct|union|enum)\s+)*[A-Za-z_]\w*)"
                  r"\s*(?P<ptr>\**)\s*\b" + re.escape(var) + r"\b\s*(?:ASM_REG\s*\([^)]*\))?\s*(?P<arr>\[[^\]]*\])?\s*(?=[;=,])", body, re.M)
    if not m:
        return None, False
    return type_class(m.group("ty").split()[-1], bool(m.group("ptr") or m.group("arr"))), False


def rhs_kind(rhs, params):
    r = rhs.strip()
    while True:
        m = CAST_RE.match(r)
        if not m:
            break
        r = r[m.end():].strip()
    if not r:
        return "other"
    if "?" in r:
        return "cond"
    if re.match(r"^[A-Za-z_]\w*\s*\(", r) and not r.startswith("sizeof"):
        return "call"
    if re.fullmatch(r"-?(?:0x[0-9A-Fa-f]+|\d+)[uUlL]*", r):
        # a KSEG0 literal is an address spelled as a number - where retail names a symbol
        return "addrlit" if re.fullmatch(r"0x80[0-9A-Fa-f]{6}[uUlL]*", r) else "const"
    if r.startswith("&") or re.search(r"\b0x80[0-9A-Fa-f]{6}\b", r) and not re.search(r"->|\[", r):
        return "addr"
    if re.fullmatch(r"[A-Za-z_]\w*", r):
        return "param" if r in params else "global" if r.startswith("D_") else "copy"
    load = r.startswith("*") or "->" in r or re.search(r"[\w)\]]\s*\[", r) is not None
    arith = ARITH_RE.search(re.sub(r"->", ".", r.lstrip("*"))) is not None
    return "load+arith" if load and arith else "load" if load else "arith" if arith else "other"


DEF_TMPL = r"(?<![.>\w])\b{v}\b\s*(=(?!=)|\+=|-=|\*=|/=|%=|&=|\|=|\^=|<<=|>>=|\+\+|--)|(?:\+\+|--)\s*\b{v}\b"


def var_facts(body, var, params, site_spans):
    """Declared type, definition kinds and use count of `var` inside one function body (masked)."""
    ty, is_param = decl_of(body, var, params)
    defs, def_pos = [], []
    for m in re.finditer(DEF_TMPL.format(v=re.escape(var)), body):
        op = m.group(1)
        def_pos.append(m.start())
        if op is None or op in ("++", "--"):
            defs.append("incr")
        elif op != "=":
            defs.append("update")
        else:
            end = body.find(";", m.end())
            defs.append(rhs_kind(body[m.end():end if end >= 0 else len(body)], params))
    refs = [m.start() for m in re.finditer(r"(?<![.>\w])\b" + re.escape(var) + r"\b", body)]
    uses = [p for p in refs if not any(a <= p < b for a, b in site_spans) and p not in def_pos]
    return {"var_type": ty, "var_param": is_param, "defs": defs, "ndefs": len(defs), "nuses": max(0, len(uses) - 1 if ty and not is_param else len(uses))}


def enclosing_loops(masked, lo, pos):
    """(in_loop, in_if) for pos, from the headers of the blocks that enclose it."""
    stack, last = [], lo
    for i in range(lo + 1, pos):
        c = masked[i]
        if c == "{":
            head = masked[last:i]
            stack.append(("loop" if re.search(r"\b(for|while)\s*\(|\bdo\s*$", head) else
                          "if" if re.search(r"\bif\s*\(|\belse\s*$", head) else "block"))
            last = i + 1
        elif c == "}":
            if stack:
                stack.pop()
            last = i + 1
        elif c == ";":
            last = i + 1
    return "loop" in stack, "if" in stack


def site_facts(text, masked, sites, idx):
    kind, macro, arg, start, end, line_no, repl = sites[idx]
    lines = text.splitlines()
    if kind == "reg":
        m = re.search(r"([A-Za-z_]\w*)\s*(\[[^\]]*\])?\s*$", repl)
        var, reg = (m.group(1) if m else None), arg
    else:
        a = [x.strip() for x in arg.split(",")] if arg else []
        var = a[0] if a and re.fullmatch(r"[A-Za-z_]\w*", a[0]) else None
        reg = a[0].strip('"') if a and a[0].startswith('"') else None
    rec = {"site": idx, "kind": kind, "macro": macro, "arg": arg[:60], "var": var, "reg": reg,
           "line": line_no, "stmt": " ".join(lines[line_no - 1].split())[:100] if line_no <= len(lines) else ""}
    rec.update({k: v for k, v in context_of(text, start, end, line_no).items() if k not in ("nonmatching_file", "enclosing")})
    fb = fn_bounds(masked, start)
    others = [s[5] for j, s in enumerate(sites) if j != idx]
    rec["gap_prev"] = min((line_no - l for l in others if l <= line_no), default=None)
    rec["gap_next"] = min((l - line_no for l in others if l >= line_no), default=None)
    rec["same_var"] = sum(1 for j, s in enumerate(sites) if j != idx and var and
                          (re.search(r"\b" + re.escape(var) + r"\b", s[2]) or s[0] == "reg" and s[6].split()[-1:] == [var]))
    if fb:
        lo, hi = fb
        body = masked[lo:hi + 1]
        params = params_of(masked, lo)
        spans = [(s[3] - lo, s[4] - lo) for s in sites if lo <= s[3] <= hi]
        if var:
            rec.update(var_facts(body, var, params, spans))
        rec["in_loop"], rec["in_if"] = enclosing_loops(masked, lo, start)
        fl0 = masked.count("\n", 0, lo) + 1
        fl1 = masked.count("\n", 0, hi) + 1
        rec["pos_frac"] = round((line_no - fl0) / max(1, fl1 - fl0), 2)
        # the neighbouring code lines, blank and pure-comment lines skipped
        code = [(i + 1, " ".join(l.split())) for i, l in enumerate(masked.splitlines()) if fl0 <= i + 1 <= fl1 and l.strip()]
        k = next((j for j, (n, _) in enumerate(code) if n >= line_no), None)
        if k is not None:
            rec["prev_code"] = code[k - 1][1][:80] if k > 0 else ""
            rec["next_code"] = code[k + 1][1][:80] if k + 1 < len(code) else ""
    return rec


# ------------------------------------------------------------------------------- erasure

ERASED_PIN_NOTE_RE = re.compile(
    r"[ \t]*/\*\s*(?:MATCH(?: pin)?\s*:|UNRESOLVED C shape \(pin\)|Byte-exact pin\b).*?\*/", re.S)

def erase_many(text, chosen, clean_notes=False):
    """Erase the chosen site tuples (from one sites_of(text) call), last first.  With clean_notes,
    the pin note on an erased pin's own line goes with it (a landing must not leave a comment
    describing a pin that is gone)."""
    cur = text
    for s in sorted(chosen, key=lambda s: s[3], reverse=True):
        whole_line = s[0] == "stmt" and text[s[4] - 1:s[4]] == "\n"
        cur = erase(cur, s)
        if not clean_notes or whole_line:
            continue
        ls = cur.rfind("\n", 0, s[3]) + 1
        le = cur.find("\n", s[3])
        le = len(cur) if le < 0 else le
        m = ERASED_PIN_NOTE_RE.search(cur, ls)
        if m and m.start() < le:
            cur = cur[:m.start()] + cur[m.end():]
            le = cur.find("\n", ls)
            le = len(cur) if le < 0 else le
        if not cur[ls:le].strip():
            cur = cur[:ls] + cur[le + 1:]
    if clean_notes:      # an `#ifndef NON_MATCHING` block left empty goes too (preprocessor only)
        cur = EMPTY_NM_RE.sub("", cur)
    return cur


EMPTY_NM_RE = re.compile(r"^[ \t]*#ifndef NON_MATCHING[ \t]*\n[ \t]*#endif[^\n]*\n", re.M)


# ----------------------------------------------------------------------------------- groups

def _tranges(rec):
    """The retail word ranges a single erasure moved (pins_site.jsonl's compact regions)."""
    return [tuple(r["t"]) for r in rec.get("regions") or [] if isinstance(r, dict)]


def _touch(ra, rb, slack=1):
    """Do two sets of retail word ranges meet (within `slack` words)?  Empty = unknown = yes."""
    if not ra or not rb:
        return True
    return any(a0 <= b1 + slack and b0 <= a1 + slack for a0, a1 in ra for b0, b1 in rb)


def linked(a, b, j, ra=(), rb=()):
    """Do two pins hold the SAME instructions?  a, b: each pin's cost erased alone; j: both erased.

    `shared = a + b - j` is roughly how many residue words the two have in common.  The pair is
    one unit when the smaller pin's damage is (almost) all shared - not merely when the joint
    cost is below the sum, which in a ten-pin row with 40 % overlapping pairs chains every pin
    into one group, i.e. the strip again - and when their retail word ranges actually meet.
    A pair that costs LESS than either alone always is one unit."""
    if a is None or b is None or j is None:
        return False
    if j < min(a, b):
        return True
    shared = a + b - j
    return shared >= max(1, min(a, b) - 1) and _touch(ra, rb)


_LINK = None


def linkage_index():
    """{(row id, in_sha): (singles {site: (total, tranges, line)}, pairs {(i, j): total})} from
    the two ledgers.  Built into a local and rebound once: sweep workers are threads."""
    global _LINK
    if _LINK is None:
        built = collections.defaultdict(lambda: ({}, {}))
        for r in read_jsonl(SITES_OUT):
            if r.get("status") == "ok":
                built[(r["id"], r["in_sha"])][0][r["site"]] = (r.get("total"), _tranges(r), r.get("line"))
        for r in read_jsonl(SUBSETS_OUT):
            if len(r["s"]) == 2 and r.get("status") == "ok":
                built[(r["id"], r["in_sha"])][1][tuple(r["s"])] = r.get("total")
        _LINK = dict(built)
    return _LINK


def pin_groups(row_id, sha, n):
    """The row's pins grouped by what they hold, at the text with this sha, as
    [{"sites": [i, ...], "cost": estimated joint damage, "pairs": measured pairs inside}].

    Union-find over `linked` pairs.  A group's cost is its largest measured pair (or its single
    cost): an ESTIMATE for groups of three or more, whose joint cost nobody measured - the search
    that uses a group measures it with its first verify.  None when the ledgers have nothing for
    this text (a row that changed since pin_sites last ran)."""
    singles, pairs = linkage_index().get((row_id, sha), ({}, {}))
    if len(singles) < n:
        return None
    parent = list(range(n))

    def find(x):
        while parent[x] != x:
            parent[x] = parent[parent[x]]
            x = parent[x]
        return x
    for (i, k), j in pairs.items():
        if i < n and k < n and linked(singles[i][0], singles[k][0], j, singles[i][1], singles[k][1]):
            parent[find(i)] = find(k)
    comp = collections.defaultdict(list)
    for i in range(n):
        comp[find(i)].append(i)
    out = []
    for members in comp.values():
        inner = [t for (i, k), t in pairs.items() if i in members and k in members and t is not None]
        cost = max(inner) if inner else singles[members[0]][0]
        out.append({"sites": sorted(members), "cost": cost, "pairs": len(inner)})
    return sorted(out, key=lambda g: (g["cost"] is None, g["cost"] or 0, -len(g["sites"])))


def run_groups(a):
    """The group-size histogram over every row the ledgers cover at its current text."""
    hist, rows_n, costs = collections.Counter(), 0, collections.Counter()
    for row, text, sites in targets(a):
        g = pin_groups(row["id"], sha_text(text), len(sites))
        if g is None or len(sites) < 2:
            continue
        pair_data = any(x["pairs"] for x in g) or len(sites) == 1
        rows_n += 1
        for x in g:
            hist[(len(sites) if len(sites) <= 10 else 11, min(len(x["sites"]), 6))] += 1
            if len(x["sites"]) > 1:
                c = x["cost"]
                costs["<= 2" if c is not None and c <= 2 else "3-5" if c is not None and c <= 5 else
                      "6-12" if c is not None and c <= 12 else "13+"] += 1
    print(f"{rows_n} rows with groups at their current text")
    for n in sorted({k[0] for k in hist}):
        cells = {s: hist[(n, s)] for s in range(1, 7)}
        print(f"  {('%d pins' % n) if n <= 10 else '11+ pins':>9}: " +
              "  ".join(f"size{s if s < 6 else '6+'}={cells[s]}" for s in range(1, 7)))
    print("multi-pin groups by estimated joint cost:", dict(costs))


# ------------------------------------------------------------------------------------ driver

def scored_mask(text):
    """mask() with the port-only / #if 0 lines blanked too: the facts describe the code the byte
    gate compiles, not a port arm's alternative spelling of it."""
    m = mask(text)
    if not HAS_PP_RE.search(text):
        return m
    out = []
    for ln, lab in zip(m.split("\n"), arm_labels(text) + ["both"]):
        out.append(" " * len(ln) if lab in ("port", "dead") else ln)
    return "\n".join(out)


def load_only(arg):
    if not arg:
        return None
    p = Path(arg)
    return set(p.read_text().split()) if p.exists() else set(arg.split(","))


def targets(a):
    only, skip = load_only(a.only), load_only(a.skip) or set()
    out = []
    for row in rows():
        if row["container"] == "ovmovie" or not row.get("exists") or not row.get("stock"):
            continue
        if (only and row["id"] not in only) or row["id"] in skip:
            continue
        p = clean_path(row)
        if not p.exists():
            continue
        text = p.read_text(errors="replace")
        if "ASM_" not in text:
            continue
        sites = sites_of(text)
        if sites:
            out.append((row, text, sites))
    return out


def run_sites(a):
    done = {(r["id"], r["in_sha"], r["site"]) for r in read_jsonl(SITES_OUT)}
    jobs = []
    for row, text, sites in targets(a):
        sh = sha_text(text)
        masked = scored_mask(text)
        for i in range(len(sites)):
            if (row["id"], sh, i) not in done:
                jobs.append((row, text, masked, sites, i, sh))
    print(f"pin_sites --sites: {len(jobs)} sites to measure ({len(done)} journalled)", flush=True)

    def one(job):
        row, text, masked, sites, i, sh = job
        rec = {"id": row["id"], "container": row["container"], "size": row["size"], "cfg": row["cfg"],
               "in_sha": sh, "nsites": len(sites)}
        try:
            rec.update(site_facts(text, masked, sites, i))
        except Exception as e:                      # a facts bug must not cost the measurement
            rec.update({"site": i, "macro": sites[i][1], "facts_err": repr(e)[:120]})
        v = score(row, erase(text, sites[i]))
        rec.update({k: v.get(k) for k in ("status", "exact", "total", "class", "secs")})
        if v.get("regions"):
            rec["nreg"] = len(v["regions"])
            rec["regions"] = compact(v["regions"])
        return rec

    t0, n = time.time(), 0
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(one, jobs):
            append_jsonl(SITES_OUT, rec)
            n += 1
            if n % 250 == 0:
                el = time.time() - t0
                print(f"{n}/{len(jobs)} {el:.0f}s eta {el / n * (len(jobs) - n):.0f}s", flush=True)
    print(f"done {n} in {time.time() - t0:.0f}s", flush=True)


def run_subsets(a):
    done = {(r["id"], r["in_sha"], tuple(r["s"])) for r in read_jsonl(SUBSETS_OUT)}
    jobs, per_row = [], {}
    for row, text, sites in targets(a):
        n = len(sites)
        if n < max(2, a.min_pins) or n > a.max_pins:
            continue
        sh = sha_text(text)
        per_row[row["id"]] = (row, text, sites, sh)
        for k in range(2, min(n, a.max_k or n) + 1):
            for sub in itertools.combinations(range(n), k):
                if (row["id"], sh, sub) not in done:
                    jobs.append((row, text, sites, sub, sh))
    print(f"pin_sites --subsets: {len(jobs)} subsets over {len(per_row)} rows ({len(done)} journalled)", flush=True)

    def one(job):
        row, text, sites, sub, sh = job
        v = score(row, erase_many(text, [sites[i] for i in sub]))
        rec = {"id": row["id"], "in_sha": sh, "n": len(sites), "s": list(sub),
               "macros": [sites[i][1] for i in sub]}
        rec.update({k: v.get(k) for k in ("status", "exact", "total", "class", "secs")})
        if v.get("regions"):
            rec["nreg"] = len(v["regions"])
            rec["regions"] = [[r["op"], r["t"][0], r["t"][1]] for r in v["regions"][:MAX_REGIONS]]
        return rec

    t0, n = time.time(), 0
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(one, jobs):
            append_jsonl(SUBSETS_OUT, rec)
            n += 1
            if n % 250 == 0:
                el = time.time() - t0
                print(f"{n}/{len(jobs)} {el:.0f}s eta {el / n * (len(jobs) - n):.0f}s", flush=True)
    print(f"done {n} in {time.time() - t0:.0f}s", flush=True)

    if not a.land_dir:
        return
    # the largest exact subset per row, measured at the row's CURRENT text, becomes a candidate
    best = {}
    for r in read_jsonl(SUBSETS_OUT):
        if not r.get("exact") or r["id"] not in per_row or r["in_sha"] != per_row[r["id"]][3]:
            continue
        if len(r["s"]) > len(best.get(r["id"], [])):
            best[r["id"]] = r["s"]
    out = Path(a.land_dir)
    for rid, sub in sorted(best.items()):
        row, text, sites, sh = per_row[rid]
        cand = erase_many(text, [sites[i] for i in sub], clean_notes=True)
        p = out / row["container"] / Path(row["c_path"]).name
        p.parent.mkdir(parents=True, exist_ok=True)
        p.write_text(cand)
        # the text the candidate was cut from: apply_candidates refuses it if the row has moved on
        p.with_name(p.name + ".base_sha").write_text(sh + "\n")
        print(f"candidate {rid}: {len(sub)} of {len(sites)} pins", flush=True)
    print(f"{len(best)} candidates in {out}", flush=True)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sites", action="store_true")
    ap.add_argument("--subsets", action="store_true")
    ap.add_argument("--groups", action="store_true", help="print the pin-group histogram")
    ap.add_argument("--max-pins", type=int, default=5)
    ap.add_argument("--min-pins", type=int, default=2)
    ap.add_argument("--max-k", type=int, help="largest subset to erase (2 = pairs only: the linkage "
                    "of a row with too many pins for every subset)")
    ap.add_argument("--workers", type=int, default=10)
    ap.add_argument("--only")
    ap.add_argument("--skip")
    ap.add_argument("--land-dir")
    a = ap.parse_args()
    if a.sites:
        run_sites(a)
    if a.subsets:
        run_subsets(a)
    if a.groups:
        run_groups(a)


if __name__ == "__main__":
    main()
