#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/town_pointees.h"
#include "town/scene/motion.h"


extern s32 D_800190C0[3];


/* Store two 16.16 values, clear the third component, and invoke both callbacks. */
void submit_player_position_record(void) {
    s32 *fixed_values;
    s32 second_value;

    D_800190C0[0] =
        town_scene_root->position->x
    << 16;
    second_value =
        town_scene_root->position->y;
    fixed_values = D_800190C0;
    fixed_values[2] = 0;
    fixed_values[1] = second_value << 16;
    ((s32 (*) (s32))town_scene_root->services->callback_208)(0);
    ((s32 (*) (s32))town_scene_root->services->callback_228)(0);
}
