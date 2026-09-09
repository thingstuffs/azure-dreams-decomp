#!/usr/bin/env python3
"""Compare one overlay C candidate against its recorded retail function bytes."""

from __future__ import annotations

import argparse
import atexit
import importlib.util
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path
from typing import Any


ROOT = Path(__file__).resolve().parents[2]
MATCH_PY = ROOT / "tools/match.py"
TOOLS_DIR = ROOT / "tools"
DEFAULT_CONTAINER = ROOT / "work/s3_splat/extract/DUNGEON_DUNGEON.BIN"
CC_SH = ROOT / "tools/cc.sh"
NM = "mipsel-linux-gnu-nm"

# This file is invoked directly from work/g3 by the census controller.  A
# spec-loaded match.py still resolves its normal sibling imports through
# sys.path, so make the repository tools directory explicit instead of
# depending on a caller-provided PYTHONPATH.
if str(TOOLS_DIR) not in sys.path:
    sys.path.insert(0, str(TOOLS_DIR))

spec = importlib.util.spec_from_file_location("match", MATCH_PY)
M = importlib.util.module_from_spec(spec)
assert spec.loader is not None
spec.loader.exec_module(M)

# Linker-script assignment line, e.g. "func_80024EEC = 0x80024EEC;" or
# "D_800814A0 = 0x800814A0; // type:data" -- used to read match.py's catalog files.
_SYM_ASSIGN = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=")
# Overlay-local symbol whose retail address is encoded in its own name.
_NAME_ENCODED = re.compile(r"(func|D)_([0-9A-Fa-f]{8})$")
_RENAMED: dict[str, str] | None = None

def _renamed_symbols() -> dict[str, str]:
    """readable name -> original func_<addr> from config/names.tsv (tools/ccproc.py's alias table)."""
    global _RENAMED
    if _RENAMED is None:
        _RENAMED = {}
        p = ROOT / "config" / "names.tsv"
        if p.exists():
            for raw in p.read_text(errors="replace").splitlines():
                cols = raw.split("#", 1)[0].rstrip().split("\t")
                if len(cols) >= 3 and cols[1].strip() and cols[2].strip() and cols[2].strip() != cols[1].strip():
                    _RENAMED[cols[2].strip()] = cols[1].strip()
    return _RENAMED


# LEAD 12b: the per-function as-flags lookup was FIRST written here, then
# needed verbatim by three more consumers (the synth scorer close_gap.build_got,
# the landing gate overlay_local_gate.compile_c_segments, and the cache identity
# compile_cache_identity.assembler_input_manifest).  Two implementations of an
# evidence lookup is two chances to disagree -- and a disagreement here means a
# row scores exact in one tool and not in another, or a dial compile and a
# non-dial compile share a cache key.  So the implementation moved to
# tools/overlay_as_flags.py and this module re-exports it unchanged; the
# docstrings, the schema, the true_name aliasing and the loud SystemExit on a
# malformed/proofless/conflicting record all live there now.
import overlay_as_flags as _AS_FLAGS      # noqa: E402  (TOOLS_DIR pinned above)
import rowbase as _ROWBASE                # noqa: E402  (TOOLS_DIR pinned above)

overlay_as_flags_table = _AS_FLAGS.overlay_as_flags_table
default_as_flags = _AS_FLAGS.default_as_flags


def catalog_symbols() -> set[str]:
    """Every symbol name match.py can already resolve when it links (see
    build_text): func names from func_sizes.json (FUNC_NAMES), already-named
    library funcs/data (NAMED_SYMS_LIST), and the two generated undefined_*
    linker-script catalogs. Anything here keeps its catalog-provided address;
    the name-encoded fallback only fills the gaps."""
    names: set[str] = set(M.FUNC_NAMES)
    names.update(name for name, _ in M.NAMED_SYMS_LIST)
    for path in (M.UNDEF_SYMS, M.UNDEF_FUNCS):
        p = Path(path)
        if not p.exists():
            continue
        for raw in p.read_text(errors="replace").splitlines():
            hit = _SYM_ASSIGN.match(raw.split("//", 1)[0])
            if hit:
                names.add(hit.group(1))
    return names


