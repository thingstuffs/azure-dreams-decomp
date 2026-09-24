#!/usr/bin/env python3
"""Derive each row's cleanliness level from the current clean tree -> ledger/levels.jsonl.

L0 verified exact at the pin.  L1 no boilerplate, dead pins erased (t2 journalled), no blocking
fidelity site (a whole function emitted by top-level asm counts as one: owner ruling 2026-09-24) and no pseudo-call to a label inside the row (whether or not the baseline audit
listed it) -- EXCEPT a LABEL_AS_CALL site, or an intra-tail-call hit, whose target carries a
DECIDED `cross-segment`/`cross-image` `ledger/split_audit.jsonl` record for THIS row: that is a
real inter-module jump, not scaffolding for this row (owner ruling 2026-09-22 afternoon, "im ok
with a level change as long as it's picked up at some level"), so it no longer counts toward
`blocking`.  It is still picked up at L4 below, unchanged: `tools/split_audit.py` only ever audits
`tail_jump_targets` members (see its own docstring), so an exempted target is by construction
already counted in `tail_jumps`.  L2 also no M2C_FIELD.  L3 a Layer-2 pass journalled (locals/comments) AND every
tail-jump dependency of the row -- a noreturn pseudo-call in the text, or a call to a symbol in
this row's container `config/sibcall_syms*.txt`/`config/noreturn_syms*.txt` -- carries a
`ledger/split_audit.jsonl` record (owner ruling 2026-09-22 evening: a retail `j` to a "function"
symbol may mean a mis-split, and that deserves a check before L3) whose `kind` is neither `intra`
(mis-split/pseudo-call) nor `unresolved`; a row with no tail-jump dependency is unaffected.  L4
adds the module criterion (`l4_modules` sweep) AND pins == 0 AND no tail-jump dependency of any
kind, audited or not -- the sibcall/noreturn tail-jump scaffolding is a residue class in its own
right (owner ruling: "needs to be covered by a level, somewhere").  L5 STRICT: no fidelity site of
ANY audit class, no computed-goto table, no inline asm, no NON_MATCHING guard (pins and tail-jumps
are already excluded by L4).  A row that cannot reach L5 stays at L4 with its residue documented;
`l5_residue` names what is left, `l4_residue` names what blocks L4 (`pins`/`tail_jump`/
`not_in_module`).  See docs/PIN_CAMPAIGN_CHARTER.md "Rulings 2026-09-22 (evening)" and "Rulings
2026-09-22 (afternoon, goal round)".
"""
import re, collections
from pathlib import Path
from common import ROOT, LEDGER, rows, read_jsonl, write_jsonl, raw_path
from census import (M2C_LOCAL_RE, audit_index, DECL_LINE, DEF_HEADER_RE,
                     audit_sites, live_sites as census_live_sites)
from pin_census import arm_labels, HAS_PP_RE, sites_of

# ---- spelling shims the pre-preprocessor scans must see through -----------------------------
# Two devices in the tree hide or misdirect a tail-jump dependency for a regex that reads the C
# *before* the preprocessor (evidence: docs/evidence/split_fragments_20260922.md):
#   * the true-base rename shim `#define func_<legacy> func_<true>` (src/dungeon/func_80BD3BA8.c).
#     It MISDIRECTS: the legacy spelling is 0x12000 above the real label, so tools/split_audit.py
#     resolved it into a foreign overlay segment and reported that segment's jumps as this row's
#     (§3).  The real targets are labels inside the row's own extent, i.e. `intra`.
#   * the returning-call shim `#define func_X_returning func_X` and its `__mips__` twin
#     `__asm__(".set func_X_returning, func_X")` (src/dungeon/func_81898B70.c, func_80CEB850.c).
#     It HIDES: `func_X_returning(` never matches `func_[0-9A-F]{8}\s*\(`, so no record was ever
#     demanded of a call the container's noreturn list does cover (§5.1).
# The alias map is read from the WHOLE file, both preprocessor arms on purpose: a `_returning`
# shim spells the same alias in each arm, and taking it only from the arm arm_labels() keeps would
# make the result depend on which arm that is.
DEFINE_ALIAS_RE = re.compile(r"^[ \t]*#[ \t]*define[ \t]+([A-Za-z_]\w*)[ \t]+(func_[0-9A-F]{8})[ \t]*$", re.M)
SET_ALIAS_RE = re.compile(r"\.set[ \t]+([A-Za-z_]\w*)[ \t]*,[ \t]*(func_[0-9A-F]{8})")
# `static void (*const NAME[])(void) ... = { f, g, ... };` -- a casesi / dispatch jump table.  Its
# entries are the ADDRESSES of labels, not calls, and in an overlay they routinely point inside
# another row's function (§1: func_80025DF4 is func_80024F10's shared epilogue; §2: three 8-byte
# case bodies).  Blanked here so a table entry can never be read as a tail-jump dependency,
# whatever list the symbol happens to be on.
FPTR_TABLE_RE = re.compile(
    r"\(\s*\*\s*(?:const[ \t]+)?[A-Za-z_]\w*\s*\[[^\]\n]*\]\s*\)\s*\([^;{)]*\)[^=;{]*=\s*\{[^{}]*\}\s*;", re.S)

