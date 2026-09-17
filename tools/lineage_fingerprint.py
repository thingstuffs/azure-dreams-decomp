#!/usr/bin/env python3
"""Scan retail bytes for compiler-lineage provenance signatures.

This clean-tree copy is adapted from reference ``tools/lineage_fingerprint.py``
(SHA-256 ``0bea8aadef1587db64d6b9d4471f85fba992e8c9579d5664f867f98710fc333e``).
It resolves overlay rows through the clean ledger and retail containers.  A store
scheduled in a ``jal``/``j`` delay slot is reported as scheduling evidence only:
stock GCC 2.7.2 can place an ordinary object-local store there, so that signature
does not select a compiler family or cause a claimed-lineage conflict.

Capstone is intentionally not installed in the clean virtualenv.  Run with the
reference environment, for example::

  <reference-repo>/.venv/bin/python tools/lineage_fingerprint.py \
      func_819A764C --overlay dungeon --claimed 2.7.2

Rows with data before the compiled function can select the instruction body with
``--body-offset`` and optional ``--body-size`` (both accept decimal or ``0x``).

Exit codes: 0 = no conflict, 2 = claimed lineage conflicts with byte evidence.
"""
from __future__ import annotations

import argparse
from dataclasses import dataclass
from pathlib import Path
import re
from typing import Mapping, Sequence

from common import ROOT, rows

try:
    from capstone import Cs, CS_ARCH_MIPS, CS_MODE_LITTLE_ENDIAN, CS_MODE_MIPS32
except ImportError:  # Keep --help and the pure classifier usable in cleanvenv.
    Cs = None
    CS_ARCH_MIPS = CS_MODE_LITTLE_ENDIAN = CS_MODE_MIPS32 = None


STORES = {"sb", "sh", "sw", "swl", "swr"}
LOADS = {"lb", "lbu", "lh", "lhu", "lw", "lwl", "lwr"}
TEMPS = {"$v0", "$v1", "$a0", "$a1", "$a2", "$a3",
         "$t0", "$t1", "$t2", "$t3", "$t4", "$t5", "$t6", "$t7", "$t8", "$t9"}
SAVED = {"$s0", "$s1", "$s2", "$s3", "$s4", "$s5", "$s6", "$s7", "$fp"}
CALLER_CLOBBERED = TEMPS | {"$ra"}
MEMRE = re.compile(r"\((\$\w+)\)")

FAMILY_A = "<=2.7.2-family"
FAMILY_B = "cdk/2.8.x-family"

CONTAINER_FILES = {
    "main": "MAIN_MAIN.BIN",
    "town": "TOWN_TOWN.BIN",
    "dungeon": "DUNGEON_DUNGEON.BIN",
    "dungeon_engine": "DUNGEON_DUNGEON.BIN",
    "ovmovie": "OVMOVIE.BIN",
}


@dataclass(frozen=True)
class Classification:
    """Pure family decision derived from a scan's evidence map."""

    verdict: str
    family: str | None
    notes: tuple[str, ...] = ()


def back_edge_regions(ins: Sequence[tuple[str, str]]) -> list[tuple[int, int]]:
    """Return inclusive instruction-index ranges covered by backward branches.

    Capstone disassembles at address zero, so a direct branch's final operand is
    its byte offset within ``ins``.  Zero propagation is intentionally linear;
    conservatively suppress zero-copy evidence within every natural back edge.
    This guard is retained from the reference implementation.
    """
    regions = []
    for i, (mn, ops) in enumerate(ins):
        if not mn.startswith("b") or mn == "break":
            continue
        target_text = ops.rsplit(",", 1)[-1].strip()
        try:
            target_addr = int(target_text, 0)
        except ValueError:
            continue
        if target_addr % 4:
            continue
        target_i = target_addr // 4
        if 0 <= target_i < i:
            regions.append((target_i, i))
    return regions


def in_back_edge_region(index: int, regions: Sequence[tuple[int, int]]) -> bool:
    return any(start <= index <= end for start, end in regions)


