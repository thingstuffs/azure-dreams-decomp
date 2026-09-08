#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} VecState;

typedef struct {
    u8 pad00[0x14];
    u16 counter;
} ChildState;

typedef struct {
    ChildState *child;
    u8 pad04[12];
    u16 counter;
    u8 pad12[2];
    s16 limit;
} OwnerState;

typedef struct {
    u8 pad00[0x1A];
    u16 angle;
} EntityState;

extern void func_800478B8(void *);
extern s32 D_800814A0[];

/* Advance counters, rotation, and position, and set flags when the counter exceeds its limit. */
void func_818B7D3C(OwnerState *owner, VecState *vec, EntityState *entity)
{
    owner->child->counter++;
    owner->counter++;
    func_800478B8(entity);
    entity->angle += 0x300;

    vec->x += vec->dx;
    vec->y += vec->dy;
    vec->z += vec->dz;

    if ((s16)owner->counter > owner->limit) {
        ((u16 *)owner)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
