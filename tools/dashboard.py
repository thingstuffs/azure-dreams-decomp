#!/usr/bin/env python3
"""Render the campaign dashboard (dashboard/index.html) from the ledger and journals.

    python3 tools/dashboard.py            # write once
    tools/dashboard_serve.sh              # regenerate every 60 s and serve on :8002
"""
import collections, html, json, os, re, subprocess, sys, time
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, PARKED_CONTAINERS, rows, read_jsonl, PIN

OUT = ROOT / "dashboard"; OUT.mkdir(exist_ok=True)
CONTAINERS = ("slus", "main", "town", "dungeon", "ovmovie")
LEVEL_NAMES = {-1: "excluded (non-stock at pin)", 0: "L0 verified byte-exact", 1: "L1 no boilerplate / dead pins", 2: "L2 typed structs, no raw offsets", 3: "L3 named locals (refined)", 4: "L4 modules + shared headers", 5: "L5 pin-free or documented"}

def fmt(n): return f"{n:,}"
def pct(a, b): return f"{100*a/b:.1f}%" if b else "-"

def sh(cmd):
    try: return subprocess.run(cmd, shell=True, capture_output=True, text=True, timeout=20).stdout
    except Exception as e: return str(e)

def running():
    out = []
    ps = sh("ps -eo pid,args")
    for line in ps.splitlines():
        for key, label in (("tools/agent_task.py", "agent campaign"), ("tools/sweep.py", "sweep"), ("tools/build/gate_all.py", "container gate"), ("overlay_local_gate.py", "window gate"), ("tools/reverify.py", "re-verify"), ("tools/pin_census.py", "pin census"), ("verify.py --baseline", "baseline")):
            if key in line and "grep" not in line:
                pid, *args = line.split(None, 1)
                try:
                    secs = int(time.time() - os.stat(f"/proc/{pid}").st_mtime)     # ps etime is unreliable on this host
                    elapsed = f"{secs//3600}h{(secs%3600)//60:02d}m"
                except OSError:
                    elapsed = "?"
                a = " ".join(args); m = re.search(r"--model (\S+).*?--limit (\d+)", a)
                out.append({"what": label, "pid": pid, "elapsed": elapsed, "args": (m.group(0) if m else a[-80:])})
    return out

