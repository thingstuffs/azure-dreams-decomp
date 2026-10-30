#include "shared/town_pointees.h"
#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "town/scene.h"



/* Initialize the three context fields to 1, 11, and 3. */
void initialize_three_context_fields_1(void) {
    (*(s32 * *)((u8 *)(((void **)town_scene_root->position)) + 0)) = 1;
    town_scene_root->position->x = 11;
    town_scene_root->position->y = 3;
}
