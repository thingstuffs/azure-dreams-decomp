#include "common.h"

typedef struct {
    s32 x;
    s32 y;
    s32 z;
    s32 dx;
    s32 dy;
    s32 dz;
} Motion;

typedef struct {
    u8 pad0[0x48];
    u16 counter;
} Actor;

extern void func_800478B8(s32 arg0);
extern void func_8003DB94(s32 arg0, void *arg1, s32 arg2);
extern s32 D_800814A0;
extern s32 D_800E9E14[];
extern s32 D_800E9E34[];

/* Advance motion, update every eighth tick, and flag zero horizontal velocity. */
void func_800BD898(Actor *actor, Motion *motion, s32 actor_id) {
    u16 tick;

    func_800478B8(actor_id);
    motion->x += motion->dx;
    motion->y += motion->dy;
    motion->z += motion->dz;

    tick = (actor->counter + 1) & 7;
    actor->counter = tick;
    if (tick == 0) {
        if (motion->dz < 0) {
            func_8003DB94(actor_id, D_800E9E34, 0);
        } else {
            func_8003DB94(actor_id, D_800E9E14, 0);
        }
    }
    if (motion->dx == 0) {
        *(u16 *)((u8 *)actor - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
