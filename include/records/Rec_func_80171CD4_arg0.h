/* Rec_func_80171CD4_arg0: record class from the struct census (tools/gen_records.py).
 * Provenance: param:dungeon:func_80171CD4:arg0; 2 functions (dungeon 2); span 0x9E.
 * Reached as a parameter in: func_80171CD4:arg0 (1), func_80172688:arg0 (1)
 * Every view here is one some function reads the offset with; member names are offsets
 * until evidence names them.  Regenerate, never hand-edit: the census is the source. */
#ifndef REC_FUNC_80171CD4_ARG0_H
#define REC_FUNC_80171CD4_ARG0_H

#include "common.h"

typedef struct Rec_func_80171CD4_arg0 {
    u8 pad_00[0x8C];
    s32 unk_8C;
    s32 unk_90;
    u8 pad_94[0x2];
    s16 unk_96;
    u8 pad_98[0x2];
    union { s8 as_s8; u8 as_u8; } unk_9A;   /* read as s8 by 1, u8 by 1 */
    s8 unk_9B;
    u8 pad_9C[0x1];
    s8 unk_9D;
} Rec_func_80171CD4_arg0;

#endif
