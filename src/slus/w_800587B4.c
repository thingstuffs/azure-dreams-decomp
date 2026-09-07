#include "common.h"

/* extern/typedef decls */
/* D_80085FA4: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (func_800589B8, func_800599B0, func_80058940, func_80058B70) -> declare size > 8 bytes. */
extern s32 D_80085FA4[4];

/* D_800869B0: accessed via %hi/%lo (not gp_rel) in this and sibling funcs
 * (func_800589B8, func_80058940, func_80058B70) -> declare size > 8 bytes. */
extern s32 D_800869B0[4];

/* D_800737A4: hi/lo access -> size must be > 8 bytes (see func_800584E4 in src/code.c) */
extern s32 D_800737A4[4];

extern void func_80056C30(void);
extern void func_800599B0(void);

/* Initialization routine: sets up a couple of global state words (an address-like
 * value and a flags/size value), runs two subsystem init routines, then marks a
 * global flag/counter as active. */
void func_800587B4(void)
{
    D_80085FA4[0] = 0x80080000;
    D_800869B0[0] = 0xC000;
    func_80056C30();
    func_800599B0();
    D_800737A4[0] = 1;
}
