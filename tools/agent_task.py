#!/usr/bin/env python3
"""Layer-2 agent loop: one row -> one model call -> verify -> accept or refuse.  Bake-off harness.

    python3 tools/agent_task.py --model gpt-6-astra --effort high --rows main/func_X,town/func_Y
    python3 tools/agent_task.py --model gpt-5.6-luna --effort xhigh --sample 10 --seed 3

The model gets the current clean C for the row, the task (readable locals, a one-line summary,
control-flow simplification only where it stays exact), the verify command it may run, and must
write the result file.  The harness verifies independently; accepted output goes to
refine/<container>/<name>.c and the journal ledger/agents/<model>.jsonl records outcome, wall
time and token usage from the codex session log.
"""
import argparse, json, os, random, re, shutil, subprocess, sys, tempfile, time
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, UP, LEDGER, rows, read_jsonl, append_jsonl, sha_text
from verify import verify

INCLUDE = ROOT / "include"
COMMIT = False
PROMPT = """You are cleaning up one function of a byte-exact PlayStation decompilation (Azure Dreams, GCC 2.7.2/2.8.1 era).
The file below already compiles to the retail bytes. Make it READABLE without changing the machine code:
- rename m2c locals (temp_v0, arg0, sp10, var_a1 ...) to names that say what they hold; keep `func_XXXXXXXX`/`D_XXXXXXXX` symbols unchanged
- add ONE line summary comment above the function (what it does), as a /* C comment */ (never //), no chatter, no line-by-line narration
- local names in lowercase_snake_case (project style); keep them short and specific
- you MAY simplify control flow (goto -> loops/if) and fold trivial temps ONLY if the bytes stay identical; when unsure leave the shape
- keep every ASM_* pin macro, every extern declaration and every struct as they are unless you prove the change is byte-exact
- do NOT rename struct members (`unk_XX` stay: they are named later from evidence across all users); do not add or remove members
Verify with:  {verify}
It prints JSON; "exact": true is required. You may run it as often as you like. Write the final file to {out} (overwrite). Reply with one line: DONE <n_verify_runs> or GAVEUP <reason>.

--- {name} ---
{src}
"""

def run_codex(model, effort, prompt, workdir, timeout):
    cmd = ["codex", "exec", "-C", str(workdir), "--dangerously-bypass-approvals-and-sandbox", "--skip-git-repo-check",
           "-m", model, "-c", f'model_reasoning_effort="{effort}"', "-o", str(workdir / "last_message.txt"), "-"]
    t0 = time.time()
    try:
        r = subprocess.run(cmd, input=prompt, capture_output=True, text=True, timeout=timeout, cwd=workdir)
        rc = r.returncode; err = (r.stderr or "")[-400:]
    except subprocess.TimeoutExpired:
        rc = -1; err = "timeout"
    secs = round(time.time() - t0, 1)
    usage = {}
    # codex records the rollout under ~/.codex/sessions/YYYY/MM/DD/*.jsonl with the cwd and a
    # running total_token_usage; the work dir is unique per row so cwd identifies the session
    try:
        day = time.strftime("%Y/%m/%d", time.gmtime())
        sess_dir = Path.home() / ".codex/sessions" / day
        for f in sorted(sess_dir.glob("*.jsonl"), key=lambda p: p.stat().st_mtime, reverse=True)[:40]:
            txt = f.read_text(errors="replace")
            if f'"cwd":"{workdir}"' in txt or f'"cwd": "{workdir}"' in txt:
                m = re.findall(r'"total_token_usage":\{([^}]*)\}', txt)
                if m:
                    usage = {k: int(v) for k, v in re.findall(r'"(\w+)":(\d+)', m[-1])}
                usage["session"] = f.name
                break
    except Exception as e:
        usage = {"error": str(e)[:80]}
    return rc, secs, usage, err

