#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 find_active_rect_containing_point(s32 point_x, s32 point_y);
extern s32 select_dungeon_spawn_tile(u8 *x_out, u8 *y_out);
extern s32 refresh_actor_proximity_state();
typedef struct {
    u8 pad[10];
    u16 counter;
} DungeonState;

/* Resets entity state, selects a new position, and increments the dungeon counter. */
void begin_actor_random_warp(Rec_func_800A9E70_arg0 *entity, void *unused, void *position, EntityRec *entity_state) {
    s32 tile_mask;
    s32 flags;
    s32 tile_x;
    s32 tile_y;
    void *tile_x_ptr;

    entity->unk_9A.as_s8 = 4;
    entity->unk_9B.as_s8 = 0;
    entity->unk_8C = 0;
    entity->unk_96.as_s16 = 0x10;
    entity->unk_98 = entity->unk_98 | 8;
    flags = entity_state->flags1C | 0x10000;
    entity_state->flags1C = flags;
    tile_x = ((SpriteFrameState *)position)->tile_x;
    tile_y = ((SpriteFrameState *)position)->tile_y;
    tile_mask = 0x3000;
    if (flags & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
    tile_x_ptr = (u8 *)position + 0x24;
    while ((s16)select_dungeon_spawn_tile(tile_x_ptr, (u8 *)position + 0x25) < 0) {
        tile_x_ptr = (u8 *)position + 0x24;
    }
    ((SpriteFrameState *)position)->room_index = find_active_rect_containing_point(((SpriteFrameState *)position)->tile_x,
        ((SpriteFrameState *)position)->tile_y);
    refresh_actor_proximity_state(entity_state);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
}
