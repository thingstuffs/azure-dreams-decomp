#!/usr/bin/env python3
"""LEAD 12b — the ONE per-function as-flags lookup, shared by every consumer.

Background
----------
maspsx/as flags are a *per-translation-unit* dial in this project, never a
global one: ``--expand-div`` was tried globally and **VETOED 2026-07-03** (it
changes already-matched runtime-div functions and shifts later symbol
addresses; see ``tools/maspsx_leads.md`` LEAD 12/12b).  The main-EXE route is
``tools/configure.py::AS_FLAGS``, keyed by the TU path ``src/w_XXXXXXXX.c``;
``match.py`` turns those stems into ``func_XXXXXXXX`` keys
(``match.DEFAULT_FUNC_AS_FLAGS``).  Overlay rows have no ``src/*.c`` TU, so
LEAD 12b added the overlay-name analogue: one JSON record per line in
``config/overlays/<overlay>.as_flags.jsonl``::

    {"schema": "azure-clean.overlay-asflags.v1", "func": "func_803300DC",
     "true_name": "func_8001A8DC", "as_flags": "--expand-div",
     "proof": <how the flag was proven byte-exact>}

``func`` is the SYNTHETIC row key (``row["func_vram"]``) and is unique within
the container family, so it is an identity.  ``true_name`` is the rowbase
true-space name — needed because a landed in-region TU defines its TRUE name
and the gate compiles it under that name — but it is **not** an identity.

Why the true name is not a key (2026-08-23)
-------------------------------------------
A bare ``func_<TRUE VRAM8>`` is a **RAM-SLOT LABEL** shared by up to 25 rows
(``docs/rowbase_identity.md``, rule R1: identity = ``(family, foff)``).  Two
dungeon rows really do define ``func_801712C4`` — ``func_81329AC4`` (foff
0x1349AC4, region ``jtbl_1343F78``) and ``func_80EDFAC4`` (foff 0xEFFAC4,
region ``sweep_0EFF000``) — and only the first proved a maspsx dial.  Keying
the table by the bare name handed ``func_80EDFAC4`` the other row's
``--retail-func-81329ac4-proto`` dial, whose frozen full-function signature
then mismatched and took the whole ``dungeon_deep_t8b_eff8b8`` window red.
``func_80173294`` (rows ``func_80F89A94`` / ``func_80977A94``) was the same
bug in ``dungeon_deep_t8b_997064``.

So resolution is region-qualified: a query that can name its row — by the
synthetic key, or by ``(family, foff)`` — is answered from the row's
**identity** (``func_<TRUE>__<family>__<region>``), and the bare name is used
only as a last-resort fallback when it is *unambiguous inside that family*.
An ambiguous bare name with no region context raises (rule R2: never
first-match, never silently skip).  Every consumer goes through
``resolve_as_flags``/``default_as_flags`` — there is one resolver.

Why this module exists
----------------------
The lookup was first written inside ``work/g3/overlay_func_compare.py`` (the
production scorer, commit ``7adbdc51``).  Three further consumers — the synth
scorer (``close_gap.build_got``), the landing gate
(``overlay_local_gate.compile_c_segments``) and the cache identity
(``compile_cache_identity.assembler_input_manifest``) — need the SAME answer
for the same row, or a row scores exact in one tool and not in another, and a
dial compile and a non-dial compile of the same row share a cache key.  Two
implementations of an evidence lookup is two chances to disagree, so the
scorer now delegates here as well: this file is the only copy.

Evidence discipline (same as ``rowbase_link_vram``)
---------------------------------------------------
The evidence file is OPTIONAL — no file, or no record for the row, returns
``""``, which is byte-for-byte the pre-LEAD-12b behaviour of every consumer.
A malformed or proofless record fails LOUDLY (``SystemExit``): a silently
DROPPED as-flag re-hides the dial this route exists to expose, and a silently
ADDED one fires a globally-vetoed dial on a row that never proved it.

Overlay names are normalised to their container FAMILY (``town_deep_t8b_2afff4``
-> ``town``) through ``overlay_evidence.family_for``, the same mapping the
maspsx evidence-file selection uses, so a gate name and a scorer ``--overlay``
resolve to one table.  The table is deliberately NOT searched across families:
town and dungeon both load at 0x80080000, so the same ``func_800XXXXX`` name is
different code per container (``tools/overlay_evidence.py`` header) — an
overlay-blind lookup would be unsound, not merely imprecise.
"""

