/* Rec_func_80173D78_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80173D78:arg0; 2 functions (dungeon 2); span 0xAD.
 * Reached as a parameter in: func_80173D78:arg0 (1), func_80175DD0:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80173D78_ARG0_H
#define REC_FUNC_80173D78_ARG0_H

#include "common.h"

typedef struct Rec_func_80173D78_arg0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
    u8 pad_2C[0x60];
    void * unk_8C;
    u8 pad_90[0x6];
    u16 unk_96;
    u8 pad_98[0x2];
    u8 unk_9A;
    u8 unk_9B;
    u8 pad_9C[0x8];
    void * unk_A4;
    u8 pad_A8[0x4];
    u8 unk_AC;
} Rec_func_80173D78_arg0;

#endif
