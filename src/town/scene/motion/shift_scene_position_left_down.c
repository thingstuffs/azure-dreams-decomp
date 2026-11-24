#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/motion.h"

/* Invoke the town callback with 1 and move the position by -0x40 in X and +0x40 in Y. */
void shift_scene_position_left_down(void)
{
    town_scene_root->services->callback_248(1);
    town_scene_root->position->x -= 0x40;
    town_scene_root->position->y += 0x40;
}
