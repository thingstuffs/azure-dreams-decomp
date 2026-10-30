#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene.h"


/* Calls the state callback with 0xC and checks whether y is between 0x401 and 0x4FF. */
s32 check_scene_y_range(void) {
    town_scene_root->services->callback_258(0xC);
    return (u32)(town_scene_root->position->y - 0x401) < 0xFFU;
}
