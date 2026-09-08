/* Rec_func_8002290C_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:main:func_8002290C:arg0; 2 functions (main 2); span 0x8E4.
 * Reached as a parameter in: func_8002290C:arg0 (1), func_80022C48:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8002290C_ARG0_H
#define REC_FUNC_8002290C_ARG0_H

#include "common.h"

typedef struct Rec_func_8002290C_arg0 {
    u8 pad_00[0x8];
    s32 unk_08;
    s32 unk_0C;
    u8 pad_10[0x4];
    s32 unk_14;
    u8 pad_18[0x8];
    s32 unk_20;
    u8 pad_24[0x8BC];
    void * unk_8E0;
} Rec_func_8002290C_arg0;

#endif
