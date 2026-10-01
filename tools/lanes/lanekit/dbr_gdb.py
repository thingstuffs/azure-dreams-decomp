"""dbr_gdb.py - the gdb half of dbr.py: trace gcc 2.x reorg.c (delay-slot filling) inside the kit's cc1.

Sourced by `gdb -batch -nx -x dbr_gdb.py --args <cell>/cc1 f.i ...` (dbr.py builds that command; never run it by
hand).  The cc1 builds under toolchain/compilers are static i386 executables built at -O0 with their symbol table
(no DWARF): every reorg.c routine is a real call, arguments sit on the stack at entry (cdecl), the return value is
in %eax.  Breakpoints are placed at the routines' ENTRY ADDRESSES, which dbr.py reads with `nm` and passes in
$DBR_SYMS (a JSON file) - no address is hard-coded here, so a rebuilt cc1 still works.

Everything this script learns goes to $DBR_OUT as JSON lines: one `in` record when a routine is entered (its
arguments decoded: insn uids, `struct resources` contents, rtx code names) and one `out` record when it returns
(the return value decoded), each with a call id and the id of the traced routine it was called from (`p`), so
dbr.py can rebuild the call tree.  Nothing is printed; nothing in the compile is changed except for the
`get_attr_*` queries on a candidate eligible_for_delay rejected (pure attribute reads - dbr.py checks that the
traced compile's assembly is byte-identical to a plain compile and says so).

Only the function named in $DBR_FUNC is traced (all functions when it is empty): the inner breakpoints are
enabled at that function's dbr_schedule entry and disabled at its exit, from the driver loop at the bottom
(gdb forbids changing breakpoints inside a stop callback).
"""
import json
import os

import gdb

SYMS = json.load(open(os.environ["DBR_SYMS"]))
OUT = open(os.environ["DBR_OUT"], "w")
FUNC = os.environ.get("DBR_FUNC") or None
WORDS = int(SYMS.get("hard_reg_words", 3))
ADDR = SYMS["addr"]                       # name -> entry / data address
TYPE_ENUM = SYMS.get("type_enum") or []

SIG = SYMS.get("sig") or {}               # routine -> its parameter names, read from the cell's own reorg.c
DEFAULT_SIG = {
    "fill_simple_delay_slots": ["first", "non_jumps_p"],
    "mark_target_live_regs": ["target", "res"],
    "fill_slots_from_thread": ["insn", "condition", "thread", "opposite_thread", "likely", "thread_if_true",
                               "own_thread", "own_opposite_thread", "slots_to_fill", "pslots_filled"],
}

INF = gdb.selected_inferior()
STATE = {"active": False, "func": None, "ids": 0, "pending": [], "names": None, "fdsr": [], "dbr_bp": None}
STACK = []                                # [(call id, routine name)] of the traced frames currently live
INNER = []                                # the breakpoints enabled only inside the traced dbr_schedule


# ------------------------------------------------------------------------------------------ memory

def mem(a, n):
    return bytes(INF.read_memory(a, n))


def u32(a):
    return int.from_bytes(mem(a, 4), "little")


def s32(a):
    v = u32(a)
    return v - (1 << 32) if v & 0x80000000 else v


def u16(a):
    return int.from_bytes(mem(a, 2), "little")


def cstr(a, n=80):
    if not a:
        return None
    b = mem(a, n)
    return b.split(b"\0", 1)[0].decode("latin-1")


def esp():
    return int(gdb.parse_and_eval("$esp")) & 0xffffffff


def arg(i):
    """Argument i at a routine's entry address (return address at 0(%esp))."""
    return u32(esp() + 4 * (i + 1))


def P(fn, param):
    """The argument named `param` of routine `fn` at its entry (None when this release has no such parameter)."""
    names_ = SIG.get(fn) or DEFAULT_SIG.get(fn) or []
    if param not in names_:
        return None
    return arg(names_.index(param))


def eax():
    return int(gdb.parse_and_eval("$eax")) & 0xffffffff


