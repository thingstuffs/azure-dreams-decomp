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

/* If a0 is a "type 6" entry that is currently the ring-buffer head slot,
 * copy its pointed-to pair (f0,f4) out into the globals D_800814B0/B4 and
 * repoint a0's pointer at those globals. Otherwise clear a0's type byte. */
void func_8003F2A4(S_8003F2A4 *a0) {
    if (a0->type != 6 ||
        a0 != (S_8003F2A4 *)&D_80083968[D_800814D0]) {
        a0->type = 0;
        return;
    }
    D_800814B0 = a0->ptr->f0;
    D_800814B4 = a0->ptr->f4;
    a0->ptr = (S_8003F2A4_pair *)&D_800814AC[4];
}
