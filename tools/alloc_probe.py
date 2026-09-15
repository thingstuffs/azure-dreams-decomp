#!/usr/bin/env python3
"""Allocator counterfactual probe: WHICH single allocator input, changed by the smallest amount, is
SUFFICIENT for the unpinned compile to reproduce the pinned (retail-exact) assembly?

    python3 tools/alloc_probe.py <row_id> [--source cand.c] [--site N] [--json] [--out report.json]
    python3 tools/alloc_probe.py --calibrate 40 [--out-dir work/alloc_probe]
    python3 tools/alloc_probe.py --population 40 [--traces work/alloc_retrace/raw]

tools/alloc_trace.py reads the stock GCC 2.x allocator's inputs for a pinned ASM_REG site; it says what the
allocator saw. This tool asks the counterfactual: erase the one pin, bind retail's hard register to the
pseudo the erased build uses (`alloc_trace.diagnose_site`), then recompile the ERASED text under gdb once
per knob, each run writing ONE allocator input at the moment that decision is taken, and compare the run's
normalized assembly with the pinned build's (P). A knob whose run equals P is sufficient: it names the
variable and the lever. `force` (make the target's own assignment retail's register, changing no input) is
the oracle: if even forcing the one assignment does not reproduce P, the site is not a single-assignment
site at all.

Knobs, in the order the minimal knob is chosen from:

  force            local: mask regs_live_at[birth..death) to "all busy except retail" at the target
                   quantity's own find_free_reg entry, restore + post_mark_life(retail) at the return.
                   global: mask hard_reg_conflicts[allocno] the same way around find_reg.
  force-return     local: set $eax at the find_free_reg return (and fix regs_live_at by hand).
                   global: write reg_renumber[pseudo], set regs_used_so_far, propagate retail into the
                   hard_reg_conflicts of conflicting allocnos (conflicts/allocno_row_words).
  local            sugg, unconflict, refs+1, refs-1, shorten-death, shorten-birth,
                   competitor-refs-1, competitor-unsugg, order-swap
  global           pref, copypref, unconflict, order-swap, used-so-far-set, used-so-far-clear,
                   competitor-unpref

Hooks: `qty_order` is alloca'd inside block_alloc and has no symbol, so local order knobs are written
through the `qsort` call itself (argument 0 IS qty_order; argument 3 distinguishes the suggestion sort
qty_sugg_compare_1 from the main sort qty_compare_1, and the return address identifies block_alloc as the
caller). block_alloc uses inline compares when next_qty <= 3, so that hook does not exist for small blocks
and a run that needs it records the gdb event `swap_qty_order: no qsort hook` with applied=0 rather than
silently doing nothing. Priority knobs are written at the earliest hook that still precedes the sort that
reads them; on a next_qty <= 3 block that is the block's first find_free_reg, which precedes the second
(inline) sort only when it comes from the suggestions pass, so such a run records the call's
`just_try_suggested` argument and the block's next_qty and is reported as `blockfirst-fallback` or
`blockfirst-fallback-late` + `applied_after_decision` (a late run is never counted as sufficient).
`unconflict` at the target's own find_free_reg entry (the breakpoint fires before the body reads
regs_live_at, so the write takes effect for that very call); every global knob at dump_conflicts, which is
after the allocno sort and prune_preferences and before any find_reg. Competitor knobs are planned only
when an attempt EARLIER than the target's own took retail's register (both scopes); the site record's
`competitor` says which source named it, or that none was found and the knobs were not planned.

Every run records the allocator's ACTUAL result for the target (reg_renumber[pseudo] at the target block's
block_alloc return, or at the target allocno's last find_reg return), so a knob that did not change the
decision is distinguished from one that changed the decision but not the assembly. Each site also gets a
no-op control (gdb attached, nothing written); if its assembly differs from a normal compile of the erased
text the site is `untrusted` and nothing else about it is reported.

ANALYSIS ONLY. Nothing is written to src/, ledger/ or config/; no gates, sweeps, pin_search,
apply_candidates or lane launches. --calibrate reads landed pre-fix texts with `git show <commit>~1:path`
and runs no other git command. Every compile and gdb run happens in its own tempfile directory with cwd
there, under nice, at most --jobs (<= 6) at a time.
"""
import argparse
import collections
import difflib
import json
import os
from pathlib import Path
import random
import re
import subprocess
import sys
import tempfile
import time
from concurrent.futures import ThreadPoolExecutor

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, parse_cfg, sha_text
from pin_census import sites_of
from pin_sites import erase_many
from xform.sched_trace import normalize
from alloc_trace import (FIRST, diagnose_site, hard_number, observe, reg_name, var_name)

MAX_JOBS = 6
ARGCOPY = re.compile(r"\(set \(reg/v:\w+ (\d+)\)\s*\n?\s*\(reg:\w+ (\d+) (\w+)\)\)")

# The order the minimal knob is chosen in, per scope (the brief's order; `unconflict` and `order-swap`
# exist in both scopes and rank differently in each).
LOCAL_ORDER = ["force", "force-return", "sugg", "unconflict", "refs+1", "refs-1",
               "shorten-death", "shorten-birth", "competitor-refs-1", "competitor-unsugg", "order-swap"]
GLOBAL_ORDER = ["force", "force-return", "pref", "copypref", "unconflict", "order-swap",
                "used-so-far-set", "used-so-far-clear", "competitor-unpref"]
KNOB_ORDER = LOCAL_ORDER + [n for n in GLOBAL_ORDER if n not in LOCAL_ORDER]


# ------------------------------------------------------------------ pure parts

def distance(a, b):
    """Non-equal lines between two normalized assembly listings (0 == identical).

    `normalize` returns a list of lines; a string is accepted too."""
    if a is None or b is None:
        return None
    x = a.splitlines() if isinstance(a, str) else list(a)
    y = b.splitlines() if isinstance(b, str) else list(b)
    n = 0
    for tag, i1, i2, j1, j2 in difflib.SequenceMatcher(None, x, y, autojunk=False).get_opcodes():
        if tag != "equal":
            n += max(i2 - i1, j2 - j1)
    return n


def primary_entry(rec):
    """The reasons entry the probe perturbs: the first bound pseudo the allocator actually owns."""
    for want in ("local", "global"):
        for d in rec.get("reasons") or []:
            if d.get("owner") == want and (d.get("quantity") if want == "local" else d.get("allocno") is not None):
                return d
    return None


