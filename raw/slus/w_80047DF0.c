#include "common.h"

/* Regular (>8B) globals accessed via %hi/%lo. */
extern unsigned char D_80016000[0x10];
extern unsigned char D_80023000[0x10];

/* <=8B global -> $gp small-data store (as -G8 sees size<=8 for this symbol
   in this TU, so the store to it is gp-relative). */
extern void *D_8008152C;

extern void *uploadImageTiles(void *a0, unsigned short a1, int a2, int a3, void *a4);

/* Calls uploadImageTiles with two fixed globals and three fixed constants, storing
   the result into D_8008152C. */
void func_80047DF0(void)
{
    D_8008152C = uploadImageTiles(&D_80016000, 0xB, 0x7900, 0xD, &D_80023000);
}
