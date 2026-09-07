#include "common.h"

typedef struct {
    s32 x, y, z;
    s32 vx, vy, vz;
} VecState;

typedef struct S_800814A0 {
    s32 val;
    s32 pad[2];
} S_800814A0;

extern u8 D_80045340[];
extern S_800814A0 D_800814A0;

void func_80024DD8(void) __attribute__((noreturn));
extern void func_8004491C(void *, u8 *);
extern void func_800478B8(void *);

void func_81845484(void *arg0, VecState *arg1, void *arg2) {
    void *temp_v1 = *(void **)arg0;
    s32 vz;
    s16 state;
    u16 timer;

    *(u16 *)((s8 *)temp_v1 + 0x52) |= 0x8000;

    vz = arg1->vz;
    if (vz != 0) {
        vz -= 0x20000;
    }
    arg1->vz = vz;
    arg1->x += arg1->vx;
    arg1->y += arg1->vy;
    arg1->z += arg1->vz;

    state = *(s16 *)((s8 *)arg0 + 0x4C);
    if (state != 0) {
        if (state == 1) {
            goto state_1;
        }
        func_80024DD8();
    }

    timer = *(u16 *)((s8 *)arg0 + 0x48) - 1;
    *(u16 *)((s8 *)arg0 + 0x48) = timer;
    if ((s16)timer <= 0) {
        func_8004491C((s8 *)arg0 - 0x20, D_80045340);
        *(u16 *)((s8 *)arg0 + 0x4C) += 1;
        func_80024DD8();
    }
    return;

state_1:
    func_800478B8(arg2);
    if (*(u16 *)((s8 *)arg2 + 0x14) & 0x6000) {
        *(s8 *)((s8 *)arg2 + 4) = 0;
        *(s8 *)((s8 *)arg2 + 5) = 0;
    }
    if (*(u8 *)((s8 *)arg2 + 0xC) <= *(s16 *)((s8 *)arg0 + 0x4A)) {
        *(u32 *)((s8 *)arg2 + 0xC) = 0;
        *(u16 *)((s8 *)arg0 - 2) |= 0x8000;
        D_800814A0.val |= 0x8000;
        func_80024DD8();
    }
    {
        u8 val = *(u8 *)((s8 *)arg2 + 0xE) - *(u8 *)((s8 *)arg0 + 0x4A);
        *(u8 *)((s8 *)arg2 + 0xE) = val;
        *(u8 *)((s8 *)arg2 + 0xD) = val;
        *(u8 *)((s8 *)arg2 + 0xC) = val;
    }
}