from __future__ import annotations

import dataclasses
import importlib.util
import json
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]

SCHEMA = "azure-clean.overlay-asflags.v1"

IDENTITY_DOC = "docs/rowbase_identity.md"

# Overlay-local symbol whose retail address is encoded in its own name.
_NAME_ENCODED = re.compile(r"(func|D)_([0-9A-Fa-f]{8})$")


def _norm_func_key(name: str) -> str:
    """``func_803300dc`` -> ``func_803300DC`` (match.DEFAULT_FUNC_AS_FLAGS' casing)."""
    hit = _NAME_ENCODED.fullmatch(name or "")
    return f"{hit.group(1)}_{hit.group(2).upper()}" if hit else (name or "")


_EVIDENCE_MOD = None


def _overlay_evidence():
    global _EVIDENCE_MOD
    if _EVIDENCE_MOD is None:
        mod = sys.modules.get("overlay_evidence")
        if mod is None or not hasattr(mod, "family_for"):
            spec = importlib.util.spec_from_file_location(
                "_asflags_overlay_evidence", ROOT / "tools" / "overlay_evidence.py")
            mod = importlib.util.module_from_spec(spec)
            assert spec.loader is not None
            spec.loader.exec_module(mod)
        _EVIDENCE_MOD = mod
    return _EVIDENCE_MOD


def _family(overlay: str) -> str:
    """Container family for a gate/overlay name ('town_deep_t8b_2afff4' -> 'town').

    Falls back to the raw name when it maps to no known family, so an unknown
    name simply finds no evidence file (the pre-LEAD-12b answer) instead of
    raising in a consumer that only wanted a default flag string.
    """
    try:
        return _overlay_evidence().family_for(overlay)
    except Exception:
        return str(overlay)


def evidence_path(overlay: str) -> Path:
    return ROOT / f"config/overlays/{_family(overlay)}.as_flags.jsonl"


# ---------------------------------------------------------------------------
# The evidence records
# ---------------------------------------------------------------------------


@dataclasses.dataclass(frozen=True)
class Record:
    """One ``<family>.as_flags.jsonl`` line.

    ``func_key`` is the SYNTHETIC row key — an identity inside the family.
    ``true_key`` is the bare rowbase slot label, which is NOT an identity;
    it is only ever used through :func:`resolve_as_flags`.
    """

    func_key: str
    true_key: str | None
    as_flags: str
    lineno: int


@dataclasses.dataclass(frozen=True)
class Table:
    records: tuple[Record, ...]
    by_syn: dict[str, str]              # synthetic row key -> flags
    by_true: dict[str, tuple[Record, ...]]   # bare slot label -> records claiming it
    path: Path


_TABLE_CACHE: dict[str, tuple[tuple, Table]] = {}


def _stamp(path: Path) -> tuple[int, int] | None:
    try:
        st = path.stat()
    except OSError:
        return None
    return (st.st_mtime_ns, st.st_size)


