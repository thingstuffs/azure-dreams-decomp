#include "modules/dungeon_ovl_1829800.h"

void draw_and_restore_fading_object(void *object_arg, void *position_arg, void *sprite_arg) {
    s16 move_ticks;
    s32 start_y;
    s32 move_ticks_left;
    s32 draw_scale;
    s32 direction;
    s8 fade_out_ticks;
    s8 fade_out_left;
    s8 state;
    u16 saved_render_value;
    u16 update_count;
    u8 fade_in_left;
    u8 fade_out_level;
    u8 next_fade_out;
    u8 fade_in_level;
    u8 next_fade_in;
    s32 red;
    s32 green;
    s32 blue;
    u16 *direction_table;
    S_80025C94_1 *motion;
    S_80025C94_0 *object;
    S_80025C94_2 *sprite;
    S_80025C94_3 *position;
    S_80025C94_5 *appearance;
    GameWork *render_context;
    void *object_ptr;
    void *fade_in_ticks;

    update_count = (*(u16 *)D_8002715C);
    object_ptr = object_arg;
    motion = object_ptr;
    position = position_arg;
    sprite = sprite_arg;
    object = motion;
    (*(u16 *)D_8002715C) = update_count + 1;
    render_context = &g_game_work;
    state = object->unk_72.s;
    switch (state) {
    case 0:
        sprite->unk_1E = 0x1000;
        sprite->unk_1C = 0x1000;
        sprite->unk_0E = 0U;
        sprite->unk_0D = 0U;
        sprite->unk_0C = 0U;
        object->unk_73.s = 8;
        object->unk_2A = 0x400;
        direction_table = (u16 *)0x80010000;
        direction = (((S_80025C94_6 *)((s8 *)direction_table + (object->unk_6A * 2)))->unk_2094 + 2) & 7;
        position->unk_00.at02.v = D_800DCEAC[direction];
        start_y = D_800DCEBC[direction];
        position->unk_0A = 0;
        position->unk_04.at02.v = start_y;
        sprite->unk_24 = (u8) (((s8 *)dir_step_x)[direction * 2] + 1);
        sprite->unk_25 = (u8) (((s8 *)dir_step_y)[direction * 2] + 1);
        object->unk_72.s = (s8) ((u8) object->unk_72.s + 1);
    case 1:
        fade_in_ticks = (void *) object->unk_73.s;
        if (fade_in_ticks != NULL) {
            fade_in_level = sprite->unk_0E;
            next_fade_in = fade_in_level + ((s32) (0x80 - fade_in_level) / (s32) fade_in_ticks);
            sprite->unk_0E = next_fade_in;
            sprite->unk_0D = next_fade_in;
            sprite->unk_0C = next_fade_in;
        }
        fade_in_left = object->unk_73.u - 1;
        object->unk_73.u = fade_in_left;
        if ((fade_in_left << 0x18) <= 0) {
            sprite->unk_0E = 0x80U;
            sprite->unk_0D = 0x80U;
            sprite->unk_0C = 0x80U;
            object->unk_73.u = 0U;
            object->unk_72.u = (u8) (object->unk_72.u + 1);
        }
    case 2:
        if (D_8002715A != 0) {
            object->unk_73.u = 8U;
            position->unk_16 = 8;
            object->unk_72.u = (u8) (object->unk_72.u + 1);
        }
        break;
    case 3:
        fade_out_ticks = object->unk_73.s;
        if (fade_out_ticks != 0) {
            fade_out_level = sprite->unk_0E;
            next_fade_out = fade_out_level + ((s32) (0 - fade_out_level) / fade_out_ticks);
            sprite->unk_0E = next_fade_out;
            sprite->unk_0D = next_fade_out;
            sprite->unk_0C = next_fade_out;
        }
        fade_out_left = (u8) object->unk_73.s - 1;
        object->unk_73.s = fade_out_left;
        if ((fade_out_left << 0x18) <= 0) {
            object->unk_72.u = (u8) (object->unk_72.u + 1);
        }
        break;
    default:
        motion->unk_96 = 0;
        return;
    }
    move_ticks = motion->unk_96;
    if (move_ticks != 0) {
        position->unk_00.at00.v = (s32) (position->unk_00.at00.v + ((s32) ((((sprite->unk_24 - 1) << 6)
            - (s16) position->unk_00.at02.v) << 0x10) / move_ticks));
        position->unk_04.at00.v = (s32) (position->unk_04.at00.v + ((s32) ((((sprite->unk_25 - 1) << 6)
            - (s16) position->unk_04.at02.v) << 0x10) / (s16) motion->unk_96));
        move_ticks_left = (u16) motion->unk_96 - 1;
        motion->unk_96 = move_ticks_left;
        if ((move_ticks_left << 0x10) <= 0) {
            motion->unk_96 = 0;
        }
    }
    if (object->unk_14 & 0x40000) {
        motion->unk_92 = -0x20;
    } else {
        motion->unk_92 = 0;
    }
    motion->unk_9D = 0;
    appearance = ((S_80025C94_7_pre *)(object->unk_58))[-1].unk_00;
    saved_render_value = ((u16)render_context->view.viewAngle);
    render_context->view.viewAngle = (u16) appearance->unk_1A;
    sprite->unk_14 = (u16) (sprite->unk_14 & 0xFFBF);
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v + 0x100);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v + 0x100);
    if ((*(s16 *)D_80027158) == object->unk_6A) {
        draw_scale = ((*(s16 *)D_80027156) << 9) + 0x400;
        object->unk_2A = draw_scale;
    } else {
        object->unk_2A = 0x400;
    }
    object->unk_5C(motion, position, sprite, motion);
    position->unk_00.at02.v = (u16) (position->unk_00.at02.v - 0x100);
    position->unk_04.at02.v = (u16) (position->unk_04.at02.v - 0x100);
    render_context->view.viewAngle = saved_render_value;
    object->unk_88 = 0;
    red = appearance->unk_0C;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        red = red >> 1;
    }
    sprite->unk_0C = red;
    green = appearance->unk_0D;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        green = green >> 1;
    }
    sprite->unk_0D = green;
    blue = appearance->unk_0E;
    if (object->unk_6A != ((S_80025C94_7 *)(object->unk_58))->unk_26) {
        blue = blue >> 1;
    }
    sprite->unk_0E = blue;
    return;
}
