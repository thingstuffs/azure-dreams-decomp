#include "modules/town_door.h"

/* Increase the door opening angle and switch handlers when fully open. */
void func_800A08F0(S_800A08F0_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E + 0x40;
    door->unk_6E = opening_angle;
    if ((s16) opening_angle >= 0x400) {
        door->unk_6E = 0x400U;
        door->unk_50 = &func_800A092C;
    }
}
