#!/usr/bin/env python3
"""Landing-identity screen + region-qualified naming receipt (option 3).

WHY THIS EXISTS
---------------
``docs/rowbase_lane_phase2.md`` item 2 (owner decision B) says: a TU landed
inside a PROVEN rowbase region defines the function under its TRUE-space name
(``func_<foff+delta>``) while the result row keeps its synthetic key.  The
original screen built on that doc read its NOTE as "two TUs may never define one
true name", and enforced that by treating each ``first_pass_matched`` directory
as ONE link unit.  Both halves of that model are wrong and
``work/debt_20260729/opt3_region_qualified_names_spec.md`` (owner decision,
2026-07-29) replaces them:

* **A directory is not a link unit.**  One ``overlay.yaml`` gate window can pull
  TUs from two directories (``config/overlays/dungeon_engine.overlay.yaml:83-95``
  merges ``overlays/dungeon/first_pass_matched`` with
  ``overlays/dungeon_engine/first_pass_matched``).  The link unit is a GATE
  WINDOW; the bookkeeping unit is a **landing unit** — the
  ``(source_dir, results.json, evidence_family)`` triple of spec §1.1.  There
  are five, and ``dungeon_engine`` resolves its rows against ``dungeon``'s
  evidence file, which is why its 76 debt rows were invisible to the old
  three-family census.
* **A bare true name is a RAM-SLOT LABEL, not an identity.**  Two genuinely
  different functions in two different rowbase regions legitimately carry the
  same ``func_<true vram>`` (24 such slot groups live today).  The canonical
  identity is region-qualified — ``func_<VRAM8>__<family>__<region>``, derived by
  ``tools/rowbase_identity.py`` and never written into C source.

**PWU (Per-Window Uniqueness)** is what makes the bare label legal in C text: for
every ``ld`` the tree emits, no two input objects define one strong global.  Held
by construction — every proven-region row is mini-linked ALONE and injected as
raw bytes (``tools/overlay_local_gate.py:915-975``), and everything left in the
shared link is synthetic-named and per-window unique (``:291-306``).  It is
enforced by ``overlay_local_gate.assert_unique_globals`` (spec §2.2), at the
gate, not here.

So this module no longer asks "is this name taken?".  It asks two different
questions (spec §5.3):

* **(a) self-address correctness** — ``check_landing_identity`` is the ONLY
  refusal left.  A TU that defines a ``func_<8hex>`` global which is neither its
  synthetic row key nor the true name its own foff derives is self-addressing at
  the WRONG BASE (the WINDOW-LINK DIVERGENCE class,
  ``rowbase_rename_reverify.py:12-18``), and no name-uniqueness test can see it.
  Another TU defining the same bare name but resolving to a DIFFERENT qualified
  identity is a legal cross-region slot share: allowed, and recorded.
* **(b) structural invariants** — ``assert_region_injectivity`` (RIA),
  ``assert_stem_uniqueness`` and ``assert_pwu``.  A violation of any of them is
  evidence/tree CORRUPTION, never an owner call: the messages say so and never
  offer the ``static`` / copy-suffix workflow.

and it is still the single source of truth for "who owns symbol X", used by BOTH
the live screens (``overlay_land_function.land_function``, ``rowbase.promote``,
``rowbase_rename_reverify``) and the offline receipt (``report()``), so the two
can never drift apart.

Comment awareness: identifier scans run over a masked copy of the source in
which comments and string/char literal bodies are blanked (offsets preserved),
so a true name mentioned only in a ``/* ... */`` or ``//`` comment is neither a
false "compliant" nor a false owner.

Usage:
  tools/rowbase_naming_debt.py report [--unit town ...] [--json PATH]
  tools/rowbase_naming_debt.py owners --symbol func_800178B4 [--family town]
                                      [--unit dungeon_engine]
Exit: 0 always for ``report``/``owners`` (it is a receipt, not a gate);
      the blocking behaviour lives in the callers listed above.
"""
from __future__ import annotations

import json
import re
import sys
import time
from collections.abc import Mapping
from pathlib import Path
from typing import Iterable, Sequence

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(Path(__file__).resolve().parent))
import rowbase  # noqa: E402
import rowbase_identity  # noqa: E402
from overlay_evidence import family_for  # noqa: E402

SCHEMA = "azure-clean.rowbase-naming-debt.v2"
SPEC_DOC = "work/debt_20260729/opt3_region_qualified_names_spec.md"

#: The five landing units of spec §1.1 (``rowbase_identity`` is the authority).
DEFAULT_UNITS: tuple[str, ...] = rowbase_identity.UNIT_IDS

FUNC_RE = re.compile(r"\bfunc_[0-9A-Fa-f]{8}\b")
# A bare slot label.  ALWAYS ``fullmatch`` — ``func_800178B4_helper`` and
# ``xfunc_800178B4`` are NOT true names (session-lead review note 2026-07-29).
BARE_RE = rowbase_identity.BARE_RE
# `#define BODY_NAME func_80D17074` — the bank-table composite shape defines its
# body through a macro alias (overlays/dungeon/first_pass_matched/func_80D17000.c).
MACRO_ALIAS_RE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)[ \t]+"
                            r"(func_[0-9A-Fa-f]{8})[ \t]*$", re.M)
# `__asm__("func_XXXXXXXX")` symbol pin (both the composite table definition and
# the noreturn-scaffolding `extern ... __asm__("...")` declaration use this).
ASM_NAME_RE = re.compile(r'__asm__?\s*\(\s*"(func_[0-9A-Fa-f]{8})"')
GLOBL_RE = re.compile(r'\.globl\s+(func_[0-9A-Fa-f]{8})')

#: Where PWU is actually enforced.  Named here so the landing layer and the gate
#: layer quote one site (spec §2.2; ``tools/overlay_local_gate.py`` is task T3).
PWU_ENFORCER = "tools/overlay_local_gate.py::assert_unique_globals (spec §2.2)"

