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

typedef struct S_80171A18_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x2];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
} S_80171A18_3;   /* arg0 in advance_actor_along_queued_path */

   /* (u8 *)arg3 + ((S_80171A18_0 *)arg3)->unk_8A.s in advance_actor_along_queued_path */

extern void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);
extern s32 get_rounded_facing_and_rounding_flag(s16 start_x, s16 start_y, s16 end_x, s16 end_y, u16 *flags);

extern u8 hikewne_direction_frames[];
#include "dungeon/monster/hikewne.h"
#include "engine/graphics.h"

/* Advances the actor along its queued path and updates movement timing. */
void advance_actor_along_queued_path(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *actor, ActorRecord *move_state) {
    void *next_cell;
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
    if (((S_80171A18_0 *)move_state)->unk_71.u <= ((S_80171A18_0 *)move_state)->unk_8A.s) {
        return;
    }

    anim_table = *(u8 **)&actor->frameTable;
    if (anim_table != hikewne_direction_frames && anim_table != hikewne_alt_direction_frames) {
        (actor->frameTable) = hikewne_direction_frames;
        select_sprite_entry(
            actor,
            hikewne_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_80171A18_0 *)move_state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    next_cell = (u8 *)move_state + ((S_80171A18_0 *)move_state)->unk_8A.s;
    if (actor->tile_x == ((ActorStatusBytesView *)next_cell)->path_x
        && actor->tile_y == ((ActorStatusBytesView *)next_cell)->path_y) {
        move_offset = ((S_80171A18_3 *)motion)->unk_92;
        remaining_offset = ((S_80171A18_0 *)move_state)->unk_88;
        ((S_80171A18_3 *)motion)->unk_92 = move_offset + 0x20;
        ((S_80171A18_0 *)move_state)->unk_88 = remaining_offset - 0x20;
        ((S_80171A18_0 *)move_state)->unk_8A.u = ((S_80171A18_0 *)move_state)->unk_8A.u + 1;
    } else {
        old_x = actor->tile_x;
        old_y = actor->tile_y;
        occupancy_mask = 0x3000;
        if (((S_80171A18_0 *)move_state)->unk_1C & 0x2000) {
            occupancy_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, occupancy_mask);

        actor->tile_x = ((ActorStatusBytesView *)((u8 *)move_state
            + ((S_80171A18_0 *)move_state)->unk_8A.s))->path_x;
        actor->tile_y = ((ActorStatusBytesView *)((u8 *)move_state
            + ((S_80171A18_0 *)move_state)->unk_8A.s))->path_y;
        ((S_80171A18_0 *)move_state)->unk_8A.u++;

        new_x = actor->tile_x;
        new_y = actor->tile_y;
        occupancy_mask = 0x3000;
        if (((S_80171A18_0 *)move_state)->unk_1C & 0x2000) {
            occupancy_mask = 0x300;
        }
        cycle_map_cell_flags(new_x, new_y, occupancy_mask);

        ((S_80171A18_0 *)move_state)->unk_2A = get_rounded_facing_and_rounding_flag(
            old_x, old_y, actor->tile_x, actor->tile_y,
            &motion->action_state_flags);
    }
    ((S_80171A18_3 *)motion)->unk_9A = 0xF;
    ((S_80171A18_3 *)motion)->unk_8C = 0;
    (*(u32 *)((u8 *)move_state + 0x1C)) |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        ((S_80171A18_3 *)motion)->unk_96 = 0;
        return;
    }

    ((S_80171A18_3 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((S_80171A18_0 *)move_state)->unk_71.u;
        if (step_count > 0) {
            ((S_80171A18_3 *)motion)->unk_96 = 8 / step_count;
        }
    }
}
