#include "shared/entity.h"
#include "common.h"
#include "shared/town_object.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "shared/position_views.h"
#include "town/person/position.h"
#include "town/person.h"



   /* target in ease_reaction_position_with_vertical_offset */


/* Decrement the lifetime and ease the position toward the target with a vertical offset. */
void ease_reaction_position_with_vertical_offset(TownObjectRecord *state_arg, void *position_arg) {
    TownObjectRecord *state = state_arg;
    ObjectNodeHeader *target_table;
    s32 x_delta;
    s32 y_delta;
    u16 ticks_left;
    ObjectPosition *position = position_arg;

    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        initialize_reaction_data_and_timer_13(state);
        return;
    }
    target_table = &scene_object_list_anchor;
    x_delta = target_table->position->x.w.i
        - position->x.w.i;
    position->x.w.i = (s16) ((u16) position->x.w.i + (x_delta / 4));
    y_delta = target_table->position->y.w.i
        - position->y.w.i;
    position->y.w.i = (s16) ((u16) position->y.w.i + (y_delta / 4));
    {
        ObjectPosition *target;
        s32 z_step;
        s32 target_z;

        target = target_table->position;
        z_step = position->z.w.i;
        target_z = target->z.w.i;
        z_step += 0xD0;
        z_step = target_z - z_step;
        position->z.w.i += z_step / 4;
    }
}
