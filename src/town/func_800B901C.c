#include "common.h"

extern void func_800491F4(void *a0, void *a1, int a2);
extern u8 D_800D17C4[];

/* Passes the target and D_800D17C4 to func_800491F4 with argument 24. */
void func_800B677C(void *target) {
    func_800491F4(target, D_800D17C4, 24);
}
