#include "frontend/settings/initialization.h"
#include "shared/entity.h"
/* Settings-screen object creation and initialization, with a helper for copying two words. */
#include "modules/main_title_callbacks.h"
#include "shared/object_node.h"
/* cfail-repair: tf7-phase1-cache-v3 */
#include "common.h"
#include "m2c_compat.h"
#include "engine/node.h"
#include "frontend/settings.h"
#include "engine/effect/screen_fade.h"
#include "main/data.h"
#include "sdk/libgpu.h"
#include "slus.h"
#include "shared/entity.h"

typedef struct Sol9Copy8 {
    u8 bytes[8];
} Sol9Copy8;

/* Copies the Sol9Copy8 record to the destination; the size argument is unused. */
static inline void sol9_copy8(void *dst, const void *src, s32 ignored_size) {
    *(Sol9Copy8 *)dst = *(const Sol9Copy8 *)src;
    (void)ignored_size;
}

                      /* extern */
extern M2C_UNK card_selection_display_data;
extern s8 animation_tick_scale;
extern s32 saved_cd_playback_volume_scale;
extern s32 saved_sequence_volume_scale;
extern s32 saved_voice_gain_scale;
extern s32 volume_slider_levels[3];

/* Initializes the settings screen palette, labels, panels, and sliders. */
void initialize_settings_screen(void) {
    SettingsInitializationFrame frame;
    s32 heading_x;
    s32 heading_y;
    s32 panel_x_fixed;
    s32 panel_y_fixed;
    s32 next_slider;
    s32 footer_text;
    s32 top_text;
    s32 choice_text;
    s32 middle_text;
    s32 choice_heading;
    s32 bottom_text;
    s32 channel_text;
    s32 next_channel;
    s32 second_level;
    s32 first_level;
    s32 palette_mask;
    s32 *levels;
    s32 descriptor_color;
    register s32 index;
    s32 item_index;
    s32 third_level;
    register ObjectNodeHeader *screen_object;
    void *settings;

    settings = NULL;
    sol9_copy8(frame.bytes + 0x270, &settings_palette_rect, 8);
    first_level = 0x100;
    animation_tick_scale = 1;
    levels = volume_slider_levels;
    if (saved_sequence_volume_scale != 0x7FFF) {
        first_level = (s32) saved_sequence_volume_scale >> 7;
    }
    second_level = 0x100;
    levels[0] = first_level;
    if (saved_voice_gain_scale != 0x7FFF) {
        second_level = (s32) saved_voice_gain_scale >> 7;
    }
    third_level = 0x100;
    levels[1] = second_level;
    if (saved_cd_playback_volume_scale != 0x7FFF) {
        third_level = (s32) saved_cd_playback_volume_scale >> 7;
    }
    levels[2] = third_level;
    SD_Call(0x200);
    StoreImage(frame.bytes + 0x270, frame.bytes + 0x70);
    DrawSync(0);
    index = 0xFF;
    palette_mask = ~0x7FFF;
    do {
        frame.fields.palette[index] = frame.fields.palette[index] | palette_mask;
        index -= 1;
    } while (index >= 0);
    LoadImage(frame.bytes + 0x270, frame.bytes + 0x70);
    screen_object = allocate_flagged_object_node(0x11);
    if (screen_object != NULL) {
        screen_object->update_callback = (void *)handle_settings_menu_input;
        register_node(screen_object, build_settings_sprite_tiles);
        settings = ((void *)screen_object) + 0x20;
        screen_object->position->y.w.i = 0xF0;
        (*(s16 *)((u8 *)settings + 4)) = 0x20;
        (*(s16 *)((u8 *)settings + 0x14)) = (s16) ((u8) D_80013184 >> 5);
        index = 2;
        (*(s16 *)((u8 *)settings + 0xE)) = (s16) D_80013180;
        (*(s16 *)((u8 *)settings + 0x10)) = (s16) D_80013181;
        ((SettingsScreenBody *)settings)->blue = (s16) D_80013182;
        do {
            if (*(s16 *)((u8 *)settings + index * 2 + 14) >= 0xFF) {
                *(s16 *)((u8 *)settings + index * 2 + 14) = 0x100;
            }
            index -= 1;
        } while (index >= 0);
        if ((D_80013186 & 1) == 0) {
            ((SettingsScreenBody *)settings)->flags = (u16) (((SettingsScreenBody *)settings)->flags | 2);
        } else {
            ((SettingsScreenBody *)settings)->flags = (u16) (((SettingsScreenBody *)settings)->flags & 0xFFFD);
        }
    }
    render_screen_fade_decreasing_intensity(settings);
    panel_x_fixed = 0x400000;
    panel_y_fixed = 0xA00000;
    frame.fields.x.v = panel_x_fixed;
    frame.fields.y.v = panel_y_fixed;
    create_type(frame.bytes, &D_8008AC70, &D_80078AF0, settings);
    heading_x = 0x94;
    heading_y = 0x44;
    frame.fields.x.w.i = heading_x;
    frame.fields.y.w.i = heading_y;
    create_type(frame.bytes, set_output, &card_selection_display_data, settings);
    frame.fields.label.y = 0xD0;
    frame.fields.label.style = 1;
    frame.fields.label.extra = 0;
    frame.fields.label.font = 0x7C80;
    frame.fields.label.color = 0x808080;
    index = 0x1A;
    frame.fields.label.owner = settings;
    frame.fields.label.flags = 0;
    do {
        frame.fields.label.x = index * 8 + 48;
        footer_text = D_8008B2FC[index];
        frame.fields.label.order = index * 2 + 30;
        frame.fields.label.text = footer_text;
        initialize_and_submit_record(cycle_owner_effect_color, &frame.fields.label.flags);
        index -= 1;
    } while (index >= 0);
    frame.fields.label.x = 0x74;
    frame.fields.label.y = 0xC;
    frame.fields.label.text = D_8008B2B0;
    initialize_and_submit_record(&D_8008B030, &frame.fields.label.flags);
    index = 0;
    frame.fields.label.x = 0x20;
    do {
        frame.fields.label.y = index * 0xC + 0x20;
        top_text = (&D_8008B2B4)[index];
        frame.fields.label.text = top_text;
        initialize_and_submit_record(&D_8008B030, &frame.fields.label.flags);
        index += 1;
    } while (index < 2);
    item_index = 0;
    frame.fields.label.y -= 6;
    do {
        frame.fields.label.value = 0;
        frame.fields.label.index = item_index;
        frame.fields.label.x = item_index * 0x40 + 0xBE;
        choice_text = (&D_8008B2BC)[item_index];
        frame.fields.label.text = choice_text;
        initialize_and_submit_record(update_settings_effect_color, &frame.fields.label.flags);
        item_index += 1;
    } while (item_index < 2);
    frame.fields.label.x = 0x20;
    item_index = 3;
    do {
        frame.fields.label.y = item_index * 0xC + 0x40;
        middle_text = D_8008B2C4[item_index];
        frame.fields.label.text = middle_text;
        initialize_and_submit_record(&D_8008B030, &frame.fields.label.flags);
        item_index -= 1;
    } while (item_index >= 0);
    item_index = 1;
    do {
        frame.fields.label.x = item_index * 0x40 + 0xBE;
        choice_heading = D_8008B2D4[item_index];
        frame.fields.label.text = choice_heading;
        initialize_and_submit_record(&D_8008B030, &frame.fields.label.flags);
        item_index -= 1;
    } while (item_index >= 0);
    frame.fields.label.x = 0x20;
    item_index = 0;
    do {
        frame.fields.label.y = item_index * 0xC + 0x78;
        bottom_text = (&D_8008B2DC)[item_index];
        frame.fields.label.text = bottom_text;
        initialize_and_submit_record(&D_8008B030, &frame.fields.label.flags);
        item_index += 1;
    } while (item_index < 2);
    frame.fields.label.x = 0xB2;
    item_index = 2;
    do {
        frame.fields.label.y = item_index * 0xC + 0x7E;
        channel_text = D_8008B2E4[item_index];
        frame.fields.label.text = channel_text;
        initialize_and_submit_record(&D_8008B030, &frame.fields.label.flags);
        item_index -= 1;
    } while (item_index >= 0);
    frame.fields.panel.x = 0x1C;
    frame.fields.panel.width = 0x100;
    frame.fields.panel.style = 2;
    frame.fields.panel.shading = 1;
    descriptor_color = 0x202020;
    frame.fields.panel.color = descriptor_color;
    frame.fields.panel.flags = 0;
    frame.fields.panel.owner = settings;
    frame.fields.panel.height = 0x1C;
    frame.fields.panel.y = 0x1C;
    initialize_available(propagate_record_high_bit, &frame.fields.panel.flags);
    frame.fields.panel.height = 0x34;
    frame.fields.panel.y = 0x3C;
    initialize_available(propagate_record_high_bit, &frame.fields.panel.flags);
    frame.fields.panel.height = 0x2E;
    frame.fields.panel.y = 0x74;
    initialize_available(propagate_record_high_bit, &frame.fields.panel.flags);
    frame.fields.panel.x = 0x20;
    frame.fields.panel.y = 0xA6;
    frame.fields.panel.width = 0x40;
    frame.fields.panel.height = 0x18;
    initialize_available(pack_three_capped_components_and_flag, &frame.fields.panel.flags);
    frame.fields.panel.x = 0xCA;
    frame.fields.panel.height = 8;
    frame.fields.panel.width = 0x40;
    frame.fields.panel.shading = 0;
    frame.fields.panel.index = 2;
    do {
        frame.fields.panel.color = 0xFF << (frame.fields.panel.index * 8);
        frame.fields.panel.y = (frame.fields.panel.index * 0xC) + 0x7E;
        initialize_available(load_indexed, &frame.fields.panel.flags);
        next_channel = frame.fields.panel.index - 1;
        frame.fields.panel.index = next_channel;
    } while (next_channel >= 0);
    frame.fields.panel.height = 8;
    frame.fields.panel.color = 0xFFFFFF;
    frame.fields.panel.style = 0;
    frame.fields.panel.shading = 0;
    frame.fields.panel.index = 2;
    do {
        frame.fields.panel.y = ((frame.fields.panel.index + 1) * 0xC) + 0x40;
        initialize_available(load_table, &frame.fields.panel.flags);
        next_slider = frame.fields.panel.index - 1;
        frame.fields.panel.index = next_slider;
    } while (next_slider >= 0);
}
