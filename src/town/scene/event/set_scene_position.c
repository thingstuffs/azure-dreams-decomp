#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/event.h"

/* Set the scene position record: state word 1, x = 0x15, y = 8. */
void set_scene_position_0x15_8(void) {
    *(s32 *)town_scene_root->position = 1;
    ((TownPositionState *)town_scene_root->position)->x = 0x15;
    ((TownPositionState *)town_scene_root->position)->y = 8;
}
