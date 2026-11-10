#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"
#include "dungeon/level.h"
#include "dungeon/monster/hikewne_frames.h"
#include "dungeon/level/update_map_cell_flags_with_item_limit_api.h"


   /* cell in advance_actor_along_queued_path */


   /* (u8 *)arg3 + ((S_80171A18_0 *)arg3)->unk_8A.s in advance_actor_along_queued_path */

#include "dungeon/monster/hikewne.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

/* Advances the actor along its queued path and updates movement timing. */
void advance_actor_along_queued_path(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *actor, ActorRecord *move_state) {
    u8 *anim_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;
    s32 move_offset;
    s32 remaining_offset;

    if (((s8)move_state->movement_queue_state) <= 0) {
        return;
    }
    if (move_state->movement_queue_state <= move_state->unk_8A) {
        return;
    }

    anim_table = *(u8 **)&actor->frameTable;
    if (anim_table != hikewne_direction_frames && anim_table != hikewne_alt_direction_frames) {
        (actor->frameTable) = hikewne_direction_frames;
        select_sprite_entry(
            actor,
            hikewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + move_state->facing + 0x100) >> 9) & 7],
            0);
    }

    if (actor->tile_x == move_state->path_x[move_state->unk_8A]
        && actor->tile_y == move_state->path_y[move_state->unk_8A]) {
        move_offset = (u16)motion->unk_90.parts.high;
        remaining_offset = ((u16)move_state->ground_height);
        motion->unk_90.parts.high = move_offset + 0x20;
        move_state->ground_height = remaining_offset - 0x20;
        move_state->unk_8A = move_state->unk_8A + 1;
    } else {
        old_x = actor->tile_x;
        old_y = actor->tile_y;
        occupancy_mask = 0x3000;
        if (move_state->flags1C & 0x2000) {
            occupancy_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, occupancy_mask);

        actor->tile_x = move_state->path_x[move_state->unk_8A];
        actor->tile_y = move_state->path_y[move_state->unk_8A];
        move_state->unk_8A++;

        new_x = actor->tile_x;
        new_y = actor->tile_y;
        occupancy_mask = 0x3000;
        if (move_state->flags1C & 0x2000) {
            occupancy_mask = 0x300;
        }
        cycle_map_cell_flags(new_x, new_y, occupancy_mask);

        move_state->facing = get_rounded_facing_and_rounding_flag(
            old_x, old_y, actor->tile_x, actor->tile_y,
            &motion->action_state_flags);
    }
    motion->action_id = 0xF;
    motion->unk_8C.word = 0;
    move_state->flags1C = (u32)((u32)move_state->flags1C | (0x40000000));

    if (g_dungeon_status.flags & 0x80) {
        motion->action_timer = 0;
        return;
    }

    motion->action_timer = 8;
    {
        s32 step_count = move_state->movement_queue_state;
        if (step_count > 0) {
            motion->action_timer = 8 / step_count;
        }
    }
}
