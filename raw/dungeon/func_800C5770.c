#include "common.h"

extern s32 D_800814A0[3];
extern s16 func_800BCB04(u16, u16, s16);

void func_800CAED0(void *arg0, void *arg1) {
    s16 result;
    u16 timer;

    result = func_800BCB04(((u16 *)arg1)[1], ((u16 *)arg1)[3], (s16)(((u16 *)arg1)[5] + 2));
    if ((s16)((u16 *)arg1)[5] < result) {
        ((s32 *)arg1)[0] += ((s32 *)arg1)[3];
        ((s32 *)arg1)[1] += ((s32 *)arg1)[4];
        ((s32 *)arg1)[2] += ((s32 *)arg1)[5];
        ((s32 *)arg1)[3] -= ((s32 *)arg1)[3] >> 2;
        ((s32 *)arg1)[4] -= ((s32 *)arg1)[4] >> 2;
        ((s32 *)arg1)[5] += 0x8000;
    } else {
        ((u16 *)arg1)[5] = result;
    }
    timer = ((u16 *)arg0)[0x4B] - 8;
    ((u16 *)arg0)[0x4B] = timer;
    if ((timer << 16) <= 0) {
        ((u16 *)arg0)[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
