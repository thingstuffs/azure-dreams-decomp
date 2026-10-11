#include "common.h"

/* Resource flag and load helpers. */

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void func_8004B530(unsigned short *object)
{
    unsigned short *flags;
    if (object != 0) {
        flags = object - 1;
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}

/* --- wave-60 --- */

/* Ring-buffer size accumulator. */
extern int D_80080A7C;

/* Adds the amount to the global accumulator. */
void func_8004066C(int amount)
{
    D_80080A7C = D_80080A7C + amount;
}


extern void file_load_com(void *arg);

typedef struct { u32 word; } PackedLoc;
extern PackedLoc D_80080B9C;

/* Passes the global buffer to file_load_com. */
void func_80050FCC(void)
{
    file_load_com(&D_80080B9C);
}

extern int D_800814A0;

/* Sets bit 0x8000 in the object's preceding flags and global flags if non-NULL. */
void func_8004B1A4(unsigned short *object)
{
    unsigned short *flags;
    if (object != 0) {
        flags = object - 1;
        *flags |= 0x8000;
        D_800814A0 |= 0x8000;
    }
}
