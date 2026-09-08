#include "common.h"

extern s16 func_800C2AE8();
extern void func_80033D08(void *arg0);
extern void func_800A7308(void *arg0, void *arg1, s32 arg2);
extern void func_80095388(void *arg0);

typedef void (*S_800A9C80_Callback)(void *, void *, s32);

/* Advances position and handles ground contact or continued motion. */
void func_800A73E0(void *entity, void *motion, s32 context) {
    s32 x;
    s32 velocity_x;
    s32 velocity_y;
    s32 velocity_z;
    u16 counter;
    S_800A9C80_Callback callback;

    x = *(s32 *)((u8 *)motion + 0x0);
    velocity_x = *(s32 *)((u8 *)motion + 0xC);
    velocity_y = *(s32 *)((u8 *)motion + 0x10);
    velocity_z = *(s32 *)((u8 *)motion + 0x14);
    x += velocity_x;
    *(s32 *)((u8 *)motion + 0x0) = x;
    *(s32 *)((u8 *)motion + 0x4) += velocity_y;
    *(s32 *)((u8 *)motion + 0x8) += velocity_z;
    if (func_800C2AE8(motion, velocity_y, velocity_z) < *(s16 *)((u8 *)motion + 0xA)) {
        *(s16 *)((u8 *)motion + 0xA) = func_800C2AE8(motion);
        counter = *(u16 *)((u8 *)entity + 0x90) - 1;
        *(u16 *)((u8 *)entity + 0x90) = counter;
        if ((s16)counter < 0) {
            func_80033D08(entity);
            callback = *(S_800A9C80_Callback *)((u8 *)entity + 0x54);
            callback(entity, motion, context);
            return;
        }
        func_800A7308(entity, motion, context);
        return;
    }
    func_80095388(motion);
}
