#!/usr/bin/env python3
"""Layer-2 agent loop: one row -> one model call -> verify -> accept or refuse.  Bake-off harness.

    python3 tools/agent_task.py --model gpt-6-astra --effort high --rows main/func_X,town/func_Y
    python3 tools/agent_task.py --model gpt-5.6-luna --effort xhigh --sample 10 --seed 3

The model gets the current clean C for the row, the task (readable locals, a one-line summary,
control-flow simplification only where it stays exact), the verify command it may run, and must
write the result file.  The harness verifies independently; accepted output is kept under
ledger/agents/out/<model>/ and, with --commit, landed into src/<container>/<name>.c through
tools/promote.py (journal ledger/promotions.jsonl); ledger/agents/<model>.jsonl records outcome,
wall time and token usage from the codex session log.
"""
import argparse, json, os, random, re, shutil, subprocess, sys, tempfile, time
from pathlib import Path
sys.path.insert(0, str(Path(__file__).resolve().parent))
from common import ROOT, LEDGER, rows, read_jsonl, append_jsonl, sha_text, raw_path
from verify import verify

INCLUDE = ROOT / "include"
COMMIT = False
PROMPT = """You are cleaning up one function of a byte-exact PlayStation decompilation (Azure Dreams, GCC 2.7.2/2.8.1 era).
The file below already compiles to the retail bytes. Make it READABLE without changing the machine code:
- rename m2c locals (temp_v0, arg0, sp10, var_a1 ...) to names that say what they hold; keep `func_XXXXXXXX`/`D_XXXXXXXX` symbols unchanged
- add ONE line summary comment above the function (what it does), as a /* C comment */ (never //), no chatter, no line-by-line narration
- local names in lowercase_snake_case (project style); keep them short and specific
- you MAY simplify control flow (goto -> loops/if) and fold trivial temps ONLY if the bytes stay identical; when unsure leave the shape
- SCAFFOLDING: every ASM_* pin macro, every maspsx marker (ASM_TAILSLOT_PIN/ASM_PAGEBASE_PIN/ASM_JALDELAY_PIN) and every pseudo-call to a noreturn tail label (`extern void func_X(void) __attribute__((noreturn)); func_X();` standing for a jump inside this function) is debt: it stands for a source shape nobody has found yet. For each one, TRY to remove it — delete the pin and re-verify; turn a mid-row tail pseudo-call into if/else that rejoins at the shared tail; give a zero-argument pass-through call its real arguments — and keep the removal only when verify says "exact": true. Never leave a pin out on a guess; a removal that costs bytes goes back. Report how many you removed in your DONE line: DONE <n_verify_runs> pins:<before>-><after> sites:<before>-><after>
- keep every extern declaration and every struct as they are unless you prove the change is byte-exact
- do NOT rename struct members (`unk_XX` stay: they are named later from evidence across all users); do not add or remove members
Verify with:  {verify}
It prints JSON; "exact": true is required. You may run it as often as you like. Before you reply DONE, run it ONCE MORE with `--gate` appended: that proves the file through the retail window (the proof of record; slower). If it reports "gate": "NO MATCH", the last change respelled a jump or tail call in a way the window rejects (this row may be linked at a different address than the isolated check assumes): undo that change, keep the pinned spelling, and re-verify. Write the final file to {out} (overwrite). Reply with one line: DONE <n_verify_runs> or GAVEUP <reason>.

{evidence}--- {name} ---
{src}
"""

