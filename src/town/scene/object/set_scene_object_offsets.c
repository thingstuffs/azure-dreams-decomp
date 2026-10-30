#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/object.h"


/* Set the referenced structure's two values to 1248 and 992. */
void set_scene_object_offsets(void) {
    town_scene_root->position->x = 1248;
    town_scene_root->position->y = 992;
}
