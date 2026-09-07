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


typedef struct S_800C9F34_0 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    s16 unk_0A;
    void * unk_0C;
} S_800C9F34_0;   /* st in func_800C9F34 */

typedef struct S_800C9F34_1 {
    u8 pad_00[0x98];
    u16 unk_98;
    s8 unk_9A;
} S_800C9F34_1;   /* arg0 in func_800C9F34 */

typedef struct S_800C9F34_2 {
    u8 pad_00[0x18];
    s32 unk_18;
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
    u8 pad_29[0x44];
    s8 unk_6D;
} S_800C9F34_2;   /* arg3 in func_800C9F34 */

typedef struct S_800C9F34_3 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    s8 unk_26;
} S_800C9F34_3;   /* arg2 in func_800C9F34 */

typedef struct S_800C9F34_4 {
    u8 pad_00[0x58];
    s32 unk_58;
} S_800C9F34_4;   /* D_800814A8 in func_800C9F34 */

void func_800C9F34(S_800C9F34_1 *arg0, M2C_UNK arg1, S_800C9F34_3 *arg2, void *arg3) {
    void *st = &D_80083460;

    if (((S_800C9F34_0 *)st)->unk_02 & 0x1000) {
        arg0->unk_9A = 0xE;
        func_800CA0DC(arg0);
        func_800CA0B8();
        return;
    }
    if (((S_800C9F34_0 *)st)->unk_02 & 0x2000) {
        goto block_14;
    }
    arg0->unk_9A = 0xE;
    ((S_800C9F34_2 *)arg3)->unk_1C =
        ((S_800C9F34_2 *)arg3)->unk_1C | 0x40000;
    arg0->unk_98 =
        arg0->unk_98 & 0xFFF7;
    if (((S_800C9F34_2 *)arg3)->unk_28 == 0) {
        goto call_aa94;
    }
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
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
    if ((((S_800C9F34_0 *)st)->unk_0C == arg3) &&
        (((S_800C9F34_0 *)st)->unk_0A == 0) &&
        !(((S_800C9F34_0 *)st)->unk_02 & 8)) {
        ((S_800C9F34_2 *)arg3)->unk_18 = 0;
        ((S_800C9F34_0 *)st)->unk_0C = 0;
        func_800CA0B8();
    }
    return;

block_14:
    arg2->unk_26 = func_8009FB34(
        arg2->unk_24, arg2->unk_25);
    if ((((S_800C9F34_2 *)arg3)->unk_6D > 0) &&
        (!(D_80083462 & 0x2000) ||
         ((func_8009A180(arg3,
            ((S_800C9F34_4 *)D_800814A8)->unk_58 + 0x20) << 0x10) == 0))) {
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
