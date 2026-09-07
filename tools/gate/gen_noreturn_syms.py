#!/usr/bin/env python3
"""Auto-derive the set of ZERO-ARG noreturn callee symbols from the C sources.

LEAD 18-GENERAL (ladder step 2 — evidence file). The "this callee never
returns" fact is declared in the C via ``__attribute__((noreturn))`` (or a
``NORETURN`` macro token) but gcc erases it before maspsx sees the assembly.
This scanner recovers that side-channel: it walks the decomp C sources, finds
every declaration/definition carrying the noreturn marker, extracts the declared
symbol name, and writes the sorted/deduped set to the container family's
evidence file. maspsx's tail-call pass then fires ``jal``->``j`` on calls to
those symbols without needing a hardcoded per-function name list.

PER-CONTAINER FILES (Phase B activation, build/tmp_infra/phaseb_prescan.md
Task 3): town_scene and dungeon_engine both load at vram 0x80080000, so the
same func_800XXXXX name is DIFFERENT code per container — evidence derived
from one container's C must never fire on another container's compile. Each
family therefore scans ONLY its own C and writes its own file:

  main    -> config/noreturn_syms.txt          (SLUS EXE + MAIN.BIN, the
             co-resident non-aliasing pair — the maspsx default)
  town    -> config/noreturn_syms.town.txt
  dungeon -> config/noreturn_syms.dungeon.txt
  ovmovie -> config/noreturn_syms.ovmovie.txt

Selection at compile time is tools/overlay_evidence.py's job (the
$MASPSX_NORETURN_FILE env var).

TRACKED SOURCES ONLY (2026-09-01, the durable class-fix; see
``_assert_tracked_source_globs``). This scanner USED to also sweep the untracked
wave scratch dirs ``work/overlay_wave/candidates{,_town,_dungeon,_ovmovie}/``.
That glob bought the build NOTHING — a candidate is compiled in isolation with
its own declarations self-served (tools/overlay_evidence.py
``evidence_env_with_candidate``; the per-segment merge in
``overlay_local_gate.compile_c_segments``), so it never needed tracked-census
membership — while letting ANY lane's speculative, often never-matching draft
rewrite a GLOBAL build input at the next landing's census regen. It caused three
measured breaks of landed byte-exact rows: func_80024948 (dungeon_deep_t8_197a),
func_80024094 (fid_818ED25C) and func_8002614C (fid_819ACDA0). The scan globs are
now restricted to TRACKED roots and a ``work/`` glob is a hard error.

CORPUS-PROVEN FIRING RULE (see build/tmp_infra/tailcall_discriminator_report.md):
retail/ASPSX rewrites ``jal SYM`` -> ``j SYM`` iff SYM is a noreturn callee that
takes ZERO arguments (``(void)`` / ``()``). Across the whole MAIN.BIN corpus this
is 66/66 sites with zero counterexamples: every void noreturn callee's 29 sites
are ``j``, and the single ARG-taking noreturn callee (``func_8007BEF0(s32)``)
keeps ``jal`` at all 37 of its sites, across every config. So this scanner emits
a symbol ONLY when its declared parameter list is empty — the emitted set is the
*void-noreturn* set, and arg-taking noreturn callees are intentionally excluded.

FALSE MEMBERS (`config/noreturn_false_members.jsonl`, 2026-08-08).
The census is keyed on the BARE name and is BUILD-WIRED family-wide: maspsx
LEAD 18 rewrites every ``jal SYM`` to ``j SYM`` for any member. But a symbol
retail reaches BOTH ways — ``j`` from a tail call, ``jal`` from a caller that
uses the result — cannot be expressed by a name-keyed set, and the wrong half is
silent (`tools/noreturn_census_guard.py` REPORT 1 names them: 26 such symbols sit
under 26 banked TUs). Scanning alone cannot fix this, because the declaring TU
generally NEEDS its own ``noreturn`` attribute: dropping it regresses that TU
(measured — func_81839358 goes 0 -> 42 words off), while census membership
regresses every OTHER caller in the family.

So membership is subtracted, not the declaration: a family+func record in the
exclusion file drops the symbol from the generated census while every TU keeps
its attribute. GCC still emits the tail ``j`` from the attribute inside the
declaring TU; only the family-wide maspsx rewrite stops. `proof` is REQUIRED on
every record — an unproven exclusion silently disables a real tail-call
conversion, which is the A2/B5 defect this module fails closed on elsewhere.

Idempotent and fast. Run from anywhere; paths resolve against the repo root.
"""

