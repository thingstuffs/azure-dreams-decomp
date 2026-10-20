#include "modules/dungeon_resource03_slot0.h"
#include "shared/sprite_frame_state.h"

void complete_actor_jump_to_destination(void *jump, void *motion, void *map_entity, void *actor) {
    s32 facing_distance;
    s32 frames_left;
    s16 next_timer;
    s32 actor_flags;
    s32 state;

    state = ((R03_80172258_S_80172258_0 *)jump)->unk_9B;
    switch (state) {
    case 0:
        if (!(((SpriteFrameState *)map_entity)->flags & 0x6000)) {
            break;
        }
        ((SpriteFrameState *)map_entity)->frameTable = ((u8 *)D_80173C94);
        select_sprite_entry(
            map_entity,
            ((u8 *)D_80173C94)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
            0);
        ((R03_80172258_S_80172258_0 *)jump)->unk_98 |= 8;
        ((EntityRec *)motion)->flags14 = 0xFFF20000;
        ((EntityRec *)actor)->flags1C &= 0xF7FFFFFF;
        ((R03_80172258_S_80172258_0 *)jump)->unk_A0 = 0;
        ((R03_80172258_S_80172258_0 *)jump)->unk_9B++;

    case 1:
        frames_left = ((R03_80172258_S_80172258_0 *)jump)->unk_96.s;
        ((R03_80172258_S_80172258_0 *)jump)->unk_90 -= ((R03_80172258_S_80172258_0 *)jump)->unk_A0;
        if (frames_left != 0) {
            {
                s32 target_x = ((SpriteFrameState *)map_entity)->unk_24 << 6;
                s32 current_x = ((EntityRec *)motion)->x.w.i - 0x20;

                ((EntityRec *)motion)->unk_0C = ((target_x - current_x) << 16) / frames_left;
            }
            {
                s32 target_y = ((SpriteFrameState *)map_entity)->unk_25 << 6;
                s32 current_y = ((EntityRec *)motion)->y.w.i - 0x20;

                ((EntityRec *)motion)->unk_10 = ((target_y - current_y) << 16) /
                    ((R03_80172258_S_80172258_0 *)jump)->unk_96.s;
            }
            ((R03_80172258_S_80172258_0 *)jump)->unk_A0 += ((EntityRec *)motion)->flags14;
            ((EntityRec *)motion)->flags14 += 0x38000;
        }
        ((R03_80172258_S_80172258_0 *)jump)->unk_90 += ((R03_80172258_S_80172258_0 *)jump)->unk_A0;
        if (((R03_80172258_S_80172258_0 *)jump)->unk_96.s < 2) {
            ((R03_80172258_S_80172258_0 *)jump)->unk_90 = 0;
            ((R03_80172258_S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((EntityRec *)actor)->flags1C |= 0x08000000;
            ((R03_80172258_S_80172258_0 *)jump)->unk_9B++;
        }

    case 2:
        if (((u32)((EntityRec *)actor)->flags1C) & 0x08000000) {
            ((R03_80172258_S_80172258_0 *)jump)->unk_98 &= 0xFFF7;
            ((EntityRec *)motion)->flags14 = 0;
            ((EntityRec *)motion)->unk_10 = 0;
            ((EntityRec *)motion)->unk_0C = 0;
            set_record_integer_tile_center(motion, ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25);
            ((SpriteFrameState *)map_entity)->frameTable = ((u8 *)D_80173C9C);
            select_sprite_entry(
                map_entity,
                ((u8 *)D_80173C9C)[((g_game_work.view.camera_rotation.parts.viewAngle + ((EntityRec *)actor)->facing + 0x100) >> 9) & 7],
                0);
            ((R03_80172258_S_80172258_0 *)jump)->unk_9B++;
        }
    default:
        break;
    }

    next_timer = ((R03_80172258_S_80172258_0 *)jump)->unk_96.u - 1;
    ((R03_80172258_S_80172258_0 *)jump)->unk_96.s = next_timer;
    if ((next_timer << 16) <= 0) {
        ((EntityRec *)motion)->flags14 = 0;
        ((EntityRec *)motion)->unk_10 = 0;
        ((EntityRec *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25);
        reduce_actor_food_meter(actor, 4);
        advance_status_timers(actor);
        {
            u32 count_unsigned;
            s32 count_signed;

            count_signed = g_dungeon_status.activity_counts.parts.pending_movement_count;
            count_unsigned = ((u16)g_dungeon_status.activity_counts.parts.pending_movement_count);

            if (count_signed != 0) {
                g_dungeon_status.activity_counts.parts.pending_movement_count = count_unsigned - 1;
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
                    ((SpriteFrameState *)map_entity)->unk_24, ((SpriteFrameState *)map_entity)->unk_25,
                    D_80082E80.tile_position.parts.tile_x, D_80082E80.tile_position.parts.tile_y, &facing_distance));
            }
        }

finish:
        if ((check_actor_floor_trap(map_entity, actor) << 16) > 0) {
            ((R03_80172258_S_80172258_0 *)jump)->unk_8C = ((void *)func_80170E54);
            on_actor_status_updated(actor);
        }
    }
}