def _blank_keep_lines(m):
    """Blank a matched span, preserving its line count exactly: the callers zip this text against
    pin_census.arm_labels(text), which is per-line, so dropping a line would misalign the arms."""
    return "\n" * m.group(0).count("\n")

def resolve_spellings(text):
    """The view every tail-jump detector below reads: alias shims expanded to the symbol they
    really name, function-pointer jump tables blanked.  Line count is preserved exactly."""
    if "func_" not in text:
        return text
    alias = {}
    for rx in (DEFINE_ALIAS_RE, SET_ALIAS_RE):
        for a, b in rx.findall(text):
            if a != b:
                alias[a] = b
    text = FPTR_TABLE_RE.sub(_blank_keep_lines, text)
    if not alias:
        return text
    for a in list(alias):                          # follow `#define A B` / `#define B C` chains
        seen, b = {a}, alias[a]
        while b in alias and b not in seen:
            seen.add(b); b = alias[b]
        alias[a] = b
    text = DEFINE_ALIAS_RE.sub("", text)           # the shim lines themselves name no dependency
    pat = "|".join(re.escape(a) for a in sorted(alias, key=len, reverse=True))   # longest first
    return re.sub(r"\b(" + pat + r")\b", lambda m: alias[m.group(1)], text)

def _noreturn_call_targets(text):
    """func_ targets declared noreturn or asm-aliased anywhere in this text AND actually called
    via a tail-call statement (`return TARGET(...)` or `TARGET(...)` at the start of a line) --
    the pseudo-call shape maspsx's tail-jal->j pass produces.  No extent filter: intra_tail_calls
    narrows this to targets inside the row's own [base, base+size); tail_jump_targets does not,
    because a target OUTSIDE the row is exactly the case the owner's 2026-09-22 ruling asks a
    level to check (a retail `j` to a "function" symbol may mean the row was split wrong).

    "declared noreturn" covers the literal `__attribute__((noreturn))` spelling AND the bare
    `NORETURN` macro token (`#define NORETURN __attribute__((noreturn))` / `#define NORETURN`
    under `#else`, the portable-noreturn idiom this tree uses, e.g. src/dungeon/func_81988E48.c
    pre-landing: `extern void func_80024908(void) NORETURN;`) -- tools/gate/gen_noreturn_syms.py
    has treated the two as equivalent since it exists (`_NORETURN_MACRO_RE`); this regex did not,
    so a row whose ONLY spelling of a target's noreturn-ness is the macro was silently invisible
    to this per-row source detector, independent of whether the target is on the container's
    sibcall/noreturn list (found 2026-09-22, docs/evidence -- dungeon/func_81988E48's own
    func_80024908() pseudo-call, in-extent, never got a split_audit.jsonl record)."""
    text = resolve_spellings(text)
    # only the arms the build compiles: a noreturn declaration + call that live solely inside an
    # `#ifdef NON_MATCHING` (or `#if 0`) arm is text no compiler sees, so it is not a tail call in
    # the product (town/func_8051EDA4, 2026-09-22) -- same classification census.live_sites uses.
    if HAS_PP_RE.search(text):
        text = "\n".join("" if lab in ("port", "dead") else ln
                         for ln, lab in zip(text.splitlines(), arm_labels(text)))
    targets = set(re.findall(
        r"\b(func_[0-9A-F]{8})\s*\([^;{]*\)\s*(?:__attribute__\s*\(\s*\(\s*noreturn\b|NORETURN\b)",
        text))
    targets |= set(re.findall(r"(?:asm|__asm__)\s*\(\s*\"(func_[0-9A-F]{8})\"\s*\)", text))
    return {tgt for tgt in targets
            if re.search(r"^[ \t]*(?:return[ \t]+)?" + re.escape(tgt) + r"\s*\(", text, re.M)}

