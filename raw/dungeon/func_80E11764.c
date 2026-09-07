#include "common.h"

extern void func_800478B8(void *);
extern s32 func_800644B8(s16);
extern s32 func_80064584(s16);
extern s32 D_800814A0[];

void func_80174F64(u16 *arg0, s32 *arg1, u8 *arg2)
{
    s32 product;

    arg0[0]++;
    func_800478B8(arg2);
    if (*(u16 *)(arg2 + 0x14) & 0x6000) {
        arg0[-1] |= 0x8000;
        D_800814A0[0] |= 0x8000;
        return;
    }

    arg0[3] += arg0[4];
    arg1[0] = arg1[3] + (((func_80064584((s16)arg0[2]) >> 4) *
                           (s16)arg0[3]) << 8);
    product = (func_800644B8((s16)arg0[2]) >> 4) * (s16)arg0[3];
    *(u16 *)((u8 *)arg1 + 0xA) -= 2;
    arg1[1] = arg1[4] + (product << 8);
}
