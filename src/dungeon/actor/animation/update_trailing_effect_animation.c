#include "dungeon/actor/animation.h"
#include "common.h"
#include "shared/object_flags.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"

extern u8 trailing_effect_frame_limit[];

/* Update a trailing effect's position, brightness, and animation frame. */
void update_trailing_effect_animation(ActorTrailWork *effect, TrailMotion *transform, SpriteFrameState *render_data)
{
    s32 history_index;
    s16 brightness;
    s32 brightness_delta;
    u8 source_brightness;
    u16 brightness_offset;
    s16 phase;
    s16 frames_left;
    u16 fade_brightness;
    u8 *next_frame;
    u8 fade_in_brightness;
    u8 fade_out_brightness;
    void *history_src;
    void *history_dst;
    void *related;
    ObjectNodeHeader *parent;
    SpriteFrameState *related_sprite;
    ActorTrailWork *linked_data;

    for (history_index = 6; history_index > 0; history_index--) {
        effect->history[history_index].x = effect->history[history_index - 1].x;
        effect->history[history_index].y = effect->history[history_index - 1].y;
        effect->history[history_index].z = effect->history[history_index - 1].z;
    }

    effect->history[0].x = transform->position.x.parts.whole.u;
    effect->history[0].y = transform->position.y.parts.whole.u;
    effect->history[0].z = transform->position.z.parts.whole.u;

    related = effect->follow;
    if (related == 0) {
        phase = effect->state.s;
        switch (phase) {
        case 0:
            transform->position.x.parts.whole.u += ((effect->target->position.x.parts.whole.s - transform->position.x.parts.whole.s) * 4) /
                               effect->timer.s;
            transform->position.y.parts.whole.u += ((effect->target->position.y.parts.whole.s - transform->position.y.parts.whole.s) * 4) /
                               effect->timer.s;
            transform->position.z.value +=
                (effect->target->position.z.value -
                 (rsin(effect->timer.s * 42) << 12) -
                 transform->position.z.value) /
                effect->timer.s;

            if (effect->brightness.s < 0xC0) {
                effect->brightness.u = effect->brightness.u + 0x10;
            }
            fade_in_brightness = effect->brightness.byte;
            render_data->color.c.g = fade_in_brightness;
            render_data->color.c.b = fade_in_brightness;
            render_data->color.c.r = fade_in_brightness;

            frames_left = effect->timer.u - 1;
            effect->timer.s = frames_left;
            if (frames_left <= 0) {
                transform->position.x.parts.whole.u = effect->target->position.x.parts.whole.u;
                transform->position.y.parts.whole.u = effect->target->position.y.parts.whole.u;
                transform->position.z.parts.whole.u = effect->target->position.z.parts.whole.u;
                effect->state.u++;
            }
            break;
        case 1:
            related = effect->owner;
            if (related != 0) {
                related = NODE_HEADER(related)->sprite;
                related_sprite = related;
                related_sprite->color.c.r = ((effect->ticks & 3) * 0x10) + 0x40;
                related_sprite->color.c.g = ((effect->ticks & 3) * 0x10) + 0x40;
                related_sprite->color.c.b = ((effect->ticks & 3) * 0x10) + 0x40;
            }

            fade_brightness = effect->brightness.u;
            fade_brightness = fade_brightness - ((s32)(fade_brightness << 16) >> 19);
            effect->brightness.u = fade_brightness;
            fade_out_brightness = effect->brightness.byte;
            render_data->color.c.g = fade_out_brightness;
            render_data->color.c.b = fade_out_brightness;
            render_data->color.c.r = fade_out_brightness;

            if (effect->brightness.s < 0x11) {
                NODE_HEADER(effect)->flags |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
    } else {
        related = NODE_BODY(related);
        linked_data = related;
        transform->position.x.parts.whole.u = linked_data->history[2].x;
        transform->position.y.parts.whole.u = linked_data->history[2].y;
        transform->position.z.parts.whole.u = linked_data->history[2].z;

        parent = effect->follow;
        related = parent->sprite;
        related_sprite = related;
        source_brightness = related_sprite->color.c.r;
        brightness_offset = effect->shade_offset.u;
        brightness_delta = source_brightness - brightness_offset;
        brightness = brightness_delta;
        if ((s16)brightness_delta < 0x20) {
            brightness = 0;
        }

        frames_left = effect->timer.u - 1;
        effect->timer.s = frames_left;
        if ((frames_left <= 0) && ((s16)brightness == 0)) {
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        render_data->color.c.b = brightness;
        render_data->color.c.g = brightness;
        render_data->color.c.r = brightness;
    }

    transform->velocity.x.parts.whole.s = effect->history[4].x + (rand() & 0xF) - 8;
    transform->velocity.y.parts.whole.s = effect->history[4].y + (rand() & 0xF) - 8;
    transform->velocity.z.parts.whole.s = effect->history[4].z + (rand() & 0xF) - 8;

    next_frame = (u8 *)render_data->source + 0xC;
    render_data->source = next_frame;
    if (trailing_effect_frame_limit < next_frame) {
        render_data->source = trailing_effect_frame_limit - 0x48;
    }
    effect->ticks++;
}
