#include "common.h"

typedef struct S_800AB538_0 {
    u8 pad_00[0x92];
    s16 unk_92;
    u8 pad_94[0x2];
    union { s16 s; u16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_800AB538_0;   /* p0 in func_800AB538 */

typedef struct S_800AB538_1 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x68];
    u16 unk_88;
    u16 unk_8A;
} S_800AB538_1;   /* p3 in func_800AB538 */

typedef struct S_800AB538_2 {
    u8 pad_00[0x2];
    union { s16 s; u16 u; } unk_02;   /* accessed as both */
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
} S_800AB538_2;   /* base in func_800AB538 */

typedef struct S_800AB538_3 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    union { s16 s; u16 u; } unk_06;   /* accessed as both */
    u8 pad_08[0x2];
    union { s16 s; u16 u; } unk_0A;   /* accessed as both */
    u8 pad_0C[0x4];
    s32 unk_10;
    s32 unk_14;
} S_800AB538_3;   /* p1 in func_800AB538 */

typedef struct S_800AB538_4 {
    u8 pad_00[0x1C];
    u16 unk_1C;
    u16 unk_1E;
} S_800AB538_4;   /* p2 in func_800AB538 */



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
    u8 *p0 = arg0;
    u8 *p1 = arg1;
    u8 *p2 = arg2;
    u8 *p3 = arg3;
    s32 count;
    s16 value;
    s32 result;
    u16 delta;
    s32 state;

    state = ((S_800AB538_0 *)p0)->unk_9B;
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
        s32 continuation_state = 0;

        ASM_KEEP(continuation_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        return func_800AB758();
    }

state_ge_2:
    if (state == 2) {
        goto state_2;
    }
    {
        s32 continuation_state = 0;

        ASM_KEEP(continuation_state);   /* UNRESOLVED C shape (pin): removing it changes the basic-block layout; the source shape that makes it unnecessary has not been found */
        return func_800AB758();
    }

state_0:
    ((S_800AB538_0 *)p0)->unk_96.s = 0x10;
    ((S_800AB538_1 *)p3)->unk_1C &= 0xFFFBFFFF;
    (*(u16 *)((u8 *)p0 + 0x98)) |= 8;
    if (D_80013714 & 2) {
        s32 tail_result;

        ((S_800AB538_0 *)p0)->unk_9B = 2;
        tail_result = func_800AB754();
        ASM_SCHED_BARRIER();   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
        return tail_result;
    }
    ((S_800AB538_1 *)p3)->unk_8A = 0x800 / ((S_800AB538_0 *)p0)->unk_96.s;
    {
        s32 continuation_state =
            ((S_800AB538_0 *)p0)->unk_9B + 1;

        ASM_TAILSLOT_PIN(continuation_state);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        return func_800AB734();
    }

state_1:
    count = ((S_800AB538_0 *)p0)->unk_96.s - 2;
    if (count > 0) {
        u8 *base = D_80083780;

        (*(s32 *)((u8 *)p1 + 0xC)) =
            ((((S_800AB538_2 *)base)->unk_02.s - ((S_800AB538_3 *)p1)->unk_02) << 16) / count;
        ((S_800AB538_3 *)p1)->unk_10 =
            ((((S_800AB538_2 *)base)->unk_06.s - ((S_800AB538_3 *)p1)->unk_06.s) << 16) /
            (((S_800AB538_0 *)p0)->unk_96.s - 2);
        return func_800AB694();
    }

    {
        u8 *base = D_80083780;

        (*(s32 *)((u8 *)p1 + 0x10)) = 0;
        (*(s32 *)((u8 *)p1 + 0xC)) = 0;
        (*(u16 *)((u8 *)p1 + 2)) = ((S_800AB538_2 *)base)->unk_02.u;
        ((S_800AB538_3 *)p1)->unk_06.u = ((S_800AB538_2 *)base)->unk_06.u;
    }

    value = ((S_800AB538_0 *)p0)->unk_96.s;
    if (value != 0) {
        result = func_800644B8(value << 6);
        {
            s16 *height = &D_8008378A;

            result >>= 4;
            ((S_800AB538_3 *)p1)->unk_14 =
                ((*height - result - ((S_800AB538_3 *)p1)->unk_0A.s) << 16) /
                ((S_800AB538_0 *)p0)->unk_96.s;
        }
    }

    delta = ((S_800AB538_4 *)p2)->unk_1C - ((S_800AB538_1 *)p3)->unk_8A;
    ((S_800AB538_4 *)p2)->unk_1C = delta;
    ((S_800AB538_4 *)p2)->unk_1E = delta;

    value = ((S_800AB538_0 *)p0)->unk_96.u - 1;
    ((S_800AB538_0 *)p0)->unk_96.s = value;
    if (value < 0) {
        (*(s32 *)((u8 *)p1 + 0x14)) = 0;
        ((S_800AB538_1 *)p3)->unk_88 = (u16)D_8008378A;
        ((S_800AB538_3 *)p1)->unk_0A.u = (u16)D_8008378A;
        ((S_800AB538_0 *)p0)->unk_92 = 0;
        ((S_800AB538_0 *)p0)->unk_9B++;
        return func_800AB754();
    }
    return 0;

state_2:
    ((S_800AB538_4 *)p2)->unk_1E = 0;
    ((S_800AB538_4 *)p2)->unk_1C = 0;
       /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    {
        s32 flags = ((S_800AB538_1 *)p3)->unk_1C;

        flags |= 0x800000;
        ((S_800AB538_1 *)p3)->unk_1C = flags;
        ASM_KEEP(flags);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    }
    return 0;
}

/* MECHANISM: Four pointer holds preserve the 0x28 frame and s0/s1/s3/s2 save order.
   Signed s32 state/count, retail-ordered labels, and branch-local held bases align the CFG.
   A value-preserving AB754 Shape-B blocks tail merging; LEAD-28b sinks AB734's pinned v0 add.
   The scoped case-2 v0 carrier and fence hold lw/lui/or/sw followed by the final zero. */
