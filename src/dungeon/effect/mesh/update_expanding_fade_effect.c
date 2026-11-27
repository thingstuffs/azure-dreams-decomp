#include "shared/object_node.h"
#include "common.h"
#include "dungeon/effect/mesh.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "records/Rec_D_80082E80.h"
#include "sdk/libc.h"
#include "sdk/libgte.h"
#include "slus.h"






/* Expand and fade a spiraling effect while updating its position. */
void update_expanding_fade_effect(ExpandingFadeEffectBody *effect, ObjectPosition *position, SpriteFrameState *sprite) {
    u16 height_offset;
    u16 age;
    u16 scale;
    u8 brightness;

    age = effect->age + 1;
    effect->age = age;
    if ((s16) age >= 0xA) {
        brightness = sprite->color.c.b - 0x10;
        sprite->color.c.b = brightness;
        sprite->color.c.g = brightness;
        sprite->color.c.r = brightness;
    }
    effect->angle.u = (u16) (effect->angle.u + 0x100);
    effect->radius++;
    height_offset = (u16) (effect->height_offset - 8) - (rand() % 9);
    effect->height_offset = height_offset;
    if ((u16) sprite->scale_x < 0x400U) {
        scale = sprite->scale_y + 0x40;
        sprite->scale_y = scale;
        sprite->scale_x = scale;
    }
    advance_sprite_animation_and_textures(sprite);
    if (sprite->flags & 0x6000) {
        (*(u16 *)((u8 *)effect + -2)) = (u16) (NODE_HEADER(effect)->flags | NODE_REMOVE);
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    position->x.v = (s32) (effect_position_source->x.v + (((rsin((s16) effect->angle.u)
        >> 4) * effect->radius) << 8));
    position->y.v = (s32) (effect_position_source->y.v
        + (((rcos((s16) effect->angle.u) >> 4) * effect->radius)
           << 8));
    position->z.w.i = (s16) (effect_position_source->z.w.i
        + effect->height_offset);
}
