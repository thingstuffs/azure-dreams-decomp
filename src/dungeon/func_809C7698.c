/* Relink of matched dungeon/func_809A3698; every changed retail word is a paired relocation. */
#include "modules/dungeon_ovl_9c32d4.h"

void func_80150E98(ovl_9c32d4_809A3698_MotionState *state, ovl_9c32d4_809A3698_MotionPosition *position) {
    s16 height;
    s16 speed;
    height = func_800BCB04(position->x.ovl_9c32d4_809A3698_half.high, position->y.ovl_9c32d4_809A3698_half.high, (s16)(position->z.ovl_9c32d4_809A3698_half.high + 2));
    if ((s16)position->z.ovl_9c32d4_809A3698_half.high < height) {
        position->x.word -= (D_8006CCD8[state->direction] * state->speed) << 11;
        position->y.word -= (D_8006CCE8[state->direction] * state->speed) << 11;
        position->z.word += (0xC0 - state->speed) << 10;
    }
    speed = state->speed - 8;
    state->speed = speed;
    if (speed <= 0) {
        *(u16 *)((u8 *)state - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
