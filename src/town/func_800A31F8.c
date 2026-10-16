#include "modules/town_door.h"

/* Decrease the door opening angle and switch handlers when closed. */
void townAdvanceDoorCloseAngle(S_800A0958_0 *door) {
    u16 opening_angle;

    opening_angle = door->unk_6E - 0x40;
    door->unk_6E = opening_angle;
    if ((opening_angle << 0x10) <= 0) {
        door->unk_6E = 0U;
        door->unk_50 = &townEmitDoorPositionEffect;
    }
}
