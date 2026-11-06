#include "shared/entity.h"
#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/level.h"
#include "dungeon/monster/cyclone.h"
#include "dungeon/monster/cyclone_frames.h"


void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */
s32 check_movement_clearance_and_height(); /* extern */
s16 get_rounded_facing_and_rounding_flag(); /* Unprototyped: retail call extends the result to this declared width; no shared prototype keeps it */             /* extern */

/* Advance the entity along its stored path and update its heading and movement timing. */
void advance_path_motion(ActorRecord *body, ObjectPosition *position, SpriteFrameState *sprite, ActorRecord *actor) {
    s32 old_cell_mask;
    s32 new_cell_mask;
    s16 heading;
    s32 step_count;
    s32 old_x;
    s32 old_y;
    s32 next_x;
    s32 next_y;
    s32 move_flag;
    ActorRecord *state = actor;

    if ((((s8)state->movement_queue_state) > 0) && ((s32) (u8) ((s8)state->movement_queue_state)
        > state->unk_8A)) {
        if (sprite->frameTable != cyclone_move_direction_frames) {
            (sprite->frameTable) = cyclone_move_direction_frames;
            select_sprite_entry(sprite, cyclone_move_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + state->facing + 0x100)
                >> 9) & 7], 0);
        }
        old_x = sprite->tile_x;
        old_y = sprite->tile_y;
        old_cell_mask = 0x3000;
        if (state->flags1C & 0x2000) {
            old_cell_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, old_cell_mask);
        heading = get_rounded_facing_and_rounding_flag(old_x, old_y, state->path_x[state->unk_8A], state->path_y[state->unk_8A],
            ((void *)body) + 0x98);
        check_movement_clearance_and_height(heading, sprite, state, 0x20);
        sprite->tile_x = (u8) state->path_x[state->unk_8A];
        sprite->tile_y = (u8) state->path_y[state->unk_8A];
        state->unk_8A = (s16) ((u16) state->unk_8A + 1);
        move_flag = state->flags1C & 0x2000;
        next_x = sprite->tile_x;
        next_y = sprite->tile_y;
        new_cell_mask = 0x3000;
        if (move_flag) {
            new_cell_mask = 0x300;
            cycle_map_cell_flags(next_x, next_y, new_cell_mask);
        } else {
            cycle_map_cell_flags(next_x, next_y, new_cell_mask);
        }
        state->facing = heading;
        body->action_id.s = 0xF;
        body->unk_8C.word = 0;
        (state->flags1C) = (s32) (state->flags1C | 0x40000000);
        if (g_dungeon_status.flags & 0x80) {
            body->action_timer.s = 0;
            return;
        }
        body->action_timer.s = 8;
        step_count = (u8) ((s8)state->movement_queue_state);
        if ((s32) step_count > 0) {
            body->action_timer.s = (s16) (8 / (s32) step_count);
        }
    }
}

/* MECHANISM: Byte-table typing fixes the indexed lbu sequence. */