def dest_reg(mn: str, ops: str) -> str | None:
    """Return the register written by an instruction (approximate)."""
    if mn in STORES or mn.startswith("b") or mn in (
            "j", "jr", "nop", "mult", "multu", "div", "divu", "sync", "break"):
        return None
    if mn in ("jal", "jalr", "bal"):
        return "$ra"
    first = ops.split(",")[0].strip() if ops else None
    return first if first and first.startswith("$") else None


def is_div_guard_lui(ins: Sequence[tuple[str, str]], i: int) -> bool:
    """Exclude the ``lui $at,0x8000`` constant in signed div/rem trap guards."""
    nxt = ins[i + 1] if i + 1 < len(ins) else ("", "")
    if nxt[0] in ("bne", "beq") and "$at" in nxt[1]:
        return True
    for k in range(max(0, i - 3), i):
        if ins[k][0] in ("addiu", "li") and re.match(
                r"\$at,\s*(\$zero,\s*)?-1$", ins[k][1]):
            return True
    return False


def parse_hi_imm(ops: str) -> int | None:
    match = re.match(r"\$\w+,\s*(-?0x[0-9a-f]+|\d+)$", ops)
    if not match:
        return None
    value = int(match.group(1), 0) & 0xFFFF
    return value if 0x8000 <= value <= 0x80FF else None


def scan(words_bytes: bytes):
    """Purely scan instruction bytes.

    Returns ``(instructions, evidence, held_pages, gp_refs)``.  ``slot_store``
    remains visible in ``evidence`` but is family-neutral in :func:`classify`.
    """
    if Cs is None:
        raise RuntimeError(
            "capstone is unavailable; run with <reference-repo>/.venv/bin/python")
    md = Cs(CS_ARCH_MIPS, CS_MODE_MIPS32 | CS_MODE_LITTLE_ENDIAN)
    ins = [(instruction.mnemonic, instruction.op_str)
           for instruction in md.disasm(words_bytes, 0)]
    loop_regions = back_edge_regions(ins)

    evidence = {key: [] for key in (
        "at_macro", "split_store", "held_page", "slot_store",
        "split_la", "zero_copy", "ret_copy")}
    gp_refs = 0
    last_lui = {}
    zero_regs = set()
    held_uses = {}
    held_done = []

    def finalize_held(reg):
        value = held_uses.pop(reg, None)
        if value and value[1] >= 2:
            held_done.append((reg, value[0], value[1]))

    for i, (mn, ops) in enumerate(ins):
        base = None
        match = MEMRE.search(ops)
        if match:
            base = match.group(1)
            if base == "$gp":
                gp_refs += 1

        if mn in STORES and base:
            if base == "$at":
                evidence["at_macro"].append(f"[{i}] {mn} {ops}")
            elif base in TEMPS and base in last_lui and i - last_lui[base][0] <= 6:
                evidence["split_store"].append(
                    f"[{last_lui[base][0]}] lui {base},0x{last_lui[base][1]:x} + "
                    f"[{i}] {mn} {ops}")
            if i > 0 and ins[i - 1][0] in ("jal", "j", "bal") and base != "$sp":
                evidence["slot_store"].append(
                    f"[{i - 1}] {ins[i - 1][0]} {ins[i - 1][1]} + [{i}] {mn} {ops}")
        if (mn in LOADS or mn in STORES) and base in held_uses:
            held_uses[base][1] += 1

        if (mn == "lui" and "$at" in ops.split(",")[0]
                and not is_div_guard_lui(ins, i)):
            evidence["at_macro"].append(f"[{i}] lui {ops}")

        if mn == "addiu" and i > 0 and ins[i - 1][0] == "lui":
            prev_dest = ins[i - 1][1].split(",")[0].strip()
            parts = [part.strip() for part in ops.split(",")]
            if len(parts) == 3 and parts[1] == prev_dest and parts[0] != prev_dest:
                evidence["split_la"].append(
                    f"[{i - 1}] lui {ins[i - 1][1]} + [{i}] addiu {ops}")

        if mn == "move":
            parts = [part.strip() for part in ops.split(",")]
            if (len(parts) == 2 and parts[1] in zero_regs
                    and not in_back_edge_region(i, loop_regions)):
                evidence["zero_copy"].append(
                    f"[{i}] move {ops} ({parts[1]} known zero)")
            if len(parts) == 2 and parts[1] == "$v0" and i >= 2 \
                    and ins[i - 2][0] in ("jal", "jalr"):
                evidence["ret_copy"].append(f"[{i}] move {ops} after call")

        dest = dest_reg(mn, ops)
        if dest:
            last_lui.pop(dest, None)
            zero_regs.discard(dest)
            finalize_held(dest)
        if mn == "lui":
            high = parse_hi_imm(ops)
            if high is not None and dest:
                last_lui[dest] = (i, high)
                if dest in SAVED:
                    held_uses[dest] = [i, 0]
        if mn == "move" and dest:
            source = ops.split(",")[1].strip()
            if source == "$zero" or source in zero_regs:
                zero_regs.add(dest)
        if mn in ("addiu", "ori", "li"):
            parts = [part.strip() for part in ops.split(",")]
            if (len(parts) == 3 and parts[1] == "$zero"
                    and parts[2] in ("0", "0x0") and dest):
                zero_regs.add(dest)
        if mn in ("jal", "jalr"):
            zero_regs -= CALLER_CLOBBERED
            for reg in list(last_lui):
                if reg in CALLER_CLOBBERED:
                    del last_lui[reg]

    for reg in list(held_uses):
        finalize_held(reg)
    held = [f"[{index}] lui {reg} ({count} uses)"
            for reg, index, count in held_done]
    return ins, evidence, held, gp_refs


