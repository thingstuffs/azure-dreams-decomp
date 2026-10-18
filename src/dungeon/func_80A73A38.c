#include "modules/dungeon_resource07_slot0.h"

void settle_directional_motion_at_tile(void *motion_state, void *motion, void *sprite, void *entity)
{
    s32 direction;
    s16 timer;
    s32 tracked_entity;

    direction = (((EntityRec *)entity)->unk_6A >> 9) & 7;
    switch (((R07_80173238_S_80173238_1 *)motion_state)->unk_9B) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C = ((s16 *)((s8 *)dir_step_x))[direction] << 18;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 = ((s16 *)((s8 *)dir_step_y))[direction] << 18;
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_9B++;


        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R07_80173238_S_80173238_2 *)motion)->unk_14 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_10 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_0C = 0;
            begin_actor_display_action(motion_state, motion, sprite, ((u8 *)D_80174178));
            return;
        }
        if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x8000) {
            ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s = 0;
            ((R07_80173238_S_80173238_1 *)motion_state)->unk_9B = 3;
            return;
        }

        if (((u32)((EntityRec *)entity)->flags1C) & 0x228) {
            timer = 8;
        } else {
            timer = -1;
        }
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s = timer;

        ((R07_80173238_S_80173238_2 *)motion)->unk_0C -= ((R07_80173238_S_80173238_2 *)motion)->unk_0C / 4;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 -= ((R07_80173238_S_80173238_2 *)motion)->unk_10 / 4;

    case 1:
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;

        if (((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s > 0) {
            ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s = ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.u - 1;
        } else if (((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000) {
            ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s = 0;
        }

        if (((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s != 0) {
            return;
        }
        if (((EntityRec *)entity)->unk_28 == 0) {
            ((R07_80173238_S_80173238_2 *)motion)->unk_14 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_10 = 0;
            ((R07_80173238_S_80173238_2 *)motion)->unk_0C = 0;
            begin_actor_display_action(motion_state, motion, sprite, ((u8 *)D_80174178));
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174150);
        func_80047784(
            sprite,
            ((u8 *)D_80174150)[((g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_9B++;
        return;

    case 2:
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C -= ((s16 *)((s8 *)dir_step_x))[direction] << 14;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 -= ((s16 *)((s8 *)dir_step_y))[direction] << 14;
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80174150);
        func_80047784(
            sprite,
            ((u8 *)D_80174150)[((g_game_work.view.viewAngle + ((EntityRec *)entity)->facing + 0x100) >> 9) & 7],
            0);
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s = 8;
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_9B++;
        return;

    case 3:
        timer = ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s;
        if (timer != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)sprite)->unk_24 << 6;
                s32 current_x = ((R07_80173238_S_80173238_2 *)motion)->unk_00.at02.v - 0x20;
                ((R07_80173238_S_80173238_2 *)motion)->unk_0C = ((target_x - current_x) << 15) / timer;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)sprite)->unk_25 << 6;
                s32 current_y = ((R07_80173238_S_80173238_2 *)motion)->unk_04.at02.v - 0x20;
                ((R07_80173238_S_80173238_2 *)motion)->unk_10 =
                    ((target_y - current_y) << 15) / ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s;
            }
        }

        timer = ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.u - 1;
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_96.s = timer;
        if ((s32)(timer << 16) > 0) {
            return;
        }

        ((R07_80173238_S_80173238_2 *)motion)->unk_14 = 0;
        ((R07_80173238_S_80173238_2 *)motion)->unk_10 = 0;
        ((R07_80173238_S_80173238_2 *)motion)->unk_0C = 0;
        ((R07_80173238_S_80173238_2 *)motion)->unk_00.at00.v = ((((Rec_D_80082E80 *)sprite)->unk_24 << 6) + 0x20) << 16;
        ((R07_80173238_S_80173238_2 *)motion)->unk_04.at00.v = ((((Rec_D_80082E80 *)sprite)->unk_25 << 6) + 0x20) << 16;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);

        tracked_entity = ((s32)g_dungeon_status.unk_10);
        if (tracked_entity == (s32)((u8 *)entity - 0x20)) {
            g_dungeon_status.unk_10 = tracked_entity & 0x7FFFFFFF;
        }
        ((R07_80173238_S_80173238_1 *)motion_state)->unk_8C = ((void *)func_80170E54);

        return;

    default:
        return;
    }
}