#: Every structural-invariant message ends with this.  A violation is CORRUPTION
#: of the evidence or the tree — it is never resolved by an owner naming choice,
#: so no ``static`` / copy-suffix workflow is offered (spec §5.3(b)).
CORRUPTION_HINT = (
    "This is evidence/tree corruption — fix the record. It is NOT an owner "
    "naming decision: region injectivity (spec §1.4) makes it impossible while "
    "the evidence is sound, so `static`, a copy-suffixed file name and picking a "
    "winner are all wrong answers here. Nothing was written.")


# ---------------------------------------------------------------------------
# Source scanning
# ---------------------------------------------------------------------------


def mask_source(src: str) -> str:
    """Blank comments and string/char literal bodies, preserving every offset.

    Structural scans (brace depth, definition shape) must not see braces or
    identifiers that live inside a comment or a literal.  Offsets are preserved
    so a match position in the mask indexes the same character in the original.
    """
    out = list(src)
    i, n = 0, len(src)
    while i < n:
        c = src[i]
        if c == "/" and i + 1 < n and src[i + 1] == "*":
            j = src.find("*/", i + 2)
            j = n if j < 0 else j + 2
        elif c == "/" and i + 1 < n and src[i + 1] == "/":
            j = src.find("\n", i)
            j = n if j < 0 else j
        elif c in "\"'":
            quote, j = c, i + 1
            while j < n:
                if src[j] == "\\":
                    j += 2
                    continue
                if src[j] == quote:
                    j += 1
                    break
                if src[j] == "\n":  # unterminated literal: stop at the newline
                    break
                j += 1
            # keep the delimiters themselves so the span is still recognisable
            i += 1
            j = min(j, n)
            for k in range(i, max(i, j - 1)):
                out[k] = "\n" if src[k] == "\n" else " "
            i = j
            continue
        else:
            i += 1
            continue
        for k in range(i, j):
            out[k] = "\n" if src[k] == "\n" else " "
        i = j
    return "".join(out)


def _depths(masked: str) -> list[int]:
    """Brace depth immediately BEFORE each character."""
    depth = 0
    out = []
    for ch in masked:
        out.append(depth)
        if ch == "{":
            depth += 1
        elif ch == "}":
            depth = max(0, depth - 1)
    out.append(depth)
    return out


def _balanced_close(text: str, open_idx: int) -> int | None:
    depth = 0
    for i in range(open_idx, len(text)):
        if text[i] == "(":
            depth += 1
        elif text[i] == ")":
            depth -= 1
            if depth == 0:
                return i
    return None


def _skip_ws(text: str, i: int) -> int:
    while i < len(text) and text[i].isspace():
        i += 1
    return i


def _declaration_start(masked: str, idx: int) -> int:
    """Start of the declaration containing ``idx`` (previous ``;``/``{``/``}``)."""
    start = 0
    for ch in (";", "{", "}"):
        pos = masked.rfind(ch, 0, idx)
        if pos + 1 > start:
            start = pos + 1
    return start


def _stronger(a: str | None, b: str) -> str:
    """global beats static — a symbol defined globally anywhere in the TU is global."""
    return "global" if "global" in (a, b) else b


#: Everything between the previous ``;``/``{``/``}`` and a declarator name has to
#: look like a TYPE — words, whitespace and pointer stars, ending in an
#: identifier.  An EMPTY head (``name[i] = 0;`` after a ``;``) and a head holding
#: an operator (``x = name``) are exactly what this rejects.
_OBJECT_HEAD_RE = re.compile(r"^[\s\w*]*\b\w+\s*\**\s*$")
#: Preprocessor lines are not part of a declaration head (`#ifdef __mips__`
#: routinely sits between the previous `;` and a guarded definition).
_DIRECTIVE_RE = re.compile(r"(?m)^[ \t]*#.*$")
#: Declarator name -> ``=``: optional array bounds and GCC attributes, nothing
#: else.  Parenthesised groups are taken whole so ``__attribute__((section(..)))``
#: passes; the excluded operator characters keep ``name != x`` and ``name <= x``
#: from ever reaching the ``=``.
_OBJECT_TAIL_RE = re.compile(r"(?:[^;={}()<>!+\-*/%&|^~?]|\([^;{}]*\))*=(?!=)")
#: Bound on the declarator tail scan — a definition head is never this long, and
#: an unbounded scan over a whole TU is the only way this regex gets expensive.
_OBJECT_TAIL_SPAN = 4096


def _object_definition_at(masked: str, start: int, end: int) -> str | None:
    """Linkage of the file-scope C OBJECT definition whose declarator name
    occupies ``masked[start:end]``, or ``None`` when that occurrence is not one.

    A row symbol does not have to be a function.  The COMPOSITE DATA shape —
    ``const OverlayInitData func_80950CC0 __attribute__((section(".text.…"))) =
    { … };`` (overlays/town, w80 2026-08-03) — defines the row symbol as a
    plain C object: no ``(`` after the name and no ``__asm__("func_…")`` pin, so
    both shapes ``file_definitions`` knew about missed it entirely.

    Conservative on purpose; all three must hold.

    * **file scope** — brace depth 0, so a local ``int name = 3;`` and an
      assignment ``name[i] = 0;`` inside a body cannot qualify;
    * **a type before it** — the declaration head is words/stars only and does
      not say ``extern``, so ``extern int name;`` and ``x = name;`` are out;
    * **an initializer after it** — ``name … =``, so a prototype, a call, a
      tentative definition and every read of the name are out.
    """
    if masked.count("{", 0, start) != masked.count("}", 0, start):
        return None
    head = _DIRECTIVE_RE.sub("", masked[_declaration_start(masked, start):start])
    if not _OBJECT_HEAD_RE.match(head) or re.search(r"\bextern\b", head):
        return None
    if not _OBJECT_TAIL_RE.match(masked, end, min(len(masked),
                                                  end + _OBJECT_TAIL_SPAN)):
        return None
    return "static" if re.search(r"\bstatic\b", head) else "global"


