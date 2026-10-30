#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/object.h"


/* Set the inner object's unk4 and unk8 fields to 1248 and 1184. */
void set_scene_object_offset_b(void) {
    town_scene_root->position->x = 1248;
    town_scene_root->position->y = 1184;
}
