/* Rec_func_80167A98_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80167A98:arg0; 2 functions (dungeon 2); span 0x74.
 * Reached as a parameter in: func_80167A98:arg0 (1), func_80167C74:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80167A98_ARG0_H
#define REC_FUNC_80167A98_ARG0_H

#include "common.h"

typedef struct Rec_func_80167A98_arg0 {
    u8 pad_00[0x12];
    s16 unk_12;
    u8 pad_14[0x4];
    s16 unk_18;
    u8 pad_1A[0x2];
    s16 unk_1C;
    u16 unk_1E;
    u8 pad_20[0x4];
    void * unk_24;
    u8 pad_28[0x34];
    s32 unk_5C;
    s32 unk_60;
    s32 unk_64;
    s32 unk_68;
    s32 unk_6C;
    s32 unk_70;
} Rec_func_80167A98_arg0;

#endif
