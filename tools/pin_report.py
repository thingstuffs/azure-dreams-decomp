#!/usr/bin/env python3
"""Pin census analysis -> Markdown: what each pin kind is for, how often it is dead, and how
the bytes break when it is removed (breakage class), cross-tabbed by context.

    python3 tools/pin_report.py ledger/pins_sample.jsonl > docs/PIN_CENSUS.md
"""
import collections, json, sys
from common import read_jsonl

def pct(a, b): return f"{100*a/b:.0f}%" if b else "-"

def tab(recs, title, keyf, min_n=1, classes=4):
    g = collections.defaultdict(list)
    for r in recs: g[keyf(r)].append(r)
    rows = []
    for k, v in sorted(g.items(), key=lambda kv: -len(kv[1])):
        if len(v) < min_n: continue
        free = sum(1 for r in v if r["exact"]); fail = sum(1 for r in v if r["status"] != "ok")
        cls = collections.Counter(r["class"] or "?" for r in v if not r["exact"] and r["status"] == "ok")
        dw = collections.Counter(("same-len" if r["dwords"] == 0 else ("longer" if (r["dwords"] or 0) > 0 else "shorter")) for r in v if not r["exact"] and r["dwords"] is not None)
        rows.append(f"| {k} | {len(v)} | {free} ({pct(free, len(v))}) | {fail} | " + ", ".join(f"{c} {n}" for c, n in cls.most_common(classes)) + f" | {dict(dw)} |")
    return f"\n### {title}\n\n| key | sites | dead (erasable) | build-fail | breakage classes when kept | length when kept |\n|---|---:|---:|---:|---|---|\n" + "\n".join(rows) + "\n"

def main():
    recs = [r for r in read_jsonl(sys.argv[1]) if r]
    n = len(recs); free = sum(1 for r in recs if r["exact"])
    rows_ = collections.defaultdict(list)
    for r in recs: rows_[r["id"]].append(r)
    all_dead = sum(1 for v in rows_.values() if all(r["exact"] for r in v))
    out = [f"# Pin census ({sys.argv[1]})\n",
           f"Single-site erasure from the original pinned text, one experiment per site, verified against retail bytes.\n",
           f"- sites: **{n}** in **{len(rows_)}** rows; dead on their own: **{free} ({pct(free, n)})**; rows whose every pin is dead on its own: **{all_dead}** ({pct(all_dead, len(rows_))})",
           f"- build failures: {sum(1 for r in recs if r['status'] != 'ok')}\n",
           "A pin is *dead* if erasing it alone leaves the bytes exact. Pins interact: the greedy transform (T2) erases more than the single-site rate in some rows and less in others.\n"]
    out.append(tab(recs, "by macro", lambda r: r["macro"]))
    out.append(tab([r for r in recs if r["kind"] == "reg"], "ASM_REG by register", lambda r: f"${r['reg']} ({r['reg_class']})", min_n=3))
    out.append(tab(recs, "by container", lambda r: r["container"]))
    out.append(tab(recs, "by compiler cell", lambda r: r["cfg"].split()[0]))
    out.append(tab(recs, "by context", lambda r: (("in-#define " if r["in_macro_def"] else "") + ("after-call " if r["prev_call"] else "") + ("before-call " if r["next_call"] else "") + ("before-return " if r["next_return"] else "") + ("after-label " if r["prev_label"] else "") + ("after-loop-head " if r["prev_loop"] else "")).strip() or "plain", min_n=10))
    out.append(tab(recs, "macro x context (top)", lambda r: f"{r['macro']} " + (("after-call" if r["prev_call"] else "") + (" before-call" if r["next_call"] else "") + (" before-return" if r["next_return"] else "") or "plain"), min_n=15))
    out.append(tab(recs, "by function size", lambda r: ("<=128 B" if r["size"] <= 128 else "<=512 B" if r["size"] <= 512 else "<=2 KB" if r["size"] <= 2048 else ">2 KB")))
    out.append(tab(recs, "by pins in the function", lambda r: ("1-2" if r["nsites"] <= 2 else "3-5" if r["nsites"] <= 5 else "6-10" if r["nsites"] <= 10 else "11-25" if r["nsites"] <= 25 else ">25")))
    # breakage classes overall
    cls = collections.Counter(r["class"] or "?" for r in recs if not r["exact"] and r["status"] == "ok")
    out.append("\n### Breakage classes over all kept pins\n\n| class | kept sites | share | what it means | mechanical alternative to try |\n|---|---:|---:|---|---|")
    meaning = {
        "reg-rename": ("same instructions, different register colouring", "declaration-order / first-use permutation (bounded search); merge two temps into one"),
        "reorder-only": ("same instructions, different order (scheduler)", "statement reorder in source; split/join expressions; barrier only if needed"),
        "slot-rotation": ("branch/jump delay-slot fill differs", "reorder the statement before the branch; a plain temp instead of a pin"),
        "hold-set": ("different callee-saved set / frame layout", "reduce live ranges (scope a temp), or accept a documented pin"),
        "const-remat": ("constant re-materialised vs kept in a register", "hoist the constant into a named local used twice; volatile-free"),
        "li-expansion": ("immediate load expanded differently (lui/addiu vs li)", "write the constant in the retail split form; a named local"),
        "addressing": ("address computed differently (%hi/%lo vs gp, base+offset)", "extern declaration shape (array vs scalar) — a declaration transform"),
        "code-motion": ("a statement moved across a call/branch", "re-place the statement in source order; a dependency through a local"),
        "length-drift": ("different instruction count (extra/missing move, nop)", "usually a copy that must be coalesced: reuse the variable; agent tier"),
        "block-order": ("basic blocks laid out in a different order", "goto/if polarity flip; agent tier"),
        "polarity": ("branch condition inverted", "swap if/else arms or invert the comparison"),
        "broad": ("many differences at once", "not mechanical: the pin is load-bearing for the whole shape"),
        "linked-target": ("a jump/call target word differs", "not a codegen matter: symbol/label placement"),
        "div-guard": ("assembler div/rem trap-guard expansion", "assembler dial, not C"),
        "delay-slot": ("the instruction in a branch/jump delay slot differs", "a temp that is dead after the branch; usually the TAILSLOT pin family — assembler-shaped, keep documented"),
        "dead-code-retention": ("retail keeps a computation the compiler now drops", "a volatile-free use of the value (assign to a local that is passed on)"),
        "match": ("", ""), "?": ("unclassified (build ok, no class)", "")}
    tot_kept = sum(cls.values())
    for c, k in cls.most_common():
        m = meaning.get(c, ("", ""))
        out.append(f"| {c} | {k} | {pct(k, tot_kept)} | {m[0]} | {m[1]} |")
    print("\n".join(out))

if __name__ == "__main__":
    main()
