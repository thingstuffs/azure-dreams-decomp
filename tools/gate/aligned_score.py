#!/usr/bin/env python3
"""Score candidate C files against retail bytes with LCS-aligned distance
(subs + indels over reloc-normalized words) instead of positional word counts.

Positional words_off is meaningless under length drift; this is the required
metric for any closeness claim in a wall/rebuild report (az-wall-deconstruct
Phase 5, az-c-rebuild loop). Promoted from work/wall_8003E758/score_configs.py.

Usage:
  auto     : python3 tools/aligned_score.py --func func_8004099C cand.c
             (overlay/container/config resolve via tools/az_target.py; an
              ambiguous name — main-EXE AND overlay bytes — errors and asks
              for --overlay/--main rather than guessing)
  main EXE : python3 tools/aligned_score.py --func func_8003E758 --main v3.c v4.c [--configs "cdk O2,cdk O1"]
  overlay  : python3 tools/aligned_score.py --func func_8004099C --overlay ovmovie \
                 --container work/s3_splat/extract/OVMOVIE.BIN cand.c \
                 [--configs "2.7.2-G0,2.7.2-G0 -fno-strength-reduce"]
  diff     : add --diff to print the underlying tool's positional disasm diff
  regions  : add --regions to print ALIGNED mismatch regions with disasm —
             read THIS (not --diff) to bucket residuals: positional listings
             show a one-word insertion as hundreds of shifted X rows, while
             the aligned view shows it as one insert region

Overlay --configs entries not in the default list are passed straight through
as --match-config strings, so any "GCCVER-GN [flags]" combo works.

CAVEAT (overlay legacy diff/region mode): overlay_func_compare.py truncates the
hex used by that display path to target length, so a build LONGER than retail
loses its tail there. `--summary-json` uses the compact oracle and retains the
full generated length and aligned tail indels.
Interpretation of the decomposition (both modes):
  high indels + low subs  -> layout/emission-order problem (fix source order, cheap)
  subs in register fields -> coloring/dialect (owner may not be C; stop grinding C)
  moved blocks double-count as indels (known artifact).
"""
import argparse
import importlib.util
import json
import os
import re
import subprocess
import sys
from difflib import SequenceMatcher

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
sys.path.insert(0, os.path.join(ROOT, "tools"))
import residue_class as RC
import az_target
import match as M


def _load_module(name, path):
    spec = importlib.util.spec_from_file_location(name, path)
    mod = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(mod)
    return mod


# Reuse the canonical reloc_suspect detector (work/g3/overlay_func_compare.py)
# instead of re-deriving the indels==0/length-match/all-substitutions formula
# here -- one definition, shared by both the overlay JSON path (which already
# carries the flag) and this tool's own main-EXE/human-readable paths (which
# compute subs/indels locally and would otherwise never see it).
OFC = _load_module("overlay_func_compare", os.path.join(ROOT, "work", "g3", "overlay_func_compare.py"))

MAIN_CONFIGS = [
    ("2.7.2 O2",       ["--gcc", "2.7.2", "--opt", "O2"]),
    ("2.7.2 O1",       ["--gcc", "2.7.2", "--opt", "O1"]),
    ("cdk O2",         ["--gcc", "2.7.2-cdk", "--opt", "O2"]),
    ("cdk O1",         ["--gcc", "2.7.2-cdk", "--opt", "O1"]),
    ("cdk O1+sched2",  ["--gcc", "2.7.2-cdk", "--opt", "O1", "--gcc-flags", "-fschedule-insns2"]),
    ("cdk O2 nocse2",  ["--gcc", "2.7.2-cdk", "--opt", "O2", "--gcc-flags", "-fno-rerun-cse-after-loop"]),
    ("cdk O2 noexp",   ["--gcc", "2.7.2-cdk", "--opt", "O2", "--gcc-flags", "-fno-expensive-optimizations"]),
    ("cdk O2 nosched", ["--gcc", "2.7.2-cdk", "--opt", "O2", "--gcc-flags", "-fno-schedule-insns -fno-schedule-insns2"]),
    ("2.8.0 O1",       ["--gcc", "2.8.0", "--opt", "O1"]),
    ("2.8.1 O1",       ["--gcc", "2.8.1", "--opt", "O1"]),
    # NB: match.py --psyq X --opt O1 silently runs -O2 (cc_psyq.sh hardcodes it);
    # the O1 psyq cell below overrides via --gcc-flags (last -O wins).
    ("psyq4.0 O2",     ["--psyq", "4.0", "--opt", "O2"]),
    ("psyq4.1 O2",     ["--psyq", "4.1", "--opt", "O2"]),
    ("psyq4.1 O1",     ["--psyq", "4.1", "--opt", "O2", "--gcc-flags", "-O1"]),
]

