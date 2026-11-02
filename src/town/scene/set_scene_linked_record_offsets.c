#include "common.h"
#include "shared/record_ptrs.h"
#include "town/scene.h"
#include "shared/town_root.h"


/* Set the linked record's second and third values to 1696 and 800. */
void set_scene_linked_record_offsets(void) {
    town_scene_root->position->x = 1696;
    town_scene_root->position->y = 800;
}
