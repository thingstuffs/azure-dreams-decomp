#include "common.h"
#include "shared/dungeon_status.h"

extern void update_actor_status_and_food(void *);
extern s16 relink_entity_and_clear_high_flag(void *context, void *position, void *entity, s16 near_range, s16 far_range, s32 state_out_addr);
extern void choose_heading_and_advance_actor(void *, s32, s32, void *);

/* Checks an object action, dispatches its update, and clears flags as needed. */
s32 check_object_action_and_clear_flags(void *object, s32 query_x, s32 query_y, s32 action_override) {
    void *saved_object = object;
    s32 next_state;
    s32 clear_result;
    s16 action_result;
    s32 override_bits;

    action_result = relink_entity_and_clear_high_flag(query_x, query_y, saved_object, 3, 6,
                           (u8 *)saved_object + 0x9C);
    if (action_result < 0) {
        return 0;
    }
    override_bits = action_override << 16;
    if (override_bits == 0) {
        next_state = 0xE;
        if (action_result != 0) {
            if (action_result == 2) {
                goto call_block;
            }
            goto tail_block;
        }
        *((s8 *)saved_object + 0x9A) = next_state;
        update_actor_status_and_food(saved_object);
        return 0;
    } else {
        choose_heading_and_advance_actor(saved_object, query_x, query_y, saved_object);
        return 0;
    }
call_block:
    choose_heading_and_advance_actor(saved_object, query_x, query_y, saved_object);
    return 0;

tail_block:
    *((u8 *)saved_object + 0x71) &= 0x7F;
    if (g_dungeon_status.flags & 8) {
        clear_result = 0;
    } else {
        return 1;
    }
    *(u16 *)((u8 *)saved_object + 0x46) &= 0x7FFF;
    return clear_result;

    return 0;
}

