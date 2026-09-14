#!/usr/bin/env python3
"""Allocator trace: read the stock GCC 2.x register allocator's ACTUAL state for one pinned ASM_REG site.

    python3 tools/alloc_trace.py <row_id> [--source <cand.c>] [--site N] [--out trace.json] [--json]

Harvested from the alloc_astra lane (2026-09-14, tools/allocator_gdb.py + global_enrich.py +
trace_classify.py + the binding half of alloc_inputs.diagnose). For each ASM_REG site it compiles the
text twice with -da (pinned, and the same text with that one pin erased), binds the pin's hard register
to the pseudo the erased build uses for it (user-variable flagged (reg ...) correspondence in sched, or
rtl when sched has none), then runs the cell's own unstripped i386 cc1 under gdb with breakpoints on
local-alloc's find_free_reg / block_alloc and global.c's dump_conflicts / find_reg, and reads out of the
compiler's memory:

  local   qty_birth/death/size/mode/n_refs/n_calls_crossed, qty_phys_sugg and qty_phys_copy_sugg
          (three 32-bit words per hard-reg set), the reg_next_in_qty pseudo chain, regs_live_at at the
          quantity's birth..death, and every find_free_reg attempt in order with its returned register
  global  allocno_order/reg/size/n_refs/live_length/calls_crossed, hard_reg_conflicts,
          hard_reg_preferences, hard_reg_copy_preferences, and each find_reg attempt with
          regs_used_so_far / regs_someone_prefers / no_global_alloc_regs and the reg_renumber result

and prints, per site, which of those decided the pinned register. Stock lreg prints assignments and flow
statistics but NOT the qty vectors, so gdb is the only way to see the allocator's inputs.

Requires gdb and unstripped cc1 symbols (`nm -S toolchain/compilers/gcc-<cell>/cc1` must find qty_birth;
duplicate local symbols are resolved by taking the copy nearest qty_birth, which avoids CSE's unrelated
same-named statics). Per-cell FIRST_PSEUDO_REGISTER, as the lane recorded it: 2.6.3 = 67, 2.7.2 = 68,
2.7.2-cdk = 76, 2.8.0 = 76, 2.8.1 = 76.

ANALYSIS ONLY. No byte score is computed here and nothing is written to src/: tools/verify.py is the
only exactness authority. A trace is trusted only when the traced compile's assembly equals a normal
compile of the same text (`assembly_equal`) and `errors` is empty; an untrusted site prints its error
and no diagnosis. Cost: one full-dump compile for the row plus, per site, one compile and one gdb run:
0.4 s for the single site of a 56-byte row (dungeon/func_81811388), ~1.7 s per site on a 4.9 KB one
(dungeon/func_819A1654, 16 sites in 27 s). One cc1/gdb at a time.

Reason labels are the lane's taxonomy (evidence/trace_sites.jsonl). `reasons` comes from the pass dumps
plus the local quantity trace; for a global owner `attempt_reasons` adds the finer find_reg reading that
the lane ran only over its census subset (so a global site the lane left unenriched shows
"global-competition-or-scan-unresolved" under `reasons` and a specific cause under `attempt_reasons`).

Runs one cc1/gdb at a time; there is deliberately no --jobs. All compiler input, -da dumps and gdb
scripts live in one automatically deleted tempfile directory (honours TMPDIR); cc1 runs with cwd there.
--out embeds every site's whole trace (3.2 MB for the 16 sites of dungeon/func_819A1654), so keep it
outside the work/ subtrees that agents search; --json prints the same report without the traces.
"""
import argparse
import collections
import difflib
import json
import os
from pathlib import Path
import re
import subprocess
import sys
import tempfile

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
from common import rows, clean_path, parse_cfg, sha_text
from pin_census import sites_of
from pin_sites import erase_many
from xform.reg_state import features
from xform.sched_trace import normalize

# FIRST_PSEUDO_REGISTER per stock cell, read out of the compilers themselves by the alloc_astra lane.
FIRST = {"2.6.3": 67, "2.7.2": 68, "2.7.2-cdk": 76, "2.8.0": 76, "2.8.1": 76}
PHASES = ("rtl", "jump", "cse", "loop", "cse2", "flow", "combine", "regmove", "sched", "lreg", "greg", "sched2")
REG = re.compile(r"\(reg(?P<flags>/\w+)?:([A-Z0-9]+) (\d+)(?: [^)]+)?\)")
STAT = re.compile(r"^Register (\d+) used (\d+) times across (-?\d+) insns([^\n]*)", re.M)

GPR = ("$zero $at $v0 $v1 $a0 $a1 $a2 $a3 $t0 $t1 $t2 $t3 $t4 $t5 $t6 $t7 "
       "$s0 $s1 $s2 $s3 $s4 $s5 $s6 $s7 $t8 $t9 $k0 $k1 $gp $sp $fp $ra").split()


