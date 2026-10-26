#include "shared/actor_status_ids.h"
#include "common.h"
#include "shared/dungeon_moving_views.h"
#include "dungeon/actor.h"
#include "dungeon/level.h"

typedef struct S_800A9AFC_2 {
    u8 pad_00[0x73];
    u8 unk_73;
    u8 pad_74[0x7];
    u8 unk_7B;
} S_800A9AFC_2;   /* (arg1 + ((S_800A9AFC_0 *)arg1)->unk_71) in rotate_actor_movement_queue */


s32 get_entity_effect_value();             /* extern */
extern s32 memmove(void *, void *, s32);     /* extern */
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */

typedef struct S_800A9AFC_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    u16 unk_2A;
    u8 pad_2C[0x3E];
    u16 unk_6A;
    u8 pad_6C[0x5];
    u8 unk_71;
    u8 pad_72[0x2];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
    u8 pad_7D[0xB];
    u16 unk_88;
    u16 unk_8A;
} S_800A9AFC_0;   /* arg1 in rotate_actor_movement_queue */

   /* arg0 in rotate_actor_movement_queue */

/* Rotates queued coordinates into the current position and updates tile flags. */
void rotate_actor_movement_queue(MovingTile *position, void *state) {
    s32 clear_mask;
    s32 set_mask;
    s32 status_result;
    u8 next_x;
    u8 next_y;

    if (((S_800A9AFC_0 *)state)->unk_71 & 0x7F) {
        status_result = (s16) get_entity_effect_value(state, STATUS_NO_TILE_OCCUPANCY);
        if (status_result == 0) {
            s32 flags;
            u8 tile_x;
            u8 tile_y;

            flags = ((S_800A9AFC_0 *)state)->unk_1C;
            tile_x = position->tile_x;
            tile_y = position->tile_y;
            clear_mask = 0x3000;
            if (flags & 0x2000) {
                clear_mask = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, clear_mask);
        }
        next_x = ((S_800A9AFC_0 *)state)->unk_74;
        next_y = ((S_800A9AFC_0 *)state)->unk_7C;
        memmove(state + 0x74, state + 0x75, 0xF);
        ((S_800A9AFC_2 *)((state + ((S_800A9AFC_0 *)state)->unk_71)))->unk_73 = (u8) position->tile_x;
        ((S_800A9AFC_2 *)((state + ((S_800A9AFC_0 *)state)->unk_71)))->unk_7B = (u8) position->tile_y;
        position->tile_x = next_x;
        position->tile_y = next_y;
        ((S_800A9AFC_0 *)state)->unk_88 = (u16) ((S_800A9AFC_0 *)state)->unk_8A;
        ((S_800A9AFC_0 *)state)->unk_2A = (u16) ((S_800A9AFC_0 *)state)->unk_6A;
        if (status_result == 0) {
            s32 flags;
            u8 tile_x;
            u8 tile_y;

            flags = ((S_800A9AFC_0 *)state)->unk_1C;
            tile_x = position->tile_x;
            tile_y = position->tile_y;
            set_mask = 0x3000;
            if (flags & 0x2000) {
                set_mask = 0x300;
            }
            cycle_map_cell_flags(tile_x, tile_y, set_mask);
        }
        ((S_800A9AFC_0 *)state)->unk_8A = 0U;
    }
}
