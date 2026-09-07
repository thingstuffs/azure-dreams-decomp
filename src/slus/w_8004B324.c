#include "common.h"

extern void func_8004B298(void *a0, void *a1);
extern void func_8004B2E0(void *a0, void *a1);

/* Trivial wrapper: forwards both args unchanged to func_8004B298(a0,a1)
   then func_8004B2E0(a0,a1). */
void func_8004B324(void *a0, void *a1)
{
    func_8004B298(a0, a1);
    func_8004B2E0(a0, a1);
}
