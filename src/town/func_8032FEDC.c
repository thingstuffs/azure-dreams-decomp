#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"



/* Stores two values scaled by 32 in the current record's auxiliary data. */
void set_record_scaled_auxiliary_values(s32 unused, s32 value_04, s32 value_08) {
    ((TownPositionState *)D_80016000->unk_1C)->x = (s32) (value_04 << 5);
    ((TownPositionState *)D_80016000->unk_1C)->y = (s32) (value_08 << 5);
}
