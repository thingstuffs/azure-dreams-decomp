#!/usr/bin/env python3
"""Toolchain fidelity STEP 1b: which compiler emitted the 2.8-era return epilogues? (measurement only)

Brief: work/fidelity/STEP1B_BRIEF.md; report: docs/evidence/fidelity_step1b_epilogue.md.

gcc 2.8.0 / 2.8.1 / 2.91.66 / 2.95.2 (and the genuine SN CC1PSX builds of them) emit the return as RTL
(`mips_expand_epilogue`): reorg fills the `j $31` slot with the `addu $sp,$sp,N` teardown, and final prints the
pair under `.set noreorder`.  gcc 2.6.3 / 2.7.2 print the epilogue as TEXT (`function_epilogue`): `.set noreorder`
only when reorg supplied an epilogue delay insn, which `mips_epilogue_delay_slots` allows only when the frame is
empty or saves nothing but $31; otherwise `addu $sp,$sp,N / j $31` in REORDER mode, and the assembler fills the
slot.  For every row at a 2.8-era cell this tool compiles the row's CURRENT source and assembles, with GENUINE
ASPSX, several cc1 outputs, each compared (aspsx_diff's comparator) with the row's maspsx object (= retail):

  base       our cell's cc1, as the pipeline runs it (step 1's genuine leg)
  all        base with EVERY noreorder `j $31 / addu $sp,$sp,N` block rewritten to reorder mode
             (tools/fidelity/probe_reorder_epilogue.py's rewrite)
  t272       base rewritten by gcc 2.7.2's rule: a block is rewritten unless the function saves only $31 (.mask
             0x80000000, .fmask 0) AND a real instruction sits between the `lw $31` and the `j $31` (the 2.7.2
             epilogue-delay form `lw $31 / X / j $31 / addu`, which 2.7.2 also prints under noreorder)
  fndb       our cell's cc1 with -fno-delayed-branch (the one stock option that leaves the return to the assembler)
  psyq       the GENUINE SN CC1PSX of the cell's generation (--psyq; 2.8.x: psyq4.4 `2.8.1 SN32 BUILD 4.0.0010`,
             2.91.66: the SN `egcs-2.91.66 (PSX)` build, 2.95.2: psyq4.6), driven through our gcc driver/cpp by a
             cc1 wrapper; plus `psyq_t272` (the same rule on its output)

The retail return shape of every `jr $ra` in the maspsx object, and the per-function epilogue census of the cc1
output (.mask, restores, block form), are recorded too.

    python3 tools/fidelity/epilogue_model.py [--workers 8] [--only ID,..|@file] [--cells 2.8.0,2.8.1,...] [--psyq]
    python3 tools/fidelity/epilogue_model.py --one dungeon/func_7FFE7BE8 [--psyq]
    python3 tools/fidelity/epilogue_model.py --report          # tables for the evidence doc

Step 1c (work/fidelity/STEP1C_BRIEF.md) re-targets the `psyq` leg at any held cc1 through two environment variables
read at import (the --worker subprocesses re-import this module, so command-line options would not reach them):

  EPILOGUE_MODEL_OUT   output root (journal default <OUT>/epilogue_model.jsonl, scratch <OUT>/tmp); default step1b
  Lost-compiler hunt B adds psyq_s_sha (body hash), psyq_s_equal_t272 / psyq_s_diff_t272 (twin with our cell's
  output after the t272 rewrite: the candidate differs from the 2.8-era cell only in the epilogue).

  EPILOGUE_MODEL_CC1   JSON {cell: [label, cc1 path (repo-relative or absolute), twin?, mode]} replacing PSYQ_CC1;
                       mode = "wibo" (Windows PE, default), "native" (a host ELF cc1) or "dosemu" (DOS/go32 cc1 under
                       dosemu2; every file next to the cc1, e.g. GO32.EXE, is copied into the run directory)
"""
from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
import time
from collections import Counter, defaultdict
from concurrent.futures import ThreadPoolExecutor
from pathlib import Path

