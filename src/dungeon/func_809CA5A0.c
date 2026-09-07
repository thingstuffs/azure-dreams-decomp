#include "common.h"

typedef struct S_80171DA0_0 {
    u8 pad_00[0x2A];
    s16 unk_2A;
    u8 pad_2C[0x1A];
    u16 unk_46;
    u8 pad_48[0x25];
    u8 unk_6D;
    u8 pad_6E[0x3];
    u8 unk_71;
    u8 pad_72[0x12];
    u8 unk_84;
    u8 unk_85;
} S_80171DA0_0;   /* arg3 in func_80171DA0 */

typedef struct S_80171DA0_1 {
    u8 pad_00[0x24];
    u8 unk_24;
    u8 unk_25;
    u8 pad_26[0x6];
    u8 * unk_2C;
} S_80171DA0_1;   /* held_arg2 in func_80171DA0 */

typedef struct S_80171DA0_2 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0xA];
    u8 unk_9A;
    u8 unk_9B;
} S_80171DA0_2;   /* arg0 in func_80171DA0 */



extern void func_80047784();
extern void func_8009C93C();
extern s32 func_800A0134();
extern s32 func_800A04F0();
extern s32 func_800A2B5C();
extern s32 func_800A2CB8();
extern void func_800C7930();
extern s16 D_80083228;
extern s32 D_80083460;
extern u8 D_80173C7C;

s32 func_80171DA0(S_80171DA0_2 *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 result;
    u16 flags;
    u8 top_flags;
    s32 held_arg1;
    register void *held_arg2 ASM_REG("$19");   /* MATCH pin: keeps a statement from moving across a call/branch */
    register u32 status_page ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
    register u16 *status ASM_REG("$18");   /* MATCH pin: retail register colouring depends on it */
    volatile s32 frame_pad[2];

    top_flags = ((S_80171DA0_0 *)arg3)->unk_71;
    held_arg1 = arg1;
    top_flags &= 0x7F;
    ((S_80171DA0_0 *)arg3)->unk_71 = top_flags;
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    status_page = 0x80080000U;
    ASM_KEEP(status_page);   /* MATCH pin: load-bearing for the whole function shape */
    status = (u16 *)(status_page + 0x3460);
    ASM_KEEP(status);   /* MATCH pin: load-bearing for the whole function shape */
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    held_arg2 = arg2;

    result = func_800A04F0(arg3, ((S_80171DA0_1 *)held_arg2)->unk_24,
                           ((S_80171DA0_1 *)held_arg2)->unk_25, ((S_80171DA0_0 *)arg3)->unk_2A);
    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }

    flags = status[1];
    if (flags & 0x2000) {
        return -1;
    }
    if (!(((S_80171DA0_0 *)arg3)->unk_46 & 0x8000) && (flags & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(result, arg3) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, held_arg1, 8, 0x300);
    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
    return -1;

transition_ok:
    {
        s32 angle;
        register u32 scratch ASM_REG("$2");   /* MATCH pin: load-bearing for the whole function shape */
        u8 *effect;

        arg0->unk_9A = 0x11;
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        scratch = 0x7C;
        effect = &D_80173C7C;
        arg0->unk_9B = 0;
        arg0->unk_8C = 0;
        ((S_80171DA0_0 *)arg3)->unk_84 = scratch;
        ASM_SCHED_BARRIER();   /* MATCH pin: load-bearing for the whole function shape */
        scratch = 0x80080000U;
        ASM_KEEP(scratch);   /* MATCH pin: retail schedule: same instructions, different order without it */
        ((S_80171DA0_0 *)arg3)->unk_85 = 0;
        ((S_80171DA0_1 *)held_arg2)->unk_2C = effect;
        scratch = (s32)*(s16 *)(scratch + 0x3228);
        angle = ((S_80171DA0_0 *)arg3)->unk_2A;
        scratch += angle;
        scratch += 0x100;
        scratch = ((s32)scratch >> 9) & 7;
        scratch += (u32)effect;
        func_80047784(held_arg2,
                      *(u8 *)scratch,
                      0);
        ((S_80171DA0_0 *)arg3)->unk_6D--;
        func_8009C93C(arg3, held_arg2, ((S_80171DA0_0 *)arg3)->unk_2A, 1, 0);
        return 1;
    }
}

/* MECHANISM: An addressless 8-byte frame object plus held s2 status base gives the 0x40 frame;
   split s5/s3 input live ranges and a zero-byte abort fence reproduce the prologue and local CFG.
   A held a1 effect base and successive v0 scratch roles close the success addressing chain. */
