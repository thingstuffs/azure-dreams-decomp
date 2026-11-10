#include "shared/dungeon_status.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "dungeon/actor/motion.h"
#include "shared/dir_step.h"
#include "m2c_compat.h"
#include "records/Rec_func_800A9E70_arg0.h"
#include "shared/entity.h"
#include "dungeon/level.h"




void update_map_cell_flags_with_item_limit();                 /* extern */

/* Move the position one step in the actor's direction and update movement state. */
void begin_pushed_actor_move(void *state_in, ObjectPosition *unused, void *position_in, void *actor_in) {
    Rec_func_800A9E70_arg0 *state = state_in;
    SpriteFrameState *position = position_in;
    ActorRecord *actor = actor_in;
    s32 next_x;
    s32 direction_index;
    s32 tile_mask;
    s32 move_mask;

    state->unk_9A.as_s8 = 0xA;
    state->unk_9B.as_s8 = 0;
    state->unk_8C = 0;
    move_mask = 0x3000;
    if (actor->flags1C & ACTOR_PLAYER_SIDE) {
        move_mask = 0x300;
    }
    tile_mask = move_mask & 0xFFFF;
    update_map_cell_flags_with_item_limit(position->tile_x, position->tile_y, tile_mask);
    direction_index = (actor->movement_facing >> 8) & 0xE;
    next_x = position->tile_x + (u8) *(direction_index + ((s8 *)dir_step_x));
    next_x = (u8) next_x;
    position->tile_x = next_x;
    position->tile_y = (u8) (position->tile_y + *(direction_index + ((s8 *)dir_step_y)));
    cycle_map_cell_flags(position->tile_x, position->tile_y, tile_mask);
    actor->flags1C = (s32) (actor->flags1C & ~ACTOR_PUSH_PENDING);
    state->unk_96.as_s16 = 0x21;
    state->unk_98 = (u16) (state->unk_98 | 8);
    g_dungeon_status.activity_counts.parts.pending_action_count = (u16)((u16) g_dungeon_status.activity_counts.parts.pending_action_count + 1);
}
