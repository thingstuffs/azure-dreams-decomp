#include "common.h"

extern void func_8001ACE8(s32);
extern void func_8001AD60(s32);

/* Dispatches consecutive indices to one of two handlers according to successive mask bits. */
void func_8001B168(s32 base, s32 bits, s32 count)
{
    s32 offset;

    for (offset = 0; offset < count; offset++) {
        if (bits & 1) {
            func_8001ACE8(base + offset);
        } else {
            func_8001AD60(base + offset);
        }
        bits >>= 1;
    }
}
