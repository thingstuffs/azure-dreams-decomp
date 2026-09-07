#!/usr/bin/env python3
"""Region-qualified true names: the sole derivation authority for rowbase identity.

Spec: ``work/debt_20260729/opt3_region_qualified_names_spec.md`` (option 3, owner
decision 2026-07-29).  This module is task T1 of §7 and implements §5.1 exactly.

THE ONE IDEA
------------
A bare ``func_<TRUE VRAM8>`` is a **RAM-SLOT LABEL, not a function identity**.
Two genuinely different functions living in two different rowbase regions
legitimately carry the same true name (24 such slot groups exist today across
town + dungeon).  The canonical identity is therefore region-qualified::

    func_<VRAM8>__<family>__<region>      e.g. func_800178B4__town__sweep_3F6460

* ``VRAM8``  — the true vram, 8 UPPERCASE hex digits, minted ``"func_%08X"``.
* ``family`` — the EVIDENCE family, i.e. ``overlay_evidence.family_for(unit)``.
  ``dungeon_engine`` normalises to ``dungeon`` on purpose: the two landing units
  share one ``config/overlays/dungeon.rowbase.jsonl``, therefore one region
  namespace, therefore the same function landed in both units gets the SAME
  identity (72 such rows today — correct, not ambiguity).
* ``region`` — the ``region`` field of the matching rowbase record, verbatim.
* The separator is a DOUBLE underscore; no part may contain ``__``.

DERIVED, NEVER PERSISTED (spec §3.5).  Nothing here is written into a ``.c``
file, a results row, a gate YAML or a queue TSV.  Identity is re-derived from
``(landing unit, foff)`` at every use, because ``overlay_local_gate.load_matches``
already carries a fail-loud for a stale persisted ``row["true_name"]`` and a
second derivable-but-persisted name field would only double that staleness
surface.  Row identity stays ``(landing unit, row["func_vram"])`` and TU file
stems stay the synthetic key — neither changes.

WHY BARE NAMES STAY LEGAL IN C TEXT — **PWU** (spec §1.3/§2.1).  Every
proven-region row is mini-linked ALONE and injected into its window as raw bytes
(``overlay_local_gate.py:915-975``), and everything left in the shared link is
synthetic-named and per-window unique (``:291-306``), so no two same-named
objects ever reach one ``ld``.  A qualifier in C source would also silently
break ~10 ``\\b``-bounded ``func_[0-9A-Fa-f]{8}`` scanners.  This module never
asks anyone to rename a symbol.

WHY QUALIFIED IDENTITY IS UNAMBIGUOUS BY CONSTRUCTION — **RIA** (spec §1.4).
Within one rowbase region the delta is a single constant, so ``true = foff +
delta`` is injective on that region, and ``rowbase._records`` fail-closes on
overlapping foff spans, so ``foff -> region`` is a well-defined partial
function.  ``(family, region, vram) <-> (family, foff)`` is therefore a bijection
over proven-region rows: "two functions, one identity" cannot happen.
``ambiguities()`` is the executable statement of that claim, and a non-empty
result means the evidence or a results JSON is CORRUPT — it is never an owner
decision and never a naming choice.

Measured live over all five landing units, 2026-07-29:
2,522 proven-region landed rows -> 2,450 distinct qualified ids, 0 ambiguities,
72 cross-unit duplicates (dungeon n dungeon_engine, same foff = same function),
24 bare-name slot shares.

Imports ``rowbase`` and ``overlay_evidence.family_for`` and nothing else from
the tree.  Validates the region-id contract (spec §3.4 rule 4) at import,
fail-closed: all 188 region ids pass today, and the check exists so a future
hand-added region id cannot silently break parsing.
"""
from __future__ import annotations

import dataclasses
import json
import re
import sys
from pathlib import Path
from typing import Iterable, Sequence

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import overlay_evidence  # noqa: E402
import rowbase  # noqa: E402

SCHEMA = "azure-clean.rowbase-identity.v1"

