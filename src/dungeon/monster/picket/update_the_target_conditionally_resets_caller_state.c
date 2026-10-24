#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"

typedef struct S_801724A8_0 {
    u8 pad_00[0x8C];
    s32 * unk_8C;
    union { struct { s32 v; } at00; struct { u8 pad[0x2]; s16 v; } at02; } unk_90;   /* overlapping accesses */
} S_801724A8_0;   /* arg0 in update_the_target_conditionally_resets_caller_state */


s32 advance_status_timers();                     /* extern */
void spend_actor_mp();            /* extern */
                /* extern */
void update_dungeon_actor_behavior_facing_animation_state(void *actor, void *context, void *sprite, ActorRecord *entity);

/*
 * On completed tile movement, spends MP and advances status timers, resuming behavior and clearing
 * its counter only after a positive signed floor-trap result. Clears the secondary action halfword
 * under dungeon status flag 0x80. /
 */
void update_the_target_conditionally_resets_caller_state(S_801724A8_0 *state, void *context, void *source, ActorRecord *target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        spend_actor_mp(target, 3);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = &update_dungeon_actor_behavior_facing_animation_state;
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
