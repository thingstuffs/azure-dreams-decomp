#include "modules/town_door.h"

/* Decrease the door opening angle and switch handlers when closed. */
void func_800A0958(S_800A0958_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E - 0x40;
    door->unk_6E = opening_angle;
    if ((opening_angle << 0x10) <= 0) {
        door->unk_6E = 0U;
        door->unk_50 = &func_800A07E8;
    }
}