SPEC_DOC = "work/debt_20260729/opt3_region_qualified_names_spec.md"

# --- §3.4 parsing rule (normative) -----------------------------------------
# Declared exactly as the spec writes them.  NOTE: QID_RE alone is LOOSER than
# the normative rule, because REGION_RE's body allows ``_`` and so would let
# ``sweep__3F6460`` through as a region.  Rule 1 (split on "__" MUST yield
# exactly 3 parts) is the stricter, normative gate and is what ``parse`` runs
# first; QID_RE is the published surface pattern.
QID_RE = re.compile(r"^func_(?P<vram>[0-9A-Fa-f]{8})__(?P<family>[a-z][a-z0-9_]*)"
                    r"__(?P<region>[A-Za-z][A-Za-z0-9_]*)$")
REGION_RE = re.compile(r"^[A-Za-z][A-Za-z0-9_]{0,39}$")

# A bare/legacy slot label.  ALWAYS used with re.fullmatch, never match/search:
# ``func_800178B4_helper`` must NOT be accepted as a true name (session-lead
# review note, 2026-07-29).
BARE_RE = re.compile(r"func_[0-9A-Fa-f]{8}")

SEP = "__"


class AmbiguousTrueName(SystemExit):
    """A bare true name that two or more distinct functions own (spec §5.0 R2).

    Carries every owner so the caller never has to re-derive them; the message
    lists each owner's qualified identity, unit, row key, region, foff and size.
    Never first-match, never silently skip.
    """

    def __init__(self, message: str, owners: Sequence[dict] = ()) -> None:
        super().__init__(message)
        self.message = message
        self.owners = [dict(o) for o in owners]


# ---------------------------------------------------------------------------
# The five landing units (spec §1.1)
# ---------------------------------------------------------------------------


@dataclasses.dataclass(frozen=True)
class Unit:
    """One landing unit: ``(source_dir, results.json, evidence_family)``.

    A ``first_pass_matched`` directory is NOT a link unit — one
    ``overlay.yaml`` gate window can pull TUs from two directories
    (``config/overlays/dungeon_engine.overlay.yaml:83-95``).  This triple is the
    bookkeeping unit; the link unit is a gate window (spec §1.3/§9.3).
    """

    id: str
    source_dir: Path
    results_path: Path
    evidence_family: str

    def at(self, root: Path | str | None) -> "Unit":
        """This unit rebased on ``root`` (tests / alternate trees)."""
        if root is None:
            return self
        return _unit(self.id, Path(root))


def _unit(unit_id: str, root: Path) -> Unit:
    return Unit(id=unit_id,
                source_dir=root / f"overlays/{unit_id}/first_pass_matched",
                results_path=root / f"overlays/{unit_id}/overlay_first_pass_results.json",
                # dungeon_engine -> dungeon, derived live, never hardcoded.
                evidence_family=overlay_evidence.family_for(unit_id))


UNIT_IDS: tuple[str, ...] = ("town", "dungeon", "dungeon_engine", "main", "ovmovie")

LANDING_UNITS: dict[str, Unit] = {u: _unit(u, ROOT) for u in UNIT_IDS}

#: Default ``units=`` argument — all five landing units, in census order.
ALL: tuple[str, ...] = UNIT_IDS

#: The evidence families the five units resolve to (``dungeon_engine`` folds
#: into ``dungeon``).  This is the "known evidence family" set of §3.4 rule 2.
EVIDENCE_FAMILIES: tuple[str, ...] = tuple(
    sorted({u.evidence_family for u in LANDING_UNITS.values()}))


def unit_for(unit: str | Unit, *, root: Path | str | None = None) -> Unit:
    """Resolve a landing-unit id (or a ``Unit``) to a ``Unit``, fail-loud.

    Deliberately strict: a gate/overlay name such as ``town_scene`` is NOT a
    landing unit.  Callers holding a gate name must route it through
    ``overlay_evidence.family_for`` themselves (spec §5.3).
    """
    if isinstance(unit, Unit):
        return unit.at(root) if root is not None else unit
    key = str(unit)
    if key not in LANDING_UNITS:
        raise ValueError(
            f"unknown landing unit {unit!r}; the five units are {list(LANDING_UNITS)} "
            f"({SPEC_DOC} §1.1). A gate/overlay name is not a landing unit.")
    return _unit(key, Path(root)) if root is not None else LANDING_UNITS[key]