HERE = Path(__file__).resolve().parent
ROOT = HERE.parents[1]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(HERE))

OUT = Path(os.environ.get("EPILOGUE_MODEL_OUT") or ROOT / "work/fidelity/step1b")
if not OUT.is_absolute():
    OUT = ROOT / OUT
# this tool's OWN scratch root: aspsx_diff's default (work/fidelity/tmp/rows) is shared with the other fidelity jobs,
# and removing it at the end of a run destroys their in-flight temp dirs (it did, 2026-09-24: 10 asv_trial rows)
TMP = OUT / "tmp"


def _aspsx():
    import aspsx_diff as A
    A.TMP = TMP
    return A
JOURNAL = OUT / "epilogue_model.jsonl"
CELLS_2X = ("2.8.0", "2.8.1", "2.91.66", "2.95.2")
# genuine SN cc1 per cell generation: (label, path relative to the genuine toolchain root, twin?)
PSYQ_CC1 = {"2.8.0": ("psyq4.4 (2.8.1 SN32 BUILD 4.0.0010)", "psyq/psyq4.4/CC1PSX.EXE", False),
            "2.8.1": ("psyq4.4 (2.8.1 SN32 BUILD 4.0.0010)", "psyq/psyq4.4/CC1PSX.EXE", True),
            "2.91.66": ("SN egcs-2.91.66 (PSX)", None, True),        # extracted from the 4.5 MFD archive, see --egcs
            "2.95.2": ("psyq4.6 (2.95.2)", "psyq/psyq4.6/CC1PSX.EXE", True)}
_OVR = os.environ.get("EPILOGUE_MODEL_CC1")
if _OVR:
    PSYQ_CC1 = {c: (v[0], str(v[1] if Path(v[1]).is_absolute() else ROOT / v[1]), bool(v[2]),
                    v[3] if len(v) > 3 else "wibo") for c, v in json.loads(_OVR).items()}
VERS = ("2.79", "2.77")

# a gcc noreorder return block (`%*j $31` with the teardown reorg put in its slot)
EPI = re.compile(r"\t\.set\tnoreorder\n\t\.set\tnomacro\n\tj\t\$31\n\t(addu\t\$sp,\$sp,\d+)\n\t\.set\tmacro\n\t\.set\treorder\n")
MASK = re.compile(r"^\t\.mask\t0x([0-9a-fA-F]+),")
FMASK = re.compile(r"^\t\.fmask\t0x([0-9a-fA-F]+),")
RA_MASK = 0x80000000
RESTORE = re.compile(r"^\tlw\t\$(1[6-9]|2[0-3]|30|31|fp),-?\d+\(\$sp\)")
INSN = re.compile(r"^\t[a-z]")


# --------------------------------------------------------------------------------------- the cc1 text model
def functions_s(src):
    """[(name, start, end)] character spans `.ent NAME` .. `.end NAME` of a gcc -S listing."""
    out = []
    for m in re.finditer(r"^\t\.ent\t(\S+)\n", src, re.M):
        e = re.compile(r"^\t\.end\t" + re.escape(m.group(1)) + r"\n", re.M).search(src, m.end())
        out.append((m.group(1), m.start(), e.end() if e else len(src)))
    return out


def prev_real(src, pos):
    """The last instruction line before character `pos` (comments such as gcc's `#nop`, directives, labels and
    blank lines skipped)."""
    for l in reversed(src[:pos].split("\n")):
        if INSN.match(l):
            return l.strip()
    return ""


