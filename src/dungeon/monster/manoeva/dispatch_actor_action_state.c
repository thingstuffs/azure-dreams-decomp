#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/monster/manoeva.h"

#include "dungeon/player/object/action_state.h"
#include "dungeon/actor/state.h"



/* Updates body state and flags according to the state handler result. */
s32 dispatch_actor_action_state(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, s32 unused_force_state) {
    ObjectPosition *saved_position;
    SpriteFrameState *saved_sprite;
    ActorRecord *saved_actor;
    s32 call_result;
    s32 state;

    saved_position = position;
    saved_sprite = sprite;
    saved_actor = body;
    call_result = relink_entity_and_clear_high_flag(saved_position, saved_sprite, saved_actor, 2, 4, &saved_actor->unk_9C);
    call_result <<= 16;
    state = call_result >> 16;
    call_result = 0;
    if (state >= 0) {
        switch (state) {
        case 0:
            saved_actor->action_id = 0xE;
            update_actor_status_and_mp(saved_actor);
            return 0;
        case 2:
            advance_actor_turn_path(saved_actor, saved_position, saved_sprite, saved_actor);
            return 0;
        case 1:
            saved_actor->movement_queue_state =
                    saved_actor->movement_queue_state & 0x7F;
            if ((has_pending_dungeon_activity(saved_actor) << 0x10) != 0) {
                saved_actor->action_flags =
                    (u16) (saved_actor->action_flags & 0x7FFF);
                return 0;
            }
        default:
            saved_actor->movement_queue_state =
                    saved_actor->movement_queue_state & 0x7F;
            if ((g_dungeon_status.flags & 8) == 0) {
                call_result = 1;
                break;
            }
            saved_actor->action_flags =
                (u16) (saved_actor->action_flags & 0x7FFF);
            return 0;
        }
    }
    return call_result;
}