PROMPT_READABILITY = """You are cleaning up functions of a byte-exact PlayStation decompilation (Azure Dreams, GCC 2.7.2/2.8.1 era).
Each file below already compiles to the retail bytes. Make it READABLE without changing the machine code, and do ONLY this:
- rename m2c locals (temp_v0, arg0, sp10, var_a1 ...) to names that say what they hold; keep `func_XXXXXXXX`/`D_XXXXXXXX` symbols unchanged
- add ONE line summary comment above each function (what it does), as a /* C comment */ (never //), no chatter, no line-by-line narration
- local names in lowercase_snake_case (project style); short and specific; use the EVIDENCE block's names where one is given
- do NOT touch pins (ASM_*), markers, extern declarations, structs, control flow or member names (`unk_XX` stay): those are handled by other lanes
Verify each file with its own command below (it prints JSON; "exact": true is required). Write each result to its own path (overwrite).
Do not explore the repository: everything you need is in this message. Reply with one line per file: DONE <id> <n_verify_runs> or GAVEUP <id> <reason>.
"""

PROMPT_FIDELITY = """You are removing ONE class of matching scaffolding from a function of a byte-exact PlayStation decompilation (Azure Dreams, GCC 2.7.2/2.8.1 era, maspsx assembler front end).
The file below already compiles to the retail bytes, but it carries fidelity sites the decompiler left: a pseudo-call to a LABEL inside the function (retail has a plain `j` there; the C spells it as a call to a symbol that is declared noreturn, aliased with asm("func_X"), or listed in config/sibcall_syms.<container>.txt / config/noreturn_syms.<container>.txt so the assembler turns the `jal` into `j`), and/or a call written `f()` with no arguments where retail's callee reads argument registers the caller left in place. The bytes must stay identical; the scaffolding must go.
FACTS for this row (from the retail bytes and the row database):
{facts}
RECIPES (measured on 60 rows; read them before the first edit):
- LABEL inside the function, forward target: `if (c) {{ A; target(); return; }} B; T`  ->  `if (c) {{ A' }} else {{ B' }} T`, where T is the code the jump lands on (LANDING WORD above, counted in words from the function start under its true name). The shared tail often starts mid-way through what looks like else-only code; a merged value (both arms feed one store) may need `register T v ASM_REG("$n")`; a redundant assignment written literally in BOTH arms is what fills a branch delay slot; when the tail is already spelled out right after the call, just delete the call.
- Backward target: a loop (`for(;;)`, `while`, `do/while`), not a tail.
- A target that is a real sibling function with the arguments in disguise: call it plainly WITH its real arguments (min/max style "same function either way").
- Levers that closed rows the earlier reports called dead ends: `ASM_SCHED_BARRIER()` placed before a guard clause or after an arm's store makes gcc keep a redundant reload / share one epilogue through a `j` instead of emitting one per arm; the order of the guard clauses decides which arm gcc lays out as the hot fall-through; a loop that sinks a truncated `(s16)count` into the tail jump's delay slot is a plain `do/while` with the mismatch arm as `continue` and `return (s16)count;` at the end, no pin needed (even when the file's own MECHANISM comment claims pins are required); a call's "arguments" and its compared return can be pure decoration (`return (u32)x < 2;`).
- Dead ends (do not spend verifies): a trivial jump to the next instruction (gcc deletes it); a dead value that must sit in the synthesized `j`'s delay slot; a leaf function whose two arms retail merges into one shared `jr ra` through a `j` (gcc emits two epilogues); any rewrite needing a new intra-function `j` when ROWBASE below says no (it links at the wrong address).
- Pass-through `f()`: pass what the needed registers hold at the call (the caller's own parameters, adding `s32 argN` to the caller's list when it declares none; an earlier call's argument variable; a value loaded just before). `hold-set` residue = gcc now keeps a value live across a call that retail did not (or the reverse): pass an expression gcc can recompute instead of a held variable, or the opposite. A value retail passes only because it happened to be in the register has no C spelling: report it as garbage-passthru.
Verify with:  {verify}
It prints JSON; "exact": true is required. Append --diff to the same command to print the positional disasm diff against retail (free; the mismatched jump/branch word tells you where retail lands). Keep local names and the summary comment as they are. The declaration of a removed target goes away with it. Use ASM_* pins only as a last resort with a one-line /* MATCH: ... */ note. Before you reply DONE, run the verify ONCE MORE with `--gate` appended (the retail window is the proof of record); if it says "gate": "NO MATCH", undo the last change and re-verify.
Write the final file to {out} (overwrite). Reply with one line: DONE <n_verify_runs> sites:<before>-><after> or GAVEUP <reason>.

{evidence}--- {name} ---
{src}
"""