def _family(family: str) -> str:
    """Validate an EVIDENCE family name, fail-loud.

    Refusing ``dungeon_engine`` here is the point: passing a raw unit/overlay
    string where an evidence family is required is the exact defect that makes
    ``codex_wave._naming_defect`` mis-classify engine rows as non-rowbase
    (spec §4.2).  ``rowbase._records`` would silently return [] for it.
    """
    key = str(family)
    if key not in EVIDENCE_FAMILIES:
        hint = ""
        try:
            mapped = overlay_evidence.family_for(key)
            hint = f" — did you mean family_for({key!r}) == {mapped!r}?"
        except ValueError:
            pass
        raise ValueError(f"{key!r} is not an evidence family "
                         f"{list(EVIDENCE_FAMILIES)}{hint}")
    return key


# ---------------------------------------------------------------------------
# Rowbase regions (fail-loud parse, mtime-stamped cache)
# ---------------------------------------------------------------------------

# path -> (stat stamp, records).  Only ever holds the newest stamp per path, so
# a jsonl rewritten by ``rowbase.promote`` mid-process is re-read, not served
# stale.  Keeps ``identity_table`` from re-parsing the evidence 6,000 times.
_REGION_CACHE: dict[str, tuple[tuple[int, int] | None, list[dict]]] = {}


def clear_cache() -> None:
    """Drop the region cache. Not normally needed — entries are stamped with the
    jsonl's ``(mtime_ns, size)`` and re-read when it changes — but an explicit
    valve for callers that rewrite evidence in-process (``rowbase.promote``) or
    within one filesystem timestamp tick (tests)."""
    _REGION_CACHE.clear()


def _stamp(path: Path) -> tuple[int, int] | None:
    try:
        st = path.stat()
    except OSError:
        return None
    return (st.st_mtime_ns, st.st_size)


def _records(family: str, *, root: Path | str | None = None) -> list[dict]:
    """``rowbase._records`` for ``family``, rooted at ``root``, cached by mtime.

    Parse errors and overlapping regions still fail loudly — that fail-closed
    behaviour is what makes ``foff -> region`` a well-defined partial function
    (RIA, spec §1.4), so it must not be softened here.
    """
    base = Path(root) if root is not None else ROOT
    path = base / f"config/overlays/{family}.rowbase.jsonl"
    stamp = _stamp(path)
    cached = _REGION_CACHE.get(str(path))
    if cached is not None and cached[0] == stamp:
        return cached[1]
    old = rowbase.ROOT
    try:
        rowbase.ROOT = base
        recs = rowbase._records(family)
    finally:
        rowbase.ROOT = old
    _REGION_CACHE[str(path)] = (stamp, recs)
    return recs


def region_for(family: str, foff: int, *, proven_only: bool = True,
               root: Path | str | None = None) -> dict | None:
    """The rowbase record covering ``foff`` in ``family``, or ``None``.

    ``proven_only`` defaults to **True** (note: the opposite of
    ``rowbase.delta_for``) because identity is a LANDING-side fact: a solved-only
    region has no proven true base, so its rows have no true name and therefore
    no qualified identity (spec §4.1 — the 90 solved-only rows are NOT
    qualified, and no ``__noregion`` sentinel is invented for them).

    Returns a fresh dict — mutating it cannot corrupt the cache::

        {"region": str, "start": int, "end": int, "delta": int,
         "base_confidence": str | None, "rec": dict}

    ``start``/``end``/``delta`` mirror ``rowbase._records`` so callers can
    compute ``foff + delta`` without a second lookup; ``rec`` is a copy of the
    raw jsonl record.
    """
    fam = _family(family)
    off = int(foff)
    for entry in _records(fam, root=root):
        if entry["start"] <= off < entry["end"]:
            rec = entry["rec"]
            confidence = rec.get("base_confidence")
            if proven_only and confidence != "proven":
                return None
            return {"region": rec["region"], "start": entry["start"],
                    "end": entry["end"], "delta": entry["delta"],
                    "base_confidence": confidence, "rec": dict(rec)}
    return None