def global_competitor(rec, pseudo, fn=None):
    """(competitor pseudo, allocno, source) for a global target: an allocno that was handed retail's
    register BEFORE the target's own find_reg attempt.

    `attempt_reason` names a genuine earlier competitor (source `attempt_reasons`: it scans the recorded
    attempts and stops at the target's own), but only when retail is in the target's own conflict set
    (`earlier-global-conflict`), which is a minority of global sites. The fallback reads the recorded
    find_reg attempts directly and, since the 2026-09-15 fix, stops at the target's own FIRST attempt
    exactly as `local_competitor` stops at the target's own quantity, so it too can only name an EARLIER
    attempt (source `earlier-attempt`). Before that fix it took the first same-function attempt whose
    result was retail's register in EITHER direction, and 14 of the 19 competitors it found on the
    population sample were LATER than the target's own attempt: `order-swap` / `competitor-unpref` built
    on such a competitor read as "make the target beat the value that took the register from it" when
    they were really "reorder against whoever holds retail's register". Now there is no competitor in
    that case and the caller plans no competitor knobs at all.

    The boundary is the target's FIRST attempt, so when `retry_global_alloc` gives the target a failed
    early attempt and a successful later one, the attempts between them are not offered as competitors:
    `earlier-attempt` is a subset of what `attempt_reason` would name, never a superset."""
    for d in rec.get("attempt_reasons") or []:
        if d.get("pseudo") != pseudo:
            continue
        for z in d.get("competitors") or []:
            a = allocno_of(rec, d.get("function"), z.get("pseudo"))
            if a is not None:
                return z.get("pseudo"), a, "attempt_reasons"
    hard = rec.get("hard")
    for at in (rec.get("trace") or {}).get("global_attempts") or []:
        if fn is not None and at.get("function") != fn:
            continue
        if at.get("pseudo") == pseudo:
            break                 # the target's own attempt: nothing after it competed FOR the register
        if at.get("result") != hard:
            continue
        a = allocno_of(rec, at.get("function"), at.get("pseudo"))
        if a is not None:
            return at.get("pseudo"), a, "earlier-attempt"
    return None, None, None


def local_competitor(rec, d, hard):
    """The quantity that took retail's register before the target, from the block's attempt list."""
    z = (d.get("competitors") or [None])[0]
    if z:
        return z
    qty = d["quantity"]["qty"]
    for block in (rec.get("trace") or {}).get("blocks") or []:
        if block.get("function") != d.get("function") or block.get("block") != d.get("block"):
            continue
        for at in block.get("attempts") or []:
            if at.get("qty") == qty:
                break
            if at.get("result") == hard:
                q = next((x for x in block.get("quantities") or [] if x["qty"] == at["qty"]), {})
                return dict(qty=at["qty"], pseudos=q.get("pseudos"), priority=q.get("priority"),
                            target_priority=None, same_priority=False, suggested=False, source="attempts")
    return None


def competitor_record(rec, d, hard):
    """What the plan knows about the competitor, for the site record: who it is, which source named it,
    and that it PRECEDES the target (both scopes now accept earlier attempts only).

    When no earlier competitor exists the competitor knobs (local: competitor-refs-1, competitor-unsugg,
    order-swap; global: order-swap, competitor-unpref) are not planned at all, and this record says so
    rather than leaving their absence unexplained."""
    if d.get("owner") == "local":
        c = local_competitor(rec, d, hard)
        if c is None:
            return dict(found=False, source="none", earlier=False,
                        note="no earlier quantity in the block took retail's register: "
                             "competitor knobs not planned")
        return dict(found=True, source=c.get("source") or "competitors", earlier=True,
                    qty=c.get("qty"), pseudos=c.get("pseudos"))
    cp, ca, src = global_competitor(rec, d.get("pseudo"), d.get("function"))
    if ca is None:
        return dict(found=False, source="none", earlier=False,
                    note="no find_reg attempt before the target's own returned retail's register: "
                         "competitor knobs not planned")
    return dict(found=True, source=src, earlier=True, pseudo=cp, allocno=ca)


def allocno_of(rec, fn, pseudo):
    for g in (rec.get("trace") or {}).get("global_states") or []:
        if g.get("function") == fn and pseudo in g.get("allocno_reg", []):
            return g["allocno_reg"].index(pseudo)
    return None


def plan_knobs(rec, hard=None):
    """The knob plan for one diagnosed site record (pure: no gdb, no compiler).

    Returns a list of knob dicts {name, scope, hook, ops, special, target, competitor, note}. `ops` are
    primitives the gdb side interprets against live memory (bit sets and vectors are runtime state, so
    they are read-modify-written there, never precomputed here)."""
    hard = rec.get("hard") if hard is None else hard
    d = primary_entry(rec)
    if d is None or hard is None or hard < 0:
        return []
    fn, pseudo = d.get("function"), d.get("pseudo")
    out = []

    def add(name, hook, ops, special=None, competitor=None, note=None):
        out.append(dict(name=name, scope=d["owner"], hook=hook, ops=ops, special=special,
                        target=target, competitor=competitor, note=note))

    if d["owner"] == "local":
        q = d["quantity"]
        qty, birth, death = q["qty"], q["birth"], q["death"]
        target = dict(scope="local", function=fn, block=d.get("block"), qty=qty,
                      pseudo=pseudo, birth=birth, death=death)
        comp = local_competitor(rec, d, hard)
        cq = comp["qty"] if comp else None
        comp_rec = dict(qty=cq, pseudos=comp.get("pseudos"), source=comp.get("source") or "competitors",
                        earlier=True) if comp else None
        add("force", "own", [], special="force-mask")
        add("force-return", "own", [], special="force-return")
        add("sugg", "presort", [dict(op="setbit", sym="qty_phys_sugg", idx=qty, bit=hard),
                                dict(op="add_i16", sym="qty_phys_num_sugg", idx=qty, delta=1)])
        add("unconflict", "own", [dict(op="clrbit_range", sym="regs_live_at", lo=birth, hi=death, bit=hard)])
        add("refs+1", "presort", [dict(op="add_i32", sym="qty_n_refs", idx=qty, delta=1)])
        if q.get("n_refs", 0) > 1:
            add("refs-1", "presort", [dict(op="add_i32", sym="qty_n_refs", idx=qty, delta=-1)])
        if death - birth > 1:
            add("shorten-death", "presort", [dict(op="add_i32", sym="qty_death", idx=qty, delta=-1)])
            add("shorten-birth", "presort", [dict(op="add_i32", sym="qty_birth", idx=qty, delta=1)])
        if cq is not None:
            add("competitor-refs-1", "presort",
                [dict(op="add_i32", sym="qty_n_refs", idx=cq, delta=-1)], competitor=comp_rec)
            add("competitor-unsugg", "presort",
                [dict(op="clear_sugg", sym="qty_phys_copy_sugg", num="qty_phys_num_copy_sugg", idx=cq, bit=hard),
                 dict(op="clear_sugg", sym="qty_phys_sugg", num="qty_phys_num_sugg", idx=cq, bit=hard)],
                competitor=comp_rec)
            add("order-swap", "postsort2", [dict(op="swap_qty_order", a=qty, b=cq)], competitor=comp_rec,
                note="needs next_qty > 3 (no qsort call to hook otherwise)")
        return out

    a = d.get("allocno")
    target = dict(scope="global", function=fn, allocno=a, pseudo=pseudo)
    cp, ca, csrc = global_competitor(rec, pseudo, fn)
    comp_rec = dict(allocno=ca, pseudo=cp, source=csrc, earlier=True) if ca is not None else None
    add("force", "global", [], special="force-mask")
    add("force-return", "global", [], special="force-return")
    add("pref", "global", [dict(op="setbit", sym="hard_reg_preferences", idx=a, bit=hard)])
    add("copypref", "global", [dict(op="setbit", sym="hard_reg_copy_preferences", idx=a, bit=hard)])
    add("unconflict", "global", [dict(op="clrbit", sym="hard_reg_conflicts", idx=a, bit=hard)])
    if ca is not None:
        add("order-swap", "global",
            [dict(op="swap_order", sym="allocno_order", count="max_allocno", a=a, b=ca)],
            competitor=comp_rec)
    add("used-so-far-set", "global", [dict(op="setbit_direct", sym="regs_used_so_far", bit=hard)])
    add("used-so-far-clear", "global", [dict(op="clrbit_direct", sym="regs_used_so_far", bit=hard)])
    if ca is not None:
        add("competitor-unpref", "global",
            [dict(op="clrbit", sym="hard_reg_preferences", idx=ca, bit=hard),
             dict(op="clrbit", sym="hard_reg_copy_preferences", idx=ca, bit=hard)],
            competitor=comp_rec)
    return out


