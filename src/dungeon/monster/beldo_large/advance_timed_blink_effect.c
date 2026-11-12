#include "dungeon/monster/beldo_large_data.h"
#include "slus.h"
/* cfail-repair: recovered external dispatch table */
#include "common.h"
#include "dungeon/monster/beldo_large.h"
#include "shared/object_flags.h"
#include "dungeon/system.h"
#include "shared/object_node.h"




   /* the 0x2 bytes before state in advance_timed_blink_effect, addressed as state[-1] */


/* Advances a timed blinking effect, triggers sounds, and sets completion flags. */
void advance_timed_blink_effect(SecondaryEncounterObjectBody *state_data_arg, void *unused, SpriteFrameState *color_data_arg) {
    SpriteFrameState *color_data = color_data_arg;
    SecondaryEncounterObjectBody *state_data = state_data_arg;
    s32 phase;
    s32 bright_shade;
    u16 dim_shade;
    u16 next_phase;
    u16 frame;
    u16 blink_frame;

    phase = state_data->phase.s;
    switch ((u32) phase) {
    case 1:
        frame = state_data->frame + 1;
        state_data->frame = frame;
        if (!(frame & 3)) {
            initialize_timed_motion_step(6, 0xC);
            play_sound_if_enabled(0x818);
        }
        if (!(state_data->frame & 7)) {
            bright_shade = 0xFF;
            if (color_data->color.c.r != bright_shade) {
                color_data->color.c.b = bright_shade;
                color_data->color.c.g = bright_shade;
                color_data->color.c.r = bright_shade;
            } else {
                dim_shade = 0x80;
                color_data->color.c.b = dim_shade;
                color_data->color.c.g = dim_shade;
                color_data->color.c.r = dim_shade;
            }
        }
        if ((s16) state_data->frame == 0x28) {
            {
                u8 *flag_page = (u8 *) 0x80170000;
                *(u16 *)((u8 *)&encounter_blink_update_flag) = 1;
            }
        }
        if ((s16) state_data->frame >= 0x28) {
            next_phase = state_data->phase.u + 1;
            state_data->phase.u = next_phase;
            return;
        }
        break;
    case 2:
        blink_frame = state_data->frame + 1;
        state_data->frame = blink_frame;
        if (!(blink_frame & 3)) {
            play_sound_if_enabled(0x818);
        }
        if (!(state_data->frame & 7)) {
            bright_shade = 0xFF;
            if (color_data->color.c.r != bright_shade) {
                color_data->color.c.b = bright_shade;
                color_data->color.c.g = bright_shade;
                color_data->color.c.r = bright_shade;
            } else {
                dim_shade = 0x80;
                color_data->color.c.b = dim_shade;
                color_data->color.c.g = dim_shade;
                color_data->color.c.r = dim_shade;
            }
        }
        if ((s16) state_data->frame >= 0x3C) {
            state_data->frame = 0U;
            state_data->phase.s = (s16) ((u16) state_data->phase.s + 1);
            color_data->color.c.b = 0x80;
            color_data->color.c.g = 0x80;
            color_data->color.c.r = 0x80;
            return;
        }
        break;
    case 4:
        NODE_HEADER(state_data)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    case 0:
    case 3:
    default:
        break;
    }
}
