#include "common.h"
#include "shared/town_object.h"
#include "shared/entity.h"
#include "shared/vector.h"
#include "town/player/motion.h"
#include "town/player/object.h"
#include "town/player/state_update_g00548.h"


typedef struct Position {
    s32 x;
    s32 y;
    s32 z;
    s32 half_dx;
    s32 half_dy;
    s32 half_dz;
} Position;

extern IntVector3 player_halfway_target;


/* Compute half the offset to the target, then snap to it and advance state when the timer expires. */
void move_player_halfway_to_target(TownObjectRecord *state, ObjectPosition *position, SpriteFrameState *context)
{
    u16 timer;
    IntVector3 *target;

    target = &player_halfway_target;
    position->velocity_x = (target->x - position->x.v) / 2;
    position->velocity_y = (target->y - position->y.v) / 2;
    position->velocity_z = (target->z - position->z.v) / 2;

    timer = ((u16)state->unk_0A) - 1;
    state->unk_0A = timer;
    if ((s16)timer < 0) {
        position->x.v = target->x;
        position->y.v = target->y;
        position->z.v = target->z;
        clear_object_velocity(position);

        state->move_target_x = ((u16)position->x.w.i);
        state->move_target_y = ((u16)position->y.w.i);
        dispatch_selected_entry_if_nonzero(town_scene_record_handlers, state, context);

        state->unk_04 = update_player_global_state;
        state->player_facing = 0x400;
    }
}
