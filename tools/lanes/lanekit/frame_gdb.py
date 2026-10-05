"""frame_gdb.py - gdb half of frame_trace.py: log every stack-slot allocation inside the kit's cc1 (static i386 -O0,
symbols only). Records (JSON lines to $FT_OUT): assign_stack_local (mode, size, align, frame_offset before/after,
caller chain), alter_reg (i, from_reg, reg_renumber/refs/equiv flags, caller), delete_output_reload, new_spill_reg,
spill_hard_reg, setup_save_areas, retry_global_alloc. Never run by hand: frame_trace.py builds the command."""
import json, os
import gdb

OUT = open(os.environ["FT_OUT"], "w")
INF = gdb.selected_inferior()

def u32(a):
    return int.from_bytes(bytes(INF.read_memory(a, 4)), "little")
def s32(a):
    v = u32(a); return v - (1 << 32) if v & 0x80000000 else v
def s16(a):
    v = int.from_bytes(bytes(INF.read_memory(a, 2)), "little"); return v - 65536 if v & 0x8000 else v
def cstr(a, n=40):
    if not a: return None
    return bytes(INF.read_memory(a, n)).split(b"\0", 1)[0].decode("latin-1")
def esp():
    return int(gdb.parse_and_eval("$esp")) & 0xffffffff
def arg(i):
    return s32(esp() + 4 * (i + 1))
def sym(name):
    return int(gdb.parse_and_eval("(unsigned long)&%s" % name)) & 0xffffffff
def glob_int(name):
    return s32(sym(name))
def glob_ptr(name):
    return u32(sym(name))
def mode_name(m):
    return cstr(u32(sym("mode_name") + 4 * m)) if 0 <= m < 64 else str(m)
def rtx_code(x):
    return int.from_bytes(bytes(INF.read_memory(x, 2)), "little") if x else -1
def rtx_name(x):
    c = rtx_code(x); return cstr(u32(sym("rtx_name") + 4 * c)) if c >= 0 else None
def uid(x):
    return s32(x + 4) if x else None
def callers(n=6):
    out = []; f = gdb.newest_frame().older()
    while f is not None and len(out) < n:
        out.append(f.name() or "?"); f = f.older()
    return out
def reg_info(i):
    rr = glob_ptr("reg_renumber"); rn = glob_ptr("reg_n_refs"); rc = glob_ptr("reg_equiv_constant")
    rm = glob_ptr("reg_equiv_memory_loc"); rb = glob_ptr("reg_basic_block"); rd = glob_ptr("reg_n_deaths")
    rcc = glob_ptr("reg_n_calls_crossed"); rrx = glob_ptr("regno_reg_rtx")
    rtx = u32(rrx + 4 * i) if rrx else 0
    d = {"i": i, "renumber": s16(rr + 2 * i) if rr else None, "refs": s32(rn + 4 * i) if rn else None,
         "equiv_const": bool(u32(rc + 4 * i)) if rc else None, "equiv_mem": bool(u32(rm + 4 * i)) if rm else None,
         "block": s32(rb + 4 * i) if rb else None, "deaths": s16(rd + 2 * i) if rd else None,
         "calls": s32(rcc + 4 * i) if rcc else None}
    if rtx:
        d["mode"] = mode_name(int.from_bytes(bytes(INF.read_memory(rtx + 2, 1)), "little") & 0xff)
        d["code"] = rtx_name(rtx)
    return d

def emit(rec):
    OUT.write(json.dumps(rec) + "\n"); OUT.flush()

class Fin(gdb.FinishBreakpoint):
    def __init__(self, frame, rec):
        super().__init__(frame, internal=True); self.rec = rec
    def stop(self):
        self.rec["frame_offset_after"] = glob_int("frame_offset")
        try: self.rec["ret"] = int(self.return_value) & 0xffffffff if self.return_value is not None else None
        except Exception: pass
        emit(self.rec); return False
    def out_of_scope(self):
        self.rec["frame_offset_after"] = "?"; emit(self.rec)

class Entry(gdb.Breakpoint):
    def __init__(self, name, fn):
        super().__init__("*0x%x" % sym(name), internal=True); self.fn = fn; self.nm = name
    def stop(self):
        try:
            rec = {"ev": self.nm}; fin = self.fn(rec)
            if fin: Fin(gdb.newest_frame(), rec)
            else: emit(rec)
        except Exception as e:
            emit({"ev": self.nm, "error": repr(e)})
        return False

def on_asl(rec):
    rec.update(mode=mode_name(arg(0)), size=arg(1), align=arg(2), frame_offset_before=glob_int("frame_offset"),
               callers=callers(7)); return True
def on_alter(rec):
    i, fr = arg(0), arg(1); rec.update(reg=reg_info(i), from_reg=fr, callers=callers(4),
                                       frame_offset_before=glob_int("frame_offset")); return True
def on_dor(rec):
    insn, j, orl = arg(0), arg(1), arg(2)
    ri = u32(sym("reload_in") + 4 * j); rin = ri
    while rin and rtx_name(rin) == "subreg": rin = u32(rin + 4)
    rec.update(insn=uid(insn), j=j, output_reload_insn=uid(orl), orl_code_before=rtx_name(orl),
               reload_in=rtx_name(rin), reload_in_regno=(s32(rin + 4) if rin and rtx_name(rin) == "reg" else None))
    rec["_orl"] = orl; return True
def on_nsr(rec):
    rec.update(cls=arg(0), max_needs=arg(1), callers=callers(3)); return True
def on_shr(rec):
    rec.update(regno=arg(0), global_=arg(1), cant_eliminate=arg(3)); return True
def on_ssa(rec):
    rec.update(frame_offset_before=glob_int("frame_offset")); return True
def on_rga(rec):
    rec.update(regno=arg(0)); return True
def on_eri(rec):
    rec.update(insn=uid(arg(0))); return False
def on_reload(rec):
    rec.update(frame_offset_before=glob_int("frame_offset"), outgoing_args=glob_int("current_function_outgoing_args_size")); return True

class DorFin(Fin):
    pass

Entry("assign_stack_local", on_asl)
Entry("alter_reg", on_alter)
Entry("new_spill_reg", on_nsr)
Entry("spill_hard_reg", on_shr)
Entry("setup_save_areas", on_ssa)
Entry("retry_global_alloc", on_rga)
Entry("reload", on_reload)

class Dor(gdb.Breakpoint):
    def __init__(self):
        super().__init__("*0x%x" % sym("delete_output_reload"), internal=True)
    def stop(self):
        rec = {"ev": "delete_output_reload"}
        try:
            on_dor(rec); orl = rec.pop("_orl")
            class F(gdb.FinishBreakpoint):
                def __init__(s, fr): super().__init__(fr, internal=True)
                def stop(s):
                    rec["orl_code_after"] = rtx_name(orl); rec["deleted"] = rec["orl_code_after"] == "note"
                    emit(rec); return False
                def out_of_scope(s): emit(rec)
            F(gdb.newest_frame())
        except Exception as e:
            rec["error"] = repr(e); emit(rec)
        return False
Dor()

gdb.execute("run")
emit({"ev": "done", "frame_offset_final": glob_int("frame_offset")})
