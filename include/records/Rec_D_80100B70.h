/* Rec_D_80100B70: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_80100B70; 2 functions (town 2); span 0x70.
 * Reached as a parameter in: func_800A12B4:arg0 (1), func_800A1354:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_80100B70_H
#define REC_D_80100B70_H

#include "common.h"

typedef struct Rec_D_80100B70 {
    u8 pad_00[0x10];
    s16 unk_10;
    u16 unk_12;
    u8 pad_14[0x5A];
    u16 unk_6E;
} Rec_D_80100B70;

#endif
