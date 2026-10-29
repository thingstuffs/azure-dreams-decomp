#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/object.h"


/* Set the referenced object's unk4 and unk8 fields to 800 and 736. */
void set_scene_object_offset_a(void) {
    ((TownPositionState *)town_scene_root->position)->x = 800;
    ((TownPositionState *)town_scene_root->position)->y = 736;
}