def names():
    """rtx_name / note_insn_name / reg_names, read from the inferior once (they differ between releases)."""
    if STATE["names"] is None:
        rtx = [cstr(u32(ADDR["rtx_name"] + 4 * i)) for i in range(SYMS["n_rtx"])]
        notes = [cstr(u32(ADDR["note_insn_name"] + 4 * i)) for i in range(SYMS["n_notes"])]
        regs = [cstr(u32(ADDR["reg_names"] + 4 * i)) for i in range(SYMS["n_regs"])]
        STATE["names"] = (rtx, notes, regs)
        emit({"t": "names", "rtx": rtx, "notes": notes, "regs": regs})
    return STATE["names"]


# --------------------------------------------------------------------------------------------- rtx

def code(x):
    return u16(x)


def cname(x):
    if not x:
        return None
    c = code(x)
    rtx = names()[0]
    return rtx[c] if c < len(rtx) else "code%d" % c


def flagbits(x):
    b = mem(x + 3, 1)[0]                  # jump, call, unchanging, volatil, in_struct, used, integrated (LSB first)
    return {"jump": b & 1, "call": b >> 1 & 1, "unch": b >> 2 & 1, "vol": b >> 3 & 1, "ins": b >> 4 & 1}


def uid(x):
    return s32(x + 4) if x else None


def pattern(x):
    return u32(x + 16)


def nxt(x):
    return u32(x + 12)


def prv(x):
    return u32(x + 8)


def jump_label(x):
    return u32(x + 32)


def note_name(x):
    n = s32(x + 20)
    if n >= 0:
        return "line"
    notes = names()[1]
    return notes[-n] if -n < len(notes) else "note%d" % n


def label_number(x):
    return s32(x + 16)


def is_active(x):
    k = cname(x)
    if k in ("call_insn", "jump_insn"):
        return True
    return k == "insn" and cname(pattern(x)) not in ("use", "clobber")


def describe(x, deep=False):
    """Compact JSON for one insn-chain object: [uid, kind, extra]."""
    if not x:
        return None
    k = cname(x)
    d = {"u": uid(x), "k": k}
    if k in ("insn", "jump_insn", "call_insn"):
        p = pattern(x)
        pk = cname(p)
        d["pk"] = pk
        f = flagbits(x)
        if f["vol"]:
            d["deleted"] = 1
        if f["ins"]:
            d["from_target"] = 1
        if k == "jump_insn":
            if f["unch"]:
                d["annul"] = 1
            jl = jump_label(x)
            if jl and cname(jl) == "code_label":
                d["jl"] = uid(jl)
                d["jn"] = label_number(jl)
        if pk == "use":
            inner = u32(p + 4)
            if inner and cname(inner) in ("insn", "jump_insn", "call_insn"):
                d["use_of"] = uid(inner)
        if pk == "sequence":
            vec = u32(p + 4)
            n = s32(vec)
            d["seq"] = [describe(u32(vec + 4 + 4 * i)) for i in range(max(0, min(n, 8)))]
    elif k == "code_label":
        d["n"] = label_number(x)
        d["nuses"] = s32(x + 24)
    elif k == "note":
        d["note"] = note_name(x)
    return d


def res(p):
    """`struct resources` {char memory, unch_memory, volatil, cc; HARD_REG_SET regs} - the same in every release."""
    if not p:
        return None
    b = mem(p, 4 + 4 * WORDS)
    return {"p": p, "mem": b[0], "unch": b[1], "vol": b[2], "cc": b[3],
            "r": [int.from_bytes(b[4 + 4 * i:8 + 4 * i], "little") for i in range(WORDS)]}


def insn_list(lst, limit=8):
    out = []
    while lst and len(out) < limit:
        out.append(describe(u32(lst + 4)))
        lst = u32(lst + 8)
    return out


def chain(start, limit, back=False):
    out, x = [], start
    while x and len(out) < limit:
        out.append(describe(x))
        x = prv(x) if back else nxt(x)
    return out


