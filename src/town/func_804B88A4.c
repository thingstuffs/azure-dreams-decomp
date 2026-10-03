#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

typedef void (*TownCallback)(s32);

typedef struct {
    s32 value_00;
    s32 value_04;
    s32 value_08;
} TownPosition;


/* Runs the town callbacks and offsets the position based on its x value. */
void func_800170A4(void)
{
    TownPosition *position;
    s32 position_x;

    D_80016000->unk_20->callback_258(0xB);
    D_80016000->unk_20->callback_244(1);

    position = ((TownPosition *)D_80016000->unk_1C);
    position_x = position->value_00;
    if (position_x == 2 || position_x == 0) {
        position->value_08 += 0x30;
        return;
    }
    position->value_04 -= 0x40;
}
