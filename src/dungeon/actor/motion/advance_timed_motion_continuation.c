#include "common.h"
#include "shared/entity.h"
#include "dungeon/actor/motion.h"
#include "dungeon/level.h"
#include "shared/dungeon_status.h"

typedef struct S_80097AF8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_80097AF8_1;   /* arg1 in advance_timed_motion_continuation */

typedef struct S_80097AF8_2 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_80097AF8_2;   /* arg2 in advance_timed_motion_continuation */


typedef struct S_80097AF8_4 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x3C];
    void * unk_5C;
} S_80097AF8_4;   /* arg3 in advance_timed_motion_continuation */

/* Advance the timed motion sequence and select its continuation when status flags allow. */
void advance_timed_motion_continuation(ActorRecord *actor, S_80097AF8_1 *motion, S_80097AF8_2 *status, S_80097AF8_4 *owner)
{
    s32 state;
    s32 owner_flags;
    u16 state_ticks;
    u8 next_state;

    state = actor->action_phase;
    switch (state) {
    case 0:
        state_ticks = actor->action_timer - 1;
        actor->action_timer = state_ticks;
        if ((state_ticks << 16) > 0) {
            return;
        }
        motion->unk_14 = 0xFFEA0000;
        next_state = actor->action_phase;
        actor->action_timer = 0;
        next_state++;
        actor->action_phase = next_state;
        return;
    case 1:
        state_ticks = actor->action_timer + 1;
        actor->action_timer = state_ticks;
        if ((actor->unk_A0.parts.high & 0x10) == 0) {
            return;
        }
        if ((s16)state_ticks < 4) {
            return;
        }
        motion->unk_14 = 0;
        next_state = actor->action_phase;
        next_state++;
        actor->action_phase = next_state;
        return;
    case 2:
        if ((status->unk_14 & 0x6000) == 0) {
            return;
        }
        if (g_dungeon_status.activity_counts.parts.pending_action_count != 0) {
            return;
        }
        owner_flags = owner->unk_1C;
        if (owner_flags & 0x200000) {
            owner->unk_1C = owner_flags & 0xFFDFFFFF;
            g_dungeon_status.flags |= 0x412;
            process_unflagged_linked_entries_alt(owner->unk_5C);
            process_unflagged_linked_entries(owner->unk_5C);
        }
        actor->unk_8C.handler = update_actor_commands_and_facing;
        return;
    }
}