def census(src):
    """Per function: mask, fmask, restores, and every return block's form."""
    out = []
    for name, s, e in functions_s(src):
        body = src[s:e]
        mk = next((int(m.group(1), 16) for m in map(MASK.match, body.split("\n")) if m), 0)
        fm = next((int(m.group(1), 16) for m in map(FMASK.match, body.split("\n")) if m), 0)
        blocks = []
        for m in EPI.finditer(body):
            pr = prev_real(body, m.start())
            blocks.append({"prev": pr, "after_ra_load": bool(re.match(r"lw\t\$31,", pr))})
        plain = len(re.findall(r"^\tj\t\$31\n", body, re.M)) - len(blocks)
        out.append({"f": name, "mask": f"{mk:08x}", "fmask": f"{fm:08x}", "ra_only": mk == RA_MASK and fm == 0,
                    "restores": sum(1 for l in body.split("\n") if RESTORE.match(l)),
                    "nr_sp": len(blocks), "other_ret": plain, "blocks": blocks})
    return out


TEXT_EPI = re.compile(r"^\taddu\t\$sp,\$sp,\d+\n\tj\t\$31\n", re.M)


def epi_forms(src):
    """Return forms of a cc1 listing (step 1c): in functions that save a register besides $31 (where gcc 2.7.2's
    text epilogue can take no delay insn), `filled` = noreorder `j $31 / addu $sp` blocks (the RTL epilogue after
    reorg), `text` = reorder-mode `addu $sp / j $31` (2.7.2's text epilogue); `ra_only_*` the same in $31-only
    frames; `text_filled` = the teardown in the slot under a plain `.set noreorder` (an older text epilogue)."""
    out = Counter()
    for name, s, e in functions_s(src):
        body = src[s:e]
        mk = next((int(m.group(1), 16) for m in map(MASK.match, body.split("\n")) if m), 0)
        fm = next((int(m.group(1), 16) for m in map(FMASK.match, body.split("\n")) if m), 0)
        pre = "ra_only_" if (mk == RA_MASK and fm == 0) else ("" if mk else "leaf_")
        out[pre + "filled"] += len(EPI.findall(body))
        out[pre + "text"] += len(TEXT_EPI.findall(body))
        # teardown in the return slot WITHOUT reorg's `.set nomacro` wrapper: an older text epilogue printed filled
        # under `.set noreorder` (gcc 2.5.7)
        out[pre + "text_filled"] += len(re.findall(r"^\tj\t\$31\n\taddu\t\$sp,\$sp,\d+\n", body, re.M)) - len(EPI.findall(body))
    return {k: v for k, v in out.items() if v}


def rewrite(src, rule):
    """Rewrite noreorder return blocks to reorder mode (`addu $sp,$sp,N / j $31`).
    rule 'all': every block.  rule 't272': gcc 2.7.2's function_epilogue decision (see module doc)."""
    pieces, last = [], 0
    for name, s, e in functions_s(src):
        body = src[s:e]
        mk = next((int(m.group(1), 16) for m in map(MASK.match, body.split("\n")) if m), 0)
        fm = next((int(m.group(1), 16) for m in map(FMASK.match, body.split("\n")) if m), 0)
        ra_only = mk == RA_MASK and fm == 0

        def sub(m):
            if rule == "t272" and ra_only and not re.match(r"lw\t\$31,", prev_real(body, m.start())):
                return m.group(0)          # 2.7.2's epilogue-delay form: kept under noreorder
            return "\t" + m.group(1) + "\n\tj\t$31\n"
        pieces += [src[last:s], EPI.sub(sub, body)]
        last = e
    pieces.append(src[last:])
    return "".join(pieces)


