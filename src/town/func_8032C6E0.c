#include "common.h"

extern void func_8001ACA0(s16 *result);


/* Return zero when result[0] is below 0xF45 and result[1] is at least 0x1127. */
s32 func_80016EE0(void) {
    s16 result[4];
    s32 second;

    func_8001ACA0(result);
    if (result[0] < 0xF45) {
        second = result[1];
        if (second >= 0x1127) {
            ASM_SCHED_BARRIER();
            return 0;
        }
        return 1;
    }
    return 1;
}
