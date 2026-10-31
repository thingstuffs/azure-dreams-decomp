#include "common.h"
#include "dungeon/monster/ghosh.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"
typedef struct {
    u8 data[24];
} Config24;
extern u8 D_8016A87C[];
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);


/* Move the entity to a selected offset from the origin and update its cell flags. */
void move_boss_effect_to_offset(s32 offset_index) {
    const Config24 *offset_table;
    Config24 offsets;
    s32 old_cell_mask;
    s32 new_cell_mask;
    u8 *offset_bytes;
    TileObject *origin;
    u8 old_x;
    u8 old_y;
    u8 new_x;
    u8 new_y;
    register s16 *offset_pair;
    ObjectPosition *position;
    SpriteFrameState *entity;
    ActorRecord *entity_state;


    offset_table = (const Config24 *)D_8016A87C;
    offsets = *offset_table;
    offset_pair = (s16 *)offsets.data;
    old_cell_mask = 0x3000;
    entity_state = (void *)(ghosh_boss_node + 1);
    entity = ghosh_boss_node->sprite;
    position = ghosh_boss_node->position;
    entity->flags = (u16) (entity->flags & 0xFF7F);
    old_x = entity->tile_x;
    old_y = entity->tile_y;
    if (entity_state->flags1C & 0x2000) {
        old_cell_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, old_cell_mask);
    origin = &reference_tile_object;
    offset_pair = &offset_pair[offset_index];
    offset_bytes = (u8 *)offset_pair;
    entity->tile_x = (u8) (origin->tile_position.parts.tile_x + offset_bytes[0]);
    entity->tile_y = (u8) (origin->tile_position.parts.tile_y + offset_bytes[1]);
    set_record_integer_tile_center(position, entity->tile_x, entity->tile_y);
    new_x = entity->tile_x;
    new_y = entity->tile_y;
    new_cell_mask = 0x3000;
    if (entity_state->flags1C & 0x2000) {
        new_cell_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, new_cell_mask);
}
