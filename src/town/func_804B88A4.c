#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef void (*TownCallback)(s32);


/* Runs the town callbacks and offsets the position based on its x value. */
void func_800170A4(void)
{
    TownPositionState *position;
    s32 position_x;

    D_80016000->unk_20->callback_258(0xB);
    D_80016000->unk_20->callback_244(1);

    position = D_80016000->unk_1C;
    position_x = position->unk_00;
    if (position_x == 2 || position_x == 0) {
        position->y += 0x30;
        return;
    }
    position->x -= 0x40;
}
