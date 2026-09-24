#include "slus/cd_cohort_types.h"

/* Two adjacent scalar globals (loaded/stored individually via $gp) that are
 * also treated as one small struct when their combined address is taken. */

/* >8B neighbour spanning 0x800814AC..0x800814B7 (established in w_8003D5A4.c),
 * used to synthesize the hi/lo address-of D_800814B0 (offset 4 into it) per
 * the dual-access-global split-declaration technique. */
extern u8 D_800814AC[12];

typedef struct {
    s32 f0;
    s32 f4;
} S_8003F2A4_pair;

/* Copy a type 6 ring-head entry's pair to globals and repoint it there, or clear the entry's type. */
void func_8003F2A4(SlusCdQueueEntry *entry) {
    if (entry->unk00 != 6 ||
        entry != &D_80083968[D_800814D0]) {
        entry->unk00 = 0;
        return;
    }
    D_800814B0 = ((S_8003F2A4_pair *)(*(u32 *)((u8 *)entry + 4)))->f0;
    D_800814B4 = ((S_8003F2A4_pair *)(*(u32 *)((u8 *)entry + 4)))->f4;
    (*(u32 *)((u8 *)entry + 4)) = (u32)&D_800814AC[4];
}
