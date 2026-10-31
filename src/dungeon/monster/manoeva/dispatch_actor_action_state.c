#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "dungeon/monster/manoeva.h"

#include "dungeon/player/object/action_state.h"
#include "dungeon/actor/state.h"

void update_actor_status_and_mp(ActorRecord *entity);                      /* extern */


/* Updates object state and flags according to the state handler result. */
s32 dispatch_actor_action_state(void *object, s32 state_input_a, s32 state_input_b) {
    s32 saved_input_a;
    s32 saved_input_b;
    void *saved_object;
    s32 call_result;
    s32 state;

    saved_input_a = state_input_a;
    saved_input_b = state_input_b;
    saved_object = object;
    call_result = relink_entity_and_clear_high_flag(saved_input_a, saved_input_b, saved_object, 2, 4, saved_object + 0x9C);
    call_result <<= 16;
    state = call_result >> 16;
    call_result = 0;
    if (state >= 0) {
        switch (state) {
        case 0:
            ((ActorRecord *)saved_object)->action_id.s = 0xE;
            update_actor_status_and_mp(saved_object);
            return 0;
        case 2:
            advance_actor_turn_path(saved_object, saved_input_a, saved_input_b, saved_object);
            return 0;
        case 1:
            ((ActorRecord *)saved_object)->movement_queue_state =
                    (u8) (((ActorRecord *)saved_object)->movement_queue_state & 0x7F);
            if ((has_pending_dungeon_activity(saved_object) << 0x10) != 0) {
                ((ActorRecord *)saved_object)->action_flags =
                    (u16) (((ActorRecord *)saved_object)->action_flags & 0x7FFF);
                return 0;
            }
        default:
            ((ActorRecord *)saved_object)->movement_queue_state =
                    (u8) (((ActorRecord *)saved_object)->movement_queue_state & 0x7F);
            if ((g_dungeon_status.flags & 8) == 0) {
                call_result = 1;
                break;
            }
            ((ActorRecord *)saved_object)->action_flags =
                (u16) (((ActorRecord *)saved_object)->action_flags & 0x7FFF);
            return 0;
        }
    }
    return call_result;
}
