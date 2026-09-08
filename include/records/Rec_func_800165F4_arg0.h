/* Rec_func_800165F4_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_800165F4:arg0; 5 functions (town 5); span 0x1A.
 * Reached as a parameter in: func_80016F2C:arg0 (1), func_80016FF8:arg0 (1), func_80017490:arg0 (1), func_8001762C:arg0 (1), func_80019B54:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800165F4_ARG0_H
#define REC_FUNC_800165F4_ARG0_H

#include "common.h"

typedef struct Rec_func_800165F4_arg0 {
    u8 pad_00[0x10];
    s32 unk_10;
    u8 pad_14[0x4];
    s16 unk_18;
} Rec_func_800165F4_arg0;

#endif
