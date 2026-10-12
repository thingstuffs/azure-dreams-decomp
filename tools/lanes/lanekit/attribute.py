#!/usr/bin/env python3
"""Attribute every aligned raw-word difference to the last deciding GCC pass.

The input is compiled once with -dap/-da.  Assembly UID comments bind emitted
words to RTL insns; value_luid's stable-UID history binds those insns to pass
snapshots.  Register-only, frame-offset, and delay-slot differences receive
their more specific downstream owner.  Results are diagnostic and non-stageable.
"""
from __future__ import annotations

import argparse
import collections
import difflib
import json
import re
from pathlib import Path

import kitlib
import oracle_search
import pass_oracle
import sncheck
import value_luid

PHASE_NAME = {
    "rtl": "expand/rtl",
    "jump": "jump1",
    "cse": "cse1",
    "loop": "loop",
    "cse2": "cse2",
    "flow": "flow",
    "combine": "combine",
    "sched": "sched1",
    "lreg": "local allocation",
    "greg": "global allocation",
    "sched2": "reload/sched2",
    "jump2": "jump2 cross-jump",
    "dbr": "reorg/delay-slot",
}
UID_COMMENT = re.compile(r"#\s*(\d+)\s+[A-Za-z0-9_./-]+\s*$")
MACHINE = re.compile(r"^\s*([A-Za-z][A-Za-z0-9_.]*)\s+(.*?)\s*$")


def _integer(token):
    token = token.strip().split()[0]
    try:
        return int(token, 0)
    except ValueError:
        return None


def expansion_words(mnemonic, operands):
    """Number of MIPS words emitted by the small pseudo set used by cc1."""
    mnemonic = mnemonic.lower()
    if mnemonic == "li":
        value = _integer(operands.rsplit(",", 1)[-1])
        if value is None:
            return 2
        value &= 0xFFFFFFFF
        signed = value if value < 0x80000000 else value - 0x100000000
        return 1 if -32768 <= signed <= 32767 or value <= 0xFFFF or value & 0xFFFF == 0 else 2
    if mnemonic in ("la", "dla"):
        return 2
    return 1


def asm_word_map(asm, byte_words):
    """Return one assembly/UID record per candidate word, with explicit gaps."""
    out = []
    for line in asm.splitlines():
        code = line.split("#", 1)[0].strip()
        if not code or code.startswith((".", "#")) or code.endswith(":"):
            continue
        match = MACHINE.match(code)
        if not match:
            continue
        mnemonic, operands = match.groups()
        uid_match = UID_COMMENT.search(line)
        uid = int(uid_match.group(1)) if uid_match else None
        for part in range(expansion_words(mnemonic, operands)):
            out.append({"uid": uid, "asm": code, "expansion_part": part})
    # A mismatch is retained as evidence instead of silently shifting UIDs.
    if len(out) < byte_words:
        out.extend({"uid": None, "asm": None, "expansion_part": None} for _ in range(byte_words - len(out)))
    return out[:byte_words], {"mapped_words": min(len(out), byte_words), "assembly_words": len(out), "binary_words": byte_words}


def _word_register_only(a, b):
    mask, fields = oracle_search.word_regs(a)
    return bool(fields) and oracle_search.word_regs(b)[0] == mask and (a & ~mask) == (b & ~mask)


def _frame_offset_only(a, b):
    op_a, op_b = a >> 26, b >> 26
    base_a, base_b = (a >> 21) & 31, (b >> 21) & 31
    return op_a == op_b and 0x20 <= op_a <= 0x3F and base_a == base_b and base_a in (29, 30) and (a & 0xFFFF) != (b & 0xFFFF)


def _last_uid_pass(uid, dumps):
    if uid is None:
        return "expand/rtl", []
    history = value_luid.transitions(dumps, uid)
    last = None
    previous = None
    for item in history:
        if item.get("pattern") is None:
            last = item["pass"]
        elif previous is None or item.get("pattern") != previous:
            last = item["pass"]
        if item.get("pattern") is not None:
            previous = item["pattern"]
        if "moved at" in item.get("event", ""):
            last = item["pass"]
    return PHASE_NAME.get(last, last or "expand/rtl"), history


def _register_owner(uid, dumps):
    by_phase = {}
    for phase in ("lreg", "greg", "sched2"):
        hit = next((r for r in value_luid.records(dumps.get(phase, "")) if r["uid"] == uid), None)
        by_phase[phase] = hit and hit["pattern"]
    if by_phase["greg"] and by_phase["sched2"] and by_phase["greg"] != by_phase["sched2"]:
        return "reload/register-choice"
    if by_phase["lreg"] and by_phase["greg"] and by_phase["lreg"] != by_phase["greg"]:
        return "global allocation/register-choice"
    return "local/global allocation/register-choice"


def _control_word(word):
    op = word >> 26
    return op in (1, 2, 3, 4, 5, 6, 7) or op == 0 and (word & 0x3F) in (8, 9)


