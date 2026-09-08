#include "common.h"

extern void func_80033AE8(s32 arg0);
extern s16 D_800D15C0[];

/* Processes the terminated ID list, 54 evenly spaced IDs, and ID 0xD31. */
void func_800B074C(void)
{
    s32 list_index;
    s32 range_index;

    if (D_800D15C0[0] != 0) {
        list_index = 0;
        do {
            func_80033AE8(D_800D15C0[list_index]);
            list_index++;
        } while (D_800D15C0[list_index] != 0);
    }

    range_index = 0;
    do {
        func_80033AE8((0x03F40000 + (range_index * 0x2B0000)) >> 16);
        range_index++;
    } while (range_index < 54);

    func_80033AE8(0xD31);
}
