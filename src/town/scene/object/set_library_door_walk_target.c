#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene/object.h"


/* Sets the global object's inner fields to 1248 and 1184. */
void set_library_door_walk_target(void) {
    Rec_D_80016000 *outer = town_scene_root;
    outer->position->x = 1248;
    outer->position->y = 1184;
}
