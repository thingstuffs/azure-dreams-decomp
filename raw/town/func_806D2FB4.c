#include "common.h"

extern void func_80016D20(s32);

void func_800167B4(s16 *arg0, s32 count)
{
    volatile s32 frame_pad[2];
    s32 i;
    s16 *pairs;

    i = 0;
    if (count > 0) {
        pairs = arg0;
        do {
            func_80016D20(pairs[0]);
            i++;
            func_80016D20(pairs[1]);
            pairs += 2;
        } while (i < count);
    }
}