def ruid_of(u):
    p = u32(ADDR["uid_to_ruid"]) if "uid_to_ruid" in ADDR else 0
    if not p or u is None or u < 0 or u > STATE.get("max_uid", -1):
        return None
    return s32(p + 4 * u)


# --------------------------------------------------------------------------------------------- log

def emit(rec):
    OUT.write(json.dumps(rec, separators=(",", ":")) + "\n")


def parent():
    return STACK[-1][0] if STACK else None


def new_id():
    STATE["ids"] += 1
    return STATE["ids"]


# -------------------------------------------------------------------------------- per-routine entry

def a_insn(i):
    return describe(arg(i))


def enter_fill(name):
    rec = {}
    if name == "fill_simple_delay_slots":
        rec["non_jumps"] = P(name, "non_jumps_p")
    if "reorg_pass_number" in ADDR:
        rec["pass"] = s32(ADDR["reorg_pass_number"])
    if not STATE.get("snap"):
        first = STATE.get("first")
        STATE["snap"] = True
        snap = chain(first, 6000)
        STATE["max_uid"] = max((d["u"] for d in snap if d), default=-1)
        rec["chain"] = snap
        rec["ruid"] = {str(d["u"]): ruid_of(d["u"]) for d in snap if d}
    return rec


def enter_mtj():
    j = arg(0)
    cond = arg(1)
    lab = jump_label(j)
    rec = {"insn": describe(j), "label": describe(lab) if lab else None, "cond": cname(cond) if cond else None}
    if cond and cname(cond) not in ("const_int",):
        op1 = u32(cond + 8)
        rec["cond_op1"] = cname(op1)
        if op1 and cname(op1) == "const_int":
            rec["cond_op1_val"] = s32(op1 + 4)
    if lab:
        before = []
        x = prv(lab)
        while x and cname(x) == "note" and len(before) < 30:
            before.append(note_name(x))
            x = prv(x)
        rec["notes_before_label"] = before
        a = nxt(lab)
        rec["note_after_label"] = note_name(a) if a and cname(a) == "note" else None
        rec["after_label"] = describe(a) if a else None
    p = pattern(j)
    if cname(p) == "set":
        src = u32(p + 8)
        if cname(src) == "if_then_else":
            outs = []
            for k in (1, 2):
                e = u32(src + 4 + 4 * k)
                if cname(e) == "label_ref":
                    outs.append(flagbits(e)["ins"])
                else:
                    outs.append(None)
            rec["label_outside_loop"] = outs
    rec["ruid_insn"] = ruid_of(uid(j))
    rec["ruid_label"] = ruid_of(uid(lab)) if lab else None
    rec["max_uid"] = STATE.get("max_uid")
    return rec


def enter_own():
    thread, label, allow = arg(0), arg(1), arg(2)
    rec = {"thread": describe(thread), "label": describe(label) if label else None, "allow": allow}
    if thread:
        walk, x = [], thread
        while x and len(walk) < 40:
            walk.append(describe(x))
            if is_active(x):
                break
            x = nxt(x)
        rec["to_active"] = walk
        if not allow:
            back, x = [], prv(thread)
            while x and len(back) < 40:
                if cname(x) != "note":
                    back.append(describe(x))
                    if cname(x) == "barrier":
                        break
                x = prv(x)
            rec["before"] = back
    return rec


def enter_fsft():
    f = "fill_slots_from_thread"
    cond = P(f, "condition")
    rec = {"insn": describe(P(f, "insn")), "cond": cname(cond) if cond else None, "thread": describe(P(f, "thread")),
           "opposite": describe(P(f, "opposite_thread")), "likely": P(f, "likely"), "if_true": P(f, "thread_if_true"),
           "own": P(f, "own_thread"), "own_opp": P(f, "own_opposite_thread"), "to_fill": P(f, "slots_to_fill")}
    ps = P(f, "pslots_filled")
    rec["filled"] = s32(ps) if ps else None
    return rec


