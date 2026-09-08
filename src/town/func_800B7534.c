#include "common.h"

extern u8 D_800D1760[];
extern void func_800491F4(void *a0, void *a1, s32 a2);

/* Processes the target with D_800D1760 and parameter 41. */
void func_800B4C94(void *target) {
    func_800491F4(target, D_800D1760, 41);
}