def object_undefined_symbols(c_file: Path, gcc_ver: str, gcc_flags: str) -> set[str] | None:
    """Compile a throwaway object through the same pinned pipeline build_text
    uses and list its undefined externals via ``nm -u``. Which externals a TU
    references depends only on its C source, so this set matches the object
    build_text will link. Returns None if the scratch compile fails (build_text
    will then surface the real compile error)."""
    with tempfile.TemporaryDirectory() as td:
        obj = os.path.join(td, "scan.o")
        proc = subprocess.run(
            [str(CC_SH), str(c_file), obj, gcc_ver, gcc_flags, ""],
            capture_output=True,
            text=True,
        )
        if proc.returncode != 0 or not os.path.exists(obj):
            return None
        nm = subprocess.run([NM, "-u", obj], capture_output=True, text=True)
        undef: set[str] = set()
        for line in nm.stdout.splitlines():
            parts = line.split()
            if len(parts) >= 2 and parts[-2] == "U":
                undef.add(parts[-1])
        return undef


def inject_name_encoded_symbols(
    c_file: Path, gcc_ver: str, gcc_flags: str, target: str
) -> tuple[list[str], list[str]]:
    """Port of the overlay gate's idea to this isolation harness: for every
    undefined ``func_XXXXXXXX``/``D_XXXXXXXX`` external NOT already covered by
    match.py's catalogs, synthesize ``SYM = 0xADDR;`` (address parsed from the
    name) into the link so ld resolves the relocation instead of failing and
    silently falling back to the UNLINKED object (which reads every reloc as 0
    and yields phantom word diffs).

    func_ names are appended to FUNC_NAMES (build_text writes them name-encoded);
    D_ names are appended to NAMED_SYMS_LIST as an absolute value. Catalog
    entries are never touched, so their addresses take precedence.

    Returns (injected, unresolved): injected symbols we defined, and undefined
    symbols we could neither find in a catalog nor name-encode (ld will still
    fail on these)."""
    undef = object_undefined_symbols(c_file, gcc_ver, gcc_flags)
    if undef is None:
        return [], []
    catalog = catalog_symbols()
    injected: list[str] = []
    unresolved: list[str] = []
    renamed = _renamed_symbols()
    for name in sorted(undef):
        if name == target or name in catalog:
            continue
        hit = _NAME_ENCODED.fullmatch(name)
        if hit is None and name in renamed:
            # a readable name from config/names.tsv (the defining TU aliases it to its func_<addr>);
            # this TU only references it, so the address comes from the original symbol
            hit = _NAME_ENCODED.fullmatch(renamed[name])
            if hit is not None:
                M.NAMED_SYMS_LIST.append((name, f"0x{int(hit.group(2), 16):08X}"))
                injected.append(name)
                continue
        if hit is None:
            unresolved.append(name)
            continue
        addr = int(hit.group(2), 16)
        if hit.group(1) == "func":
            M.FUNC_NAMES.append(name)
        else:
            M.NAMED_SYMS_LIST.append((name, f"0x{addr:08X}"))
        injected.append(name)
    return injected, unresolved


def cfg_path(raw: str | Path) -> Path:
    p = Path(raw)
    return p if p.is_absolute() else ROOT / p


def split_config(label: str) -> tuple[str, str]:
    # Canonical: tools/match.py parse_config_label handles both the plus
    # dialect ("2.7.2+-fno-strength-reduce") and the gate's space dialect
    # ("2.7.2-cdk -G0 -fno-schedule-insns") identically everywhere.
    return M.parse_config_label(label)


def compiler_for(ver: str) -> str:
    matches = [p for p in M.COMPILERS if p.endswith("gcc-" + ver)]
    if not matches:
        raise SystemExit(f"unknown gcc version {ver}")
    return matches[0]


