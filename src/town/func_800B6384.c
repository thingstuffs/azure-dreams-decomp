#include "common.h"


/* Moves the first color channel toward neutral gray and copies it to the other two. */
void func_800B3AE4(u8 *object) {
    s32 channel_value;
    s32 blended_value;
    s32 target_delta;

    channel_value = object[0x24];
    target_delta = 0x80 - channel_value;
    if (target_delta < 0) {
        target_delta += 3;
    }
    blended_value = channel_value + (target_delta >> 2);
    object[0x24] = blended_value;
    channel_value = blended_value;
    ASM_KEEP(channel_value);
    object[0x25] = blended_value;
    object[0x26] = channel_value;
}