def intra_tail_call_targets(r, text, targets=None):
    """The target set intra_tail_calls counts: a noreturn-declared or asm-aliased func_ target
    whose address lies in [true base, +size) and which the text still calls (declarations
    excluded) -- whether or not the baseline audit listed it.  `targets`, if given, is a
    precomputed _noreturn_call_targets(text) -- evaluate_row shares it with tail_jump_targets so
    the same text is not scanned for the noreturn/asm-alias pattern twice per row.  Split out from
    intra_tail_calls (which just counts these) so evaluate_row can look each target up in
    split_audit_index individually -- owner ruling 2026-09-22 afternoon: a target with a DECIDED
    cross-segment/cross-image record does not count toward `blocking`, even though this narrower
    extent heuristic called it intra."""
    m = re.match(r"func_([0-9A-F]{8})$", r.get("true_name") or r["func"] or "")
    if not m or r["kind"] != "overlay": return set()
    base = int(m.group(1), 16); end = base + r["size"]
    if targets is None: targets = _noreturn_call_targets(text)
    return {tgt for tgt in targets if base <= int(tgt[5:], 16) < end}

def intra_tail_calls(r, text, targets=None):
    """Count form of intra_tail_call_targets -- kept for callers/tests that only need the count."""
    return len(intra_tail_call_targets(r, text, targets))

def live_audit_sites(r, text):
    """Full site strings ('CLASS|target|extra') still live in `text`, from the same
    container/func keys census.live_audit tallies -- but live_audit only returns {class: n}, which
    throws the target away.  The split-audit exemption in evaluate_row (owner ruling 2026-09-22
    afternoon) needs the target to look up a specific (row, target) pair in split_audit_index, so
    this keeps the site list census.live_sites/audit_sites already compute, unfiltered by class."""
    keys = [f"{r['container']}/{f}" for f in (r.get("defs") or [r["func"]])]
    out = []
    for k in keys:
        out.extend(census_live_sites(text, audit_sites().get(k, [])))
    return out

_CONTAINER_SYMS = {}
def container_tail_syms(container):
    """The union of config/sibcall_syms[.<container>].txt and config/noreturn_syms[.<container>].txt
    for this row's container: symbols retail reaches only by `j` (a genuine tail dispatcher, LEAD
    22) or that maspsx's own noreturn pass rewrote from `jal` to `j` (LEAD 18).  `main` has no
    suffix; town/dungeon/ovmovie do (see the files themselves).  A call of one of these from a row
    is a tail-jump dependency under the owner's 2026-09-22 ruling, whether or not it is also a
    noreturn pseudo-call in the C.  Cached per container; missing files are silently empty."""
    if container not in _CONTAINER_SYMS:
        out = set()
        suffix = "" if container == "main" else f".{container}"
        for stem in ("sibcall_syms", "noreturn_syms"):
            p = ROOT / "config" / f"{stem}{suffix}.txt"
            if p.exists():
                for line in p.read_text(errors="replace").splitlines():
                    tok = line.split("#", 1)[0].split()
                    if tok:
                        out.add(tok[0])
        _CONTAINER_SYMS[container] = out
    return _CONTAINER_SYMS[container]

CALL_TOKEN_RE = re.compile(r"\b([A-Za-z_][A-Za-z0-9_]*)\s*\(")
IDENT_RE = re.compile(r"\b[A-Za-z_][A-Za-z0-9_]*\b")   # a genuine identifier scan: comment-stripping
                                                        # can JOIN text (`func_X/* */()`), so CALL_TOKEN_RE
                                                        # on raw text is not provably a superset of
                                                        # _call_text's tokens, but an atomic identifier is