from __future__ import annotations

import argparse
import json
import re
import sys
from pathlib import Path, PurePosixPath

ROOT = Path(__file__).resolve().parents[1]

# Per-container-family scan globs and output files. A family scans ONLY its
# own C sources (see the module docstring for why sharing is unsound), and ONLY
# TRACKED ones (see TRACKED_SOURCE_ROOTS / _assert_tracked_source_globs).
CONTAINERS: dict[str, dict[str, object]] = {
    "main": {
        "out": "config/noreturn_syms.txt",
        "globs": [
            "src/**/*.c",
            "overlays/main/first_pass_matched/*.c",
            # Declaration-only, never-compiled, never-#included evidence source
            # (2026-09-06). Seven MAIN.BIN callees are genuinely zero-arg
            # noreturn but CANNOT carry the attribute in the caller TU that
            # needs it: with the attribute visible, gcc deletes the trailing
            # instruction that fills the converted tail-j's delay slot and the
            # row stops matching for a different reason. Their only prior source
            # was the untracked candidates glob 337355ce (correctly) cut, which
            # silently un-matched all seven rows -- see the file's own header and
            # work/bridge_remediation_20260905/F_noreturn_census_fix/REPORT.txt.
            "config/noreturn_evidence.main.c",
        ],
    },
    "town": {
        "out": "config/noreturn_syms.town.txt",
        "globs": [
            "overlays/town/first_pass_matched/*.c",
        ],
    },
    "dungeon": {
        "out": "config/noreturn_syms.dungeon.txt",
        "globs": [
            "overlays/dungeon/first_pass_matched/*.c",
            "overlays/dungeon_engine/first_pass_matched/*.c",
        ],
    },
    "ovmovie": {
        "out": "config/noreturn_syms.ovmovie.txt",
        "globs": [
            "overlays/ovmovie/first_pass_matched/*.c",
        ],
    },
}

# Repo-relative first path components a census may derive C evidence from. Every
# one is a TRACKED (git-checked-in) tree, so a census entry always traces to a
# reviewable commit. ``work/`` is deliberately absent: it is per-lane scratch,
# gitignored, and rewritten mid-flight by live waves.
TRACKED_SOURCE_ROOTS = frozenset({"src", "overlays", "include", "asm", "config"})

# The scratch roots this refusal exists for, named so the error is actionable.
_UNTRACKED_ROOT_HINT = {
    "work": ("wave scratch (work/overlay_wave/candidates*/ etc.) -- a candidate "
             "self-serves its own decls at compile time via "
             "tools/overlay_evidence.py evidence_env_with_candidate, so it never "
             "needs tracked-census membership; sweeping it lets an unlanded, "
             "often never-matching draft rewrite a GLOBAL build input"),
    "build": "generated build output",
    "toolchain": "vendored toolchain",
}


def _assert_tracked_source_globs(label: str, globs: list[str]) -> None:
    """Fail closed on a C-source scan glob rooted outside a TRACKED tree.

    THE DEFECT THIS EXISTS FOR (three measured incidents, 2026-08-31/09-01).
    The census generators used to scan ``work/overlay_wave/candidates*/``. A
    census is a GLOBAL, build-wired maspsx input: LEAD 18 rewrites every
    ``jal SYM`` -> ``j SYM`` family-wide for any member, and gen_sibcall_syms
    rule 3 hands a symbol between passes on membership. So one lane's
    speculative ``__attribute__((noreturn))`` in an UNTRACKED NOMATCH draft
    silently rewrote a global build input at the next landing's census regen and
    broke landed byte-exact rows -- func_80024948 (window dungeon_deep_t8_197a),
    func_80024094 (fid_818ED25C, silent for five days) and func_8002614C
    (fid_819ACDA0). Untracked evidence also makes the census
    non-reproducible: ``--check`` drifts depending on what a live wave happens
    to have written to disk that minute.

    This is a REFUSAL, not a filter: silently ignoring the glob would let a
    caller believe an evidence base exists where none does, which is the
    A2/B5 empty-census defect ``_fail_closed_reason`` guards the other end of.
    """
    for glob in globs:
        root = PurePosixPath(glob).parts[0] if glob else ""
        if root in TRACKED_SOURCE_ROOTS:
            continue
        hint = _UNTRACKED_ROOT_HINT.get(root, "not a tracked source tree")
        raise SystemExit(
            f"{label}: C-source scan glob {glob!r} is rooted at {root!r}/ -- "
            f"{hint}.\n"
            f"A census is a GLOBAL build-wired maspsx input; deriving it from "
            f"untracked scratch is how func_80024948 / func_80024094 / "
            f"func_8002614C each silently broke a LANDED byte-exact row.\n"
            f"Scan globs must be rooted at one of: "
            f"{', '.join(sorted(TRACKED_SOURCE_ROOTS))}.")

