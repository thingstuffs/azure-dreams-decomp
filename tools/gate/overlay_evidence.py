#!/usr/bin/env python3
"""Per-container maspsx evidence-file selection (Phase B activation, step 4).

The maspsx tail-call passes (LEAD 18 noreturn, LEAD 22 arg-sibcall, LEAD 19
frame-elision) consume two evidence files, selected via environment variables:

  $MASPSX_NORETURN_FILE  (default: config/noreturn_syms.txt)
  $MASPSX_SIBCALL_FILE   (default: config/sibcall_syms.txt)

Those defaults are the MAIN-family evidence — the co-resident SLUS EXE +
MAIN.BIN boot/menu overlay pair, whose vram ranges do not alias, proven safe
as one merged set. Every other container family gets its OWN files because a
shared/merged set is unsound (build/tmp_infra/phaseb_prescan.md Task 3):

  * town_scene and dungeon_engine BOTH load at 0x80080000 — the same
    func_800XXXXX name is DIFFERENT code per container (coincidental aliasing);
  * genuinely-shared resident callees (vram < 0x80030000) are ``j``-only in one
    container but ``jal``'d in the other (27 measured conflicts) — a merged
    file would wrongly convert the ``jal`` side.

A per-family file that does not exist yet loads as an EMPTY set inside maspsx
(the passes stay inert), which is the safe direction — so wiring a family
before its evidence exists is a no-op, never a regression.

Used by tools/overlay_local_gate.py (keyed by the overlay YAML ``name``) and
work/g3/overlay_func_compare.py (keyed by ``--overlay``). The main SLUS ninja
build and tools/match.py never set the variables and keep the defaults.
"""

from __future__ import annotations

import importlib.util
from collections.abc import Iterable
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

FAMILIES = ("main", "town", "dungeon", "ovmovie")

# The maspsx built-in default noreturn file (main family) — the base a 'main'
# compile or a family with no override file starts from.
DEFAULT_NORETURN_FILE = ROOT / "config" / "noreturn_syms.txt"

_GEN = None


def _gen_noreturn():
    """Lazily load tools/gen_noreturn_syms.py to reuse its corpus-proven
    zero-arg noreturn extraction (scan_text) — the SAME rule the offline census
    uses, so a self-served decl matches what landing + regeneration will emit."""
    global _GEN
    if _GEN is None:
        spec = importlib.util.spec_from_file_location(
            "gen_noreturn_syms", ROOT / "tools" / "gen_noreturn_syms.py")
        mod = importlib.util.module_from_spec(spec)
        assert spec.loader is not None
        spec.loader.exec_module(mod)
        _GEN = mod
    return _GEN


def candidate_noreturn_syms(c_text: str) -> set[str]:
    """The zero-arg noreturn callee symbols a candidate declares in its OWN
    source (LEAD-18 self-serve). A wave candidate is compiled in isolation,
    OUTSIDE the dirs the per-family census scans, so without deriving these its
    ``__attribute__((noreturn))`` / ``NORETURN`` decls never reach maspsx and the
    jal->j tail-call conversion never fires."""
    return set(_gen_noreturn().scan_text(c_text or ""))


def load_noreturn_file(path: str | Path) -> set[str]:
    """Read a noreturn evidence file into a symbol set (skips the header/blank
    lines), matching maspsx's own loader."""
    syms: set[str] = set()
    try:
        for line in Path(path).read_text(errors="replace").splitlines():
            line = line.strip()
            if line and not line.startswith("#"):
                syms.add(line)
    except OSError:
        pass
    return syms


def family_for(name: str) -> str:
    """Map an overlay/gate name to its container family.

    Accepts plain family names and gate/overlay names derived from them:
    'main', 'main_boot', 'main_7fdd' -> 'main'; 'town', 'town_scene_3e' ->
    'town'; 'dungeon', 'dungeon_engine', 'dungeon_deep_0a68' -> 'dungeon';
    'ovmovie' -> 'ovmovie'.
    """
    base = str(name).strip().lower()
    for fam in FAMILIES:
        if base == fam or base.startswith(fam + "_"):
            return fam
    raise ValueError(f"cannot map overlay name {name!r} to a container family")