def diff_removed_sites(diff_text):
    """(variable, register) of the ASM_REG sites a landed diff REMOVED (removed minus re-added)."""
    def sites(sign):
        # `register s32 value ASM_REG("$2") = input_value;`: the declaration is to the LEFT of the macro.
        out = []
        for line in diff_text.splitlines():
            if not line.startswith(sign) or line.startswith(sign * 2):
                continue
            m = re.search(r"(.*?)\bASM_REG\w*\s*\(\s*([^)]*?)\s*\)", line[1:])
            if m:
                out.append((var_name(re.sub(r"\bregister\b", " ", m[1])),
                            m[2].strip().strip('"').lstrip("$")))
        return out
    added = collections.Counter(sites("+"))
    removed = []
    for s in sites("-"):
        if added[s]:
            added[s] -= 1
        else:
            removed.append(s)
    return removed


def diff_variables(diff_text):
    """Identifiers the diff's changed lines declare or assign (the variables the fix touched)."""
    out = set()
    for line in diff_text.splitlines():
        if not line or line[0] not in "+-" or line[:2] in ("++", "--"):
            continue
        s = re.sub(r"\bASM_\w+\s*\([^)]*\)", " ", line[1:])
        s = re.sub(r"/\*.*?\*/", " ", s)
        s = re.sub(r"(?:->|\.)\s*[A-Za-z_]\w*", " ", s)   # a struct field is not a variable
        for m in re.finditer(r"\b([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*(?:=[^=]|\+\+|--|[-+*/|&^]=|>>=|<<=)", s):
            out.add(m[1])
        m = re.match(r"\s*(?:register\s+|const\s+|static\s+|volatile\s+|unsigned\s+|signed\s+)*"
                     r"[A-Za-z_]\w*\s*\**\s*([A-Za-z_]\w*)\s*(?:\[[^\]]*\])?\s*[;=,]", s)
        if m:
            out.add(m[1])
        for m2 in re.finditer(r"\(\s*\*+\s*([A-Za-z_]\w*)\s*\)\s*\(", s):
            out.add(m2[1])
    return out - {"if", "for", "while", "return", "switch", "sizeof", "else", "do"}


def parse_index(md_text):
    """The landed-exemplar table: dicts(commit, row, regs_before, regs_after, diff)."""
    out = []
    for line in md_text.splitlines():
        m = re.match(r"\|\s*([0-9a-f]{6,})\s*\|\s*(\S+)\s*\|\s*(\d+)\D+(\d+)\s*\|[^|]*\|\s*(\S+\.diff)\s*\|", line)
        if m:
            out.append(dict(commit=m[1], row=m[2], regs_before=int(m[3]), regs_after=int(m[4]), diff=m[5]))
    return out


def pseudo_names(rtl_text, function, c_text):
    """pseudo -> C name, for the pseudos a gcc 2.x rtl dump lets us name at all.

    2.x dumps carry no `(reg/v:SI N [ name ])` decoration, so only the prologue argument copies
    `(set (reg/v:SI N) (reg:SI 4 a0))` can be named, from the function's own parameter list."""
    chunks = re.split(r"^;; Function (\S+)[^\n]*\n", rtl_text, flags=re.M)
    body = ""
    for k in range(1, len(chunks), 2):
        if chunks[k] == function:
            body = chunks[k + 1]
    params = []
    m = re.search(r"\b" + re.escape(function) + r"\s*\(([^)]*)\)\s*\{", c_text)
    if m and m[1].strip() not in ("", "void"):
        params = [var_name(p) for p in m[1].split(",")]
    out = {}
    for mm in ARGCOPY.finditer(body.replace("\n", " ")):
        i = int(mm[2]) - 4          # $a0..$a3 are the first four parameters
        if 0 <= i < 4 and i < len(params) and params[i]:
            out[int(mm[1])] = params[i]
    return out


def strict_fix_variables(diff_text, var):
    """The fix's changed variables EXCLUDING `var`'s own declaration lines.

    The brief's rule ("identifiers whose declarations or assignments appear in the changed lines") makes
    the pinned variable a member by construction: the line that removes its `ASM_REG` IS its declaration.
    This stricter reading asks whether the fix touched the variable anywhere ELSE."""
    keep = []
    decl = re.compile(r"^\s*(?:register\s+|const\s+|static\s+|volatile\s+|unsigned\s+|signed\s+)*"
                      r"[A-Za-z_]\w*\s*\**\s*" + re.escape(var or "\0") + r"\s*(?:\[[^\]]*\])?"
                      r"\s*(?:ASM_\w+\s*\([^)]*\))?\s*[;=]")
    for line in diff_text.splitlines():
        if line[:1] in "+-" and line[:2] not in ("++", "--") and decl.match(line[1:]):
            continue
        keep.append(line)
    return diff_variables("\n".join(keep))


# ------------------------------------------------------------------ gdb driver