HEADER = (
    "# AUTO-GENERATED by tools/gen_noreturn_syms.py "
    "-- do not hand-edit; declare noreturn in the C instead\n"
)

# C keywords / type tokens that must never be mistaken for a function name.
_TYPE_TOKENS = {
    "void", "int", "char", "short", "long", "unsigned", "signed", "float",
    "double", "const", "volatile", "static", "extern", "struct", "union",
    "enum", "register", "inline", "typedef", "return", "sizeof", "if", "while",
    "for", "switch", "do", "else", "goto", "u8", "u16", "u32", "u64", "s8",
    "s16", "s32", "s64", "f32", "f64", "uint8_t", "uint16_t", "uint32_t",
    "int8_t", "int16_t", "int32_t", "bool", "size_t", "vs32", "vu32",
}

_ATTR_RE = re.compile(r"__attribute__\s*\(\(.*?\)\)", re.DOTALL)
_NORETURN_ATTR_RE = re.compile(r"__attribute__\s*\(\(.*?\bnoreturn\b", re.DOTALL)
_NORETURN_MACRO_RE = re.compile(r"\bNORETURN\b")
_NAME_BEFORE_PAREN_RE = re.compile(r"([A-Za-z_]\w*)\s*\(")


def _strip_comments(text: str) -> str:
    text = re.sub(r"/\*.*?\*/", " ", text, flags=re.DOTALL)
    text = re.sub(r"//[^\n]*", " ", text)
    return text


def _carries_noreturn(stmt: str) -> bool:
    return bool(_NORETURN_ATTR_RE.search(stmt) or _NORETURN_MACRO_RE.search(stmt))


def _balanced_paren_body(s: str, open_idx: int) -> str | None:
    """Return the text inside the parentheses whose ``(`` is at ``open_idx``.

    Handles nesting (e.g. a function-pointer parameter ``void (*fn)(void)``) so
    the whole parameter list is captured, not just up to the first ``)``. Returns
    None if the parenthesis is unbalanced.
    """
    depth = 0
    for idx in range(open_idx, len(s)):
        ch = s[idx]
        if ch == "(":
            depth += 1
        elif ch == ")":
            depth -= 1
            if depth == 0:
                return s[open_idx + 1:idx]
    return None


def _extract_name(stmt: str) -> str | None:
    # Drop attribute clauses and the bare NORETURN macro so the only remaining
    # parenthesised group is the parameter list; the function name is the
    # identifier immediately preceding it.
    s = _ATTR_RE.sub(" ", stmt)
    s = _NORETURN_MACRO_RE.sub(" ", s)
    m = _NAME_BEFORE_PAREN_RE.search(s)
    if not m:
        return None
    name = m.group(1)
    if name in _TYPE_TOKENS:
        return None
    # CORPUS-PROVEN (build/tmp_infra/tailcall_discriminator_report.md, 66/66):
    # only ZERO-ARG noreturn callees are retail-rewritten jal->j; the one
    # arg-taking noreturn callee keeps jal at every site. Emit the symbol ONLY
    # when its parameter list is empty -- `()` or `(void)`. m.end() - 1 is the
    # index of the `(` that opens the parameter list.
    params = _balanced_paren_body(s, m.end() - 1)
    if params is None:
        return None
    if params.strip() not in ("", "void"):
        return None
    return name


