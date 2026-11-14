#include "dungeon/level/floor_flags.h"
#include "shared/actor_status_flags.h"
#include "common.h"
#include "shared/dungeon_floor.h"
#include "shared/tile_object.h"
#include "shared/record_ptrs.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "dungeon/menu.h"
#include "dungeon/system.h"
#include "dungeon/player/object/action_state.h"




typedef struct S_func_8009E038_3 {
    s32 unk_00;
} S_func_8009E038_3;

typedef struct S_func_8009E038_6 {
    u8 pad_00[0x296C];
    s32 unk_296C;
} S_func_8009E038_6;

typedef struct S_func_8009E038_8 {
    u8 pad_00[0x3630];
    s16 unk_3630;
    s16 unk_3632;
    s16 unk_3634;
    s16 unk_3636;
} S_func_8009E038_8;

enum ViewportState {
    VIEWPORT_RESET = 0,
    VIEWPORT_HOLD = 1,
    VIEWPORT_FOLLOW = 0x10,
    VIEWPORT_SHRINK = 0x20,
    VIEWPORT_RESUME = 0x30,
};

/* Update the viewport transition, blending its bounds, center, scale, and brightness. */
void update_viewport_transition(InactiveTypeTwelveObjectBody *transition, ObjectPosition *center, SpriteFrameState *render_params,
    s32 *context) {
    s32 top_step;
    GameWork *input;
    s16 reset_frames;
    s16 move_frames;
    s16 next_scale;
    s16 reset_remaining;
    s16 hold_remaining;
    s32 state;
    s16 move_remaining;
    s32 current_scale;
    s32 height_step;
    s32 flags;
    s32 cleared_flags;
    s32 previous_state;
    s32 flags_mask;
    u16 offset_x;
    u16 idle_frames;
    u16 shrink_scale;
    u16 reduced_scale;
    u16 offset_y;
    u16 target_scale;
    u16 target_left;
    u16 target_top;
    u16 target_width;
    u16 target_height;
    u16 reset_scale;
    u16 blended_scale;
    u16 moving_scale;
    u8 brightness;
    u8 next_brightness;
    SpriteFrameState *render;
    S_func_8009E038_8 *viewport_page;
    S_func_8009E038_6 *flags_page;
    s32 left_step;
    s32 shared_flags;

    render = render_params;
    input = &g_game_work;
    if (dungeon_floor_flags & 0x2000) {
        if (transition->state < VIEWPORT_SHRINK) {
            transition->state = VIEWPORT_SHRINK;
        }
    }
    flags = dungeon_floor_flags;
    if (flags & FLOOR_MAP_VIEW_HOLD) {
        previous_state = transition->state;
        cleared_flags = flags & ~0x2000;
        dungeon_floor_flags = cleared_flags;
        if (previous_state >= 2) {
            transition->state = VIEWPORT_RESET;
            transition->frames_left = 8;
        }
        transition->idle_frames = 0U;
        dungeon_floor_flags &= 0xFEFFFFFF;
    } else if ((u32) ((u16) transition->state - VIEWPORT_SHRINK) < 0x10U) {
        if (!(dungeon_floor_flags & 0x2000)) {
            transition->state = VIEWPORT_RESUME;
        }
    }
    if (transition->state != VIEWPORT_RESET || (dungeon_actor_ring_anchor->flags1C & ACTOR_BLIND)) {
        transition->idle_frames = 0U;
        dungeon_floor_flags &= 0xFEFFFFFF;
    }
    state = transition->state;
    switch (state) {
    case VIEWPORT_RESET:
        if (!(dungeon_floor_flags & FLOOR_MAP_VIEW_HOLD)) {
            idle_frames = transition->idle_frames + 1;
            transition->idle_frames = idle_frames;
            if ((s16) idle_frames == 0x1F) {
                dungeon_floor_flags = (s32) (dungeon_floor_flags | 0x01000000);
                create_fullscreen_grayscale_ramp(0);
            } else if ((s16) idle_frames >= 0x20) {
                transition->idle_frames = 0x20U;
            }
        }
        reset_frames = transition->frames_left;
        if (reset_frames > 0) {
            brightness = render->color.c.b;
            next_brightness = brightness + ((s32) (0x80 - brightness) / reset_frames);
            render->color.c.b = next_brightness;
            render->color.c.g = next_brightness;
            render->color.c.r = next_brightness;
            reset_scale = render->scale_y;
            offset_x = render->offset_x;
            blended_scale = reset_scale + ((s32) (0x3000 - reset_scale) / transition->frames_left);
            render->scale_y = blended_scale;
            render->scale_x = blended_scale;
            offset_y = render->offset_y;
            render->offset_x = (offset_x + ((s32) (0x20 - offset_x) / transition->frames_left));
            render->offset_y = (offset_y + ((s32) (0x20 - offset_y) / transition->frames_left));
            center->x.w.i = (s16) ((u16) center->x.w.i + ((s32) (0xA0 - center->x.w.i) / transition->frames_left));
            center->y.w.i = (s16) ((u16) center->y.w.i + ((s32) (0x78 - center->y.w.i) / transition->frames_left));
            transition->view_x = (s16) ((u16) transition->view_x + ((s32) (0
                - transition->view_x) / transition->frames_left));
            transition->view_y = (s16) ((u16) transition->view_y + ((s32) (0
                - transition->view_y) / transition->frames_left));
            transition->view_width = (s16) ((u16) transition->view_width + ((s32) (0x140
                - transition->view_width) / transition->frames_left));
            transition->view_height = (s16) ((u16) transition->view_height + ((s32) (0xE0
                - transition->view_height) / transition->frames_left));
        }
        reset_remaining = (u16) transition->frames_left - 1;
        transition->frames_left = reset_remaining;
        if ((reset_remaining << 0x10) <= 0) {
            center->x.w.i = 0xA0;
            center->y.w.i = 0x78;
            render->scale_y = 0x3000U;
            render->scale_x = 0x3000U;
            render->offset_x = 0x20U;
            render->offset_y = 0x20U;
            render->color.word = 0x808080;
            transition->view_width = 0x140;
            transition->view_height = 0xE0;
            shared_flags = ((S_func_8009E038_3 *)&dungeon_floor_flags)->unk_00;
            transition->view_x = 0;
            transition->view_y = 0;
            transition->frames_left = 0;
            state = FLOOR_MAP_VIEW_HOLD;
            if (shared_flags & state) {
                transition->frames_left = 0x1E;
                transition->state = (s16) ((u16) transition->state + 1);
            } else if (!(input->buttons & 0x100)) {
                transition->frames_left = 4;
                transition->state = VIEWPORT_FOLLOW;
            }
        }
        break;
    case VIEWPORT_HOLD:
        hold_remaining = (u16) transition->frames_left - 1;
        transition->frames_left = hold_remaining;
        if ((hold_remaining << 0x10) > 0) {
            break;
        }
        flags_mask = FLOOR_MAP_VIEW_HOLD_CLEAR_MASK;
        shared_flags = 8;
        flags_page = (S_func_8009E038_6 *)0x800E0000;
        transition->frames_left = shared_flags;
        shared_flags = flags_page->unk_296C;
        state = VIEWPORT_FOLLOW;
        transition->state = state;
        shared_flags &= flags_mask;
        flags_page->unk_296C = shared_flags;
        break;
    case VIEWPORT_FOLLOW:
        move_frames = transition->frames_left;
        if (move_frames != 0) {
            moving_scale = ((s32) (transition->target_scale - render->scale_y) / move_frames) + render->scale_y;
            render->scale_y = moving_scale;
            render->scale_x = moving_scale;
            center->x.w.i = (s16) ((u16) center->x.w.i + ((s32) (transition->target_center_x
                - center->x.w.i) / transition->frames_left));
            center->y.w.i = (s16) ((u16) center->y.w.i + ((s32) (transition->target_center_y
                - center->y.w.i) / transition->frames_left));
            render->offset_x = (((s32) (reference_tile_object.tile_position.parts.tile_x - render->offset_x) / transition->frames_left)
                + render->offset_x);
            render->offset_y = (((s32) (reference_tile_object.tile_position.parts.tile_y - render->offset_y) / transition->frames_left)
                + render->offset_y);
            left_step = (s32) (transition->target_x - transition->view_x) / transition->frames_left;
            transition->view_x = (s16) ((u16) transition->view_x + left_step);
            top_step = (s32) (transition->target_y - transition->view_y) / transition->frames_left;
            transition->view_y = (s16) ((u16) transition->view_y + top_step);
            transition->view_width = (s16) ((u16) transition->view_width + ((s32) (transition->target_width
                - transition->view_width) / transition->frames_left));
            height_step = (s32) (transition->target_height - transition->view_height) / transition->frames_left;
            transition->view_height = (s16) ((u16) transition->view_height + height_step);
            move_remaining = (u16) transition->frames_left - 1;
            transition->frames_left = move_remaining;
            if ((move_remaining << 0x10) <= 0) {
                center->x.w.i = (s16) (u16) transition->target_center_x;
                center->y.w.i = (s16) (u16) transition->target_center_y;
                target_scale = (u16) transition->target_scale;
                render->scale_y = target_scale;
                render->scale_x = target_scale;
                render->offset_x = reference_tile_object.tile_position.parts.tile_x;
                render->offset_y = reference_tile_object.tile_position.parts.tile_y;
                target_left = (u16) transition->target_x;
                viewport_page = (S_func_8009E038_8 *)0x80010000;
                transition->view_x = (s16) target_left;
                viewport_page->unk_3630 = target_left;
                target_top = (u16) transition->target_y;
                transition->view_y = (s16) target_top;
                viewport_page->unk_3632 = target_top;
                target_width = (u16) transition->target_width;
                transition->view_width = (s16) target_width;
                viewport_page->unk_3634 = target_width;
                target_height = (u16) transition->target_height;
                transition->view_height = (s16) target_height;
                viewport_page->unk_3636 = target_height;
            }
        } else {
            render->offset_x = reference_tile_object.tile_position.parts.tile_x;
            render->offset_y = reference_tile_object.tile_position.parts.tile_y;
        }
        if (input->buttons & 0x10) {
            if ((input->pressed_buttons) & 8) {
                current_scale = transition->target_scale;
                if (current_scale < 0x5000) {
                    next_scale = (u16) transition->target_scale + 0x1000;
                    transition->target_scale = next_scale;
                    *(s32 *)0x8001363C = (s32) next_scale;
                } else {
                    transition->target_scale = 0;
                    *(s32 *)0x8001363C = 0;
                }
                transition->frames_left = 4;
            }
        }
        if (!(input->buttons & 0x100)) {
            break;
        }
        if ((has_pending_actor_or_turn_action(0) << 0x10) != 0) {
            break;
        }
        clear_pending_action_event();
        flags_mask = 0xFEFFFFFF;
        flags_page = (S_func_8009E038_6 *)0x800E0000;
        shared_flags = flags_page->unk_296C;
        transition->idle_frames = 0U;
        transition->state = VIEWPORT_RESET;
        state = 1;
        transition->frames_left = state;
        shared_flags &= flags_mask;
        flags_page->unk_296C = shared_flags;
        break;
    case VIEWPORT_SHRINK:
        shrink_scale = render->scale_y;
        reduced_scale = shrink_scale - (shrink_scale >> 2);
        render->scale_y = reduced_scale;
        if ((u32) (reduced_scale & 0xFFFF) < 0x100U) {
            render->scale_y = 0U;
        }
        break;
    case VIEWPORT_RESUME:
        transition->state = VIEWPORT_FOLLOW;
        transition->frames_left = 4;
        break;
    }
    queue_black_draw_buffer_rectangle(transition);
    return;
}
