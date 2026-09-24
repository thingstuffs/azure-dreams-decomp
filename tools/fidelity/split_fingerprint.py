#!/usr/bin/env python3
"""Split-address fingerprint census over RETAIL words (toolchain fidelity plan, step 2; measurement only).

Question: which rows' retail bytes show compiler-level address splitting (gcc's `mips_split_addresses`
HIGH/LO_SUM path: 2.7.2-cdk -mgas, 2.8.0, 2.8.1, 2.91.66, 2.95.2), which 2.6.3 / 2.7.2 (no such path in
their mips.c) and genuine ASPSX (never splits an `la` macro) cannot produce?

Input words
  overlay rows : the scorer's retail slice, build_ovl/work/s3_splat/extract/<BIN>[foff : foff+size]
  slus rows    : baserom/slus_006.14 at each defined function's address/size (symbols from the linked
                 build_slus ELF, whose ._800 section is byte-identical to the baserom from 0x800)
  --mode reloc : the round-77 sceptic's detector, verbatim, over ledger/cache/slus_dis (pinned TU objects
                 WITH relocations) - the calibration run, slus only.

Detector (raw words, one record per `lui rX,P` with rX != $0; see docs/evidence/fidelity_step2_split_fingerprint.md)
  The walker follows the lui's value forward along the fall-through path (through delay slots, into the
  target of an unconditional in-function `b`/`j`, stopping after `jr`, dropping caller-saved carriers after
  a call, at most WINDOW steps) and records every LO user: `addiu rY,rC,lo` / load / store with base rC,
  where rC is rX or a register derived from it by `addu` (indexed access).
  classes (not fingerprints):
    at_macro   lui $at + access through $at        - an ASPSX macro (store/indexed); a splitting cc1 never uses $at
    int_ori    lui + ori user                        - an integer constant (cse fold + large_int split, every cell)
    page_only  lui with no LO user on the walked path  - a round integer used as a value, or a HIGH whose LO lies
                                                     off the path (another block): not counted either way
    orphan_high lui overwritten on straight-line code before any read (reported, not counted)
    nonram     LO target outside 0x80000000-0x801FFFFF (scratchpad/IO/other integers)
    macro_la   lui rX ; addiu rX,rX,lo   (adjacent, only user)
    macro_load lui rX ; l* rX,lo(rX)     (adjacent, only user)
    macro_idx  lui rX ; addu rX,rX,rI ; l* rX,lo(rX)
  fingerprint kinds (a HIGH may carry several):
    high_in_slot    the lui sits in a branch/jump delay slot (a macro never fits a slot)
    interleaved     an unrelated instruction between the lui and its first LO user
    slot_lo         the only thing between them is a branch/jump whose delay slot holds the LO (weak)
    lo_other_reg    addiu rY,rX,lo with rY != rX (LO_SUM into another register)
    load_other_reg  load rY,lo(rX) with rY != rX (the load macro uses its destination as the temporary)
    store_high_base store through a non-$at HIGH (the store macro always uses $at)
    shared_high     one lui feeds >= 2 LO users (a macro re-materialises); shared_multioff: distinct targets
  flags: funcaddr (an addiu target is a known function address), after_call (a call between HIGH and first LO),
         multi_symbol (the LO targets straddle a known symbol start: a page base shared by several symbols,
         the page-constant shape, reported as page_shared and NOT counted as a fingerprint).

    python3 tools/fidelity/split_fingerprint.py                     # all containers (resumable)
    python3 tools/fidelity/split_fingerprint.py --container slus --only slus/w_8003D92C
    python3 tools/fidelity/split_fingerprint.py --mode reloc        # sceptic calibration table (stdout)
    python3 tools/fidelity/split_fingerprint.py --validate          # raw detector vs slus relocations
"""
from __future__ import annotations
import argparse, bisect, collections, hashlib, json, mmap, os, re, subprocess, sys
from concurrent.futures import ProcessPoolExecutor
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, current_text, read_jsonl, write_jsonl, CACHE, LEDGER  # noqa: E402

DETECTOR = "sf-2"
WINDOW = 48
OUT = ROOT / "work/fidelity/split_fingerprint.jsonl"
TMP = ROOT / "work/fidelity/tmp2"
ELF = ROOT / "build_slus/build/slus_006.14.elf"
BASEROM = ROOT / "baserom/slus_006.14"
SLUS_VRAM, SLUS_FOFF = 0x8002D000, 0x800
EXTRACT = ROOT / "build_ovl/work/s3_splat/extract"
BINS = {"dungeon": "DUNGEON_DUNGEON.BIN", "town": "TOWN_TOWN.BIN", "main": "MAIN_MAIN.BIN", "ovmovie": "OVMOVIE.BIN"}
PAGE_PINS = ROOT / "work/native_lane/r77_fable_splitaddr/cands/page_pin_rows.txt"
SPLIT_CELLS = {"2.7.2-cdk", "2.8.0", "2.8.1", "2.91.66", "2.95.2"}
STRICT = ("high_in_slot", "interleaved", "lo_other_reg", "load_other_reg", "store_high_base", "shared_high")
KINDS = STRICT + ("slot_lo", "shared_multioff")
CALLER_SAVED = set(range(1, 16)) | {24, 25, 31}
RAM_LO, RAM_HI = 0x80000000, 0x80200000


def splitting(cell, flags):
    flags = flags or ""
    return cell in SPLIT_CELLS and "-mmips-as" not in flags and "-mno-split-addresses" not in flags


# ------------------------------------------------------------------ MIPS I decoder (what the walker needs)
LOADS = {32, 33, 34, 35, 36, 37, 38}          # lb lh lwl lw lbu lhu lwr
STORES = {40, 41, 42, 43, 46}                 # sb sh swl sw swr
CP_MEM = {50, 58}                             # lwc2 swc2 (base read only)


def dec(w):
    op = w >> 26
    return op, (w >> 21) & 31, (w >> 16) & 31, (w >> 11) & 31, w & 63, w & 0xFFFF


def sext(i):
    return i - 0x10000 if i & 0x8000 else i


