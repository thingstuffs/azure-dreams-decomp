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

/* Returns the record for the given category and item, or NULL if absent. */
S_800133E8 *func_8004A784(int category, int item)
{
    S_800133E8 *record = 0;
    int index = func_8004A6C0(category, item);

    if (index < 0x14) {
        record = (S_800133E8 *)0x800133E8 + index;
    }
    return record;
}
