#include "common.h"

typedef s32 M2C_UNK;

#define M2C_FIELD(expr, type_ptr, offset) (*(type_ptr)((s8 *)(expr) + (offset)))

extern s32 func_8009A180();
extern s8 func_8009FB34();
extern s32 func_800A1C58();
extern void func_800CA0B8(void) __attribute__((noreturn));
extern M2C_UNK func_800CA0DC();
extern M2C_UNK func_800CA93C();
extern M2C_UNK func_800CAA94();
extern u16 D_80013714;
extern void *D_800814A8;
extern M2C_UNK D_80083460;
extern u16 D_80083462;

void func_800C9F34(void *arg0, M2C_UNK arg1, void *arg2, void *arg3) {
    void *st = &D_80083460;

    if (M2C_FIELD(st, u16 *, 2) & 0x1000) {
        M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
        func_800CA0DC(arg0);
        func_800CA0B8();
        return;
    }
    if (M2C_FIELD(st, u16 *, 2) & 0x2000) {
        goto block_14;
    }
    M2C_FIELD(arg0, s8 *, 0x9A) = 0xE;
    M2C_FIELD(arg3, s32 *, 0x1C) =
        M2C_FIELD(arg3, s32 *, 0x1C) | 0x40000;
    M2C_FIELD(arg0, u16 *, 0x98) =
        M2C_FIELD(arg0, u16 *, 0x98) & 0xFFF7;
    if (M2C_FIELD(arg3, u8 *, 0x28) == 0) {
        goto call_aa94;
    }
    ASM_SCHED_BARRIER();
    if ((D_80013714 & 8) == 0) {
        goto path_a1c58;
    }
call_aa94:
    func_800CAA94(arg0, arg1, arg2);
    func_800CA0B8();
    return;

path_a1c58:
    if ((func_800A1C58(arg3) << 0x10) == 0) {
        goto block_14;
    }
    if ((M2C_FIELD(st, void **, 0xC) == arg3) &&
        (M2C_FIELD(st, s16 *, 0xA) == 0) &&
        !(M2C_FIELD(st, u16 *, 2) & 8)) {
        M2C_FIELD(arg3, s32 *, 0x18) = 0;
        M2C_FIELD(st, void **, 0xC) = 0;
        func_800CA0B8();
    }
    return;

block_14:
    M2C_FIELD(arg2, s8 *, 0x26) = func_8009FB34(
        M2C_FIELD(arg2, u8 *, 0x24), M2C_FIELD(arg2, u8 *, 0x25));
    if ((M2C_FIELD(arg3, s8 *, 0x6D) > 0) &&
        (!(D_80083462 & 0x2000) ||
         ((func_8009A180(arg3,
            M2C_FIELD(D_800814A8, s32 *, 0x58) + 0x20) << 0x10) == 0))) {
        func_800CA93C(arg0, arg1, arg2);
    }
}

/* MECHANISM (byte-exact @2.8.1-G0, 106/106):
   1. NO PINS. The inherited ASM_REG("$17") pin made arg0's incoming copy a body
      insn (emitted last, into the beq delay slot) and exposed $4==$17 to cse, which
      deleted retail's `move $a0,$s1`. Unpinned, gcc's own allocno priority
      (floor_log2(n_refs)*freq/live_length) lands arg3=$16 arg0=$17 base=$18
      arg2=$19 arg1=$20 with the copies in declaration order — retail exactly.
   2. func_800CA0DC(arg0) is the 8th arg0 reference; it crosses the floor_log2
      boundary 2->3 so arg0 outranks the held base and takes $17 instead of $18.
      The `move $a0` it implies is deleted post-reload ($4 still holds arg0 in the
      entry extended block), so it costs zero words.
   3. `void *st = &D_80083460;` is the held base ($s2), reloaded at 2($s2) three
      times; D_80083462 stays a SEPARATE global so its access re-materialises its
      own page (retail's lui 0x8008 at 0x800C4910) after $s2 has died.
   4. ASM_SCHED_BARRIER() at the head of the `arg3->0x28 == 0` fallthrough thread is
      the whole point: reorg's stop_search_p() returns 1 on ASM_INPUT, so
      fill_eager_delay_slots cannot steal the `lui %hi(D_80013714)` from the
      fallthrough and falls back to the target thread, putting `move $a0,$s1` in the
      slot and redirecting the branch to 0x800C4884 — retail's fill. Needed because
      mostly_true_jump() is pinned to 0 here (EQ condition; rare_destination is 0 on
      both sides), which always makes gcc try the fallthrough thread first. */