OVERLAY_CONFIGS = [
    "2.7.2-G0",
    "2.7.2-G0 -fno-strength-reduce",
    "2.7.2-G0 -fno-schedule-insns",
    "2.6.3-G0",
    "2.7.2-cdk-G0",
    "2.8.0-G0",
    "2.8.1-G0",
    # "2.8.1-G0 -fsn-hold-heuristic" and "2.8.1-sn0-G0" removed 2026-09-05:
    # both depended on the patched (non-stock) gcc-2.8.1 cc1 that was silently
    # installed into toolchain/compilers/gcc-2.8.1/ on 2026-07-24; 0 landed rows
    # carried either label. See docs/bridge_remediation_plan_20260905.md.
    "2.95.2-G0",
    "2.91.66-G0",
]

HEXRE = re.compile(r"^\s*(got|tgt): ([0-9a-f]+)$")
DIFFLINE_RE = re.compile(r"^  ([ X~]) \[\s*(\d+)\]")


def annotate_diff_lines(lines, got, tgt):
    """Mark every real word-level SUBSTITUTION line so reloc-level subs whose
    rendered disasm text is identical are still visible, not just the ones
    that happen to differ textually.

    The underlying tool (tools/match.py disasm_diff/word_diff) already tags
    each positional word pair '  ' equal / '~ ' masked j-jal reloc / 'X ' real
    mismatch -- 'X ' is exactly the aligned-score definition of a substitution
    when there is no indel drift (see module docstring: --diff is positional,
    --regions is indel-aware). This is purely a rendering pass: it reuses that
    same tag, replaces the leading marker with '!' on a real sub, and appends
    the raw words being compared so an identical-looking disasm pair is still
    provably a mismatch. Non-substitution lines pass through unchanged.
    """
    if got is None or tgt is None:
        return lines
    out = []
    for line in lines:
        m = DIFFLINE_RE.match(line)
        if m and m.group(1) == "X":
            idx = int(m.group(2))
            i = idx * 4
            gw, tw = got[i:i + 4], tgt[i:i + 4]
            if len(gw) == 4 and len(tw) == 4 and gw != tw:
                line = "!" + line[3:] + f"  raw 0x{gw.hex()} vs 0x{tw.hex()}"
        out.append(line)
    return out


def main_cmd(func, cfile, args, disasm=False, compact=False):
    cmd = ["python3", os.path.join(ROOT, "tools", "match.py"), func, cfile] + args
    if compact:
        cmd.append("--summary-json")
    elif not disasm:
        cmd.append("--no-disasm")
    return cmd


def overlay_cmd(func, cfile, overlay, config, container=None, disasm=False, compact=False):
    cmd = [
        "python3", os.path.join(ROOT, "work", "g3", "overlay_func_compare.py"),
        "--overlay", overlay, "--func", func, "--c-file", cfile,
        "--match-config", config,
    ]
    if compact:
        cmd.append("--summary-json")
    elif not disasm:
        cmd.append("--no-disasm")
    if container:
        cmd += ["--container", container]
    return cmd


HARNESS_ERROR = "HARNESS-ERROR"


