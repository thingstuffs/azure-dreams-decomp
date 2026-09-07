#include "common.h"

extern unsigned char D_800D16BC[16];
extern void func_800491F4(void *a0, void *a1, int a2);

void func_800B3EC4(void *a0)
{
    func_800491F4(a0, D_800D16BC, 33);
}