def main():
    rs = rows(); by = {r["id"]: r for r in rs}
    live = [r for r in rs if r["container"] not in PARKED_CONTAINERS]
    lv = {x["id"]: x for x in read_jsonl(LEDGER / "levels.jsonl")}
    tot_b = sum(r["size"] for r in live); tot_n = len(live)
    # ---- levels
    L = collections.defaultdict(lambda: [0, 0]); Lc = collections.defaultdict(lambda: collections.defaultdict(lambda: [0, 0]))
    for r in live:
        l = lv.get(r["id"], {}).get("level", -1); L[l][0] += 1; L[l][1] += r["size"]; Lc[r["container"]][l][0] += 1; Lc[r["container"]][l][1] += r["size"]
    cum = {}
    for l in range(0, 6):
        cum[l] = (sum(L[k][0] for k in L if k >= l), sum(L[k][1] for k in L if k >= l))
    # ---- gate
    gate = {}
    for j in read_jsonl(LEDGER / "gate.jsonl"): gate[j["window"]] = j
    gc = collections.Counter((j["container"].replace(".overlay", ""), j["result"]) for j in gate.values())
    gate_kinds = collections.Counter()
    for j in gate.values():
        if j["result"] == "MATCH": continue
        d = j["detail"]
        gate_kinds["retired bridge compiler cell (pin bump)" if "No such file" in d and "compilers/" in d else "assembler dial signature (pin bump)" if "signature mismatch" in d else "fails from raw too (upstream drift, pin bump)" if j["result"] == "NO MATCH" else "other: " + d[:60]] += 1
    # ---- agents
    ag = collections.Counter(); ag_tok = 0; ag_last = []; ag_cont = collections.Counter()
    for p in sorted((LEDGER / "agents").glob("*campaign*.jsonl")):
        for j in read_jsonl(p):
            ag[j["outcome"]] += 1; ag_tok += (j.get("usage") or {}).get("output_tokens", 0); ag_last.append(j)
            if j["outcome"] == "accepted": ag_cont[j["id"].split("/")[0]] += 1
    ag_last = ag_last[-8:]
    # ---- remaining work
    census = {c["id"]: c for c in read_jsonl(LEDGER / "census.jsonl")}
    def cur_text(r):
        p = ROOT / "src" / r["container"] / Path(r["c_path"]).name
        return p.read_text(errors="replace") if p.exists() else ""
    off_files = off_sites = pin_rows = pin_sites = 0
    for r in live:
        t = cur_text(r)
        n = len(re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in t.splitlines() if not l.lstrip().startswith("#"))))
        if n: off_files += 1; off_sites += n
        k = len(re.findall(r"\bASM_[A-Z0-9_]+\(", t))
        if k: pin_rows += 1; pin_sites += k
    windowless = sum(1 for r in live if r["kind"] == "overlay" and not r.get("gate_config"))
    nonstock = sum(1 for r in live if not r["stock"])
    drift = [b for b in read_jsonl(LEDGER / "reverify.jsonl") if not (b["exact"] or (b["status"] == "ok" and b["exact"] is None))]
    # ---- html
    now = time.strftime("%Y-%m-%d %H:%M:%S UTC", time.gmtime())
    H = [f"""<!doctype html><html><head><meta charset="utf-8"><meta http-equiv="refresh" content="60"><meta name="viewport" content="width=device-width, initial-scale=1"><title>azure-clean</title>
<style>
:root{{color-scheme:dark}} body{{font:15px/1.5 system-ui,-apple-system,sans-serif;margin:0;padding:16px;color:#d6d6d6;background:#121417;max-width:1100px}}
h1{{margin:0 0 4px;font-size:22px;color:#fff}} h2{{margin:26px 0 8px;font-size:16px;color:#fff;border-bottom:1px solid #2c3136;padding-bottom:4px}}
.tw{{overflow-x:auto;-webkit-overflow-scrolling:touch}} table{{border-collapse:collapse;margin:6px 0;min-width:100%}} td,th{{padding:5px 9px;border-bottom:1px solid #23272c;text-align:right;white-space:nowrap}}
th{{background:#1b1f24;color:#aab}} td:first-child,th:first-child{{text-align:left}} tr:nth-child(even) td{{background:#161a1e}}
.kpis{{display:flex;flex-wrap:wrap;gap:8px 22px;margin:10px 0 4px}} .kpi b{{font-size:24px;color:#fff;font-weight:600}} .kpi span{{display:block;color:#8a929c;font-size:12px}}
.bar{{height:9px;background:#2a2f35;border-radius:5px;overflow:hidden;width:min(420px,45vw)}} .bar i{{display:block;height:100%;background:#3ba776}}
.ok{{color:#4cc38a}} .bad{{color:#e5484d}} .muted{{color:#8a929c}} code{{background:#1f2429;color:#c9d1d9;padding:1px 5px;border-radius:3px;font-size:13px}}
pre{{background:#1b1f24;color:#c9d1d9;padding:10px;border-radius:6px;overflow-x:auto;font-size:12.5px}} ul{{padding-left:20px}} li{{margin:4px 0}} a{{color:#6cb6ff}}
@media (max-width:640px){{body{{padding:10px;font-size:14px}} .kpi b{{font-size:20px}} td,th{{padding:4px 6px}} .bar{{width:38vw}}}}
</style></head><body>
<h1>azure-clean</h1><div class="muted">pin <code>{PIN}</code> · generated {now} · refreshes every 60 s · ovmovie parked (listed, not counted)</div>"""]
    H.append('<div class="kpis">' + "".join(f'<div class="kpi"><b>{v}</b><span>{k}</span></div>' for k, v in (
        ("functions (rows)", fmt(tot_n)), ("bytes", fmt(tot_b)), ("at ≥ L2", pct(cum[2][1], tot_b)), ("at ≥ L3", pct(cum[3][1], tot_b)),
        ("windows byte-identical", f"{sum(v for (c, r), v in gc.items() if r == 'MATCH')} / {len(gate)}"), ("agent rows accepted", fmt(ag["accepted"])))) + '</div>')
    H.append("<h2>Cleanliness levels (bytes at or above)</h2><table><tr><th>level</th><th>rows</th><th>bytes</th><th>% bytes</th><th></th></tr>")
    for l in range(0, 6):
        n, b = cum[l]; H.append(f"<tr><td>{LEVEL_NAMES[l]}</td><td>{fmt(n)}</td><td>{fmt(b)}</td><td>{pct(b, tot_b)}</td><td><div class=bar><i style='width:{100*b/max(tot_b,1):.1f}%'></i></div></td></tr>")
    H.append(f"<tr><td class=muted>{LEVEL_NAMES[-1]}</td><td>{fmt(L[-1][0])}</td><td>{fmt(L[-1][1])}</td><td>{pct(L[-1][1], tot_b)}</td><td></td></tr></table>")
    H.append("<table><tr><th>container</th><th>rows</th><th>bytes</th>" + "".join(f"<th>≥L{l}</th>" for l in range(1, 6)) + "</tr>")
    for c in CONTAINERS:
        sel = [r for r in rs if r["container"] == c]; b = sum(r["size"] for r in sel)
        cells = "".join(f"<td>{pct(sum(Lc[c][k][1] for k in Lc[c] if k >= l), b)}</td>" for l in range(1, 6)) if c not in PARKED_CONTAINERS else "<td colspan=5 class=muted>parked</td>"
        H.append(f"<tr><td>{c}</td><td>{fmt(len(sel))}</td><td>{fmt(b)}</td>{cells}</tr>")
    H.append("</table>")
    # running
    H.append("<h2>Running now</h2>")
    run = running()
    H.append("<table><tr><th>what</th><th>pid</th><th>elapsed</th><th>args</th></tr>" + "".join(f"<tr><td>{html.escape(x['what'])}</td><td>{x['pid']}</td><td>{x['elapsed']}</td><td style='text-align:left'><code>{html.escape(x['args'])}</code></td></tr>" for x in run) + "</table>" if run else "<div class=muted>nothing running</div>")
    # agents
    H.append(f"<h2>Agent campaign (Layer 2, Astra)</h2><div>accepted <b>{fmt(ag['accepted'])}</b> · rejected {ag['rejected']} · quota stops {ag['quota']} · unchanged {ag['unchanged']} · output tokens {fmt(ag_tok)} · per container: " + ", ".join(f"{k} {v}" for k, v in ag_cont.most_common()) + "</div>")
    H.append("<table><tr><th>last rows</th><th>outcome</th><th>secs</th><th>locals</th></tr>" + "".join(f"<tr><td>{j['id']}</td><td class={'ok' if j['outcome']=='accepted' else 'bad'}>{j['outcome']}</td><td>{j.get('secs')}</td><td>{j.get('m2c_locals_in')}→{j.get('m2c_locals_left')}</td></tr>" for j in reversed(ag_last)) + "</table>")
    # gate
    H.append("<h2>Container gate (latest verdict per window)</h2><table><tr><th>container</th><th>MATCH</th><th>ERROR</th><th>NO MATCH</th></tr>")
    for c in ("town", "main", "dungeon", "dungeon_engine", "ovmovie"):
        H.append(f"<tr><td>{c}</td><td class=ok>{gc[(c,'MATCH')]}</td><td>{gc[(c,'ERROR')]}</td><td class={'bad' if gc[(c,'NO MATCH')] else ''}>{gc[(c,'NO MATCH')]}</td></tr>")
    H.append("</table><div>not green: " + ("; ".join(f"{v} × {html.escape(k)}" for k, v in gate_kinds.most_common()) or "none") + "</div>")
    # remaining work
    H.append("<h2>Remaining work and known issues</h2><ul>")
    for line in (
        f"raw offset access still in <b>{off_files}</b> functions / {fmt(off_sites)} sites (T4 refusals: search-failed shapes in the largest dungeon functions, unparsed struct-typed pointers)",
        f"pins surviving in <b>{pin_rows}</b> functions / {fmt(pin_sites)} sites, each annotated with its measured class; classes and alternatives in docs/PIN_CENSUS.md",
        f"<b>{len(drift)}</b> rows and the gate's non-green windows are upstream drift at the pin (retired bridge cells, assembler change); resolve at the <b>pin bump</b> once the bridge lane is at zero",
        f"{windowless} rows have no gate window; {nonstock} rows are non-stock at the pin (become stock at the pin bump)",
        "T3a (epilogue label-as-call → return) retired: every target is a resident shared tail; needs a linked-gate-verified treatment later",
        "Layer 3 next: shared headers from docs/STRUCT_CENSUS.md (record classes by provenance), then modules and names (L4), pin documentation complete (L5)",
        "swap-over checklist: docs/SWAPOVER.md (disc round-trip script, whole-container link, 17 windowless rows, maspsx name tables)",
        "ovmovie parked by the owner (movie playback exists elsewhere); listed, not counted"):
        H.append(f"<li>{line}</li>")
    H.append("</ul>")
    # commits
    H.append("<h2>Recent commits</h2><pre>" + html.escape(sh("git -C " + str(ROOT) + " log --format='%h %ad %s' --date=format:%H:%M -10")) + "</pre>")
    H.append("</body></html>")
    page = "\n".join(H).replace("<table>", '<div class="tw"><table>').replace("</table>", "</table></div>")
    (OUT / "index.html").write_text(page)
    print(f"dashboard written: {OUT/'index.html'} ({tot_n} rows, ≥L2 {pct(cum[2][1], tot_b)}, gate MATCH {sum(v for (c, r), v in gc.items() if r == 'MATCH')}/{len(gate)}, running {len(run)})")

if __name__ == "__main__":
    main()
