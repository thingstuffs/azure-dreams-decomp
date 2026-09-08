/* Rec_D_800FE490: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_800FE490; 2 functions (town 2); span 0x16.
 * Reached as a parameter in: func_8008FD48:arg0 (1), func_80095910:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_800FE490_H
#define REC_D_800FE490_H

#include "common.h"

typedef struct Rec_D_800FE490 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s8 unk_14;
    s8 unk_15;
} Rec_D_800FE490;

#endif
