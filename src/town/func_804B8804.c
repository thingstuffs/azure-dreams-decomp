#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"


/* Sets the global object's inner fields to 1248 and 1184. */
void set_scene_global_object_offsets(void) {
    Rec_D_80016000 *outer = D_80016000;
    ((TownPositionState *)outer->unk_1C)->x = 1248;
    ((TownPositionState *)outer->unk_1C)->y = 1184;
}
