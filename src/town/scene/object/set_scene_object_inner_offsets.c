#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the current object's inner values to 1696 and 1184. */
void set_scene_object_inner_offsets(void) {
    ((TownPositionState *)D_80016000->unk_1C)->x = 1696;
    ((TownPositionState *)D_80016000->unk_1C)->y = 1184;
}
