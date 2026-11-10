#include "dungeon/actor/state.h"
#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void choose_heading_and_advance_actor(ActorRecord *, s32, void *, ActorRecord *);

/* Checks an object action, dispatches its update, and clears flags as needed. */
s32 check_object_action_and_clear_flags(ActorRecord *object, s32 query_x, void *query_y, s32 action_override) {
    ActorRecord *saved_object = object;
    s16 action_result;
    s32 override_bits;

    action_result = relink_entity_and_clear_high_flag(query_x, query_y, saved_object, 3, 6,
                           (u8 *)saved_object + 0x9C);
    if (action_result < 0) {
        return 0;
    }
    override_bits = action_override << 16;
    if (override_bits == 0) {
        switch (action_result) {
        case 0:
            saved_object->action_id = 0xE;
            update_actor_status_and_mp(saved_object);
            return 0;
        case 2:
            choose_heading_and_advance_actor(saved_object, query_x, query_y, saved_object);
            return 0;
        }
    } else {
        choose_heading_and_advance_actor(saved_object, query_x, query_y, saved_object);
        return 0;
    }
    saved_object->movement_queue_state &= 0x7F;
    if (g_dungeon_status.flags & 8) {
        saved_object->action_flags &= 0x7FFF;
        return 0;
    }
    return 1;
}

