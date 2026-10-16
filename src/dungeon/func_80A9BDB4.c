#include "modules/dungeon_resource08_slot0.h"

void func_801715B4(void *action, s32 action_id, void *entity, void *move_state) {
    void *state = move_state;
    s32 tile_mask;
    s16 move_result;
    s16 direction;
    s16 x;
    s32 y;
    s32 step_count;
    u8 new_x;
    u8 new_y;

    if (((R08_801715B4_S_80171570_0 *)state)->unk_71.s <= 0) {
        return;
    }
    if (((R08_801715B4_S_80171570_0 *)state)->unk_71.u <= ((R08_801715B4_S_80171570_0 *)state)->unk_8A) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != ((u8 *)D_80174C2C)) {
        (*(u8 * *)((u8 *)entity + 0x2C)) = ((u8 *)D_80174C2C);
        func_80047784(
            entity,(s16)(((u8 *)D_80174C2C)[((gameWork.view.viewAngle + ((R08_801715B4_S_80171570_0 *)state)->unk_2A + 0x100) >> 9) & 7]),(s16)(0));
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    tile_mask = 0x3000;
    if (((R08_801715B4_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A3D0(x, y, tile_mask);

    direction = ((s16)dungeonGetRoundedFacingAndRoundingFlag((s16)(x),(s16)(y),(s16)(((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_74),(s16)(((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_7C),
        (u8 *)action + 0x98));
    move_result = ((s16)dungeonCheckMovementClearanceAndHeight((s16)(direction), entity, state, 0x20));

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_74;
    tile_mask = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((R08_801715B4_S_80171570_3 *)((u8 *)state + ((R08_801715B4_S_80171570_0 *)state)->unk_8A))->unk_7C;
    ((R08_801715B4_S_80171570_0 *)state)->unk_8A = (u16)((R08_801715B4_S_80171570_0 *)state)->unk_8A + 1;

    new_x = ((Rec_D_80082E80 *)entity)->unk_24;
    new_y = ((Rec_D_80082E80 *)entity)->unk_25;
    if (((R08_801715B4_S_80171570_0 *)state)->unk_1C & 0x2000) {
        tile_mask = 0x300;
    }
    func_8009A21C((s16)(new_x),(s16)(new_y),(u16)(tile_mask));
    ((R08_801715B4_S_80171570_0 *)state)->unk_2A = direction;

    if (move_result == 3 && !(dungeonStatus.flags & 0x80)
        && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
        func_80171F40(action, action_id, entity, state);
        ((R08_801715B4_S_80171570_2 *)action)->unk_8C = 0;
    } else {
        ((R08_801715B4_S_80171570_2 *)action)->unk_9A = 0x0F;
        ((R08_801715B4_S_80171570_2 *)action)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + 0x1C)) |= 0x40000000;
    if (dungeonStatus.flags & 0x80) {
        ((R08_801715B4_S_80171570_2 *)action)->unk_96 = 0;
        return;
    }

    ((R08_801715B4_S_80171570_2 *)action)->unk_96 = 8;
    step_count = ((R08_801715B4_S_80171570_0 *)state)->unk_71.u;
    if (step_count > 0) {
        ((R08_801715B4_S_80171570_2 *)action)->unk_96 = 8 / step_count;
    }
}
