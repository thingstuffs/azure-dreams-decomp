#include "modules/dungeon_ovl_cb3000.h"

void dungeonAdvanceActorStoredPath(void *motion, s32 update_param, void *entity, void *state) {
    s32 tile_mask;
    s32 old_x;
    s32 old_y;
    s32 new_x;
    s32 new_y;
    s16 heading;
    s16 move_result;
    s16 stored_result;
    s32 result_code;

    if (((CB_80171590_S_80171590_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (!((s32)((CB_80171590_S_80171590_0 *)state)->unk_71.u > ((CB_80171590_S_80171590_0 *)state)->unk_8A.s)) {
        return;
    }

    if (((CB_80171590_S_80171590_1 *)entity)->unk_2C != D_801752AC) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = D_801752AC;
        func_80047784(
            entity,
            D_801752AC[((gameWork.view.viewAngle + ((CB_80171590_S_80171590_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    old_x = ((CB_80171590_S_80171590_1 *)entity)->unk_24;
    old_y = ((CB_80171590_S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((CB_80171590_S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(old_x, old_y, tile_mask);

    heading = dungeonGetRoundedFacingAndRoundingFlag(
        old_x,
        old_y,
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_74,
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)motion + 0x98);
    move_result = dungeonCheckMovementClearanceAndHeight(heading, entity, state, 0x20);

    ((CB_80171590_S_80171590_1 *)entity)->unk_24 =
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_74;
    ((CB_80171590_S_80171590_1 *)entity)->unk_25 =
        ((CB_80171590_S_80171590_3 *)((u8 *)state + ((CB_80171590_S_80171590_0 *)state)->unk_8A.s))->unk_7C;
    ((CB_80171590_S_80171590_0 *)state)->unk_8A.u++;

    new_x = ((CB_80171590_S_80171590_1 *)entity)->unk_24;
    new_y = ((CB_80171590_S_80171590_1 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((CB_80171590_S_80171590_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A21C(new_x, new_y, tile_mask);
    ((CB_80171590_S_80171590_0 *)state)->unk_2A = heading;

    stored_result = move_result;
    result_code = move_result;
    if (result_code == 2) {
        if (!(dungeonStatus.flags & 0x80)) {
            if (!(((CB_80171590_S_80171590_1 *)entity)->unk_14 & 0x8000)) {
                func_80171F58(motion, update_param, entity, state);
                ((CB_80171590_S_80171590_2 *)motion)->unk_A4 = stored_result;
            } else {
                ((CB_80171590_S_80171590_2 *)motion)->unk_9A = 15;
            }
        } else {
            ((CB_80171590_S_80171590_2 *)motion)->unk_9A = 15;
        }
    } else {
        if (result_code == 3 && !(dungeonStatus.flags & 0x80) && !(((CB_80171590_S_80171590_1 *)entity)->unk_14 & 0x8000)) {
            func_80171F58(motion, update_param, entity, state);
            ((CB_80171590_S_80171590_2 *)motion)->unk_A4 = stored_result;
        } else {
            ((CB_80171590_S_80171590_2 *)motion)->unk_9A = 15;
        }
    }

    ((CB_80171590_S_80171590_2 *)motion)->unk_8C = 0;
    (*(u32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (dungeonStatus.flags & 0x80) {
        ((CB_80171590_S_80171590_2 *)motion)->unk_96 = 0;
        return;
    }
    ((CB_80171590_S_80171590_2 *)motion)->unk_96 = 8;
    {
        s32 step_count = ((CB_80171590_S_80171590_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((CB_80171590_S_80171590_2 *)motion)->unk_96 = 8 / step_count;
        }
    }
    return;
}