def has_slot(w):
    op, rs, rt, rd, fn, imm = dec(w)
    return op in (1, 2, 3, 4, 5, 6, 7) or (op == 0 and fn in (8, 9))


def regs_rw(w):
    """(reads, writes) as sets of GPR numbers ($0 dropped)."""
    op, rs, rt, rd, fn, imm = dec(w)
    r, wr = set(), set()
    if op == 0:
        if fn in (0, 2, 3): r = {rt}; wr = {rd}
        elif fn in (4, 6, 7): r = {rs, rt}; wr = {rd}
        elif fn == 8: r = {rs}
        elif fn == 9: r = {rs}; wr = {rd}
        elif fn in (16, 18): wr = {rd}
        elif fn in (17, 19): r = {rs}
        elif fn in (24, 25, 26, 27): r = {rs, rt}
        elif fn >= 32: r = {rs, rt}; wr = {rd}
    elif op == 1:
        r = {rs}
        if rt in (16, 17): wr = {31}
    elif op == 3: wr = {31}
    elif op in (4, 5): r = {rs, rt}
    elif op in (6, 7): r = {rs}
    elif 8 <= op <= 14: r = {rs}; wr = {rt}
    elif op == 15: wr = {rt}
    elif op in (16, 18):
        if rs in (0, 2): wr = {rt}
        elif rs in (4, 6): r = {rt}
    elif op in LOADS:
        r = {rs} | ({rt} if op in (34, 38) else set()); wr = {rt}
    elif op in STORES: r = {rs, rt}
    elif op in CP_MEM: r = {rs}
    r.discard(0); wr.discard(0)
    return r, wr


def is_call(w):
    op, rs, rt, rd, fn, imm = dec(w)
    return op == 3 or (op == 0 and fn == 9) or (op == 1 and rt in (16, 17))


def next_pc(words, k, base):
    """After the branch/jump at k and its slot k+1: [indices to continue at] (None = stop)."""
    w = words[k]; op, rs, rt, rd, fn, imm = dec(w)
    if op == 0 and fn == 8:                                   # jr
        return None
    uncond_b = (op == 4 and rs == 0 and rt == 0) or (op == 1 and rt == 1 and rs == 0)
    if uncond_b:
        t = k + 1 + sext(imm)
        return t if 0 <= t < len(words) else None
    if op == 2:                                               # j
        if base is None: return None
        t = (((base + 4 * k) & 0xF0000000) | ((w & 0x3FFFFFF) << 2)) - base
        t //= 4
        return t if 0 <= t < len(words) else None
    return k + 2                                              # conditional branch / call: fall through


# ------------------------------------------------------------------ the raw-word walker
def _walk(words, i, k, rx, hi, base, slot_of_call):
    """Follow the value of `lui rx,hi` (at index i) from index k: LO users, value uses, the path walked."""
    n = len(words)
    carriers = {rx}
    users = []                   # (step, k, type, base, other_reg, target)
    steps = []                   # path indices visited (after the lui)
    value_use = ori = orphan = branch_seen = False
    call_seen_before_first = False
    if slot_of_call: carriers = carriers - CALLER_SAVED
    after_slot = None            # (successor, was_call) once a branch's delay slot has executed
    visited = set()
    while carriers and len(steps) < WINDOW and 0 <= k < n and k not in visited:
        visited.add(k)
        x = words[k]
        xop, xrs, xrt, xrd, xfn, ximm = dec(x)
        reads, writes = regs_rw(x)
        steps.append(k)
        creads = reads & carriers
        if creads:
            tgt = ((hi << 16) + sext(ximm)) & 0xFFFFFFFF
            if xop == 9 and xrs in carriers:                                  # addiu (LO_SUM)
                users.append((len(steps), k, "addiu", xrs, xrt, tgt))
            elif xop == 13 and xrs in carriers:                               # ori: integer
                ori = True
            elif (xop in LOADS or xop in STORES or xop in CP_MEM) and xrs in carriers:
                t = "load" if xop in LOADS else "store" if xop in STORES else "cpmem"
                users.append((len(steps), k, t, xrs, xrt, tgt))
                if xop in STORES and xrt in carriers:
                    value_use = True
            elif xop == 0 and xfn == 33 and len(creads) == 1 and not users:    # addu: indexed base
                carriers = carriers | {xrd}
                writes = writes - {xrd}
            else:
                value_use = True
        if is_call(x) and not users:
            call_seen_before_first = True
        if rx in writes and not creads and not users and not value_use and not branch_seen:
            orphan = True
        if has_slot(x):
            branch_seen = True
        carriers = carriers - writes
        if after_slot is not None:                 # x was a delay slot
            succ, was_call = after_slot; after_slot = None
            if was_call: carriers = carriers - CALLER_SAVED
            if succ is None: break
            k = succ
            continue
        if has_slot(x):
            after_slot = (next_pc(words, k, base), is_call(x))
        k += 1
    return {"users": users, "steps": steps, "value_use": value_use, "ori": ori, "orphan": orphan,
            "call_first": call_seen_before_first}


