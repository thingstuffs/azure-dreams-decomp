#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"

typedef void (*TownCallback)(s32);


/* Runs the town callbacks and offsets the position based on its x value. */
void run_scene_callbacks_with_x_offset(void)
{
    TownPositionState *position;
    s32 position_x;

    town_scene_root->services->callback_258(0xB);
    town_scene_root->services->callback_244(1);

    position = town_scene_root->position;
    position_x = position->unk_00;
    if (position_x == 2 || position_x == 0) {
        position->y += 0x30;
        return;
    }
    position->x -= 0x40;
}
