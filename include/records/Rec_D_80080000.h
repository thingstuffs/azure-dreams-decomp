/* Rec_D_80080000: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80080000; 3 functions (dungeon 3); span 0x14A4.
 * Rooted at: D_80080000 (3)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80080000_H
#define REC_D_80080000_H

#include "common.h"

typedef struct Rec_D_80080000 {
    u8 pad_00[0x14A0];
    s32 unk_14A0;
} Rec_D_80080000;

#endif