def load_rows(path: Path) -> list[dict[str, Any]]:
    with path.open() as f:
        rows = json.load(f)
    if not isinstance(rows, list):
        raise SystemExit(f"{path} must contain a JSON list")
    return rows


def _geometry_matches(row: dict[str, Any], key: str, expected: int | None) -> bool:
    if expected is None:
        return True
    try:
        return int(row[key]) == expected
    except (KeyError, TypeError, ValueError):
        return False


def find_row(func: str, overlay: str, *, foff: int | None = None,
             vram: int | None = None, size: int | None = None) -> dict[str, Any]:
    path = ROOT / f"overlays/{overlay}/overlay_first_pass_results.json"
    hits = [
        row for row in load_rows(path)
        if (row.get("func_vram") == func and not row.get("rerun")
            and _geometry_matches(row, "foff", foff)
            and _geometry_matches(row, "vram", vram)
            and _geometry_matches(row, "size", size))
    ]
    if len(hits) != 1:
        geometry = ", ".join(
            f"{key}={value:#x}" for key, value in (
                ("foff", foff), ("vram", vram), ("size", size))
            if value is not None)
        suffix = f" with {geometry}" if geometry else ""
        raise SystemExit(
            f"expected one row for {func}{suffix} in {path}, found {len(hits)}")
    return hits[0]


def rowbase_link_vram(overlay: str, foff: int, default_vram: int) -> tuple[int, dict[str, Any] | None]:
    """True link base for rows in proven alias regions (rowbase evidence lane).

    Some container regions load at a vram that differs from the synthetic row
    identity (gap probes 2026-07-19: the j->0x8016/0x8017xxxx words across the
    dungeon corpus are functions' OWN local jumps in their true address space;
    at the synthetic base they are unclosable by any C shape). Evidence lives
    in config/overlays/<overlay>.rowbase.jsonl — one JSON record per line:
      {"schema": "azure-clean.rowbase.v1", "region": <name>,
       "foff_start": "0x..", "foff_end": "0x..", "delta": "0x..",
       "base_confidence": ..., "proof": <how the base was proven>}
    Proof standard (owner-approved 2026-07-19): >=2 local j's solving one base
    (or a jump-table delta fingerprint) + >=1 byte-exact recompile at that
    base. Returns (link_vram, matched_record); rows outside every region keep
    the synthetic vram. Malformed evidence fails loudly — silent fallback
    would quietly re-poison the scores this lane exists to fix."""
    path = ROOT / f"config/overlays/{overlay}.rowbase.jsonl"
    if not path.exists():
        return default_vram, None
    regions: list[dict[str, Any]] = []
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        try:
            rec = json.loads(line)
            if rec.get("schema") != "azure-clean.rowbase.v1":
                raise ValueError(f"schema {rec.get('schema')!r}")
            start = int(str(rec["foff_start"]), 0)
            end = int(str(rec["foff_end"]), 0)
            delta = int(str(rec["delta"]), 0)
            if not (0 <= start < end) or not rec.get("proof"):
                raise ValueError("bad extent or missing proof")
        except (ValueError, KeyError, TypeError) as exc:
            raise SystemExit(f"{path}:{lineno}: invalid rowbase record: {exc}")
        for prev in regions:
            if start < prev["end"] and prev["start"] < end:
                raise SystemExit(
                    f"{path}:{lineno}: region overlaps {prev['rec'].get('region')}")
        regions.append({"start": start, "end": end, "delta": delta, "rec": rec})
    for region in regions:
        if region["start"] <= foff < region["end"]:
            return foff + region["delta"], region["rec"]
    return default_vram, None


def word_mismatch_count(got: bytes, target: bytes,
                        mask_relocations: bool = True) -> int:
    count = 0
    for i in range(0, len(target), 4):
        g = got[i : i + 4]
        t = target[i : i + 4]
        if g == t:
            continue
        if mask_relocations and len(g) == 4:
            gw = int.from_bytes(g, "little")
            tw = int.from_bytes(t, "little")
            if (gw >> 26) == (tw >> 26) and (tw >> 26) in (2, 3):
                continue
        count += 1
    return count