def _call_text(text):
    """Comment-stripped, definition-header-blanked, declaration-blanked, port/dead-arm-blanked
    text: the same view census.live_sites reads a call from, reused here so a prototype, the
    row's own definition header, or text the build never compiles is never counted as a
    tail-jump dependency.  Without the definition-header blank, a row whose own name is in its
    container's noreturn/sibcall list (a noreturn function or dispatcher defined in-tree) would
    list itself as a tail-jump dependency off its own `void func_X(...) {` header alone.  Alias
    shims are expanded and jump tables blanked first (resolve_spellings), so the token a call is
    counted under is the symbol the preprocessor really emits."""
    text = resolve_spellings(text)
    if HAS_PP_RE.search(text):
        text = "\n".join("" if lab in ("port", "dead") else ln
                         for ln, lab in zip(text.splitlines(), arm_labels(text)))
    code = re.sub(r"//[^\n]*", "", re.sub(r"/\*.*?\*/", "", text, flags=re.S))
    code = DEF_HEADER_RE.sub("{", code)
    return "\n".join(l for l in code.splitlines() if not DECL_LINE.match(l) and not l.lstrip().startswith("#"))

def tail_jump_targets(r, text, nr_targets=None):
    """Every tail-jump dependency of this row, sorted: a noreturn-declared/asm-aliased func_
    target actually called anywhere in the text (not only inside the row's own extent -- that
    narrower question is intra_tail_calls, the mis-split detector) UNION any call of a symbol in
    this row's container sibcall/noreturn list.  Each target needs a ledger/split_audit.jsonl
    record -- schema azure-clean.split-audit.v1, one record per (row, target) -- to clear L3, and
    none at all to clear L4.  `nr_targets`, if given, is a precomputed _noreturn_call_targets(text)
    (see intra_tail_calls).  The container-list side is skipped when that list is empty (e.g.
    slus, which has no config/sibcall_syms.slus.txt) or when a cheap raw-text token scan already
    rules it out -- filtering (_call_text) only ever removes text, so a raw-text miss means the
    filtered text cannot match either, and the expensive scan is skipped.  resolve_spellings does
    REWRITE tokens, but only to a symbol the raw text already contains (the right-hand side of the
    `#define`/`.set` that names the alias), so the raw-text prefilter stays a valid superset."""
    targets = set(nr_targets if nr_targets is not None else _noreturn_call_targets(text))
    csyms = container_tail_syms(r["container"])
    if csyms and (csyms & set(IDENT_RE.findall(text))):
        called = set(CALL_TOKEN_RE.findall(_call_text(text)))
        targets |= csyms & called
    return sorted(targets)

def split_audit_index():
    """{(row id, target): kind} from ledger/split_audit.jsonl (schema azure-clean.split-audit.v1).
    That file is written elsewhere (tools/split_audit.py, concurrent work); a missing file means
    "no audit yet" -- every tail-jump dependency then counts as unaudited, never as cleared."""
    idx = {}
    p = LEDGER / "split_audit.jsonl"
    if p.exists():
        for j in read_jsonl(p):
            idx[(j.get("id"), j.get("target"))] = j.get("kind")
    return idx

def audit_gate(row_id, targets, split_idx):
    """kinds aligned to `targets`, and whether every one clears L3: a record must exist and its
    kind must be neither `intra` (mis-split) nor `unresolved`.  `"missing"` is this function's own
    sentinel for "no record at all" -- it is not one of schema azure-clean.split-audit.v1's kind
    values (`intra`/`extern-jal`/`extern-j-only`/`cross-segment`/`cross-image`/`text-only`/`asm`/
    `unresolved`) -- and is treated the same as `unresolved` for the L3 gate: no record yet is no
    different from "not resolved yet".

    `cross-segment` (added 2026-09-22 with tools/split_audit.py's own fix) clears L3 exactly like
    `extern-jal`: it is a decided verdict -- the target address is not inside the declaring row's
    own segment under that row's delta, so it is NOT a mis-split of this row and no foreign
    segment's jumps may be attributed to it -- and, like every other tail-jump dependency, it
    still blocks L4, which tolerates none of any kind.

    `cross-image` (added 2026-09-22) clears L3 on the same footing: the target is not inside the
    declaring CONTAINER's image at all under that row's delta, and it is decided elsewhere --
    either it is a function of the co-resident SLUS base executable (`image: "slus"`), or retail
    CALLS it with a `jal`, in the row's own retail bytes or inside the row's own segment run,
    while its code is on no image in the tree (`image: "absent"`).  A `jal` is a call and a call
    has a C producer, which is what a retail `j` lacks, so it is not a mis-split of this row.  It
    blocks L4 like every other tail-jump dependency.  The L3 predicate below needs no change for
    either kind: it is the "not intra/unresolved/missing" form, so a new DECIDED kind clears it
    and only an undecided one blocks."""
    kinds = [split_idx.get((row_id, t), "missing") for t in targets]
    return kinds, all(k not in ("intra", "unresolved", "missing") for k in kinds)


