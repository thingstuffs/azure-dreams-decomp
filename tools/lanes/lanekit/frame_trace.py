#!/usr/bin/env python3
"""frame_trace.py <row> <cand.c|pinned|erased> [--cfg CFG] [--raw]
Runs the cell's cc1 under gdb (frame_gdb.py) and prints every stack-slot allocation of the function: who called
assign_stack_local (expand / reload alter_reg / caller-save), for which pseudo (with its refs, deaths, block, calls
crossed, renumber, REG_EQUIV flags), the slot size/alignment and frame_offset before/after; plus every
delete_output_reload (deleted or not), new_spill_reg, spill_hard_reg and retry_global_alloc. The answer to 'where
do the frame bytes come from'. Usage from the lane: python3 tools/frame_trace.py dungeon/func_80DE48EC cand/x.c --cfg 2.7.2-cdk-G0"""
import json, os, subprocess, sys, tempfile
from pathlib import Path
_ROOT = Path(__file__).resolve().parents[3]
KIT = str(_ROOT / "tools/lanes/lanekit")
sys.path.insert(0, KIT); sys.path.insert(0, str(_ROOT / "tools"))
import kitlib                                                        # noqa: E402
lane = kitlib.bootstrap()
from common import parse_cfg, NICE                                   # noqa: E402
ROOT = _ROOT
args = [a for a in sys.argv[1:] if not a.startswith("--")]
cfg = None
if "--cfg" in sys.argv: cfg = sys.argv[sys.argv.index("--cfg") + 1]
args = [a for a in args if a != cfg]
row = kitlib.row_of(args[0]); what = args[1]
if what == "pinned": text = kitlib.base_text(row, lane)
elif what == "erased": text = kitlib.erased_text(kitlib.base_text(row, lane))
else: text = Path(what).read_text()
cell, flags = parse_cfg(cfg or row["cfg"])
D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
with tempfile.TemporaryDirectory(prefix="ftrace_") as td:
    d = Path(td); (d / "f.c").write_text(text)
    r = subprocess.run(NICE + [str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags, "-I" + str(ROOT / "include"), "-w", "f.c", "-o", "f.i"],
                       cwd=d, capture_output=True, text=True)
    if r.returncode: sys.exit("cpp failed: " + (r.stderr or r.stdout)[-800:])
    out = d / "trace.jsonl"
    env = dict(os.environ, FT_OUT=str(out), TMPDIR=str(d))
    cmd = ["gdb", "-batch", "-nx", "-iex", "set debuginfod enabled off", "-iex", "set pagination off",
           "-x", str(Path(__file__).with_name("frame_gdb.py")), "--args", str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-o", "f.s"]
    r = subprocess.run(cmd, cwd=d, capture_output=True, text=True, env=env, timeout=600)
    recs = [json.loads(l) for l in out.read_text().splitlines()] if out.exists() else []
    if not recs: sys.exit("no trace: " + (r.stderr or r.stdout)[-1500:])
    if "--raw" in sys.argv:
        for x in recs: print(json.dumps(x))
    asm = (d / "f.s").read_text() if (d / "f.s").exists() else ""
# report
print("# frame_trace %s %s at %s" % (row["id"], what, cfg or row["cfg"]))
import re
m = re.search(r"\.frame\s+\$sp,(\d+)", asm) or re.search(r"subu\s+\$sp,\$sp,(\d+)", asm)
print("frame size (asm): %s   outgoing args: %s" % (m.group(1) if m else "?", next((x.get("outgoing_args") for x in recs if x["ev"] == "reload"), "?")))
phase = "expand"
for x in recs:
    ev = x["ev"]
    if ev == "reload": phase = "reload"; print("-- reload() entered: frame_offset %s" % x["frame_offset_before"]); continue
    if ev == "assign_stack_local":
        if x["size"] == 0: continue
        who = [c for c in x["callers"] if c not in ("assign_stack_local",)]
        print("SLOT  %-6s size %-3d align %-3d  frame_offset %s -> %s   via %s" % (x["mode"], x["size"], x["align"], x["frame_offset_before"], x.get("frame_offset_after"), " < ".join(who[:5])))
    elif ev == "alter_reg":
        r_ = x["reg"]
        if r_["renumber"] is not None and r_["renumber"] < 0 and (x["frame_offset_before"] != x.get("frame_offset_after")):
            tag = "SLOT"
        else: tag = "    "
        if tag == "SLOT" or x["from_reg"] != -1 or "--all" in sys.argv:
            print("%s alter_reg pseudo %d (%s %s) from_reg %d renumber %s refs %s deaths %s block %s calls %s equiv_const %s equiv_mem %s  <- %s   fo %s -> %s" % (
                tag, r_["i"], r_.get("mode"), r_.get("code"), x["from_reg"], r_["renumber"], r_["refs"], r_["deaths"], r_["block"], r_["calls"], r_["equiv_const"], r_["equiv_mem"],
                x["callers"][1] if len(x["callers"]) > 1 else "?", x["frame_offset_before"], x.get("frame_offset_after")))
    elif ev == "delete_output_reload":
        print("DOR   insn %s reload %s (in: %s r%s) output_reload_insn %s -> %s" % (x.get("insn"), x.get("j"), x.get("reload_in"), x.get("reload_in_regno"), x.get("output_reload_insn"), "DELETED" if x.get("deleted") else "kept (%s)" % x.get("orl_code_after")))
    elif ev == "new_spill_reg":
        print("SPILLREG class %s (max_needs %s) -> hard reg %s" % (x.get("cls"), x.get("max_needs"), x.get("ret")))
    elif ev == "spill_hard_reg":
        print("SPILL_HARD_REG %s cant_eliminate %s" % (x.get("regno"), x.get("cant_eliminate")))
    elif ev == "setup_save_areas":
        print("CALLER-SAVE setup_save_areas: fo %s -> %s" % (x["frame_offset_before"], x.get("frame_offset_after")))
    elif ev == "retry_global_alloc":
        print("RETRY_GLOBAL_ALLOC pseudo %s" % x.get("regno"))
    elif ev == "done":
        print("-- final frame_offset %s" % x["frame_offset_final"])
    elif "error" in x:
        print("ERR", x)
