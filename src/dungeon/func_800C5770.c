#include "common.h"

extern s32 D_800814A0[3];
extern s16 func_800BCB04(u16, u16, s16);

/* Update damped motion with gravity, clamp to the floor, and flag expiration. */
void func_800CAED0(void *object, void *motion) {
    s16 floor_height;
    u16 lifetime;

    floor_height = func_800BCB04(((u16 *)motion)[1], ((u16 *)motion)[3], (s16)(((u16 *)motion)[5] + 2));
    if ((s16)((u16 *)motion)[5] < floor_height) {
        ((s32 *)motion)[0] += ((s32 *)motion)[3];
        ((s32 *)motion)[1] += ((s32 *)motion)[4];
        ((s32 *)motion)[2] += ((s32 *)motion)[5];
        ((s32 *)motion)[3] -= ((s32 *)motion)[3] >> 2;
        ((s32 *)motion)[4] -= ((s32 *)motion)[4] >> 2;
        ((s32 *)motion)[5] += 0x8000;
    } else {
        ((u16 *)motion)[5] = floor_height;
    }
    lifetime = ((u16 *)object)[0x4B] - 8;
    ((u16 *)object)[0x4B] = lifetime;
    if ((lifetime << 16) <= 0) {
        ((u16 *)object)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