def scan_text(text: str) -> set[str]:
    names: set[str] = set()
    text = _strip_comments(text)
    # Join backslash-continued lines FIRST so a multi-line directive is dropped
    # whole: with the strip below alone, a two-line `#define X \` left its
    # continuation in the text, which merged into the next `;`-statement and
    # silently deleted the noreturn decl that followed it (func_818BC9CC,
    # 2026-09-02 -- the in-row `j` came back as `jal`+`nop` with no diagnostic).
    text = re.sub(r"\\[ \t]*\r?\n", " ", text)
    # Drop preprocessor lines (e.g. `#define NORETURN __attribute__((noreturn))`).
    text = re.sub(r"^\s*#.*$", "", text, flags=re.MULTILINE)
    # Treat braces as statement boundaries so a `... noreturn ... { body }`
    # definition signature is isolated from its body.
    text = text.replace("{", ";").replace("}", ";")
    for stmt in text.split(";"):
        if not _carries_noreturn(stmt):
            continue
        name = _extract_name(stmt)
        if name:
            names.add(name)
    return names


def collect(globs: list[str], label: str = "scan globs") -> set[str]:
    # Fail closed BEFORE any disk read: an untracked-root glob is a refusal, so
    # no caller can accidentally derive census evidence from scratch. See
    # _assert_tracked_source_globs.
    _assert_tracked_source_globs(label, globs)
    names: set[str] = set()
    for glob in globs:
        for path in sorted(ROOT.glob(glob)):
            try:
                text = path.read_text(errors="replace")
            except OSError:
                continue
            names |= scan_text(text)
    return names


FALSE_MEMBERS_PATH = "config/noreturn_false_members.jsonl"
FALSE_MEMBER_SCHEMA = "azure-clean.noreturn-false-member.v1"


def false_members(fam: str, path: Path | None = None) -> set[str]:
    """Symbols this family must NOT emit even though a TU declares them noreturn.

    See the module docstring. Every record needs `schema`, `family`, `func` and a
    non-empty `proof`; anything else is a hard SystemExit rather than a silently
    dropped exclusion, because both failure directions change generated bytes."""
    src = ROOT / FALSE_MEMBERS_PATH if path is None else path
    if not src.exists():
        return set()
    out: set[str] = set()
    for lineno, line in enumerate(src.read_text().splitlines(), 1):
        line = line.strip()
        if not line or line.startswith("#"):
            continue
        try:
            rec = json.loads(line)
        except ValueError as exc:
            raise SystemExit(f"{FALSE_MEMBERS_PATH}:{lineno}: not JSON ({exc})")
        if rec.get("schema") != FALSE_MEMBER_SCHEMA:
            raise SystemExit(f"{FALSE_MEMBERS_PATH}:{lineno}: schema must be "
                             f"{FALSE_MEMBER_SCHEMA!r}, got {rec.get('schema')!r}")
        for field in ("family", "func", "proof"):
            if not str(rec.get(field) or "").strip():
                raise SystemExit(
                    f"{FALSE_MEMBERS_PATH}:{lineno}: {field!r} is required and "
                    f"non-empty. An unproven exclusion silently disables a real "
                    f"tail-call jal->j conversion for the whole family.")
        if rec.get("family") not in CONTAINERS:
            raise SystemExit(f"{FALSE_MEMBERS_PATH}:{lineno}: unknown family "
                             f"{rec.get('family')!r}")
        if rec["family"] == fam:
            out.add(rec["func"])
    return out


def count_sources(globs: list[str]) -> int:
    """Number of C source files the family's globs actually match.

    ZERO means there is no evidence base at all -- the historical silent-defect
    (config/noreturn_syms.{town,dungeon,ovmovie}.txt shipped header-only because
    the scan dirs were empty at Phase-B activation time). Writing a header-only
    census in that state silently disables every tail-call jal->j conversion for
    the container (residual_routing_20260712.md A2/B5). We fail closed on it."""
    return sum(1 for glob in globs for _ in ROOT.glob(glob))


def render(names: list[str]) -> str:
    """The exact bytes an evidence file holds for ``names`` (sorted)."""
    return HEADER + "".join(f"{n}\n" for n in names)


def symcount(text: str | None) -> int:
    """Non-comment, non-blank symbol lines in an evidence-file body."""
    if not text:
        return 0
    n = 0
    for line in text.splitlines():
        s = line.strip()
        if s and not s.startswith("#"):
            n += 1
    return n