def scan(words, base=None, funcs=frozenset(), symstarts=()):
    """Classify every non-$0 lui in one function's words.  Returns a list of event dicts."""
    events = []
    n = len(words)
    for i, w in enumerate(words):
        op, rs, rt, rd, fn, imm = dec(w)
        if op != 15 or rt == 0:
            continue
        rx, hi = rt, imm
        in_slot = i > 0 and has_slot(words[i - 1])
        ev = {"i": i, "reg": rx, "hi": hi}
        if in_slot:
            # a HIGH in a delay slot: reorg filled the slot from the branch target (users there) or from the
            # fall-through; walk the taken path first, then the fall-through, keep the first that has LO users
            br = words[i - 1]; bop, brs, brt = dec(br)[:3]
            starts = []
            if bop in (4, 5, 6, 7) or (bop == 1 and brt in (0, 1)):
                starts.append(i + sext(dec(br)[5]))              # branch target: (i-1) + 1 + off
            nx = next_pc(words, i - 1, base)
            if nx is not None: starts.append(nx)
            st = None
            for k0 in starts:
                if 0 <= k0 < n:
                    st = _walk(words, i, k0, rx, hi, base, is_call(br))
                    if st["users"] or st["ori"]: break
            if st is None:
                st = {"users": [], "steps": [], "value_use": False, "ori": False, "orphan": False, "call_first": False}
        else:
            st = _walk(words, i, i + 1, rx, hi, base, False)
        users, steps, ori, orphan, call_seen_before_first = st["users"], st["steps"], st["ori"], st["orphan"], st["call_first"]
        # ---- classify
        tg = [u[5] for u in users]
        if rx == 1:
            ev["cls"] = "at_macro" if users and all(RAM_LO <= t < RAM_HI for t in tg) else ("int_ori" if ori else "at_other")
            events.append(ev); continue
        if ori:
            ev["cls"] = "int_ori"; events.append(ev); continue
        if not users:
            # orphan_high: overwritten on straight-line code before any read - half of a pair whose other half
            # is gone (only a compiler that emits HIGH as its own insn can leave one); page_only: a value use
            ev["cls"] = "orphan_high" if orphan and not in_slot else "page_only"; events.append(ev); continue
        if not all(RAM_LO <= t < RAM_HI for t in tg):
            ev["cls"] = "nonram"; ev["t"] = tg[0]; events.append(ev); continue
        ev["t"] = tg[0]
        first = users[0]
        if not in_slot and len(users) == 1 and first[0] == 1 and first[3] == rx and first[4] == rx and first[2] in ("addiu", "load"):
            ev["cls"] = "macro_la" if first[2] == "addiu" else "macro_load"; events.append(ev); continue
        if (not in_slot and len(users) == 1 and first[0] == 2 and first[2] == "load" and first[4] == first[3] == rx
                and steps and dec(words[steps[0]])[0] == 0 and dec(words[steps[0]])[4] == 33 and dec(words[steps[0]])[3] == rx):
            ev["cls"] = "macro_idx"; events.append(ev); continue
        kinds = set()
        if in_slot:
            kinds.add("high_in_slot")
        # instructions between lui and first user on the path (an indexing addu does not count)
        between = [steps[s] for s in range(first[0] - 1)]
        between = [b for b in between if not (dec(words[b])[0] == 0 and dec(words[b])[4] == 33 and (regs_rw(words[b])[0] & {rx}))]
        if between:
            if len(between) == 1 and has_slot(words[between[0]]) and first[1] == between[0] + 1:
                kinds.add("slot_lo")
            else:
                kinds.add("interleaved")
        for u in users:
            if u[2] == "addiu" and u[4] != u[3]: kinds.add("lo_other_reg")
            if u[2] == "load" and u[4] != u[3]: kinds.add("load_other_reg")
            if u[2] in ("store", "cpmem") and u[3] != 1: kinds.add("store_high_base")
        if len(users) >= 2:
            kinds.add("shared_high")
            if len(set(tg)) >= 2: kinds.add("shared_multioff")
        flags = []
        if any(u[2] == "addiu" and u[5] in funcs for u in users): flags.append("funcaddr")
        if call_seen_before_first: flags.append("after_call")
        lo_t, hi_t = min(tg), max(tg)
        if hi_t > lo_t and symstarts:
            j = bisect.bisect_right(symstarts, lo_t)
            if j < len(symstarts) and symstarts[j] <= hi_t:
                flags.append("multi_symbol")
        if not kinds:
            ev["cls"] = "macro_other"          # e.g. adjacent same-register pair that is not a pure macro shape
        else:
            ev["cls"] = "page_shared" if "multi_symbol" in flags else "fingerprint"
        ev["kinds"] = sorted(kinds); ev["flags"] = flags; ev["nusers"] = len(users)
        events.append(ev)
    return events


def strict_kinds(ev):
    return [k for k in ev.get("kinds", ()) if k in STRICT]


def summarise(events, where):
    """Row-level counts; `where(i)` renders a word index as an address string."""
    cls = collections.Counter(e["cls"] for e in events)
    kinds = collections.Counter(); ex = collections.defaultdict(list); flags = collections.Counter()
    fp = fp_data = weak = 0
    for e in events:
        if e["cls"] != "fingerprint":
            if e["cls"] in ("page_shared", "int_ori", "at_macro") and len(ex[e["cls"]]) < 3:
                ex[e["cls"]].append(where(e["i"]))
            continue
        for k in e["kinds"]:
            kinds[k] += 1
            if len(ex[k]) < 3: ex[k].append(where(e["i"]))
        for f in e["flags"]: flags[f] += 1
        if strict_kinds(e):
            fp += 1
            if "funcaddr" not in e["flags"]: fp_data += 1
        else:
            weak += 1
    return {"n_lui": len(events), "cls": dict(cls), "kinds": dict(kinds), "fpflags": dict(flags),
            "fp_highs": fp, "fp_data_highs": fp_data, "weak_highs": weak, "ex": dict(ex),
            "addr_highs": sum(v for k, v in cls.items() if k in ADDR_CLASSES)}


ADDR_CLASSES = ("fingerprint", "page_shared", "macro_la", "macro_load", "macro_idx", "macro_other", "at_macro")


# ------------------------------------------------------------------ material
_ELF = None
def elf_symbols():
    """{name: (addr, size|None)} from the linked SLUS ELF (first definition wins)."""
    global _ELF
    if _ELF is None:
        out = subprocess.run(["mipsel-linux-gnu-nm", "-S", str(ELF)], capture_output=True, text=True, check=True).stdout
        d = {}
        for l in out.splitlines():
            p = l.split()
            if len(p) == 4 and p[2] in "TtDdBbRr":
                d.setdefault(p[3], (int(p[0], 16), int(p[1], 16)))
            elif len(p) == 3 and p[1] in "TtDdBbRr":
                d.setdefault(p[2], (int(p[0], 16), None))
        _ELF = d
    return _ELF


def _masked_eq(sec, ws):
    """Pinned-object section words (with relocations) == retail words, relocation fields masked."""
    for x, y in zip(sec, ws):
        if not x[2]:
            if x[3] != y: return False
        elif x[2][0] == "R_MIPS_26":
            if (x[3] >> 26) != (y >> 26): return False
        elif (x[3] >> 16) != (y >> 16):
            return False
    return len(sec) == len(ws)


