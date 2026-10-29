#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/motion.h"

typedef void (*Callback)(s32);


/* Invoke the town callback with 1 and advance both position coordinates by 0x40. */
void shift_scene_position(void)
{
    town_scene_root->services->callback_248(1);
    ((TownPositionState *)town_scene_root->position)->x += 0x40;
    ((TownPositionState *)town_scene_root->position)->y += 0x40;
}