PROMPT_FIELDS = """You are typing the raw memory accesses of one function of a byte-exact PlayStation decompilation (Azure Dreams, GCC 2.7.2/2.8.1 era).
The file below already compiles to the retail bytes. Every `M2C_FIELD(base, T *, off)` / `FIELD(base, T, off)` access is untyped: replace them with typed accesses through structs, byte-exact:
- for each base pointer, declare a local struct the project way: `typedef struct S_<func>_<n> {{ ... }} S_<func>_<n>;` with members named `unk_XX` (hex offset), `u8 pad_XX[n]` between them, widths and signedness exactly as accessed (s8/u8/s16/u16/s32/u32, pointers as `void *` unless the file already knows the pointee type); a member read with two widths gets a small union member; when the file already has such a struct for that base, extend it
- give the base pointer that struct type (a cast at the point of use is acceptable when the base is an expression)
- keep `func_XXXXXXXX`/`D_XXXXXXXX` symbols, every ASM_* pin, every extern declaration, control flow and the summary comment unchanged; do not rename struct members that already exist (`unk_XX`); do not guess semantic member names
- GCC 2.x has no strict aliasing, so this holds for nearly every row; when one access breaks the bytes, leave THAT access as an explicit cast `*(T *)((u8 *)base + off)` and type the rest
Verify with:  {verify}
It prints JSON; "exact": true is required; --diff appended prints the disasm diff. Before you reply DONE, run it ONCE MORE with `--gate` appended. Write the final file to {out} (overwrite). Reply with one line: DONE <n_verify_runs> fields:<before>-><after> or GAVEUP <reason>.

{evidence}--- {name} ---
{src}
"""

