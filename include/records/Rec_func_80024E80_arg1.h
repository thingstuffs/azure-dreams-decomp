/* Rec_func_80024E80_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80024E80:arg1; 2 functions (dungeon 2); span 0x14.
 * Reached as a parameter in: func_80024E80:arg1 (1), func_80025094:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80024E80_ARG1_H
#define REC_FUNC_80024E80_ARG1_H

#include "common.h"

typedef struct Rec_func_80024E80_arg1 {
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; s16 v; } at02_s16; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_08;   /* overlapping accesses */
    u8 pad_0C[0x2];
    u16 unk_0E;
    u8 pad_10[0x2];
    u16 unk_12;
} Rec_func_80024E80_arg1;

#endif