# ---------------------------------------------------------------------------
# Mint / parse (spec §3.1, §3.4)
# ---------------------------------------------------------------------------


def _bare_vram(true_name: str) -> int:
    """The vram of a bare ``func_<8hex>``; fail-loud on anything else.

    ``re.fullmatch``, never ``match``/``search``: ``func_800178B4_helper`` and
    ``xfunc_800178B4`` are not true names.
    """
    name = str(true_name)
    if not BARE_RE.fullmatch(name):
        raise ValueError(
            f"{true_name!r} is not a bare true name (func_ + exactly 8 hex digits)")
    return int(name[5:13], 16)


def _region_id(region_id: str) -> str:
    rid = str(region_id)
    if SEP in rid or not REGION_RE.fullmatch(rid):
        raise ValueError(
            f"region id {region_id!r} violates the region-id contract "
            f"{REGION_RE.pattern!r} / no '{SEP}' ({SPEC_DOC} §3.4 rule 4)")
    return rid


def qualify(true_name: str, family: str, region_id: str) -> str:
    """Mint ``func_<VRAM8>__<family>__<region>``.

    ``true_name`` may be any case; the mint is always UPPERCASE (``"func_%08X"``),
    matching every existing mint site in the tree.
    """
    vram = _bare_vram(true_name)
    fam = _family(family)
    rid = _region_id(region_id)
    return f"func_{vram:08X}{SEP}{fam}{SEP}{rid}"


def parse(qid: str) -> tuple[str, str, str]:
    """``qid -> (true_name, family, region_id)``; raises ``ValueError`` on malformed.

    Implements §3.4 in order: split on ``__`` MUST yield exactly 3 parts (so a
    region containing ``__`` is a hard error, not a silently accepted region),
    then each part is checked with ``fullmatch``.  ``true_name`` comes back
    canonicalised to uppercase, so ``qualify(*parse(x))`` normalises ``x`` and
    ``parse(qualify(...))`` round-trips.
    """
    text = str(qid)
    parts = text.split(SEP)
    if len(parts) != 3:
        raise ValueError(
            f"{qid!r} is not a qualified identity: split on '{SEP}' yielded "
            f"{len(parts)} part(s), expected exactly 3 "
            f"(func_<VRAM8>{SEP}<family>{SEP}<region>; no part may contain '{SEP}')")
    if not BARE_RE.fullmatch(parts[0]):
        raise ValueError(f"{qid!r}: {parts[0]!r} is not func_ + exactly 8 hex digits")
    fam = _family(parts[1])
    rid = _region_id(parts[2])
    # §3.4 rule 3: the vram is the fixed slice qid[5:13] (identical to
    # parts[0][5:13] once the split rule has passed) — parsing accepts either
    # case, minting always emits uppercase.
    return (f"func_{int(text[5:13], 16):08X}", fam, rid)


def vram_of(name_or_qid: str) -> int:
    """The true vram of a bare true name OR a qualified identity."""
    text = str(name_or_qid)
    if SEP in text:
        return _bare_vram(parse(text)[0])
    return _bare_vram(text)


def is_qualified(name: str) -> bool:
    """True iff ``name`` parses as a qualified identity."""
    try:
        parse(name)
    except ValueError:
        return False
    return True


# ---------------------------------------------------------------------------
# Rows -> identity
# ---------------------------------------------------------------------------


