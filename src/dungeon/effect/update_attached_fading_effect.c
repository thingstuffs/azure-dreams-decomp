#include "shared/object_node.h"
#include "shared/entity.h"
#include "shared/sprite_frame_state.h"
#include "common.h"
#include "shared/object_flags.h"
#include "shared/dungeon_moving_views.h"
#include "engine/node.h"
#include "dungeon/effect.h"
#include "dungeon/effect/popup_body.h"

#ifndef NULL
#define NULL 0
#endif


extern s32 attached_fade_draw_address;

/* Update an attached effect with damped vertical motion, fading, shrinking, and flashing. */
void update_attached_fading_effect(ActorValuePopupBody *effect, ObjectPosition *motion, SpriteFrameState *sprite) {
    s32 phase;
    s16 next_phase;
    s32 rebound_speed;
    s32 velocity;
    s32 rebound_velocity;
    s32 damped_speed;
    s32 update_value;
    u16 fade_frames;
    u16 hold_frames;
    u16 shrink_frames;
    u16 frame;
    u16 scale;
    u16 next_scale;
    u8 brightness;
    u8 next_brightness;
    ObjectNodeHeader *parent;
    ObjectPosition *parent_pos;

    parent = effect->owner;
    if (parent != NULL) {
        if (parent->flags & 0x8000) {
            effect->owner = NULL;
            effect->anchor_position = NULL;
        }
    }
    if (effect->start_delay != 0) {
        effect->start_delay = (s16) ((u16) effect->start_delay - 1);
        return;
    }
    parent_pos = effect->anchor_position;
    if (parent_pos != NULL) {
        motion->x.w.i = ((u16)motion->x.w.i - (effect->anchor_x - parent_pos->x.unsigned_parts.integer));
        effect->anchor_x = (u16) effect->anchor_position->x.unsigned_parts.integer;
        motion->y.w.i = ((u16)motion->y.w.i - (effect->anchor_y
            - effect->anchor_position->y.unsigned_parts.integer));
        effect->anchor_y = (u16) effect->anchor_position->y.unsigned_parts.integer;
        motion->z.w.i = ((u16)motion->z.w.i - (effect->anchor_z
            - effect->anchor_position->z.unsigned_parts.integer));
        effect->anchor_z = (u16) effect->anchor_position->z.unsigned_parts.integer;
    }
    phase = effect->phase;
    switch (phase) {
    case 0:
        motion->velocity_z = 0x200000;
        motion->z.w.i = ((u16)motion->z.w.i - 0x80);
        effect->bounce_velocity.at00.v = 0x200000;
        sprite->scale_y = 0x1000U;
        sprite->scale_x = 0x1000U;
        register_node(NODE_HEADER(effect), &attached_fade_draw_address);
        effect->phase_ticks = 0x10U;
        effect->phase = (s16) ((u16) effect->phase + 1);
    case 1:
        fade_frames = effect->phase_ticks - 1;
        effect->phase_ticks = fade_frames;
        if ((s16) fade_frames > 0) {
            brightness = sprite->color.c.b;
            next_brightness = brightness + ((s32) (0x80 - brightness) / (s16) fade_frames);
            sprite->color.c.b = next_brightness;
            sprite->color.c.g = next_brightness;
            sprite->color.c.r = next_brightness;
        } else {
            next_phase = (u16) effect->phase + 1;
            effect->phase = next_phase;
        }
        break;
    case 3:
        hold_frames = effect->phase_ticks - 1;
        effect->phase_ticks = hold_frames;
        if ((hold_frames << 0x10) <= 0) {
            update_value = 8;
            effect->phase_ticks = update_value;
            next_phase = (u16) effect->phase + 1;
            effect->phase = next_phase;
        }
        break;
    case 4:
        shrink_frames = effect->phase_ticks - 1;
        effect->phase_ticks = shrink_frames;
        if ((s16) shrink_frames > 0) {
            scale = sprite->scale_y;
            next_scale = scale + ((s32) (0 - scale) / (s16) shrink_frames);
            sprite->scale_y = next_scale;
            sprite->scale_x = next_scale;
            motion->z.w.i = ((u16)motion->z.w.i + 6);
        } else {
            NODE_HEADER(effect)->flags = (u16) (NODE_HEADER(effect)->flags | 0x8000);
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        break;
    case 2:
    default:
        break;
    }
    motion->z.v = (s32) (motion->z.v + motion->velocity_z);
    frame = effect->frame_count + 1;
    effect->frame_count = frame;
    if (frame & 1) {
        velocity = motion->velocity_z;
        update_value = velocity >> 1;
        damped_speed = velocity >> 0x11;
        if (damped_speed < 0) {
            damped_speed = 0 - damped_speed;
        }
        motion->velocity_z = update_value;
        if (damped_speed < 2) {
            rebound_velocity = 0 - ((s32) effect->bounce_velocity.at00.v >> 1);
            effect->bounce_velocity.at00.v = rebound_velocity;
            motion->velocity_z = rebound_velocity;
            rebound_speed = effect->bounce_velocity.at02.v;
            if (rebound_speed < 0) {
                rebound_speed = 0 - rebound_speed;
            }
            if (rebound_speed < 2) {
                if (effect->phase < 3) {
                    effect->phase = 3;
                    effect->phase_ticks = 8U;
                }
            }
        }
    }
    if (effect->flashing != 0) {
        update_value = 0x2CF0F0F0;
        if (effect->frame_count & 3) {
            update_value = 0x2C404040;
        }
        sprite->color.word = update_value;
    }
}
