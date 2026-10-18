#include "modules/dungeon_resource12_slot0.h"

void complete_actor_arc_movement(void *action, void *motion, void *map_actor, void *actor) {
    s32 target_distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((R12_80172290_S_80172290_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)map_actor)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)map_actor + 0x2C)) = ((u8 *)D_80175A6C);
        func_80047784(
            map_actor,
            ((u8 *)D_80175A6C)[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((R12_80172290_S_80172290_0 *)action)->unk_98 |= 8;
        ((EntityRec *)motion)->flags14 = 0xFFF00000;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((R12_80172290_S_80172290_0 *)action)->unk_A0 = 0;
        ((R12_80172290_S_80172290_0 *)action)->unk_9B++;
                        /* fallthrough */
    case 1:
        frames_left = ((R12_80172290_S_80172290_0 *)action)->unk_96.s;
        ((R12_80172290_S_80172290_0 *)action)->unk_90 -= ((R12_80172290_S_80172290_0 *)action)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((Rec_D_80082E80 *)map_actor)->unk_24 << 6;
                s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

                ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((Rec_D_80082E80 *)map_actor)->unk_25 << 6;
                s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

                ((EntityRec *)motion)->unk_10 = ((target_y - current_y) << 16) /
                    ((R12_80172290_S_80172290_0 *)action)->unk_96.s;
            }
            ((R12_80172290_S_80172290_0 *)action)->unk_A0 += ((EntityRec *)motion)->flags14;
            ((EntityRec *)motion)->flags14 += 0x40000;
        }
        ((R12_80172290_S_80172290_0 *)action)->unk_90 += ((R12_80172290_S_80172290_0 *)action)->unk_A0;
        if (((R12_80172290_S_80172290_0 *)action)->unk_96.s < 0) {
            ((R12_80172290_S_80172290_0 *)action)->unk_90 = 0;
            ((R12_80172290_S_80172290_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((R12_80172290_S_80172290_0 *)action)->unk_9B++;
        }
                        /* fallthrough */
    case 2:
        if (((u32)((EntityRec *)actor)->flags1C) & 0x08000000) {
            ((R12_80172290_S_80172290_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);
            (*(u8 * *)((u8 *)map_actor + 0x2C)) = ((u8 *)D_80175A74);
            func_80047784(
                map_actor,
                ((u8 *)D_80175A74)[((g_game_work.view.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((R12_80172290_S_80172290_0 *)action)->unk_9B++;
        }
        break;
    }

    next_timer = ((R12_80172290_S_80172290_0 *)action)->unk_96.u - 1;
    ((R12_80172290_S_80172290_0 *)action)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25);
        reduce_actor_food_meter(actor, 4);
        advance_status_timers(actor);
        {
            u32 count;
            s32 signed_count;

            signed_count = g_dungeon_status.unk_08;
            count = ((u16)g_dungeon_status.unk_08);

            if (signed_count != 0) {
                g_dungeon_status.unk_08 = count - 1;
            }
        }

        actor_flags = ((u32)((EntityRec *)actor)->flags1C);
        if (actor_flags & 0x2000) {
            if (((EntityRec *)actor)->unk_46 & 0x8000) {
                ((EntityRec *)actor)->unk_46 &= 0x7FFF;
            }
        } else if (!(actor_flags & 0x410)) {
            if (actor_flags & 0x20000) {

                ((EntityRec *)actor)->facing = ((s16)get_rounded_facing_and_rounding_flag(
                    ((Rec_D_80082E80 *)map_actor)->unk_24, ((Rec_D_80082E80 *)map_actor)->unk_25,
                    D_80082E80.tileX, D_80082E80.tileY, &target_distance));
            }
        }

        if ((check_actor_floor_trap(map_actor, actor) << 16) > 0) {
            ((R12_80172290_S_80172290_0 *)action)->unk_8C = ((void *)update_actor_state_and_select_target);
            func_800A9A04(actor);
        }
    }
}