@dataclasses.dataclass(frozen=True)
class RowRef:
    """One results-JSON row that owns a qualified identity."""

    unit: str          # landing-unit id ("dungeon_engine" stays itself)
    func: str          # row["func_vram"] — the synthetic row key AND the TU stem
    foff: int
    size: int | None
    family: str        # evidence family (dungeon_engine -> dungeon)
    region: str
    vram: int          # true vram
    qid: str
    landed: bool       # a TU with this stem exists in the unit's source_dir
    result: str | None

    @property
    def true_name(self) -> str:
        """The BARE slot label — what the C text defines. Not an identity."""
        return f"func_{self.vram:08X}"

    @property
    def source_path(self) -> Path:
        """The TU, anchored at the real tree ROOT (not at a test ``root=``)."""
        return LANDING_UNITS[self.unit].source_dir / f"{self.func}.c"

    def as_dict(self) -> dict:
        d = dataclasses.asdict(self)
        d["true_name"] = self.true_name
        return d

    def describe(self) -> str:
        size = "?" if self.size is None else str(self.size)
        return (f"{self.qid}  unit={self.unit} row={self.func} "
                f"region={self.region} foff=0x{self.foff:X} size={size}")


def _rows(unit: Unit) -> list[dict]:
    """A unit's results rows.

    Missing file -> ``[]`` (a partial test tree is legitimate).  Present but
    unparseable -> ``SystemExit``: silently censusing zero rows out of a corrupt
    results JSON would make the 2,522-row invariant fail invisibly.
    """
    path = unit.results_path
    if not path.is_file():
        return []
    try:
        data = json.loads(path.read_text())
    except (OSError, ValueError) as exc:
        raise SystemExit(f"{path}: unreadable results JSON: {exc}")
    if not isinstance(data, list):
        raise SystemExit(f"{path}: results JSON is not a list")
    return data


def _stems(unit: Unit) -> set[str]:
    d = unit.source_dir
    if not d.is_dir():
        return set()
    return {p.stem for p in d.glob("*.c")}


def identity_for_row(unit: str | Unit, row: dict, *,
                     root: Path | str | None = None) -> str | None:
    """The qualified identity of one results row, or ``None``.

    ``None`` means "no true name": the row has no ``foff``, or its foff is in no
    rowbase region, or the region is only ``solved`` (spec §4.1 — those 741 + 90
    rows keep ``(unit, func_vram)`` as their identity).

    Pure derivation: it does NOT filter on ``rerun`` / ``result`` / TU presence.
    ``identity_table`` applies the landing filter.
    """
    u = unit_for(unit, root=root)
    foff = row.get("foff")
    if foff is None:
        return None
    region = region_for(u.evidence_family, int(foff), proven_only=True, root=root)
    if region is None:
        return None
    true_name = "func_%08X" % ((int(foff) + region["delta"]) & 0xFFFFFFFF)
    return qualify(true_name, u.evidence_family, region["region"])


def row_refs(units: Iterable[str | Unit] = ALL, *, root: Path | str | None = None,
             landed_only: bool = True, match_only: bool = True) -> list[RowRef]:
    """Every proven-region row in ``units``, as ``RowRef``s.

    Defaults are the census space of spec §1.2/§1.4: non-``rerun``,
    ``result == "MATCH"``, TU on disk — 2,522 rows across the five units today.
    """
    out: list[RowRef] = []
    for unit in units:
        u = unit_for(unit, root=root)
        stems = _stems(u)
        rows = []
        for row in _rows(u):
            if row.get("rerun"):
                continue
            if match_only and row.get("result") != "MATCH":
                continue
            func, foff = row.get("func_vram"), row.get("foff")
            if not func or foff is None:
                continue
            landed = func in stems
            if landed_only and not landed:
                continue
            rows.append((int(foff), str(func), row, landed))
        for foff, func, row, landed in sorted(rows, key=lambda r: (r[0], r[1])):
            region = region_for(u.evidence_family, foff, proven_only=True, root=root)
            if region is None:
                continue
            vram = (foff + region["delta"]) & 0xFFFFFFFF
            size = row.get("size")
            out.append(RowRef(
                unit=u.id, func=func, foff=foff,
                size=None if size is None else int(size),
                family=u.evidence_family, region=region["region"], vram=vram,
                qid=qualify("func_%08X" % vram, u.evidence_family, region["region"]),
                landed=landed, result=row.get("result")))
    return out


