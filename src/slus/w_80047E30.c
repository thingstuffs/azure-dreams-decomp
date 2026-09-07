#include "common.h"

/* Advances D_80016000's internal state via func_80046F88, applies a fixed
   effect (0xB/0x7900/0xD) via func_80047054, then publishes D_80016000's
   address into D_8008152C. */
/* S_80016000: opaque >8B blob (16 bytes) whose address is passed around by
   this wave's siblings; no fields are dereferenced inside THIS function
   (field accesses happen inside the callees, not decompiled in this wave). */
extern u8 D_80016000[0x10];

/* S_8008152C: <=8B global (gp-relative store in THIS TU) that simply holds
   a pointer value published by the sibling wrappers. */
extern void *D_8008152C;

extern void func_80046F88(void *a0);
extern void func_80047054(void *a0, u16 a1, u16 a2, u16 a3);

void advanceEffectState(void)
{
    func_80046F88(&D_80016000);
    func_80047054(&D_80016000, 0xB, 0x7900, 0xD);
    D_8008152C = &D_80016000;
}
