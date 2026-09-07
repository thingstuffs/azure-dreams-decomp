#!/usr/bin/env python3
"""I5 -- residue auto-classifier (docs/one_to_one_program.md §2 taxonomy, §3 I5).

Given an overlay + func + candidate C + compiler config, compile through the SAME
pinned pipeline overlay_func_compare uses (reuse its machinery: per-container maspsx
evidence selection, name-encoded symbol injection, match.py build_text) and classify
the word-level residue against the retail bytes into the R1-R10 residue families:

    slot-rotation  reorder-only  reg-rename  hold-set  const-remat
    li-expansion   addressing    block-order polarity  length-drift  broad
    div-guard      (LEAD 12b: an assembler div/rem trap-guard expansion, not codegen)

The diff is realigned with an LCS pass over the (reloc-normalized) instruction words
BEFORE classifying, so an insertion/deletion drift does not masquerade as N unrelated
substitutions.  Deterministic and LLM-free.

    tools/residue_class.py --overlay town --func func_800AACA8 \\
        --c-file <c> --match-config 2.7.2-G0                       # one function
    tools/residue_class.py --batch --overlay town --max-words 8    # a first-pass set
    tools/residue_class.py --batch --all --max-words 8 \\
        --out work/residue_class/classified.jsonl                  # every overlay

Style-matched to tools/first_pass.py (argparse, ROOT resolution, process pool).
"""

from __future__ import annotations

import argparse
import contextlib
import importlib.util
import io
import json
import os
import re
import sys
from collections import Counter
from concurrent.futures import ProcessPoolExecutor
from difflib import SequenceMatcher
from pathlib import Path
from typing import Any

ROOT = Path(__file__).resolve().parents[1]

# --- reuse the exact overlay compare/machinery (evidence env + symbol injection +
#     match.py build_text) so a residue classification is compiled identically to a
#     gate compare.  Imported as modules (same trick first_pass.py uses for match). ---
_ofc_spec = importlib.util.spec_from_file_location(
    "overlay_func_compare", ROOT / "work/g3/overlay_func_compare.py")
OFC = importlib.util.module_from_spec(_ofc_spec)
assert _ofc_spec.loader is not None
_ofc_spec.loader.exec_module(OFC)
M = OFC.M

_ev_spec = importlib.util.spec_from_file_location(
    "overlay_evidence", ROOT / "tools/overlay_evidence.py")
EV = importlib.util.module_from_spec(_ev_spec)
assert _ev_spec.loader is not None
_ev_spec.loader.exec_module(EV)

# overlay name -> retail container the first-pass foff/size index into.  town/dungeon/
# ovmovie per the I5 brief; dungeon_engine shares DUNGEON.BIN (its rows carry the same
# foff as the dungeon set); main is MAIN.BIN.  All five validated against known-MATCH rows.
CONTAINERS = {
    "town": ROOT / "work/roundtrip/extract/TOWN/TOWN.BIN",
    "dungeon": ROOT / "work/roundtrip/extract/DUNGEON/DUNGEON.BIN",
    "dungeon_engine": ROOT / "work/roundtrip/extract/DUNGEON/DUNGEON.BIN",
    "main": ROOT / "work/roundtrip/extract/MAIN/MAIN.BIN",
    "ovmovie": ROOT / "work/roundtrip/extract/OVMOVIE.BIN",
}
OVERLAYS = tuple(CONTAINERS)

# ---------------------------------------------------------------------------- compile

def _set_evidence(overlay: str) -> None:
    """Select the container-family maspsx evidence files for ``overlay`` (Phase-B
    per-container selection).  Pop first so a prior overlay's vars never leak into a
    'main' compile (whose empty-dict return means 'use the built-in defaults')."""
    for k in ("MASPSX_NORETURN_FILE", "MASPSX_SIBCALL_FILE"):
        os.environ.pop(k, None)
    os.environ.update(EV.evidence_env(overlay))


def read_target(overlay: str, row: dict[str, Any]) -> bytes:
    with CONTAINERS[overlay].open("rb") as f:
        f.seek(int(row["foff"]))
        return f.read(int(row["size"]))


