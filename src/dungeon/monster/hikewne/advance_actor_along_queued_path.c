#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "shared/actor_status.h"
#include "dungeon/level.h"

typedef struct S_80171A18_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    union { s8 s; u8 u; } unk_71;   /* accessed as both */
    u8 pad_72[0x16];
    u16 unk_88;
    union { s16 s; u16 u; } unk_8A;   /* accessed as both */
} S_80171A18_0;   /* arg3 in advance_actor_along_queued_path */

   /* cell in advance_actor_along_queued_path */


   /* (u8 *)arg3 + ((S_80171A18_0 *)arg3)->unk_8A.s in advance_actor_along_queued_path */

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);

extern u8 hikewne_direction_frames[];
#include "dungeon/monster/hikewne.h"
#include "engine/graphics.h"
#include "dungeon/item.h"

/* Advances the actor along its queued path and updates movement timing. */
void advance_actor_along_queued_path(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *actor, ActorRecord *move_state) {
    ActorStatusBytesView *next_cell;
    u8 *anim_table;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s32 occupancy_mask;
    s32 move_offset;
    s32 remaining_offset;

    if (((S_80171A18_0 *)move_state)->unk_71.s <= 0) {
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

    next_cell = (ActorStatusBytesView *)((u8 *)move_state + move_state->unk_8A);
    if (actor->tile_x == next_cell->path_x
        && actor->tile_y == next_cell->path_y) {
        move_offset = motion->unk_90.parts.high.u;
        remaining_offset = ((S_80171A18_0 *)move_state)->unk_88;
        motion->unk_90.parts.high.u = move_offset + 0x20;
        move_state->ground_height = remaining_offset - 0x20;
        move_state->unk_8A = ((S_80171A18_0 *)move_state)->unk_8A.u + 1;
    } else {
        old_x = actor->tile_x;
        old_y = actor->tile_y;
        occupancy_mask = 0x3000;
        if (move_state->flags1C & 0x2000) {
            occupancy_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, occupancy_mask);

        actor->tile_x = ((ActorStatusBytesView *)((u8 *)move_state
            + move_state->unk_8A))->path_x;
        actor->tile_y = ((ActorStatusBytesView *)((u8 *)move_state
            + move_state->unk_8A))->path_y;
        ((S_80171A18_0 *)move_state)->unk_8A.u++;

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
    motion->action_id.u = 0xF;
    motion->unk_8C.word = 0;
    (*(u32 *)((u8 *)move_state + 0x1C)) |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        motion->action_timer.u = 0;
        return;
    }

    motion->action_timer.u = 8;
    {
        s32 step_count = move_state->movement_queue_state;
        if (step_count > 0) {
            motion->action_timer.u = 8 / step_count;
        }
    }
}
