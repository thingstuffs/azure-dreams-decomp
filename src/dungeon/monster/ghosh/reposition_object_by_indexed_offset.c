#include "common.h"
#include "shared/tile_object.h"
#include "dungeon/level.h"
#include "dungeon/player/object.h"

typedef struct {
    u32 words[3];
} __attribute__((packed)) Copy12;

typedef struct {
    u8 pad[0x1C];
    s32 flags;
} Status;

void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern Copy12 D_8016A858[];
extern u8 *ghosh_actor_node;

/* Reposition the current object using an indexed offset from the reference coordinates. */
void reposition_object_by_indexed_offset(s32 offset_index) {
    Copy12 offsets = D_8016A858[0];
    s32 old_tile_mask;
    u8 *offset_bytes;
    s16 *xy_offset;
    ObjectPosition *position;
    u8 *object;
    TileObject *origin;
    u8 *state;
    Status *status;
    s32 offset_pos;
    s32 status_flags;
    s32 x;
    s32 y;
    s32 updated_y;

    state = ghosh_actor_node;
    object = *(u8 **)(state + 0xC);
    old_tile_mask = 0x3000;
    status = (Status *)state + 1;
    position = *(ObjectPosition **)(state + 8);
    *(u16 *)(object + 0x14) &= 0xFF7F;
    x = object[0x24];
    y = object[0x25];
    if (status->flags & 0x2000) {
        old_tile_mask = 0x300;
    }
    offset_bytes = (u8 *)&offsets;
    update_map_cell_flags_with_item_limit(x, y, old_tile_mask);
    origin = &reference_tile_object;
    offset_pos = offset_index << 1;
    xy_offset = (s16 *)(offset_bytes + offset_pos);
    object[0x24] = origin->tile_position.parts.tile_x + ((u8 *)xy_offset)[0];
    object[0x25] = origin->tile_position.parts.tile_y + ((u8 *)xy_offset)[1];
    set_record_integer_tile_center(position, object[0x24], object[0x25]);
    status_flags = *(s32 *)&status->flags;
    x = object[0x24];
    updated_y = object[0x25];
    if (status_flags & 0x2000) {
        cycle_map_cell_flags(x, updated_y, 0x300);
    } else {
        cycle_map_cell_flags(x, updated_y, 0x3000);
    }
}