PROBE_SCRIPT = r'''
import gdb,json,struct
C=json.load(open("probe_config.json"));A=C["addresses"];FIRST=C["first_pseudo"]
T=C["target"];K=C["knob"];HARD=C["hard"];LO,HI=C["block_alloc"];COMPAR=C["compar"]
S={"applied":0,"hook_fired":0,"results":[],"events":[],"forced":[]}
inf=lambda:gdb.selected_inferior()
mem=lambda a,n:bytes(inf().read_memory(a,n))
wr=lambda a,b:inf().write_memory(a,b)
def i32(a):return struct.unpack("<i",mem(a,4))[0]
def u32(a):return struct.unpack("<I",mem(a,4))[0]
def w32(a,v):wr(a,struct.pack("<i",v))
def i16(a):return struct.unpack("<h",mem(a,2))[0]
def w16(a,v):wr(a,struct.pack("<h",v))
def ptr(n):return struct.unpack("<I",mem(A[n],4))[0]
def sc(n):return i32(A[n])
def fname():return mem(ptr("current_function_name"),128).split(b"\x00")[0].decode(errors="replace")
def args(n):
    sp=int(gdb.parse_and_eval("$esp"));return [i32(sp+4*(i+1)) for i in range(n)]
def uargs(n):
    sp=int(gdb.parse_and_eval("$esp"));return [u32(sp+4*(i+1)) for i in range(n)]
def retaddr():return i32(int(gdb.parse_and_eval("$esp")))
def getset(a):return list(struct.unpack("<III",mem(a,12)))
def putset(a,w):wr(a,struct.pack("<III",*w))
def setbit(a,b):
    w=getset(a);w[b//32]|=1<<(b%32);putset(a,w)
def clrbit(a,b):
    w=getset(a);w[b//32]&=~(1<<(b%32))&0xffffffff;putset(a,w)
def testbit(a,b):return bool(getset(a)[b//32]&(1<<(b%32)))
def onlybit(a,b):
    putset(a,[0xffffffff]*3);clrbit(a,b)
def renumber(p):return struct.unpack("<h",mem(ptr("reg_renumber")+2*p,2))[0]
def record(tag):
    try:S["results"].append([tag,renumber(T["pseudo"])])
    except Exception as e:S["events"].append("record %s: %s"%(tag,e))
def do(ops):
    for o in ops:
        k=o["op"]
        try:
            if k=="setbit":setbit(ptr(o["sym"])+12*o["idx"],o["bit"])
            elif k=="clrbit":clrbit(ptr(o["sym"])+12*o["idx"],o["bit"])
            elif k=="setbit_direct":setbit(A[o["sym"]],o["bit"])
            elif k=="clrbit_direct":clrbit(A[o["sym"]],o["bit"])
            elif k=="clrbit_range":
                for j in range(max(0,o["lo"]),max(0,o["hi"])):clrbit(ptr(o["sym"])+12*j,o["bit"])
            elif k=="add_i32":
                a=ptr(o["sym"])+4*o["idx"];w32(a,i32(a)+o["delta"])
            elif k=="add_i16":
                a=ptr(o["sym"])+2*o["idx"];w16(a,i16(a)+o["delta"])
            elif k=="clear_sugg":
                a=ptr(o["sym"])+12*o["idx"]
                if testbit(a,o["bit"]):
                    clrbit(a,o["bit"]);n=ptr(o["num"])+2*o["idx"];w16(n,max(0,i16(n)-1))
            elif k=="swap_order":
                arr=ptr(o["sym"]);n=sc(o["count"]);v=[i32(arr+4*i) for i in range(n)]
                if o["a"] in v and o["b"] in v:
                    i,j=v.index(o["a"]),v.index(o["b"]);w32(arr+4*i,o["b"]);w32(arr+4*j,o["a"])
                else:S["events"].append("swap_order: value missing")
            elif k=="swap_qty_order":
                arr=S.get("qty_order")
                if arr is None:S["events"].append("swap_qty_order: no qsort hook (next_qty<=3)");return
                n=sc("next_qty");v=[i32(arr+4*i) for i in range(n)]
                if o["a"] in v and o["b"] in v:
                    i,j=v.index(o["a"]),v.index(o["b"]);w32(arr+4*i,o["b"]);w32(arr+4*j,o["a"])
                else:S["events"].append("swap_qty_order: value missing")
            else:S["events"].append("unknown op "+k)
            S["applied"]+=1
        except Exception as e:S["events"].append("%s: %s"%(k,e))
class BlockDone(gdb.FinishBreakpoint):
    def __init__(self):super().__init__(gdb.newest_frame(),internal=True)
    def stop(self):
        record("block_alloc");return False
class Block(gdb.Breakpoint):
    def stop(self):
        S["block"]=args(1)[0];S["fn"]=fname();S["first_free"]=True;S["qty_order"]=None
        if T["scope"]=="local" and S["fn"]==T["function"] and S["block"]==T["block"]:
            try:BlockDone()
            except Exception as e:S["events"].append("blockdone: %s"%e)
        return False
def in_block():
    return S.get("fn")==T["function"] and S.get("block")==T.get("block")
class FreeDone(gdb.FinishBreakpoint):
    def __init__(self,born,dead,mode):
        super().__init__(gdb.newest_frame(),internal=True);self.born=born;self.dead=dead;self.mode=mode
    def stop(self):
        try:
            got=int(gdb.parse_and_eval("$eax"))&0xffffffff
            got=got if got<0x80000000 else got-0x100000000
            if self.mode=="mask":
                for j,w in zip(range(self.born,self.dead),S["saved"].pop()):putset(ptr("regs_live_at")+12*j,w)
                if got>=0:
                    for j in range(self.born,self.dead):setbit(ptr("regs_live_at")+12*j,HARD)
                S["forced"].append(["mask",got])
            elif self.mode=="ret":
                for j in range(self.born,self.dead):
                    if got>=0 and got!=HARD:clrbit(ptr("regs_live_at")+12*j,got)
                    setbit(ptr("regs_live_at")+12*j,HARD)
                gdb.execute("set $eax = %d"%HARD);S["applied"]+=1
                S["forced"].append(["ret",got])
        except Exception as e:S["events"].append("freedone: %s"%e)
        return False
class Free(gdb.Breakpoint):
    def stop(self):
        try:
            aa=args(7);q=aa[2];born,dead=aa[5],aa[6]
            if in_block() and S.get("first_free"):
                # find_free_reg(class,mode,qty,accept_call_clobbered,JUST_TRY_SUGGESTED,born,dead):
                # only the suggestions pass (local-alloc.c 1469-1477) passes 1, so aa[4] says whether the
                # block's first call is that pass's - i.e. whether it still PRECEDES the second (inline)
                # sort - or the main pass at line 1527, which is AFTER it. Raw facts only here; the
                # late/not-late reading is derived in alloc_probe.fallback_status.
                S["first_free_just_try_suggested"]=aa[4]
                try:S["block_next_qty"]=sc("next_qty")
                except Exception as e:S["events"].append("next_qty: %s"%e)
                if not S["hook_fired"] and K["hook"] in ("blockfirst","presort"):
                    # next_qty <= 3 means block_alloc sorts inline and calls no qsort: the block's first
                    # find_free_reg is then the earliest reachable hook.
                    do(K["ops"]);S["hook_fired"]+=1
                    S["hook_used"]="blockfirst" if K["hook"]=="blockfirst" else "blockfirst-fallback"
            S["first_free"]=False
            if in_block() and T["scope"]=="local" and q==T["qty"]:
                if K["hook"]=="own" and not K["special"]:
                    do(K["ops"]);S["hook_fired"]+=1
                elif K["special"]=="force-mask":
                    # a stack: find_free_reg calls itself (suggested-only fallback, caller-saves)
                    S.setdefault("saved",[]).append([getset(ptr("regs_live_at")+12*j) for j in range(born,dead)])
                    for j in range(born,dead):onlybit(ptr("regs_live_at")+12*j,HARD)
                    S["applied"]+=1;S["hook_fired"]+=1;FreeDone(born,dead,"mask")
                elif K["special"]=="force-return":
                    S["hook_fired"]+=1;FreeDone(born,dead,"ret")
        except Exception as e:S["events"].append("free: %s"%e)
        return False
class SortDone(gdb.FinishBreakpoint):
    def __init__(self):super().__init__(gdb.newest_frame(),internal=True)
    def stop(self):
        do(K["ops"]);S["hook_fired"]+=1;S["hook_used"]="postsort2";return False
class Sort(gdb.Breakpoint):
    def stop(self):
        try:
            ra=retaddr()
            if not (LO<=ra<HI) or not in_block():return False
            aa=uargs(4);S["qty_order"]=aa[0]
            if aa[3]==COMPAR.get("sugg") and K["hook"]=="presort" and not S["hook_fired"]:
                do(K["ops"]);S["hook_fired"]+=1;S["hook_used"]="presort"
            if aa[3]==COMPAR.get("main") and K["hook"]=="postsort2":SortDone()
        except Exception as e:S["events"].append("sort: %s"%e)
        return False
class GlobalStart(gdb.Breakpoint):
    def stop(self):
        try:
            if fname()!=T["function"]:return False
            record("local-done")
            if K["hook"]=="global" and not K["special"]:
                do(K["ops"]);S["hook_fired"]+=1;S["hook_used"]="dump_conflicts"
        except Exception as e:S["events"].append("global: %s"%e)
        return False
class RegDone(gdb.FinishBreakpoint):
    def __init__(self,mode):
        super().__init__(gdb.newest_frame(),internal=True);self.mode=mode
    def stop(self):
        try:
            if self.mode=="mask":
                putset(ptr("hard_reg_conflicts")+12*T["allocno"],S["saved"].pop())
            elif self.mode=="ret":
                w16(ptr("reg_renumber")+2*T["pseudo"],HARD);setbit(A["regs_used_so_far"],HARD)
                n=sc("max_allocno");rw=sc("allocno_row_words");cf=ptr("conflicts")
                for j in range(n):
                    if i32(cf+4*(T["allocno"]*rw+j//32))&(1<<(j%32)):
                        setbit(ptr("hard_reg_conflicts")+12*j,HARD)
                S["applied"]+=1
            record("find_reg")
        except Exception as e:S["events"].append("regdone: %s"%e)
        return False
class GlobalFind(gdb.Breakpoint):
    def stop(self):
        try:
            aa=args(5)
            if T["scope"]!="global" or aa[0]!=T["allocno"]:return False
            if K["special"]=="force-mask":
                S.setdefault("saved",[]).append(getset(ptr("hard_reg_conflicts")+12*T["allocno"]))
                onlybit(ptr("hard_reg_conflicts")+12*T["allocno"],HARD)
                S["applied"]+=1;S["hook_fired"]+=1;RegDone("mask")
            elif K["special"]=="force-return":
                S["hook_fired"]+=1;RegDone("ret")
            else:RegDone("none")
        except Exception as e:S["events"].append("find_reg: %s"%e)
        return False
Block("*"+str(A["block_alloc"]),internal=True)
Free("*"+str(A["find_free_reg"]),internal=True)
if "qsort" in A:Sort("*"+str(A["qsort"]),internal=True)
if "dump_conflicts" in A:GlobalStart("*"+str(A["dump_conflicts"]),internal=True)
if "find_reg" in A:GlobalFind("*"+str(A["find_reg"]),internal=True)
gdb.execute("run")
json.dump(S,open("probe_result.json","w"),separators=(",",":"))
'''


