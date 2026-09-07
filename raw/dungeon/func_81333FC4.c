#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s32 func_8009A66C();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801739C0[8];
extern u8 D_801739C8[8];
extern u8 D_801739D0[8];
extern u8 D_801739D8[8];

void func_8016AFC4(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 move_mode;
    s32 behavior;
    s32 count;
    s32 old_x;
    s32 old_y;
    s16 direction;
    u8 *entry;

    if (FIELD(arg3, s8, 0x71) <= 0) {
        return;
    }
    {
        s32 path_count = FIELD(arg3, u8, 0x71);
        if (FIELD(arg3, s16, 0x8A) >= path_count) {
            return;
        }
    }

    behavior = FIELD(arg0, u8, 0xAC);
    switch (behavior) {
    case 0:
        if (FIELD(arg2, u8 *, 0x2C) != D_801739C0) {
            FIELD(arg2, u8 *, 0x2C) = D_801739C0;
            func_80047784(arg2,
                D_801739C0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 1:
        if (FIELD(arg2, u8 *, 0x2C) != D_801739C8) {
            FIELD(arg2, u8 *, 0x2C) = D_801739C8;
            func_80047784(arg2,
                D_801739C8[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 2:
        if (FIELD(arg2, u8 *, 0x2C) != D_801739D0) {
            FIELD(arg2, u8 *, 0x2C) = D_801739D0;
            func_80047784(arg2,
                D_801739D0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        break;
    case 3:
        if (FIELD(arg2, u8 *, 0x2C) != D_801739D8) {
            FIELD(arg2, u8 *, 0x2C) = D_801739D8;
            func_80047784(arg2,
                D_801739D8[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                0);
        }
        break;
    }

    move_mode = 0x3000;
    old_x = FIELD(arg2, u8, 0x24);
    old_y = FIELD(arg2, u8, 0x25);
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        move_mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, move_mode);

    entry = (u8 *)arg3 + FIELD(arg3, s16, 0x8A);
    direction = func_800A0818(old_x, old_y, FIELD(entry, u8, 0x74),
                              FIELD(entry, u8, 0x7C), (u8 *)arg0 + 0x98);
    func_8009A66C(direction, arg2, arg3, 0x20);

    FIELD(arg2, u8, 0x24) =
        FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74);
    FIELD(arg2, u8, 0x25) =
        FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C);
    FIELD(arg3, u16, 0x8A)++;

    func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                  (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);

    FIELD(arg3, s16, 0x2A) = direction;
    FIELD(arg0, s8, 0x9A) = 0xF;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg3, s32, 0x1C) |= 0x40000000;

    if (D_80083462 & 0x80) {
        FIELD(arg0, s16, 0x96) = 0;
        return;
    }

    if (FIELD(arg0, u8, 0xB0) != 0) {
        FIELD(arg0, s16, 0x96) = 0x10;
    } else {
        FIELD(arg0, s16, 0x96) = 8;
    }
    count = FIELD(arg3, u8, 0x71);
    if (count > 0) {
        FIELD(arg0, s16, 0x96) = FIELD(arg0, s16, 0x96) / count;
    }
}
