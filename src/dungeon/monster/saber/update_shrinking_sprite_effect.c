#include "common.h"
#include "shared/sprite_frame_state.h"
#include "shared/object_flags.h"
#include "slus.h"

typedef struct {
    u8 color[3];
    u8 pad03[0x2F];
    s16 scale;
    s16 divisor;
    s16 x;
    s16 y;
    u8 pad3A[6];
    s32 pos[3];
    s32 vel[3];
} Actor;

typedef struct {
    s32 xyz[3];
} Vec3;

typedef struct {
    u8 pad00[0xC];
    s8 color[3];
    u8 pad0F[0xD];
    u16 size0;
    u16 size1;
} Sprite;

/* Advance the actor, fade and shrink its sprite, and flag proximity or fade completion. */
void update_shrinking_sprite_effect(Actor *actor, Vec3 *vec, SpriteFrameState *sprite)
{
    s32 distance_x;
    s32 distance_y;
    u16 reduced_size;
    u16 sprite_size;

    vec->xyz[0] += actor->pos[0];
    vec->xyz[1] += actor->pos[1];
    vec->xyz[2] += actor->pos[2];
    actor->pos[0] += actor->vel[0];
    actor->pos[1] += actor->vel[1];
    actor->pos[2] += actor->vel[2];

    distance_x = __builtin_abs(actor->x - *(s16 *)((u8 *)vec + 2));
    if (distance_x < 0x10) {
        distance_y = __builtin_abs(actor->y - *(s16 *)((u8 *)vec + 6));
        if (distance_y < 0x10) {
            *(u16 *)((u8 *)actor - 2) |= NODE_REMOVE;
            object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        }
    }

    sprite->color.c.r = actor->color[0] * actor->scale / actor->divisor;
    sprite->color.c.g = actor->color[1] * actor->scale / actor->divisor;
    sprite_size = sprite->scale_x;
    reduced_size = sprite_size - 0xC8;
    sprite_size = reduced_size;
    sprite->color.c.b = actor->color[2] * actor->scale / actor->divisor;
    if ((s16)reduced_size < 0) {
        sprite_size = 0;
    }
    sprite->scale_x = sprite_size;
    sprite->scale_y = sprite_size;
    actor->scale = (u16)actor->scale - 8;
    advance_sprite_animation_and_textures(sprite);
    if (actor->scale <= 0) {
        *(u16 *)((u8 *)actor - 2) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