def fallback_status(hook, res):
    """(hook_used, applied_after_decision) for one gdb result: did a `presort` knob land too late?

    A `presort` knob that could not be written at the suggestion qsort falls back to the block's first
    find_free_reg (block_alloc sorts inline and calls no qsort when next_qty <= 3). That hook precedes
    the second sort ONLY when the block's first find_free_reg comes from the suggestions pass, which the
    allocator enters only for quantities that already carry a suggestion (local-alloc.c 1469-1477): the
    gdb side records that call's `just_try_suggested` argument, and a 0 means the first call is the one
    at line 1527, AFTER the sort the priority knobs (refs+-1, shorten-*, sugg) were meant to change. Such
    a run is reported as `blockfirst-fallback-late` with `applied_after_decision` true and is NOT counted
    as a sufficient knob: it is not a valid test of the lever, whatever assembly it produced. A missing
    flag is unknown, not late. (Measured before this marking existed: none of the 22 runs that took the
    fallback changed the allocator's result.)"""
    used = res.get("hook_used")
    if hook != "presort" or used != "blockfirst-fallback":
        return used, False
    if res.get("first_free_just_try_suggested") == 0:
        return "blockfirst-fallback-late", True
    return used, False


def cc1_table(cc1):
    """{name: (address, size)} from the unstripped i386 cc1, duplicates resolved near qty_birth."""
    out = subprocess.run(["nm", "-S", str(cc1)], capture_output=True, text=True, check=True).stdout
    syms = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4:
            syms.setdefault(p[3], []).append((int(p[0], 16), int(p[1], 16)))
        elif len(p) == 3 and p[1].lower() in "tbdrvw":
            syms.setdefault(p[2], []).append((int(p[0], 16), 0))
    if "qty_birth" not in syms:
        raise SystemExit("alloc_probe: %s has no qty_birth symbol (stripped cc1?)" % cc1)
    anchor = syms["qty_birth"][0][0]
    return {n: min(v, key=lambda a: abs(a[0] - anchor)) for n, v in syms.items()}


