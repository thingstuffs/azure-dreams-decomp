/* Rec_func_80025D28_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80025D28:arg0; 2 functions (dungeon 2); span 0x42.
 * Reached as a parameter in: func_80025D28:arg0 (2)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80025D28_ARG0_H
#define REC_FUNC_80025D28_ARG0_H

#include "common.h"

typedef struct Rec_func_80025D28_arg0 {
    u8 unk_00;
    s8 unk_01;
    s8 unk_02;
    s8 unk_03;
    s32 unk_04;
    u8 pad_08[0x2];
    s8 unk_0A;
    s8 unk_0B;
    u8 pad_0C[0x10];
    s16 unk_1C;
    s16 unk_1E;
    s16 unk_20;
    u8 pad_22[0xE];
    u16 unk_30;
    u8 pad_32[0x2];
    u16 unk_34;
    s16 unk_36;
    s16 unk_38;
    u8 pad_3A[0x4];
    s16 unk_3E;
    s16 unk_40;
} Rec_func_80025D28_arg0;

#endif
