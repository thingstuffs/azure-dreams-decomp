#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef void (*Callback)(s32);


/* Invoke both town callbacks with 1 and shift the position by (+32, -16). */
void func_80017270(void)
{
    D_80016000->unk_20->callback_248(1);
    D_80016000->unk_20->callback_244(1);
    ((TownPositionState *)D_80016000->unk_1C)->x += 0x20;
    ((TownPositionState *)D_80016000->unk_1C)->y -= 0x10;
}
