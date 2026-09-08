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

/* Advance effect motion, update its data, and set expiry flags when its timer runs out. */
void func_80EB886C(EffectState *effect, VecState *motion, void *update_data) {
    motion->x += motion->vx;
    motion->y += motion->vy;
    motion->z += motion->vz;
    func_800478B8(update_data);
    if ((s16)--effect->timer <= 0) {
        *(u16 *)((u8 *)effect - 2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
