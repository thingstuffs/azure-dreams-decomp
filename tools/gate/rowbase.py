#!/usr/bin/env python3
"""Rowbase evidence: true link bases for alias regions (docs/rowbase_lane_phase2.md).

Single source of truth for consumers of ``config/overlays/<family>.rowbase.jsonl``.
Scoring-layer only: row identity (names, foff, size, target bytes) is never
changed here — only the vram a candidate is LINKED at, and which symbol name a
true-space TU defines. Landing-side consumers must pass ``proven_only=True``
(base_confidence "proven" = >=1 byte-exact recompile at the base); scoring uses
every record ("solved" = j-solve evidence, owner decision C).

Records are one JSON object per line:
  {"schema": "azure-clean.rowbase.v1", "region": ..., "foff_start": "0x..",
   "foff_end": "0x..", "delta": "0x..", "base_confidence": ..., "proof": ...}
Malformed or overlapping records fail loudly — silent fallback would quietly
re-poison the scores this lane exists to fix.
"""
from __future__ import annotations

import json
import re
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent

SCHEMA = "azure-clean.rowbase.v1"


def _records(family: str) -> list[dict]:
    path = ROOT / f"config/overlays/{family}.rowbase.jsonl"
    if not path.exists():
        return []
    out: list[dict] = []
    spans: list[tuple[int, int]] = []
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        try:
            rec = json.loads(line)
            if rec.get("schema") != SCHEMA:
                raise ValueError(f"schema {rec.get('schema')!r}")
            start = int(str(rec["foff_start"]), 0)
            end = int(str(rec["foff_end"]), 0)
            delta = int(str(rec["delta"]), 0)
            if not (0 <= start < end) or not rec.get("proof"):
                raise ValueError("bad extent or missing proof")
        except (ValueError, KeyError, TypeError) as exc:
            raise SystemExit(f"{path}:{lineno}: invalid rowbase record: {exc}")
        for ps, pe in spans:
            if start < pe and ps < end:
                raise SystemExit(f"{path}:{lineno}: overlapping rowbase regions")
        spans.append((start, end))
        out.append({"start": start, "end": end, "delta": delta, "rec": rec})
    return out


def delta_for(family: str, foff: int, *, proven_only: bool = False) -> int | None:
    for region in _records(family):
        if region["start"] <= foff < region["end"]:
            if proven_only and region["rec"].get("base_confidence") != "proven":
                return None
            return region["delta"]
    return None


def link_vram(family: str, foff: int, default_vram: int,
              *, proven_only: bool = False) -> int:
    delta = delta_for(family, foff, proven_only=proven_only)
    return default_vram if delta is None else foff + delta


def target_symbol(family: str, foff: int, synthetic: str, c_text: str,
                  *, proven_only: bool = False) -> str:
    """The symbol a candidate TU defines: in-region sources self-address in
    TRUE space, so prefer func_<true> when the TU defines it and not the
    synthetic name.

    A bank-table composite can define the row symbol through an assembler-name
    pin on an initialized object instead of a C function definition.  Treat
    that established shape as a definition too; otherwise a correctly renamed
    composite passes the naming gate but the scoring oracle tries to extract
    the obsolete synthetic symbol from its object.
    """
    delta = delta_for(family, foff, proven_only=proven_only)
    if delta is None:
        return synthetic
    true_name = f"func_{foff + delta:08X}"
    def defines(name: str) -> bool:
        c_function = re.search(r"\b" + re.escape(name) + r"\s*\(", c_text)
        asm_pin = re.search(
            r'__asm__?\s*\(\s*"' + re.escape(name) + r'"\s*\)', c_text)
        return c_function is not None or asm_pin is not None

    if defines(true_name) and not defines(synthetic):
        return true_name
    return synthetic


