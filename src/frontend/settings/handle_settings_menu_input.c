#include "shared/game_work.h"
#include "shared/object_flags.h"

typedef unsigned char u8;
typedef signed char s8;
typedef unsigned short u16;
typedef short s16;
typedef unsigned int u32;
typedef int s32;
typedef struct Gfx
{
    u8 pad0[0x3180];
    s32 color;
    u8 shade;
    u8 pad5;
    u8 flags;
    u8 pad7;
}
Gfx;
typedef struct Menu
{
    s16 pad0;
    s16 f2;
    s16 f4;
    s16 pad6;
    s16 state;
    s16 timer;
    s16 row;
    s16 red;
    s16 green;
    s16 blue;
    u16 shade;
    u16 flags;
}
Menu;
extern u8 animation_tick_scale;
extern u8 runtime_state_restore_requested;
extern s32 saved_cd_playback_volume_scale;
extern s32 saved_sequence_volume_scale;
extern s32 saved_voice_gain_scale;
extern s32 volume_slider_levels[3];
extern s32 runtime_saved_state_word;
extern s32 render_screen_fade_decreasing_intensity();
extern s32 render_screen_fade_increasing_intensity();
extern void SD_Call();
extern void sound_set_cd_playback_volume_scale();
extern void sound_set_sequence_volume_scale();
extern void sound_set_voice_gain_scale();
extern void create_settings_controller();
/* Handles the options menu, adjusting audio levels and applying display settings. */
void handle_settings_menu_input(Menu *menu)
{
    GameWork *pad;
    s32 buttons;
    s32 delta;
    s32 row;
    s32 adjusted_value;
    s32 *level_slot;
    s32 *levels;
    s32 level;
    s32 *volume_a;
    ObjectFlagBlock *settings_flags;
    s32 *volume_c;
    s32 *volume_b;
    s16 *color_base;
    s32 scaled_a;
    s32 green_bits;
    s32 volume_or_red;
    s32 shade;
    s32 blue_bits;
    s32 red_green;
    u16 menu_flags;
    u16 new_flags;
    s32 channel_or_color;
    s32 blue;
    s32 scaled_b;
    animation_tick_scale = 1;
    pad = &g_game_work;
    switch (menu->state) {
    case 0:
        menu->state = ((u16) menu->state) + 1;

    case 1:
        if ((render_screen_fade_decreasing_intensity(menu) << 16) == 0) {
            return;
        }
        menu->timer = 300;
        menu->state = ((u16) menu->state) + 1;
        return;

    case 2:
        buttons = (pad->pressed_buttons);
        if (buttons & 0x1000) {
            SD_Call(0x502);
            menu->row = (menu->row + 6) % 7;
        }
        else if (buttons & 0x4000) {
            SD_Call(0x502);
            menu->row = (menu->row + 1) % 7;
        }
        else if (buttons & 0xA000) {
            if (menu->row == 0) {
                SD_Call(0x502);
                menu_flags = menu->flags;
                if (menu_flags & 2) {
                    new_flags = menu_flags & 0xFFFD;
                }
                else {
                    new_flags = menu_flags | 2;
                }
                menu->flags = new_flags;
            }
        }
        buttons = pad->buttons;
        delta = -8;
        if (!(buttons & 0x8000)) {
            delta = ((buttons & 0x2000) != 0) * 8;
        }
        if (delta != 0) {
            row = menu->row;
            switch (row) {
            case 1:
            case 2:
            case 3:
                channel_or_color = row - 1;
                levels = volume_slider_levels;

                level_slot = levels + channel_or_color;
                adjusted_value = *level_slot + delta;
                *level_slot = adjusted_value;
                if (adjusted_value < 0) {
                    *level_slot = 0;
                }
                else if (adjusted_value >= 0x101) {
                    *level_slot = 0x100;
                }
                if (channel_or_color == 1) {
                    SD_Call(0x516);
                }
                volume_a = &saved_sequence_volume_scale;
                scaled_a = 0x7FFF;
                level = volume_slider_levels[0];
                if (level < 0x100) {
                    scaled_a = level << 7;
                }
                scaled_b = 0x7FFF;
                do {
                    *volume_a = scaled_a;
                }
                while (0);
                volume_b = &saved_voice_gain_scale;
                level = volume_slider_levels[1];
                if (level < 0x100) {
                    scaled_b = level << 7;
                }
                *volume_b = scaled_b;
                volume_c = &saved_cd_playback_volume_scale;
                volume_or_red = 0x7FFF;
                level = volume_slider_levels[2];
                if (level < 0x100) {
                    volume_or_red = level << 7;
                }
                *volume_c = volume_or_red;
                sound_set_sequence_volume_scale(*((s16 *) volume_a));
                sound_set_voice_gain_scale(*((s16 *) volume_b));
                sound_set_cd_playback_volume_scale(*((s16 *) (&saved_cd_playback_volume_scale)));
                break;
            case 4:
            case 5:
            case 6:
                channel_or_color = menu->row - 4;
                color_base = (s16 *) ((u32) (channel_or_color * 2) + (u32) menu);

                adjusted_value = ((u16) color_base[7]) + delta;
                color_base[7] = adjusted_value;
                adjusted_value = (s16) adjusted_value;
                if (adjusted_value < 0) {
                    color_base[7] = 0;
                }
                else if (adjusted_value >= 0x101) {
                    color_base[7] = 0x100;
                }
                break;
            }
        }

        if ((pad->buttons & 9) == 9) {
            if ((pad->pressed_buttons) & 2) {
                menu->shade = (menu->shade + 1) & 3;
            }
        }

        if (!((pad->pressed_buttons) & 0x840)) {
            return;
        }
        shade = (s16) menu->shade;
        delta = shade << 5;
        channel_or_color = ((Gfx *) 0x80010000)->color & 0xFF000000;
        volume_or_red = 0xFF;
        if (menu->red < 0x100) {
            volume_or_red = menu->red;
        }
        level = menu->green;
        green_bits = level < 0x100;
        if (green_bits) {
            green_bits = level << 8;
        }
        else {
            green_bits = 0xFF00;
        }
        red_green = volume_or_red + green_bits;
        do {
            blue = menu->blue;
        }
        while (0);
        if (blue < 0x100) {
            channel_or_color = channel_or_color + (red_green + (blue << 16));
        }
        else {
            blue_bits = channel_or_color + 0xFF0000;
            channel_or_color = blue_bits + red_green;
        }
        if (((Gfx *) 0x80010000)->shade != delta) {
            runtime_state_restore_requested = 1;
        }
        if (((Gfx *) 0x80010000)->color != channel_or_color) {
            runtime_state_restore_requested = 1;
        }
        if (menu->flags & 2) {
            if (((Gfx *) 0x80010000)->flags & 1) {
                runtime_state_restore_requested = 1;
            }
        }
        else if (!(((Gfx *) 0x80010000)->flags & 1)) {
            runtime_state_restore_requested = 1;
        }
        if (runtime_state_restore_requested == 1) {
            ((Gfx *) 0x80010000)->shade = delta;
            object_flag_block.unk_0C = delta;
            ((Gfx *) 0x80010000)->color = channel_or_color;
            runtime_saved_state_word = channel_or_color;
            if (menu->flags & 2) {
                ((Gfx *) 0x80010000)->flags = ((Gfx *) 0x80010000)->flags & 0xFE;
            }
            else {
                ((Gfx *) 0x80010000)->flags = ((Gfx *) 0x80010000)->flags | 1;
            }
            object_flag_block.unk_04 = ((Gfx *) 0x80010000)->flags;
        }
        menu->flags = menu->flags | 0x8000;
        menu->state = ((u16) menu->state) + 1;
        return;

    case 3:
        SD_Call(0x1200);
        menu->f2 = 0;
        menu->f4 = 0x10;
        menu->state = ((u16) menu->state) + 1;

    case 4:
        if ((render_screen_fade_increasing_intensity(menu) << 16) == 0) {
            return;
        }
        create_settings_controller();
        settings_flags = &object_flag_block;
        ((u16 *) menu)[-1] |= 0x8000;
        settings_flags->flags |= 0x8000;
        return;

    }

}