def classify(evidence: Mapping[str, Sequence[str]]) -> Classification:
    """Purely classify scan evidence without considering any claimed lineage."""
    n_at = len(evidence.get("at_macro", ()))
    n_split = len(evidence.get("split_store", ()))
    notes = []
    if evidence.get("slot_store"):
        notes.append("store-filled call/jump slots (observed scheduling; family-neutral)")
    if evidence.get("split_la"):
        notes.append("SPLIT_ADDRESSES two-reg la (cdk/4.1-lineage)")
    if evidence.get("ret_copy"):
        notes.append("return-copy habit (plain-2.7.2 trait)")

    if n_at and n_split:
        return Classification(
            "MIXED dialect (hybrid; route to az-wall-deconstruct; cf. 8003E758)",
            None, tuple(notes))
    if n_split or len(evidence.get("zero_copy", ())) >= 2:
        return Classification(f"{FAMILY_B} store emission/cse habits", FAMILY_B, tuple(notes))
    if n_at:
        return Classification(f"{FAMILY_A} store emission (assembler macros)",
                              FAMILY_A, tuple(notes))
    return Classification("insufficient store-emission evidence (few globals?)",
                          None, tuple(notes))


def classify_claim(text: str) -> str | None:
    lowered = text.lower()
    if any(key in lowered for key in ("2.8", "cdk", "4.1", "2.9")):
        return FAMILY_B
    if any(key in lowered for key in ("2.6", "2.7", "4.0")):
        return FAMILY_A
    return None


def body_slice(raw: bytes, offset: int = 0, size: int | None = None) -> bytes:
    """Return a validated, word-aligned instruction-body slice."""
    if offset < 0 or offset % 4:
        raise ValueError("body offset must be a non-negative multiple of 4")
    if size is None:
        size = len(raw) - offset
    if size < 0 or size % 4:
        raise ValueError("body size must be a non-negative multiple of 4")
    if offset > len(raw) or offset + size > len(raw):
        raise ValueError(
            f"body slice [{offset}, {offset + size}) exceeds {len(raw)} retail bytes")
    return raw[offset:offset + size]


