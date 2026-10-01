#!/usr/bin/env python3
"""dbr.py - why reorg.c (delayed-branch scheduling) filled, or did not fill, each delay slot.

    cd work/native_lane/<lane> && source <repo>/tools/lanes/lanekit/env.sh
    python3 <repo>/tools/lanes/lanekit/dbr.py <row> [text] [--cfg CFG] [--insn UID ...] [--all] [--retail]

`text` is `pinned`, `erased` (the default, as in why.py) or a candidate file.  For every branch, jump and call
with a delay slot it prints which reorg routine filled the slot and from where:

  fill_simple (backward)   an insn from BEFORE the branch/call (the backward scan, stopped by a label/jump/asm)
  fill_simple (forward)    an insn from AFTER a call (or the target of the unconditional jump that ended that scan)
  fill_eager  fall-through / target thread, `steal` (from a filled branch at the thread's head), `copy` (taken
                           from a thread the branch does not own: the branch is redirected past it), `likely`
                           (the +-increment trick), relax_delay_slots changes

and, per slot (`--insn UID`, `--all`, or by default every slot that is empty or was filled by fill_eager), every
candidate insn the routines considered, in order, with the reason each was refused:

  * a resource conflict - the register/memory named (`insn_references_resource_p` / `insn_sets_resource_p`
    against the `set` / `needed` resources of the insns it would move past; mark_set/mark_referenced_resources);
  * live at the opposite thread - `mark_target_live_regs` says the register is live where the branch goes the other
    way, with WHY: live entering that block (flow), first read before any set in the forward scan, or put there by
    an update_block `(use (insn N))` marker of an insn already moved into another delay slot (the r85_opus_fit2
    800C379C finding), and whether the scan reached an unconditional jump;
  * may trap (a memory access may not be hoisted into a non-annulled slot), redundant with an earlier insn;
  * not eligible: `get_attr_type` / `dslot` / `length` of the candidate (a load / mfhi / branch has its own delay
    slot; an insn of length > 1 word is too big) - or the annulled alternative is unavailable (no branch-likely on
    MIPS I);
  * scan stops: a label (and which one), a jump, an asm / an already-filled sequence (stop_search_p); a thread that
    is not owned (own_thread_p: which label is in the way, or no barrier before the target) so only its head can be
    taken;
  * the branch prediction: mostly_true_jump's value and the rule that gave it - __builtin_expect (cdk),
    LABEL_OUTSIDE_LOOP_P, a NOTE_INSN_LOOP_BEG before the target label, a NOTE_INSN_LOOP_VTOP right after it (the
    2.x scan looks at NEXT_INSN(label) only), rare_destination of target / fall-through (return = 1, noreturn call
    = 2), EQ/NE/sign tests against 0, backward/forward.

How it knows: the `.dbr` dump holds only reorg's statistics and the final SEQUENCEs, so the decisions come from
running the cell's own cc1 under gdb (`dbr_gdb.py`, batch mode, no prompts, a timeout) with breakpoints on the
reorg.c routines; their arguments and return values are logged and replayed against the reorg.c control flow.
The cc1 binaries are -O0 with symbols (no DWARF): breakpoints are placed by `nm` address, never hard-coded.
The traced compile's assembly is compared with a plain compile (`trace faithful`), and the fills the trace
recorded are compared with the `.dbr` SEQUENCEs (`trace vs .dbr`).  `--no-gdb` prints the static half only
(fills classified from the `.dbr`/`.jump2` dumps, the prediction rebuilt from the notes) when gdb is missing.

Cells: 2.7.2-cdk, 2.8.0, 2.8.1 - full (validated on the four r85 residues, see README).  2.7.2 / 2.6.3 - the
trace runs, but find_dead_or_set_registers is not a separate routine there, so the liveness WHY stops at
"live at the target".  2.91.66 / 2.95.2 - the trace runs and the routines are the same names (resource.c), but
egcs' reorg.c differs in detail: the replay is printed with an UNVALIDATED tag.

`--retail` byte-scores the text and puts retail's slot word beside ours; when retail's slot insn is one of the
candidates, the line `DECIDING:` names the refusal that kept it out (or, for an empty retail slot, the routine
that filled ours).  `--json OUT` writes the whole replay.  Nothing is written outside the lane; the ledger is
never touched.
"""
from __future__ import annotations

import argparse
import json
import os
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path

_HERE = Path(__file__).resolve().parent
sys.path.insert(0, str(_HERE))
if not (_HERE / "kitlib.py").is_file():                      # a draft / lane copy: use the repository's kit
    _root = next(p for p in _HERE.parents if (p / "tools/common.py").is_file())
    sys.path.insert(0, str(_root / "tools/lanes/lanekit"))
import kitlib                                                             # noqa: E402

HERE = Path(__file__).resolve().parent
GDB_SCRIPT = HERE / "dbr_gdb.py"
ROOT = kitlib.ROOT

SUPPORT = {
    "2.7.2-cdk": "full",
    "2.8.0": "full",
    "2.8.1": "full",
    "2.7.2": "partial (no find_dead_or_set_registers routine: liveness reasons stop at 'live at the target')",
    "2.6.3": "partial (no find_dead_or_set_registers / redundant_insn routines)",
    "2.91.66": "UNVALIDATED (egcs reorg.c/resource.c: the same routines, replay not validated)",
    "2.95.2": "UNVALIDATED (egcs reorg.c/resource.c: the same routines, replay not validated)",
}

FUNCS = """dbr_schedule fill_simple_delay_slots fill_eager_delay_slots relax_delay_slots make_return_insns get_jump_flags
num_delay_slots eligible_for_delay eligible_for_annul_false eligible_for_annul_true insn_references_resource_p
insn_sets_resource_p redundant_insn may_trap_p try_split stop_search_p own_thread_p mostly_true_jump rare_destination
condjump_expect_p mark_target_live_regs find_basic_block find_dead_or_set_registers mark_set_resources
emit_delay_sequence steal_delay_list_from_target steal_delay_list_from_fallthrough reorg_redirect_jump update_block
optimize_skip delete_from_delay_slot try_merge_delay_insns fill_slots_from_thread get_attr_type get_attr_dslot
get_attr_length""".split()
DATA = "rtx_name note_insn_name reg_names current_function_name uid_to_ruid reorg_pass_number basic_block_head".split()

GPR = ["zero", "at", "v0", "v1", "a0", "a1", "a2", "a3", "t0", "t1", "t2", "t3", "t4", "t5", "t6", "t7",
       "s0", "s1", "s2", "s3", "s4", "s5", "s6", "s7", "t8", "t9", "k0", "k1", "gp", "sp", "fp", "ra"]
CALL_USED = set(range(1, 16)) | {24, 25, 31, 64, 65, 66}
HEADER_RE = re.compile(r"\((insn|jump_insn|call_insn|code_label|note|barrier)(/[a-z/]+)? (\d+) ")
TOK_RE = re.compile(r'"(?:[^"\\]|\\.)*"|[()\[\]]|[^\s()\[\]"]+')
ANNOT_RE = re.compile(r"^\s*(\S.*?)\s+#\s+(\d+) (\S+)\s*$")     # `-dap`: `# 17 name` (2.7.2: `#  17 name`)
TRIAL_FUNCS = ("insn_references_resource_p", "insn_sets_resource_p", "redundant_insn", "try_split",
               "eligible_for_delay", "eligible_for_annul_false", "eligible_for_annul_true")


# ================================================================================ symbols / compile

