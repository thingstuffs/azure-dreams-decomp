#!/usr/bin/env python3
"""Build and byte-compare a standalone overlay window.

This intentionally stays out of the main configure.py/ninja path.  It consumes an
overlay YAML with a ``standalone_build`` block, compiles matched C functions and
assembles explicitly staged checked-in assembly sources (platform-library twins
under ``asm/psyq`` and hand-written game assembly under ``asm/nonmatchings``, see
ASM_SOURCE_ROOTS) in place, fills every other split fragment with incbin-backed
asm-equivalent sections, links the requested window, and compares it with
extracted container bytes.
"""

from __future__ import annotations

import argparse
import hashlib
import json
import os
import re
import shutil
import subprocess
import sys
import dataclasses
from dataclasses import dataclass
from pathlib import Path
from typing import Any

import yaml

sys.path.insert(0, str(Path(__file__).resolve().parent))
from overlay_evidence import (  # noqa: E402
    DEFAULT_NORETURN_FILE, candidate_noreturn_syms, evidence_env,
    evidence_env_with_candidate, load_noreturn_file, proven_false_members)
from overlay_as_flags import default_as_flags  # noqa: E402  (LEAD 12b)
import rowbase_naming_debt  # noqa: E402


ROOT = Path(__file__).resolve().parents[1]
DEFAULT_CONFIG = ROOT / "config/overlays/dungeon_engine.overlay.yaml"
CONTAINER_ALTERNATIVES = {
    "dungeon_engine": [
        "DUNGEON_DUNGEON.BIN",
        "DUNGEON.BIN",
        "DUNGEON/DUNGEON.BIN",
    ],
    "main_boot": [
        "MAIN_MAIN.BIN",
        "MAIN.BIN",
        "MAIN/MAIN.BIN",
    ],
    "ovmovie": [
        "OVMOVIE.BIN",
    ],
    "town_scene": [
        "TOWN_TOWN.BIN",
        "TOWN.BIN",
        "TOWN/TOWN.BIN",
    ],
}

AS = "mipsel-linux-gnu-as"
LD = "mipsel-linux-gnu-ld"
NM = "mipsel-linux-gnu-nm"
OBJCOPY = "mipsel-linux-gnu-objcopy"
READELF = "mipsel-linux-gnu-readelf"


@dataclass(frozen=True)
class MatchEntry:
    start: int
    size: int
    func: str
    config: str
    source: Path
    source_group: str
    link_vram: int | None = None
    # ``platform_asm`` is reserved for checked-in PSYQ/library assembly and
    # ``game_asm`` for checked-in hand-written GAME assembly (see
    # ASM_SOURCE_ROOTS).  Neither shares the C compile path: they are assembled
    # sources with a checked-in boundary, not a way to smuggle ad hoc inline
    # assembly through the C gate.
    source_kind: str = "c"

    @property
    def end(self) -> int:
        return self.start + self.size


@dataclass(frozen=True)
class Segment:
    index: int
    kind: str
    start: int
    end: int
    vram: int
    section: str
    name: str | None = None
    match: MatchEntry | None = None
    bytes_path: Path | None = None

    @property
    def size(self) -> int:
        return self.end - self.start


def rel(path: Path) -> str:
    try:
        return str(path.relative_to(ROOT))
    except ValueError:
        return str(path)


def parse_int(value: Any, field: str) -> int:
    if isinstance(value, int):
        return value
    if isinstance(value, str):
        return int(value, 0)
    raise SystemExit(f"{field} must be an int or 0x-prefixed string, got {value!r}")


def run(
    cmd: list[str], *, cwd: Path = ROOT, stdout: Any = None, env: dict[str, str] | None = None
) -> subprocess.CompletedProcess:
    full_env = {**os.environ, **env} if env else None
    proc = subprocess.run(cmd, cwd=cwd, text=True, stdout=stdout, stderr=subprocess.PIPE, env=full_env)
    if proc.returncode != 0:
        shown = " ".join(cmd)
        err = proc.stderr.strip()
        raise SystemExit(f"command failed: {shown}\n{err}")
    return proc


def file_sha1(path: Path) -> str:
    h = hashlib.sha1()
    with path.open("rb") as f:
        for chunk in iter(lambda: f.read(1024 * 1024), b""):
            h.update(chunk)
    return h.hexdigest()


def load_yaml(path: Path) -> dict[str, Any]:
    with path.open() as f:
        return yaml.safe_load(f)


def cfg_path(raw: str) -> Path:
    p = Path(raw)
    return p if p.is_absolute() else ROOT / p


# The two assembly landing routes, each pinned to ONE checked-in directory.
#
#   platform_asm -- canonical PSY-Q/SDK library twins (asm/psyq).  A row landed
#     this way is a library function the game merely linked against.
#   game_asm -- hand-written GAME assembly that has no portable-C form at all
#     (asm/nonmatchings, the repository's existing home for checked-in
#     disassembly).  MAIN's boot installers are the motivating case: they save
#     $ra to a fixed BSS global instead of a stack frame and dispatch BIOS
#     vectors inline, an ABI no compiler configuration in this project emits.
#
# Both are narrow ON PURPOSE.  They accept an in-tree ``.s`` under their own
# directory and nothing else: no /tmp scratch file, no generated adapter, no C.
# Landing one still has to survive the same staged whole-window byte compare as
# a C candidate (tools/overlay_land_function.py), so the boundary check is an
# admissibility rule, never a substitute for the byte proof.
#
# asm/nonmatchings is also the one directory under asm/ that tools/configure.py
# excludes from the main-EXE link (it is INCLUDE_ASM'd by src/ instead), so an
# overlay-owned source parked there cannot perturb the sha1-gated EXE build.
#
# DURABILITY REQUIREMENT (2026-08-18, learned the hard way).  All of ``asm/`` is
# gitignored and REGENERATED -- .gitignore: "the repository must contain ZERO
# game bytes ... Everything here is regenerated from a user-supplied disc".  The
# platform twins satisfy that because config/slus_006.14.yaml (tracked, and
# carrying only addresses and names) declares the splat segments that emit them,
# e.g. ``[0x3d548, asm, psyq/libcard/A74]``.  A row landed through either route
# therefore records an ``asm_path`` in TRACKED metadata that points into an
# UNTRACKED tree, and that is only sound while something regenerates the file
# from the disc.  Never land a hand-authored .s here: after a fresh clone it
# would not exist and this window's gate would hard-fail for everyone else.
# Give the source a generator first (the model to copy is the splat entry
# above), then land it.
ASM_SOURCE_ROOTS = {
    "platform_asm": Path("asm") / "psyq",
    "game_asm": Path("asm") / "nonmatchings",
}
ASM_SOURCE_KINDS = frozenset(ASM_SOURCE_ROOTS)


def validate_asm_source(raw: str | Path, kind: str = "platform_asm", *,
                        root: Path = ROOT) -> Path:
    """Resolve and validate one checked-in assembly source of ``kind``.

    Only sources under this kind's directory in :data:`ASM_SOURCE_ROOTS` may be
    landed; arbitrary ``.s`` files (and C sources) remain outside the overlay
    gate's boundary.  Resolving before the ancestry check also prevents a
    symlink from escaping that boundary.
    """
    if kind not in ASM_SOURCE_ROOTS:
        raise SystemExit(f"unknown assembly source kind: {kind!r}")
    boundary = ASM_SOURCE_ROOTS[kind].as_posix()
    path = Path(raw)
    if not path.is_absolute():
        path = root / path
    try:
        resolved = path.resolve(strict=True)
    except OSError as exc:
        raise SystemExit(f"{kind} source missing: {path}: {exc}") from exc
    library_root = (root / ASM_SOURCE_ROOTS[kind]).resolve()
    try:
        resolved.relative_to(library_root)
    except ValueError as exc:
        raise SystemExit(
            f"{kind} source outside {boundary} boundary: {rel(resolved)}; "
            "game C must use the normal portable gate, and game assembly must "
            f"live (and be regenerable) under {ASM_SOURCE_ROOTS['game_asm'].as_posix()}"
        ) from exc
    if resolved.suffix.lower() != ".s":
        raise SystemExit(
            f"{kind} source must be .s under {boundary}: {rel(resolved)}")
    if not resolved.is_file():
        raise SystemExit(f"{kind} source is not a regular file: {rel(resolved)}")
    return resolved