def reg_name(n):
    """Hard register number -> MIPS name; r<N> for anything cell-specific (66+) or a pseudo."""
    if 0 <= n < 32:
        return GPR[n]
    if 32 <= n < 64:
        return "$f%d" % (n - 32)
    if n == 64:
        return "$hi"
    if n == 65:
        return "$lo"
    return "r%d" % n


def reg_names(ns):
    return ",".join(reg_name(n) for n in ns) if ns else "-"


def hard_number(arg):
    """The ASM_REG macro's register argument ('$v0', '"2"', 'a1', '$s0') as a hard register number.

    -1 means the spelling was not understood, which the caller must report as such: a site that failed
    to parse binds nothing, and 'nothing bound' would otherwise read as an allocator fact."""
    s = arg.strip("$\"")
    if s.isdigit():
        return int(s)
    if "$" + s in GPR:
        return GPR.index("$" + s)
    return {"hi": 64, "lo": 65, "s8": 30}.get(s, -1)


def regclass(n):
    return "argument" if 4 <= n <= 7 else "return" if n in (2, 3) else "saved" if 16 <= n <= 23 else "other"


def var_name(decl):
    """The declared name in an ASM_REG declaration, function pointers included:
    'register s32 value' -> value, 'register int (*callback)(void *)' -> callback."""
    if not decl:
        return None
    m = re.search(r"\(\s*\*+\s*([A-Za-z_]\w*)\s*\)", decl)
    if m:
        return m[1]
    ids = re.findall(r"[A-Za-z_]\w*", decl)
    return ids[-1] if ids else None


# ---------------------------------------------------------------- stock dumps

def parse_comments(dumps, first=68):
    """lreg/greg/flow comment state per function: flow statistics, local assignments, global order,
    conflicts, preferences, dispositions, and reg<->pseudo copies (potential suggestions, not the
    qty_phys_* vectors, which only the debugger can see)."""
    result = {}
    # Function names prevent cross-function pseudo-number collisions.
    for phase, src in dumps.items():
        chunks = re.split(r"^;; Function (\S+)[^\n]*\n", src, flags=re.M)
        for k in range(1, len(chunks), 2):
            name, s = chunks[k:k + 2]
            f = result.setdefault(name, dict(first_pseudo=first, stats={}, local={}, global_order=[],
                                             conflicts={}, preferences={}, assigned={}, copies=[], stat_phase=None))
            if phase in ("flow", "sched", "lreg"):
                stats = {}
                for m in STAT.finditer(s):
                    n, refs, live = int(m[1]), int(m[2]), int(m[3])
                    tail = m[4]

                    def num(p, default, tail=tail):
                        z = re.search(p, tail)
                        return int(z[1]) if z else default

                    stats[n] = dict(refs=refs, live=live, block=num(r"in block (\d+)", -1),
                                    deaths=num(r"dies in (\d+) places", 1), calls=num(r"crosses (\d+) calls?", 0),
                                    bytes=num(r"(\d+) bytes", 4),
                                    regclass=tail.split("; pref ", 1)[-1].split(";")[0] if "; pref " in tail
                                    else ("restricted" if "or none" in tail else "default"))
                if stats:
                    f["stats"] = stats
                    f["stat_phase"] = phase
            if phase == "lreg":
                f["local"] = {int(n): int(h) for n, h in re.findall(r";; Register (\d+) in (\d+)\.", s)}
                for pat in features(s)["raw"]:
                    if re.fullmatch(r"\(set \(reg[^)]*\) \(reg[^)]*\)\)", pat):
                        rr = [int(m[3]) for m in REG.finditer(pat)]
                        if len(rr) == 2 and (rr[0] < first) != (rr[1] < first):
                            f["copies"].append(rr)
            if phase == "greg":
                order = re.search(r";; \d+ regs to allocate:([^\n]*)", s)
                if order:
                    f["global_order"] = [int(x.split("+")[0])
                                         for x in re.findall(r"\d+(?:\+\d+)*", re.sub(r"\(\d+\)", "", order[1]))]
                for key in ("conflicts", "preferences"):
                    f[key] = {int(n): list(map(int, re.findall(r"\d+", v)))
                              for n, v in re.findall(r";; (\d+) " + key + r":([^\n]*)", s)}
                disp = re.search(r";; Register dispositions:([\s\S]*?)(?:;; Hard regs used:|\Z)", s)
                if disp:
                    f["assigned"] = {int(n): int(h) for n, h in re.findall(r"(\d+) in (\d+)", disp[1])}
    return result


