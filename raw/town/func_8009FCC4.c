/* v30 (round 4): PRODUCTION SOURCE -- byte-exact `func_8009D424` (row
   func_8009FCC4) at stock 2.7.2-cdk-G0.  Self-contained flattening of v29; no
   include, no dial macros.  Ordinary defined C on the unmodified stock
   compiler: no register pins, no ASM_KEEP, no inline asm, no volatile, no fake
   callees or labels, no compiler patches.

   Three spellings carry the whole result (each measured, see REPORT_ROUND4.md):

   1. `arg3` is stored to write_base+0x95 DIRECTLY -- it is the tenth value live
      across both calls while all nine callee-saved registers are taken, so
      global alloc leaves it unallocated (global.c:924 forbids caller-saved for
      a call-crossing allocno; CALLER_SAVE_PROFITABLE at regs.h:171 is false at
      2 refs / 2 calls) and reload spills it.  Being a narrowing (u8) parm it
      carries no REG_EQUIV, so alter_reg/assign_stack_local puts it at the first
      frame local 0x10($sp) and order_regs_for_reload (reload1.c:3810) hands it
      potential_reload_regs[0] = $t0, because $t0..$t9 are the only registers
      the RTL never names.  Retail's `sb $a3,0x10($sp)` in the jal delay slot IS
      that spill's store; `lbu $t0,0x10($sp)` / `nop` / `sb $t0,0x95($a0)` are
      its reload.

   2. `arg4` is consumed DIRECTLY (no held copy).  A `held_arg4 = arg4` body copy
      absorbs assign_parms' own narrowing insn and carries a body LUID above the
      arg5/arg7/arg8 conversions, so sched2's LUID tie-break emits arg4's stack
      load LAST of the four; using arg4 directly keeps the assign_parms insn,
      whose LUID is the lowest of the four, and restores retail's
      ascending-offset order 0x50, 0x54, 0x5C, 0x60.  The same change lengthens
      arg4's live range from 66 to 69 insns, which is what makes
      allocno_compare (global.c:587) colour held_arg1 (2 refs / 68) before it,
      giving retail's arg1 -> $s6, arg4 -> $s7, arg2 -> $fp, byte -> spilled.

   3. `func_8003FD64` takes TWO parameters, as declared in src/w_80053374.c:28,
      src/w_800525D4.c:32 and src/w_8003FB98.c:23.  A third argument would give
      held_arg2 a third reference and re-price it above arg4.

   The held_arg1 / held_arg2 copies exist to keep assign_parms' REG_EQUIV home
   slot off those two values: update_equiv_regs doubles reg_live_length for any
   pseudo carrying a REG_EQUIV note, which would drop them below the arg3 byte
   in allocno_compare and make one of THEM the spill victim instead. */
#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

typedef void (*Callback)(void *, void *, void *);

extern void *func_8003FD64(s32, void *);
extern s16 func_800C2AE8(void *);
extern u8 D_80083498[];
extern u32 D_800D3950[];
extern u16 D_800D5070[];

/* rowbase owner: func_8009D424( */
s32 func_8009D424(s32 arg0, s32 arg1, s32 arg2, u8 arg3, u8 arg4,
                  u8 arg5, s32 arg6, u16 arg7, u16 arg8, s32 arg9)
{
    s32 held_arg1;
    void *obj;
    void *part0;
    void *part3;
    void *part2;
    u16 value;
    void *write_base;
    u32 color;
    void *call_part2;
    s32 held6;
    s32 held9;
    s32 held_arg2;

    held_arg1 = arg1;
    held_arg2 = arg2;
    obj = func_8003FD64(0x136, D_80083498);
    if (obj == 0) {
        return 0;
    }
    if ((arg0 & 0xC0000000) == 0xC0000000) {
        FIELD(obj, u32, 0x10) = D_800D3950[(u16)arg0];
    }
    if ((arg0 & 0xC0000000) != 0xC0000000) {
        FIELD(obj, u32, 0x10) = arg0;
    }

    if (arg0 & 1) { part0 = FIELD(obj, void *, 8); part2 = FIELD(obj, void *, 0xC); }
    else if (arg0 & 2) { part0 = FIELD(obj, void *, 8); part2 = FIELD(obj, void *, 0xC); }
    else if (arg0 & 4) { part0 = FIELD(obj, void *, 8); part2 = FIELD(obj, void *, 0xC); }
    else { part0 = FIELD(obj, void *, 8); part2 = FIELD(obj, void *, 0xC); }

    FIELD(part0, u16, 2) = arg7;
    part3 = (u8 *)obj + 0x20;
    FIELD(part0, u16, 6) = arg8;

    if (arg5 == 0) {
        FIELD(part0, s16, 0xA) = -0x40;
    } else {
        FIELD(part0, s16, 0xA) = -0xC0;
    }
    FIELD(part0, s16, 0xA) = func_800C2AE8(part0);
    if (part0 != 0) { color = 0x808080; }
    else { color = 0x808080; }
    FIELD(part3, u16, 0x84) = FIELD(part0, u16, 2);
    if (part0 != 0) {
        if (part2 != 0) { write_base = part3; }
        else { write_base = part3; }
    } else {
        if (part2 != 0) { write_base = part3; }
        else { write_base = part3; }
    }
    FIELD(write_base, u16, 0x86) = FIELD(part0, u16, 6);
    FIELD(part2, s16, 0x1E) = 0x1000;
    FIELD(part2, s16, 0x1C) = 0x1000;
    FIELD(part2, s32, 0xC) = color;
    value = D_800D5070[held_arg1 & 3];
    FIELD(write_base, s8, 0x94) = held_arg2;
    FIELD(write_base, u8, 0x95) = arg3;
    FIELD(write_base, u8, 0x96) = arg4;
    if (part0 != 0) {
        if (part2 != 0) { held6 = arg6; }
        else { held6 = arg6; }
    } else { held6 = arg6; }
    FIELD(write_base, s32, 0x48) = held6;
    if (part0 != 0) {
        if (part2 != 0) { held9 = arg9; }
        else { held9 = arg9; }
    } else { held9 = arg9; }
    FIELD(write_base, s8, 0x93) = 0;
    FIELD(write_base, s8, 0x70) = 0;
    FIELD(write_base, s8, 0x71) = 0;
    FIELD(write_base, u16, 0x72) = value;
    FIELD(write_base, u16, 0x6E) = value;
    FIELD(write_base, s32, 0x98) = held9;
    if (part0 != 0) {
        if (part2 != 0) { call_part2 = part2; }
        else { call_part2 = part2; }
    } else { call_part2 = part2; }
    ((Callback)FIELD(obj, u32, 0x10))(write_base, part0, call_part2);
    return 1;
}
