#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "m2c_compat.h"
#include "town/scene/motion.h"



/* Scale both position components by 64 and add the 0x220 offset. */
void scale_scene_position(void) {
    TownPositionState *first_position;
    TownPositionState *second_position;

    first_position = town_scene_root->position;
    first_position->x = (s32) ((first_position->x << 6) + 0x220);
    second_position = town_scene_root->position;
    second_position->y = (s32) ((second_position->y << 6) + 0x220);
}
