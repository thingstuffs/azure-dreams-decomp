#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/object.h"


/* Sets the global object's inner fields to 1248 and 1184. */
void set_scene_global_object_offsets(void) {
    Rec_D_80016000 *outer = town_scene_root;
    ((TownPositionState *)outer->position)->x = 1248;
    ((TownPositionState *)outer->position)->y = 1184;
}
