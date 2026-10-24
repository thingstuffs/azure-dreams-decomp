#include "dungeon/actor/animation.h"
#include "common.h"
#include "shared/object_flags.h"

#define U8_AT(p, o) (*(u8 *)((u8 *)(p) + (o)))
#define U16_AT(p, o) (*(u16 *)((u8 *)(p) + (o)))
#define PTR_AT(p, o) (*(void **)((u8 *)(p) + (o)))


extern s32 rsin(s32);
extern s32 rand(void);
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
    u32 next_frame;
    u8 fade_in_brightness;
    u8 fade_out_brightness;
    void *history_src;
    void *history_dst;
    void *related;
    void *parent;

    for (history_index = 6; history_index > 0; history_index--) {
        effect->history[history_index].x.u = effect->history[history_index - 1].x.u;
        effect->history[history_index].y.u = effect->history[history_index - 1].y.u;
        effect->history[history_index].z.u = effect->history[history_index - 1].z.u;
    }

    effect->history[0].x.u = transform->position.x.parts.whole.u;
    effect->history[0].y.u = transform->position.y.parts.whole.u;
    effect->history[0].z.u = transform->position.z.parts.whole.u;

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
            related = PTR_AT(effect, 4);
            if (related != 0) {
                related = PTR_AT(related, -0x14);
                U8_AT(related, 0xC) = ((effect->ticks & 3) * 0x10) + 0x40;
                U8_AT(related, 0xD) = ((effect->ticks & 3) * 0x10) + 0x40;
                U8_AT(related, 0xE) = ((effect->ticks & 3) * 0x10) + 0x40;
            }

            fade_brightness = effect->brightness.u;
            fade_brightness = fade_brightness - ((s32)(fade_brightness << 16) >> 19);
            effect->brightness.u = fade_brightness;
            fade_out_brightness = effect->brightness.byte;
            render_data->color.c.g = fade_out_brightness;
            render_data->color.c.b = fade_out_brightness;
            render_data->color.c.r = fade_out_brightness;

            if (effect->brightness.s < 0x11) {
                U16_AT(effect, -2) |= NODE_REMOVE;
                object_flag_block.flags |= OBJECT_REMOVE_PENDING;
            }
        }
    } else {
        related = (u8 *)related + 0x20;
        transform->position.x.parts.whole.u = U16_AT(related, 0x34);
        transform->position.y.parts.whole.u = U16_AT(related, 0x36);
        transform->position.z.parts.whole.u = U16_AT(related, 0x38);

        parent = effect->follow;
        related = PTR_AT(parent, 0xC);
        source_brightness = U8_AT(related, 0xC);
        brightness_offset = effect->shade_offset.u;
        brightness_delta = source_brightness - brightness_offset;
        brightness = brightness_delta;
        if ((s16)brightness_delta < 0x20) {
            brightness = 0;
        }

        frames_left = effect->timer.u - 1;
        effect->timer.s = frames_left;
        if ((frames_left <= 0) && ((s16)brightness == 0)) {
            U16_AT(effect, -2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
        render_data->color.c.b = brightness;
        render_data->color.c.g = brightness;
        render_data->color.c.r = brightness;
    }

    transform->velocity.x.parts.whole.s = effect->history[4].x.u + (rand() & 0xF) - 8;
    transform->velocity.y.parts.whole.s = effect->history[4].y.u + (rand() & 0xF) - 8;
    transform->velocity.z.parts.whole.s = effect->history[4].z.u + (rand() & 0xF) - 8;

    next_frame = (u32)render_data->source + 0xC;
    render_data->source = (void *)next_frame;
    if ((u32)trailing_effect_frame_limit < next_frame) {
        render_data->source = trailing_effect_frame_limit - 0x48;
    }
    effect->ticks++;
}