def defines_object(masked: str, name: str) -> bool:
    """True when the MASKED source defines ``name`` as a file-scope C object.

    The one predicate both naming screens ask, so
    ``codex_wave._naming_defect`` and this module's ``file_definitions`` cannot
    disagree about the composite data shape (the same reason
    ``codex_wave._mask_source`` delegates to ``mask_source``).
    """
    return any(_object_definition_at(masked, m.start(), m.end()) is not None
               for m in re.finditer(rf"\b{re.escape(name)}\b", masked))


def file_definitions(src: str) -> dict[str, str]:
    """Symbols this translation unit DEFINES -> ``"global"`` or ``"static"``.

    Declarations (``extern void func_X();``), prototypes, call sites and comment
    mentions are not definitions.  Recognised definition shapes:

    * a top-level ``NAME(args) {`` function definition (``NAME`` may be an
      object-like macro that aliases a ``func_`` name);
    * an ``__asm__("func_X")`` symbol pin on a non-``extern`` declarator that
      carries an initializer — the bank-table composite shape.  Its linkage is
      ``global`` when the TU also emits ``.globl func_X``.
    * a file-scope C OBJECT definition, ``const T func_X … = { … };``
      (``defines_object``) — the same composite shape written WITHOUT a pin,
      i.e. the row symbol is the declarator's own name.  Added 2026-08-03 with
      the matching ``codex_wave._naming_defect`` fix so the collect screen and
      the landing screen see one set of definition shapes.  Scanned over every
      landed TU and all 12485 wave candidates on disk it adds exactly one
      symbol (``func_80950CC0`` in its own TU), so it widens no refusal in
      ``check_landing_identity`` — a name equal to the TU's own row key is the
      one thing that screen never objects to.
    """
    masked = mask_source(src)
    depths = _depths(masked)
    aliases: dict[str, set[str]] = {}
    for m in MACRO_ALIAS_RE.finditer(src):
        aliases.setdefault(m.group(1), set()).add(m.group(2))

    out: dict[str, str] = {}
    names = "|".join([r"func_[0-9A-Fa-f]{8}"]
                     + [re.escape(a) for a in sorted(aliases)])
    for m in re.finditer(rf"\b(?:{names})\b", masked):
        token = m.group(0)
        i = _skip_ws(masked, m.end())
        if i >= len(masked) or masked[i] != "(":
            obj = _object_definition_at(masked, m.start(), m.end())
            if obj is not None:
                for name in (aliases.get(token) or {token}):
                    out[name] = _stronger(out.get(name), obj)
            continue
        close = _balanced_close(masked, i)
        if close is None:
            continue
        j = _skip_ws(masked, close + 1)
        if j >= len(masked) or masked[j] != "{":
            continue
        if depths[m.start()] != 0:
            continue
        head = masked[_declaration_start(masked, m.start()):m.start()]
        linkage = "static" if re.search(r"\bstatic\b", head) else "global"
        for name in (aliases.get(token) or {token}):
            out[name] = _stronger(out.get(name), linkage)

    globl = set(GLOBL_RE.findall(src))
    for m in ASM_NAME_RE.finditer(src):
        name = m.group(1)
        head = src[_declaration_start(masked, m.start()):m.start()]
        if re.search(r"\bextern\b", head):
            continue  # `extern void f(void) __asm__("func_X");` is an alias decl
        tail_end = src.find(";", m.end())
        tail = src[m.end():tail_end if tail_end >= 0 else len(src)]
        if "=" not in tail and "{" not in tail:
            continue  # a declarator with no initializer/body defines nothing
        out[name] = _stronger(out.get(name), "global" if name in globl else "static")
    return out


# ---------------------------------------------------------------------------
# Landing units (spec §1.1) — a UNIT, never a bare family, is the scope
# ---------------------------------------------------------------------------


def unit_id(name: str) -> str:
    """Resolve ``name`` to one of the five landing-unit ids, fail-loud.

    Accepts a landing-unit id (``dungeon_engine`` stays itself), a family, or a
    gate/overlay name (``town_scene`` -> ``town``, via ``family_for``).  A name
    that maps to nothing raises ``ValueError`` — never a silent default, which is
    the exact defect that makes ``codex_wave._naming_defect`` treat engine rows
    as non-rowbase (spec §4.2).
    """
    key = str(name)
    if key in rowbase_identity.LANDING_UNITS:
        return key
    fam = family_for(key)  # raises ValueError on an unmappable name
    if fam not in rowbase_identity.LANDING_UNITS:  # pragma: no cover - defensive
        raise ValueError(f"{name!r} maps to family {fam!r}, which is not a "
                         f"landing unit {list(rowbase_identity.LANDING_UNITS)}")
    return fam


def family_of(name: str) -> str:
    """The EVIDENCE family of a landing unit / family / gate name.

    ``dungeon_engine -> dungeon``: the two units share
    ``config/overlays/dungeon.rowbase.jsonl``, therefore one region namespace.
    """
    return family_for(str(name))


def units_of_family(family: str) -> list[str]:
    """Every landing unit whose evidence family is ``family``."""
    return [u for u in DEFAULT_UNITS
            if rowbase_identity.LANDING_UNITS[u].evidence_family == family]


def source_dir_for(unit: str, *, root: Path | None = None) -> Path:
    return (root or ROOT) / f"overlays/{unit_id(unit)}/first_pass_matched"


def results_path_for(unit: str, *, root: Path | None = None) -> Path:
    return ((root or ROOT)
            / f"overlays/{unit_id(unit)}/overlay_first_pass_results.json")


def _rows(unit: str, *, root: Path | None = None) -> list[dict]:
    path = results_path_for(unit, root=root)
    if not path.is_file():
        return []
    try:
        data = json.loads(path.read_text())
    except (OSError, ValueError):
        return []
    return data if isinstance(data, list) else []


