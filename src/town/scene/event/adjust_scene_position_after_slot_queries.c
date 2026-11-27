#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"

void adjust_scene_position_after_slot_queries(void)
{
    TownPositionState *position;
    s32 mode;

    town_scene_root->services->anyone_now_ang_get(12);
    town_scene_root->services->callback_258(12);
    position = town_scene_root->position;
    mode = position->script_var_0;
    if (mode == 2 || mode == 0) {
        position->y += 0x40;
    } else {
        position->x -= 0x40;
    }
}
