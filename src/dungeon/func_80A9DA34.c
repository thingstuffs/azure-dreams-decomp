#include "modules/dungeon_resource08_slot0.h"

void func_80173234(void *action, void *motion, void *sprite, void *entity)
{
    s32 state;
    s16 move_timer;
    s32 tracked_entity;

    state = ((R08_80173234_S_80173234_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        func_800AD4D0(entity);
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C =
            -((s16 *)((s8 *)dirStepX))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 15;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 =
            -((s16 *)((s8 *)dirStepY))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 15;
        ((R08_80173234_S_80173234_0 *)action)->unk_9B++;

        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R08_80173234_S_80173234_1 *)motion)->unk_14 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_10 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_0C = 0;
            func_800AAA54(action, motion, sprite, ((u8 *)D_80174C74));
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((R08_80173234_S_80173234_0 *)action)->unk_96.s = 0;
            ((R08_80173234_S_80173234_0 *)action)->unk_9B = 3;
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x228) {
            move_timer = 8;
        } else {
            move_timer = -1;
        }
        ((R08_80173234_S_80173234_0 *)action)->unk_96.s = move_timer;

        ((R08_80173234_S_80173234_1 *)motion)->unk_0C -= ((R08_80173234_S_80173234_1 *)motion)->unk_0C / 4;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 -= ((R08_80173234_S_80173234_1 *)motion)->unk_10 / 4;
                        /* fall through */

    case 1:
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;

        if (((R08_80173234_S_80173234_0 *)action)->unk_96.s > 0) {
            ((R08_80173234_S_80173234_0 *)action)->unk_96.s = ((R08_80173234_S_80173234_0 *)action)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((R08_80173234_S_80173234_0 *)action)->unk_96.s = 0;
        }

        if (((R08_80173234_S_80173234_0 *)action)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R08_80173234_S_80173234_1 *)motion)->unk_14 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_10 = 0;
            ((R08_80173234_S_80173234_1 *)motion)->unk_0C = 0;
            func_800AAA54(action, motion, sprite, ((u8 *)D_80174C74));
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C44);
        func_80047784(
            sprite,
            ((u8 *)D_80174C44)[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R08_80173234_S_80173234_0 *)action)->unk_9B++;
        return;

    case 2:
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C +=
            ((s16 *)((s8 *)dirStepX))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 +=
            ((s16 *)((s8 *)dirStepY))[(((EntityRec *)entity)->unk_6A >> 9) & 7] << 14;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174C44);
        func_80047784(
            sprite,
            ((u8 *)D_80174C44)[((gameWork.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R08_80173234_S_80173234_0 *)action)->unk_96.s = 8;
        ((R08_80173234_S_80173234_0 *)action)->unk_9B++;
        return;

    case 3:
        move_timer = ((R08_80173234_S_80173234_0 *)action)->unk_96.s;
        if (move_timer != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_x = ((R08_80173234_S_80173234_1 *)motion)->unk_00.at02.v - 0x20;
                ((R08_80173234_S_80173234_1 *)motion)->unk_0C = ((target_x - current_x) << 15) / move_timer;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_y = ((R08_80173234_S_80173234_1 *)motion)->unk_04.at02.v - 0x20;
                ((R08_80173234_S_80173234_1 *)motion)->unk_10 =
                    ((target_y - current_y) << 15) / ((R08_80173234_S_80173234_0 *)action)->unk_96.s;
            }
        }

        move_timer = ((R08_80173234_S_80173234_0 *)action)->unk_96.u - 1;
        ((R08_80173234_S_80173234_0 *)action)->unk_96.s = move_timer;
        if ((s32)(move_timer << 16) > 0) {
            return;
        }

        ((R08_80173234_S_80173234_1 *)motion)->unk_14 = 0;
        ((R08_80173234_S_80173234_1 *)motion)->unk_10 = 0;
        ((R08_80173234_S_80173234_1 *)motion)->unk_0C = 0;
        ((R08_80173234_S_80173234_1 *)motion)->unk_00.at00.v = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
        ((R08_80173234_S_80173234_1 *)motion)->unk_04.at00.v = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
        func_800A2B04(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        tracked_entity = ((s32)dungeonStatus.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            dungeonStatus.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        ((R08_80173234_S_80173234_0 *)action)->unk_8C = ((void *)func_80170E7C);
    }
}
