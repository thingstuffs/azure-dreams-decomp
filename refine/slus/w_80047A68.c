#include "common.h"

/* Already-matched callee (defined elsewhere): returns &D_800FC000[a0]. */
extern void *func_80047A44(int a0);

extern void func_800479D4(void *a0, void *a1, unsigned short a2);

/* Regular (>8B) global pointer accessed via %hi/%lo. */
extern void *D_80080A90[4];

/* Passes the indexed slot, global pointer, and low 16 bits of value to func_800479D4. */
void func_80047A68(int slot_index, int value)
{
    func_800479D4(func_80047A44(slot_index), D_80080A90[0], (unsigned short)value);
}
