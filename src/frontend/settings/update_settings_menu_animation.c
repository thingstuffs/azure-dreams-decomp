#include "frontend/settings/controller_body.h"
#include "modules/main_title_callbacks.h"
#include "common.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "frontend/settings.h"
#include "engine/effect/screen_fade.h"
#include "main/data.h"

#ifndef NULL
#define NULL 0
#endif

extern u8 animation_tick_scale[];

extern short SD_Call(int flags);
extern void *allocate_flagged_object_node(s32 flags);
extern void reset_game_state_preserving_session_fields(void);
extern void request_scene_dispatch_state(s16 requested_state);
extern void func_80089c24();

/* Updates menu animation, selection, and idle demo transitions. */
void update_settings_menu_animation(SettingsMenuBody *obj, s32 *position) {
    int frames_left;
    int slot;
    u16 next_state;
    void *child;
    GameWork *input = &g_game_work;

    frames_left = obj->counter - 1;
    obj->counter = frames_left;

    switch (obj->state) {
    case 0:
        if ((input->pressed_buttons) != 0) {
            obj->state = 16;
            return;
        }
        if ((s16) render_screen_fade_decreasing_intensity(&obj->fade)) {
            obj->flags &= ~1;
            obj->state = 1;
        }
        return;

    case 1:
        if (input->buttons != 0) {
            obj->state = 16;
            return;
        }
        position[1] += 0xFFFEC000;
        if (*(s16 *) ((u8 *) position + 6) >= 0) {
            return;
        }
        position[1] = 0;
        obj->counter = 105;
        obj->state = 2;
        return;

    case 2:
        if (input->buttons != 0) {
            obj->state = 19;
            return;
        }
        if ((s16) frames_left > 0) {
            return;
        }
        for (slot = 2; slot >= 0; slot--) {
            obj->slotsA[slot]->state = 1;
        }
        for (slot = 1; slot >= 0; slot--) {
            obj->slotsB[slot]->state = 1;
        }
        obj->counter = 95;
        obj->state = 3;
        return;

    case 3:
        if (input->buttons != 0) {
            obj->state = 19;
        }
        if ((s16) obj->counter > 0) {
            return;
        }
        obj->counter = 1800;
        obj->state = 4;
        return;

    case 4:
        if (input->buttons != 0) {
            obj->counter = 1800;
        }
        if ((input->pressed_buttons) & 0x1000) {
            obj->selected_item = (s16) ((obj->selected_item + 2) % 3);
        } else if ((input->pressed_buttons) & 0x4000) {
            obj->selected_item = (s16) ((obj->selected_item + 1) % 3);
        }
        if ((input->pressed_buttons) & 0x840) {
            SD_Call(obj->selected_item == 2 ? 1314 : 1306);
            obj->counter = 96;
            obj->state = 32;
            return;
        }
        if ((s16) obj->counter > 0) {
            return;
        }
        obj->state = 254;
        return;

    case 16:
        obj->fade.unk_2 = 0;
        obj->fade.param = 8;
        obj->state = 17;
                        /* fallthrough */
    case 17:
        if ((s16) render_screen_fade_increasing_intensity(&obj->fade)) {
            position[1] = 0;
            obj->fade.unk_2 = 0;
            obj->state = 18;
        }
        return;

    case 18:
        if ((s16) render_screen_fade_decreasing_intensity(&obj->fade)) {
            obj->fade.unk_2 = 0;
            obj->state = 19;
        }
        return;

    case 19:
        for (slot = 2; slot >= 0; slot--) {
            obj->slotsA[slot]->state = 16;
        }
        for (slot = 1; slot >= 0; slot--) {
            obj->slotsB[slot]->state = 2;
        }
        obj->counter = 1800;
        obj->state = 4;
        return;

    case 32:
        if ((s16) frames_left > 0) {
            return;
        }
        {
            u16 flags = obj->flags;
            animation_tick_scale[0] = 2;
            obj->flags = flags | 1;
        }
        switch (obj->selected_item) {
        case 0:
            child = allocate_flagged_object_node(256);
            if (child == NULL) {
                next_state = 255;
                obj->state = next_state;
                break;
            }
            *(void **) ((u8 *) child + 16) = (void *) assign_object_descriptor_on_check;
            obj->state = 253;
            break;
        case 1:
        {
            u8 *globals_base;
            u16 mode_value;
            u16 phase_value;
            globals_base = (u8 *) 0x80010000;
            mode_value = 5;
            phase_value = 2;
            reset_game_state_preserving_session_fields();
            *(s16 *) (globals_base + 0x2094) = mode_value;
            *(globals_base + 0x2D6E) = 0;
            *(s16 *) (globals_base + 0x2098) = phase_value;
            request_scene_dispatch_state(6);
            next_state = 255;
            obj->state = next_state;
            break;
        }
        case 2:
            obj->state = 253;
            func_80089c24();
            break;
        default:
            next_state = 255;
            obj->state = next_state;
            break;
        }
        return;

    case 253:
        animation_tick_scale[0] = 2;
        ((u16 *) obj)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;

    case 254:
    {
        u8 demo_index;
        animation_tick_scale[0] = 2;
        demo_index = attract_scene_index[0];
        switch (demo_index & 7) {
        case 0:
        case 4:
            request_scene_dispatch_state(30);
            break;
        case 2:
        case 6:
            request_scene_dispatch_state(32);
            break;
        case 1:
            request_scene_dispatch_state(18);
            break;
        case 3:
            request_scene_dispatch_state(19);
            break;
        case 5:
            request_scene_dispatch_state(20);
            break;
        case 7:
            request_scene_dispatch_state(21);
            break;
        }
        {
            u8 next_demo = attract_scene_index[0];
            u16 flags = obj->flags;
            obj->state = 255;
            next_demo = (next_demo + 1) & 7;
            flags |= 1;
            attract_scene_index[0] = next_demo;
            obj->flags = flags;
        }
        return;
    }

    case 255:
        break;

    default:
        return;
    }
}