def enter_fdsr():
    target, r, jt, jc = arg(0), arg(1), arg(2), arg(3)
    STATE["fdsr"].append(r)
    gdb.set_convenience_variable("dbr_res", r)
    rec = {"target": describe(target), "res": res(r), "jump_count": jc, "jt": jt}
    if len(STATE["fdsr"]) == 1:
        rec["chain"] = chain(target, 80)
    return rec


def enter_mtlr():
    return {"target": describe(P("mark_target_live_regs", "target")), "res_p": P("mark_target_live_regs", "res")}


ENTRY = {
    "fill_simple_delay_slots": lambda: enter_fill("fill_simple_delay_slots"),
    "fill_eager_delay_slots": lambda: enter_fill("fill_eager_delay_slots"),
    "relax_delay_slots": lambda: enter_fill("relax_delay_slots"),
    "make_return_insns": lambda: {},
    "get_jump_flags": lambda: {"insn": a_insn(0)},
    "num_delay_slots": lambda: {"insn": a_insn(0)},
    "eligible_for_delay": lambda: {"insn": a_insn(0), "slot": arg(1), "trial": a_insn(2)},
    "eligible_for_annul_false": lambda: {"insn": a_insn(0), "slot": arg(1), "trial": a_insn(2)},
    "eligible_for_annul_true": lambda: {"insn": a_insn(0), "slot": arg(1), "trial": a_insn(2)},
    "insn_references_resource_p": lambda: {"trial": a_insn(0), "res": res(arg(1)), "inc": arg(2)},
    "insn_sets_resource_p": lambda: {"trial": a_insn(0), "res": res(arg(1)), "inc": arg(2)},
    "redundant_insn": lambda: {"trial": a_insn(0), "insn": a_insn(1)},
    "may_trap_p": lambda: {"x": cname(arg(0))},
    "try_split": lambda: {"trial": a_insn(1)},
    "stop_search_p": lambda: {"trial": a_insn(0), "labels_p": arg(1)},
    "own_thread_p": enter_own,
    "mostly_true_jump": enter_mtj,
    "rare_destination": lambda: {"insn": a_insn(0)},
    "condjump_expect_p": lambda: {"insn": a_insn(0)},
    "mark_target_live_regs": enter_mtlr,
    "find_basic_block": lambda: {"insn": a_insn(0)},
    "find_dead_or_set_registers": enter_fdsr,
    "mark_set_resources": lambda: {"x": a_insn(0), "res": res(arg(1))},
    "emit_delay_sequence": lambda: {"insn": a_insn(0), "list": insn_list(arg(1)), "length": arg(2)},
    "steal_delay_list_from_target": lambda: {"insn": a_insn(0), "seq": seq_of(arg(2))},
    "steal_delay_list_from_fallthrough": lambda: {"insn": a_insn(0), "seq": seq_of(arg(2))},
    "reorg_redirect_jump": lambda: {"jump": a_insn(0), "old": describe(jump_label(arg(0))) if jump_label(arg(0)) else None,
                                    "new": describe(arg(1)) if arg(1) else None},
    "update_block": lambda: {"insn": a_insn(0), "where": a_insn(1)},
    "optimize_skip": lambda: {"insn": a_insn(0)},
    "delete_from_delay_slot": lambda: {"insn": a_insn(0)},
    "try_merge_delay_insns": lambda: {"insn": a_insn(0), "thread": a_insn(1)},
    "fill_slots_from_thread": enter_fsft,
}


def seq_of(pat):
    if not pat or cname(pat) != "sequence":
        return None
    vec = u32(pat + 4)
    return [describe(u32(vec + 4 + 4 * i)) for i in range(max(0, min(s32(vec), 8)))]


# --------------------------------------------------------------------------------- per-routine exit

def ret_int(ctx):
    return {"ret": s32_from(eax())}


def s32_from(v):
    return v - (1 << 32) if v & 0x80000000 else v


def ret_insn(ctx):
    v = eax()
    return {"ret": describe(v) if v else None}


def ret_list(ctx):
    v = eax()
    return {"ret": insn_list(v) if v else []}


