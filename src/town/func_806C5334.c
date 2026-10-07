#include "common.h"
#include "shared/record_ptrs.h"
#include "m2c_compat.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



/* Invoke the context callback and check whether the stored value is below 0x3E0. */
s32 func_80016334(void) {
    ((void (*) (s32))D_80016000->unk_20->callback_248)(0);
    return ((TownPositionState *)D_80016000->unk_1C)->x
    < 0x3E0;
}
