#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/dungeon_status.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"
#include "dungeon/actor/state.h"
#include "dungeon/actor.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"

#include "dungeon/item/find_active_rect_containing_point_api.h"
typedef struct {
    u8 pad[10];
    u16 counter;
} DungeonState;

/* Resets entity state, selects a new position, and increments the dungeon counter. */
void begin_actor_random_warp(ActorRecord *entity, ObjectPosition *unused, SpriteFrameState *position, ActorRecord *entity_state) {
    s32 tile_mask;
    s32 flags;
    s32 tile_x;
    s32 tile_y;
    void *tile_x_ptr;

    entity->action_id = 4;
    entity->action_phase = 0;
    entity->unk_8C.handler = NULL;
    entity->action_timer = 0x10;
    entity->action_state_flags = entity->action_state_flags | 8;
    flags = entity_state->flags1C | 0x10000;
    entity_state->flags1C = flags;
    tile_x = position->tile_x;
    tile_y = position->tile_y;
    tile_mask = 0x3000;
    if (flags & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(tile_x, tile_y, tile_mask);
    tile_x_ptr = &position->tile_x;
    while ((s16)select_dungeon_spawn_tile(tile_x_ptr, &position->tile_y) < 0) {
        tile_x_ptr = &position->tile_x;
    }
    position->room_index = find_active_rect_containing_point(position->tile_x,
        position->tile_y);
    refresh_actor_proximity_state(entity_state);
    g_dungeon_status.activity_counts.parts.pending_action_count = ((u16)g_dungeon_status.activity_counts.parts.pending_action_count) + 1;
}