def attribute(row, text, out, timeout=180, source=True):
    out = Path(out).resolve()
    if not out.is_relative_to(kitlib.lane_dir()):
        raise ValueError("attribution output must be lane-owned")
    out.mkdir(parents=True, exist_ok=True)
    (out / ".ignore").write_text("*\n")
    dumps = kitlib.dumps(row, text, timeout=timeout, asm_names=True)
    if not dumps or dumps.get("error"):
        raise RuntimeError("dump compile failed: " + str((dumps or {}).get("error")))
    from common import parse_cfg
    import alloc_sim

    cell, _ = parse_cfg(row["cfg"])
    function = value_luid.main_function_name(row, text, alloc_sim.FIRST[cell])
    dumps = value_luid.function_dumps(dumps, function)
    raw = pass_oracle.raw_bytes(row, text, dumps["asm"], out / "raw")
    got = (out / "raw/forced.bin").read_bytes()
    retail = (out / "raw/retail.bin").read_bytes()
    got_words = [int.from_bytes(got[i:i + 4], "little") for i in range(0, len(got), 4)]
    retail_words = [int.from_bytes(retail[i:i + 4], "little") for i in range(0, len(retail), 4)]
    amap, coverage = asm_word_map(dumps["asm"], len(got_words))
    sources, source_note = value_luid.source_twin(row, text, dumps, timeout) if source else ({}, "source twin disabled")
    rows = []
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, got_words, retail_words, autojunk=False).get_opcodes():
        if tag == "equal":
            continue
        count = max(i2 - i1, j2 - j1)
        for n in range(count):
            ci = i1 + n if n < i2 - i1 else None
            ri = j1 + n if n < j2 - j1 else None
            meta = amap[ci] if ci is not None and ci < len(amap) else {"uid": None, "asm": None}
            uid = meta.get("uid")
            cw = got_words[ci] if ci is not None else None
            rw = retail_words[ri] if ri is not None else None
            owner, history = _last_uid_pass(uid, dumps)
            reason = "last observed UID creation/rewrite/move"
            if cw is not None and rw is not None and _frame_offset_only(cw, rw):
                owner, reason = "frame/assign_stack_local", "stack/frame-base displacement differs"
            elif cw is not None and rw is not None and _word_register_only(cw, rw):
                owner, reason = _register_owner(uid, dumps), "aligned opcode differs only in register fields"
            elif ci is not None and ci > 0 and _control_word(got_words[ci - 1]):
                owner, reason = "reorg/delay-slot", "word occupies a control-transfer delay slot"
            elif tag == "insert":
                neighbor = got_words[ci - 1] if ci and ci <= len(got_words) else None
                owner = "reorg/delay-slot" if neighbor is not None and _control_word(neighbor) else owner
                reason = "retail-only word; owner inferred from aligned neighboring UID"
            source_hit = next((sources.get((h["pass"], uid)) for h in reversed(history) if sources.get((h["pass"], uid))), None)
            rows.append({
                "candidate_word": ci,
                "retail_word": ri,
                "candidate_hex": "0x%08x" % cw if cw is not None else None,
                "retail_hex": "0x%08x" % rw if rw is not None else None,
                "alignment": tag,
                "uid": uid,
                "asm": meta.get("asm"),
                "pass": owner,
                "reason": reason,
                "source": source_hit,
                "history": history,
            })
    histogram = dict(sorted(collections.Counter(r["pass"] for r in rows).items()))
    rec = {
        "version": 1,
        "row": row["id"],
        "cfg": row["cfg"],
        "function": function,
        "counterfactual": False,
        "stageable": False,
        "reviewer": "pending",
        "raw": raw,
        "coverage": coverage,
        "source_evidence": source_note,
        "pass_histogram": histogram,
        "differences": rows,
    }
    (out / "attribution.json").write_text(json.dumps(rec, indent=2) + "\n")
    (out / "attribution.md").write_text(render(rec))
    return rec


def render(rec):
    lines = ["# Divergence attribution: " + rec["row"], "", "Raw aligned distance: %s. Reviewer pending; diagnostic only." % rec["raw"]["aligned_distance"], "", "## Pass histogram", ""]
    for name, count in rec["pass_histogram"].items():
        lines.append("- %s: %d word(s)" % (name, count))
    lines += ["", "## Deciding words", "", "| candidate | retail | uid | pass | instruction | reason |", "|---:|---:|---:|---|---|---|"]
    for row in rec["differences"]:
        lines.append("| %s | %s | %s | %s | `%s` | %s |" % (
            row["candidate_hex"] or "missing", row["retail_hex"] or "missing", row["uid"] if row["uid"] is not None else "?",
            row["pass"], (row["asm"] or "unknown").replace("|", "/"), row["reason"].replace("|", "/")))
    return "\n".join(lines) + "\n"


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("row")
    parser.add_argument("text")
    parser.add_argument("--out", type=Path)
    parser.add_argument("--timeout", type=float, default=180)
    parser.add_argument("--no-source", action="store_true")
    args = parser.parse_args(argv)
    lane = kitlib.bootstrap()
    row = kitlib.row_of(args.row)
    text = sncheck.input_text(args.text, row, lane)
    out = args.out or lane / "attribution" / row["id"].replace("/", "__")
    rec = attribute(row, text, out, args.timeout, not args.no_source)
    print(json.dumps({"row": rec["row"], "words": len(rec["differences"]), "histogram": rec["pass_histogram"]}, indent=2))
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
