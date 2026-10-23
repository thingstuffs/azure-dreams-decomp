#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/tile_object.h"
extern s32 ghosh_boss_node[3];
typedef struct {
    u8 data[24];
} Config24;
extern u8 D_8016A87C[];
extern void update_map_cell_flags_with_item_limit(u8, u8, s32);
extern void set_record_integer_tile_center(s32, u8, u8);
extern void cycle_map_cell_flags(s16 x, s16 y, u16 flags);

typedef struct S_80171168_0 {
    u8 pad_00[0x8];
    s32 unk_08;
    void * unk_0C;
} S_80171168_0;   /* *D_80174CD8 in move_boss_effect_to_offset */

typedef struct S_80171168_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
} S_80171168_2;

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
    s32 entity_id;
    SpriteFrameState *entity;
    S_80171168_2 *entity_state;

    offset_table = (const Config24 *)D_8016A87C;
    offsets = *offset_table;
    offset_pair = (s16 *)offsets.data;
    old_cell_mask = 0x3000;
    entity_state = *ghosh_boss_node + 0x20;
    entity = ((S_80171168_0 *)(*ghosh_boss_node))->unk_0C;
    entity_id = ((S_80171168_0 *)(*ghosh_boss_node))->unk_08;
    entity->flags = (u16) (entity->flags & 0xFF7F);
    old_x = entity->tile_x;
    old_y = entity->tile_y;
    if (entity_state->unk_1C & 0x2000) {
        old_cell_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, old_cell_mask);
    origin = &reference_tile_object;
    offset_pair = &offset_pair[offset_index];
    offset_bytes = (u8 *)offset_pair;
    entity->tile_x = (u8) (origin->tile_position.parts.tile_x + offset_bytes[0]);
    entity->tile_y = (u8) (origin->tile_position.parts.tile_y + offset_bytes[1]);
    set_record_integer_tile_center(entity_id, entity->tile_x, entity->tile_y);
    new_x = entity->tile_x;
    new_y = entity->tile_y;
    new_cell_mask = 0x3000;
    if (entity_state->unk_1C & 0x2000) {
        new_cell_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, new_cell_mask);
}
