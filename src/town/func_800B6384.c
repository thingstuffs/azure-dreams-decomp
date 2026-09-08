#include "common.h"

#ifdef NON_MATCHING
#define COMPILER_BARRIER() ((void)0)
#define KEEP_COMPILER(var) ((void)0)
#else
#define COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")
#define KEEP_COMPILER(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

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
    COMPILER_BARRIER();
    channel_value = blended_value;
    KEEP_COMPILER(channel_value);
    object[0x25] = blended_value;
    object[0x26] = channel_value;
}
