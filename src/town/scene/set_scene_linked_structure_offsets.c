#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"


/* Set the linked structure's two values to 1248 and 1184. */
void set_scene_linked_structure_offsets(void) {
    ((TownPositionState *)town_scene_root->position)->x = 1248;
    ((TownPositionState *)town_scene_root->position)->y = 1184;
}