# ---- fidelity residue (owner rulings 2026-09-24; docs/TOOLCHAIN_FIDELITY_PLAN.md) -------------------------------
# cell_imitation (blocks L4): the row's RETAIL shows compiler address splitting (ledger/split_fingerprint_rows.jsonl,
#   tools/fidelity/split_fingerprint.py) but its registered cell cannot split - the recipe is wrong and the text
#   imitates the right one.  Clears by itself when the row moves to a splitting cell.
# maspsx_pass (blocks L4): the row is retail-exact only through a maspsx rewrite genuine ASPSX does not make, driven
#   by the source (cdk-imitating la passes, jal->j and marked-slot rewrites) - ledger/maspsx_dependence.jsonl.
# maspsx_dependent (blocks L5): exact only through the toolchain MODEL, not a fault of the row's C - the pre-July-1997
#   cc1 epilogue rules, the small-extern $gp model, the pre-2.56 ASPSX dials (docs/evidence/fidelity_step1*_*.md).
_FID = None
SPLITTING_CELLS = ("2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2")   # = tools/fidelity/split_fingerprint.SPLIT_CELLS

def fidelity_index():
    global _FID
    if _FID is None:
        fp = {j["id"] for j in read_jsonl(LEDGER / "split_fingerprint_rows.jsonl")} if (LEDGER / "split_fingerprint_rows.jsonl").exists() else set()
        dep = {j["id"]: set(j.get("kinds", [])) for j in read_jsonl(LEDGER / "maspsx_dependence.jsonl")} if (LEDGER / "maspsx_dependence.jsonl").exists() else {}
        _FID = (fp, dep)
    return _FID

def _fid_cell(r):
    return int(r["id"] in fidelity_index()[0] and not cfg_splits(r.get("cfg")))

def _fid_has(r, kind):
    return int(kind in fidelity_index()[1].get(r["id"], ()))

def cfg_splits(cfg):
    toks = (cfg or "").split()
    return bool(toks) and toks[0].startswith(SPLITTING_CELLS) and "-mmips-as" not in toks and "-mno-split-addresses" not in toks

WHOLE_ASM_FN_RE = re.compile(r'"\s*\.ent\s+[A-Za-z_]\w*')

