#include "modules/dungeon_resource10_slot0.h"

void func_80170B0C(R10_80170B0C_Actor *actor, R10_80170B0C_Vec3 *vec, R10_80170B0C_Sprite *sprite)
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
            *(u16 *)((u8 *)actor - 2) |= 0x8000;
            objectFlagBlock.flags |= 0x8000;
        }
    }

    sprite->color[0] = actor->color[0] * actor->scale / actor->divisor;
    sprite->color[1] = actor->color[1] * actor->scale / actor->divisor;
    sprite_size = sprite->size0;
    reduced_size = sprite_size - 0xC8;
    sprite_size = reduced_size;
    sprite->color[2] = actor->color[2] * actor->scale / actor->divisor;
    if ((s16)reduced_size < 0) {
        sprite_size = 0;
    }
    sprite->size0 = sprite_size;
    sprite->size1 = sprite_size;
    actor->scale = (u16)actor->scale - 8;
    func_800478B8(sprite);
    if (actor->scale <= 0) {
        *(u16 *)((u8 *)actor - 2) |= 0x8000;
        objectFlagBlock.flags |= 0x8000;
    }
}