def run_knob(row, text, knob, hard, cell, flags, table, keep=None):
    """One gdb compile of `text` with one knob applied. Returns assembly + the allocator's own result."""
    cc = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    addresses = {n: a for n, (a, _) in table.items()}
    cfg = dict(addresses=addresses, first_pseudo=FIRST.get(cell, 76), hard=hard,
               target=knob["target"], knob=dict(hook=knob["hook"], ops=knob["ops"], special=knob["special"]),
               block_alloc=[table["block_alloc"][0], table["block_alloc"][0] + table["block_alloc"][1]],
               compar=dict(sugg=table.get("qty_sugg_compare_1", (0, 0))[0],
                           main=table.get("qty_compare_1", (0, 0))[0]))
    t0 = time.time()
    with tempfile.TemporaryDirectory(prefix="allocprobe_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        pre = subprocess.run([str(cc / "gcc"), "-B" + str(cc) + "/", "-E", "-O2", *flags,
                              "-I" + str(ROOT / "include"), "-w", f.name, "-o", "f.i"],
                             cwd=d, capture_output=True, text=True, timeout=60)
        if pre.returncode:
            return dict(name=knob["name"], error="preprocess: " + pre.stderr[-400:], seconds=time.time() - t0)
        (d / "probe_config.json").write_text(json.dumps(cfg))
        (d / "probe.py").write_text(PROBE_SCRIPT)
        (d / "probe.gdb").write_text("set pagination off\nset confirm off\nset debuginfod enabled off\n"
                                     "set startup-with-shell off\nsource probe.py\n")
        try:
            run = subprocess.run(["gdb", "--batch", "--nx", "-x", "probe.gdb", "--args",
                                  str(cc / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-da", "-o", "f.s"],
                                 cwd=d, capture_output=True, text=True,
                                 timeout=float(os.getenv("ALLOC_PROBE_GDB_TIMEOUT", "180")))
        except subprocess.TimeoutExpired:
            return dict(name=knob["name"], error="gdb-timeout", seconds=time.time() - t0)
        res = json.loads((d / "probe_result.json").read_text()) if (d / "probe_result.json").exists() else {}
        asm = normalize((d / "f.s").read_text(errors="replace")) if (d / "f.s").exists() else None
        rtl = ""
        if keep:
            for name in keep:
                p = d / name
                rtl = p.read_text(errors="replace") if p.exists() else rtl
        hook_used, late = fallback_status(knob["hook"], res)
        return dict(name=knob["name"], hook=knob["hook"], special=knob["special"],
                    competitor=knob.get("competitor"), note=knob.get("note"),
                    assembly=asm, applied=res.get("applied", 0), hook_fired=res.get("hook_fired", 0),
                    hook_used=hook_used, applied_after_decision=late,
                    block_next_qty=res.get("block_next_qty"),
                    first_free_just_try_suggested=res.get("first_free_just_try_suggested"),
                    result=(res.get("results") or [[None, None]])[-1][1],
                    results=res.get("results"), forced=res.get("forced"),
                    gdb_events=res.get("events"), rtl=rtl,
                    error=None if res and run.returncode == 0 else (run.stderr or run.stdout)[-400:],
                    seconds=time.time() - t0)


def probe_site(row, text, pins, index, target=None, jobs=5, base=None):
    """Probe one ASM_REG site: the force oracle, every knob, and the no-op control."""
    t0 = time.time()
    cell, flags = parse_cfg(row["cfg"])
    site = pins[index]
    hard = hard_number(site[2])
    out = dict(row=row["id"], site=index, line=site[5], var=var_name(site[6]),
               register=site[2], hard=hard, cell=cell)
    if cell not in FIRST:
        out.update(status="non-stock-cell")
        return out
    target = target or observe(row, text)
    if target.get("error"):
        out.update(status="pinned-compile-failed", error=target["error"][:300])
        return out
    base = base or diagnose_site(row, text, pins, index, target=target)
    out["labels"] = base.get("labels")
    out["attempt_labels"] = base.get("attempt_labels")
    if not base.get("valid"):
        out.update(status=base.get("status") or "trace-invalid", error=(base.get("error") or "")[:300])
        return out
    erased = erase_many(text, [site], clean_notes=True)
    erased_obs = observe(row, erased)
    if erased_obs.get("error"):
        out.update(status="erased-compile-failed", error=erased_obs["error"][:300])
        return out
    P = target["assembly"]
    out["erased_distance"] = distance(P, erased_obs["assembly"])
    plan = plan_knobs(base, hard)
    if not plan:
        out.update(status="no-knob-plan")
        return out
    d = primary_entry(base)
    out["owner"] = d["owner"]
    out["pseudo"] = d["pseudo"]
    out["function"] = d["function"]
    out["competitor"] = competitor_record(base, d, hard)
    control = dict(name="control", hook="none", ops=[], special=None, target=plan[0]["target"], competitor=None)
    table = cc1_table(ROOT / "toolchain/compilers" / ("gcc-" + cell) / "cc1")
    runs = []
    with ThreadPoolExecutor(max_workers=max(1, min(jobs, MAX_JOBS))) as ex:
        # cc1 names its -da dumps after its INPUT file (f.i), so the rtl dump is f.i.rtl.
        futs = [ex.submit(run_knob, row, erased, control, hard, cell, flags, table, keep=["f.i.rtl"])]
        futs += [ex.submit(run_knob, row, erased, k, hard, cell, flags, table) for k in plan]
        for f in futs:
            runs.append(f.result())
    ctrl, knobs = runs[0], runs[1:]
    out["control"] = dict(equal_erased=ctrl.get("assembly") == erased_obs["assembly"],
                          result=ctrl.get("result"), error=ctrl.get("error"), seconds=ctrl.get("seconds"))
    names = pseudo_names(ctrl.get("rtl") or "", d["function"], erased)
    out["pseudo_name"] = out["var"]
    out["competitor_names"] = {}
    if not out["control"]["equal_erased"]:
        out.update(status="untrusted", seconds=time.time() - t0,
                   knobs=[{k: v for k, v in r.items() if k not in ("assembly", "rtl")} for r in knobs])
        return out
    sufficient = []
    for r in knobs:
        r["equal"] = r.get("assembly") is not None and r["assembly"] == P
        r["distance"] = distance(P, r.get("assembly"))
        r["changed_result"] = r.get("result") != ctrl.get("result")
        r["got_retail"] = r.get("result") == hard
        comp = r.get("competitor") or {}
        for key in ("pseudo", "pseudos"):
            for p in ([comp[key]] if key == "pseudo" and comp.get(key) is not None else (comp.get(key) or [])):
                if p in names:
                    out["competitor_names"].setdefault(r["name"], names[p])
        # a knob written after the decision it meant to change is not a test of that lever, whatever
        # assembly it produced: keep `equal`/`distance` on the run, but never call it sufficient.
        if r["equal"] and not r.get("applied_after_decision"):
            sufficient.append(r["name"])
        r.pop("assembly", None)
        r.pop("rtl", None)
    order = {n: i for i, n in enumerate(LOCAL_ORDER if out["owner"] == "local" else GLOBAL_ORDER)}
    sufficient.sort(key=lambda n: order.get(n, 99))
    forces = [r for r in knobs if r["name"] in ("force", "force-return")]
    out.update(status="ok", knobs=knobs, sufficient=sufficient,
               # erasing this pin alone already reproduces P: every knob is then trivially "sufficient",
               # so such a site is counted separately and kept out of the rates.
               erased_exact=out["erased_distance"] == 0,
               force_exact=any(r["equal"] for r in forces),
               force_variant=next((r["name"] for r in forces if r["equal"]), None),
               force_applied=any(r["hook_fired"] for r in forces),
               force_got_retail=any(r["got_retail"] for r in forces),
               minimal_knob=next((n for n in sufficient if n not in ("force", "force-return")), None),
               any_knob=bool([n for n in sufficient if n not in ("force", "force-return")]),
               seconds=time.time() - t0)
    return out


def probe_row(rid, source=None, site=None, jobs=5):
    row = next((r for r in rows() if r["id"] == rid), None)
    if row is None:
        raise SystemExit("alloc_probe: unknown row %s" % rid)
    text = Path(source).read_text() if source else clean_path(row).read_text()
    return probe_row_text(row, text, site=site, jobs=jobs), row, text


def probe_row_text(row, text, site=None, jobs=5):
    pins = sites_of(text)
    chosen = [site] if site is not None else [i for i, s in enumerate(pins) if s[1] == "ASM_REG"]
    target = observe(row, text) if chosen else None
    rep = dict(id=row["id"], cfg=row["cfg"], sha=sha_text(text), pins=len(pins),
               reg_sites=sum(s[1] == "ASM_REG" for s in pins), sites=[])
    for i in chosen:
        if i >= len(pins) or pins[i][1] != "ASM_REG":
            rep["sites"].append(dict(site=i, status="not-an-ASM_REG-site"))
            continue
        rep["sites"].append(probe_site(row, text, pins, i, target=target, jobs=jobs))
    return rep


def print_report(rep):
    print("%s  cfg %s  %d ASM_REG of %d pins" % (rep["id"], rep["cfg"], rep["reg_sites"], rep["pins"]))
    for s in rep["sites"]:
        print("site %d  line %s  %s  pinned %s  status %s  %.1fs"
              % (s["site"], s.get("line"), s.get("var"), s.get("register"), s.get("status"),
                 s.get("seconds") or 0))
        if s.get("status") != "ok":
            if s.get("error"):
                print("  error: %s" % s["error"][:200])
            continue
        print("  %s pseudo %s in %s   erased distance %s   labels %s"
              % (s["owner"], s["pseudo"], s["function"], s["erased_distance"], ",".join(s.get("labels") or [])))
        if s.get("erased_exact"):
            print("  PIN INERT: erasing this pin alone already reproduces P - every knob below is "
                  "trivially 'sufficient' and none of them is evidence")
        c = s.get("competitor") or {}
        print("  competitor: %s (source %s, earlier %s)"
              % (("qty %s" % c.get("qty")) if c.get("qty") is not None else
                 ("pseudo %s / allocno %s" % (c.get("pseudo"), c.get("allocno")) if c.get("found")
                  else "none - competitor knobs not planned"),
                 c.get("source"), c.get("earlier")))
        print("  force: %s (%s)   sufficient knobs: %s   minimal: %s"
              % ("EXACT" if s["force_exact"] else "no", s.get("force_variant") or "neither variant",
                 ", ".join(s["sufficient"]) or "none", s.get("minimal_knob") or "-"))
        for r in s["knobs"]:
            print("    %-18s %-10s applied=%d fired=%d result=%-5s %s%s"
                  % (r["name"], r.get("hook"), r.get("applied", 0), r.get("hook_fired", 0),
                     reg_name(r["result"]) if isinstance(r.get("result"), int) and r["result"] >= 0 else "-",
                     "EQUAL" if r.get("equal") else ("differs(%s)" % r.get("distance")
                                                     if r.get("distance") is not None else
                                                     "error: " + (r.get("error") or "?")[:80]),
                     "  [applied after the decision: not a test of this lever]"
                     if r.get("applied_after_decision") else ""))


# ------------------------------------------------------------------ calibration

def git_show(spec):
    p = subprocess.run(["git", "-C", str(ROOT), "show", spec], capture_output=True, text=True)
    return p.stdout if p.returncode == 0 else None


def choose_exemplars(n, max_bytes=3500, min_lines=0):
    """Smallest landed REG diffs first, stock cells only, at most one per row.

    `min_lines` raises the floor on changed lines: the smallest landed diffs are all one-declaration
    changes whose only touched variable is the pinned one, which makes the agreement question trivial,
    so a second sample of larger fixes is measured alongside them."""
    idx = ROOT / "work/native_lane/alloc_astra/evidence/exemplars_landed"
    R = {r["id"]: r for r in rows()}
    cands, seen, skipped = [], set(), collections.Counter()
    for e in parse_index((idx / "INDEX.md").read_text()):
        r = R.get(e["row"])
        if r is None:
            skipped["row gone"] += 1
            continue
        if parse_cfg(r["cfg"])[0] not in FIRST:
            skipped["non-stock cell"] += 1
            continue
        if e["row"] in seen:
            skipped["duplicate row"] += 1
            continue
        d = idx / e["diff"]
        if not d.is_file():
            skipped["diff missing"] += 1
            continue
        text = d.read_text(errors="replace")
        changed = sum(1 for l in text.splitlines() if l[:1] in "+-" and l[:2] not in ("++", "--"))
        removed = diff_removed_sites(text)
        if not removed:
            skipped["no removed ASM_REG site in the diff"] += 1
            continue
        seen.add(e["row"])
        cands.append(dict(e, changed_lines=changed, removed=removed, cell=parse_cfg(r["cfg"])[0],
                          variables=sorted(diff_variables(text)), row_bytes=r["size"]))
    cands.sort(key=lambda c: (c["changed_lines"], c["row"]))
    skipped["over the %d-byte row cap" % max_bytes] = sum(1 for c in cands if c["row_bytes"] > max_bytes)
    keep = [c for c in cands if c["row_bytes"] <= max_bytes]
    if min_lines:
        skipped["fewer than %d changed lines" % min_lines] = sum(1 for c in keep
                                                                 if c["changed_lines"] < min_lines)
        keep = [c for c in keep if c["changed_lines"] >= min_lines]
    return keep[:n], skipped, len(cands)


def calibrate(n, jobs, out_dir, min_lines=0, kind="calibration"):
    chosen, skipped, pool = choose_exemplars(n, min_lines=min_lines)
    recs = []
    for c in chosen:
        row = next(r for r in rows() if r["id"] == c["row"])
        pre = git_show("%s~1:src/%s.c" % (c["commit"], c["row"]))
        if pre is None:
            recs.append(dict(kind=kind, row=c["row"], commit=c["commit"], status="pre-fix-text-missing"))
            continue
        pins = sites_of(pre)
        want = {(v, r) for v, r in c["removed"]}
        idxs = [i for i, s in enumerate(pins)
                if s[1] == "ASM_REG" and (var_name(s[6]), s[2].strip('"').lstrip("$")) in want]
        if not idxs:
            recs.append(dict(kind=kind, row=c["row"], commit=c["commit"],
                             status="removed-site-not-found-in-pre-fix-text", removed=c["removed"]))
            continue
        target = observe(row, pre)
        for i in idxs[:2]:
            rec = probe_site(row, pre, pins, i, target=target, jobs=jobs)
            rec.update(kind=kind, commit=c["commit"], diff=c["diff"],
                       fix_variables=c["variables"], changed_lines=c["changed_lines"])
            rec["agreement"] = agreement(rec, c["variables"])
            recs.append(rec)
            write_jsonl(out_dir, rec)
    return recs, skipped, pool


def agreement(rec, fix_vars):
    """Does the knob name a variable the landed fix changed?"""
    if rec.get("status") != "ok":
        return "not-measured"
    fix = set(fix_vars)
    knob = rec.get("minimal_knob")
    if not rec.get("sufficient"):
        return "no-sufficient-knob"
    if rec.get("var") is None:
        return "no-binding"
    names = rec.get("competitor_names") or {}
    if knob and knob.startswith("competitor"):
        cname = names.get(knob)
        if cname is None:
            return "competitor-unnamed"
        return "competitor-variable-in-fix" if cname in fix else "no-overlap"
    if knob:
        return "same-variable" if rec["var"] in fix else "no-overlap"
    return "force-only"


def write_jsonl(out_dir, rec):
    p = Path(out_dir) / "calibration.jsonl"
    p.parent.mkdir(parents=True, exist_ok=True)
    with p.open("a") as f:
        f.write(json.dumps({k: v for k, v in rec.items() if k != "knobs"} |
                           {"knobs": [{k: v for k, v in r.items() if k not in ("gdb_events",)}
                                      for r in rec.get("knobs") or []]}, separators=(",", ":")) + "\n")


def population(n, jobs, traces, out_dir, seed=20260915, max_bytes=3500):
    """Current pinned sites from rows with 1-3 pins whose src sha still matches the trace."""
    R = {r["id"]: r for r in rows()}
    pool, skipped = [], collections.Counter()
    for f in sorted(Path(traces).glob("*.json")):
        t = json.loads(f.read_text())
        r = R.get(t.get("id"))
        if r is None or not clean_path(r).exists():
            skipped["row gone"] += 1
            continue
        text = clean_path(r).read_text(errors="replace")
        if sha_text(text) != t.get("sha"):
            skipped["source drifted since the trace"] += 1
            continue
        pins = sites_of(text)
        if not 1 <= len(pins) <= 3:
            skipped["not a 1-3 pin row"] += 1
            continue
        if parse_cfg(r["cfg"])[0] not in FIRST:
            skipped["non-stock cell"] += 1
            continue
        if r["size"] > max_bytes:
            skipped["over the %d-byte row cap" % max_bytes] += 1
            continue
        ok = True
        for s in t.get("sites") or []:
            i = s.get("site")
            if i is None or i >= len(pins) or (s.get("hard") is not None
                                               and s["hard"] != hard_number(pins[i][2])):
                ok = False
        if not ok:
            skipped["trace site index no longer aligns"] += 1
            continue
        for i, s in enumerate(pins):
            if s[1] == "ASM_REG":
                pool.append((t["id"], i))
    rnd = random.Random(seed)
    rnd.shuffle(pool)
    recs = []
    for rid, i in pool[:n]:
        row = R[rid]
        text = clean_path(row).read_text()
        pins = sites_of(text)
        rec = probe_site(row, text, pins, i, jobs=jobs)
        rec["kind"] = "population"
        recs.append(rec)
        write_jsonl(out_dir, rec)
    return recs, skipped, len(pool)


def summarise(recs):
    """The counts the brief asks for, over a list of site records."""
    c = collections.Counter()
    c["sites"] = len(recs)
    for r in recs:
        c["status:" + str(r.get("status"))] += 1
        if r.get("status") != "ok":
            continue
        c["trusted"] += 1
        if r.get("erased_distance") == 0:
            # the pin is inert at this site: the erased build already equals P, so no knob is evidence
            c["erase-alone-already-exact"] += 1
            continue
        c["live"] += 1
        if r.get("force_exact"):
            c["force-exact"] += 1
            c["force-variant:" + str(r.get("force_variant"))] += 1
        if r.get("any_knob"):
            c["one-knob"] += 1
            c["minimal:" + str(r.get("minimal_knob"))] += 1
        if r.get("agreement"):
            c["agreement:" + r["agreement"]] += 1
        for k in r.get("knobs") or []:
            if k.get("applied_after_decision"):
                c["knob-applied-after-decision"] += 1
            if k.get("error"):
                c["knob-error"] += 1
            elif not k.get("hook_fired"):
                c["knob-hook-never-fired"] += 1
            elif not k.get("changed_result"):
                c["knob-did-not-change-the-result"] += 1
    return c


def main():
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    ap.add_argument("row", nargs="?", help="row id, e.g. dungeon/func_81811388")
    ap.add_argument("--source", help="candidate .c to read instead of the row's current src text")
    ap.add_argument("--site", type=int, help="one site index from tools/pin_census.sites_of")
    ap.add_argument("--json", action="store_true")
    ap.add_argument("--out", help="write the full JSON report here")
    ap.add_argument("--jobs", type=int, default=5, help="concurrent gdb runs (max %d)" % MAX_JOBS)
    ap.add_argument("--calibrate", type=int, metavar="N", help="probe N landed pre-fix sites")
    ap.add_argument("--min-lines", type=int, default=0,
                    help="--calibrate: only diffs with at least this many changed lines (a second sample)")
    ap.add_argument("--population", type=int, metavar="N", help="probe N current pinned sites")
    ap.add_argument("--traces", default=str(ROOT / "work/alloc_retrace/raw"))
    ap.add_argument("--out-dir", default=str(ROOT / "work/alloc_probe"))
    args = ap.parse_args()
    try:
        os.nice(10)
    except OSError:
        pass
    if args.calibrate:
        kind = "calibration" if not args.min_lines else "calibration-large"
        recs, skipped, pool = calibrate(args.calibrate, args.jobs, args.out_dir, args.min_lines, kind)
        print(json.dumps(dict(kind=kind, pool=pool, skipped=dict(skipped),
                              counts=dict(summarise(recs))), indent=2))
        return
    if args.population:
        recs, skipped, pool = population(args.population, args.jobs, args.traces, args.out_dir)
        print(json.dumps(dict(kind="population", pool=pool, skipped=dict(skipped),
                              counts=dict(summarise(recs))), indent=2))
        return
    if not args.row:
        raise SystemExit("alloc_probe: give a row id, --calibrate N or --population N")
    rep, _, _ = probe_row(args.row, args.source, args.site, args.jobs)
    if args.out:
        Path(args.out).write_text(json.dumps(rep, separators=(",", ":")) + "\n")
    if args.json:
        print(json.dumps(rep, indent=2))
    else:
        print_report(rep)


if __name__ == "__main__":
    main()
