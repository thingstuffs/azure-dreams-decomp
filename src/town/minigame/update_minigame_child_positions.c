#include "town/paired_indicators.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/slus_callbacks.h"
#include "engine/node.h"
#include "sdk/libc.h"
#include "town/minigame.h"

extern u8 D_80024334[16];
extern u16 D_80024500[8];
extern u8 D_800F8E9C[16];

/* Initialize two child objects, blink their color, and ease their positions toward active or resting targets. */
void update_minigame_child_positions(PairedIndicators *state)
{
    IndicatorChildNode *child_obj;
    IndicatorChild *child_state;
    s32 kind;
    s32 mask_index;
    s32 color;
    s32 child_index;
    u16 blink_ticks;

    switch (state->state) {
    case 0:
        state->second_x = 0x410;
        state->first_x = 0x340;
        state->second_y = 0x348;
        state->first_y = 0x348;
        state->second_z = -0x60;
        state->first_z = -0x60;

        kind = state->kind;
        switch (kind) {
        case 0:
            state->second_target_z = -0x60;
            state->first_target_z = -0x60;
            break;
        case 1:
            state->second_target_z = -0x98;
            state->first_target_z = -0x98;
            break;
        case 2:
            state->second_target_z = -0x30;
            state->first_target_z = -0x30;
            break;
        case 3:
            state->first_target_z = -0xB0;
            state->second_target_z = -0x10;
            break;
        case 4:
            state->first_target_z = -0x10;
            state->second_target_z = -0xB0;
        }

        child_index = 1;
        do {
            child_obj = allocate_flagged_object_node(0x136);
            if (child_obj != 0) {
                child_state = &child_obj->work;
                child_obj->header.update_callback = D_80024334;
                register_node(child_obj, project_sprite_chain);
                kind = (s32)child_obj->header.sprite;
                ((SpriteFrameState *)kind)->flags = 0xC;
                color = 0x00808080;
                ((SpriteFrameState *)kind)->scale_y = 0x800;
                ((SpriteFrameState *)kind)->scale_x = 0x800;
                ((SpriteFrameState *)kind)->source = D_800F8E9C;
                ((SpriteFrameState *)kind)->unk_04 = 0;
                ((SpriteFrameState *)kind)->frame_ticks = 0;
                ((SpriteFrameState *)kind)->color.word = color;
                child_obj->work.source = state;
                child_state->use_first = child_index;
            }
            child_index--;
        } while (child_index >= 0);
        state->state = 1;
        break;

    case 1:
        break;

    default:
        return;
    }

    blink_ticks = state->blink_ticks + 1;
    state->blink_ticks = blink_ticks;
    if (((blink_ticks >> 2) & 1) != 0) {
        mask_index = state->kind;
        color = (s32)state->owner;
        if ((((IndicatorOwner *)color)->blink_flags & D_80024500[mask_index]) != 0) {
            state->blink_color = 0;
        } else {
            state->blink_color = 0x00FFFFFF;
        }
    } else {
        state->blink_color = 0x00FFFFFF;
    }
    if (state->owner->value >= state->threshold) {
        s32 first_step = (state->first_target_z - state->first_z) >> 1;
        s32 second_step = (state->second_target_z - state->second_z) >> 1;

        state->first_z = (u16)state->first_z + first_step;
        state->second_z = (u16)state->second_z + second_step;
        state->flags &= ~1;
        return;
    }

    {
        s32 first_step = (-0x60 - state->first_z) >> 1;
        s32 second_step = (-0x60 - state->second_z) >> 1;
        s32 second_pos;
        s32 rest_distance;
        s32 abs_rest_distance;

        state->first_z = (u16)state->first_z + first_step;
        second_pos = (u16)state->second_z + second_step;
        state->second_z = second_pos;
        abs_rest_distance = abs((s16)second_pos + 0x60);
        if (abs_rest_distance < 2) {
            state->flags |= 1;
        }
    }

    return;
}

