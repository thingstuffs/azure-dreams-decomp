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


s32 get_entity_effect_value(ActorRecord *entry, s32 effect_id);             /* extern */
extern s32 memmove(void *, void *, s32);     /* extern */
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */

   /* arg0 in rotate_actor_movement_queue */

/* Rotates queued coordinates into the current position and updates tile flags. */
void rotate_actor_movement_queue(MovingTile *position, ActorRecord *state) {
    s32 clear_mask;
    s32 set_mask;
    s32 status_result;
    u8 next_x;
    u8 next_y;

    if (state->movement_queue_state & 0x7F) {
        status_result = (s16) get_entity_effect_value(state, STATUS_NO_TILE_OCCUPANCY);
        if (status_result == 0) {
            s32 flags;
            u8 tile_x;
            u8 tile_y;

            flags = state->flags1C;
            tile_x = position->tile_x;
            tile_y = position->tile_y;
            clear_mask = 0x3000;
            if (flags & 0x2000) {
                clear_mask = 0x300;
            }
            update_map_cell_flags_with_item_limit(tile_x, tile_y, clear_mask);
        }
        next_x = state->path_x[0];
        next_y = state->path_y[0];
        memmove(((void *)state) + 0x74, ((void *)state) + 0x75, 0xF);
        ((S_800A9AFC_2 *)((((void *)state) + state->movement_queue_state)))->unk_73 = (u8) position->tile_x;
        ((S_800A9AFC_2 *)((((void *)state) + state->movement_queue_state)))->unk_7B = (u8) position->tile_y;
        position->tile_x = next_x;
        position->tile_y = next_y;
        state->ground_height = (u16) state->unk_8A;
        state->facing = (u16) state->movement_facing;
        if (status_result == 0) {
            s32 flags;
            u8 tile_x;
            u8 tile_y;

            flags = state->flags1C;
            tile_x = position->tile_x;
            tile_y = position->tile_y;
            set_mask = 0x3000;
            if (flags & 0x2000) {
                set_mask = 0x300;
            }
            cycle_map_cell_flags(tile_x, tile_y, set_mask);
        }
        state->unk_8A = 0U;
    }
}