# ------------------------------------------------------------------------------------------ retail shape
def retail_shapes(mv, scope):
    """Every `jr $ra` in the (retail-exact) maspsx units: prev / delay classes."""
    c = Counter()
    for f in scope:
        t = [w for w, _, _ in mv.tokens(f)]
        for i, w in enumerate(t):
            if w != 0x03E00008:
                continue
            d = t[i + 1] if i + 1 < len(t) else None
            p = t[i - 1] if i else None
            sp = lambda x: x is not None and (x >> 16) == 0x27BD and (x & 0x8000) == 0     # addiu sp,sp,+N
            ldra = lambda x: x is not None and (x >> 16) == 0x8FBF                          # lw ra,N(sp)
            if sp(d):
                c["filled_sp" + ("_after_lw_ra" if ldra(p) else "")] += 1
            elif d == 0 and sp(p):
                c["sp_before_nop" + ("_ld_shadow" if i >= 2 and ldra(t[i - 2]) else "")] += 1
            elif d == 0:
                c["nop_other"] += 1
            else:
                c["filled_other"] += 1
    return dict(c)


# ----------------------------------------------------------------------------------- genuine cc1 wrapper
WRAP = r'''#!/usr/bin/env python3
# cc1 stand-in: the genuine SN CC1PSX under wibo, called by our gcc driver (tools/fidelity/epilogue_model.py)
import os, shutil, subprocess, sys, tempfile
WIBO, CC1, TMPROOT = %r, %r, %r
args = sys.argv[1:]; inp = out = None; rest = []; i = 0
while i < len(args):
    a = args[i]
    if a == "-o": out = args[i + 1]; i += 2; continue
    if a in ("-dumpbase", "-auxbase"): rest += [a, os.path.basename(args[i + 1])]; i += 2; continue
    if not a.startswith("-") and inp is None: inp = a; i += 1; continue
    rest.append(a); i += 1
d = tempfile.mkdtemp(prefix="c", dir=TMPROOT)
try:
    shutil.copyfile(inp, os.path.join(d, "in.i"))
    env = dict(os.environ, TMPDIR=d, TMP=d, TEMP=d)
    r = subprocess.run([WIBO, CC1] + rest + ["in.i", "-o", "out.s"], cwd=d, env=env, capture_output=True, text=True)
    sys.stderr.write(r.stderr[-2000:])
    if not os.path.exists(os.path.join(d, "out.s")):
        sys.stderr.write(r.stdout[-2000:]); sys.exit(r.returncode or 1)
    shutil.copyfile(os.path.join(d, "out.s"), out)
    sys.exit(r.returncode)
finally:
    shutil.rmtree(d, ignore_errors=True)
'''


DOSWRAP = r'''#!/usr/bin/env python3
# cc1 stand-in: a DOS/go32 cc1 under dosemu2, called by our gcc driver (tools/fidelity/epilogue_model.py, step 1c)
import os, shutil, subprocess, sys, tempfile
CC1, TMPROOT = %r, %r
args = sys.argv[1:]; inp = out = None; rest = []; i = 0
while i < len(args):
    a = args[i]
    if a == "-o": out = args[i + 1]; i += 2; continue
    if a in ("-dumpbase", "-auxbase"): i += 2; continue
    if not a.startswith("-") and inp is None: inp = a; i += 1; continue
    rest.append(a); i += 1
d = tempfile.mkdtemp(prefix="d", dir=TMPROOT)
try:
    src = os.path.dirname(CC1)
    for n in os.listdir(src):
        shutil.copyfile(os.path.join(src, n), os.path.join(d, n.upper()))
    shutil.copyfile(inp, os.path.join(d, "IN.I"))
    cmd = " ".join([os.path.basename(CC1).upper()] + rest + ["IN.I", "-o", "OUT.S"])
    r = subprocess.run(["dosemu", "-dumb", "-quiet", "-K", d, "-E", cmd], cwd=d, stdin=subprocess.DEVNULL,
                       capture_output=True, text=True, errors="replace", timeout=600)
    got = [n for n in os.listdir(d) if n.lower() == "out.s"]
    if not got:
        sys.stderr.write("dosemu: no output for: " + cmd + "\n" + (r.stdout + r.stderr)[-2000:]); sys.exit(1)
    shutil.copyfile(os.path.join(d, got[0]), out)
    sys.exit(0)
finally:
    shutil.rmtree(d, ignore_errors=True)
'''


