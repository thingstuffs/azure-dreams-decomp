#include "common.h"

/* Ring buffer of 32 history entries, each 0x18 (24) bytes; only offset 0 is
 * accessed elsewhere (func_8003F240), matching D_80083968's established layout. */
typedef struct {
    u8 unk00;
    u8 pad[0x17];
} Struct80083968;

extern u8 D_800814D0;
extern Struct80083968 D_80083968[32];

/* Two adjacent scalar globals (loaded/stored individually via $gp) that are
 * also treated as one small struct when their combined address is taken. */
extern s32 D_800814B0;
extern s32 D_800814B4;

/* >8B neighbour spanning 0x800814AC..0x800814B7 (established in w_8003D5A4.c),
 * used to synthesize the hi/lo address-of D_800814B0 (offset 4 into it) per
 * the dual-access-global split-declaration technique. */
extern u8 D_800814AC[12];

typedef struct {
    s32 f0;
    s32 f4;
} S_8003F2A4_pair;

typedef struct {
    u8 type;
    u8 pad[3];
    S_8003F2A4_pair *volatile ptr;
} S_8003F2A4;

/* Copy a type 6 ring-head entry's pair to globals and repoint it there, or clear the entry's type. */
void func_8003F2A4(S_8003F2A4 *entry) {
    if (entry->type != 6 ||
        entry != (S_8003F2A4 *)&D_80083968[D_800814D0]) {
        entry->type = 0;
        return;
    }
    D_800814B0 = entry->ptr->f0;
    D_800814B4 = entry->ptr->f4;
    entry->ptr = (S_8003F2A4_pair *)&D_800814AC[4];
}