def observe(row, text):
    """Compile text in its own cell with -da in a temp dir and return normalized asm + dump state."""
    cell, flags = parse_cfg(row["cfg"])
    cc = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    with tempfile.TemporaryDirectory(prefix="alloctrace_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        cmd = [str(cc / "gcc"), "-B" + str(cc) + "/", "-S", "-O2", *flags,
               "-I" + str(ROOT / "include"), "-w", "-da", f.name, "-o", "f.s"]
        try:
            p = subprocess.run(cmd, cwd=d, capture_output=True, text=True,
                               timeout=float(os.getenv("ALLOC_TRACE_TIMEOUT", "45")))
        except subprocess.TimeoutExpired:
            return dict(assembly=None, error="compiler-timeout", state={}, patterns={})
        if p.returncode or not (d / "f.s").is_file():
            return dict(assembly=None, error=(p.stderr or p.stdout)[-1000:], state={}, patterns={})
        ds = {q.suffix[1:]: q.read_text(errors="replace") for q in d.iterdir() if q.suffix[1:] in PHASES}
        ds = {p2: ds[p2] for p2 in PHASES if p2 in ds}
        patterns = {}
        for phase in ("rtl", "sched", "lreg"):
            chunks = re.split(r"^;; Function (\S+)[^\n]*\n", ds.get(phase, ""), flags=re.M)
            for k in range(1, len(chunks), 2):
                patterns.setdefault(chunks[k], {})[phase] = features(chunks[k + 1])["raw"]
        return dict(assembly=normalize((d / "f.s").read_text(errors="replace")), error=None,
                    state=parse_comments(ds, FIRST.get(cell, 76)), patterns=patterns, cell=cell)


# ------------------------------------------------------- pinned/erased binding

def shape(p):
    return REG.sub(lambda m: "(reg:" + m[2] + ")", p)


def aligned(a, b):
    aa, bb = list(map(shape, a)), list(map(shape, b))
    if aa == bb:
        return list(zip(a, b)), True
    pairs = []
    for block in difflib.SequenceMatcher(None, aa, bb, autojunk=False).get_matching_blocks():
        pairs.extend(zip(a[block.a:block.a + block.size], b[block.b:block.b + block.size]))
    return pairs, False


def owner_of(f, n):
    if n < f.get("first_pseudo", 68):
        return "hard"
    if n in f["local"]:
        return "local"
    if n in f["global_order"]:
        return "global"
    return "unassigned-or-eliminated"