def psyq_root(tmp):
    """A compilers root whose gcc-<cell> dirs are our driver/cpp with the genuine CC1PSX as cc1."""
    A = _aspsx()
    import hashlib
    key = hashlib.sha1(json.dumps(sorted((c, list(v)) for c, v in PSYQ_CC1.items())).encode()).hexdigest()[:10]
    root = Path(tmp) / ("psyqcc" if not _OVR else "psyqcc-" + key)     # one root per cc1 mapping (step 1c)
    if root.exists():
        return root
    final, root = root, Path(tempfile.mkdtemp(prefix=root.name + ".", dir=tmp))   # built aside, renamed: workers race
    for cell, spec in PSYQ_CC1.items():
        rel, mode = spec[1], (spec[3] if len(spec) > 3 else "wibo")
        cc1 = (A.GENUINE / rel) if rel else EGCS_CC1
        if not cc1 or not Path(cc1).exists():
            continue
        d = root / f"gcc-{cell}"; d.mkdir(parents=True)
        src = ROOT / "toolchain/compilers" / f"gcc-{cell}"
        for n in os.listdir(src):
            if n != "cc1":
                os.symlink(src / n, d / n)
        if mode == "native":
            os.symlink(cc1, d / "cc1"); continue
        if mode == "dosemu":
            (d / "cc1").write_text(DOSWRAP % (str(cc1), str(A.TMP)))
        else:
            (d / "cc1").write_text(WRAP % (str(A.WIBO), str(cc1), str(A.TMP)))
        os.chmod(d / "cc1", 0o755)
    try:
        os.rename(root, final)
    except OSError:                        # another worker won the race: use its root
        shutil.rmtree(root, ignore_errors=True)
    return final


# the SN egcs-2.91.66 CC1PSX.EXE: psyq 4.5 MFD archive (toolchain/genuine/psyq/_archives/rar45) BIN/WIN/, copied here
EGCS_CC1 = os.environ.get("STEP1B_EGCS_CC1") or str(ROOT / "work/fidelity/step1b/genuine_cc1/egcs-2.91.66-psx/CC1PSX.EXE")


# -------------------------------------------------------------------------------------------- one row
def prep(A, row, cfg, td, compilers=None):
    """aspsx_diff's context for `row` at `cfg`, optionally with every cell's compiler taken from `compilers`."""
    from common import clean_path
    import verify
    ofc = A._ofc()[0]
    saved = (verify.COMPILERS, ofc.compiler_for)
    try:
        if compilers is not None:
            verify.COMPILERS = compilers
            ofc.compiler_for = lambda ver: str(compilers / f"gcc-{ver}")
        if row["kind"] == "slus":
            return A.prepare_slus(row, clean_path(row), cfg, row.get("row_asflags") or "", td)
        return A.prepare_overlay(row, clean_path(row), cfg, None, td)
    finally:
        verify.COMPILERS, ofc.compiler_for = saved


def genuine_best(A, s, flags, ver, mv, scope, td):
    modes, _ = A.genuine_modes(s, flags)
    best = None
    for fl, equ in modes:
        lnk, err = A.run_aspsx(A.aspsx_input(s, equ), ver, fl, td)
        if lnk is None:
            best = best or {"err": err}
            continue
        gv = A.View(A.read_lnk(lnk), mv, A.aliases(s))
        gv.composite = mv.composite; gv.follow = mv.follow
        for f in scope:
            gv.add_unit(f, mv)
        c = A.compare_units(mv, gv, scope)
        cand = {"exact": c["exact"], "diff": c["diff"], "len_m": c["len_m"], "len_g": c["len_g"],
                "mode": " ".join(fl[1:] + (["equ"] if equ else []))}
        if best is None or "err" in best or (cand["exact"], -cand["diff"]) > (best["exact"], -best["diff"]):
            best = cand
    return best


