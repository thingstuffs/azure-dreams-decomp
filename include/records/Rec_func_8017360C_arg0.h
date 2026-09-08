/* Rec_func_8017360C_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_8017360C:arg0; 2 functions (dungeon 2); span 0xA4.
 * Reached as a parameter in: func_80173AAC:arg0 (1), func_80173E00:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_8017360C_ARG0_H
#define REC_FUNC_8017360C_ARG0_H

#include "common.h"

typedef struct Rec_func_8017360C_arg0 {
    u8 pad_00[0x8C];
    union { u8 * as_pu8; void * as_pv; } unk_8C;   /* read as u8 * by 1, void * by 1 */
    u8 pad_90[0x2];
    u16 unk_92;
    u8 pad_94[0x7];
    u8 unk_9B;
    u8 pad_9C[0x2];
    u16 unk_9E;
    u8 pad_A0[0x2];
    u16 unk_A2;
} Rec_func_8017360C_arg0;

#endif