def _run(cmd):
    """Run the underlying oracle once and reduce it to (status, got, tgt).

    ``status`` is ``"MATCH"``, ``"CFAIL"`` (the COMPILER rejected the candidate),
    a ``HARNESS-ERROR ...`` string (the DRIVER never reached the compiler), or
    ``None`` (a normal scored comparison; the hex walls are in got/tgt).

    Why HARNESS-ERROR is its own status (2026-09-01, wave_20260901_burndown):
    every oracle ``SystemExit`` -- "missing config; pass --match-config" when a
    row's DB ``config`` is null, "expected one row ... found 0/2", "unknown gcc
    version", the short/empty target-slice refusal -- writes to STDERR and
    leaves stdout empty.  This function used to discard the return code and the
    stderr entirely and hand main() a bare (None, None, None), which printed the
    same ``build-fail/no-hex`` line a real compile failure prints.  A sweep
    reading that output cannot tell "the C is broken" from "I invoked the driver
    wrong", so a config-contract mistake is banked as a CFAIL verdict against
    the candidate -- the class that re-served 19 already-compiling DUNGEON rows
    into CFAIL diagnosis lanes.  Name it, and it can never be mistaken again.
    """
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=600, cwd=ROOT)
    out = r.stdout
    if re.search(r"^MATCH", out, re.M):
        return "MATCH", None, None
    if re.search(r"^CFAIL", out, re.M):
        return "CFAIL", None, None
    got = tgt = None
    for line in out.splitlines():
        m = HEXRE.match(line)
        if m:
            if m.group(1) == "got":
                got = bytes.fromhex(m.group(2))
            else:
                tgt = bytes.fromhex(m.group(2))
    if (got is None or tgt is None) and r.returncode != 0:
        # The driver failed before producing a comparison: NOT a compile result.
        detail = (r.stderr or out or "").strip().splitlines()
        tail = " | ".join(line.strip() for line in detail[-3:])[:300]
        return f"{HARNESS_ERROR} rc={r.returncode}: {tail or 'no diagnostic'}", None, None
    return None, got, tgt


def _run_summary(cmd):
    """Run a compact underlying oracle and parse its sole JSON record."""
    r = subprocess.run(cmd, capture_output=True, text=True, timeout=600, cwd=ROOT)
    for line in reversed(r.stdout.splitlines()):
        try:
            record = json.loads(line)
        except json.JSONDecodeError:
            continue
        if record.get("schema") == "azure-clean.compiler-oracle.v1":
            return record
    raise RuntimeError(
        "compact oracle returned no JSON record: " + (r.stderr or r.stdout)[-300:])


def print_regions(got, tgt):
    """Print aligned (LCS) mismatch regions side by side with disasm."""
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_MIPS32, CS_MODE_LITTLE_ENDIAN
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 | CS_MODE_LITTLE_ENDIAN)

    def dis(b):
        out = []
        for i in range(0, len(b), 4):
            d = list(md.disasm(b[i:i + 4], 0))
            out.append(f"{d[0].mnemonic} {d[0].op_str}" if d else b[i:i + 4].hex())
        return out

    G, T = dis(got), dis(tgt)
    gn = [RC._norm(int.from_bytes(got[i:i + 4], "little")) for i in range(0, len(got), 4)]
    tn = [RC._norm(int.from_bytes(tgt[i:i + 4], "little")) for i in range(0, len(tgt), 4)]
    sm = SequenceMatcher(a=gn, b=tn, autojunk=False)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        print(f"--- {tag} got[{i1}:{i2}] tgt[{j1}:{j2}]")
        for k in range(max(i2 - i1, j2 - j1)):
            l = G[i1 + k] if i1 + k < i2 else ""
            r = T[j1 + k] if j1 + k < j2 else ""
            print(f"   {l:34s} | {r}")


def aligned_stats(got, tgt, strict=False):
    """Metric parity (Option C, 2026-07-21): overlay builds are LINKED with
    every call target resolved, so j/jal words are evidence and the reported
    totals must be STRICT — the masked flavor claimed TOTAL 0 on candidates
    whose call targets genuinely differ (func_80099954).  The unlinked
    main-EXE matcher keeps masking (targets unknowable there)."""
    return M.aligned_word_stats(got, tgt, mask_relocations=not strict)