def evidence_env(name: str) -> dict[str, str]:
    """Env overrides selecting ``name``'s container-family evidence files.

    'main' returns {} — the maspsx built-in defaults ARE the main-family files
    (config/noreturn_syms.txt + config/sibcall_syms.txt), and returning no
    override keeps the byte-exact SLUS/MAIN paths provably unchanged.
    """
    fam = family_for(name)
    if fam == "main":
        return {}
    return {
        "MASPSX_NORETURN_FILE": str(ROOT / f"config/noreturn_syms.{fam}.txt"),
        "MASPSX_SIBCALL_FILE": str(ROOT / f"config/sibcall_syms.{fam}.txt"),
    }


def proven_false_members(name: str) -> set[str]:
    """The PROVEN false members of ``name``'s family noreturn census.

    ``config/noreturn_false_members.jsonl`` records symbols a TU declares
    ``noreturn`` that the family-wide census must NOT carry, because retail
    reaches them BOTH ways (CLASS 1) or the declaration itself is wrong
    (CLASS 2).  ``gen_noreturn_syms.py`` already subtracts them when it writes
    the census; this exposes the same set to callers that build a census-like
    set of their own.
    """
    return set(_gen_noreturn().false_members(family_for(name)))


def evidence_env_with_candidate(name: str, c_text: str,
                                scratch_dir: str | Path,
                                exclude: Iterable[str] | None = None,
                                ) -> dict[str, str]:
    """``evidence_env(name)`` with the candidate's OWN source-declared zero-arg
    noreturn callees (LEAD-18 self-serve) unioned into the noreturn evidence.

    ``exclude`` drops symbols from the CANDIDATE side of the union before it is
    taken (the base census is never filtered — it is already correct).  Callers
    that use this to build one env for MANY translation units must pass
    ``proven_false_members(name)``: a false member is per-TU knowledge, so
    hoisting a candidate's declaration of one to a whole window re-injects the
    very fiction the census eviction removed and silently breaks the window's
    OTHER TUs (fid_819ACDA0, 2026-09-01).  A single-TU caller
    (``overlay_func_compare``) must NOT pass it — there the union IS the
    per-segment evidence, and filtering it would deny the declaring TU the
    conversion its own source proves.

    The per-family census is regenerated offline from LANDED sources and cannot
    know a not-yet-landed wave candidate's decls; overlay_func_compare previously
    just pointed ``$MASPSX_NORETURN_FILE`` at that (often empty) census, so a
    candidate's noreturn tail calls stayed ``jal`` and never matched retail's
    ``j``. When the candidate declares symbols beyond the census, this writes a
    MERGED file under ``scratch_dir`` and points the var at it — clobbering
    neither the census nor the candidate. Otherwise the plain family env is
    returned unchanged. Once the candidate lands and the census is regenerated,
    the landed/gate build emits the very same conversion, so the compare is
    consistent with the eventual byte-exact build."""
    env = dict(evidence_env(name))
    candidate = candidate_noreturn_syms(c_text)
    if exclude:
        candidate -= set(exclude)
    if not candidate:
        return env
    base_file = env.get("MASPSX_NORETURN_FILE", str(DEFAULT_NORETURN_FILE))
    base = load_noreturn_file(base_file)
    if candidate <= base:
        return env
    merged = base | candidate
    out = Path(scratch_dir) / "noreturn_syms.selfserve.txt"
    out.write_text(
        "# AUTO-MERGED (overlay_func_compare LEAD-18 self-serve): per-family "
        "census + this candidate's own zero-arg noreturn decls\n"
        + "".join(f"{s}\n" for s in sorted(merged)))
    env["MASPSX_NORETURN_FILE"] = str(out)
    return env
