/* Rec_func_80173DD4_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80173DD4:arg0; 2 functions (dungeon 2); span 0xAE.
 * Reached as a parameter in: func_80173DD4:arg0 (1), func_80175060:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80173DD4_ARG0_H
#define REC_FUNC_80173DD4_ARG0_H

#include "common.h"

typedef struct Rec_func_80173DD4_arg0 {
    u8 pad_00[0x88];
    u16 unk_88;
    u8 pad_8A[0x2];
    void * unk_8C;
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0xA];
    u16 unk_A6;
    u8 pad_A8[0x4];
    s16 unk_AC;
} Rec_func_80173DD4_arg0;

#endif
