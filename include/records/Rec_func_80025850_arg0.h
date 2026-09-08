/* Rec_func_80025850_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80025850:arg0; 2 functions (dungeon 3); span 0x58.
 * Reached as a parameter in: func_800259CC:arg0 (2), func_80026084:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80025850_ARG0_H
#define REC_FUNC_80025850_ARG0_H

#include "common.h"

typedef struct Rec_func_80025850_arg0 {
    u8 pad_00[0x8];
    s32 unk_08;
    u8 pad_0C[0xC];
    void * unk_18;
    u8 pad_1C[0x38];
    s32 unk_54;
} Rec_func_80025850_arg0;

#endif
