#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80175140[];
extern u8 D_80175148[];

void func_80171960(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    u8 *table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 mode;

    if (FIELD(arg3, s8, 0x71) <= 0) {
        return;
    }
    if (FIELD(arg3, u8, 0x71) <= FIELD(arg3, s16, 0x8A)) {
        return;
    }

    table = FIELD(arg2, u8 *, 0x2C);
    if (table != D_80175140 && table != D_80175148) {
        FIELD(arg2, u8 *, 0x2C) = D_80175140;
        func_80047784(
            arg2,
            D_80175140[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
            0);
        FIELD(arg0, s16, 0xA8) = 0;
    }

    old_x = FIELD(arg2, u8, 0x24);
    old_y = FIELD(arg2, u8, 0x25);
    mode = 0x3000;
    if (FIELD(arg3, s32, 0x1C) & 0x2000) {
        mode = 0x300;
    }
    func_8009A3D0(old_x, old_y, mode);

    FIELD(arg2, u8, 0x24) =
        FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74);
    FIELD(arg2, u8, 0x25) =
        FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C);
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
    FIELD(arg3, u32, 0x1C) |= 0x40000000;
    FIELD(arg0, u8, 0x9A) = 0xF;
    FIELD(arg0, s32, 0x8C) = 0;

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

/* MECHANISM:
 * Mirror the byte-exact movement-family source shape: keep the dead a1 ABI
 * slot, hold old coordinates in s3/s4, and use a signed-word tail count.
 * The 0x80171B04 jump is the local early-return epilogue.
 */