def linked_words_equal(got: bytes, target: bytes) -> bool:
    """Strict compare after build_text linked the function at its retail VRAM.

    The generic main-EXE matcher masks j/jal operands because an unlinked object
    cannot know them.  This overlay harness injects every name-encoded external
    and links at the target VRAM, so those operands are resolved evidence.  A
    masked compare accepted a jump to a local epilogue instead of retail's
    shared epilogue; the full window gate then correctly rejected the source.
    """
    return (len(got) >= len(target) and got[:len(target)] == target and
            all(byte == 0 for byte in got[len(target):]))


_RELOC_SUSPECT_NEAR_RATIO = 0.9


def _reloc_suspect_flags(substitutions: int | None, indels: int | None,
                          generated_words: int | None,
                          target_words: int | None) -> dict[str, Any]:
    """Flag the whole-body positional-shift artifact: indels==0, generated
    length == target length, and EVERY word differs (substitutions ==
    target_words). That signature is almost always a relocation/link-base/
    config artifact (wrong lineage, wrong link base, a stale evidence file,
    ...) -- NOT N real words of codegen divergence.

    Historical damage (work/reports/zq_maspsx_leads_20260714.md, "Mechanism
    friction & improvement ideas" #2): a banked candidate scored 47/47
    all-substitutions at the wrong config/link base and the residue classifier
    stamped it ``const-remat``, which was plausible enough to hide the
    artifact for days. The 2026-07-24 func_81881F60 vacuous-compare (a
    short/empty target slice producing false MATCHes) was an adjacent disease
    in the same family: a harness-level artifact masquerading as a real
    signal.

    Returns additive-only flags, never gating or replacing any existing
    field:
      - ``reloc_suspect``: the strict/primary signal (substitutions ==
        target_words, indels == 0, matching length).
      - ``reloc_suspect_ratio``: substitutions / target_words when indels==0
        and length matches, else None -- lets a caller apply its own bar.
      - ``reloc_suspect_near_0_9``: a lower-bar companion (ratio >= 0.9) for
        the same smell when a handful of words happen to coincide by chance.
        This is a superset of ``reloc_suspect`` (1.0 >= 0.9); check the strict
        flag first, it is the historically-documented signature.
    """
    flags: dict[str, Any] = {
        "reloc_suspect": False,
        "reloc_suspect_ratio": None,
        "reloc_suspect_near_0_9": False,
    }
    if (indels != 0 or not target_words or generated_words != target_words
            or substitutions is None):
        return flags
    ratio = substitutions / target_words
    flags["reloc_suspect_ratio"] = ratio
    flags["reloc_suspect"] = substitutions == target_words
    flags["reloc_suspect_near_0_9"] = ratio >= _RELOC_SUSPECT_NEAR_RATIO
    return flags


def _augment_reloc_suspect(record: dict[str, Any]) -> dict[str, Any]:
    """Merge :func:`_reloc_suspect_flags` into a compiler-oracle summary
    record in place, reading the ``aligned``/``length_words`` fields the
    record already carries. Additive only -- never touches an existing key."""
    aligned = record.get("aligned") or {}
    lw = record.get("length_words") or {}
    record.update(_reloc_suspect_flags(
        aligned.get("substitutions"), aligned.get("indels"),
        lw.get("generated"), lw.get("target")))
    return record


_CANONICAL_NORETURN = {"", ".town", ".dungeon", ".ovmovie"}