def slus_functions(row):
    """[(name, vram, nwords, section|None)] for every global function the row's linked TU object defines
    (build_slus/build/src/<tu>.o `T` symbols; address and size from the linked ELF).  `section` is the pinned
    object's section from ledger/cache/slus_dis when it aligns with retail under a relocation mask (the
    ground truth for symbol-vs-literal HIGHs), else None."""
    syms = elf_symbols()
    stem = Path(row["c_path"]).stem
    obj = ROOT / "build_slus/build/src" / f"{stem}.o"
    names = []
    if obj.exists():
        for l in subprocess.run(["mipsel-linux-gnu-nm", str(obj)], capture_output=True, text=True).stdout.splitlines():
            p = l.split()
            if len(p) == 3 and p[1] == "T": names.append(p[2])
    path = CACHE / "slus_dis" / f"{row['id'].split('/')[1]}.txt"
    secs = reloc_words(path) if path.exists() else []
    mm = container_bytes("slus")
    out = []
    for n in names:
        a, sz = syms.get(n, (None, None))
        if a is None or not sz or not (SLUS_VRAM <= a < SLUS_VRAM + 0x7F800):
            continue
        o = a - SLUS_VRAM + SLUS_FOFF
        ws = words_of(bytes(mm[o: o + sz]))
        sec = None
        for s_ in secs:
            if len(s_) >= len(ws) and _masked_eq(s_[:len(ws)], ws):
                sec = s_[:len(ws)]; break
        out.append((n, a, len(ws), sec))
    return sorted(out, key=lambda t: t[1])


def words_of(b):
    return [int.from_bytes(b[j:j + 4], "little") for j in range(0, len(b) - len(b) % 4, 4)]


_MM = {}
def container_bytes(container):
    if container not in _MM:
        p = BASEROM if container == "slus" else EXTRACT / BINS[container]
        f = open(p, "rb")
        _MM[container] = mmap.mmap(f.fileno(), 0, access=mmap.ACCESS_READ)
    return _MM[container]


def retail_slices(row):
    """[(label, vram|None, bytes)] for the row (slus: sections that could not be located are dropped)."""
    mm = container_bytes(row["container"])
    if row["kind"] == "slus":
        return [(n, a, bytes(mm[a - SLUS_VRAM + SLUS_FOFF: a - SLUS_VRAM + SLUS_FOFF + 4 * k]))
                for n, a, k, _ in slus_functions(row)]
    base = row.get("true_name") or row["func"]
    try: vram = int(base[5:], 16)
    except Exception: vram = None
    return [(row["func"], vram, bytes(mm[row["foff"]: row["foff"] + row["size"]]))]


def known_addresses():
    """({container: function addresses}, {container: sorted data-symbol starts}).  Overlay address spaces
    overlap each other and the SLUS tail, so both tables are per container: SLUS functions/data from the
    linked ELF; an overlay's functions from its rows (func/true_name), its data from the D_XXXXXXXX
    names its own sources use, plus SLUS data below 0x80080000 (the resident part)."""
    syms = elf_symbols()
    rs = rows()
    slus_defs = {x for r in rs if r["kind"] == "slus" for x in (r.get("defs") or [])}
    fslus = {a for n, (a, sz) in syms.items() if n.startswith("func_") or n in slus_defs}
    data_slus = {a for n, (a, sz) in syms.items() if RAM_LO <= a < RAM_HI and a not in fslus and not n.startswith("_")}
    funcs = {"slus": frozenset(fslus)}
    starts = {"slus": sorted(data_slus)}
    tok = re.compile(r"\bD_([0-9A-F]{8})\b")
    for c in BINS:
        f = {a for a in fslus if a < 0x80080000}
        for r in rs:
            if r["container"] == c:
                for n in (r.get("func"), r.get("true_name")):
                    if n and re.fullmatch(r"func_[0-9A-F]{8}", n): f.add(int(n[5:], 16))
        funcs[c] = frozenset(f)
        s_ = {a for a in data_slus if a < 0x80080000}
        d = ROOT / "src" / c
        if d.is_dir():
            for p_ in d.glob("*.c"):
                for m in tok.finditer(p_.read_text(errors="replace")):
                    a = int(m.group(1), 16)
                    if RAM_LO <= a < RAM_HI: s_.add(a)
        starts[c] = sorted(s_)
    return funcs, starts


def page_pin_rows():
    d = {}
    if PAGE_PINS.exists():
        for l in PAGE_PINS.read_text().splitlines():
            p = l.split("\t")
            if len(p) >= 3:
                d[p[0][len("src/"):-2]] = (int(p[1]), int(p[2]))
    return d


def module_info():
    mods = {m["id"]: (m["container"], m["module"]) for m in read_jsonl(LEDGER / "modules.jsonl")}
    cen = {(x["container"], x["module"]): x for x in read_jsonl(LEDGER / "module_recipe_census.jsonl")}
    return mods, cen


# ------------------------------------------------------------------ per-row job
_G = {}
def _init(funcs, starts):
    _G["funcs"], _G["starts"] = funcs, starts


