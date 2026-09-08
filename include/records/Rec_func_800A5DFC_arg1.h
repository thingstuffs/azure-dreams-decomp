/* Rec_func_800A5DFC_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800A5DFC:arg1; 2 functions (dungeon 2); span 0x18.
 * Reached as a parameter in: func_800A5DFC:arg1 (1), func_801721B0:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800A5DFC_ARG1_H
#define REC_FUNC_800A5DFC_ARG1_H

#include "common.h"

typedef struct Rec_func_800A5DFC_arg1 {
    u8 pad_00[0x2];
    s16 unk_02;
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Rec_func_800A5DFC_arg1;

#endif
