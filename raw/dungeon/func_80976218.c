#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_801740E0[];
extern u8 D_801740E8[];

void func_80171A18(void *arg0, s32 arg1, void *arg2, void *arg3) {
    void *cell;
    u8 *table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 mode;
    s32 value_92;
    s32 value_88;

    if (FIELD(arg3, s8, 0x71) <= 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x71) <= FIELD(arg3, s16, 0x8A)) {
        return;
    }

    table = FIELD(arg2, u8 *, 0x2C);
    if (table != D_801740E0 && table != D_801740E8) {
        FIELD(arg2, u8 *, 0x2C) = D_801740E0;
        func_80047784(
            arg2,
            D_801740E0[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
    }

    cell = (u8 *)arg3 + FIELD(arg3, s16, 0x8A);
    if (FIELD(arg2, u8, 0x24) == FIELD(cell, u8, 0x74) &&
        FIELD(arg2, u8, 0x25) == FIELD(cell, u8, 0x7C)) {
        value_92 = FIELD(arg0, u16, 0x92);
        value_88 = FIELD(arg3, u16, 0x88);
        FIELD(arg0, u16, 0x92) = value_92 + 0x20;
        FIELD(arg3, u16, 0x88) = value_88 - 0x20;
        FIELD(arg3, u16, 0x8A) = FIELD(arg3, u16, 0x8A) + 1;
        goto finish_move;
    }

    old_x = FIELD(arg2, u8, 0x24);
    old_y = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, mode);

    FIELD(arg2, u8, 0x24) = FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74);
    FIELD(arg2, u8, 0x25) = FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C);
    FIELD(arg3, u16, 0x8A)++;

    new_x = FIELD(arg2, u8, 0x24);
    new_y = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A21C(new_x, new_y, mode);

    FIELD(arg3, s16, 0x2A) = func_800A0818(
        old_x, old_y, FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
        (u8 *)arg0 + 0x98);

finish_move:
    FIELD(arg0, u8, 0x9A) = 0xF;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg3, u32, 0x1C) |= 0x40000000;

    if (D_80083462 & 0x80) {
        FIELD(arg0, u16, 0x96) = 0;
        return;
    }

    FIELD(arg0, u16, 0x96) = 8;
    {
        s32 hp = FIELD(arg3, u8, 0x71);
        if (hp > 0) {
            FIELD(arg0, u16, 0x96) = 8 / hp;
        }
    }
}
