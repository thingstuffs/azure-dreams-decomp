#!/usr/bin/env python3
"""Fidelity ratchet shim for the landing paths (intake §B.3 / §G-12).

The audit itself lives in tools/census/gaps/decomp_audit.py (it needs `portlib`
and the container bytes); tools/integrate.py and tools/overlay_land_function.py
live in tools/.  This module is the one import they make, so neither landing
tool has to know where the census tree is or how to put it on sys.path.

WHAT IT ENFORCES
----------------
A ratchet, not a wall.  config/decomp_audit_baseline.json grandfathers every
fidelity site that exists today; a landing is refused only when the CANDIDATE C
for the row being landed ADDS a blocking-class site (LABEL_AS_CALL or
PASSTHRU_NO_ARGS) that the baseline does not already carry for that row.  A site
that disappears never blocks -- that is the burn-down.  Byte-derived debt classes
(PASSTHRU, INDIRECT_PASSTHRU, JT_KEEP_ORDER) never block at all; see the
decomp_audit.py docstring for why.

TWO LABEL_AS_CALL shapes are counted but not refused, each with its own census
label, each still written into the baseline, each printed by the landing:

  * `noreturn-tail` -- a MID-ROW `j` target the candidate C declares zero-arg
    `__attribute__((noreturn))`: a REGISTERED tail jump, the same declaration
    tools/gen_noreturn_syms.py reads to write config/noreturn_syms.<family>.txt.
    Some rows only reach byte-exact with that spelling.
  * `shape-d-pin` -- a target an authenticated per-site SHAPE-D sibcall pin
    (include/common.h ASM_SHAPE_D_SIBCALL_PIN, maspsx LEAD 29/35) names at
    exactly this site address, with the callee in the family's binary-derived
    sibcall census.  Those rows match BECAUSE maspsx converted that `jal` to
    retail's `j`; the noreturn escape would mean declaring a returning callee
    noreturn, which is both a fiction and circular (the declaration arms census
    rule 3 against the sibcall membership the pass itself gates on).

An epilogue label qualifies for neither, and the alternative to both was the
blanket override below.  decomp_audit.DECLARED_TAIL_JUMP and
decomp_audit.SHAPE_D_PINNED_TAIL_JUMP carry the full arguments.

ROW KEYING (2026-08-24)
-----------------------
The baseline keys a row by "<container>/<func_vram>" -- the extractor's synthetic
name, which is unique inside a container and does NOT move when an identity sweep
renames the row to its true name.  A baseline written under the old
"<container>/<true_name or func_vram>" scheme carries no `key_scheme` field; this
shim then DISABLES itself (loudly) instead of refusing every renamed row, because
a ratchet that has lost its keys is a wall.  Fix it with --write-baseline.

COST
----
Only the row being landed is audited, never the ~5,000-row tree: the container
bytes are memory-mapped and loaded lazily, so one landing costs 0.1-0.7 s
(docs/fidelity_ratchet.md).  Pass one shared `Session` through a whole wave and
the baseline and the container maps are paid for once.

OVERRIDE
--------
`--allow-fidelity-regression` on either landing tool, or
AZ_ALLOW_FIDELITY_REGRESSION=1 in the environment (the env var exists because
both landing entry points are also called as LIBRARY functions by wave drivers
that do not forward CLI flags).  An intended regression should be followed by
  tools/census/gaps/decomp_audit.py --write-baseline
so the next landing of that row starts from the new truth.

THE OVERRIDE IS LOUD (2026-09-01).  It used to SHORT-CIRCUIT: with the flag or
the env var set, the audit was never run at all, so nobody -- not the operator,
not the landing record, not the next reader -- learned which sites had just
entered the tree.  The 2026-09-01 baseline regeneration found the bill:
**44 would-refuse sites had entered silently through this blanket override**
(work/wave_20260901_burndown/baseline_report.md).

So the audit now ALWAYS runs.  What the override PERMITS is unchanged -- every
landing it allowed before, it still allows -- but each waived site is printed to
stderr, appended to the durable ledger below, and returned on the landing record,
with the required `--write-baseline` adjudication named every time.

  work/queues/fidelity_waivers.jsonl
"""
from __future__ import annotations

