#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


typedef s32 (*Callback)(s32);



/* Runs the context callback and checks whether the state code is in 0x3DC through 0x3E4. */
s32 func_800162C4(void) {
    s32 stateCode;

    ((Callback)D_80016000->unk_20->callback_248)(0);
    stateCode =
        ((TownPositionState *)D_80016000->unk_1C)->x;
    return stateCode >= 0x3E0 ? stateCode < 0x3E5 : stateCode >= 0x3DC;
}
