#include "common.h"

extern void func_80033AE8(s32 arg0);
extern s16 D_800D15C0[];

void func_800B074C(void)
{
    s32 index;
    s32 i;

    if (D_800D15C0[0] != 0) {
        index = 0;
        do {
            func_80033AE8(D_800D15C0[index]);
            index++;
        } while (D_800D15C0[index] != 0);
    }

    i = 0;
    do {
        func_80033AE8((0x03F40000 + (i * 0x2B0000)) >> 16);
        i++;
    } while (i < 54);

    func_80033AE8(0xD31);
}
