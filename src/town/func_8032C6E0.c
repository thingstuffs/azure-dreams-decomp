#include "common.h"

extern void func_8001ACA0(s16 *result);

#ifdef NON_MATCHING
#define EMPTY_BARRIER() ((void)0)
#else
#define EMPTY_BARRIER() __asm__ __volatile__("")
#endif

s32 func_80016EE0(void) {
    s16 result[4];
    s32 second;

    func_8001ACA0(result);
    if (result[0] < 0xF45) {
        second = result[1];
        if (second >= 0x1127) {
            EMPTY_BARRIER();
            return 0;
        }
        return 1;
    }
    return 1;
}