def ret_res(ctx):
    return {"res": res(ctx["res_p"])}


def ret_bb(ctx):
    b = s32_from(eax())
    rec = {"ret": b}
    if b >= 0 and "basic_block_head" in ADDR:
        heads = u32(ADDR["basic_block_head"])
        if heads:
            rec["head"] = describe(u32(heads + 4 * b))
    return rec


def ret_fdsr(ctx):
    v = eax()
    rec = {"ret": describe(v) if v else None, "res": res(ctx["res_p"])}
    if ctx.get("jt"):
        t = u32(ctx["jt"])
        rec["jump_target"] = describe(t) if t else None
    STATE["fdsr"].pop()
    gdb.set_convenience_variable("dbr_res", STATE["fdsr"][-1] if STATE["fdsr"] else 0)
    return rec


def ret_fsft(ctx):
    v = eax()
    rec = {"ret": insn_list(v) if v else []}
    if ctx.get("ps"):
        rec["filled"] = s32(ctx["ps"])
    return rec


EXIT = {
    "fill_simple_delay_slots": None, "fill_eager_delay_slots": None, "relax_delay_slots": None,
    "make_return_insns": None, "num_delay_slots": ret_int, "eligible_for_delay": ret_int,
    "eligible_for_annul_false": ret_int, "eligible_for_annul_true": ret_int,
    "insn_references_resource_p": ret_int, "insn_sets_resource_p": ret_int, "redundant_insn": ret_insn,
    "may_trap_p": ret_int, "try_split": ret_insn, "stop_search_p": ret_int, "own_thread_p": ret_int,
    "mostly_true_jump": ret_int, "rare_destination": ret_int, "condjump_expect_p": ret_int,
    "mark_target_live_regs": ret_res, "find_basic_block": ret_bb, "find_dead_or_set_registers": ret_fdsr,
    "mark_set_resources": ret_res, "steal_delay_list_from_target": ret_list,
    "steal_delay_list_from_fallthrough": ret_list, "optimize_skip": ret_list,
    "try_merge_delay_insns": None, "fill_slots_from_thread": ret_fsft,
}
ENTRY_ONLY = {"get_jump_flags", "emit_delay_sequence", "reorg_redirect_jump", "update_block",
              "delete_from_delay_slot"}
ATTR_ON_FAIL = {"eligible_for_delay", "eligible_for_annul_false", "eligible_for_annul_true"}


class Exit(gdb.FinishBreakpoint):
    def __init__(self, cid, name, ctx):
        super().__init__(gdb.newest_frame(), internal=True)
        self.cid, self.name, self.ctx = cid, name, ctx

    def stop(self):
        while STACK and STACK[-1][0] != self.cid:
            STACK.pop()                   # a frame left without its finish (cannot happen at -O0; kept safe)
        if STACK:
            STACK.pop()
        rec = {"t": "out", "i": self.cid, "f": self.name}
        fn = EXIT.get(self.name)
        if fn:
            try:
                rec.update(fn(self.ctx))
            except gdb.error as e:
                rec["err"] = str(e)
        emit(rec)
        if self.name in ATTR_ON_FAIL and rec.get("ret") == 0 and self.ctx.get("trial_p"):
            STATE["pending"].append(("attr", self.cid, self.ctx["trial_p"]))
            return True                   # the driver queries the trial's attributes (inferior calls)
        return False

    def out_of_scope(self):
        emit({"t": "lost", "i": self.cid, "f": self.name})