def strip_s(s):
    """The `.ent`..`.end` bodies of a cc1 output, comments dropped (the twin comparison; the genuine binaries
    place the `.extern` block and a duplicate `.text` differently - work/tailslot_aspsx/CC1_DIFFERENTIAL.md s.3)."""
    return [l for n, a, b in functions_s(s) for l in s[a:b].split("\n") if l.strip() and not l.lstrip().startswith("#")]


def process_row(row, psyq=False):
    A = _aspsx()
    from common import parse_cfg
    t0 = time.time()
    A.TMP.mkdir(parents=True, exist_ok=True)
    os.environ["TMPDIR"] = str(A.TMP); tempfile.tempdir = str(A.TMP)
    td = tempfile.mkdtemp(prefix=row["id"].replace("/", "__") + "_", dir=A.TMP)
    rec = {"row": row["id"], "container": row["container"], "cfg": row["cfg"], "cell": parse_cfg(row["cfg"])[0]}
    try:
        from common import clean_path
        import hashlib
        rec["src_sha"] = hashlib.sha1(Path(clean_path(row)).read_bytes()).hexdigest()[:12]   # (hunt B: the registry moves)
        ctx, err = prep(A, row, row["cfg"], td)
        if ctx is None:
            rec.update(status="error", err=("compile: " + str(err))[:300]); return rec
        mo, err = A.run_maspsx(ctx["m_in"], ctx["as_args"], Path(td) / "m.o", ctx["env"])
        if mo is None:
            rec.update(status="error", err=("maspsx: " + str(err))[:300]); return rec
        mv = A.View(A.read_elf(mo))
        if row["kind"] == "slus":
            scope = sorted(mv.funcs)
        else:
            scope = [ctx["symbol"]]
            mv.add_unit(scope[0]); mv.composite = {scope[0]}; A.shape_unit(mv, scope[0], len(ctx["retail"]))
        rec["maspsx_exact"] = ctx["maspsx_exact"]
        rec["retail_ret"] = retail_shapes(mv, scope)
        base = ctx["g_src"]
        rec["census"] = census(base)
        srcs = {"base": base, "all": rewrite(base, "all"), "t272": rewrite(base, "t272")}
        td2 = tempfile.mkdtemp(prefix="fndb_", dir=td)
        c2, err = prep(A, row, row["cfg"] + " -fno-delayed-branch", td2)
        srcs["fndb"] = c2["g_src"] if c2 else None
        if psyq:
            cell = rec["cell"]
            rec["psyq_cc1"] = PSYQ_CC1[cell][0] + ("" if PSYQ_CC1[cell][2] else " [cross-generation]")
            td3 = tempfile.mkdtemp(prefix="psyq_", dir=td)
            c3, err = prep(A, row, row["cfg"], td3, compilers=psyq_root(A.TMP))
            if c3 is None:
                rec["psyq_err"] = str(err)[:300]
            else:
                ps = c3["g_src"]
                rec["psyq_epi"] = epi_forms(ps)
                rec["psyq_s_equal"] = strip_s(ps) == strip_s(base)
                if not rec["psyq_s_equal"]:
                    import difflib
                    rec["psyq_s_diff"] = sum(1 for l in difflib.unified_diff(strip_s(base), strip_s(ps), n=0)
                                             if l[:1] in "+-" and l[:3] not in ("+++", "---"))
                # lost-compiler hunt B (additive): a body hash for cross-compiler comparison, and the twin test
                # against our cell's output after gcc 2.7.2's epilogue rule - True means the candidate and our
                # 2.8-era cell differ ONLY in the return epilogue
                import hashlib
                rec["psyq_s_sha"] = hashlib.sha1("\n".join(strip_s(ps)).encode()).hexdigest()[:16]
                b272 = strip_s(rewrite(base, "t272"))
                rec["psyq_s_equal_t272"] = strip_s(ps) == b272
                if not rec["psyq_s_equal_t272"]:
                    import difflib
                    rec["psyq_s_diff_t272"] = sum(1 for l in difflib.unified_diff(b272, strip_s(ps), n=0)
                                                  if l[:1] in "+-" and l[:3] not in ("+++", "---"))
                srcs["psyq"] = ps; srcs["psyq_t272"] = rewrite(ps, "t272")
        res = {}
        for tag, s in srcs.items():
            if s is None:
                res[tag] = {"err": "no cc1 output"}; continue
            if tag.endswith("t272") or tag == "all":
                src0 = base if tag != "psyq_t272" else srcs["psyq"]
                if s == src0:                      # the rule changed nothing: the base verdict stands
                    res[tag] = dict(res.get("base" if tag != "psyq_t272" else "psyq", {}), same_as_input=True)
                    continue
            res[tag] = {v: genuine_best(A, s, ctx["flags"], v, mv, scope, td) for v in
                        (VERS if tag in ("t272", "psyq_t272") else VERS[:1])}
        rec["res"] = res
        rec["status"] = "ok"
        return rec
    except Exception as exc:
        import traceback
        rec.update(status="error", err=("harness: " + "".join(traceback.format_exception_only(type(exc), exc)).strip())[:300])
        return rec
    finally:
        rec["secs"] = round(time.time() - t0, 1)
        shutil.rmtree(td, ignore_errors=True)


