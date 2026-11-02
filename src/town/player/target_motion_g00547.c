/* Move player motion toward target coordinates (G00547). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0608. */
#include "town/player/target_motion_g00547.h"
#include "town/player.h"
#include "town/player/object.h"
#include "town/player/record.h"

/* Move the object toward its target and advance the state when the timer expires. */
void move_player_toward_target(UnsignedCountdownView *state_arg_arg, void *object) {
    TownPlayerRecord *state = (TownPlayerRecord *)state_arg_arg;

    u16 ticks_left;

    *(s32 *)((u8 *)object + 0x14) = (player_target_position[2] - *(s32 *)((u8 *)object + 8)) / 2;
    ticks_left = state->timer.as_u16 - 1;
    state->timer.as_u16 = ticks_left;
    if ((s16) ticks_left < 0) {
        *(s32 *)((u8 *)object + 8) = player_target_position[2];
        clear_entity_record_fields(object);
        state->timer.as_u16 = 0xA;
        state->unk_04 = &D_8009AAB8;
    }
}

/* Approach the target position and finish the motion when the countdown expires. */
void approach_player_target_position(UnsignedCountdownView *state_arg, void *motion)
{
    TownPlayerRecord *state = (TownPlayerRecord *)state_arg;

    u16 ticks_left;

    state->unk_10.as_u16 += 0x200;
    *(s32 *)((u8 *)motion + 0xC) =
        (player_target_position[0] - *(s32 *)((u8 *)motion + 0)) / 2;
    *(s32 *)((u8 *)motion + 0x10) =
        (player_target_position[1] - *(s32 *)((u8 *)motion + 4)) / 2;
    ticks_left = state->timer.as_u16 - 1;
    state->timer.as_u16 = ticks_left;
    if ((s16)ticks_left < 0) {
        *(s32 *)((u8 *)motion + 0) = player_target_position[0];
        *(s32 *)((u8 *)motion + 4) = player_target_position[1];
        clear_entity_record_fields(motion);
        state->unk_04 = &D_8009AB74;
        state->unk_10.as_u16 = 0;
    }
}