def _landed_rows_broken_at_true_base(family: str, region: dict) -> list[tuple[str, int]]:
    """Banked rows in ``region`` whose tree TU does NOT reproduce at the true base.

    Scoring already links at the true base for any region with a record (solved or
    proven — owner decision C), so this is a direct read of what promotion would do to
    the landing gate, not a simulation. Returns [(func, words_off)]; empty means the
    region's base is uniform across everything already banked in it.

    Fail-OPEN on infrastructure errors (a compare that will not run must not silently
    authorise a promotion, but it also must not be reported as a broken row) — an
    unscoreable row is skipped and named in the caller's output via words_off -1.
    """
    import glob
    import subprocess
    import sys as _sys

    matched_dir = ROOT / f"overlays/{family}/first_pass_matched"
    if not matched_dir.is_dir():
        return []
    try:
        rows = json.loads(
            (ROOT / f"overlays/{family}/overlay_first_pass_results.json").read_text())
    except (OSError, ValueError):
        return []
    foffs = {r["func_vram"]: int(r["foff"]) for r in rows
             if r.get("func_vram") and not r.get("rerun") and r.get("foff") is not None}
    configs = {r["func_vram"]: r.get("config") for r in rows
               if r.get("func_vram") and not r.get("rerun")}
    container = ROOT / f"work/s3_splat/extract/{family.upper()}_{family.upper()}.BIN"
    if not container.exists():
        return []

    broken: list[tuple[str, int]] = []
    for path in sorted(glob.glob(str(matched_dir / "func_*.c"))):
        name = Path(path).stem
        foff = foffs.get(name)
        if foff is None or not (region["start"] <= foff < region["end"]):
            continue
        best = None
        # The row's OWN recorded config first — that is the only config under which
        # the banked C was ever claimed to reproduce. Probing a fixed list instead
        # measures "does this row also happen to reproduce under some OTHER
        # compiler" and reports a legitimate config difference as a broken base
        # (2026-07-28: 6 false blockers on xfer_dungeon_A3000, all byte-exact at
        # the true base under their own config). The fixed list stays as a
        # fallback for rows with no recorded config.
        own = configs.get(name)
        probe = ([own] if own else []) + [c for c in ("2.8.1-G0", "2.7.2-cdk-G0",
                                                     "2.7.2-G0", "2.8.0-G0")
                                          if c != own]
        for cfg in probe:
            proc = subprocess.run(
                [_sys.executable, str(ROOT / "work/g3/overlay_func_compare.py"),
                 "--overlay", family, "--func", name, "--c-file", path,
                 "--match-config", cfg, "--container", str(container),
                 "--no-disasm", "--summary-json"],
                capture_output=True, text=True, cwd=ROOT)
            try:
                summary = json.loads(proc.stdout)
            except ValueError:
                continue
            if summary.get("exact") is True and summary.get("status") == "MATCH":
                best = 0
                break
            w = summary.get("words_off")
            if isinstance(w, int) and (best is None or w < best):
                best = w
        if best != 0:
            broken.append((name, best if isinstance(best, int) else -1))
    return broken


def _region_of_row(family: str, func: str) -> dict:
    """The rowbase record covering ``func``'s foff, fail-loud. Read-only."""
    regions = _records(family)  # fail-loud parse + overlap check first
    rows = json.loads(
        (ROOT / f"overlays/{family}/overlay_first_pass_results.json").read_text())
    hits = [r for r in rows if r.get("func_vram") == func and not r.get("rerun")]
    if len(hits) != 1:
        raise SystemExit(f"promote: expected one row for {func}, found {len(hits)}")
    foff = int(hits[0]["foff"])
    region = next((r for r in regions if r["start"] <= foff < r["end"]), None)
    if region is None:
        raise SystemExit(f"promote: {func} (foff 0x{foff:X}) is in no rowbase region")
    region = dict(region)
    region["foff"] = foff
    return region


def promotion_preflight(family: str, func: str) -> dict:
    """READ-ONLY dry run of ``promote``'s identity pre-flight.

    Same code path the real promotion takes, with nothing compiled and nothing
    written — the receipt for "would promoting this region be refused?".
    """
    import rowbase_naming_debt  # local: rowbase_naming_debt imports this module
    region = _region_of_row(family, func)
    out = rowbase_naming_debt.promotion_identity_preflight(family, region)
    out["base_confidence"] = region["rec"].get("base_confidence")
    out["proof_func"] = func
    out["dry_run"] = True
    return out


