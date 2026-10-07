#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef void (*Callback)(s32);


/* Invoke the town callback with 1 and advance both position coordinates by 0x40. */
void func_800171CC(void)
{
    D_80016000->unk_20->callback_248(1);
    ((TownPositionState *)D_80016000->unk_1C)->x += 0x40;
    ((TownPositionState *)D_80016000->unk_1C)->y += 0x40;
}
