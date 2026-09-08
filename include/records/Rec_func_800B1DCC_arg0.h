/* Rec_func_800B1DCC_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800B1DCC:arg0; 3 functions (town 3); span 0x1C.
 * Reached as a parameter in: func_800B1F80:arg0 (1), func_800B2068:arg0 (1), func_800B2400:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800B1DCC_ARG0_H
#define REC_FUNC_800B1DCC_ARG0_H

#include "common.h"

typedef struct Rec_func_800B1DCC_arg0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    s32 unk_18;
} Rec_func_800B1DCC_arg0;

#endif
