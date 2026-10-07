#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Stores two values scaled by 32 in the current record's auxiliary data. */
void func_8001A6DC(M2C_UNK unused, s32 value_04, s32 value_08) {
    ((TownPositionState *)D_80016000->unk_1C)->x = (s32) (value_04 << 5);
    ((TownPositionState *)D_80016000->unk_1C)->y = (s32) (value_08 << 5);
}
