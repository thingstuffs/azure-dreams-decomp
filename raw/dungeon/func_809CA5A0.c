#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

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

s32 func_80171DA0(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 result;
    u16 flags;
    u8 top_flags;
    register s32 held_arg1 ASM_REG("$21");
    register void *held_arg2 ASM_REG("$19");
    register u32 status_page ASM_REG("$2");
    register u16 *status ASM_REG("$18");
    volatile s32 frame_pad[2];

    top_flags = FIELD(arg3, u8, 0x71);
    ASM_SCHED_BARRIER();
    held_arg1 = arg1;
    top_flags &= 0x7F;
    FIELD(arg3, u8, 0x71) = top_flags;
    ASM_SCHED_BARRIER();
    status_page = 0x80080000U;
    ASM_KEEP(status_page);
    status = (u16 *)(status_page + 0x3460);
    ASM_KEEP(status);
    if (status[1] & 0x2000) {
        goto abort_transition;
    }
    held_arg2 = arg2;
    ASM_KEEP(held_arg2);

    result = func_800A04F0(arg3, FIELD(held_arg2, u8, 0x24),
                           FIELD(held_arg2, u8, 0x25), FIELD(arg3, s16, 0x2A));
    if ((func_800A2CB8(arg3, result) << 16) == 0) {
        return 0;
    }

    flags = status[1];
    if (flags & 0x2000) {
        return -1;
    }
    if (!(FIELD(arg3, u16, 0x46) & 0x8000) && (flags & 8)) {
        return -1;
    }
    if ((u16)(-func_800A0134(result, arg3) + 0x40) >= 0x81U) {
        return 0;
    }
    if ((func_800A2B5C(arg3) << 16) != 0) {
        return -1;
    }

    func_800C7930((u8 *)arg3 - 0x20, held_arg1, 8, 0x300);
    ASM_KEEP(held_arg1);
    if ((func_800A2B5C(arg3) << 16) == 0) {
        goto transition_ok;
    }

abort_transition:
    ASM_SCHED_BARRIER();
    return -1;

transition_ok:
    {
        s32 angle;
        register u32 scratch ASM_REG("$2");
        register u8 *effect ASM_REG("$5");

        FIELD(arg0, u8, 0x9A) = 0x11;
        ASM_SCHED_BARRIER();
        scratch = 0x7C;
        ASM_KEEP(scratch);
        effect = &D_80173C7C;
        ASM_KEEP(effect);
        FIELD(arg0, u8, 0x9B) = 0;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg3, u8, 0x84) = scratch;
        ASM_SCHED_BARRIER();
        scratch = 0x80080000U;
        ASM_KEEP(scratch);
        FIELD(arg3, u8, 0x85) = 0;
        FIELD(held_arg2, u8 *, 0x2C) = effect;
        scratch = (s32)*(s16 *)(scratch + 0x3228);
        angle = FIELD(arg3, s16, 0x2A);
        ASM_CLOBBER("$4");
        scratch += angle;
        scratch += 0x100;
        scratch = ((s32)scratch >> 9) & 7;
        scratch += (u32)effect;
        func_80047784(held_arg2,
                      *(u8 *)scratch,
                      0);
        FIELD(arg3, u8, 0x6D)--;
        func_8009C93C(arg3, held_arg2, FIELD(arg3, s16, 0x2A), 1, 0);
        return 1;
    }
}

/* MECHANISM: An addressless 8-byte frame object plus held s2 status base gives the 0x40 frame;
   split s5/s3 input live ranges and a zero-byte abort fence reproduce the prologue and local CFG.
   A held a1 effect base and successive v0 scratch roles close the success addressing chain. */