def compile_words(overlay: str, row: dict[str, Any], c_file: str,
                  match_config: str | None) -> dict[str, Any]:
    """Compile one candidate through the pinned pipeline and return
    {status, words_off, got, tgt, link_fail, unresolved}.  status in
    MATCH / NOMATCH / CFAIL.

    The compile is done IDENTICALLY to the census/gate compare
    (overlay_func_compare.py, the harness that produced the frozen census this
    module is driven against): the SAME rowbase true-base resolution and the
    SAME phantom signal.  In particular ``link_fail`` mirrors the canonical
    harness -- it is set only when ``inject_name_encoded_symbols`` leaves a
    genuinely UNRESOLVED external (no catalog entry AND not name-encodable), in
    which case that reloc reads 0 and the residue really is phantom.  It is NOT
    set for a small-data $gp overflow (``ld FAILED ... R_MIPS_GPREL16``) of a
    RESOLVED/injected symbol: the census classifies those (li-expansion,
    addressing, ...) and so must this module, or a whole band of rowbase rows is
    falsely typed link_fail and dropped to probe-attn while the census routes
    them.  (Historical over-broad string-match on "ld FAILED"/"UNLINKED"
    conflated the two; G3.)"""
    _set_evidence(overlay)
    config = match_config or row.get("config")
    if not config:
        return {"status": "CFAIL", "err": "no config"}
    gcc_ver, gcc_flags = OFC.split_config(config)
    target = read_target(overlay, row)
    cpath = Path(c_file)
    if not cpath.is_absolute():
        cpath = ROOT / cpath
    func = row["func_vram"]
    # Rowbase true-base resolution -- reuse the canonical harness machinery so a
    # residue classification is compiled at the SAME base a gate compare uses
    # (overlay_func_compare.rowbase_link_vram / tools/rowbase.py).  In-region
    # candidates self-address in TRUE space, so link there and prefer whichever
    # symbol name the TU actually defines (true-space vs synthetic row identity).
    link_vram, rowbase = OFC.rowbase_link_vram(
        overlay, int(row["foff"]), int(row["vram"]))
    target_symbol = func
    if rowbase is not None:
        true_name = f"func_{link_vram:08X}"
        c_text = cpath.read_text(errors="replace")
        if (re.search(rf"\b{re.escape(true_name)}\s*\(", c_text)
                and not re.search(rf"\b{re.escape(func)}\s*\(", c_text)):
            target_symbol = true_name
    # Capture stderr so the noisy match.py/ld warnings do not pollute the caller.
    # The honest phantom signal is the `unresolved` set (parity with the
    # canonical harness), NOT a stderr string-match -- see the docstring.
    cap = io.StringIO()
    with contextlib.redirect_stderr(cap):
        _injected, unresolved = OFC.inject_name_encoded_symbols(
            cpath, gcc_ver, gcc_flags, func)
        got, err = M.build_text(
            str(cpath), OFC.compiler_for(gcc_ver), "O2", "2.56",
            gcc_flags, "", link_vram, target=target_symbol,
            retail_text=target)
    link_fail = bool(unresolved)
    if got is None:
        return {"status": "CFAIL", "err": (err or "")[:160], "config": config}
    got = got[: len(target)]
    # Metric parity (Option C, 2026-07-21): this module compiles LINKED at the
    # true base with every external injected, so call-target words are resolved
    # evidence — status and words_off are STRICT (the masked flavor reported
    # 8133564C at 4 when the strict truth was 24, and could call MATCH on a
    # candidate whose call targets differ).  classify() keeps its own masked
    # normalization internally: a catalog gap must not change a residue CLASS.
    ok = len(got) >= len(target) and got[:len(target)] == target
    return {
        "status": "MATCH" if ok else "NOMATCH",
        "words_off": 0 if ok else M.word_mismatch_count(
            got.hex(), target, mask_relocations=False),
        # Boundary case (2026-07-21 re-journal lesson): for rows in UNPROVEN
        # rowbase regions, strict counts are phantom-laden (synthetic-named
        # callees resolve at synthetic addresses; masked 9 vs strict 252 on
        # deep-dungeon rows) — the masked figure remains the honest selection
        # heuristic there until the region base is proven.  Consumers admit by
        # words_off, falling back to words_off_masked when region proof is
        # absent.
        "words_off_masked": 0 if ok else M.word_mismatch_count(got.hex(), target),
        "got": got, "tgt": target, "config": config, "link_fail": link_fail,
        "unresolved": unresolved,
    }

# ---------------------------------------------------------------------------- decode

BRANCH = {"beq", "bne", "blez", "bgtz", "bltz", "bgez", "bltzal", "bgezal",
          "beqz", "bnez", "bgezal", "b", "bal", "bgezl", "bltzl", "beql", "bnel"}
JUMP = {"j", "jal", "jr", "jalr"}
CTRL = BRANCH | JUMP
COMPL = {"beq": "bne", "bne": "beq", "blez": "bgtz", "bgtz": "blez",
         "bltz": "bgez", "bgez": "bltz", "beqz": "bnez", "bnez": "beqz"}
LOADSTORE = {"lw", "sw", "lb", "lbu", "lh", "lhu", "sb", "sh", "lwl", "lwr",
             "swl", "swr", "lwc2", "swc2", "lwc1", "swc1", "ldc2", "sdc2"}
