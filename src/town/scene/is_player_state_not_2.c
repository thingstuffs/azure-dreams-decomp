#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"



/* Returns whether the referenced record's unk_38 field differs from 2. */
s32 is_player_state_not_2(void) {
    return ((TownPositionState *)D_80016000->unk_1C)->unk_38 != 2;
}