class Entry(gdb.Breakpoint):
    def __init__(self, name):
        super().__init__("*0x%x" % ADDR[name], internal=True)
        self.name = name

    def stop(self):
        try:
            if self.name == "mark_set_resources" and arg(1) != (STATE["fdsr"][-1] if STATE["fdsr"] else -1):
                return False
            cid = new_id()
            rec = {"t": "in", "i": cid, "f": self.name, "p": parent()}
            rec.update(ENTRY[self.name]())
            emit(rec)
            if self.name in ENTRY_ONLY:
                return False
            ctx = {}
            if self.name == "mark_target_live_regs":
                ctx["res_p"] = P(self.name, "res")
            if self.name == "mark_set_resources":
                ctx["res_p"] = arg(1)
            if self.name == "find_dead_or_set_registers":
                ctx["res_p"], ctx["jt"] = arg(1), arg(2)
            if self.name == "fill_slots_from_thread":
                ctx["ps"] = P(self.name, "pslots_filled")
            if self.name in ATTR_ON_FAIL:
                ctx["trial_p"] = arg(2)
            STACK.append((cid, self.name))
            Exit(cid, self.name, ctx)
        except gdb.error as e:
            emit({"t": "err", "f": self.name, "msg": str(e)})
        return False


class DbrEntry(gdb.Breakpoint):
    """dbr_schedule(first, file): the per-function gate.  Stops (returns True) so the driver can enable the
    inner breakpoints; its finish stops again so the driver can disable them."""

    def __init__(self):
        super().__init__("*0x%x" % ADDR["dbr_schedule"], internal=True)

    def stop(self):
        fname = cstr(u32(ADDR["current_function_name"])) if "current_function_name" in ADDR else None
        names()
        if FUNC and fname != FUNC:
            emit({"t": "skip", "func": fname})
            return False
        STATE["func"] = fname
        STATE["snap"] = False
        STATE["first"] = arg(0)                   # dbr_schedule (first, file) in every release
        cid = new_id()
        emit({"t": "in", "i": cid, "f": "dbr_schedule", "func": fname, "p": None})
        STACK.append((cid, "dbr_schedule"))
        STATE["pending"].append(("enable", cid))
        return True


class DbrExit(gdb.FinishBreakpoint):
    def __init__(self, cid):
        super().__init__(gdb.newest_frame(), internal=True)
        self.cid = cid

    def stop(self):
        STACK.clear()
        emit({"t": "out", "i": self.cid, "f": "dbr_schedule"})
        STATE["pending"].append(("disable", self.cid))
        return True


# ------------------------------------------------------------------------------------------ driver

def alive():
    try:
        return INF.pid != 0 and bool(INF.threads())
    except gdb.error:
        return False


def attr_query(cid, trial):
    """get_attr_type / dslot / length of a rejected candidate - inferior calls, only from the driver."""
    rec = {"t": "attr", "i": cid, "trial": uid(trial)}
    for nm in ("get_attr_type", "get_attr_dslot", "get_attr_length"):
        if nm not in ADDR:
            continue
        try:
            v = int(gdb.parse_and_eval("((int (*)(unsigned int)) 0x%x) (0x%x)" % (ADDR[nm], trial)))
            rec[nm[9:]] = v
        except gdb.error as e:
            rec[nm[9:] + "_err"] = str(e)
    if "type" in rec and 0 <= rec["type"] < len(TYPE_ENUM):
        rec["type_name"] = TYPE_ENUM[rec["type"]]
    emit(rec)


def drive():
    for name in ENTRY:
        if name in ADDR:
            bp = Entry(name)
            bp.enabled = False
            if name == "mark_set_resources":
                bp.condition = "*(unsigned int *)($esp + 8) == $dbr_res"
            INNER.append(bp)
    gdb.set_convenience_variable("dbr_res", 0)
    DbrEntry()
    gdb.execute("run", to_string=True)
    while alive():
        while STATE["pending"]:
            job = STATE["pending"].pop(0)
            if job[0] == "enable":
                for bp in INNER:
                    bp.enabled = True
                DbrExit(job[1])
            elif job[0] == "disable":
                for bp in INNER:
                    bp.enabled = False
            elif job[0] == "attr":
                attr_query(job[1], job[2])
        gdb.execute("continue", to_string=True)
    emit({"t": "end"})
    OUT.close()


try:
    drive()
except Exception as e:                    # noqa: BLE001 - recorded for dbr.py, which reports it
    emit({"t": "fatal", "msg": "%s: %s" % (type(e).__name__, e)})
    OUT.close()