def identity_table(units: Iterable[str | Unit] = ALL, *,
                   root: Path | str | None = None,
                   landed_only: bool = True,
                   match_only: bool = True) -> dict[str, list[RowRef]]:
    """``{qualified id: [RowRef, ...]}`` over ``units``, keys sorted by id.

    Live today over all five units: 2,522 rows -> 2,450 ids.  The 72-id gap is
    entirely ``dungeon`` n ``dungeon_engine`` same-foff rows — ONE function whose
    TU exists in two landing units (resolved at build time by
    ``only_if_missing: true``).  Same identity for the same function is correct;
    ``ambiguities()`` is what tests for the real defect.
    """
    table: dict[str, list[RowRef]] = {}
    for ref in row_refs(units, root=root, landed_only=landed_only,
                        match_only=match_only):
        table.setdefault(ref.qid, []).append(ref)
    return {qid: table[qid] for qid in sorted(table)}


def ambiguities(units: Iterable[str | Unit] = ALL, *,
                root: Path | str | None = None,
                table: dict[str, list[RowRef]] | None = None,
                landed_only: bool = True,
                match_only: bool = True) -> list[dict]:
    """Qualified ids owned by two or more DISTINCT functions. Must be ``[]``.

    Distinctness is ``(family, func_vram)``: the 72 rows that appear in both
    ``dungeon`` and ``dungeon_engine`` carry one row key and one foff, so they
    are one function in two landing units, not an ambiguity.

    A non-empty result is CORRUPTION (equal foffs in one results JSON, or an
    overlapping/duplicated rowbase record), never an owner decision — RIA
    (spec §1.4) says it is impossible while the evidence is sound.
    """
    if table is None:
        table = identity_table(units, root=root, landed_only=landed_only,
                               match_only=match_only)
    out: list[dict] = []
    for qid, refs in table.items():
        if len({r.func for r in refs}) < 2:
            continue
        first = refs[0]
        out.append({"qid": qid, "vram": first.vram, "family": first.family,
                    "region": first.region,
                    "funcs": sorted({r.func for r in refs}),
                    "owners": [r.as_dict() for r in refs]})
    return sorted(out, key=lambda g: g["qid"])


def slot_shares(units: Iterable[str | Unit] = ALL, *,
                root: Path | str | None = None,
                landed_only: bool = True,
                match_only: bool = True) -> list[dict]:
    """``(family, BARE true name)`` groups owned by 2+ distinct identities.

    Census, not defect (spec §5.4 / §9.4): a cross-region slot share is legal.
    24 groups covering 49 landed rows today.
    """
    by_name: dict[tuple[str, str], list[RowRef]] = {}
    for ref in row_refs(units, root=root, landed_only=landed_only,
                        match_only=match_only):
        by_name.setdefault((ref.family, ref.true_name), []).append(ref)
    out = []
    for (family, true_name), refs in by_name.items():
        qids = sorted({r.qid for r in refs})
        if len(qids) < 2:
            continue
        out.append({"family": family, "true_name": true_name, "qids": qids,
                    "owners": [r.as_dict() for r in refs]})
    return sorted(out, key=lambda g: (g["family"], g["true_name"]))


# ---------------------------------------------------------------------------
# Legacy (bare) name ingest — spec §5.0 R1/R2
# ---------------------------------------------------------------------------


