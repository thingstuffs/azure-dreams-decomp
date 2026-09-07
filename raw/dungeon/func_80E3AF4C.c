#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

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
    if (FIELD(arg0, s16, 0x1E) != 0) {
        goto active;
    }

    if (*FIELD(arg0, u16 *, 8) & 1) {
        limit = 0x1400;
    }

    base = FIELD(arg0, void *, 0xC);
    object = (u8 *)base + 0x20;
    if (FIELD(object, u32, 0x1C) & 0x00800000) {
        goto failure;
    }
    if (FIELD(base, u16, 0x1E) & 0x8000) {
        goto failure;
    }
    if (FIELD(object, void *, 0x8C) == (void *)D_8017398C) {
        goto failure;
    }
    if ((func_80042900(object, 0xA) << 16) != 0) {
        goto failure;
    }

    if (FIELD(object, s8, 0x87) != -1) {
        void *sample = FIELD(arg0, void *, 0x18);

        raw = func_800BCB04(FIELD(sample, u16, 2),
                            FIELD(sample, u16, 6),
                            (s16)(FIELD(sample, u16, 0xA) - 4));
    } else {
        raw = FIELD(FIELD(arg0, void *, 0x18), u16, 0xA);
    }

    position = FIELD(arg0, void *, 0x18);
    scale = scale - ((raw - FIELD(position, u16, 0xA)) << 6);
    if (scale < 0) {
        scale = 0;
    }
    if (scale >= 0x1801) {
        scale = 0;
    }

    if (scale >= 0xF81) {
        FIELD(arg1, u16, 2) = FIELD(position, u16, 2);
        FIELD(arg1, u16, 6) = FIELD(FIELD(arg0, void *, 0x18), u16, 6);
        FIELD(arg1, u16, 0xA) = raw;

        cap = limit;
        if (cap == 0x1000) {
            value = FIELD(arg0, u16, 0x1C);
            if (FIELD(arg0, s16, 0x1C) >= 0x1001) {
                angle = value - 0x400;
                FIELD(arg0, s16, 0x1C) = angle;
                if (angle < 0x1000) {
                    FIELD(arg0, s16, 0x1C) = cap;
                }
            } else {
                angle = value + 0x400;
                FIELD(arg0, s16, 0x1C) = angle;
                if (angle >= 0x1001) {
                    FIELD(arg0, s16, 0x1C) = cap;
                }
            }
        } else {
            angle = FIELD(arg0, u16, 0x1C) + 0x800;
            FIELD(arg0, s16, 0x1C) = angle;
            if (cap < angle) {
                FIELD(arg0, s16, 0x1C) = limit;
            }
        }
    } else {
        angle = FIELD(arg0, u16, 0x1C) - 0x400;
        FIELD(arg0, s16, 0x1C) = angle;
        if (angle < 0) {
            FIELD(arg0, s16, 0x1C) = 0;
        }
    }

    FIELD(arg2, u16, 0x12) = FIELD(FIELD(arg0, void *, 0x14), u16, 0x12);
    FIELD(arg2, s32, 0xC) = FIELD(FIELD(arg0, void *, 0x14), s32, 0xC);
    FIELD(arg2, u16, 0x1C) = FIELD(arg0, u16, 0x1C) +
        (func_80064584(FIELD(arg0, s16, 0x20) << 8) >> 4);
    FIELD(arg2, u16, 0x1E) = FIELD(arg0, u16, 0x1C) +
        (func_800644B8(FIELD(arg0, s16, 0x20) << 8) >> 4);

    kind = *FIELD(arg0, u8 *, 4);
    if (kind == 0xF) {
        FIELD(arg0, s16, 0x22) =
            (func_80064584(FIELD(arg0, s16, 0x20) << 8) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x24) =
            (func_800644B8(FIELD(arg0, s16, 0x20) << 8) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x26) =
            (func_80064584((FIELD(arg0, s16, 0x20) << 8) + 0x200) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x28) =
            (func_800644B8((FIELD(arg0, s16, 0x20) << 8) + 0x200) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x2A) =
            (func_80064584((FIELD(arg0, s16, 0x20) << 8) + 0x400) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x2C) =
            (func_800644B8((FIELD(arg0, s16, 0x20) << 8) + 0x400) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x2E) =
            (func_80064584((FIELD(arg0, s16, 0x20) << 8) + 0x600) >> 3) + 0x1000;
        FIELD(arg0, s16, 0x30) =
            (func_800644B8((FIELD(arg0, s16, 0x20) << 8) + 0x600) >> 3) + 0x1000;
        goto increment;
    }
    if (kind == 0) {
        FIELD(arg0, s16, 0x1C) = 0;
        goto increment;
    }

    FIELD(arg0, s16, 0x30) = 0x1000;
    FIELD(arg0, s16, 0x2E) = 0x1000;
    FIELD(arg0, s16, 0x2C) = 0x1000;
    FIELD(arg0, s16, 0x2A) = 0x1000;
    FIELD(arg0, s16, 0x28) = 0x1000;
    FIELD(arg0, s16, 0x26) = 0x1000;
    FIELD(arg0, s16, 0x24) = 0x1000;
    FIELD(arg0, s16, 0x22) = 0x1000;
    goto increment;

active:
    value = FIELD(arg2, u16, 0x1C) + 0x100;
    FIELD(arg2, u16, 0x1C) = value;
    if (value < 0x2001U) {
        goto active_continue;
    }

failure:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
    goto done;

active_continue:
    FIELD(arg2, u16, 0x1E) += 0x100;

increment:
    FIELD(arg0, u16, 0x20)++;

done:
    return;
}