def validate_platform_asm_source(raw: str | Path, *, root: Path = ROOT) -> Path:
    """Resolve and validate one platform-library (``asm/psyq``) source."""
    return validate_asm_source(raw, "platform_asm", root=root)


def validate_game_asm_source(raw: str | Path, *, root: Path = ROOT) -> Path:
    """Resolve and validate one hand-written game assembly source."""
    return validate_asm_source(raw, "game_asm", root=root)


def find_extractor(configured: str | None) -> Path:
    candidates: list[Path] = []
    if configured:
        candidates.append(cfg_path(configured))
    env = os.environ.get("OVERLAY_EXTRACT_BINS")
    if env:
        candidates.append(Path(env))
    candidates.extend(
        [
            ROOT / "work/overlay_recon/extract_bins.py",
            Path("<upstream>/work/overlay_recon/extract_bins.py"),
        ]
    )
    for candidate in candidates:
        if candidate.exists():
            return candidate
    tried = "\n  ".join(str(p) for p in candidates)
    raise SystemExit(f"extract_bins.py not found; tried:\n  {tried}")


def ensure_container(cfg: dict[str, Any], sb: dict[str, Any]) -> tuple[Path, Path | None]:
    extract_cfg = sb.get("extract", {})
    target = cfg_path(extract_cfg.get("container_path") or cfg["options"]["target_path"])
    expected_sha1 = str(cfg.get("sha1") or "").strip()
    used_extractor: Path | None = None

    if target.exists() and (not expected_sha1 or file_sha1(target) == expected_sha1):
        return target, used_extractor

    out_dir = cfg_path(extract_cfg.get("out_dir", "work/s3_splat/extract"))
    disc = cfg_path(extract_cfg.get("disc_path", "bin/Azure Dreams.bin"))
    extractor = find_extractor(extract_cfg.get("extractor"))
    out_dir.mkdir(parents=True, exist_ok=True)
    run([sys.executable, str(extractor), str(disc), str(out_dir)], stdout=subprocess.DEVNULL)
    used_extractor = extractor

    if not target.exists():
        names = CONTAINER_ALTERNATIVES.get(str(cfg.get("name")), [])
        for name in names:
            alt = out_dir / name
            if alt.exists():
                target = alt
                break
    if not target.exists():
        raise SystemExit(f"extraction finished but container is missing: {rel(target)}")
    if expected_sha1:
        got = file_sha1(target)
        if got != expected_sha1:
            raise SystemExit(f"{rel(target)} sha1 mismatch: got {got}, expected {expected_sha1}")
    return target, used_extractor


def load_rows(path: Path) -> list[dict[str, Any]]:
    with path.open() as f:
        rows = json.load(f)
    if not isinstance(rows, list):
        raise SystemExit(f"{rel(path)} must contain a JSON list")
    return rows


def in_window(row: dict[str, Any], start: int, end: int) -> bool:
    foff = row.get("foff")
    size = row.get("size")
    return isinstance(foff, int) and isinstance(size, int) and start <= foff < end and foff + size <= end


def config_to_flags(config: str) -> tuple[str, str]:
    # Canonical parsing lives in tools/match.py (parse_config_label) so the
    # gate, the compare harness, and worker-reported labels all agree — a
    # plus-dialect label ("2.8.1+-G0 -fno-schedule-insns") once reached this
    # whitespace-only splitter and produced compiler "gcc-2.8.1+" (landing
    # failure, 2026-07-07 ovmovie wave).
    return _match_mod().parse_config_label(config)


_MATCH_MOD = None


def _match_mod():
    global _MATCH_MOD
    if _MATCH_MOD is None:
        sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
        import match
        _MATCH_MOD = match
    return _MATCH_MOD


def load_matches(sb: dict[str, Any], window_start: int, window_end: int,
                 family: str | None = None) -> tuple[dict[tuple[int, int], MatchEntry], dict[str, int]]:
    matches: dict[tuple[int, int], MatchEntry] = {}
    counts: dict[str, int] = {}
    for group in sb.get("matched_sources", []):
        group_name = group.get("name") or group.get("source_dir") or "matched"
        rows = load_rows(cfg_path(group["results"]))
        source_dir = cfg_path(group["source_dir"])
        only_if_missing = bool(group.get("only_if_missing", False))
        skip_rerun = bool(group.get("skip_rerun", True))
        added = 0
        for row in rows:
            if row.get("result") != "MATCH":
                continue
            if skip_rerun and row.get("rerun"):
                continue
            if not in_window(row, window_start, window_end):
                continue
            key = (row["foff"], row["size"])
            if only_if_missing and key in matches:
                continue
            func = row["func_vram"]
            source_kind = row.get("source_kind", "c")
            if source_kind in ASM_SOURCE_KINDS:
                raw_source = row.get("asm_path")
                if not isinstance(raw_source, str):
                    raise SystemExit(
                        f"{source_kind} row for {func} has no asm_path")
                source = validate_asm_source(raw_source, source_kind, root=ROOT)
            else:
                source = source_dir / f"{func}.c"
                if not source.exists():
                    raise SystemExit(f"matched source missing for {func}: {rel(source)}")
            # Rowbase (docs/rowbase_lane_phase2.md): a landed in-region source
            # defines its TRUE-space name and is pre-linked at the true base.
            section_func, link_vram = func, None
            true_name = row.get("true_name")
            if family is not None:
                delta = _rowbase_proven_delta(family, int(row["foff"]))
                if delta is not None:
                    expected = f"func_{int(row['foff']) + delta:08X}"
                    if isinstance(true_name, str) and true_name == expected:
                        section_func, link_vram = true_name, int(row["foff"]) + delta
                    elif true_name is not None:
                        # A RECORDED-but-mismatched true_name is corruption —
                        # fail loudly (WINDOW-LINK DIVERGENCE class). A row
                        # with NO true_name is the LEGACY population: 244 rows
                        # landed pre-lane (or pre-promotion of their region)
                        # whose synthetic link reproduced retail bytes through
                        # a green gate (no alias-band j words) — their
                        # synthetic link is the verified behavior; keep it.
                        raise SystemExit(
                            f"landed {func}: row 0x{int(row['foff']):X} lies in a "
                            f"PROVEN rowbase region (true base {expected}) but its "
                            f"results row true_name is {true_name!r} — refusing the "
                            "synthetic-vram link (owner decision B; fix the results "
                            "row or the evidence extent).")
            if key not in matches:
                added += 1
            matches[key] = MatchEntry(
                start=row["foff"],
                size=row["size"],
                func=section_func,
                config=row.get("config") or "2.7.2",
                source=source,
                source_group=group_name,
                link_vram=link_vram,
                source_kind=source_kind,
            )
        counts[group_name] = added
    return matches, counts


def load_split_rows(sb: dict[str, Any], window_start: int, window_end: int) -> list[dict[str, Any]]:
    rows = [
        row
        for row in load_rows(cfg_path(sb["split_results"]))
        if not row.get("rerun") and in_window(row, window_start, window_end)
    ]
    rows.sort(key=lambda row: row["foff"])
    last_end = window_start
    seen: set[int] = set()
    for row in rows:
        if row["foff"] in seen:
            raise SystemExit(f"duplicate split start 0x{row['foff']:X} in {sb['split_results']}")
        seen.add(row["foff"])
        if row["foff"] < last_end:
            raise SystemExit(f"overlapping split row at 0x{row['foff']:X}")
        last_end = row["foff"] + row["size"]
    return rows


def _rowbase_proven_delta(family: str, foff: int) -> int | None:
    """True-base delta for a foff in a PROVEN rowbase region (else None).
    Same evidence file the scoring loader validates; landing-side consumers
    accept only base_confidence "proven" (docs/rowbase_lane_phase2.md)."""
    path = cfg_path(f"config/overlays/{family}.rowbase.jsonl")
    if not path.exists():
        return None
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        try:
            rec = json.loads(line)
            start, end = int(str(rec["foff_start"]), 0), int(str(rec["foff_end"]), 0)
            delta = int(str(rec["delta"]), 0)
        except (ValueError, KeyError, TypeError) as exc:
            raise SystemExit(f"{path}:{lineno}: invalid rowbase record: {exc}")
        if start <= foff < end and rec.get("base_confidence") == "proven":
            return delta
    return None