def promote(family: str, func: str, candidate: str, config: str) -> dict:
    """Promote the solved region containing ``func`` to proven (phase-2 item 3,
    owner-approved): a candidate that recompiles byte-exact at the region base
    IS the T1 recompile proof. Fail-closed — the proof compile runs NOW through
    the isolation compare (linked-strict, rowbase-aware); no cached record is
    trusted. Region extents are never changed here, only ``base_confidence``,
    and the original j-solve proof text is preserved."""
    import hashlib
    import subprocess
    import sys as _sys

    path = ROOT / f"config/overlays/{family}.rowbase.jsonl"
    region = _region_of_row(family, func)
    foff = region["foff"]
    rec = region["rec"]
    if rec.get("base_confidence") == "proven":
        return {"region": rec["region"], "status": "already-proven"}
    if rec.get("base_confidence") != "solved":
        raise SystemExit(f"promote: region {rec['region']} is "
                         f"{rec.get('base_confidence')!r}, not 'solved'")
    # IDENTITY PRE-FLIGHT (option 3, work/debt_20260729/opt3_region_qualified_names_spec.md
    # §4.1/§5.2 B7). Promotion is a BATCH mint: the instant this region turns
    # proven, owner decision B (docs/rowbase_lane_phase2.md item 2) gives every
    # already-landed row in it a TRUE-space name. The old screen refused that
    # plan whenever any minted BARE name was already defined somewhere in the
    # family — which was a false blocker, because a bare true name is a RAM-SLOT
    # LABEL, not an identity: two functions in two DIFFERENT rowbase regions
    # legitimately share one. (That false blocker is exactly what stopped
    # sweep_0D312D0: func_80D12E64 -> func_80172664, "already owned" by
    # func_80C40E64 at foff 0xBC0E64, a different region entirely.)
    #
    # What is left is the real, structural question. Within ONE region the delta
    # is a single constant, so foff -> true name is injective (RIA, spec §1.4):
    # two DISTINCT rows minting one identity is impossible while the evidence is
    # sound, and therefore corruption rather than an owner call. The pre-flight
    # asserts that and returns the legal cross-region slot shares as a census.
    # Runs before the proof compile because it is pure file reads: a doomed
    # promotion fails in seconds, not builds.
    import rowbase_naming_debt  # local: rowbase_naming_debt imports this module
    preflight = rowbase_naming_debt.promotion_identity_preflight(family, region)
    # container must be family-resolved: the compare tool's --container default
    # is the DUNGEON bin, which false-NOMATCHes every other family (the
    # container-resolution defect family — collect container-null, Flag-A).
    container = ROOT / f"work/s3_splat/extract/{family.upper()}_{family.upper()}.BIN"
    if not container.exists():
        raise SystemExit(f"promote: no container for family {family!r}: {container}")
    proof = subprocess.run(
        [_sys.executable, str(ROOT / "work/g3/overlay_func_compare.py"),
         "--overlay", family, "--func", func, "--c-file", candidate,
         "--match-config", config, "--container", str(container),
         "--no-disasm", "--summary-json"],
        capture_output=True, text=True, cwd=ROOT)
    try:
        summary = json.loads(proof.stdout)
    except json.JSONDecodeError:
        raise SystemExit(f"promote: proof compile produced no summary "
                         f"(rc={proof.returncode}):\n{proof.stderr[-800:]}")
    if not (proof.returncode == 0 and summary.get("exact") is True
            and summary.get("status") == "MATCH"):
        raise SystemExit(f"promote: proof compile is NOT byte-exact "
                         f"(rc={proof.returncode} {summary.get('status')} "
                         f"words_off={summary.get('words_off')}) "
                         f"— region {rec['region']} stays solved")
    # PRE-FLIGHT (2026-07-27): promotion moves the LANDING-SIDE link base for every row
    # in the region, banked rows included — they were landed while it was `solved`, so
    # the gate staged them at the SYNTHETIC vram. Promoting into a region that holds a
    # banked row which does not reproduce at the TRUE base cannot help: that row's gate
    # window will not verify, so nothing new in the window can land either. Fix the row
    # first, then promote.
    #
    # CAREFUL ABOUT THE CAUSAL CLAIM. On sweep_0C0B000 this check fires for
    # func_80BEB814 — but that row was ALREADY failing before any promotion: the gate
    # baseline on its window fails at the identical byte with the region left `solved`
    # and nothing staged. It landed cleanly on 2026-07-18 and regressed later
    # (1 word: a link-address-sensitive jal->j at word 15), so the promotion was the
    # messenger, not the cause. A 40-row random sample of banked dungeon rows found
    # 39/40 still reproducing, so that is one stale row, not a systemic regression.
    #
    # Note the instrument's limit: this scores each TU in ISOLATION, while the gate
    # builds a whole window. A residue that turns on whether a callee is present (jal vs
    # j at a call site) can read differently in the two. Treat a hit here as "this row
    # needs looking at before the region is promoted", which is exactly the action it
    # blocks on — not as proof that promotion would have caused it.
    blockers = _landed_rows_broken_at_true_base(family, region)
    if blockers:
        raise SystemExit(
            f"promote: REFUSED — region {rec['region']} contains banked rows that do not "
            f"reproduce at the true base: "
            + "; ".join(f"{f} (words_off {w})" for f, w in blockers)
            + ". Promoting cannot help while those rows are broken — their gate windows "
              "will not verify, so nothing else in the window can land either. This may "
              "predate the promotion (check the gate baseline with the region left as-is "
              "before blaming it). Repair the banked row, then promote.")
    sha = hashlib.sha256(Path(candidate).read_bytes()).hexdigest()[:12]
    true_vram = foff + region["delta"]
    rec["base_confidence"] = "proven"
    rec["proof"] = (f"{rec['proof']}; PROMOTED solved->proven: byte-exact "
                    f"recompile {func} at true base 0x{true_vram:08X} "
                    f"(candidate sha {sha} @ {config}, linked-strict isolation "
                    f"compare, phase-2 item-3 hook)")
    lines = path.read_text().splitlines()
    replaced = 0
    for i, line in enumerate(lines):
        s = line.strip()
        if not s or s.startswith("#"):
            continue
        parsed = json.loads(s)
        if (parsed.get("region") == rec["region"]
                and parsed.get("foff_start") == rec["foff_start"]):
            lines[i] = json.dumps(rec)
            replaced += 1
    if replaced != 1:
        raise SystemExit(f"promote: matched {replaced} jsonl lines for region "
                         f"{rec['region']} — refusing to write")
    path.write_text("\n".join(lines) + "\n")
    _records(family)  # re-parse: fail loudly if the write broke anything
    return {"region": rec["region"], "status": "promoted",
            "true_base": f"0x{true_vram:08X}", "proof_func": func,
            # informational census from the identity pre-flight: legal
            # cross-region RAM-slot shares this mint creates (spec §5.4).
            "identities": preflight["identities"],
            "slot_shares": len(preflight["slot_shares"])}


if __name__ == "__main__":
    import argparse
    ap = argparse.ArgumentParser(description=__doc__)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("promote", help="promote a solved region to proven via a "
                       "byte-exact recompile proof (phase-2 item 3)")
    p.add_argument("--family", required=True)
    p.add_argument("--func", required=True)
    p.add_argument("--candidate", required=True)
    p.add_argument("--config", required=True)
    p.set_defaults(fn=lambda a: promote(a.family, a.func, a.candidate, a.config))
    q = sub.add_parser("preflight", help="READ-ONLY: what promoting the region "
                       "containing --func would do to the identity space "
                       "(no compile, no write)")
    q.add_argument("--family", required=True)
    q.add_argument("--func", required=True)
    q.set_defaults(fn=lambda a: promotion_preflight(a.family, a.func))
    args = ap.parse_args()
    print(json.dumps(args.fn(args), indent=1))
