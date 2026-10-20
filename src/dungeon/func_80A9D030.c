#include "modules/dungeon_resource08_slot0.h"
#include "shared/sprite_frame_state.h"

void update_staged_movement_and_return_to_tile(void *action, EntityRec *motion, void *sprite, EntityRec *actor)
{
    s32 state;
    s32 direction_offset;
    s32 vertical_speed;
    u16 ticks_left;

    state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
    switch (state) {
    case 0:
        if (((SpriteFrameState *)sprite)->flags & 0x8000) {
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = 3;
            ((R08_80172830_S_80172830_0 *)action)->unk_96 = 0;
            ((SpriteFrameState *)sprite)->flags |= 0x6000;
            return;
        }

        direction_offset = (((((u16)actor->facing) >> 9) & 7) + 4) % 8;
        motion->unk_0C =
            dir_step_x[direction_offset] * 3 << 16;
        motion->unk_10 =
            dir_step_y[direction_offset] * 3 << 16;
        motion->flags14 = 0;
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C34);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C34)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {
            s32 next_state;

            next_state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
            ((R08_80172830_S_80172830_0 *)action)->unk_96 = 0;
            next_state++;
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = next_state;
            return;
        }

    case 1:
        motion->unk_0C -= motion->unk_0C >> 2;
        motion->unk_10 -= motion->unk_10 >> 2;
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C64);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C64)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        {
            s32 next_state;

            next_state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
            ((R08_80172830_S_80172830_0 *)action)->unk_96 = 4;
            next_state++;
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = next_state;
            return;
        }

    case 2:
        if (!(((SpriteFrameState *)sprite)->flags & 0xE000)) {
            return;
        }
        play_sound_if_enabled(0x808);
        ((SpriteFrameState *)sprite)->frameTable = ((u8 *)D_80174C6C);
        select_sprite_entry(sprite,
            ((u8 *)D_80174C6C)[((g_game_work.view.camera_rotation.parts.viewAngle + actor->facing + 0x100) >> 9) & 7],
            0);
        ((R08_80172830_S_80172830_0 *)action)->unk_96 = 0x14;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        {
            s32 next_state;

            next_state = ((R08_80172830_S_80172830_0 *)action)->unk_9B;
            next_state++;
            ((R08_80172830_S_80172830_0 *)action)->unk_9B = next_state;
            return;
        }

    case 3:
        ticks_left = ((R08_80172830_S_80172830_0 *)action)->unk_96;
        vertical_speed = motion->flags14;
        ticks_left--;
        ((R08_80172830_S_80172830_0 *)action)->unk_96 = ticks_left;
        if ((s16)ticks_left < 12) {
            vertical_speed += 0x1400;
        } else {
            vertical_speed += 0x20000;
        }
        motion->flags14 = vertical_speed;
        ((R08_80172830_S_80172830_0 *)action)->unk_90 += vertical_speed;

        if ((s16)((R08_80172830_S_80172830_0 *)action)->unk_96 == 0x11) {
            s32 direction_step;
            s16 *x_steps;
            s16 *x_step;
            s16 *y_step;

            direction_offset = ((u16)actor->facing) >> 8;
            x_steps = dir_step_x;
            x_step = (s16 *)((u8 *)x_steps + (direction_offset & 0xE));
            direction_step = *x_step;
            motion->unk_0C =
                (direction_step * 3 << 16) + ((direction_step * 3 << 16) >> 2);
            y_step = (s16 *)((u8 *)&dir_step_y + (direction_offset & 0xE));
            direction_step = *y_step;
            motion->flags14 = 0xFFF70000;
            motion->unk_10 =
                (direction_step * 3 << 16) + ((direction_step * 3 << 16) >> 2);
            ((R08_80172830_S_80172830_0 *)action)->unk_90 = 0;
            ((R08_80172830_S_80172830_0 *)action)->unk_98 |= 8;
        }

        if (((((SpriteFrameState *)sprite)->unk_04 == 3) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            resolve_attack_damage_and_effects(actor, sprite,(s16)(actor->facing),(s16)(1));
        }

        if (((((SpriteFrameState *)sprite)->unk_04 == 5) &&
             (((SpriteFrameState *)sprite)->flags & 0x1000)) ||
            (((SpriteFrameState *)sprite)->flags & 0x8000)) {
            motion->unk_0C =
                ((((((SpriteFrameState *)sprite)->unk_24 << 6) + 0x20) << 16) -
                 motion->x.v) / (s16)((R08_80172830_S_80172830_0 *)action)->unk_96;
            motion->unk_10 =
                ((((((SpriteFrameState *)sprite)->unk_25 << 6) + 0x20) << 16) -
                 motion->y.v) / (s16)((R08_80172830_S_80172830_0 *)action)->unk_96;
        }

        if (((s16)((R08_80172830_S_80172830_0 *)action)->unk_96 > 0) &&
            !(((SpriteFrameState *)sprite)->flags & 0x8000)) {
            return;
        }
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        set_record_integer_tile_center(motion,(u8)((SpriteFrameState *)sprite)->unk_24,(u8)((SpriteFrameState *)sprite)->unk_25);
        reduce_actor_food_meter(actor, 0x100);
        (*(u8 * *)((u8 *)action + 0x8C)) = ((void *)update_actor_behavior_and_effect);
        g_dungeon_status.active_actor = 0;
        (*(u16 *)((u8 *)action + 0x98)) &= 0xFFF7;
        advance_status_timers(actor);
        if (actor->unk_6D == 0) {
            actor->unk_46 &= 0x7FFF;
            return;
        }
        ((void * *)D_800E3DE8)[0] = (u8 *)actor - 0x20;

        return;
    }
}