def exact(r, tag, ver="2.79"):
    x = (r.get("res") or {}).get(tag) or {}
    if x.get("same_as_input"):
        x = {k: v for k, v in x.items() if k != "same_as_input"}
    v = x.get(ver) or (x.get("2.79") if ver != "2.79" else None)
    return bool(v and v.get("exact"))


# ------------------------------------------------------------------------------------------------ report
def report(recs, step1):
    from common import rows
    by = {r["id"]: r for r in rows()}
    dep = {}
    tsv = ROOT / "docs/evidence/fidelity_step1_maspsx_dependent.tsv"
    for l in tsv.read_text().splitlines()[1:]:
        p = l.split("\t")
        dep[p[0]] = p[8]
    probe = set()
    for l in (ROOT / "work/fidelity/reorder_epilogue_probe.txt").read_text().splitlines():
        if l.strip():
            probe.add(l.split()[0])
    out = []
    ok = [r for r in recs if r.get("status") == "ok"]
    out.append(f"records {len(recs)}, ok {len(ok)}, errors {len(recs) - len(ok)}\n")

    def grp(r):
        g = step1.get(r["row"], {})
        if g.get("exact_versions"):
            return "genuine-exact (control)"
        c = dep.get(r["row"], "")
        if c in ("_maybe_unfill_return_delay", "_unfill_via_load_delay"):
            return c
        if r["row"] in probe:
            return "probe set, other cause"
        return "maspsx-dependent, other cause"
    tags = ["base", "all", "t272", "fndb"] + (["psyq", "psyq_t272"] if any("psyq" in (r.get("res") or {}) for r in ok) else [])
    out.append("| group | rows | " + " | ".join(tags) + " |")
    out.append("|---|---|" + "---|" * len(tags))
    G = defaultdict(list)
    for r in ok:
        G[grp(r)].append(r)
    for g in sorted(G, key=lambda k: -len(G[k])):
        rs = G[g]
        out.append(f"| {g} | {len(rs)} | " + " | ".join(
            str(sum(exact(r, t) for r in rs)) + ("" if t not in ("psyq", "psyq_t272") else f"/{sum(1 for r in rs if t in r.get('res', {}))}")
            for t in tags) + " |")
    out.append(f"| **all** | {len(ok)} | " + " | ".join(str(sum(exact(r, t) for r in ok)) for t in tags) + " |")
    out.append("")
    # by container x cell for t272
    out.append("| container | cell | rows | base | t272 (2.79) | t272 (2.77) | not t272-exact |")
    out.append("|---|---|---|---|---|---|---|")
    CC = defaultdict(list)
    for r in ok:
        CC[(r["container"], r["cell"])].append(r)
    for k in sorted(CC):
        rs = CC[k]
        miss = [r["row"].split("/")[1] for r in rs if not exact(r, "t272")]
        out.append(f"| {k[0]} | {k[1]} | {len(rs)} | {sum(exact(r, 'base') for r in rs)} | {sum(exact(r, 't272') for r in rs)} | "
                   f"{sum(exact(r, 't272', '2.77') for r in rs)} | {len(miss)} |")
    return "\n".join(out)