def _regions(family: str, *, root: Path | None = None) -> list[dict]:
    """Every rowbase record for ``family`` (proven AND solved), fail-loud parse."""
    old = rowbase.ROOT
    try:
        rowbase.ROOT = root or ROOT
        return rowbase._records(family)
    finally:
        rowbase.ROOT = old


def _proven_region_at(family: str, foff: int, *, root: Path | None = None) -> dict | None:
    return rowbase_identity.region_for(family, int(foff), proven_only=True,
                                       root=root or ROOT)


def _row_index(units: Iterable[str], *, root: Path | None = None
               ) -> dict[str, tuple[str, int, int | None]]:
    """``{func_vram: (unit, foff, size)}`` over ``units`` (first unit wins)."""
    out: dict[str, tuple[str, int, int | None]] = {}
    for unit in units:
        for row in _rows(unit, root=root):
            if row.get("rerun"):
                continue
            func, foff = row.get("func_vram"), row.get("foff")
            if not func or foff is None or func in out:
                continue
            size = row.get("size")
            out[str(func)] = (unit, int(foff),
                              None if size is None else int(size))
    return out


# ---------------------------------------------------------------------------
# Unit-level ownership
# ---------------------------------------------------------------------------


def landed_definitions(unit: str, *, source_dir: Path | None = None,
                       root: Path | None = None,
                       exclude: Iterable[str] = (),
                       include_static: bool = False) -> dict[str, list[str]]:
    """``{bare symbol: [defining TU stem, ...]}`` for one landing unit.

    A LINK fact, deliberately kept link-shaped: what the C text defines is a bare
    slot label, so this map stays keyed on bare names.  ``landed_identities`` is
    the identity-shaped view the report keys on.

    Only GLOBAL definitions are reported unless ``include_static``; a ``static``
    definition cannot reach a link at all.
    """
    directory = (source_dir if source_dir is not None
                 else source_dir_for(unit, root=root))
    skip = set(exclude)
    owners: dict[str, list[str]] = {}
    if not directory.is_dir():
        return owners
    for path in sorted(directory.glob("*.c")):
        stem = path.stem
        if stem in skip:
            continue
        try:
            text = path.read_text(errors="replace")
        except OSError:
            continue
        for name, linkage in file_definitions(text).items():
            if linkage != "global" and not include_static:
                continue
            owners.setdefault(name, []).append(stem)
    return owners


def landed_identities(unit: str, *, root: Path | None = None) -> dict[str, list[str]]:
    """``{qualified id: [TU stem, ...]}`` for one landing unit.

    Derived, never persisted (spec §3.5): the id comes from ``(unit, foff)``
    through ``rowbase_identity``, not from any field in the results row or the
    source.  Rows with no proven region have no true name and therefore no
    qualified identity — they are absent here, and their identity stays
    ``(unit, func_vram)``.
    """
    out: dict[str, list[str]] = {}
    for qid, refs in rowbase_identity.identity_table([unit_id(unit)],
                                                     root=root or ROOT).items():
        out[qid] = sorted({r.func for r in refs})
    return out


# ---------------------------------------------------------------------------
# (a) The landing screen — self-address correctness (spec §5.3(a))
# ---------------------------------------------------------------------------


def _bare_globals(defined_globals) -> list[str]:
    """The bare ``func_<8hex>`` GLOBAL symbols out of a caller's definition set.

    Accepts either an iterable of symbol names or the ``file_definitions`` map
    (in which case ``static`` linkage is dropped — a static definition never
    reaches a link).  ``fullmatch`` only: ``func_800178B4_helper`` is not a slot
    label and must not be screened as one.
    """
    if isinstance(defined_globals, Mapping):
        names = [n for n, linkage in defined_globals.items() if linkage == "global"]
    elif isinstance(defined_globals, str):
        names = [defined_globals]
    else:
        names = list(defined_globals or ())
    return [n for n in dict.fromkeys(names) if n and BARE_RE.fullmatch(n)]


def _base_aliases(family: str, foff: int, synthetic: str, *,
                  root: Path | None = None) -> dict[str, str]:
    """``{name: why}`` for every name THIS row would carry under another base.

    A wrong-base self-address is the same function written at a different link
    base, so the names it can wear are exactly: the synthetic (window) name, and
    ``func_<foff + delta>`` for every rowbase region in the family — proven or
    solved.  Membership here is what makes a foreign global provably the
    WINDOW-LINK DIVERGENCE defect rather than an unrelated extra symbol.
    """
    out: dict[str, str] = {synthetic: "the synthetic/window base"}
    for entry in _regions(family, root=root):
        name = "func_%08X" % ((int(foff) + entry["delta"]) & 0xFFFFFFFF)
        rec = entry["rec"]
        out.setdefault(name, f"region {rec.get('region')} "
                             f"({rec.get('base_confidence')} base, "
                             f"delta 0x{entry['delta']:X})")
    return out


def self_address_error(unit: str, func: str, symbol: str, expected: str,
                       synthetic: str, why: str | None, *,
                       action: str = "landing") -> str:
    """The one refusal message left in the landing path (spec §5.3(a))."""
    origin = (f" That name is what this row would be called at {why} — i.e. the "
              f"TU is compiled against the wrong link base." if why else
              " That name belongs to neither base this row can legally use.")
    return (
        f"WRONG-BASE SELF-ADDRESS REFUSED: {action} {func} in landing unit "
        f"{unit!r} defines the global {symbol}, which is neither its synthetic "
        f"row key {synthetic} nor the true name {expected} that its own foff "
        f"derives.{origin} This is the WINDOW-LINK DIVERGENCE class "
        f"(tools/rowbase_rename_reverify.py:12-18): the TU's own local j words "
        f"resolve into the wrong address space, and no name-uniqueness test can "
        f"see it. Rebuild the candidate against the base its foff derives, then "
        f"re-run. Nothing was written: this {action} was refused before any "
        f"file, journal or backup was touched. "
        f"(NOTE: two TUs sharing one bare true name across DIFFERENT rowbase "
        f"regions is legal and is NOT what this refusal is about — "
        f"{SPEC_DOC} §5.3.)")