def _assert_evidence_not_clobbered(ev_mod: Any, c_text: str) -> None:
    """Fail closed if the selected maspsx noreturn evidence would silently drop
    the candidate's OWN zero-arg noreturn declarations, or if it points at a
    writable path inside config/.

    Historical defect (residual_routing_20260712.md A2/B5, zq_maspsx_leads P1):
    overlay_func_compare force-pointed ``$MASPSX_NORETURN_FILE`` at an often-empty
    per-family census, suppressing the LEAD-18 self-serve so a candidate's
    ``noreturn`` tail calls stayed ``jal`` and never matched retail's ``j``. The
    fix (``evidence_env_with_candidate``) unions the candidate's decls into a
    scratch file; this guard makes any regression to the clobber path impossible:
    the effective noreturn set MUST contain every symbol the candidate declares,
    and a merged/self-serve file MUST live outside config/ so a compare can never
    overwrite a tracked census."""
    candidate = ev_mod.candidate_noreturn_syms(c_text)
    nr_file = os.environ.get("MASPSX_NORETURN_FILE") or str(ev_mod.DEFAULT_NORETURN_FILE)
    effective = ev_mod.load_noreturn_file(nr_file)
    missing = sorted(candidate - effective)
    if missing:
        raise SystemExit(
            "overlay_func_compare: maspsx noreturn evidence CLOBBERED -- the "
            f"candidate declares zero-arg noreturn {missing} but the effective "
            f"$MASPSX_NORETURN_FILE ({nr_file}) omits them, so the jal->j "
            "tail-call conversion would silently not fire. Refusing to compare "
            "against a clobbered evidence set (see evidence_env_with_candidate).")
    config_dir = str((ev_mod.ROOT / "config").resolve())
    canonical = {str((ev_mod.ROOT / f"config/noreturn_syms{sfx}.txt").resolve())
                 for sfx in _CANONICAL_NORETURN}
    resolved = str(Path(nr_file).resolve())
    if resolved.startswith(config_dir + os.sep) and resolved not in canonical:
        raise SystemExit(
            f"overlay_func_compare: $MASPSX_NORETURN_FILE points inside config/ at "
            f"a non-canonical path ({nr_file}); a merged/self-serve evidence file "
            "must live in scratch so a compare can never overwrite a tracked census.")


def _attach_assembly(record: dict, asm_output: str | None) -> None:
    """Record the raw compiler assembly build_text just published (path/size/sha256).

    Mirrors match.py's `compiler_assembly` key so both verifier surfaces expose the
    scored assembly the same way; without it the metered wave contract would still
    have to tell overlay workers to compile the candidate themselves.
    """
    if not asm_output:
        return
    assembly = M._assembly_record(asm_output)
    if assembly:
        record["compiler_assembly"] = assembly
    # The post-maspsx listing rides the SAME derived path (no second flag), so the
    # overlay branch cannot end up publishing one listing and not the other -- the
    # failure mode that kept --asm-output overlay-blind for 62 waves.
    maspsx = M._assembly_record(M.maspsx_assembly_path(asm_output))
    if maspsx:
        record["maspsx_assembly"] = maspsx