def load(path):
    recs = {}
    if path.exists():
        for l in path.read_text().splitlines():
            if l.strip():
                r = json.loads(l); recs[r["row"]] = r
    return recs


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--workers", type=int, default=8)
    ap.add_argument("--only")
    ap.add_argument("--cells", default=",".join(CELLS_2X))
    ap.add_argument("--psyq", action="store_true", help="also compile with the genuine SN CC1PSX")
    ap.add_argument("--one"); ap.add_argument("--worker", help=argparse.SUPPRESS)
    ap.add_argument("--journal", default=str(JOURNAL))
    ap.add_argument("--force", action="store_true")
    ap.add_argument("--report", action="store_true")
    a = ap.parse_args()
    from common import rows, parse_cfg
    by = {r["id"]: r for r in rows()}
    jpath = Path(a.journal)
    if a.report:
        step1 = load(ROOT / "work/fidelity/aspsx_diff.jsonl")
        print(report(list(load(jpath).values()), step1)); return
    if a.one or a.worker:
        rec = process_row(by[a.one or a.worker], psyq=a.psyq)
        print(json.dumps(rec, indent=None if a.worker else 1, separators=(",", ":") if a.worker else None)); return
    cells = set(a.cells.split(","))
    rs = [r for r in by.values() if parse_cfg(r["cfg"])[0] in cells]
    if a.only:
        ids = [x.strip() for x in (Path(a.only[1:]).read_text().split() if a.only.startswith("@") else a.only.split(","))]
        rs = [by[i] for i in ids if i in by]
    done = load(jpath)
    todo = [r for r in rs if a.force or done.get(r["id"], {}).get("status") != "ok"
            or (a.psyq and "psyq_cc1" not in done[r["id"]])]
    print(f"epilogue_model: {len(rs)} rows selected, {len(todo)} to compute", flush=True)
    OUT.mkdir(parents=True, exist_ok=True)
    A = _aspsx()

    def one(r):
        cmd = A.NICE + [sys.executable, str(Path(__file__)), "--worker", r["id"]] + (["--psyq"] if a.psyq else [])
        p = subprocess.run(cmd, capture_output=True, text=True, timeout=3600, cwd=str(ROOT))
        try:
            return json.loads(p.stdout.strip().splitlines()[-1])
        except Exception:
            return {"row": r["id"], "status": "error", "err": "worker: " + (p.stderr or p.stdout)[-300:]}
    t0 = time.time(); n = 0
    with ThreadPoolExecutor(max_workers=min(a.workers, 10)) as ex, open(jpath, "a") as fh:
        for rec in ex.map(one, todo):
            fh.write(json.dumps(rec, separators=(",", ":")) + "\n"); fh.flush()
            done[rec["row"]] = rec; n += 1
            if n % 50 == 0:
                print(f"  {n}/{len(todo)} {time.time() - t0:.0f}s", flush=True)
    with open(jpath, "w") as fh:
        for rid in sorted(done):
            fh.write(json.dumps(done[rid], separators=(",", ":")) + "\n")
    shutil.rmtree(A.TMP, ignore_errors=True)
    print(f"epilogue_model: done {n} rows in {time.time() - t0:.0f}s -> {jpath}", flush=True)


if __name__ == "__main__":
    main()
