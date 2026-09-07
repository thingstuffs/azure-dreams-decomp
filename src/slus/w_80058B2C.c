#include "common.h"

extern int func_800589B8(int a0);
extern int func_80058AA8(int a0, int a1);

/* Calls func_800589B8 twice with the same argument (its internal state
   changes between calls), then combines the low bytes of both results via
   func_80058AA8, returning the low 16 bits. */
int func_80058B2C(int a0)
{
    int v0;
    int v1;

    v0 = func_800589B8(a0);
    v1 = func_800589B8(a0);
    return func_80058AA8(v0 & 0xFF, v1 & 0xFF) & 0xFFFF;
}
