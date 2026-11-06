#include "common.h"
#include "dungeon/monster/beldo/expanding_fade.h"
#include "shared/object_node.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "shared/dungeon_moving_views.h"



   /* arg1 in expand_fade_effect_and_expire */

   /* src in expand_fade_effect_and_expire */

extern void advance_sprite_animation_and_textures(void *primitive);

/* Copy the effect position, expand and fade its primitive, and flag expiration. */
void expand_fade_effect_and_expire(void *effect_arg, MovingPosition *position, SpriteFrameState *primitive)
{
    BeldoExpandingFadeBody *effect = effect_arg;
    s16 ticks_left;
    s32 shade;
    u16 extent;
    MovingPosition *source_position;

    source_position = effect->source_position;
    position->x = source_position->x;
    position->y = source_position->y;
    position->z = source_position->z;

    extent = primitive->scale_y + 0x320;
    primitive->scale_y = extent;
    primitive->scale_x = extent;

    ticks_left = effect->ticks_left - 1;
    shade = (s32)(ticks_left * 0x50) / (s16)effect->duration;
    effect->ticks_left = (u16)ticks_left;
    primitive->color.c.b = shade;
    primitive->color.c.g = shade;
    primitive->color.c.r = shade;
    advance_sprite_animation_and_textures(primitive);

    if ((s16)effect->ticks_left <= 0) {
        NODE_HEADER(effect)->flags = (u16)(NODE_HEADER(effect)->flags | 0x8000);
        object_flag_block.flags = (s32)(object_flag_block.flags | OBJECT_REMOVE_PENDING);
    }
}
