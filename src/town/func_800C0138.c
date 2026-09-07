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
extern void func_800BD92C(s32 arg0, void *arg1);
extern s32 D_800814A0;
extern s32 D_800E9E14[];
extern s32 D_800E9E34[];

void func_800BD898(Actor *arg0, Motion *arg1, s32 arg2) {
    u16 temp_v0;

    func_800478B8(arg2);
    arg1->x += arg1->dx;
    arg1->y += arg1->dy;
    arg1->z += arg1->dz;

    temp_v0 = (arg0->counter + 1) & 7;
    arg0->counter = temp_v0;
    if (temp_v0 == 0) {
        if (arg1->dz < 0) {
            func_800BD92C(arg2, D_800E9E34);
            return;
        }
        func_8003DB94(arg2, D_800E9E14, 0);
    }
    if (arg1->dx == 0) {
        *(u16 *)((u8 *)arg0 - 2) |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
