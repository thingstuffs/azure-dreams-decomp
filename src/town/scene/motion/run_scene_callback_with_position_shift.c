#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef void (*Callback)(s32);


/* Invoke both town callbacks with 1 and shift the position by (+32, -16). */
void run_scene_callback_with_position_shift(void)
{
    town_scene_root->services->callback_248(1);
    town_scene_root->services->callback_244(1);
    ((TownPositionState *)town_scene_root->position)->x += 0x20;
    ((TownPositionState *)town_scene_root->position)->y -= 0x10;
}
