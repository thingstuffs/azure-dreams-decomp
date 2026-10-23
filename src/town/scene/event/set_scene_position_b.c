#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

/* Set the scene position record: state word 1, x = 0x2A, y = 8. */
void set_scene_position_0x2a_8(void) {
    *(s32 *)town_scene_root->position = 1;
    ((TownPositionState *)town_scene_root->position)->x = 0x2A;
    ((TownPositionState *)town_scene_root->position)->y = 8;
}
