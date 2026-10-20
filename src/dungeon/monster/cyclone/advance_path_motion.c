#include "common.h"
#include "shared/game_work.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "records/Rec_D_80082E80.h"

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


void select_sprite_entry();         /* extern */
void cycle_map_cell_flags();             /* extern */
void update_map_cell_flags_with_item_limit();             /* extern */
s32 check_movement_clearance_and_height(); /* extern */
s16 get_rounded_facing_and_rounding_flag();             /* extern */
extern u8 D_80176460[8];

/* Advance the entity along its stored path and update its heading and movement timing. */
void advance_path_motion(void *motion, void *unused, void *entity, void *path_state) {
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
        if (((Rec_D_80082E80 *)entity)->unk_2C.as_pv != D_80176460) {
            (((Rec_D_80082E80 *)entity)->unk_2C.as_pv) = D_80176460;
            select_sprite_entry(entity, D_80176460[((g_game_work.view.viewAngle + ((S_801716D8_0 *)state)->unk_2A + 0x100)
                >> 9) & 7], 0);
        }
        old_x = ((Rec_D_80082E80 *)entity)->unk_24;
        old_y = ((Rec_D_80082E80 *)entity)->unk_25;
        old_cell_mask = 0x3000;
        if (((S_801716D8_0 *)state)->unk_1C & 0x2000) {
            old_cell_mask = 0x300;
        }
        update_map_cell_flags_with_item_limit(old_x, old_y, old_cell_mask);
        path_step = state + ((S_801716D8_0 *)state)->unk_8A;
        heading = get_rounded_facing_and_rounding_flag(old_x, old_y, ((S_801716D8_2 *)path_step)->unk_74, ((S_801716D8_2 *)path_step)->unk_7C,
            motion + 0x98);
        check_movement_clearance_and_height(heading, entity, state, 0x20);
        ((Rec_D_80082E80 *)entity)->unk_24 = (u8) ((S_801716D8_4 *)((state + ((S_801716D8_0 *)state)->unk_8A)))->unk_74;
        ((Rec_D_80082E80 *)entity)->unk_25 = (u8) ((S_801716D8_4 *)((state + ((S_801716D8_0 *)state)->unk_8A)))->unk_7C;
        ((S_801716D8_0 *)state)->unk_8A = (s16) ((u16) ((S_801716D8_0 *)state)->unk_8A + 1);
        move_flag = ((S_801716D8_0 *)state)->unk_1C & 0x2000;
        next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        next_y = ((Rec_D_80082E80 *)entity)->unk_25;
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
