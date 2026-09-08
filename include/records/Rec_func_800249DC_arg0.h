/* Rec_func_800249DC_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_800249DC:arg0; 2 functions (dungeon 2); span 0x4A.
 * Reached as a parameter in: func_800249DC:arg0 (1), func_819ACB28:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_800249DC_ARG0_H
#define REC_FUNC_800249DC_ARG0_H

#include "common.h"

typedef struct Rec_func_800249DC_arg0 {
    union { struct { void * v; } at00_pv; struct { u8 pad[0x2]; s16 v; } at02_s16; } unk_00;   /* overlapping accesses */
    u8 pad_04[0x2];
    s16 unk_06;
    u8 pad_08[0x2];
    s16 unk_0A;
    u8 pad_0C[0x10];
    s32 unk_1C;
    s32 unk_20;
    s32 unk_24;
    u8 pad_28[0xC];
    s32 unk_34;
    s32 unk_38;
    s32 unk_3C;
    u8 pad_40[0x8];
    u16 unk_48;
} Rec_func_800249DC_arg0;

#endif
