#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/vector.h"
#include "town/scene/motion.h"



extern IntVector3 town_player_fixed_position;

/* Builds a record with two 16.16 values and a zero third value, then invokes the context callbacks. */
void set_player_position_record(void) {
    Rec_D_80016000 *context;
    IntVector3 *output;
    s32 source_value2;

    context = town_scene_root;
    town_player_fixed_position.x = context->position->x << 16;
    source_value2 = context->position->y;
    output = &town_player_fixed_position;
    output->z = 0;
    output->y = source_value2 << 16;
    ((void (*)(s32))context->services->callback_208)(0);
    town_scene_root->services->callback_224(output);
}