def evaluate_row(r, text, raw_text, promoted, sweeps, split_idx):
    """Pure per-row ladder logic for one L0 row (main() only calls this once l0 is confirmed): `r`
    the row dict, `text`/`raw_text` the current and pinned source, `promoted` the set of ids
    landed per ledger/promotions.jsonl, `sweeps` {sweep name: {id: record}}, `split_idx` from
    split_audit_index().  Returns the levels.jsonl record for this row, minus `id`/`evidence`
    (main() adds those).  No filesystem access beyond the module-level config caches, so this is
    directly unit-testable with synthetic rows/text (tools/tests/test_levels.py)."""
    live_sites_full = live_audit_sites(r, text)          # site strings with target kept, unlike live_audit's tally
    live = collections.Counter(s.split("|")[0] for s in live_sites_full)             # live: a removed site no longer blocks
    nr_targets = _noreturn_call_targets(text)   # shared with tail_jump_targets: scan the text once
    # owner ruling 2026-09-22 (afternoon): a LABEL_AS_CALL site, or an intra_tail_calls hit, whose
    # target carries a DECIDED cross-segment/cross-image split_audit record for THIS row is a real
    # inter-module jump, not scaffolding for this row -- exempt from `blocking`.  PASSTHRU_NO_ARGS
    # is unchanged.  The exemption never weakens L4: split_audit.py only ever audits
    # tail_jump_targets members, so an exempted target is already counted in `tail_jumps` below.
    def _decided_cross(tgt):
        return split_idx.get((r["id"], tgt)) in ("cross-segment", "cross-image")
    label_blocking = any(s.startswith("LABEL_AS_CALL|") and not _decided_cross(s.split("|")[1]) for s in live_sites_full)
    passthru_blocking = any(s.startswith("PASSTHRU_NO_ARGS|") for s in live_sites_full)
    itc_targets = intra_tail_call_targets(r, text, nr_targets)
    itc_blocking = any(not _decided_cross(tgt) for tgt in itc_targets)
    # owner ruling 2026-09-24: a function whose body is emitted by top-level asm (`.ent <name>` in an
    # `__asm__` string, e.g. slus/w_8005A1D0's 39 `.word` lines) is not decompiled - it is a missing
    # function, so it is a blocking fidelity site and the row stays at L0 until it is written in C.
    asm_function = bool(WHOLE_ASM_FN_RE.search(text))
    blocking = label_blocking or passthru_blocking or itc_blocking or asm_function
    any_site = bool(live)
    # The charter's counter (docs/PIN_CAMPAIGN_CHARTER.md rule 5: status.py "Pin sites now" =
    # pin_census.sites_of), not a raw `ASM_X(` token count.  The token count also read macro
    # DEFINITIONS (`#define ASM_KEEP(v) __asm__(...)`, a wrapper's body), text in NON_MATCHING/#if 0
    # arms no byte gate compiles, and `ASM_REG` on a non-`register` local (gcc 2.x ignores that
    # asm-spec: byte-neutral, verified on dungeon/func_81329D94), so levels.jsonl summed 3,756 pins
    # in 916 rows against the counter's 3,701 in 902 (docs/evidence/r76_pin_count_discrepancy.md).
    pins = len(sites_of(text))
    tail_idiom = len(re.findall(r"__attribute__\s*\(\s*\(\s*noreturn\s*\)\s*\)", text)) + len(re.findall(r"\b(?:asm|__asm__)\s*\(\s*\"func_[0-9A-F]{8}\"\s*\)", text))
    computed_goto = len(re.findall(r"\bgoto\s*\*", text)); inline_asm = len(re.findall(r"__asm__|\basm\s*\(", re.sub(r"\bASM_[A-Z0-9_]+\(", "", text)))
    boiler = "This header contains macros emitted by m2c" in text or "typedef float f32;" in text
    tj_targets = tail_jump_targets(r, text, nr_targets)
    tj_kinds, tail_ok = audit_gate(r["id"], tj_targets, split_idx)
    tail_jumps = len(tj_targets)
    in_module = r["id"] in sweeps.get("l4_modules", {})
    level = 0
    if not boiler and (pins == 0 or r["id"] in sweeps.get("t2_pins", {})) and not blocking:
        level = 1
        if not re.search(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#"))):
            level = 2
            # L3 also needs every tail-jump dependency audited (owner ruling 2026-09-22 evening):
            # a split_audit record, none of them "intra" (mis-split) or "unresolved".
            if r["id"] in promoted and text != raw_text and tail_ok:   # a landed Layer-2 body is the src text (ledger/promotions.jsonl)
                level = 3
                # L4 = module placement AND pins == 0 (strict, not the t2_pins sweep loophole)
                # AND zero tail-jump dependency of any kind, audited or not.
                fp_rows, dep = fidelity_index()
                cell_imitation = int(r["id"] in fp_rows and not cfg_splits(r.get("cfg")))
                maspsx_pass = int("maspsx_pass" in dep.get(r["id"], ()))
                if in_module and pins == 0 and tail_jumps == 0 and not cell_imitation and not maspsx_pass:
                    level = 4
                    # L5 is strict on what is left once L4's pins/tail-jump gate has already run:
                    # no fidelity site of any audit class, no computed-goto table, no inline asm,
                    # no NON_MATCHING guard.  A row that cannot get there stays at L4 (T6 notes).
                    if not any_site and computed_goto == 0 and inline_asm == 0 and "NON_MATCHING" not in text \
                            and "maspsx_dependent" not in dep.get(r["id"], ()):
                        level = 5
    recs = sorted(set(re.findall(r'#include "records/(Rec_[A-Za-z0-9_]+)\.h"', text)))
    return {"level": level, "pins_left": pins, "m2c_field": len(re.findall(r"(?<![A-Za-z0-9_])(?:M2C_)?FIELD\(", "\n".join(l for l in text.splitlines() if not l.lstrip().startswith("#")))), "blocking": blocking, "records": recs,
            "tail_jumps": tail_jumps, "split_audit": tj_kinds,
            "l5_residue": [k for k, v in (("pins", pins), ("tail_call", tail_idiom), ("fidelity_site", int(any_site)), ("computed_goto", computed_goto), ("inline_asm", inline_asm), ("non_matching", int("NON_MATCHING" in text)), ("maspsx_dependent", _fid_has(r, "maspsx_dependent"))) if v],
            "l4_residue": [k for k, v in (("pins", pins), ("tail_jump", tail_jumps), ("not_in_module", int(not in_module)), ("cell_imitation", _fid_cell(r)), ("maspsx_pass", _fid_has(r, "maspsx_pass"))) if v],
            "l5_fidelity": sorted(fidelity_index()[1].get(r["id"], ()))}

def main():
    promoted = {j["id"] for j in read_jsonl(LEDGER / "promotions.jsonl") if j.get("outcome") == "landed"} if (LEDGER / "promotions.jsonl").exists() else set()
    try:
        from evidence import EV as _EV
        _ev = {e["id"]: [k for k in ("assert_sites", "identifiers", "adrando", "data", "vm", "knowledge", "name") if e.get(k)] for e in read_jsonl(_EV / "rows.jsonl")} if (_EV / "rows.jsonl").exists() else {}
    except Exception:
        _ev = {}
    base = {b["id"]: b for b in read_jsonl(LEDGER / "baseline.jsonl")}
    sweeps = {}
    for p in (LEDGER / "sweeps").glob("*.jsonl"):
        sweeps[p.stem] = {j["id"]: j for j in read_jsonl(p) if j.get("id") and j.get("outcome") in ("applied", "noop")}
    # SLUS placement comes from a reviewed build certificate whose shared inputs
    # are still current. A historical sweep entry cannot substitute for that proof.
    from slus_module_evidence import valid_placements
    placement = {rid: rec for rid, rec in sweeps.get("l4_modules", {}).items() if not rid.startswith("slus/")}
    placement.update(valid_placements())
    sweeps["l4_modules"] = placement
    audit = audit_index()
    split_idx = split_audit_index()   # ledger/split_audit.jsonl -- see the module docstring; empty until it exists
    out = []; tally = collections.Counter()
    for r in rows():
        b = base.get(r["id"], {})
        l0 = r["stock"] and (b.get("exact") is True or (r["kind"] == "slus" and b.get("status") == "ok"))
        if not l0:
            out.append({"id": r["id"], "level": -1}); tally[-1] += r["size"]; continue
        cp = ROOT / "src" / r["container"] / Path(r["c_path"]).name
        text = (cp if cp.exists() else raw_path(r)).read_text(errors="replace")
        raw_text = raw_path(r).read_text(errors="replace") if raw_path(r).exists() else ""
        rec = evaluate_row(r, text, raw_text, promoted, sweeps, split_idx)
        rec["id"] = r["id"]; rec["evidence"] = list(_ev.get(r["id"], []))
        if r["id"] in placement:
            rec["module"] = placement[r["id"]].get("module")
            if r["id"].startswith("slus/"):
                rec["evidence"].append("module_certificate")
        out.append(rec); tally[rec["level"]] += r["size"]
        if rec["records"]: tally["records"] += r["size"]; tally["records_rows"] += 1
    write_jsonl(LEDGER / "levels.jsonl", out)
    tot = sum(r["size"] for r in rows())
    for l in sorted(k for k in tally if isinstance(k, int)): print(f"L{l}: {tally[l]:,} B ({100*tally[l]/tot:.1f}%)")
    print(f"on shared record headers (T7): {tally['records_rows']} rows, {tally['records']:,} B ({100*tally['records']/tot:.1f}%)")

if __name__ == "__main__":
    main()