def scan_row(row):
    sl = retail_slices(row)
    h = hashlib.sha256(b"".join(b for _, _, b in sl)).hexdigest()
    funcs, starts = _G["funcs"].get(row["container"], frozenset()), _G["starts"].get(row["container"], [])
    events_all = []; labels = []
    for n, vram, b in sl:
        ws = words_of(b)
        for e in scan(ws, vram, funcs, starts):
            e["fn"] = n; e["vram"] = vram
            events_all.append(e)
    def where(e):
        return f"0x{e['vram'] + 4 * e['i']:08X}" if e.get("vram") is not None else f"{e['fn']}+0x{4 * e['i']:X}"
    s = summarise(events_all, lambda i: None)
    # examples rendered as addresses (summarise saw bare indices)
    ex = collections.defaultdict(list)
    for e in events_all:
        keys = e.get("kinds", []) if e["cls"] == "fingerprint" else [e["cls"]] if e["cls"] in ("page_shared", "int_ori", "at_macro") else []
        for k in keys:
            if len(ex[k]) < 3: ex[k].append(where(e))
    s["ex"] = dict(ex)
    s["words"] = sum(len(b) // 4 for _, _, b in sl)
    s["retail_sha"] = h[:16]
    s["det"] = DETECTOR
    return row["id"], s, events_all


def row_meta(r, mods, cen, pp):
    from pin_census import sites_of
    text = current_text(r)
    key = mods.get(r["id"])
    c = cen.get(key) if key else None
    return {"id": r["id"], "container": r["container"], "module": key[1] if key else None,
            "census_recipe": c.get("best_recipe") if c else None,
            "cfg": r["cfg"], "cell": r["cell"], "flags": r["flags"], "splitting": splitting(r["cell"], r["flags"]),
            "pins": len(sites_of(text)), "page_pins": pp.get(r["id"], (0, 0))[0],
            "page_lit": len(PAGE_LIT_RE.findall(CMT_RE.sub("", text))), "asm_hi": len(ASM_HI_RE.findall(text)),
            "asm_words": len(ASM_WORDS_RE.findall(text))}


PAGE_LIT_RE = re.compile(r"\b0x8[0-9A-Fa-f]{3}0000[uUlL]*\b")       # a literal RAM page in the C (0x8XXX0000)
ASM_HI_RE = re.compile(r"(?:__asm__|asm)\s*(?:volatile|__volatile__)?\s*\([^;]*?(?:%%?hi\(|\blui\b)", re.S)
CMT_RE = re.compile(r"/\*.*?\*/|//[^\n]*", re.S)
ASM_WORDS_RE = re.compile(r'"\s*\.word\s+0x[0-9A-Fa-f]{8}')                 # a function emitted as raw words


SCAN_KEYS = ("n_lui", "addr_highs", "cls", "kinds", "fpflags", "fp_highs", "fp_data_highs", "weak_highs", "ex", "words", "retail_sha", "det")


def _job(r):
    rid, s, _ = scan_row(r)
    return rid, s


def run(args):
    rs = [r for r in rows() if r["exists"]]
    if args.container: rs = [r for r in rs if r["container"] == args.container]
    if args.only: keep = set(args.only.split(",")); rs = [r for r in rs if r["id"] in keep]
    prev = {x["id"]: x for x in read_jsonl(OUT)}
    funcs, starts = known_addresses()
    _init(funcs, starts)
    mods, cen = module_info(); pp = page_pin_rows()
    todo = []
    for r in rs:
        p = prev.get(r["id"])
        if p and p.get("det") == DETECTOR and not args.force:
            # hash-keyed: rescan only when the retail slice changed
            sl = retail_slices(r)
            if hashlib.sha256(b"".join(b for _, _, b in sl)).hexdigest()[:16] == p.get("retail_sha"):
                continue
        todo.append(r)
    print(f"split_fingerprint: {len(rs)} rows selected, {len(todo)} to scan", flush=True)
    res = {}
    if args.workers > 1 and len(todo) > 50:
        with ProcessPoolExecutor(max_workers=args.workers, initializer=_init, initargs=(funcs, starts)) as ex:
            for rid, s in ex.map(_job, todo, chunksize=32):
                res[rid] = s
    else:
        for r in todo:
            rid, s = _job(r); res[rid] = s
    out = dict(prev)
    for r in rs:
        s = res.get(r["id"])
        base = s if s is not None else (prev.get(r["id"]) or {})
        rec = row_meta(r, mods, cen, pp)
        for k in SCAN_KEYS:
            if k in base: rec[k] = base[k]
        rec["fp"] = rec.get("fp_highs", 0) > 0
        out[r["id"]] = rec
    order = {r["id"]: i for i, r in enumerate(rows())}
    write_jsonl(OUT, sorted(out.values(), key=lambda x: order.get(x["id"], 1 << 30)))
    print(f"wrote {OUT} ({len(out)} rows)")


# ------------------------------------------------------------------ calibration: the sceptic's reloc detector
def reloc_words(path):
    """[[section words: [mnemonic, args, reloc|None, word]]] from an objdump -d -r listing."""
    secs = []; words = None
    for l in open(path).read().splitlines():
        m = re.match(r"^\s*([0-9a-f]+):\s+(?:([0-9a-f]{8})\s+(\S+)\s*(.*)|(R_MIPS_\w+)\s+(\S+))", l)
        if not m: continue
        if m.group(2):
            if int(m.group(1), 16) == 0 or words is None:
                words = []; secs.append(words)
            words.append([m.group(3), m.group(4).strip(), None, int(m.group(2), 16)])
        else:
            words[-1][2] = (m.group(5), m.group(6))
    return secs


def sceptic_kinds(words):
    """The round-77 sceptic's scan (work/native_lane/r77_fable_splitaddr, REPORT item 5), verbatim."""
    kinds = set()
    for i, (mn, args, rel, _) in enumerate(words):
        if mn != "lui" or not rel or rel[0] != "R_MIPS_HI16": continue
        rx = args.split(",")[0]
        if rx in ("at", "$at", "$1"): continue
        sym = rel[1].split("+")[0]
        for j in range(i + 1, min(i + 8, len(words))):
            mn2, a2, rel2, _ = words[j]
            if rel2 and rel2[0] == "R_MIPS_LO16" and rel2[1].split("+")[0] == sym:
                parts = [p.strip() for p in a2.split(",")]
                if mn2 == "addiu" and len(parts) == 3 and parts[1] == rx:
                    if parts[0] != rx: kinds.add("lo_sum_other_reg")
                    if j > i + 1: kinds.add("pair_interleaved")
                elif re.match(r"l[bhw]u?$|lw[lr]$", mn2) and len(parts) == 2:
                    mb = re.search(r"\((\$?\w+)\)", parts[1])
                    if mb and mb.group(1) == rx and parts[0] != rx: kinds.add("load_base_ne_dest")
                    if mb and mb.group(1) == rx and j > i + 1: kinds.add("load_split_from_lui")
                break
    return kinds


def reloc_mode(args):
    from pin_census import sites_of
    R = {r["id"]: r for r in rows()}
    fp = collections.Counter()
    per = {}
    for path in sorted((CACHE / "slus_dis").glob("*.txt")):
        stem = path.stem; rid = "slus/" + stem
        if rid not in R: continue
        r = R[rid]; cell = r["cell"] + (" -mmips-as" if "-mmips-as" in (r["flags"] or "") else "")
        src = ROOT / "src/slus" / f"{stem}.c"
        if not src.exists(): fp[(cell, "nosrc", "_rows")] += 1; continue
        status = "pinned" if sites_of(src.read_text(errors="replace")) else "pinfree"
        kinds = set()
        for sec in reloc_words(path):
            kinds |= sceptic_kinds(sec)
        per[rid] = sorted(kinds)
        fp[(cell, status, "_rows")] += 1
        if kinds:
            fp[(cell, status, "any")] += 1
            for k in kinds: fp[(cell, status, k)] += 1
    for k in sorted(fp): print(*k, fp[k], sep="\t")
    return per


# ------------------------------------------------------------------ validation: raw detector vs slus relocations
def validate(args):
    """For every slus function: align the pinned object's section to the retail slice, then label each raw-detector
    HIGH by what the pinned object has at that word (R_MIPS_HI16 symbol / literal page immediate)."""
    R = {r["id"]: r for r in rows() if r["kind"] == "slus"}
    funcs, starts = known_addresses(); _init(funcs, starts)
    tab = collections.Counter(); unmatched = 0; matched = 0
    lit_rows = collections.defaultdict(list)
    for rid, r in sorted(R.items()):
        path = CACHE / "slus_dis" / (rid.split("/")[1] + ".txt")
        if not path.exists(): continue
        for n, vram, k, sec in slus_functions(r):
            if sec is None:
                unmatched += 1; continue
            matched += 1
            ws = [x[3] for x in sec]
            o = vram - SLUS_VRAM + SLUS_FOFF
            ws = words_of(bytes(container_bytes("slus")[o: o + 4 * k]))
            for e in scan(ws, vram, funcs["slus"], starts.get("slus", [])):
                o = sec[e["i"]]
                src = "sym" if o[2] and o[2][0] == "R_MIPS_HI16" else "literal" if (o[3] & 0xFFFF) else "zero"
                key = e["cls"] if e["cls"] != "fingerprint" else ("fingerprint:" + ("strict" if strict_kinds(e) else "weak"))
                tab[(key, src)] += 1
                if e["cls"] in ("fingerprint", "page_shared") and src == "literal":
                    lit_rows[rid].append(f"0x{vram + 4 * e['i']:08X}")
    print(f"functions aligned {matched}, unaligned {unmatched}")
    for k in sorted(tab): print(*k, tab[k], sep="\t")
    print("rows whose fingerprint HIGHs are literal pages in the pinned object:", len(lit_rows))
    for rid, v in sorted(lit_rows.items()): print(" ", rid, R[rid]["cfg"], ",".join(v[:4]))

# ------------------------------------------------------------------ report: tables + the step-4 files
def cell_label(r):
    f = r.get("flags") or ""
    return r["cell"] + (" -mmips-as" if "-mmips-as" in f else "") + (" -mno-split-addresses" if "-mno-split-addresses" in f else "")


def recipe_splits(recipe):
    if not recipe: return None
    from common import parse_cfg
    cell, flags = parse_cfg(recipe)
    return splitting(cell, " ".join(flags))


def mechanism(r):
    """What in the CURRENT source makes a non-splitting cell emit the split shape (best guess from the text)."""
    m = []
    if r.get("asm_words", 0) >= 4: return "asm_words"
    if r.get("page_pins"): m.append("page_pin")
    elif r.get("page_lit"): m.append("page_literal")
    if r.get("asm_hi"): m.append("inline_asm_hi")
    if not m: m.append("pins_other" if r.get("pins") else "maspsx_or_other")
    return "+".join(m)


def report(args):
    rs = [x for x in read_jsonl(OUT)]
    sc = {}
    try:
        import io, contextlib
        buf = io.StringIO()
        with contextlib.redirect_stdout(buf):
            sc = reloc_mode(args)
    except Exception as e:  # the calibration is optional in the report
        print("reloc calibration failed:", e, file=sys.stderr)
    P = print
    P("## Table 1 - fingerprint rate by container x registered cell x pin status\n")
    P("`rows` all rows; `addr` rows with >= 1 RAM-address HIGH (any class); `fp` rows with >= 1 strict fingerprint HIGH;"
      " `fp/addr` the rate; `weak` rows whose only split evidence is slot_lo; `at` rows with an `$at` macro access.\n")
    P("| container | registered cell | splits? | pins | rows | addr | fp | fp/addr | weak-only | at |")
    P("|---|---|---|---|---:|---:|---:|---:|---:|---:|")
    t = collections.defaultdict(lambda: [0, 0, 0, 0, 0])
    for r in rs:
        k = (r["container"], cell_label(r), "yes" if r["splitting"] else "NO", "pinned" if r["pins"] else "pin-free")
        v = t[k]; v[0] += 1; v[1] += r.get("addr_highs", 0) > 0; v[2] += r["fp"]
        v[3] += (r.get("weak_highs", 0) > 0 and not r["fp"]); v[4] += r.get("cls", {}).get("at_macro", 0) > 0
    for k in sorted(t):
        v = t[k]
        P(f"| {k[0]} | {k[1]} | {k[2]} | {k[3]} | {v[0]} | {v[1]} | {v[2]} | {100 * v[2] / v[1] if v[1] else 0:.0f}% | {v[3]} | {v[4]} |")
    # totals by splitting class
    P("\n### Totals by cell class (all containers)\n")
    P("| cell class | pins | rows | addr | fp | fp/addr |")
    P("|---|---|---:|---:|---:|---:|")
    t2 = collections.defaultdict(lambda: [0, 0, 0])
    for r in rs:
        k = ("splitting" if r["splitting"] else "non-splitting", "pinned" if r["pins"] else "pin-free")
        v = t2[k]; v[0] += 1; v[1] += r.get("addr_highs", 0) > 0; v[2] += r["fp"]
    for k in sorted(t2):
        v = t2[k]; P(f"| {k[0]} | {k[1]} | {v[0]} | {v[1]} | {v[2]} | {100 * v[2] / v[1] if v[1] else 0:.1f}% |")
    # slus: sceptic (reloc) vs raw
    if sc:
        P("\n## Table 2 - slus: the sceptic's relocation detector vs the raw-word detector (per row)\n")
        P("| registered cell | pins | rows | sceptic any | raw fp | both | sceptic only | raw only |")
        P("|---|---|---:|---:|---:|---:|---:|---:|")
        t3 = collections.defaultdict(lambda: [0, 0, 0, 0, 0, 0])
        so, ro = collections.defaultdict(list), collections.defaultdict(list)
        for r in rs:
            if r["container"] != "slus" or r["id"] not in sc: continue
            k = (cell_label(r), "pinned" if r["pins"] else "pin-free")
            a, b = bool(sc[r["id"]]), r["fp"]
            v = t3[k]; v[0] += 1; v[1] += a; v[2] += b; v[3] += a and b; v[4] += a and not b; v[5] += b and not a
            if a and not b: so[k].append(r["id"])
            if b and not a: ro[k].append(r["id"])
        for k in sorted(t3):
            v = t3[k]; P(f"| {k[0]} | {k[1]} | {v[0]} | {v[1]} | {v[2]} | {v[3]} | {v[4]} | {v[5]} |")
        P("\nsceptic-only rows (first 12 per stratum): " + "; ".join(f"{k[0]}/{k[1]}: {', '.join(x.split('/')[1] for x in v[:12])}" for k, v in sorted(so.items())))
        P("\nraw-only rows (first 12 per stratum): " + "; ".join(f"{k[0]}/{k[1]}: {', '.join(x.split('/')[1] for x in v[:12])}" for k, v in sorted(ro.items())))
    # kinds by cell class (pin-free)
    P("\n## Table 3 - fingerprint kinds, pin-free rows (HIGH counts)\n")
    kinds = list(KINDS)
    P("| cell class | " + " | ".join(kinds) + " | funcaddr | after_call | page_shared |")
    P("|---|" + "---:|" * (len(kinds) + 3))
    t4 = collections.defaultdict(collections.Counter)
    for r in rs:
        if r["pins"]: continue
        k = "splitting" if r["splitting"] else "non-splitting"
        t4[k].update(r.get("kinds", {})); t4[k].update(r.get("fpflags", {}))
        t4[k]["page_shared"] += r.get("cls", {}).get("page_shared", 0)
    for k in sorted(t4):
        c = t4[k]; P(f"| {k} | " + " | ".join(str(c[x]) for x in kinds) + f" | {c['funcaddr']} | {c['after_call']} | {c['page_shared']} |")
    # modules
    mods = collections.defaultdict(list)
    for r in rs:
        if r.get("module"): mods[(r["container"], r["module"])].append(r)
    mrecs = []
    for (c, m), lst in sorted(mods.items()):
        rec_ = lst[0].get("census_recipe")
        pf = [r for r in lst if not r["pins"]]
        pfa = [r for r in pf if r.get("addr_highs", 0) > 0]
        pff = [r for r in pf if r["fp"]]
        alla = [r for r in lst if r.get("addr_highs", 0) > 0]
        allf = [r for r in lst if r["fp"]]
        spl = recipe_splits(rec_)
        if rec_ is None: verdict = "no census"
        elif spl and pff: verdict = "agree"
        elif spl and not pfa: verdict = "no evidence (no pin-free addressing)"
        elif spl and len(pfa) >= 3: verdict = "CONTRADICT (splitting recipe, no pin-free fingerprint)"
        elif spl: verdict = "weak (splitting recipe, < 3 pin-free addressing rows, no fingerprint)"
        elif pff: verdict = "CONTRADICT (non-splitting recipe, pin-free fingerprint)"
        elif pfa: verdict = "agree"
        else: verdict = "no evidence (no pin-free addressing)"
        regnon = [r["id"] for r in lst if not r["splitting"] and r["fp"]]
        mrecs.append({"container": c, "module": m, "census_recipe": rec_, "recipe_splits": spl, "rows": len(lst),
                      "pinfree": len(pf), "pinfree_addr": len(pfa), "pinfree_fp": len(pff), "addr": len(alla), "fp": len(allf),
                      "verdict": verdict, "fp_rows_registered_nonsplitting": regnon})
    write_jsonl(ROOT / "work/fidelity/module_fingerprint.jsonl", mrecs)
    P("\n## Table 4 - module census best_recipe vs the fingerprint (dungeon/town/main; slus has no module census)\n")
    P("| census recipe | splits? | modules | agree | contradict | weak/no evidence | rows fp/addr (pin-free) |")
    P("|---|---|---:|---:|---:|---:|---:|")
    t5 = collections.defaultdict(lambda: [0, 0, 0, 0, 0, 0])
    for x in mrecs:
        if x["census_recipe"] is None: continue
        v = t5[(x["census_recipe"], x["recipe_splits"])]
        v[0] += 1; v[1] += x["verdict"] == "agree"; v[2] += x["verdict"].startswith("CONTRADICT"); v[3] += not (x["verdict"] == "agree" or x["verdict"].startswith("CONTRADICT"))
        v[4] += x["pinfree_fp"]; v[5] += x["pinfree_addr"]
    for k in sorted(t5, key=lambda k: -t5[k][0]):
        v = t5[k]; P(f"| {k[0]} | {'yes' if k[1] else 'NO'} | {v[0]} | {v[1]} | {v[2]} | {v[3]} | {v[4]}/{v[5]} |")
    P("\nContradictions:\n")
    P("| module | census recipe | pin-free fp/addr | all fp/addr | rows registered non-splitting with fp |")
    P("|---|---|---:|---:|---|")
    for x in mrecs:
        if x["verdict"].startswith("CONTRADICT"):
            P(f"| {x['container']}/{x['module']} | {x['census_recipe']} | {x['pinfree_fp']}/{x['pinfree_addr']} | {x['fp']}/{x['addr']} | {', '.join(i.split('/')[1] for i in x['fp_rows_registered_nonsplitting'][:6])} |")
    # page-pin rows and the step-4 candidates
    pp = page_pin_rows()
    by = {r["id"]: r for r in rs}
    cols = ["id", "cfg", "splitting", "pins", "page_pins", "page_lit", "asm_hi", "asm_words", "fp", "fp_highs", "kinds", "examples",
            "module", "census_recipe", "census_splits", "mechanism", "step4"]
    def line(r):
        ex = sorted({a for k, v in (r.get("ex") or {}).items() if k in KINDS for a in v})[:3]
        cs = recipe_splits(r.get("census_recipe"))
        st4 = "CANDIDATE" if (not r["splitting"]) and r["fp"] else "weak" if (not r["splitting"]) and r.get("weak_highs") else ""
        return [r["id"], r["cfg"], "yes" if r["splitting"] else "NO", r["pins"], r["page_pins"], r.get("page_lit", 0), r.get("asm_hi", 0), r.get("asm_words", 0),
                "FP" if r["fp"] else ("weak" if r.get("weak_highs") else "-"), r.get("fp_highs", 0),
                ",".join(f"{k}:{v}" for k, v in sorted((r.get("kinds") or {}).items())), ",".join(ex),
                r.get("module") or "", r.get("census_recipe") or "", "" if cs is None else ("yes" if cs else "NO"), mechanism(r),
                st4]
    with open(ROOT / "work/fidelity/page_pin_fingerprint.tsv", "w") as fh:
        fh.write("\t".join(cols) + "\n")
        for rid in pp:
            if rid in by: fh.write("\t".join(map(str, line(by[rid]))) + "\n")
    cands = [r for r in rs if not r["splitting"] and r["fp"]]
    cands.sort(key=lambda r: (not r["pins"], r["container"], r["id"]))
    weak = [r for r in rs if not r["splitting"] and not r["fp"] and r.get("weak_highs")]
    with open(ROOT / "work/fidelity/step4_candidates.tsv", "w") as fh:
        fh.write("\t".join(cols) + "\n")
        for r in cands + weak: fh.write("\t".join(map(str, line(r))) + "\n")
    P("\n## Table 5 - page-constant pin rows (work/native_lane/r77_fable_splitaddr/cands/page_pin_rows.txt)\n")
    P("| registered cell | splits? | rows | page-pin sites | retail fp | weak only | no evidence |")
    P("|---|---|---:|---:|---:|---:|---:|")
    t6 = collections.defaultdict(lambda: [0, 0, 0, 0, 0])
    for rid, (n, tot) in pp.items():
        r = by.get(rid)
        if not r: continue
        v = t6[(cell_label(r), r["splitting"])]
        v[0] += 1; v[1] += n; v[2] += r["fp"]; v[3] += (not r["fp"] and r.get("weak_highs", 0) > 0); v[4] += (not r["fp"] and not r.get("weak_highs"))
    for k in sorted(t6):
        v = t6[k]; P(f"| {k[0]} | {'yes' if k[1] else 'NO'} | {v[0]} | {v[1]} | {v[2]} | {v[3]} | {v[4]} |")
    P("\n## Table 6 - step-4 candidates (registered at a non-splitting cell, retail shows a strict fingerprint)\n")
    P("| mechanism in current source | pinned rows | pin-free rows | page-pin sites | census recipe splits (yes/NO/none) |")
    P("|---|---:|---:|---:|---|")
    t7 = collections.defaultdict(lambda: [0, 0, 0, collections.Counter()])
    for r in cands:
        v = t7[mechanism(r)]; v[0] += bool(r["pins"]); v[1] += not r["pins"]; v[2] += r["page_pins"]
        cs = recipe_splits(r.get("census_recipe")); v[3]["none" if cs is None else ("yes" if cs else "NO")] += 1
    for k in sorted(t7, key=lambda k: -(t7[k][0] + t7[k][1])):
        v = t7[k]; P(f"| {k} | {v[0]} | {v[1]} | {v[2]} | {v[3]['yes']}/{v[3]['NO']}/{v[3]['none']} |")
    P(f"\ncandidates: {len(cands)} rows ({sum(1 for r in cands if r['pins'])} pinned, {sum(r['pins'] for r in cands)} pins,"
      f" {sum(r['page_pins'] for r in cands)} page-pin sites); by registered cell: "
      + ", ".join(f"{k} {v}" for k, v in collections.Counter(cell_label(r) for r in cands).most_common()))
    P("\n## Table 7 - rows registered with -mmips-as / -mno-split-addresses\n")
    P("| row | cfg | pins | fp | kinds | at_macro HIGHs |")
    P("|---|---|---:|---|---|---:|")
    for r in rs:
        f = r.get("flags") or ""
        if "-mmips-as" in f or "-mno-split-addresses" in f:
            P(f"| {r['id']} | {r['cfg']} | {r['pins']} | {'FP' if r['fp'] else '-'} | {','.join(sorted(r.get('kinds') or {}))} | {r.get('cls', {}).get('at_macro', 0)} |")


def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("--container"); ap.add_argument("--only", help="comma-separated row ids")
    ap.add_argument("--workers", type=int, default=8); ap.add_argument("--force", action="store_true")
    ap.add_argument("--mode", choices=("raw", "reloc"), default="raw")
    ap.add_argument("--validate", action="store_true")
    ap.add_argument("--report", action="store_true", help="markdown tables to stdout; writes step4_candidates.tsv, page_pin_fingerprint.tsv, module_fingerprint.jsonl")
    ap.add_argument("--events", help="print the raw events of one row id")
    a = ap.parse_args()
    if a.events:
        R = {r["id"]: r for r in rows()}
        funcs, starts = known_addresses(); _init(funcs, starts)
        rid, s, evs = scan_row(R[a.events])
        for e in evs:
            print(e.get("fn"), f"0x{(e['vram'] or 0) + 4 * e['i']:08X}", f"${e['reg']}", f"0x{e['hi']:04X}", e["cls"],
                  ",".join(e.get("kinds", [])), ",".join(e.get("flags", [])), f"t=0x{e['t']:08X}" if "t" in e else "")
        print(json.dumps(s))
        return
    if a.mode == "reloc": reloc_mode(a); return
    if a.validate: validate(a); return
    if a.report: report(a); return
    run(a)


if __name__ == "__main__":
    main()