def corruption_error(kind: str, detail: str, *, action: str = "landing") -> str:
    """A structural-invariant violation message (spec §5.3(b))."""
    return f"{kind} — {action} REFUSED. {detail} {CORRUPTION_HINT}"


def check_landing_identity(unit: str, func: str, foff: int | None,
                           defined_globals, *,
                           size: int | None = None,
                           source_dir: Path | None = None,
                           root: Path | None = None,
                           owners: dict[str, list[str]] | None = None,
                           action: str = "landing") -> dict:
    """Screen one landing against the QUALIFIED identity model (spec §5.3).

    Replaces ``check_landing_collision``.  It refuses exactly one thing — a TU
    self-addressing at the wrong base — and RECORDS, without refusing, the legal
    case where another TU in the unit defines the same bare true name but
    resolves to a different qualified identity (the 14 landed pairs / 24 slot
    groups).  Structural violations (RIA, stem uniqueness) raise as corruption.

    ``defined_globals`` is the candidate's definition set: either the
    ``file_definitions`` map or an iterable of global symbol names.

    Returns a record the caller can log::

        {"unit","func","foff","family","synthetic","expected","region","qid",
         "interior_labels":[...], "slot_shares":[...], "notes":[str,...]}

    Raises ``SystemExit`` on refusal; returns cleanly otherwise.
    """
    uid = unit_id(unit)
    family = family_of(uid)
    synthetic = str(func)
    directory = (source_dir if source_dir is not None
                 else source_dir_for(uid, root=root))

    region = None if foff is None else _proven_region_at(family, foff, root=root)
    expected = synthetic
    qid = None
    if region is not None:
        expected = "func_%08X" % ((int(foff) + region["delta"]) & 0xFFFFFFFF)
        qid = rowbase_identity.qualify(expected, family, region["region"])

    # --- (a) self-address correctness -------------------------------------
    candidate = _bare_globals(defined_globals)
    aliases = ({} if foff is None
               else _base_aliases(family, foff, synthetic, root=root))
    if size is None:
        # sibling units of the family too: a caller holding the family name
        # ("dungeon") may be landing into the dungeon_engine source_dir.
        entry = _row_index(units_of_family(family), root=root).get(synthetic)
        size = entry[2] if entry else None
    base_vram = (rowbase_identity.vram_of(expected)
                 if BARE_RE.fullmatch(expected) else None)

    interior: list[str] = []
    for symbol in candidate:
        if symbol in (synthetic, expected):
            continue
        why = aliases.get(symbol)
        if why is None and size is not None and base_vram is not None:
            # An INTERIOR LABEL: a second symbol inside this row's own
            # [base, base + size) byte span — the bank-table composite shape
            # (`func_80D17000.c` defines its 720-byte table AND the body at
            # +0x74).  It is a legitimate extra definition of THIS row's own
            # bytes, not the same function written at another base, so it is
            # recorded rather than refused.  See the spec deviation note in the
            # module header of tools/test_rowbase_naming_debt.py.
            off = rowbase_identity.vram_of(symbol) - base_vram
            if 0 < off < int(size):
                interior.append(symbol)
                continue
        raise SystemExit(self_address_error(uid, synthetic, symbol, expected,
                                            synthetic, why, action=action))

    # --- (b) structural invariants ----------------------------------------
    notes: list[str] = []
    shares: list[dict] = []
    if qid is not None:
        if owners is None:
            owners = landed_definitions(uid, source_dir=directory, root=root,
                                        exclude=(synthetic,))
        index = _row_index(units_of_family(family), root=root)
        for other in sorted(set(owners.get(expected, []))):
            if other == synthetic:
                continue
            other_qid = None
            entry = index.get(other)
            if entry is not None:
                other_region = _proven_region_at(family, entry[1], root=root)
                if other_region is not None:
                    other_qid = rowbase_identity.qualify(
                        "func_%08X" % ((entry[1] + other_region["delta"])
                                       & 0xFFFFFFFF),
                        family, other_region["region"])
            if other_qid == qid:
                raise SystemExit(corruption_error(
                    "STEM UNIQUENESS VIOLATED",
                    f"TUs {other}.c and {synthetic}.c in landing unit {uid!r} "
                    f"both resolve to the qualified identity {qid}. Stems are "
                    f"the synthetic row key, so two stems cannot share one "
                    f"identity unless a results row is duplicated (two rows at "
                    f"one foff) or a TU file was copied.",
                    action=action))
            shares.append({"symbol": expected, "func": other, "qid": other_qid,
                           "unit": entry[0] if entry else None,
                           "foff": entry[1] if entry else None,
                           "size": entry[2] if entry else None})
            if other_qid is None:
                notes.append(
                    f"SLOT SHARE (unresolved): {other}.c in {uid} also defines "
                    f"{expected}, but its own identity cannot be derived (no "
                    f"non-rerun row, or no proven region). Allowed — a bare true "
                    f"name is a RAM-slot label, and PWU is enforced at the gate "
                    f"by {PWU_ENFORCER}.")
            else:
                notes.append(
                    f"SLOT SHARE: {expected} is a RAM-slot label owned by two "
                    f"identities — {qid} ({synthetic}) and {other_qid} ({other}). "
                    f"Legal and recorded, not refused ({SPEC_DOC} §5.3). "
                    f"Build-artifact disambiguation (segment_obj_key) and PWU "
                    f"({PWU_ENFORCER}) cover the link.")
        # RIA: two DISTINCT rows resolving to one identity is corruption.
        ria = [g for g in rowbase_identity.ambiguities(units_of_family(family),
                                                       root=root or ROOT)
               if g["qid"] == qid]
        if ria:
            raise SystemExit(corruption_error(
                "REGION INJECTIVITY (RIA) VIOLATED",
                f"identity {qid} is owned by {len(ria[0]['funcs'])} distinct "
                f"rows: {', '.join(ria[0]['funcs'])}. Within one rowbase region "
                f"the delta is a single constant, so foff -> true name is "
                f"injective; two distinct rows in one region resolving to one "
                f"true name means equal foffs in the results JSON or an "
                f"overlapping/duplicated rowbase record.",
                action=action))
    for symbol in interior:
        notes.append(
            f"INTERIOR LABEL: {symbol} lies inside {synthetic}'s own "
            f"{size}-byte span at base {expected} — a second definition of this "
            f"row's OWN bytes (bank-table composite shape), not a wrong-base "
            f"self-address.")

    return {"unit": uid, "func": synthetic,
            "foff": None if foff is None else int(foff),
            "family": family, "synthetic": synthetic, "expected": expected,
            "region": None if region is None else region["region"],
            "qid": qid, "interior_labels": interior, "slot_shares": shares,
            "notes": notes}


