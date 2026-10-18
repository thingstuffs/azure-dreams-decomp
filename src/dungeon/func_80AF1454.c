#include "modules/dungeon_resource10_slot0.h"

void func_80172C54(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 height_step;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 facing_aux;
    DungeonGlobalStatus *global_base;

    state = ((R10_80172C54_S_80172C54_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((Rec_D_80082E80 *)sprite)->unk_14.at00_u16.v & 0x6000)) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801759A8);
        func_80047784(
            sprite,
            ((u8 *)D_801759A8)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R10_80172C54_S_80172C54_0 *)action)->unk_98 |= 8;
        actor->flags1C &= 0xF7FFFFFF;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s = 5;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_A4 = 0;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_90 -= ((R10_80172C54_S_80172C54_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = ((Rec_D_80082E80 *)sprite)->unk_24;
            pos_x = motion->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            motion->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = motion->y.w.i;
            pos_y -= 0x20;
            motion->unk_10 =
                (((((Rec_D_80082E80 *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s;

            ((R10_80172C54_S_80172C54_0 *)action)->unk_A4 =
                (-func_800644B8(((R10_80172C54_S_80172C54_0 *)action)->unk_9E.s * 0x199)) << 10;
        }

        height_offset = ((R10_80172C54_S_80172C54_0 *)action)->unk_90;
        height_step = ((R10_80172C54_S_80172C54_0 *)action)->unk_A4;
        next_move_ticks = ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.u;
        height_offset += height_step;
        next_move_ticks -= 1;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_9E.u = next_move_ticks;
        ((R10_80172C54_S_80172C54_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) < 0) {
            ((R10_80172C54_S_80172C54_0 *)action)->unk_90 = 0;
            ((R10_80172C54_S_80172C54_0 *)action)->unk_98 &= 0xFFF7;
            actor->flags1C |= 0x08000000;
            ((R10_80172C54_S_80172C54_0 *)action)->unk_9B++;
        }
    case 2:
        if (actor->flags1C & 0x08000000) {
            ((R10_80172C54_S_80172C54_0 *)action)->unk_98 &= 0xFFF7;
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
            (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_801759B8);
            func_80047784(
                sprite,
                ((u8 *)D_801759B8)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
                0);
            ((R10_80172C54_S_80172C54_0 *)action)->unk_9B++;
        }
        break;

    case 3:
        if (((Rec_D_80082E80 *)sprite)->unk_2C.as_pu8 == ((u8 *)D_80175988)) {
            break;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = ((u8 *)D_80175988);
        func_80047784(
            sprite,
            ((u8 *)D_80175988)[((g_game_work.view.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
    }

    action_ticks = ((R10_80172C54_S_80172C54_0 *)action)->unk_96 - 1;
    ((R10_80172C54_S_80172C54_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    motion->flags14 = 0;
    motion->unk_10 = 0;
    motion->unk_0C = 0;
    set_record_integer_tile_center(motion, ((Rec_D_80082E80 *)sprite)->unk_24, ((Rec_D_80082E80 *)sprite)->unk_25);
    reduce_actor_food_meter(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->unk_08 != 0) {
        (*(u16 *)&global_base->unk_08)--;
    }

    actor_flags = actor->flags1C;
    if (actor_flags & 0x2000) {
        if (actor->unk_46 & 0x8000) {
            actor->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            actor->facing = ((s16)get_rounded_facing_and_rounding_flag((s16)(((Rec_D_80082E80 *)sprite)->unk_24),(s16)(((Rec_D_80082E80 *)sprite)->unk_25),(s16)(D_80082E80.tileX),(s16)(D_80082E80.tileY),
                &facing_aux));
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((R10_80172C54_S_80172C54_0 *)action)->unk_8C = ((void *)func_801717F4);
        func_800A9A04(actor);
    }
}
