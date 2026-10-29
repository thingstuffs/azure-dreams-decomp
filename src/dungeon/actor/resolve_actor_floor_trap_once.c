#include "common.h"
#include "shared/entity.h"
#include "dungeon/actor/state.h"
#include "dungeon/player/object.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

extern s32 trigger_actor_floor_trap(void *, void *);

/* Attempts a pending action and updates dungeon state on success. */
s32 resolve_actor_floor_trap_once(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 result;

    if (body->action_phase.u == 0) {
        actor->movement_queue_state &= 0x7F;
        if (g_dungeon_status.flags & 0x2000) {
            return 0;
        }
        if ((try_claim_dungeon_action_slot(actor) << 16) != 0) {
            return 0;
        }

        result = trigger_actor_floor_trap(sprite, actor);
        if ((result << 16) != 0) {
            g_dungeon_status.active_actor = 0;
            g_dungeon_status.trap_counts.parts.pending_trap_count -= 1;
            body->action_phase.u = 1;
        }
    } else {
        result = 1;
    }
    return (s16)result;
}
