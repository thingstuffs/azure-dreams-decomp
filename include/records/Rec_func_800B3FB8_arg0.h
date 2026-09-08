/* Rec_func_800B3FB8_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800B3FB8:arg0; 2 functions (town 3); span 0x60.
 * Reached as a parameter in: func_800B3FB8:arg0 (2), func_800B43E8:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800B3FB8_ARG0_H
#define REC_FUNC_800B3FB8_ARG0_H

#include "common.h"

typedef struct Rec_func_800B3FB8_arg0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x38];
    s32 unk_5C;
} Rec_func_800B3FB8_arg0;

#endif
