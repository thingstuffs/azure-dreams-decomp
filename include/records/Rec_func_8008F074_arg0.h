/* Rec_func_8008F074_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_8008F074:arg0; 2 functions (town 2); span 0x54.
 * Reached as a parameter in: func_8008F074:arg0 (1), func_800BF9E4:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8008F074_ARG0_H
#define REC_FUNC_8008F074_ARG0_H

#include "common.h"

typedef struct Rec_func_8008F074_arg0 {
    u8 pad_00[0x14];
    s8 unk_14;
    u8 pad_15[0x33];
    s32 unk_48;
    u8 pad_4C[0x4];
    s32 unk_50;
} Rec_func_8008F074_arg0;

#endif
