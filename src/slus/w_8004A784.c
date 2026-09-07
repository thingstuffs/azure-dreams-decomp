#include "common.h"

/* 19-byte-stride record table at 0x800133E8 (20 entries), immediately
   preceding the 4-byte {short,short} table D_80013564 (indexed the same
   way, by func_8004A6C0()). Not referenced anywhere else as a %hi/%lo
   symbol, so the retail code materializes its base as a raw 32-bit literal
   (lui;ori), not a &symbol reloc (lui;addiu) -- do the same here. */
typedef struct {
    char unk[0x13];
} S_800133E8;

extern int func_8004A6C0(int a0, int a1);

/* Returns &((S_800133E8*)0x800133E8)[func_8004A6C0(a0, a1)] if that index
   is valid (< 20), otherwise NULL. */
S_800133E8 *func_8004A784(int a0, int a1)
{
    S_800133E8 *result = 0;
    int i = func_8004A6C0(a0, a1);

    if (i < 0x14) {
        result = (S_800133E8 *)0x800133E8 + i;
    }
    return result;
}
