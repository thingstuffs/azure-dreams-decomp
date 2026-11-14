/* Move player motion toward target coordinates. */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0608. */
#include "town/player/target_motion_g00547.h"
#include "town/player.h"
#include "town/player/object.h"
#include "town/player/record.h"

/* Move the object toward its target and advance the state when the timer expires. */
void move_player_toward_target(UnsignedCountdownView *state_arg_arg, ObjectPosition *object) {
    TownPlayerRecord *state = (TownPlayerRecord *)state_arg_arg;

    u16 ticks_left;

    object->velocity_z = (player_target_position[2] - object->z.v) / 2;
    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((s16) ticks_left < 0) {
        object->z.v = player_target_position[2];
        clear_object_velocity(object);
        state->timer = 0xA;
        state->unk_04 = &D_8009AAB8;
    }
}

/* Approach the target position and finish the motion when the countdown expires. */
void approach_player_target_position(UnsignedCountdownView *state_arg, ObjectPosition *motion)
{
    TownPlayerRecord *state = (TownPlayerRecord *)state_arg;

    u16 ticks_left;

    state->unk_10 = (u16)(state->unk_10 + 0x200);
    motion->velocity_x =
        (player_target_position[0] - motion->x.v) / 2;
    motion->velocity_y =
        (player_target_position[1] - motion->y.v) / 2;
    ticks_left = state->timer - 1;
    state->timer = ticks_left;
    if ((s16)ticks_left < 0) {
        motion->x.v = player_target_position[0];
        motion->y.v = player_target_position[1];
        clear_object_velocity(motion);
        state->unk_04 = &D_8009AB74;
        state->unk_10 = 0;
    }
}
