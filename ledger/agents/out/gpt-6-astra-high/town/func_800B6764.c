#include "common.h"

extern unsigned char D_800D16BC[16];
extern void func_800491F4(void *a0, void *a1, int a2);

/* Pass the target and D_800D16BC to func_800491F4 with code 33. */
void func_800B3EC4(void *target)
{
    func_800491F4(target, D_800D16BC, 33);
}
