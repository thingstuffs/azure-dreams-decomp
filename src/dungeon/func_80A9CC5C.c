#include "modules/dungeon_resource08_slot0.h"
#include "shared/sprite_frame_state.h"

void func_8017245C(void *action, void *motion, void *sprite, void *actor)
{
    s32 state;
    s32 move_ticks;
    s32 target_x;
    s32 pos_x;
    s32 height_offset;
    s32 arc_offset;
    s32 pos_y;
    s32 next_move_ticks;
    s32 action_ticks;
    s32 actor_flags;
    s32 direction_aux;
    DungeonGlobalStatus *global_base;

    state = ((R08_8017245C_S_80172478_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)sprite)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C54);
        select_sprite_entry(
            sprite,
            ((u8 *)D_80174C54)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R08_8017245C_S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
            0);
        ((R08_8017245C_S_80172478_0 *)action)->unk_98 |= 8;
        ((R08_8017245C_S_80172478_2 *)actor)->unk_1C.s &= 0xF7FFFFFF;
        ((R08_8017245C_S_80172478_0 *)action)->unk_A8.s = 5;
        ((R08_8017245C_S_80172478_0 *)action)->unk_A4 = 0;
        ((R08_8017245C_S_80172478_0 *)action)->unk_9B++;

    case 1:
        move_ticks = ((R08_8017245C_S_80172478_0 *)action)->unk_A8.s;
        ((R08_8017245C_S_80172478_0 *)action)->unk_90 -= ((R08_8017245C_S_80172478_0 *)action)->unk_A4;
        if (move_ticks != 0) {
            target_x = ((SpriteFrameState *)sprite)->unk_24;
            pos_x = ((EntityRec *)motion)->x.w.i;
            target_x <<= 6;
            pos_x -= 0x20;

            ((EntityRec *)motion)->unk_0C = ((target_x - pos_x) << 16) / move_ticks;

            pos_y = ((EntityRec *)motion)->y.w.i;
            pos_y -= 0x20;
            ((EntityRec *)motion)->unk_10 =
                (((((SpriteFrameState *)sprite)->unk_25 << 6) - pos_y) << 16) /
                ((R08_8017245C_S_80172478_0 *)action)->unk_A8.s;

            ((R08_8017245C_S_80172478_0 *)action)->unk_A4 =
                (-func_800644B8(((R08_8017245C_S_80172478_0 *)action)->unk_A8.s * 0x199)) << 10;
        }

        height_offset = ((R08_8017245C_S_80172478_0 *)action)->unk_90;
        arc_offset = ((R08_8017245C_S_80172478_0 *)action)->unk_A4;
        next_move_ticks = ((R08_8017245C_S_80172478_0 *)action)->unk_A8.u;
        height_offset += arc_offset;
        next_move_ticks -= 1;
        ((R08_8017245C_S_80172478_0 *)action)->unk_A8.u = next_move_ticks;
        ((R08_8017245C_S_80172478_0 *)action)->unk_90 = height_offset;
        if ((next_move_ticks << 16) >= 0) {
            break;
        }

        ((R08_8017245C_S_80172478_0 *)action)->unk_90 = 0;
        ((R08_8017245C_S_80172478_0 *)action)->unk_98 &= 0xFFF7;
        ((R08_8017245C_S_80172478_2 *)actor)->unk_1C.s |= 0x08000000;
        ((R08_8017245C_S_80172478_0 *)action)->unk_9B++;
        break;
    case 2:
        if (((R08_8017245C_S_80172478_2 *)actor)->unk_1C.s & 0x08000000) {
            ((R08_8017245C_S_80172478_0 *)action)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
            ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C5C);
            select_sprite_entry(
                sprite,
                ((u8 *)D_80174C5C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((R08_8017245C_S_80172478_2 *)actor)->unk_2A + 0x100) >> 9) & 7],
                0);

            ((R08_8017245C_S_80172478_0 *)action)->unk_9B++;
        }
        break;
    }
    action_ticks = ((R08_8017245C_S_80172478_0 *)action)->unk_96 - 1;
    ((R08_8017245C_S_80172478_0 *)action)->unk_96 = action_ticks;
    if ((action_ticks << 16) > 0) {
        return;
    }

    ((EntityRec *)motion)->flags14 = 0;
    ((EntityRec *)motion)->unk_10 = 0;
    ((EntityRec *)motion)->unk_0C = 0;
    set_record_integer_tile_center(motion, ((SpriteFrameState *)sprite)->unk_24, ((SpriteFrameState *)sprite)->unk_25);
    reduce_actor_food_meter(actor, 4);
    advance_status_timers(actor);

    global_base = &g_dungeon_status;
    if (global_base->activity_counts.parts.pending_movement_count != 0) {
        (*(u16 *)&global_base->activity_counts.parts.pending_movement_count)--;
    }

    actor_flags = ((R08_8017245C_S_80172478_2 *)actor)->unk_1C.u;
    if (actor_flags & 0x2000) {
        if (((R08_8017245C_S_80172478_2 *)actor)->unk_46 & 0x8000) {
            ((R08_8017245C_S_80172478_2 *)actor)->unk_46 &= 0x7FFF;
        }
    } else if (!(actor_flags & 0x410)) {
        if (actor_flags & 0x20000) {
            ((R08_8017245C_S_80172478_2 *)actor)->unk_2A = ((s16)get_rounded_facing_and_rounding_flag((s16)((SpriteFrameState *)sprite)->unk_24,(s16)((SpriteFrameState *)sprite)->unk_25,(s16)(D_80082E80.tile_position.parts.tile_x),(s16)(D_80082E80.tile_position.parts.tile_y),
                &direction_aux));
        }
    }

    if ((check_actor_floor_trap(sprite, actor) << 16) > 0) {
        ((R08_8017245C_S_80172478_0 *)action)->unk_8C = ((void *)update_actor_behavior_and_effect);
        on_actor_status_updated(actor);
    }
}
