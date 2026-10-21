/* Movement overlap wait (G00334). */
/* Original-file evidence: inferred (adjacency/recipe/locality), inferred-strong - CL:dungeon/func_800A4DA8. */
#include "dungeon/actor/movement_overlap_wait_g00334.h"

/* Try to move the entity, update positional sounds, and select the next action state. */
s32 try_move_actor_to_valid_position(void *action, void *context, void *position, void *entity) {
    s32 move_result;
    s16 old_x;
    s16 old_y;
    u32 entity_flags;
    u32 post_flags;
    u8 player_state;

    if (((has_pending_dungeon_activity(entity) << 16) == 0) &&
        ((*(u16 *)((u8 *)action - 2) & 0x8000) == 0) &&
        ((*(u32 *)((u8 *)entity + 0x1C) & 0x80000) == 0) &&
        ((*(u32 *)((u8 *)entity + 0x14) & 0x100000) == 0) &&
        ((player_state = *(u8 *)((u8 *)primary_actor_record + 0x9A)) != 0x18) &&
        (player_state != 0x11) &&
        ((check_entity_eligibility(entity) << 16) != 0)) {
        old_x = *(u8 *)((u8 *)position + 0x24);
        old_y = *(u8 *)((u8 *)position + 0x25);
        move_result = (s16)update_object_coordinates_if_valid(position, entity);
        if (move_result != 0) {
            entity_flags = *(u32 *)((u8 *)entity + 0x1C) | 0x40000000;
            *(u32 *)((u8 *)entity + 0x1C) = entity_flags;
            update_map_cell_flags_with_item_limit(old_x, old_y, (entity_flags & 0x2000) ? 0x300 : 0x3000);
            post_flags = *(u32 *)((u8 *)entity + 0x1C);
            cycle_map_cell_flags(*(u8 *)((u8 *)position + 0x24),
                          *(u8 *)((u8 *)position + 0x25),
                          (post_flags & 0x2000) ? 0x300 : 0x3000);

            if (move_result == 1) {
                begin_actor_overlap_wait(action, context, position, entity);
                return 1;
            } else {
                begin_actor_random_warp(action, context, position, entity);
                return 1;
            }
        }
    }
    return 0;
}

/* Sets the entity state to 3, clears its progress, and increments the global counter. */
void begin_actor_overlap_wait(void *entity, void *unused_1, void *unused_2, void *unused_3) {
    *(s8 *)((s8 *)entity + 0x9A) = 3;
    *(s8 *)((s8 *)entity + 0x9B) = 0;
    *(s32 *)((s8 *)entity + 0x8C) = 0;
    *(s16 *)((s8 *)entity + 0x96) = 4;
    g_dungeon_status.activity_counts.parts.pending_action_count += 1;
}
