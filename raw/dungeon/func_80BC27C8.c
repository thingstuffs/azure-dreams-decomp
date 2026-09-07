#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s32 func_80047784();
extern s32 func_8009A21C();
extern s32 func_8009A3D0();
extern s16 func_800A0818();

extern s16 D_80083228;
extern u16 D_80083462;
extern u8 D_80174634[];

void func_80171FC8(void *arg0, s32 arg1, void *arg2, void *arg3)
{
    s32 distance;
    s32 flags;
    s32 old_x;
    s32 old_y;
    s32 count;
    u16 hp;
    u16 energy;
    u16 step;
    void *tile;

    if (FIELD(arg3, s8, 0x71) <= 0) {
        return;
    }
    if ((s32)FIELD(arg3, u8, 0x71) <= FIELD(arg3, s16, 0x8A)) {
        return;
    }

    if (FIELD(arg2, u8 *, 0x2C) != D_80174634) {
        FIELD(arg2, u8 *, 0x2C) = D_80174634;
        func_80047784(arg2,
                     D_80174634[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7],
                     0);
    }

    tile = (u8 *)arg3 + FIELD(arg3, s16, 0x8A);
    if (FIELD(arg2, u8, 0x24) == FIELD(tile, u8, 0x74) &&
        FIELD(arg2, u8, 0x25) == FIELD(tile, u8, 0x7C)) {
        hp = FIELD(arg0, u16, 0x92);
        energy = FIELD(arg3, u16, 0x88);
        FIELD(arg0, u16, 0x92) = hp + 0x20;
        step = FIELD(arg3, u16, 0x8A);
        FIELD(arg3, u16, 0x88) = energy - 0x20;
        FIELD(arg3, u16, 0x8A) = step + 1;
        goto update_state;
    }

    flags = FIELD(arg3, s32, 0x1C);
    old_x = FIELD(arg2, u8, 0x24);
    old_y = FIELD(arg2, u8, 0x25);
    distance = 0x3000;
    if (flags & 0x2000) {
        distance = 0x300;
    }
    
    func_8009A3D0(old_x, old_y, distance);

    FIELD(arg2, u8, 0x24) = FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x74);
    FIELD(arg2, u8, 0x25) = FIELD((u8 *)arg3 + FIELD(arg3, s16, 0x8A), u8, 0x7C);
    FIELD(arg3, u16, 0x8A) += 1;

    func_8009A21C(FIELD(arg2, u8, 0x24), FIELD(arg2, u8, 0x25),
                  (FIELD(arg3, s32, 0x1C) & 0x2000) ? 0x300 : 0x3000);

    FIELD(arg3, s16, 0x2A) =
        func_800A0818(old_x, old_y, FIELD(arg2, u8, 0x24),
                      FIELD(arg2, u8, 0x25), (u8 *)arg0 + 0x98);

update_state:
    FIELD(arg0, s8, 0x9A) = 0xF;
    FIELD(arg0, s32, 0x8C) = 0;
    FIELD(arg3, s32, 0x1C) |= 0x40000000;

    if (D_80083462 & 0x80) {
        FIELD(arg0, u16, 0x96) = 0;
        goto done;
    }

    FIELD(arg0, u16, 0x96) = 8;
    count = FIELD(arg3, u8, 0x71);
    if (count > 0) {
        FIELD(arg0, u16, 0x96) = 8 / count;
    }

done:
    return;
}
