#include "modules/town_door.h"

/* Set the object handler when func_800352FC returns zero. */
void townSetDoorHandlerIfReady(S_800A0CC0_0 *object, s32 value_1, s32 value_2, s32 value_3) {
    if (func_800352FC() == 0) {
        object->unk_50 = &townSelectTowerEntryHandlerByItemCount;
    }
}
