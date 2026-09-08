#include "common.h"

/* S_80016000: opaque >8B blob (16 bytes) whose address is passed around by
   this wave's siblings; no fields are dereferenced inside THIS function
   (field accesses happen inside the callees, not decompiled in this wave). */
extern u8 D_80016000[0x10];

/* S_8008152C: <=8B global (gp-relative store in THIS TU) that simply holds
   a pointer value published by the sibling wrappers. */
extern void *D_8008152C;

extern void func_80046F88(void *a0);
extern void func_80047054(void *a0, u16 a1, u16 a2, u16 a3);

/* Advances the effect state, applies a fixed effect, and publishes the state pointer. */
void advanceEffectState(void)
{
    func_80046F88(&D_80016000);
    func_80047054(&D_80016000, 0xB, 0x7900, 0xD);
    D_8008152C = &D_80016000;
}
