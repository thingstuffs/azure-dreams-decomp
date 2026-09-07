#include "common.h"

/* --- gcc 2.7.2 -O2 -G0 -fno-schedule-insns translation unit --- */

/* Sets a "used"/flag bit (0x8000) both on a 16-bit flags field located 2
 * bytes before the object pointer, and on a global 32-bit flags word, when
 * the object pointer is non-NULL. */
extern int D_800814A0;

void func_8004B530(unsigned short *a0)
{
    if (a0 != 0) {
        a0[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* --- wave-60 --- */

/* D_80080A7C is a small scalar, but this TU is compiled with -G0 (small-data
 * disabled), so gcc addresses it via lui/%hi + lw/sw/%lo instead of via $gp. */
extern int D_80080A7C;

/* Adds a0 to the running counter/accumulator at D_80080A7C. */
void func_8004066C(int a0)
{
    D_80080A7C = D_80080A7C + a0;
}


/* Wrapper that forwards the address of D_80080B9C to func_80041284. */
extern void func_80041284(void *arg);

typedef struct {
    unsigned char data[16];
} D_80080B9C_t;

extern D_80080B9C_t D_80080B9C;

void func_80050FCC(void)
{
    func_80041284(&D_80080B9C);
}

/* Sets a "used"/flag bit (0x8000) both on a 16-bit flags field located 2
 * bytes before the object pointer, and on a global 32-bit flags word, when
 * the object pointer is non-NULL. Identical sibling of func_8004B530
 * (code5.c), part of the gcc 2.7.2 -O2 -G0 -fno-schedule-insns TU. */
extern int D_800814A0;

void func_8004B1A4(unsigned short *a0)
{
    if (a0 != 0) {
        a0[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
