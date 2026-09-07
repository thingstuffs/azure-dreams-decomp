#include "common.h"

typedef struct Obj800A5BC0 {
    u8 pad0[8];
    s16 timer;
    u8 padA[6];
    s32 x;
    s32 dx;
    s32 y;
    s32 dy;
    s16 value;
} Obj800A5BC0;

extern s32 D_800814A0[3];
extern void func_800A2FCC(void *ctx, s32 x, s32 y, s32 value);

void func_800A3320(Obj800A5BC0 *obj, void *ctx)
{
    obj->timer--;
    if (obj->timer < 0) {
        *(u16 *)((u8 *)obj - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    obj->x += obj->dx;
    obj->y += obj->dy;
    obj->dx -= 16;
    obj->value = (obj->timer * 255) / 20;
    func_800A2FCC(ctx, obj->x, obj->y, obj->value);
}
