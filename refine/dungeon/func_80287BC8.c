#include "common.h"

extern s16 D_8001F668[];
extern u8 D_8001F6A8[];

/* Checks whether a stored pair contains only the two supplied values. */
s32 func_8001ABC8(s16 value_a, s16 value_b)
{
    s32 pair_index;
    s32 first;
    s32 second;
    u8 *pairs;
    u8 *pair;
    u8 value;

    pair_index = D_8001F668[0] - 1;
    if (pair_index >= 0) {
        first = value_a;
        second = value_b;
        pairs = D_8001F6A8;
        pair = pairs + pair_index * 2;
        do {
            value = pair[0];
            if (((value == first) || (value == second)) &&
                (((value = pair[1]) == first) || (value == second))) {
                return 1;
            }
            pair_index--;
            pair -= 2;
        } while (pair_index >= 0);
    }

    return 0;
}
