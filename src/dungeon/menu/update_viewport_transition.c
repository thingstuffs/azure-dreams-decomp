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


typedef struct S_func_8009E038_1 {
    u8 pad_00[2];
    s16 unk_02;
    u8 pad_04[2];
    s16 unk_06;
} S_func_8009E038_1;

typedef struct S_func_8009E038_2 {
    u8 pad_00[0xC];
    union {
        s32 s32;
        struct {
            u8 unk_0C;
            u8 unk_0D;
            u8 unk_0E;
        } bytes;
    } unk_0C;
    u8 pad_10[0xC];
    u16 unk_1C;
    u16 unk_1E;
    union {
        s16 s16;
        u16 u16;
    } unk_20;
    union {
        s16 s16;
        u16 u16;
    } unk_22;
} S_func_8009E038_2;

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
void update_viewport_transition(InactiveTypeTwelveObjectBody *transition, S_func_8009E038_1 *center, S_func_8009E038_2 *render_params,
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
    S_func_8009E038_2 *render;
    S_func_8009E038_8 *viewport_page;
    S_func_8009E038_6 *flags_page;
    s32 left_step;
    s32 shared_flags;

    render = render_params;
    input = &g_game_work;
    if (((S_func_8009E038_3 *)&dungeon_floor_flags)->unk_00 & 0x2000) {
        if (transition->unk_18.halves.high.s < VIEWPORT_SHRINK) {
            transition->unk_18.halves.high.s = VIEWPORT_SHRINK;
        }
    }
    flags = ((S_func_8009E038_3 *)&dungeon_floor_flags)->unk_00;
    if (flags & FLOOR_MAP_VIEW_HOLD) {
        previous_state = transition->unk_18.halves.high.s;
        cleared_flags = flags & ~0x2000;
        (*(s32 *)&dungeon_floor_flags) = cleared_flags;
        if (previous_state >= 2) {
            transition->unk_18.halves.high.s = VIEWPORT_RESET;
            transition->unk_1C.halves.low.s = 8;
        }
        transition->unk_2C = 0U;
        dungeon_floor_flags &= 0xFEFFFFFF;
    } else if ((u32) ((u16) transition->unk_18.halves.high.s - VIEWPORT_SHRINK) < 0x10U) {
        if (!(((S_func_8009E038_3 *)&dungeon_floor_flags)->unk_00 & 0x2000)) {
            transition->unk_18.halves.high.s = VIEWPORT_RESUME;
        }
    }
    if (transition->unk_18.halves.high.s != VIEWPORT_RESET || (dungeon_actor_ring_anchor->flags1C & ACTOR_BLIND)) {
        transition->unk_2C = 0U;
        dungeon_floor_flags &= 0xFEFFFFFF;
    }
    state = transition->unk_18.halves.high.s;
    switch (state) {
    case VIEWPORT_RESET:
        if (!((*(s32 *)((u8 *)&dungeon_floor_flags + 0)) & FLOOR_MAP_VIEW_HOLD)) {
            idle_frames = transition->unk_2C + 1;
            transition->unk_2C = idle_frames;
            if ((s16) idle_frames == 0x1F) {
                (*(s32 *)&dungeon_floor_flags) = (s32) (((S_func_8009E038_3 *)&dungeon_floor_flags)->unk_00 | 0x01000000);
                create_fullscreen_quad_updater(0);
            } else if ((s16) idle_frames >= 0x20) {
                transition->unk_2C = 0x20U;
            }
        }
        reset_frames = transition->unk_1C.halves.low.s;
        if (reset_frames > 0) {
            brightness = render->unk_0C.bytes.unk_0E;
            next_brightness = brightness + ((s32) (0x80 - brightness) / reset_frames);
            render->unk_0C.bytes.unk_0E = next_brightness;
            render->unk_0C.bytes.unk_0D = next_brightness;
            render->unk_0C.bytes.unk_0C = next_brightness;
            reset_scale = render->unk_1E;
            offset_x = render->unk_20.u16;
            blended_scale = reset_scale + ((s32) (0x3000 - reset_scale) / (s16) transition->unk_1C.halves.low.s);
            render->unk_1E = blended_scale;
            render->unk_1C = blended_scale;
            offset_y = render->unk_22.u16;
            render->unk_20.u16 = (u16) (offset_x + ((s32) (0x20 - offset_x) / (s16) transition->unk_1C.halves.low.s));
            render->unk_22.u16 = (u16) (offset_y + ((s32) (0x20 - offset_y) / (s16) transition->unk_1C.halves.low.s));
            center->unk_02 = (s16) ((u16) center->unk_02 + ((s32) (0xA0 - center->unk_02) / (s16) transition->unk_1C.halves.low.s));
            center->unk_06 = (s16) ((u16) center->unk_06 + ((s32) (0x78 - center->unk_06) / (s16) transition->unk_1C.halves.low.s));
            transition->unk_04.halves.low.s = (s16) ((u16) transition->unk_04.halves.low.s + ((s32) (0
                - transition->unk_04.halves.low.s) / (s16) transition->unk_1C.halves.low.s));
            transition->unk_04.halves.high.s = (s16) ((u16) transition->unk_04.halves.high.s + ((s32) (0
                - transition->unk_04.halves.high.s) / (s16) transition->unk_1C.halves.low.s));
            transition->unk_08.halves.low.s = (s16) ((u16) transition->unk_08.halves.low.s + ((s32) (0x140
                - transition->unk_08.halves.low.s) / (s16) transition->unk_1C.halves.low.s));
            transition->unk_08.halves.high.s = (s16) ((u16) transition->unk_08.halves.high.s + ((s32) (0xE0
                - transition->unk_08.halves.high.s) / (s16) transition->unk_1C.halves.low.s));
        }
        reset_remaining = (u16) transition->unk_1C.halves.low.s - 1;
        transition->unk_1C.halves.low.s = reset_remaining;
        if ((reset_remaining << 0x10) <= 0) {
            center->unk_02 = 0xA0;
            center->unk_06 = 0x78;
            render->unk_1E = 0x3000U;
            render->unk_1C = 0x3000U;
            render->unk_20.u16 = 0x20U;
            render->unk_22.u16 = 0x20U;
            render->unk_0C.s32 = 0x808080;
            transition->unk_08.halves.low.s = 0x140;
            transition->unk_08.halves.high.s = 0xE0;
            shared_flags = ((S_func_8009E038_3 *)&dungeon_floor_flags)->unk_00;
            transition->unk_04.halves.low.s = 0;
            transition->unk_04.halves.high.s = 0;
            transition->unk_1C.halves.low.s = 0;
            state = FLOOR_MAP_VIEW_HOLD;
            if (shared_flags & state) {
                transition->unk_1C.halves.low.s = 0x1E;
                transition->unk_18.halves.high.s = (s16) ((u16) transition->unk_18.halves.high.s + 1);
            } else if (!(input->buttons & 0x100)) {
                transition->unk_1C.halves.low.s = 4;
                transition->unk_18.halves.high.s = VIEWPORT_FOLLOW;
            }
        }
        break;
    case VIEWPORT_HOLD:
        hold_remaining = (u16) transition->unk_1C.halves.low.s - 1;
        transition->unk_1C.halves.low.s = hold_remaining;
        if ((hold_remaining << 0x10) > 0) {
            break;
        }
        flags_mask = FLOOR_MAP_VIEW_HOLD_CLEAR_MASK;
        shared_flags = 8;
        flags_page = (S_func_8009E038_6 *)0x800E0000;
        transition->unk_1C.halves.low.s = shared_flags;
        shared_flags = flags_page->unk_296C;
        state = VIEWPORT_FOLLOW;
        transition->unk_18.halves.high.s = state;
        shared_flags &= flags_mask;
        flags_page->unk_296C = shared_flags;
        break;
    case VIEWPORT_FOLLOW:
        move_frames = transition->unk_1C.halves.low.s;
        if (move_frames != 0) {
            moving_scale = ((s32) (transition->unk_1C.halves.high.s - render->unk_1E) / move_frames) + render->unk_1E;
            render->unk_1E = moving_scale;
            render->unk_1C = moving_scale;
            center->unk_02 = (s16) ((u16) center->unk_02 + ((s32) (transition->unk_14.halves.low.s
                - center->unk_02) / (s16) transition->unk_1C.halves.low.s));
            center->unk_06 = (s16) ((u16) center->unk_06 + ((s32) (transition->unk_14.halves.high.s
                - center->unk_06) / (s16) transition->unk_1C.halves.low.s));
            render->unk_20.u16 = (u16) (((s32) (reference_tile_object.tile_position.parts.tile_x - render->unk_20.u16) / (s16) transition->unk_1C.halves.low.s)
                + render->unk_20.u16);
            render->unk_22.u16 = (u16) (((s32) (reference_tile_object.tile_position.parts.tile_y - render->unk_22.u16) / (s16) transition->unk_1C.halves.low.s)
                + render->unk_22.u16);
            left_step = (s32) (transition->unk_0C.halves.low.s - transition->unk_04.halves.low.s) / (s16) transition->unk_1C.halves.low.s;
            transition->unk_04.halves.low.s = (s16) ((u16) transition->unk_04.halves.low.s + left_step);
            top_step = (s32) (transition->unk_0C.halves.high.s - transition->unk_04.halves.high.s) / (s16) transition->unk_1C.halves.low.s;
            transition->unk_04.halves.high.s = (s16) ((u16) transition->unk_04.halves.high.s + top_step);
            transition->unk_08.halves.low.s = (s16) ((u16) transition->unk_08.halves.low.s + ((s32) (transition->unk_10.halves.low.s
                - transition->unk_08.halves.low.s) / (s16) transition->unk_1C.halves.low.s));
            height_step = (s32) (transition->unk_10.halves.high.s - transition->unk_08.halves.high.s) / (s16) transition->unk_1C.halves.low.s;
            transition->unk_08.halves.high.s = (s16) ((u16) transition->unk_08.halves.high.s + height_step);
            move_remaining = (u16) transition->unk_1C.halves.low.s - 1;
            transition->unk_1C.halves.low.s = move_remaining;
            if ((move_remaining << 0x10) <= 0) {
                center->unk_02 = (s16) (u16) transition->unk_14.halves.low.s;
                center->unk_06 = (s16) (u16) transition->unk_14.halves.high.s;
                target_scale = (u16) transition->unk_1C.halves.high.s;
                render->unk_1E = target_scale;
                render->unk_1C = target_scale;
                render->unk_20.s16 = (s16) reference_tile_object.tile_position.parts.tile_x;
                render->unk_22.s16 = (s16) reference_tile_object.tile_position.parts.tile_y;
                target_left = (u16) transition->unk_0C.halves.low.s;
                viewport_page = (S_func_8009E038_8 *)0x80010000;
                transition->unk_04.halves.low.s = (s16) target_left;
                viewport_page->unk_3630 = target_left;
                target_top = (u16) transition->unk_0C.halves.high.s;
                transition->unk_04.halves.high.s = (s16) target_top;
                viewport_page->unk_3632 = target_top;
                target_width = (u16) transition->unk_10.halves.low.s;
                transition->unk_08.halves.low.s = (s16) target_width;
                viewport_page->unk_3634 = target_width;
                target_height = (u16) transition->unk_10.halves.high.s;
                transition->unk_08.halves.high.s = (s16) target_height;
                viewport_page->unk_3636 = target_height;
            }
        } else {
            render->unk_20.s16 = (s16) reference_tile_object.tile_position.parts.tile_x;
            render->unk_22.s16 = (s16) reference_tile_object.tile_position.parts.tile_y;
        }
        if (input->buttons & 0x10) {
            if ((input->pressed_buttons) & 8) {
                current_scale = transition->unk_1C.halves.high.s;
                if (current_scale < 0x5000) {
                    next_scale = (u16) transition->unk_1C.halves.high.s + 0x1000;
                    transition->unk_1C.halves.high.s = next_scale;
                    *(s32 *)0x8001363C = (s32) next_scale;
                } else {
                    transition->unk_1C.halves.high.s = 0;
                    *(s32 *)0x8001363C = 0;
                }
                transition->unk_1C.halves.low.s = 4;
            }
        }
        if (!(input->buttons & 0x100)) {
            break;
        }
        if ((has_pending_actor_or_turn_action(0) << 0x10) != 0) {
            break;
        }
        clear_pending_item_action_state();
        flags_mask = 0xFEFFFFFF;
        flags_page = (S_func_8009E038_6 *)0x800E0000;
        shared_flags = flags_page->unk_296C;
        transition->unk_2C = 0U;
        transition->unk_18.halves.high.s = VIEWPORT_RESET;
        state = 1;
        transition->unk_1C.halves.low.s = state;
        shared_flags &= flags_mask;
        flags_page->unk_296C = shared_flags;
        break;
    case VIEWPORT_SHRINK:
        shrink_scale = render->unk_1E;
        reduced_scale = shrink_scale - (shrink_scale >> 2);
        render->unk_1E = reduced_scale;
        if ((u32) (reduced_scale & 0xFFFF) < 0x100U) {
            render->unk_1E = 0U;
        }
        break;
    case VIEWPORT_RESUME:
        transition->unk_18.halves.high.s = VIEWPORT_FOLLOW;
        transition->unk_1C.halves.low.s = 4;
        break;
    }
    queue_black_draw_buffer_rectangle(transition);
    return;
}
