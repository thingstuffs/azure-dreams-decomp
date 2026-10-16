#include "modules/dungeon_resource10_slot0.h"

void func_80171D7C(void *movement, void *motion, void *entity, void *path_state) {
    void *state = path_state;
    s32 move_flags;
    s16 heading;
    s16 move_result;
    s16 x;
    s32 y;

    if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_71.s <= 0) {
        return;
    }

    if (((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 != 0xF) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_90 = 0;
        ((Rec_func_80171CD4_arg1 *)motion)->unk_14 = 0;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9D = 0;
    }

    if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_71.u <= ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s) {
        return;
    }

    if (((Rec_D_80082E80 *)entity)->unk_2C.as_pu8 != ((u8 *)D_80175980)) {
        (*(u8 * *)((u8 *)entity + (0x2C))) = ((u8 *)D_80175980);
        func_80047784(
            entity,
            ((u8 *)D_80175980)[((gameWork.view.viewAngle + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_2A + 0x100) >> 9) & 7],
            0);
    }

    x = ((Rec_D_80082E80 *)entity)->unk_24;
    y = ((Rec_D_80082E80 *)entity)->unk_25;
    move_flags = 0x3000;
    if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_1C & 0x2000) {
        move_flags = 0x300;
    }
    func_8009A3D0(x, y, move_flags);

    heading = ((s16)dungeonGetRoundedFacingAndRoundingFlag(
        x,
        y,
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_74,
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_7C,
        (u8 *)movement + 0x98));
    move_result = ((s16)dungeonCheckMovementClearanceAndHeight(heading, entity, state, 0x20));

    ((Rec_D_80082E80 *)entity)->unk_24 =
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_74;
    move_flags = 0x3000;
    ((Rec_D_80082E80 *)entity)->unk_25 =
        ((R10_80171D7C_S_80171CD4_4 *)((u8 *)state + ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.s))->unk_7C;
    ((R10_80171D7C_S_80171CD4_0 *)state)->unk_8A.u++;

    {
        s32 next_x = ((Rec_D_80082E80 *)entity)->unk_24;
        s32 next_y = ((Rec_D_80082E80 *)entity)->unk_25;

        if (((R10_80171D7C_S_80171CD4_0 *)state)->unk_1C & 0x2000) {
            move_flags = 0x300;
        }
        func_8009A21C(next_x, next_y, move_flags);
    }

    ((R10_80171D7C_S_80171CD4_0 *)state)->unk_2A = heading;
    if (move_result == 3) {
        if (!(dungeonStatus.flags & 0x80) && !(((Rec_D_80082E80 *)entity)->unk_14.at00_u16.v & 0x8000)) {
            func_80172730(movement, motion, entity, state);
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        } else {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
            ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
        }
    } else {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_9A.as_u8 = 0xF;
        ((Rec_func_80171CD4_arg0 *)movement)->unk_8C = 0;
    }
    (*(s32 *)((u8 *)state + (0x1C))) |= 0x40000000;
    if (dungeonStatus.flags & 0x80) {
        ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 0;
        return;
    }

    ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8;
    {
        s32 step_count = ((R10_80171D7C_S_80171CD4_0 *)state)->unk_71.u;
        if (step_count > 0) {
            ((Rec_func_80171CD4_arg0 *)movement)->unk_96 = 8 / step_count;
        }
    }
}
