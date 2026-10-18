#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"


/* Set the current record's two state values to 0x560 and 0x3E0. */
void set_scene_record_state_offsets(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 0x560;
    ((TownPositionState *)D_80016000->unk_1C)->y = 0x3E0;
}