def add_staged_matches(
    matches: dict[tuple[int, int], MatchEntry],
    match_counts: dict[str, int],
    split_rows: list[dict[str, Any]],
    staged: list[list[str]] | None,
    family: str | None = None,
) -> None:
    """Overlay one-off C sources onto the build without editing result JSON."""
    if not staged:
        return
    by_func: dict[str, dict[str, Any]] = {}
    for row in split_rows:
        func = row.get("func_vram")
        if isinstance(func, str):
            if func in by_func:
                raise SystemExit(f"duplicate split row for staged function {func}")
            by_func[func] = row

    for func, raw_source, config in staged:
        row = by_func.get(func)
        if row is None:
            raise SystemExit(f"staged function {func} is not in the configured split window")
        source = cfg_path(raw_source)
        if not source.exists():
            raise SystemExit(f"staged source missing for {func}: {rel(source)}")
        # Rowbase naming inversion (owner decision B): an in-region source
        # defines the function under its TRUE-space name, so the KEEP-covered
        # section is .text.<true_name>. Row lookup stays synthetic; only the
        # section/compile symbol follows the source.
        section_func = func
        link_vram = None
        if family is not None:
            delta = _rowbase_proven_delta(family, int(row["foff"]))
            if delta is not None:
                true_name = f"func_{int(row['foff']) + delta:08X}"
                text = source.read_text(errors="replace")
                definitions = rowbase_naming_debt.file_definitions(text)
                masked = rowbase_naming_debt.mask_source(text)
                if (true_name in definitions
                        and not re.search(
                            r"\b" + re.escape(func) + r"\s*\(", masked)):
                    section_func = true_name
                    # In-region rows link OUT of the window's linear address
                    # space: the segment is pre-linked at its true base and
                    # injected as bytes (docs/rowbase_lane_phase2.md, A).
                    link_vram = int(row["foff"]) + delta
                else:
                    raise SystemExit(
                        f"staged {func}: row 0x{int(row['foff']):X} lies in a PROVEN "
                        f"rowbase region (true base 0x{int(row['foff']) + delta:08X}) but "
                        f"the source does not satisfy the naming inversion — it must "
                        f"define {true_name} and never mention {func}( (owner decision B, "
                        "docs/rowbase_lane_phase2.md item 2). Refusing the synthetic-vram "
                        "link: the TU's own local j words would resolve synthetic and the "
                        "window compare would fail with phantom j-word diffs "
                        "(WINDOW-LINK DIVERGENCE class, gap probe 2026-07-19).")
        key = (row["foff"], row["size"])
        matches[key] = MatchEntry(
            start=row["foff"],
            size=row["size"],
            func=section_func,
            config=config,
            source=source,
            source_group="staged",
            link_vram=link_vram,
        )
    match_counts["staged"] = len(staged)


def add_asm_matches(
    matches: dict[tuple[int, int], MatchEntry],
    match_counts: dict[str, int],
    split_rows: list[dict[str, Any]],
    staged: list[list[str]] | None,
    kind: str = "platform_asm",
) -> None:
    """Add checked-in assembly sources of ``kind`` to one gate run.

    ``staged`` is a list of ``[FUNC, ASM_SOURCE]`` pairs.  The function and
    size still come from the configured split row; the source only supplies
    the bytes.  This keeps the row geometry authoritative and makes a source
    that is too long/short fail at the link/compare boundary instead of
    silently changing the window shape.
    """
    if not staged:
        return
    label = kind.replace("_", " ")
    by_func: dict[str, dict[str, Any]] = {}
    for row in split_rows:
        func = row.get("func_vram")
        if isinstance(func, str):
            if func in by_func:
                raise SystemExit(f"duplicate split row for {label} {func}")
            by_func[func] = row

    for raw in staged:
        if len(raw) != 2:
            raise SystemExit(f"{label} stage entry must be FUNC ASM_SOURCE")
        func, raw_source = raw
        row = by_func.get(func)
        if row is None:
            raise SystemExit(f"{label} function {func} is not in the configured split window")
        source = validate_asm_source(raw_source, kind, root=ROOT)
        key = (row["foff"], row["size"])
        if key in matches:
            raise SystemExit(
                f"{label} stage overlaps an existing matched source at "
                f"0x{int(row['foff']):X} ({func})")
        matches[key] = MatchEntry(
            start=row["foff"], size=row["size"], func=func,
            config=kind.replace("_", "-"), source=source,
            source_group=kind.replace("_", "-"), source_kind=kind,
        )
    match_counts[kind] = len(staged)


def add_platform_asm_matches(
    matches: dict[tuple[int, int], MatchEntry],
    match_counts: dict[str, int],
    split_rows: list[dict[str, Any]],
    staged: list[list[str]] | None,
) -> None:
    """Add checked-in PSYQ/library assembly twins to one gate run."""
    add_asm_matches(matches, match_counts, split_rows, staged, "platform_asm")


def build_segments(
    rows: list[dict[str, Any]],
    matches: dict[tuple[int, int], MatchEntry],
    window_start: int,
    window_end: int,
    vram_delta: int,
) -> list[Segment]:
    segments: list[Segment] = []
    cursor = window_start

    def add_raw(start: int, end: int) -> None:
        if end <= start:
            return
        idx = len(segments)
        segments.append(
            Segment(
                index=idx,
                kind="raw",
                start=start,
                end=end,
                vram=start + vram_delta,
                section=f".ovlseg_{idx:04d}",
                name=f"raw_{start:06X}",
            )
        )

    for row in rows:
        start = row["foff"]
        end = start + row["size"]
        add_raw(cursor, start)
        idx = len(segments)
        match = matches.get((start, row["size"]))
        if match is not None:
            kind = (match.source_kind if match.source_kind in ASM_SOURCE_KINDS
                    else "c")
            segments.append(
                Segment(
                    index=idx,
                    kind=kind,
                    start=start,
                    end=end,
                    vram=start + vram_delta,
                    # Assembled objects retain their canonical bare .text
                    # section.  The linker script scopes that section to this
                    # one object, so no source symbol rewrite is needed (and
                    # the retail library identity is preserved).
                    section=(".text" if kind in ASM_SOURCE_KINDS
                             else f".text.{match.func}"),
                    name=match.func,
                    match=match,
                )
            )
        else:
            name = row.get("func_vram") or f"asm_{start:06X}"
            segments.append(
                Segment(
                    index=idx,
                    kind="asm",
                    start=start,
                    end=end,
                    vram=start + vram_delta,
                    section=f".ovlseg_{idx:04d}",
                    name=name,
                )
            )
        cursor = end
    add_raw(cursor, window_end)
    return segments


def write_raw_asm(segments: list[Segment], container: Path, out_s: Path) -> None:
    incbin_path = rel(container)
    lines: list[str] = []
    for seg in segments:
        if seg.kind == "c" or seg.kind in ASM_SOURCE_KINDS:
            continue
        if seg.kind == "rowbase":
            # Pre-linked true-base bytes (rowbase lane); inject verbatim.
            lines.append(f'.section {seg.section},"ax",@progbits')
            lines.append(f"L_rowbase_{seg.index:04d}:")
            lines.append(f'.incbin "{rel(seg.bytes_path)}"')
            lines.append("")
            continue
        flags = "ax" if seg.kind == "asm" else "a"
        lines.append(f'.section {seg.section},"{flags}",@progbits')
        if seg.kind == "asm" and seg.name and re.fullmatch(r"func_[0-9A-Fa-f]{8}", seg.name):
            lines.extend(
                [
                    f".global {seg.name}",
                    f".type {seg.name}, @function",
                    f"{seg.name}:",
                ]
            )
        else:
            lines.append(f"L_{seg.name}:")
        lines.append(f'.incbin "{incbin_path}", 0x{seg.start:X}, 0x{seg.size:X}')
        if seg.kind == "asm" and seg.name and re.fullmatch(r"func_[0-9A-Fa-f]{8}", seg.name):
            lines.append(f".size {seg.name}, . - {seg.name}")
        lines.append("")
    out_s.write_text("\n".join(lines))


def duplicate_match_funcs(segments: list[Segment]) -> set[str]:
    """Names claimed by more than one C segment of this window.

    A rowbase row's ``match.func`` is its TRUE-space name, and true names are
    NOT unique inside one container.  Town's proven ``sweep_*`` regions are
    separately streamed scene chunks that all load into the SAME RAM band
    (18 of 22 regions map into ~0x80016100-0x8001D450 / ~0x80020260-0x80026DC8),
    so two genuinely DIFFERENT functions from two different scenes legitimately
    resolve to one ``func_<true vram>`` name.  Ten such town pairs exist today
    (verified byte-distinct at their own foffs, e.g. func_800178B4: 148B at
    0x3F68B4 vs 232B at 0x3F08B4).
    """
    counts: dict[str, int] = {}
    for seg in segments:
        if seg.kind == "c" and seg.match is not None:
            counts[seg.match.func] = counts.get(seg.match.func, 0) + 1
    return {name for name, n in counts.items() if n > 1}


