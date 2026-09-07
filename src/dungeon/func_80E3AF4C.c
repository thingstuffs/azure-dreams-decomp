#include "common.h"

typedef struct S_8017474C_0 {
    u8 pad_00[0x4];
    u8 * unk_04;
    u16 * unk_08;
    void * unk_0C;
    u8 pad_10[0x4];
    void * unk_14;
    void * unk_18;
    union { u16 s; s16 u; } unk_1C;   /* accessed as both */
    s16 unk_1E;
    union { s16 s; u16 u; } unk_20;   /* accessed as both */
    s16 unk_22;
    s16 unk_24;
    s16 unk_26;
    s16 unk_28;
    s16 unk_2A;
    s16 unk_2C;
    s16 unk_2E;
    s16 unk_30;
} S_8017474C_0;   /* arg0 in func_8017474C */

typedef struct S_8017474C_1 {
    u8 pad_00[0x1C];
    u32 unk_1C;
    u8 pad_20[0x67];
    s8 unk_87;
    u8 pad_88[0x4];
    void * unk_8C;
} S_8017474C_1;   /* object in func_8017474C */

typedef struct S_8017474C_2 {
    u8 pad_00[0x1E];
    u16 unk_1E;
} S_8017474C_2;   /* base in func_8017474C */

typedef struct S_8017474C_3 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017474C_3;   /* sample in func_8017474C */

typedef struct S_8017474C_4 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x6];
    u16 unk_0A;
} S_8017474C_4;   /* position in func_8017474C */

typedef struct S_8017474C_5 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017474C_5;   /* arg1 in func_8017474C */

typedef struct S_8017474C_6 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
    u8 pad_14[0x8];
    u16 unk_1C;
    u16 unk_1E;
} S_8017474C_6;   /* arg2 in func_8017474C */

typedef struct S_8017474C_7 {
    u8 pad_00[0x6];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
} S_8017474C_7;   /* ((S_8017474C_0 *)arg0)->unk_18 in func_8017474C */

typedef struct S_8017474C_8 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x2];
    u16 unk_12;
} S_8017474C_8;   /* ((S_8017474C_0 *)arg0)->unk_14 in func_8017474C */



extern s32 func_80042900(void *, s32);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 func_800BCB04(u16, u16, s16);

extern s32 D_800814A0;
extern u8 D_8017398C[];

