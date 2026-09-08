#include "common.h"

extern void func_800B2280(void *arg0, s32 arg1, s32 arg2);
extern u8 D_8001029C[];

__asm__(".set D_8001029C, 0x8001029C");

/* Calls func_800B2280 with D_8001029C and fixed parameters 0 and 20. */
void func_800B2344(void) {
    func_800B2280(D_8001029C, 0, 20);
}
