/* Rec_func_800381D0_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:slus:func_800381D0:arg0; 2 functions (slus 2); span 0x2F.
 * Reached as a parameter in: func_800381D0:arg0 (1), func_80039148:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800381D0_ARG0_H
#define REC_FUNC_800381D0_ARG0_H

#include "common.h"
#include "m2c_compat.h"   /* M2C_UNK* views: rows that never needed the compat header still compile */

typedef struct Rec_func_800381D0_arg0 {
    u8 pad_00[0x10];
    M2C_UNK * unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0x2];
    u8 * unk_1C;
    s16 unk_20;
    s16 unk_22;
    u8 pad_24[0x1];
    u8 unk_25;
    u8 pad_26[0x8];
    u8 unk_2E;
} Rec_func_800381D0_arg0;

#endif
