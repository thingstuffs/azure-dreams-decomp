#include "common.h"

#define FIELD(obj, type, offset) (*(type *)((u8 *)(obj) + (offset)))

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} Vec3s;

extern s32 func_8003DE58(void *, void *, Vec3s *, s32);

extern s32 D_800814A0[3];
extern u8 D_80175E54[];
extern u8 D_80175E5C[];
extern u8 D_80175E64[];

void func_80171A38(void *arg0, void *arg1, void *arg2)
{
    void *record;
    void *part;
    void *source;
    u16 next_value;
    Vec3s delta;

    record = (u8 *)FIELD(arg0, void *, 0x20) - 0x20;
    if ((FIELD(record, u16, 0x1e) & 0x8000) != 0) {
        goto mark_used;
    }

    do { part = FIELD(record, void *, 0xc); } while (0);
    next_value = FIELD(part, u16, 6);
    source = FIELD(record, void *, 8);
    FIELD(arg2, u16, 6) = next_value + 1;

    if (FIELD(part, s8, 4) == 0) {
        FIELD(arg2, s16, 0x1e) = 0x400;
        FIELD(arg2, s16, 0x1c) = 0x400;
    }
    if (FIELD(part, s8, 4) == 1) {
        FIELD(arg2, s16, 0x1e) = 0x700;
        FIELD(arg2, s16, 0x1c) = 0x700;
    }
    if (FIELD(part, s8, 4) == 2) {
        FIELD(arg2, s16, 0x1e) = 0xa00;
        FIELD(arg2, s16, 0x1c) = 0xa00;
    }
    if (FIELD(part, s8, 4) == 3) {
        FIELD(arg2, s16, 0x1e) = 0x700;
        FIELD(arg2, s16, 0x1c) = 0x700;
    }
    if (FIELD(part, s8, 4) == 4) {
        FIELD(arg2, s16, 0x1e) = 0x400;
        FIELD(arg2, s16, 0x1c) = 0x400;
    }

    FIELD(arg1, u16, 2) = FIELD(source, u16, 2);
    FIELD(arg1, u16, 6) = FIELD(source, u16, 6);
    FIELD(arg1, u16, 0xa) = FIELD(source, u16, 0xa);

    if (func_8003DE58(
            FIELD(FIELD(record, void *, 0xc), void *, 8),
            FIELD(record, void *, 0xc), &delta, 0) != 0) {
        FIELD(arg1, u16, 2) += delta.x;
        FIELD(arg1, u16, 6) += delta.y;
        FIELD(arg1, u16, 0xa) += delta.z;
    }

    if (FIELD(part, void *, 0x2c) == D_80175E54 ||
        FIELD(part, void *, 0x2c) == D_80175E5C ||
        FIELD(part, void *, 0x2c) == D_80175E64) {
        return;
    }

mark_used:
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0[0] |= 0x8000;
}
