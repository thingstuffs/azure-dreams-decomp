#include "common.h"

/* Already-matched callee (defined elsewhere): returns &D_800FC000[a0]. */
extern void *func_80047A44(int a0);

extern void func_800479D4(void *a0, void *a1, unsigned short a2);

/* Regular (>8B) global pointer accessed via %hi/%lo. */
extern void *D_80080A90[4];

/* Looks up the a0'th large struct slot, then forwards it, the fixed global
   pointer, and the truncated a1 argument through to func_800479D4. */
void func_80047A68(int a0, int a1)
{
    func_800479D4(func_80047A44(a0), D_80080A90[0], (unsigned short)a1);
}
