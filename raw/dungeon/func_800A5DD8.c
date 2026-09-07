#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern s32 func_800644B8();
extern s32 func_800AB694();
extern s32 func_800AB734();
extern s32 func_800AB754();
extern s32 func_800AB758();

extern u16 D_80013714;
extern u8 D_80083780[];
extern s16 D_8008378A;

s32 func_800AB538(void *arg0, void *arg1, void *arg2, void *arg3)
{
    register u8 *p0 ASM_REG("$16") = arg0;
    register u8 *p1 ASM_REG("$17") = arg1;
    register u8 *p2 ASM_REG("$19") = arg2;
    register u8 *p3 ASM_REG("$18") = arg3;
    s32 count;
    s16 value;
    s32 result;
    u16 delta;
    s32 state;

    state = FIELD(p0, u8, 0x9B);
    if (state == 1) {
        goto state_1;
    }
    if ((s32)state >= 2) {
        goto state_ge_2;
    }
    if (state == 0) {
        goto state_0;
    }
    {
        register s32 continuation_state ASM_REG("$2") = 0;

        ASM_KEEP(continuation_state);
        return func_800AB758();
    }

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    {
        register s32 continuation_state ASM_REG("$2") = 0;

        ASM_KEEP(continuation_state);
        return func_800AB758();
    }

state_0:
    FIELD(p0, s16, 0x96) = 0x10;
    FIELD(p3, s32, 0x1C) &= 0xFFFBFFFF;
    FIELD(p0, u16, 0x98) |= 8;
    if (D_80013714 & 2) {
        s32 tail_result;

        FIELD(p0, u8, 0x9B) = 2;
        tail_result = func_800AB754();
        ASM_SCHED_BARRIER();
        return tail_result;
    }
    FIELD(p3, u16, 0x8A) = 0x800 / FIELD(p0, s16, 0x96);
    {
        register s32 continuation_state ASM_REG("$2") =
            FIELD(p0, u8, 0x9B) + 1;

        ASM_TAILSLOT_PIN(continuation_state);
        return func_800AB734();
    }

state_1:
    count = FIELD(p0, s16, 0x96) - 2;
    if (count > 0) {
        u8 *base = D_80083780;

        FIELD(p1, s32, 0xC) =
            ((FIELD(base, s16, 2) - FIELD(p1, s16, 2)) << 16) / count;
        FIELD(p1, s32, 0x10) =
            ((FIELD(base, s16, 6) - FIELD(p1, s16, 6)) << 16) /
            (FIELD(p0, s16, 0x96) - 2);
        return func_800AB694();
    }

    {
        u8 *base = D_80083780;

        FIELD(p1, s32, 0x10) = 0;
        FIELD(p1, s32, 0xC) = 0;
        FIELD(p1, u16, 2) = FIELD(base, u16, 2);
        FIELD(p1, u16, 6) = FIELD(base, u16, 6);
    }

    value = FIELD(p0, s16, 0x96);
    if (value != 0) {
        result = func_800644B8(value << 6);
        {
            s16 *height = &D_8008378A;

            result >>= 4;
            FIELD(p1, s32, 0x14) =
                ((*height - result - FIELD(p1, s16, 0xA)) << 16) /
                FIELD(p0, s16, 0x96);
        }
    }

    delta = FIELD(p2, u16, 0x1C) - FIELD(p3, u16, 0x8A);
    FIELD(p2, u16, 0x1C) = delta;
    FIELD(p2, u16, 0x1E) = delta;

    value = FIELD(p0, u16, 0x96) - 1;
    FIELD(p0, s16, 0x96) = value;
    if (value < 0) {
        FIELD(p1, s32, 0x14) = 0;
        FIELD(p3, u16, 0x88) = (u16)D_8008378A;
        FIELD(p1, u16, 0xA) = (u16)D_8008378A;
        FIELD(p0, s16, 0x92) = 0;
        FIELD(p0, u8, 0x9B)++;
        return func_800AB754();
    }
    return 0;

state_2:
    FIELD(p2, u16, 0x1E) = 0;
    FIELD(p2, u16, 0x1C) = 0;
    ASM_SCHED_BARRIER();
    {
        register s32 flags ASM_REG("$2") = FIELD(p3, s32, 0x1C);

        flags |= 0x800000;
        FIELD(p3, s32, 0x1C) = flags;
        ASM_KEEP(flags);
    }
    return 0;
}

/* MECHANISM: Four pointer holds preserve the 0x28 frame and s0/s1/s3/s2 save order.
   Signed s32 state/count, retail-ordered labels, and branch-local held bases align the CFG.
   A value-preserving AB754 Shape-B blocks tail merging; LEAD-28b sinks AB734's pinned v0 add.
   The scoped case-2 v0 carrier and fence hold lw/lui/or/sw followed by the final zero. */
