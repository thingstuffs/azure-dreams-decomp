#include "common.h"

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

extern void func_800478B8(Sprite *);
extern s32 D_800814A0[3];

void func_80AC5284(Actor *actor, Vec3 *vec, Sprite *sprite)
{
    s32 dx;
    s32 dy;
    u16 size;
    u16 clamped;

    vec->xyz[0] += actor->pos[0];
    vec->xyz[1] += actor->pos[1];
    vec->xyz[2] += actor->pos[2];
    actor->pos[0] += actor->vel[0];
    actor->pos[1] += actor->vel[1];
    actor->pos[2] += actor->vel[2];

    dx = __builtin_abs(actor->x - *(s16 *)((u8 *)vec + 2));
    if (dx < 0x10) {
        dy = __builtin_abs(actor->y - *(s16 *)((u8 *)vec + 6));
        if (dy < 0x10) {
            *(u16 *)((u8 *)actor - 2) |= 0x8000;
            D_800814A0[0] |= 0x8000;
        }
    }

    sprite->color[0] = actor->color[0] * actor->scale / actor->divisor;
    sprite->color[1] = actor->color[1] * actor->scale / actor->divisor;
    clamped = sprite->size0;
    size = clamped - 0xC8;
    clamped = size;
    sprite->color[2] = actor->color[2] * actor->scale / actor->divisor;
    if ((s16)size < 0) {
        clamped = 0;
    }
    sprite->size0 = clamped;
    sprite->size1 = clamped;
    actor->scale = (u16)actor->scale - 8;
    func_800478B8(sprite);
    if (actor->scale <= 0) {
        *(u16 *)((u8 *)actor - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