CONSTMAT = {"lui", "ori", "addiu", "li", "la", "addu", "or", "move"}
REGS = {"zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2",
        "t3", "t4", "t5", "t6", "t7", "s0", "s1", "s2", "s3", "s4", "s5",
        "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "s8", "ra"}
SAVED = {"s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "fp", "s8"}
_MEMOP = re.compile(r"^(-?(?:0x[0-9a-fA-F]+|\d+))\((\w+)\)$")


def parse_insn(text: str | None) -> tuple[str, list[str], list[str]]:
    """(mnemonic, register-tokens, non-register-tokens) from an objdump line."""
    text = (text or "").strip()
    if not text:
        return "", [], []
    parts = text.split(None, 1)
    mnem = parts[0]
    ops = parts[1] if len(parts) > 1 else ""
    regs: list[str] = []
    imms: list[str] = []
    for tok in (t.strip() for t in ops.split(",") if t.strip()):
        mem = _MEMOP.match(tok)
        if mem:
            imms.append(mem.group(1))
            regs.append(mem.group(2))
        elif tok in REGS:
            regs.append(tok)
        else:
            imms.append(tok)
    return mnem, regs, imms


def _norm(word: int) -> int:
    """Mask j/jal (opcode 2/3) target immediates -- link-time relocations the matcher
    ignores -- so realignment and multiset tests treat them as equal."""
    op = word >> 26
    return (op << 26) if op in (2, 3) else word

# ---------------------------------------------------------------------------- classify

def _frame_size(dis: dict[int, str]) -> int | None:
    for txt in dis.values():
        m = re.match(r"addiu sp,sp,(-?\d+)", txt or "")
        if m:
            return int(m.group(1))
    return None


def _saved_count(dis: dict[int, str]) -> int:
    n = 0
    for txt in dis.values():
        m = re.match(r"(sw|lw)\s+(\w+),", txt or "")
        if m and m.group(2) in SAVED:
            n += 1
    return n


# --- E7/E8 register-role dataflow (dead-word + delay-slot detection) ---------------
_STORE = {"sw", "sb", "sh", "swl", "swr", "swc2", "sdc2", "swc1"}


def _reg_roles(mnem: str, regs: list[str]) -> tuple[str | None, set[str]]:
    """(destination-reg-or-None, source-reg-set) for a decoded insn.  Stores,
    branches, jr/jalr and mult/div read all their register operands and write
    none we track; everything else (ALU/const-mat/load) writes regs[0] and reads
    the rest.  Deliberately conservative -- used only to decide 'is this tgt word
    consumed before it is overwritten' (E7 dead-word)."""
    if not regs:
        return None, set()
    if (mnem in _STORE or mnem in BRANCH
            or mnem in ("jr", "jalr", "mult", "multu", "div", "divu")):
        return None, set(regs)
    if mnem in ("j", "jal"):
        return None, set()
    return regs[0], set(regs[1:])


def _dead_before_redef(dis: dict[int, str], start: int, reg: str, n: int) -> bool:
    """True iff ``reg`` (materialized at tgt word ``start``) is written again before
    any read -- i.e. the value at ``start`` has no consumer (a retained dead word)."""
    for k in range(start + 1, n):
        mnem, regs, _ = parse_insn(dis.get(k * 4))
        if not mnem:
            continue
        dest, reads = _reg_roles(mnem, regs)
        if reg in reads:
            return False
        if dest == reg:
            return True
    return False


# --- div-guard (LEAD 12b): assembler div/rem TRAP-GUARD expansion -----------------
_DIV_GUARD_BRANCH = {"bnez", "beqz", "bne", "beq"}


def _imm_int(imms: list[str]) -> int | None:
    """LAST operand token that parses as an integer literal, or None.

    Last, not first, because objdump prints a two-field break as ``break hi,lo``
    (``break 0x0,0x7``) while retail's ASPSX encoding disassembles to the
    one-field ``break 0x7``; the trap code is the last field in both."""
    out = None
    for tok in imms:
        try:
            out = int(tok, 0)
        except ValueError:
            continue
    return out


def div_guard_words(dis: dict[int, str], n: int) -> tuple[set[int], list[str]]:
    """Word indices covered by every assembler div/rem TRAP-GUARD expansion in
    ``dis`` (a M._disasm_words map), plus the form of each.

    Genuine ASPSX -- and our maspsx under ``--expand-div`` -- expands the `div`
    macro with trap guards; maspsx's DEFAULT (``expand_div=False``,
    toolchain/maspsx/maspsx/__init__.py "# EXPAND_ZERO_DIV") emits only
    ``div $zero,rs,rt`` + ``mflo rd``, so the guard words show up as a pure
    INSERTION against retail:

      unsigned (divu/remu), zero-check only:   bnez rt,L ; nop ; break 0x7
      signed   (div/rem), + overflow check:    ... ; li at,-1 ; bne rt,at,L2 ;
                                               lui at,0x8000 ; bne rs,at,L2 ;
                                               nop ; break 0x6

    Anchored on ``break 0x7`` (the divide-by-zero trap) so a lone `break` or an
    unrelated branch/nop pair cannot match."""
    def at(i: int) -> tuple[str, list[str], list[str]]:
        return parse_insn(dis.get(i * 4))

    covered: set[int] = set()
    forms: list[str] = []
    for j in range(2, n):
        mnem, _regs, imms = at(j)
        if mnem != "break" or _imm_int(imms) != 0x7:
            continue
        if at(j - 1)[0] != "nop" or at(j - 2)[0] not in _DIV_GUARD_BRANCH:
            continue
        words = {j - 2, j - 1, j}
        form = "unsigned"
        tail = [at(j + k) for k in range(1, 7)] if j + 6 < n else []
        if (tail
                and tail[0][0] in ("li", "addiu") and "at" in tail[0][1]
                and _imm_int(tail[0][2]) == -1
                and tail[1][0] in ("bne", "beq") and "at" in tail[1][1]
                and tail[2][0] == "lui" and "at" in tail[2][1]
                and _imm_int(tail[2][2]) == 0x8000
                and tail[3][0] in ("bne", "beq") and "at" in tail[3][1]
                and tail[4][0] == "nop"
                and tail[5][0] == "break" and _imm_int(tail[5][2]) == 0x6):
            words.update(range(j + 1, j + 7))
            form = "signed"
        covered.update(words)
        forms.append(form)
    return covered, forms


def classify(got: bytes, tgt: bytes) -> dict[str, Any]:
    """Classify a NOMATCH residue.  Returns {class, confidence, evidence,
    secondary, words_off, signals}.  Multi-label: primary + optional secondary."""
    size = len(tgt)
    gw = [int.from_bytes(got[i:i + 4], "little") for i in range(0, size, 4)]
    tw = [int.from_bytes(tgt[i:i + 4], "little") for i in range(0, size, 4)]
    gn = [_norm(w) for w in gw]
    tn = [_norm(w) for w in tw]
    n = len(tn)
    gd = M._disasm_words(got)
    td = M._disasm_words(tgt)

    def gi(i: int) -> tuple[str, list[str], list[str]]:
        return parse_insn(gd.get(i * 4))

    def ti(i: int) -> tuple[str, list[str], list[str]]:
        return parse_insn(td.get(i * 4))

    diff_idx = [i for i in range(n) if gn[i] != tn[i]]
    words_off = len(diff_idx)
    if not diff_idx:
        # E1 -- port match.py:674-681 linked-target catch.  _norm masks j/jal target
        # immediates (link-time relocations), so a STRICT NOMATCH whose only raw diffs
        # are resolved jump/call targets collapses to zero normalized diffs here.  The
        # census oracle types that "linked-target" (high), NOT a clean "match"; agree
        # with it instead of silently reporting a match on a strict NOMATCH.
        raw_diff = [i for i in range(n) if gw[i] != tw[i]]
        if raw_diff:
            # Confidence hinges on whether a link/base explanation is even possible.
            # A base shift or synthetic-name misresolution moves EVERY affected
            # target the same way; a LONE differing target while OTHER j/jal target
            # words in the same body match exactly is the cross-function shared-tail
            # signature (retail tail-merges into an out-of-extent epilogue alias --
            # func_800C1D6C word 58, adjudicated 2026-07-24: local join vs retail
            # j into the 0xBF6xx helper page) -- a REAL divergence needing the
            # epilogue-alias C idiom, not a relink.
            matched_targets = sum(1 for i in range(n)
                                  if gw[i] == tw[i] and gn[i] != gw[i])
            lone = len(raw_diff) == 1 and matched_targets > 0
            deltas = {tw[i] - gw[i] for i in raw_diff}
            conf = "med" if (lone or len(deltas) > 1) else "high"
            sig = ["resolved-jump/call-target-diff"]
            if lone:
                sig.append("lone-target-diff-among-matching-targets(shared-tail?)")
            if len(deltas) > 1:
                sig.append("inconsistent-target-deltas")
            return {"class": "linked-target", "confidence": conf,
                    "evidence": f"{len(raw_diff)} resolved jump/call target word(s) "
                                f"differ (link-time relocations, masked by _norm); "
                                f"{matched_targets} other target word(s) match",
                    "secondary": None, "words_off": 0,
                    "signals": sig}
        return {"class": "match", "confidence": "high", "evidence": "",
                "secondary": None, "words_off": 0, "signals": []}

    # --- LCS realignment over normalized words -> aligned substitutions + indels ---
    sm = SequenceMatcher(a=gn, b=tn, autojunk=False)
    subs: list[tuple[int, int]] = []          # (got idx, tgt idx) 1:1 aligned pairs
    ins_idx: list[int] = []                   # tgt-only words (inserted vs got)
    del_idx: list[int] = []                   # got-only words (deleted vs tgt)
    for tag, i1, i2, j1, j2 in sm.get_opcodes():
        if tag == "equal":
            continue
        if tag == "replace":
            k = min(i2 - i1, j2 - j1)
            subs.extend((i1 + x, j1 + x) for x in range(k))
            del_idx.extend(range(i1 + k, i2))
            ins_idx.extend(range(j1 + k, j2))
        elif tag == "insert":
            ins_idx.extend(range(j1, j2))
        elif tag == "delete":
            del_idx.extend(range(i1, i2))
    indels = len(ins_idx) + len(del_idx)

    signals: list[str] = []
    cands: list[tuple[str, str, str]] = []    # (class, confidence, evidence)

    # aligned substitution insns
    pairs = [(gi(a), ti(b), a, b) for a, b in subs]

    # ---- rowbase-unproven signal (E3): _norm masks j/jal targets, so a STRICT word
    #      count that dwarfs the masked count (>=3x) means the residue is dominated by
    #      resolved call/jump-target mismatches -- the classic UNPROVEN-rowbase
    #      signature (synthetic-named callees resolving at synthetic addresses; the
    #      compile_words docstring cites masked 9 vs strict 252 on deep-dungeon rows).
    #      A diagnostic signal only (does not change the residue CLASS); wave_route
    #      routes it to catalog/rowbase proof, never a wave. ----
    raw_off = sum(1 for i in range(n) if gw[i] != tw[i])
    if raw_off >= 3 * max(1, words_off):
        signals.append(f"rowbase-unproven(strict={raw_off}/masked={words_off})")

    # ---- extent-prefix (E2): a contiguous >=6-word INSERTION run anchored at tgt
    #      word 0 is a callback/jump table (or other non-code extent) the C source
    #      never emits -- a recarve/jtbl row-identity fix, NOT a wave/permuter shape. ----
    ins_set = set(ins_idx)
    prefix_run = 0
    while prefix_run in ins_set:
        prefix_run += 1
    if prefix_run >= 6:
        signals.append(f"extent-prefix={prefix_run}")
        cands.append(("extent-prefix", "high",
                      f"{prefix_run}-word insertion run anchored at word 0 "
                      f"(extent-prefix / callback-jtbl); tgt@0='{td.get(0,'')}'"))

    # ---- slot-rotation (R1 / LEAD 26): adjacent branch/jump delay-slot swap ----
    swaps: list[int] = []
    i = 0
    while i < n - 1:
        if gn[i] == tn[i + 1] and gn[i + 1] == tn[i] and gn[i] != gn[i + 1]:
            mnems = {gi(i)[0], gi(i + 1)[0], ti(i)[0], ti(i + 1)[0]}
            if mnems & CTRL:
                swaps.append(i)
                i += 2
                continue
        i += 1
    swap_cover: set[int] = set()
    for s in swaps:
        swap_cover.update((s, s + 1))
    if swaps:
        signals.append(f"swaps={len(swaps)}")
        full = swap_cover.issuperset(diff_idx)
        ex = swaps[0]
        cands.append(("slot-rotation", "high" if full else "med",
                      f"[{ex}]<->[{ex+1}] got '{gd.get(ex*4,'')}'/'{gd.get(ex*4+4,'')}'"
                      f" vs tgt swapped"))

    # ---- reorder-only (R4): identical multiset, different order ----
    if sorted(gn) == sorted(tn) and gn != tn:
        signals.append("same-multiset")
        cands.append(("reorder-only", "high" if not swaps else "med",
                      f"identical {n}-word multiset, {words_off} words reordered"))

    # ---- polarity (R5): complementary branch opcode flip on the SAME compared
    #      operands (a true == -> bne inversion; different regs = drift mis-pairing) ----
    pol = [(g[0], t[0], b) for g, t, a, b in pairs
           if COMPL.get(g[0]) == t[0] and g[1] == t[1]]
    if pol:
        signals.append(f"polarity={len(pol)}")
        gmn, tmn, at = pol[0]
        cands.append(("polarity", "high" if len(pol) * 2 >= words_off else "med",
                      f"got '{gmn}' vs tgt '{tmn}' @[{at}] (+{len(pol)} flips)"))

    # ---- block-order: only branch-displacement deltas (same mnem+regs, diff target) ----
    if pairs and all(
        g[0] in BRANCH and g[0] == t[0] and g[1] == t[1] and g[2] != t[2]
        for g, t, a, b in pairs
    ):
        signals.append("branch-displacement")
        g, t, a, b = pairs[0]
        cands.append(("block-order", "med",
                      f"all {len(pairs)} diffs are branch-displacement ('{g[0]}' {g[2]} vs {t[2]})"))

    # ---- reg-rename (R2 coloring): same opcodes, consistent register substitution ----
    if pairs:
        regmap: dict[str, str] = {}
        ok = True
        for g, t, a, b in pairs:
            if g[0] != t[0] or g[2] != t[2] or len(g[1]) != len(t[1]):
                ok = False
                break
            for ra, rb in zip(g[1], t[1]):
                if regmap.setdefault(ra, rb) != rb:
                    ok = False
                    break
            if not ok:
                break
        changed = {k: v for k, v in regmap.items() if k != v}
        if ok and changed and indels == 0:
            signals.append(f"regmap={len(changed)}")
            ev = ",".join(f"{k}->{v}" for k, v in list(changed.items())[:4])
            cands.append(("reg-rename", "high" if len(changed) >= 2 else "med",
                          f"consistent reg subst {{{ev}}} over {len(pairs)} words"))

    # ---- li-expansion: same-position immediate-load ENCODING variant (li vs addi,
    #      ori vs addiu, ...): same destination reg + same literal, different opcode ----
    imm_enc = {"li", "addi", "addiu", "ori"}
    enc = [(g, t, b) for g, t, a, b in pairs
           if g[0] in imm_enc and t[0] in imm_enc and g[0] != t[0]
           and g[1] and t[1] and g[1][0] == t[1][0]
           and g[2] and t[2] and g[2][-1] == t[2][-1]]
    if enc:
        signals.append(f"imm-enc={len(enc)}")
        g, t, b = enc[0]
        cands.append(("li-expansion", "high" if len(enc) * 2 >= words_off else "med",
                      f"imm-load encoding @[{b}] got '{g[0]}' vs tgt '{t[0]}' (same value)"))

    # ---- div-guard (LEAD 12b): the residue is an assembler div/rem TRAP GUARD, not a
    #      codegen difference.  maspsx omits it by default (expand_div=False) while
    #      genuine ASPSX 2.56 always emits it, so the words arrive as pure insertions
    #      -- and the guard's OWN words (li at,-1 / lui at,0x8000) then trip the
    #      li-expansion lui_delta test, which is exactly the misread this class fixes
    #      (func_803300DC was typed li-expansion while its own signals read
    #      drift-ins:+bnez,+nop,+break).  Owner is the ASSEMBLER DIAL: re-score with
    #      as_flags="--expand-div" BEFORE any C or maspsx spend (audit: aligned 18 ->
    #      0, byte-exact).  Ranked above li-expansion in `priority` below. ----
    tgt_guard, tgt_forms = div_guard_words(td, n)
    got_guard, got_forms = div_guard_words(gd, n)
    guard_ins = sorted(tgt_guard & ins_set)
    guard_del = sorted(got_guard & set(del_idx))
    if len(guard_ins) >= 3 or len(guard_del) >= 3:
        missing = len(guard_ins) >= len(guard_del)
        forms = tgt_forms if missing else got_forms
        cover, side = ((guard_ins, ins_idx) if missing else (guard_del, del_idx))
        signals.append("div-guard=%d(%s)" % (len(forms), ",".join(sorted(set(forms)))))
        # "high" only when the guard explains the WHOLE one-sided drift and nothing
        # was substituted: a shorter got also shows the guard's own length shortfall
        # on the other side, so `indels` is the wrong denominator here.
        full = not subs and set(side) <= (tgt_guard if missing else got_guard)
        cands.append((
            "div-guard", "high" if full else "med",
            ("tgt carries %d div/rem trap-guard expansion(s) [%s] our maspsx omits "
             "(expand_div=False); %d of %d inserted words are guard words -- re-score "
             "with as_flags=\"--expand-div\" before any C/maspsx spend"
             if missing else
             "got carries %d div/rem trap-guard expansion(s) [%s] retail does NOT; "
             "%d of %d deleted words are guard words -- drop the --expand-div as-flag "
             "on this row")
            % (len(forms), ",".join(forms), len(cover), len(side))))

    # ---- li-expansion: 1-word imm (addiu/ori/li) vs 2-word lui+ori for same value ----
    ins_mn = Counter(ti(j)[0] for j in ins_idx)
    del_mn = Counter(gi(i)[0] for i in del_idx)
    lui_delta = ins_mn["lui"] - del_mn["lui"]
    if indels and abs(lui_delta) and (ins_mn["ori"] or del_mn["ori"]
                                      or ins_mn["addiu"] or del_mn["addiu"]
                                      or ins_mn["li"] or del_mn["li"]):
        side = "tgt" if lui_delta > 0 else "got"
        signals.append(f"lui_delta={lui_delta}")
        cands.append(("li-expansion", "med",
                      f"{side} carries {abs(lui_delta)} extra lui vs 1-word imm (ori/addiu/li)"))

    # ---- const-remat (R2c): same constant materialized more times on one side ----
    def mat_counts(dis: dict[int, str]) -> Counter:
        c: Counter = Counter()
        for txt in dis.values():
            if (txt or "").startswith(("lui ", "li ", "ori ")):
                c[txt] += 1
        return c
    gmat, tmat = mat_counts(gd), mat_counts(td)
    remat = [(k, gmat[k], tmat.get(k, 0)) for k in gmat
             if gmat[k] > tmat.get(k, 0) and gmat[k] >= 2]
    if remat:
        signals.append(f"remat={len(remat)}")
        k, gc, tc = max(remat, key=lambda x: x[1] - x[2])
        cands.append(("const-remat", "med",
                      f"got materializes '{k}' {gc}x vs tgt {tc}x"))

    # ---- hold-set (R2 LICM): frame-size delta and/or callee-save count delta ----
    gf, tf = _frame_size(gd), _frame_size(td)
    gs, ts = _saved_count(gd), _saved_count(td)
    if (gf is not None and tf is not None and gf != tf) or gs != ts:
        frame_differs = gf is not None and tf is not None and gf != tf
        # E4: with the frame sizes EQUAL (or unknown) and only the callee-save COUNT
        # differing, hold-set is unreliable -- 8046847C@15 was really a slot rotation.
        # Demote to low so consumers do not trust the class (effective_class et al.).
        hs_conf = "med" if frame_differs else "low"
        signals.append(f"frame={gf}/{tf},saved={gs}/{ts}")
        cands.append(("hold-set", hs_conf,
                      f"frame {gf} vs {tf}; callee-saves {gs} vs {ts} (LICM hold-set delta)"))

    # ---- addressing: %hi/%lo vs gp vs indexed base differences in loads/stores ----
    addr = [(g, t, b) for g, t, a, b in pairs
            if g[0] == t[0] and g[0] in LOADSTORE and g[1] != t[1]
            and ("gp" in g[1] or "gp" in t[1] or g[2] != t[2])]
    if addr:
        signals.append(f"addressing={len(addr)}")
        g, t, b = addr[0]
        cands.append(("addressing", "med",
                      f"load/store base/form differs @[{b}] ('{g[0]}' {g[1]}{g[2]} vs {t[1]}{t[2]})"))

    # ---- length-drift / code-motion (E5): insertion/deletion misalignment dominates.
    #      When the generated word count equals the target's, the indels are pure code
    #      MOTION (a balanced move), not a genuine length change -> class "code-motion";
    #      a real shortfall (got shorter than tgt) stays "length-drift".  ALWAYS surface
    #      the drifting mnemonics as SIGNALS (nop-drift vs lui-drift vs load/store motion
    #      route differently -- the old length-drift bucket was opaque). ----
    if indels and indels >= max(1, len(subs)):
        top_ins = [f"+{ti(j)[0]}" for j in ins_idx[:3]]
        top_del = [f"-{gi(i)[0]}" for i in del_idx[:3]]
        signals.append(f"indels={indels}(ins{len(ins_idx)}/del{len(del_idx)})")
        signals.append("drift-ins:" + ",".join(top_ins))
        signals.append("drift-del:" + ",".join(top_del))
        equal_len = len(got) == len(tgt)
        drift_cls = "code-motion" if equal_len else "length-drift"
        kind = "equal-length motion" if equal_len else "net length change"
        cands.append((drift_cls, "med" if indels >= 2 else "low",
                      f"{indels} indel words ({kind}, subs={len(subs)}); "
                      f"{' '.join(top_ins)} {' '.join(top_del)}".strip()))

    # ---- dead-word (E7): a tgt-side INSERTED const-mat/move whose destination register
    #      is redefined before any read is a retained dead word (ASM_KEEP measurably
    #      overfires on these).  Emit signal "dead-word" + secondary "dead-code-retention"
    #      -> maspsx-lead/park review, never an auto-spent wave/permuter slot. ----
    dead_words: list[tuple[int, str]] = []
    for j in ins_idx:
        mn, regs, _imm = ti(j)
        if mn in CONSTMAT and regs and _dead_before_redef(td, j, regs[0], n):
            dead_words.append((j, mn))
    if dead_words:
        signals.append(f"dead-word={len(dead_words)}")
        j0, _mn0 = dead_words[0]
        cands.append(("dead-code-retention", "med",
                      f"{len(dead_words)} tgt-side dead const-mat/move word(s) "
                      f"(no consumer before redefinition); e.g. [{j0}] '{td.get(j0*4,'')}'"))

    # ---- delay-slot (E8): diffs confined to the word AFTER a branch/jump where one side
    #      is a nop and the other a real insn -> a maspsx delay-slot fill/steal (SHAPE-A/C),
    #      not a wave shape.  Signal always; promote to a primary-worthy class only when
    #      ALL diffs are delay-slot (confined).  Routes az-maspsx-lead/finisher. ----
    def _is_nop(dis: dict[int, str], i: int) -> bool:
        return (dis.get(i * 4) or "").strip() in ("nop", "")

    ds = [i for i in diff_idx if i > 0
          and (parse_insn(gd.get((i - 1) * 4))[0] in CTRL
               or parse_insn(td.get((i - 1) * 4))[0] in CTRL)
          and (_is_nop(gd, i) or _is_nop(td, i))]
    # Surface only when the residue IS a delay-slot lead: either fully confined to
    # delay slots (-> primary-worthy class), or delay-slot diffs dominate (>= half, min
    # 2).  Incidental delay-slot nops inside a larger code-motion residue are not a
    # maspsx lead, and an over-broad signal is useless as an instrument selector.
    if ds:
        confined = len(ds) == words_off
        if confined or len(ds) >= max(2, (words_off + 1) // 2):
            signals.append(f"delay-slot={len(ds)}")
        if confined:
            cands.append(("delay-slot", "high",
                          f"all {len(ds)} diff word(s) are nop-vs-insn in a branch/jump "
                          f"delay slot (e.g. [{ds[0]}])"))

    # ---- selection: fixed specificity priority; primary + one distinct secondary ----
    # dead-code-retention is deliberately LAST: E7 makes it a SECONDARY marker (route
    # to maspsx-lead/park review), it must never outrank even the code-motion fallback.
    priority = ["extent-prefix", "delay-slot", "slot-rotation", "reorder-only",
                "polarity", "block-order", "reg-rename", "div-guard", "li-expansion",
                "const-remat", "hold-set", "addressing", "code-motion",
                "length-drift", "dead-code-retention"]
    conf_rank = {"high": 0, "med": 1, "low": 2}

    def _sort_key(c: tuple[str, str, str]) -> tuple[int, int]:
        cls_name, conf, _ev = c
        pri = priority.index(cls_name)
        # E6: a partial-cover slot-rotation (confidence != high) must NOT be primary --
        # push it below every named class so a real residue class is promoted and the
        # rotation falls through to secondary (classifier-side mirror of the G4 demotion
        # in wave_pack_common.effective_class; keep the two consistent).
        if cls_name == "slot-rotation" and conf != "high":
            pri = len(priority)
        return (pri, conf_rank[conf])

    cands.sort(key=_sort_key)

    if not cands:
        return {"class": "broad", "confidence": "low",
                "evidence": f"{words_off} words off, no named signal (C-shape/R10); "
                            f"indels={indels} subs={len(subs)}",
                "secondary": None, "words_off": words_off, "signals": signals}

    primary = cands[0]
    secondary = next((c for c in cands[1:] if c[0] != primary[0]), None)
    secondary_cls = secondary[0] if secondary else None
    # E7: surface the actionable dead-code-retention marker as the secondary when the
    # only class outranking it for that slot is the opaque code-motion/length-drift
    # fallback (or nothing) -- a dead-word finding is a concrete maspsx-lead/park route,
    # more useful than "some indel drift". The primary is never disturbed (dead words are
    # insertions, so a drift class always outranks dead-code-retention for primary).
    if (any(s.startswith("dead-word=") for s in signals)
            and primary[0] != "dead-code-retention"
            and secondary_cls in (None, "code-motion", "length-drift")):
        secondary_cls = "dead-code-retention"
    return {
        "class": primary[0], "confidence": primary[1], "evidence": primary[2],
        "secondary": secondary_cls,
        "words_off": words_off, "signals": signals,
    }

# ---------------------------------------------------------------------------- batch

def load_rows(overlay: str) -> list[dict[str, Any]]:
    path = ROOT / f"overlays/{overlay}/overlay_first_pass_results.json"
    with path.open() as f:
        return json.load(f)


def candidate_rows(overlay: str, max_words: int) -> list[dict[str, Any]]:
    """NOMATCH rows with words_off<=max_words and an existing candidate C on disk."""
    out = []
    for row in load_rows(overlay):
        if row.get("rerun"):
            continue
        if row.get("result") != "NOMATCH":
            continue
        if int(row.get("words_off", 999)) > max_words:
            continue
        cp = row.get("c_path")
        if not cp:
            continue
        cpath = Path(cp)
        if not cpath.is_absolute():
            cpath = ROOT / cpath
        if not cpath.exists():
            continue
        out.append(row)
    return out


def _task(job: tuple[str, dict[str, Any], bool]) -> dict[str, Any]:
    overlay, row, do_class = job
    func = row["func_vram"]
    rec: dict[str, Any] = {"overlay": overlay, "func": func,
                           "words_off_recorded": row.get("words_off"),
                           "config": row.get("config")}
    try:
        res = compile_words(overlay, row, row["c_path"], row.get("config"))
    except Exception as exc:  # never let one bad row kill the pool
        rec.update(status="ERROR", note=repr(exc)[:160])
        return rec
    rec["status"] = res["status"]
    if res["status"] == "CFAIL":
        rec["note"] = res.get("err", "")
        return rec
    rec["words_off"] = res["words_off"]
    if res["status"] == "MATCH":
        return rec
    if res.get("link_fail"):
        # relocs read 0 -> the word diff is phantom; do not pretend to classify it.
        rec.update({"class": "linkfail", "confidence": "low",
                    "evidence": "ld fallback to UNLINKED object; word diff is phantom",
                    "secondary": None, "signals": ["link_fail"]})
        return rec
    if do_class:
        cl = classify(res["got"], res["tgt"])
        rec.update(**{k: cl[k] for k in ("class", "confidence", "evidence",
                                         "secondary", "signals")})
    return rec


def run_batch(overlays: list[str], max_words: int, workers: int,
              do_class: bool) -> list[dict[str, Any]]:
    jobs = [(ov, row, do_class)
            for ov in overlays for row in candidate_rows(ov, max_words)]
    print(f"residue_class: {len(jobs)} rows over {overlays} (<= {max_words} words), -j{workers}",
          file=sys.stderr)
    results = []
    if workers <= 1:
        for j in jobs:
            results.append(_task(j))
    else:
        with ProcessPoolExecutor(max_workers=workers) as ex:
            for r in ex.map(_task, jobs):
                results.append(r)
    return results

# ---------------------------------------------------------------------------- CLI

def main() -> int:
    ap = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--overlay", choices=OVERLAYS)
    ap.add_argument("--func")
    ap.add_argument("--c-file")
    ap.add_argument("--match-config")
    ap.add_argument("--batch", action="store_true",
                    help="classify every candidate row in the overlay(s)")
    ap.add_argument("--all", action="store_true", help="all five overlays (batch)")
    ap.add_argument("--max-words", type=int, default=8,
                    help="only rows with words_off <= this (default 8)")
    ap.add_argument("-j", "--workers", type=int, default=6)
    ap.add_argument("--out", default=None, help="write jsonl (batch mode)")
    a = ap.parse_args()

    if a.batch:
        overlays = list(OVERLAYS) if a.all else [a.overlay]
        if not overlays or overlays == [None]:
            ap.error("batch mode needs --overlay or --all")
        results = run_batch(overlays, a.max_words, a.workers, do_class=True)
        if a.out:
            outp = Path(a.out)
            if not outp.is_absolute():
                outp = ROOT / outp
            outp.parent.mkdir(parents=True, exist_ok=True)
            with outp.open("w") as f:
                for r in results:
                    f.write(json.dumps(r) + "\n")
            print(f"wrote {len(results)} rows -> {outp}", file=sys.stderr)
        dist = Counter(r.get("class", r["status"]) for r in results)
        print("class distribution:", dict(dist.most_common()))
        return 0

    # single-function mode
    if not (a.overlay and a.func and a.c_file):
        ap.error("single mode needs --overlay --func --c-file")
    row = OFC.find_row(a.func, a.overlay)
    res = compile_words(a.overlay, row, a.c_file, a.match_config)
    print(f"{res['status']} {a.func} words_off={res.get('words_off','-')}")
    if res["status"] == "NOMATCH":
        cl = classify(res["got"], res["tgt"])
        print(f"  class={cl['class']} ({cl['confidence']})"
              f" secondary={cl['secondary']}")
        print(f"  evidence: {cl['evidence']}")
        print(f"  signals:  {cl['signals']}")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