def fidelity_facts(row, text):
    """The row's fidelity sites as facts for PROMPT_FIDELITY: class, target, whether the target lies inside
    the row (and the landing word), needed registers for pass-throughs, rowbase coverage."""
    from census import audit_sites, live_audit
    live = live_audit(row, text)
    sites = [s for s in audit_sites().get(row["id"], []) if s.split("|")[0] in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS")]
    tb = row.get("true_name") or row["func"]
    base = int(tb[5:], 16) if re.match(r"func_[0-9A-F]{8}$", tb or "") else None
    need = {}
    try:
        for rec in json.load(open(ROOT / "ledger/cache/audit.json"))["records"]:
            if rec.get("cls") == "PASSTHRU_NO_ARGS" and f"{rec['container']}/{rec['row_key']}" == row["id"]:
                need[rec["target"]] = rec.get("need")
    except Exception:
        pass
    covered = None
    p = ROOT / f"config/overlays/{row['container']}.rowbase.jsonl"
    if p.exists() and row.get("foff") is not None:
        covered = False
        for l in p.read_text().splitlines():
            l = l.strip()
            if not l or l.startswith("#"): continue
            j = json.loads(l)
            if int(str(j["foff_start"]), 0) <= row["foff"] < int(str(j["foff_end"]), 0): covered = True; break
    lines = [f"- row {row['id']}: the function is defined as {tb} (its true link address), {row['size']} bytes, compiler cell {row['cfg']}"]
    for s in sites:
        cls, tgt = (s.split("|") + ["", ""])[:2]
        tv = int(tgt[5:], 16) if re.match(r"func_[0-9A-F]{8}$", tgt) else None
        if cls == "LABEL_AS_CALL":
            if base is not None and tv is not None and base <= tv < base + row["size"]:
                lines.append(f"- LABEL_AS_CALL: `{tgt}` is a label INSIDE this function at word {(tv - base) // 4} (byte +0x{tv - base:X} from the start): retail jumps there with `j`; the call spelling must go")
            else:
                lines.append(f"- LABEL_AS_CALL: `{tgt}` lies outside this function's extent: retail reaches it with a plain `j` (a tail jump to a dispatcher); the C spells it as a call")
        else:
            lines.append(f"- PASSTHRU_NO_ARGS: `{tgt}()` is called with no arguments but reads registers {need.get(tgt, '?')} at the call")
    lines.append(f"- live blocking sites now: {sum(live.get(k, 0) for k in ('LABEL_AS_CALL', 'PASSTHRU_NO_ARGS'))}")
    if covered is not None:
        lines.append("- ROWBASE: " + ("a proven rowbase region covers this row, so a new intra-function `j` links at the right address" if covered else "NO proven rowbase region covers this row: a rewrite that needs a NEW intra-function `j` cannot link correctly; only shapes that need no new jump (delete-the-call, loop forms, plain calls) can succeed"))
    return "\n".join(lines)

# the batched fidelity packet reuses the single-row prompt's recipes; facts, verify command and output path are per row
PROMPT_FIDELITY_BATCH = (PROMPT_FIDELITY.split("FACTS for this row")[0].replace("from a function of", "from several small functions of").replace("The file below already compiles", "Each file below already compiles")
    + "RECIPES" + PROMPT_FIDELITY.split("RECIPES", 1)[1].split("Verify with:")[0]
    + "Each file has its own verify command below (JSON; \"exact\": true is required; append --diff for the positional disasm diff against retail, free; run it ONCE MORE with --gate before you reply DONE for that file). Keep local names and the summary comment; the declaration of a removed target goes away with it; ASM_* pins only as a last resort with a one-line /* MATCH: ... */ note. Write each result to its own path (overwrite). Do not explore the repository: everything you need is in this message.\nReply with one line per file: DONE <id> <n_verify_runs> sites:<before>-><after> or GAVEUP <id> <reason>.\n")

def batch_prompt(items):
    """items: [(row, out_path, verify_cmd, evidence_block, src)] -> one prompt for several small rows."""
    if MODE == "fidelity":
        parts = [PROMPT_FIDELITY_BATCH]
        for row, out, vcmd, ev, src in items:
            parts.append(f"=== ROW {row['id']}  (function {row['func']}, {row['size']} bytes)\nfile: {out}\nverify: {vcmd}\nFACTS:\n{fidelity_facts(row, src)}\n{ev}--- source ---\n{src}\n")
        return "\n".join(parts)
    parts = [PROMPT_READABILITY]
    for row, out, vcmd, ev, src in items:
        parts.append(f"=== ROW {row['id']}  (function {row['func']}, {row['size']} bytes)\nfile: {out}\nverify: {vcmd}\n{ev}--- source ---\n{src}\n")
    return "\n".join(parts)

def run_codex(model, effort, prompt, workdir, timeout):
    cmd = ["codex", "exec", "-C", str(workdir), "--dangerously-bypass-approvals-and-sandbox", "--skip-git-repo-check",
           "-m", model, "-c", f'model_reasoning_effort="{effort}"', "-o", str(workdir / "last_message.txt"), "--json", "-"]
    t0 = time.time()
    try:
        r = subprocess.run(cmd, input=prompt, capture_output=True, text=True, timeout=timeout, cwd=workdir)
        rc = r.returncode; err = (r.stderr or "")[-400:]
    except subprocess.TimeoutExpired:
        rc = -1; err = "timeout"; r = None
    secs = round(time.time() - t0, 1)
    usage = {}
    # usage from the client's own event stream (codex exec --json): the last event carrying a usage/total_token_usage object
    try:
        for line in (r.stdout if r else "").splitlines():
            try: j = json.loads(line)
            except Exception: continue
            s = json.dumps(j)
            if "usage" in s or "total_token_usage" in s:
                def dig(o):
                    if isinstance(o, dict):
                        if "input_tokens" in o and "output_tokens" in o: return o
                        for v in o.values():
                            f = dig(v)
                            if f: return f
                    return None
                u = dig(j)
                if u:
                    usage = {k: v for k, v in u.items() if isinstance(v, int)}; usage["source"] = "json-events"
                    tid = j.get("thread_id") or j.get("id") or (j.get("thread") or {}).get("id")
                    if tid: usage["thread"] = str(tid)[:40]
    except Exception as e:
        usage = {"error": str(e)[:80]}
    if usage: return rc, secs, usage, err
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

OUT_TAG = ""   # journal/out suffix so parallel arms (pilots) keep their bodies apart
MODE = "full"  # or "readability"
BATCH = 0
RETRY_ALL = False

def one(row, model, effort, timeout):
    name = Path(row["c_path"]).name
    cp = ROOT / "src" / row["container"] / name
    src = (cp if cp.exists() else raw_path(row)).read_text(errors="replace")
    work = Path(tempfile.mkdtemp(prefix="agent_", dir=str(ROOT / "work")))
    out = work / name; out.write_text(src)
    verify_cmd = f"python3 {ROOT}/tools/verify.py {row['id']} {out} --include-root {INCLUDE}"
    try:
        from evidence import prompt_block   # facts from the disc and earlier analysis for this row (docs/EVIDENCE.md); '' when none
        ev = prompt_block(row["id"])
    except Exception:
        ev = ""
    if MODE == "readability":
        prompt = batch_prompt([(row, out, verify_cmd, ev, src)])
    elif MODE == "fidelity":
        prompt = PROMPT_FIDELITY.format(verify=verify_cmd, out=out, name=name, src=src, evidence=ev, facts=fidelity_facts(row, src))
    elif MODE == "fields":
        prompt = PROMPT_FIELDS.format(verify=verify_cmd, out=out, name=name, src=src, evidence=ev)
    else:
        prompt = PROMPT.format(verify=verify_cmd, out=out, name=name, src=src, evidence=ev)
    rc, secs, usage, err = run_codex(model, effort, prompt, work, timeout)
    new = out.read_text(errors="replace") if out.exists() else src
    reply = (work / "last_message.txt").read_text(errors="replace").strip()[-200:] if (work / "last_message.txt").exists() else ""
    rec = {"id": row["id"], "model": model, "effort": effort, "mode": MODE, "rc": rc, "secs": secs, "usage": usage, "reply": reply, "evidence": bool(ev),
           "changed": new != src, "in_sha": sha_text(src), "lines_in": src.count("\n"), "lines_out": new.count("\n")}
    quota = rc != 0 and any(k in (err or "").lower() for k in ("rate limit", "usage limit", "quota", "429", "too many requests"))
    if quota:
        rec["outcome"] = "quota"; rec["err"] = (err or "")[-200:]
        shutil.rmtree(work, ignore_errors=True)
        return rec
    if new == src:
        rec["outcome"] = "unchanged"
    else:
        v = verify(row, out, include_root=INCLUDE)
        rec.update({"exact": v.get("exact"), "class": v.get("class"), "total": v.get("total")})
        if v.get("exact"):
            keep = LEDGER / "agents" / "out" / (f"{model}-{effort}" + (f"-{OUT_TAG}" if OUT_TAG else "")) / row["container"]; keep.mkdir(parents=True, exist_ok=True); (keep / name).write_text(new)
            if COMMIT:   # land into src/ (the gated tree) and journal it: ledger/promotions.jsonl is what L3 reads
                from promote import promote_text
                prec = promote_text(row, new, f"agent:{model}-{effort}" + (f"-{OUT_TAG}" if OUT_TAG else ""), pre_verified_sha=sha_text(new))
                append_jsonl(LEDGER / "promotions.jsonl", prec); rec["landed"] = prec["outcome"] in ("landed", "noop")
            rec["outcome"] = "accepted"; rec["out_sha"] = sha_text(new)
            # readability proxies
            rec["m2c_locals_left"] = len(set(re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+)\b", new)))
            rec["m2c_locals_in"] = len(set(re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+)\b", src)))
            rec["gotos_in"] = len(re.findall(r"\bgoto\b", src)); rec["gotos_out"] = len(re.findall(r"\bgoto\b", new))
            # scaffolding removal attempted by the lane (PLAN: every L3 lane tries; the journal keeps the counts)
            rec["pins_in"] = len(re.findall(r"\bASM_[A-Z0-9_]+\(", src)); rec["pins_out"] = len(re.findall(r"\bASM_[A-Z0-9_]+\(", new))
            try:
                from census import live_audit
                bi = live_audit(row, src); bo = live_audit(row, new)
                rec["sites_in"] = sum(bi.get(k, 0) for k in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS")); rec["sites_out"] = sum(bo.get(k, 0) for k in ("LABEL_AS_CALL", "PASSTHRU_NO_ARGS"))
            except Exception:
                pass
        else:
            rec["outcome"] = "rejected"
    shutil.rmtree(work, ignore_errors=True)
    return rec

def finish_row(row, model, effort, src, out, work, rc, secs, usage, reply, err, batch_id=None, n_in_batch=1):
    """Verify one row's output file and build its journal record (shared by one() and batch())."""
    new = out.read_text(errors="replace") if out.exists() else src
    rec = {"id": row["id"], "model": model, "effort": effort, "mode": MODE, "rc": rc, "secs": round(secs / n_in_batch, 1), "batch_secs": secs, "usage": usage, "reply": reply,
           "batch": batch_id, "batch_n": n_in_batch, "changed": new != src, "in_sha": sha_text(src), "lines_in": src.count("\n"), "lines_out": new.count("\n")}
    quota = rc != 0 and any(k in (err or "").lower() for k in ("rate limit", "usage limit", "quota", "429", "too many requests"))
    if quota:
        rec["outcome"] = "quota"; rec["err"] = (err or "")[-200:]; return rec
    if new == src:
        rec["outcome"] = "unchanged"; return rec
    v = verify(row, out, include_root=INCLUDE)
    rec.update({"exact": v.get("exact"), "class": v.get("class"), "total": v.get("total")})
    if v.get("exact"):
        name = Path(row["c_path"]).name
        keep = LEDGER / "agents" / "out" / (f"{model}-{effort}" + (f"-{OUT_TAG}" if OUT_TAG else "")) / row["container"]; keep.mkdir(parents=True, exist_ok=True); (keep / name).write_text(new)
        if COMMIT:
            from promote import promote_text
            prec = promote_text(row, new, f"agent:{model}-{effort}" + (f"-{OUT_TAG}" if OUT_TAG else ""), pre_verified_sha=sha_text(new))
            append_jsonl(LEDGER / "promotions.jsonl", prec); rec["landed"] = prec["outcome"] in ("landed", "noop")
        rec["outcome"] = "accepted"; rec["out_sha"] = sha_text(new)
        rec["m2c_locals_left"] = len(set(re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+)\b", new)))
        rec["m2c_locals_in"] = len(set(re.findall(r"\b(temp_[a-z0-9_]+|arg[0-9]|sp[0-9A-F]{2,}|var_[a-z0-9_]+)\b", src)))
        rec["gotos_in"] = len(re.findall(r"\bgoto\b", src)); rec["gotos_out"] = len(re.findall(r"\bgoto\b", new))
        rec["pins_in"] = len(re.findall(r"\bASM_[A-Z0-9_]+\(", src)); rec["pins_out"] = len(re.findall(r"\bASM_[A-Z0-9_]+\(", new))
        rec["summary"] = bool(re.search(r"^/\*.*\*/\s*\n\s*(?:[A-Za-z_][\w\s\*]*?)\bfunc_", new, re.M))
    else:
        rec["outcome"] = "rejected"
    return rec

def batch(rows_, model, effort, timeout):
    """One codex call for several small rows (readability-only packet); one journal record per row."""
    work = Path(tempfile.mkdtemp(prefix="agentb_", dir=str(ROOT / "work")))
    items = []
    for row in rows_:
        name = Path(row["c_path"]).name
        cp = ROOT / "src" / row["container"] / name
        src = (cp if cp.exists() else raw_path(row)).read_text(errors="replace")
        out = work / name; out.write_text(src)
        vcmd = f"python3 {ROOT}/tools/verify.py {row['id']} {out} --include-root {INCLUDE}"
        try:
            from evidence import prompt_block; ev = prompt_block(row["id"])
        except Exception:
            ev = ""
        items.append((row, out, vcmd, ev, src))
    prompt = batch_prompt(items)
    rc, secs, usage, err = run_codex(model, effort, prompt, work, timeout)
    reply = (work / "last_message.txt").read_text(errors="replace").strip() if (work / "last_message.txt").exists() else ""
    bid = work.name
    recs = []
    for row, out, vcmd, ev, src in items:
        line = next((l for l in reply.splitlines() if row["id"] in l), "")[-160:]
        rec = finish_row(row, model, effort, src, out, work, rc, secs, usage, line, err, batch_id=bid, n_in_batch=len(items))
        rec["evidence"] = bool(ev); recs.append(rec)
    shutil.rmtree(work, ignore_errors=True)
    return recs

def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--model", required=True); ap.add_argument("--effort", default="high"); ap.add_argument("--rows")
    ap.add_argument("--sample", type=int); ap.add_argument("--seed", type=int, default=1); ap.add_argument("--timeout", type=int, default=900)
    ap.add_argument("--min-size", type=int, default=100); ap.add_argument("--max-size", type=int, default=600)
    ap.add_argument("--commit", action="store_true", help="also land accepted output into src/ (campaign mode; journal ledger/promotions.jsonl)")
    ap.add_argument("--with-gotos", action="store_true", help="sample only rows whose current text has gotos")
    ap.add_argument("--all", action="store_true", help="every eligible row not yet journalled (campaign mode)")
    ap.add_argument("--workers", type=int, default=1); ap.add_argument("--limit", type=int)
    ap.add_argument("--container")
    ap.add_argument("--tag", default="", help="journal name suffix")
    ap.add_argument("--mode", default="full", choices=["full", "readability", "fidelity", "fields"], help="full = the standing prompt (names + summary + removal attempts + gate step); readability = names + summary only, prepared packet, no exploration; fidelity = remove the row's LABEL_AS_CALL / PASSTHRU_NO_ARGS sites (facts + recipes in the prompt); fields = type the M2C_FIELD accesses through local structs")
    ap.add_argument("--batch", type=int, default=0, help="rows per codex call (readability and fidelity modes): related small rows share one session")
    ap.add_argument("--batch-bytes", type=int, default=6000, help="max summed source bytes per batch")
    ap.add_argument("--retry-all", action="store_true", help="serve rows again even after two failed attempts at the same text")
    a = ap.parse_args()
    global COMMIT, OUT_TAG, MODE, BATCH, RETRY_ALL; COMMIT = a.commit; OUT_TAG = a.tag; MODE = a.mode; BATCH = a.batch if a.mode in ("readability", "fidelity") else 0; RETRY_ALL = a.retry_all
    lv = {x["id"]: x for x in read_jsonl(LEDGER / "levels.jsonl")}
    rs = [r for r in rows() if lv.get(r["id"], {}).get("level", -1) >= 1 and a.min_size <= r["size"] <= a.max_size]
    if a.with_gotos:
        def has_goto(r):
            cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            t = (cp if cp.exists() else raw_path(r)).read_text(errors="replace")
            return bool(re.search(r"\bgoto\b", t))
        rs = [r for r in rs if has_goto(r)]
    if a.rows: keep = set(a.rows.split(",")); rs = [r for r in rows() if r["id"] in keep]
    elif a.sample: random.seed(a.seed); rs = random.sample(rs, min(a.sample, len(rs)))
    (LEDGER / "agents").mkdir(exist_ok=True); journal = LEDGER / "agents" / (f"{a.model}-{a.effort}" + (f"-{a.tag}" if a.tag else "") + ".jsonl")
    (ROOT / "work").mkdir(exist_ok=True)
    if a.container: rs = [r for r in rs if r["container"] == a.container]
    if a.all or (a.rows and a.commit):
        # 'quota' and 'rejected' rows are retried; an accepted row counts as done once its body landed in src/
        # (ledger/promotions.jsonl); a body set aside by a pin bump is served again.  A --rows list in
        # campaign mode (--commit) is filtered the same way, so a relaunch after a quota stop serves only
        # the rows this journal has not finished.
        from promote import landed_ids
        landed = landed_ids()
        done = {j["id"] for j in read_jsonl(journal) if j.get("outcome") == "unchanged" or (j.get("outcome") == "accepted" and j["id"] in landed)}
        rs = [r for r in rs if r["id"] not in done]
        rs.sort(key=lambda r: r["size"])
    if not RETRY_ALL:
        # a row that failed twice on the SAME text gets no third identical attempt (new text or --retry-all re-opens it)
        fails = {}
        for j in read_jsonl(journal):
            if j.get("outcome") in ("rejected", "build-failed", "gate-mismatch") and j.get("in_sha"): fails[(j["id"], j["in_sha"])] = fails.get((j["id"], j["in_sha"]), 0) + 1
        def cur_sha(r):
            cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            return sha_text((cp if cp.exists() else raw_path(r)).read_text(errors="replace"))
        skipped = [r for r in rs if fails.get((r["id"], cur_sha(r)), 0) >= 2]
        if skipped:
            print(f"{len(skipped)} rows skipped: two failed attempts at their current text (use --retry-all)", flush=True)
            rs = [r for r in rs if r not in skipped]
    if a.limit: rs = rs[:a.limit]
    # batches: same container, adjacent in file order, bounded by rows and summed source bytes
    units = []
    if BATCH > 1:
        cur = []
        def size_of(r):
            cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
            return (cp if cp.exists() else raw_path(r)).stat().st_size
        for r in sorted(rs, key=lambda r: (r["container"], r.get("foff") or 0)):
            if cur and (len(cur) >= BATCH or cur[0]["container"] != r["container"] or sum(size_of(x) for x in cur) + size_of(r) > a.batch_bytes):
                units.append(cur); cur = []
            cur.append(r)
        if cur: units.append(cur)
    else:
        units = [[r] for r in rs]
    print(f"{len(rs)} rows in {len(units)} unit(s), {a.workers} workers, model {a.model} {a.effort}, mode {MODE}" + (f", batch {BATCH}" if BATCH > 1 else ""), flush=True)
    from concurrent.futures import ThreadPoolExecutor, as_completed
    def work(unit):
        at = time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())
        recs = batch(unit, a.model, a.effort, a.timeout) if len(unit) > 1 else [one(unit[0], a.model, a.effort, a.timeout)]
        for rec in recs: rec["at"] = at
        return recs
    quota_hits = 0; stop = False
    with ThreadPoolExecutor(max_workers=a.workers) as ex:
        pending = set(); it = iter(units)
        while not stop and (pending or True):
            while len(pending) < a.workers and not stop:
                u = next(it, None)
                if u is None: break
                pending.add(ex.submit(work, u))
            if not pending: break
            done_f = next(as_completed(pending)); pending.discard(done_f)
            for rec in done_f.result():
                append_jsonl(journal, rec); print(json.dumps({k: rec.get(k) for k in ("id", "outcome", "secs", "class", "total", "m2c_locals_in", "m2c_locals_left", "gotos_in", "gotos_out", "reply")}), flush=True)
                quota_hits = quota_hits + 1 if rec["outcome"] == "quota" else 0
                if quota_hits >= 3:
                    print("QUOTA: three consecutive rate-limit failures; stopping (relaunch with --all after the reset)", flush=True)
                    stop = True
        if stop: ex.shutdown(wait=False, cancel_futures=True)

if __name__ == "__main__":
    main()
