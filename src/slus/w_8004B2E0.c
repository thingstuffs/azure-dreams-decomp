#include "common.h"

/* Decrements the counter at *a1; when it is still nonzero afterward, sets
 * the "used"/flag bit (0x8000) both on the 16-bit flags field located one
 * halfword before a0, and on the global 32-bit flags word D_800814A0.
 * Sibling of func_8004B530/func_8004B1A4 (code5.c, gcc 2.7.2 -O2 -G0
 * -fno-schedule-insns TU) which share the identical tail. */
extern int D_800814A0;

void func_8004B2E0(unsigned short *a0, int *a1)
{
    if (--(*a1) != 0) {
        a0[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
