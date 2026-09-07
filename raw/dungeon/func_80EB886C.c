#include "common.h"

typedef struct {
    u32 x;
    s32 y;
    s32 z;
    s32 vx;
    s32 vy;
    s32 vz;
} VecState;

typedef struct {
    u8 pad[0x48];
    u16 timer;
} EffectState;

extern void func_800478B8(void *arg0);
extern s32 D_800814A0[];

void func_80EB886C(EffectState *arg0, VecState *arg1, void *arg2) {
    arg1->x += arg1->vx;
    arg1->y += arg1->vy;
    arg1->z += arg1->vz;
    func_800478B8(arg2);
    if ((s16)--arg0->timer <= 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
