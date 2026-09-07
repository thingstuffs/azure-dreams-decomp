#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 func_800A0818(s32, s32, s32, s32, void *);
extern void func_800CA1C8(void) __attribute__((noreturn));

extern u16 D_80083462;

void func_800CA0DC(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 count;
    s32 old_x;
    s32 old_y;

    if (FIELD(arg3, s8, 0x71) <= 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x71) <= FIELD(arg3, s16, 0x8A)) {
        return;
    }

    old_x = FIELD(arg2, u8, 0x24);
    old_y = FIELD(arg2, u8, 0x25);
    FIELD(arg2, u8, 0x24) =
        FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74);
    FIELD(arg2, u8, 0x25) =
        FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C);
    FIELD(arg3, u16, 0x8A)++;

    FIELD(arg3, s16, 0x2A) =
        func_800A0818(old_x, old_y, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25), (u8 *)arg0 + 0x98);
    FIELD(arg3, s32, 0x1C) |= 0x40000000;
    FIELD(arg0, u8, 0x9A) = 0xF;
    FIELD(arg0, s32, 0x8C) = 0;

    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        func_800CA1C8();
    }

    FIELD(arg0, s16, 0x96) = 8;
    count = FIELD(arg3, u8, 0x71);
    if (count > 0) {
        FIELD(arg0, s16, 0x96) = 8 / count;
    }
}