def segment_obj_key(seg: Segment, dup_funcs: set[str]) -> str:
    """Per-segment build-artifact key (object, and rowbase mini .ld/.elf/.bin).

    These artifacts used to be keyed by ``seg.match.func`` alone.  When one
    window contains BOTH members of a same-true-name pair the second compile
    silently overwrote the first's object at the identical path, and the
    rowbase mini-link then picked up the other row's bytes -- observed as
    ``rowbase segment func_800178B4: pre-linked bytes 148B do not cover the
    row extent 232B exactly`` in town_deep_t8_03ea.

    Remedy mirrors the OBJECT-SCOPED placement pattern already used in the
    rowbase block below (Option D, third instance func_818AA8D8): scope the
    artifact per TU so two TUs can never merge at one path.  The disambiguating
    suffix is applied ONLY to names that actually collide inside this window,
    so every window without a collision keeps byte-identical build artifacts
    and byte-identical linker-script text.
    """
    assert seg.match is not None
    func = seg.match.func
    return f"{func}__{seg.start:06X}" if func in dup_funcs else func


def compile_c_segments(
    segments: list[Segment], obj_dir: Path, env: dict[str, str] | None = None,
    overlay: str | None = None,
) -> list[Path]:
    """Compile every C segment of the window through tools/cc.sh.

    LEAD 12b: ``cc.sh``'s $5 (MASPSX_FLAGS) used to be a hardcoded "", so the
    gate could not reproduce a row whose byte-exactness needs a per-function
    maspsx dial — and, because the gate re-compiles the WHOLE window on every
    future run, an unwired gate would break that window forever after the row
    landed.  ``overlay`` is the gate/overlay name; the lookup
    (tools/overlay_as_flags.py) is the same one the production scorer and the
    synth scorer use, and it returns "" for every row without an evidence
    record — so a window with no dialled row compiles byte-for-byte as before.
    ``seg.match.func`` is the TRUE-space name for a rowbase in-region row, and
    a bare true name is a RAM-SLOT LABEL, not an identity (docs/rowbase_identity
    .md rule R1) -- ``func_801712C4`` is shared by dungeon rows ``func_81329AC4``
    and ``func_80EDFAC4``.  Resolving by that name alone handed the second row
    the first one's ``--retail-func-81329ac4-proto`` dial and took the whole
    ``dungeon_deep_t8b_eff8b8`` window red (same bug: ``func_80173294`` /
    ``dungeon_deep_t8b_997064``).  The lookup is therefore given the row's
    ``foff``, which is what makes it region-qualified.

    PER-SEGMENT NORETURN EVIDENCE (2026-08-08). Each segment compiles with the
    window env UNIONED with its OWN zero-arg noreturn declarations, instead of
    one env shared by the whole window. This is a no-op for almost everything --
    the census is GENERATED from the landed sources, so for a landed segment
    ``census >= own decls`` already -- and it matters in exactly one case: a
    symbol excluded as a PROVEN FALSE MEMBER (config/noreturn_false_members.jsonl).
    Such a symbol is one retail reaches BOTH ways, ``j`` from a tail call and
    ``jal`` from a caller that uses the result, so no family-wide name-keyed set
    can be right for both callers at once. Per-segment evidence can: the TU that
    declares it keeps its ``j``, and the TU that does not keeps its ``jal``.
    Whether a callee returns is per-TU knowledge, and the declaration is where
    that knowledge lives.

    Without this, excluding a false member silently regresses its DECLARING TU
    (measured: func_81839358 emitted ``jal`` at file 0x1859547 where retail has
    ``j``, failing the whole dungeon_deep_t8_1830 window) -- trading one blocked
    window for another. The isolation verifier does not show it, because
    ``evidence_env_with_candidate`` self-serves the candidate's own decls; only a
    plain (non-``--stage-match``) gate of the declaring TU's window exposes it.
    """
    obj_dir.mkdir(parents=True, exist_ok=True)
    dup_funcs = duplicate_match_funcs(segments)
    objects: list[Path] = []
    base_noreturn_file = (env or {}).get(
        "MASPSX_NORETURN_FILE", str(DEFAULT_NORETURN_FILE))
    base_noreturn = load_noreturn_file(base_noreturn_file)
    for seg in segments:
        if seg.kind != "c" or seg.match is None:
            continue
        gcc_ver, gcc_flags = config_to_flags(seg.match.config)
        out_o = obj_dir / f"{segment_obj_key(seg, dup_funcs)}.o"
        seg_env = env
        own = candidate_noreturn_syms(
            Path(seg.match.source).read_text(errors="replace"))
        if own - base_noreturn:
            merged = obj_dir / f"{segment_obj_key(seg, dup_funcs)}.noreturn.txt"
            merged.write_text(
                "# AUTO-MERGED (overlay_local_gate per-segment evidence): window "
                "census + this segment's own zero-arg noreturn decls\n"
                + "".join(f"{s}\n" for s in sorted(base_noreturn | own)))
            seg_env = dict(env or {})
            seg_env["MASPSX_NORETURN_FILE"] = str(merged)
        run(
            [
                str(ROOT / "tools/cc.sh"),
                str(seg.match.source),
                str(out_o),
                gcc_ver,
                gcc_flags,
                # (family, foff) -- NOT the bare name: ``seg.match.func`` is the
                # row's TRUE name for an in-region row, and a bare true name is
                # a RAM-slot label shared by several rows, so the name alone
                # resolved the WRONG row's dial (docs/rowbase_identity.md R1).
                default_as_flags(seg.match.func, overlay, foff=seg.match.start),
            ],
            env=seg_env,
        )
        objects.append(out_o)
    return objects


def compile_asm_segments(
    segments: list[Segment], obj_dir: Path,
) -> dict[int, Path]:
    """Assemble checked-in asm segments and return segment-indexed objects.

    This path uses the repository's split-assembly wrapper (``as.sh``), not
    ``cc.sh`` or any C preprocessing.  The object map is keyed by segment
    index because canonical PSYQ symbols are library names (``_card_info``,
    etc.), while the overlay row remains a synthetic ``func_XXXXXXXX`` label.
    """
    obj_dir.mkdir(parents=True, exist_ok=True)
    out: dict[int, Path] = {}
    for seg in segments:
        if seg.kind not in ASM_SOURCE_KINDS or seg.match is None:
            continue
        source = validate_asm_source(seg.match.source, seg.kind, root=ROOT)
        obj = obj_dir / f"{seg.kind}_{seg.name}_{seg.start:06X}.o"
        run([str(ROOT / "tools" / "as.sh"), str(source), str(obj)])
        out[seg.index] = obj
    return out


# Back-compat alias: the platform route's original entry point.
compile_platform_asm_segments = compile_asm_segments


def check_bare_text_empty(objects: list[Path]) -> None:
    # The linker script /DISCARD/s the bare .text section, so any function or
    # asm-pinned table bytes that land there (instead of .text.<funcname>) are
    # silently dropped and the output segment zero-fills over real retail bytes
    # (chain-H c01 func_81892800: a naked-asm .text-pinned jump table never got
    # renamed because tools/ccproc.py sectioning only fires on gcc-emitted .ent
    # lines). Corpus-proven invariant: all 1414 known-good match objects have a
    # zero-size bare .text, so any non-empty one is that defect class.
    sect_re = re.compile(r"^\s*\[\s*\d+\]\s+\.text\s+PROGBITS\s+\S+\s+\S+\s+([0-9A-Fa-f]+)")
    for obj in objects:
        proc = subprocess.run(
            [READELF, "-SW", str(obj)],
            cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE,
        )
        if proc.returncode != 0:
            raise SystemExit(f"command failed: {READELF} -SW {obj}\n{proc.stderr.strip()}")
        for line in proc.stdout.splitlines():
            m = sect_re.match(line)
            if m and int(m.group(1), 16) != 0:
                raise SystemExit(
                    f"{obj.name}: {int(m.group(1), 16)} bytes in bare .text — the gate "
                    "discards this section, so these bytes would silently zero-fill the "
                    "window at land time. Cause: content pinned with a naked asm label or "
                    '__attribute__((section(".text"))) is not renamed by ccproc.py (its '
                    "sectioning triggers on gcc .ent lines only). Fix the candidate: pin "
                    'tables/asm into section(".text.<funcname>") and define the function '
                    "under its real name so everything lands in one KEEP-covered section."
                )