def resolve_legacy(bare: str, *, family: str | None = None, foff: int | None = None,
                   unit: str | Unit | None = None, root: Path | str | None = None,
                   landed_only: bool = False) -> str:
    """A bare ``func_<8hex>`` (e.g. a frozen w77 pack's ``rowbase_true_name``)
    resolved to a qualified identity.

    R1 — with region context, resolve DETERMINISTICALLY.  If ``foff`` is given
    the region is re-derived from it and the name is never searched for; the
    supplied ``bare`` name is cross-checked against the derived one and a
    mismatch raises (that is a stale roster entry, not something to paper over).

    R2 — without ``foff``, search within the family (all five units when no
    family/unit is given).  Exactly one owning identity -> resolve.  Two or more
    -> raise ``AmbiguousTrueName`` listing EVERY owner with its region, foff and
    size.  Never first-match, never silently skip.

    ``landed_only`` defaults to **False** for the search: slot ownership is an
    evidence fact, not a landing fact, so a row whose TU has not landed yet still
    counts as an owner.  That is the loud direction — a name is never resolved
    now and ambiguous later.  Pass ``landed_only=True`` for the §1.4 census
    space (24 ambiguous names instead of 44).

    Also accepts an already-qualified id (validated, canonicalised, and checked
    against ``foff`` when one is supplied), so a boundary can call this on input
    of either shape.
    """
    text = str(bare)
    fam: str | None = None
    if unit is not None:
        fam = unit_for(unit, root=root).evidence_family
    if family is not None:
        fam2 = _family(family)
        if fam is not None and fam2 != fam:
            raise ValueError(f"resolve_legacy: unit {unit!r} is family {fam!r} but "
                             f"family={family!r} was also passed")
        fam = fam2

    already = parse(text) if SEP in text else None
    if already is not None and fam is not None and already[1] != fam:
        raise ValueError(f"resolve_legacy: {text!r} is family {already[1]!r}, "
                         f"not {fam!r}")
    name = already[0] if already is not None else f"func_{_bare_vram(text):08X}"

    if foff is not None:
        if fam is None:
            raise ValueError(
                "resolve_legacy: foff needs region context — pass family= or unit= "
                f"(spec §5.0 R1). Got foff=0x{int(foff):X} for {bare!r}.")
        off = int(foff)
        region = region_for(fam, off, proven_only=True, root=root)
        if region is None:
            raise ValueError(
                f"resolve_legacy: foff 0x{off:X} in family {fam!r} is in no PROVEN "
                f"rowbase region — that row has no true name, so it has no "
                f"qualified identity (its identity stays (unit, func_vram)).")
        derived = "func_%08X" % ((off + region["delta"]) & 0xFFFFFFFF)
        if derived != name:
            raise ValueError(
                f"resolve_legacy: {bare!r} does not belong to foff 0x{off:X} in "
                f"family {fam!r}: region {region['region']} (delta "
                f"0x{region['delta']:X}) derives {derived}. The foff is "
                f"authoritative (spec §5.0 R1) — fix the caller's name.")
        qid = qualify(derived, fam, region["region"])
        if already is not None and qualify(*already) != qid:
            raise ValueError(f"resolve_legacy: {text!r} disagrees with foff "
                             f"0x{off:X}, which derives {qid}")
        return qid

    if already is not None:
        return qualify(*already)

    search_units = [u for u in ALL
                    if fam is None or unit_for(u, root=root).evidence_family == fam]
    # Broad space (the default): every non-rerun row with a proven-region foff,
    # landed or not, MATCH or not. Narrow space (landed_only=True): the §1.4
    # census space, i.e. landed MATCH rows only.
    owners = [r for r in row_refs(search_units, root=root,
                                  landed_only=landed_only, match_only=landed_only)
              if r.true_name == name and (fam is None or r.family == fam)]
    by_qid: dict[str, list[RowRef]] = {}
    for ref in owners:
        by_qid.setdefault(ref.qid, []).append(ref)

    if not by_qid:
        scope = f"family {fam!r}" if fam else "any of the five landing units"
        raise ValueError(
            f"resolve_legacy: no proven-region row in {scope} owns the slot "
            f"{name} — it cannot be qualified. Either the name is synthetic, or "
            f"its region is not proven yet.")
    if len(by_qid) == 1:
        return next(iter(by_qid))

    refs = sorted(owners, key=lambda r: (r.qid, r.unit, r.foff))
    scope = f"family {fam!r}" if fam else "the five landing units"
    lines = "\n".join("  " + r.describe() for r in refs)
    raise AmbiguousTrueName(
        f"AMBIGUOUS TRUE NAME {name}: in {scope} it is a RAM-SLOT LABEL owned by "
        f"{len(by_qid)} distinct functions in different rowbase regions, not an "
        f"identity ({SPEC_DOC} §5.0 R2). Owners:\n{lines}\n"
        f"Resolve it deterministically by passing the row's foff — every boundary "
        f"that holds the row has it: resolve_legacy({name!r}, family={fam!r}, "
        f"foff=<row foff>).",
        owners=[r.as_dict() for r in refs])