# ---------------------------------------------------------------------------
# (b) Structural invariants — asserted; a violation is CORRUPTION
# ---------------------------------------------------------------------------


def assert_region_injectivity(units: Iterable[str] = DEFAULT_UNITS, *,
                              root: Path | None = None,
                              action: str = "check") -> None:
    """RIA (spec §1.4/§5.3(b)): no qualified identity has two distinct owners."""
    groups = rowbase_identity.ambiguities(list(units), root=root or ROOT)
    if not groups:
        return
    detail = "; ".join(f"{g['qid']} <- " + ", ".join(g["funcs"]) for g in groups)
    raise SystemExit(corruption_error(
        "REGION INJECTIVITY (RIA) VIOLATED",
        f"{len(groups)} qualified identit(y/ies) are owned by two or more "
        f"distinct rows: {detail}. Within one rowbase region the delta is a "
        f"single constant, so this cannot happen while the evidence is sound — "
        f"look for equal foffs in a results JSON or an overlapping/duplicated "
        f"rowbase record.", action=action))


def assert_stem_uniqueness(unit: str, *, root: Path | None = None,
                           action: str = "check") -> None:
    """Two TUs in one landing unit may not resolve to one qualified identity."""
    bad = {qid: stems for qid, stems in landed_identities(unit, root=root).items()
           if len(stems) > 1}
    if not bad:
        return
    detail = "; ".join(f"{qid} <- " + ", ".join(stems)
                       for qid, stems in sorted(bad.items()))
    raise SystemExit(corruption_error(
        "STEM UNIQUENESS VIOLATED",
        f"landing unit {unit_id(unit)!r} has {len(bad)} qualified identit(y/ies) "
        f"claimed by two or more TU stems: {detail}. Stems are the synthetic row "
        f"key, so this means a duplicated results row (two rows at one foff) or "
        f"a copied TU file.", action=action))


def assert_pwu(defined_by: Mapping[str, Sequence[str]], *, where: str,
               action: str = "link") -> None:
    """PWU (spec §2.1): no two objects in one link define one strong global.

    ENFORCEMENT LIVES AT THE GATE — ``overlay_local_gate.assert_unique_globals``
    walks the real ``nm -g`` output for every ``ld`` the tree emits.  This is the
    same invariant stated over an already-collected ``{symbol: [definer, ...]}``
    map, so the landing layer and the gate layer quote one message and cannot
    drift.  Held by construction: proven-region rows are mini-linked alone,
    everything else is synthetic-named and per-window unique.
    """
    dupes = {sym: list(objs) for sym, objs in defined_by.items()
             if len({str(o) for o in objs}) > 1}
    if not dupes:
        return
    detail = "; ".join(f"{sym} <- " + ", ".join(sorted({str(o) for o in objs}))
                       for sym, objs in sorted(dupes.items()))
    raise SystemExit(corruption_error(
        "PER-WINDOW UNIQUENESS (PWU) VIOLATED",
        f"{len(dupes)} symbol(s) are defined by two or more objects in {where}: "
        f"{detail}. PWU is held by construction — every proven-region row is "
        f"mini-linked alone and injected as raw bytes, and everything left in "
        f"the shared link is synthetic-named and per-window unique — so a "
        f"violation is an INFRASTRUCTURE defect (build-artifact key collision, "
        f"a row staged twice), and the remedy is segment_obj_key / mini-link "
        f"isolation, not a symbol rename. Enforced at {PWU_ENFORCER}.",
        action=action))


def assert_structural_invariants(units: Iterable[str] = DEFAULT_UNITS, *,
                                 root: Path | None = None) -> dict:
    """Run every landing-side structural assertion of spec §5.3(b)."""
    units = list(units)
    assert_region_injectivity(units, root=root)
    for unit in units:
        assert_stem_uniqueness(unit, root=root)
    return {"units": units, "region_injectivity": "ok", "stem_uniqueness": "ok",
            "pwu": f"enforced at {PWU_ENFORCER}"}


# ---------------------------------------------------------------------------
# Promotion pre-flight (spec §4.1 / §5.2 B7)
# ---------------------------------------------------------------------------