def parse_symbol_file(path: Path) -> dict[str, int]:
    out: dict[str, int] = {}
    if not path.exists():
        return out
    line_re = re.compile(r"^\s*([A-Za-z_][A-Za-z0-9_]*)\s*=\s*(0x[0-9A-Fa-f]+)\s*;")
    with path.open(errors="replace") as f:
        for raw in f:
            line = raw.split("//", 1)[0]
            m = line_re.match(line)
            if m:
                out[m.group(1)] = int(m.group(2), 16)
    return out


# nm type letters that denote a STRONG DEFINED global -- text, data, rodata,
# bss, absolute.  Deliberately EXCLUDES:
#   C  common/tentative (gcc 2.7.x emits every uninitialised file-scope object
#      this way; ld merges them, so two objects carrying one `C` symbol is
#      legal and must never trip the guard),
#   W/V  weak (definition is overridable by design),
#   U  undefined (a reference, not a definition).
# `A` stays in this set, but assert_unique_globals collapses EQUAL-VALUED
# duplicate `A` definitions (owner decision 2026-08-03): the landed
# `__asm__(".set D_X, 0xADDR")` / `sym = 0xADDR` address-alias idiom defines
# the same absolute symbol at the same value from many TUs, ld accepts it
# (main_boot byte-proved with three such groups in the link), and firing on it
# blocked the whole window.  Conflicting values still fail closed.
STRONG_DEFINED_NM_TYPES = frozenset("TDRBA")

# Per-object `nm -g` memo, keyed by (path, mtime_ns, size) so a rewritten
# object (raw_segments.o is re-assembled after the rowbase injection) is
# re-read.  This is what lets assert_unique_globals run at the shared link
# without spawning a second nm per object: write_linker_script has already
# indexed exactly those objects a few lines earlier.
_NM_CACHE: dict[tuple[str, int, int], list[tuple[str, str, str | None]]] = {}


