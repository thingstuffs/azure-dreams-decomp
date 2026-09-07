#include "common.h"

extern void func_80033AE8(s32 arg0);
extern s16 D_800D253C[66];
extern s16 D_800D25C0[66];

void func_800C0D80(void) {
    if (D_800D253C[0] != 0) {
        s32 index = 0;

        do {
            func_80033AE8(D_800D253C[index]);
            func_80033AE8(D_800D25C0[index]);
            index++;
        } while (D_800D253C[index] != 0);
    }
}

/* MECHANISM: The entry guard is a direct halfword read and the guarded do-while
   shares one array index across the two calls and the next-element sentinel.
   Strength reduction is intended to derive the retail advancing s0/s1 bases. */
