#include "common.h"

extern void func_80016D20(s32);

// Pass each signed 16-bit value in the input pairs to func_80016D20 in order.
void func_800167B4(s16 *value_pairs, s32 pair_count)
{
    volatile s32 frame_pad[2];
    s32 pair_index;
    s16 *current_pair;

    pair_index = 0;
    if (pair_count > 0) {
        current_pair = value_pairs;
        do {
            func_80016D20(current_pair[0]);
            pair_index++;
            func_80016D20(current_pair[1]);
            current_pair += 2;
        } while (pair_index < pair_count);
    }
}