def symbols(cc1, cell):
    """{addr, sizes, hard_reg_words, type_enum} for one cc1 (nm), the JSON dbr_gdb.py reads."""
    out = subprocess.run(["nm", "-S", str(cc1)], capture_output=True, text=True, check=True).stdout
    addr, size = {}, {}
    for line in out.splitlines():
        p = line.split()
        if len(p) == 4:
            a, s, t, n = p
        elif len(p) == 3:
            a, t, n = p
            s = "0"
        else:
            continue
        if n in FUNCS and t in "tT":
            addr[n] = int(a, 16)
        elif n in DATA and t in "DBdb":
            if n in addr and t in "db":                     # a global beats a same-named static (reg_names)
                continue
            addr[n] = int(a, 16)
            size[n] = int(s, 16)
    missing = [f for f in ("dbr_schedule", "fill_simple_delay_slots", "fill_eager_delay_slots",
                           "fill_slots_from_thread", "rtx_name", "note_insn_name", "reg_names") if f not in addr]
    if missing:
        raise SystemExit("dbr: %s has no symbol for %s - cannot trace this cc1" % (cc1, ", ".join(missing)))
    n_regs = size["reg_names"] // 4
    md = ROOT / "toolchain/gcc-src" / cell / "config/mips/mips.md"
    enum = []
    if md.is_file():
        m = re.search(r'\(define_attr "type"\s+"([^"]+)"', md.read_text(errors="replace"))
        if m:
            enum = [x.strip() for x in m.group(1).split(",")]
    return {"addr": addr, "hard_reg_words": (n_regs + 31) // 32, "n_rtx": size["rtx_name"] // 4,
            "n_notes": size["note_insn_name"] // 4, "n_regs": n_regs, "type_enum": enum, "sig": signatures(cell)}


def signatures(cell):
    """routine -> [parameter names] from the cell's own reorg.c / resource.c (the argument order differs between
    releases: egcs drops fill_simple_delay_slots' `first` and fill_slots_from_thread's `own_opposite_thread`,
    2.95.2's mark_target_live_regs takes `insns` first)."""
    out = {}
    for f in ("reorg.c", "resource.c"):
        p = ROOT / "toolchain/gcc-src" / cell / f
        if not p.is_file():
            continue
        t = p.read_text(errors="replace")
        for fn in FUNCS:
            if fn in out:
                continue
            m = re.search(r"^%s \(([^)]*)\)\s*$" % fn, t, re.M)
            if m:
                out[fn] = [x.strip() for x in m.group(1).replace("\n", " ").split(",") if x.strip()]
    return out


def run_gdb(cc1, cell, workdir, flags, func, timeout):
    """cc1 under gdb (batch, no prompts) in `workdir` (holding f.i): (trace records, f.s text, error)."""
    syms = workdir / "syms.json"
    syms.write_text(json.dumps(symbols(cc1, cell)))
    trace = workdir / "trace.jsonl"
    kitlib.add_paths()
    from common import NICE                                              # noqa: E402
    cmd = NICE + ["gdb", "-batch", "-nx", "-iex", "set debuginfod enabled off", "-iex", "set pagination off",
                  "-iex", "set confirm off", "-iex", "set startup-with-shell off", "-iex", "set width 0",
                  "-x", str(GDB_SCRIPT), "--args", str(cc1), "f.i", "-quiet", "-O2", *flags, "-w", "-dap",
                  "-o", "f.s"]
    env = dict(os.environ, DBR_SYMS=str(syms), DBR_OUT=str(trace), DBR_FUNC=func or "", TMPDIR=str(workdir))
    try:
        r = subprocess.run(cmd, cwd=workdir, capture_output=True, text=True, env=env, timeout=timeout,
                           stdin=subprocess.DEVNULL)
    except subprocess.TimeoutExpired:
        return None, None, "gdb trace timed out after %d s (raise --timeout)" % timeout
    recs = []
    if trace.is_file():
        for line in trace.read_text(errors="replace").splitlines():
            try:
                recs.append(json.loads(line))
            except ValueError:
                pass
    fatal = [x["msg"] for x in recs if x.get("t") == "fatal"]
    if fatal:
        return recs, None, "gdb script failed: %s" % fatal[0]
    if not any(x.get("t") == "end" for x in recs):
        return recs, None, "gdb trace incomplete (exit %s): %s" % (r.returncode, (r.stderr or r.stdout)[-600:])
    s = workdir / "f.s"
    return recs, s.read_text(errors="replace") if s.is_file() else None, None


def compile_row(row, text, func, use_gdb=True, timeout=300):
    """kitlib.dumps' compile (module rows: the unit that holds the function), plus the gdb trace of that unit.

    Returns {'asm', '<pass>': dump, 'trace': [...]|None, 'faithful': bool|None, 'gdb_error': str|None,
    'cell', 'flags', 'error'}."""
    kitlib.add_paths()
    from common import parse_cfg, NICE                                   # noqa: E402
    to = float(os.environ.get("PIN_CC_TIMEOUT", "60"))
    with tempfile.TemporaryDirectory(prefix="dbr_") as td:
        d = Path(td)
        cand = d / "f.c"
        cand.write_text(text)
        sources = [(cand, row["cfg"])]
        if kitlib.module_fingerprint(row) is not None:
            from variant_screen import screen_sources                    # noqa: E402
            sources = screen_sources(row, cand, d)
        env = dict(os.environ, TMPDIR=str(d), PYTHONDONTWRITEBYTECODE="1")
        out = {"error": None, "trace": None, "faithful": None, "gdb_error": None}
        hold = None
        for i, (source, cfg) in enumerate(sources):
            cell, flags = parse_cfg(cfg)
            D = ROOT / "toolchain/compilers" / ("gcc-" + cell)
            w = d / ("unit%d" % i)
            w.mkdir()
            try:
                r = subprocess.run(NICE + [str(D / "gcc"), "-B" + str(D) + "/", "-E", "-O2", *flags,
                                           "-I" + str(ROOT / "include"), "-w", source.name, "-o", str(w / "f.i")],
                                   cwd=source.parent, capture_output=True, text=True, env=env, timeout=to)
                if r.returncode:
                    return {"error": (r.stderr or r.stdout)[-800:]}
                r = subprocess.run(NICE + [str(D / "cc1"), "f.i", "-quiet", "-O2", *flags, "-w", "-dap", "-o", "f.s"],
                                   cwd=w, capture_output=True, text=True, env=env, timeout=to)
                if r.returncode:
                    return {"error": (r.stderr or r.stdout)[-800:]}
            except subprocess.TimeoutExpired:
                return {"error": "compiler-timeout"}
            asm = (w / "f.s").read_text(errors="replace")
            if isinstance(func, (list, tuple)):
                hit = [f for f in func if re.search(r"^%s:" % re.escape(f), asm, re.M)]
                ents = re.findall(r"^\s*\.ent\s+(\S+)", asm, re.M)
                if hit:
                    func = hit[0]
                elif len(ents) == 1 and len(sources) == 1:
                    func = ents[0]                # the file defines one function under another name
                else:
                    out.setdefault("defined", []).extend(ents)
                    continue
            if hold is None and re.search(r"^%s:" % re.escape(func), asm, re.M):
                hold = (w, D, cell, flags, asm)
                out["asm"] = asm
                for p in sorted(w.iterdir()):
                    suf = p.suffix[1:]
                    if suf in kitlib.PASS_SUFFIX:
                        out[suf] = p.read_text(errors="replace")
        if hold is None:
            return {"error": "no compiled unit defines %s (defined: %s) - pass --func NAME" % (
                func, ", ".join(out.get("defined", [])[:12]) or "?")}
        w, D, cell, flags, asm = hold
        out["cell"], out["flags"], out["func"] = cell, flags, func
        if not use_gdb:
            return out
        if not shutil.which("gdb"):
            out["gdb_error"] = "gdb is not installed: static mode only"
            return out
        g = w / "gdb"
        g.mkdir()
        shutil.copy(w / "f.i", g / "f.i")
        recs, gasm, err = run_gdb(D / "cc1", cell, g, flags, func, timeout)
        out["trace"], out["gdb_error"] = recs, err
        if gasm is not None:
            out["faithful"] = gasm == asm
        return out


# ===================================================================================== static dumps

def function_chunk(dump, func):
    """The part of a pass dump that belongs to `func` (dumps print `;; Function NAME` before each)."""
    if not dump:
        return ""
    parts = re.split(r"^;; Function (\S+)\s*$", dump, flags=re.M)
    for i in range(1, len(parts) - 1, 2):
        if parts[i] == func:
            return parts[i + 1]
    return dump if len(parts) == 1 else ""


def balanced(text, start):
    depth, i, n = 0, start, len(text)
    while i < n:
        c = text[i]
        if c == '"':
            j = text.find('"', i + 1)
            i = n if j < 0 else j
        elif c in "([":
            depth += 1
        elif c in ")]":
            depth -= 1
            if depth == 0:
                return text[start:i + 1]
        i += 1
    return text[start:]


def sexpr(text):
    stack = [[]]
    for t in TOK_RE.findall(text):
        if t in "([":
            stack.append([])
        elif t in ")]":
            if len(stack) > 1:
                x = stack.pop()
                stack[-1].append(x)
        else:
            stack[-1].append(t)
    while len(stack) > 1:
        x = stack.pop()
        stack[-1].append(x)
    return stack[0][0] if stack[0] else []


def parse_insns(chunk):
    """uid -> {'kind', 'flags', 'text', 'sx'} for every insn-chain object in a dump chunk (SEQUENCE elements
    included; the first occurrence wins - a copy_rtx'd insn keeps its uid)."""
    out = {}
    for m in HEADER_RE.finditer(chunk):
        uid = int(m.group(3))
        if uid in out:
            continue
        txt = balanced(chunk, m.start())
        out[uid] = {"kind": m.group(1), "flags": m.group(2) or "", "text": txt}
    return out


def sx_of(rec):
    if "sx" not in rec:
        rec["sx"] = sexpr(rec["text"])
    return rec["sx"]


def hard_regs(e):
    """[regno...] of a `(reg:MODE N name)` s-expression (multi-word modes on a GPR span 2)."""
    try:
        n = int(e[1])
    except (ValueError, IndexError):
        return []
    mode = e[0].split(":")[-1] if ":" in e[0] else "SI"
    if n < 32 and mode in ("DI", "DF"):
        return [n, n + 1]
    return [n]


def effects(rec):
    """{'use': set, 'set': set, 'mread', 'mwrite', 'call'} of one insn's PATTERN (+ a call's usage list) - the
    static mirror of mark_referenced_resources / mark_set_resources, used only to NAME the conflicting register."""
    eff = {"use": set(), "set": set(), "mread": False, "mwrite": False, "call": False}
    if not rec:
        return eff
    sx = sx_of(rec)
    kind = rec["kind"]
    if kind not in ("insn", "jump_insn", "call_insn") or len(sx) < 5:
        return eff

    def use(e):
        if not isinstance(e, list) or not e:
            return
        h = e[0]
        if not isinstance(h, str):
            for x in e:
                use(x)
            return
        if h.startswith("reg"):
            eff["use"].update(hard_regs(e))
            return
        if h.startswith("mem"):
            eff["mread"] = True
        if h.startswith("call"):
            eff["call"] = True
        if h.startswith("set"):
            dest(e[1] if len(e) > 1 else None)
            use(e[2] if len(e) > 2 else None)
            return
        if h.startswith("clobber"):
            x = e[1] if len(e) > 1 else None
            if isinstance(x, list) and x and isinstance(x[0], str) and x[0].startswith("reg"):
                eff["set"].update(hard_regs(x))
            return
        for x in e[1:]:
            use(x)

    def dest(e):
        if not isinstance(e, list) or not e or not isinstance(e[0], str):
            return
        h = e[0]
        if h.startswith("reg"):
            eff["set"].update(hard_regs(e))
        elif h.startswith("mem"):
            eff["mwrite"] = True
            for x in e[1:]:
                use(x)
        elif h.startswith(("subreg", "strict_low_part", "zero_extract", "sign_extract")):
            for x in e[1:]:
                if isinstance(x, list) and x and isinstance(x[0], str) and x[0].startswith("reg"):
                    eff["set"].update(hard_regs(x))
                else:
                    use(x)
    use(sx[4])
    if kind == "call_insn":
        eff["call"] = True
        usage = sx[-1]
        if isinstance(usage, list) and usage and isinstance(usage[0], str) and usage[0].startswith("expr_list"):
            use(usage)
        eff["set"].update(CALL_USED)
    return eff


def one_line(rec, width=100):
    """The insn's PATTERN on one line (no uid header, insn code, LOG_LINKS or REG_NOTES)."""
    if not rec:
        return "?"
    t = rec["text"]
    m = re.match(r"\(\w+(?:/[a-z/]+)? \d+ \d+ \d+ ", t)
    body = t[m.end():] if m else t
    if rec["kind"] in ("insn", "jump_insn", "call_insn") and body.startswith("("):
        body = balanced(body, 0)
    body = re.sub(r"\s+", " ", body)
    return body if len(body) <= width else body[:width - 1] + "..."


def asm_by_uid(asm, func):
    """uid -> [asm line...] (copies keep their uid, so a uid can print more than once) for `func`, plus
    label number -> '$L<n>'."""
    out, inside = {}, False
    for raw in asm.splitlines():
        s = raw.strip()
        if s.startswith(".ent") and s.split()[-1] == func:
            inside = True
            continue
        if s.startswith(".end") and inside:
            break
        if not inside:
            continue
        m = ANNOT_RE.match(raw)
        if m:
            out.setdefault(int(m.group(2)), []).append(re.sub(r"\s+", " ", m.group(1).split("#")[0].strip()))
    return out


# ======================================================================================== the trace

class Node:
    __slots__ = ("i", "f", "p", "inr", "outr", "kids", "attr", "parent")

    def __init__(self, rec):
        self.i, self.f, self.p = rec["i"], rec["f"], rec.get("p")
        self.inr, self.outr, self.kids, self.attr, self.parent = rec, None, [], None, None

    @property
    def ret(self):
        return (self.outr or {}).get("ret")

    def trial(self):
        t = self.inr.get("trial") or self.inr.get("insn")
        return t.get("u") if isinstance(t, dict) else None


def build_tree(recs, func):
    nodes, names, roots = {}, None, []
    for r in recs:
        t = r.get("t")
        if t == "names":
            names = r
        elif t == "in":
            n = Node(r)
            nodes[n.i] = n
            par = nodes.get(n.p)
            if par:
                n.parent = par
                par.kids.append(n)
            else:
                roots.append(n)
        elif t == "out" and r["i"] in nodes:
            nodes[r["i"]].outr = r
        elif t == "attr" and r["i"] in nodes:
            nodes[r["i"]].attr = r
    dbr = [n for n in roots if n.f == "dbr_schedule" and (n.inr.get("func") == func or not func)]
    return (dbr[0] if dbr else None), nodes, names


def walk(n):
    yield n
    for k in n.kids:
        yield from walk(k)


# ==================================================================================== the replay

class Replay:
    def __init__(self, row, func, d, recs):
        self.row, self.func, self.d = row, func, d
        self.cell = d.get("cell")
        self.root, self.nodes, names = build_tree(recs or [], func)
        self.regnames = (names or {}).get("regs") or []
        self.pre = parse_insns(function_chunk(d.get("jump2", ""), func))
        self.post = parse_insns(function_chunk(d.get("dbr", ""), func))
        self.asm = asm_by_uid(d.get("asm", ""), func)
        self.chain, self.ruid = [], {}
        if self.root:
            for n in walk(self.root):
                if n.f.startswith("fill_") and n.inr.get("chain"):
                    self.chain = [x for x in n.inr["chain"] if x]
                    self.ruid = {int(k): v for k, v in (n.inr.get("ruid") or {}).items() if v is not None}
                    break
        if not self.ruid:
            self.ruid = {u: i for i, u in enumerate(self._jump2_order())}
        self.pos = {x["u"]: i for i, x in enumerate(self.chain)}
        self.labels = {x["u"]: x.get("n") for x in self.chain if x.get("k") == "code_label"}
        for u, rec in self.pre.items():
            if rec["kind"] == "code_label" and u not in self.labels:
                sx = sx_of(rec)
                try:
                    self.labels[u] = int(sx[4])
                except (ValueError, IndexError):
                    pass

    def _jump2_order(self):
        return [int(m.group(3)) for m in HEADER_RE.finditer(function_chunk(self.d.get("jump2", ""), self.func))]

    # ------------------------------------------------------------------------------- naming

    def reg(self, n):
        if n < 32:
            return "$" + GPR[n]
        if n < len(self.regnames) and self.regnames[n]:
            return self.regnames[n] if self.regnames[n].startswith("$") else "$" + self.regnames[n]
        return "$r%d" % n

    def regs_of(self, res):
        out = []
        if not res:
            return out
        lim = len(self.regnames) or 76         # bits past FIRST_PSEUDO_REGISTER are regset spill (pseudos)
        for w, v in enumerate(res.get("r") or []):
            for b in range(32):
                if v >> b & 1 and w * 32 + b < lim:
                    out.append(w * 32 + b)
        return out

    def res_text(self, res, limit=14):
        if not res:
            return "?"
        rs = [self.reg(r) for r in self.regs_of(res)]
        extra = [k for k, nm in (("mem", "memory"), ("vol", "volatile"), ("cc", "cc")) if res.get(k)]
        s = " ".join(rs[:limit]) + (" +%d" % (len(rs) - limit) if len(rs) > limit else "")
        return (s + (" " if s and extra else "") + " ".join(extra)) or "(nothing)"

    def rec(self, uid):
        return self.pre.get(uid) or self.post.get(uid)

    def label(self, uid):
        n = self.labels.get(uid)
        return "$L%d" % n if n is not None else "label uid %s" % uid

    def show(self, d):
        """One insn (a trace dict or a uid) as `uid asm-or-rtl`."""
        if d is None:
            return "(end of function)"
        uid = d["u"] if isinstance(d, dict) else d
        kind = d.get("k") if isinstance(d, dict) else (self.rec(uid) or {}).get("kind")
        if kind == "code_label":
            if isinstance(d, dict) and d.get("n") is not None and uid not in self.labels:
                return "$L%d (code_label uid %d, made by reorg)" % (d["n"], uid)
            return "%s (code_label uid %d)" % (self.label(uid), uid)
        if kind == "note":
            return "note %d %s" % (uid, d.get("note", "") if isinstance(d, dict) else "")
        if kind == "barrier":
            return "barrier %d" % uid
        if isinstance(d, dict) and d.get("seq"):
            inner = d["seq"][0]
            return "%s (+%d in its slot)" % (self.show(inner), len(d["seq"]) - 1) if inner else "sequence %d" % uid
        a = self.asm.get(uid)
        if a:
            return "%d `%s`" % (uid, a[0])
        r = self.rec(uid)
        if isinstance(d, dict) and d.get("pk") == "use" and d.get("use_of") is not None:
            return "%d (use (insn %d))" % (uid, d["use_of"])
        return "%d %s" % (uid, one_line(r, 80) if r else "(%s)" % (d.get("pk") if isinstance(d, dict) else "?"))

    # ------------------------------------------------------------------------- conflicts

    def conflict(self, trial_uid, res, how):
        """Name what makes insn_references_resource_p / insn_sets_resource_p true."""
        eff = effects(self.rec(trial_uid))
        regs = set(self.regs_of(res))
        if how == "refs":
            hit = sorted(eff["use"] & regs)
            mem = eff["mread"] and res.get("mem")
        else:
            hit = sorted(eff["set"] & regs)
            mem = eff["mwrite"] and res.get("mem")
        parts = [self.reg(r) for r in hit]
        if mem:
            parts.append("memory")
        if res.get("vol"):
            parts.append("volatile")
        if not parts:
            return "(no static overlap found; the resource set was: %s)" % self.res_text(res)
        return " ".join(parts)

    # ----------------------------------------------------------------------- predictions

    def explain_mtj(self, n):
        i = n.inr
        ret = n.ret
        expect = next((k for k in n.kids if k.f == "condjump_expect_p"), None)
        rares = [k for k in n.kids if k.f == "rare_destination"]
        rd = rares[0].ret if rares else None
        rf = rares[1].ret if len(rares) > 1 else None
        lab = i.get("label") or {}
        facts = []
        rule = None
        if expect is not None and expect.ret:
            rule = (2 if expect.ret > 0 else -1, "__builtin_expect (condjump_expect_p = %d)" % expect.ret)
        lo = i.get("label_outside_loop") or []
        if rule is None and any(x == 1 for x in lo):
            rule = (-1, "the branch leaves a loop (LABEL_OUTSIDE_LOOP_P on its label_ref)")
        nb = i.get("notes_before_label") or []
        na = i.get("note_after_label")
        facts.append("notes before %s: %s" % (self.label(lab.get("u")), ", ".join(x.replace("NOTE_INSN_", "") for x in nb) or "none"))
        facts.append("right after it: %s" % ((na or "").replace("NOTE_INSN_", "") or "an insn"))
        if rule is None and "NOTE_INSN_LOOP_BEG" in nb:
            rule = (2, "NOTE_INSN_LOOP_BEG before the target label (a jump to the loop top)")
        if rule is None and na == "NOTE_INSN_LOOP_VTOP":
            rule = (1, "NOTE_INSN_LOOP_VTOP right after the target label (a jump to the loop test)")
        facts.append("rare_destination target %s / fall-through %s" % (rd, rf))
        if rule is None and rd is not None and rf is not None and rf != rd:
            diff = rf - rd
            v = {-2: -1, -1: 0, 1: 1, 2: 2}.get(diff)
            if v is not None:
                rule = (v, "rare_destination: fall-through %d - target %d = %d (1 = reaches a return, 2 = a "
                           "noreturn call)" % (rf, rd, diff))
        cond = i.get("cond")
        zero = i.get("cond_op1") == "const_int" and i.get("cond_op1_val") == 0
        if rule is None:
            if cond is None:
                rule = (0, "no condition")
            elif cond == "const_int":
                rule = (1, "unconditional")
            elif cond == "eq":
                rule = (0, "EQ test: 'EQ tests are usually false'")
            elif cond == "ne":
                rule = (1, "NE test: 'NE tests are usually true'")
            elif cond in ("le", "lt") and zero:
                rule = (0, "%s against 0: 'most quantities are positive'" % cond.upper())
            elif cond in ("ge", "gt") and zero:
                rule = (1, "%s against 0: 'most quantities are positive'" % cond.upper())
        if rule is None:
            ri, rl = i.get("ruid_insn"), i.get("ruid_label")
            if ri is None or rl is None:
                rule = (1, "position unknown (a new insn): assumed taken")
            else:
                rule = (1 if ri > rl else 0, "%s branch (ruid %d vs label %d)" % ("backward" if ri > rl else "forward", ri, rl))
        agree = "" if rule[0] == ret else "  [MISMATCH: the rule replay gives %s - report this]" % rule[0]
        meaning = {2: "very likely taken", 1: "likely taken", 0: "likely NOT taken", -1: "very unlikely taken"}.get(ret, "?")
        return ret, "mostly_true_jump = %s (%s): %s%s" % (ret, meaning, rule[1], agree), facts

    def explain_own(self, n):
        i = n.inr
        if n.ret:
            return "owned"
        lab = (i.get("label") or {}).get("u")
        for x in i.get("to_active") or []:
            if x and x.get("k") == "code_label" and (x["u"] != lab or x.get("nuses") != 1):
                return "NOT owned: %s (used %s times) sits before its first active insn" % (self.label(x["u"]), x.get("nuses"))
        if not i.get("allow"):
            for x in i.get("before") or []:
                if x.get("k") == "barrier":
                    break
                if x.get("k") == "code_label" or (x.get("k") == "insn" and x.get("pk") not in ("use", "clobber")):
                    return "NOT owned: %s precedes it with no barrier in between (code falls into the target)" % self.show(x)
                if x.get("k") in ("jump_insn", "call_insn"):
                    return "NOT owned: %s precedes it with no barrier (falls through into it)" % self.show(x)
            return "NOT owned (no barrier before the target)"
        return "NOT owned"

    # -------------------------------------------------------------------------- liveness

    def mtlr_source(self, n):
        """The mark_target_live_regs call that did the work (a later call on the same target may hit the cache)."""
        if any(k.f in ("find_basic_block", "find_dead_or_set_registers") for k in n.kids):
            return n, False
        tu = (n.inr.get("target") or {}).get("u")
        best = None
        for m in self.nodes.values():
            if m.f == "mark_target_live_regs" and m.i < n.i and (m.inr.get("target") or {}).get("u") == tu \
                    and any(k.f == "find_dead_or_set_registers" for k in m.kids):
                best = m
        return (best or n), True

    def explain_live(self, n, regs):
        """Lines: why each of `regs` is in mark_target_live_regs' result for n's target."""
        src, cached = self.mtlr_source(n)
        tgt = n.inr.get("target")
        lines = []
        if cached and src is not n:
            lines.append("(the target's liveness was cached from an earlier call, #%d)" % src.i)
        elif cached:
            lines.append("(cached result, the computing call is not in the trace)")
        bb = next((k for k in src.kids if k.f == "find_basic_block"), None)
        fd = next((k for k in src.kids if k.f == "find_dead_or_set_registers"), None)
        sub = [k for k in src.kids if k.f == "mark_target_live_regs"]
        final = set(self.regs_of((n.outr or {}).get("res")))
        for r in sorted(regs):
            why = []
            if fd is None:
                why.append("live at %s (no find_dead_or_set_registers detail in this cell)" % self.show(tgt))
                lines.append("%s: %s" % (self.reg(r), "; ".join(why)))
                continue
            before = set(self.regs_of(fd.inr.get("res")))
            after = set(self.regs_of((fd.outr or {}).get("res")))
            if r in before:
                head = (bb.outr or {}).get("head") if bb else None
                why.append("live entering the target (flow's live-at-start of block %s%s, updated over the insns "
                           "from its head to the target)" % ((bb.ret if bb else "?"),
                                                            ", head %s" % self.show(head) if head else ""))
                first = self.first_touch(fd.inr.get("chain") or [], r)
                if first:
                    why.append(first)
            adders = []
            for k in fd.kids:
                if k.f != "mark_set_resources":
                    continue
                b0 = set(self.regs_of(k.inr.get("res")))
                b1 = set(self.regs_of((k.outr or {}).get("res")))
                if r in b1 - b0:
                    adders.append(k)
            for k in adders:
                x = (k.inr.get("x") or {}).get("u")
                where = self.slot_home(x)
                why.append("ADDED by find_dead_or_set_registers at (use (insn %s)) - update_block's marker for %s%s: "
                           "the registers that insn sets count as live" % (x, self.show(x), where))
            if r not in before and not adders and r in after:
                why.append("set live inside the forward scan (a nested branch)")
            jt = (fd.outr or {}).get("jump_target")
            ji = (fd.outr or {}).get("ret")
            if ji:
                why.append("the forward scan reached unconditional %s -> %s; the result is ANDed with what is live "
                           "there (+ used before set on the way): %s" % (self.show(ji), self.show(jt) if jt else "?",
                                                                        "kept" if r in final else "removed"))
            elif sub:
                why.append("the scan hit a jump (nested mark_target_live_regs)")
            else:
                why.append("the forward scan reached no unconditional jump (nothing ANDs it away)")
            lines.append("%s: %s" % (self.reg(r), "; ".join(why)))
        return lines

    def first_touch(self, chain, r):
        """The first insn of find_dead_or_set_registers' forward walk (NEXT_INSN order) that reads or sets r."""
        for x in chain[1:] if chain else []:
            if not x:
                continue
            k = x.get("k")
            if k == "code_label":
                continue
            if k in ("jump_insn",) and x.get("jl") is not None:
                eff = effects(self.rec(x["u"]))
                if r in eff["use"]:
                    return "first read by %s before any set" % self.show(x)
                return "the walk reaches %s (it continues at %s for an unconditional jump)" % (
                    self.show(x), self.label(x.get("jl")))
            if x.get("pk") == "use" and x.get("use_of") is not None:
                if r in effects(self.rec(x["use_of"]))["set"]:
                    return "kept live by (use (insn %d)) at uid %d" % (x["use_of"], x["u"])
                continue
            if x.get("pk") == "sequence":
                for e in x.get("seq") or []:
                    eff = effects(self.rec(e["u"]))
                    if r in eff["use"]:
                        return "first read by %s (in a filled sequence) before any set" % self.show(e)
                    if r in eff["set"]:
                        return "set by %s (in a filled sequence) - dead after it" % self.show(e)
                continue
            if k in ("insn", "call_insn", "jump_insn"):
                eff = effects(self.rec(x["u"]))
                if r in eff["use"]:
                    return "first read by %s before any set: stays live" % self.show(x)
                if r in eff["set"]:
                    return "set by %s before any read" % self.show(x)
        return None

    def slot_home(self, uid):
        for m in self.nodes.values():
            if m.f == "emit_delay_sequence" and any(e and e.get("u") == uid for e in m.inr.get("list") or []):
                return ", moved into the delay slot of %s" % self.show(m.inr.get("insn"))
        for m in self.nodes.values():
            if m.f == "update_block" and (m.inr.get("insn") or {}).get("u") == uid:
                return " (moved by reorg; marker before %s)" % self.show(m.inr.get("where"))
        return ""

    # ----------------------------------------------------------------------- trial groups

    def groups(self, events):
        """Split a routine's child events into per-trial groups [(trial uid or None, [nodes])]."""
        out = []
        for e in events:
            if e.f == "stop_search_p":
                out.append([e.trial(), [e]])
                continue
            t = e.trial() if e.f in TRIAL_FUNCS else None
            if t is not None:
                if out and out[-1][0] == t and not any(x.f.startswith("eligible_for") for x in out[-1][1]):
                    out[-1][1].append(e)
                else:
                    out.append([t, [e]])
                continue
            if e.f == "may_trap_p" and out and out[-1][0] is not None:
                out[-1][1].append(e)
                continue
            if e.f == "update_block" and out and out[-1][0] == (e.inr.get("insn") or {}).get("u"):
                out[-1][1].append(e)
                continue
            out.append([None, [e]])
        return out

    def verdict(self, uid, evs, roles, ctx):
        """(status, text) for one trial: ACCEPTED / REJECTED / SKIPPED / STOP / note."""
        first = evs[0]
        if first.f == "stop_search_p" and first.ret == 1:
            return "STOP", self.stop_reason(first.inr.get("trial"), first.inr.get("labels_p"))
        names = [e.f for e in evs]
        trial_d = first.inr.get("trial") if first.f == "stop_search_p" else None
        if ctx.get("thread") and first.f == "insn_sets_resource_p" and ctx.get("filled_before"):
            red = next((e for e in evs if e.f == "redundant_insn"), None)
            if red is not None and red.ret:
                return "PAST", "after the fill: redundant with %s, so the redirected branch skips it too" % self.show(red.ret)
            return "PAST", "after the fill: not redundant (or conflicts) - the redirected branch lands here"
        if ctx.get("thread") and len(evs) == 1 and first.f == "insn_references_resource_p" and \
                roles.get(first.inr["res"]["p"]) == "opposite":
            if first.ret:
                return "NOSTEAL", ("the filled branch at the thread head reads %s, live at the opposite thread: its slot "
                                   "insns may not be stolen" % self.res_text(first.inr["res"]))
            return "STEAL", "the filled branch at the thread head reads nothing live at the opposite thread: try to steal its slot"
        if ctx.get("thread") and all(e.f.startswith("eligible_for") for e in evs) and ctx.get("after_loop"):
            e = evs[0]
            return ("ACCEPTED" if e.ret else "REJECTED",
                    "the 'likely' trick (branch very likely taken, nothing found): put the thread head's +-increment in "
                    "the slot and undo it on the fall-through - %s" % ("eligible" if e.ret else self.inelig(e)))
        for e in evs:
            if e.f == "insn_references_resource_p" and e.ret == 1:
                role = roles.get(e.inr["res"]["p"], "set")
                return "REJECTED", self.blame(uid, e.inr["res"], "refs", role, ctx)
            if e.f == "insn_sets_resource_p" and e.ret == 1:
                p = e.inr["res"]["p"]
                role = roles.get(p, "needed")
                what = self.conflict(uid, e.inr["res"], "sets")
                if role == "opposite":
                    regs = set(effects(self.rec(uid))["set"]) & set(self.regs_of(e.inr["res"]))
                    txt = "sets %s, LIVE at the opposite thread %s" % (what, self.show(ctx.get("opp_target")))
                    sub = self.explain_live(ctx["opp_mtlr"], regs) if ctx.get("opp_mtlr") and regs else []
                    return "REJECTED", txt + "".join("\n            %s" % s for s in sub)
                return "REJECTED", self.blame(uid, e.inr["res"], "sets", role, ctx)
            if e.f == "redundant_insn" and e.ret:
                return "REDUNDANT", "redundant with %s before the branch: dropped from the thread, no slot used" % self.show(e.ret)
            if e.f == "may_trap_p" and e.ret == 1:
                return "REJECTED", ("may trap (may_trap_p: it %s): it may not be hoisted into a non-annulled slot "
                                    "from %s" % (self.trap_what(uid), "after a call" if ctx.get("side") == "after"
                                                 else "this thread"))
            if e.f.startswith("eligible_for") and e.ret == 0:
                return "REJECTED", self.inelig(e)
            if e.f.startswith("eligible_for") and e.ret == 1:
                return "ACCEPTED", "eligible: taken into the slot" + (" (annulled)" if "annul" in e.f else "")
        if first.f == "stop_search_p" and len(evs) == 1:
            d = trial_d or {}
            if d.get("k") == "code_label":
                return "LABEL", "%s: passed; the thread is no longer owned" % self.label(d.get("u")) if ctx.get("thread") \
                    else "label"
            if d.get("pk") in ("use", "clobber"):
                return "SKIPPED", "%s: skipped" % d.get("pk").upper()
            if ctx.get("thread"):
                return "END", "not examined: an earlier candidate was refused and this thread is not owned " \
                              "(only the head of an un-owned thread can be taken)"
            return "SKIPPED", "not examined"
        if "try_split" in names and not any(n.startswith("eligible") for n in names):
            return "REJECTED", "conflict-free but not tried (no eligible_for_delay call)"
        return "?", "(%s)" % ", ".join(names)

    def between(self, trial, ctx):
        """The insns `trial` would be moved past (chain order at reorg start), for naming who conflicts."""
        order = [x["u"] for x in self.chain if x and x.get("k") in ("insn", "jump_insn", "call_insn")
                 and x.get("pk") not in ("use", "clobber")]
        pos = {u: i for i, u in enumerate(order)}
        side, delay, start = ctx.get("side"), ctx.get("delay"), ctx.get("start")
        if trial not in pos:
            return []
        if side == "backward" and delay in pos:
            return order[pos[trial] + 1:pos[delay] + 1]
        if side == "after" and delay in pos:
            return [delay] + order[pos[delay] + 1:pos[trial]]
        if start in pos and pos[start] < pos[trial]:
            return order[pos[start]:pos[trial]]
        return []

    def blame(self, trial, res, how, role, ctx):
        """`reads $a0, which 31 `jal ...` (the call itself) sets` - the register/memory and the insn behind it."""
        eff = effects(self.rec(trial))
        regs = set(self.regs_of(res))
        mine = eff["use"] if how == "refs" else eff["set"]
        hit = mine & regs
        mem = (eff["mread"] if how == "refs" else eff["mwrite"]) and res.get("mem")
        what = " ".join([self.reg(r) for r in sorted(hit)] + (["memory"] if mem else []) +
                        (["volatile"] if res.get("vol") else [])) or "(no static overlap; the set was %s)" % self.res_text(res)
        verb = "reads" if how == "refs" else "sets"
        theirs = "use" if (how == "sets" and role == "needed") else "set"
        cands = self.between(trial, ctx)
        if ctx.get("side") != "backward":
            cands = cands[::-1]                   # nearest first: the insn just ahead of the candidate
        culprit = None
        for c in cands:
            e2 = effects(self.rec(c))
            if e2[theirs] & hit or (mem and (e2["mwrite"] or e2["call"] if theirs == "set" else e2["mread"] or e2["call"])):
                culprit = c
                break
        side = ctx.get("side")
        if culprit is not None:
            who = self.show(culprit)
            if culprit == ctx.get("delay"):
                who += " (the %s itself)" % ("call" if (self.rec(culprit) or {}).get("kind") == "call_insn" else "branch")
            elif side in ("fall-through thread", "target thread"):
                who += " (ahead of it in the thread, not taken)"
            return "%s %s, which %s %s" % (verb, what, who, "reads" if theirs == "use" else "sets")
        where = {"backward": "an insn between it and the branch/call", "after": "the call or an insn before it",
                 }.get(side, "an insn ahead of it in the %s that stays" % (side or "thread"))
        return "%s %s, which %s %s" % (verb, what, where, "reads" if theirs == "use" else "sets")

    def trap_what(self, uid):
        eff = effects(self.rec(uid))
        if eff["mread"] or eff["mwrite"]:
            return "accesses memory"
        return "may trap"

    def inelig(self, e):
        a = e.attr or {}
        if e.f != "eligible_for_delay":
            return "not eligible for the ANNULLED slot (%s = 0: no branch-likely on this ISA)" % e.f
        bits = []
        if a.get("dslot"):
            bits.append("type %s has its own delay slot (dslot=yes)" % a.get("type_name", a.get("type")))
        if a.get("length") not in (None, 1):
            bits.append("too big: length %s words (a slot holds 1)" % a.get("length"))
        if not bits:
            bits.append("eligible_for_delay = 0 (type %s, dslot %s, length %s)" % (a.get("type_name", a.get("type")),
                                                                                  a.get("dslot"), a.get("length")))
        return "not eligible: " + "; ".join(bits)

    def stop_reason(self, d, labels_p):
        if d is None:
            return "start/end of the function"
        k, pk = d.get("k"), d.get("pk")
        if k == "code_label":
            return "%s - a label ends the scan" % self.label(d["u"])
        if k == "jump_insn":
            return "%s - a jump ends the scan" % self.show(d)
        if k == "barrier":
            return "barrier %d" % d["u"]
        if pk == "sequence":
            inner = (d.get("seq") or [{}])[0]
            return "an already-filled delay sequence (%s) ends the scan" % self.show(inner) if inner else "a SEQUENCE"
        if pk in ("asm_input", "asm_operands") or k == "insn":
            return "%s - an asm statement ends the scan (stop_search_p: asm_noperands >= 0)" % self.show(d)
        return self.show(d)

    # ------------------------------------------------------------------------- the routines

    def roles_for(self, events, opp_ptr=None):
        roles = {}
        if opp_ptr is not None:
            roles[opp_ptr] = "opposite"
        for e in events:
            if e.f == "insn_references_resource_p":
                p = e.inr["res"]["p"]
                roles.setdefault(p, "set")
        for e in events:
            if e.f == "insn_sets_resource_p":
                p = e.inr["res"]["p"]
                roles.setdefault(p, "needed")
        return roles

    def trial_lines(self, events, ctx, roles, indent):
        lines, outcome = [], []
        for t, evs in self.groups(events):
            f0 = evs[0].f
            if t is None and f0 not in ("stop_search_p",):
                continue
            if all(e.f == "try_split" for e in evs):
                continue                  # the thread head's split before the scan, not a candidate
            if ctx.get("thread") and outcome and outcome[-1][0] in ("STOP", "END") and evs[0].f.startswith("eligible_for"):
                ctx["after_loop"] = True
            st, txt = self.verdict(t, evs, roles, ctx)
            if st == "ACCEPTED":
                ctx["filled_before"] = True
            show = self.show(evs[0].inr.get("trial") or t) if t is not None else "-"
            if st == "STOP":
                lines.append("%sstop: %s" % (indent, txt))
                outcome.append(("STOP", None, txt))
            elif st == "SKIPPED" and "USE" in txt or st == "SKIPPED" and "CLOBBER" in txt:
                lines.append("%s%s  %s" % (indent, show, txt))
            elif st in ("LABEL", "END"):
                lines.append("%s%s  %s" % (indent, show, txt))
                outcome.append((st, t, txt))
            else:
                lines.append("%s%s  %s  %s" % (indent, show, "->" if st != "?" else "", "%s: %s" % (st, txt)))
                outcome.append((st, t, txt))
        return lines, outcome

    def explain_fsft(self, n, indent):
        i = n.inr
        side = "target thread" if i.get("if_true") else "fall-through thread"
        opp_m = next((k for k in n.kids if k.f == "mark_target_live_regs"), None)
        ctx = {"thread": True, "side": side, "opp_mtlr": opp_m, "delay": (i.get("insn") or {}).get("u"),
               "start": (i.get("thread") or {}).get("u"),
               "opp_target": (opp_m.inr.get("target") if opp_m else i.get("opposite"))}
        roles = self.roles_for(n.kids, opp_m.inr.get("res_p") if opp_m else None)
        head = "%s%s from %s%s; own_thread %s; opposite %s%s" % (
            indent, side, self.show(i.get("thread")), " (likely)" if i.get("likely") else "", i.get("own"),
            self.show(i.get("opposite")),
            ", live there: %s" % self.res_text((opp_m.outr or {}).get("res")) if opp_m else " (unconditional: nothing needed there)")
        if i.get("thread") is None:
            return (["%s%s: the thread is the end of the function - nothing to take" % (indent, side)], [], [])
        lines = [head]
        tl, outcome = self.trial_lines([k for k in n.kids if k.f not in ("mark_target_live_regs",)], ctx, roles, indent + "    ")
        lines += tl
        for k in n.kids:
            if k.f.startswith("steal_delay_list"):
                got = k.ret or []
                lines.append("%s    %s(%s): %s" % (indent, k.f, ", ".join(self.show(x) for x in k.inr.get("seq") or []),
                                                 "took " + ", ".join(self.show(x) for x in got) if got else "nothing"))
            if k.f == "reorg_redirect_jump":
                lines.append("%s    branch redirected %s -> %s (past the insn taken from the target)" % (
                    indent, self.show(k.inr.get("old")), self.show(k.inr.get("new"))))
        got = n.ret or []
        lines.append("%s    => %s" % (indent, ("filled with " + ", ".join(self.show(x) for x in got)) if got else "nothing"))
        return lines, outcome, got

    def attempts(self):
        """[{insn uid, routine, pass, lines, filled, outcome}] in trace order."""
        out = []
        if not self.root:
            return out
        for r in self.root.kids:
            if r.f == "fill_simple_delay_slots":
                out += self.simple(r)
            elif r.f == "fill_eager_delay_slots":
                out += self.eager(r)
            elif r.f == "relax_delay_slots":
                out += self.relax(r)
        return out

    def simple(self, r):
        res, cur = [], None
        mode = "calls" if r.inr.get("non_jumps") else "jumps"
        ps = (r.inr.get("pass") or 0) + 1
        segs = []
        for k in r.kids:
            if k.f == "get_jump_flags":
                cur = [k]
                segs.append(cur)
            elif cur is not None:
                cur.append(k)
        for seg in segs:
            insn = seg[0].inr.get("insn") or {}
            u = insn.get("u")
            evs = seg[1:]
            lines = []
            filled = []
            # the unconditional jump right after a call (tried first)
            first_stop = next((j for j, e in enumerate(evs) if e.f == "stop_search_p"), len(evs))
            pre = [e for e in evs[:first_stop] if e.f == "eligible_for_delay"]
            for e in pre:
                lines.append("    the unconditional jump after it %s: %s" % (
                    self.show(e.inr.get("trial")), "eligible (moved into the slot)" if e.ret else self.inelig(e)))
            back = []
            fwd = []
            j = first_stop
            # backward part = stop_search_p groups; it ends at the STOP (ret 1) or a full slot
            while j < len(evs):
                e = evs[j]
                back.append(e)
                j += 1
                if e.f == "stop_search_p" and e.ret == 1:
                    break
                if e.f == "eligible_for_delay" and e.ret == 1:
                    nxt = evs[j] if j < len(evs) else None
                    if nxt is None or nxt.f != "stop_search_p":
                        break
            fwd = evs[j:]
            roles = self.roles_for(back + fwd)
            if any(e.f == "stop_search_p" for e in back):
                lines.append("    backward from the %s (insns before it):" % ("call" if insn.get("k") == "call_insn" else "branch"))
                tl, oc = self.trial_lines(back, {"side": "backward", "delay": u}, roles, "      ")
                lines += tl
            fsft = [e for e in fwd if e.f == "fill_slots_from_thread"]
            plain = [e for e in fwd if e.f != "fill_slots_from_thread"]
            if any(e.f in ("insn_references_resource_p", "insn_sets_resource_p") for e in plain):
                lines.append("    forward (insns after it%s):" % (", may not trap: the call may not return"
                                                                  if insn.get("k") == "call_insn" else ""))
                tl, oc = self.trial_lines(plain, {"side": "after", "delay": u}, roles, "      ")
                lines += tl
            if insn.get("k") == "jump_insn" and any(e.f == "mark_target_live_regs" for e in plain):
                lines.append("    forward (a conditional branch: fill_simple takes nothing after it; jumps to other "
                             "targets on the way add what is live there to `needed`):")
            for e in plain:
                if e.f == "mark_target_live_regs":
                    lines.append("      (a jump to another target on the way: live at %s = %s added to `needed`)" % (
                        self.show(e.inr.get("target")), self.res_text((e.outr or {}).get("res"))))
                if e.f == "reorg_redirect_jump":
                    lines.append("      jump redirected %s -> %s" % (self.show(e.inr.get("old")), self.show(e.inr.get("new"))))
            for e in fsft:
                own = next((x for x in fwd if x.f == "own_thread_p"), None)
                if own:
                    lines.append("    the jump's target %s" % self.explain_own(own))
                fl, oc, got = self.explain_fsft(e, "    ")
                lines += fl
            for e in evs:
                if e.f == "emit_delay_sequence":
                    filled = [x for x in e.inr.get("list") or [] if x]
            res.append({"insn": u, "kind": insn.get("k"), "routine": "fill_simple_delay_slots (%s)" % mode,
                        "pass": ps, "lines": lines, "filled": filled})
        return res

    def eager(self, r):
        res, cur = [], None
        ps = (r.inr.get("pass") or 0) + 1
        segs = []
        for k in r.kids:
            if k.f == "num_delay_slots":
                cur = [k]
                segs.append(cur)
            elif cur is not None:
                cur.append(k)
        for seg in segs:
            insn = seg[0].inr.get("insn") or {}
            u = insn.get("u")
            evs = seg[1:]
            lines, filled = [], []
            owns = [e for e in evs if e.f == "own_thread_p"]
            mtj = next((e for e in evs if e.f == "mostly_true_jump"), None)
            if mtj:
                pred, txt, facts = self.explain_mtj(mtj)
                lines.append("    " + txt)
                lines.append("        (%s)" % "; ".join(facts))
                order = ("target thread first, then the fall-through (if owned)" if pred > 0
                         else "fall-through first (only if owned), then the target thread")
            else:
                pred, order = 2, "unconditional: the target thread only"
            if owns:
                lines.append("    own_target: %s%s" % (self.explain_own(owns[0]),
                             "; own_fallthrough: %s" % self.explain_own(owns[1]) if len(owns) > 1 else ""))
            lines.append("    order: %s" % order)
            fs = [e for e in evs if e.f == "fill_slots_from_thread"]
            if mtj and pred <= 0 and len(owns) > 1 and not owns[1].ret:
                lines.append("    fall-through thread NOT tried (not owned)")
            for e in fs:
                fl, oc, got = self.explain_fsft(e, "    ")
                lines += fl
            for e in evs:
                if e.f == "emit_delay_sequence":
                    filled = [x for x in e.inr.get("list") or [] if x]
            heads = {}
            for e in fs:
                t_, o_ = (e.inr.get("thread") or {}).get("u"), (e.inr.get("opposite") or {}).get("u")
                if e.inr.get("if_true"):
                    heads.setdefault("target", [t_, False])[1] = True
                    heads.setdefault("fall-through", [o_, False])
                else:
                    heads.setdefault("fall-through", [t_, False])[1] = True
                    heads.setdefault("target", [o_, False])
            res.append({"insn": u, "kind": insn.get("k"), "routine": "fill_eager_delay_slots", "pass": ps,
                        "lines": lines, "filled": filled, "pred": pred if mtj else None, "heads": heads,
                        "pred_text": txt if mtj else "unconditional"})
        return res

    def relax(self, r):
        """relax_delay_slots' changes (any depth: try_merge_delay_insns deletes from slots, redirects, re-emits)."""
        res = []
        ps = (r.inr.get("pass") or 0) + 1
        for k in walk(r):
            if k is r:
                continue
            via = k.parent.f if k.parent is not None and k.parent is not r else "relax_delay_slots"
            u, emptied, filled = None, False, []
            if k.f == "reorg_redirect_jump":
                u = (k.inr.get("jump") or {}).get("u")
                txt = "redirected %s -> %s (%s)" % (self.show(k.inr.get("old")), self.show(k.inr.get("new")), via)
            elif k.f == "delete_from_delay_slot":
                d = k.inr.get("insn") or {}
                for m in self.nodes.values():
                    if m.f == "emit_delay_sequence" and m.i < k.i and any(x and x.get("u") == d.get("u") for x in m.inr.get("list") or []):
                        u = (m.inr.get("insn") or {}).get("u")
                emptied = True
                txt = "%s taken back out of this slot by %s%s" % (
                    self.show(d), via, " (merged as redundant into the slot of %s)" % self.show(k.parent.inr.get("insn"))
                    if via == "try_merge_delay_insns" else "")
            elif k.f == "emit_delay_sequence":
                u = (k.inr.get("insn") or {}).get("u")
                filled = [x for x in k.inr.get("list") or [] if x]
                txt = "re-emitted with %s (%s)" % (", ".join(self.show(x) for x in filled), via)
            else:
                continue
            res.append({"insn": u, "kind": None, "routine": "relax_delay_slots", "pass": ps,
                        "lines": ["    " + txt], "filled": filled, "emptied": emptied})
        return res

    # ------------------------------------------------------------------------- final state

    def final_slots(self):
        """delay insn uid -> {'slots': [uid...], 'from_target': [...], 'annul'} from the .dbr dump."""
        out = {}
        chunk = function_chunk(self.d.get("dbr", ""), self.func)
        for m in re.finditer(r"\(insn (\d+) \d+ \d+ \(sequence\[", chunk):
            sx = sexpr(balanced(chunk, m.start()))
            try:
                elems = sx[4][1]
            except (IndexError, TypeError):
                continue
            uids = []
            for e in elems:
                if isinstance(e, list) and len(e) > 1:
                    uids.append((e[0], int(e[1])))
            if not uids:
                continue
            head = uids[0]
            out[head[1]] = {"kind": head[0].split("/")[0], "annul": "/u" in head[0],
                            "slots": [u for _, u in uids[1:]], "from_target": [u for k, u in uids[1:] if "/s" in k]}
        return out

    def delay_insns(self):
        """Every insn that needed a slot, in chain order: uid -> kind (from num_delay_slots > 0 in the trace,
        or the .dbr SEQUENCE heads + unfilled branches/calls of the .jump2 chain)."""
        seen = {}
        if self.root:
            for n in walk(self.root):
                if n.f == "num_delay_slots" and n.ret and n.ret > 0:
                    d = n.inr.get("insn") or {}
                    if d.get("u") is not None:
                        seen.setdefault(d["u"], d.get("k"))
        for u, v in self.final_slots().items():
            seen.setdefault(u, v["kind"])
        if not self.root:
            for u, rec in self.pre.items():
                if rec["kind"] in ("jump_insn", "call_insn") and "addr_vec" not in rec["text"] and "addr_diff_vec" not in rec["text"]:
                    seen.setdefault(u, rec["kind"])
        return sorted(seen.items(), key=lambda kv: (self.ruid.get(kv[0], 10 ** 6), kv[0]))


# ==================================================================================== static mode

def static_fill_source(rp, u, slot, fin):
    """Where a slot insn came from, read from the dumps alone."""
    if slot in fin.get("from_target", []):
        return "target thread (INSN_FROM_TARGET_P)"
    a, b = rp.ruid.get(u), rp.ruid.get(slot)
    if b is None:
        return "a new insn (split or copied)"
    if a is None:
        return "?"
    if b < a:
        return "before the branch/call (fill_simple backward)"
    return "after it (fall-through thread / forward scan)"


REVERSE = {"eq": "ne", "ne": "eq", "lt": "ge", "ge": "lt", "le": "gt", "gt": "le", "ltu": "geu", "geu": "ltu",
           "leu": "gtu", "gtu": "leu"}


def static_prediction(rp, uid):
    """mostly_true_jump rebuilt from the .jump2 chain alone (no rare_destination / LABEL_OUTSIDE_LOOP_P /
    __builtin_expect): the loop notes around the target label and the condition.  --no-gdb only."""
    rec = rp.pre.get(uid)
    if not rec or rec["kind"] != "jump_insn":
        return None
    sx = sx_of(rec)
    pat = sx[4] if len(sx) > 4 else None
    if not (isinstance(pat, list) and pat and pat[0] == "set" and isinstance(pat[2], list) and pat[2]
            and pat[2][0].startswith("if_then_else")):
        return None
    ite = pat[2]
    cond = ite[1][0].split(":")[0] if isinstance(ite[1], list) else None
    arm1 = ite[2]
    lab = None
    for arm, rev in ((ite[2], False), (ite[3], True)):
        if isinstance(arm, list) and arm and arm[0] == "label_ref":
            lab = int(arm[1])
            if rev and cond:
                cond = REVERSE.get(cond, cond)
            break
    del arm1
    order = [(int(m.group(3)), m.group(1)) for m in HEADER_RE.finditer(function_chunk(rp.d.get("jump2", ""), rp.func))]
    pos = {u: i for i, (u, _) in enumerate(order)}
    if lab not in pos:
        return None
    i = pos[lab]
    j = i
    while j + 1 < len(order) and order[j + 1][1] in ("note", "code_label"):
        j += 1
    k = j
    while k > i and order[k][1] != "code_label":
        k -= 1
    lab = order[k][0]                      # dbr_schedule retargets to the last of consecutive labels

    def note(u):
        r = rp.pre.get(u)
        m = re.search(r"(NOTE_INSN_\w+)\)\s*$", r["text"]) if r else None
        return m.group(1) if m else "line"
    before = []
    b = pos[lab] - 1
    while b >= 0 and order[b][1] == "note":
        before.append(note(order[b][0]))
        b -= 1
    after = note(order[pos[lab] + 1][0]) if pos[lab] + 1 < len(order) and order[pos[lab] + 1][1] == "note" else None
    zero = "(const_int 0)" in rec["text"].split("label_ref")[0]
    if "NOTE_INSN_LOOP_BEG" in before:
        return 2, "LOOP_BEG before %s" % rp.label(lab)
    if after == "NOTE_INSN_LOOP_VTOP":
        return 1, "LOOP_VTOP right after %s" % rp.label(lab)
    rule = {"eq": (0, "EQ"), "ne": (1, "NE")}.get(cond)
    if not rule and zero and cond in ("lt", "le"):
        rule = (0, cond.upper() + " 0")
    if not rule and zero and cond in ("ge", "gt"):
        rule = (1, cond.upper() + " 0")
    if not rule:
        rule = (1 if pos[uid] > pos[lab] else 0, "backward" if pos[uid] > pos[lab] else "forward")
    return rule


# ========================================================================================= output

def summary(rp, atts, retail):
    fin = rp.final_slots()
    rows = []
    by_insn = {}
    for a in atts:
        by_insn.setdefault(a["insn"], []).append(a)
    for u, kind in rp.delay_insns():
        f = fin.get(u)
        slot = f["slots"] if f else []
        who = "-"
        last_fill = None
        for a in by_insn.get(u, []):
            if a["filled"]:
                last_fill = a
            elif a.get("emptied"):
                last_fill = None
                who = "emptied by relax p%d" % a["pass"]
        if last_fill:
            who = "%s p%d" % (last_fill["routine"].replace("_delay_slots", "").replace("fill_", ""), last_fill["pass"])
            ext = thread_of(last_fill)
            if ext:
                who += " " + ext
        elif slot:
            who = static_fill_source(rp, u, slot[0], f)
        agree = ""
        gone = u not in rp.asm
        if rp.root and not gone:
            traced = [x["u"] for x in (last_fill["filled"] if last_fill else [])]
            traced = [x for x in traced if not slot or x in slot] if last_fill and last_fill["routine"].startswith("relax") else traced
            agree = "" if traced == slot else "  [.dbr differs: trace %s]" % (traced or "empty")
        ours = (", ".join("`%s`" % (rp.asm.get(s, ["?"])[0]) for s in slot) if slot
                else "(insn deleted by reorg)" if gone else "nop (empty)")
        ret = ""
        if retail is not None:
            ret = retail.get(u, "?")
        rows.append((u, (rp.asm.get(u) or [one_line(rp.rec(u), 40)])[0], ours, who + agree, ret))
    return rows


def thread_of(a):
    """`(fall-through thread)` / `(target thread)` / `(steal)` / `(backward)` / `(forward)` for the summary."""
    txt = "\n".join(a["lines"])
    if a["routine"].startswith("fill_eager") or "thread from" in txt:
        last = None
        for line in a["lines"]:
            s = line.strip()
            if s.startswith(("fall-through thread", "target thread")):
                last = s.split(" from ")[0]
            if s.startswith("=> filled") and last:
                return "(%s)" % last
        if "took " in txt:
            return "(steal)"
    if a["routine"].startswith("fill_simple"):
        if "backward" in txt and any("ACCEPTED" in l for l in a["lines"]):
            return "(backward)"
        if "forward" in txt:
            return "(forward)"
    return ""


def retail_slots(row, text, asm, func, rp):
    """uid of a delay insn -> retail's word after it (the slot), via the scorer's listing."""
    import retailmap as RM                                               # noqa: E402
    v = kitlib.score_at(row, text, diff=True)
    rows_ = RM.scorer_rows(v.get("text"))
    if not rows_:
        return None, "exact" if v.get("exact") else (v.get("status") or "no listing")
    gen = [(i, g) for i, g, _ in rows_ if g]
    by_uid, _by_gen, cov = RM.uid_map(asm, gen)
    m, _regions, _moved = RM.align(rows_)
    ret_text = {i: t for i, _, t in rows_ if t}
    gen_text = {i: g for i, g, _ in rows_ if g}
    out = {}
    for u, _k in rp.delay_insns():
        ws = by_uid.get(u)
        if not ws:
            continue
        g = ws[0]
        r = m.get(g)
        if r is None:
            out[u] = "(branch not aligned)"
            continue
        out[u] = "%s | ours %s" % (ret_text.get(r + 1, "?"), gen_text.get(g + 1, "?"))
    return out, "%d/%d words placed" % (cov[0], cov[1])


def deciding(rp, u, atts, retail_line):
    """If retail's slot insn is one of the candidates, the refusal that kept it out."""
    if not retail_line or retail_line.startswith("("):
        return None
    ret = retail_line.split("|")[0].strip()
    if not ret:
        return None
    if ret.split()[0] == "nop":
        fills = [a for a in atts if a["filled"]]
        if fills:
            return "retail's slot is EMPTY; ours was filled by %s (pass %d) - retail must have refused that candidate" % (
                fills[-1]["routine"], fills[-1]["pass"])
        return None
    rk = norm_regs_key(ret)
    for a in atts:
        for line in a["lines"]:
            m = re.match(r"\s*(\d+) `([^`]*)`\s+->\s+(REJECTED|STOP|REDUNDANT|LABEL|END):?\s*(.*)", line)
            if m and norm_regs_key(m.group(2)) == rk:
                return "retail's slot insn `%s` = our %s: %s in %s (pass %d): %s" % (
                    ret, m.group(1), m.group(3), a["routine"], a["pass"], m.group(4).split("\n")[0])
    for a in atts:
        for side, (hu, tried) in (a.get("heads") or {}).items():
            if hu is None or tried:
                continue
            if any(norm_regs_key(x) == rk for x in rp.asm.get(hu, [])):
                other = "fall-through" if side == "target" else "target"
                got = ", ".join(rp.show(x) for x in a["filled"]) or "nothing"
                return ("retail's slot insn `%s` = the head of our %s thread (%s), which fill_eager never tried: %s, so the "
                        "%s thread was tried first and filled the slot with %s" % (
                            ret, side, rp.show(hu), a.get("pred_text", "?"), other, got))
    return None


def norm_regs_key(s):
    """Disassembly and gcc assembly spell registers differently ($4 vs a0): compare on mnemonic + register numbers."""
    s = s.strip().lower().replace("$", "")
    names = {n: str(i) for i, n in enumerate(GPR)}
    names.update({"s8": "30"})
    toks = re.split(r"([,\s()]+)", s)
    out = []
    for t in toks:
        out.append(names.get(t, t))
    s = "".join(out)
    s = re.sub(r"\s+", " ", s)
    s = re.sub(r"0x[0-9a-f]+", lambda m: str(int(m.group(0), 16)), s)
    s = re.sub(r"\b(addu|subu|and|or|xor|slt|sltu) (\w+),(\w+),(-?\d+)$",
               lambda m: "%s %s,%s,%s" % ({"addu": "addiu", "subu": "subiu", "and": "andi", "or": "ori", "xor": "xori",
                                           "slt": "slti", "sltu": "sltiu"}[m.group(1)], m.group(2), m.group(3), m.group(4)), s)
    return s


def report(row, text, tname, func=None, insns=(), show_all=False, retail=False, no_gdb=False, timeout=300,
           json_out=None, lane=None, top=None):
    """Print the replay of `text` compiled as `row` (already at the wanted cfg).  why.py --pass dbr calls this
    (with top=--top: at most that many per-slot sections when no --insn is named)."""
    lane_root = Path(lane or kitlib.lane_dir()).resolve()
    if json_out:
        jo = Path(json_out) if Path(json_out).is_absolute() else lane_root / json_out
        try:
            jo.resolve().relative_to(lane_root)
        except ValueError:
            raise SystemExit("dbr: --json %s is outside the lane %s" % (json_out, lane_root))
    func = func or [f for f in (row.get("true_name"), row["func"]) if f]
    d = compile_row(row, text, func, use_gdb=not no_gdb, timeout=timeout)
    if d.get("error"):
        raise SystemExit("dbr: %s: %s" % (tname, d["error"]))
    func = d["func"]
    cell = d.get("cell")
    print("# dbr %s  %s  (function %s, recipe %s, cell support: %s)" % (row["id"], tname, func, row["cfg"],
                                                                         SUPPORT.get(cell, "unknown cell")))
    if d.get("gdb_error"):
        print("# gdb: %s - static mode (fills from the dumps, no decisions)" % d["gdb_error"])
    elif d.get("trace") is not None:
        print("# trace faithful: %s" % ("yes - the traced compile's assembly is identical to a plain compile"
                                         if d.get("faithful") else "NO - the traced assembly differs; distrust the replay"))
    rp = Replay(row, func, d, d.get("trace"))
    if d.get("trace") is not None and rp.root is None:
        print("# the trace never entered dbr_schedule for %s (recipe without delay-slot scheduling?)" % func)
    atts = rp.attempts()
    rmap, rnote = (None, None)
    if retail:
        rmap, rnote = retail_slots(row, text, d["asm"], func, rp)
        if rmap is None:
            print("# retail: %s - %s" % (rnote, "generated == retail: every slot below IS retail's" if rnote == "exact"
                                         else "no listing to align"))
        else:
            print("# retail: slot words aligned through the scorer listing (%s)" % rnote)
    rows = summary(rp, atts, rmap)
    if not rp.root:
        rows = [r[:3] + (r[3] + ("  pred %s: %s" % sp if sp else ""),) + r[4:]
                for r in rows for sp in [static_prediction(rp, r[0])]]
        print("# static mode: `filled by` is read from where the slot insn sat in .jump2; `pred` is mostly_true_jump rebuilt "
              "from the .jump2 loop notes and the condition only (rare_destination, LABEL_OUTSIDE_LOOP_P and "
              "__builtin_expect need the trace)")
    if rp.root:
        n_ok = sum(1 for r in rows if ".dbr differs" not in r[3])
        gone = sum(1 for r in rows if r[2].startswith("(insn deleted"))
        print("# trace vs .dbr: %d of %d delay insns end with the fill the trace recorded%s%s" % (
            n_ok, len(rows), " (%d deleted by reorg)" % gone if gone else "", "" if n_ok == len(rows) else " (the rest were changed later - relax_delay_slots / pass 2 - see their lines)"))
    print()
    head = ["uid", "delay insn", "slot (.dbr)", "filled by"] + (["retail slot | ours"] if rmap else [])
    body = [[str(r[0]), r[1], r[2], r[3]] + ([r[4]] if rmap else []) for r in rows]
    print(kitlib.fmt_table(head, body))
    by_insn = {}
    for x in atts:
        by_insn.setdefault(x["insn"], []).append(x)
    fin = rp.final_slots()
    pick = list(insns) or [u for u, _ in rp.delay_insns() if show_all or not fin.get(u) or
                      any(x["routine"].startswith("fill_eager") and x["filled"] for x in by_insn.get(u, []))]
    if not rp.root:
        if pick:
            print("\n(static mode: the per-candidate reasons need the gdb trace)")
        pick = []
    more = 0
    if top is not None and not insns and len(pick) > top:
        pick, more = pick[:top], len(pick) - top
    for u in pick:
        print()
        f = fin.get(u)
        print("== %s   [%s]   slot: %s" % (rp.show(u), (rp.rec(u) or {}).get("kind", "?"),
                                          ", ".join(rp.show(s) for s in f["slots"]) if f else "EMPTY (nop)"))
        if rmap and u in rmap:
            print("   retail slot | ours: %s" % rmap[u])
        seen_lines = {}
        for x in by_insn.get(u, []):
            key = (x["routine"], tuple(re.sub(r"\n?[^\n]*was cached[^\n]*", "", l) for l in x["lines"]),
                   tuple(s["u"] for s in x["filled"]))
            if key in seen_lines:
                print("  pass %d  %s: identical to pass %d" % (x["pass"], x["routine"], seen_lines[key]))
                continue
            seen_lines[key] = x["pass"]
            print("  pass %d  %s%s" % (x["pass"], x["routine"],
                                       ":  filled with %s" % ", ".join(rp.show(s) for s in x["filled"]) if x["filled"] else ""))
            for line in x["lines"]:
                print(line)
        if not by_insn.get(u):
            print("  (no attempt recorded: the slot was filled before the routines looked at it, or the insn is "
                  "not in the traced function)")
        if rmap and u in rmap:
            dc = deciding(rp, u, by_insn.get(u, []), rmap[u])
            if dc:
                print("  DECIDING: %s" % dc)
    if more:
        print("\n(%d more slot sections: name one with --insn UID, or run dbr.py --all)" % more)
    if json_out:
        out = jo
        out.write_text(json.dumps({"row": row["id"], "text": tname, "func": func, "cell": cell,
                                   "final": {str(k): v for k, v in fin.items()},
                                   "attempts": [{k: v for k, v in x.items()} for x in atts],
                                   "retail": rmap}, indent=1, default=str))
        print("\n# wrote %s" % out)



def main():
    ap = argparse.ArgumentParser(description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    ap.add_argument("row_id")
    ap.add_argument("text", nargs="?", default=None, help="pinned, erased (default) or a candidate file")
    ap.add_argument("--variant", default=None, help="same as the positional text (why.py spelling)")
    ap.add_argument("--cfg", help="compile as if the row were registered at this cfg (no ledger write)")
    ap.add_argument("--func", help="the C function to trace (default: the row's true_name / func)")
    ap.add_argument("--insn", type=int, action="append", default=[], help="explain this delay insn (uid); repeatable")
    ap.add_argument("--all", action="store_true", help="explain every delay insn (default: empty or fill_eager slots)")
    ap.add_argument("--retail", action="store_true", help="byte-score and print retail's slot word beside ours")
    ap.add_argument("--no-gdb", action="store_true", help="static mode: fills from the dumps only, no decisions")
    ap.add_argument("--timeout", type=int, default=300, help="seconds for the gdb run (default 300)")
    ap.add_argument("--json", help="write the replay (attempts, final slots) to this file (inside the lane)")
    a = ap.parse_args()
    if a.text and a.variant and a.text != a.variant:
        ap.error("give the text once")
    spec = a.text or a.variant or "erased"
    lane = kitlib.bootstrap()
    row = kitlib.row_of(a.row_id)
    if a.cfg:
        row = kitlib.row_at_cfg(row, a.cfg)
    base = kitlib.base_text(row, lane)
    if spec in ("pinned", "base"):
        text, tname = base, "pinned"
    elif spec == "erased":
        text, tname = kitlib.erased_text(base), "erased"
    else:
        p = Path(spec)
        if not p.is_file():
            raise SystemExit("dbr: %r is neither 'pinned', 'erased' nor a file" % spec)
        text, tname = p.read_text(errors="replace"), p.stem
    report(row, text, tname, func=a.func, insns=a.insn, show_all=a.all, retail=a.retail, no_gdb=a.no_gdb,
           timeout=a.timeout, json_out=a.json, lane=lane)


if __name__ == "__main__":
    main()