void func_8017474C(void *arg0, void *arg1, void *arg2)
{
    void *base;
    void *object;
    void *position;
    s16 limit;
    s32 raw;
    s32 cap;
    s16 scale;
    s16 angle;
    u16 value;
    u8 kind;

    scale = 0x1000;
    limit = scale;
    if (((S_8017474C_0 *)arg0)->unk_1E != 0) {
        goto active;
    }

    if (*((S_8017474C_0 *)arg0)->unk_08 & 1) {
        limit = 0x1400;
    }

    base = ((S_8017474C_0 *)arg0)->unk_0C;
    object = (u8 *)base + 0x20;
    if (((S_8017474C_1 *)object)->unk_1C & 0x00800000) {
        goto failure;
    }
    if (((S_8017474C_2 *)base)->unk_1E & 0x8000) {
        goto failure;
    }
    if (((S_8017474C_1 *)object)->unk_8C == (void *)D_8017398C) {
        goto failure;
    }
    if ((func_80042900(object, 0xA) << 16) != 0) {
        goto failure;
    }

    if (((S_8017474C_1 *)object)->unk_87 != -1) {
        void *sample = ((S_8017474C_0 *)arg0)->unk_18;

        raw = func_800BCB04(((S_8017474C_3 *)sample)->unk_02,
                            ((S_8017474C_3 *)sample)->unk_06,
                            (s16)(((S_8017474C_3 *)sample)->unk_0A - 4));
    } else {
        raw = ((S_8017474C_7 *)(((S_8017474C_0 *)arg0)->unk_18))->unk_0A;
    }

    position = ((S_8017474C_0 *)arg0)->unk_18;
    scale = scale - ((raw - ((S_8017474C_4 *)position)->unk_0A) << 6);
    if (scale < 0) {
        scale = 0;
    }
    if (scale >= 0x1801) {
        scale = 0;
    }

    if (scale >= 0xF81) {
        ((S_8017474C_5 *)arg1)->unk_02 = ((S_8017474C_4 *)position)->unk_02;
        ((S_8017474C_5 *)arg1)->unk_06 = ((S_8017474C_7 *)(((S_8017474C_0 *)arg0)->unk_18))->unk_06;
        ((S_8017474C_5 *)arg1)->unk_0A = raw;

        cap = limit;
        if (cap == 0x1000) {
            value = ((S_8017474C_0 *)arg0)->unk_1C.s;
            if (((S_8017474C_0 *)arg0)->unk_1C.u >= 0x1001) {
                angle = value - 0x400;
                ((S_8017474C_0 *)arg0)->unk_1C.u = angle;
                if (angle < 0x1000) {
                    ((S_8017474C_0 *)arg0)->unk_1C.u = cap;
                }
            } else {
                angle = value + 0x400;
                ((S_8017474C_0 *)arg0)->unk_1C.u = angle;
                if (angle >= 0x1001) {
                    ((S_8017474C_0 *)arg0)->unk_1C.u = cap;
                }
            }
        } else {
            angle = ((S_8017474C_0 *)arg0)->unk_1C.s + 0x800;
            ((S_8017474C_0 *)arg0)->unk_1C.u = angle;
            if (cap < angle) {
                ((S_8017474C_0 *)arg0)->unk_1C.u = limit;
            }
        }
    } else {
        angle = ((S_8017474C_0 *)arg0)->unk_1C.s - 0x400;
        ((S_8017474C_0 *)arg0)->unk_1C.u = angle;
        if (angle < 0) {
            ((S_8017474C_0 *)arg0)->unk_1C.u = 0;
        }
    }

    ((S_8017474C_6 *)arg2)->unk_12 = ((S_8017474C_8 *)(((S_8017474C_0 *)arg0)->unk_14))->unk_12;
    ((S_8017474C_6 *)arg2)->unk_0C = ((S_8017474C_8 *)(((S_8017474C_0 *)arg0)->unk_14))->unk_0C;
    ((S_8017474C_6 *)arg2)->unk_1C = ((S_8017474C_0 *)arg0)->unk_1C.s +
        (func_80064584(((S_8017474C_0 *)arg0)->unk_20.s << 8) >> 4);
    ((S_8017474C_6 *)arg2)->unk_1E = ((S_8017474C_0 *)arg0)->unk_1C.s +
        (func_800644B8(((S_8017474C_0 *)arg0)->unk_20.s << 8) >> 4);

    kind = *((S_8017474C_0 *)arg0)->unk_04;
    if (kind == 0xF) {
        ((S_8017474C_0 *)arg0)->unk_22 =
            (func_80064584(((S_8017474C_0 *)arg0)->unk_20.s << 8) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_24 =
            (func_800644B8(((S_8017474C_0 *)arg0)->unk_20.s << 8) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_26 =
            (func_80064584((((S_8017474C_0 *)arg0)->unk_20.s << 8) + 0x200) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_28 =
            (func_800644B8((((S_8017474C_0 *)arg0)->unk_20.s << 8) + 0x200) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_2A =
            (func_80064584((((S_8017474C_0 *)arg0)->unk_20.s << 8) + 0x400) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_2C =
            (func_800644B8((((S_8017474C_0 *)arg0)->unk_20.s << 8) + 0x400) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_2E =
            (func_80064584((((S_8017474C_0 *)arg0)->unk_20.s << 8) + 0x600) >> 3) + 0x1000;
        ((S_8017474C_0 *)arg0)->unk_30 =
            (func_800644B8((((S_8017474C_0 *)arg0)->unk_20.s << 8) + 0x600) >> 3) + 0x1000;
        goto increment;
    }
    if (kind == 0) {
        ((S_8017474C_0 *)arg0)->unk_1C.u = 0;
        goto increment;
    }

    ((S_8017474C_0 *)arg0)->unk_30 = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_2E = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_2C = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_2A = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_28 = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_26 = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_24 = 0x1000;
    ((S_8017474C_0 *)arg0)->unk_22 = 0x1000;
    goto increment;

active:
    value = ((S_8017474C_6 *)arg2)->unk_1C + 0x100;
    ((S_8017474C_6 *)arg2)->unk_1C = value;
    if (value < 0x2001U) {
        goto active_continue;
    }

failure:
    (*(u16 *)((u8 *)arg0 + -2)) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

active_continue:
    ((S_8017474C_6 *)arg2)->unk_1E += 0x100;

increment:
    ((S_8017474C_0 *)arg0)->unk_20.u++;

done:
    return;
}
