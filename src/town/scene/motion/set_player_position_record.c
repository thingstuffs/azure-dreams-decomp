#include "common.h"
#include "shared/record_ptrs.h"
#include "shared/town_root.h"
#include "shared/vector.h"



extern IntVector3 D_80019AE0;

/* Builds a record with two 16.16 values and a zero third value, then invokes the context callbacks. */
void set_player_position_record(void) {
    Rec_D_80016000 *context;
    IntVector3 *output;
    s32 source_value2;

    context = town_scene_root;
    D_80019AE0.x = ((TownPositionState *)context->position)->x << 16;
    source_value2 = ((TownPositionState *)context->position)->y;
    output = &D_80019AE0;
    output->z = 0;
    output->y = source_value2 << 16;
    ((void (*)(s32))context->services->callback_208)(0);
    town_scene_root->services->callback_224(output);
}
