#include "modules/dungeon_ovl_cd7000.h"

void func_8014D590(void *motion, s32 update_param, void *entity, void *state) {
    s32 tile_mask;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s16 heading;
    s16 move_result;
    s16 stored_result;
    s32 result_code;

    if (((CL_CD7000_80171590_S_80171590_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (!((s32)((CL_CD7000_80171590_S_80171590_0 *)state)->unk_71.u > ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_8A.s)) {
        return;
    }

    if (((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_2C != D_801512AC) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_801512AC;
        func_80047784(
            entity,
            D_801512AC[((g_game_work.view.viewAngle + ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_x = ((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_24;
    old_y = ((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((CL_CD7000_80171590_S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    update_map_cell_flags_with_item_limit(old_x, old_y, tile_mask);

    heading = get_rounded_facing_and_rounding_flag(
        old_x,
        old_y,
        ((CL_CD7000_80171590_S_80171590_3 *)((u8 *)state + ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_74,
        ((CL_CD7000_80171590_S_80171590_3 *)((u8 *)state + ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)motion + 0x98);
    move_result = check_movement_clearance_and_height(heading, entity, state, 0x20);

    ((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_24 =
        ((CL_CD7000_80171590_S_80171590_3 *)((u8 *)state + ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_74;
    ((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_25 =
        ((CL_CD7000_80171590_S_80171590_3 *)((u8 *)state + ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_7C;
    ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_8A.u++;

    new_x = ((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_24;
    new_y = ((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((CL_CD7000_80171590_S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    cycle_map_cell_flags(new_x, new_y, tile_mask);
    ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_2A = heading;

    stored_result = move_result;
    result_code = move_result;
    if (result_code == 2) {
        if (!(g_dungeon_status.flags & 0x80)) {
            if (!(((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_14 & 0x8000)) {
                func_8014DF58(motion, update_param, entity, state);
                ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_A4 = stored_result;
            } else {
                ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_9A = 15;
            }
        } else {
            ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_9A = 15;
        }
    } else {
        if (result_code == 3 && !(g_dungeon_status.flags & 0x80) && !(((CL_CD7000_80171590_S_80171590_1 *)entity)->unk_14 & 0x8000)) {
            func_8014DF58(motion, update_param, entity, state);
            ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_A4 = stored_result;
        } else {
            ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_9A = 15;
        }
    }

    ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_8C = 0;
    (*(u32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (g_dungeon_status.flags & 0x80) {
        ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_96 = 0;
        return;
    }
    ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((CL_CD7000_80171590_S_80171590_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((CL_CD7000_80171590_S_80171590_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
    return;
}
