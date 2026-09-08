/* Rec_func_80024264_arg1: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80024264:arg1; 2 functions (dungeon 2); span 0x18.
 * Reached as a parameter in: func_81868B84:arg1 (1), func_80024264:arg1 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80024264_ARG1_H
#define REC_FUNC_80024264_ARG1_H

#include "common.h"

typedef struct Rec_func_80024264_arg1 {
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_00;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_04;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_08;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_0C;   /* overlapping accesses */
    union { struct { s32 v; } at00_s32; struct { u8 pad[0x2]; u16 v; } at02_u16; } unk_10;   /* overlapping accesses */
    s32 unk_14;
} Rec_func_80024264_arg1;

#endif
