#include "common.h"

typedef struct Entry {
    s32 field0;
    s32 field4;
    s32 field8;
    s32 fieldC;
} Entry;

extern void func_800DC628(void *arg0, s32 arg1);

void func_800DCAC4(void *arg0, s32 arg1) {
    void *p = arg0;
    s32 i;
    s32 offset;

    for (i = 0; i < 9; i++) {
        ((Entry *)*(s8 **)((s8 *)p + 0))[i].field4 =
            (s32)(((Entry *)*(s8 **)((s8 *)p + 4)) + i);
    }

    i = 0;
    do { offset = i; } while (0);
    for (; i < 9; i++, offset += 0xC) {
        ((Entry *)*(s8 **)((s8 *)p + 0))[i].field8 =
            (s32)(*(s8 **)((s8 *)p + 8) + offset);
    }

    for (i = 0; i < 9; i++) {
        ((Entry *)*(s8 **)((s8 *)p + 0))[i].field0 =
            ((s32 *)*(s8 **)((s8 *)p + 0xC))[i];
    }

    *(s16 *)(*(s8 **)((s8 *)p + 8) + 0x12) = 0x5F;
    *(s16 *)(*(s8 **)((s8 *)p + 8) + 0x1E) = 0x61;
    *(s16 *)(*(s8 **)((s8 *)p + 8) + 0x44) = -0xF;
    *(s16 *)(*(s8 **)((s8 *)p + 4) + 0x88) = 0x9A;
    *(s16 *)(*(s8 **)((s8 *)p + 4) + 0x8A) = 0x69;
    *(s16 *)(*(s8 **)((s8 *)p + 8) + 0x68) = -0xF;
    *(s16 *)(*(s8 **)((s8 *)p + 8) + 0x60) = 0x800;

    if (arg1 != 0) {
        do {
            return func_800DC628(p, 0x400);
        } while (0);
    }
    func_800DC628(p, 0);
}
