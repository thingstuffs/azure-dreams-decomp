#include "common.h"

extern int func_800B8C90(void *a0);
extern int func_80049374(void *a0, int *a1);

extern int D_80080B34[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */
extern int D_80080B40[4]; /* >8B forces %hi/%lo addressing (matches target's lui/addiu) */

/* Calls func_800B8C90(a0); selects one of two globals based on the boolean
 * result and forwards (a0, &global) to func_80049374, returning its result. */
int func_800494B4(void *a0)
{
    void *s0 = a0;
    int v0 = func_800B8C90(a0);
    int *a1;

    if (v0) {
        a1 = D_80080B34;
    } else {
        a1 = D_80080B40;
    }

    return func_80049374(s0, a1);
}
