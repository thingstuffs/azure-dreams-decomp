/* Rec_D_800287A4: record class from the struct census (tools/gen_records.py).
 * Provenance: global:D_800287A4; 2 functions (dungeon 2); span 0x2C.
 * Reached as a parameter in: func_8009D218:arg2 (1), func_800CB82C:arg2 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_D_800287A4_H
#define REC_D_800287A4_H

#include "common.h"

typedef struct Rec_D_800287A4 {
    u8 pad_00[0x13];
    s8 unk_13;
    u8 pad_14[0x16];
    u16 unk_2A;
} Rec_D_800287A4;

#endif
