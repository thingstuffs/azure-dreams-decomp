#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"
#include "engine/graphics.h"
#include "dungeon/level.h"

typedef struct S_801716D8_0 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0xA];
    s16 unk_2A;
    u8 pad_2C[0x45];
    s8 unk_71;
    u8 pad_72[0x18];
    s16 unk_8A;
} S_801716D8_0;   /* state in advance_path_motion */

typedef struct S_801716D8_2 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801716D8_2;

typedef struct S_801716D8_3 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    u8 pad_90[0x6];
    s16 unk_96;
    u8 pad_98[0x2];
    s8 unk_9A;
} S_801716D8_3;   /* arg0 in advance_path_motion */

typedef struct S_801716D8_4 {
    u8 pad_00[0x74];
    u8 unk_74;
    u8 pad_75[0x7];
    u8 unk_7C;
} S_801716D8_4;   /* (state + ((S_801716D8_0 *)state)->unk_8A) in advance_path_motion */

void update_map_cell_flags_with_item_limit(s32 x, s32 y, u16 flags);             /* extern */
s32 check_movement_clearance_and_height(); /* extern */
s16 get_rounded_facing_and_rounding_flag();             /* extern */
extern u8 cyclone_move_direction_frames[8];

/* Advance the entity along its stored path and update its heading and movement timing. */
void advance_path_motion(void *motion, void *unused, SpriteFrameState *entity, void *path_state) {
    s32 old_cell_mask;
    s32 new_cell_mask;
    s16 heading;
    s32 step_count;
    s32 old_x;
    s32 old_y;
    s32 next_x;
    s32 next_y;
    s32 move_flag;
    void *path_step;
    void *state = path_state;

    if ((((S_801716D8_0 *)state)->unk_71 > 0) && ((s32) (u8) ((S_801716D8_0 *)state)->unk_71
        > ((S_801716D8_0 *)state)->unk_8A)) {
        if (entity->frameTable != cyclone_move_direction_frames) {
            (entity->frameTable) = cyclone_move_direction_frames;
            select_sprite_entry(entity, cyclone_move_direction_frames[((g_game_work.view.camera_rotation.parts.viewAngle + ((S_801716D8_0 *)state)->unk_2A + 0x100)
                >> 9) & 7], 0);
        }
        old_x = entity->tile_x;
        old_y = entity->tile_y;
        old_cell_mask = 0x3000;
        if (((S_801716D8_0 *)state)->unk_1C & 0x2000) {
            old_cell_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, old_cell_mask);
        path_step = state + ((S_801716D8_0 *)state)->unk_8A;
        heading = get_rounded_facing_and_rounding_flag(old_x, old_y, ((S_801716D8_2 *)path_step)->unk_74, ((S_801716D8_2 *)path_step)->unk_7C,
            motion + 0x98);
        check_movement_clearance_and_height(heading, entity, state, 0x20);
        entity->tile_x = (u8) ((S_801716D8_4 *)((state + ((S_801716D8_0 *)state)->unk_8A)))->unk_74;
        entity->tile_y = (u8) ((S_801716D8_4 *)((state + ((S_801716D8_0 *)state)->unk_8A)))->unk_7C;
        ((S_801716D8_0 *)state)->unk_8A = (s16) ((u16) ((S_801716D8_0 *)state)->unk_8A + 1);
        move_flag = ((S_801716D8_0 *)state)->unk_1C & 0x2000;
        next_x = entity->tile_x;
        next_y = entity->tile_y;
        new_cell_mask = 0x3000;
        if (move_flag) {
            new_cell_mask = 0x300;
            cycle_map_cell_flags(next_x, next_y, new_cell_mask);
        } else {
            cycle_map_cell_flags(next_x, next_y, new_cell_mask);
        }
        ((S_801716D8_0 *)state)->unk_2A = heading;
        ((S_801716D8_3 *)motion)->unk_9A = 0xF;
        ((S_801716D8_3 *)motion)->unk_8C = 0;
        (((S_801716D8_0 *)state)->unk_1C) = (s32) (((S_801716D8_0 *)state)->unk_1C | 0x40000000);
        if (g_dungeon_status.flags & 0x80) {
            ((S_801716D8_3 *)motion)->unk_96 = 0;
            return;
        }
        ((S_801716D8_3 *)motion)->unk_96 = 8;
        step_count = (u8) ((S_801716D8_0 *)state)->unk_71;
        if ((s32) step_count > 0) {
            ((S_801716D8_3 *)motion)->unk_96 = (s16) (8 / (s32) step_count);
        }
    }
}

/* MECHANISM: Byte-table typing fixes the indexed lbu sequence. */
