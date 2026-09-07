#include "common.h"

extern u32 D_800D66E8[3];
extern s32 D_800D66F0[3];
extern s32 D_800D6718[3];
extern s32 D_800D671C[3];
extern void func_800C3050(void *, s32, void *, void *, void *, void *);

void func_800CAB44(void *arg0, s32 arg1, s16 *arg2) {
    func_800C3050(arg0, 0x4F, D_800D6718, D_800D671C, D_800D66E8, D_800D66F0);
    arg2[9] = 3;
    ((u8 *)arg0)[0x70] = 2;
}
