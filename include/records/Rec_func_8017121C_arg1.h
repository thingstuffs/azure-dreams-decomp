/* Rec_func_8017121C_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_8017121C:arg1; 3 functions (dungeon 3); span 0x18.
 * Reached as a parameter in: func_8017121C:arg1 (1), func_801714FC:arg1 (1), func_801743C4:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8017121C_ARG1_H
#define REC_FUNC_8017121C_ARG1_H

#include "common.h"

typedef struct Rec_func_8017121C_arg1 {
    u8 pad_00[0x2];
    u16 unk_02;
    u8 pad_04[0x2];
    u16 unk_06;
    u8 pad_08[0x2];
    u16 unk_0A;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} Rec_func_8017121C_arg1;

#endif
