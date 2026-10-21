/* Move player motion toward target coordinates (G00547). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - PD:town/engine:800D0608. */
#include "town/player/target_motion_g00547.h"

/* Move the object toward its target and advance the state when the timer expires. */
void move_player_toward_target(void *state, void *object) {
    u16 ticks_left;

    *(s32 *)((u8 *)object + 0x14) = (D_800D0608[2] - *(s32 *)((u8 *)object + 8)) / 2;
    ticks_left = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = ticks_left;
    if ((s16) ticks_left < 0) {
        *(s32 *)((u8 *)object + 8) = D_800D0608[2];
        clear_entity_record_fields(object);
        *(u16 *)((u8 *)state + 0xA) = 0xA;
        *(s32 **)((u8 *)state + 4) = &D_8009AAB8;
    }
}

/* Approach the target position and finish the motion when the countdown expires. */
void approach_player_target_position(void *state, void *motion)
{
    u16 ticks_left;

    *(u16 *)((u8 *)state + 0x10) += 0x200;
    *(s32 *)((u8 *)motion + 0xC) =
        (D_800D0608[0] - *(s32 *)((u8 *)motion + 0)) / 2;
    *(s32 *)((u8 *)motion + 0x10) =
        (D_800D0608[1] - *(s32 *)((u8 *)motion + 4)) / 2;
    ticks_left = *(u16 *)((u8 *)state + 0xA) - 1;
    *(u16 *)((u8 *)state + 0xA) = ticks_left;
    if ((s16)ticks_left < 0) {
        *(s32 *)((u8 *)motion + 0) = D_800D0608[0];
        *(s32 *)((u8 *)motion + 4) = D_800D0608[1];
        clear_entity_record_fields(motion);
        *(s32 **)((u8 *)state + 4) = &D_8009AB74;
        *(u16 *)((u8 *)state + 0x10) = 0;
    }
}