def plan_family(fam: str) -> dict:
    """Deterministically derive what this family's evidence file SHOULD contain
    plus the fail-closed diagnostics, without touching disk."""
    cfg = CONTAINERS[fam]
    globs = list(cfg["globs"])
    out = ROOT / str(cfg["out"])
    scanned = collect(globs, label=f"[{fam}]")
    # Subtract proven false members AFTER scanning, so the fail-closed
    # diagnostics below still see a real evidence base (n_sources) and an
    # exclusion can never be mistaken for an empty scan.
    excluded = sorted(false_members(fam) & scanned)
    names = sorted(scanned - set(excluded))
    tracked = out.read_text() if out.exists() else None
    return {
        "fam": fam,
        "out": out,
        "names": names,
        "excluded": excluded,
        "new_text": render(names),
        "n_sources": count_sources(globs),
        "tracked_text": tracked,
        "tracked_syms": symcount(tracked),
    }


def _fail_closed_reason(plan: dict, allow_empty_scan: bool, allow_empty: bool) -> str | None:
    """Return an actionable message if writing this plan would be a silent
    evidence-regression, else None. Legitimately-empty families (e.g. ovmovie,
    which declares zero zero-arg noreturn callees over 48 scanned sources) pass:
    they have a real evidence base and no populated file to clobber."""
    fam, n_src, nsyms, tracked = (
        plan["fam"], plan["n_sources"], len(plan["names"]), plan["tracked_syms"])
    if n_src == 0 and not allow_empty_scan:
        return (f"[{fam}] 0 source files match its scan globs -- no evidence base. "
                f"Refusing to write a header-only census that would silently disable "
                f"tail-call jal->j conversion. Populate the scan dirs, or pass "
                f"--allow-empty-scan to bootstrap a new container.")
    if nsyms == 0 and tracked > 0 and not allow_empty:
        return (f"[{fam}] regeneration yields 0 symbols but the tracked file holds "
                f"{tracked} -- this would silently clobber a populated census. "
                f"Investigate the source change, or pass --allow-empty to override.")
    return None


def main() -> int:
    ap = argparse.ArgumentParser(description=__doc__)
    ap.add_argument(
        "--container",
        choices=["all", *CONTAINERS],
        default="all",
        help="which container family's evidence file(s) to regenerate",
    )
    ap.add_argument(
        "--check", action="store_true",
        help="verify each tracked file already equals a fresh regeneration; "
             "write NOTHING, print a unified diff on drift, exit 1 if any family "
             "drifts or would fail closed (deterministic-regeneration gate)")
    ap.add_argument(
        "--allow-empty-scan", action="store_true",
        help="permit writing when a family's scan globs match 0 source files")
    ap.add_argument(
        "--allow-empty", action="store_true",
        help="permit overwriting a populated census with an empty regeneration")
    args = ap.parse_args()

    families = list(CONTAINERS) if args.container == "all" else [args.container]
    failures: list[str] = []
    for fam in families:
        plan = plan_family(fam)
        out = plan["out"]
        reason = _fail_closed_reason(plan, args.allow_empty_scan, args.allow_empty)
        if reason:
            failures.append(reason)
            print(f"FAIL {reason}", file=sys.stderr)
            continue
        if args.check:
            if plan["tracked_text"] != plan["new_text"]:
                failures.append(f"[{fam}] {out.relative_to(ROOT)} drifted from sources")
                print(f"DRIFT {out.relative_to(ROOT)}: tracked != regeneration",
                      file=sys.stderr)
                _print_diff(plan["tracked_text"] or "", plan["new_text"],
                            str(out.relative_to(ROOT)))
            else:
                note = (f"; {len(plan['excluded'])} false member(s) excluded"
                        if plan["excluded"] else "")
                print(f"ok {out.relative_to(ROOT)}: {len(plan['names'])} "
                      f"symbol(s) [{fam}]{note}")
            continue
        out.parent.mkdir(parents=True, exist_ok=True)
        out.write_text(plan["new_text"])
        note = (f"; {len(plan['excluded'])} proven false member(s) excluded: "
                f"{', '.join(plan['excluded'])}") if plan["excluded"] else ""
        print(f"wrote {out.relative_to(ROOT)}: {len(plan['names'])} "
              f"noreturn symbol(s) [{fam}]{note}")

    if failures:
        return 1
    return 0


def _print_diff(old: str, new: str, label: str) -> None:
    import difflib
    diff = difflib.unified_diff(
        old.splitlines(keepends=True), new.splitlines(keepends=True),
        fromfile=f"tracked/{label}", tofile=f"regenerated/{label}")
    sys.stderr.writelines(diff)


if __name__ == "__main__":
    raise SystemExit(main())
