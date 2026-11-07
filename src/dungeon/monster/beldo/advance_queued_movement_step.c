#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "dungeon/item.h"
#include "dungeon/monster/beldo.h"
#include "dungeon/data.h"

extern s32 select_sprite_entry();
extern void cycle_map_cell_flags();
void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);

/* Advances a queued movement step and updates position, direction, and timing. */
void advance_queued_movement_step(ActorRecord *motion, ObjectPosition *unused, SpriteFrameState *sprite, ActorRecord *path) {
    s32 tile_mask;
    s32 step_count;
    s32 old_x;
    s32 old_y;

    if (((s8)path->movement_queue_state) <= 0) {
        return;
    }
    if (path->movement_queue_state <= path->unk_8A) {
        return;
    }

    if (*(u8 **)&sprite->frameTable != beldo_frame_set_1) {
        (sprite->frameTable) = beldo_frame_set_1;
        select_sprite_entry(
            sprite,
            beldo_frame_set_1[((g_game_work.view.camera_rotation.parts.viewAngle + path->facing + 0x100) >> 9) & 7],
            0);
        sprite->frame_ticks = 1;
        motion->unk_A0.parts.high = 0;
        motion->unk_9E = 0;
    }

    if (sprite->tile_x == path->path_x[path->unk_8A] &&
        sprite->tile_y == path->path_y[path->unk_8A]) {
        u16 remaining_offset = ((u16)path->ground_height);
        motion->unk_90.parts.high.u += 0x20;
        path->ground_height = remaining_offset - 0x20;
        path->unk_8A++;
    } else {
        old_x = sprite->tile_x;
        old_y = sprite->tile_y;
        tile_mask = 0x3000;
        if (path->flags1C & 0x2000) {
            tile_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

        sprite->tile_x =
            path->path_x[path->unk_8A];
        sprite->tile_y =
            path->path_y[path->unk_8A];
        path->unk_8A++;

        cycle_map_cell_flags(sprite->tile_x, sprite->tile_y,
                      (path->flags1C & 0x2000) ? 0x300 : 0x3000);

        path->facing =
            get_rounded_facing_and_rounding_flag(old_x, old_y, sprite->tile_x,
                          sprite->tile_y, (u8 *)motion + 0x98);
    }
    motion->action_id = 0xF;
    motion->unk_8C.word = 0;
    path->flags1C |= 0x40000000;

    if (g_dungeon_status.flags & 0x80) {
        motion->action_timer = 0;
        return;
    }

    motion->action_timer = 8;
    step_count = path->movement_queue_state;
    if (step_count > 0) {
        motion->action_timer = 8 / step_count;
    }
}
