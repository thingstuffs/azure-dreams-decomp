#include "shared/sprite_frame_state.h"
#include "common.h"
#include "dungeon/actor.h"
#include "dungeon/actor/motion.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "dungeon/actor/status.h"
#include "dungeon/monster/picket.h"


#include "dungeon/actor/spend_actor_mp_api.h"

/*
 * On completed tile movement, spends MP and advances status timers, resuming behavior and clearing
 * its counter only after a positive signed floor-trap result. Clears the secondary action halfword
 * under dungeon status flag 0x80. /
 */
void update_the_target_conditionally_resets_caller_state(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    if (update_actor_movement_to_tile(body, position, sprite, actor) != 0) {
        spend_actor_mp(actor, 3);
        advance_status_timers(actor);
        if ((check_actor_floor_trap(sprite, actor) << 0x10) <= 0) {
            return;
        }
        body->unk_8C.handler = &update_dungeon_actor_behavior_facing_animation_state;
        body->unk_90.value = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        body->unk_90.parts.high = 0;
    }
}
