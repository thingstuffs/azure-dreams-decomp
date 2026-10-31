#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"
#include "shared/entity.h"

s32 check_diagonal_side_height(s32 direction, s16 tile_x, s16 tile_y, s16 height);
void *find_eligible_actor_at_tile_and_height(void *, u16, u16, s16);
s32 check_entity_interaction_compatibility(void *, void *);

/* Returns the first valid candidate found while checking eight neighboring positions. */
void *find_monster_neighbor_candidate(void *entity, u16 x, u16 y) {
    u16 *x_offsets;
    u16 *y_offsets;
    void *entity_data;
    void *entity_ptr;
    u16 origin_x;
    u16 origin_y;
    void *candidate;
    s32 attempt;
    s32 direction;

    entity_ptr = entity;
    origin_x = x;
    origin_y = y;
    x_offsets = dir_step_x;
    y_offsets = dir_step_y;
    entity_data = *(void **)((s8 *)entity_ptr - 0x14);
    direction = g_dungeon_status.turn_counter & 7;
    for (attempt = 0; attempt < 8; attempt++, direction = (direction + 1) & 7) {
        candidate = find_eligible_actor_at_tile_and_height(entity_ptr, (origin_x + x_offsets[direction]) & 0xFFFF, (origin_y
            + y_offsets[direction]) & 0xFFFF, *(s16 *)((s8 *)entity_ptr + 0x88));
        if (candidate != 0 && ((check_entity_interaction_compatibility(entity_ptr, candidate) << 16) != 0)) {
            if (((check_diagonal_side_height(direction, *(u8 *)((s8 *)entity_data + 0x24), *(u8 *)((s8 *)entity_data + 0x25),
                (s16)((u16)*(s16 *)((s8 *)entity_ptr + 0x88) - 0x20)) << 16) == 0)) {
                continue;
            }
            entity_ptr = entity;
            return candidate;
        }
    }
    return 0;
}