def _nm_globals(obj: Path) -> list[tuple[str, str, str | None]]:
    """``(nm type letter, symbol, value hex or None)`` per object, in nm order.

    ``U`` is reported with the literal type ``"U"`` and value ``None``.
    Classification is byte-for-byte the pre-2026-07-29 ``nm_symbols`` parsing,
    so the derived ``(defined, undefined)`` sets -- and therefore every linker
    script this tool writes -- are unchanged.  The value column exists solely
    so the PWU guard can tell equal-valued absolute address aliases (legal,
    collapsed) from conflicting ones (defect, fail closed).
    """
    key: tuple[str, int, int] | None
    try:
        st = obj.stat()
        key = (str(obj), st.st_mtime_ns, st.st_size)
    except OSError:
        key = None
    if key is not None:
        cached = _NM_CACHE.get(key)
        if cached is not None:
            return cached
    proc = subprocess.run([NM, "-g", str(obj)], cwd=ROOT, text=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
    if proc.returncode != 0:
        raise SystemExit(f"command failed: {NM} -g {obj}\n{proc.stderr.strip()}")
    out: list[tuple[str, str, str | None]] = []
    for raw in proc.stdout.splitlines():
        line = raw.strip()
        if not line:
            continue
        parts = line.split()
        if len(parts) == 2 and parts[0] == "U":
            out.append(("U", parts[1], None))
        elif len(parts) >= 3 and re.fullmatch(r"[0-9A-Fa-f]+", parts[0]):
            out.append((parts[1], parts[2], parts[0]))
    if key is not None:
        _NM_CACHE[key] = out
    return out


@dataclass(frozen=True)
class NmIndex:
    """Which objects define / reference which global symbol.

    ``defined`` keeps the old ``nm_symbols`` semantics (ANY defined type, so C
    and W are in it) because the linker-script generator resolves against it.
    ``strong`` is the PWU-relevant subset (STRONG_DEFINED_NM_TYPES only).
    ``strong_detail`` carries ``(object, nm type, value hex)`` per strong
    definition so the guard can collapse equal-valued absolute aliases.
    """

    defined: dict[str, list[Path]]
    strong: dict[str, list[Path]]
    undefined: dict[str, list[Path]]
    strong_detail: dict[str, list[tuple[Path, str, str | None]]]


def nm_index(objects: list[Path]) -> NmIndex:
    """One ``nm -g`` pass over ``objects`` -> per-symbol object lists.

    An object appearing twice in ``objects`` contributes twice: that is what
    ``ld`` sees, and a repeated input is itself a duplicate-definition defect.
    """
    defined: dict[str, list[Path]] = {}
    strong: dict[str, list[Path]] = {}
    undefined: dict[str, list[Path]] = {}
    strong_detail: dict[str, list[tuple[Path, str, str | None]]] = {}
    for obj in objects:
        for sym_type, name, value in _nm_globals(obj):
            if sym_type == "U":
                undefined.setdefault(name, []).append(obj)
                continue
            defined.setdefault(name, []).append(obj)
            if sym_type in STRONG_DEFINED_NM_TYPES:
                strong.setdefault(name, []).append(obj)
                strong_detail.setdefault(name, []).append((obj, sym_type, value))
    return NmIndex(defined=defined, strong=strong, undefined=undefined,
                   strong_detail=strong_detail)


def nm_symbols(objects: list[Path]) -> tuple[set[str], set[str]]:
    """(defined, undefined) symbol sets, derived from :func:`nm_index`."""
    index = nm_index(objects)
    return set(index.defined), set(index.undefined)


PWU_REMEDY = """\
PWU (Per-Window Uniqueness) is a structural invariant of this gate, not an
owner decision: no `ld` invocation may receive two objects defining the same
strong global.  A true name is a RAM-SLOT LABEL, not a function identity --
two genuinely different functions in two different rowbase regions legitimately
carry the same func_<true vram> (24 such slot groups exist today across town
and dungeon).  A duplicate here is therefore an INFRASTRUCTURE DEFECT in the
gate and is fixed HERE.  It is never fixed by editing, renaming or duplicating
a landed C source, and it is never an owner naming call.
Remedy, in order:
  1. every row with a proven rowbase delta must be mini-linked ALONE at its
     true base and injected as raw bytes, so it never reaches the shared link
     (Leg A: check the row still carries match.link_vram out of load_matches
     and that its object is dropped from c_objects);
  2. per-TU build artifacts must be scoped by segment_obj_key(), so two TUs
     sharing one true name can never merge at one .o/.ld/.elf/.bin path
     (this is the town_deep_t8_03ea / func_800178B4 defect, 2026-07-29);
  3. everything left in the shared link is synthetic-named and per-window
     unique -- load_split_rows fail-closes on duplicate and overlapping foffs,
     so a duplicate that survives 1 and 2 means a split row or a results row
     is corrupt.
Equal-valued absolute (`A`) address aliases -- the landed
`__asm__(".set D_X, 0xADDR")` / `sym = 0xADDR` idiom -- are NOT violations:
ld accepts them and this guard collapses them (owner decision 2026-08-03,
w79a main_boot incident).  An absolute symbol in the listing above therefore
carries CONFLICTING values across its defining objects, or collides with a
real section definition, and one of those definitions is wrong.
Spec: work/debt_20260729/opt3_region_qualified_names_spec.md (1.3, 2.1, 2.2,
amendment 2.2a)."""


def assert_unique_globals(
    objects: list[Path], where: str, *, expect_count: int | None = None
) -> None:
    """Fail closed unless every strong global in ``objects`` is defined once.

    ``where`` names the link this list feeds (window + shared/mini link); it is
    quoted in the failure so the message identifies the offending gate window
    without the caller re-deriving it.

    ``expect_count`` additionally pins the number of link inputs.  The rowbase
    mini-link passes 1: that is Leg A of the PWU proof -- a proven-region row
    is linked ALONE at its true base -- stated as an executable assertion
    instead of a property re-derived by reading main() every time.

    Only STRONG_DEFINED_NM_TYPES count.  Commons and weaks are excluded, or the
    guard would fire on legitimate tentative definitions (gcc 2.7.x emits
    file-scope objects as `C`) and on deliberate weak overrides.

    Amendment 2026-08-03 (owner-approved, spec 2.2a): a symbol whose every
    definition is absolute (`A`) at ONE value is a slot-address alias, not a
    duplicate -- ld demonstrably accepts it (main_boot carried three such
    groups through weeks of byte-proved links) and the pre-amendment guard
    blocked the whole window on them (w79a: func_8000E68C / func_8001DB84).
    Absolute definitions at CONFLICTING values, and any mix of absolute with a
    real section definition, still fail closed.
    """
    if expect_count is not None and len(objects) != expect_count:
        listing = "".join(f"\n    {rel(obj)}" for obj in objects) or "\n    (none)"
        raise SystemExit(
            f"PWU violation (infrastructure defect) at {where}: this link was "
            f"handed {len(objects)} input object(s), expected exactly "
            f"{expect_count}.{listing}\n{PWU_REMEDY}"
        )
    index = nm_index(objects)
    duplicated: dict[str, list[tuple[Path, str, str | None]]] = {}
    for name, objs in sorted(index.strong.items()):
        if len(objs) <= 1:
            continue
        detail = index.strong_detail[name]
        if all(t == "A" and v is not None for _, t, v in detail):
            if len({int(v, 16) for _, _, v in detail}) == 1:
                continue  # equal-valued absolute address aliases: legal idiom
        duplicated[name] = detail
    if not duplicated:
        return
    lines = [
        f"PWU violation (infrastructure defect) at {where}: "
        f"{len(duplicated)} strong global symbol(s) defined by more than one "
        f"of the {len(objects)} objects in this link."
    ]
    for name, detail in duplicated.items():
        lines.append(f"  {name} defined by {len(detail)} objects:")
        lines.extend(
            f"    {rel(obj)} ({sym_type}"
            + (f" @ 0x{int(value, 16):08x}" if sym_type == "A" and value is not None else "")
            + ")"
            for obj, sym_type, value in detail
        )
    lines.append(PWU_REMEDY)
    raise SystemExit("\n".join(lines))


def symbol_addr(name: str, named: dict[str, int]) -> int | None:
    if name in named:
        return named[name]
    m = re.fullmatch(r"(?:func|D)_([0-9A-Fa-f]{8})", name)
    if m:
        return int(m.group(1), 16)
    return None


def write_linker_script(
    segments: list[Segment],
    objects: list[Path],
    gp_value: int,
    symbol_files: list[Path],
    out_ld: Path,
    placements: dict[str, int] | None = None,
    scoped_placements: list[tuple[str, str, int]] | None = None,
    obj_paths: dict[int, Path] | None = None,
) -> list[str]:
    defined, undefined = nm_symbols(objects)
    named: dict[str, int] = {}
    for path in symbol_files:
        named.update(parse_symbol_file(path))

    assignments: list[str] = [f"_gp = 0x{gp_value:08X};"]
    unknown: list[str] = []
    for name in sorted(undefined - defined):
        addr = symbol_addr(name, named)
        if addr is None:
            unknown.append(name)
        else:
            assignments.append(f"{name} = 0x{addr:08X};")
    if unknown:
        raise SystemExit("unresolved symbols without known addresses: " + ", ".join(unknown))

    lines = [
        "OUTPUT_FORMAT(\"elf32-tradlittlemips\")",
        "OUTPUT_ARCH(mips)",
        *assignments,
        "SECTIONS",
        "{",
    ]
    for seg in segments:
        out_name = f".out_{seg.index:04d}"
        keep = f"*({seg.section})"
        if getattr(seg, "kind", None) == "c" and seg.name:
            # A C segment's TU exists solely for this row, so collect ALL its
            # NAMED .text.* sections in object emit order (bank-table composites
            # emit .text.<row> + the body's auto function-section; gcc 2.7.x
            # ignores section attributes on function definitions, so the
            # single-section form is unreachable from source — object-scoped
            # KEEP is the correct-by-construction rule; 2026-07-22
            # func_81251000 n=7). Bare .text is EXCLUDED: it is corpus-proven
            # empty (check_bare_text_empty fail-louds otherwise) but carries
            # align=16, and folding it first pads any row whose base is not
            # 16-aligned — 12 leading zero bytes shifted func_80026C54's body
            # off its true base (2026-07-22, three replay siblings wedged).
            # Prefer the caller's explicit index->object map: with a
            # same-true-name pair in one window the object basename is
            # disambiguated (segment_obj_key) and no longer equals
            # f"{seg.name}.o", so the name search alone would silently fall
            # back to the un-scoped *(.text.*) KEEP.
            obj = (obj_paths or {}).get(seg.index)
            if obj is None:
                obj = next((o for o in objects
                            if os.path.basename(str(o)) == f"{seg.name}.o"), None)
            if obj is not None:
                keep = f'"{obj}"(.text.*)'
        elif getattr(seg, "kind", None) in ASM_SOURCE_KINDS:
            # Checked-in assembly sources intentionally emit bare .text and
            # their own symbols (_card_info, _card_load, func_800217C8, ...).
            # Keep only this object's .text in this row's output section; the
            # /DISCARD/ rule below remains in force for every other bare .text.
            obj = (obj_paths or {}).get(seg.index)
            if obj is None:
                raise SystemExit(
                    f"{seg.kind} segment {seg.name} has no assembled object")
            keep = f'"{obj}"(.text)'
        if getattr(seg, "kind", None) in ASM_SOURCE_KINDS:
            # Canonical PSYQ .text carries 16-byte input alignment, but an
            # overlay row may begin at any 4-byte boundary (these twins start
            # at +0x4/+0xC within a 16-byte run).  SUBALIGN(1) suppresses
            # linker-inserted leading/trailing alignment so the object bytes
            # occupy exactly the row extent.
            lines.append(
                f"  {out_name} 0x{seg.vram:08X} : SUBALIGN(1) {{ KEEP({keep}) }}")
        else:
            lines.append(f"  {out_name} 0x{seg.vram:08X} : {{ KEEP({keep}) }}")
    # Evidence-derived local-jtbl placement (Option D, 2026-07-20): a rowbase
    # TU with a compiler-local switch table must resolve its %hi/%lo against
    # retail's table address (match._local_section_placements). NOLOAD keeps
    # the resolution address-only — no bytes enter the image; the window's
    # raw retail segments remain the sole authority for the table area. With
    # no derived placement the /DISCARD/ below still dies loudly, unchanged.
    for sect, base in sorted((placements or {}).items()):
        lines.append(
            f"  {sect} 0x{base:08X} (NOLOAD) : SUBALIGN(4) {{ KEEP(*({sect}*)) }}")
    # Object-scoped variant for in-window C segments in the MAIN link: the
    # filespec pins each placement to its own TU so two objects' local tables
    # can never merge into one address. Same NOLOAD epistemics as above.
    for n, (obj_name, sect, base) in enumerate(sorted(scoped_placements or [])):
        lines.append(
            f"  .dplace_{n:02d} 0x{base:08X} (NOLOAD) : SUBALIGN(4) "
            f"{{ KEEP(\"{obj_name}\"({sect}*)) }}")
    lines.extend(
        [
            "  /DISCARD/ : {",
            "    *(.text) *(.data) *(.bss) *(.sdata) *(.sbss)",
            # The window's data regions are raw-incbin-owned, so any data a C
            # match emits is phantom by construction (e.g. a label-pinning
            # keepalive table dispatching through the retail jump table).
            # Discard it; rodata the C's own text actually references dies
            # loudly at link time instead of silently fattening the window.
            "    *(.rodata*) *(.rdata*) *(.lit4) *(.lit8) *(.scommon)",
            "    *(.reginfo) *(.MIPS.abiflags) *(.pdr) *(.gnu.attributes)",
            "    *(.comment) *(.note*) *(.mdebug*)",
            "  }",
            "}",
            "",
        ]
    )
    out_ld.write_text("\n".join(lines))
    return unknown


def first_mismatch(a: bytes, b: bytes) -> tuple[int, int, int] | None:
    for i, (x, y) in enumerate(zip(a, b)):
        if x != y:
            return i, x, y
    if len(a) != len(b):
        return min(len(a), len(b)), len(a), len(b)
    return None


def write_manifest(path: Path, cfg_name: str, container: Path, segments: list[Segment], match_counts: dict[str, int]) -> None:
    data = {
        "overlay": cfg_name,
        "container": rel(container),
        "segment_count": len(segments),
        "segment_counts": {
            "c": sum(1 for s in segments if s.kind == "c"),
            "platform_asm": sum(1 for s in segments if s.kind == "platform_asm"),
            "game_asm": sum(1 for s in segments if s.kind == "game_asm"),
            "asm": sum(1 for s in segments if s.kind == "asm"),
            "raw": sum(1 for s in segments if s.kind == "raw"),
            "rowbase": sum(1 for s in segments if s.kind == "rowbase"),
        },
        "matched_source_counts": match_counts,
        "c_segments": [
            {
                "func": s.name,
                "file_start": f"0x{s.start:X}",
                "vram": f"0x{s.vram:X}",
                "size": s.size,
                "source": rel(s.match.source) if s.match else None,
                "config": s.match.config if s.match else None,
                "source_group": s.match.source_group if s.match else None,
                **({"rowbase_link_vram": f"0x{s.match.link_vram:X}"}
                   if s.match and s.match.link_vram is not None else {}),
            }
            for s in segments
            if s.kind in ("c", "rowbase")
        ],
        "platform_asm_segments": [
            {
                "func": s.name,
                "file_start": f"0x{s.start:X}",
                "vram": f"0x{s.vram:X}",
                "size": s.size,
                "source": rel(s.match.source) if s.match else None,
                "source_group": s.match.source_group if s.match else None,
            }
            for s in segments if s.kind == "platform_asm"
        ],
        "game_asm_segments": [
            {
                "func": s.name,
                "file_start": f"0x{s.start:X}",
                "vram": f"0x{s.vram:X}",
                "size": s.size,
                "source": rel(s.match.source) if s.match else None,
                "source_group": s.match.source_group if s.match else None,
            }
            for s in segments if s.kind == "game_asm"
        ],
    }
    path.write_text(json.dumps(data, indent=2) + "\n")


def compile_corpus(work_root: Path) -> tuple[int, dict[str, int]]:
    """Compile every canonical all-overlay first-pass matched C file.

    This is a compile-only audit. Placement/linkage still belongs to each
    overlay-local gate; the corpus check proves the checked-in matched C sources
    still pass the pinned compiler/maspsx path.
    """
    canonical = ["main", "town", "dungeon", "ovmovie"]
    out_dir = work_root / "corpus_compile"
    if out_dir.exists():
        shutil.rmtree(out_dir)
    out_dir.mkdir(parents=True, exist_ok=True)

    jobs: list[tuple[str, dict[str, Any], Path]] = []
    counts: dict[str, int] = {}
    for overlay in canonical:
        rows = load_rows(ROOT / f"overlays/{overlay}/overlay_first_pass_results.json")
        count = 0
        for row in rows:
            if row.get("result") != "MATCH" or row.get("rerun"):
                continue
            source = ROOT / f"overlays/{overlay}/first_pass_matched/{row['func_vram']}.c"
            if not source.exists():
                raise SystemExit(f"matched corpus source missing: {rel(source)}")
            jobs.append((overlay, row, source))
            count += 1
        counts[overlay] = count

    for idx, (overlay, row, source) in enumerate(jobs, 1):
        gcc_ver, gcc_flags = config_to_flags(row.get("config") or "2.7.2")
        obj_dir = out_dir / overlay
        obj_dir.mkdir(exist_ok=True)
        obj = obj_dir / f"{idx:04d}_{source.stem}.o"
        # Per-container maspsx evidence selection (0x80080000 vram aliasing --
        # town/dungeon evidence must never fire on the other family's compile).
        run([str(ROOT / "tools/cc.sh"), str(source), str(obj), gcc_ver, gcc_flags,
             default_as_flags(row["func_vram"], overlay, row.get("true_name"),
                              foff=row.get("foff"))],
            env=evidence_env(overlay))
        if idx % 100 == 0:
            print(f"corpus compile: {idx}/{len(jobs)}")

    return len(jobs), counts


def main() -> int:
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--config", default=str(DEFAULT_CONFIG), help="overlay YAML")
    parser.add_argument("--clean", action="store_true", help="remove this overlay's work build dir first")
    parser.add_argument(
        "--compile-corpus",
        action="store_true",
        help="also compile-audit every canonical all-overlay first-pass matched C file",
    )
    parser.add_argument(
        "--stage-match",
        action="append",
        nargs=3,
        metavar=("FUNC", "CFILE", "CONFIG"),
        help=(
            "compile one C file as a matched segment for this run only; "
            "useful for preflighting overlay landings"
        ),
    )
    parser.add_argument(
        "--stage-platform-asm", "--stage-asm", dest="stage_platform_asm",
        action="append", nargs=2, metavar=("FUNC", "ASM_SOURCE"),
        help=(
            "stage one checked-in platform-library assembly source for this "
            "run only; source must be under asm/psyq (repeatable)"
        ),
    )
    parser.add_argument(
        "--stage-game-asm", dest="stage_game_asm",
        action="append", nargs=2, metavar=("FUNC", "ASM_SOURCE"),
        help=(
            "stage one checked-in hand-written GAME assembly source for this "
            "run only; source must be under asm/nonmatchings (repeatable)"
        ),
    )
    args = parser.parse_args()

    config_path = cfg_path(args.config)
    cfg = load_yaml(config_path)
    sb = cfg.get("standalone_build")
    if not isinstance(sb, dict):
        raise SystemExit(f"{rel(config_path)} lacks a standalone_build block")

    window = sb["window"]
    window_start = parse_int(window["file_start"], "window.file_start")
    window_end = parse_int(window["file_end"], "window.file_end")
    vram_start = parse_int(window["vram_start"], "window.vram_start")
    vram_delta = vram_start - window_start
    gp_value = parse_int(cfg["options"].get("gp_value", 0), "options.gp_value")
    work_dir = cfg_path(sb.get("work_dir", "work/s3_splat")) / cfg["name"]
    # Cross-process exclusive lock per gate. The build dir is shared state:
    # a concurrent --clean (agent battery, second land, ad-hoc gate run) wipes
    # objects mid-link and produces bogus 'No such file or directory' /
    # corrupted-window failures (chain_20260712_G c02: 2 of 3 land failures).
    # Blocks until the peer finishes — gate runs are minutes, not hours.
    work_dir.mkdir(parents=True, exist_ok=True)
    import fcntl
    lock_fh = open(work_dir / ".gate.lock", "w")
    fcntl.flock(lock_fh, fcntl.LOCK_EX)
    build_dir = work_dir / "build"
    if args.clean and build_dir.exists():
        shutil.rmtree(build_dir)
    build_dir.mkdir(parents=True, exist_ok=True)

    container, extractor = ensure_container(cfg, sb)
    if container.stat().st_size < window_end:
        raise SystemExit(f"{rel(container)} is shorter than requested window end 0x{window_end:X}")

    split_rows = load_split_rows(sb, window_start, window_end)
    matches, match_counts = load_matches(sb, window_start, window_end,
                                         family=cfg["name"].split("_")[0])
    add_staged_matches(matches, match_counts, split_rows, args.stage_match,
                       family=cfg["name"].split("_")[0])
    add_asm_matches(matches, match_counts, split_rows,
                    args.stage_platform_asm, "platform_asm")
    add_asm_matches(matches, match_counts, split_rows,
                    args.stage_game_asm, "game_asm")
    segments = build_segments(split_rows, matches, window_start, window_end, vram_delta)

    raw_s = build_dir / "raw_segments.s"
    raw_o = build_dir / "raw_segments.o"
    write_raw_asm(segments, container, raw_s)
    run([AS, "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-O1", "-G0", "-o", str(raw_o), str(raw_s)])

    # Per-container maspsx evidence selection, keyed by the gate's overlay name
    # (main_* -> defaults; town_*/dungeon_*/ovmovie* -> their own files).
    # Staged candidates are not in the per-family census yet (it is regenerated
    # from LANDED sources only), so union their own zero-arg noreturn decls into
    # the evidence — the same env the isolation verifier proved the match under.
    #
    # MINUS THE PROVEN FALSE MEMBERS (fid_819ACDA0 second instance, 2026-09-01).
    # This env is the WINDOW's base, shared by every C segment, so a staged
    # candidate's decl of a symbol evicted as a proven false member would be
    # hoisted onto the window's LANDED neighbours and re-create exactly the
    # fiction the eviction removed. Measured: staging the byte-exact
    # func_819A1654 (which legitimately declares func_8002614C noreturn for its
    # own four tail `j`s) flipped landed func_819ACDA0's word 237 from `jal` to
    # `j` and took the whole dungeon_deep_t8_19c0 window red at file 0x19CD157.
    # Nothing is lost: compile_c_segments() unions EVERY segment's own decls
    # into its own compile (per-segment evidence, 2026-08-08), and a staged
    # segment's source is its staged file — so the declaring TU still self-serves
    # the conversion, which is also what it gets once it lands. The filter is
    # also what makes this env a faithful simulation of the post-landing census:
    # gen_noreturn_syms.py subtracts the same set when it regenerates.
    if args.stage_match:
        staged_text = "\n".join(
            cfg_path(raw_source).read_text()
            for _func, raw_source, _config in args.stage_match)
        c_env = evidence_env_with_candidate(
            cfg["name"], staged_text, build_dir,
            exclude=proven_false_members(cfg["name"]))
    else:
        c_env = evidence_env(cfg["name"])
    c_objects = compile_c_segments(segments, build_dir / "obj", env=c_env,
                                   overlay=cfg["name"])
    asm_objects = compile_asm_segments(segments, build_dir / "obj")
    check_bare_text_empty(c_objects)
    symbol_files = [cfg_path("config/slus_006.14.symbols.txt")]
    if cfg["options"].get("symbol_addrs_path"):
        symbol_files.append(cfg_path(cfg["options"]["symbol_addrs_path"]))

    # Rowbase pre-link-inject (docs/rowbase_lane_phase2.md, owner decision A):
    # a C segment for a PROVEN alias-region row links at its TRUE base, which
    # lies outside the window's linear address space. Link that object alone at
    # the true vram (same symbol machinery), then inject the resulting bytes as
    # a raw segment — the bytes still come from compiling the actual source.
    rowbase_objs: set[Path] = set()
    scoped_placements: list[tuple[str, str, int]] = []
    # Computed BEFORE the loop mutates segments[i] to kind="rowbase", so the
    # same key set is reused for the main link's obj_paths map below.
    dup_funcs = duplicate_match_funcs(segments)
    seg_objs: dict[int, Path] = {}
    for i, seg in enumerate(segments):
        if seg.kind != "c" or seg.match is None:
            continue
        obj_key = segment_obj_key(seg, dup_funcs)
        obj = build_dir / "obj" / f"{obj_key}.o"
        seg_objs[seg.index] = obj
        # Option D: derive retail's placement for any compiler-local switch
        # table this TU references, from the row's own retail bytes. Any
        # anomaly returns {} and the /DISCARD/ fail-loud behavior is kept.
        import match as _match
        with container.open("rb") as _stream:
            _stream.seek(seg.start)
            _row_bytes = _stream.read(seg.end - seg.start)
        placements = _match._local_section_placements(
            str(obj), seg.match.func,
            seg.match.link_vram if seg.match.link_vram is not None else seg.vram,
            _row_bytes)
        if seg.match.link_vram is None:
            # In-window C segment (no rowbase mini-link): its local jtbl dies
            # at the main link's /DISCARD/ without a placement (the gate half
            # of the Option-D disease, third instance: func_818AA8D8). Emit
            # OBJECT-SCOPED so two TUs' .rodata can never merge at one base.
            scoped_placements.extend(
                (str(obj), sect, base) for sect, base in placements.items())
            continue
        mini = Segment(index=0, kind="c", start=seg.start, end=seg.end,
                       vram=seg.match.link_vram, section=seg.section,
                       name=seg.match.func, match=seg.match)
        mini_objects = [obj]
        mini_ld = build_dir / f"rowbase_{obj_key}.ld"
        write_linker_script([mini], mini_objects, gp_value, symbol_files, mini_ld,
                            placements=placements, obj_paths={0: obj})
        mini_elf = build_dir / f"rowbase_{obj_key}.elf"
        mini_bin = build_dir / f"rowbase_{obj_key}.bin"
        # Leg A of PWU, executable: a proven-region row links ALONE, so its
        # true name can never meet another object's copy of that name.
        assert_unique_globals(
            mini_objects, f"{cfg['name']} rowbase mini-link {obj_key}",
            expect_count=1)
        run([LD, "-EL", "--no-check-sections", "-T", str(mini_ld),
             "-o", str(mini_elf), *map(str, mini_objects)])
        run([OBJCOPY, "-O", "binary", str(mini_elf), str(mini_bin)])
        data = mini_bin.read_bytes()
        if len(data) < seg.size or any(b != 0 for b in data[seg.size:]):
            raise SystemExit(
                f"rowbase segment {seg.match.func} (foff 0x{seg.start:X}, "
                f"obj {rel(obj)}): pre-linked bytes "
                f"{len(data)}B do not cover the row extent {seg.size}B exactly")
        if len(data) != seg.size:
            mini_bin.write_bytes(data[:seg.size])
        segments[i] = dataclasses.replace(
            seg, kind="rowbase", bytes_path=mini_bin,
            section=f".ovlseg_{seg.index:04d}")
        rowbase_objs.add(obj)
    c_objects = [o for o in c_objects if o not in rowbase_objs]
    if rowbase_objs:
        # Raw asm was written before conversion; regenerate with the injected
        # rowbase segments included.
        write_raw_asm(segments, container, raw_s)
        run([AS, "-EL", "-march=r3000", "-mtune=r3000", "-no-pad-sections", "-O1", "-G0", "-o", str(raw_o), str(raw_s)])
    seg_objs.update(asm_objects)
    all_objects = [raw_o, *c_objects, *asm_objects.values()]

    out_stem = cfg["name"]
    link_ld = build_dir / f"{out_stem}.ld"
    write_linker_script(segments, all_objects, gp_value, symbol_files, link_ld,
                        scoped_placements=scoped_placements,
                        obj_paths=seg_objs)
    # PWU guard, immediately before the shared link: everything that reaches
    # this ld is synthetic-named and per-window unique (Leg B), because every
    # proven-region row was mini-linked and stripped from c_objects above
    # (Leg A).  Silent on every currently-green window; see PWU_REMEDY.
    assert_unique_globals(all_objects, f"{cfg['name']} shared link")
    elf = build_dir / f"{out_stem}.elf"
    rebuilt = build_dir / f"{out_stem}.window.bin"
    run([LD, "-EL", "--no-check-sections", "-T", str(link_ld), "-o", str(elf), *map(str, all_objects)])
    run([OBJCOPY, "-O", "binary", str(elf), str(rebuilt)])

    with container.open("rb") as f:
        f.seek(window_start)
        target = f.read(window_end - window_start)
    got = rebuilt.read_bytes()
    manifest = work_dir / f"{out_stem}_manifest.json"
    write_manifest(manifest, cfg["name"], container, segments, match_counts)

    print(f"overlay: {cfg['name']}")
    print(f"config: {rel(config_path)}")
    print(f"container: {rel(container)}")
    if extractor:
        print(f"extractor: {extractor}")
    print(f"window: 0x{window_start:X}..0x{window_end:X} -> 0x{vram_start:X}..0x{vram_start + (window_end - window_start):X}")
    print(
        "segments: "
        f"{len(segments)} total, "
        f"{sum(1 for s in segments if s.kind in ('c', 'rowbase'))} c, "
        f"{sum(1 for s in segments if s.kind == 'platform_asm')} platform asm, "
        f"{sum(1 for s in segments if s.kind == 'game_asm')} game asm, "
        f"{sum(1 for s in segments if s.kind == 'asm')} asm, "
        f"{sum(1 for s in segments if s.kind == 'raw')} raw"
    )
    print("matched source counts: " + ", ".join(f"{k}={v}" for k, v in match_counts.items()))
    print(f"manifest: {rel(manifest)}")

    if len(got) != len(target):
        print(f"NO MATCH: rebuilt length {len(got)} != target length {len(target)}")
        return 1
    mismatch = first_mismatch(got, target)
    if mismatch:
        off, g, t = mismatch
        print(f"NO MATCH: first mismatch at window+0x{off:X} file 0x{window_start + off:X}: got 0x{g:02X}, target 0x{t:02X}")
        return 1

    print(f"MATCH: rebuilt overlay window byte-identical ({len(target)} bytes)")
    if args.compile_corpus:
        total, counts = compile_corpus(cfg_path(sb.get("work_dir", "work/s3_splat")))
        print("corpus matched C compile counts: " + ", ".join(f"{k}={v}" for k, v in counts.items()))
        print(f"PASS: compiled {total} canonical all-overlay matched C files")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
