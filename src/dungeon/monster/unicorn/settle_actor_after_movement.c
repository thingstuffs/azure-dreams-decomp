#include "dungeon/monster/unicorn/settle_actor_after_movement.h"

/* Advance the actor movement animation and settle it onto its destination tile. */
void settle_actor_after_movement(void *animation, void *motion, void *sprite, void *actor)
{
    s32 direction_x;
    s32 direction_y;
    s32 direction_offset;
    s32 state;
    s32 next_state;

    direction_offset = ((u16)((T_80172664_S_80172664_0 *)actor)->unk_2A >> 8) & 0xE;
    direction_x = *(s16 *)((u8 *)((s8 *)dir_step_x) + direction_offset);
    direction_y = *(s16 *)((u8 *)((s8 *)dir_step_y) + direction_offset);
    ((T_80172664_S_80172664_1 *)animation)->unk_96.s--;
    state = ((T_80172664_S_80172664_1 *)animation)->unk_9B;

    switch (state) {
    case 0:
        if (((T_80172664_S_80172664_2 *)sprite)->unk_14 & 0x8000) {
            ((T_80172664_S_80172664_1 *)animation)->unk_9B = 0xFF;
            ((T_80172664_S_80172664_2 *)sprite)->unk_14 |= 0x6000;
            resolve_attack_damage_and_effects(actor, sprite, ((T_80172664_S_80172664_0 *)actor)->unk_2A, 1);
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_80174D7C;
        select_sprite_entry(
            sprite,
            *(&D_80174D7C +
              (((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172664_S_80172664_0 *)actor)->unk_2A + 0x100) >> 9) & 7)),
            0);
        {
            s32 shifted_x = direction_x << 19;
            ((T_80172664_S_80172664_3 *)motion)->unk_0C = (direction_x << 17) - shifted_x;
        }
        {
            s32 shifted_y = direction_y << 19;
            ((T_80172664_S_80172664_3 *)motion)->unk_10 = (direction_y << 17) - shifted_y;
        }
        ((T_80172664_S_80172664_1 *)animation)->unk_98 |= 8;
        ((T_80172664_S_80172664_0 *)actor)->unk_1C &= 0xF7FFFFFF;
        ((T_80172664_S_80172664_1 *)animation)->unk_96.s = 4;
        ((T_80172664_S_80172664_3 *)motion)->unk_14 = (s32)0xFFFC0000;
        ((T_80172664_S_80172664_1 *)animation)->unk_9B = ((T_80172664_S_80172664_1 *)animation)->unk_9B + 1;
        return;

    case 1:
        ((T_80172664_S_80172664_1 *)animation)->unk_90 += ((T_80172664_S_80172664_3 *)motion)->unk_14;
        ((T_80172664_S_80172664_3 *)motion)->unk_14 += ((T_80172664_S_80172664_3 *)motion)->unk_14 >> 2;
        if (((T_80172664_S_80172664_1 *)animation)->unk_96.u > 0) {
            return;
        }

        (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_80174D84;
        select_sprite_entry(
            sprite,
            *(&D_80174D84 +
              (((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172664_S_80172664_0 *)actor)->unk_2A + 0x100) >> 9) & 7)),
            0);
        next_state = ((T_80172664_S_80172664_1 *)animation)->unk_9B;
        ((T_80172664_S_80172664_1 *)animation)->unk_96.s = 8;
        ((T_80172664_S_80172664_1 *)animation)->unk_9B = next_state + 1;
        return;

    case 2:
    {
        s32 velocity_x = ((T_80172664_S_80172664_3 *)motion)->unk_0C;
        s32 velocity_y = ((T_80172664_S_80172664_3 *)motion)->unk_10;
        s32 velocity_z = ((T_80172664_S_80172664_3 *)motion)->unk_14;

        ((T_80172664_S_80172664_3 *)motion)->unk_0C = velocity_x - (velocity_x >> 3);
        ((T_80172664_S_80172664_3 *)motion)->unk_10 = velocity_y - (velocity_y >> 3);
        ((T_80172664_S_80172664_3 *)motion)->unk_14 = velocity_z - (velocity_z >> 3);
    }
        if (((T_80172664_S_80172664_1 *)animation)->unk_96.u == 4) {
            ((T_80172664_S_80172664_3 *)motion)->unk_0C = 0;
            ((T_80172664_S_80172664_3 *)motion)->unk_10 = 0;
            ((T_80172664_S_80172664_3 *)motion)->unk_14 = 0;
        }
        if (((T_80172664_S_80172664_1 *)animation)->unk_96.u > 0) {
            return;
        }
        ((T_80172664_S_80172664_1 *)animation)->unk_96.s = 4;
        ((T_80172664_S_80172664_3 *)motion)->unk_0C = direction_x << 18;
        ((T_80172664_S_80172664_3 *)motion)->unk_10 = direction_y << 18;
        play_sound_if_enabled(0x809);
        ((T_80172664_S_80172664_1 *)animation)->unk_9B = ((T_80172664_S_80172664_1 *)animation)->unk_9B + 1;
        return;

    case 3:
        ((T_80172664_S_80172664_1 *)animation)->unk_90 += 0xC0000;
        ((T_80172664_S_80172664_3 *)motion)->unk_0C += direction_x << 18;
        ((T_80172664_S_80172664_3 *)motion)->unk_10 += direction_y << 18;
        if (((T_80172664_S_80172664_1 *)animation)->unk_96.u > 0) {
            return;
        }
        resolve_attack_damage_and_effects(actor, sprite, ((T_80172664_S_80172664_0 *)actor)->unk_2A, 1);
        ((T_80172664_S_80172664_1 *)animation)->unk_9B = ((T_80172664_S_80172664_1 *)animation)->unk_9B + 1;
        return;

    case 4:
        ((T_80172664_S_80172664_1 *)animation)->unk_90 += 0xC0000;
        if (!(((T_80172664_S_80172664_2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        (*(u8 * *)((u8 *)sprite + 0x2C)) = &D_80174D8C;
        select_sprite_entry(
            sprite,
            *(&D_80174D8C +
              (((g_game_work.view.camera_rotation.parts.viewAngle + ((T_80172664_S_80172664_0 *)actor)->unk_2A + 0x100) >> 9) & 7)),
            0);
        ((T_80172664_S_80172664_3 *)motion)->unk_14 = 0;
        ((T_80172664_S_80172664_1 *)animation)->unk_90 = 0;
        ((T_80172664_S_80172664_1 *)animation)->unk_98 &= 0xFFF7;
        ((T_80172664_S_80172664_0 *)actor)->unk_1C |= 0x08000000;
        ((T_80172664_S_80172664_1 *)animation)->unk_9B = 0xFF;
        return;

    case 0xFF:
    {
        s32 tile_x = ((T_80172664_S_80172664_2 *)sprite)->unk_24 << 6;
        s32 position_x = ((T_80172664_S_80172664_3 *)motion)->unk_02 - 0x20;
        ((T_80172664_S_80172664_3 *)motion)->unk_0C = ((tile_x - position_x) << 15) >> 1;
    }
        {
            s32 tile_y = ((T_80172664_S_80172664_2 *)sprite)->unk_25 << 6;
            s32 position_y = ((T_80172664_S_80172664_3 *)motion)->unk_06 - 0x20;
            ((T_80172664_S_80172664_3 *)motion)->unk_10 = ((tile_y - position_y) << 15) >> 1;
        }
        if (!(((T_80172664_S_80172664_2 *)sprite)->unk_14 & 0xE000)) {
            return;
        }
        ((T_80172664_S_80172664_3 *)motion)->unk_10 = 0;
        ((T_80172664_S_80172664_3 *)motion)->unk_0C = 0;
        set_record_integer_tile_center(motion, ((T_80172664_S_80172664_2 *)sprite)->unk_24, ((T_80172664_S_80172664_2 *)sprite)->unk_25);
        reduce_actor_food_meter(actor, 0x100);
        ((T_80172664_S_80172664_1 *)animation)->unk_8C = &D_80170E7C;
        g_dungeon_status.active_actor = 0;
        advance_status_timers(actor);
        if (((T_80172664_S_80172664_0 *)actor)->unk_6D == 0) {
            ((T_80172664_S_80172664_0 *)actor)->unk_46 &= 0x7FFF;
        } else {
            D_800E3DE8 = (u8 *)actor - 0x20;
        }

    }
}
