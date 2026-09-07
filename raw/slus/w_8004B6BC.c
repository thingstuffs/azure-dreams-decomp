#include "common.h"

extern void func_8004B634(void);
extern void func_8003F320(void);
extern void func_800253A0(void *a0, void *a1, s32 a2, void *a3);

/* Trivial wrapper: calls func_8004B634(void), then func_8003F320(void), then
 * forwards a0,a1,constant 2, and the original a2 (renamed a3) to func_800253A0. */
void func_8004B6BC(void *a0, void *a1, void *a2)
{
    func_8004B634();
    func_8003F320();
    func_800253A0(a0, a1, 2, a2);
}