def _resolve_overlay(func: str, overlay: str) -> dict:
    candidates = [row for row in rows()
                  if row.get("func") == func and row.get("kind") == "overlay"
                  and row.get("container") == overlay]
    if not candidates:
        raise ValueError(f"{func} not found in clean overlay ledger for {overlay}")
    if len(candidates) != 1:
        raise ValueError(f"{func} has {len(candidates)} clean ledger rows in overlay {overlay}")
    row = candidates[0]
    filename = CONTAINER_FILES.get(row["container"])
    if filename is None:
        raise ValueError(f"no retail-container mapping for {row['container']!r}")
    container = ROOT / "work" / "disc" / "containers" / filename
    if not container.exists():
        raise ValueError(f"retail container missing: {container}")
    return {"kind": "overlay", "overlay": row["container"], "row": row,
            "container": container, "foff": int(row["foff"]), "size": int(row["size"])}


def resolve_target(func: str, overlay: str | None = None) -> dict:
    """Resolve an explicit overlay target without importing ``az_target``."""
    if not overlay:
        raise ValueError("--overlay is required (this tool resolves overlay rows only)")
    return _resolve_overlay(func, overlay)


def retail_bytes(target: Mapping[str, object]) -> bytes:
    with Path(target["container"]).open("rb") as source:
        source.seek(int(target["foff"]))
        raw = source.read(int(target["size"]))
    if len(raw) != int(target["size"]):
        raise ValueError(
            f"short retail read: wanted {target['size']} bytes, got {len(raw)}")
    return raw


def _integer(text: str) -> int:
    return int(text, 0)


def main(argv: Sequence[str] | None = None) -> int:
    parser = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    parser.add_argument("func")
    parser.add_argument("--overlay", required=True)
    parser.add_argument("--claimed", help="lineage attribution to check, e.g. 2.7.2-family")
    parser.add_argument("--body-offset", type=_integer, default=0,
                        help="skip a data prefix before scanning (bytes; decimal or 0x)")
    parser.add_argument("--body-size", type=_integer,
                        help="scan this many body bytes (decimal or 0x; default: remainder)")
    parser.add_argument("--evidence", type=int, default=3,
                        help="evidence lines per signature")
    args = parser.parse_args(argv)

    try:
        target = resolve_target(args.func, overlay=args.overlay)
        whole_raw = retail_bytes(target)
        raw = body_slice(whole_raw, args.body_offset, args.body_size)
        _ins, evidence, held, gp_refs = scan(raw)
    except (RuntimeError, ValueError) as exc:
        parser.error(str(exc))

    where = f"overlay {target['overlay']}"
    body = ""
    if args.body_offset or args.body_size is not None:
        body = f", body +0x{args.body_offset:X}..+0x{args.body_offset + len(raw):X}"
    print(f"== lineage fingerprint: {args.func} ({where}, {len(raw) // 4} words{body}) ==")

    def show(label, items):
        head = "; ".join(items[:args.evidence])
        print(f"{label:26s} {len(items):3d}   {head}")

    show("$at macro stores", evidence["at_macro"])
    show("compiler-split stores", evidence["split_store"])
    show("held-page bases (s-reg)", held)
    show("store in jal/j slot", evidence["slot_store"])
    show("two-reg split la", evidence["split_la"])
    show("zero-equiv copies", evidence["zero_copy"])
    show("return-copy after call", evidence["ret_copy"])
    print(f"{'$gp refs':26s} {gp_refs:3d}")

    decision = classify(evidence)
    suffix = "; " + "; ".join(decision.notes) if decision.notes else ""
    print(f"VERDICT: {decision.verdict}{suffix}")

    if args.claimed and decision.family:
        claimed_family = classify_claim(args.claimed)
        if claimed_family and claimed_family != decision.family:
            print(f"\nLINEAGE CONFLICT: claimed '{args.claimed}' ({claimed_family}) but the "
                  f"bytes say {decision.family}. Re-derive the attribution before iterating C.")
            return 2
        print(f"claimed '{args.claimed}' is consistent with the byte evidence")
    elif args.claimed:
        print(f"claimed '{args.claimed}' cannot be tested from family-neutral/insufficient evidence")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
