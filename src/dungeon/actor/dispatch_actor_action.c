#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "dungeon/actor.h"

extern void update_actor_status_and_mp(void *);

/* Updates the actor state, consumes completed counts, and dispatches its action. */
void dispatch_actor_action_2(ActorRecord *actor, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *state) {
    s16 old_count;

    if (!(g_dungeon_status.flags & 0x2000)) {
        if (state->flags1C & 0x100) {
            begin_pushed_actor_move(actor, position, sprite, state);
            return;
        }
        if (actor->action_id.u != 0xE) {
            actor->action_id.u = 0xE;
        }
    }
    if (state->pending_turn_updates > 0) {
        old_count = (s8)(((u8 *)state)[0x6D] + 0);
        *(s32 *)(((u8 *)state) + 0x60) = 0;
        update_actor_status_and_mp(state);
        if ((old_count != 0) && (state->pending_turn_updates == 0)) {
            state->hp -= 1;
        }
        if (state->hp == 0) {
            g_dungeon_status.pending_display_owner = ((ObjectNodeHeader *)state - 1);
            begin_actor_display_action(actor, position, sprite, 0);
            return;
        }
    }
    if (state->hp_delta != 0) {
        begin_ready_actor_directional_action(actor, position, sprite, 0);
    }
}