def evidence_records(overlay: str) -> Table:
    """Parse ``config/overlays/<family>.as_flags.jsonl``; ``Table`` with no
    records when the file is absent.  Malformed / proofless lines fail LOUDLY."""
    path = evidence_path(overlay)
    stamp = _stamp(path)
    if stamp is None:
        _TABLE_CACHE.pop(str(path), None)
        return Table(records=(), by_syn={}, by_true={}, path=path)
    cached = _TABLE_CACHE.get(str(path))
    if cached is not None and cached[0] == stamp:
        return cached[1]
    records: list[Record] = []
    by_syn: dict[str, str] = {}
    by_true: dict[str, list[Record]] = {}
    for lineno, line in enumerate(path.read_text().splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        try:
            rec = json.loads(line)
            if rec.get("schema") != SCHEMA:
                raise ValueError(f"schema {rec.get('schema')!r}")
            flags = str(rec["as_flags"])
            if not rec.get("proof"):
                raise ValueError("missing proof")
            names = [rec["func"]] + ([rec["true_name"]] if rec.get("true_name") else [])
            keys = [_norm_func_key(str(n)) for n in names]
            if not all(_NAME_ENCODED.fullmatch(k) for k in keys):
                raise ValueError(f"func/true_name not name-encoded: {names}")
        except (ValueError, KeyError, TypeError) as exc:
            raise SystemExit(f"{path}:{lineno}: invalid as-flags record: {exc}")
        entry = Record(func_key=keys[0],
                       true_key=keys[1] if len(keys) > 1 else None,
                       as_flags=flags, lineno=lineno)
        # The SYNTHETIC key is an identity, so a repeat with different flags is
        # corruption -- keep the pre-2026-08-23 fail-loud verbatim.
        if by_syn.setdefault(entry.func_key, flags) != flags:
            raise SystemExit(
                f"{path}:{lineno}: conflicting as_flags for {entry.func_key}: "
                f"{by_syn[entry.func_key]!r} vs {flags!r}")
        records.append(entry)
        if entry.true_key:
            by_true.setdefault(entry.true_key, []).append(entry)
    table = Table(records=tuple(records), by_syn=by_syn,
                  by_true={k: tuple(v) for k, v in by_true.items()}, path=path)
    _TABLE_CACHE[str(path)] = (stamp, table)
    return table


def overlay_as_flags_table(overlay: str) -> dict[str, str]:
    """LEGACY flat view: ``{name: flags}`` keyed by BOTH names.

    Kept for the three ``work/g3/overlay_func_compare*.py`` re-exports and any
    reporting caller.  **Do not resolve a row through this** — the bare true
    name is a RAM-slot label and this view cannot tell two owners apart (that
    is the 2026-08-23 bug).  :func:`resolve_as_flags` is the resolver.
    """
    table = evidence_records(overlay)
    flat = dict(table.by_syn)
    for key, recs in table.by_true.items():
        flags = {r.as_flags for r in recs}
        if len(flags) > 1:
            # Two owners of one slot label with different dials: the flat view
            # has no way to say which. Refuse rather than pick.
            raise SystemExit(
                f"{table.path}: bare slot label {key} claimed by "
                f"{len(recs)} records with different as_flags {sorted(flags)!r}; "
                f"the flat table cannot express that — use resolve_as_flags() "
                f"({IDENTITY_DOC} rule R1).")
        flat.setdefault(key, recs[0].as_flags)
    return flat


# ---------------------------------------------------------------------------
# Region-qualified identity index (docs/rowbase_identity.md rule R1)
# ---------------------------------------------------------------------------


@dataclasses.dataclass(frozen=True)
class IdentityIndex:
    """Per-family view of ``rowbase_identity`` needed to disambiguate a slot label.

    ``row_qid``     synthetic row key -> qualified identity (proven regions only)
    ``slot_owners`` bare slot label   -> {qualified identity, ...}
    ``owners``      bare slot label   -> [describe() strings] for the R2 message
    """

    row_qid: dict[str, str]
    slot_owners: dict[str, frozenset]
    owners: dict[str, tuple[str, ...]]


_IDENTITY_MOD = None


def _rowbase_identity():
    """``tools/rowbase_identity.py`` — imported LAZILY.

    Only the disambiguation path needs it, and importing it validates the
    region-id contract over every ``config/overlays/*.rowbase.jsonl``.  The
    common path (a query that names a record's synthetic key, or a row with no
    evidence record at all) never pays for that.
    """
    global _IDENTITY_MOD
    if _IDENTITY_MOD is None:
        mod = sys.modules.get("rowbase_identity")
        if mod is None or not hasattr(mod, "row_refs"):
            tools = str(ROOT / "tools")
            if tools not in sys.path:
                sys.path.insert(0, tools)
            import rowbase_identity as mod  # type: ignore[no-redef]
        _IDENTITY_MOD = mod
    return _IDENTITY_MOD


_INDEX_CACHE: dict[str, tuple[tuple, IdentityIndex]] = {}


def _index_stamp(family: str, ri) -> tuple:
    paths = [ROOT / f"config/overlays/{family}.rowbase.jsonl"]
    for unit in ri.LANDING_UNITS.values():
        if unit.evidence_family == family:
            paths.append(unit.results_path)
    return tuple((str(p), _stamp(p)) for p in paths)


def identity_index(family: str) -> IdentityIndex:
    """Build (or serve cached) the ``(family, foff)`` identity view.

    Census space is the BROAD one (``landed_only=False, match_only=False``) —
    the loud direction of ``rowbase_identity.resolve_legacy``: slot ownership
    is an evidence fact, not a landing fact, so a name is never resolved now
    and ambiguous later.
    """
    ri = _rowbase_identity()
    try:
        fam = ri._family(family)
    except ValueError:
        return IdentityIndex(row_qid={}, slot_owners={}, owners={})
    stamp = _index_stamp(fam, ri)
    cached = _INDEX_CACHE.get(fam)
    if cached is not None and cached[0] == stamp:
        return cached[1]
    row_qid: dict[str, str] = {}
    slot_owners: dict[str, set] = {}
    owners: dict[str, list[str]] = {}
    for ref in ri.row_refs(landed_only=False, match_only=False):
        if ref.family != fam:
            continue
        row_qid.setdefault(_norm_func_key(ref.func), ref.qid)
        slot_owners.setdefault(ref.true_name, set()).add(ref.qid)
        owners.setdefault(ref.true_name, []).append(ref.describe())
    index = IdentityIndex(
        row_qid=row_qid,
        slot_owners={k: frozenset(v) for k, v in slot_owners.items()},
        owners={k: tuple(sorted(v)) for k, v in owners.items()})
    _INDEX_CACHE[fam] = (stamp, index)
    return index


def _as_off(foff) -> int:
    """``0xEFFAC4`` / ``"0xEFFAC4"`` / ``15726276`` -> int.  Results JSONs store
    ints, but queue/report rows sometimes carry the hex string."""
    if isinstance(foff, str):
        return int(foff, 0)
    return int(foff)


def identity_for(family: str, foff: int) -> str | None:
    """``(family, foff)`` -> qualified identity, or ``None`` outside a proven region."""
    ri = _rowbase_identity()
    try:
        fam = ri._family(family)
    except ValueError:
        return None
    region = ri.region_for(fam, _as_off(foff), proven_only=True)
    if region is None:
        return None
    true_name = "func_%08X" % ((_as_off(foff) + region["delta"]) & 0xFFFFFFFF)
    return ri.qualify(true_name, fam, region["region"])


def record_identity(family: str, record: Record) -> str | None:
    """The qualified identity of the ROW a record belongs to, or ``None``.

    Derived from the record's synthetic key — which is the row key — through
    the family's row census, never from its ``true_name`` text.
    """
    return identity_index(family).row_qid.get(record.func_key)


class AmbiguousSlotLabel(SystemExit):
    """A bare true name that two or more rows own, asked for without a region."""


# ---------------------------------------------------------------------------
# main-EXE fallback table
# ---------------------------------------------------------------------------


_MAIN_TABLE: dict[str, str] | None = None


def main_func_as_flags() -> dict[str, str]:
    """``match.DEFAULT_FUNC_AS_FLAGS`` — the main-EXE ``src/w_*.c`` table.

    Prefers an already-imported ``match`` (every LEAD-12b consumer has one, so
    this is free); otherwise spec-loads ``tools/match.py`` and reads the table
    it derives.  There is deliberately no second copy of the configure.py
    AS_FLAGS derivation rule here — this always returns match.py's own answer.
    """
    global _MAIN_TABLE
    mod = sys.modules.get("match")
    if mod is not None and hasattr(mod, "DEFAULT_FUNC_AS_FLAGS"):
        return mod.DEFAULT_FUNC_AS_FLAGS
    if _MAIN_TABLE is None:
        tools = str(ROOT / "tools")
        if tools not in sys.path:
            sys.path.insert(0, tools)
        spec = importlib.util.spec_from_file_location(
            "_asflags_match", ROOT / "tools" / "match.py")
        m = importlib.util.module_from_spec(spec)
        assert spec.loader is not None
        spec.loader.exec_module(m)
        _MAIN_TABLE = dict(m.DEFAULT_FUNC_AS_FLAGS)
    return _MAIN_TABLE


# ---------------------------------------------------------------------------
# Per-CONTAINER defaults (2026-09-06, maspsx general-return-delay install)
# ---------------------------------------------------------------------------
# Distinct from the per-function evidence table above (LEAD 12b) and from a
# truly global default (LEAD 12's veto, 2026-07-03, tools/maspsx_leads.md):
# this is a per-CONTAINER build fact, keyed by family and carried for every
# row of that family regardless of whether the row owns an as_flags record.
#
# ``--fill-shadowed-return-delay`` (work/bridge_wave_20260906/
# maspsx_general_return_delay/REPORT.md, general.patch): the corpus census
# (REPORT.md SS3.3) found no per-instruction discriminator between the two
# DUNGEON sites where retail FILLS the shadowed-producer return-delay slot and
# the four TOWN sites of the byte-identical shape where retail KEEPS it — the
# only axis that separates them is which container's build produced the
# object. docs/bridge_remediation_plan_20260905.md SS3 THE RULE permits a
# per-container assembler switch (never a per-function one), so the flag is
# default-off in maspsx and turned on here for the whole ``dungeon`` family
# only. Measured (REPORT.md SS6.2 arm 2b): with the switch on, the ONLY rows
# in the entire 5,882-row matched corpus whose bytes move are the two target
# dungeon rows (``func_81984AF4``, ``func_8195AE0C``) -- every other dungeon
# row, and every town/main/ovmovie row (which never receive this flag), is
# byte-identical to before.
_CONTAINER_DEFAULT_AS_FLAGS: dict[str, str] = {
    "dungeon": "--fill-shadowed-return-delay",
}


def _merge_container_default(flags: str, family: str | None) -> str:
    """Fold in this family's container-wide default flag, once, if any."""
    extra = _CONTAINER_DEFAULT_AS_FLAGS.get(family or "")
    if not extra or extra in flags.split():
        return flags
    return f"{flags} {extra}".strip()


# ---------------------------------------------------------------------------
# THE resolver
# ---------------------------------------------------------------------------


def _overlay_hit(name: str, *, family: str, table: Table, func: str,
                 foff: int | None) -> tuple[str, str] | None:
    """Overlay-evidence answer for one candidate ``name``, or ``None`` for a miss.

    ``func`` is the caller's row-name argument (used as the row key when the
    name being resolved is the row's TRUE name).  Raises on an ambiguous slot
    label with no region context (rule R2).
    """
    key = _norm_func_key(name)
    # 1. The synthetic row key IS an identity -- always authoritative.
    if key in table.by_syn:
        return (table.by_syn[key], "row-key")
    recs = table.by_true.get(key)
    if not recs:
        return None

    # 2. Region-qualified resolution (rule R1). Region context is either an
    #    explicit foff, or -- when the name being disambiguated is the row's
    #    TRUE name and ``func`` is therefore the row key -- the row key itself.
    qid = None
    if foff is not None:
        qid = identity_for(family, foff)
    elif key != _norm_func_key(func):
        qid = identity_index(family).row_qid.get(_norm_func_key(func))
    if qid is not None:
        for rec in recs:
            if record_identity(family, rec) == qid:
                return (rec.as_flags, "identity")
        # The row is known and owns no record: it has no dial. Definitive.
        return None

    # 3. No region context: the bare name may be used only when it is
    #    unambiguous inside the family (rule R2 -- never first-match).
    index = identity_index(family)
    owners = index.slot_owners.get(key, frozenset())
    if len(recs) == 1 and len(owners) <= 1:
        return (recs[0].as_flags, "bare-unambiguous")
    lines = "\n".join("  " + o for o in index.owners.get(key, ()))
    raise AmbiguousSlotLabel(
        f"{table.path}: AMBIGUOUS SLOT LABEL {key} in family {family!r}: it is a "
        f"RAM-slot label owned by {len(owners)} distinct functions, and "
        f"{len(recs)} as-flags record(s) claim it, so the per-function dial "
        f"cannot be resolved from the name alone ({IDENTITY_DOC} rule R2). "
        f"Owners:\n{lines}\n"
        f"Pass the row's foff -- default_as_flags(func, overlay, true_name, "
        f"foff=<row foff>) -- or query by the synthetic row key.")


def resolve_as_flags(func: str, overlay: str | None = None,
                     true_name: str | None = None, *,
                     foff: int | None = None) -> tuple[str, str]:
    """``(flags, how)`` for one row.  ``how`` names the rung that answered.

    Rungs, first hit wins, per name in ``(func, true_name)``:

    ``row-key``           the name is a record's SYNTHETIC key (an identity)
    ``identity``          resolved through ``(family, foff)`` / the row key
    ``bare-unambiguous``  the bare slot label has exactly one owner in the family
    ``main-table``        ``match.DEFAULT_FUNC_AS_FLAGS`` (the main-EXE route)
    ``none``              no evidence -- ``""``, the pre-LEAD-12b answer

    Deliberately per-function, never global (LEAD 12, veto of 2026-07-03) --
    except for the per-CONTAINER defaults in ``_CONTAINER_DEFAULT_AS_FLAGS``
    above, which this always folds into the ladder's answer before returning.
    """
    family = _family(overlay) if overlay else None
    flags, how = _resolve_as_flags_ladder(func, overlay, true_name,
                                          foff=foff, family=family)
    return (_merge_container_default(flags, family), how)


def _resolve_as_flags_ladder(func: str, overlay: str | None, true_name: str | None,
                             *, foff: int | None, family: str | None) -> tuple[str, str]:
    """The per-function ladder alone, before the per-container default."""
    table = evidence_records(overlay) if overlay else Table((), {}, {}, ROOT)
    main = main_func_as_flags()
    for name in (func, true_name):
        if not name:
            continue
        if family is not None:
            hit = _overlay_hit(name, family=family, table=table, func=func, foff=foff)
            if hit is not None:
                return hit
        key = _norm_func_key(name)
        if key in main:
            return (main[key], "main-table")
    return ("", "none")


def default_as_flags(func: str, overlay: str | None = None,
                     true_name: str | None = None, *,
                     foff: int | None = None) -> str:
    """Per-function default as-flags for this row, or "" when nothing matches.

    ``foff`` is the row's file offset in its container.  Pass it whenever the
    caller has it: it is what makes the answer region-qualified rather than
    slot-label-keyed (``docs/rowbase_identity.md`` rule R1).  Without it a
    query naming a SHARED slot label raises instead of guessing.

    "" is the pre-LEAD-12b behaviour, so a row with no evidence compiles — and
    hashes — exactly as it did before.
    """
    return resolve_as_flags(func, overlay, true_name, foff=foff)[0]


if __name__ == "__main__":  # overlay_as_flags.py <func> [overlay] [true_name] [foff]
    args = sys.argv[1:]
    if not args:
        raise SystemExit(
            "usage: overlay_as_flags.py <func> [overlay] [true_name] [foff]")
    _foff = int(args[3], 0) if len(args) > 3 and args[3] else None
    _flags, _how = resolve_as_flags(*args[:3], foff=_foff)
    print(_flags)
    print(f"# how={_how}", file=sys.stderr)
