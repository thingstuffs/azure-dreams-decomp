#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"

#include "shared/entity.h"
#include "dungeon/actor.h"
#include "dungeon/actor/status.h"



void spend_actor_mp(ActorRecord *entity, s32 base_reduction);            /* extern */
                /* Updates the target and resets state after a successful check or a reset flag. */
void update_actor_target_after_check(ActorRecord *state, ObjectPosition *motion, SpriteFrameState *sprite, ActorRecord *target) {
    if (update_actor_movement_to_tile(state, motion, sprite, target) != 0) {
        spend_actor_mp(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(sprite, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C.handler = &update_actor_facing_animation;
        state->unk_90.value = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.parts.high.s = 0;
    }
}