def one(row, model, effort, timeout):
    name = Path(row["c_path"]).name
    cp = ROOT / "src" / row["container"] / name
    src = (cp if cp.exists() else UP / row["c_path"]).read_text(errors="replace")
    work = Path(tempfile.mkdtemp(prefix="agent_", dir=str(ROOT / "work")))
    out = work / name; out.write_text(src)
    verify_cmd = f"python3 {ROOT}/tools/verify.py {row['id']} {out} --include-root {INCLUDE}"
    prompt = PROMPT.format(verify=verify_cmd, out=out, name=name, src=src)
    rc, secs, usage, err = run_codex(model, effort, prompt, work, timeout)
    new = out.read_text(errors="replace") if out.exists() else src
    reply = (work / "last_message.txt").read_text(errors="replace").strip()[-200:] if (work / "last_message.txt").exists() else ""
    rec = {"id": row["id"], "model": model, "effort": effort, "rc": rc, "secs": secs, "usage": usage, "reply": reply,
           "changed": new != src, "in_sha": sha_text(src), "lines_in": src.count("\n"), "lines_out": new.count("\n")}
    if new == src:
        rec["outcome"] = "unchanged"
    else:
        v = verify(row, out, include_root=INCLUDE)
        rec.update({"exact": v.get("exact"), "class": v.get("class"), "total": v.get("total")})
        if v.get("exact"):
            keep = LEDGER / "agents" / "out" / f"{model}-{effort}" / row["container"]; keep.mkdir(parents=True, exist_ok=True); (keep / name).write_text(new)
            if COMMIT:
                dst = ROOT / "refine" / row["container"] / name; dst.parent.mkdir(parents=True, exist_ok=True); dst.write_text(new)
            rec["outcome"] = "accepted"; rec["out_sha"] = sha_text(new)
            # readability proxies
            rec["m2c_locals_left"] = len(set(re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+)\b", new)))
            rec["m2c_locals_in"] = len(set(re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+)\b", src)))
            rec["gotos_in"] = len(re.findall(r"\bgoto\b", src)); rec["gotos_out"] = len(re.findall(r"\bgoto\b", new))
        else:
            rec["outcome"] = "rejected"
    shutil.rmtree(work, ignore_errors=True)
    return rec

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--model", required=True); ap.add_argument("--effort", default="high"); ap.add_argument("--rows")
    ap.add_argument("--sample", type=int); ap.add_argument("--seed", type=int, default=1); ap.add_argument("--timeout", type=int, default=900)
    ap.add_argument("--min-size", type=int, default=100); ap.add_argument("--max-size", type=int, default=600)
    ap.add_argument("--commit", action="store_true", help="also write accepted output to refine/ (campaign mode)")
    ap.add_argument("--with-gotos", action="store_true", help="sample only rows whose current text has gotos")
    ap.add_argument("--all", action="store_true", help="every eligible row not yet journalled (campaign mode)")
    ap.add_argument("--workers", type=int, default=1); ap.add_argument("--limit", type=int)
    ap.add_argument("--container")
    ap.add_argument("--tag", default="", help="journal name suffix")
    a = ap.parse_args()
    global COMMIT; COMMIT = a.commit
    lv = {x["id"]: x for x in read_jsonl(LEDGER / "levels.jsonl")}
    rs = [r for r in rows() if lv.get(r["id"], {}).get("level", -1) >= 1 and a.min_size <= r["size"] <= a.max_size]
    if a.with_gotos:
        def has_goto(r):
            cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            t = (cp if cp.exists() else UP / r["c_path"]).read_text(errors="replace")
            return bool(re.search(r"\bgoto\b", t))
        rs = [r for r in rs if has_goto(r)]
    if a.rows: keep = set(a.rows.split(",")); rs = [r for r in rows() if r["id"] in keep]
    elif a.sample: random.seed(a.seed); rs = random.sample(rs, min(a.sample, len(rs)))
    (LEDGER / "agents").mkdir(exist_ok=True); journal = LEDGER / "agents" / (f"{a.model}-{a.effort}" + (f"-{a.tag}" if a.tag else "") + ".jsonl")
    (ROOT / "work").mkdir(exist_ok=True)
    if a.container: rs = [r for r in rs if r["container"] == a.container]
    if a.all:
        done = {j["id"] for j in read_jsonl(journal) if j.get("outcome") in ("accepted", "unchanged")}
        rs = [r for r in rs if r["id"] not in done]
        rs.sort(key=lambda r: r["size"])
    if a.limit: rs = rs[:a.limit]
    print(f"{len(rs)} rows, {a.workers} workers, model {a.model} {a.effort}", flush=True)
    from concurrent.futures import ThreadPoolExecutor
    def work(r):
        rec = one(r, a.model, a.effort, a.timeout); rec["at"] = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
        return rec
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        for rec in ex.map(work, rs):
            append_jsonl(journal, rec); print(json.dumps({k: rec.get(k) for k in ("id", "outcome", "secs", "class", "total", "m2c_locals_in", "m2c_locals_left", "gotos_in", "gotos_out", "reply")}), flush=True)

if __name__ == "__main__":
    main()