def _attach_regional_alignment(record: dict, got: bytes | None,
                               target: bytes) -> None:
    """Attach optional linked-strict regional alignment enrichment.

    ``regional_alignment_signature`` lives in ``match.py`` so the overlay and
    main-EXE scoring surfaces share one regional/LCS implementation.  This is
    an additive summary field only: compute it after a successful build, using
    the same effective stream as ``compiler_oracle_summary`` (accepted all-zero
    padding after the target is trimmed), with relocation masking disabled (the
    overlay path links at the target address), and never let it participate in
    the scalar score, status, or exit code.
    The helper is optional during rolling upgrades of the two verifier modules;
    an absent or failing enrichment leaves the ordinary summary untouched.

    Do not pass a quartile count here.  The helper's default quartile policy is
    part of its shared API; a caller-specific value would make otherwise
    identical overlay and main-EXE records incomparable.
    """
    if got is None:
        return
    regional = getattr(M, "regional_alignment_signature", None)
    if not callable(regional):
        return
    # Keep regional candidate_words and aligned totals on the same stream as
    # compiler_oracle_summary: linked-strict accepts zero-filled alignment
    # padding after retail and removes it before scoring.  Passing raw ``got``
    # here would report a phantom regional indel/length for an otherwise
    # accepted padded build.
    effective_got = got
    if len(got) > len(target) and all(byte == 0 for byte in got[len(target):]):
        effective_got = got[:len(target)]
    try:
        stats = regional(effective_got, target, mask_relocations=False)
    except Exception:
        # Regional alignment is diagnostic enrichment, not verdict machinery.
        # A rollout edge case must not change the linked-strict result or make
        # summary-json fail.
        return
    if stats is not None:
        record["regional_alignment"] = stats


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--overlay", required=True)
    parser.add_argument("--func", required=True)
    parser.add_argument("--foff", type=lambda value: int(value, 0), default=None,
                        help="exact target file offset (split-identity discriminator)")
    parser.add_argument("--vram", type=lambda value: int(value, 0), default=None,
                        help="exact target VRAM (split-identity discriminator)")
    parser.add_argument("--size", type=lambda value: int(value, 0), default=None,
                        help="exact target byte size (split-identity discriminator)")
    parser.add_argument("--c-file", required=True)
    parser.add_argument("--as-flags", dest="as_flags", default=None,
                        help="maspsx/as flags for this compile (LEAD 12b). Use the '=' "
                             "spelling -- --as-flags=\"--expand-div\" -- a value starting "
                             "with '-' cannot follow a space. Default: the per-function "
                             "lookup in "
                             "default_as_flags() -- config/overlays/<overlay>"
                             ".as_flags.jsonl then match.DEFAULT_FUNC_AS_FLAGS, for the "
                             "row name and its rowbase true name -- and empty when "
                             "neither has evidence (the pre-LEAD-12b behaviour). Pass "
                             "\"\" to force the empty baseline over a lookup hit.")
    parser.add_argument("--match-config", default=None)
    parser.add_argument("--container", default=str(DEFAULT_CONTAINER))
    parser.add_argument("--no-disasm", action="store_true")
    parser.add_argument("--summary-json", action="store_true",
                        help="emit one compact compiler-oracle JSON record; suppress hex/diffs")
    parser.add_argument("--asm-output", default=None,
                        help="publish the raw gcc -S output this call scored to this path "
                             "(atomic; the record carries its path/size/sha256 under "
                             "compiler_assembly). Wave workers read it instead of "
                             "invoking gcc on a full candidate themselves.")
    args = parser.parse_args()
    # Same guards match.py enforces: the published assembly must correspond to
    # exactly the one compile whose record is being printed.
    if args.asm_output and not args.summary_json:
        parser.error("--asm-output requires --summary-json")

    # Per-container maspsx evidence selection (tools/overlay_evidence.py):
    # town/dungeon evidence must never fire on the other family's compile
    # (0x80080000 vram aliasing). Set BEFORE any compile below -- both the
    # direct CC_SH calls and match.py's maspsx subprocess inherit os.environ.
    # LEAD-18 self-serve: the candidate is compiled in isolation, OUTSIDE the
    # dirs the per-family census scans, so its own zero-arg noreturn decls are
    # unioned into $MASPSX_NORETURN_FILE here (the census alone would leave the
    # jal->j tail-call conversion inert). Scratch dir lives for the whole run.
    ev_spec = importlib.util.spec_from_file_location(
        "overlay_evidence", ROOT / "tools/overlay_evidence.py")
    ev_mod = importlib.util.module_from_spec(ev_spec)
    assert ev_spec.loader is not None
    ev_spec.loader.exec_module(ev_mod)
    c_file = cfg_path(args.c_file)
    try:
        c_text = c_file.read_text(errors="replace")
    except OSError:
        c_text = ""
    ev_scratch = tempfile.mkdtemp(prefix="ofc_ev_")
    atexit.register(lambda: shutil.rmtree(ev_scratch, ignore_errors=True))
    os.environ.update(
        ev_mod.evidence_env_with_candidate(args.overlay, c_text, ev_scratch))
    _assert_evidence_not_clobbered(ev_mod, c_text)

    row = find_row(
        args.func, args.overlay, foff=args.foff, vram=args.vram, size=args.size)
    config = args.match_config or row.get("config")
    if not config:
        raise SystemExit("missing config; pass --match-config")
    gcc_ver, gcc_flags = split_config(config)
    container = cfg_path(args.container)
    if not container.exists():
        # Disc-style display names ("TOWN/TOWN.BIN") don't resolve from the
        # repo root; fall back to the canonical extraction tree.
        alt = ROOT / "work/roundtrip/extract" / args.container
        if alt.exists():
            container = alt
    with container.open("rb") as f:
        f.seek(int(row["foff"]))
        target = f.read(int(row["size"]))
    if int(row["size"]) == 0 or len(target) != int(row["size"]):
        # A short/empty retail slice (foff beyond EOF, wrong container, zero-size
        # row) previously produced a VACUOUS "MATCH ... size=0" — observed
        # 2026-07-24 on func_81881F60 vs MAIN_MAIN.BIN (2.5MB) at foff 0x18A1F60:
        # four false-positive MATCHes. An empty target proves nothing; refuse.
        raise SystemExit(
            f"overlay_func_compare: target slice short/empty — read {len(target)} "
            f"of {int(row['size'])} byte(s) at foff 0x{int(row['foff']):X} from "
            f"{container} (foff beyond EOF / wrong container / zero-size row?). "
            "Refusing the vacuous compare.")

    _injected, unresolved = inject_name_encoded_symbols(c_file, gcc_ver, gcc_flags, args.func)
    if unresolved and not args.summary_json:
        # ld cannot resolve these (not in any catalog, not name-encodable), so it
        # will fail and match.py falls back to the UNLINKED object. Warn LOUDLY and
        # name the culprits so the word diff below is not mistaken for a real diff.
        print(
            "overlay_func_compare WARNING: "
            f"{len(unresolved)} undefined symbol(s) have no catalog entry and no "
            "name-encoded address: "
            + ", ".join(unresolved)
            + " -> ld will FAIL and compare the UNLINKED object; the reported "
            "words_off includes PHANTOM relocation diffs.",
            file=sys.stderr,
        )

    link_vram, rowbase = rowbase_link_vram(
        args.overlay, int(row["foff"]), int(row["vram"]))
    # In-region candidates are written in TRUE address space (their
    # self-address / local-jump words must resolve to true addresses), so the
    # function may be defined under its true-space name rather than the
    # synthetic row identity. Extract whichever the TU actually defines.
    target_symbol = args.func
    if rowbase is not None:
        target_symbol = _ROWBASE.target_symbol(
            args.overlay, int(row["foff"]), args.func, c_text)
    if rowbase is not None and not args.summary_json:
        print(
            f"rowbase: linking at true base 0x{link_vram:08X} "
            f"(region {rowbase.get('region')}, delta {rowbase.get('delta')}; "
            f"synthetic row vram 0x{int(row['vram']):08X}; "
            f"target symbol {target_symbol})",
            file=sys.stderr,
        )
    # LEAD 12b: the as-flags positional used to be a hardcoded "" here, so no overlay
    # row could reach a maspsx dial (--expand-div et al.) from any wave entry point.
    # Explicit --as-flags wins; otherwise the per-function evidence lookup, which
    # returns "" (the old behaviour) unless a row proved a flag.
    as_flags = (args.as_flags if args.as_flags is not None else default_as_flags(
        args.func, args.overlay,
        target_symbol if target_symbol != args.func else None))
    if as_flags and not args.summary_json:
        print(f"as-flags: {as_flags} "
              f"({'--as-flags' if args.as_flags is not None else 'per-func default'})",
              file=sys.stderr)
    got, err = M.build_text(
        str(c_file),
        compiler_for(gcc_ver),
        "O2",
        "2.56",
        gcc_flags,
        as_flags,
        link_vram,
        target=target_symbol,
        retail_text=target,
        asm_output=args.asm_output,
    )
    rowbase_note = (
        f"rowbase: linked at true base 0x{link_vram:08X} "
        f"(region {rowbase.get('region')}, delta {rowbase.get('delta')})"
        if rowbase is not None else None)
    if got is None:
        if args.summary_json:
            warnings = ([f"unresolved symbols: " + ",".join(unresolved)] if unresolved else [])
            warnings += [rowbase_note] if rowbase_note else []
            warnings = warnings or None
            record = M.compiler_oracle_summary(
                args.func, config, str(c_file), __file__, target,
                build_error=err, compiler_path=os.path.join(compiler_for(gcc_ver), "gcc"),
                warnings=warnings, mask_relocations=False)
            # Provenance: an as-flag changes the scored bytes, so the record must say
            # which one produced it. Emitted ONLY when non-empty, so the default
            # record is byte-identical to the pre-LEAD-12b one.
            if as_flags:
                record["as_flags"] = as_flags
            # build_text publishes the raw -S the moment gcc succeeds, so a
            # maspsx/as/link failure still leaves the assembly a worker needs to
            # diagnose the CFAIL. A gcc-stage failure leaves no file (the stale
            # one was unlinked) and _assembly_record returns None.
            _attach_assembly(record, args.asm_output)
            M.print_oracle_summary(_augment_reloc_suspect(record))
            return 2
        print(f"CFAIL {err}")
        return 2
    if args.summary_json:
        warnings = (["unresolved symbols: " + ",".join(unresolved)] if unresolved else [])
        warnings += [rowbase_note] if rowbase_note else []
        warnings = warnings or None
        record = M.compiler_oracle_summary(
            args.func, config, str(c_file), __file__, target, got=got,
            compiler_path=os.path.join(compiler_for(gcc_ver), "gcc"), warnings=warnings,
            mask_relocations=False)
        if as_flags:
            record["as_flags"] = as_flags
        _attach_assembly(record, args.asm_output)
        _attach_regional_alignment(record, got, target)
        M.print_oracle_summary(_augment_reloc_suspect(record))
        return 0 if linked_words_equal(got, target) else 1
    got = got[: len(target)]
    ok = linked_words_equal(got, target)
    print(
        f"{'MATCH' if ok else 'NO MATCH'} {args.func} "
        f"{config} foff=0x{int(row['foff']):X} size={len(target)} "
        f"words_off={0 if ok else word_mismatch_count(got, target, False)}"
    )
    if ok:
        return 0
    # Same reloc_suspect signal as the JSON path, computed from the same
    # linked-strict aligned stats. Printed to STDOUT (not stderr) and AFTER the
    # MATCH/NO MATCH line on purpose: stderr is line-buffered while this
    # script's stdout is block-buffered when piped, so a stderr line emitted
    # here would race ahead of the (still-buffered) result line in any caller
    # that merges the two streams and reads line 0 (overlay_permute_queue.py,
    # overlay_byte_permute_spam.py) -- putting it on stdout after line 0 keeps
    # that contract intact while still surfacing the warning to a human.
    subs, indels = M.aligned_word_stats(got, target, mask_relocations=False)
    tgt_words = (len(target) + 3) // 4
    reloc = _reloc_suspect_flags(subs, indels, (len(got) + 3) // 4, tgt_words)
    if reloc["reloc_suspect"]:
        print(
            "overlay_func_compare WARNING: reloc_suspect -- every word differs "
            f"({subs}/{tgt_words}, indels=0) with matching length; this is "
            "almost always a relocation/link-base/config artifact, not "
            f"{tgt_words} real words of codegen divergence -- verify the "
            "lineage/link base/evidence file before treating this as a genuine "
            "near-miss (see work/reports/zq_maspsx_leads_20260714.md)."
        )
    elif reloc["reloc_suspect_near_0_9"]:
        print(
            "overlay_func_compare WARNING: reloc_suspect_near_0_9 -- "
            f"{subs}/{tgt_words} words differ (>=90%, indels=0, matching "
            "length); check for a relocation/link-base artifact before "
            "trusting this as codegen divergence."
        )
    print(f"got: {got.hex()}")
    print(f"tgt: {target.hex()}")
    diff = M.disasm_diff(got.hex(), target) if not args.no_disasm else ""
    print(diff if diff else M.word_diff(got.hex(), target))
    return 1


if __name__ == "__main__":
    raise SystemExit(main())
