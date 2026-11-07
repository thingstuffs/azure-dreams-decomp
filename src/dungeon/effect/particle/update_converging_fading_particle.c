#include "sdk/libc.h"
#include "common.h"
#include "dungeon/effect/particle.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "dungeon/effect/particle/converging_fade.h"

/* Update effect motion and color, flagging it near its target or when fully faded. */
void update_converging_fading_particle(ConvergingFadeBody *effect, ObjectPosition *position) {
    s16 fade_level;
    s32 scaled_red;
    s32 scaled_green;
    s32 target_dx;
    s32 target_dy;
    s32 scaled_blue;

    position->x.v = (s32) (position->x.v
        + effect->velocity_x);
    position->y.v = (s32) (position->y.v
        + effect->velocity_y);
    position->z.v = (s32) (position->z.v + effect->velocity_z);
    effect->velocity_x = (s32) (effect->velocity_x + effect->acceleration_x);
    effect->velocity_y = (s32) (effect->velocity_y + effect->acceleration_y);
    effect->velocity_z = (s32) (effect->velocity_z + effect->acceleration_z);
    target_dx = abs(effect->target_x - position->x.w.i);
    if (target_dx < 0x10) {
        target_dy = abs(effect->target_y - position->y.w.i);
        if (target_dy < 0x10) {
            NODE_HEADER(effect)->flags |= NODE_REMOVE;
            object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
        }
    }
    scaled_red = effect->base_color.c.r * effect->fade_level;
    effect->color.c.r = (s8) (scaled_red / 256);
    scaled_green = effect->base_color.c.g * effect->fade_level;
    effect->color.c.g = (s8) (scaled_green / 256);
    scaled_blue = effect->base_color.c.b * effect->fade_level;
    effect->color.c.b = (s8) (scaled_blue / 256);
    fade_level = (u16) effect->fade_level - 8;
    effect->fade_level = fade_level;
    effect->draw_color = (s32) effect->color.word;
    if ((fade_level << 0x10) <= 0) {
        NODE_HEADER(effect)->flags |= NODE_REMOVE;
        object_flag_block.flags = (s32) (object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