def compact_results(args, configs, cmd_for, overlay):
    out = []
    for cfile in args.cfiles:
        evaluations = []
        errors = []
        for label, cfg in configs:
            try:
                rec = _run_summary(cmd_for(cfile, cfg, False, True))
            except subprocess.TimeoutExpired:
                errors.append({"config": label, "status": "TIMEOUT"})
                continue
            except Exception as exc:
                errors.append({"config": label, "status": "ERROR", "error": str(exc)[:300]})
                continue
            # overlay records already carry reloc_suspect (overlay_func_compare
            # stamps it before printing); main-EXE records come from match.py
            # directly and do not, so augment here too -- same shared function,
            # idempotent on records that already have it.
            evaluations.append(OFC._augment_reloc_suspect(rec))
        built = [r for r in evaluations if r.get("build_status") == "ok"]
        best = min(built, key=lambda r: (
            not bool(r.get("exact")), r["aligned"]["total"],
            r.get("words_off") if r.get("words_off") is not None else 10**9,
            r.get("config", ""))) if built else (evaluations[-1] if evaluations else None)
        item = {
            "c_file": cfile,
            "evaluated": len(evaluations),
            "build_failures": sum(r.get("build_status") == "failed" for r in evaluations),
            "best": best,
        }
        if errors:
            item["errors"] = errors
        out.append(item)
    print(json.dumps({
        "schema": "azure-clean.aligned-score.v1",
        "function": args.func,
        "overlay": overlay,
        "results": out,
    }, sort_keys=True, separators=(",", ":")))


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("cfiles", nargs="+")
    ap.add_argument("--func", required=True)
    ap.add_argument("--overlay", help="overlay name (ovmovie/town/dungeon...); auto-resolved via az_target when omitted")
    ap.add_argument("--main", action="store_true", help="force main-EXE mode (needed only if the name is vram-ambiguous)")
    ap.add_argument("--container", help="overlay container path (auto-resolved when omitted)")
    ap.add_argument("--configs", help="comma-separated labels to run (overlay mode: unknown labels pass through as match-config strings)")
    ap.add_argument("--diff", action="store_true", help="print the positional disasm diff for the best-scoring config")
    ap.add_argument("--regions", action="store_true", help="print ALIGNED mismatch regions (disasm) for the best-scoring config")
    ap.add_argument("--summary-json", action="store_true",
                    help="emit compact JSON with the best oracle record per C file")
    args = ap.parse_args()
    if args.summary_json and (args.diff or args.regions):
        ap.error("--summary-json cannot be combined with --diff/--regions")

    overlay, container = args.overlay, args.container
    if not overlay and not args.main:
        desc = az_target.resolve(args.func, overlay=None, main_exe=False)
        if desc["kind"] == "overlay":
            overlay = desc["overlay"]
            container = container or desc["container"]
            if not args.summary_json:
                print(f"resolved: overlay {overlay}, container {os.path.relpath(container, ROOT)}, "
                      f"first-pass config {desc.get('config')}")
        else:
            if not args.summary_json:
                print("resolved: main EXE")
    elif overlay and not container:
        desc = az_target.resolve(args.func, overlay=overlay)
        container = desc["container"]

    if overlay:
        labels = args.configs.split(",") if args.configs else OVERLAY_CONFIGS
        configs = [(c.strip(), c.strip()) for c in labels]
        cmd_for = lambda cfile, cfg, dis=False, compact=False: overlay_cmd(
            args.func, cfile, overlay, cfg, container, dis, compact)
        if not args.summary_json:
            print("NOTE overlay mode: build truncated to target length upstream; "
                  "indels past target end are invisible.")
            print("NOTE the TOTAL below is the GLOBAL-LCS aligned distance. "
                  "--summary-json reports the oracle's REGIONAL alignment total, "
                  "which is the number rosters/dossiers store as "
                  "aligned_distance and can be several points LOWER. "
                  "Do not compare one against the other and call the difference "
                  "a regression (2026-09-01: three CFAIL rows were reported as "
                  "'stale cache' on exactly that mix-up).")
    else:
        only = set(c.strip() for c in args.configs.split(",")) if args.configs else None
        configs = [(label, a) for label, a in MAIN_CONFIGS if only is None or label in only]
        # Unknown labels pass through as custom cells (parity with overlay
        # mode): "GCCVER OPT [flags...]" e.g. "2.7.2 O2 -G0" or
        # "2.7.2-cdk O2 -fno-strength-reduce -G0". Without this, per-row
        # non-default cells (the -G0 LIBSPU family) are unscorable here and
        # ledger refreshes mis-read them as score regressions.
        if only:
            known = {label for label, _ in MAIN_CONFIGS}
            for label in sorted(only - known):
                parts = label.split()
                if len(parts) < 2:
                    continue
                ver, opt, extra = parts[0], parts[1], parts[2:]
                a = (["--psyq", ver[4:]] if ver.startswith("psyq") else ["--gcc", ver]) + ["--opt", opt]
                if extra:
                    a += ["--gcc-flags", " ".join(extra)]
                configs.append((label, a))
        cmd_for = lambda cfile, cfg, dis=False, compact=False: main_cmd(
            args.func, cfile, cfg, dis, compact)

    if args.summary_json:
        compact_results(args, configs, cmd_for, overlay)
        return

    for cfile in args.cfiles:
        print(f"## {cfile}")
        results = []
        for label, cfg in configs:
            try:
                status, got, tgt = _run(cmd_for(cfile, cfg))
            except subprocess.TimeoutExpired:
                print(f"{label:28s} TIMEOUT")
                continue
            if status == "MATCH":
                print(f"{label:28s} *** MATCH ***")
                results.append((0, 0, label, cfg, {}, None, None))
                continue
            if isinstance(status, str) and status.startswith(HARNESS_ERROR):
                # The driver never reached the compiler -- print it as its own
                # line so no sweep can bank it as a verdict on the candidate.
                print(f"{label:28s} {status}")
                continue
            if got is None or tgt is None:
                print(f"{label:28s} build-fail/no-hex")
                continue
            subs, indels = aligned_stats(got, tgt, strict=bool(overlay))
            cl = RC.classify(got, tgt)
            reloc = OFC._reloc_suspect_flags(
                subs, indels, (len(got) + 3) // 4, (len(tgt) + 3) // 4)
            results.append((subs + indels, subs, label, cfg, cl, got, tgt))
            reloc_tag = (" RELOC-SUSPECT" if reloc["reloc_suspect"] else
                         " reloc-suspect~" if reloc["reloc_suspect_near_0_9"] else "")
            print(f"{label:28s} len {len(got)//4:3d}/{len(tgt)//4:3d}  subs {subs:3d}  indels {indels:3d}  "
                  f"TOTAL {subs+indels:3d}  class {cl.get('class')}  sig {';'.join(cl.get('signals', [])[:4])}"
                  f"{reloc_tag}")
        if results:
            results.sort(key=lambda r: r[0])
            best = results[0]
            print(f"BEST: {best[2]}  total={best[0]}")
            if args.regions and best[5] is not None:
                print(f"--- aligned regions at {best[2]} ---")
                print_regions(best[5], best[6])
            if args.diff:
                print(f"--- disasm diff at {best[2]} ---")
                r = subprocess.run(cmd_for(cfile, best[3], True),
                                   capture_output=True, text=True, timeout=600, cwd=ROOT)
                out = r.stdout
                # drop the got:/tgt: hex walls; keep status + disasm columns
                kept = [l for l in out.splitlines() if not HEXRE.match(l)]
                # mark every real substitution line ('!' + raw words) so a
                # reloc-level sub with identical rendered text is still
                # findable -- see annotate_diff_lines() docstring.
                print("\n".join(annotate_diff_lines(kept, best[5], best[6])))


if __name__ == "__main__":
    main()