def promotion_identity_preflight(family: str, region: dict, *,
                                 root: Path | None = None) -> dict:
    """What promoting ``region`` solved->proven does to the identity space.

    Replaces ``promotion_collisions``.  Promotion is a BATCH mint: the instant
    the region turns proven every already-landed row inside it acquires a true
    name.  Under RIA those names cannot collide WITHIN the region, and a bare
    name already defined by a TU in a DIFFERENT region is a legal slot share —
    the false blocker that stopped ``sweep_0D312D0``.  So this returns a census
    and refuses only corruption.

    ``region`` is a ``rowbase._records`` entry (``start``/``end``/``delta``/
    ``rec``); the region is still ``solved`` at call time, which is why the
    identity is minted from the passed record and not re-derived through
    ``region_for(proven_only=True)``.
    """
    fam = family_of(family)
    region_id = region["rec"].get("region")
    delta = int(region["delta"])
    units = units_of_family(fam)

    plan: list[dict] = []
    for unit in units:
        directory = source_dir_for(unit, root=root)
        for row in _rows(unit, root=root):
            if row.get("rerun") or row.get("result") != "MATCH":
                continue
            func, foff = row.get("func_vram"), row.get("foff")
            if not func or foff is None:
                continue
            foff = int(foff)
            if not (region["start"] <= foff < region["end"]):
                continue
            if not (directory / f"{func}.c").is_file():
                continue
            true_name = "func_%08X" % ((foff + delta) & 0xFFFFFFFF)
            plan.append({"unit": unit, "func": str(func), "foff": foff,
                         "size": row.get("size"), "true_name": true_name,
                         "qid": rowbase_identity.qualify(true_name, fam,
                                                         region_id)})

    by_qid: dict[str, list[dict]] = {}
    for item in plan:
        by_qid.setdefault(item["qid"], []).append(item)
    ambiguous = [{"qid": qid, "funcs": sorted({i["func"] for i in items}),
                  "owners": items}
                 for qid, items in sorted(by_qid.items())
                 if len({i["func"] for i in items}) > 1]
    if ambiguous:
        detail = "; ".join(f"{g['qid']} <- " + ", ".join(g["funcs"])
                           for g in ambiguous)
        raise SystemExit(corruption_error(
            "REGION INJECTIVITY (RIA) VIOLATED",
            f"promoting region {region_id} would give {len(ambiguous)} "
            f"identit(y/ies) two or more distinct owners: {detail}. Inside one "
            f"region the delta is a single constant, so two distinct rows can "
            f"only land on one true name if their foffs are equal — a duplicated "
            f"results row or an overlapping rowbase record.",
            action="promotion"))

    # Legal cross-region slot shares: a bare true name minted here that a TU
    # OUTSIDE this region already defines.  Recorded, never refused.
    in_region = {i["func"] for i in plan}
    outside: dict[str, list[tuple[str, str]]] = {}
    for unit in units:
        for symbol, stems in landed_definitions(unit, root=root,
                                                exclude=in_region).items():
            for stem in stems:
                outside.setdefault(symbol, []).append((unit, stem))
    index = _row_index(units, root=root)
    shares: list[dict] = []
    for item in sorted(plan, key=lambda i: i["true_name"]):
        holders = outside.get(item["true_name"], [])
        if not holders:
            continue
        owners = []
        for unit, stem in sorted(holders):
            entry = index.get(stem)
            other_qid = None
            if entry is not None:
                other_region = _proven_region_at(fam, entry[1], root=root)
                if other_region is not None:
                    other_qid = rowbase_identity.qualify(
                        "func_%08X" % ((entry[1] + other_region["delta"])
                                       & 0xFFFFFFFF),
                        fam, other_region["region"])
            owners.append({"unit": unit, "func": stem, "qid": other_qid,
                           "foff": entry[1] if entry else None,
                           "size": entry[2] if entry else None})
        shares.append({"true_name": item["true_name"], "qid": item["qid"],
                       "func": item["func"], "unit": item["unit"],
                       "also_defined_by": owners})

    return {"family": fam, "region": region_id, "units": units,
            "rows": len(plan), "identities": len(by_qid),
            "identity_ambiguities": ambiguous, "slot_shares": shares,
            "status": "clean"}


# ---------------------------------------------------------------------------
# Debt enumeration (the receipt) — spec §5.4
# ---------------------------------------------------------------------------


def synthetic_debt_rows(unit: str, *, root: Path | None = None) -> list[dict]:
    """Landed rows in a PROVEN region whose TU still defines only the synthetic
    key — decision-B debt, for ONE landing unit.

    Authoritative because it reads the real TU content, not the (possibly stale)
    ``row["true_name"]`` JSON field.
    """
    uid = unit_id(unit)
    family = family_of(uid)
    directory = source_dir_for(uid, root=root)
    if not directory.is_dir():
        return []
    out: list[dict] = []
    for row in _rows(uid, root=root):
        if row.get("rerun") or row.get("result") != "MATCH":
            continue
        func, foff = row.get("func_vram"), row.get("foff")
        if not func or foff is None:
            continue
        foff = int(foff)
        region = _proven_region_at(family, foff, root=root)
        if region is None:
            continue
        path = directory / f"{func}.c"
        if not path.is_file():
            continue
        true_name = "func_%08X" % ((foff + region["delta"]) & 0xFFFFFFFF)
        defs = file_definitions(path.read_text(errors="replace"))
        if true_name in defs:
            continue  # compliant
        if func not in defs:
            continue  # defines neither name (asm-only shell); not rename debt
        out.append({"unit": uid, "family": family, "func": func, "foff": foff,
                    "true_name": true_name, "region": region["region"],
                    "qid": rowbase_identity.qualify(true_name, family,
                                                    region["region"]),
                    "c_path": f"overlays/{uid}/first_pass_matched/{func}.c"})
    return out


def slot_shares(units: Iterable[str] = DEFAULT_UNITS, *,
                root: Path | None = None) -> list[dict]:
    """Bare true names owned by two or more distinct QUALIFIED identities.

    This is ``collisions()`` renamed and inverted (spec §9.4): a cross-region
    slot share is a CENSUS fact, not a defect.  Leaving it named "collision" is
    what kept re-manufacturing the false blocker that stopped the
    ``sweep_0D312D0`` promote.  24 groups covering 49 landed rows today.
    """
    return rowbase_identity.slot_shares([unit_id(u) for u in units],
                                        root=root or ROOT)


def identity_ambiguities(units: Iterable[str] = DEFAULT_UNITS, *,
                         root: Path | None = None) -> list[dict]:
    """Qualified identities owned by two or more distinct functions.

    MUST be empty.  Non-zero is a hard failure of the migration, and corruption
    of the evidence rather than an owner decision (spec §5.4 / §6.4 item 3).
    """
    return rowbase_identity.ambiguities([unit_id(u) for u in units],
                                        root=root or ROOT)