def dump_priority(s):
    refs, live = s.get("refs", 0), s.get("live", 0)
    return int((refs.bit_length() - 1) * refs * max(1, (s.get("bytes", 4) + 3) // 4) * 10000 / live) \
        if refs > 0 and live > 0 else None


def bind(target, cand, hard):
    """Which pseudo of the ERASED build carries the value the pinned build holds in `hard`.

    The binding half of the lane's alloc_inputs.diagnose: align the two builds' instruction patterns by
    register-anonymised shape, and count user-variable (reg .../v) operands that are `hard` on the pinned
    side and a pseudo on the erased side. sched is the anchor (after the pin's scheduling effect, before
    allocation); rtl is the fallback when sched shows nothing, and then both sides must be /v."""
    bound = []
    for fn, bs in cand["state"].items():
        if fn not in target["state"]:
            continue
        ap = target["patterns"].get(fn, {})
        bp = cand["patterns"].get(fn, {})
        phase = "sched" if ap.get("sched") and bp.get("sched") else "lreg"
        pairs, _ = aligned(ap.get(phase, []), bp.get(phase, []))
        anchor = phase
        counts = collections.Counter()
        for pa, pb in pairs:
            for ra, rb in zip(REG.finditer(pa), REG.finditer(pb)):
                if int(ra[3]) == hard and "v" in (ra["flags"] or "") and int(rb[3]) >= bs.get("first_pseudo", 68):
                    counts[int(rb[3])] += 1
        if not counts:
            anchor = "rtl"
            rp, _ = aligned(ap.get("rtl", []), bp.get("rtl", []))
            for pa, pb in rp:
                for ra, rb in zip(REG.finditer(pa), REG.finditer(pb)):
                    if int(ra[3]) == hard and "v" in (ra["flags"] or "") \
                            and int(rb[3]) >= bs.get("first_pseudo", 68) and "v" in (rb["flags"] or ""):
                        counts[int(rb[3])] += 1
        for r, n in counts.most_common():
            st = bs["stats"].get(r, {})
            bound.append(dict(function=fn, pseudo=r, anchor=anchor, evidence_occurrences=n,
                              owner=owner_of(bs, r), assigned=bs["assigned"].get(r), stats=st,
                              global_priority_proxy=dump_priority(st),
                              hard_conflict=hard in bs["conflicts"].get(r, []),
                              preference=hard in bs["preferences"].get(r, []),
                              potential_copies=[x for x in bs["copies"] if r in x]))
    return bound


# ------------------------------------------------------------------- the trace

# Runs inside gdb's own python. Reads only memory; never writes compiler state.
GDB_SCRIPT = r'''
import gdb,json,struct
C=json.load(open('trace_config.json'));A=C['addresses'];FIRST=C['first_pseudo']
events=[];blocks=[];globals_=[];global_attempts=[];current=None
mem=lambda a,n:bytes(gdb.selected_inferior().read_memory(a,n))
def integer(a):return struct.unpack('<i',mem(a,4))[0]
def pointer(n):return struct.unpack('<I',mem(A[n],4))[0]
def scalar(n):return integer(A[n])
def function_name():return mem(pointer('current_function_name'),128).split(b'\x00')[0].decode(errors='replace')
def vec(n,count,short=False):
    if count==0:return []
    return list(struct.unpack('<'+('h' if short else 'i')*count,mem(pointer(n),count*(2 if short else 4))))
def mask(addr):
    w=struct.unpack('<III',mem(addr,12));return [n for n in range(FIRST) if w[n//32]&(1<<(n%32))]
def sets(n,count):return [mask(pointer(n)+12*i) for i in range(count)]
def args(n):
    sp=int(gdb.parse_and_eval('$esp'));return [integer(sp+4*(i+1)) for i in range(n)]
class Block(gdb.Breakpoint):
    def stop(self):
        global current
        current={'function':function_name(),'block':args(1)[0],'quantities':None,'attempts':[]};blocks.append(current);return False
class Result(gdb.FinishBreakpoint):
    def __init__(self,e):
        super().__init__(gdb.newest_frame(),internal=True);self.e=e
    def stop(self):
        v=int(gdb.parse_and_eval('$eax'))&0xffffffff;self.e['result']=v if v<0x80000000 else v-0x100000000;return False
class Free(gdb.Breakpoint):
    def stop(self):
        try:
            aa=args(7);n=scalar('next_qty');q=aa[2]
            if current['quantities'] is None:
                names=['qty_birth','qty_death','qty_size','qty_mode','qty_n_refs','qty_n_calls_crossed','qty_first_reg','qty_min_class','qty_alternate_class']
                vv={name:vec(name,n) for name in names}
                vv.update({name:vec(name,n,True) for name in ['qty_phys_reg','qty_phys_num_copy_sugg','qty_phys_num_sugg']})
                vv.update({name:sets(name,n) for name in ['qty_phys_copy_sugg','qty_phys_sugg']})
                qq=[]
                for i in range(n):
                    rec={name.removeprefix('qty_'):v[i] for name,v in vv.items()};rec['qty']=i
                    r=rec['first_reg'];chain=[]
                    while r>=FIRST and len(chain)<500 and r not in chain:
                        chain.append(r);r=integer(pointer('reg_next_in_qty')+4*r)
                    rec['pseudos']=chain
                    refs=rec['n_refs'];live=rec['death']-rec['birth']
                    rec['priority']=int(((refs.bit_length()-1)*refs*rec['size']/live)*10000) if refs>0 and live>0 else None
                    qq.append(rec)
                current['quantities']=qq
                current['initial_occupied']={str(rec['qty']):sorted(set(n for j in range(max(0,rec['birth']),max(0,rec['death'])) for n in mask(pointer('regs_live_at')+12*j))) for rec in qq}
                current['fixed']=mask(A['fixed_reg_set']);current['call_used']=mask(A['call_used_reg_set'])
            occupied=set()
            if aa[5]>=0 and aa[6]>=aa[5]:
                for i in range(aa[5],aa[6]):occupied.update(mask(pointer('regs_live_at')+12*i))
            e=dict(qty=q,regclass=aa[0],mode=aa[1],accept_call_clobbered=aa[3],suggestions_only=aa[4],birth=aa[5],death=aa[6],occupied=sorted(occupied))
            current['attempts'].append(e);Result(e)
        except Exception as e:events.append(str(e))
        return False
class Global(gdb.Breakpoint):
    def stop(self):
        try:
            n=scalar('max_allocno');names=['allocno_order','allocno_reg','allocno_size','allocno_calls_crossed','allocno_n_refs','allocno_live_length']
            g={k:vec(k,n) for k in names};g['function']=function_name()
            for k in ['hard_reg_conflicts','hard_reg_preferences','hard_reg_copy_preferences']:g[k]=sets(k,n)
            globals_.append(g)
        except Exception as e:events.append(str(e))
        return False
class GlobalResult(gdb.FinishBreakpoint):
    def __init__(self,e):super().__init__(gdb.newest_frame(),internal=True);self.e=e
    def stop(self):
        self.e['result']=struct.unpack('<h',mem(pointer('reg_renumber')+2*self.e['pseudo'],2))[0];return False
class GlobalFind(gdb.Breakpoint):
    def stop(self):
        try:
            aa=args(5);i=aa[0];n=scalar('max_allocno')
            e=dict(function=function_name(),allocno=i,pseudo=integer(pointer('allocno_reg')+4*i),alternate=aa[2],accept_call_clobbered=aa[3],retry=aa[4])
            # All five stock cells export these; a cell that did not must degrade the explanation, not the trace.
            for name in ['hard_reg_conflicts','hard_reg_preferences','hard_reg_copy_preferences','regs_someone_prefers']:
                e[name]=mask(pointer(name)+12*i) if name in A else []
            for name in ['fixed_reg_set','call_used_reg_set','no_global_alloc_regs','regs_used_so_far']:e[name]=mask(A[name]) if name in A else []
            e['calls']=integer(pointer('allocno_calls_crossed')+4*i)
            global_attempts.append(e);GlobalResult(e)
        except Exception as e:events.append(str(e))
        return False
Block('*'+str(A['block_alloc']),internal=True);Free('*'+str(A['find_free_reg']),internal=True)
if 'dump_conflicts' in A:Global('*'+str(A['dump_conflicts']),internal=True)
if 'find_reg' in A:GlobalFind('*'+str(A['find_reg']),internal=True)
gdb.execute('run')
json.dump(dict(blocks=blocks,global_states=globals_,global_attempts=global_attempts,errors=events),open('allocator_trace.json','w'),separators=(',',':'))
'''


def cc1_symbols(cc1):
    """Symbol addresses from the unstripped i386 cc1. Duplicated local symbols (CSE has its own
    same-named statics) are resolved by taking the copy nearest qty_birth."""
    out = subprocess.run(["nm", "-S", str(cc1)], capture_output=True, text=True, check=True).stdout
    symbols = {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4:
            symbols.setdefault(p[3], []).append(int(p[0], 16))
    if "qty_birth" not in symbols:
        raise SystemExit("alloc_trace: %s has no qty_birth symbol (stripped cc1?)" % cc1)
    anchor = symbols["qty_birth"][0]
    return {n: min(v, key=lambda a: abs(a - anchor)) for n, v in symbols.items()}


def trace(row, text, normal_assembly, retain=None):
    """Run the cell's cc1 on `text` under gdb and read the allocator's state out of its memory.

    normal_assembly is the normalized assembly of an ordinary compile of the same text: the driver's
    predefines and cc1 options differ in some cells, so the traced listing is compared with it and the
    state is trusted only when they are equal."""
    cell, flags = parse_cfg(row["cfg"])
    cc = ROOT / "toolchain/compilers" / ("gcc-" + cell)
    addresses = cc1_symbols(cc / "cc1")
    with tempfile.TemporaryDirectory(prefix="alloctrace_gdb_") as td:
        d = Path(td)
        f = d / Path(row["c_path"]).name
        f.write_text(text)
        pre = subprocess.run([str(cc / "gcc"), "-B" + str(cc) + "/", "-E", "-O2", *flags,
                              "-I" + str(ROOT / "include"), "-w", f.name, "-o", "f.i"],
                             cwd=d, capture_output=True, text=True, timeout=45)
        if pre.returncode:
            return dict(error=pre.stderr[-2000:], assembly_equal=False)
        (d / "trace_config.json").write_text(json.dumps(dict(addresses=addresses,
                                                            first_pseudo=FIRST.get(cell, 76))))
        (d / "trace.py").write_text(GDB_SCRIPT)
        (d / "trace.gdb").write_text("set pagination off\nset confirm off\nset debuginfod enabled off\n"
                                     "set startup-with-shell off\nsource trace.py\n")
        run = subprocess.run(["gdb", "--batch", "--nx", "-x", "trace.gdb", "--args",
                              str(cc / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-da", "-o", "f.s"],
                             cwd=d, capture_output=True, text=True,
                             timeout=float(os.getenv("ALLOC_TRACE_GDB_TIMEOUT", "120")))
        result = json.loads((d / "allocator_trace.json").read_text()) if (d / "allocator_trace.json").exists() else {}
        result["error"] = None if result and run.returncode == 0 else run.stderr[-2000:]
        asm = (d / "f.s").read_text(errors="replace") if (d / "f.s").exists() else ""
        result["assembly_equal"] = bool(asm) and normalize(asm) == normal_assembly
        if retain:
            dest = Path(retain)
            dest.mkdir(parents=True, exist_ok=True)
            for name in ("f.s", "allocator_trace.json", "trace_config.json", "trace.py", "trace.gdb"):
                if (d / name).exists():
                    (dest / name).write_bytes((d / name).read_bytes())
            (dest / "gdb.log").write_text(run.stdout + "\n" + run.stderr)
        return result


# ------------------------------------------------------------------ diagnosis

def target_reason(tr, bound, hard):
    """Why the erased build's pseudo did not land in `hard` (the lane's trace_classify taxonomy)."""
    fn, pseudo, owner = bound["function"], bound["pseudo"], bound["owner"]
    if owner == "local":
        found = []
        for block in tr.get("blocks", []):
            if block.get("function") != fn:
                continue
            for q in block.get("quantities") or []:
                if pseudo not in q["pseudos"]:
                    continue
                attempts = [a for a in block["attempts"] if a["qty"] == q["qty"]]
                accepted = [a for a in attempts if a.get("result", -1) >= 0]
                if not accepted:
                    continue
                a = accepted[-1]
                reason, competitors = [], []
                initial = block["initial_occupied"].get(str(q["qty"]), [])
                if hard in block["fixed"]:
                    reason.append("fixed-register-exclusion")
                if q["n_calls_crossed"] and hard in block["call_used"] and not a["accept_call_clobbered"]:
                    reason.append("call-clobber-exclusion")
                if hard in initial:
                    reason.append("preexisting-hard-conflict")
                if hard in a["occupied"] and hard not in initial:
                    for z in block["quantities"]:
                        if z["qty"] == q["qty"] or max(z["birth"], q["birth"]) >= min(z["death"], q["death"]):
                            continue
                        prior = []
                        for aa in block["attempts"]:
                            if aa is a:
                                break
                            if aa["qty"] == z["qty"] and aa.get("result") == hard:
                                prior.append(aa)
                        if prior:
                            competitors.append(dict(qty=z["qty"], pseudos=z["pseudos"], priority=z["priority"],
                                                    target_priority=q["priority"],
                                                    same_priority=z["priority"] == q["priority"],
                                                    suggested=bool(z["phys_copy_sugg"] or z["phys_sugg"])))
                    reason.append("earlier-quantity-conflict")
                if not reason and a["result"] != hard:
                    reason.append("suggestion-selection" if a["suggestions_only"] else "hard-register-scan-order")
                if a["result"] == hard:
                    reason.append("target-register-already-selected")
                found.append(dict(owner=owner, reasons=reason, function=fn, pseudo=pseudo, block=block["block"],
                                  quantity=q, attempt=a, competitors=competitors))
        return found or [dict(owner=owner, reasons=["local-trace-unmapped"], pseudo=pseudo)]
    if owner == "global":
        found = []
        for g in tr.get("global_states", []):
            if g.get("function") != fn or pseudo not in g["allocno_reg"]:
                continue
            i = g["allocno_reg"].index(pseudo)
            reason = []
            h, prefs = g["hard_reg_conflicts"][i], g["hard_reg_preferences"][i]
            if hard in h:
                reason.append("global-hard-conflict")
            if g["allocno_calls_crossed"][i] and hard in list(range(16)) + [24, 25, 26, 27, 28, 29, 31]:
                reason.append("call-clobber-exclusion")
            if prefs and hard not in prefs:
                reason.append("other-global-preference")
            if not reason:
                reason.append("global-competition-or-scan-unresolved")
            found.append(dict(owner=owner, reasons=reason, function=fn, pseudo=pseudo, allocno=i,
                              order=g["allocno_order"].index(i), refs=g["allocno_n_refs"][i],
                              live=g["allocno_live_length"][i], calls=g["allocno_calls_crossed"][i],
                              preferences=prefs, copy_preferences=g["hard_reg_copy_preferences"][i],
                              hard_conflicts=h))
        return found or [dict(owner=owner, reasons=["global-trace-unmapped"], pseudo=pseudo)]
    return [dict(owner=owner, reasons=["pseudo-eliminated-before-allocation"], pseudo=pseudo)]


def attempt_reason(tr, bound, hard):
    """The finer global reading: the actual find_reg attempt that assigned the pseudo (global_enrich)."""
    fn, pseudo = bound["function"], bound["pseudo"]
    ats = [a for a in tr.get("global_attempts", [])
           if a["function"] == fn and a["pseudo"] == pseudo and a.get("result", -1) >= 0]
    if not ats:
        return dict(reasons=["no-successful-global-attempt"], pseudo=pseudo)
    a = ats[-1]
    g = next((g for g in tr["global_states"] if g["function"] == fn and pseudo in g["allocno_reg"]), None)
    initial = g["hard_reg_conflicts"][g["allocno_reg"].index(pseudo)] if g else []
    reasons, competitors = [], []
    if a["result"] == hard:
        reasons.append("target-register-already-selected")
    else:
        if hard in a["fixed_reg_set"] or hard in a["no_global_alloc_regs"]:
            reasons.append("global-fixed-or-frame-exclusion")
        if a["calls"] and hard in a["call_used_reg_set"] and not a["accept_call_clobbered"]:
            reasons.append("call-clobber-exclusion")
        if hard in initial:
            reasons.append("preexisting-hard-or-local-conflict")
        elif hard in a["hard_reg_conflicts"]:
            reasons.append("earlier-global-conflict")
            for z in tr["global_attempts"]:
                if z is a:
                    break
                if z["function"] == fn and z.get("result") == hard and g and z["pseudo"] in g["allocno_reg"]:
                    i, j = g["allocno_reg"].index(z["pseudo"]), g["allocno_reg"].index(pseudo)

                    def priority(k):
                        refs, live = g["allocno_n_refs"][k], g["allocno_live_length"][k]
                        return int(((refs.bit_length() - 1) * refs / live) * 10000 * g["allocno_size"][k]) \
                            if refs > 0 and live > 0 else None

                    competitors.append(dict(pseudo=z["pseudo"], priority=priority(i), target_priority=priority(j),
                                            same_priority=priority(i) == priority(j),
                                            preferences=z["hard_reg_preferences"]))
        if not reasons:
            if a["result"] in a["hard_reg_copy_preferences"]:
                reasons.append("global-copy-preference-selection")
            elif a["result"] in a["hard_reg_preferences"]:
                reasons.append("global-preference-selection")
            elif hard not in a["regs_used_so_far"] and a["result"] in a["regs_used_so_far"]:
                reasons.append("already-used-register-selection")
            elif hard in a["regs_someone_prefers"]:
                reasons.append("lower-priority-preference-reservation")
            else:
                reasons.append("global-scan-order-or-class")
    return dict(function=fn, pseudo=pseudo, hard=hard, reasons=reasons, attempt=a, competitors=competitors)


# -------------------------------------------------------------------- one site

def diagnose_site(row, text, pins, index, retain=None, target=None):
    """Erase pin `index` alone, bind its hard register to a pseudo, and trace that compile."""
    site = pins[index]
    hard = hard_number(site[2])
    rec = dict(site=index, line=site[5], var=var_name(site[6]),
               register=site[2], hard=hard, register_class=regclass(hard))
    if hard < 0:
        rec.update(valid=False, error="unparsed-register " + site[2])
        return rec
    if target is None:
        target = observe(row, text)
    if target["error"]:
        rec.update(valid=False, error="pinned-compile: " + target["error"])
        return rec
    erased = erase_many(text, [site], clean_notes=True)
    cand = observe(row, erased)
    if cand["error"]:
        rec.update(valid=False, error="erased-compile: " + cand["error"])
        return rec
    bound = bind(target, cand, hard)
    rec["bound"] = bound
    rec["bound_count"] = len(bound)
    if not bound:
        rec.update(valid=False, status="unmapped-binding", reasons=[])
        return rec
    tr = trace(row, erased, cand["assembly"], retain=retain)
    rec["assembly_equal"] = bool(tr.get("assembly_equal"))
    rec["trace_errors"] = tr.get("errors")
    rec["error"] = tr.get("error")
    rec["valid"] = bool(tr.get("assembly_equal") and not tr.get("error") and not tr.get("errors"))
    if not rec["valid"]:
        return rec
    rec["reasons"] = [r for b in bound for r in target_reason(tr, b, hard)]
    rec["attempt_reasons"] = [attempt_reason(tr, b, hard) for b in bound if b["owner"] == "global"]
    rec["labels"] = sorted({k for d in rec["reasons"] for k in d["reasons"]})
    rec["attempt_labels"] = sorted({k for d in rec["attempt_reasons"] for k in d["reasons"]})
    rec["trace"] = tr
    return rec


# ---------------------------------------------------------------------- report

def print_site(rec):
    head = "site %d  line %s  %s  pinned %s (r%d, %s)" % (
        rec["site"], rec["line"], rec.get("var") or "?", reg_name(rec["hard"]), rec["hard"], rec["register_class"])
    print(head)
    if rec.get("status") == "unmapped-binding":
        print("  no pseudo bound to the pinned register in the erased build (unmapped-binding)")
        return
    if not rec.get("valid"):
        print("  NOT VALID  assembly_equal=%s  error=%s  trace_errors=%s"
              % (rec.get("assembly_equal"), (rec.get("error") or "")[:200], rec.get("trace_errors")))
        return
    by_pseudo = {}
    for d in rec.get("attempt_reasons", []):
        by_pseudo.setdefault(d.get("pseudo"), []).append(d)
    for d in rec["reasons"]:
        owner = d["owner"]
        print("  erased pseudo %s in %s  owner=%s" % (d["pseudo"], d.get("function", "?"), owner))
        if owner == "local":
            q, a = d["quantity"], d["attempt"]
            print("    quantity %d in block %d  refs %d  live %d (birth %d death %d)  calls %d  size %d  priority %s"
                  % (q["qty"], d["block"], q["n_refs"], q["death"] - q["birth"], q["birth"], q["death"],
                     q["n_calls_crossed"], q["size"], q["priority"]))
            print("    suggestions %s  copy-suggestions %s  got %s%s"
                  % (reg_names(q["phys_sugg"]), reg_names(q["phys_copy_sugg"]),
                     reg_name(a["result"]) if a.get("result", -1) >= 0 else "none",
                     "  (suggestions-only attempt)" if a.get("suggestions_only") else ""))
            print("    occupied at the attempt %s" % reg_names(a["occupied"]))
            for z in d.get("competitors", []):
                print("    competitor quantity %d (pseudos %s) priority %s vs %s%s%s"
                      % (z["qty"], z["pseudos"], z["priority"], z["target_priority"],
                         "  same-priority" if z["same_priority"] else "",
                         "  suggested" if z["suggested"] else ""))
        elif owner == "global":
            print("    allocno %s order %s  refs %s  live length %s  calls crossed %s"
                  % (d.get("allocno"), d.get("order"), d.get("refs"), d.get("live"), d.get("calls")))
            print("    preferences %s  copy-preferences %s"
                  % (reg_names(d.get("preferences") or []), reg_names(d.get("copy_preferences") or [])))
            print("    hard_conflicts %s" % reg_names(d.get("hard_conflicts") or []))
        print("    reasons: %s" % ", ".join(d["reasons"]))
        for e in by_pseudo.get(d["pseudo"], []):
            a = e.get("attempt") or {}
            if a:
                # The used/preferred sets cover every hard register; only the integer ones read usefully.
                gpr = lambda ns: reg_names([n for n in (ns or []) if n < 32])
                print("    find_reg attempt: got %s  used-so-far(int) %s  someone-prefers(int) %s"
                      % (reg_name(a["result"]) if a.get("result", -1) >= 0 else "none",
                         gpr(a.get("regs_used_so_far")), gpr(a.get("regs_someone_prefers"))))
            print("    attempt reasons: %s" % ", ".join(e["reasons"]))


def main():
    ap = argparse.ArgumentParser(description="Read the stock allocator's state for a row's ASM_REG pins.")
    ap.add_argument("row", help="row id, e.g. town/func_800A10FC")
    ap.add_argument("--source", help="candidate .c to read instead of the row's current src text")
    ap.add_argument("--site", type=int, help="one site index from tools/pin_census.sites_of (all ASM_REG by default)")
    ap.add_argument("--out", help="write the full JSON report (traces included) here")
    ap.add_argument("--json", action="store_true", help="print the JSON report instead of the compact diagnosis")
    ap.add_argument("--retain", help="analysis-only export directory for the last site's gdb artifacts")
    args = ap.parse_args()

    row = next((r for r in rows() if r["id"] == args.row), None)
    if row is None:
        raise SystemExit("alloc_trace: unknown row %s" % args.row)
    text = Path(args.source).read_text() if args.source else clean_path(row).read_text()
    pins = sites_of(text)
    chosen = [args.site] if args.site is not None else [i for i, s in enumerate(pins) if s[1] == "ASM_REG"]
    if args.site is not None and (args.site < 0 or args.site >= len(pins)):
        raise SystemExit("alloc_trace: site %d out of range (%d pins)" % (args.site, len(pins)))
    if args.site is not None and pins[args.site][1] != "ASM_REG":
        raise SystemExit("alloc_trace: site %d is %s, not ASM_REG" % (args.site, pins[args.site][1]))
    cell = parse_cfg(row["cfg"])[0]
    report = dict(id=row["id"], cfg=row["cfg"], cell=cell, first_pseudo=FIRST.get(cell, 76),
                  source=args.source or str(clean_path(row)), sha=sha_text(text),
                  pins=len(pins), reg_sites=sum(s[1] == "ASM_REG" for s in pins), sites=[])
    if not chosen:
        report["note"] = "no ASM_REG sites"
        if not args.json:
            print("%s  cfg %s  no ASM_REG sites (%d pins)" % (row["id"], row["cfg"], len(pins)))
    else:
        target = observe(row, text)
        if not args.json:
            print("%s  cfg %s  cell %s  FIRST_PSEUDO_REGISTER %d  %d ASM_REG of %d pins"
                  % (row["id"], row["cfg"], cell, report["first_pseudo"], report["reg_sites"], len(pins)))
        for i in chosen:
            rec = diagnose_site(row, text, pins, i, retain=args.retain, target=target)
            report["sites"].append(rec)
            if not args.json:
                print_site(rec)
    if args.out:
        Path(args.out).write_text(json.dumps(report, separators=(",", ":")) + "\n")
    if args.json:
        slim = dict(report, sites=[{k: v for k, v in s.items() if k != "trace"} for s in report["sites"]])
        print(json.dumps(slim, indent=2))


if __name__ == "__main__":
    main()
