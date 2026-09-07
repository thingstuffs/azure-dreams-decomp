#include "common.h"

extern s16 D_8001F668[];
extern u8 D_8001F6A8[];

s32 func_8001ABC8(s16 arg0, s16 arg1)
{
    s32 i;
    s32 first;
    s32 second;
    u8 *base;
    u8 *pair;
    u8 value;

    i = D_8001F668[0] - 1;
    if (i >= 0) {
        first = arg0;
        second = arg1;
        base = D_8001F6A8;
        pair = base + i * 2;
        do {
            value = pair[0];
            if (((value == first) || (value == second)) &&
                (((value = pair[1]) == first) || (value == second))) {
                return 1;
            }
            i--;
            pair -= 2;
        } while (i >= 0);
    }

    return 0;
}