def cross_unit_duplicates(units: Iterable[str] = DEFAULT_UNITS, *,
                          root: Path | None = None) -> list[str]:
    """Qualified identities present in two or more landing units.

    Informational, and correct: 72 today, entirely ``dungeon`` ∩
    ``dungeon_engine`` same-foff rows — ONE function whose TU exists in two
    landing units, resolved at build time by ``only_if_missing: true``.
    """
    table = rowbase_identity.identity_table([unit_id(u) for u in units],
                                            root=root or ROOT)
    return [qid for qid, refs in table.items() if len({r.unit for r in refs}) > 1]


def report(units: Iterable[str] = DEFAULT_UNITS, *,
           root: Path | None = None) -> dict:
    """The qualified-identity receipt over the five landing units (spec §5.4)."""
    units = [unit_id(u) for u in units]
    table = rowbase_identity.identity_table(units, root=root or ROOT)
    per_unit: dict[str, dict] = {}
    debt_total = 0
    for unit in units:
        debt = synthetic_debt_rows(unit, root=root)
        debt_total += len(debt)
        unit_refs = {qid: [r for r in refs if r.unit == unit]
                     for qid, refs in table.items()}
        unit_refs = {qid: refs for qid, refs in unit_refs.items() if refs}
        per_unit[unit] = {
            "family": family_of(unit),
            "landed_rows": sum(len(refs) for refs in unit_refs.values()),
            "qualified_ids": len(unit_refs),
            "debt_count": len(debt),
            "slot_shares": len(slot_shares([unit], root=root)),
            "identity_ambiguities": len(identity_ambiguities([unit], root=root)),
            "debt_funcs": sorted(r["func"] for r in debt),
        }
    shares = slot_shares(units, root=root)
    ambiguous = identity_ambiguities(units, root=root)
    cross = cross_unit_duplicates(units, root=root)
    return {
        "schema": SCHEMA,
        "spec": SPEC_DOC,
        "generated_at": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime()),
        "units": units,
        "per_unit": per_unit,
        "proven_region_rows": sum(len(refs) for refs in table.values()),
        "qualified_ids": len(table),
        "debt_count": debt_total,
        "total_debt": debt_total,          # v1 key, kept so old readers still work
        "slot_shares": len(shares),
        "slot_share_groups": [
            {"family": g["family"], "true_name": g["true_name"], "qids": g["qids"],
             "owners": [{"unit": o["unit"], "func": o["func"], "qid": o["qid"],
                         "region": o["region"], "foff": o["foff"],
                         "size": o["size"]} for o in g["owners"]]}
            for g in shares],
        "identity_ambiguities": len(ambiguous),
        "identity_ambiguity_groups": ambiguous,
        "cross_unit_duplicates": len(cross),
        "cross_unit_duplicate_ids": cross,
    }


# ---------------------------------------------------------------------------
# CLI
# ---------------------------------------------------------------------------


def _cmd_report(a) -> int:
    units = a.unit or list(DEFAULT_UNITS)
    data = report(units)
    for unit in data["units"]:
        block = data["per_unit"][unit]
        print(f"{unit}: {block['debt_count']} synthetic-name TUs in proven "
              f"regions, {block['landed_rows']} proven-region rows -> "
              f"{block['qualified_ids']} identities, "
              f"{block['slot_shares']} slot shares, "
              f"{block['identity_ambiguities']} identity ambiguities")
    for group in data["slot_share_groups"]:
        print(f"    slot {group['true_name']} ({group['family']}): "
              + ", ".join(group["qids"]))
    print(f"TOTAL: {data['debt_count']} debt rows, "
          f"{data['slot_shares']} slot shares (informational), "
          f"{data['identity_ambiguities']} identity ambiguities (MUST be 0), "
          f"{data['cross_unit_duplicates']} cross-unit duplicates")
    if a.json:
        out = Path(a.json)
        out = out if out.is_absolute() else ROOT / out
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(json.dumps(data, indent=1, sort_keys=True) + "\n")
        print(f"wrote {out}")
    return 0


def _cmd_owners(a) -> int:
    units = [a.unit] if a.unit else (
        units_of_family(family_of(a.family)) if a.family else list(DEFAULT_UNITS))
    units = [unit_id(u) for u in units]
    if a.symbol:
        name = f"func_{rowbase_identity.vram_of(a.symbol):08X}"
        refs = [r for r in rowbase_identity.row_refs(units, landed_only=False,
                                                     match_only=False)
                if r.true_name == name]
        print(json.dumps({
            "symbol": name,
            "units": units,
            "identities": sorted({r.qid for r in refs}),
            "owners": [r.as_dict() for r in
                       sorted(refs, key=lambda r: (r.qid, r.unit, r.foff))],
            "defining_tus": {u: landed_definitions(
                u, include_static=a.include_static).get(name, []) for u in units},
        }, indent=1))
    else:
        out = {}
        for unit in units:
            owners = landed_definitions(unit, include_static=a.include_static)
            out[unit] = {"symbols": len(owners),
                         "duplicate_definitions": {k: v for k, v in owners.items()
                                                   if len(v) > 1}}
        print(json.dumps(out, indent=1, sort_keys=True))
    return 0


def main(argv: list[str] | None = None) -> int:
    import argparse
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    p = sub.add_parser("report", help="decision-B naming debt + qualified-identity "
                                      "census over the five landing units")
    p.add_argument("--unit", action="append",
                   help="landing unit (default: all five)")
    p.add_argument("--json", help="also write the receipt JSON here")
    p.set_defaults(fn=_cmd_report)
    q = sub.add_parser("owners", help="every qualified owner of a bare true name")
    q.add_argument("--symbol")
    q.add_argument("--family", help="evidence family (expands to its landing units)")
    q.add_argument("--unit", help="one landing unit")
    q.add_argument("--include-static", action="store_true")
    q.set_defaults(fn=_cmd_owners)
    a = ap.parse_args(argv)
    return a.fn(a)


if __name__ == "__main__":
    raise SystemExit(main())
