/* Rec_func_80097D54_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:town:func_80097D54:arg0; 2 functions (town 2); span 0x20.
 * Reached as a parameter in: func_80097D54:arg0 (1), func_800983BC:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80097D54_ARG0_H
#define REC_FUNC_80097D54_ARG0_H

#include "common.h"

typedef struct Rec_func_80097D54_arg0 {
    u8 pad_00[0xA];
    u16 unk_0A;
    u8 pad_0C[0x4];
    s16 unk_10;
    u8 pad_12[0xA];
    s32 unk_1C;
} Rec_func_80097D54_arg0;

#endif
