/* Rec_func_8009CD18_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_8009CD18:arg1; 2 functions (town 2); span 0x22.
 * Reached as a parameter in: func_800A6DA0:arg2 (1), func_800A6E1C:arg2 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8009CD18_ARG1_H
#define REC_FUNC_8009CD18_ARG1_H

#include "common.h"

typedef struct Rec_func_8009CD18_arg1 {
    u8 pad_00[0x16];
    s16 unk_16;
    u8 pad_18[0x4];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
} Rec_func_8009CD18_arg1;

#endif