import datetime
import importlib.util
import json
import os
import sys

ROOT = os.path.dirname(os.path.dirname(os.path.abspath(__file__)))
_AUDIT_PATH = os.path.join(ROOT, "tools", "census", "gaps", "decomp_audit.py")

OVERRIDE_ENV = "AZ_ALLOW_FIDELITY_REGRESSION"
OVERRIDE_FLAG = "--allow-fidelity-regression"

_mod = None


def audit_module():
    """tools/census/gaps/decomp_audit.py, imported by path and cached.

    Returns None when the census tree is absent (a partial checkout, a
    `git archive` of an old revision, a worktree without work/s3_splat).  A
    missing auditor must never block a landing, so every caller treats None as
    "no findings".
    """
    global _mod
    if _mod is None:
        if not os.path.exists(_AUDIT_PATH):
            _mod = False
        else:
            spec = importlib.util.spec_from_file_location(
                "az_decomp_audit", _AUDIT_PATH)
            mod = importlib.util.module_from_spec(spec)
            try:
                spec.loader.exec_module(mod)      # inserts its own dir for portlib
            except Exception:                      # noqa: BLE001 - never block a landing
                _mod = False
            else:
                sys.modules["az_decomp_audit"] = mod
                _mod = mod
    return _mod or None


def override_active(flag: bool = False) -> bool:
    """True when this landing is allowed to ADD fidelity sites."""
    if flag:
        return True
    v = os.environ.get(OVERRIDE_ENV, "").strip().lower()
    return v not in ("", "0", "false", "no", "off")


class Session:
    """One baseline load + one set of memory-mapped containers, reused across a
    wave.  Cheap to construct; construct one per landing if that is simpler."""

    def __init__(self, baseline_path: str | None = None):
        self.mod = audit_module()
        self.baseline = self.mod.load_baseline(baseline_path) if self.mod else {}
        self.auditor = self.mod.Auditor() if self.mod else None
        self.key_scheme_ok = bool(
            self.mod and self.baseline
            and self.mod.baseline_is_current(self.baseline))
        if self.mod and self.baseline and not self.key_scheme_ok:
            print("decomp_audit ratchet: DISABLED -- " + self.mod.STALE_BASELINE_MSG)

    @property
    def enabled(self) -> bool:
        """A ratchet with keys it can no longer read is a wall, so a stale-keyed
        baseline disables the hook rather than refusing every renamed row."""
        return bool(self.mod and self.baseline and self.key_scheme_ok)

    def refusals(self, overlay: str, func: str, text: str, row=None) -> list[str]:
        """Messages for every ADDED blocking site, or [] when the landing is clean,
        the row cannot be audited, or there is no baseline to ratchet against."""
        if not self.enabled:
            return []
        try:
            return self.mod.landing_refusals(overlay, func, text,
                                             baseline=self.baseline,
                                             aud=self.auditor, row=row)
        except Exception as exc:                   # noqa: BLE001
            # A crash in the auditor is a bug in the auditor, not a reason to
            # stop the project landing byte-exact code.  Say so loudly and pass.
            print(f"decomp_audit ratchet: SKIPPED {overlay}/{func} "
                  f"(auditor error: {exc})")
            return []


_DEFAULT: Session | None = None


def session(baseline_path: str | None = None) -> Session:
    global _DEFAULT
    if _DEFAULT is None or baseline_path is not None:
        s = Session(baseline_path)
        if baseline_path is None:
            _DEFAULT = s
        return s
    return _DEFAULT


def landing_refusals(overlay: str, func: str, text: str, row=None,
                     baseline_path: str | None = None) -> list[str]:
    """One-shot form, mirroring portability_lint.landing_refusals()."""
    return session(baseline_path).refusals(overlay, func, text, row=row)


