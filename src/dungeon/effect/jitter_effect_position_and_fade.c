#include "common.h"
#include "sdk/libc.h"
#include "shared/object_flags.h"
#include "shared/object_node.h"
#include "shared/sprite_part_command.h"
#include "dungeon/effect.h"

extern s8 D_80024AE0[];
extern u16 D_80024A70;

/* Jitters the sprite around its base coordinates, cycles its commands, and fades it. */
void jitter_effect_position_and_fade(JitterEffectBody *effect, ObjectPosition *position, SpriteFrameState *sprite) {
    s32 axes_left;
    u16 *base_coord;
    s32 jitter;
    s32 fade;
    u16 base_value;
    u16 next_scale;
    SpritePartCommand *next_command;
    u8 brightness;
    ObjectPosition *anchor;
    Fixed1616 *motion_axis;

    anchor = effect->anchor;
    D_80024A70++;
    if (anchor != 0) {
        ((Fixed1616 *)&position->velocity_x)->w.i = anchor->x.unsigned_parts.integer;
        ((Fixed1616 *)&position->velocity_y)->w.i = effect->anchor->y.unsigned_parts.integer;
        ((Fixed1616 *)&position->velocity_z)->w.i = effect->anchor->z.unsigned_parts.integer;
    }
    motion_axis = &position->x;
    base_coord = effect->base_position;
    axes_left = 3;
    do {
        axes_left--;
        jitter = (rand() & 0xF) - 8;
        base_value = *base_coord;
        base_coord++;
        motion_axis->w.i = base_value + jitter * D_80024AE0[effect->phase];
        motion_axis++;
    } while (axes_left > 0);
    next_command = sprite->source;
    next_command++;
    sprite->source = next_command;
    if ((void *)next_command >= (void *)D_80024AE0) {
        sprite->source = D_80024AE0 - 7 * sizeof(SpritePartCommand);
    }
    next_scale = sprite->scale_y - sprite->scale_y / 24;
    sprite->scale_y = next_scale;
    sprite->scale_x = next_scale;
    fade = (u16)effect->fade;
    fade -= 8;
    effect->fade = fade + effect->phase / 2;
    brightness = effect->fade;
    sprite->color.c.b = brightness;
    sprite->color.c.g = brightness;
    sprite->color.c.r = brightness;
    if (effect->fade <= 0) {
        NODE_HEADER(effect)->flags |= 0x8000;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
