#include "common.h"

extern s16 func_800C2AE8();
extern void func_80033D08(void *arg0);
extern void func_800A7308(void *arg0, void *arg1, s32 arg2);
extern void func_80095388(void *arg0);

typedef void (*S_800A9C80_Callback)(void *, void *, s32);

void func_800A73E0(void *arg0, void *arg1, s32 arg2) {
    s32 x;
    s32 velocity;
    s32 dx;
    s32 dy;
    u16 hp;
    S_800A9C80_Callback callback;

    x = *(s32 *)((u8 *)arg1 + 0x0);
    velocity = *(s32 *)((u8 *)arg1 + 0xC);
    dx = *(s32 *)((u8 *)arg1 + 0x10);
    dy = *(s32 *)((u8 *)arg1 + 0x14);
    x += velocity;
    *(s32 *)((u8 *)arg1 + 0x0) = x;
    *(s32 *)((u8 *)arg1 + 0x4) += dx;
    *(s32 *)((u8 *)arg1 + 0x8) += dy;
    if (func_800C2AE8(arg1, dx, dy) < *(s16 *)((u8 *)arg1 + 0xA)) {
        *(s16 *)((u8 *)arg1 + 0xA) = func_800C2AE8(arg1);
        hp = *(u16 *)((u8 *)arg0 + 0x90) - 1;
        *(u16 *)((u8 *)arg0 + 0x90) = hp;
        if ((s16)hp < 0) {
            func_80033D08(arg0);
            callback = *(S_800A9C80_Callback *)((u8 *)arg0 + 0x54);
            callback(arg0, arg1, arg2);
            return;
        }
        func_800A7308(arg0, arg1, arg2);
        return;
    }
    func_80095388(arg1);
}