def refusal_message(func: str, refusals: list[str], tool: str = "") -> str:
    """The message both landing tools print.  Names the site and the class,
    says how to fix it, and says -- explicitly -- how to override."""
    n = sum(1 for r in refusals if r.startswith("NEW fidelity site")) or len(refusals)
    lines = [f"fidelity ratchet REFUSED {func}: "
             f"{n} NEW semantically-wrong site(s) "
             f"(config/decomp_audit_baseline.json grandfathers the existing ones)"]
    lines += ["  " + r for r in refusals]
    lines.append(
        f"  -> fix the C (see docs/fidelity_ratchet.md; the classes and their analyses are "
        f"port/docs/decomp_issues.md sections 11/12/20-22/24, and port/tools/gen_sources.py "
        f"already does the mechanical rewrite), or override with "
        f"{OVERRIDE_FLAG}{(' on ' + tool) if tool else ''} / {OVERRIDE_ENV}=1 and then "
        f"re-run tools/census/gaps/decomp_audit.py --write-baseline.")
    return "\n".join(lines)


#: Durable record of every site the blanket override let through.  Untracked
#: (``work/`` is gitignored) but append-only and machine-readable, so "what did
#: the overrides actually admit" is answerable without re-auditing the tree --
#: which is exactly the question the 2026-09-01 regeneration had to answer the
#: hard way, by finding 44 leaked sites after the fact.
WAIVER_LEDGER = os.path.join(ROOT, "work", "queues", "fidelity_waivers.jsonl")


def waiver_message(func: str, refusals: list[str], tool: str = "",
                   ledger: str | None = None) -> str:
    """The message the override prints.  Same shape as :func:`refusal_message`,
    opposite verdict: these sites ARE landing, and here is what they are."""
    n = sum(1 for r in refusals if r.startswith("NEW fidelity site")) or len(refusals)
    lines = [f"fidelity ratchet WAIVED {func}: {n} NEW semantically-wrong site(s) "
             f"LANDED ANYWAY under {OVERRIDE_FLAG}"
             f"{(' on ' + tool) if tool else ''} / {OVERRIDE_ENV}=1"]
    lines += ["  " + r for r in refusals]
    lines.append(
        "  -> REQUIRED FOLLOW-UP: tools/census/gaps/decomp_audit.py "
        "--write-baseline, and ADJUDICATE the result -- a site with no "
        "sanctioned route belongs in adjudication.withheld_blocking_sites, not "
        "in the grandfathered set. Skipping this is how 44 would-refuse sites "
        "entered the tree unrecorded before 2026-09-01.")
    lines.append(f"  -> recorded: {os.path.relpath(ledger or WAIVER_LEDGER, ROOT)}")
    return "\n".join(lines)


def record_waiver(overlay: str, func: str, refusals: list[str], tool: str = "",
                  ledger: str | None = None) -> str:
    """Print the waiver to stderr AND append it to the durable ledger.

    Never raises: an override that cannot write its ledger must still not break
    a landing that the override itself already permitted.  Returns the message
    so the caller can put it on the landing record too.
    """
    path = ledger or WAIVER_LEDGER
    message = waiver_message(func, refusals, tool, ledger=path)
    print(message, file=sys.stderr)
    try:
        os.makedirs(os.path.dirname(path), exist_ok=True)
        with open(path, "a", encoding="utf-8") as fh:
            fh.write(json.dumps({
                "waived_utc": datetime.datetime.now(datetime.timezone.utc)
                                       .isoformat(timespec="seconds"),
                "overlay": overlay, "func": func, "tool": tool,
                "sites": list(refusals),
                "write_baseline_adjudication_required": True,
            }, sort_keys=True) + "\n")
    except Exception as exc:  # noqa: BLE001 - a ledger outage never blocks a landing
        print(f"decomp_audit ratchet: waiver ledger unwritable ({exc}); the "
              f"waiver above is NOT durably recorded", file=sys.stderr)
    return message


def overlay_for_resident() -> str:
    """The container name integrate.py's src/ TUs belong to."""
    return "slus"
