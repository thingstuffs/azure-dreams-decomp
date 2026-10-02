#include "common.h"

extern void func_800B2280(void *arg0, s32 arg1, s32 arg2);

/* Calls func_800B2280 with D_8001029C and fixed parameters 0 and 20. */
void func_800B2344(void) {
    func_800B2280((void *)0x8001029C, 0, 20);
}
