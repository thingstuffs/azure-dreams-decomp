/* Rec_func_800D4BD4_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800D4BD4:arg1; 3 functions (dungeon 3); span 0x42.
 * Reached as a parameter in: func_800D4BD4:arg1 (1), func_800D4DE8:arg0 (1), func_800D5294:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800D4BD4_ARG1_H
#define REC_FUNC_800D4BD4_ARG1_H

#include "common.h"

typedef struct Rec_func_800D4BD4_arg1 {
    void * unk_00;
    u8 pad_04[0x8];
    s32 unk_0C;
    u8 pad_10[0x6];
    u16 unk_16;
    u8 pad_18[0x6];
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x14];
    u16 unk_3C;
    u16 unk_3E;
    u16 unk_40;
} Rec_func_800D4BD4_arg1;

#endif