# ---------------------------------------------------------------------------
# Region-id contract (spec §3.4 rule 4) — validated at import, fail-closed
# ---------------------------------------------------------------------------


def validate_region_contract(root: Path | str | None = None) -> int:
    """Every region id in every ``config/overlays/*.rowbase.jsonl`` must
    fullmatch ``REGION_RE`` and must not contain ``__``.

    Returns the number of regions checked (188 today).  Raises ``SystemExit``
    naming every offender: a region id that breaks the parsing rule would make
    ``parse`` silently mis-split identities, so this is fail-closed and runs at
    import.  It only VALIDATES — it never renames a region.
    """
    base = Path(root) if root is not None else ROOT
    checked = 0
    bad: list[str] = []
    for path in sorted((base / "config/overlays").glob("*.rowbase.jsonl")):
        family = path.name[:-len(".rowbase.jsonl")]
        for entry in _records(family, root=base):
            rid = entry["rec"].get("region")
            checked += 1
            if not isinstance(rid, str) or SEP in rid or not REGION_RE.fullmatch(rid):
                bad.append(f"{path.name}: region {rid!r}")
    if bad:
        raise SystemExit(
            "REGION-ID CONTRACT VIOLATION — a rowbase region id is not parseable "
            f"as part of a qualified identity ({SPEC_DOC} §3.4 rule 4). Every id "
            f"must fullmatch {REGION_RE.pattern!r} and contain no '{SEP}':\n  "
            + "\n  ".join(bad)
            + "\nFix the record. Nothing renames a region automatically.")
    return checked


#: Regions validated at import time (188 today). Recomputed on every import.
REGION_COUNT: int = validate_region_contract()


# ---------------------------------------------------------------------------
# CLI (read-only receipt; exit 0 — this module is not a gate)
# ---------------------------------------------------------------------------


def _summary(root: Path | str | None = None) -> dict:
    table = identity_table(root=root)
    refs = [r for refs in table.values() for r in refs]
    per_unit: dict[str, int] = {}
    for ref in refs:
        per_unit[ref.unit] = per_unit.get(ref.unit, 0) + 1
    return {
        "schema": SCHEMA,
        "units": list(ALL),
        "region_count": REGION_COUNT,
        "proven_region_rows": len(refs),
        "qualified_ids": len(table),
        "rows_per_unit": per_unit,
        "identity_ambiguities": len(ambiguities(table=table)),
        "cross_unit_duplicates": sum(
            1 for refs_ in table.values() if len({r.unit for r in refs_}) > 1),
        "slot_shares": len(slot_shares(root=root)),
    }


if __name__ == "__main__":
    import argparse

    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("summary", help="census over the five landing units (JSON)")
    p = sub.add_parser("owners", help="every qualified owner of a bare true name")
    p.add_argument("--symbol", required=True)
    p.add_argument("--family")
    args = ap.parse_args()
    if args.cmd == "summary":
        print(json.dumps(_summary(), indent=1))
    else:
        name = f"func_{_bare_vram(args.symbol):08X}"
        fam = _family(args.family) if args.family else None
        found = [r for r in row_refs(landed_only=False, match_only=False)
                 if r.true_name == name and (fam is None or r.family == fam)]
        print(json.dumps([r.as_dict() for r in
                          sorted(found, key=lambda r: (r.qid, r.unit))], indent=1))
