#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"

extern void update_actor_status_and_mp(ActorRecord *entity);
extern s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr); /* Unprototyped: uses the value as a pointer where the definition has an integer (or the reverse) */
extern void choose_heading_and_advance_actor(ActorRecord *, s32, s32, void *);

/* Checks an object action, dispatches its update, and clears flags as needed. */
s32 check_object_action_and_clear_flags(ActorRecord *object, s32 query_x, s32 query_y, s32 action_override) {
    void *saved_object = object;
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
            *((s8 *)saved_object + 0x9A) = 0xE;
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
    *((u8 *)saved_object + 0x71) &= 0x7F;
    if (g_dungeon_status.flags & 8) {
        *(u16 *)((u8 *)saved_object + 0x46) &= 0x7FFF;
        return 0;
    }
    return 1;
}

