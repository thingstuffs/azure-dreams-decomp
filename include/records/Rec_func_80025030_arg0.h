/* Rec_func_80025030_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:main:func_80025030:arg0; 2 functions (main 2); span 0x50.
 * Reached as a parameter in: func_8002592C:arg0 (1), func_8002593C:object (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80025030_ARG0_H
#define REC_FUNC_80025030_ARG0_H

#include "common.h"

typedef struct Rec_func_80025030_arg0 {
    u8 pad_00[0x20];
    s32 unk_20;
    u8 pad_24[0x4];
    s32 unk_28;
    u8 pad_2C[0x4];
    s32 unk_30;
    u8 pad_34[0x10];
    s32 unk_44;
    s32 unk_48;
    s32 unk_4C;
} Rec_func_80025030_arg0;

#endif
