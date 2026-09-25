#include "common.h"

extern s32 D_80081480;
extern s32 D_8008148C;

/* Next function in the binary; its address is registered as the next
 * per-frame callback. */
extern void func_80043D04(void);

/* Registers a function-pointer callback (matched, gcc 2.8.1, src/code2.c). */
extern void func_80040A88(void (*a0)(void));

/* Copies D_8008148C's leading word into D_80081480 and registers func_80043D04 as the next callback. */
void func_80043CD0(void)
{
    D_80081480 = D_8008148C;
    func_80040A88(func_80043D04);
}
