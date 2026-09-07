#include "common.h"

#ifdef NON_MATCHING
#define KEEP_VALUE(v) ((void)0)
#else
#define KEEP_VALUE(v) __asm__ __volatile__("" : "=r"(v) : "0"(v))
#endif

void func_8008D344(s8 *arg0, s32 arg1, s32 arg2, s32 arg3) {
    s32 value;

    value = 0x2C;
    arg0[0x9A] = value;
    arg0[0x9B] = 0;
    *(s32 *)(arg0 + 0x8C) = 0;
    if (arg3 == 0) {
        KEEP_VALUE(value);
        value++;
        arg0[0x9A] = value;
    }
}
