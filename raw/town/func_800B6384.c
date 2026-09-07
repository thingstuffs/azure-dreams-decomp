#include "common.h"

#ifdef NON_MATCHING
#define COMPILER_BARRIER() ((void)0)
#define KEEP_COMPILER(var) ((void)0)
#else
#define COMPILER_BARRIER() __asm__ __volatile__("" : : : "memory")
#define KEEP_COMPILER(var) __asm__ __volatile__("" : "=r"(var) : "0"(var))
#endif

void func_800B3AE4(u8 *arg0) {
    s32 temp1;
    s32 temp0;
    s32 var;

    temp1 = arg0[0x24];
    var = 0x80 - temp1;
    if (var < 0) {
        var += 3;
    }
    temp0 = temp1 + (var >> 2);
    arg0[0x24] = temp0;
    COMPILER_BARRIER();
    temp1 = temp0;
    KEEP_COMPILER(temp1);
    arg0[0x25] = temp0;
    arg0[0x26] = temp1;
}
