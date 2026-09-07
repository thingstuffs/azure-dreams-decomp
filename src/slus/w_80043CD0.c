#include "common.h"

/* D_8008148C and D_80081480 are accessed via %hi/%lo (not $gp-relative) in
 * the target asm, so their containing symbols must be larger than the -G8
 * small-data threshold; declare them as (oversized) structs so gcc/as emit
 * direct %hi/%lo addressing instead of a $gp-relative load/store. Only the
 * leading word (field_0) is touched by this function or its siblings. */
struct S_80081480 { s32 field_0; s8 pad[8]; };
struct S_8008148C { s32 field_0; s8 pad[8]; };

extern struct S_80081480 D_80081480;
extern struct S_8008148C D_8008148C;

/* Next function in the binary; its address is registered as the next
 * per-frame callback. */
extern void func_80043D04(void);

/* Registers a function-pointer callback (matched, gcc 2.8.1, src/code2.c). */
extern void func_80040A88(void (*a0)(void));

/* Copies D_8008148C's leading word into D_80081480, then registers
 * func_80043D04 as the next callback via func_80040A88. */
void func_80043CD0(void)
{
    D_80081480.field_0 = D_8008148C.field_0;
    func_80040A88(func_80043D04);
}
