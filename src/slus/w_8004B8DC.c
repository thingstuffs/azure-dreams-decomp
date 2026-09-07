#include "common.h"

extern void func_8004B834(void);
extern void func_8003F320(void);
extern void func_800B6A0C(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4);

/* Trivial wrapper: calls func_8004B834(void), then func_8003F320(void), then
 * forwards the original a0-a3 plus a stack-passed 5th argument to func_800B6A0C. */
void func_8004B8DC(s32 a0, s32 a1, s32 a2, s32 a3, s32 a4)
{
    func_8004B834();
    func_8003F320();
    func_800B6A0C(a0, a1, a2, a3, a4);
}
