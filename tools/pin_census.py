#!/usr/bin/env python3
"""Pin census: for every ASM_* pin site, record what it is, where it sits, and what happens
to the retail bytes when it alone is erased (exact / breakage class).

    python3 tools/pin_census.py --sample 200 --workers 4 --out ledger/pins_sample.jsonl
    python3 tools/pin_census.py --all --workers 6 --out ledger/pins.jsonl      (resumable)
    python3 tools/pin_census.py --report ledger/pins.jsonl > docs/PIN_CENSUS.md

Erasure semantics (kind -> rewrite):
  stmt   `ASM_X(...);` statement line            -> line removed (inside a #define: token removed, '\\' kept)
  reg    `register T v ASM_REG("$r")`            -> `T v`
Only one site is erased per experiment, from the ORIGINAL pinned text, so each record measures
that pin's own necessity.  Greedy multi-site erasure is a separate transform (xform/pins).
"""
import argparse, collections, json, os, random, re, sys, tempfile, time
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path
from common import LEDGER, ROOT, rows, read_jsonl, append_jsonl, raw_path
from verify import verify

STMT_RE = re.compile(r"^([ \t]*)(ASM_(?!REG\b)[A-Z0-9_]+)\(([^;\n]*)\);[ \t]*(\\?)[ \t]*\n", re.M)
INLINE_STMT_RE = re.compile(r"(ASM_(?!REG\b)[A-Z0-9_]+)\(([^;\n]*)\);")
REG_RE = re.compile(r"\bregister\b([^;=\n]*?)\s+ASM_REG\(\"\$?([a-z0-9]+)\"\)")
CALL_RE = re.compile(r"\b(func_[0-9A-F]{8}|[A-Za-z_][A-Za-z0-9_]*)\s*\(")
REG_CLASS = {**{f"{n}": "v" for n in ("2", "3", "v0", "v1")}, **{f"{n}": "a" for n in ("4", "5", "6", "7", "a0", "a1", "a2", "a3")},
             **{f"{n}": "s" for n in ("16", "17", "18", "19", "20", "21", "22", "23", "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7")},
             **{f"{n}": "t" for n in ("8", "9", "10", "11", "12", "13", "14", "15", "24", "25", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7", "t8", "t9")},
             "30": "fp", "fp": "fp", "29": "sp", "sp": "sp", "31": "ra", "ra": "ra", "28": "gp", "gp": "gp", "1": "at", "at": "at"}

PP_RE = re.compile(r"^[ \t]*#[ \t]*(ifdef|ifndef|if|elif|else|endif)\b[ \t]*(.*?)[ \t]*(?:/[*/].*)?$")
NM_TRUE_RE = re.compile(r"^(?:NON_MATCHING|defined[ \t]*\(?[ \t]*NON_MATCHING[ \t]*\)?)$")
NM_FALSE_RE = re.compile(r"^![ \t]*(?:NON_MATCHING|defined[ \t]*\(?[ \t]*NON_MATCHING[ \t]*\)?)$")
HAS_PP_RE = re.compile(r"^[ \t]*#[ \t]*if", re.M)
CMT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
# An instruction written into a string (`__asm__("lui $2, ...")`, `"nop"`).  NOT an asm label
# (`extern void f(void) __asm__("func_8001672C");` - the noreturn tail spelling, 160 files), a
# `.set` page-base or a `#maspsx_*` marker: a label names a symbol, it emits nothing.  The older
# per-tool regex (`"[a-z]`) matched labels too, and t15/pin_lane refused 80 rows on it.
ASM_BODY_RE = re.compile(r'\b(?:__asm__|__asm|asm)\s*(?:__volatile__|volatile)?\s*\(\s*"(?:nop"|[a-z][a-z0-9.]*(?:[ \t;]|\\n))')
RAW_REG_ASM_RE = re.compile(r'\bregister\b[^;=\n]*\b(?:__asm__|asm)\s*\(\s*"\$')


def arm_labels(text):
    """One label per line: which build compiles it.

      'match'  only the byte-exact build: an `#ifndef NON_MATCHING` arm, the `#else` of an
               `#ifdef NON_MATCHING`
      'port'   only the -DNON_MATCHING port build - never scored against retail, and every ASM_*
               macro there expands to a no-op
      'dead'   neither (`#if 0`, or a port arm nested in a match arm)
      'both'   everything else, the directive lines included

    Every pin tool used to refuse a row outright when "NON_MATCHING" appeared anywhere in its text:
    189 pinned rows, 105 of them with every pin outside any such arm and 52 within 12 words of
    pin-free, were never searched by t15, t9 or a lane pack.  This is what they needed instead.
    """
    labels, stack = [], []           # per open #if: [side of the first arm, side of the current arm]
    flip = {"port": "match", "match": "port"}
    for ln in text.splitlines():
        m = PP_RE.match(ln)
        if m:
            d, cond = m.group(1), m.group(2).strip()
            if d in ("ifdef", "ifndef", "if"):
                if d == "ifdef":
                    side = "port" if cond == "NON_MATCHING" else None
                elif d == "ifndef":
                    side = "match" if cond == "NON_MATCHING" else None
                else:
                    side = ("port" if NM_TRUE_RE.match(cond) else "match" if NM_FALSE_RE.match(cond)
                            else "dead" if cond == "0" else None)
                stack.append([side, side])
            elif d in ("elif", "else") and stack:
                stack[-1][1] = flip.get(stack[-1][0])      # every later arm is the other build (or both)
            elif d == "endif" and stack:
                stack.pop()
            labels.append("both")
            continue
        sides = {f[1] for f in stack if f[1]}
        labels.append("dead" if "dead" in sides or sides >= {"port", "match"} else
                      "port" if "port" in sides else "match" if "match" in sides else "both")
    return labels


def unscored_text(text):
    """The code no byte gate ever compiles (the 'port' and 'dead' arms), comments dropped and
    whitespace squeezed.  A candidate that changes it edited something no verify can see: the
    byte-exact verdict says nothing about it, so the sweep and the lane lander refuse it."""
    if not HAS_PP_RE.search(text):
        return ""
    lines = text.splitlines()
    keep = [ln for ln, lab in zip(lines, arm_labels(text)) if lab in ("port", "dead")]
    return " ".join(CMT_RE.sub(" ", "\n".join(keep)).split())


def asm_blocker(text):
    """Why a row's pin-free text still carries hand-written scaffolding, or None."""
    if ASM_BODY_RE.search(text):
        return "inline asm body"
    if RAW_REG_ASM_RE.search(text):
        return "raw register asm binding"
    return None


_LINT = None
_PIN_STMT_RE = re.compile(r"\bASM_[A-Z0-9_]+\s*\([^;]*\)\s*;")
_DW0_OPEN_RE = re.compile(r"\bdo\s*\{")
_DW0_CLOSE_RE = re.compile(r"\}\s*while\s*\(\s*0\s*\)\s*;")


def _arm_view(text, want):
    """The code lines carrying one of the labels in `want`, directives and comments dropped."""
    lines = text.splitlines()
    labs = arm_labels(text) if HAS_PP_RE.search(text) else ["both"] * len(lines)
    keep = [ln for ln, lab in zip(lines, labs) if lab in want and not PP_RE.match(ln)]
    return CMT_RE.sub(" ", "\n".join(keep))


def port_view(text):
    """What the -DNON_MATCHING port build compiles, for comparison only: whitespace squeezed, the
    no-op ASM_* statements and the `do { ... } while (0)` barrier wrappers dropped - neither
    means anything to the port build."""
    s = _PIN_STMT_RE.sub(" ", _arm_view(text, ("port", "both")))
    s = _DW0_CLOSE_RE.sub(" ", _DW0_OPEN_RE.sub(" ", s))
    return " ".join(s.split())


def landing_refusal(new, cur, relpath):
    """Why a byte-exact candidate must still not land, or None.

    Byte equality proves only the code the matching build compiles.  So a candidate is refused
    when it edits code no byte gate compiles (`unscored_text`), or when the -DNON_MATCHING port
    build's front end rejects it (tools/gate/portability_lint.py, 16 ms, self-grandfathering: a
    row whose landed text already fails does not block its own candidate).

    One exception, an ARM COLLAPSE: a candidate that drops an `#ifdef NON_MATCHING` split because
    one spelling turned out byte-exact for the matching build (town/func_8050E100, 2026-09-11: the
    port arm's `D_80017618 = func_80017560;` was retail's source all along).  Its port arm text
    changes, but what the port build compiles does not - so it lands when `port_view` is identical
    (barriers and no-op pins aside) and no `#if 0` text changed; the matching side is proven by the
    byte gate, the port side by that identity plus the port front end below."""
    global _LINT
    if unscored_text(new) != unscored_text(cur):
        if port_view(new) != port_view(cur) or _arm_view(new, ("dead",)).split() != _arm_view(cur, ("dead",)).split():
            return "edits a NON_MATCHING/#if 0 arm that no byte gate compiles"
    if _LINT is None:
        import importlib.util
        spec = importlib.util.spec_from_file_location("portability_lint", ROOT / "tools/gate/portability_lint.py")
        mod = importlib.util.module_from_spec(spec)
        spec.loader.exec_module(mod)
        _LINT = mod                    # bound only once complete: a racing thread sees None or all
    errs = _LINT.port_compile_refusals(new, relpath, str(ROOT))
    return errs[0][:300] if errs else None


def sites_of(text):
    """Return [(kind, macro, arg, start, end, line_no, replacement_text)] for every LIVE pin: a pin in
    a 'port'/'dead' arm compiles to nothing in either build and scaffolds nothing."""
    out = _all_sites(text)
    if out and HAS_PP_RE.search(text):
        labels = arm_labels(text)
        out = [s for s in out if s[5] > len(labels) or labels[s[5] - 1] not in ("port", "dead")]
    return out


def _all_sites(text):
    out = []
    for m in STMT_RE.finditer(text):
        indent, macro, arg, bs = m.group(1), m.group(2), m.group(3), m.group(4)
        line_no = text.count("\n", 0, m.start()) + 1
        # a statement line inside a #define ends with a backslash: keep the continuation
        repl = (indent + "\\\n") if bs else ""
        out.append(("stmt", macro, arg.strip(), m.start(), m.end(), line_no, repl))
    covered = [(s[3], s[4]) for s in out]
    for m in INLINE_STMT_RE.finditer(text):           # pins sharing a line with other code
        if any(a <= m.start() < b for a, b in covered): continue
        line_no = text.count("\n", 0, m.start()) + 1
        out.append(("stmt", m.group(1), m.group(2).strip(), m.start(), m.end(), line_no, ""))
    for m in REG_RE.finditer(text):
        line_no = text.count("\n", 0, m.start()) + 1
        out.append(("reg", "ASM_REG", m.group(2), m.start(), m.end(), line_no, m.group(1).strip()))
    return sorted(out, key=lambda s: s[3])

def context_of(text, start, end, line_no):
    lines = text.splitlines()
    i = line_no - 1
    line = lines[i] if i < len(lines) else ""
    def near(j):
        return lines[j].strip() if 0 <= j < len(lines) else ""
    prev, nxt = near(i - 1), near(i + 1)
    in_def = line.lstrip().startswith("#define") or line.rstrip().endswith("\\") or (i > 0 and lines[i-1].rstrip().endswith("\\"))
    # find enclosing function name: last def line above
    fn = None
    for j in range(i, -1, -1):
        m = re.match(r"^[ \t]*[A-Za-z_][A-Za-z0-9_ \*]*?\b\**(func_[0-9A-F]{8}|[a-z_][a-z0-9_]*)\s*\(", lines[j])
        if m and not lines[j].startswith((" ", "\t")) and not lines[j].startswith("extern"): fn = m.group(1); break
    depth = 0
    for j in range(0, i):
        depth += lines[j].count("{") - lines[j].count("}")
    return {"in_macro_def": in_def, "prev_call": bool(re.search(r"\bfunc_[0-9A-F]{8}\s*\(", prev)) or bool(re.search(r"\b[a-z_][a-z0-9_]*\s*\([^;]*\);", prev)),
            "next_call": bool(re.search(r"\bfunc_[0-9A-F]{8}\s*\(", nxt)),
            "next_return": nxt.startswith("return") or nxt == "}", "prev_label": bool(re.match(r"^[A-Za-z_][A-Za-z0-9_]*:\s*$", prev)),
            "prev_loop": bool(re.match(r"^(for|while|do)\b", prev)), "depth": depth, "line_frac": round(line_no / max(len(lines), 1), 2),
            "nonmatching_file": "NON_MATCHING" in text, "enclosing": fn}

def erase(text, site):
    kind, macro, arg, start, end, line_no, repl = site
    return text[:start] + repl + text[end:]

def one(job):
    row, idx = job
    text = raw_path(row).read_text(errors="replace")
    sites = sites_of(text)
    if idx >= len(sites):
        return None
    site = sites[idx]
    kind, macro, arg, start, end, line_no, repl = site
    rec = {"id": row["id"], "container": row["container"], "size": row["size"], "cfg": row["cfg"], "site": idx, "nsites": len(sites),
           "kind": kind, "macro": macro, "arg": arg[:60], "reg": arg if kind == "reg" else None,
           "reg_class": REG_CLASS.get(arg) if kind == "reg" else None, "line": line_no}
    rec.update(context_of(text, start, end, line_no))
    cand = erase(text, site)
    with tempfile.TemporaryDirectory() as td:
        p = Path(td) / Path(row["c_path"]).name
        p.write_text(cand)
        v = verify(row, p)
    rec.update({"exact": v.get("exact"), "status": v.get("status"), "class": v.get("class"), "subs": v.get("subs"), "indels": v.get("indels"),
                "total": v.get("total"), "dwords": (v.get("gen_words") or 0) - (v.get("tgt_words") or 0) if v.get("gen_words") is not None else None,
                "signals": (v.get("signals") or [])[:3], "secs": v.get("secs"), "err": (v.get("err") or None)})
    return rec

def report(path):
    recs = [r for r in read_jsonl(path) if r]
    def pct(a, b): return f"{100*a/b:.0f}%" if b else "-"
    def table(title, keyf, min_n=1):
        g = collections.defaultdict(list)
        for r in recs: g[keyf(r)].append(r)
        print(f"\n### {title}\n\n| key | sites | free | build-fail | top breakage classes |\n|---|---:|---:|---:|---|")
        for k, v in sorted(g.items(), key=lambda kv: -len(kv[1])):
            if len(v) < min_n: continue
            free = sum(1 for r in v if r["exact"]); bf = sum(1 for r in v if r["status"] == "failed")
            cls = collections.Counter(r["class"] for r in v if not r["exact"] and r["status"] != "failed")
            top = ", ".join(f"{c} {n}" for c, n in cls.most_common(4))
            print(f"| {k} | {len(v)} | {free} ({pct(free, len(v))}) | {bf} | {top} |")
    n = len(recs); free = sum(1 for r in recs if r["exact"])
    rows_ = {r["id"] for r in recs}
    print(f"# Pin census\n\nsites={n} rows={len(rows_)} free={free} ({pct(free, n)}) build-fail={sum(1 for r in recs if r['status']=='failed')}")
    table("by macro", lambda r: r["macro"])
    table("by ASM_REG register class", lambda r: f"$" + (r["reg"] or "") + " (" + (r["reg_class"] or "?") + ")", min_n=3) if any(r["kind"] == "reg" for r in recs) else None
    table("by container", lambda r: r["container"])
    table("by compiler cell", lambda r: r["cfg"].split()[0])
    table("by context (macro,in_def,prev_call,next_call,next_return)", lambda r: f"{r['macro']} def={int(r['in_macro_def'])} pc={int(r['prev_call'])} nc={int(r['next_call'])} nr={int(r['next_return'])}", min_n=8)
    table("breakage class x macro (non-free only)", lambda r: f"{r['class']} <- {r['macro']}" if not r["exact"] else "free", min_n=5)
    table("delta words when broken", lambda r: ("free" if r["exact"] else f"dwords={r['dwords']:+d}" if r["dwords"] is not None else "n/a"), min_n=5)

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--sample", type=int); ap.add_argument("--all", action="store_true"); ap.add_argument("--seed", type=int, default=1)
    ap.add_argument("--workers", type=int, default=4); ap.add_argument("--out", default="ledger/pins.jsonl"); ap.add_argument("--report")
    ap.add_argument("--container"); ap.add_argument("--max-sites", type=int, default=40)
    a = ap.parse_args()
    if a.report:
        report(a.report); return
    rs = [r for r in rows() if r["exists"] and r["stock"] and (not a.container or r["container"] == a.container)]
    cen = {c["id"]: c for c in read_jsonl(LEDGER / "census.jsonl")}
    pinned = [r for r in rs if cen.get(r["id"], {}).get("pin_total", 0) > 0]
    if a.sample:
        random.seed(a.seed)
        # stratify: proportional to container, but cap huge files by --max-sites
        pinned = random.sample(pinned, min(a.sample, len(pinned)))
    jobs = []
    for r in pinned:
        n = len(sites_of(raw_path(r).read_text(errors="replace")))
        jobs += [(r, i) for i in range(min(n, a.max_sites))]
    out = ROOT / a.out
    done = {(x["id"], x["site"]) for x in read_jsonl(out) if x}
    jobs = [j for j in jobs if (j[0]["id"], j[1]) not in done]
    print(f"rows={len(pinned)} sites={len(jobs)} (done already {len(done)}) workers={a.workers}", flush=True)
    t0 = time.time(); n = 0
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(one, jobs):
            if rec is None: continue
            append_jsonl(out, rec); n += 1
            if n % 100 == 0:
                el = time.time() - t0; print(f"{n}/{len(jobs)} {el:.0f}s eta {el/n*(len(jobs)-n):.0f}s", flush=True)
    print(f"done {n} in {time.time()-t0:.0f}s")

if __name__ == "__main__":
    main()
