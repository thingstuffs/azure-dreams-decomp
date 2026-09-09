#include "common.h"

/* --- gcc 2.7.2 -O2 -G0 -fno-schedule-insns translation unit --- */

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void func_8004B530(unsigned short *object)
{
    if (object != 0) {
        object[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* --- wave-60 --- */

/* D_80080A7C is a small scalar, but this TU is compiled with -G0 (small-data
 * disabled), so gcc addresses it via lui/%hi + lw/sw/%lo instead of via $gp. */
extern int D_80080A7C;

/* Adds the amount to the global accumulator. */
void func_8004066C(int amount)
{
    D_80080A7C = D_80080A7C + amount;
}


extern void file_load_com(void *arg);

typedef struct {
    unsigned char data[16];
} D_80080B9C_t;

extern D_80080B9C_t D_80080B9C;

/* Passes the global buffer to file_load_com. */
void func_80050FCC(void)
{
    file_load_com(&D_80080B9C);
}

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void func_8004B1A4(unsigned short *object)
{
    if (object != 0) {
        object[-1] |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
